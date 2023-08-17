module REIformslive
  class Session
    require 'faraday'

    def self.get path: '/'
      connection
        .get(path)
        .body
    end

    def self.put path: '/', data: {}
      connection
        .put(path, data)
        .body
    end

    def self.base_url
      'https://sa-api.staging.reiformslive.com.au'
    end

    def self.connection
      conn = Faraday.new base_url
      conn.basic_auth '4b66ff95-ade7-413e-b086-0044de7b4ccf', 'ae7e5a1b-e85d-43c4-8d01-fd5cb47d7044'
      conn
    end
  end
end
