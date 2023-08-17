require 'date_time_attributes/railtie' if defined?(Rails)

module DateTimeAttributes

  module ClassMethods

    def date_time_attributes_for *date_time_attributes
      date_time_attributes.each { |attribute| define_date_time_accessors_for attribute }
    end

    private

    def define_date_time_accessors_for attribute
      attribute_name = attribute.to_s.sub /_at$/, ""
      assignment = "#{attribute}=".to_sym

      self.class_eval do

        define_method "#{attribute_name}_date" do
          attribute_to_time_with_format attribute, '%Y-%m-%d'
        end

        define_method "#{attribute_name}_time" do
          attribute_to_time_with_format attribute, '%H:%M:%S'
        end

        define_method "#{attribute_name}_date=" do |new_date|
          if blank_value? new_date
            self.send assignment, nil
            return
          end
          new_date = Date.parse new_date if new_date.is_a? String
          self.send assignment, (self.send(attribute) || Time.now).change(year: new_date.year, month: new_date.month, day: new_date.day)
        end

        define_method "#{attribute_name}_time=" do |new_time|
          return if blank_value? new_time
          new_time = Time.parse new_time if new_time.is_a? String
          self.send assignment, (self.send(attribute) || Time.now).change(hour: new_time.hour, min: new_time.min, sec: new_time.sec)
        end

        private

        def attribute_to_time_with_format attribute, format
          value = self.send(attribute)
          return '' unless value.respond_to? :to_time
          value = value.to_time
          return '' unless value.respond_to? :utc
          value.utc.strftime format
        end

        def blank_value? value
          value.respond_to?(:empty?) ? !!value.empty? : !value
        end

      end
    end

  end

end
