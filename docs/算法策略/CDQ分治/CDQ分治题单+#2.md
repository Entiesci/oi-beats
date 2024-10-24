# CDQ分治题单

## [CEOI2017] Building Bridges

### 题目描述

有 $n$ 根柱子依次排列，每根柱子都有一个高度。第 $i$ 根柱子的高度为 $h_i$。

现在想要建造若干座桥，如果一座桥架在第 $i$ 根柱子和第 $j$ 根柱子之间，那么需要 $(h_i-h_j)^2$​​ 的代价。

在造桥前，所有用不到的柱子都会被拆除，因为他们会干扰造桥进程。第 $i$ 根柱子被拆除的代价为 $w_i$，注意 $w_i$ 不一定非负，因为可能政府希望拆除某些柱子。

现在政府想要知道，通过桥梁把第 $1$ 根柱子和第 $n$ 根柱子连接的最小代价。注意桥梁不能在端点以外的任何地方相交。

### 输入格式

第一行一个正整数 $n$。

第二行 $n$ 个空格隔开的整数，依次表示 $h_1,h_2,\cdots,h_n$​​。

第三行 $n$ 个空格隔开的整数，依次表示 $w_1,w_2,\cdots,w_n$​​。

### 输出格式

输出一行一个整数表示最小代价，注意最小代价不一定是正数。

### 样例 #1

#### 样例输入 #1

```C++
6
3 8 7 1 6 6
0 -1 9 1 2 0
```

#### 样例输出 #1

```C++
17
```

### 提示

对于 $100\%$ 的数据，有 $2\le n\le 10^5;0\le h_i,\vert w_i\vert\le 10^6$。

## 寒假作业

### 题目描述

他们共有 $n$ 项寒假作业。zzy 给每项寒假作业都定义了一个疲劳值 $a_i$，表示抄这个作业所要花的精力。

zzs 现在想要知道，有多少组连续的寒假作业的疲劳值的平均值不小于 $k$？

简单地说，给定一个长度为 $n$ 的正整数序列 $\{a_i\}$，求出有多少个**连续**子序列的平均值不小于 $k$。

### 思路

非常简单的cdq分治

先把所有数-=k，转化为平均数>=0的区间数量

也就是区间和>=0的区间数量

对于区间[l, r]内部所有区间的贡献，令区间中点为mid，先计算[l, mid]和[mid + 1, r]的所有贡献，然后再计算[l, r]内所有跨过区间中点mid的区间贡献就行

跨过中点的区间一定是$i∈[l,mid]$的一段$[i, mid]$和$j∈[mid+1,r]$的一段$[mid + 1, j]$组成，我们前面求后缀和后面求前缀和把所有上述区间和搞出来，然后分别排序双指针扫一遍就可以统计答案了

有前缀和转化为逆序对的做法，实质其实一样，都是cdq分治

**注意以上是cdq分治的套路！牢记！**

---

```C++
#include<bits/stdc++.h>
#define rep(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define per(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
#define int long long
#define pii pair<int,int>

#define lc(x) (x<<1)
#define rc(x) (x<<1|1)

#define rd read()
inline int read(){
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out){
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}

const int N=1e5+15;
const int INF=1e9+5;
const int MOD=998244353;

int n, k, a[N];
int tmp[N];

int cdq(int l, int r){
	if (l == r) return a[l] >= 0;
	int mid = (l + r) / 2;
	int res = cdq(l, mid) + cdq(mid + 1, r);

	tmp[mid] = a[mid];
	tmp[mid + 1] = a[mid + 1];
	for (int i = mid - 1; i >= l; i--)tmp[i] = tmp[i + 1] + a[i];
	for (int i = mid + 2; i <= r; i++)tmp[i] = tmp[i - 1] + a[i];

	sort(tmp + l, tmp + mid + 1);
	sort(tmp + mid + 1, tmp + r + 1);
	for (int i = l, j = r; i <= mid; i++){
		while (j > mid && tmp[i] + tmp[j] >= 0) j--;
		res += r - j;
	}
	return res;
}

signed main(){
	scanf("%lld%lld", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]), a[i] -= k;
	printf("%lld\n", cdq(1, n));
	return 0;
}

```

