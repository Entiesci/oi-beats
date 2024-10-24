# AC自动机

[AC自动机](https://flowus.cn/fd6716bb-f405-4698-a9db-2bbd53422388)

ac自动机：多次询问一个单词在文本中出现的次数/在几个单词中的子串有出现。

[TJOI2013] 单词，[COCI2015] Divljak



## [TJOI2013] 单词

### 题目描述

小张最近在忙毕设,所以一直在读论文。一篇论文是由许多单词组成但小张发现一个单词会在论文中出现很多次，他想知道每个单词分别在论文中出现了多少次。

### 思路

看了样例后，我们发现好像并没有那么简单。

std

```C++
#include <bits/stdc++.h>
#include <queue>
#define rep(l, r, i) for (int i = l, END##i = r; i <= END##i; ++i)
#define per(r, l, i) for (int i = r, END##i = l; i >= END##i; --i)
using namespace std;
#define int long long
#define pii pair<int, int>

#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)

#define rd read()
inline int read() {
  int xx = 0, ff = 1;
  char tr = getchar();
  while (tr < '0' || tr > '9') {
    if (tr == '-')
      ff = -1;
    tr = getchar();
  }
  while (tr >= '0' && tr <= '9')
    xx = xx * 10 + (tr - '0'), tr = getchar();
  return xx * ff;
}
inline void write(int out) {
  if (out < 0)
    putchar('-'), out = -out;
  if (out > 9)
    write(out / 10);
  putchar(out % 10 + '0');
}

#define db double
#define rtn return

const int N = 2e6 + 5;
const int M = 1e5;
int MOD = 1e9 + 7;
const int INF = 1e12;

int n, a[N], h[N], cnt, last, tr[N][26], sz[N], fail[N];
char s[N];
void insert(int x) {
  scanf("%s", s + 1);
  int now = 0, len = strlen(s + 1);
  for (int i = 1; i <= len; i++) {
    int u = s[i] - 'a';
    if (!tr[now][u])
      tr[now][u] = ++cnt;
    now = tr[now][u];
    sz[now]++;
  }
  a[x] = now;
}
void build() {
  int i, head = 0, tail = 0;
  for (i = 0; i < 26; i++)
    if (tr[0][i])
      h[++tail] = tr[0][i];
  while (head < tail) {
    int x = h[++head], y;
    for (i = 0; i < 26; i++)
      if (y = tr[x][i]) {
        h[++tail] = y;
        fail[y] = tr[fail[x]][i];
      } else
        tr[x][i] = tr[fail[x]][i];
  }
}

signed main() {
  n = rd;
  for (int i = 1; i <= n; i++)
    insert(i);
  build();

  for (int i = cnt; i >= 0; i--)
    sz[fail[h[i]]] += sz[h[i]];
  for (int i = 1; i <= n; i++)
    printf("%d\n", sz[a[i]]);
  return 0;
}

```

### 输入格式

第一行一个整数 $N$，表示有 $N$ 个单词。

接下来 $N$ 行每行一个单词,每个单词都由小写字母 $a-z$ 组成。

### 输出格式

输出 $N$ 个整数,第 $i$ 行的数表示第 $i$ 个单词在文章中出现了多少次。

### 样例 #1

#### 样例输入 #1

```C++
3
a
aa
aaa
```

#### 样例输出 #1

```C++
6
3
1
```

### 提示

#### 数据规模与约定

- $30\%$ 的数据， 单词总长度不超过 $10^3$。

- $100\%$ 的数据，$1 \leq n \leq 200$，单词总长度不超过 $10^6$。

## [USACO15FEB] Censoring G

### 题目描述

FJ 把杂志上所有的文章摘抄了下来并把它变成了一个长度不超过 $10^5$ 的字符串 $s$。他有一个包含 $n$ 个单词的列表，列表里的 $n$ 个单词记为 $t_1 \cdots t_n$。他希望从 $s$ 中删除这些单词。

FJ 每次在 $s$ 中找到最早出现的列表中的单词（最早出现指该单词的开始位置最小），然后从 $s$ 中删除这个单词。他重复这个操作直到 $s$ 中没有列表里的单词为止。注意删除一个单词后可能会导致 $s$ 中出现另一个列表中的单词。

FJ 注意到列表中的单词不会出现一个单词是另一个单词子串的情况，这意味着每个列表中的单词在 $s$ 中出现的开始位置是互不相同的。

请帮助 FJ 完成这些操作并输出最后的 $s$。

### 思路

std

### 输入格式

第一行是一个字符串，表示文章 $s$。

第二行有一个整数，表示单词列表的单词个数 $n$。

第 $3$ 到第 $(n + 2)$ 行，每行一个字符串，第 $(i + 2)$ 行的字符串 $t_i$ 表示第 $i$ 个单词。

### 输出格式

输出一行一个字符串，表示操作结束后的 $s$。

### 提示

##### 数据规模与约定

对于全部的测试点，保证：

- $1 \leq |s|, \sum\limits_{i = 1}^n |t_i|, n \leq 10^5$。

- 字符串均只含小写字母。

- 操作结束后 $s$ 不会被删成空串。

- 对于所有的 $i \neq j$，$t_i$ 不是 $t_j$ 的子串。

其中对于一个字符串 $x$，约定 $|x|$ 表示 $x$ 的长度。

---

##### 提示

操作过程中 $s$ 有可能某一个前缀子串被完全删除，请格外注意这一点。

下面是哈希写法。

```C++
#include <bits/stdc++.h>
#include <queue>
#define rep(l, r, i) for (int i = l, END##i = r; i <= END##i; ++i)
#define per(r, l, i) for (int i = r, END##i = l; i >= END##i; --i)
using namespace std;
#define int long long
#define pii pair<int, int>

#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)

#define rd read()
inline int read() {
  int xx = 0, ff = 1;
  char tr = getchar();
  while (tr < '0' || tr > '9') {
    if (tr == '-')
      ff = -1;
    tr = getchar();
  }
  while (tr >= '0' && tr <= '9')
    xx = xx * 10 + (tr - '0'), tr = getchar();
  return xx * ff;
}
inline void write(int out) {
  if (out < 0)
    putchar('-'), out = -out;
  if (out > 9)
    write(out / 10);
  putchar(out % 10 + '0');
}

#define db double
#define rtn return

const int N = 2e5 + 5;
const int M = 1e5;
int MOD = 1e9 + 7;
const int INF = 1e12;

const int b = 131;
int h[N], mul[N] = {1};
char str[N], u[N], tmp[N];
int ptr;
struct node {
  int len;
  int h;
} t[N];
bool cmp(const node &a, const node &b) { return a.len < b.len; }
inline int calHash(int j, int i) { return h[i] - h[j - 1] * mul[i - j + 1]; }
signed main() {
  scanf("%s", str + 1);
  int n = strlen(str + 1), m;
  m = rd;
  for (int i = 1; i <= m; ++i) {
    scanf("%s", tmp + 1);
    t[i].len = strlen(tmp + 1);
    for (int j = 1; j <= t[i].len; ++j)
      t[i].h = t[i].h * b + tmp[j];
  }
  sort(t + 1, t + 1 + m, cmp);
  for (int i = 1; i <= n; ++i)
    mul[i] = (mul[i - 1] * b);
  for (int i = 1; i <= n; ++i) {
    u[++ptr] = str[i], h[ptr] = h[ptr - 1] * b + u[ptr];
    while (ptr < t[1].len && i < n)
      u[++ptr] = str[++i], h[ptr] = h[ptr - 1] * b + u[ptr];
    for (int j = 1; j <= m && ptr; ++j)
      if (ptr - t[j].len + 1 >= 1 &&
          calHash(ptr - t[j].len + 1, ptr) == t[j].h) {
        ptr -= t[j].len;
      }
  }
  for (int i = 1; i <= ptr; ++i)
    putchar(u[i]);
  cout << endl;
  return 0;
}
```

## [COCI2015] Divljak

### 题目描述

Alice 有 $n$ 个字符串 ${S}_1, {S}_2, \ldots, {S}_n$，Bob 有一个字符串集合 ${T}$，一开始集合是空的。

接下来会发生 $q$ 个操作，操作有两种形式：

1. `1 P`：Bob 往自己的集合里添加了一个字符串 ${P}$。

2. `2 x`：Alice 询问 Bob，集合 ${T}$ 中有多少个字符串包含串 ${S}_x$（我们称串 ${A}$ 包含串 ${B}$，当且仅当 ${B}$ 是 ${A}$ 的子串）。

### 思路

std

### 输入格式

第一行一个整数 $n$。

接下来 $n$ 行，第 $i$ 行一个字符串 ${S}_i$。

接下来一行一个整数 $q$。

接下来 $q$ 行，每行一个操作。

### 输出格式

对每个 `2 x` 操作，一行一个整数，表示答案。

### 样例 #1

#### 样例输入 #1

```C++
3
a
bc
abc
5
1 abca
2 1
1 bca
2 2
2 3
```

#### 样例输出 #1

```C++
1
2
1
```

### 提示

对于 $100\%$ 的数据，$1 \leq n,q \leq 10^5$，字符串由小写字母构成，$S$ 和 $P$ 的总长分别 $\le 2 \times 10^6$。

## You Are Given Some Strings...

### 题面翻译

你有一个字符串 $t$ 和 $n$ 个字符串 $s_1,s_2,...,s_n$,所有字符串都只含有小写英文字母。

令 $f(t,s)$ 为 $s$ 在 $t$ 中的出现次数，如 $f('aaabacaa','aa')=3$,$f('ababa','aba')=2$.

请计算 $\sum_{i=1}^n\sum_{j=1}^nf(t,s_i+s_j)$,其中 $s+t$ 代表 $s$ 和 $t$ 连接起来。

注意如果存在两对整数 $i_1,j_1,i_2,j_2$,使 $s_{i_1}+s_{j_1}=s_{i_2}+s_{j_2}$,你需要把 $f(t,s_{i_1}+s_{j_1})$ 和 $f(t,s_{i_2}+s_{j_2})$ 加在答案里。

### 思路

考虑枚举t中的划分点x，该点及之前为$s_i$（长度不定）​,该点之后为$s_j$​,统计一下$s_i$​,$s_j$​的数量$f_1(x),f_2(x+1)$然后乘法原理相乘即可。

---

std

```C++
#include <bits/stdc++.h>
#include <queue>
#define rep(l, r, i) for (int i = l, END##i = r; i <= END##i; ++i)
#define per(r, l, i) for (int i = r, END##i = l; i >= END##i; --i)
using namespace std;
#define int long long
#define pii pair<int, int>

#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)

#define rd read()
inline int read() {
  int xx = 0, ff = 1;
  char tr = getchar();
  while (tr < '0' || tr > '9') {
    if (tr == '-')
      ff = -1;
    tr = getchar();
  }
  while (tr >= '0' && tr <= '9')
    xx = xx * 10 + (tr - '0'), tr = getchar();
  return xx * ff;
}
inline void write(int out) {
  if (out < 0)
    putchar('-'), out = -out;
  if (out > 9)
    write(out / 10);
  putchar(out % 10 + '0');
}

#define db double
#define rtn return

const int N = 4e5 + 5;
const int M = 3e7 + 5;
int MOD = 1e9 + 7;
const int INF = 1e12;
int n, id[N];
char t[N], s[N], t2[N];
struct ACAM {
  int flag[N], fail[N], ch[N][26], id;

  void add(char a[], int val) {
    int len = strlen(a + 1), now = 0;
    for (int i = 1; i <= len; i++) {
      if (!ch[now][a[i] - 'a'])
        ch[now][a[i] - 'a'] = ++id;
      now = ch[now][a[i] - 'a'];
    }
    flag[now] += val;
  }
  void getFail() {
    queue<int> q;
    for (int i = 0; i <= 25; i++)
      if (ch[0][i])
        q.push(ch[0][i]);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      flag[u] += flag[fail[u]];
      for (int i = 0; i <= 25; i++) {
        if (ch[u][i])
          fail[ch[u][i]] = ch[fail[u]][i], q.push(ch[u][i]);
        else
          ch[u][i] = ch[fail[u]][i];
      }
    }
  }
} tr, tr2;
signed main() {
  scanf("%s", t + 1);
  int l = strlen(t + 1);
  for (int i = 1; i <= l; i++)
    t2[i] = t[l - i + 1]; // 反向
  tr.add(t, 0);
  tr2.add(t2, 0);
  n = rd;
  for (int i = 1; i <= n; i++) {
    scanf("%s", s + 1), tr.add(s, 1);
    reverse(s + 1, s + 1 + strlen(s + 1));
    tr2.add(s, 1);
  }
  tr.getFail();
  tr2.getFail();

  int now = 0, len = strlen(t + 1), ans = 0;
  for (int i = 1; i <= len; i++) {
    now = tr2.ch[now][t2[i] - 'a'];
    id[i] = now;//反向串的下标信息
  } 
  now = 0;
  for (int i = 1; i <= len - 1; i++) {
    now = tr.ch[now][t[i] - 'a'];
    ans += tr.flag[now] * tr2.flag[id[len - i]];
  }
  cout << ans;
}

```

### 题目描述

You are given a string $t$ and $n$ strings $s_1, s_2, \dots, s_n$ . All strings consist of lowercase Latin letters.

Let $f(t, s)$ be the number of occurences of string $s$ in string $t$ . For example, $f('\text{aaabacaa}', '\text{aa}') = 3$ , and $f('\text{ababa}', '\text{aba}') = 2$ .

Calculate the value of $\sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n} f(t, s_i + s_j)$ , where $s + t$ is the concatenation of strings $s$ and $t$ . Note that if there are two pairs $i_1$ , $j_1$ and $i_2$ , $j_2$ such that $s_{i_1} + s_{j_1} = s_{i_2} + s_{j_2}$ , you should include both $f(t, s_{i_1} + s_{j_1})$ and $f(t, s_{i_2} + s_{j_2})$ in answer.

