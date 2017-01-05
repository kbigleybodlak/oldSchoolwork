#4. Write a function sort(v) that returns the sorted array v. Do not use Ruby sort methods; write your own sort. Array v must remain unchanged. [Slide 137 shows how to return an array]  

def sort(v,left=0,right=nil)
	p = v[left] #pivot
	l=left #minimum index of array
	tmp = left
	if right == nil
		right = v.length - 1
	end
	r = right #maximum index of array
	
	if left > right
		return
	end
	#quicksort algorithm
	while l < r
		if tmp == l
			if v[r] <= p
				v[tmp] = v[r]
				l = l + 1
				tmp = r
			else
				r = r - 1
			end
		elsif tmp == r
			if v[l] >= p
				v[tmp] = v[l]
				r = r - 1
				tmp = l
			else
				l = l + 1
			end
		end
	end
	
	v[tmp] = p
	
	sort(v,left, tmp - 1)
	sort(v, tmp + 1, right)
end


arr = [1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4]
puts "the array before sorting"
puts arr
puts
sort(arr)
puts "after sort"
puts arr



	

