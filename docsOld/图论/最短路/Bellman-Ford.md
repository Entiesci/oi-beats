# Bellman-Ford

求总路径条数不多于K条的最短路径

```C++
#include<bits/stdc++.h>
using namespace std;
int n,m,ans;
int dis[5005],road[5005][5005];

void bellman(){
	
	for(int i=2;i<=n;i++)dis[i]=0x3f3f3f3f;
	dis[1]=0;
	for(int i=1;i<=n;i++){
		int flag=0;
		for(int j=1;j<=m;j++){
			if(dis[j]>dis[i]/如果1->j比1->i->j远，则更新它 
		}
		if(!flag)break;	//如果没有更新则break 
	}
}
int main(){
	memset(road,0x3f3f3f3f,sizeof road);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		road[u][v]=w;
	
	}
	bellman();
	
	for(int i=1;i<=n;i++)cout<<dis[i]<<' ';

    return 0;
}
```

另外一种写法

```C++
#include<bits/stdc++.h>
using namespace std;
int n,m,ans;
int d[5005];
struct node{
	int u,v,w;
}e[5050];
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int c,c2,y;
		cin>>c>>c2>>y;
		e[i].u=c2;e[i].v=c;e[i].w=y;
	
	}
	for(int i=2;i<=n;i++)d[i]=0x3f3f3f3f;
	for(int i=1;i<=n-1;i++){
		for(int j=1;j<=m;j++){
			d[e[j].v]=min(d[e[j].u]+e[j].w,d[e[j].v]);
		}
	}
	for(int i=1;i<=m;i++){
		if(d[e[i].v]>d[e[i].u]+e[i].w){
			printf("NO");return 0;  //有负环
		}
	}
	for(int i=1;i<=n;i++)cout<<d[i]<<' ';

    return 0;
}
```

因为图的最短路径不包含负环或正环，故显然最多只能包含 n−1 条边，于是进行 n−1 次松弛操作。

若经过 n−1 轮松弛操作后仍能松弛，说明图存在负权回路。