### 输入格式

The first line contains string $t$ ( $1 \le |t| \le 2 \cdot 10^5$ ).

The second line contains integer $n$ ( $1 \le n \le 2 \cdot 10^5$ ).

Each of next $n$ lines contains string $s_i$ ( $1 \le |s_i| \le 2 \cdot 10^5$ ).

It is guaranteed that $\sum\limits_{i=1}^{n} |s_i| \le 2 \cdot 10^5$ . All strings consist of lowercase English letters.

### 输出格式

Print one integer — the value of $\sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n} f(t, s_i + s_j)$ .

### 样例 #1

#### 样例输入 #1

```C++
aaabacaa
2
a
aa
```

#### 样例输出 #1

```C++
5
```

### 样例 #2

#### 样例输入 #2

```C++
aaabacaa
4
a
a
a
b
```

#### 样例输出 #2

```C++
33
```

## [POI2000] 病毒

### 题目描述

二进制病毒审查委员会最近发现了如下的规律：某些确定的二进制串是病毒的代码。如果某段代码中不存在任何一段病毒代码，那么我们就称这段代码是安全的。现在委员会已经找出了所有的病毒代码段，试问，是否存在一个无限长的安全的二进制代码。

示例：

例如如果 $\{011, 11, 00000\}$ 为病毒代码段，那么一个可能的无限长安全代码就是 $010101 \ldots$。如果 $\{01, 11, 000000\}$ 为病毒代码段，那么就不存在一个无限长的安全代码。

