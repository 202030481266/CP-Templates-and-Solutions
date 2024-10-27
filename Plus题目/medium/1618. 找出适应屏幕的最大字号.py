# """
# This is FontInfo's API interface.
# You should not implement it, or speculate about its implementation
# """
#class FontInfo(object):
#    Return the width of char ch when fontSize is used.
#    def getWidth(self, fontSize, ch):
#        """
#        :type fontSize: int
#        :type ch: char
#        :rtype int
#        """
# 
#    def getHeight(self, fontSize):
#        """
#        :type fontSize: int
#        :rtype int
#        """
from typing import List

class Solution:
    def maxFont(self, text: str, w: int, h: int, fonts: List[int], fontInfo : 'FontInfo') -> int:
        l, r = -1, len(fonts)        

        while l+1 < r:
            mid = (l+r)//2
            res = 0
            for ch in text:
                res += fontInfo.getWidth(fonts[mid],ch)
            if fontInfo.getHeight(fonts[mid]) <= h and res <= w:
                l = mid
            else:
                r = mid
        
        return -1 if l == -1 else fonts[l]