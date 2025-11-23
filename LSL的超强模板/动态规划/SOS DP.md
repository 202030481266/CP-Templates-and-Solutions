这份模板包含了三个部分：

1.  **求子集和 (SOS DP)**
2.  **求超集和 (Sum Over Supersets)**
3.  **逆操作 (Inverse SOS DP)** —— *这一点非常重要，用于容斥原理或还原数组。*

-----

### 核心定义

在比赛中，通常数据范围是 $N=20$ 到 $22$（对应 $2^{20} \approx 10^6$ 或 $2^{22} \approx 4 \times 10^6$）。

```cpp
const int M = 20; // 比特位数，根据题目要求修改，例如 20
const int MAX_MASK = 1 << M;
long long dp[MAX_MASK]; // 使用 long long 防止溢出
```

-----

### 1\. 求子集和模板 (Sum Over Subsets)

**功能：** 计算 $dp[mask] = \sum_{i \subseteq mask} A[i]$
**口诀：** “第 $i$ 位是 1 的，要把第 $i$ 位是 0 的加进来。”

```cpp
// 初始化：先将原始数组 A 的值填入 dp
// 例如：for(int i=0; i < (1<<M); ++i) dp[i] = A[i];

for (int i = 0; i < M; ++i) {
    for (int mask = 0; mask < (1 << M); ++mask) {
        if (mask & (1 << i)) {
            dp[mask] += dp[mask ^ (1 << i)];
        }
    }
}
```

### 2\. 求超集和模板 (Sum Over Supersets)

**功能：** 计算 $dp[mask] = \sum_{mask \subseteq i} A[i]$
**口诀：** “第 $i$ 位是 0 的，要把第 $i$ 位是 1 的加进来。”

```cpp
// 初始化：同样先将原始数组 A 的值填入 dp

for (int i = 0; i < M; ++i) {
    for (int mask = 0; mask < (1 << M); ++mask) {
        if (!(mask & (1 << i))) { // 注意这里是取反 !
            dp[mask] += dp[mask ^ (1 << i)];
        }
    }
}
```

-----

### 3\. 进阶：逆操作 (Inverse SOS DP)

**这是高手技巧：**
有时候题目给你的是“已经求完子集和”的状态，让你**还原**出原始数组；或者在做**容斥原理**（Inclusion-Exclusion）时，你需要减回去。

它的逻辑和正向操作完全相反：正向是 `+`，逆向就是 `-`。

#### 3.1 子集和的逆操作 (还原数组)

```cpp
// dp[mask] 当前存储的是子集和，我们想还原回原始值

for (int i = 0; i < M; ++i) {
    for (int mask = 0; mask < (1 << M); ++mask) {
        if (mask & (1 << i)) {
            dp[mask] -= dp[mask ^ (1 << i)]; // 减回去
        }
    }
}
```

#### 3.2 超集和的逆操作

```cpp
// dp[mask] 当前存储的是超集和，我们想还原回原始值

for (int i = 0; i < M; ++i) {
    for (int mask = 0; mask < (1 << M); ++mask) {
        if (!(mask & (1 << i))) {
            dp[mask] -= dp[mask ^ (1 << i)]; // 减回去
        }
    }
}
```

-----

### 4\. 比赛实战注意事项 (Tips)

1.  **空间优化：** 不需要开二维数组 $dp[M][1 \ll M]$，直接在以为数组上滚动更新即可（如上所示），因为每层循环只依赖上一层的结果。
2.  **时间复杂度：** 严格的 $O(M \cdot 2^M)$。
      * 如果 $M=20$，计算量约为 $2 \times 10^7$，C++ 可以在 100ms\~200ms 内跑完。
      * 如果 $M=24$，计算量约为 $4 \times 10^8$，可能会超时（2-3秒），需要非常小心或卡常。
3.  **初始化：** 很多题目中，原始数组 $A[i]$ 其实就是频次数组 $cnt[i]$。别忘了先把输入数据转换成频次放入 $dp$ 数组中再开始跑循环。
4.  **FWT (快速沃尔什变换)：** 其实 SOS DP 就是 **FWT (Or Convolution)** 的一半。如果你听到别人说 FWT 或 FMT (Fast Mobius Transform)，指的基本上就是这个算法。