### 输入格式

第一行是两个整数，分别表示序列长度 $n$ 和给定的参数 $k$。

第二行有 $n$ 个整数，第 $i$ 个整数表示序列的第 $i$ 个数字 $a_i$。

### 输出格式

输出一行一个整数表示答案。

### 样例 #1

#### 样例输入 #1

```C++
3 2
1
2
3
```

#### 样例输出 #1

```C++
4
```

### 提示

##### 样例 1 解释

共有 $6$ 个连续的子序列，分别是 $(1)$、$(2)$、$(3)$、$(1,2)$、$(2,3)$、$(1,2,3)$，平均值分别为 $1$、$2$、$3$、$1.5$、$2.5$、$2$，其中平均值不小于 $2$ 的共有 $4$ 个。

##### 数据规模与约定

- 对于 $20\%$ 的数据，保证 $n \leq 100$。

- 对于 $50\%$ 的数据，保证 $n \leq 5000$。

- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 10^5$，$1 \leq a_i,k \leq 10^4$。

## [BJOI2016] 回转寿司

### 题目描述

酷爱日料的小Z经常光顾学校东门外的回转寿司店。在这里，一盘盘寿司通过传送带依次呈现在小Z眼前。

不同的寿司带给小Z的味觉感受是不一样的，我们定义小Z对每盘寿司都有一个满意度。

例如小Z酷爱三文鱼，他对一盘三文鱼寿司的满意度为 $10$；小Z觉得金枪鱼没有什么味道，他对一盘金枪鱼寿司的满意度只有 $5$；小Z最近看了电影《美人鱼》，被里面的八爪鱼恶心到了，所以他对一盘八爪鱼刺身的满意度是 $-100$。

特别地，小Z是个著名的吃货，他吃回转寿司有一个习惯，我们称之为“狂吃不止”。具体地讲，当他吃掉传送带上的一盘寿司后，他会毫不犹豫地吃掉它后面的寿司，直到他不想再吃寿司了为止。

今天，小Z再次来到了这家回转寿司店，$N$ 盘寿司将依次经过他的面前。其中，小Z对第 $i$ 盘寿司的满意度为$a_i$。

小Z可以选择从哪盘寿司开始吃，也可以选择吃到哪盘寿司为止。他想知道共有多少种不同的选择，使得他的满意度之和不低于 $L$，且不高于 $R$。

注意，虽然这是回转寿司，但是我们不认为这是一个环上的问题，而是一条线上的问题。即，小Z能吃到的是输入序列的一个连续子串；最后一盘转走之后，第一盘并不会再出现一次。

### 思路

我们可以枚举 r=1∼n，求出对于每个 r 有多少 l 符合条件，累加即是答案。用权值线段树查询l的个数即可。

或者我们可以使用cdq分治来解决本题。

这道题很明显一开始要先求个前缀和，这个问题就转换成求i< j，s[j]-s[i]>=L且s[j]-s[i]<=R的对数（0<=i< n)。感觉这个形式跟逆序对有点像，于是便想到了归并排序。但有点区别，那就是答案的统计方式就没有那么简单了。

但其实我们化一下式子，变成s[i]-s[j]>=L,s[i]-s[j]<=R（看代码就能理解了），发现就可以用队列来维护。

---

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long


#define rd read()
int read(){
	int xx=0,ff=1;
	char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') ff=-1;c=getchar();}
	while(c>='0'&&c<='9') xx=xx*10+(c-'0'),c=getchar();
	return xx*ff;
}
void write(int out){
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}


int L,R,ans,qzh[110000];
void cdq(int l,int r){
    if(l==r)return ;
    int mid=(l+r)/2;
    cdq(l,mid),cdq(mid+1,r);
    int head=l,tail=l-1;
    for(int i=mid+1;i<=r;i++){
        while(tail+1<=mid && qzh[i]>=qzh[tail+1]+L)tail++;
        while(head<=mid && qzh[i]>qzh[head]+R)head++;
        ans+=tail-head+1;
    }
    sort(qzh+l,qzh+r+1);
}//cdq分治
signed main(){
    int n=rd;L=rd,R=rd;
    for(int i=1;i<=n;i++){
        int x=rd;;
        qzh[i]=qzh[i-1]+x;//前缀和
    }
    cdq(0,n);
    printf("%lld\n",ans);
    return 0;
}


