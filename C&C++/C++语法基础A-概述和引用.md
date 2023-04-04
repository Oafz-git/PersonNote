# 概述和引用

## （一） helloworld

```C++
#include <iostream>     //标准输入、输出流  input ----输入；output ----输出； stdio
using namespace std;    //标准命名空间 
int main()              //程序入口函数
{
    cout << "hello world" << 12334 << endl;//cout 标准输出流，endl是输出换行并刷新缓冲区
    system("pause");// 阻塞
    return EXIT_SUCCESS;
}
```

1. C++编程的两大思想：面向对象、泛型编程
2. C++面向对象的三大特性：封装、继承、多态
3. `::`作用域运算符——当`::`前没有任何作用域情况下，代表使用全局作用域

## （二）namespace的使用

* 用途：解决命名冲突
* 使用：存放变量、函数、结构体、类等。。。
* 声明：必须声明在全局作用域下
* 命名空间可以嵌套命名空间
* 命名空间是开放的（合并），可以随时向命名空间添加新成员

```C++
namespace B
{
    int m_A = 20;
}
namespace B
{
    int m_B = 50;
}
```

* 命名空间是可以匿名的，相当于在变量前加了一个关键字static
  * 静态static的特性：
        1. 生命周期；
        2. 只能在本文件中使用

```C++
namespace 
{
    int m_C = 50;// static int m_C = 50;
}
```

* 命名空间是可以起别名的

```C++
namespace veryLongName
{
    int m_A = 0;
}
namespace veryShortName = veryLongName;//起别名
```

## （三）using声明和using编译指令

```C++
namespace k
{
    int s = 1;    
}
void test1()
{
    //注意：当using声明和就近原则同时出现时，需要避免二义性
    int s = 2;
    using k::s;//using声明
    cout << s << endl;
}
void test2()
{
    //注意：当using编译指令和就近原则同时出现时，优先使用就近原则    
    int s = 2;
    using namespace k;//using编译指令
    cout << s << endl;
}
```

## （四）C++对C语言增强

### 1. 全局变量检测增强

全局变量重定义

### 2. 函数检测增强

* 形参变量类型检测
* 形参传入个数检测
* 函数的声明的返回值检测
* 函数返回值检测

### 3. 类型转换检测

```C++
void test()
{
    char *p = (char*)malloc(64);//(char*)在C语言中可以没有，在C++语言中不能丢失
}
```

### 4. `struct`增强

```C++
    struct Person()
    {
        int age;
        void func(); //C语言的struct中不能放函数；C++语言的struct中可以放函数        
    }
    void test()
    {
        /*struct*/ Person p;//C语言声明结构体时必须加struct；C++语言下声明结构体可以不加struct
    }
```

### 5. bool类型的增强

C语言中没有bool类型；

### 6. 三目运算符增强

```C++
    int a = 10;
    int b = 20;
    *(a > b ? &a : &b) = 100; 
    a > b ? a : b = 100;//在C语言中检测错误；在C++中可以通过；
    //原因：C语言中三目运算符返回值；C++语言中三目运算符返回变量
```

### 7. const增强

* 全局const修饰变量：收到常量区保护，及时语法通过，运行也会报错

```C++
const int m_A = 100;//全局const
void test()
{
    m_A = 200;//直接修改：C和C++都会语法错误
    //间接修改：
    int *p = &m_A;//C语言通过
    int *p = (int*)&m_A;//C++语法通过
    *p = 200;//都是运行报错
}
```

* 局部const修饰变量

```C++
void test()
{
    const int m_B = 100;//局部const
    int *p = &m_B;//C语法通过
    int *p = (int*)&m_B;//C++语法通过
    *p = 200;//C语言可以修改；C++语言无法修改，但不报错
    int arr[m_B];//C语法不可以初始化数组；C++可以
}
```

<img src= "https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Cplus01.png" width=67%/>

* const修饰的全局变量在C语言中默认的是外部链接（变量可以在其它文件中使用）
* const修饰的全局变量在C++语言中默认的是内部链接（变量只能在当前文件使用），需要用`extern`来提高全局变量的作用域
  
***`const`分配内存情况***

1. 对`const`修饰的变量取地址时
2. `const`前加入`extern`修饰后时
3. 使用变量初始化`const`修饰的变量时

```C++
void test()
{
    int a = 10;
    const int m_A = a;
    int *p = (int*)&m_A;//会分配内存
    *p = 20;//可修改
}
```

4. 对于自定义数据类型使用`const`时

```C++
struct Person
{
    string name;
    int age;
};
void test()
{
    const Person p;
    Person **p = (Person *)&p;//会分配内存
    pp->name = "aaa";//可修改
    pp->age = 10;
}
```

***尽量使用`const`代替`#define`***

1. `const`有类型，可进行编译器类型安全检查；`#define`无类型，不可进行类型检查
2. `const`有作用域；而`#define`不重视作用域，默认定义处到文件结尾，如果定义在指定作用域下有效的常量，那么`#define`就不能用

## （五）引用基本语法

### 1. 用途：给变量起别名

### 2. 语法：Type &别名 = 原名;

### 3. 引用必须初始化，一旦初始化，就不能改变指向

### 4. 对数组的引用

```C++
//方式一
int arr[10];
int (&pArr)[10] = arr;
//方式二
//先定义数组别名，再定义引用
typedef int(ARRAY_TYPE)[10];
ARRAY_TYPE &pArr2 = arr;
```

### 5. 参数的传递方式

* 值传递
* 地址传递
* 引用传递

### 6. 引用的注意事项

* 函数的返回值不要是返回局部变量的引用
* 如果函数的返回值是一个引用（返回static修饰的变量），那么这个函数可以作为左值进行运算

### 7. 引用的本质

   在C++内部实现是一个指针常量，引用所占空间大小与指针相同

```C++
Type& aRef = val;//自动转换Type* const ref = &val,这也能说明引用为什么必须初始化
```

### 8. 指针的引用

```C++
struct Person
{
    int age;
};
void allocateSpace(Person *&p)
{
    p = (Person*)malloc(sizeof(Person));
    p->age = 100;
}
void test()
{
    Person *p = NULL;
    allocateSpace(p);
}
```

### 9. 常量的引用

* 引用必须引一块合法的空间；但是加入const之后，语法就通过了。

```C++
int &ref = 10;//错误
const int &ref = 10;//正确，编译器优化，类似于 int temp = 10; const int &ref = temp;
```

* 使用场景

```C++
void showValue(const int &a)
{
    a = 1000;//参数中有const，所以报错
}
void test()
{
    int a = 100;
    showValue(a);
}
```
