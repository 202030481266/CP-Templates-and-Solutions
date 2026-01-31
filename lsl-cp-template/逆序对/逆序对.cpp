
int cnt=0;
void Merge(int r[],int r1[],int s,int m,int t)	// 合并子序列
{
	int i=s,j=m+1,k=s;
	int b;
	while(i<=m && j<=t){
		if(r[i]<=r[j]){       // 取较小者放入r1[k]中
			r1[k++]=r[i++];
		}
		else{                 	
			cnt+=m-i+1;	// 若左边数大于右边数，则左边数及其后边数都大于该右边数		
			b=i;              
			while(b<=m){
				printf("[%d,%d]\n",r[b],r[j]);
				// vec.push_back(make_pair(b, j));
				b++;
			}
			r1[k++]=r[j++];
		}
 
	}
	while(i<=m)			// 若第一个子序列没处理完，则进行收尾处理;下同
		r1[k++]=r[i++];
	while(j<=t)
		r1[k++]=r[j++];
}
void MergeSort(int r[],int s,int t){  // 对序列r[s]~r[t]进行归并排序
	int m,r1[1000],i;
	if(s==t)
		return ;
	else{
		m=(s+t)/2;	       // 划分
		MergeSort(r,s,m);     // 子问题1
		MergeSort(r,m+1,t);   // 子问题2
		Merge(r,r1,s,m,t);    // 合并
		for(i=s;i<=t;i++)
			r[i]=r1[i];
	}
}
int main() {
  MergeSort(b, s, t); // b为数组名字，[s,t]闭区间中的逆序对的个数为count个
}