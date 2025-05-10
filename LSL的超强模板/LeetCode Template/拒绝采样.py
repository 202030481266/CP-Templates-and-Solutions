import numpy as np
import math # 用于 math.cos, math.sin, math.sqrt
# from typing import List # 如果你严格使用类型提示

class Solution:
    """
    该类用于在一个指定的圆内随机生成点。
    """

    def __init__(self, radius: float, x_center: float, y_center: float):
        """
        初始化 Solution 对象。

        参数:
            radius (float): 圆的半径。
            x_center (float): 圆心的 x 坐标。
            y_center (float): 圆心的 y 坐标。
        """
        self.a = x_center  # 圆心的 x 坐标
        self.b = y_center  # 圆心的 y 坐标
        self.r = radius    # 圆的半径

    def randPoint_original_incorrect(self) -> list[float]:
        """
        原始的、不正确的采样方法。
        这种方法会导致点在圆心附近更密集，而不是在整个圆盘上均匀分布。
        """
        # 角度在 [0, 2π) 上均匀随机选取，这是正确的
        angle = np.random.uniform(0, 2 * np.pi)
        
        # 半径在 [0, self.r] 上线性均匀随机选取，这是问题所在！
        # 线性选择半径会导致靠近圆心的区域被“过度采样”。
        # 想象一下，半径从 0 到 0.1r 的小圆盘，和半径从 0.9r 到 r 的圆环，
        # 它们在半径轴上占据的长度相同，因此被选中的概率也相同。
        # 但是，后者的面积远大于前者。因此，单位面积内，前者会落入更多的点。
        radius_sample = np.random.uniform(0, self.r) 
        
        # 转换为笛卡尔坐标并加上圆心偏移
        x = self.a + radius_sample * math.cos(angle)
        y = self.b + radius_sample * math.sin(angle)
        return [x, y]

    def randPoint_rejection(self) -> list[float]:
        """
        使用拒绝采样 (Rejection Sampling) 的方法。
        这种方法在概念上简单，并且保证了点的均匀分布。
        原理：
        1. 在一个能完整包围圆的正方形内随机生成一个点。
           这个正方形的边长为 2 * self.r，中心与圆心重合。
           x 坐标范围: [self.a - self.r, self.a + self.r]
           y 坐标范围: [self.b - self.r, self.b + self.r]
        2. 判断这个点是否在圆内。
           如果 (px - self.a)^2 + (py - self.b)^2 <= self.r^2，则点在圆内。
        3. 如果点在圆内，则接受该点。
        4. 如果点在圆外，则拒绝该点，并重复步骤1，直到找到一个在圆内的点。

        优点：容易理解和实现，适用于各种形状的均匀采样。
        缺点：可能会有性能开销，因为一些生成的点会被拒绝。
               对于圆，接受率是 (圆面积 / 正方形面积) = (π * r^2) / ((2r)^2) = π / 4 ≈ 78.5%。
               平均需要生成 1 / (π/4) ≈ 1.27 个点才能得到一个有效的点。
        """
        while True:
            # 步骤1: 在包围盒（正方形）内随机生成一个点 (px, py)
            # px 在 [self.a - self.r, self.a + self.r) 内均匀分布
            px = np.random.uniform(self.a - self.r, self.a + self.r)
            # py 在 [self.b - self.r, self.b + self.r) 内均匀分布
            py = np.random.uniform(self.b - self.r, self.b + self.r)
            
            # 步骤2 & 3: 检查点是否在圆内
            # 为了避免计算开方 (sqrt)，比较距离的平方与半径的平方
            if (px - self.a)**2 + (py - self.b)**2 <= self.r**2:
                return [px, py] # 如果在圆内，返回该点

    def randPointMath(self) -> list[float]:
        """
        使用数学方法修正半径分布，以确保点在圆内均匀分布。
        这是推荐的、效率更高的方法。

        原理 (为什么需要对半径开方):
        我们希望在圆盘的任何等面积的小区域内，采样到点的概率是相同的。
        考虑极坐标 (r_sample, angle_sample)。
        - 角度 (angle_sample): 在 [0, 2π) 之间均匀选取是正确的，因为圆具有旋转对称性。
        - 半径 (r_sample): 
          如果我们线性地从 [0, R] (R是圆的总半径) 中选取 r_sample，
          那么一个在 [r, r+dr] 范围内的小圆环的面积是 dA = 2π * r_sample * dr。
          可以看到，当 r_sample 较小时，即使 dr 相同，dA 也较小。
          当 r_sample 较大时，dA 较大。
          如果我们希望单位面积上的点数相同，那么我们需要一种方法，使得被选中的“概率密度”与面积成正比。

          更形式化地，我们希望一个点落在半径为 r' 的圆内的概率 P(r_sample <= r') 与该圆的面积成正比：
          P(r_sample <= r') = (面积(半径r')) / (面积(总半径R)) = (π * r'^2) / (π * R^2) = (r'/R)^2。
          这是一个累积分布函数 (CDF)。
          根据逆变换采样法 (Inverse Transform Sampling)，如果我们有一个目标CDF F(x)，
          并且我们从 [0,1] 均匀分布中抽取一个随机数 u，那么 x = F_inverse(u) 将具有所需的分布。
          
          设 u = (r_sample / R)^2。
          解出 r_sample：
          sqrt(u) = r_sample / R
          r_sample = R * sqrt(u)

          因此，我们首先生成一个在 [0, 1] 上均匀分布的随机数 `u_for_radius`，
          然后计算实际使用的采样半径为 `self.r * math.sqrt(u_for_radius)`。
          这确保了生成的点在整个圆盘上是均匀分布的。
        """
        # 步骤1: 角度在 [0, 2π) 上均匀随机选取
        angle = np.random.uniform(0, 2 * np.pi)
        
        # 步骤2: 半径的正确采样
        # 首先生成一个在 [0, 1) 范围内的均匀随机数
        # 这个随机数代表了面积的比例因子（经过开方后）
        random_val_for_radius_squared_ratio = np.random.uniform(0, 1)
        
        # 实际采样半径 r_sample = R * sqrt(u)
        # math.sqrt() 用于开平方
        radius_sample = self.r * math.sqrt(random_val_for_radius_squared_ratio)
        
        # 步骤3: 将极坐标 (radius_sample, angle) 转换为笛卡尔坐标，并加上圆心偏移
        x = self.a + radius_sample * math.cos(angle)
        y = self.b + radius_sample * math.sin(angle)
        
        return [x, y]
    
    def randPoint(self) -> list[float]:
        """
        主采样函数，默认调用推荐的数学方法。
        你可以更改它以调用 randPoint_rejection() 来测试拒绝采样。
        """
        return self.randPointMath() # 或者 self.randPoint_rejection()

