#include <cstddef>
#include<string>
#include<string.h>
#include<iostream>
#include<thread>
#include<mutex> //互斥锁


using namespace std ;

//饥汉模式

/*
class Object{
private:
    int value;
private:
    Object(int x=0):value(x) {cout<<"create object"<<endl;}
    Object(const Object&) = delete;//表示禁止使用拷贝构造函数来复制对象。
    Object& operator=(const Object&) = delete;//禁止使用赋值运算符来赋值对象
public:
    ~Object(){cout<<"destroy object"<<endl;}
};
//简单类型，没有指针、没有动态的获取资源、没有虚函数、没有文件指针，只有基本类型属性。可以通过赋值构造函数
//如果一个类的对象是单例模式，也可以使用这些语句来防止对象被复制或赋值。单例模式是指一个类只能有一个实例，如果允许对象被拷贝或赋值，就有可能会创建多个实例，违反单例模式的原则。

//如果不写 Object(const Object&) = delete;和Object& operator=(const Object&) = delete;	就会在编译时产生缺省的拷贝构造函数和赋值


/*
class Object{
private:
    int value;
    Object objx;//error 	类中不能出现类类型自身构建的对象，否则在构建对象时会陷入无限递归
}；

class Object{
private:
    int value;
    static Object objx;	//ok
}；
*/

/*
class Object{
private:
    int value;
    static Object objx;	//ok
private:
    Object(int x=0):value(x) {cout<<"create object"<<endl;}
    Object(const Object&) = delete;//表示禁止使用拷贝构造函数来复制对象。
    Object& operator=(const Object&) = delete;//禁止使用赋值运算符来赋值对象
public:
    ~Object(){cout<<"destroy object"<<endl;}
    void SetValue(int x=0) {value=x};
    //void SetValue(Object * const this,int x=0);   //const修饰this指针，进入函数后this指针自身不能被修改

    int GetValue()const {return value;}//常方法
    //int GetValue(const Object* const this);   //第一个const修饰this指针的解引用，即其所指之物

    //静态函数没有this指针，可以拿“对象名/类型名::”调用，不能用const修饰因为其没有this指针
    static Object& GetObject()//类内的成员函数用static修饰，可以直接那类型名调用
    {
        //全局对象objx在函数结束后仍存在，所以可以以引用的形式返回
        return objx;//必须以引用的形式返回，不能以值的形式返回，因为会建立一个将亡值返回(需要调动拷贝构造函数)
    }
};

Object Object::objx(10);
//第一个Object表示对象objx的类型，第二个Object::表示objx时Object的静态成员
//Object类中定义了一个名为objx的静态成员变量，并在类外部进行了初始化。在C++中，静态成员变量的初始化需要在类外部进行，而不是在构造函数中进行。
//objx是Object类类域中定义的一个静态成员变量，则可以调用私有的构造函数，

Object Objz(10);//error 定义一个全局对象不能通过，无法访问private成员，构造函数为私有


int main()
{
    Object::objx.value=0;   //error 在主函数中无法访问objx的私有成员value，只能在类内访问

    Object& obja=Object::GetObject();
    Object& objb=Object::GetObject();

    obja.SetValue(100);
    cout<<objb.GetValue()<<endl;
}

void funa()
{
    Object& obja=Object::GetObject();
    obja.SetValue(100);
}

void funb()
{
    Object& objb=Object::GetObject();
    cout<<objb.GetValue()<<endl;
}
*/

//懒汉模式

std::mutex mtx;	//全局互斥锁

class Object{
private:
    int value;
    static Object* pobj;//定义一个静态指针
private:
    Object(int x=0):value(x) {cout<<"create object"<<endl;}
    Object(const Object&) = delete;//表示禁止使用拷贝构造函数来复制对象。
    Object& operator=(const Object&) = delete;//禁止使用赋值运算符来赋值对象
public:
    ~Object(){cout<<"destroy object"<<endl;}
    void SetValue(int x=0) {value=x};
    
    int GetValue()const {return value;}//常方法
    static Object& GetRefObject()//获得对象的引用。类内的成员函数用static修饰，可以直接拿类型名调用
    {
        //new()操作并非原子操作，所以需要在if()之外对整个判断语句加锁
        mtx.lock();//加锁，创建完成后需要解锁
        if(nullptr == pobj)
        {
            pobj=new Object(10);
            /*new在线程进行中可能被打断
                1 sizeof(Object); 2 malloc(); 3 调用拷贝构造函数构建对象； 4 返回对象地址给pobj。
            */
        }
        mtx.unlock();//解锁
        return *pobj;
    }
};

Object* Object::pobj = nullptr;

void fun1()
{
    Object& obja=Object::GetRefObject();//第一次构建时pobj==nullptr，则调动构造函数构建对象
    obja.SetValue(100);
    cout<< &obja <<endl;
}

void fun2()
{
    Object& objb=Object::GetRefObject();//第二次在调用时pobj!=nullptr,则不再调动构造函数
    cout<<objb.GetValue()<<endl;
    cout<< &objb <<endl;
}

int main()
{
    std::thread tha(fun1);
    std::thread thb(fun2);
    //当static Object& GetRefObject()中未添加互斥锁mutex时，fun1和fun2最终所打印出的obja和objb的地址不同，说明并非一个单例模式
    //当加锁操作在if()语句之中，因为new()操作并非一个原子操作（需要四步来创建对象），所以仍然有可能打印出两个不同的地址，说明构建了两个对象
    
    tha.join();//join()等待线程结束
    thb.join();
}