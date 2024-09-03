/*                                                                                
                      Keyblinds Guide
     				###################
      @Ntsc 2024

      - Ctrl+Alt+G then P : Enter luogu problem details
      - Ctrl+Alt+B : Run all cases in CPH
      - ctrl+D : choose this and dump to the next
      - ctrl+Shift+L : choose all like this
      - ctrl+K then ctrl+W: close all
      - Alt+la/ra : move mouse to pre/nxt pos'
	  
*/
#include <bits/stdc++.h>
#include <queue>
using namespace std;

#define rep(i, l, r) for (int i = l, END##i = r; i <= END##i; ++i)
#define per(i, r, l) for (int i = r, END##i = l; i >= END##i; --i)
#define pb push_back
#define mp make_pair
#define int long long
#define ull unsigned long long
#define pii pair<int, int>
#define ps second
#define pf first

// #define innt int
#define itn int
// #define inr intw
// #define mian main
// #define iont int

#define rd read()
int read(){
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

#define ell dbg('\n')
const char el='\n';
const bool enable_dbg = 1;
template <typename T,typename... Args>
void dbg(T s,Args... args) {
	if constexpr (enable_dbg){
    cerr << s;
    if(1)cerr<<' ';
		if constexpr (sizeof...(Args))
			dbg(args...);
	}
}

#define zerol = 1
#ifdef zerol
#define cdbg(x...) do { cerr << #x << " -> "; err(x); } while (0)
void err() { cerr << endl; }
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) { for (auto v: a) cerr << v << ' '; err(x...); }
template<typename T, typename... A>
void err(T a, A... x) { cerr << a << ' '; err(x...); }
#else
#define dbg(...)
#endif


const int N = 3e5 + 5;
const int INF = 1e18;
const int M = 1e7;
const int MOD = 1e9 + 7;


int mx,mn;
int c[N];

vector<int> e[N];

void add(int a,int b){
    e[a].pb(b);
    e[b].pb(a);
}

namespace LCA{
    int dep[N];

    int fa[N][22];


    void dfs(itn x,int f){
        dep[x]=dep[f]+1;
        for(auto v:e[x]){
            if(v==f)continue;
            fa[v][0]=x;
            for(int i=1;i<=20;i++){
                fa[v][i]=fa[fa[v][i-1]][i-1];
            }
            dfs(v,x);
        }
    }


    int lca(int a,int b){
        if(dep[a]<dep[b])swap(a,b);
        for(int i=20;~i;i--){
            if(dep[fa[a][i]]>=dep[b])a=fa[a][i];

        }

        if(a==b)return a;
        for(int i=20;~i;i--){
            if(fa[a][i]!=fa[b][i]){
                a=fa[a][i];
                b=fa[b][i];
            }
        }

        return fa[a][0];
    }


    int getDis(int a,int b){
        int anc=lca(a,b);
        return dep[a]-dep[anc]+dep[b]-dep[anc];
    }
}


using LCA::getDis;



void solve(){
    int n=rd,q=rd;
    for(int i=1;i<n;i++){
        add(rd,rd);

    }

    LCA::dfs(1,0);
    // cdbg(getDis(2,4));

    while(q--){
        int a=rd,da=rd,c=rd,dc=rd;
        int f=0;

        for(int i=1;i<=n;i++){
            int Da=getDis(a,i);
            if(Da!=da)continue;
            // cdbg(a,c,i,"ok1");
            int Dc=getDis(c,i);
            if(Dc!=dc)continue;

            cout<<i<<endl;
            f=1;
            break;
        }


        if(!f)cout<<-1<<endl;
    }
}

signed main() {
    // freopen("hunting.in","r",stdin);
    // freopen("hunting.out","w",stdout);

    int T=1;
    while(T--){
    	solve();
    }
    return 0;
}