# --- 使用示例 ---
if __name__ == '__main__':
    # 创建一个圆心在 (1, 2)，半径为 10 的 Solution 对象
    solution_obj = Solution(radius=10, x_center=1, y_center=2)

    print("使用原始不正确方法生成的点 (可能在圆心附近更密集):")
    for _ in range(3):
        point = solution_obj.randPoint_original_incorrect()
        print(point)

    print("\n使用拒绝采样方法生成的点 (均匀分布):")
    for _ in range(3):
        point = solution_obj.randPoint_rejection()
        print(point)

    print("\n使用数学修正方法生成的点 (均匀分布，推荐):")
    for _ in range(3):
        point = solution_obj.randPointMath() # 或者 solution_obj.randPoint()
        print(point)

    # 可视化 (需要 matplotlib)
    try:
        import matplotlib.pyplot as plt
        
        num_points = 2000
        
        points_incorrect = np.array([solution_obj.randPoint_original_incorrect() for _ in range(num_points)])
        points_rejection = np.array([solution_obj.randPoint_rejection() for _ in range(num_points)])
        points_math = np.array([solution_obj.randPointMath() for _ in range(num_points)])

        fig, axs = plt.subplots(1, 3, figsize=(18, 6), sharex=True, sharey=True)
        fig.suptitle(f"在圆 (x-{solution_obj.a})^2 + (y-{solution_obj.b})^2 = {solution_obj.r}^2 内采样点", fontsize=16)

        axs[0].scatter(points_incorrect[:, 0], points_incorrect[:, 1], s=5, alpha=0.5)
        axs[0].set_title("原始错误方法 (中心密集)")
        axs[0].set_aspect('equal', adjustable='box')
        circle_plot = plt.Circle((solution_obj.a, solution_obj.b), solution_obj.r, color='red', fill=False)
        axs[0].add_artist(circle_plot)


        axs[1].scatter(points_rejection[:, 0], points_rejection[:, 1], s=5, alpha=0.5, color='green')
        axs[1].set_title("拒绝采样方法 (均匀)")
        axs[1].set_aspect('equal', adjustable='box')
        circle_plot = plt.Circle((solution_obj.a, solution_obj.b), solution_obj.r, color='red', fill=False)
        axs[1].add_artist(circle_plot)

        axs[2].scatter(points_math[:, 0], points_math[:, 1], s=5, alpha=0.5, color='purple')
        axs[2].set_title("数学修正方法 (均匀)")
        axs[2].set_aspect('equal', adjustable='box')
        circle_plot = plt.Circle((solution_obj.a, solution_obj.b), solution_obj.r, color='red', fill=False)
        axs[2].add_artist(circle_plot)
        
        for ax in axs:
            ax.set_xlabel("x")
            ax.set_ylabel("y")
            ax.grid(True, linestyle='--', alpha=0.7)

        plt.tight_layout(rect=[0, 0, 1, 0.96])
        plt.show()

    except ImportError:
        print("\nMatplotlib 未安装，无法进行可视化。请运行 'pip install matplotlib' 来安装。")