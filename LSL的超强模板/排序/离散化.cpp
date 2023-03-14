// 离散化a数组

void discrete() {
  sort(a + 1, a + 1 + n);
  int len = unique(a + 1, a + 1 + n) - a - 1;
  for(int i = 1; i <= len; i++) b[i] = a[i];
}