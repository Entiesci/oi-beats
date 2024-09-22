[F03【模板】KMP 算法——信息学竞赛算法_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1Ag411o7US/?spm_id_from=333.999.0.0)


# KMP算法

### 百科介绍

KMP算法的核心是利用匹配失败后的信息，尽量减少模式串与主串的匹配次数以达到快速匹配的目的。具体实现就是通过一个next()函数实现，函数本身包含了模式串的局部匹配信息。KMP算法的时间复杂度O(m+n)

**字符串的模式匹配**

字符串的模式匹配是一种常用的运算。所谓模式匹配,可以简单地理解为在目标(字符串)中寻找一个给定的模式(也是字符串)，返回目标和模式匹配的第一个子串的首字符位置。通常目标串比较大，而模式串则比较短小

**模式匹配的类型**

(1)精确匹配
如果在目标T中至少一处存在模式P，则称匹配成功，否则即使目标与模式只有一个字符不同也不能称为匹配成功，即匹配失败。给定一个字符或符号组成的字符串目标对象T和一个字符串模式P，模式匹配的目的是在目标T中搜索与模式P完全相同的子串,返回T和P匹配的第一个字符串的首字母位置 。
(2)近似匹配
如果模式P与目标T(或其子串)存在某种程度的相似,则认为匹配成功。常用的衡量字符串相似度的方法是根据一个串转换成另一个串所需的基本操作数目来确定。基本操作由字符串的插入、删除和替换来组成 。

**KMP模式匹配算法**

KMP算法是一种改进的字符串匹配算法,其关键是利用匹配失败后的信息,尽量减少模式串与主串的匹配次数以达到快速匹配的目的 。
求得模式的特征向量之后，基于特征分析的快速模式匹配算法(KMP模式匹配算法)与朴素匹配算法类似，只是在每次匹配过程中发生某次失配时，不再单纯地把模式后移一位，而是根据当前字符的特征数来决定模式右移的位数 。

## 例题 #1 KMP字符串匹配

题目描述

给出两个字符串 $s_1$ 和 $s_2$，若 $s_1$ 的区间 $[l, r]$ 子串与 $s_2$ 完全相同，则称 $s_2$ 在 $s_1$ 中出现了，其出现位置为 $l$。
现在请你求出 $s_2$ 在 $s_1$ 中所有出现的位置。

定义一个字符串 $s$ 的 border 为 $s$ 的一个**非 $s$ 本身**的子串 $t$，满足 $t$ 既是 $s$ 的前缀，又是 $s$ 的后缀。
对于 $s_2$，你还需要求出对于其每个前缀 $s'$ 的最长 border $t'$ 的长度。

输入格式

第一行为一个字符串，即为 $s_1$。
第二行为一个字符串，即为 $s_2$。

输出格式

首先输出若干行，每行一个整数，**按从小到大的顺序**输出 $s_2$ 在 $s_1$ 中出现的位置。
最后一行输出 $|s_2|$ 个整数，第 $i$ 个整数表示 $s_2$ 的长度为 $i$ 的前缀的最长 border 长度。

对于全部的测试点，保证 $1 \leq |s_1|,|s_2| \leq 10^6$，$s_1, s_2$ 中均只含大写英文字母。

### Solution

```C++
  	#include<bits/stdc++.h>
	using namespace std;
   	char a[1000100],b[1000100];
    int p[1000100],ls1,ls2,j;
    
    void pre(){
    	for(int i=2;i<=ls2;i++){
            while(j>0 && b[i]!=b[j+1]) j=p[j];
            if(b[i]==b[j+1]) j++;
            p[i]=j;
        }
	}
    int main(){
        scanf("%s%s",a+1,b+1);
        ls1=strlen(a+1),ls2=strlen(b+1);
        p[1]=0;
      	pre();

        j=0;
        for(int i=1;i<=ls1;i++){
            while(j>0 && a[i]!=b[j+1]) j=p[j];
            if(a[i]==b[j+1]) j++;
            if(j==ls2) printf("%d\n",i-ls2+1),j=p[j];
        }
        for(int i=1;i<ls2;i++)
        printf("%d ",p[i]);
        printf("%d",p[ls2]);
        return 0;
    }
```

## 练习

对nxt数组的本质探究

