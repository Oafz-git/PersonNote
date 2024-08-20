# 模板

函数模板：建立一个通用函数，其函数类型和形参类型不具体制定，用一个虚拟的类型来代表。

* C++提供两种模版机制：**函数模板**和**类模板**

* 泛型编程：类型参数化，又称**参数模板**

## 一、函数模板

### 1.基本语法

1. 创建函数模版：`template<typename T>`T是一个通用类型，告诉编译器后面紧跟着的函数或类中出现了T，不要报错
2. 调用函数模版：
   * 自动类型推导：必须让编译器推导出一致的T，才能使用模板--不可以进行隐式类型转换
   * 显示指定类型：显示告诉编译器T的类型--可以进行隐式类型转换，如果转不成功，也不可以使用这个模板
   * 如果没有参数，函数模板必须指定出T的类型，才可以使用

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
    //3、如果没有参数，函数模板必须指定出T的类型，才可以使用
    mySwap2<int>();
}
```

#### 示例：通过选择法实现int和char排序

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

### 2.函数模板和普通函数的区别

1. 如果普通函数和函数模版可以同时调用，**优先调用普通函数**；
2. 在普通函数和函数模版可以同时调用的情况，如果想强制调用函数模板中的内容，可以**使用空参数列表**
3. 函数模板可以重载
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

### 3.模板机制

* 编译器并不是把函数模板处理成能够处理任何类型的函数
* **函数模板**通过具体类型产生不同的函数---**模版函数**
* 编译器会对函数模板进行**两次编译**，在**声明**时对模板代码本身进行编译，在**调用**时对参数替换后的代码进行编译

### 4.模板局限性及具体化

***问题：***
模板并不是真正的通用代码，对于一些自定义数据类型，模板有时不能实现效果  
***方法：***
可以通过**具体化**实现对自定义数据类型进行操作

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



//模板具体化形式
template<> 
bool myCompare<Person>(Person& a, Person& b)
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

## 二、类模板

### 1.基本语法

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

### 2.类模板中成员函数的创建时机

* 类模板中的**成员函数**并不是在一开始就创建出来的，是在**运行时**创建的

```C++
class Person1
{
public:
    void showPeron1(){}
};
class Person2
{
public:
    void showPerson2(){}
};
template<class T>
class Person
{
public:
    void func1()
    {
        obj.showPerson1();
    }
    void func2()
    {
        obj.showPerson2();
    }
    T obj;
};
void test()
{
    Person<Person1> p1;
    p1.func1();
    p1.func2();
}
```

### 3.类模板作为函数参数（三种方式）

```C++
template<class NAMETYPE, class AGETYPE>
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
//1、指定传入类型
void doWork1(Person<string,int> & p)
{
    cout << p.m_Name << p.m_Age << endl;
}
//2、参数模板化
template<class T1, class T2>
void doWork2(Person<T1,T2>& p)
{
    cout << typeid(T1).name() << endl;//查看数据类型
    cout << p.m_Name << p.m_Age << endl;
}
//3、整个类进行模版化
template<class T>
void doWork3(T& p)
{
    cout << p.m_Name << p.m_Age << endl;
}
void test()
{
    Person<string,int> p("A",10);
    doWork3(p);
}
```

### 4.类模板碰到继承的问题及解决

```C++
template<class T>
class Base
{
public:
    T m_A;
}
template<class T1, class T2>
class Son : public Base<T2>
{
public:
    T1 m_B;
}
void test()
{
    Son<int double> s;
}

```

### 5.类模板的类外实现

```C++
template<class T1, class T2>
class Person
{
public:
    Person(T1 name , T2 age);
    void showPerson();
    T1 m_Name;
    T2 m_Age;
};
//构造函数的类外实现
template <class T1, class T2>
Person<T1,T2>::Person(T1 name ,T2 age){}
//成员函数的类外实现
template<class T1, class T2>
void Person<T1,T2>::showPerson() {}
```

#### 6.类模板的分文件编写问题及解决

* 类模板**不建议做分文件编写**，因为成员函数**创建时机在运行阶段**，使用时候必须要包含 `.cpp`才可以
* 将类中的成员函数的声明和实现写到一个文件中，并将文件的后缀名改为`.hpp`即可

### 7.类模板和友元

```C++
template<class T1, class T2> class Person;

//告诉编译器有个模板的声明
template<class T1, class T2> void printPerson2(Person<T1, T2>& p);

//将模板函数的声明和实现写在一起
template<class T1, class T2> 
void printPerson3(Person<T1, T2>& p)
{
    cout << p.m_Name << p.m_Age << endl;
}

template<class T1, class T2>
class Person
{
    //1、全局函数和友元作类内实现
    friend void printPerson(Person<T1, T2>& p)
    {
        cout << p.m_Name << p.m_Age << endl;
    }

    //2、全局函数和友元作类外实现
    friend void printPerson2<>(Person<T1, T2>& p);

    //3、全局函数和友元作类外实现
    friend void printPerson3<>(Person<T1, T2>& p);
public:
    Person(T1 name, T2 age)
    {
        this->m_Age = age;  
        this->m_Name = name;
    }
private:
    T1 m_Name;
    T2 m_Age;
};

template <class T1, class T2>
void printPerson2(Person<T1, T2>& p)
{
    cout << p.m_Name << p.m_Age << endl;
}

void test()
{
    Person<string, int> p("sss", 10);
    //printPerson(p);
    //printPerson2(p);
    printPerson3(p);
}
```