```

### 输入格式

第一行三个正整数 $N,L,R$，表示寿司盘数，满意度的下限和上限。
第二行包含 $N$ 个整数 $a_i$，表示小Z对寿司的满意度。

### 输出格式

一行一个整数，表示有多少种方案可以使得小Z的满意度之和不低于 $L$ 且不高于 $R$。

### 样例 #1

#### 样例输入 #1

```C++
5 5 9
1 2 3 4 5
```

#### 样例输出 #1

```C++
6
```

### 提示

【数据范围】

$1\le N \le 10^5



因为每个人都只有可能选择两款相邻的尺码，我们按每个人第一款尺码从小到大排序后从小到大贪心地分配各个款式的衣服即可，即优先分配尺码小的衣服，不够了再分配尺码大的。

其它真的就没了。

---

**一些字符串操作**

`t.find(",",0)` 返回字符串 $t$ 中第一个 `,` 的下标。

`t.substr(0, pos)` 取出下标范围内的子串，返回值为 `string`。

---

```C++
/*
CB Ntsc
*/

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define pii pair<int, int>
#define pf first
#define ps second

#define err cerr<<"Error"
#define rd read()
#define nl putc('\n')
#define ot write
#define nl putchar('\n')
inline int rd
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}

const int INF = 1e9;
const int N = 2e6+5;
const int M = 1e6+5;
const int S=1e6+5;
const int maxlog = 10;
string ds[10]={"S","M","L","XL","XXL","XXXL"};
struct node{
	int a,b,id;
}p[N];
int tot;
int ans[N];
int c[N],n;
void cal(string s,int id,int f,int idx){
	for(int i=0;i<6;i++){
		if(ds[i]==s){
			if(f==1)p[id].a=i,p[id].id=idx;
			if(f==2)p[id].b=i,p[id].id=idx;
			if(!f){
				ans[idx]=i;
				c[i]--;
				if(c[i]<0){
					cout<<"NO"<<endl;
					exit(0);
				}
				return ;
			}
			
		}
	}
}
bool cmp(node a,node b){
	return a.a<b.a;
}

