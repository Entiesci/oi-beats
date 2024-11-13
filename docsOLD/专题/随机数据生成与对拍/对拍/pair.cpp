#include <bits/stdc++.h>
using namespace std;
int main(){
    int t = 0;
    while(true){
      /*linux//windows*/
        printf("test #%d: ", ++t);
        system("make.exe > data.in");
//        cerr<<"OK1"<<endl;
        system("std.exe < data.in > data.ans");
//        cerr<<"OK2"<<endl;
        system("code.exe < data.in > data.out");
//        cerr<<"OK3"<<endl;
        if(system("fc data.out data.ans > data.log")){
            //system("fc data.out data.ans > data.log");
            printf("WA\n");
            break;
        }else{
            printf("AC\n");
        }
    }
	return 0;
}