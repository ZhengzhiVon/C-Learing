# C11中的range-based(基于范围)的for循环

## 传统循环

**必须明确的确定for循环开头以及结尾条件**

```c++
//循环遍历数组
int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };  
for (int i = 0; i < 10; i++){
   	cout << arr[i];  
}

//循环遍历容器
std::vector<int> vec {1,2,3,4,5,6,7,8,9,10};  
for (std::vector<int>::iterator itr = vec.begin(); itr != vec.end(); itr++){
    cout << *itr;
}

int main()
{
    int ar[]={1,2,3,4,5,6,7,8,9,10};
    int n=sizeof(ar)/sizeof(ar[0]);
    int* ip=NULL;
    
    for(int i=0;i<n;++i)
    {
        cout<<ar[i]<<" ";
    }
    
    cout<<endl;
    
    for(ip=ar;ip!=ar+n;++ip)
    {
		cout<<ar[i]<<" ";
    }
    cout<<endl;
    
    return 0;
}
```

## 基于范围的for循环（range-based）

在C98中，不同的容器和数组，遍历的方法不尽相同，写法不统一，也不够简洁，而C++11基于范围的for循环以统一、简洁的方式来遍历容器和数组，用起来更方便了。

### 示例

```c++
int main()
{
	int ar[]={1,2,3,4,5,6,7,8,9,10};
    for(int x:ar)
    {
        cout<<x<<" ";
        cout<<endl;
        
        return 0;
    }
}

//以下基于范围的for循环的一般格式
for(ElemType val: array)
{
	...//statement 循环体处理ElemType
}
```

- **Elemlype：是范围变量的数据类型。它必须与数组（容器）元素的数据类型一样，或者是数组元素可以自动转换过来的类型。**
- **val：是范围变量的名称。该变量将在循环选代期间依次接收数组中的元素值。在第一次循环送代期间它接收的是第一个元素的值；在第二次循环送代期间，它接收的是第二个元素的值；以此类推。**
- **array：是要让该循环进行处理的数组（容器）的名称。该循环将对数组中的每个元素选代一次。**
- **statement：是在每次循环送代期间要执行的语句。要在循环中执行更多的语句，则可以使用一组大括号来包围多个语句。与其他循环体一样，可以用continue来结束本次循环，也可以用break来跳出整个循环。**

### auto+基于范围的for循环

**在`:`之后一定是数组、容器、集合。**

```c++
//可以用auto自动推导val的数据类型
int main()
{
    int ar[]={1,2,3,4,5,6,7,8,9,10};
    for(auto x:ar)
    {
        cout<<x<<" ";
    }
    cout<<endl;
    
    for(auto &x : ar)
    {
		x+=10;
        cout<<x<<"  "''
    }
    
    return 0;
}
```

### 一些练习示例

#### 遍历vector

**使用 range-based for 循环的好处在于可以避免使用下标访问数组或容器时出现的越界问题，同时代码更加简洁易读。**

```c++
//使用 range-based for 循环遍历一个 vector

vector<int> nums = {1, 2, 3, 4, 5};
for (auto num : nums) {
    cout << num << " ";
}

//输出结果为：1 2 3 4 5
```

#### 遍历时修改容器中的元素需使用&

**需要注意的是，使用 range-based for 循环时不能修改容器中的元素，如果需要修改，则需要使用引用类型来声明循环变量。**

```C++
//修改容器中的元素需要用引用类型声明循环变量
//这段代码将 vector 中的每个元素都乘以 2。

vector<int> nums = {1, 2, 3, 4, 5};
for (auto& num : nums) {
    num *= 2;
}

```