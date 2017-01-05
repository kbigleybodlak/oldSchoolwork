#5. Create a Ruby class triangle with initalizer, accessors, and member functions for computing the perimeter and the area of arbitrary triangles. Make also a member function test that checks sides a, b, and c and classifies 
#	the triangle as (1) equilateral, (2) isosceles, (3) scalene, (4) right, and (5) not a triangle. Right triangle can be either isosceles or scalene. Compute the perimeter and area only for valid triangles (verified by test). 
#Show examples of the use of this class.  


class Triangle 
	def initialize(side1, side2, side3)
			@side1 = side1
			@side2 = side2
			@side3 = side3
	end
	
	def side1()
		@side1
	end
	def side2()
		@side2
	end
	def side3()
		@side3
	end
	def side1=(a)
		@side1 = a
	end
	def side2=(a)
		@side2 = a
	end
	def side3=(a)
		@side3 = a
	end
	
	def perimeter()
		unless self.test() == "not a triangle"
			@side1 + @side2 + @side3
		end
	end
	
	def area()
		unless self.test() == "not a triangle"
			s = self.perimeter() / 2
			Math.sqrt((s*(s-@side1)*(s-@side2)*(s-@side3)))
		end
	end
	
	def test()
		result = case
			when @side1>= @side2+@side3 || @side2 >= @side1+@side3 || @side3 >= @side1+@side2 then "not a triangle"
			when @side1 == @side2 && @side2 = @side3 then "equilateral triangle"
			when @side1**2 == (@side2**2 + @side3**2) then "right triangle"
			when @side2**2 == (@side1**2 + @side3**2) then "right triangle"
			when @side3**2 == (@side1**2 + @side2**2) then "right triangle"
			when @side1 == @side2 && @side2 != @side3 then "isosceles triangle"
			when @side2 == @side3 && @side1 != @side2 then "isosceles triangle"
			when @side1 == @side3 && @side1 != @side2 then "isosceles triangle"
			when @side1 != @side2 && @side2 !=@side3 && @side3 != @side1 then "scalene triangle"
		end
		return result
	end
	
	
end

tri = Triangle.new(3,5,6)
puts "sides of triangle "
puts tri.side1()
puts tri.side2()
puts tri.side3()
print "perimter of triangle: "
puts tri.perimeter()
print "area of triangle: "
puts tri.area()
print "this triangle is: "
puts tri.test()