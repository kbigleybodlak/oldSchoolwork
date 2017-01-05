#no. 2 loop structures
#2. Write a Ruby demo program that illustrates the use of all main Ruby loops and iterators [Reader, slide 51, and 76-102].   

#while-do, until-do, for-in, upto, downto, times, loop modifiers.
arr = [1,2,3,4]
a = 1
while a < 4 do 
	puts "#{a} "
	a += 1
end
puts
until a==7 do
	puts "#{a}"
	a += 1
end
puts "while modifier"
puts a = a-1 while a>3
puts "until modifier"
puts a = a-1 until a == 0
puts "for-in"

for piece in arr
	puts piece
end
puts "upto"
4.upto(8){|n| puts n}
puts
puts "downto"
4.downto(1){|n| puts n}
puts "times"
3.times{puts "hello"}

mult = arr.collect{|x| x**2}
puts mult
puts

ar = arr.select{|x| x>2}
puts ar
puts

ar = arr.reject{|c| c>2}
puts ar 
puts

	

