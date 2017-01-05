# 1. Write a Ruby demo program that illustrates the use of all main Ruby conditional statements [Reader, slide 51, and 52-74].  

#if-then, if-else, if elsif else, unless, unless else, if/unless modifiers, Case, case with selector.
a, b, c = 1,2,3
if a>b || b==b
	then puts "a > b"
end

if c<a
	then puts "c < a"
elsif c>a
	then puts "c > a"
else
	puts "c = a"
end
	
if b > c
	then puts "b > c"
else 
	puts "b !> c"
end

unless b == c
	puts "b != c"
end

unless a>c
	puts "a < c"
else
	puts "a !< c"
end

puts a if a ==1 

puts "c>a" unless c <a 

name = case
			when c == 1 then "1"
			when c ==2 then "2"
			when c ==3 then "3"
			else "null"
		end
puts name


	