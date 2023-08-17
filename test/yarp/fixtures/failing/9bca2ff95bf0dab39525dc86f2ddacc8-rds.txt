require 'aws-sdk-rds'

module AwsInstanceList

  class RDS < AwsInstanceList::Base

    def initialize region: 'eu-west-1'

      super region: region

      @client=Aws::RDS::Client.new region: region

    end

    def list_method
      :db_instances
    end

    def descriptions options={}
      client.describe_db_instances(options)
    end

    def db_list options: {}, fields: nil

      fields||=load_db_fields

      instances(options).map do |i|
        fields.map { |f| i.send(f) } << free_storage_space(i.db_instance_identifier) << region
      end
    end

    def load_db_fields
      yaml['db']['fields']
    end

    def free_storage_space db_instance_identifier
      metric.free_storage_space db_instance_identifier
    end

  end

end
