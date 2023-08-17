module REIformslive
  class UserTemplate
    PATH = '/user-templates'.freeze

    attr_reader :data
    
    def initialize data: '{}'
      @data = data
    end

    def id
      data['id'].to_i
    end

    def template_version_id
      data['template_version_id'].to_i
    end

    def agency_id
      data['agency_id'].to_i
    end

    def user_id
      data['user_id'].to_i
    end

    def name
      data['name']
    end

    def template?
      data['template'].to_s == 'true'
    end

    def finalised?
      data['finalised'].to_s == 'true'
    end

    def private?
      data['private'].to_s == 'true'
    end

    def created_at
      Time.at data['created'].to_i
    end

    def updated_at
      Time.at data['updated'].to_i
    end

    def given_name
      data['given_name']
    end

    def surname
      data['surname']
    end

    def full_name
      "#{given_name} #{surname}"
    end

    def template_cost
      data['template_cost'].to_i
    end

    def template_id
      data['template_id'].to_i
    end

    def original_template_name
      data['template_name']
    end

    def original_template_code
      data['template_code']
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
