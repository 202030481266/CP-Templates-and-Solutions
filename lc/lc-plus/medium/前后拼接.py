class Solution:
    def beforeAndAfterPuzzles(self, phrases: List[str]) -> List[str]:
        words = [phrase.split() for phrase in phrases]
        ans = set()
        n = len(words)
        for i in range(n):
            for j in range(n):
                if i != j and words[i][-1] == words[j][0]:
                    new_phrase = ' '.join(words[i] + words[j][1:])
                    ans.add(new_phrase)
        ans = list(ans)
        ans.sort()
        return ans