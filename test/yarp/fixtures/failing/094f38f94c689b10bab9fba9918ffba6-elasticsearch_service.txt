require 'aws-sdk-elasticsearchservice'

module AwsInstanceList

  class ElasticsearchService < AwsInstanceList::Base

    def initialize region: 'eu-west-1'

      super region: region

      @client=Aws::ElasticsearchService::Client.new region: region

    end

    def domain_names
      client.list_domain_names.map { |x| x.domain_names.map { |d| d.domain_name } }.flatten
    end

    def descriptions
      total_domains=domain_names
      begin
        @instances+=client.describe_elasticsearch_domains(domain_names: total_domains.first(5) ).domain_status_list
        total_domains=total_domains.drop(5)
      end while !total_domains.empty?
    end

    def instances
      descriptions
      @instances
    end

    def domain_list
      instances.map do |i|
        fields.map { |f| i.send(f) } + metrics(i) << region
      end
    end

    def fields
      yaml['domain_status']['fields']
    end

    def metrics instance
      type=instance.elasticsearch_cluster_config.instance_type
      nodes=instance.elasticsearch_cluster_config.instance_count
      dimensions = [ { name: 'DomainName', value: instance.domain_name },
                     { name: 'ClientId', value: instance.domain_id.split('/').first }
      ]
      free=metric.es_free_storage_space( dimensions )
      used=metric.cluster_used_space(dimensions)
      [type, nodes, free + used,free, used ]
    end

  end
end


