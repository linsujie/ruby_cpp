#!/usr/bin/ruby

require 'mkmf'

$libs = '-lgsl -L/home/linsj/mybasic/lib -lalg -Wl,-rpath=/home/linsj/mybasic/lib'

create_makefile('Chisq')
