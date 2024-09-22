# Sequence of Balls

## 题面翻译

### 题目描述

有两个字符串 $A, B$，每次可以对 $A$ 进行 $4$ 种操作：

1. 插入一个字符，花费 $t_i$ 元；

2. 删除一个字符，花费 $t_d$ 元；

3. 替换一个字符，花费 $t_r$ 元；

4. 交换相邻的两个字符，花费 $t_e$ 元。

保证费用都是 $[1, 100]$ 之间的正整数，且 $2t_e\geq t_i + t_d$。

求将 $A$ 变成 $B$ 最少需要多少元。

### 输入格式

第一行四个整数 $t_i, t_d, t_r, t_e$。

接下来两行，每行一个字符串分别表示 $A, B$，保证它们长度都不超过 $4000$。

## 思路

我们先来看到，假设只有插入，删除，替换三种操作，我们应该怎么做。

[www.luogu.com.cn](https://www.luogu.com.cn/problem/P2758)


我们定义 dp 状态 $dp_{i,j}$ 为 $A$ 的前 $i$ 个字符与 $B$ 的前 $j$ 个字符相同的最少操作数。转移，当我们 $i≠j$ 时，若 $i>j$ 说明我们在 $A$ 的前 $i$ 个字符中删去了某些字符后与 $B$ 的前 $j$ 个字符匹配。若 $i<j$ 说明我们在 $A$ 的前 $i$ 个字符中添加了某些字符后与 $B$ 的前 $j$ 个字符匹配。当然混合情况也有。

我们考虑每个操作对应的转移

- 插入 $dp_{i,j}=\min(dp_{i,j},dp_{i,j-1}+1)$

- 删除 $dp_{i,j}=\min(dp_{i,j},dp_{i-1,j}+1)$

- 替换 $dp_{i,j}=\min(dp_{i,j},dp_{i-1,j-1}+[A_i≠B_j])$

```C++

int n,m,la,lb;
int dp[N][N];
string A,B;

void minn(int &a,int b){
	a=min(a,b);
}

signed main(){

//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	freopen(".txt","w",stderr);

	cin>>A>>B;
	
	la=A.size(),lb=B.size();
	A=' '+A;
	B=' '+B;

	
	memset(dp,0x3f3f,sizeof dp);
	
	dp[0][0]=0;
	
	for(int i=0;i<=la;i++){
		for(int j=0;j<=lb;j++){
			if(j)minn(dp[i][j],dp[i][j-1]+1);//插入
			if(i)minn(dp[i][j],dp[i-1][j]+1);//删除
			if(i&&j){
				minn(dp[i][j],dp[i-1][j-1]+(A[i]!=B[j]));//替换
				
			}
		}
	}
	
	cout<<dp[la][lb]<<endl;
	
	return 0;
}

```

那么要变成本题，我们要解决两个问题：操作的花费和交换操作。

操作的花费很好解决，即：

- 插入 $dp_{i,j}=\min(dp_{i,j},dp_{i,j-1}+t_i)$

- 删除 $dp_{i,j}=\min(dp_{i,j},dp_{i-1,j}+t_d)$

- 替换 $dp_{i,j}=\min(dp_{i,j},dp_{i-1,j-1}+[A_i≠B_j]\times t_r)$，其中如果 $A_i=B_i$，那么 $[A_i≠B_i]=0$，即不需要花费。

那么对应交换操作，我们好像不能再按照这样的 dp 转移来计算了。那么我们来考虑什么时候我们需要交换操作。

如果在交换之后，我们删除了两个数其中的某一个，那么我们都交换就是没有意义的。由于题目给定 $2t_e\geq t_i + t_d$，所以我们知道，如果对同一个数字我们连续交换两次，我们不如先删除然后插入。即假设我们要交换若干个二元组 $i,j$，那么这些二元组组成的集合中不应该有重复项。

同时，假设我们交换只是为了让一个字符匹配到，那么我们不如删除或者插入。即：假设有交换二元组 $i,i+1$，如果我们为了让 $A_i$ 与 $B_j$ 匹配而交换，那么我们不如在 $A_i$ 前插入 $B_{j-1}$。如果我们为了让 $A_{i+1}$ 与 $B_j$ 匹配，那么我们不如删去 $A_i$。除非交换之后恰好两个字符都从不匹配状态变成匹配状态，否则我们不会交换 $i,i+1$。

我们还可以证明，**被交换过的数字一定不会被执行其他操作。**



假设我们想把 $a_{k}$ 这个字符交换到 $a_i$ 处 $(a_k=b_{j},0<k<i)$，注意这里肯定要保证 $k$ 尽可能的大，

如果只是交换相邻的两个字符很难保证相等，因为一交换前面的都会打乱，

所以我们考虑把 $a_k$ 到 $a_{i}$ 之间的字符都删掉，**再去 $B$ 中找 $j$ 位置左侧第一个等于 $a_i$ 的字符 $b_{p}$**，

这个时候我们再交换 $a_{k}$ 与 $a_{i}$（目的是让 $a_k,a_i$ 的相对顺序与 $b_j,b_p$ 相同，这样的话就让两个字符都匹配了，虽然还可能需要一些插入操作，但这些操作都是必要的。），然后把 $b_{p+1}$ 一直到 $b_{j-1}$ 的这些字符都插入进来，这样我们就完成一次交换且满足相等的条件。

所以我们来计算一下花费：

$t'_d=(i-k-1)\times t_d$

$t'_i=(j-p-1)\times t_i$

转移方程为 $dp_{i,j}=\min(dp_{i,j},dp_{k-1,p-1}+t'_d+t'_i+t_e)$。因为我们要快速求出 $k,p$，所以我们要预处理一下对于每个 $a_i$ 在 ****$B$ 中 $i$ 位置左侧第一个等于 $a_i$ 的字符 **$b_{p}$** 的位置。



现在$4$种操作的转移方程我们都知道了，我们可以开始写代码了。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . FancyKnowledge .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

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
//*/

//
using namespace std;
//
const int N=4e3+5;
const int M=1e3;
const int MOD=1e9+7;
const int MMOD=903250223;
const int INF=1e9;
const db eps=1e-9;
//
int n,m,la,lb;
int dp[N][N];

int ti,td,tr,te,prea[33][N],preb[33][N];
int L;


string A,B;

void minn(int &a,int b){
	a=min(a,b);
}

void init(){//预处理前驱
	for(int i=1;i<=la;i++){
		for(int j=1;j<=26;j++){
			prea[j][i+1]=prea[j][i];
		}
		prea[A[i]-'a'+1][i+1]=i;
	}
	
	for(int i=1;i<=lb;i++){
		for(int j=1;j<=26;j++){
			preb[j][i+1]=preb[j][i];
		}
		preb[B[i]-'a'+1][i+1]=i;
	}
}

signed main(){

//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	freopen(".txt","w",stderr);

	cin>>ti>>td>>tr>>te>>A>>B;
	
	la=A.size(),lb=B.size();
	A=' '+A;
	B=' '+B;
	
	init();
	
	
	memset(dp,0x3f3f,sizeof dp);
	
	dp[0][0]=0;
	
	for(int i=0;i<=la;i++){
		for(int j=0;j<=lb;j++){
			if(j)minn(dp[i][j],dp[i][j-1]+ti);//插入
			if(i)minn(dp[i][j],dp[i-1][j]+td);//删除
			if(i&&j){
				minn(dp[i][j],dp[i-1][j-1]+tr*(A[i]!=B[j]));//替换
				int s=prea[B[j]-'a'+1][i],t=preb[A[i]-'a'+1][j];
				if(s&&t){
					minn(dp[i][j],dp[s-1][t-1]+(i-s-1)*td+(j-t-1)*ti+te);//交换
				}
			}
		}
	}
	
	cout<<dp[la][lb]<<endl;
	
	return 0;
}

//check your long long and the size of memery!!!

```

[Submission #222670912 - Codeforces](https://codeforces.com/contest/67/submission/222670912)


