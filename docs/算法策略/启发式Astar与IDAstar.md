专题 | 启发式A* IDA*

## 概述

![image.png](启发式Astar与IDAstar+5e4d8b95-457d-40d5-ab5a-f47e82c4e77e/image.png)

共性：

![image.png](启发式Astar与IDAstar+5e4d8b95-457d-40d5-ab5a-f47e82c4e77e/image 1.png)

# A*

![image.png](启发式Astar与IDAstar+5e4d8b95-457d-40d5-ab5a-f47e82c4e77e/image 2.png)

具体题目具体分析：

![image.png](启发式Astar与IDAstar+5e4d8b95-457d-40d5-ab5a-f47e82c4e77e/image 3.png)

做法

![image.png](启发式Astar与IDAstar+5e4d8b95-457d-40d5-ab5a-f47e82c4e77e/image 4.png)

注：三元组为（当前代价+估价，当前点编号，当前点到起点的距离）

**那么在这道题目中，估价有什么作用呢？**

传统的最短路，我们只是不断用最小值去更新到达终点T的最短路，但我们不知道当前这条路是点击短的。如果我们用A*算法，我们就能控制bfs先走第一短的，再走第二短的...，这样的话我们就可以找到第K短的了。

注意这些

![image.png](启发式Astar与IDAstar+5e4d8b95-457d-40d5-ab5a-f47e82c4e77e/image 5.png)

敲一遍代码

```C++
/*////////ACACACACACACAC///////////
       . Code by Ntsc .
       . Love by Liye .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define ll long long
#define db double
#define rtn return
using namespace std;

const int N=1e5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;

int h[N],rh[N],to[M],w[M],ne[M],tot;
void add(int h[],int a,int b,int c){
	to[++tot]=b,w[tot]=c,ne[tot]=h[a],h[a]=tot;
}

int n,m,s,t,k;
int f[N],vis[N],cnt[N];
struct node{
	int s,v,d;
	bool operator <(const node &x)const{
		return s>x.s;
	}
};

void djstr(){
	memset(f,0x3f,sizeof f);
	priority_queue<pair<int,int>> q;
	q.push(make_pair(0,t));
	while(q.size()){
		pair<int,int> tmp=q.top();
		q.pop();
		int u=tmp.second;
		if(vis[u])continue;
		vis[u]=1;
		for(int i=rh[u];i;i=ne[i]){
			int v=to[i];
			if(f[v]>f[u]+w[i]){
				f[v]=f[u]+w[i];//f[v]是点v到t的当前距离(当前的djstr是预处理估价函数的,把t当作起点)，也是其估价函数 
				q.push(make_pair(-f[v],v));
			}
		}
	}
}

int ax(){
	priority_queue<node> pq;
	node a={f[s],s,0};
	pq.push(a);
	while(pq.size()){
		node tmp=pq.top();pq.pop();
		int u=tmp.v,d=tmp.d;
		cnt[u]++;
		if(cnt[t]==k)return d;
		for(int i=h[u];i;i=ne[i]){
			int v=to[i];
			if(cnt[v]<k){
				node a={d+w[i]+f[v],v,d+w[i]};
				pq.push(a);
			}
		}
	}
	return -1;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int a,b,c;
		cin>>a>>b>>c;
		add(h,a,b,c);add(rh,b,a,c);
	}
	cin>>s>>t>>k;
	if(s==t)k++;//如果s,t重合,那么0是最短的,A*会统计这一条,但题目要求不能算这条路,因此实际上应该要求第K+1条路 
	djstr();
	cout<<ax()<<endl;
	return 0;
}

```

**注意！A*就是变形的Dijkstra！**

核心思路：反搜求估价，正搜带估价求第K短



# IDA*

[230 IDA算法 Booksort_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1jh411P7EE/?spm_id_from=333.999.0.0&vd_source=f45ea4e1e4b3b73d5f07c57b46c43aba)

同样的，具体题目具体分析：

![image.png](启发式Astar与IDAstar+5e4d8b95-457d-40d5-ab5a-f47e82c4e77e/image 6.png)

我们可以很明显的发现提示**迭代加深**的字眼：

![image.png](启发式Astar与IDAstar+5e4d8b95-457d-40d5-ab5a-f47e82c4e77e/image 7.png)



![image.png](启发式Astar与IDAstar+5e4d8b95-457d-40d5-ab5a-f47e82c4e77e/image 8.png)

注意观察为什么要÷2

![image.png](启发式Astar与IDAstar+5e4d8b95-457d-40d5-ab5a-f47e82c4e77e/image 9.png)

### 知识扩展：双向BFS

放图，秒懂

![https://tse1-mm.cn.bing.net/th/id/OIP-C.On44jvHe-eDNm83-a7xq0QHaHH?pid=ImgDet&rs=1](https://tse1-mm.cn.bing.net/th/id/OIP-C.On44jvHe-eDNm83-a7xq0QHaHH?pid=ImgDet&rs=1)

本题中一边BFS从初始状态开始搜，一边BFS从排好序后开始搜（打乱地搜），限制步数为2，如果有一对BFS搜索最终状态相同，即找到一条符合线路

### IDA*算法

 

![image.png](启发式Astar与IDAstar+5e4d8b95-457d-40d5-ab5a-f47e82c4e77e/image 10.png)

考察以下案例

![image.png](启发式Astar与IDAstar+5e4d8b95-457d-40d5-ab5a-f47e82c4e77e/image 11.png)

我们发现了3个错误连接，分别为**1-4，5-2，3-6**

在极佳状态下，我们一次操作最多能修正3个错误连接。那么我们每DFS到一个状态，就去统计当前还剩下的错误状态的个数n，如果$\lceil n\div 3\rceil + 当前已经移动的步数 > 4$，那么我们就进行剪枝。

怎么样，是不是想法很简单？

![image.png](启发式Astar与IDAstar+5e4d8b95-457d-40d5-ab5a-f47e82c4e77e/image 12.png)

IDA*算法需要具体题目具体讨论，没有固定的代码模板，这里也就不写了

本题的**IDA*核心思想**是：

制定一个估价函数，求出当前状态下达到目的还需要的最少步数（假设一切理想），如果仍然无法满足要求，就果断砍掉。

