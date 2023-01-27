#include <bits/stdc++.h>
using namespace std;//最高62进制的
const int N = 1000;
int t[N], A[N];
char OldData[N], NewData[N]; // 转换前、后的数据
int olds, news;              // 转换前、后的进制
void trans() {
  int i, len, k = 0;
  len = strlen(OldData);
  for (i = len; i >= 0; --i) {
    t[len - 1 - i] =  OldData[i] - (OldData[i] < 58 ? 48 : OldData[i] < 97 ? 55 : 61);
  }
  while (len) {
    for (i = len; i >= 1; --i) {
      t[i - 1] += t[i] % news * olds;
      t[i] /= news;
    }
    A[k++] = t[0] % news;
    t[0] /= news;
    while (len > 0 && !t[len - 1]) {
      --len;
    }
  }
  NewData[k] = NULL;
  for (i = 0; i < k; ++i) {
    NewData[k - 1 - i] = A[i] + (A[i] < 10 ? 48 : A[i] < 36 ? 55 : 61);
  }
}
int main() {
  scanf("%d %d", &olds, &news);
  scanf("%s", OldData);
  trans();
  printf("%s\n", NewData);
  return 0;
}
