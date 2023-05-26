#include<iostream>
#include <type_traits>

using namespace std;

class Int
{
    int _value;
public:
    Int(int x=0) :_value(x) {cout<<"Create Int: "<<_value<<endl;}
    Int(const Int& it):_value(it._value) {cout<<"Copy Create Int: "<<this<<endl;}
    Int& operator=(const Int& it)
    {
        if(this==&it) return *this;
        _value=it._value;
        cout<<this<<" = "<< &it <<endl;
        return *this;
    }
    ~Int() {cout<<"Destroy Int: "<<_value<<endl;}

    void SetValue(int x) {_value=x;}
    Int& SetValue1(int x) 
    {
        _value=x;
        return *this;////需要函数结束时，当前对象仍然存在，才能以引用返回or返回地址(生存期)
 	}
    int GetValue()const {return _value;}
    void ShowValue()const {cout<<_value<<endl;}
};

/*
//对比对象的生存期
Int fun(int x)
{
    Int tmp;
    return tmp;
}
int main1()
{
    Int(1).ShowValue();//不具名对象，右值，生存期只在该语句执行期间，执行完该语句后就会被销毁
    fun(2).ShowValue();//函数结束后被销毁
    Int(50).SetValue1(200).ShowValue();//可以打印，此行语句结束后被销毁
    return 0;
}

//左值引用和右值引用
//内置类型



int main()
{
    int a=10;
    const int b=20;

    int& ra=a;
    //int& rb=b;//error,可以通过b的引用rb来修改常量b
    const int& rb=b;//常引用，向下兼容引用一切，保证值不会被修改
    const int& rx=10;//常性左值引用可以引用左值(常性与普通都可以)、右值

    //int& rc=10;//error，左值引用不能引用右值10
    int&& rc=10;//右值引用，没有引用的引用
    //int&& rra=a;//error，右值引用不能引用左值

    //区别
    int&& ry=10;
    ry+=100;//右值引用可以被改变
    //int tmp=10;   int&&ry=tmp;
    const int& rt=20;
    //int tmp=20;   const int &rb=tmp;
}
*/

//函数重载
/*
//void func(int a){};
//左值引用
void func(int& val)
{
    cout<<"L_value reference"<<endl;
}
//常量左值引用
void func(const int& val)
{
    cout<<"const Lvalue reference"<<endl;
}
//右值引用
void func(int &&val)
{
    cout<<"R_value reference"<<endl;
}

int main()
{
    int a=10;
    const int b=20;
    func(a);
    func(b);
    func(10);
    return 0;

}
*/

//函数返回值_内置类型
/*
//以值返回，构造一个将亡值返回
int func()
{
    int x=10;
    return x;
}
int main()
{
    int a=func();
    //int& b=func();//error,func返回值为一个将亡值(右值)
    const int& c=func();//右值可以取左值常引用
    int&& d =func();//ok，右值引用
    return 0;
}

//以左值引用返回
int& func()
{
    int x=10;
    return x;
}
int main()
{
    int a=func();
    int& b=func();
    const int& c=func();
    //int&& d=func();   无法将右值引用绑定到左值
    return 0;
}

//以右值引用返回
int&& func()
{
    return int(10);
    //return 10;
}

int main()
{
    int a=func();
    //int& b=func(); 无法将右值引用绑定到左值
    const int& c=func();
    int&& d=func();
    return 0;
}
*/

//类类型的右值引用
int main1()
{
    Int a=Int(1);
    //Int& b=Int(2);
    const Int& c=Int(3);
    Int&& d=Int(4);
    a.ShowValue();
    c.ShowValue();
    d.ShowValue();
    return 0;
}

//构造函数的隐式转换
int main2()
{
    const Int &a=1;
    //const int &a=(Int)(1);
    Int && b=2;
    //Int && b=(Int)(2);
    Int && c=b; //error
    Int &d=b;
    return 0;
}

//使用explicit明确关键，组织构造函数的隐式转换
/*
class Int
{
    int _value;
    public:
    explicit Int(int x=0) :_value(x)
    {
        cout<<"Create Int: "<<_value<<endl;
    }
};*/

//右值引用与函数重载
Int func()
{
    Int tmp(10);
    return tmp;
}

int main()
{
    Int a=func();
    Int& b=func();
    const Int& C=func();
    Int&& rd=func();
    return 0;
}

Int func(int x)
{
    Int tmp(x);
    return tmp;
}

int main4()
{
    Int a = func(1);//优化：return的tmp直接构建了a本身，省略构建将亡值对象
    /*
    Int a;
    a=func();	//这样先构建一个将亡值对象tmp，在构建一个对象a，然后把tmp赋值给a
    */
    //Int& b = func(2);//error,返回一个将亡值对象(右值)
    const Int& c = func(3);//const固定将亡值对象，直到主函数结束时在销毁释放
    Int&& rd = func(4); //再再主函数栈帧中固定一个将亡值对象
    return 0;
}
/*
Int &func(int x)
{
    Int tmp(x);
    return tmp;//以引用&返回，不构建一个将亡值对象，直接将tmp返回给所接受的对象，func函数结束后tmp对象就直接被销毁
}

int main()
{
    Int a = func(1);//用tmp初始化a之后，tnp已经被销毁
    //Int a=*func(1);	实际执行了解引用
    
    //b、c引用的是一个已经被销毁释放的对象
    Int& b = func(2);//
    const Int& c = func(3);
    //Int&& rd = func(4);//error，以&返回则为左值不能以右值引用接收 
    return 0;
}
*/

//以右值引用返回
/*
Int&& func(int x)
{
	//Int tmp(x);
    //return tmp;//error,tmp是一个左值，不能以右值引用接收
    return Int(x);//ok,不具名对象为右值，可以被右值引用接收。此不具名对象构建在func()函数的栈帧之中，不在主函数的栈帧中
    
}

int main()
{
    Int a=func(1);
    a.ShowValue();//fun函数结束之后，已经被销毁
    return 0;
}
*/