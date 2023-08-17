# frozen_string_literal: true

require_relative "ruby3/version"
require "dotenv/load"
require "net/http"
require "json"
module Slack
  module Ruby3
    class Error < StandardError; end
    def self.push webhook_url: "", message: "hoi!"
      uri = URI.parse(webhook_url)
      http = Net::HTTP.new(uri.host, uri.port)
      http.use_ssl = true
      http.verify_mode = OpenSSL::SSL::VERIFY_NONE
      req = Net::HTTP::Post.new(uri.path, initheader = { "Content-Type" => "application/json" })
      req.body = { text: message }.to_json
      status_code = http.request(req).code
      return "Sent Message: #{message}" if status_code.to_i == 200
      "Error Code: #{status_code}\nSomething wrong."
    end
  end
end