现在给出所有的病毒代码段，判断是否存在无限长的安全代码。

### 思路

我们知道，AC自动机是一种多模字符串匹配算法。构造 Trie 树 后，在模式串末尾一位的结点作上标记。平常的 AC自动机 是尽量能多接触到这些标记，使总值最大。本题倒是有点奇葩，要构造一个可行的无限长文本串，使没有任何子串为给出模式串中的一个。也就是说，我们需要让平常 AC自动机 的查询操作，尽量避免标记，能用失配指针跳转就跳转。

因为要有无限长的可行串，根据 AC自动机 的原理，我们可以将结点连接到儿子的边当作一条单向边，同时失配指针也当作一条单向边，如果存在一个环，且环上没有任何危险标记（即病毒代码段末尾一位的结点专门作的编号），此时 AC自动机 能一直在环上匹配，并且永远也不会得到为模式串的一个子串，就像程序中的死循环一样。这个找环我们可以通过 dfs 来实现。

- 1 . 我们需要建立两个布尔数组，其中一个布尔数组记录每个节点在当前 dfs 走的路径上有没有被选中，另一个布尔数组记录每个节点历史上有没有被访问过。如果当前路径形成回路，就找到环了，应该还是比较好实现的。

- 2 . 避免危险标记，也就是说如果下一个结点拥有危险标记，就不走那个结点。

