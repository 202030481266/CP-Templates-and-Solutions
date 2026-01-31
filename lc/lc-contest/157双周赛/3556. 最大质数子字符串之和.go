import (
	"fmt"
	"strconv"
)

func isPrime(n int64) bool {
	if n <= 1 {
		return false
	}
	for i := int64(2); i*i <= n; i++ {
		if n%i == 0 {
			return false
		}
	}
	return true
}

func sumOfLargestPrimes(s string) int64 {
	p1, p2, p3 := int64(0), int64(0), int64(0)
	for i := 0; i < len(s); i++ {
		for j := i; j < len(s); j++ {
			num, _ := strconv.ParseInt(s[i:j+1], 10, 64)
			if isPrime(num) {
				if num > p1 {
					p3 = p2
					p2 = p1
					p1 = num
				} else if num > p2 && num < p1 {
					p3 = p2
					p2 = num
				} else if num > p3 && num < p2 {
					p3 = num
				}
			}
		}
	}
	return p1 + p2 + p3
}