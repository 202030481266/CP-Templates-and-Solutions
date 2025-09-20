#include <algorithm>
#include <execution>
#include <vector>
#include <random>
#include <chrono>
#include <iostream>
#include <thread>
#include <numeric>  // 添加这个头文件用于 std::iota

class SortBenchmark {
private:
	std::mt19937 gen{ std::random_device{}() };

	template<typename Func>
	double measure_time(Func f) {
		auto start = std::chrono::high_resolution_clock::now();
		f();
		auto end = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double, std::milli> diff = end - start;
		return diff.count();
	}

public:
	void benchmark_different_sizes() {
		std::cout << "硬件线程数: " << std::thread::hardware_concurrency() << "\n\n";
		std::cout << "数据量\t\t串行(ms)\t并行(ms)\t加速比\n";
		std::cout << "------------------------------------------------\n";

		// 测试不同数据规模
		for (int size = 1000; size <= 100'000'000; size *= 10) {
			std::vector<int> data(size);
			std::uniform_int_distribution<> dis(0, size);

			// 生成随机数据
			std::generate(data.begin(), data.end(),
				[&]() { return dis(gen); });

			// 串行排序
			auto serial_data = data;
			double serial_time = measure_time([&]() {
				std::sort(serial_data.begin(), serial_data.end());
				});

			// 并行排序
			auto parallel_data = data;
			double parallel_time = measure_time([&]() {
				std::sort(std::execution::par_unseq,
					parallel_data.begin(), parallel_data.end());
				});

			double speedup = serial_time / parallel_time;

			std::cout << size << "\t\t"
				<< serial_time << "\t\t"
				<< parallel_time << "\t\t"
				<< speedup << "x\n";
		}
	}

	void benchmark_different_patterns() {
		const int SIZE = 10'000'000;  // 1千万元素
		std::cout << "\n不同数据模式测试 (1千万元素):\n";
		std::cout << "模式\t\t\t串行(ms)\t并行(ms)\t加速比\n";
		std::cout << "------------------------------------------------\n";

		// 1. 完全随机
		{
			std::vector<int> data(SIZE);
			std::uniform_int_distribution<> dis(0, SIZE);
			std::generate(data.begin(), data.end(),
				[&]() { return dis(gen); });

			auto serial_data = data;
			double serial_time = measure_time([&]() {
				std::sort(serial_data.begin(), serial_data.end());
				});

			auto parallel_data = data;
			double parallel_time = measure_time([&]() {
				std::sort(std::execution::par_unseq,
					parallel_data.begin(), parallel_data.end());
				});

			std::cout << "完全随机\t\t"
				<< serial_time << "\t\t"
				<< parallel_time << "\t\t"
				<< serial_time / parallel_time << "x\n";
		}

		// 2. 已排序
		{
			std::vector<int> data(SIZE);
			std::iota(data.begin(), data.end(), 0);

			auto serial_data = data;
			double serial_time = measure_time([&]() {
				std::sort(serial_data.begin(), serial_data.end());
				});

			auto parallel_data = data;
			double parallel_time = measure_time([&]() {
				std::sort(std::execution::par_unseq,
					parallel_data.begin(), parallel_data.end());
				});

			std::cout << "已排序\t\t\t"
				<< serial_time << "\t\t"
				<< parallel_time << "\t\t"
				<< serial_time / parallel_time << "x\n";
		}

		// 3. 逆序
		{
			std::vector<int> data(SIZE);
			std::iota(data.begin(), data.end(), 0);
			std::reverse(data.begin(), data.end());

			auto serial_data = data;
			double serial_time = measure_time([&]() {
				std::sort(serial_data.begin(), serial_data.end());
				});

			auto parallel_data = data;
			double parallel_time = measure_time([&]() {
				std::sort(std::execution::par_unseq,
					parallel_data.begin(), parallel_data.end());
				});

			std::cout << "逆序\t\t\t"
				<< serial_time << "\t\t"
				<< parallel_time << "\t\t"
				<< serial_time / parallel_time << "x\n";
		}

		// 4. 大量重复
		{
			std::vector<int> data(SIZE);
			std::uniform_int_distribution<> dis(0, 100);  // 只有100种值
			std::generate(data.begin(), data.end(),
				[&]() { return dis(gen); });

			auto serial_data = data;
			double serial_time = measure_time([&]() {
				std::sort(serial_data.begin(), serial_data.end());
				});

			auto parallel_data = data;
			double parallel_time = measure_time([&]() {
				std::sort(std::execution::par_unseq,
					parallel_data.begin(), parallel_data.end());
				});

			std::cout << "大量重复(100种值)\t"
				<< serial_time << "\t\t"
				<< parallel_time << "\t\t"
				<< serial_time / parallel_time << "x\n";
		}
	}
};

// 添加 main 函数作为程序入口
int main() {
	SortBenchmark benchmark;

	std::cout << "========== C++ 并行排序性能测试 ==========\n\n";

	// 运行不同规模的测试
	benchmark.benchmark_different_sizes();

	// 运行不同数据模式的测试
	benchmark.benchmark_different_patterns();

	std::cout << "\n测试完成！\n";

	return 0;
}

/*
AMD 16 threads
========== C++ 并行排序性能测试 ==========

硬件线程数: 16

数据量          串行(ms)        并行(ms)        加速比
------------------------------------------------
1000            0.0263          0.2547          0.103259x
10000           0.5052          0.5283          0.956275x
100000          5.8651          2.7597          2.12527x
1000000         53.0609         11.5263         4.60346x
10000000                632.587         105.765         5.98104x
100000000               7221.69         1091.93         6.61371x

不同数据模式测试 (1千万元素):
模式                    串行(ms)        并行(ms)        加速比
------------------------------------------------
完全随机                640.12          101.715         6.29327x
已排序                  101.937         20.9239         4.87181x
逆序                    105.467         21.0004         5.02213x
大量重复(100种值)       166.865         73.1586         2.28086x

测试完成！
*/