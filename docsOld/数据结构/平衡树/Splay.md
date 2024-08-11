# Splay

[161 普通平衡树 Splay_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1wg411Z7Qa/?spm_id_from=333.337.search-card.all.click)

那么有什么办法让BST不退还成一条链呢？这里我们就可以使用平衡树了

![image.png](Splay/image.png)

接下来我们介绍Splay的各种操作

## 节点信息

```C++
struct node{
	int s[2],fa,v,cnt,size;
	//左右儿子,父亲,节点权值,值的数量,子树大小
	void init(int p1,int v1){
		fa=p1,v=v1;cnt=size=1;
	}
}tr[N];
```

## 重要操作：旋转

要求：保序（保证中序遍历顺序不变），信息正确

**右旋**

![image.png](Splay/image 1.png)

将原来x的父亲y作为x的儿子，然后将x的右儿子变成y的左儿子

**左旋**

![image.png](Splay/image 2.png)

**Code**

```C++
void rotate(int x){
	int y=t[x].fa,z=t[y].fa;
	int k=(tr[y].s[1]==x);//这里很重要!如果true,说明x为y的左儿子,应该继续左旋
	//以下代码左右旋通用,我们以右旋为例
	tr[y].s[k]=tr[x].s[k^1];//将y的左儿子设置为x的右儿子(1)
	tr[tr[y].s[k]].fa=y;
	tr[x].s[k^1]=y;//将x的右儿子设置为y(2)
	tr[y].fa=x;
	tr[z].s[(tr[z].s[1]==y)]=x;//自动判断原来的y是z的左/右儿子
	tr[x].fa=z;//更新z的儿子,x的新父亲(3)
	pushup(x);pushup(y);//别忘了修改信息
}
```

如图

![image.png](Splay/image 3.png)

**Pushup**

```C++
void pushup(int x){//由左右儿子信息更新父亲的信息
	tr[x].size=tr[tr[x].s[0]].size/儿子的size(子树和)加上自己的大小
	//size存的是以x为根节点的子树的信息
}
```

## 核心操作：splay

目的：访问一个节点并且将其旋转到根节点

我们使用以下三种方法的组合来实现目的

![image.png](Splay/image 4.png)

问题：为什么我们不仅仅用单旋呢？

结合实例，我们发现，如果仅仅用单旋，二叉树的状况不会得到改善。

![image.png](Splay/image 5.png)

**Code**

```C++
void splay(int x,int k){//将x旋转到k下方
	while(tr[x].fa!=k){
		int y=tr[x].fa,z=tr[y].fa;
		//第一次旋转,要分情况
		if(z!=k)//若z=k,说明只需要做单旋了(说明目标点就为x的父亲)
			if((tr[y].s[0]==x)^(tr[z].s[0]==y)){//若y为z左,x为y左或者y为z右,x为y右,异或和均为0,表示是直线型
				rotate(x);
			}else rotate(y);
		//第二次旋转,都是旋转x 
		rotata(x);
	}
	if(k==0)rt=x;//如果k=0说明x被旋转到了根节点
}
```

## 其他操作

### find查找

目标：查找值v所在的节点并且将其旋转至根节点

```C++
void find(int v){
	int x=rt;
	while(tr[x].s[v>tr[x].v]&&v!=tr[x].v){//如果:找到的点没有符合要求的儿子(即走到了最靠近v的点,但v是不存在的)或者找到了v
		x=tr[x].s[v>tr[x].v];//如果v>tr[x].v,那么就走右儿子
	}
	splay(x,0);//将v或者最靠近v的那个点旋转到根节点
}
```

### getlower求前驱

```C++
int getlower(int v){
	find(v);
	int x=rt;//rt即v
	if(tr[x].v<v)return x;//若true,说明在find中就没有找到v,而是找到了最靠近v的点,若这个点的v<v,那么它就是v的前驱
	x=tr[x].s[0];//先走到v的左子树
	while(tr[x].s[1])x=tr[x].s[1];//然后不断走右儿子
	return x;
}
```

**解说**

![image.png](Splay/image 6.png)

我们要找到小于根节点v的最大值，那么根据BST性质，我们就先往v的左儿子走，现在当前点的子树都是<v的了，在其中找最大的，即不断往右儿子走

### getbigger求后继

原理与前驱相同

**Code**

```C++
int getbigger(int v){
	find(v);
	int x=rt;//rt即v
	if(tr[x].v>v)return x;//若true,说明在find中就没有找到v,而是找到了最靠近v的点,若这个点的v>v,那么它就是v的后继
	x=tr[x].s[1];//先走到v的右子树
	while(tr[x].s[0])x=tr[x].s[0];//然后不断走左儿子
	return x;
}
```

