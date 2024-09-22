# 榨取kkksc03

> [https://www.luogu.com.cn/problem/P1855](https://www.luogu.com.cn/problem/P1855)
本题在01背包基础上增加了1维度

```C++
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n,M,T, m[N],t[N], f[2*N][2*N];

int main() {
	cin >> n>>M>>T;

	for (int i = 1; i <= n; i++) {
		cin >> m[i]>>t[i];
	}

	for(int i=1;i<=n;i++)
		for(int j=M;j>=m[i];j--)
			for(int k=T;k>=t[i];k--){
				f[j][k]=max(f[j][k],f[j-m[i]][k-t[i]]+1);
			}
	cout<<f[M][T];
	return 0;
}
```

`f[][]`存的是还剩下i金钱，j时间时最多能实现的愿望数
慢慢来。
第一次循环时。`f`数组全为0；
在取`f[j][k]=max(f[j][k],f[j-m[i]][k-t[i]]+1);`时，因为`f`全为0，会更新当`f[j][k]`为1，我们不需要记录它实现了哪几个愿望，只需要知道此时可以实现几个愿望。
**分析循环**

- 最外层循环：分别讨论存取第i个愿望时要不要把这个愿望放进去（针对每一个`f[>=M-m[i]][>=T-t[i]]`,即可以把这个愿望放进去的情况，如果这个愿望本来就放不进去，就不需要讨论了>即就是原来的`f[][]`)

- 里面2层循环：可以调换，只是为了把表填满好为后续服务。在`f[>=M-m[i]][>=T-t[i]]`的条件下，不同剩余金钱好剩余时间可以实现的愿望数。

**分析递推式**

```Plain Text
f[j][k]=max(f[j][k],f[j-m[i]][k-t[i]]+1);
```

- 第`i`个梦想

- 金钱为`j`

- 时间为`m`
f[j][k]=max  **(** 如果不取这个愿望时原来可以实现的梦想 **，** 如果要取这个愿望(1+当去掉这个愿望使用的金钱和时间后能实现的愿望的最大值，就是f[j-m[i]][k-t[i]]) **)**

