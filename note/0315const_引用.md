# const、指针、引用

[TOC]



## const修饰指向与变量本身

```c++
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

```c++
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

```c++
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

## 指针之间的赋值，数值兼容性

```c++
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

```c++
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

## 引用&（别名）

```c++
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

## 引用的特点

1. **定义引用必须初始化**
2. **没有空引用**
3. **没有引用的引用（int&& x）,不能一次第一所谓的二级引用**

```c++
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

## 引用作为形参相较于指针的区别

```c++
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

## 引用与const的关系

```c++
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

```c++
int main()
{
    const int a=10;
    //int& x=a;	error	常变量不能被修改，利用普通引用则可以通过引用x来修改a
    const int& y=a;
}
```

## 函数形参设计

```c++
void fun_a(int x)
{}

void fun_b(int& y)
{}

void fun(const int& y)
{}
```

## 常引用

```c++
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

## 左值&右值&右值引用

```c++
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

## 其他引用形式

```c++
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

```c++
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

## 引用和指针的区别（重点）

**引用是指针的语法糖**

### 语法规则上的区别

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

```c++
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

```c++
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

```C++
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

```c++
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

```c++
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

## 引用的使用

```c++
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

```c++
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