- 3 . 在构造失配指针时，一个很明显的优化是：如果一个结点拥有了失配指针，它指向的结点如果有危险标记，自己必然也危险，因为它到根结点形成的串是自己到根节点的后缀。

std

```C++
#include <bits/stdc++.h>
#include <queue>
#define rep(l, r, i) for (int i = l, END##i = r; i <= END##i; ++i)
#define per(r, l, i) for (int i = r, END##i = l; i >= END##i; --i)
using namespace std;
#define int long long
#define pii pair<int, int>

#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)

#define rd read()
inline int read() {
  int xx = 0, ff = 1;
  char tr = getchar();
  while (tr < '0' || tr > '9') {
    if (tr == '-')
      ff = -1;
    tr = getchar();
  }
  while (tr >= '0' && tr <= '9')
    xx = xx * 10 + (tr - '0'), tr = getchar();
  return xx * ff;
}
inline void write(int out) {
  if (out < 0)
    putchar('-'), out = -out;
  if (out > 9)
    write(out / 10);
  putchar(out % 10 + '0');
}

#define db double
#define rtn return

const int N = 2e6 + 5;
const int M = 3e7 + 5;
int MOD = 1e9 + 7;
const int INF = 1e12;

queue<int> Q;


bool v[30001];
bool f[30001];
char c[30001];
int n;
struct Node {
  int t[2], f;
  bool c;
};
Node tr[30001];
int S = 0;

//ac自动机
inline void insert(char c[], int l) {
  int x = 0;
  for (int i = 0; i < l; i++)
    if (tr[x].t[c[i] - 48] == 0)
      tr[x].t[c[i] - 48] = ++S, x = S;
    else
      x = tr[x].t[c[i] - 48];
  tr[x].c = 1;
}
inline void getFail() {
  if (tr[0].t[0] > 0)
    Q.push(tr[0].t[0]);
  if (tr[0].t[1] > 0)
    Q.push(tr[0].t[1]);
  while (!Q.empty()) {
    int x = Q.front();
    Q.pop();
    for (int i = 0; i <= 1; i++)
      if (tr[x].t[i] > 0) {
        Q.push(tr[x].t[i]);
        int td = tr[x].f;
        while (td > 0 && tr[td].t[i] <= 0)
          td = tr[td].f;
        if (tr[td].t[i] <= 0)
          tr[tr[x].t[i]].f = 0;
        else {
          tr[tr[x].t[i]].f = tr[td].t[i];
          if (tr[tr[td].t[i]].c)
            tr[tr[x].t[i]].c = 1;
        }
      } else
        tr[x].t[i] = tr[tr[x].f].t[i];
  }
}


void dfs(int d) {
  v[d] = 1;
  for (int i = 0; i <= 1; i++)
    if (v[tr[d].t[i]]) {
      printf("TAK");
      exit(0);
    } else if (!tr[tr[d].t[i]].c && !f[tr[d].t[i]]) {

      f[tr[d].t[i]] = 1;
      dfs(tr[d].t[i]);
    }
  v[d] = false;
}

signed main() {
  n = rd;
  for (int i = 1; i <= n; i++)
    scanf("%s", c), insert(c, strlen(c));
  getFail();
  dfs(0);
  printf("NIE");
  return 0;
}

//在ac自动机上尽可能找环
```

