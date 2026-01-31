import heapq
class Solution:
    def kthLargestValue(self, matrix: List[List[int]], k: int) -> int:
        n, m = len(matrix), len(matrix[0])
        sum = [[0]*(m+1) for _ in range(n+1)]
        q = []
        for i in range(1, n+1):
            for j in range(1, m+1):
                sum[i][j] = sum[i-1][j] ^ sum[i][j-1] ^ sum[i-1][j-1] ^ matrix[i-1][j-1]
                if len(q) < k:
                    heapq.heappush(q, sum[i][j])
                elif sum[i][j] > q[0]:
                    heapq.heappop(q)
                    heapq.heappush(q, sum[i][j])
        return q[0]