[www.luogu.com.cn](https://www.luogu.com.cn/problem/P4391)

## 扩展KMP（exkmp）

[183 扩展 KMP(Z 函数)_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1Y54y1o7Ca/?spm_id_from=333.999.0.0)

给定两个字符串 $a,b$，你要求出两个数组：

- $b$ 的 $z$ 函数数组 $z$，即 $b$ 与 $b$ 的每一个后缀的 LCP（最长公共前缀）长度。

- $b$ 与 $a$ 的每一个后缀的 LCP 长度数组 $p$。

对于一个长度为 $n$ 的数组 $a$，设其权值为 $\operatorname{xor}_{i=1}^n i \times (a_i + 1)$。

```C++
/*////////ACACACACACACAC///////////
       . Code  by  Ntsc .
       . Earn knowledge .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define int long long
#define db double
#define rtn return
using namespace std;

const int N=2e7+5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;

int n,m,q,T,z[N],p[N],ans;
char s[N],t[N];

void get_z(char s[],int n){
	z[1]=n;
	int l=0,r=0;
	for(int i=2;i<=n;i++){
		if(i<=r)z[i]=min(z[i-l+1],r-i+1);
		while(s[1+z[i]]==s[i+z[i]])z[i]++;
		
		if(i+z[i]-1>r)l=i,r=i+z[i]-1;//转移box 
	}
}

void get_p(char s[],char t[],int n,int m){
	int l=0,r=0;
	for(int i=1;i<=m;i++){
		if(i<=r)p[i]=min(z[i-l+1],r-i+1);
		while(s[1+p[i]]==t[i+p[i]]&&1+p[i]<=n&&i+p[i]<=m)p[i]++;
		
		if(i+p[i]-1>r)l=i,r=i+p[i]-1;//转移box 
	}
}

signed main(){
	scanf("%s",t+1);
	scanf("%s",s+1);
	n=strlen(s+1);
	m=strlen(t+1);
	get_z(s,n);
	get_p(s,t,n,m);
	
//	for(int i=1;i<=n;i++)cerr<<z[i]<<' ';
//	cerr<<"z[]end\n";
	for(int i=1;i<=n;i++)ans^=i*(z[i]+1);
	cout<<ans<<endl;
	ans=0;
	for(int i=1;i<=m;i++)ans^=i*(p[i]+1);
	cout<<ans<<endl;
	return 0;
}


```

注意求的是b的z函数

### Z函数

z 函数
对于一个长度为 n 的字符串 s 。$ z_i$表示 $s $与其后缀 $s[ i , n ] $的最长公共前缀 （ LCP ） 的长度

![image.png](KMP/image.png)

暴力计算自然是O(n^2)

### Z-box

手扶着铁窗~~我望~~外边~~~

![image.png](KMP/image 1.png)

对于 i, 我们称区间$ [i,i+ z[i]- 1 ]$ 是的匹配段 ， 也可以叫 Z-box
算法过程中我们维护右端点最靠右的匹配段 。 为了方便 ， 记作[l, r ] 。 s [l,r]一定等于 s  的前缀 。
在计算 z[i] 时我们保证l≤i

举个例子，此时我们已经处理了z[1\sim 5]，此时盒子为[5,8]，那么我们在处理z[6\sim 8]时就可以直接从z[2\sim 4]转移过来。

**算法流程**

![image.png](KMP/image 2.png)

对比一下？马拉车如下：

![image.png](KMP/image 3.png)

我们来解释一下

![image.png](KMP/image 4.png)

1. 我们可以保证s[1,r-l+1]=s[l,r]，但是其余部分我们不能保证。如果i在box内
(1) 如z[i-l+1]<r-i+1，说明z[i-l+1]的对应的字符串全部在box内，所以我们可以保证z[i-l+1]可以完美转移到z[i]
(2) 如z[i-l+1]≥r-i+1，说明z[i-l+1]的对应的字符串前部分在box内，所以我们可以不能保证z[i-l+1]可以完美转移到z[i]，故对于伸出box外的部分，我们要逐个枚举

2. 如果i在box外。那么我们只好暴力枚举了。

但是有一个重点就是box的转移了。要不然这个算法就失去了意义。

求出 $z[i]$ 后 ， 如果 $i + z[i] - 1 > r$, 则更新盒子 $l = i , r = i + z [i]-1$。为什么呢？因为i + z[i] - 1 代表当前z[i]的对应串的右端点。如果i + z[i] - 1 > r，就说明对应串的右端点伸出了当前的box

![image.png](KMP/image 5.png)

很明显，以左图为例，红色box区间已经没有用处了，而现在我们知道蓝色区间对应相等，那么我们就可以把box转移到[l',r']

### 代码

```C++
void get_z(char s[],int n){
	z[1]=n;
	int l=0,r=0;
	for(int i=2;i<=n;i++){
		if(i<=r)z[i]=min(z[i-l+1],r-i+1);
		while(s[1+z[i]]==s[i+z[i]])z[i]++;
		if(i+z[i]-1>r)l=i;r=i+z[i]-1;//转移box 
	}
}
```

时间复杂度分析

时间复杂度完全取决于while，而我们知道，只有当前z[i]对应字符的右边界伸出了box，伸出多少就跑几遍while。而在伸出后我们又会更新box，所以我们的while次数$=r$从$1\sim n=n$次

### P函数

$b$ 与 $a$ 的每一个后缀的 LCP 长度数组 $p$。



```C++
void get_p(char s[],char p[],int n,int m){
	int l=0,r=0;
	for(int i=1;i<=n;i++){
		if(i<=r)p[i]=min(z[i-l+1],r-i+1);
		while(s[1+p[i]]==t[i+p[i]]&&1+p[i]<=n&&i+p[i]<=m)p[i]++;
		
		if(i+p[i]-1>r)l=i;r=i+p[i]-1;//转移box 
	}
}
```