signed main(){
	for(int i=0;i<6;i++)c[i]=rd;
	n=rd;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		int pos=s.find(",",0);
		if(pos==EOF){
			cal(s,0,0,i);
		}else{
			cal(s.substr(0,pos),++tot,1,i);
			cal(s.substr(pos+1,s.size()-1),tot,2,i);
		}

	}

	// for(int i=1;i<=tot;i++){
	// 	cerr<<p[i].a<<' '<<p[i].b<<endl;
	// }

	sort(p+1,p+tot+1,cmp);
	for(int i=1;i<=tot;i++){
		int a=p[i].a,b=p[i].b,id=p[i].id;
		if(c[a])c[a]--,ans[id]=a;
		else c[b]--,ans[id]=b;
		if(c[b]<0){
			cout<<"NO"<<endl;
			return 0;
		}
	}
	cout<<"YES\n";
	for(int i=1;i<=n;i++){
		cout<<ds[ans[i]]<<endl;
	}
}
/*
2 5
0 1 1 1 1
0 1 1 2 4
0 2 1 2 1
0 2 1 1 4
*/
```

### 题目描述

The organizers of a programming contest have decided to present t-shirts to participants. There are six different t-shirts sizes in this problem: S, M, L, XL, XXL, XXXL (sizes are listed in increasing order). The t-shirts are already prepared. For each size from S to XXXL you are given the number of t-shirts of this size.

During the registration, the organizers asked each of the $n$ participants about the t-shirt size he wants. If a participant hesitated between two sizes, he could specify two neighboring sizes — this means that any of these two sizes suits him.

Write a program that will determine whether it is possible to present a t-shirt to each participant of the competition, or not. Of course, each participant should get a t-shirt of proper size:

- the size he wanted, if he specified one size;

- any of the two neibouring sizes, if he specified two sizes.

If it is possible, the program should find any valid distribution of the t-shirts.

### 输入格式

The first line of the input contains six non-negative integers — the number of t-shirts of each size. The numbers are given for the sizes S, M, L, XL, XXL, XXXL, respectively. The total number of t-shirts doesn't exceed $100000$ .

The second line contains positive integer $n$ ( $1<=n<=100000$ ) — the number of participants.

The following $n$ lines contain the sizes specified by the participants, one line per participant. The $i$ -th line contains information provided by the $i$ -th participant: single size or two sizes separated by comma (without any spaces). If there are two sizes, the sizes are written in increasing order. It is guaranteed that two sizes separated by comma are neighboring.

### 输出格式

If it is not possible to present a t-shirt to each participant, print «NO» (without quotes).

Otherwise, print $n+1$ lines. In the first line print «YES» (without quotes). In the following $n$ lines print the t-shirt sizes the orginizers should give to participants, one per line. The order of the participants should be the same as in the input.

If there are multiple solutions, print any of them.

### 样例 #1

#### 样例输入 #1

```C++
0 1 0 1 1 0
3
XL
S,M
XL,XXL
```

#### 样例输出 #1

```C++
YES
XL
M
XXL
```

### 样例 #2

#### 样例输入 #2

```C++
1 1 2 0 1 1
5
S
M
S,M
XXL,XXXL
XL,XXL
```

#### 样例输出 #2

```C++
NO
```

## Anton and Ira

### 题面翻译

给定两个排列 s  和 p ，每次可以交换 p  中的两个数，代价为它们间的距离，问最小代价使 p 变为 s  。要输出方案

### 思路

我们转换一下题面，对 $p$ 建立以 $s$ 为基底的映射，因此 $s$ 变成了 $1\sim n$ 的有序排列，$p$ 变成 $1\sim n $ 的乱序排列，以便于我们进行讨论。

那么现在我们要找到一个普适化的策略来调整 $p$ 使得 $p$ 最终变得升序。

我们可以证明，一定存在 $(i,j),i<j$ 有 $p_j≤i,j≤p_i$。我们可以尝试构造反例来证明，可以发现即使是设计的构造最终也定会存在上面的情况。这也可以说明在 $p$ 变得有序之前，一定会有以上满足条件的二元组存在。

然后当我们每次发现这种二元组，就交换其即可。

事实证明暴力出奇迹。

---

```C++
/*
CB Ntsc
*/

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define pii pair<int, int>
#define pf first
#define ps second

#define err cerr<<"Error"
#define rd read()
#define nl putc('\n')
#define ot write
#define nl putchar('\n')
inline int rd
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}

const int INF = 1e9;
const int N = 2e6+5;
const int M = 1e6+5;
const int S=1e6+5;
const int maxlog = 10;

int n;
int a[N],b[N],t[N]; 
int ans[N][2],top;
int cnt;

signed main(){
	n=rd;
	for(int i=1;i<=n;i++)a[i]=rd;
	for(int i=1;i<=n;i++)b[rd]=i;
	for(int i=1;i<=n;i++)t[i]=b[a[i]];
	for(int i=1;i<=n;i++)b[i]=t[i];
	while(1){
		int f=0;
		int p=0;
		while(b[p]==p)p++;
		for(int i=p;i<=n;i++){
			if(b[i]<=i)continue;
			for(int j=i+1;j<=n;j++){
				if(b[j]<=i&&j<=b[i]){
					cnt+=(j-i);
					ans[++top][0]=i,ans[top][1]=j;
					swap(b[i],b[j]);
					f=1;break;
				}
			}
			if(f)break;	
		}
		if(!f)break;
	}
	cout<<cnt<<endl<<top<<endl;
	for(int i=1;i<=top;i++){
		cout<<ans[i][0]<<' '<<ans[i][1]<<endl;
	}
}

