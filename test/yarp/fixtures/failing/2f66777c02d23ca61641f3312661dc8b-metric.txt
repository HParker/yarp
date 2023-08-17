require 'aws-sdk-cloudwatch'

module AwsInstanceList

  class Metric

    attr_accessor :client

    def initialize region: 'eu-west-1'
      @client=Aws::CloudWatch::Client.new region: region
    end

    def statistics options
      client.get_metric_statistics options
    end

    def list options
      client.list_metrics options
    end

    def free_storage_space db_instance_identifier
      resp=statistics( {
        namespace: "AWS/RDS",
        metric_name: "FreeStorageSpace",
        dimensions: [
          {
            name: "DBInstanceIdentifier",
            value: db_instance_identifier,
          },
        ],
        start_time: Time.now - 600,
        end_time: Time.now ,
        period: 60,
        statistics: ["Minimum"]
      })

      if resp.datapoints.empty?
        '-'
      else
        resp.datapoints.last.minimum / ( 1024.0 ** 3)
      end

    end

    def bytes_used_for_cache cache_cluster_id
      resp=statistics( {
        namespace: "AWS/ElastiCache",
        metric_name: "BytesUsedForCache",
        dimensions: [
          {
            name: "CacheClusterId",
            value: cache_cluster_id,
          },
        ],
        start_time: Time.now - 600,
        end_time: Time.now ,
        period: 60,
        statistics: ["Maximum"]
      })

      resp.datapoints.last.maximum

    end


    def freeable_memory cache_cluster_id
      resp=statistics( {
        namespace: "AWS/ElastiCache",
        metric_name: "FreeableMemory",
        dimensions: [
          {
            name: "CacheClusterId",
            value: cache_cluster_id,
          },
        ],
        start_time: Time.now - 600,
        end_time: Time.now ,
        period: 60,
        statistics: ["Maximum"]
      })

      resp.datapoints.last.maximum

    end

    def es_free_storage_space dimensions
      resp=statistics( {
        namespace: "AWS/ES",
        metric_name: "FreeStorageSpace",
        dimensions: dimensions,
        start_time: Time.now - 600,
        end_time: Time.now ,
        period: 60,
        statistics: ["Minimum"]
      })

      if resp.datapoints.empty?
        '-'
      else
        resp.datapoints.last.minimum
      end
    end

    def cluster_used_space dimensions
      resp=statistics( {
        namespace: "AWS/ES",
        metric_name: "ClusterUsedSpace",
        dimensions: dimensions,
        start_time: Time.now - 600,
        end_time: Time.now ,
        period: 60,
        statistics: ["Maximum"]
      })

      if resp.datapoints.empty?
        '-'
      else
        resp.datapoints.last.maximum
      end
    end
  end
end

