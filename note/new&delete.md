# 【C++学习】new&delete

## 利用new和delete在C++中惊醒动态内存管理

### 可执行程序（进程）的虚拟地址空间：

**内核:**操作系统

**栈区:**函数的形参，非静态的局部变量,函数现场保护数据等等,栈是向下增长的。

**共享库的内存映射区域:**用于装载一个共享的动态内存库。用户可使用系统接口创建共享内存,做进程间通信。

**堆区:**用于程序运行时动态内存分配，堆是可以上增长的。

**数据段:**存储全局数据和静态数据，分为.bss和.data。

**代码段:**可执行的程序(机器指令)和常量数据。

## new&delete运算符的使用

```c++
int main()
{

		int n=10;
		int* ipa=new int(10);
		int* ipb=new[n] (10);
		int* ipc=new[n]{1,2,3,4,5,6,7};

		delete ipa;
		delete[]ipb;
		delete[]ipc;

		return 0;	
}
```



## new&delete的函数方式使用

```c++
int main()
{
		int n=10;

		int* ipa=(int*)::operator new(sizeof(int));
		//(int*)malloc(sizeof(int));

		int* ipb=(int*)::operator new(sizeof(int) *n);
		//(int*)malloc(sizeof(int) *n);

		::operator delete(ipa);
		::operator delete(ipb);
		return 0;

}
```



## 定位new(placement new expression)

**定位new可以在指定的位置分配内存**

```c++
int main()
{
		int n =10;
		int* ipa=(int*)ma1loc(sizeof(int));
		int* ipb = (int*)::operator new(sizeof(int) *n);

		new(ipa)int(20);
		new(ipb) int[]{ 1,2,3,4,5,6,7,8,9};
    
		free(ipa);
		::operator delete(ipb);

		return 0;
}
```



## 对于内置类型new/ delete/ malloc/free可以混用

**区别:**

（1）new/delete是C++中的运算符。malloc/ free是函数。

（2）malloc申请内存空间时，手动计算所需大小，new只需类型名，自动计算大小;

（3）malloc申请的内存空间不会初始化，new可以初始化;

（4）malloc的返回值为void*,接收时必须强转，new不需要;

（5）malloc申请内存空间失败时，返回的是NULL，使用时必须判空;

​		  new申请内存空间失败时抛出异常，所以要有捕获异常处理程序;