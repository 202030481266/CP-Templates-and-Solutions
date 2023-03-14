#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdio>
using namespace std;
long long bg,bl;
long long f[10005],a,b,p=9901;
long long cnt[10005];
long long ans=1;

long long ppow (long long a,long long b){
	long long r=1,base=a;
	while(b){
		if(b&1) r=(base*r)%p;
		base=(base*base)%p;
		b>>=1;
	}
	return r;
}

long long ga(int i){
	return ppow(i,p-2)%p;
}

void sp(){
	for(long long i=2;i<=bg;i++){
		if(bg%i==0){
			cnt[a]=0;
			while(bg%i==0) cnt[a]++,bg/=i; 
			if(i%p==1) ans=ans*(cnt[a]+1)%p;
			else ans=ans*((ppow(i,cnt[a]*bl+1)-1)*ga(i-1))%p;
		}
	}
}

int main(){
	cin>>bg>>bl;
	sp();
	cout<<ans;
}
