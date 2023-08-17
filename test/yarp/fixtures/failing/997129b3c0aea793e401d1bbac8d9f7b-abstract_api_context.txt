class IdnSdkRuby::Com::Nbos::Capi::Api::V0::AbstractApiContext < IdnSdkRuby::Com::Nbos::Capi::Api::V0::ApiContext
	attr_accessor :name

	@@apiContexts = {}

	def initialize(name = nil)
		@name = (name != nil && !name.empty?) ? name : "app"
	end
	
	def self.registerApiContext(apiContext)
		@@apiContexts[apiContext.getName()] = apiContext
		puts "Registered Contexts with API Context = >#{@@apiContexts}"
	end

	def self.get(name)
		ctx = @@apiContexts[name]
		if (ctx == nil)
			ctx = IdnSdkRuby::Com::Nbos::Capi::Api::V0::InMemoryApiContext.new(name)
			IdnSdkRuby::Com::Nbos::Capi::Api::V0::AbstractApiContext.registerApiContext(ctx)
		end
		return ctx
	end

end #end of class
					