### Del删除节点

我们考虑到直接删除节点比较麻烦，但如果这个点是一个叶子节点就简单多了，我们又观察到，在下图这个常见的结构中，son节点既满足son>x又满足son<y。在前面我们已经可以求出son的前驱和后继，那么只要我们把son的前驱和后继向上旋转，就可以把son移到叶子节点的位置，就方便删除了

![image.png](Splay/image 7.png)

**Code**

```C++
void del(int v){
	int pre=getlower(v),nxt=getbigger(v);
	splay(pre,0);splay(nxt,pre);//将pre旋转到根节点,将nxt旋转到pre的下方,只要就构造出了如图所示的图像
	int del=tr[nxt].s[0];
	if(tr[del].cnt>1)tr[del].cnt--,splay(del,0);//这里进行splay主要是为了pushup
	else tr[nxt].s[0]=0,splay(nxt,0);//直接清空nxt的左儿子,并且更新它
}
```



注意，因为删除一个节点需要求出它的前驱和后继，我们就在平衡树中插入一个无穷小和一个无穷大，重要就能保证一定能找到任意一个点的前驱和后继

### Getrank查询排名

~~直接将v旋转到根节点，然后返回其左子树的大小即可~~ 会被HAck

```C++
int getrank(int v){
	// find(v);
	// return tr[tr[rt].s[0]].size;//没有加上1的原因是树上还有一个无穷小的节点
    //不能用上面的代码！！会WA一个点
	insert(v);
    int res=tr[tr[rt].s[0]].size;
    del(v);
    return res;
}
```

### Getval查询权值

```C++
int getval(int k){//查询第k小的点的权值
	int x=rt;
	k++;//因为有一个无穷小,所以实际上要查询的点是第k+1小的
	while(1){
		if(tr[tr[x].s[0]].size/走右边
			x=tr[x].s[1];k-=tr[tr[x].s[0]].size+tr[x].cnt;
		}else{
			if(tr[[x].s[0]].size>=k)x=tr[x].s[0];//走左边,若为true说明第k小的在左边,否则说明即不是右边,左边也没有,那就是它自己了
			else break;
		}
		
	}
	splay(x);//splay仅仅是用来整理平衡树的,防止其退化为链
	return tr[x].v;
}
```

### Insert插入一个值

**Code**

```C++
void insert(int v){
	 int x=rt,p=0;
	 while(x&&tr[x].v!=v){
	 	p=x;x=tr[x].s[v>tr[x].v];//走到最靠近v的位置，如果v存在那么x停在v上，否则x走到满足v插入的位置的空节点
	 }
	 if(x)tr[x].cnt++;//x原来就存在了
	 else{//添加一个节点
	 	x=++idx;
	 	tr[p].s[v>tr[p].v]=x;//p是x的父节点1
	 	tr[x].init(p,v);//初始化这个点，父亲为p，权值为v
	 }
	 splay(x,0);//splay防止退化成链
}
```

## 完整代码`AC`

