require 'aws-sdk-elasticache'

module AwsInstanceList

  class ElastiCache < AwsInstanceList::Base

    def initialize region: 'eu-west-1'

      super region: region

      @client=Aws::ElastiCache::Client.new region: region

    end

    def list_method
      :cache_clusters
    end

    def descriptions options={}
      client.describe_cache_clusters(options)
    end

    def bytes_used_for_cache cache_cluster_id
      metric.bytes_used_for_cache cache_cluster_id
    end

    def freeable_memory cache_cluster_id
      metric.freeable_memory cache_cluster_id
    end

    def cache_list options: {}, fields: nil

      fields||=load_cache_fields

      instances(options).map do |i|
        fields.map { |f| i.send(f) } + metrics(i) << region
      end
    end

    def group_name i
      i.cache_parameter_group.cache_parameter_group_name
    end

    def maxmemory cache_node_type
      yaml['maxmemory'][cache_node_type]
    end

    def load_cache_fields
      yaml['cache']['fields']
    end

    def metrics instance
      used=bytes_used_for_cache(instance.cache_cluster_id) / 1024
      total=maxmemory(instance.cache_node_type) / 1024
      [total, used]
    end

  end
end


