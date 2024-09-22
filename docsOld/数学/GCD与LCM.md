# GCD与LCM

## **最大公因数**





### 辗转相除法

辗转相除法求`gcd(a,b)`算法实现

```C++
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
```

压行后（不知道对不对）

```C++
int gcd(int a, int b) {return b?gcd(b, a % b):a;}
```

### 更相减损术

gcd(a,b)=gcd(a-b,b)，递归条件你为a-b=0时返回b。

```C++
int gcd(int a,int b){
    if(a<b)swap(a,b);
    if(!b)return a;
    if((a&1)==0||(b&1)==0)return gcd(a>>1,b>>1)<<1;
    if((a&1)==0){a>>=1;return gcd(a,b);}
    if((b&1)==0){b>>=1;return gcd(a,b);}
    return gcd(a-b,b);
}
```



### STL

```C++
__gcd(int a,int b)
```



![v2-59ac8410625b8f4f90aa9aa07fd5e55a_b.jpg](GCD与LCM/v2-59ac8410625b8f4f90aa9aa07fd5e55a_b.jpg)

## **最小公倍数**

两个或多个整数公有的倍数叫做它们的公倍数，其中除0以外最小的一个公倍数就叫做这几个整数的最小公倍数。整数a，b的最小公倍数记为 $[a,b] $，同样的，a，b，c的最小公倍数记为$[a,b,c]$，多个整数的最小公倍数也有同样的记号。

与最小公倍数相对应的概念是最大公约数，a，b的最大公约数记为 **$(a,b)$** 。关于最小公倍数与最大公约数，我们有这样的定理： **$(a,b)\times[a,b]=ab$** ($a,b$均为整数)。



