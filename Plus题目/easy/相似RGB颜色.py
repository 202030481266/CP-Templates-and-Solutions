class Solution:
    def similarRGB(self, color: str) -> str:
        # 枚举颜色
        a, b, c = int(color[1:3], 16), int(color[3:5], 16), int(color[5:7], 16)
        def cal(x) -> str:
            res = ""
            mx = 1e9
            # 能够缩写的数字表示必然是 00, 11, 22...ff 
            for i in range(16):
                hex_digit = f"{i:x}" * 2
                hex_value = int(hex_digit, 16)
                if (x - hex_value) ** 2 < mx:
                    mx = (x - hex_value) ** 2
                    res = hex_digit
            return res
        return "#" + cal(a) + cal(b) + cal(c)
