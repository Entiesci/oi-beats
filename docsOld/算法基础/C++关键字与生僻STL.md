C++关键字与生僻STL

|A – C|D – P|R – Z||
|-|-|-|-|
|`[alignas](https://en.cppreference.com/w/cpp/keyword/alignas)` (C+/xor_eq)`||

# STL函数

- `unique`去除容器中相邻的重复元素。`unique(ForwardIterator first, ForwardIterator last)`，返回值为指向 **去重后** 容器结尾的迭代器，原容器大小不变（多于的元素放在最后而不会消失）。与 `sort` 结合使用可以实现完整容器去重。返回值为指针，取地址后为unique后不同值的数量。





```C++
int n,m,p,q,T,a[N],ans;
signed main(){
	cin>>n;
	for(int i=2;i<=n+1;i++)cin>>a[i];
	sort(a+2,a+n+2);
	auto val=unique(a+2,a+n+2);
	
	cout<<"val="<<val<<endl;
	cout<<"*val="<<*val<<endl;
	cout<<"&val="<<&val<<endl;
	for(int i=1;i<=n;i++)cout<<a[i]<<' ';
}
```



```C++
5
1 1 2 3 4
val=0x7ff73a62a0a8
*val=4
&val=0x4318fff788
1 2 3 4 4
```

- `lower_bound` 在一个有序序列中进行二分查找，返回指向第一个 大于等于 x 的元素的位置的迭代器。如果不存在这样的元素，则返回尾迭代器。`lower_bound(v.begin(),v.end(),x)```。





```C++
int n,m,p,q,T,a[N],ans;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	cin>>m;
	auto val=lower_bound(a+1,a+n+1,m);
	cout<<"val="<<val<<endl;
	cout<<"*val="<<*val<<endl;
	cout<<"&val="<<&val<<endl;
    cout<<"val-a="<<val-a<<endl;
}
```



```C++
5
1 3 4 7 8
6
val=0x7ff76767a0a0
*val=7
&val=0x9e41bffb80
val-a=4
```

- `nth_element`：按指定范围进行分类，即找出序列中第mid 大的元素，使其左边均为小于它的数，右边均为大于它的数。`nth_element(v.begin(), v.begin() + mid, v.end(), cmp)` 或 nth_element(a + begin, a + begin + mid, a + end, cmp)。





```C++
int n,m,p,q,T,a[N],ans;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	cin>>m;
	nth_element(a+1,a+m+1,a+n+1);
	for(int i=1;i<=n;i++)cout<<a[i]<<' ';
}

```



```C++
5
3 7 6 4 1
3
3 1 4 6 7
```

- `next_permutation`，重新排列范围内的元素[第一，最后一个）返回按照**字典序排列**的下一个值较大的组合。返回值为bool，当有下一个排列可用时返回1，排列穷尽时返回0，如果继续运行则返回字典序最小的情况重新开始。





```C++
int n,m,p,q,T,a[N],ans;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	cin>>m;
	while(m--){
		next_permutation(a+1,a+n+1);
		for(int i=1;i<=n;i++)cout<<a[i]<<' ';
		cout<<'\n';
	}
}
```



```C++
5
1 2 3 4 5
6
1 2 3 5 4
1 2 4 3 5
1 2 4 5 3
1 2 5 3 4
1 2 5 4 3
1 3 2 4 5
```

- `rand()` 随机数

- [https://blog.csdn.net/onion23/article/details/118558454](https://blog.csdn.net/onion23/article/details/118558454)

# STL结构

## Set

使用Set便捷维护区间重叠问题

[www.luogu.com.cn](https://www.luogu.com.cn/problem/P2161)

## Rope

`rope`块状链表，用法同vector，删除x个元素`erase(pos,x)`,插入`insert(pos,v)`

## Bitset

不仅仅是01数组，还有更优秀的操作。和vector<bool>一样属于原生压位的。

好例题

[www.luogu.com.cn](https://www.luogu.com.cn/problem/P1441)


## union

以下代码

```C++
union node{
	int a;
	char b;
}s;

signed main(){
	cin>>s.a>>s.b;
	cout<<s.b<<endl<<s.a;
	
	return 0;
}

```

```C++
in: 456 c
out: c 99
```

即改变要求，会把其他的都变成改值对应类型的值。



