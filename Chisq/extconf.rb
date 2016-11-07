#!/usr/bin/ruby

require 'mkmf'

$libs = '-lgsl -L/home/linsj/mybasic/lib -lalg '

create_makefile('Chisq')
