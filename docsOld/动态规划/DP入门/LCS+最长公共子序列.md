# LCS 最长公共子序列

【模板】最长公共子序列

题目描述

给出 $1,2,\ldots,n$ 的两个排列 $P_1$ 和 $P_2$ ，求它们的最长公共子序列。

输入格式

第一行一个整数N，表示我们要将1到N插入序列中。

接下是N个数字，第k个数字Xk，表示我们将k插入到位置Xk（0<=Xk<=k-1,1<=k<=N）

输出格式

N行，第i行表示i插入Xi位置后序列的最长上升子序列的长度是多少。

100%的数据 n<=100000

- 对于 $50\%$ 的数据， $n \le 10^3$；

- 对于 $100\%$ 的数据， $n \le 10^5$。

---

我们先设计dp状态，$f_{i,j}$表示$P_1$以$i$结尾，$P_2$以$j$结尾时的LCS长度。那么有转移

- 若$P_1[i]=P_2[j]$，那么$f_{i,j}=f_{i-1-,j-1}+1$

- 否则在$f_{i-1,j},f_{i,j-1}$中取最大值

实现

两层循环即可。

基本的内容不要忘！

```C++
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
int ans,n,p1[MAXN],p2[MAXN],dp[MAXN],web[MAXN];
int main(){
	cin>>n;
	
	for(int i=1;i<=n;i++){
		cin>>p1[i];web[p1[i]]=i;
	}
	for(int i=1;i<=n;i++){
		cin>>p2[i];dp[i]=0x7f;
	}
	dp[0]=0;
	for(int i=1;i<=n;i++){
		int l=0,r=ans,mid;
		if(web[p2[i]]>dp[ans])dp[++ans]=web[p2[i]];
		else{
			while(l<r){
				mid=(l+r)/2;
				if(dp[mid]>web[p2[i]])r=mid;
				else l=mid+1;
			}
			dp[l]=min(web[p2[i]],dp[l]);
		}
	
	}
	cout<<ans;
	return 0;
} 
```

