// 拓扑排序
func findAllRecipes(recipes []string, ingredients [][]string, supplies []string) []string {
	mp := make(map[string]int)
	rmp := make(map[int]string)
	id := 0
	for _, r := range recipes {
		if mp[r] == 0 {
			id++
			mp[r] = id
			rmp[id] = r
		}
	}
	for i := 0; i < len(ingredients); i++ {
		for j := 0; j < len(ingredients[i]); j++ {
			if mp[ingredients[i][j]] == 0 {
				id++
				mp[ingredients[i][j]] = id
			}
		}
	}
	var q []int
	g := make([][]int, id+1)
	degree := make([]int, id+1)
	for i := 0; i < len(recipes); i++ {
		for _, s := range ingredients[i] {
			g[mp[s]] = append(g[mp[s]], mp[recipes[i]])
			degree[mp[recipes[i]]]++
		}
	}
	var ans []string
	for _, s := range supplies {
		if mp[s] > 0 {
			q = append(q, mp[s])
		}
	}
	for len(q) > 0 {
		var tmp []int
		for _, u := range q {
			if rmp[u] != "" {
				ans = append(ans, rmp[u])
			}
			for _, v := range g[u] {
				degree[v]--
				if degree[v] == 0 {
					tmp = append(tmp, v)
				}
			}
		}
		q = tmp
	}
	return ans
}