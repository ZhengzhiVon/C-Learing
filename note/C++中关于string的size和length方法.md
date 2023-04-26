# C++中关于String的size()和length()方法

## 函数声明定义

```c++
//length()
length() const _GLIBCXX_NOEXCEPT
{ return _M_rep()->_M_length; }

//size()
size() const _GLIBCXX_NOEXCEPT
{ return _M_rep()->_M_length; }
```

## 总结&示例

- **length()和size()方法的声明和定义完全相同。**
- **其原因是string最早只有length(),只能用来获取字符串长度；而在出现STL之后，为了兼容加入了和STL容器求长度的函数一个名字的size()，这样就可以方便的使用于STL的算法,例如获取vector容器的长度。**

```c++
//length()
string str = "hello";
int len = str.length();//5

//size
string str = "world";
vector <int> num(10,5)
int lenstr = str.size();//5
int lenvec = num.size();//10

```

