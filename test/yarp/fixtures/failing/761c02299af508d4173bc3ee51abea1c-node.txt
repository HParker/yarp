#!/usr/bin/ruby -w
# -*- ruby -*-

require 'arbolobra/chars'
require 'arbolobra/formatter'

module Arbolobra
  class Node
    include Comparable
    
    attr_reader :value
    attr_reader :children
    
    def initialize value, *children
      @children = if children.size == 1 && children.first.class == Array
                    children.first
                  else
                    children
                  end
      @value = value
    end

    def print intro: "", lead: "", output: $stdout, charset: Arbolobra::CharSet::DEFAULT
      fmt = Formatter.new charset: charset, output: output
      fmt.print self, intro, lead
    end

    def to_s
      "value: #{@value}, #{@children && @children.size}"
    end

    def <=> other
      cmp = value <=> other.value
      if cmp == 0
        cmp = children <=> other.children
      end
      cmp
    end
  end
end
