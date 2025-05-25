func maxSubstrings(word string) int {
	n := len(word)
	dp := make([]int, n)
	pos := make([]int, 26)
	last := make([]int, n)
	for i := 0; i < 26; i++ {
		pos[i] = -1
	}
	for i := 0; i < n; i++ {
		c := word[i] - 'a'
		last[i] = pos[c]
		pos[c] = i
	}
	for i := 1; i < n; i++ {
		lastPos := last[i]
		for i-lastPos+1 < 4 && lastPos != -1 {
			lastPos = last[lastPos]
		}
		if lastPos != -1 {
			if lastPos == 0 {
				dp[i] = 1
			} else {
				dp[i] = dp[lastPos-1] + 1
			}
		}
		if dp[i] < dp[i-1] {
			dp[i] = dp[i-1]
		}
	}
	ans := 0
	for i := 0; i < n; i++ {
		if dp[i] > ans {
			ans = dp[i]
		}
	}
	return ans
}