### 输入格式

第一行包括一个整数 $n$，表示病毒代码段的数目。

以下的 $n$ 行每一行都包括一个非空的 $01$ 字符串，代表一个病毒代码段。

### 输出格式

如果存在无限长的安全代码，输出 `TAK`，否则输出 `NIE`。

### 样例 #1

#### 样例输入 #1

```C++
3
01 
11 
00000
```

#### 样例输出 #1

```C++
NIE
```

### 提示

$1 \leq n \leq 2000$，所有病毒代码段的总长度不超过 $3 \times 10^4$。

## [USACO12JAN] Video Game G

题型：构造最多匹配

### 题目描述

Bessie 在玩一款游戏，该游戏只有三个技能键 `A`，`B`，`C` 可用，但这些键可用形成 $n$ 种特定的组合技。第 $i$ 个组合技用一个字符串 $s_i$ 表示。

Bessie 会输入一个长度为 $k$ 的字符串 $t$，而一个组合技每在 $t$ 中出现一次，Bessie 就会获得一分。$s_i$ 在 $t$ 中出现一次指的是 $s_i$ 是 $t$ 从某个位置起的连续子串。如果 $s_i$ 从 $t$ 的多个位置起都是连续子串，那么算作 $s_i$ 出现了多次。

若 Bessie 输入了恰好 $k$ 个字符，则她最多能获得多少分？

### 思路：ac自动机+dp

##### 1.设计状态

dp[i][j]表示长度为i，当前在trie上的j位置时的最大得分

其实AC自动机的题感觉状态都是这样，至少我遇到的都是这样，~~可能是我太菜了~~

$dp_{i,tr[j][k]}=max(dp_{i−1,j}+cnt_{tr[j][k]})$

### 输入格式

输入的第一行是两个整数，分别表示组合技个数 $n$ 和 Bessie 输入的字符数 $k$。

接下来 $n$ 行，每行一个字符串 $s_i$，表示一种组合技。

### 输出格式

输出一行一个整数表示答案。

### 样例 #1

#### 样例输入 #1

```C++
3 7 
ABA 
CB 
ABACB
```

#### 样例输出 #1

```C++
4
```

### 提示

##### 样例 1 解释

Bessie 如果输入 `ABACBCB`，则 `ABA` 出现了一次，`ABACB` 出现了一次，`CB` 出现了两次，共得到 $4$ 分。可以证明这是最优的输入。

##### 数据规模与约定

对于全部的测试点，保证：

- $1 \leq n \leq 20$，$1 \leq k \leq 10^3$。

- $1 \leq |s_i| \leq 15$。其中 $|s_i|$ 表示字符串 $s_i$ 的长度。

- $s$ 中只含大写字母 `A`，`B`，`C`。

## [TJOI2010] 阅读理解

### 题目描述

英语老师留了 $N$ 篇阅读理解作业，但是每篇英文短文都有很多生词需要查字典，为了节约时间，现在要做个统计，算一算某些生词都在哪几篇短文中出现过。

### 思路

对于这种明确的单词划分的匹配（或者是是检查存在性）应该怎么做呢？**Trie树**！（注意不是Tire啊）

【创新思路】或者我们靠map记录每一个单词存在的位置/个数即可。

---

下面给出map的代码

