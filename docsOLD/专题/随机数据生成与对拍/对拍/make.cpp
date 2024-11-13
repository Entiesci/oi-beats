#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(time(0));
int randint(int r){
	int res=rnd();
//	cerr<<"res="<<res<<endl;
	res=abs(res);
    return res%(r)+1;
}
int main(){
    printf("%d %d\n", 10 ,10);
    srand(time(0));

    for(int i=2;i<=10;i++){
        cout<<i<<' '<<randint(i-1)<<endl;
    }


    for(int i=1;i<=10;i++){
        cout<<randint(10)<<' '<<randint(10)<<' '<<randint(10)<<' '<<randint(10)<<endl;
    }
    return 0;
}


