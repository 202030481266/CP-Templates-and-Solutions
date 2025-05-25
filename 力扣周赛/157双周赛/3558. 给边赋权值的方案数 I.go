const mod = int(1e9) + 7

func quickPow(a, b int) int {
	var res int64 = 1
	a64 := int64(a)
	for b > 0 {
		if b&1 > 0 {
			res = res * a64 % int64(mod)
		}
		a64 = a64 * a64 % int64(mod)
		b >>= 1
	}
	return int(res)
}

func assignEdgeWeights(edges [][]int) int {
	n := len(edges) + 1
	graph := make([][]int, n+1)
	dep := make([]int, n+1)
	for _, e := range edges {
		u, v := e[0], e[1]
		graph[u] = append(graph[u], v)
		graph[v] = append(graph[v], u)
	}
	var dfs func(int, int)
	dfs = func(u, fa int) {
		dep[u] = dep[fa] + 1
		for _, v := range graph[u] {
			if v != fa {
				dfs(v, u)
			}
		}
	}
	dfs(1, 0)
	mx := 0
	for _, d := range dep {
		if d > mx {
			mx = d
		}
	}
	return quickPow(2, mx-2)
}