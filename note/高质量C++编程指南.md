# 高质量C++/编程指南

[TOC]

# 第一章 文件结构

```
.h			头文件：保存程序的声明
.c/.cpp		定义文件：保存程序的实现
```

## 1.1 版权和版本的声明

- 版权信息。
- 文件名称，标识符，摘要。
- 当前版本号，作者/修改这，完成日期。
- 版本历史信息。

```cpp
/*
*Copyright	版权信息	All rights reserved
*
*文件名称：Learning.h
*文件标识：见配置管理计划书
*摘要：记录C++/C学习笔记
*
*当前版本：1.1
*作者：VonZhengzhi
*完成日期：2023.10.20
*
*取代版本：1.0
*作者：VonZhengzhi
*完成日期：2023.10.22
*/
```

## 1.2 头文件

1. 头文件开头处的版权和版本声明。 
2. 预处理块。 
3. 函数和类结构声明等。

```cpp
//版权和版本声明

//假设头文件为graphics.h
#ifndef GRAPHICS_H // 防止 graphics.h 被重复引用 
#define GRAPHICS_H 
 
#include <math.h> // 引用标准库的头文件 
…
#include “myheader.h” // 引用非标准库的头文件 
… 
void Function1(…); // 全局函数声明 
… 
class Box // 类结构声明 
{ 
… 
}; 
#endif 
```

### 避免重复引用

头文件引用相当于直接把目标文件复制到此文件中，所以需要**避免重复引用**。需要利用`ifndef/define/endif` 结构产生**预处理块**。

### #include“”与#include<>

`#include<filename.h>`用来引用标准库的头文件。编译器**从标准库目录开始搜索**。

`#include"filename.h"`用来引用非标准库（自己编写）的头文件。编译器**从用户的工作目录开始搜索**。

**搜索路径不同提高引入编译效率，分类搜索思想，进行细化提高效率**。

### 头文件的作用

- 通过头文件来调用库功能。源代码不便（或不准）向用户公布，只要向用户提供头文件和二进制的库即可，类似于一种**封装处理**。用户只需要按照头文件中的接口声明来调用库功能，而不必关心接口怎么实现的。**编译器会从库中提取相应的代码**。 
- **头文件能加强类型安全检查**。如果某个接口被实现或被使用时，其方式与头文件中的声明不一致，编译器就会指出错误。

### 注意

- 头文件中只存放“声明”，不存放“定义”。
- 不提倡使用全局变量，尽量不要在头文件中出现像`extern` `int` `value`这类声明
- 将成员函数的定义与声明分开，无论该函数体有多么小。

## 1.3 定义文件的结构

1. 定义文件开头处的版权和版本声明。
2. 对一些头文件的引用。 
3. 程序的实现体（包括数据和代码）。

```cpp
//版权和版本声明

#include<iostream>// 引用头文件
#include<math.h>
#include “graphics.h” 

// 全局函数的实现体 
void Function1(…) 
{ 
… 
} 
 
// 类成员函数的实现体 
void Box::Draw(…) 
{ 
… 
} 
```

## 1.4 目录结构

如果一个软件的头文件数目比较多（如超过十个），通常应将头文件和定义文件分 别保存于不同的目录，以便于维护。 

例如可将头文件保存于 include 目录，将定义文件保存于 source 目录（可以是多级 目录）。 如果某些头文件是私有的，它不会被用户的程序直接引用，则没有必要公开其“声 明”。

为了加强信息隐藏，这些私有的头文件可以和定义文件存放于同一个目录。

# 第二章 程序的版式（规范化）

一些编码过程中的规范化tips，增强程序可读性。

- 在每个类声明之后、每个函数定义结束之后加空行。在一个函数体内，**逻揖上密切相关的语句之间不加空行**，其它地方应加空行分隔。
- 一行代码只做一件事情。
- 尽量在定义变量的同时初始化该变量（就近原则），防止引用或使用未被初始化的变量。
- 关于空格：

