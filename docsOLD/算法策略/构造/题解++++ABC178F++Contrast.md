# [ABC178F] Contrast

## 题面翻译

给定两个长度为 $N$ 且升序排列的序列 $A,B$ ，问是否可以重新排列 $B$ ，使得所有 $i$ 均满足 $A_i \not = B_i$ ，可行则输出 `Yes` 并换行输出任意一组可行的 $B$ ，元素以空格隔开，否则输出 `No` 。

输入先是一行一个整数 $N$ ，再是两行两个序列 $A,B$。

- $1\leq\ N\ \leq\ 2\ \times\ 10^5$

- $1\leq\ A_i,B_i\ \leq\ N$

## 思路

（恭喜！没看题解5min就想到了正解！）

~~我们进行预处理，将A中没有的数从B中剔除。~~好像并不需要。

首先考虑最简单的情况：如果 $A,B$ 中出现最多的元素相同，那么我们考虑出现最多的那个相同元素的个数。假设 $A$ 中有 $i$ 个数字 $k$，$B$ 中有 $j$ 个数字 $k$，若 $i+j>N$ 则无解。否则一定有解。

推广到所有情况，我们发现对于每一个数字 $i$，我们统计其出现的次数 $t_i$，如果存在 $t_i>N$ 则无解，否则有解。

我们考虑一下这种情况，这已经是极限情况了。但很显然，我们依旧可以找到合法的方案。

```Plain Text
6 
1 1 1 1 3 3
3 3 3 3 1 1
```

这时我把 $A$ 中或者 $B$ 中某些数字更改一下，那很显然就更可以找到合法的方案了。



至于输出方案，我们将 $B$ 排序从大到小输出，当遇到 $A_i=B_i=j$ 的情况我们就把 $B_i$ 赋值为下一个数，等 $A_i≠j$ 时我们再考虑安排 $j$。

## 代码

```C++
/*////////ACACACACACACAC///////////
	   . Coding by Ntsc .
	   . ToFind Chargcy .
	   . Prove Yourself .
/*////////ACACACACACACAC///////////

//头文件
#include<bits/stdc++.h>

//数据类型
#define ll long long
#define ull unsigned long long
#define db double
#define endl '\n'
//命名空间
using namespace std;
//常量
const int N=2e5+5;
const int M=1e3;
const int MOD=903250223;
const int INF=1e9;
//变量
int n,m,a[N],b[N],c,ton[N],y[N],ans,t,mx,res,tmp,cnt,web[M][M];
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>a[i];ton[a[i]]++;
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];ton[b[i]]++;
		mx=max(mx,ton[b[i]]);
	}

	if(mx>n){printf("No\n");return 0;}
	cout<<"Yes\n";
	for(int i=1,j=n;i<=n;i++,j--){
		if(j<1){
			cout<<t<<' ';continue;
		}
		if(a[i]==b[j]){t=b[j];while(a[i]==b[j])j--;}
		cout<<b[j]<<' ';
	}
#ifdef PAUSE_ON_EXIT
	system("pause");
#endif
	return 0;
}
```

