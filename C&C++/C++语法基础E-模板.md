# 模板

C++函数模板：建立一个通用函数，其函数类型和形参类型不具体制定，用一个虚拟的类型来代表。这个通用函数就称为**函数模版**

* C++提供两种模版机制：**函数模板**和**类模板**
* 泛型编程：类型参数化，又称**参数模板**

## 01/函数模板基础语法

1. 创建函数模版：`template<typename T>`T是一个通用类型，告诉编译器后面紧跟着的函数或类中出现了T，不要报错
2. 调用函数模版：
   * 自动类型推导：必须让编译器推导出一致的T，才能使用模板--不可以进行隐式类型转换
   * 显示指定类型：显示告诉编译器T的类型--可以进行隐式类型转换，如果转不成功，也不可以使用这个模板
   * 模板必须指定出T的类型，才可以使用

```C++
//利用模板实现通用交换函数：T是一个通用类型，告诉编译器后面紧跟着的函数或类中出现了T，不要报错
template<typename T>
void mySwap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
void mySwap2(){}

void test()
{
    int a = 10;
    int b = 20;
    //1、自动类型推导，必须让编译器推导出一致的T，才能使用模板
    mySwap(a,b);
    //2、显示指定类型：可以进行隐式类型转换，如果转不成功，也不可以使用这个模板
    mySwap<int>(a,b);
    //3、模板必须指定出T的类型，才可以使用
    mySwap2<int>();
}
```

```C++
//通过选择法实现int和char排序
template<typename T>
void mySwap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
void mySort(T arr[],int len)
{
    for (int i=0;i<len ;i++)
    {
        int min = i;
        for (int j = i+1; j < len; j++)
        {
            if (arr[min] > arr[j])
            {
                min = j;//记录最小值下标
            }
        }
        if (i != min)//将这两个值交换
        {
            mySwap(arr[i],arr[min]);
        }
    }
}

template<typename T>
void printArr(T arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << endl;
    }
}
int test()
{
    int arr[] = {3,6,2,5,1};
    int len = sizeof(arr) / sizeof(int);
    mySort(arr,len);
    printArr(arr,len);

    char charArr[] = "helloworld";
    int charlen = sizeof(charArr) / sizeof(char);
    mySort(charArr,charlen);
    printArr(charArr,charlen);
}
```

## 02/函数模板和普通函数的区别

1. 如果普通函数和函数模版可以同时调用，优先调用普通函数
2. 如果想强制调用函数模板中的内容，可以使用空参数列表
3. 函数模板也可以发生函数重载
4. 如果函数模板可以产生更好的匹配，那么优先使用的是函数模板

```C++
template<typename T>
void myPrint(T a, T b)
{
    cout << "函数模版" << endl;
}
template<typename T>
void myPrint(T a, T b, T c)
{
    cout << "函数模版<T a, T b, T c>" << endl;
}
void myPrint(int a, int b)
{
    cout << "普通函数" << endl;
}
void test()
{
    //1、如果普通函数和函数模版可以同时调用，优先调用普通函数
    int a = 10;
    int b = 20;
    myPrint(a,b);
    //2、如果想强制调用函数模板中的内容，可以使用空参数列表
    myPrint<>(a,b);
    //3、函数模板也可以发生函数重载
    myPrint(a,b,10);
    //4、如果函数模板可以产生更好的匹配，那么优先使用的是函数模板
    char c = 'c';
    char d = 'd';
    myPrint(c,d);
}
```

## 03/模板机制（了解）

* 编译器并不是把函数模板处理成能够处理任何类型的函数
* 函数模板通过具体类型产生不是的函数
* 编译器会对函数模板进行两次编译，在声明的地方对模板代码本身进行编译，在调用的地方对参数替换后的代码进行编译

## 04/模板局限性及具体化（了解）

***问题：***
模板并不是真正的通用代码，对于一些自定义数据类型，模板有时不能实现效果
***方法：***
可以通过具体化实现对自定义数据类型进行操作

```C++
class Person
{
public:
    Person(string name ,int age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }
    string m_Name;
    int m_Age;
};
template<typename T>
bool myCompare(T& a, T& b)
{
    if (a == b)
    {
        return true;
    }
    return false;
}
//模板具体化
template<> bool myCompare<Person>(Person& a, Person& b)
{
    cout << "调用具体化代码" << endl;
    if (a.m_Name == b.m_Name && a.m_Age == b.m_Age)
    {
        return true;
    }
    return false;
}
void test()
{
    Person p1("Tom",10);
    Person p2("Jerry", 20);       
    bool ret = myCompare(p1,p2);
    if (ret)
    {
        cout << "相等" << endl;
    }
    else
    {
        cout << "不相等" << endl;
    }
}
```

## 05/类模板基本语法

* 类模板：template后紧跟着一个类，那么这个类称为类模板
* 类模板类型可以设置默认参数
* 类模板不能使用自动类型推导，必须显示指定类型

```C++
//类模板：template后紧跟着一个类，那么这个类称为类模板
//类模板中的类型可以设置默认参数
template<class NAMETYPE, class AGETYPE = int>
class Person
{
public:
    Person(NAMETYPE name, AGETYPE age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }
    NAMETYPE m_Name;
    AGETYPE m_Age;
};
void test()
{
    Person<string> p("Tom",11);//类模板不能使用自动类型推导，必须显示指定类型
    cout << "姓名：" << p.m_Name << "年龄：" << p.m_Age << endl;
}
```

## 06/类模板中成员函数的创建时机

类模板中的成员函数并不是在一开始就创建出来的，是在运行时创建的

## 07/类模板作为函数参数