![image-20231023132318467](https://gitee.com/zhengzhivon/images/raw/master/imgs/image-20231023132318467.png)

- 应当将修饰符 * 和 ＆ 紧靠变量名 。

```cpp
 char *name;  int *x, y; // 此处y不会被误解为指针 
```

- 不可以滥用类的封装功能，把什么东西都往里封装，仅仅需要公开必须要让外界知道的 内容，而隐藏其它一切内容。

- 类的版式：

```cpp
//以数据为中心
class A 
{ 
private: 
    int i, j; 
    float x, y; 
	… 
public: 
    void Func1(void); 
    void Func2(void); 
	… 
}

//以行为中心，优先展示函数（接口）
class A 
{ 
public: 
    void Func1(void); 
    void Func2(void); 
    … 
private: 
    int i, j; 
    float x, y; 
    … 
}
```

# 第三章 命名规则

## 3.1 共性规则

标识符的长度应当符合“min-length && max-information”原则， 例如变量名`maxval`就比`maxValueUntilOverflow`好用。

命名规则尽量与所采用的操作系统或开发工具的风格保持一致。 例如 Windows 应用程序的标识符通常采用“大小写”混排的方式，如 `AddChild`。 而 Unix 应用程序的标识符通常采用“小写加下划线”的方式，如 `add_child`。不要将两种方式进行混用。

程序中不要出现仅靠大小写区分的相似的标识符。

变量的名字应当使用“名词”或者“形容词＋名词”。例如`newValue`。

全局函数的名字应当使用“动词”或者“动词＋名词”（动宾词组）。 类的成员函数应当只使用“动词”，被省略掉的名词就是对象本身。

```cpp
DrawBox(); // 全局函数
box->Draw(); // 类的成员函
```

尽量避免名字中出现数字编号，如 `Value1`,`Value2` 等，除非逻辑上的 确需要编号。

## 3.2 简单的 Windows 应用程序命名规则

1. 类名和函数名用大写字母开头的单词组合而成。

   ```cpp
   class Node; // 类名 
   class LeafNode; // 类名 
   void Draw(void); // 函数名 
   void SetValue(int value); // 函数名
   ```

2. 变量和参数用小写字母开头的单词组合而成。

   ```cpp
   BOOL flag; 
    int drawMode;
   ```

3. 常量全用大写的字母，用下划线分割单词。

   ```cpp
   const int MAX = 100; 
   const int MAX_LENGTH = 100;
   ```

4. 静态变量加前缀s_（表示 static）。

   ```cpp
   void Init(…) 
   { 
        static int s_initValue; // 静态变量
        … 
   }
   ```

5. 如果不得已需要全局变量，则使全局变量加前缀g（表示member），这样可以避免数据成员与成员函数的参数同名。

   ```cpp
   int g_howManyPeople; // 全局变量
   int g_howMuchMoney; // 全局变量
   ```

6. 为了防止某一软件库中的一些标识符和其它软件库中的冲突，可以为各种标识符加上能反映软件性质的前缀。

   ```cpp
   void Object::SetValue(int width, int height) 
   { 
       m_width = width; 
       m_height = height; 
   } 
   ```

# 第四章 表达式和基本语句

##  4.1 运算符优先级

![image-20231023140247659](https://gitee.com/zhengzhivon/images/raw/master/imgs/image-20231023140247659.png)

## 4.3 if语句

### 4.3.1 布尔变量与零值比较

**不可将布尔变量直接与 TRUE、FALSE 或者 1、0 进行比较**。

根据布尔类型的语义，零值为“假”（记为 FALSE），任何非零值都是“真”（记为 TRUE）。TRUE 的值究竟是什么并没有统一的标准。**例如 Visual C++ 将 TRUE 定义为 1，而 Visual Basic 则将 TRUE 定义为-1**。

```cpp
假设布尔变量名字为 flag，它与零值比较的标准 if 语句如下：
if (flag) // 表示 flag 为真 
if (!flag) // 表示 flag 为假 
    
其它的用法都属于不良风格，例如： 
 if (flag == TRUE) 
 if (flag == 1 ) 
 if (flag == FALSE) 
 if (flag == 0) 
```

### 4.3.2 整型变量与零值比较

```cpp
int value;
if (value == 0) //ok
if (value != 0)//ok
    
if (value) //error,会让人误解 value 是布尔变量 
if (!value) //error
```

### 4.3.3 浮点变量与零值比较  

**不可将浮点变量用`==`或`!=`与任何数字比较**。



```cpp
无论是 float 还是 double 类型的变量，都有精度限制。
所以一定要 将浮点变量用`==`或`!=`与数字比较，应该设法转化成“>=”或“<=”形式。 

float x;
if (x == 0.0) //error,隐含错误的比较,应转化为:
    
if ((x>=-EPSINON) && (x<=EPSINON))  其中EPSINON 是允许的误差（即精度）。  
```

###  4.3.4 指针变量与零值比较 

**应当将指针变量用“==”或“！=”与 NULL 比较**。 

指针变量的零值是“空”（记为 NULL）。尽管 NULL 的值与 0 相同，但是两者意义不同。

```cpp
int *p;
if (p == NULL) // p 与 NULL 显式比较 
```

### 4.3.5 对if语句的补充说明  

```cpp
if (NULL == p) 
    
//不是程序写错了，是程 序员为了防止将 if (p == NULL) 误写成 if (p = NULL)，而有意把 p 和 NULL 颠倒。
//编译器认为 if (p = NULL) 是合法的，但是会指出 if (NULL = p)是错误的，因为 NULL 不能被赋值。  
```

## 4.4 循环语句的效率

**在多重循环中，应当将最长的循环放在最内层，最短的循环放在最外层，以减少 CPU 跨切循环层的次数。**

```cpp
//低效率，长循环在最外层
for (row=0; row<100; row++) 
{ 
	for ( col=0; col<5; col++ ) 
	{ 
		sum = sum + a[row][col]; 
	} 
} 

//高效率，长循环在最内层
for (col=0; col<5; col++ ) 
{ 
    for (row=0; row<100; row++) 
    { 
    	sum = sum + a[row][col]; 
    } 
} 
```

关于逻辑判断，**如果循环体内存在逻辑判断，并且循环次数很大，宜将逻辑判断移到循环体的外面**。

```cpp
//低效率
for (i=0; i<N; i++) 
{ 
    if (condition) 
    	DoSomething(); 
    else 
    	DoOtherthing(); 
} 

//高效率
if (condition) 
{ 
    for (i=0; i<N; i++) 
    	DoSomething(); 
} 
else 
{ 
    for (i=0; i<N; i++) 
    DoOtherthing(); 
}
```

## 4.5 for语句的循环控制变量

## 4.6 switch 语句

```cpp
switch (variable) 
{ 
    case value1 : … 
    	break; 
    case value2 : … 
    	break; 
     … 
    default : … 
    	break; 
}
```

# 第五章 常量

## const和#define

const 常量有数据类型，而宏常量没有数据类型。编译器可以对前者进行类型安 全检查。而对后者只进行字符替换，没有类型安全检查，并且在字符替换可能会 产生意料不到的错误（边际效应）。

```cpp
#define MAX 100 /* C 语言的宏常量 */ 
const int MAX = 100; // C++ 语言的 const 常量 
const float PI = 3.14159; // C++ 语言的 const 常量
```

**需要对外公开的常量放在头文件中，不需要对外公开的常量放在定义文件的头部**。为便于管理，可以把不同模块的常量集中存放在一个公共的头文件中。

## 类中的常量

#define 定义的宏常量是全局的

用`const`修饰数据成员来实现某些常量只在类中有效。`const`数据成员只在某个对象生存期内是常 量，而对于整个类而言却是可变的，因为类可以创建多个对象，不同的对象其`const`数 据成员的值可以不同。

不能在类声明中初始化`const`数据成员，只能在类构造函数的初始化表中进行。

## 枚举常量`enum`

枚举类型(enumeration)是 C++ 中的一种派生数据类型，它是由用户定义的**若干枚举常量的集合**。是一种由程序员定义的数据类型，其合法值是与它们关联的**一组命名整数常量**。

```cpp
enum <数据类型名> {<枚举常量表>};
//关键字enum——指明其后的标识符是一个枚举类型的名字;

enum color {RED, BLUE, WHITE, BLACK}; // 定义枚举类型color，4个枚举变量值依次默认为：0，1，2，3
enum { SIZE1 = 100, SIZE2 = 200}; // 枚举常量

//枚举常量只能以标识符形式表示，而不能是整型、字符型等文字常量.

//枚举常量表——由枚举常量构成。"枚举常量"或称"枚举成员"，是以标识符形式表示的整型量，表示枚举类型的取值。各枚举常量之间以"，"间隔，且必须各不相同，且枚举变量一般是以大写字母表示(或首字母大写）；
```

### 枚举类型的创建与使用

```cpp
enum week {Sun, Mon, Tue, Wed, Thu, Fri, Sat};    //声明枚举类型

week day；  //定义week数据类型的变量, 数据类型名称week，变量名称day
day=Sun;      //为创建的变量day赋值，赋值为Sun
cout<<day<<endl;  //枚举变量可以直接输出，输出结果为0

//声明枚举类型color，并创建枚举类型变量color1, color2

enum color {RED, BLUE, WHITE, BLACK} color1, color2，color3，color4;
color3=RED;           //将枚举常量值赋给枚举变量
color4=color3;        //相同类型的枚举变量赋值，color4的值为RED

//比较同类型枚举变量color3，color4是否相等
if (color3==color4) cout<<"相等"；
```

# 第六章 函数设计

函数接口的两个要素是参数和返回值。C 语言中，函数的参数和返回值的传递方式有两种：**值传递**（pass by value）和**指针传递**（pass by pointer）。C++ 语言中多了**引用传递**（pass by reference）。

## 6.1 参数设计

一般地，应将目的参数放在前面，源参数放在后面。 

```cpp
 void StringCopy(char *strDestination, char *strSource);
```

如果参数是指针，且仅作输入用，则应在类型前加 `const`，以**防止该指针在函数体内被意外修改**。

```cpp
void StringCopy(char *strDestination，const char *strSource);
```

**如果输入参数以值传递的方式传递对象，则宜改用`const &`方式 来传递，这样可以省去临时对象的构造和析构过程，从而提高效率。**

## 6.2 返回值设计

不要将正常值和错误标志混在一起返回。正常值用输出参数获得，而 错误标志用 return 语句返回。

```cpp
char c; 
c = getchar(); 
if (c == EOF)//error
    
int getchar(void);
//在正常情况下，getchar 的确返回单个字符。但如果 getchar 碰到文件结束标志或发生读错误，它必须返回一个标志 EOF。为了区别于正常的字符，只好将 EOF 定义为负数（通常为负 1）。因此函数 getchar 就成了 int 类型
```

### 引用传递与值传递

**如果函数的返回值是一个对象，有些场合用“引用传递”替换“值传 递”可以提高效率**。而有些场合只能用“值传递”而不能用“引用传递”，否则会 出错。

```cpp
class String 
{	… 
    // 赋值函数 
    String & operate=(const String &other); 
    // 相加函数，如果没有 friend 修饰则只许有一个右侧参数 
    friend String operate+( const String &s1, const String &s2); 
private: 
	char *m_data; 
}

String & String::operate=(const String &other) 
{ 
    if (this == &other) 
    return *this; 

    delete m_data;

    m_data = new char[strlen(other.data)+1]; 
    strcpy(m_data, other.data); 
    return *this; // 返回的是 *this 的引用，无需拷贝过程 
    //如果用“值传递”的方式，虽然功能仍然正确，但由于 return 语句要把 *this 拷贝到保存返回值的外部存储单元之中，增加了不必要的开销，降低了赋值函数的效率
}

String a,b,c; 
 … 
 a = b; // 如果用“值传递”，将产生一次 *this 拷贝 
 a = b = c; // 如果用“值传递”，将产生两次 *this 拷贝 
```

```cpp
String 的相加函数 operate + 的实现如下：
String operate+(const String &s1, const String &s2) 
{ 
    String temp; 
    delete temp.data; // temp.data 是仅含‘\0’的字符串 
    temp.data = new char[strlen(s1.data) + strlen(s2.data) +1]; 
    strcpy(temp.data, s1.data); 
    strcat(temp.data, s2.data); 
    return temp; 
} 
//对于相加函数，应当用“值传递”的方式返回 String 对象。如果改用“引用传递”，那么函数返回值是一个指向局部对象 temp 的“引用”。由于 temp 在函数结束时被自动销毁，将导致返回的“引用”无效。
```

## 6.3 函数内部的实现

在函数体的“入口处”，对参数的有效性进行检查（使用断言`assert`）；在函数体的“出口处”，对 return 语句的正确性和效率进行检查。

```cpp
return 语句不可返回指向“栈内存”的“指针”或者“引用”，因为该内存在函数体结束时被自动销毁。
char * Func(void) 
{ 
    char str[] = “hello world”; // str 的内存位于栈上 
    … 
    return str; //error
}
```

```cpp
如果函数返回值是一个对象，要考虑 return 语句的效率。
//这是临时对象的语法，表示“创建一个临时对象并返回它”。
return String(s1 + s2); 

//“先创建一个局部对象 temp 并返回它的结果”
String temp(s1 + s2);
return temp; 
实质不然，上述代码将发生三件事：
首先，temp 对象被创建，同时完成初始化；
然后拷贝构造函数把 temp 拷贝到保存返回值的外部存储单元中；
最后，temp 在函数结束时被销毁（调用析构函数）。

然而“创建一个临时对象并返回它”的过程是不同的，编译器直接把临时对象创建并初始化在外部存储单元中，省去了拷贝和析构的化费，提高了效率。
    
类似地，不要将 
return int(x + y); // 创建一个临时变量并返回它 
写成 
int temp = x + y; 
return temp; 
由于内部数据类型如 int,float,double 的变量不存在构造函数与析构函数，虽然该“临时变量的语法”不会提高多少效率，但是程序更加简洁易读。
```

## 6.5 使用断言

[assert参考](https://blog.csdn.net/weixin_52377137/article/details/119864975?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169812338516800225514331%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=169812338516800225514331&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-1-119864975-null-null.142^v96^pc_search_result_base3&utm_term=%E6%96%AD%E8%A8%80assert&spm=1018.2226.3001.4187)

程序一般分为 Debug 版本和 Release 版本，Debug 版本用于内部调试，Release 版本 发行给用户使用。 **断言 assert 是仅在 Debug 版本起作用的宏，它用于检查“不应该”发生的情况**。

**assert 不是函数，而是宏**。

```cpp
#include "assert.h" 
#ifdef NDEBUG	//一旦定义了NDEBUG宏，assert() 就无效了，运用于发布模式
#define assert(e) ((void)0)
#else
#define assert(e)  \
    ((void) ((e) ? ((void)0) : __assert (#e, __FILE__, __LINE__)))
#endif

void assert( int expression );//无返回值
```

assert() 会对表达式expression进行检测：

- 如果expression的结果为 0（条件不成立），那么断言失败，表明程序出错，assert() 会向标准输出设备（一般是显示器）打印一条错误信息，并调用 abort() 函数终止程序的执行。
- 如果expression的结果为非 0（条件成立），那么断言成功，表明程序正确，assert() 不进行任何操作。

```cpp
#define NDEBUG	//在发布模式中添加以使assert()失效
#include <stdio.h>
#include <assert.h>
int main(){
    int m, n, result;
    scanf("%d %d", &m, &n);
    assert(n);//分母不为零
    result = m / n;
    printf("result = %d\n", result);
    return 0;
}
```

## 6.6 引用与指针

https://blog.csdn.net/qq_51556066/article/details/129676701?spm=1001.2014.3001.5501

### const修饰指向与变量本身

```cpp
int main()
{
    const int n=5;//cpp中，n为一个有名字的常变量
    int ar[n]={1,2,3,4,5};	//在.C的编译环境下无法通过，n不是常量，#define enum
    
    int b=0;
    int *p=（int*）&n;
    *p=100;
    b=n;	//n=5,在编译过程中已经拿5替换了n，此处应为b=5
    printf("n=%d b=%d *p=%d \n",n,b,*p);
    return 0；
}
```

**C编译方式与C++编译方式对于const（常性）的解释不同。**

```cpp
int main()
{
	int a=10,b=20;
    int * p1=&a;
    //*p1=100;a=100;p1=&b;
    const int* p2=&a;
    //int const* p2=&a;与上一行写法等价
    //*p2=100； error
    p2=&b；
    //const在*左边，修饰指针的指向能力，所以不能通过*p2改变a的值，但是p2本身可以被改变
    
    int* const p3=&a;
    //const在*右边，修饰指针变量名，使p3成为一个常性指针
    *p3=100；
    //p3=&b; error
        
    const int* const p4=&a;//指针p4的本身和指向都被const修饰为常性，不可修改
    //*p4=100;	error
    //p4=&b;	error
}
```

```cpp
int main()
{
    int a=10;
    const int b=20;
    int *p1=&a;
    //int* p2 = &b;		error	//用普通指针指向常变量，可以通过*p2=200改变b;
    const int* p2 = &b;
    int* p3=(int*)b;//不安全，二义性
    *p3=100;
    //常变量应该拿指向为常性的指针来指向其地址const int*，不能同普通指针来指向。
}
```

### 指针之间的赋值，数值兼容性

```cpp
//指针之间的相互赋值
//修改能力不能被扩展
int main()
{
    const int a=10;	//常变量，不允许被改变
    const int* s=&a; //s指向为常性，常性指针可以指向常变量or普通变量，只是不能通过解引用改变变量的值
    
    int* p1=s;			//error	可以通过*p1改变a的值，本来并不能通过*s改变a的值
    const int* p2=s;
    int* const p3=s;	//error	const修饰p3自身不能改变，但可以通过解引用*p3修改a
    const int* const p4=s;	
    return 0;
}
```

```cpp
int main()
{
    int a=10,b=10;
    int* const s=&a;	//s本身不能被改编，但可以通过解引用*s改变指向
    
    int *p=s;	//不改变s
    const int *p2=s;	//可以指向但不能改变
    int * const p3=s;
    const int * const p4=s;
    
    return 0;
}
```

### 引用&（别名）

```cpp
int main()
{
    int a=10;
    int b=a;
    int& c=a;//类型&变量-->引用；&变量-->地址
    a+=10;
    cout<<"a="<<a<<"c"<<c<<endl;
    c+=10;
    cout<<"a="<<a<<"c"<<c<<endl;
    
    cout<<"&a: "<<&a<<endl;
    cout<<"&c: "<<&a<<endl;
    //a和c的地址相同
    return 0;
}
```

### 引用的特点

1. **定义引用必须初始化**
2. **没有空引用**
3. **没有引用的引用（int&& x）,不能一次第一所谓的二级引用**

```cpp
int main()
{
    int a=10,b=20;
    //int& x;	error 定义引用必须初始化，没有空引用
    //int&& x=a;	error 不能一次定义二级引用
    int& x=a;
    int& y=x;
    return 0;
}
```

### 引用作为形参相较于指针的区别

```cpp
void Swap_Int(int* ap,int* bp)
{
    assert(ap!=NULL && bp!=NULL);
    int tmp=*ap;
    *ap=bp;
    *bp=tmp;
}

void Swap(int& x,int& y)
{
    //没有空引用，不需要进行assert断言或者判空
    int tmp=x;
    x=y;
    y=tmp;
}b

int main()
{
    int a=10,b=20;
    cout<<"a="<<a<<"b="<<b<<endl;
    //Swap_Int(&a,&b);
    Swap(a,b);
    cout<<"a="<<a<<"b="<<b<<endl;
    
    return 0;
}
```

### 引用与const的关系

```cpp
int main()
{
    int a=10;
    int& b=a;
    b+=10;
    int const& c=a;	//cosnt修饰&，常引用，c可以读取a的值，但不能通过修改c来修改a值
    int& const x=a;	//const修饰引用x本身，系统会忽略此const，可以读取和修改x
    cout<<c<<endl;
    //c+=100;	error
}
```

```cpp
int main()
{
    const int a=10;
    //int& x=a;	error	常变量不能被修改，利用普通引用则可以通过引用x来修改a
    const int& y=a;
}
```

### 函数形参设计

```cpp
void fun_a(int x)
{}

void fun_b(int& y)
{}

void fun(const int& y)
{}
```

### 常引用

```cpp
int main()
{
    int a=10;
    const int b=20;
    const int& rx=a;
    const int& ry=b;
    const int& rz=100;
    //tmp=100;
    //const int& rz=tmp;
}
```

### 左值&右值&右值引用

```cpp
//左值left value,可以进行取地址操作&a,与类型无关
//右值right value，不可以进行取地址操作，eg：10，&10 error
int main()
{
    int a=10;			//&a,left value
    const int b=20;		//&b,left value
    int& x=a;			//&x,left value
    const int& y=b;		//&y,lvalue
    double dx=12.23;	//&dx,lvalue
    int ar[5]{1,2,3,4,5};	//&ar[1],lvalue
    
    //const int& r=b;
    const int& z=10;//常引用才能作为常变量的别名
    //int tmp=10;	引用字面常量时需要开辟一个临时变量，此引用z时临时变量tmp的别名
    //const int& z=tmp;
    //z+=10;	error z为常引用不能修改原值
    
    //int&& ra=a;	error,a为左值不能进行右值引用
    int&& r=10;		//右值引用，r变成10的别名
    //int tmp=10;
    //int& r=tmp;
    r+=10;	//可以进行运算，但不是对字面常量10进行运算，而是对临时变量tmp做运算
    
    return 0;
}
```

### 其他引用形式

```cpp
//数组的引用
int main()
{
    int ar[5]{1,2,3,4,5};	//&ar[1],lvaule
    int& a=ar[1];		//引用数组里的某个元素
    
    //int &br[5];	error 数组开辟空间，引用&不开辟空间，矛盾
    int (&cr)[5]=ar;	//引用整个数组,cr是ar的别名
    
    cout<<"sizeof(ar):"<<sizeof(ar)<<endl;//20
    cout<<"sizeof(cr):"<<sizeof(cr)<<endl;//20
}
```

```cpp
//指针类型的引用
int main()
{	
    int a=10,b=20;
    int* ip=&a;
    int& x=a;
    int* s=ip;
    int *&ps=ip;	//别名ps引用整形指针ip（int*代表整型指针类型）
    
    *ps=100;	//等价于*ip=100
    cout<<"*ps=>"<<*ps<<"*ip=>"<<*ip<<endl;
    ps=&b;		//等价于ip=&b
    cout<<"*ps=>"<<*ps<<"*ip=>"<<*ip<<endl;
    *ps=200;
    cout<<"*ps=>"<<*ps<<"*ip=>"<<*ip<<endl;
    return 0;
}
```

### 引用和指针的区别（重点）

**引用是指针的语法糖**

#### 语法规则上的区别

1. **从语法规则上将，指针变量存储某个实例（变量或对象）的地址；引用则是某个实例的别名。**
2. **程序为指针变量分配内存区域<u>（32位4字节x86，64位8字节x64）</u>;而不为引用分配内存区域。**
3. **在使用指针和引用所指向或别名的实例时，解引用是指针使用时要在前加“*”；引用可以直接使用。**
4. **指针变量的值可以发生改变，存储不同实例的地址（修改所指向的地址，eg：指针++or指针--）；引用在定义时就别初始化，之后无法改变（不能再是其他实例的引用）。**
5. **指针变量可以为空（空指针NULL）；没有空引用。eg:形参的区别，形参位指针变量则需要判空或者断言，形参为引用则无需此操作。**
6. **指针变量作为形参时需要测试它的合法性（判空NULL）；引用不需要判空，则更加安全。**
7. **对指针变量使用“”sizeof“得到的时指针变量的大小<u>（32位4字节x86，64位8字节x64）</u>；对引用变量使用”sizeof“得到的大小是所引用变量的大小。**
8. **理论上指针的级数没有限制；但引用只有一级。即不存在引用的引用，但可以有指针的指针。区别：int && a;右值引用。**
9. **对指针变量的操作，会使指针指向下一个实体（变量或对象）的地址，而不知改变所指实体（变量或对象）的内容。对引用的操作直接反映到所引用的实体（变量或对象）。eg：++引用与++指针的效果不一样。**

- **补充注意点：函数不允许将局部变量以引用或者指针的形式返回。**

```cpp
int funa(int* p)
{
    if(p==NULL)		//指针需要判空or断言
        
    {
        return -1;
    }
    *p += 10;
    return *p;
}
int funb(const int& a)
{
    
}

int main()
{
    int a=10;
    int x=10;
    int& b=a;
    b=x;	//4是把x赋值给a
    int=* ip=&a;
    *ip =100;
    b+=200;
    funb(10);
    
    return 0;
}
```

```cpp
//指针和引用的大小，sizeof的使用
int main()
{
    double dx=12.25;
    double& rx=dx;
    double* dp=&dx;	//double *dp=&rx;
    
    cout<<"sizeof(rx):"<<sizeof(rx)<<endl;
    cout<<"sizeof(dp):"<<sizeof(rx)<<endl;
    retrun 0;
}
```

```cpp
//++引用与++指针的效果不一样
//++指针，指向下一个储存单元地址；++引用，直接修改所引用对象的值
int main()
{
    int ar[5]{1,2,3,4,5};
    int& a=ar[0];
    int* p=&ar[0];
    for(int i=0;i<5;++i)
    {
        cout<<ar[i]<<" ";
    }
    cout<<endl;
    //1 2 3 4 5 
    
    ++a;	//ar[0]的值+1
    a+=10'	//ar[0]的值再+10
    for(int i=0;i<5;++i)
    {
        cout<<ar[i]<<" ";
    }
    //12 2 3 4 5
    cout<<endl;
    
    cout<<"*p "<<*p<<endl;	//*p 12
    
    ++p;	//p从指向ar[0]改为指向ar[1]
   	cout<<"*p "<<*p<<endl;	//*p 2
    return 0;
}
```

```cpp
//引用与指针的相同点，函数不允许将局部变量以引用或者指针的形式返回(静态变量、全局变量可以:在函数结束后生存期未结束or形参也为引用，接受变量也为引用)
int& funx(int& y)
{
    a+=20;
    return a;
}

int* funa()
{
    int a=10;
    retrun &a;
}
int& funb()
{
    int a=20;
    return a;
}
void fun()
{
    int ar[10]={1};
}

int main()
{
    int *p=funa();
    fun();	//清理了调用funa()时所分配的栈空间，原有值被覆盖
    cout<<*p<<endl;	//0
    
    int& x=funb();
    fun();
    cout<<x<<endl;	//0
    
    int& x=funx(y);
    return 0;
}
```

### 汇编层面的区别

```cpp
//从底层上讲，引用是一个自身为常性的指针
void fun(int& x)
{
    int* ip=&x;
    x=100;
}
int main()
{
    int a=10;
    int& b=a;
    fun(a);
    fun(b);
    return 0;
}

//指针替换引用后
void fun(int * const x)
{
    int* ip=x;
    *x=100;
}
int main()
{
    int a=10;
    int* const b=&a;
    fun(&a);
    fun(b);
    return 0;
}
```

### 引用的使用

```cpp
//内置类型
int Add_Int(const int x,const int y)
{
    return x+y;//访问x，访问一次内存
}
int Add_Int_a(int& x,int& y)//传入a和b的地址（引用底层位指针）
{
    return x+y;//访问x，需要解引用，所以访问两次
}
int Add_Int_b(const int& x,const int& y)
{
    return x+y;//访问x，需要解引用，所以访问两次
}

/*对于内置类型直接使用Add_Int(int x,int y)这样的值传递，减少内存访问，不适合使用引用，因为不需要通过形参的改变来反作用于实参
*/

int main()
{
    int a=10,b=20;
    int c=0;
    c=Add_Int(a,b);
    
    cout<<c<<endl;
    return 0;
}
```

**函数是否需要通过形参的改变来反作用于实参来改变实参-->是否使用引用做形参**

```cpp
//自己设计的类型
struct Stud
{
	int ar[10];
    int num;
};
void funa(struct Stud s)//需要将s1赋值给s，调用时s也要开辟10个整型空间
{
    
}
void funb(struct Stud const& s)//别名，调用此函数是无需额外开辟空间，&s就是&s1，相当于指针{}					   //只需要传递4个字节，形参s的改变有可能改变实参s1，加上							 //const修饰,只读不可修改
    
void func(struct Stud* s)
{
    if(s==NULL) return;
    //需要断言或者判空
}

int main()
{
    struct Stud s1{1，2，3，4，5，6，7，8，9，10，10};
    funa(s1);
    funb(s1);//针对于自己设计的类型，形参最好使用引用形式，节省空间开辟并省去安全性检查
    int a=10;
    int& b=a;
    const int& c=a;
    //const int* const c=&a;	常引用，在底层表示为指向为常性
    
    return 0;
}
```

**在编写程序时，自己设计的类型形参能够用引用就不要用指针。**

# 第七章 内存管理

[参考：变量存放区域](https://blog.csdn.net/qq_51556066/article/details/130915137?spm=1001.2014.3001.5501)

## 7.1 内存分配方式

1. **从静态存储区域分配**。内存在程序编译的时候就已经分配好，这块内存在程序的 整个运行期间都存在。例如全局变量，static 变量。 
2. **在栈上创建**。在执行函数时，函数内局部变量的存储单元都可以在栈上创建，函数执行结束时这些存储单元自动被释放。栈内存分配运算内置于处理器的指令集中，效率很高，但是分配的内存容量有限。 
3. **从堆上分配**，亦称动态内存分配。程序在运行的时候用 `malloc` 或 `new` 申请任意 多少的内存，程序员自己负责在何时用 `free` 或 `delete` 释放内存。动态内存的生存期由我们决定，使用非常灵活，但问题也最多。

## 7.2 常见的内存错误

1. 内存未分配成功，在使用内存之前检查指针是否为 `NULL`，使用用 `assert(p!=NULL)`或者`if(p==NULL)`进行检查以及预防。
2. 内存分配虽然成功，但是尚**未初始化就引用它**。主要有两个起因：一是没有初始化的观念；二是误以为内存的缺省初值全为零，导致引用初值错误（例如数组） 。
3. 内存分配成功并且已经初始化，但操作越过了内存的边界。，例如数组下标越界。
4. 忘记了释放内存，造成内存泄露。 
5. 释放了内存却继续使用它。 

- 注意不要返回指向“栈内存”的“指针”或者“引用”， 因为该内存在函数体结束时被自动销毁。 
- 使用 free 或 delete 释放了内存后，没有将指针设置为 NULL，导致产生“野指针”。

## 7.3 指针与数组的对比

```cpp
char a[] = "hello world"; 
char *p = a; 
cout<< sizeof(a) << endl; // 12 字节 
cout<< sizeof(p) << endl; // 4 字节

void Func(char a[100]) 
{ 
	cout<< sizeof(a) << endl; // 4 字节而不是 100 字节 
}
```

## 7.4 指针参数传内存

```cpp
void GetMemory(char *p, int num) 
{ 
	p = (char *)malloc(sizeof(char) * num); 
    //编译器总是要为函数的每个参数制作临时副本，指针参数 p 的副本是 _p，编译器使 _p = p。如果函数体内的程序修改了_p 的内容，就导致参数 p 的内容作相应的修改。
} 
void Test(void) 
{ 
	char *str = NULL; 
	GetMemory(str, 100); // str 仍然为 NULL 
	strcpy(str, "hello"); //error运行错误
    //_p 申请了新的内存，只是把_p 所指的内存地址改变了，但是 p 丝毫未变。所以函数 GetMemory并不能输出任何东西。事实上，每执行一次 GetMemory 就会泄露一块内存，因为没有用free 释放内存。 
}

更改后：
//1、用指针参数去申请内存,需要用指针的指针
void GetMemory2(char **p, int num) //二级指针
{ 
	*p = (char *)malloc(sizeof(char) * num); 
}
void Test2(void) 
{ 
    char *str = NULL; 
    GetMemory2(&str, 100); // 注意参数是 &str，而不是 str 
    strcpy(str, "hello"); 
    cout<< str << endl; 
    free(str); 
}

//2、用函数返回值来传递动态内存
//注意：不要用 return 语句返回指向“栈内存”的指针，因为该内存在函数结束时自动消亡，数据无法保存
char *GetMemory3(int num) 
{ 
    char *p = (char *)malloc(sizeof(char) * num); //动态内存，堆区
    //char p[] = "hello world";	栈区
    return p; 
}
void Test3(void) 
{ 
    char *str = NULL; 
    str = GetMemory3(100); 
    strcpy(str, "hello"); 
    cout<< str << endl; 
    free(str); 
} 
```

## 7.5 free和delete针对于指针

`free`和`delete`只是把指针所指的内存给 释放掉，但并没有把指针本身干掉。

```cpp
char *p = (char *) malloc(100); 
strcpy(p, “hello”); 
free(p); // p 所指的内存被释放，但是 p 所指的地址仍然不变 
… 
if(p != NULL) // 没有起到防错作用 
{ 
	strcpy(p, “world”); // 出错 
} 
```

p 被 `free`以后其地址仍然不变（非NULL），只是该地址对应的内存是垃圾，**p 成了“野指针”**。如果此时不把 p 设置为 NULL，会让人误以为 p 是个合法的指针。

### 野指针

野指针就是指针的指向方向的位置是不可知的（随机的、不正确的、没有明确限制的）。

**“野指针”不是 NULL 指针，是指向“垃圾”内存的指针。**

**指针变量没有被初始化**。**任何指针变量刚被创建时不会自动成为 NULL 指针，它 的缺省值是随机的**。所以，指针变量在创建的同时应当被初始化，要么 将指针设置为 NULL，要么让它指向合法的内存。

```cpp
//1、指针未初始化
#include <stdio.h>
int main()
{
	int * p;//局部变量未初始化，默认随机值
	*p = 20;
	return 0;
}
```

**指针操作超越了变量的作用范围。**

```cpp
class A 
{ 
public: 
	void Func(void){ cout << “Func of class A” << endl; } 
};

void Test(void) 
{ 
    A *p; 
    { 
        A a; 
        p = &a; // 注意 a 的生命期 
    } 
    p->Func(); // p 是“野指针” 
} 
//函数 Test 在执行语句 p->Func()时，对象 a 已经消失，而 p 是指向 a 的，所以 p 就成了“野指针”。
```

```cpp
//2、指针访问越界
#include <stdio.h>
int main()
{
	int arr[] = { 0 };
	int *p = arr;
	for (int i = 0; i <= 11; i++)
	{
		//当指针指向范围外，p就是野指针
		*(p + i) = i;
	}
	return 0;
}
```

## 7.8 `malloc/free`与`new/delete`

[参考1](https://blog.csdn.net/cwcmcw/article/details/53873600)

[参考2](https://blog.csdn.net/LINZEYU666/article/details/120165192?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169812905616777224473647%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fblog.%2522%257D&request_id=169812905616777224473647&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~blog~first_rank_ecpm_v1~rank_v31_ecpm-2-120165192-null-null.nonecase&utm_term=%60malloc%2Ffree%60%E4%B8%8E%60new%2Fdelete&spm=1018.2226.3001.4450)

[operator new 和 operator delete](https://blog.csdn.net/liugan528/article/details/125437433?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-1-125437433-blog-80328317.235%5Ev38%5Epc_relevant_sort_base3&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-1-125437433-blog-80328317.235%5Ev38%5Epc_relevant_sort_base3&utm_relevant_index=2)

`malloc`与`free`是 C++/C 语言的标准库函数，`new/delete` 是 C++的运算符。它们都可用于申请动态内存和释放内存。

C++中针对于非内部数据类型的对象，对象每次在创建时需要自动执行构造函数，对象在消亡之前要自动执行析构函数，光用 `maloc/free` 无法满足动态对象的要求。因此 C++语言需要一个**能完成动态内存分配和初始化工作的运算符 new，以及一个 能完成清理与释放内存工作的运算符 delete。注意 new/delete 不是库函数**。

```cpp
class Obj 
{ 
public : 
    Obj(void){ cout << “Initialization” << endl; } //构造函数
    ~Obj(void){ cout << “Destroy” << endl; } //析构函数
    void Initialize(void){ cout << “Initialization” << endl; } //模拟构造函数
    void Destroy(void){ cout << “Destroy” << endl; } //模拟析构函数
};

void UseMallocFree(void) 
{ 
    Obj *a = (obj *)malloc(sizeof(obj)); // 申请动态内存 
    a->Initialize(); // 初始化 
    //… 
    a->Destroy(); // 清除工作 
    free(a); // 释放内存 
}

void UseNewDelete(void) 
{ 
    Obj *a = new Obj; // 申请动态内存并且初始化 
    //… 
    delete a; // 清除并且释放内存 
}
```

**由于内部数据类型的“对象”没有构造与析构的过程，对它们而言 `malloc/free` 和 `new/delete` 是等价的**。

**因为 C++程序经常要调用 C 函数，而 C 程序只能用 malloc/free 管理动态内存**。

### C的动态内存管理

```cpp
//C的动态内存管理
int main()
{
    int n = 10;
    int *ipa = (int*)malloc(sizeof(int)*n);
    int *ipb = (int*)calloc(n,sizeof(int));
    ipa = (int*)realloc(ipa,sizeof(int)*n*2);
    //
    free(ipa);
    ipa = NULL;
    free(ipb);
    ipb = NULL;
    return 0;
}
```

#### malloc和free的使用

```cpp
//函数malloc的原型如下： 
void * malloc(size_t size); 
//用 malloc 申请一块长度为 length 的整数类型的内存，程序如下： 
int *p = (int *) malloc(sizeof(int) * length);

//函数 free 的原型如下：
void free( void * memblock );
```

- `malloc`返回值的类型是`void *`，所以在调用 `malloc` 时要**显式地进行类型转换**，将 `void *` 转换成所需要的指针类型。 
- `malloc`函数本身并不识别要申请的内存是什么类型，它**只关心内存的总字节数**。如 int 变量在 16 位系统 下是 2 个字节，在 32 位下是 4 个字节；而 float 变量在 16 位系统下是 4 个字节，在 32 位下也是 4 个字节。
- 如果 p 是 NULL 指针， 那么 free 对 p 无论操作多少次都不会出问题。如果 p 不是 NULL 指针，那么 free 对 p 连续操作两次就会导致程序运行错误。

### C++的动态内存管理

#### new和delete的使用

```cpp
//C++的动态内存管理
//1、new运算符的使用
int main()
{
    int n = 10;
    int* ipa = new int(10); // 1 // 2;
    int* ipb = new int[n](10);
    int* ipc = new int[n] {1, 2, 3, 4, 5, 6, 7};
    delete ipa;
    delete[]ipb;
    delete[]ipc;
    return 0;
}

//2、new的函数方式使用
int main()
{
    int n = 10;
    int *ipa = (int*)::operator new(sizeof(int));
    // (int*)malloc(sizeof(int));
    int *ipb = (int*)::operator new(sizeof(int)*n);
    // (int*)malloc(sizeof(int)*n);
    ::operator delete(ipa);
    ::operator delete(ipb);
    return 0;
}

//3、定位new
int main()
{
    int n = 10;
    int* ipa = (int*)malloc(sizeof(int));
    int* ipb = (int*)::operator new(sizeof(int) * n);
    new(ipa) int(20);
    new(ipb) int[]{ 1,2,3,4,5,6,7,8,9 };
    free(ipa);
    ::operator delete(ipb);
    return 0;
}
```

#### new的种类

```cpp
int *p1 = new int(20);

int *p2 = new (nothrow) int;//不抛出异常版本的new，返回值跟空判断。

const int *p3 = new const int(40);//开辟常量内存

//定位new  
int data = 0;
int *p4 = new (&data) int(50);
//在指定的内存上划分出4字节的内存赋值为50
cout << "data:" << data << endl;//data：50
```

#### operator new 和 operator delete

当我们在C++中使用`new`和`delete`时，其实执行的是全局的`::operator new`和`::operator delete`，不过这两个函数并没有重载`new`表达式或`delete`表达式。

可以重载`operator new`和`operator delete`来控制内存的分配和释放，但不能重载`new`表达式和`delete`表达式。也就是说，**可以自定义的是实际的内存分配和释放，但不能自定义构造函数和析构函数的调用**。
我们提供新的`operator new`函数和`operator delete`函数的目的在于**改变内存分配的方式**，但是不管怎样，都不能改变`new`运算符和`delete`运算符的基本含义。

```cpp
void *operator new(size_t);     //allocate an object
void *operator delete(void *);    //free an object

void *operator new[](size_t);     //allocate an array
void *operator delete[](void *);    //free an array
```

##### 一条new的三步骤

1. **new表达式调用一个名为operator new(或operator new[])的标准库函数，该函数分配一块足够大的、原始的、未命名的内存空间以便存储特定类型的对象(或者对象的数组)；**
2. **编译器运行相应的构造函数以构造这些对象，并为其传入初始值；**
3. **对象被分配了空间并构造完成，返回一个指向该对象的指针。**

```cpp
//new：分配空间--->调用构造函数初始化--->对象构造完成，返回一个指向该对象的指针。
// new表达式
std::string *sp = new std::string("a value");  // 分配并初始化一个std::string对象
std::string *arr = new std::string[10];        // 分配10个默认初始化的std::string对象
```

##### **一条delete的两步骤**

1. **对所指对象或者对象数组执行对应的析构函数；**
2. **编译器调用名为`operator delete`或`operator delete[]`的标准库函数释放内存空间。**

```cpp
//delete：调用析构函数--->释放空间
// delete表达式
delete sp;          // 销毁*sp,然后释放sp指向的内存空间
delete [] arr;      // 销毁数组中的元素,然后释放对应的内存空间

```

#### 总结

**对于内置类型 `new / delete / malloc/free` 可以混用。**

**区别：**

 **1、 new/delete 是C++中的运算符。 `malloc / free` 是函数。** 

**2、 `malloc`申请内存空间时，手动计算所需大小，`new`只需类型名，自动计算大小；**

 **3、 `malloc`申请的内存空间不会初始化，`new`可以初始化；**

 **4、 `malloc`的返回值为`void*`, 接收时必须强转，`new`不需要；**

 **5、 `malloc`申请内存空间失败时，返回的是`NULL`，使用时必须判空；**

​		**`new`申请内存空间失败时抛出异常`bad_alloc`，所以要有捕获异常处理程序。**

# 第八章 C++函数高级特性

对比于 C 语言的函数，C++增加了**重载（overloaded）**、**内联（inline）**、**const** 和 **virtual** 四种新机制。其中重载和内联机制既可用于全局函数也可用于类的成员函数，`const` 与 `virtual` 机制仅用于类的成员函数。

## 8.1 函数重载

在C++中可以为两个或两个以上的函数提供相同的函数名称，只要参数类型不同，或参数类型相同而参数的个数不同，称为**函数重载**。

**重载函数的意义在于减少了函数名的数量，避免了名字空间的污染，提高了程序的可读性。**

```cpp
int my_max_i(int a,int b){ return a >b?a:b}

double my_max_d(double a,double b){ return a >b?a:b}

char my_max_c(char a,char b){ return a >b?a:b}

int main()
{
		int ix=my_max(12,23);
		double dx=my_max(12.23,34.45);
		char chx=my_max(‘a’,'b');

		return 0;
}

这些函数都执行了相同的一般性动作——都返回两个形参中的最大值;从用户的角度来看，只有一种操作，就是判断最大值。

这种词汇上的复杂性不是”判断参数中的最大值“问题本身固有的，而是反映了程序设计环境的一种局限性:在同一个域中出现的名字必须指向一个唯实体(函数体)。

函数重载把程序员从这种词汇复杂性中解放出来。
```

### 判断函数重载的规则

（1）如果两个函数的参数表相同，但是返回类型不同， 会被标记为编译错误:函数的重复声明。
（2）参数表的比较过程与形参名无关。

（3）如果在两个函数的参数表中，只有缺省实参不同，则第二个被视为第一个的重复声明。

（4）`typedef`为现有的数据类型提供了一个替换名，它并没有创建一个新类型 ，因此如果两个函数参数表的区别只在于一个使用了 `typedef` ,而另一个使用了与`typedef`相应的类型。则该参数表被视为相同的参数列表。

（5）当一个形参类型有`const`或`volatile`修饰时，如果形参是按值传递方式定义,在识别函数声明是否相同时,并不考虑`const`和`volatile`修饰符。

当一个形参类型有`const`或volatile修饰时,如果形参定义指针或引用时,在识别函数声明是否相同时，就要考虑`const`和`volatile`修饰符。

（6）如果在两个函数的参数表中,形参类型相同,而形参个数不同,形参默认值将会影响函数的重载。（二义性）

### 函数重载的解析步骤

（1）确定函数调用考虑的重载函数的集合，确定函数调用中实参表的属性。

（2）从重载函数集合中选择函数，该函数可以在(给出实参个数和类型)的情况下可以调用函数。

（3）选择与调用最匹配的函数。

### C++ 如何做到函数重载

C++代码在编译时会根据参数列表对函数进行重命名，当发生函数调用时，编译器会根据传入的实参去逐个匹配，以选择对应的函数，如果匹配失败，编译器就会报错。

### 名字粉碎（名字修饰）

**在C/C++中，一个程序要运行起来,需要经历以下几个阶段:预编译(预处理)、编译、汇编、链** **接。Name Mangling是一种在编译过程中，将函数名、变量名的名字重新命名的机制。**

“C"或者"C++”函数在内部(编译和链接)通过修饰名识别。修饰名是编译器在编译函数定义或者原型时生成的字符串

修饰名由函数名、类名、调用约定、返回类型、参数等共同决定。

#### C++编译时函数修饰约定规则

`_cdecl`调用约定:

（1）以”?”标识函数名的开始，后跟函数名;

（2）函数名后面以"@@YA"标识参数表的开始，后跟参数表;

（3）参数表以代号表示:

```cpp
 X——void,

 D——char,

 E——unsigned char,

 F——short,

 H——int,

 |——unsigned int,

 J——long,

 K—— unsigned long,

 M ——float,

 N——double,

 _N——bool,

 PA——表示指针，后面的代号表明指针类型，如果相同类型的指针连续出现，以”0”代 替，一个”0”代表一次重复。
```

（4）参数表的第一项为该函数的返回值类型，其后依次为参数的数据类型,指针标识在其所指数据类型前。

（5）参数表后以"@Z”标识整个名字的结束，如果该函数无参数，则以"Z"标识结束。

### extern关键字

**extern放在变量和函数声明之前，表示该变量或者函数在别的文件中已经定义，提示编译器在编译时要从别的文件中寻找**。

extern ”C“：函数名以C的方式修饰约定规则

extern ”C++“：函数名以C++的方式修饰约定规则

```cpp
如果 C++程序要调用已经被编译后的 C 函数，该怎么办？
假设某个 C 函数的声明如下：
void foo(int x, int y); 
该函数被 C 编译器编译后在库中的名字为_foo，而 C++编译器则会产生像_foo_int_int之类的名字用来支持函数重载和类型安全连接。由于编译后的名字不同，C++程序不能直接调用 C 函数。C++提供了一个 C 连接交换指定符号 extern“C”来解决这个问题。
例如：
extern “C” 
{ 
 void foo(int x, int y); 
 … // 其它函数 
} 
或者写成
extern “C” 
{ 
 #include “myheader.h” 
 … // 其它 C 头文件 
} 
这就告诉 C++编译译器，函数 foo 是个 C 连接，应该到库中找名字_foo 而不是找_foo_int_int。C++编译器开发商已经对 C 标准库的头文件作了 extern“C”处理，所以我们可以用＃include 直接引用这些头文件
```

**作用：**

**（1）声明外部变量**

在声明全局变量时，不同的文件在编译器编译时是不透明的，比如在A.c中定义int i，同时在B.c中定义int i，编译器编译时是不会报错的，但是当链接linking时会报错重复定义。当需要使用同一全局变量时，如：在A.c中定义了int i，在B.c中需要调用i，只需要在B.c中声明extern int i，表示该变量在别的文件中已经定义，编译时便不会出错，在linking…的时候会自动去查找定义过的变量i。

**（2）extern函数声明**

extern void fun()暗示该函数可能在别的文件中定义过，它和定义为void fun()，没什么区别，其用处在于复杂的项目用通过在函数前添加extern声明来取代用include" *.h"来声明函数。

**（3）单方面修改函数原型**

当声明extern void fun(int i,int j,int k)时，在之后的调用中如果按照是fun(x,y,z)的原型调用时是没有问题的，但是如果要对该函数进行修改比如输入参数，调用时为fun(x,y)此时编译器就会报错了，解决办法就是去掉extern，该头文件中声明void fun(int i,int j)，并对该函数进行修改，之后在调用的文件中包含该函数所在的头文件" *.h"即可。

**补充：**

并不是两个函数的名字相同就能构成重载。**全局函数和类的成员函数同名不算重载，因为函数的作用域不同**。

```cpp
void Print(…); // 全局函数 
class A 
{… 
	void Print(…); // 成员函数 
}

::Print(…); // 表示 Print 是全局函数而非成员函数
//如果类的某个成员函数要调用全局函数
Print，为了与成员函数 Print 区别，全局函数被调用时应加‘::’标志
```

### 隐式类型转换导致重载函数产生二义性

```cpp
#include <iostream.h> 
void output( int x); // 函数声明 
void output( float x); // 函数声明 
 
void output( int x) 
{ 
	cout << " output int " << x << endl ; 
} 
 
void output( float x) 
{ 
	cout << " output float " << x << endl ; 
} 
 
void main(void) 
{ 
    int x = 1; 
    float y = 1.0; 
    output(x); // output int 1 
    output(y); // output float 1 
    output(1); // output int 1 
    // output(0.5); // error! ambiguous call, 因为自动类型转换 
    output(int(0.5)); // output int 0 
    output(float(0.5)); // output float 0.5 
}
```

由于数字本身没有类型，将数字当作参数时将自动进行类型转换（称为**隐式类型转换**）。语句 output(0.5)将产生编译错误，<u>因为编译器不知道该将 0.5 转换成 int 还是 float 类型的参数</u>。

## 8.2成员函数的重载、覆盖与隐藏

### 8.2.1 重载与覆盖

成员函数**被重载**的特征：  

- 相同的范围（在同一个类中）；  
- 函数名字相同；  
- 参数不同；  
- virtual 关键字可有可无。 

**覆盖**是指派生类函数覆盖基类函数，特征是：

- 不同的范围（分别位于派生类与基类）；  
- 函数名字相同；  
- 参数相同；  
- 基类函数必须有 virtual 关键字。

```cpp
//函数 Base::f(int)与 Base::f(float)相互重载，而 Base::g(void)被 Derived::g(void)覆盖。

#include <iostream.h> 
class Base 
{ 
public: 
    void f(int x){ cout << "Base::f(int) " << x << endl; } 
    void f(float x){ cout << "Base::f(float) " << x << endl; } 
    virtual void g(void){ cout << "Base::g(void)" << endl;} 
}; 
 
class Derived : public Base 
{ 
public: 
	virtual void g(void){ cout << "Derived::g(void)" << endl;} 
}; 
 
void main(void) 
{ 
    Derived d; 
    Base *pb = &d; 
    pb->f(42); // Base::f(int) 42 
    pb->f(3.14f); // Base::f(float) 3.14 
    pb->g(); // Derived::g(void) 
} 
```

### 8.2.2 隐藏

**“隐藏”是指派生类的函数屏蔽了与其同名的基类函数**。

- 如果派生类的函数与基类的函数同名，但是参数不同。此时，不论有无 virtual 关键字，基类的函数将被隐藏（注意别与重载混淆）。  
- 如果派生类的函数与基类的函数同名，并且参数也相同，但是基类函数没有 virtual 关键字。此时，基类的函数被隐藏（注意别与覆盖混淆）。 

```cpp
#include <iostream.h> 
class Base 
{ 
public: 
    virtual void f(float x){ cout << "Base::f(float) " << x << endl; } 
    void g(float x){ cout << "Base::g(float) " << x << endl; } 
    void h(float x){ cout << "Base::h(float) " << x << endl; } 
}; 
class Derived : public Base 
{ 
public: 
    virtual void f(float x){ cout << "Derived::f(float) " << x << endl; } 
    void g(int x){ cout << "Derived::g(int) " << x << endl; } 
    void h(float x){ cout << "Derived::h(float) " << x << endl; } 
};

函数 Derived::f(float)覆盖了 Base::f(float)。 有virtual
函数 Derived::g(int)隐藏了 Base::g(float)，而不是重载。 
函数 Derived::h(float)隐藏了 Base::h(float)，而不是覆盖。无virtual
```

#### 隐藏作用

- 写语句 pd->f(10)的人可能真的想调用 Derived::f(char *)函数，只是他误将参数写错了。**有了隐藏规则，编译器就可以明确指出错误**。否则，编译器会静悄悄地将错就错，程序员将很难发现这个错误，流下祸根。 
- 假如类 Derived 有多个基类（多重继承），有时搞不清楚哪些基类定义了函数 f。如果没有隐藏规则，那么 pd->f(10)可能会调用一个出乎意料的基类函数 f。尽管隐藏规则看起来不怎么有道理，但它的确能消灭这些意外。

```cpp
class Base 
{ 
public: 
	void f(int x); 
}; 

class Derived : public Base 
{ 
public: 
	void f(char *str); 
}; 

语句 pd->f(10)的本意是想调用函数 Base::f(int)，但是 Base::f(int)不幸被 Derived::f(char *)隐藏了。由于数字 10不能被隐式地转化为字符串，所以在编译时出错。
void Test(void) 
{ 
    Derived *pd = new Derived; 
    pd->f(10); // error 
}
```

## 8.3 参数的缺省值

有一些参数的值在每次函数调用时都相同，书写这样的语句会使人厌烦。C++语言采用参数的缺省值使书写变得简洁（**在编译时，缺省值由编译器自动插入**）。

- 参数缺省值只能出现在函数的声明中，而不能出现在定义体中。 

  ```cpp
  void Foo(int x=0, int y=0); // 正确，缺省值出现在函数的声明中 
   
  void Foo(int x=0, int y=0)// 错误，缺省值出现在函数的定义体中 
  { 
  	… 
  }
  
  //函数的实现（定义）本来就与参数是否有缺省值无关，所以没有必要让缺省值出现在函数的定义体中。
  //参数的缺省值可能会改动，显然修改函数的声明比修改函数的定义要方便。
  ```

**使用参数的缺省值并没有赋予函数新的功能，仅仅是使书写变得简洁一些。 它可能会提高函数的易用性，但是也可能会降低函数的可理解性。所以我们只能适当地 使用参数的缺省值，要防止使用不当产生负面效果。**

## 8.4 运算符重载

[参考](https://www.cnblogs.com/ECJTUACM-873284962/p/6771262.html#_label0)

### 为什么会有运算符重载?

运算符，例如+，-，*，/只能对基本类型的常量或者变量进行运算，不能用于**对象**之间的运算,但在实际编程过程中会存在很多自定义的类型需要进行运算操作,此时原本的基本运算符不在适用,就需要对其进行**拓展**,即**运算符重载**,从而进行这些对象之间的运算.

### 什么是运算符重载？

“重载"——重新定义——创建**运算符函数**——对原本的运算符函数重载

**运算符函数**的定义与其他函数的定义类似，惟一的区别是运算符函数的函数名是由关键字operator和其后要重载的运算符符号构成的.

**运算符重载格式:**

**<返回类型说明符> operator <运算符符号>(<参数表>) {    <函数体> }**

### 举例:复数类的运算符+,-,*,/重载

```cpp
class Complex//复数类
{
	int Real;
	int Image;
public:
	Complex(int r=0,int i=0) :Real(r),Image(i)//构造函数
	{
		cout << "Creat Complex" << this << endl;
	}
	~Complex()//析构函数
	{
		cout << "Destroy Complex" << this << endl;
	}
	void Print()const//输出打印方法
	{
		cout << "Real: " << Real << "Image: " << Image << endl;
	}
    
    //+重载
	Complex operator +(const Complex& c) const
	{
		return Complex(this->Real + c.Real, this->Image + c.Image);
	}

	//-重载
	Complex operator -(const Complex& c) const
	{
		return Complex(this->Real - c.Real, this->Image - c.Image);
	}
    
	///重载
	Complex operator /(const Complex& c) const
	{
		return Complex((Real * c.Real + Image * c.Image) / (c.Real * c.Real + c.Image * c.Image),
			(Image * c.Real - Real * c.Image) / (c.Real * c.Real + c.Image * c.Image));
	}

	//*重载
	Complex operator *(const Complex& c)const
	{
		return Complex((this->Real * c.Real) - (this->Image * c.Image), (this->Image * c.Real) + (this->Real * c.Image));
	}
    
}
```

### 运算符重载时所需要遵守的一些规则

![image-20231025150413027](https://gitee.com/zhengzhivon/images/raw/master/imgs/image-20231025150413027.png)

1.不能够重载的运算符:

```cpp
"."//类关系运算符;
".*"//成员指针运算符;
"sizeof"//;
"::"//作用域运算符;
"?:"//三目运算符;
```

2.运算符重载实质上是函数重载，因此编译程序对运算符重载的选择，遵循**函数重载**的选择原则。

3.重载运算符限制在C++语言中**已有的运算符**范围内的允许重载的运算符之中，不能创建新的运算符。

4.重载之后的运算符不能改变运算符的**优先级和结合性**，也不能改变运算符操作数的个数及语法结构。

5.运算符重载不能改变该运算符用于内部类型对象的含义。(不会覆盖原始的定义,是一种拓展——函数重载)

它只能和用户自定义类型的对象一起使用，或者用于用户自定义类型的对象和内部类型的对象混合使用时。

6.运算符重载是针对新类型数据的实际需要<u>对原有运算符进行的适当的改造</u>，重载的功能应当与原有功能相类似，避免没有目的地使用重载运算符。

### 运算符重载时的this指针

当运算符重载为类的成员函数时，**函数的参数个数比原来的操作数要少一个（后置单目运算符除外）**，这是因为**成员函数用this指针隐式地访问了类的一个对象，它充当了运算符函数最左边的操作数。**

(1) 双目运算符重载为类的成员函数时，函数只显式说明一个参数，该形参是运算符的右操作数。

(2) 前置单目运算符重载为类的成员函数时，不需要显式说明参数，即函数没有形参。

(3) 后置单目运算符重载为类的成员函数时，函数要带有一个整型形参。   

调用成员函数运算符的格式如下:

 **<对象名>.operator <运算符>(<参数>)**   它等价于   **<对象名><运算符><参数>**   例如：a+b等价于`a.operator +(b)`

## 8.5 函数内联

[内联参考](https://blog.csdn.net/cxy_zjt/article/details/124776420?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-1-124776420-blog-120113957.235%5Ev38%5Epc_relevant_sort_base3&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-1-124776420-blog-120113957.235%5Ev38%5Epc_relevant_sort_base3&utm_relevant_index=1)

https://blog.csdn.net/cxy_zjt/article/details/124776420?spm=1001.2014.3001.5502

[参考2](https://blog.csdn.net/wzz953200463/article/details/116303725?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169864571716800215022659%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=169864571716800215022659&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-116303725-null-null.142^v96^pc_search_result_base3&utm_term=C%2B%2B%E5%86%85%E8%81%94%E5%87%BD%E6%95%B0&spm=1018.2226.3001.4187)

当程序执行函数调用时，系统要建立栈空间，保护现场，传递参数以及控制程序执行的转移等等， 这些工作需要系统时间和空间的开销。

函数是一个可以重复使用的代码块，CPU 会一条一条地挨着执行其中的代码。CPU 在执行主调函数代码时如果遇到了被调函数，主调函数就会暂停，CPU 转而执行被调函数的代码；被调函数执行完毕后再返回到主调函数，主调函数根据刚才的状态继续往下执行。

函数调用是有时间和空间开销的。**程序在执行一个函数之前需要做一些准备工作，要将实参、局部变量、返回地址以及若干寄存器都压入栈中，然后才能执行函数体中的代码**；函数体中的代码执行完毕后还要清理现场，将之前压入栈中的数据都出栈，才能接着执行函数调用位置以后的代码。如果函数体代码比较多，需要较长的执行时间，那么函数调用机制占用的时间可以忽略；**如果函数只有一两条语句，那么大部分的时间都会花费在函数调用机制上，这种时间开销就就不容忽视**。

为了消除函数调用的时空开销，C++ 提供一种提高效率的方法，即在编译时将函数调用处用函数体替换，类似于C语言中的宏展开。**这种在函数调用处直接嵌入函数体的函数称为内联函数（Inline Function），又称内嵌函数或者内置函数。**

<img src="https://gitee.com/zhengzhivon/images/raw/master/imgs/image-20231030143728345.png" alt="image-20231030143728345" style="zoom: 67%;" />

```cpp
call代表着函数调用，此时会存在函数的压栈等一系列操作
```

<img src="https://gitee.com/zhengzhivon/images/raw/master/imgs/image-20231030143843067.png" alt="image-20231030143843067" style="zoom:67%;" />

```cpp
使用inline关键字修饰函数my_add()之后，发现汇编代码中没有了call操作，说明省去了一系列函数调用操作（压栈、跳转、退栈和返回操作等），而是在寄存器种直接替换操作，提高了效率。
```

### 内联函数`inline`如何工作

对于任何内联函数，编译器在符号表里放入函数的声明（包括名字、参数类型、返回值类型）。如果编译器没有发现内联函数存在错误，那么该函数的代码也被放入符号表里。在调用一个内联函数时，编译器首先检查调用是否正确（进行类型安全检查，或者进行自动类型转换，当然对所有的函数都一样）。如果正确，**内联函数的代码就会直接替换函数调用**，于是省去了函数调用的开销。这个过程与预处理有显著的不同，因为**预处理器不能进行类型安全检查，或者进行自动类型转换**。假如内联函数是成员函数，对象的地址（this）会被放在合适的地方，这也是预处理器办不到的。  

**关键字 `inline`必须与函数定义体放在一起才能使函数成为内联，仅将 `inline`放在函数声明前面不起任何作用**。

```cpp
void Foo(int x, int y); 
inline void Foo(int x, int y) // inline 与函数定义体放在一起 
{ 
	… 
}
```

`inline`是一种“用于实现的关键字”，而不是一种“用于声明的关键字”。 一般地，用户可以阅读函数的声明，但是看不到函数的定义。**声明与定义不可混为一谈，用户没有必要、也不应该知道函数是否需要内联**。

```cpp
#include <iostream>
using namespace std;
 
//声明内联函数
void swap1(int *a, int *b); //也可以添加inline，但编译器会忽略
 
int main()
{
    int m, n;
    cin>>m>>n;
    cout<<m<<", "<<n<<endl;
    swap1(&m, &n);
    cout<<m<<", "<<n<<endl;
 
    return 0;
}
 
//定义内联函数
inline void swap1(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
```

### 宏定义与内联函数

内联函数可以看作是宏函数的升级版本，将宏函数的优点保留，将缺点去掉。

**C++ 语言的函数内联机制既具备宏代码的效率，又增加了安全性，而且可以自由操作类的数据成员**。所以在 C++ 程序中，应该用内联函数取代所有宏代码，“断言 assert” 恐怕是唯一的例外。

assert是仅在Debug版本起作用的宏，它用于检查“不应该”发生的情况。为了不在程序的 Debug 版本和 Release版本引起差别，assert 不应该产生任何副作用。如果 assert 是函数，由于函数调用会引起内存、代码的变动，那么将导致 Debug 版本与 Release 版本存在差异。所以 assert 不是函数，而是宏。

```cpp
//宏定义的缺点
1.不方便调试宏。（因为预编译阶段进行了替换）
	由于宏是预编译程序来处理，其替换的函数不会进入到符号表中，所以在运行时，不会带来额外的时间和空间开销，而函数会在运行时执行压栈出栈的操作，存在函数调用的开销。所以宏是不可以调试的，而函数可以进行单步调试。
2.导致代码可读性差，可维护性差，容易误用。
3.没有类型安全的检查。
    
#define MAX(a,b) (a)>(b)?(a):(b)
    
result = MAX(i,j)+2;
//被预处理器扩展为 
result = (i)>(j)?(i):(j)+2;

//由于运算符"+"比运算符"?:"的优先级高，所以上述语句并不等价于
result = ((i)>(j)?(i):(j))+2;

如果把宏代码改写成：
#define MAX(a,b) ((a)>(b)?(a):(b))
此时可以解决优先级问题，但是：
result = MAX(i++,j);
//被预处理器扩展为 
result = (i++)>(j)?(i++):(j) //在同一个表达式中i被两次求值。
```

#### 宏定义与内联函数的区别

- **内联函数在编译时展开，带参的宏在预编译时展开。** 
- **内联函数直接嵌入到目标代码中，带参的宏是简单的做文本替换。** 
- **内联函数有类型检测、语法判断等功能，宏只是替换。**
- **内联函数可以调试，而宏定义不可以。**
- **内联函数可以访问类的成员变量，宏定义不能。**

- **在类中声名同时定义的成员函数，拥有内联属性。**

- **内联函数是函数，宏不是函数。**


### 内联函数总结

**内联函数是针对C语言中宏定义的优化，把这个以空间换时间的优化从预编译阶段调整到了编译阶段，所以增加了对使用了内联机制的函数的类型安全检查，或者进行自动类型转换等操作**。

**内联以代码膨胀（拷贝）为代价，仅仅省区了函数调用的开销，从而提高程序的执行效率。（开销指的是参数的压栈、跳转、退栈和返回操作）**。

- 如果函数体内代码比较长，使用内联将导致可执行代码膨胀过大。
- 如果函数体内出现循环或者其他复杂的控制结构，那么执行函数体内代码的时间将比函数调用的开销大得多。

# 第九章 类的构造函数、析构函数与赋值函数

数据成员多为私有的，要对它们进行初始化，必须用一个公有函数来进行。同时这个函数应该在且仅在定义对象时自动执行一次。称为**构造函数**（constructor） 。 

**构造函数用途：1）创建对象，2）初始化对象中的属性，3）类型转换。**

```cpp
C++编译器将自动为 A 产生四个缺省的函数，如
    
A(void); // 缺省的无参数构造函数 
A(const A &a); // 缺省的拷贝构造函数 
~A(void); // 缺省的析构函数 
A & operate =(const A &a); // 缺省的赋值函数
```

为什么有缺省的函数，还需要自行编写？

- 如果使用“缺省的无参数构造函数”和“缺省的析构函数”，等于放弃了自主“初始化”和“清除”的机会
- “缺省的拷贝构造函数”和“缺省的赋值函数”均采用“位拷贝”而非“值拷贝”**（浅拷贝和深拷贝）** 的方式来实现，倘若类中含有指针变量，这两个函数注定将出错。**（error？）**

```
建议参考Effective c++第三版第二章去了解C++正真的构造，析构和赋值操作。
“默认的拷贝构造函数”和“缺省的赋值函数”均采用“位拷贝”而非“值拷贝”的方式来实现” ==> 这句话明显错误呀！至于怎么错就靠你自己去编译器调试了
"如果在类中没有显式地声明一个拷贝构造函数，那么，编译器将会自动生成一个默认的拷贝构造函数" ==> 这句话也错，至于怎么错就靠你自己去编译器调试了
“ 如果没有自定义复制构造函数，则系统会创建默认的复制构造函数，但系统创建的默认复制构造函数只会执行“位拷贝”” ==> 这句话也错
默认的拷贝赋值函数产生机会：如果我们没有为类定义拷贝构造函数和赋值操作符，但我们代码中又使用到了这些，编译器会自动为我们提供拷贝构造函数和赋值操作符。

默认拷贝构造函数基本工作原理：对所有的非POD类型成员变量执行拷贝构造，POD类型成员变量则进行位拷贝，当成员变量都是POD类型的时候，编译器也许不会产生拷贝构造函数，只是对对象进行位拷贝。

默认operator=基本工资原理：对所有的非POD类型成员变量执行operator=操作，POD类型成员变量则进行位拷贝，当成员变量都是POD类型的时候，编译器也许不会产生operator=，只是对对象进行位拷贝。

从上面两个工作原理看到：

1.当class成员变量是有const修饰、引用类型、不能够提供operator=操作(例如boost::nocopyable)时候就不会产生operator=，我们对这个class对象进行赋值操作的时候就是编译出错。

2.当class成员变量是不能够提供拷贝构造操作(例如boost::nocopyable)时候就不会产生拷贝构造函数，我们对这个class对象进行拷贝构造操作的时候就是编译出错。

以前(2005年前？)c++各种参考文献对构造、析构和拷贝关注较多的是“深拷贝”和“浅拷贝”问题，现在的c++可能考虑更多的是如何保证不被拷贝^_^(个人见解)。
```



## 构造函数的定义与使用