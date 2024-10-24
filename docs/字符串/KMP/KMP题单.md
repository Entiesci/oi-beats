# KMP板子的灵活运用

## [POI2006] OKR-Periods of Words

### 题面翻译

对于一个仅含小写字母的字符串 $a$，$p$ 为 $a$ 的前缀且 $p\ne a$，那么我们称 $p$ 为 $a$ 的 proper 前缀。

规定字符串 $Q$ 表示 $a$ 的周期，当且仅当 $Q$ 是 $a$ 的 proper 前缀且 $a$ 是 $Q+Q$ 的前缀。若这样的字符串不存在，则 $a$ 的周期为空串。

例如 `ab` 是 `abab` 的一个周期，因为 `ab` 是 `abab` 的 proper 前缀，且 `abab` 是 `ab+ab` 的前缀。

求给定字符串所有前缀的最大周期长度之和。

---

### 思路

---

std

```C++
/*////////ACACACACACACAC///////////
           kmp的灵活运用/实质理解
/*/
///////ACACACACACACAC///////////

// 
#include <bits/stdc++.h>

//
#define int long long
#define ull unsigned long long
#define db double
#define endl '\n'
#define err(fmt, ...)                                                          \
###__VA_ARGS__)
// /*
#define pr pair<double, int>
#define pf first
#define ps second
#define pb push_back
// */

using namespace std;
// 
const int N = 1e6 + 5;
const int M = 1e3;
const int MOD = 1e9 + 7;
const int MMOD = 903250223;
const int INF = 1e9;
const db eps = 1e-9;

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
//

int len, nxt[N];
char s[N];
int ans;
signed main() {
  len = rd;
  cin >> (s + 1);

  // kmp
  for (int i = 2, j = 0; i <= len; i++) {
    while (j && s[i] != s[j + 1])
      j = nxt[j];
    if (s[i] == s[j + 1])
      j++;
    nxt[i] = j;
  }
  for (int i = 2, j = 2; i <= len; i++, j = i) {
    while (nxt[j])
      j = nxt[j];
    if (nxt[i])
      nxt[i] = j;
    ans += i - j;
  }
  cout << ans << endl;
  return 0;
}

```

### 题目描述

A string is a finite sequence of lower-case (non-capital) letters of the English alphabet. Particularly, it may be an empty sequence, i.e. a sequence of 0 letters. By A=BC we denotes that A is a string obtained by concatenation (joining by writing one immediately after another, i.e. without any space, etc.) of the strings B and C (in this order). A string P is a prefix of the string !, if there is a string B, that A=PB. In other words, prefixes of A are the initial fragments of A. In addition, if P!=A and P is not an empty string, we say, that P is a proper prefix of A.

A string Q is a period of Q, if Q is a proper prefix of A and A is a prefix (not necessarily a proper one) of the string QQ. For example, the strings abab and ababab are both periods of the string abababa. The maximum period of a string A is the longest of its periods or the empty string, if A doesn't have any period. For example, the maximum period of ababab is abab. The maximum period of abc is the empty string.

Task Write a programme that:

reads from the standard input the string's length and the string itself,calculates the sum of lengths of maximum periods of all its prefixes,writes the result to the standard output.

### 输入格式

In the first line of the standard input there is one integer $k$ ($1\le k\le 1\ 000\ 000$) - the length of the string. In the following line a sequence of exactly $k$ lower-case letters of the English alphabet is written - the string.

### 输出格式

In the first and only line of the standard output your programme should write an integer - the sum of lengths of maximum periods of all prefixes of the string given in the input.

### 样例 #1

#### 样例输入 #1

```C++
8
babababa
```

#### 样例输出 #1

```C++
24
```

## [USACO15FEB] Censoring S

### 题面翻译

Farmer John为他的奶牛们订阅了Good Hooveskeeping杂志，因此他们在谷仓等待挤奶期间，可以有足够的文章可供阅读。不幸的是，最新一期的文章包含一篇关于如何烹制完美牛排的不恰当的文章，FJ不愿让他的奶牛们看到这些内容。

FJ已经根据杂志的所有文字，创建了一个字符串  $S$  ( $S$  的长度保证不超过  $10^6$  )，他想删除其中的子串  $T$  ,他将删去  $S$ 中第一次出现的子串  $T$  ，然后不断重复这一过程，直到  $S$  中不存在子串  $T$ 。

注意：每次删除一个子串后，可能会出现一个新的子串  $T$ （说白了就是删除之后，两端的字符串有可能会拼接出来一个新的子串  $T$ ）。

输入格式：第一行是字符串  $S$  ，第二行输入字符串  $T$ ，保证  $S$  的长度大于等于  $T$  的长度， $S$  和  $T$  都只由小写字母组成。

输出格式：输出经过处理后的字符串，保证处理后的字符串不会为空串。

Translated by @StudyingFather

### 思路

在kmp匹配中维护一个栈，然后根据nxt数组不断去跳即可。

---

std