```C++
/*
Code by Ntsc_Hodaka
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
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
const int N = 1e7 + 5;
const int M = 1e7 + 5;
const int INF = 1e9 + 5;
const double eps=1e-7;

struct node{
	int s[2],fa,v,cnt,size;
	//左右儿子,父亲,节点权值,值的数量,子树大小
	void init(int p1,int v1){
		fa=p1,v=v1;cnt=size=1;
	}
}tr[N];

bool f1;
///----///
int n,rt,idx;
///----///
bool f2;

void pushup(int x){//由左右儿子信息更新父亲的信息
	tr[x].size=tr[tr[x].s[0]].size/儿子的size(子树和)加上自己的大小
	//size存的是以x为根节点的子树的信息
}


void rotate(int x){
	int y=tr[x].fa,z=tr[y].fa;
	int k=(tr[y].s[1]==x);//这里很重要!如果true,说明x为y的左儿子,应该继续左旋
	tr[y].s[k]=tr[x].s[k^1];//将y的左儿子设置为x的右儿子(1)
	tr[tr[x].s[k^1]].fa=y;
	tr[x].s[k^1]=y;//将x的右儿子设置为y(2)
	tr[y].fa=x;
	tr[z].s[(tr[z].s[1]==y)]=x;//自动判断原来的y是z的左/右儿子
	tr[x].fa=z;//更新z的儿子,x的新父亲(3)
	pushup(y);pushup(x);//别忘了修改信息
}

void splay(int x,int k){//将x旋转到k下方
	while(tr[x].fa!=k){
		int y=tr[x].fa,z=tr[y].fa;
		//第一次旋转,要分情况
		if(z!=k)//若z=k,说明只需要做单旋了(说明目标点就为x的父亲)
			if((tr[y].s[0]==x)^(tr[z].s[0]==y)){//若y为z左,x为y左或者y为z右,x为y右,异或和均为0,表示是直线型
				rotate(x);
			}else rotate(y);
		//第二次旋转,都是旋转x 
		rotate(x);
	}
	if(k==0)rt=x;//如果k=0说明x被旋转到了根节点
}


void find(int v){
	int x=rt;
	while(tr[x].s[v>tr[x].v]&&v!=tr[x].v){//如果:找到的点没有符合要求的儿子(即走到了最靠近v的点,但v是不存在的)或者找到了v
		x=tr[x].s[v>tr[x].v];//如果v>tr[x].v,那么就走右儿子
	}
	splay(x,0);//将v或者最靠近v的那个点旋转到根节点
}

int getlower(int v){//注意返回的是下标！
	find(v);
	int x=rt;//rt即v
	if(tr[x].v<v)return x;//若true,说明在find中就没有找到v,而是找到了最靠近v的点,若这个点的v<v,那么它就是v的前驱
	x=tr[x].s[0];//先走到v的左子树
	while(tr[x].s[1])x=tr[x].s[1];//然后不断走右儿子
    splay(x,0);
	return x;
}


int getbigger(int v){//注意返回的是下标！
	find(v);
	int x=rt;//rt即v
	if(tr[x].v>v)return x;//若true,说明在find中就没有找到v,而是找到了最靠近v的点,若这个点的v>v,那么它就是v的后继
	x=tr[x].s[1];//先走到v的右子树
	while(tr[x].s[0])x=tr[x].s[0];//然后不断走左儿子
    splay(x,0);
	return x;
}

void insert(int v){
	 int x=rt,p=0;
	 while(x&&tr[x].v!=v){
	 	p=x;x=tr[x].s[v>tr[x].v];//走到最靠近v的位置，如果v存在那么x停在v上，否则x走到满足v插入的位置的空节点
	 }
	 if(x)tr[x].cnt++;//x原来就存在了
	 else{//添加一个节点
	 	x=++idx;
	 	if(p)tr[p].s[v>tr[p].v]=x;//p是x的父节点1
	 	tr[x].init(p,v);//初始化这个点，父亲为p，权值为v
	 }
	 splay(x,0);//splay防止退化成链
}

void del(int v){
	int pre=getlower(v),nxt=getbigger(v);
	splay(pre,0);splay(nxt,pre);//将pre旋转到根节点,将nxt旋转到pre的下方,只要就构造出了如图所示的图像
	int del=tr[nxt].s[0];
	if(tr[del].cnt>1)tr[del].cnt--,splay(del,0);//这里进行splay主要是为了pushup
	else tr[nxt].s[0]=0,splay(nxt,0);//直接清空nxt的左儿子,并且更新它
}


int getrank(int v){
	// find(v);
	// return tr[tr[rt].s[0]].size;//没有加上1的原因是树上还有一个无穷小的节点
    //不能用上面的代码！！会WA一个点
	insert(v);
    int res=tr[tr[rt].s[0]].size;
    del(v);
    return res;
}

int getval(int k){//查询第k小的点的权值
	int x=rt;
	k++;//因为有一个无穷小,所以实际上要查询的点是第k+1小的
	while(1){
        if(k<=tr[tr[x].s[0]].size)x=tr[x].s[0];//如果k<=左儿子的size,那么就走左儿子
		else if(tr[tr[x].s[0]].size/走右边
			k-=tr[tr[x].s[0]].size/!!
		}else{
			// if(tr[y].size>=k)x=y;//走左边,若为true说明第k小的在左边,否则说明即不是右边,左边也没有,那就是它自己了
			 break;
		}
		
	}
	splay(x,0);//splay仅仅是用来整理平衡树的,防止其退化为链
	return tr[x].v;
}



signed main() {
    // freopen("P5431_1.in", "r", stdin);
    // freopen("chfran.out", "w", stdout);
    cin>>n;
    insert(-INF);insert(INF);//插入两个无穷小的点
	for(int i=1;i<=n;i++){
		int opt,x;
		cin>>opt>>x;
		if(opt==1){
			insert(x);
		}if(opt==2){
			del(x);
		}if(opt==3){
			cout<<getrank(x)<<endl;
		}if(opt==4){
			cout<<getval(x)<<endl;
		}if(opt==5){
			cout<<tr[getlower(x)].v<<endl;
		}if(opt==6){
			cout<<tr[getbigger(x)].v<<endl;
		}
	}
    
    
    return 0;
}

/*
不要把&&写成&啊！TT
*/
```

