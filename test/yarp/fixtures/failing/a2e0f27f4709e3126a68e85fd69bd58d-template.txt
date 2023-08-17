module REIformslive
  class Template
    require 'reiformslive/core_ext'

    PATH = '/templates'.freeze

    attr_reader :data, :path
    
    def initialize data: '{}'
      @data = data
    end

    def cost
      data['cost'].to_i
    end

    def active
      data['active']
    end

    def id
      data['id'].to_i
    end

    def name
      data['name']
    end

    def code
      data['code']
    end

    def template_group_id
      data['template_group_id'].to_i
    end

    def self.all
      REIformslive::Session
        .get(path: PATH)
        .parse_json
        .map{|data| self.new data: data }
    end

    def self.find id
      self.new data:
        REIformslive::Session
          .get(path: "#{PATH}/#{id}")
          .parse_json
    end
  end
end
