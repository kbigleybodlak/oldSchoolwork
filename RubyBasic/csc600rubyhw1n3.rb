#3. Write a function mean_sigma(v) that returns two values: the mean value and the standard deviation of numbers stored in the array v [Slides 135,141 show how to return two values].  
def mean_sigma(v)
	mean = 0
	for i in v
		mean += i
	end
	mean = mean/v.length
	
	#std. dev
	sum =0
	for j in v
		sum += ((j - mean)**2)
	end
	variance = sum/(v.length - 1)
	stddev = Math.sqrt(variance)
	return mean, stddev
end

arr = [1.0,3.0,5.0,7.0]
m, s = mean_sigma(arr)
puts "mean = #{m} "
puts "std. dev = #{s}"
	