import (
	"container/heap"
	"sort"
)

type IntHeap []int
type EventHeap [][2]int

func (h IntHeap) Len() int           { return len(h) }
func (h IntHeap) Less(i, j int) bool { return h[i] < h[j] } // 最小堆
func (h IntHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *IntHeap) Push(x interface{}) {
	*h = append(*h, x.(int))
}
func (h *IntHeap) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

func (h EventHeap) Len() int           { return len(h) }
func (h EventHeap) Less(i, j int) bool { return h[i][0] < h[j][0] }
func (h EventHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *EventHeap) Push(x interface{}) {
	*h = append(*h, x.([2]int))
}
func (h *EventHeap) Pop() interface{} {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

func smallestChair(times [][]int, targetFriend int) int {
	n := len(times)
	ids := make([]int, n)
	for i := 0; i < n; i++ {
		ids[i] = i
	}
	// 按到达时间排序
	sort.Slice(ids, func(i, j int) bool {
		return times[ids[i]][0] < times[ids[j]][0]
	})

	// 找到 targetFriend 的索引
	p := 0
	for i := 0; i < n; i++ {
		if ids[i] == targetFriend {
			p = i
			break
		}
	}

	// 初始化堆
	h := &IntHeap{}    // 可用椅子堆
	eh := &EventHeap{} // 事件堆（离开时间和椅子编号）
	heap.Init(h)
	heap.Init(eh)

	// 将椅子编号 0 到 p 添加到可用椅子堆中
	for i := 0; i <= p; i++ {
		heap.Push(h, i)
	}

	// 处理到 targetFriend 之前的每个人
	for i := 0; i < p; i++ {
		// 释放所有在当前到达时间之前离开的椅子
		for eh.Len() > 0 && (*eh)[0][0] <= times[ids[i]][0] {
			ev := heap.Pop(eh).([2]int) // 类型断言为 [2]int
			heap.Push(h, ev[1])         // 将椅子放回可用堆
		}
		// 分配一个椅子
		number := heap.Pop(h).(int)                     // 类型断言为 int
		heap.Push(eh, [2]int{times[ids[i]][1], number}) // 记录离开时间和椅子编号
	}

	// 处理 targetFriend 的情况
	for eh.Len() > 0 && (*eh)[0][0] <= times[ids[p]][0] {
		ev := heap.Pop(eh).([2]int)
		heap.Push(h, ev[1])
	}
	return heap.Pop(h).(int) // 返回 targetFriend 分配的椅子
}