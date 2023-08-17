require 'yaml'

module AwsInstanceList

  class Base

    attr_accessor :client, :region, :metric

    def initialize region: 'eu-west-1'

      @region=region

      @metric = AwsInstanceList::Metric.new region: region

      @instances = []

    end

    def instances options={}
      ds=descriptions(options)
      @instances+=ds.send( list_method )
      if ds.marker
        options[:marker]=ds.marker
        instances(options)
      else
        @instances
      end
    end

    def yaml
      @yaml||=yaml_default.merge(yaml_file)[demodulize]
    end

    def yaml_default
      YAML.load_file AwsInstanceList::DEFAULT_SETTINGS
    end

    def yaml_file
      ENV.has_key?('AWS_INSTANCE_LIST_YAML') ? YAML.load_file(ENV['AWS_INSTANCE_LIST_YAML']) : {}
    end

    def demodulize
      self.class.name.split('::').last
    end

  end

end
