// 求解最大连续子段积

long long maximumProduct(long long data[], int n)
{
  long long product, currentMax, currentMin, nextMax, nextMin;
  product = currentMax = currentMin = data[0];
  for (int i = 1; i < n; i++) {
    // 正数*正数，负数*负数，两者之间得到最大的整数
    nextMax = currentMax * data[i], nextMin = currentMin * data[i];
    currentMax = max(data[i], max(nextMax, nextMin));
    currentMin = min(data[i], min(nextMax, nextMin));
    product = max(product, currentMax);
  }
  return product; 
}