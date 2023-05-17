# Lambda表达式_0511



[参考](https://blog.csdn.net/qq_37085158/article/details/124626913?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522168431981616800226542449%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=168431981616800226542449&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~baidu_landing_v2~default-1-124626913-null-null.142^v87^control,239^v2^insert_chatgpt&utm_term=C%2B%2B%E4%B8%AD%E7%9A%84lambda%E8%A1%A8%E8%BE%BE%E5%BC%8F&spm=1018.2226.3001.4187)

## Lambda表达式概念

**lambda表达式**是C++11最重要也最常用的一个特性之一。利用lambda表达式可以**编写内嵌的匿名函数**，用以**替换独立函数或者函数对象**，并且使代码更可读。从本质上来讲，**lambda表达式只是一种语法糖**，因为所有其能完成的工作都可以用其它稍微复杂的代码来实现。

```c++
#include <algorithm>
#include <cmath>

void abssort(float* x, unsigned n) {
    std::sort(x, x + n,
        // Lambda expression begins
        [](float a, float b) {
            return (std::abs(a) < std::abs(b));
        } // end of lambda expression
    );
}

```

## 基本语法结构

```c++
[capture list] (parameters) mutable throw() -> return-type { function body }
//capture list是捕获列表，用于指定lambda表达式所捕获的变量；parameters是参数列表；mutable throw是可变规则/异常说明(可省略)；return-type是返回类型；function body是函数体。

//可变规格mutable修饰符， 默认情况下Lambda函数总是一个const函数，mutable可以取消其常量性。在使用该修饰符时，参数列表不可省略（即使参数为空）。
//异常说明，用于Lamdba表达式内部函数抛出异常。

int main()
{
    auto fa = [](int x)->int  {return x+x;};//可以看作一个函数fa
    cout<<fa(10)<<endl;//输出20
}
```

很多时候`lmabda`表达式的返回值非常明显，所以C++11中允**许省略lambda表达式的返回值定义**：

```c++
auto f=[](int a){return a+=1;};
//编译器会通过return语句自动推导出返回值类型
```

**初始化列表不能用于返回值的自动推导**：

```c++
auto x=[](){return {1,2};};	//error
//此时需要显式的给出具体返回值类型

auto f = [](int x, int y) { return {x, y}; };//error
auto f = [](int x, int y) -> std::initializer_list<int> { return {x, y}; };//ok

```

当lambda表达式**没有参数列表时，参数列表可以省略**：

```c++
auto f1=[](){return 1;};

auto f2=[]{return 1;};//ok	省略空参数列表
```

## 关于捕获列表[]

**[]捕获，作用域只针对于lambda表达式所在的函数的范围内。全局变量、全局对象不存在“捕获”的概念，因为都可以使用。**

### 简单例子

```c++
#include<iostream>
using namespace std;
//lambda表达式

//全局变量、全局对象不存在“捕获”的概念，因为都可以使用。
int g_max=10;

void funa()
{
    g_max=100;
}

void fun(int x)
{
    auto fa = []()->void {};//[]的捕获针对于fun函数范围内
    fa();
}

int main()
{
    auto fa = [](int x)->int    //[]的捕获针对于main主函数的范围内的局部变量(形参)
    {
        g_max+=10;//“捕获”不针对与全局变量
        return x+x;
    };//可以看作一个函数fa

    cout<<fa(10)<<endl;
}
```

### 捕获[]用法总结

- **全局变量不需要捕获就可以使用。**

- **`[ ]`不捕获任何变量。**
- **`[&]`捕获外部作用域中所有变量，并作为引用在函数体中使用（按引用捕获，包括`this`）。**
- **`[=]`捕获外部作用域中所有变量，并作为副本在函数体中使用（按值捕获，包括`this`）。**
- **`[-，&foo]`按值捕获外部作用域中所有变量，并按引用捕获`foo`变量。(`foo`为目标变量名)。**
- **`[bar]`按值捕获bar变量，同时不捕获其他变量。(只捕获一个变量，也可以使用`[&bar]`来以引用形式使用)。**
- **`[this]`捕获当前类中的this指针，让lambda表达式拥有和当前类成员函数同样的访问权限。如果已经使用了&或者=就默认添加此选项。捕获this的目的是可以在lambda中使用当前类的成员函数和成员变量。**
- **`[&, a, this]`表示以值传递的方式捕捉变量`a`和`this`，引用传递方式捕捉其它所有变量。不过捕捉列表不允许变量重复传递([=,a],[&,&this])**

### 捕获列表[]中的值捕获和引用&捕获

- **值捕获只能进行读取操作，lambda表达式在使用被捕获的外部对象或者局部变量时会创建一个副本，所以不能修改其原值。**
- **引用捕获时并不会创建一个原值副本，所以原值可以被直接修改。**

```c++
class Int
{
private:
    int value;
public:
    Int(int x=0):value(x) {cout<<"Create Int: "<<this<<endl;}
    ~Int() {cout<<"Destroy Int: "<<this<<endl;}
    Int(const Int &it):value(it.value) {cout<<"Copy Create Int:"<<this<<endl;}
    Int& operator=(const Int &it)
    {
        if(this!=&it)
        {
            value=it.value;
        }
        cout<<this<<"operator=() "<<&it<<endl;
        return *this;
    }
    void SetValue(int x)
    {
        value=x;
    }
    int GetValue() const
    {
        return value;
    }
};

void funa(int x,int y)
{
    int z=x+y;
    Int obja(10);

    auto fa=[](int a)->void 
    {
        //z=10; error
        //a=z;  error
        cout<<a<<endl;
    };
    //[]表示此lambda表达式不捕获函数funa中的任何一个变量z,x,y
    //捕获函数中的变量是不是相当于拷贝一份变量到栈中？yes下面已解决
    auto fb =[x,z]()->void
    {
        int a=z+x;//[x,z]声明捕获目标下x,z(按照值捕获)，故可以使用
        //值捕获只能进行读取操作，不能修改其值，此处的x,z是重新开辟的变量
        //z+=100;   error
        cout<<a<<endl;
    };
    fa(19);
    fb();

    //运行时只创建一个Int对象obja
}

void funb(int x,int y)
{
    int z=x+y;
    Int obja(10);//第一次构建一个obja对象，因为fa()中用到了外部对象obja，所以之后需要拷贝构造一个其副本
    Int objb(20);//虽然objb也被捕获，但是再fa()中并未用到，所以系统也不会调用拷贝构造函数构造其副本
    auto fa=[=]()->void
    {
        cout<<obja.GetValue()<<endl;
    };
    fa();//因为是[=]，值捕获此函数内的所有变量、对象，所需需要将obja复制一遍，即通过拷贝构造函数重新构造一个新的Int对象

    auto fb=[obja,x]()->void
    {
        obja.GetValue();
        //cout<<z<<endl; error   []只捕获了obja和x
        //z+=10; error  值捕获不能修改变量、对象值
    };
    
}
void func(int x,int y)
{
    int z=x+y;
    Int obja(10);
    auto fc=[&obja,&z]()->void
    {
        obja.GetValue();//以引用捕获，故不会调用拷贝构造函数构造副本，但是以引用捕获则可以在外部改动其值
        cout<<obja.GetValue()<<endl;
        cout<<z<<endl;//ok 以引用捕获
        z+=10;//ok 以引用捕获则可以修改变量、对象值
    };
    obja.SetValue(100);//引用捕获，修改了lambda表达式fc中的obja的值；若改成值引用[obja]，则会创建一个副本，原值不会被修改
    fc();
}
int main()
{
    funa(10,20);//输出19，40，但是只构造一个Int对象
    funb(10,20);//输出10，因为是值捕获，所以构造两个Int对象，调用1次构造和析构函数，再通过拷贝构造函数重新构造一个新的Int对象
    //总结当使用值捕获时，当函数内并未用到外部对象时，系统并不会拷贝构造一个其副本；但是当函数运行过程中捕获到外部对象且确实用到此外部对象时，则系统会调用拷贝构造函数复制一份其副本
    //Q：能否共用一份外部对象而不复制一个副本？为什么要设计一个引用的机制？
    func(10,20);//输出100，因为为引用捕获，所以函数内所使用到的对象的值可以被改变
    return 0;
}
```

#### mutable关键字

可变规格`mutable`修饰符， 默认情况下Lambda函数总是一个`const`函数，`mutable`可以取消其常量性。**在使用该修饰符时，参数列表不可省略（即使参数为空）。**

按值捕获得到的外部变量值是在lambda表达式定义时的值。此时所有
外部变量均被复制了一份存储在lambda表达式变量中。**此时虽然修改lambda表达式中的这些外部变量并不会真正影响到外部，我们却仍然无法修改它们。**

**修改按值捕获的外部变量，需要显式指明lambda表达式为`mutable`:**

```c++
int main()
{
	int a=0;
    auto f1=[=] {return a++;};//error 不能修改按值捕获的外部变量
    auto f2=[=]() mutable {return a++;};//ok
}
```

## Lambda表达式的类型/实现

