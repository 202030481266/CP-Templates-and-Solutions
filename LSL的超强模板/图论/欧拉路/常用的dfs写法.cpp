void dfs(int now)
{
	for(int i=del[now];i<G[now].size();i=del[now])
	{
		del[now]=i+1;
		dfs(G[now][i])
	}
	st.push(now);
 }
 //其中 del[now] 表示 G[now][1,2……,del[now]-1] 都已经被标记访问过，下一次要从G[now][del[now]]开始访问。