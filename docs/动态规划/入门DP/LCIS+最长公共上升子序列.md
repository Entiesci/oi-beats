# LCIS 最长公共上升子序列

## 题面翻译

求两个串的最长公共上升子序列。输出长度与序列。

The first line contains an integer $n$ ( $1<=n<=500$ ) — the length of the first sequence. The second line contains $n$ space-separated integers from the range $[0,10^{9}]$ — elements of the first sequence. The third line contains an integer $m$ ( $1<=m<=500$ ) — the length of the second sequence. The fourth line contains $m$ space-separated integers from the range $[0,10^{9}]$ — elements of the second sequence.

---

```C++
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

#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)

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

const int N = 1e3 + 15;
const int INF = 1e9 + 5;
const int MOD = 1e9 + 7;
const int M = N * 21;

int n,m,a[N],b[N];
int s[N],top;
int pre[N][N],f[N][N];
    int sp,ans=0;



signed  main(){
	n=rd;
	for(int i=1;i<=n;i++)a[i]=rd;
    m=rd;
	for(int i=1;i<=m;i++)b[i]=rd;
    a[0]=b[0]=-1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i]==b[j]){
                for(int k=0;k<j;k++){
                    if(a[i]>b[k]&&f[i][j]<f[i-1][k]+1){
                        f[i][j]=f[i-1][k]+1;
                        pre[i][j]=k;
                    }
                }
            }else{
                f[i][j]=f[i-1][j];
                pre[i][j]=pre[i-1][j];

            }
        }
    }
    for(int j=1;j<=m;j++){
        if(ans<f[n][j])ans=f[n][j],sp=j;
    }
    cout<<ans<<endl;
    while(sp){
        s[++top]=b[sp];
        sp=pre[n][sp];
    }
    while(top)cout<<s[top--]<<' ';

}
```