```C++
// STL匹配

#include <bits/stdc++.h>
#define rep(l, tagr, i) for (int i = l, END##i = tagr; i <= END##i; ++i)
#define per(tagr, l, i) for (int i = tagr, END##i = l; i >= END##i; --i)
using namespace std;
#define pb push_back
#define mpy make_pair
#define int long long
#define pii pair<int, int>
#define ps b
#define pf a

#define X(j) i[j]
#define Y(j) (dp[j] + (i[j] + L) * (i[j] + L))
#define lc tr[x][0]
#define rc tr[x][1]
#define rd read()
int read() {
  int xx = 0, ff = 1;
  char op = getchar();
  while (op < '0' || op > '9') {
    if (op == '-')
      ff = -1;
    op = getchar();
  }
  while (op >= '0' && op <= '9')
    xx = xx * 10 + (op - '0'), op = getchar();
  return xx * ff;
}
void write(int out) {
  if (out < 0)
    putchar('-'), out = -out;
  if (out > 9)
    write(out / 10);
  putchar(out % 10 + '0');
}

const int N = 1e5 + 10;
int n, m, k, cnt[N];
string s;
map<string, vector<int>> a;
signed main() {
  n = rd;
  ;
  for (int i = 1; i <= n; i++) {
    int k = rd;
    for (int j = 1; j <= k; j++) {
      cin >> s;
      a[s].push_back(i);
    }
  }
  m = rd;
  for (int i = 1; i <= m; i++) {
    cin >> s;
    memset(cnt, 0, sizeof(cnt)); // cnt去重
    for (int j = 0; j < a[s].size(); j++)
      if (!cnt[a[s][j]]) {
        cout << a[s][j] << " ";
        cnt[a[s][j]]++;
      }
    puts("");
  }
  return 0;
}

```

下面给出Trie的代码

```C++
//自己写！！
```

### 输入格式

第一行为整数 $N$ ，表示短文篇数，其中每篇短文只含空格和小写字母。

按下来的 $N$ 行，每行描述一篇短文。每行的开头是一个整数 $L$ ，表示这篇短文由 $L$ 个单词组成。接下来是 $L$ 个单词，单词之间用一个空格分隔。

然后为一个整数 $M$ ，表示要做几次询问。后面有 $M$ 行，每行表示一个要统计的生词。

### 输出格式

对于每个生词输出一行，统计其在哪几篇短文中出现过，并按从小到大输出短文的序号，序号不应有重复，序号之间用一个空格隔开（注意第一个序号的前面和最后一个序号的后面不应有空格）。如果该单词一直没出现过，则输出一个空行。

### 样例 #1

#### 样例输入 #1

```C++
3
9 you are a good boy ha ha o yeah
13 o my god you like bleach naruto one piece and so do i
11 but i do not think you will get all the points
5
you
i
o
all
naruto
```

#### 样例输出 #1

```C++
1 2 3
2 3
1 2
3
2
```

### 提示

对于 $30\%$ 的数据， $1\le M\le 10^3$ 。

对于 $100\%$ 的数据，$1\le M\le 10^4$，$1\le N\le 10^3$ 。

每篇短文长度（含相邻单词之间的空格）$\le 5\times 10^3$ 字符，每个单词长度 $\le 20$ 字符。

每个测试点时限 $2$ 秒。

感谢@钟梓俊添加的一组数据。

## 单词背诵

### 题目描述

灵梦有 $n$ 个单词想要背，但她想通过一篇文章中的一段来记住这些单词。

文章由 $m$ 个单词构成，她想在文章中找出连续的一段，其中包含最多的她想要背的单词（重复的只算一个）。并且在背诵的单词量尽量多的情况下，还要使选出的文章段落尽量短，这样她就可以用尽量短的时间学习尽可能多的单词了。

---

```C++

// 字符串哈希匹配

#include <bits/stdc++.h>
#define rep(l, tagr, i) for (int i = l, END##i = tagr; i <= END##i; ++i)
#define per(tagr, l, i) for (int i = tagr, END##i = l; i >= END##i; --i)
using namespace std;
#define pb push_back
#define mpy make_pair
#define int long long
#define pii pair<int, int>
#define ps b
#define pf a

#define X(j) i[j]
#define Y(j) (dp[j] + (i[j] + L) * (i[j] + L))
#define lc tr[x][0]
#define rc tr[x][1]
#define rd read()
int read() {
  int xx = 0, ff = 1;
  char op = getchar();
  while (op < '0' || op > '9') {
    if (op == '-')
      ff = -1;
    op = getchar();
  }
  while (op >= '0' && op <= '9')
    xx = xx * 10 + (op - '0'), op = getchar();
  return xx * ff;
}
void write(int out) {
  if (out < 0)
    putchar('-'), out = -out;
  if (out > 9)
    write(out / 10);
  putchar(out % 10 + '0');
}

const int N = 1e5 + 56;
map<string, int> sum;
map<string, bool> f;
int ans1, ans2, n, m, l;
string s[N], s1;
signed main() {
  n = rd;
  for (int i = 1; i <= n; i++)
    cin >> s1, f[s1] = 1;
  m = rd;
  l = 1;
  for (int i = 1; i <= m; i++) {
    cin >> s[i];
    if (f[s[i]])
      sum[s[i]]++; // 记录单词
    if (sum[s[i]] == 1)
      ans1++, ans2 = i - l + 1;
    while (l <= i) {
      if (!f[s[l]]) {
        l++;
        continue;
      }
      if (sum[s[l]] >= 2) {
        sum[s[l]]--, l++;
        continue;
      }
      break;
    }
    ans2 = min(ans2, i - l + 1);
  }
  cout << ans1 << endl << ans2 << endl;
  return 0;
}

```

