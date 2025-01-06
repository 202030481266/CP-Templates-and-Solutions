from typing import List

arr = [20, 50, 100, 200, 500]

class ATM:

    def __init__(self):
        self.banks = [0] * 5

    def deposit(self, banknotesCount: List[int]) -> None:
        for i in range(5):
            self.banks[i] += banknotesCount[i]

    def withdraw(self, amount: int) -> List[int]:
        ans = [0] * 5
        for i in range(4, -1, -1):
            if arr[i] <= amount and self.banks[i] > 0:
                ans[i] = min(self.banks[i],amount//arr[i])
                amount -= ans[i] * arr[i]
        if amount != 0:
            return [-1]
        for i in range(5):
            self.banks[i] -= ans[i]
        return ans


# Your ATM object will be instantiated and called as such:
# obj = ATM()
# obj.deposit(banknotesCount)
# param_2 = obj.withdraw(amount)