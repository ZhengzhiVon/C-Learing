# Lambda表达式_0518(补充完毕)

[参考](https://blog.csdn.net/qq_37085158/article/details/124626913?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522168431981616800226542449%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=168431981616800226542449&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~baidu_landing_v2~default-1-124626913-null-null.142^v87^control,239^v2^insert_chatgpt&utm_term=C%2B%2B%E4%B8%AD%E7%9A%84lambda%E8%A1%A8%E8%BE%BE%E5%BC%8F&spm=1018.2226.3001.4187)

[TOC]

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

lambda表达式的类型在C++11中被称为**闭包类型（ClosureType）**。它是一个特殊的，匿名的非nunion的类类型。编译器会把一个Lambda表达式生成一个匿名类的**匿名对象**，并在类中**重载函数调用运算符**，实现了一个`operator()`方法。因此，我们可以认为它是一个带有`operatoro()`的类，即仿函数。

```c++
auto print = []{cout << "Hello World!" << endl; };

//编译器翻译上述lambda表达式
class print_class
{
public:
	void operator()(void) const
	{
		cout << "Hello World!" << endl;
	}
};
// 用构造的类创建对象，print此时就是一个函数对象
auto print = print_class();

```

### 闭包对象

在 C++ 中，lambda 表达式实际上是一个函数对象，也就是闭包对象。闭包对象是一个能够捕获其所在作用域中变量的对象。当一个 lambda 表达式被创建时，编译器会生成一个闭包对象来保存 lambda 表达式中捕获的变量。闭包对象包含了一个可调用的函数对象和一个捕获列表，用于保存捕获的变量。

闭包对象的类型是由编译器自动推导的，它通常是一个未命名的类，该类包含了 lambda 表达式中的代码和捕获的变量。当 lambda 表达式被调用时，闭包对象的 operator() 函数会被调用，从而执行 lambda 表达式中的代码。

除了捕获列表中的变量，闭包对象还可以包含一些成员变量和成员函数，用于支持 lambda 表达式中的其他操作。例如，可以在闭包对象中定义一个成员函数，用于执行 lambda 表达式中的某些操作。

### lambda表达式与函数指针

**可以使用`std:function`和`std:bind`来存储和操作lambda表达式:**

```c++
int main()
{
	int x=0;
    std::function<int(int)> f1=[](int a) {return a;};
    std::function<int(void)> f2=std::bind([](int a){return a;},123);
    x=f1(10);	//x=10
    x=f2();		//123
    return 0;
}
```

对**于没有捕获任何变量的lambda表达式，可以转换成一个普通的函数指针：**

```c++
typedef void (*Ptr)(int);//定义一个函数指针类型Ptr，指向一个以int为参数，返回为void的函数
//不能将不同类型的 lambda 表达式相互赋值

int main()
{
    int a=10,b=20;
    auto f1=[](int a)->void {cout<<a<<endl;};
    auto f2=[](int x)->void {cout<<x+10<<endl;};
    //auto f3=[=]()->int {return a++;};           //error,因为f3没有使用mutable修饰符，不能修改捕获的变量
    auto f4=[=]()mutable->int {return a++;};    //ok
    auto f5(f1);    //ok
    //f1=f2;  //error,//将f2赋值给f1，产生编译错误，因为f1和f2的类型不同
    Ptr p1=f1;  //ok
    auto f6=[=](int x)->void {cout<<"hello"<<endl;};
    //Ptr p2=f4;  //error,将f4赋值给函数指针p2，产生编译错误，因为f4的类型和Ptr不匹配
}
```

lambda 表达式 `f` 的类型是 `int (*)(int)`，它与函数指针类型 `func_t` 相同。这意味着，lambda 表达式可以像函数指针一样使用，可以将其存储在函数指针变量中，也可以将其作为参数传递给接受函数指针类型参数的函数。

```c++
int main1()
{
    // 定义一个函数指针类型 func_t，它指向一个接受一个 int 类型参数并返回一个 int 类型值的函数
    using func_t = int (*)(int);

    //声明一个lambda表达式f，它接受一个int类型参数a，并返回a
    func_t f = [](int a) -> int { return a; };

    //将f应用于123，并将结果存储在x中
    int x = f(123); //x的值为123

    cout << typeid(f).name() << endl; // 输出 int(__cdecl*)(int);

    return 0;
}
```

**lambda表达式可以说是就地定义仿函数闭包的“语法糖”。**它的捕获列表捕获住的任何外部变量，最终均会变为闭包类型的成员变量。**而一个使用了成员变量的类的`operator()`，如果能直接被转换为普通的函数指针，那么lambda表达式本身的this指针就丢失掉了。**而没有捕获任何外部变量的lambda表达式则不存在这个问题。

这里也可以很自然地解释为何按值捕获无法修改捕获的外部变量。因为按照C++标准，lambda表达式的`operator()`默认是`const`的。一个`const`成员函数是无法修改成员变量的值的。而`mutable`的作用，就在于取消`operator()const`。

需要注意的是，**没有捕获变量的lambda表达式可以直接转换为函数指针，而捕获变量的lambda表达式则不能转换为函数指针。**

```c++
typedef void (*Ptr)(int);// 定义函数指针类型 Ptr，它指向一个接受一个 int 类型参数并返回 void 的函数

Ptr p=[](int *p) {delete p;};
//ok,没有状态(没有捕获)的lambda表达式可以直接转换为函数指针

Ptr p1=[&](int *p) {delete p;};
//error,有状态(捕获了变量)的lambda表达式不能直接转换为函数指针。
```

**lambda 表达式可以像函数指针一样使用，可以将其存储在函数指针变量中，并将其作为参数传递给接受函数指针类型参数的函数。此外，lambda 表达式还可以使用捕获列表来访问外部变量。**

## C++仿函数与lambda

### 仿函数

[仿函数参考](https://blog.csdn.net/YGG12022/article/details/124043116)

仿函数（Functor）又称为函数对象（Function Object）**是一个能行使函数功能的类。**

仿函数的语法几乎和我们普通的函数调用一样，不过作**为仿函数的类，都必须重载 operator() 运算符。**仿函数类的重载函数调用运算符必须是公有的，并且返回值类型和参数列表可以自由定义。**当仿函数被调用时，实际上是调用了重载的函数调用运算符。**

如果要将某种“操作”当做算法的参数，一般有两种方法：

（1）先将该“操作”设计为一个函数，再将**函数指针**当做算法的一个参数。此方法扩展性较差，当函数参数有所变化，则无法兼容旧的代码

（2）将该“操作”设计为一个仿函数（就语言层面而言是个 class），再以该仿函数产生一个对象，并以此对象作为算法的一个参数。使用仿函数，写一个简单类，除了维护类的基本成员函数外，**只需要重载 operator() 运算符** 。这样既可以免去对一些公共变量的维护，也可以使重复使用的代码独立出来，以便下次复用。而且相对于函数更优秀的性质，仿函数还可以进行依赖、组合与继承等，这样有利于资源的管理。

#### 仿函数举例：拼接字符串

```c++
class StringAppend {
public:
    //接受一个字符串作为构造函数参数
    explicit StringAppend(const string& str) : ss(str){}
    void operator() (const string& str) const {
         cout << str << ' ' << ss << endl;
    }//将重载的函数调用运算符中将传入的字符串和构造函数中的字符串拼接起来输出
private:
    const string ss;
};
 
int main() {
    StringAppend myFunctor2("and world!");
    myFunctor2("Hello");//输出Hello and world!
}
```

#### 调用for_each函数将vector中的偶数打印出来

仿函数实现&lambda函数实现

```c++
//设计仿函数，调用for_each函数将vector中的偶数打印出来
class CoountEven
{
    int &count_;
public:
    CountEven(int &count):count_(count) {}//构造函数，初始化计数器
    void operator()(int val)    //重载函数调用符
    {
        if(!(val & 1))  //val%2==0
        {
            ++count_;
        }
    }
};

int main()
{
    std::vector<int> v={1,2,3,4,5,6};
    int even_count=0;//偶数计数器
    for_each(v.begin(), v.end(), CountEven(even_count));//遍历v并统计偶数个数
    cout<<"the number of even is "<<even_count<<even_count<<endl;//输出3
    return 0;
}

//使用lambda表达式实现
int main()
{
    std::vector<int> v={1,2,3,4,5,6};
    int even_count=0;
    for_each(v.begin(), v.end(), [&even_count](int val){
        if(val%2==0)
        {
            ++even_count;
        }
    });
    std::cout<<"the number of even is "<<even_count<<std::endl;
    return 0;
}
```

#### 补充：for_each()函数

```c++
template<class InputIt, class UnaryFunction>
UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f);
```

`for_each` 是 C++ STL 中的一个算法，它可以遍历一个序列，并对其中的每个元素执行指定的操作。具体来说，`for_each` 接受两个迭代器参数，表示要遍历的序列的范围，以及一个函数对象参数，表示要对序列中的每个元素执行的操作。

**函数对象可以是一个普通函数、一个函数指针、一个 Lambda 表达式或一个仿函数（即重载了函数调用运算符 `operator()` 的类对象）。`for_each` 会依次将序列中的每个元素传递给函数对象，让其执行操作。**

**使用 `for_each` 算法和 Lambda 表达式来遍历一个整数序列，并对其中的每个元素进行平方操作：**

```c++
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> nums{1, 2, 3, 4, 5};

    // 使用 Lambda 表达式对序列中的每个元素进行平方操作
    std::for_each(nums.begin(), nums.end(), [](int& n){ n *= n; });

    // 输出平方后的序列
    for (auto n : nums)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;//输出1 4 9 16 25

    return 0;
}

```

**注意：`for_each` 并不保证对序列中的元素按顺序进行操作。如果需要按顺序执行操作，可以使用 `std::for_each_n` 算法，它可以指定要遍历的元素个数。**

### Lambda表达式的应用

#### `count_if()`应用

```c++
//查找大于5小于10的元素的个数
int count = std::count_if(vec.begin(),vec.end(),[](int x){return x>5&&x<10;});

//查找大于10的元素的个数
int count = std::count_if(vec.begin(),vec.end(),[](int x){return x>10;};
```

使用lambda表达式的修改量是非常小的，清晰度也很好。lambda和std:function的效果是一样的，代码还更简洁了。**一般情况下可以直接用lambda来代替function，但还不能完全替代，因为还有些老的库，比如boost的一些库就不支持lambda，还需要function。**

C++11引入函数式编程的概念中的lambda，让代码更简洁，更灵活，也更强大，并提高了开发效率，提高了可维护性。

#### `remove_if`应用实例

```
std::vector<int> vec_data = {1, 2, 3, 4, 5, 6, 7, 8, 9};
int x = 5;
vec_data.erase(std::remove_if(vec.date.begin(), vec_data.end(), [](int i) { 
    return n < x;}), vec_data.end());

std::for_each(vec.date.begin(), vec_data.end(), [](int i) { 
    std::cout << i << std::endl;});

```

#### `sort`函数

```c++
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void)
{
    int data[6] = { 3, 4, 12, 2, 1, 6 };
    vector<int> testdata;
    testdata.insert(testdata.begin(), data, data + 6);

    // 对于比较大小的逻辑，使用lamdba不需要在重新定义一个函数
    sort(testdata.begin(), testdata.end(), [](int a, int b){ 
        return a > b; });

    return 0;
}

```

#### Lamdba表达式应用于多线程场景

```c++
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

int main()
{
    // vector 容器存储线程
    std::vector<std::thread> workers;
    for (int i = 0; i < 5; i++) 
    {
        workers.push_back(std::thread([]() 
        {
            std::cout << "thread function\n";
        }));
    }
    std::cout << "main thread\n";

    // 通过 for_each 循环每一个线程
    // 第三个参数赋值一个task任务
    // 符号'[]'会告诉编译器我们正在用一个匿名函数
    // lambda函数将它的参数作为线程的引用t
    // 然后一个一个的join
    std::for_each(workers.begin(), workers.end(), [](std::thread &t;) 
    {
        t.join();
    });

    return 0;
}

std::mutex mutex;
std::condition_variable condition;
std::queue<std::string> queue_data;

std::thread threadBody([&]{
	std::unique_lock<std::mutex> lock_log(mutex);
	condition.wait(lock_log, [&]{
		return !queue_data.front();
	});
	std::cout << "queue data: " << queue_data.front();
	lock_log.unlock();
});

queue_data.push("this is my data");
condition.notity_one();

if(threadBody.joinable())
{
	threadBody.join();
}

```

## Lamdba表达式应用于函数指针与function

```c++
#include <iostream>
#include <functional>
using namespace std;

int main(void)
{
    int x = 8, y = 9;
    auto add = [](int a, int b) { return a + b; };
    std::function<int(int, int)> Add = [=](int a, int b) { return a + b; };

    cout << "add: " << add(x, y) << endl;
    cout << "Add: " << Add(x, y) << endl;

    return 0;
}

```

