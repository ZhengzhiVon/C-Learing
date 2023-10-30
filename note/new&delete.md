# 【C++学习】`malloc/free`与`new/delete`

[参考1](https://blog.csdn.net/cwcmcw/article/details/53873600)

[参考2](https://blog.csdn.net/LINZEYU666/article/details/120165192?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169812905616777224473647%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fblog.%2522%257D&request_id=169812905616777224473647&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~blog~first_rank_ecpm_v1~rank_v31_ecpm-2-120165192-null-null.nonecase&utm_term=%60malloc%2Ffree%60%E4%B8%8E%60new%2Fdelete&spm=1018.2226.3001.4450)

[operator new 和 operator delete](https://blog.csdn.net/liugan528/article/details/125437433?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-1-125437433-blog-80328317.235%5Ev38%5Epc_relevant_sort_base3&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-1-125437433-blog-80328317.235%5Ev38%5Epc_relevant_sort_base3&utm_relevant_index=2)

`malloc`与`free`是 C++/C 语言的标准库函数，`new/delete` 是 C++的运算符。它们都可用于申请动态内存和释放内存。

[内存区域](https://blog.csdn.net/qq_51556066/article/details/130915137?spm=1001.2014.3001.5501)

<img src="https://gitee.com/zhengzhivon/images/raw/master/imgs/image-20231030151335014.png" alt="image-20231030151335014" style="zoom:67%;" />

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

## C的动态内存管理

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

### malloc和free的使用

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

## C++的动态内存管理

### new和delete的使用

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

### new的种类

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

**定位new可以在指定的位置分配内存**

```cpp
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

### operator new 和 operator delete

当我们在C++中使用`new`和`delete`时，其实执行的是全局的`::operator new`和`::operator delete`，不过这两个函数并没有重载`new`表达式或`delete`表达式。

可以重载`operator new`和`operator delete`来控制内存的分配和释放，但不能重载`new`表达式和`delete`表达式。也就是说，**可以自定义的是实际的内存分配和释放，但不能自定义构造函数和析构函数的调用**。
我们提供新的`operator new`函数和`operator delete`函数的目的在于**改变内存分配的方式**，但是不管怎样，都不能改变`new`运算符和`delete`运算符的基本含义。

```cpp
void *operator new(size_t);     //allocate an object
void *operator delete(void *);    //free an object

void *operator new[](size_t);     //allocate an array
void *operator delete[](void *);    //free an array
```

#### 一条new的三步骤

1. **new表达式调用一个名为operator new(或operator new[])的标准库函数，该函数分配一块足够大的、原始的、未命名的内存空间以便存储特定类型的对象(或者对象的数组)；**
2. **编译器运行相应的构造函数以构造这些对象，并为其传入初始值；**
3. **对象被分配了空间并构造完成，返回一个指向该对象的指针。**

```cpp
//new：分配空间--->调用构造函数初始化--->对象构造完成，返回一个指向该对象的指针。
// new表达式
std::string *sp = new std::string("a value");  // 分配并初始化一个std::string对象
std::string *arr = new std::string[10];        // 分配10个默认初始化的std::string对象
```

#### **一条delete的两步骤**

1. **对所指对象或者对象数组执行对应的析构函数；**
2. **编译器调用名为`operator delete`或`operator delete[]`的标准库函数释放内存空间。**

```cpp
//delete：调用析构函数--->释放空间
// delete表达式
delete sp;          // 销毁*sp,然后释放sp指向的内存空间
delete [] arr;      // 销毁数组中的元素,然后释放对应的内存空间

```

### 总结

**对于内置类型 `new / delete / malloc/free` 可以混用。**

**区别：**

 **1、 new/delete 是C++中的运算符。 `malloc / free` 是函数。** 

**2、 `malloc`申请内存空间时，手动计算所需大小，`new`只需类型名，自动计算大小；**

 **3、 `malloc`申请的内存空间不会初始化，`new`可以初始化；**

 **4、 `malloc`的返回值为`void*`, 接收时必须强转，`new`不需要；**

 **5、 `malloc`申请内存空间失败时，返回的是`NULL`，使用时必须判空；**

​		**`new`申请内存空间失败时抛出异常`bad_alloc`，所以要有捕获异常处理程序。**