
func minSwaps(nums []int) int {
	n := len(nums)
	pattern1 := make([]int, n)
	pattern2 := make([]int, n)
	for i := 0; i < n; i++ {
		pattern1[i] = i % 2
	}
	for i := 0; i < n; i++ {
		pattern2[i] = pattern1[i] ^ 1
	}
	cal := func(p []int) int {
		t1 := make([]int, 0)
		t2 := make([]int, 0)
		for i := 0; i < n; i++ {
			r := nums[i] % 2
			if r != p[i] {
				if r == 0 {
					t1 = append(t1, i)
				} else {
					t2 = append(t2, i)
				}
			}
		}
		if len(t1) != len(t2) {
			return 2000000000
		}
		res := 0
		for i := 0; i < len(t1); i++ {
			if t1[i] > t2[i] {
				res += t1[i] - t2[i]
			} else {
				res += t2[i] - t1[i]
			}
		}
		return res
	}
	ans := min(cal(pattern1), cal(pattern2))
	if ans == 2000000000 {
		return -1
	}
	return ans
}
