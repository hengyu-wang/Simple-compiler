#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;
int main()
{
//    char str[100];
//    double f;
//    str[0]='2';
//    str[1]='1';
//    str[2]='1';
//    str[3]='#';
//    cout << f << endl;
//    sscanf(str,"%lf", &f);
//    cout << f << endl;
    vector<int> a;
//    cout << a[0] << endl;
    a.push_back(1);
    cout << a.size() << endl;
    a.clear();
    cout << a.size() << endl;
    cout << a[0]<<endl;
    return 0;
}