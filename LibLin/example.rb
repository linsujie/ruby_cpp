#!/usr/local/bin/ruby
require '~/ruby_cpp/LibLin/LibLin'

def func(x, y)
  x**2 + y**2
end

def addline(table, y, vx)
  tmp = LibLin::Vectord.new
  vx.each { |x| tmp << func(x, y) }
  table << tmp
end

a = (0..20).map { |x| x / 10.0 }.to_a
b = (0..20).map { |x| x / 10.0 }.to_a
table = LibLin::Matrixd.new()
vx = LibLin::Vectord.new
vy = LibLin::Vectord.new

a.each { |x| vx << x }
b.each { |y| vy << y }
b.each { |y| addline(table, y, vx) }

p table
tab = LibLin::Table2D.new(vx, vy, table)
intp = LibLin::Interp2D.new(tab)

tab.list()
m, n = 1.7, 1.65
p intp.linask(m, n), m**2 + n**2
