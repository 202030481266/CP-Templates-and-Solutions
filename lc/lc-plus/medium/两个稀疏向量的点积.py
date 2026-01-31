class SparseVector:
    def __init__(self, nums: List[int]):
        self.vector = []
        for i,v in enumerate(nums):
            if v > 0:
                self.vector.append((i,v))

    # Return the dotProduct of two sparse vectors
    def dotProduct(self, vec: 'SparseVector') -> int:
        p, q = 0, 0
        ans = 0
        while p < len(self.vector) and q < len(vec.vector):
            if self.vector[p][0] == vec.vector[q][0]:
                ans += self.vector[p][1] * vec.vector[q][1]
                p += 1
                q += 1
            elif self.vector[p][0] < vec.vector[q][0]:
                p += 1
            else:
                q += 1
        return ans
        

# Your SparseVector object will be instantiated and called as such:
# v1 = SparseVector(nums1)
# v2 = SparseVector(nums2)
# ans = v1.dotProduct(v2)