### 输入格式

第 $1$ 行一个数 $n$，接下来 $n$ 行每行是一个长度不超过 $10$ 的字符串，表示一个要背的单词。

接着是一个数 $m$，然后是 $m$ 行长度不超过 $10$ 的字符串，每个表示文章中的一个单词。

### 输出格式

输出文件共 $2$ 行。第 $1$ 行为文章中最多包含的要背的单词数，第 $2$ 行表示在文章中包含最多要背单词的最短的连续段的长度。

### 样例 #1

#### 样例输入 #1

```C++
3
hot
dog
milk
5
hot
dog
dog
milk
hot
```

#### 样例输出 #1

```C++
3
3
```

### 提示

#### 数据规模与约定

- 对于 $30\%$ 的数据，$n \le 50$，$m \le 500$；

- 对于 $60\%$ 的数据，$n \le 300$，$m \le 5000$；

- 对于 $100\%$ 的数据，$n \le 1000$，$m \le 10^5$。

## [USACO09OCT] Barn Echoes G

极其简单，没有使用哈希算法。

### 题目描述

The cows enjoy mooing at the barn because their moos echo back, although sometimes not completely. Bessie, ever the excellent

secretary, has been recording the exact wording of the moo as it goes out and returns. She is curious as to just how much overlap there is.

Given two lines of input (letters from the set a..z, total length in the range 1..80), each of which has the wording of a moo on it, determine the greatest number of characters of overlap between one string and the other. A string is an overlap between two other strings if it is a prefix of one string and a suffix of the other string.

By way of example, consider two moos:

moyooyoxyzooo

yzoooqyasdfljkamo

The last part of the first string overlaps 'yzooo' with the first part of the second string. The last part of the second string

overlaps 'mo' with the first part of the first string. The largest overlap is 'yzooo' whose length is 5.

POINTS: 50

奶牛们非常享受在牛栏中哞叫，因为她们可以听到她们哞声的回音。虽然有时候并不能完全听到完整的回音。Bessie曾经是一个出色的秘书，所以她精确地纪录了所有的哞叫声及其回声。她很好奇到底两个声音的重复部份有多长。

输入两个字符串（长度为1到80个字母），表示两个哞叫声。你要确定最长的重复部份的长度。两个字符串的重复部份指的是同时是一个字符串的前缀和另一个字符串的后缀的字符串。

我们通过一个例子来理解题目。考虑下面的两个哞声：

moyooyoxyzooo

yzoooqyasdfljkamo

第一个串的最后的部份"yzooo"跟第二个串的第一部份重复。第二个串的最后的部份"mo"跟第一个串的第一部份重复。所以"yzooo"跟"mo"都是这2个串的重复部份。其中，"yzooo"比较长，所以最长的重复部份的长度就是5。

---

```C++
const int N = 5e4 + 5;
const int INF = 1e9;
signed main() {
  int i, j;
  string a, b;
  cin >> a >> b;
  int n = min(a.size(), b.size());
  for (i = n; i >= 1; i--)
    if (a.substr(0, i) == b.substr(b.size() - i, i))
      break;
  for (j = n; j >= 1; j--)
    if (b.substr(0, j) == a.substr(a.size() - j, j))
      break;
  cout << max(i, j);
  return 0;
}

```

### 输入格式

- Lines 1..2: Each line has the text of a moo or its echo

### 输出格式

- Line 1: A single line with a single integer that is the length of the longest overlap between the front of one string and end of the other.

### 样例 #1

#### 样例输入 #1

```C++
abcxxxxabcxabcd 
abcdxabcxxxxabcx
```

#### 样例输出 #1

```C++
11
```

### 提示

'abcxxxxabcx' is a prefix of the first string and a suffix of the second string.

## [NOI2015] 程序自动分析

### 题目描述

在实现程序自动分析的过程中，常常需要判定一些约束条件是否能被同时满足。

考虑一个约束满足问题的简化版本：假设 $x_1,x_2,x_3,\cdots$ 代表程序中出现的变量，给定 $n$ 个形如 $x_i=x_j$ 或 $x_i\neq x_j$ 的变量相等/不等的约束条件，请判定是否可以分别为每一个变量赋予恰当的值，使得上述所有约束条件同时被满足。例如，一个问题中的约束条件为：$x_1=x_2,x_2=x_3,x_3=x_4,x_4\neq x_1$，这些约束条件显然是不可能同时被满足的，因此这个问题应判定为不可被满足。

现在给出一些约束满足问题，请分别对它们进行判定。

### 输入格式

输入的第一行包含一个正整数 $t$，表示需要判定的问题个数。注意这些问题之间是相互独立的。

