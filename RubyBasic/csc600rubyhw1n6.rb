#6. Write Ruby recognizer methods limited? and sorted? that expand the Ruby class Array. The expression array.limited?(amin,amax) should return true if amin <= a[i] <= amax for all values of i. 
#	The expression array.sorted? should return  
#• 0  if the array is not sorted 
#• +1  if a[0] = a[1] = a[2] = … (increasing sequence) 
# • -1  if a[0] = a[1] = a[2] = … (decreasing sequence)  Show examples of the use of this method.  


class Array
	def limited?(amin, amax)
		result = true
		for piece in self
			if piece < amin || piece > amax
				result =  false
			end
		end
		return result
	end
	
	def sorted?()
		result = 1
		0.upto self.length-2 do |i|
			if self[i+1]  >= self[i] && result != -1
				result = 1
			elsif self[i + 1] <= self[i]
				result = -1
			else
				result = 0
				break
			end
		end
			return result
	end
	
end

sorted = [1,2,3,4,5,6]
unsorted = [2,1,6,7,3]
decreasing = [4,3,2,1]

puts "array limited to 1..6 ? "
puts sorted.limited?(1, 6)
print "result of sorted?: "
puts decreasing.sorted?()