/*
2 5
0 1 1 1 1
0 1 1 2 4
0 2 1 2 1
0 2 1 1 4
*/
```

### 题目描述

Anton loves transforming one permutation into another one by swapping elements for money, and Ira doesn't like paying for stupid games. Help them obtain the required permutation by paying as little money as possible.

More formally, we have two permutations, $p$ and $s$ of numbers from $1$ to $n$ . We can swap $p_{i}$ and $p_{j}$ , by paying $|i-j|$ coins for it. Find and print the smallest number of coins required to obtain permutation $s$ from permutation $p$ . Also print the sequence of swap operations at which we obtain a solution.

### 输入格式

The first line contains a single number $n$ ( $1<=n<=2000$ ) — the length of the permutations.

The second line contains a sequence of $n$ numbers from $1$ to $n$ — permutation $p$ . Each number from $1$ to $n$ occurs exactly once in this line.

The third line contains a sequence of $n$ numbers from $1$ to $n$ — permutation $s$ . Each number from $1$ to $n$ occurs once in this line.

### 输出格式

In the first line print the minimum number of coins that you need to spend to transform permutation $p$ into permutation $s$ .

In the second line print number $k$ ( $0<=k<=2·10^{6}$ ) — the number of operations needed to get the solution.

In the next $k$ lines print the operations. Each line must contain two numbers $i$ and $j$ ( $1<=i,j<=n$ , $i≠j$ ), which means that you need to swap $p_{i}$ and $p_{j}$ .

It is guaranteed that the solution exists.

### 样例 #1

#### 样例输入 #1

```C++
4
4 2 1 3
3 2 4 1
```

#### 样例输出 #1

```C++
3
2
4 3
3 1
```

### 提示

In the first sample test we swap numbers on positions 3 and 4 and permutation $p$ becomes 4 2 3 1. We pay $|3-4|=1$ coins for that. On second turn we swap numbers on positions 1 and 3 and get permutation $3241$ equal to $s$ . We pay $|3-1|=2$ coins for that. In total we pay three coins.

## [DBOI2019] 德丽莎世界第一可爱

### 题目背景

```C++
众所周知，德丽莎世界第一可爱。
——zhengrunzhe
```

你正在打崩坏$3$，突然家长来了，于是你装作在打数据结构题。

### 题目描述

有$n$个崩坏兽，每个崩坏兽有五个属性值：$health$生命力，$energy$能量力，$attack$攻击力，$defense$防御力，$collapse$崩坏能。

德丽莎可以任选一只崩坏兽展开攻击 假如她干掉了崩坏兽$i$ 那么她会收获$collapse[i]$的可爱值 由于德丽莎越战越勇 她打的下一只崩坏兽$j$ 需要满足$health[j]\geq health[i] , energy[j]\geq energy[i] , attack[j]\geq attack[i] , defense[j]\geq defense[i]$。

请你帮帮德丽莎计算一下她能够获得的最大可爱值。

### 思路

求四维权值最大不降链。

可以很快想到一个 $O(n^2)$ 的做法，那就是对于每个数按第一维排序，然后暴力找到合法前缀最大值（dp转移即可），更新这个数的答案。

那么实际上就是个三维偏序问题。

---

那么快速求满足n维偏序关系的所有数字中的最值，我们就用kd树罢了。

```C++

```

### 输入格式

第一行一个正整数$n$。

接下来$n$行，第$i+1$行五个整数$health[i],energy[i],attack[i],defense[i],collapse[i]$，代表着第$i$只崩坏兽的属性值。

### 输出格式

一行一个整数，代表最大可爱值（必须击杀至少一只崩坏兽），答案保证不会超过long long范围($2^{63}-1$)。

$1\leq n\leq 50000$。

对于 $100\%$ 的数据，满足 $|\mathrm{health}_i|, |\mathrm{energy}_i|, |\mathrm{attack_i}|, |\mathrm{defense}_i| \le 10^5$，$| \mathrm{collapse}_i|\le 10^9$。

题目提供者：$\color{red}{zhengrunzhe}$

