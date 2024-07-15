# Treap

```C++
struct Treap {//treap模板，有需要可以copy
    int tot, rt;
    struct node {
        int val, ch[2], rd, cnt, sz;
        void Init(int Val) { val = Val, rd = rand() % 233; sz = cnt = 1; ch[1] = ch[0] = 0; }
    }tr[N];
    void pushup(int nod) { tr[nod].sz = tr[tr[nod].ch[0]].sz + tr[tr[nod].ch[1]].sz + tr[nod].cnt; }
    void rotate(int &nod, int d) {
        int k = tr[nod].ch[d]; tr[nod].ch[d] = tr[k].ch[d ^ 1]; tr[k].ch[d ^ 1] = nod;
        pushup(nod); pushup(k); nod = k; 
    }
    void ins(int &nod, int val) {
        if (!nod) { nod = ++ tot; tr[nod].Init(val); }
        else {
            tr[nod].sz ++; 
            if (tr[nod].val == val) { tr[nod].cnt ++; return; }
            int d = val > tr[nod].val; 
            ins(tr[nod].ch[d], val);
            if (tr[nod].rd > tr[tr[nod].ch[d]].rd) rotate(nod, d);
        }
    }
    void del(int &nod, int val) {
    	if (!nod) return;
    	if (tr[nod].val == val) {
    		if (tr[nod].cnt > 1) { tr[nod].cnt --, tr[nod].sz --; return; } 
    		int d = tr[tr[nod].ch[0]].rd > tr[tr[nod].ch[1]].rd;
    		if (!tr[nod].ch[1] || !tr[nod].ch[0]) nod = tr[nod].ch[1] + tr[nod].ch[0];
    		else rotate(nod, d), del(nod, val);
		}
		else tr[nod].sz --, del(tr[nod].ch[tr[nod].val < val], val);
	}
    int pre(int nod, int val) {
        if (!nod) return -inf;
        if (tr[nod].val > val) return pre(tr[nod].ch[0], val);
        else return max(tr[nod].val, pre(tr[nod].ch[1], val));
    }
    int suc(int nod, int val) {
        if (!nod) return inf;
        if (tr[nod].val < val) return suc(tr[nod].ch[1], val);
        else return min(tr[nod].val, suc(tr[nod].ch[0], val));
    }
    int Get_Min(int nod) {
    	if (!nod) return inf;
    	return min(tr[nod].val, Get_Min(tr[nod].ch[0]));
	}
}tp;
```

