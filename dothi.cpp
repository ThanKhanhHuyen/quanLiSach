#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

#define MAX 20

struct DoThiTrongSo{
    int n;
    float D[MAX][MAX];
};

struct Canh{
    int dau;
    int cuoi;
    int value;
};

struct DoThiCanh{
    int m;
    Canh ds[MAX];
};

void nhapCanh(Canh &canh){
    int d, c, v;
    cin>>
}