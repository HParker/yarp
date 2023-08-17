require "htmon/agent/version"
require 'active_support/all'
require 'rest_client'
require 'logger'

module Htmon
  module Agent

    Check ||= Struct.new :callback, :interval, :launched_at

    def checks 
      @checks ||= []
    end

    def remote
      raise "Missing remote, fill ENV['htmon_api']" unless ENV['htmon_api']
      "#{ENV['htmon_api'].to_s.gsub(/\/$/,'')}/api/v1/metrics/"
    end

    def start config: nil
      load config
      logger = Logger.new(STDOUT)
      logger.info "Starting processing loop ..."
      loop do
        checks.each do |check|
          if check.launched_at.nil? or 
            (check.launched_at + check.interval).past?
            logger.debug "Fork check processing ..."
            Process.detach( fork { check.callback.call } )
            check.launched_at = Time.now
          end
        end
        sleep 0.2
      end
    end

    extend self

  end
end

# config related methods

def check interval: 60, &block
  Htmon::Agent.checks << Htmon::Agent::Check.new(block, interval)
end

def load_schema hostname: `hostname`.strip
  JSON.parse RestClient.get(Htmon::Agent.remote+
                            "schema?"+({hostname: hostname}).to_param)
end

def push url: nil, metric: nil, expires_after: nil, value: nil, 
  hostname: `hostname`.strip
  logger = Logger.new(STDOUT)
  
  url = "#{Htmon::Agent.remote}#{url}?"+({hostname: hostname,
                                          value: value,
                                          expire: expires_after,
                                          metric: metric }).to_param
  begin
    RestClient.post url, nil
  rescue RestClient::ExceptionWithResponse => err
    logger.error "Push to #{url.inspect} failed ..."
    logger.error err.response
  end
end

