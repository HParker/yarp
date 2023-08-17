module REIformslive
  class Credentials
    attr_reader :username, :password
    
    def initialize username: '', password: ''
      @username, @password = username, password
    end
  end
end
