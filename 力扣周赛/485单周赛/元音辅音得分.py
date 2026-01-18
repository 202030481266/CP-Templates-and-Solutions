# xiaoshulin

class Solution:
    def vowelConsonantScore(self, s: str) -> int:
        c = len([v for v in s if v in "aeiou"])
        v = len([v for v in s if v.isalpha()])
        return 0 if v == c else c // (v - c)
