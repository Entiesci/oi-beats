# 深搜

## 例题 #1 深搜回溯 八皇后

题目描述

一个如下的 $6 \times 6$ 的跳棋棋盘，有六个棋子被放置在棋盘上，使得每行、每列有且只有一个，每条对角线（包括两条主对角线的所有平行线）上至多有一个棋子。

![60.png](深搜+dfs/60.png)

上面的布局可以用序列 $2\ 4\ 6\ 1\ 3\ 5$ 来描述，第 $i$ 个数字表示在第 $i$ 行的相应位置有一个棋子，如下：

行号 $1\ 2\ 3\ 4\ 5\ 6$

列号 $2\ 4\ 6\ 1\ 3\ 5$

这只是棋子放置的一个解。请编一个程序找出所有棋子放置的解。
并把它们以上面的序列方法输出，解按字典顺序排列。
请输出前 $3$ 个解。最后一行是解的总个数。

输入格式

一行一个正整数 $n$，表示棋盘是 $n \times n$ 大小的。

输出格式

前三行为前三个解，每个解的两个数字之间用一个空格隔开。第四行只有一个数字，表示解的总数。

【数据范围】
对于 $100\%$ 的数据，$6 \le n \le 13$。

题目翻译来自NOCOW。

USACO Training Section 1.5

---

思路

**深搜递归**

对于一条从右上到左下的对角线，其上的棋子坐标应满足`x+y`为一**定值**；

对于一条从左上到右下的对角线，其上的棋子坐标应满足`x-y`为一**定值**，为了避免**负数**的产生，代码中用`x-y+n`来储存数字，具体效果读者可以自行研究。

因此,我们就可以做到使用数组快速存储与判定`对角线/行/列`是否存在别的皇后
因为我们是**逐行搜索递归**的,不需要存储该行是否有别的皇后

`chk[0]`储存了棋子的列数，每一次进行`ans[l]=i`，使`chk[0][i]`标记为已使用；

`chk[1]`和`chk[2]`储存对角线上的棋子分布情况：

代码

```C++
#include<bits/stdc++.h>

using namespace std;
int ans[14],chk[3][28],cnt,n;
void go(int l){
	if(l>n){	//找到了一种满足条件的八皇后排列!
		cnt++;
		if(cnt<=3){	//特判是第几个,输出
			for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
			cout<<endl;
		}
		return;
	}
	for(int i=1;i<=n;i++){
		if(!(chk[0][i])&&!(chk[1][l+i])&&!(chk[2][l-i+n])){	//在该行找到了一个可以放置皇后的地方,向下递归
			chk[0][i]=1;chk[1][l+i]=1;chk[2][l-i+n]=1;
			ans[l]=i;
			go(l+1);
			chk[0][i]=chk[1][l+i]=chk[2][l-i+n]=0;
		}
		//如果该行没有找到任何一个可以放到地方,则无功而返!
	}
	
}
int main() {
	cin>>n;
	go(1);
	cout<<cnt;
	return 0;
}
```

摆脱传统思想!接受递归思想!

## 练习 #1 类数位dp Lucky Numbers

Petya 非常喜爱幸运数字。大家都知道如果一个十进制正整数的各个数位中不包含除4或7以外的数，那么它就是幸运的。例如，47,774,4是幸运的，而5,17,467则不是。

当一个十进制幸运数字中含有4和7的数量相同时，这个幸运数字就是超级幸运的。例如，47,7744,474477是超级幸运的，而4,744,467则不是。

一天Petya偶然发现了一个正整数n。请帮他找出不小于n的最小的超级幸运数字。

The only line contains a positive integer $n$ ( $1<=n<=10^{100000}$ ). This number doesn't have leading zeroes.

题意

给出一个 $≤10^5$ 位的数字 $n$，求不小于它的幸运数字。

幸运数字的定义是数字中只有 $4,7$ 且 $4$ 的数量与 $7$ 相同。

思路

结合题意，很显然当 $n$ 的长度 $len$ 为奇数时，我们只能找到长度为 $len+1$ 的最小的幸运数字作为答案。

当 $len$ 为偶数时，我们只好搜索下去了。

我们用 `dfs(x,cnt1,cnt0,up)` 来表示当前要填第 $x$ 个数字，已经用了 $cnt1$ 个 $7$，$cnt0$ 个 $4$。因为我们还需要考虑到进位的问题，所以我们需要用 $up$ 来传递一下。

当我们枚举到一个数位 $i$ 时，我们能放 $4$ 的就放 $4$，否则放 $7$，或者判不成立：

- 如果 $n_i<4$，则该位填 $4$，$up$ 置 $1$。

- 如果 $n_i=4$，则该位填 $4$。

- 如果 $4<n_i<7$，则该位填 $7$，$up$ 置 1。

- 如果 $n_i=7$，则该位填 $7$。

- 如果 $n_i>7$，如果 $up=1$ 则置 $4$，否则 `return`。

这是所有的情况了。代码中我们可以合并一些情况。如果我们通过 dfs 没办法找到答案（例如数字 $9999$），那么我们只能按奇数 $len$ 的情况来输出了，输出长度为 $len+2$ 的最小幸运数字。

代码

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . FancyKnowledge .
       . Prove Yourself .
