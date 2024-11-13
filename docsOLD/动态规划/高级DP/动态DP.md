# 动态DP

注意，动态dp不是动态树分治。

在某些情况下，动态树分治可以与动态DP结合使用。例如，当需要在树上进行动态规划时，动态树分治可以用来处理树的结构变化，而动态DP可以用来计算树上的路径或子树上的状态。

摘抄[学习笔记 | 动态dp](https://flowus.cn/3aa6ab64-d771-4344-8105-035b4c6d954d)

---

## 例题 #1

给定一棵 $n$ 个点的树，点带点权。

有 $m$ 次操作，每次操作给定 $x,y$，表示修改点 $x$ 的权值为 $y$。

你需要在每次操作之后求出这棵树的最大权独立集（即“没有上司的舞会”）的权值大小。

### 思路

动态dp，顾名思义，就是带修改的dp。通常情况下暴力做这种dp没有出现该后我们都需要O(n)重新dp，但是这样就会超时。所以动态dp出现了。

---

[【洛谷P4719】动态DP【LCT】【矩阵】_p4719 lct-CSDN博客](https://blog.csdn.net/luositing/article/details/102728027)


[www.bilibili.com](https://www.bilibili.com/video/BV1HQ4y1g7u3/?spm_id_from=333.337.search-card.all.click&vd_source=f45ea4e1e4b3b73d5f07c57b46c43aba)


```C++
// 动态dp的LCT实现

#include <bits/stdc++.h>
#define rep(l, r, i) for (int i = l, END##i = r; i <= END##i; ++i)
#define per(r, l, i) for (int i = r, END##i = l; i >= END##i; --i)
using namespace std;
#define pb push_back
// #define mpy make_pair
#define int long long
#define pii pair<int, int>
#define ps b
#define pf a

#define X(j) i[j]
#define Y(j) (dp[j] + (i[j] + L) * (i[j] + L))

#define rd read()
int read() {
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
void write(int out) {
  if (out < 0)
    putchar('-'), out = -out;
  if (out > 9)
    write(out / 10);
  putchar(out % 10 + '0');
}

#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
#define notroot(x) lc(fa[x]) == x || rc(fa[x]) == x
const int N = 100010, inf = (1 << 30);
int n, m, a[N], f[N][2];
vector<int> G[N];
int ch[N][2], fa[N]; // splay:ch儿,fa父
struct matrix {
  int g[2][2];
  matrix() { g[0][0] = g[0][1] = g[1][0] = g[1][1] = -inf; }
  matrix operator*(matrix b) {
    matrix t;
    for (int i = 0; i < 2; ++i)
      for (int j = 0; j < 2; ++j)
        for (int k = 0; k < 2; ++k)
          t.g[i][j] = max(t.g[i][j], g[i][k] + b.g[k][j]);
    return t;
  }
} mt[N], tr[N]; // mt:节点x的g矩阵, tr:节点x的矩阵积

void dfs(int x) { // 预处理fa,f,mt,tr
  f[x][1] = a[x];
  for (int y : G[x]) {
    if (y != fa[x]) {
      fa[y] = x;
      dfs(y);
      f[x][0] += max(f[y][0], f[y][1]);
      f[x][1] += f[y][0];
    }
  }
  mt[x].g[0][0] = mt[x].g[0][1] = f[x][0];
  mt[x].g[1][0] = f[x][1];
  tr[x] = mt[x]; // 初始时每个点就是一个splay
}

namespace LCT {

    void pushup(int x) { // 上传
    tr[x] = mt[x];
    if (lc(x))
        tr[x] = tr[lc(x)] * tr[x];
    if (rc(x))
        tr[x] = tr[x] * tr[rc(x)]; // 矩阵积(即和取最大)
    }
    void rotate(int x) {                        // 旋转x
    int y = fa[x], z = fa[y], k = rc(y) == x; // y的右儿是x吗
    if (notroot(y))
        ch[z][rc(z) == y] = x;
    fa[x] = z; // z的儿是x,x的父是z
    ch[y][k] = ch[x][k ^ 1];
    fa[ch[x][k ^ 1]] = y; // y的儿是x的异儿,x的异儿的父是y
    ch[x][k ^ 1] = y;
    fa[y] = x; // x的异儿是y,y的父是x
    pushup(y);
    pushup(x); // 自底向上pushup
    }
    void splay(int x) {    // x伸展到根
    while (notroot(x)) { // 折线转xx,直线转yx
        int y = fa[x], z = fa[y];
        if (notroot(y))
        (rc(y) == x) ^ (rc(z) == y) ? rotate(x) : rotate(y);
        rotate(x);
    }
    }
    void access(int x) { // 打通x到树根的路
    for (int y = 0; x;) {
        splay(x);    // x转到当前splay的根
        if (rc(x)) { // x右儿子即将变成虚儿子,加上其贡献
        mt[x].g[0][0] += max(tr[rc(x)].g[0][0], tr[rc(x)].g[1][0]);
        mt[x].g[1][0] += tr[rc(x)].g[0][0];
        mt[x].g[0][1] = mt[x].g[0][0];
        }
        if (y) { // y即将变成x的实儿子,减去其贡献
        mt[x].g[0][0] -= max(tr[y].g[0][0], tr[y].g[1][0]);
        mt[x].g[1][0] -= tr[y].g[0][0];
        mt[x].g[0][1] = mt[x].g[0][0];
        }
        rc(x) = y;     // 把y变成x的右儿子(即x指向下面splay的根)
        pushup(x);     // 更新x
        x = fa[y = x]; // 把x存于y,x继续爬到上面的splay
    }
    }
    void update(int x, int y) {  // 修改点权
    access(x);                 // 通路
    splay(x);                  // 伸展
    mt[x].g[1][0] += y - a[x]; // 修改x点
    pushup(x);
    a[x] = y;
    }
    
} // namespace LCT

using namespace LCT;

signed main() {
  n = rd, m = rd;
  for (int i = 1; i <= n; ++i)
    a[i] = rd;
  for (int i = 1; i < n; i++) {
    int x = rd, y = rd;
    G[x].push_back(y);
    G[y].push_back(x);
  }
  dfs(1); // 预处理fa,f,mt,tr
  while (m--) {
    int x = rd, y = rd;
    update(x, y);
    printf("%lld\n", max(tr[x].g[0][0], tr[x].g[1][0]));
  }
}
```

- 对于 $100\%$ 的数据，保证 $1\le n,m\le 10^5$，$1 \leq u, v , x \leq n$，$-10^2 \leq a_i, y \leq 10^2$。

## 例题 #2 [CSP-S 2022] 数据传输

小 C 正在设计计算机网络中的路由系统。

测试用的网络总共有 $n$ 台主机，依次编号为 $1 \sim n$。这 $n$ 台主机之间由 $n - 1$ 根网线连接，第 $i$ 条网线连接个主机 $a_i$ 和 $b_i$。保证任意两台主机可以通过有限根网线直接或者间接地相连。受制于信息发送的功率，主机 $a$ 能够直接将信息传输给主机 $b$ 当且仅当两个主机在可以通过不超过 $k$ 根网线直接或者间接的相连。

在计算机网络中，数据的传输往往需要通过若干次转发。假定小 C 需要将数据从主机 $a$ 传输到主机 $b$（$a \neq b$），则其会选择出若干台用于传输的主机 $c_1 = a, c_2, \ldots, c_{m - 1}, c_m = b$，并按照如下规则转发：对于所有的 $1 \le i < m$，主机 $c_i$ 将信息直接发送给 $c_{i + 1}$。

每台主机处理信息都需要一定的时间，第 $i$ 台主机处理信息需要 $v_i$ 单位的时间。数据在网络中的传输非常迅速，因此传输的时间可以忽略不计。据此，上述传输过程花费的时间为 $\sum_{i = 1}^{m} v_{c_i}$。

现在总共有 $q$ 次数据发送请求，第 $i$ 次请求会从主机 $s_i$ 发送数据到主机 $t_i$。小 C 想要知道，对于每一次请求至少需要花费多少单位时间才能完成传输。

输入格式

输入的第一行包含三个正整数 $n, Q, k$，分别表示网络主机个数，请求个数，传输参数。数据保证 $1 \le n \le 2 \times {10}^5$，$1 \le Q \le 2 \times {10}^5$，$1 \le k \le 3$。

输入的第二行包含 $n$ 个正整数，第 $i$ 个正整数表示 $v_i$，保证 $1 \le v_i \le {10}^9$。

接下来 $n - 1$ 行，第 $i$ 行包含两个正整数 $a_i, b_i$，表示一条连接主机 $a_i, b_i$ 的网线。保证 $1 \le a_i, b_i \le n$。

接下来 $Q$ 行，第 $i$ 行包含两个正整数 $s_i, t_i$，表示一次从主机 $s_i$ 发送数据到主机 $t_i$ 的请求。保证 $1 \le s_i, t_i \le n$，$s_i \ne t_i$。

输出格式

$Q$ 行，每行一个正整数，表示第 $i$ 次请求在传输的时候至少需要花费多少单位的时间。

对于所有的测试数据，满足 $1 \le n \le 2 \times {10}^5$，$1 \le Q \le 2 \times {10}^5$，$1 \le k \le 3$，$1 \le a_i, b_i \le n$，$1 \le s_i, t_i \le n$，$s_i \ne t_i$。

