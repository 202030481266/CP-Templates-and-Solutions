// 求给定字符串的最长不重复子串。返回的是第一次遇到的最长不重复子串。
// 使用线性扫描和动态规划的思想

string LSWRC(string source)
{
  // 字符串长度为 0，则最长不重复子串为空。
  if (source.length() == 0) return "";
  // 设立标记数组，表示某个字符在字符串中的最后一次出现位置，如果未出现则值为-1。
  vector<int> latest(256);
  fill(latest.begin(), latest.end(), -1);
  // 初始时，最长不重复子串的长度为第一个字符构成的不重复子串，其长度为 1，起始位置为 0。
  int currentMaxLength = 1, maxLength = 1, maxLengthStartAt = 0;
  for (int i = 1; i < source.size(); i++) {
  // 如果第 i 个字符在此前未出现，则第 i 个字符可以附加在之前的最长不重复子串后
  // 构成新的不重复子串，或者该字符出现在以第 i - 1 个字符结尾的最长不重复子串
  // 之前，那么也可以附加在其后构成新的不重复子串。
  if (latest[source[i]] == -1 || latest[source[i]] < (i - currentMaxLength))
    currentMaxLength++;
  // 最长不重复子串的长度需要重新计算。
  else currentMaxLength = i - latest[source[i]];
  // 更新字符的最后一次出现位置。
  latest[source[i]] = i;
  // 通过比较获取最长不重复子串的长度和起始位置。
  if (currentMaxLength > maxLength) {
  maxLength = currentMaxLength;
  maxLengthStartAt = i - currentMaxLength + 1;
  }
  }
  // 截取最长不重复子串。
  return source.substr(maxLengthStartAt, maxLength);
}