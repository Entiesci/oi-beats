BSGS~~北上广深~~

# BSGS 大步小步算法

## BSGS求解二元一次不定方程

求关于x的同余方程 $ax\equiv1\pmod{b}$ 的最小正整数解。

---

BSGS（Baby-step giant-step）算法是一种用于解决离散对数问题的算法，但也可以被应用于求解某些形式的二元一次不定方程。二元一次不定方程通常指的是形如 $ax + by = c$ 的方程，其中 $x$ 和 $y$ 是未知数，$a$、$b$ 和 $c$ 是已知的整数。
要使用BSGS算法求解二元一次不定方程 $ax + by = c$，首先需要确保该方程有解。一个必要条件是 $c$ 必须是 $a$ 和 $b$ 的最大公约数（gcd）的倍数。如果 $\text{gcd}(a, b) \nmid c$，则方程无解。
以下是使用BSGS算法求解 $ax + by = c$ 的步骤：

1. **计算gcd**：计算 $a$ 和 $b$ 的最大公约数 $d$。如果 $d \nmid c$，则方程无解。

2. **化简方程**：将方程 $ax + by = c$ 除以 $d$，得到新的方程 $\frac{a}{d}x + \frac{b}{d}y = \frac{c}{d}$。

3. **求解化简后的方程**：现在我们假设 $\text{gcd}(\frac{a}{d}, \frac{b}{d}) = 1$，这样我们可以使用BSGS算法求解。以下是BSGS算法的步骤：
a. **Baby-step**：计算并存储一系列的值 $\frac{a}{d} \times 0, \frac{a}{d} \times 1, \frac{a}{d} \times 2, \ldots, \frac{a}{d} \times m$，其中 $m$ 是一个适当的界限。
b. **Giant-step**：计算并检查一系列的值 $\frac{c}{d} - \frac{b}{d} \times n$，其中 $n$ 是从 0 到 $m$ 的整数。对于每个这样的值，检查它是否在 baby-step 中计算过的值的集合中。
c. **找到解**：如果找到一个匹配的值，那么我们可以解出 $x$ 和 $y$。

4. **回代原方程**：一旦我们找到 $\frac{a}{d}x + \frac{b}{d}y = \frac{c}{d}$ 的解，我们可以将其乘以 $d$ 来得到原方程 $ax + by = c$ 的解。
请注意，BSGS算法通常用于解决离散对数问题，对于二元一次不定方程，通常使用扩展欧几里得算法更为直接和高效。扩展欧几里得算法可以直接求解形如 $ax + by = \text{gcd}(a, b)$ 的方程，如果 $c$ 是 $\text{gcd}(a, b)$ 的倍数，那么可以通过扩展欧几里得算法找到特解，然后通过调整特解来找到原方程的所有解。

```C++
map<int ,int > cnt;
void solve(){
    itn a=rd,b=rd;
    itn B=sqrt(b);
    for(itn i=B;~i;i--){
    	cnt[a*i%b]=i;
	}
	
	for(int i=0;i<=b/B;i++){
		itn t=i*B%b*a%b;
		t=(b+1-t)%b;
		if(cnt.find(t)!=cnt.end()){
			cout<<cnt[t]+i*B<<endl;
			exit(0);
		}
	}
}
```

但是要注意，BSGS是有局限的。它的数据不能超过10^7，否则会爆空间。比如说下面一道题就不能应用了。

## BSGS的其它应用

给定一个质数 $p$，以及一个整数 $b$，一个整数 $n$，现在要求你计算一个最小的非负整数 $l$，满足 $b^l \equiv n \pmod p$。

---

我们现在来考虑优化。令$b=ip-j,p=\lceil\sqrt m\rceil,i\in [1,p],j\in[0,p-1]$。这样的话我们b的取值恰好为$b\in[1,m]$，对于b=0我们特判即可。

那么这样的意义何在？

我们将 $b^l \equiv n \pmod m$表示为$b^{ip-j}\equiv n \pmod m$，变形$(b^i)^p\equiv nb^j \pmod m$其中p是定值。

首先，我们枚举i，用map记录二元组$(i,(b^i)^p\mod m)$，然后枚举j（独立），记录二元组$(j,nb^j\mod m)$。当我们第一次发现两个二元组$(i,(b^i)^p\mod m)(j,nb^j\mod m)$中第二元相同时，此时的i,j即答案。

这就相当于$i,j\in [1,n]$，求$f(i)=g(j)$时的i,j，我们不需要n^2枚举，只需要建立映射，看有没有i,j映射到同一个值是即可。

独立分开枚举$i,j$都是$O(\sqrt m)$的复杂度。

![image.png](BSGS/image.png)

```C++
/*
Code bnxt Ntsc_Hodaka
*/

#include <bits/stdc++.h>
using namespace std;
#define int unsigned long long
#define mp make_pair
#define pii pair<int,int>

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
    while (ch >= '0' && ch <= '9') xx = xx * 10 + (ch - '0'), ch = getchar();
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
const int INF = 1e9 + 5;
int MOD=1e9+7;
const double eps=1e-7;

bool f1;
///----///
int n,a[N],b[N],x,ans;
bool f2;

int ksm(int a,int b){
	int res=1;
	while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;
        b>>=1;
    }
	return res;
}

int bsgs(int a,int b,int p){
	a%=p;b%=p;
	if(b==1)return 0;
	int m=ceil(sqrt(p)),t=b;
	unordered_map<int,int> mp;
	mp[b]=0;
	for(int i=1;i<m;i++){
		t=t*a%p;
		mp[t]=i;
	}
	int res=ksm(a,m);
	t=1;
	for(int i=1;i<=m;i++){
		t=t*res%p;
		if(mp.count(t))return i*m-mp[t];
	}
	return -1;
}

signed main(){
	int p=rd,a=rd,b=rd;
	MOD=p;
	ans=bsgs(a,b,p);
	if(~ans)cout<<ans;
	else cout<<"no solution";
	return 0;
}


/*

*/
```