```C++
/*////////ACACACACACACAC///////////
           kmp的灵活运用/实质理解
/*/
///////ACACACACACACAC///////////

//
#include <bits/stdc++.h>

//
#define int long long
#define ull unsigned long long
#define db double
#define endl '\n'
#define err(fmt, ...)                                                          \
###__VA_ARGS__)
// /*
#define pr pair<double, int>
#define pf first
#define ps second
#define pb push_back
// */

using namespace std;
//
const int N = 1e6 + 5;
const int M = 1e3;
const int MOD = 1e9 + 7;
const int MMOD = 903250223;
const int INF = 1e9;
const db eps = 1e-9;

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
//

int la, lb, res;
char a[N], b[N];
int p[N], f[N];
int stk[N], top;
signed main() {
  cin >> a + 1;
  cin >> b + 1;
  la = strlen(a + 1);
  lb = strlen(b + 1);

  // kmp
  for (int i = 2, j = 0; i <= lb; i++) {
    while (j && b[i] != b[j + 1])
      j = p[j];
    if (b[i] == b[j + 1])
      j++;
    p[i] = j;
  }
  for (int i = 1, j = 0; i <= la; i++) {
    while (j && a[i] != b[j + 1])
      j = p[j];
    if (a[i] == b[j + 1])
      j++;
    f[i] = j;
    stk[++top] = i;
    if (j == lb)
      top -= lb, j = f[stk[top]];
  }
  for (int i = 1; i <= top; i++)
    putchar(a[stk[i]]);
  return 0;
}

```

### 题目描述

Farmer John has purchased a subscription to Good Hooveskeeping magazine for his cows, so they have plenty of material to read while waiting around in the barn during milking sessions. Unfortunately, the latest issue contains a rather inappropriate article on how to cook the perfect steak, which FJ would rather his cows not see (clearly, the magazine is in need of better editorial oversight).

FJ has taken all of the text from the magazine to create the string $S$ of length at most 10^6 characters. From this, he would like to remove occurrences of a substring $T$ to censor the inappropriate content. To do this, Farmer John finds the ***first*** occurrence of $T$ in $S$ and deletes it. He then repeats the process again, deleting the first occurrence of $T$ again, continuing until there are no more occurrences of $T$ in $S$. Note that the deletion of one occurrence might create a new occurrence of $T$ that didn't exist before.

Please help FJ determine the final contents of $S$ after censoring is complete.

### 输入格式

The first line will contain $S$. The second line will contain $T$. The length of $T$ will be at most that of $S$, and all characters of $S$ and $T$ will be lower-case alphabet characters (in the range a..z).

### 输出格式

The string $S$ after all deletions are complete. It is guaranteed that $S$ will not become empty during the deletion process.

### 样例 #1

#### 样例输入 #1

```C++
whatthemomooofun
moo
```

#### 样例输出 #1

```C++
whatthefun
```

## Om Nom and Necklace

题面翻译

已知长度为 $n$ 的字符串 $s$，对于 $s$ 的每一个前缀子串（即对于每一个 $i$，$s$ 中从第 $1$ 个字符到第 $i$ 个的所有字符组成的字符串，$1\leq i\leq n$），如果满足 $\texttt{ABABA...BA}$ 的形式（$A$、$B$ 可以为空，也可以是一个字符串，$A$ 有 $k+1$ 个，$B$ 有 $k$ 个），则请输出 $1$；否则输出 $0$，注意：$n$ 和 $k$ 给定。

---

首先将 AB视为C，那么就是判定字符串是否满足形式为CCC...CA，其中A是C的一个前缀。

判定CCC...C

使用kmp的循环节的性质，有最小循环节长度为n-nxt_n。那么如果是CC...CA，n-nxt_n求出来的是什么呢？因为A是C的前缀，所以我们也可以得到C的长度。接下来就是一系列的判定了。

```C++
// Problem: Om Nom and Necklace
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF526D
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// Challenger: Erica N
// ----
#include<bits/stdc++.h>

using namespace std;
#define rd read()
#define ull unsigned long long
#define int long long 
#define itn int
#define ps second 
#define pf first

int  read(){
	int x;
	cin>>x;
	return x;
}
#define zerol = 1
#ifdef zerol
#define cdbg(x...) do { cerr << #x << " -> "; err(x); } while (0)
void err() {
	cerr << endl;
}
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) {
	for (auto v: a) cerr << v << ' ';
	err(x...);
}
template<typename T, typename... A>
void err(T a, A... x) {
	cerr << a << ' ';
	err(x...);
}
#else
#define dbg(...)
#endif
const int N=3e5+5;
const ull P=137;
const int INF=1e9+7;
/*

策略


*/
int nxt[N];
string s;
int n,K;

void getNxt(){
	for(int i=2;i<=n;i++){
		int j=nxt[i-1];
		while(s[j+1]!=s[i]&&j)j=nxt[j];
		if(s[j+1]==s[i])j++;
		nxt[i]=j;
	}
}

signed main(){
	n=rd,K=rd;
	cin>>s;
	s=" "+s;
	getNxt();
	
	
	for(int i=1;i<=n;i++){
		int len=i-nxt[i];
		int d=i/len;
		if(i%len){
			if(d/K-d%K>0)cout<<1;
			else cout<<0;
		}else{
			if(d/K-d%K>=0)cout<<1;
			else cout<<0;
		}
		
	}
}


```

