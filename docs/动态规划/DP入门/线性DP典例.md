# 线性DP典例

## 例题 #1 [AGC031B] Reversi

题面翻译

有 $N$ 块石头摆成一行，从左数第 $i$ 块石头的颜色是 $C_i$。

现在すぬけ会进行 $0$ 次或若干次如下操作：选取两块颜色相同的石头并将两块石头之间的所有石头都染成与这两块石头相同的颜色。

求最终所有可能的石头排列方案数，答案对 $10^9 + 7$ 取模。

### 思路

【这是一个很经典的dp问题】

我们考虑dp

如果$c_{i-1}=c_i$，那么$f_i=f_{i-1}$，否则若存在$c_j=c_i,j<i$，先考虑直接继承（即不区间修改）时的转移，那么就是$f_{i-1}$。现在再考虑需要区间修改，那么就是$f_{j-1}$。如果有多个j都满足，那么就加上所有的$f_{j-1}$。显然转移即可。

---

```C++
/*
Code by Ntsc_Hodaka
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define mp make_pair
#define pii pair<int, int>

///----///
#define rd read()
inline int read() {
  int xx = 0, ff = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      ff = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
    xx = xx * 10 + (ch - '0'), ch = getchar();
  return xx * ff;
}
inline void write(int out) {
  if (out < 0)
    putchar('-'), out = -out;
  if (out > 9)
    write(out / 10);
  putchar(out % 10 + '0');
}

///----///
const int N = 2e6 + 5;
const int M = 1e7 + 5;
const int INF = 1e12 + 5;
const int MOD = 1e9+7;
const double eps = 1e-7;

int n;
int f[N],cnt[N],c[N];


signed main(){
  n=rd;
  for(int i=1;i<=n;i++){
    c[i]=rd;
  }
  f[0]=1;
  for(int i=1;i<=n;i++){
    f[i]=f[i-1];
    if(c[i-1]==c[i])continue;
    (f[i]+=cnt[c[i]])%=MOD;
    (cnt[c[i]]+=f[i-1])%=MOD;
  }
  cout<<f[n]<<endl;
}
```

- $1\ \leq\ N\ \leq\ 2\times\ 10^5$

- $1\ \leq\ C_i\ \leq\ 2\times\ 10^5(1\leq\ i\leq\ N)$