/*////////ACACACACACACAC///////////
#pragma GCC optimize(3)
//
#include<bits/stdc++.h>

//
//#define int long long
#define ull unsigned long long
#define db double
#define endl '\n'
#define err(fmt, ...) fprintf(stderr, "[%d] : " fmt "\n", __LINE__, ##__VA_ARGS__)
///*
#define pr pair<double,int>
#define pf first
#define ps second
#define pb push_back


using namespace std;
//
const int N=1e6+5;
const int M=1e3;
const int MOD=1e9+7;
const int MMOD=903250223;
const int INF=1e9;
//const int IINF=1e18;
const db eps=1e-9;
//
int m,b,q,op,idx,len,ans[N],id[N];

string n;

bool dfs(int u, int cnt0, int cnt1,int up) {
	if (cnt0 > len /2 || cnt1 > len /2) return 0;
	if (u == len) {
		for (int i=0;i<len;i++)
			cout<<ans[i];
		exit(0);
	}
	n[u]-='0';
	if(n[u]<=4||up){//能用4的就用4
		ans[u]=4;
		if(dfs(u+1,cnt0+1,cnt1,up||(n[u]<4))){
			return 1;
		}
	}
	if(n[u]<=7||up){
		ans[u]=7;
		if(dfs(u+1,cnt0,cnt1+1,up||(n[u]<7))){
			return 1;
		}
	}
	return 0;
}
void lucnum(int n){
	for(int i=1;i<=n/2;i++)cout<<4;
	for(int i=1;i<=n/2;i++)cout<<7;
}
signed main(){
//	cin>>n>>m;
	cin>>n;
	len=n.size();
	
	if(len%2){
		lucnum(len+1);
		return 0;
	}
//	cerr<<"len="<<len<<endl;
	dfs(0,0,0,0);
	lucnum(len+2);
	
}
//

```

## 练习 #2 非步进广搜 Arthur and Walls

给出一个n*m的矩阵，里面有“*”和“.”两种符号，要求把最少的“*”变成“.”，使得“.”的联通块构成一个矩形。求最少需要变几个“*”。

---

首先有一个贪心策略，即如果一道一个2x2分割中只有一个`*`，那么我们需要修改，否则就统统不需要修改。于是我们找到一个`*`就dfs下去，走联通块，并且对每个`*`判定下是否需要修改。并且只有需要修改时才继续dfs

```C++
/*  Erica N  */
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define int long long
#define ull unsigned long long
#define pii pair<int, int>
#define ps second
#define pf first
#define itn int

#define rd read()
int read(){
    int xx = 0, ff = 1;char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-')ff = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9')xx = xx * 10 + (ch - '0'), ch = getchar();
    return xx * ff;
}

#define cdbg(x...) do { cerr << #x << " -> "; err(x); } while (0)
void err() { cerr << endl; }
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) { for (auto v: a) cerr << v << ' '; err(x...); }
template<typename T, typename... A>
void err(T a, A... x) { cerr << a << ' '; err(x...); }


const int N = 3e3 + 5;
const int INF = 1e18;
const int M = 1e7;
const int MOD = 1e9 + 7;


/*


*/

char s[N][N];
int dx[]={-1,-1,0,1,1,1,0,-1};
int dy[]={0,1,1,1,0,-1,-1,-1};


int ans=0;
int n,m;

bool check(int x,int y){
    if(s[x-1][y]=='.'&&s[x-1][y+1]=='.'&&s[x][y+1]=='.')return 1;
    if(s[x+1][y]=='.'&&s[x+1][y+1]=='.'&&s[x][y+1]=='.')return 1;
    if(s[x][y-1]=='.'&&s[x+1][y-1]=='.'&&s[x+1][y]=='.')return 1;
    if(s[x-1][y-1]=='.'&&s[x-1][y]=='.'&&s[x][y-1]=='.')return 1;
    return 0;
}

void dfs(int x,int y){
    if(x<1||x>n||y<1||y>m||s[x][y]=='.')return ;
    if(!check(x,y))return ;
    // cdbg(x,y);
    s[x][y]='.';
    ans++;

    for(int i=0;i<8;i++){
        dfs(x+dx[i],y+dy[i]);
    }
}


void solve(){
     n=rd,m=rd;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>s[i][j];
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i][j]=='*')dfs(i,j);
        }
    }


    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            putchar(s[i][j]);
        }
        putchar('\n');
    }

    
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);

    int T=1;
    while(T--){
    	solve();
    }
    return 0;
}
```



## meet in the middle

见 [搜索优化算法](https://flowus.cn/612d0b19-3144-49ae-8379-443c86621667)

### 广义meet in the middle（弱化）

生命的含义：42。它可以表示成三个数的立方和：

42=(−80538738812075974)^3+80435758145817515^3+12602123297335631^3.

现在并不要求你找出如此复杂的答案。给定正整数L和x，你只需要找到**任意一组**整数三元组(a,b,c)，满足 −L≤a,b,c≤L且a^3+b^3+c^3=x。

100%的数据满足L≤1000, q,x≤10^4。

---

先枚举所有的a^3+b^3丢进map，对于给定的询问，枚举c，从map中匹配。

要善于利用预处理。

