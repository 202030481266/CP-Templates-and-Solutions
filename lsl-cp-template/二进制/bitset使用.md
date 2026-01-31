在C++中，`std::bitset` 是一个非常有用的模板类，它允许你处理固定大小的位集合。`std::bitset` 提供了多种方法来操作和查询这些位。以下是一些常用的`std::bitset`方法：

1. **构造函数**
   - `bitset<N>`：创建一个大小为N的`bitset`，所有位初始化为0。
   - `bitset<N>(unsigned long val)`：创建一个大小为N的`bitset`，并用val的二进制表示初始化。
   - `bitset<N>(const string& str)`：创建一个大小为N的`bitset`，并用字符串str中的字符（'0'或'1'）初始化。

2. **访问和修改位**
   - `operator[](size_t pos)`：返回第pos位的引用。
   - `set()`：将所有位置为1。
   - `set(size_t pos)`：将第pos位置为1。
   - `set(size_t pos, bool val)`：将第pos位置为val（0或1）。
   - `reset()`：将所有位置为0。
   - `reset(size_t pos)`：将第pos位置为0。
   - `flip()`：翻转所有位（0变1，1变0）。
   - `flip(size_t pos)`：翻转第pos位。

3. **查询位状态**
   - `test(size_t pos)`：检查第pos位是否为1。
   - `any()`：检查是否有任何位为1。
   - `none()`：检查是否所有位都为0。
   - `all()`：检查是否所有位都为1（仅当`bitset`的大小等于位的数量时才有意义）。

4. **位操作**
   - `count()`：返回1的位数。
   - `size()`：返回`bitset`的大小。
   - `to_ulong()`：将`bitset`转换为`unsigned long`。
   - `to_ullong()`：将`bitset`转换为`unsigned long long`。
   - `to_string()`：将`bitset`转换为字符串。

5. **输出**
   - `operator<<(ostream& os, const bitset<N>& b)`：将`bitset`输出到流。

这些方法使得`std::bitset`在处理位级操作时非常方便和高效。例如，你可以使用`set`方法来设置特定的位，或者使用`test`方法来检查某个位是否被设置。`bitset`在处理位掩码、标志和其他需要位级操作的场景中非常有用。