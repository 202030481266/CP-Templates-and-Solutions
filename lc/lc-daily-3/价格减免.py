class Solution:
    def discountPrices(self, sentence: str, discount: int) -> str:
        s = sentence.split()
        ans = []
        for w in s:
            if w[0].startswith('$') and len(w) > 1:
                i = 1
                res = 0
                while i < len(w) and w[i].isdigit():
                    res = res*10 + int(w[i])
                    i += 1
                if i == len(w):
                    ans.append('$' + "{:.2f}".format(res*(100-discount)/100))
                else:
                    ans.append(w)
            else:
                ans.append(w)
        return ' '.join(ans)
                