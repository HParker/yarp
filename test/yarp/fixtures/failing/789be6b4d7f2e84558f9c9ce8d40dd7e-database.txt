require 'sqlite3'

module CsvToSqlite
  class Database

    def initialize db_name: "data.sqlite3"
      @db_name = db_name
      @target_dir = target_dir
      @database_path = "#{@target_dir}/#{@db_name}"
    end

    def create
      if File.exist? @database_path
        puts "Database found"
      else
        puts "Creating database"
        SQLite3::Database.new @database_path
      end
    end

    def connect
      create
      SQLite3::Database.new @database_path
    end

    private

      def target_dir
        return './spec/src/' if ENV.key? "test"
        '.'
      end

  end
end
