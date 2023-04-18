# 【C++学习】命名空间namespace

资料：[namespace](https://blog.csdn.net/fengbingchun/article/details/78575978?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522165234777416782246410616%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=165234777416782246410616&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~baidu_landing_v2~default-1-78575978-null-null.142^v9^control,157^v4^control&utm_term=C%2B%2B+%E4%B8%AD%E7%9A%84namespace&spm=1018.2226.3001.4187)

## 为什么引入命名空间`namespace`

命名空间(`namespace`)为防止名字冲突提供了更加可控的机制。命名空间分割了全局命名空间，其中每个命名空间是一个作用域。通过在某个命名空间中定义库的名字，库的作者以及用户可以避免全局名字固有的限制。

## 命名空间的定义

**命名空间定义：**一个命名空间的定义包含两部分：首先是关键字`**namespace**`，随后是**命名空间的名字**。在命名空间名字后面是一系列由花括号括起来的声明和定义。

只要能出现在全局作用域中的声明就能置于命名空间内，主要包括：**类、变量(及其初始化操作)、函数(及其定义)、模板和其它命名空间**。

命名空间结束后无须分号，这一点与块类似。和其它名字一样，命名空间的名字也必须在定义它的作用域内保持唯一。

命名空间既可以定义在全局作用域内，也可以定义在其它命名空间中，但是不能定义在函数或类的内部。命名空间作用域后面无须分号。

**（1）普通定义：**

```c++
namespace cpp
{
		int max=10;

		int min=0;

		int my_add(int a,int b){return a+b;}
}
```

**（2）嵌套：**

```c++
namespace Primer
{
		double pi=3.14;

		double my_add(double a,double b){return a+b;}

		namespace Matrix
		{
				char my_max(char a,charb){return a>b?a:b;}
		}
}
```

**（3）同一个工程中允许存在多个相同名称的命名空间：**

```c++
namespace cpp
{
		floar pi=3.14;

		int my_sub(int a,int b)
		{
				min=a-b;
				return min;
		}
}
```

**一个命名空间就定义了一个新的作用域，命名空间中的所有内容都局限于该命名空间中。**

## 每个命名空间都是一个作用域

和其它作用域类似，命名空间中的每个名字都必须表示该空间内的唯一实体。因为不同命名空间的作用域不同，所以在不同命名空间内可以有相同名字的成员。

定义在某个命名空间中的名字可以被该命名空间内的其它成员直接访问，也可以被这些成员内嵌作用域中的任何单位访问。位于该命名空间之外的代码则必须明确指出所用的名字属于哪个命名空间。

## **未命名的命名空间**(`unnamed namespace`)

是指关键字`namespace`后紧跟花括号括起来的一系列声明语句。未命名的命名空间中定义的变量拥有静态生命周期：它们在第一次使用前创建，并且直到程序结束才销毁。

## 命名空间的使用

### 1.加命名空间及作用域限定符

```c++
int main()
{
		int a = cpp::my_add(12,23);
		printf("%1fn",primer::pi);
		printf("%fn", cpp::pi);
		Primer: :Matrix::my_max('a','b');

		return 0;
}
```



### 2.使用using将命名空间中成员引入

**使用using声明可只写一次限定修饰名。 using声明以关键字using开头,后面是被限定修饰的名字空间成员名:**

```c++
using cpp::pi;
using Primer::Matrix::my_max;

int main()
{
		printf("%1fn",Primer: :pi);
		printf("%fn"， pi); // xpp::
		my_ max('a','b');
		
		return 0;
}
```



### 3.使用`using namespace`命名空间引入

**使用using指示符可以一次性地使名字空间中所有成员都可以直接被使用，比using声明方便。**
**using指示符;以关键字using开头,后面是关键字`namespace`,然后是名字空间名。**

`using namespace 名字空间名`;

```c++
using namespace ldy ;
int main()
{
		printf("%1f n", Primer: :pi);
		printf("%fn"， pi);// cpp::
		my_ add(12,23); // cpp::
		return 0;
}
```



## 使用using指示符

**标准C++库中的所有组件都是在一个被称为std的名字空间中声明和定义的。 在采用标准C++的平台**

**上使用标准C++库中的组件,只要写一个using指示符:`using namespace std`就可以直接使用标准C++库中的所有成员。这是很方便的。**

