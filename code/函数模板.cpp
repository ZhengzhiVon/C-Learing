#include<iostream>
using namespace std;

template<class T>
T my_max(T a,T b)
{
    return a>b?a:b;
}

int main1()
{
    my_max(12, 23);
    my_max('a', 'b');
    my_max(12.23, 34.45);
    return 0;
}
/*
template <typename T,typename E>//定义一个模板参数列表

template<class F>//定义一个模板参数列表

template<typename G>////定义一个模板参数列表
*/

template<typename T>//定义一个模板参数列表
bool Compare(T a,T b)
{
    cout<<"template compare" <<endl;
    return a > b;
}
int main()
{
    Compare(10, 20);
    Compare<int>(10, 20);
    return 0;
}