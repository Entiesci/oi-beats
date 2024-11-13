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
// #define int long long
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


const int N = 1e6 + 5;
const int INF = 1e18;
const int M = 1e7;
const int MOD = 1e9 + 7;



vector<int> e[N];

// 文件！！
void add(int a,int b){
    e[a].pb(b);
    e[b].pb(a);
}

int deepestLeaf[N];
pii son[N][5];

namespace LCA{

    int fa[N][22];
    int dep[N];

    void dfs(int x,int f){
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
// 文件！！
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
        return dep[b]-dep[anc]+dep[a]-dep[anc];
    }


    int jump(int x,int d){//x上跳d层
        int goalDep=dep[x]-d;
        for(itn i=20;~i;i--){
            if(dep[fa[x][i]]>=goalDep)x=fa[x][i];
        }// 文件！！

        return x;
    }


    int queryRoad(int a,int b,int c,int abDis){
        int anc=lca(a,b);
        int ancaDis=dep[a]-dep[anc];
        int ancbDis=dep[b]-dep[anc];
        // cdbg("qR",a,b,c,abDis,ancaDis,ancbDis);
        if(ancaDis>=c)return jump(a,c);
        else return jump(b,ancbDis-(c-ancaDis));

    }

    int getPbeside(itn a,int b){
        int anc=lca(a,b);
        if(anc==a){
            return jump(b,dep[b]-dep[a]-1);
        }else{
            return fa[a][0];
        }
    }
// 文件！！
    int down(int x,int d){
        int leaf=deepestLeaf[x];
        // cdbg("dw",x,d,leaf);
        if(dep[leaf]-dep[x]<d)return -1;
        return jump(leaf,dep[leaf]-dep[x]-d);
    }

}using namespace LCA;

int query(int x,int d,int ban=0,int ban2=0){
    // cdbg("Qy",x,d,ban,ban2);
    if(d==0)return x;
    itn ans=-1;
    for(int i=1;i<=3;i++){
        int v=son[x][i].ps;
        if(v==ban||v==ban2)continue;
        if(!v)continue;
        //  cdbg(x,i,v);

        if(v==fa[x][0]){
            if(dep[v]>d-1)ans=jump(v,d-1);
            else ans=query(1,d-dep[v],getPbeside(1,x));

        }else{
            ans=down(v,d-1);
        } 
        break;
    }

    return ans;

}// 文件！！

priority_queue<pii> pq[N];//小根堆
int treeDep[N];

namespace prework{

    pii preSon[N][5];//第一次dp的记录值

    void dfs(int x,int f){
        deepestLeaf[x]=x;
        for( auto v:e[x]){
            if(v==f)continue;
            prework::dfs(v,x);
            pq[x].push(mp(preSon[v][1].pf-1,v));
            if(treeDep[x]<treeDep[v]+1){
                treeDep[x]=treeDep[v]+1;
                deepestLeaf[x]=deepestLeaf[v];
            }
        }

        while(pq[x].size()>3)pq[x].pop();

        for(int i=min(3,(int)pq[x].size());i&&pq[x].size();i--){
            preSon[x][i]=pq[x].top();
            pq[x].pop();
        }
    }

// 文件！！
    void dfs2(int x,int f){//换根dp
        while(pq[x].size())pq[x].pop();
        for(int i=1;i<=3;i++){
            pq[x].push(preSon[x][i]);
            // cdbg(x,preSon[x][i].ps,preSon[x][i].pf);
        }
        for(int i=1;i<=3;i++){
            if(preSon[f][i].ps==x)continue;
            pq[x].push(mp(son[f][i].pf-1,f));
            // cdbg(x,f,preSon[f][i].pf-1,preSon[f][i].ps);
            break;
        }

        while(pq[x].size()>3)pq[x].pop();
        
        for(int i=min(3,(int)pq[x].size());i&&pq[x].size();i--){
            son[x][i]=pq[x].top();
            // cdbg(son[x][i]);
            pq[x].pop();
        }

        for(auto v:e[x]){
            if(v==f)continue;
            dfs2(v,x);
        }
    }


    void init(){
        prework::dfs(1,0);
        prework::dfs2(1,0);
    }
}

// 文件！！

void solve(){
    itn n=rd,Q=rd;
    for(int i=1;i<n;i++){
        add(rd,rd);
    }


    dfs(1,0);
    prework::init();

    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=3;j++){
    //         cdbg(i,prework::preSon[i][j].ps);
    //     }
    // }
    // ell;
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=3;j++){
    //         cdbg(i,son[i][j].ps);
    //     }
    // }
    // ell;

    // for(int i=1;i<=n;i++){
    //     cdbg(deepestLeaf[i]);
    // }

    while(Q--){
        int a=rd,da=rd,b=rd,db=rd;
        int abDis=getDis(a,b);

        if(da>db){
            swap(a,b);
            swap(da,db);
        }
        // cdbg(a,b,lca(a,b),abDis);
		if(a==b){
			// cdbg("Q same");
			if(da!=db)cout<<-1<<endl;
			else cout<<query(a,da)<<endl;
		}else
        if(db-da==abDis){
            // cdbg("Q1");
            int ans=query(a,da,getPbeside(a,b)/*获取a的含b子树的根节点标号*/);
            if(getDis(ans,a)!=da||getDis(ans,b)!=db)ans=-1;
            cout<<ans<<endl;
        }else{
            int cha=db-da;
            if(cha>abDis){
                cout<<-1<<endl;
                continue;
            }
            int x=queryRoad(a,b,abDis-cha>>1,abDis);//定位a,b路径上离a远c的点
            // cdbg("Q2",cha,x,getPbeside(x,b));
            int ans=query(x,da-(abDis-cha>>1),getPbeside(x,b),getPbeside(x,a));
            if(getDis(ans,a)!=da||getDis(ans,b)!=db)ans=-1;
            cout<<ans<<endl;
        }
    // ell;
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

/*
10 2
10 1 
1 2
2 3
3 4
3 5
5 6
5 7
4 9
4 8

1 3 4 2
2 2 4 4


*/