对于每个问题，包含若干行：

第一行包含一个正整数 $n$，表示该问题中需要被满足的约束条件个数。接下来 $n$ 行，每行包括三个整数 $i,j,e$，描述一个相等/不等的约束条件，相邻整数之间用单个空格隔开。若 $e=1$，则该约束条件为 $x_i=x_j$。若$e=0$，则该约束条件为 $x_i\neq x_j$。

### 输出格式

输出包括 $t$ 行。

输出文件的第 $k$ 行输出一个字符串 `YES` 或者 `NO`（字母全部大写），`YES` 表示输入中的第 $k$ 个问题判定为可以被满足，`NO` 表示不可被满足。

---

```C++
// 维护边权（维护生成树）的LCT实现

#include <bits/stdc++.h>
#define rep(l, tagr, i) for (int i = l, END##i = tagr; i <= END##i; ++i)
#define per(tagr, l, i) for (int i = tagr, END##i = l; i >= END##i; --i)
using namespace std;
#define pb push_back
#define mpy make_pair
#define int long long
#define pii pair<int, int>
#define ps b
#define pf a

#define X(j) i[j]
#define Y(j) (dp[j] + (i[j] + L) * (i[j] + L))
#define lc tr[x][0]
#define rc tr[x][1]
#define rd read()
int read() {
  int xx = 0, ff = 1;
  char op = getchar();
  while (op < '0' || op > '9') {
    if (op == '-')
      ff = -1;
    op = getchar();
  }
  while (op >= '0' && op <= '9')
    xx = xx * 10 + (op - '0'), op = getchar();
  return xx * ff;
}
void write(int out) {
  if (out < 0)
    putchar('-'), out = -out;
  if (out > 9)
    write(out / 10);
  putchar(out % 10 + '0');
}
#define N 1000010
int t, n, f[N], book[N * 3];
struct node {
  int x, y, e;
} a[1000001];
bool cmp(node a, node b) { return a.e > b.e; } // 排 序将e==1的放在前面
inline void first(int kkk) {
  for (int i = 1; i <= kkk; i++)
    f[i] = i;
} // 初 始 化
int get(int x) {
  if (x == f[x])
    return x;
  return f[x] = get(f[x]);
}
signed main() {
  scanf("%d", &t);
  while (t--) {
    int tot = -1;
    memset(book, 0, sizeof(book));
    memset(a, 0, sizeof(a));
    memset(f, 0, sizeof(f));
    int flag = 1;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
      scanf("%d %d %d", &a[i].x, &a[i].y, &a[i].e);
      book[++tot] = a[i].x;
      book[++tot] = a[i].y;
    }
    sort(book, book + tot);                    // 排序
    int reu = unique(book, book + tot) - book; // 去重
    for (int i = 1; i <= n; ++i) {
      a[i].x = lower_bound(book, book + reu, a[i].x) - book;
      a[i].y = lower_bound(book, book + reu, a[i].y) - book;
    }
    first(reu);                  // 初始化
    sort(a + 1, a + n + 1, cmp); // 按e排序
    for (int i = 1; i <= n; i++) {
      int r1 = get(a[i].x);
      int r2 = get(a[i].y);
      if (a[i].e) {
        f[r1] = r2; // 就是我们的merge操作
      } else if (r1 == r2) {
        printf("NO\n");
        flag = 0; // 如果不满足条件，标记为否
        break;
      }
    }
    if (flag)
      printf("YES\n"); // 都满足条件了
  }
  return 0;
}

```

### 样例 #1

#### 样例输入 #1

```C++
2
2
1 2 1
1 2 0
2
1 2 1
2 1 1
```

#### 样例输出 #1

```C++
NO
YES
```

### 样例 #2

#### 样例输入 #2

```C++
2
3
1 2 1
2 3 1
3 1 1
4
1 2 1
2 3 1
3 4 1
1 4 0
```

#### 样例输出 #2

```C++
YES
NO
```

### 提示

【样例解释1】

在第一个问题中，约束条件为：$x_1=x_2,x_1\neq x_2$。这两个约束条件互相矛盾，因此不可被同时满足。

在第二个问题中，约束条件为：$x_1=x_2,x_1 = x_2$。这两个约束条件是等价的，可以被同时满足。

【样例说明2】

在第一个问题中，约束条件有三个：$x_1=x_2,x_2= x_3,x_3=x_1$。只需赋值使得 $x_1=x_2=x_3$，即可同时满足所有的约束条件。

在第二个问题中，约束条件有四个：$x_1=x_2,x_2= x_3,x_3=x_4,x_4\neq x_1$。由前三个约束条件可以推出 $x_1=x_2=x_3=x_4$，然而最后一个约束条件却要求 $x_1\neq x_4$，因此不可被满足。

【数据范围】

所有测试数据的范围和特点如下表所示：

