#!/usr/bin/ruby

require 'mkmf'

$libs = '-lgsl -lalg '

create_makefile('Chisq')
