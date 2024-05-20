class Solution:
    def encode(self, num: int) -> str:
        if num == 0:
            return ""
        msb = num.bit_length() - 1
        if 2 ** (msb + 1) - 1 == num:
            return "0" * (msb + 1)
        ans = bin(num - (2 ** msb - 1))[2:]
        return "0" * (msb - len(ans)) + ans