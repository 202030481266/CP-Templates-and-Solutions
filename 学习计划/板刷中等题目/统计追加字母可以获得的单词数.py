from collections import defaultdict

class Solution:
    def wordCount(self, startWords: List[str], targetWords: List[str]) -> int:
        words = set(startWords)
        for w in startWords:
            words.add(''.join(sorted(list(w))))
        ans = 0
        for w in targetWords:
            w = ''.join(sorted(list(w)))
            cnt = defaultdict(int)
            for c in w:
                cnt[c] += 1
            for i in range(len(w)): 
                if cnt[w[i]] == 1 and (w[:i] + w[i+1:]) in words:
                    ans += 1
                    break
        return ans
                    
