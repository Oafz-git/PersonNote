# 数组类封装、运算符重载、字符串类封装

**重载`[]`,`+`,`<<`,`前置++`,`后置++`,`->`,`*`,`=`,`==`,`()`**

## （一）数组类封装及重载`[]`运算符

重载`[]`运算符：可以通过`[]`设置和获取数据

```C++
//MyArray.h
class MyArray//指处理int类型
{
public:
    //默认构造
    MyArray();
    //有参构造
    MyArray(int capacity);
    //拷贝构造
    MyArray(const MyArray &arr);
    //尾插
    void pushBack(int val);
    //根据位置设置数据
    void setData(int index, int val);
    //根据位置获取数据
    int getData(int index);
    //获取数组大小
    int getSize();
    //获取数组容量
    int getCapacity();
    // 重载[]运算符，这里需要返回引用，因为函数调用不能作为左值（arr[] = 1000;不能使用）
    int& operator[] (int index);
    //析构函数
    ~MyArray();
private:
    //指向堆区的数据指针
    int* pAddress;
    //数组容量
    int m_Capacity;
    //数组大小
    int m_Size;
};
```

```C++
//MyArray.cpp
#include "MyArray.h"
MyArray::MyArray()
{
    cout << "默认构造函数调用" << endl;
    this->m_Capacity = 100;
    this->m_Size = 0;
    this->pAddress = new int[this->m_Capacity];
}
MyArray::MyArray(int capacity)
{
    cout << "有参构造函数调用" << endl;
    this->m_Capacity = capacity;
    this->m_Size = 0;
    this->pAddress = new int[this->m_Capacity];
}
MyArray::MyArray(const MyArray& arr)
{
    cout << "拷贝构造函数调用" << endl;
    this->m_Size = arr.m_Size;//注：这里可以访问arr.m_Size(private)，同类可以访问私有内容
    this->m_Capacity = arr.m_Capacity;

    //深拷贝
    this->pAddress = new int[arr.m_Capacity];
    for (int i = 0; i < arr.m_Size; i++)
    {
        this->pAddress[i] = arr.pAddress[i]; 
    }
}
void MyArray::pushBack(int val)
{
    this->pAddress[this->m_Size] = val;
    this->m_Size++; 
}
void MyArray::setData(int index, int val)
{
    this->pAddress[index] = val;
}
int MyArray::getData(int index)
{
    return this->pAddress[index];
}
int MyArray::getSize()
{
    return this->m_Size;
}
int MyArray::getCapacity()
{
    return this->m_Capacity;
}
int& MyArray::operator[] (int index)
{
    return this->pAddress[index];
}
MyArray::~MyArray()
{
    cout << "析构函数调用" << endl;
    if (this->pAddress != NULL)
    {
        delete[] this->pAddress;
        this->pAddress = NULL;
    }
}
```

## （二）运算符重载

***问题：***
对于内置类型，编译器知道运算符应该如何计算（不可能改变），但对于自定义数据类型，编译器并不知道；

***说明：***
运算符重载（operator overloading）只是一种**语法上的方便**，也就是它只是另一种函数调用的方式。

* 利用成员函数进行加号运算符重载
* 利用全局函数进行加号运算符重载
* 运算符重载可以进行函数重载

***语法：***

* 重载运算符被定义为全局函数：对于一元是一个参数，对于二元是两个参数
* 重载运算符被定义为成员函数：对于一元没有参数，对于二元是一个参数

### 1.加号运算符重载

**目的：** 可以用`+`进行对象间相加

```C++
class Person
{
public:
    Person() {}
    Person(int a, int b):m_A(a),m_B(b) {}
    //利用成员函数进行 加号运算符重载
    Person operator+(Person &p)
    {
        Person temp;
        temp.m_A = this->m_A + p.m_A;
        temp.m_B = this->m_B + p.m_B;
        return temp;
    }
    int m_A;
    int m_B;
};

//利用全局函数进行 加号运算符重载
Person operator+(Person& p1, Person& p2)
{
    Person temp;
    temp.m_A = p1.m_A + p2.m_A;
    temp.m_B = p1.m_B + p2.m_B;
    return temp;
}

//加号运算符重载 进行函数重载
Person operator+(Person& p, int a)
{
    Person temp;
    temp.m_A = p.m_A + a;
    temp.m_B = p.m_B + a;
    return temp;
}
```

### 2.左移运算符重载

**目的：** 可以使用`cout <<`和`<< endl`输出对象

```C++
class Person
{
    //将全局函数-左移运算符重载变为Person的友元函数，可以使成员变量私有化
    friend ostream& operator<< (ostream& cout, Person& p);
public:
    Person() {};
    Person(int a, int b)
    {
        this->m_A = a;
        this->m_B = b;
    }
    //void operator<<(ostream &cout){}左移运算符重载只能使用全局函数才能出现cout<<
private:
    int m_A;
    int m_B;
};
//返回值需要是ostream，才能使用endl
ostream& operator<< (ostream& cout, Person& p)
{
    cout << "p.m_A:" <<p.m_A << "p.m_B:" << p.m_B;
    return cout;
}
```

### 3.`前置++`和`后置++`运算符重载

**目的：** 自己写的MyInteger对象可以使用前置++和后置++

前置++和后置++优先使用前置++

```C++
class MyInteger
{
friend ostream& operator<<(ostream& cout, const MyInteger& myInteger);
public:
    //默认构造函数
    MyInteger() { m_Int = 0; }
    //前置++：这里只能返回引用，返回值多次使用++导致只使用了一次++
    MyInteger& operator++()
    {
        //先 + 1
        m_Int = m_Int + 1;
        //后返回
        return *this;
    }
    //后置++：这里只能返回值，因为返回的是临时变量，属于局部变量
    MyInteger operator++(int)
    {
        //先 保留当前状态
        MyInteger temp = *this;
        //后 +1 
        m_Int = m_Int + 1;
        //再返回
        return temp;
    }
private:
    int m_Int;
};

//这里的const：（E0349没有与这些操作数匹配的"<<"运算符）
//如果返回的是一个临时变量，临时变量属于纯右值，它不能绑定到左值引用，你需要使用常量左值引用或右值引用来绑定
ostream& operator<<(ostream& cout,const MyInteger& myInteger) 
{
    cout << "m_Int:" <<myInteger.m_Int;
    return cout;
}
void test01()
{
    MyInteger myinteger;
    cout << ++(++myinteger) << endl;
    cout << myinteger << endl;
}
void test02()
{
    MyInteger myinteger;
    cout << myinteger++ << endl;
    cout << myinteger << endl;
}
```

### 4.指针运算符重载-智能指针

**目的：** 用来托管new出来的对象的释放
如果想智能指针对象像指针一样调用变量和函数，需要重载`->`和`*`

```C++
class Person
{
public:
    Person()
    {
        m_Age = 0;
    }
    Person(int age)
    {
        this->m_Age = age;
    }
    ~Person(){}
    void showAge()
    {
        cout << "m_Age: " << this->m_Age << endl;
    }
private:
    int m_Age;
};
class SmartPointer//智能指针
{
public:
    SmartPointer(Person* person)
    {
        this->person = person;
    }
    ~SmartPointer()
    {
        if (this->person != NULL)
        {
            delete this->person;
            this->person = NULL;
        }
    }
    //重载->运算符，返回指针
    Person* operator->()
    {
        return this->person;
    }
    //重载*运算符，返回本体-引用
    Person& operator*()
    {
        return (*this->person);
    }
private:
    Person* person;
};
void test()
{
    /*Person* person = new Person();
    person->showAge();
    (*person).showAge();
    delete person;*/

    SmartPointer sp = SmartPointer(new Person(18));
    //如果项sp对象像指针一样调用变量和函数，需要重载->和*
    sp->showAge();//sp->->showAge();编译器简化为sp->showAge();
    (*sp).showAge();
}
```

### 5.赋值运算符`=`重载

**目的：** 为了处理类中默认的`=`的运算符的浅拷贝问题

* 系统会默认给一个类添加4个函数：默认构造、析构、拷贝构造（浅拷贝）、operator=(浅拷贝)
* 由于系统提供的`operator=`会进行简单的值拷贝，如果成员属性中有堆区的数据，会导致重复释放--需要重载`operator=`

```C++
class Person
{
public:
    Person(const char* name, int age)
    {
        this->m_Age = age;
        this->m_Name = new char[strlen(name) + 1];
        strcpy(this->m_Name,name);
    }
    Person(const Person &p)
    {
        this->m_Name = new char[strlen(p.m_Name) + 1];
        strcpy(this->m_Name, p.m_Name);
        this->m_Age = p.m_Age;
    }
    //系统会默认给一个类创建至少3个函数：默认构造、析构、拷贝构造（浅拷贝）、operator=(浅拷贝)
    Person& operator=(const Person &person)
    {
        //先判断原来的堆区是否有数据，如果有先释放
        if (this->m_Name != NULL)
        {
            delete[] this->m_Name;
            this->m_Name = NULL;
        }
        //再重新创建name
        this->m_Name = new char[strlen(person.m_Name) + 1];
        strcpy(this->m_Name, person.m_Name);
        this->m_Age = person.m_Age;
        return *this;
    }
    ~Person()
    {
        if(this->m_Name != NULL)
        {
            delete [] this->m_Name;//这里是数组，[]不能丢
            this->m_Name = NULL;
        }
    }
    int m_Age;
    char *m_Name;//注：这里的值是堆区的数据，拷贝构造函数和operator=都存在浅拷贝问题
};
void test()
{
    Person p1("A", 10);
    Person p2("B", 20);
    p1 = p2;//这里需要重载=运算符
    cout << "p1.m_Name" << p1.m_Name << "age:" << p1.m_Age << endl;
    cout << "p2.m_Name" << p2.m_Name << "age:" << p2.m_Age << endl;
    Person p3(" ", 0);
    p3 = p1 = p2;//这里的重载的=运算符 需要返回对象
    cout << "p3.m_Name" << p3.m_Name << "age:" << p3.m_Age << endl;
    Person p4(p3);
    cout << "p4.m_Name" << p4.m_Name << "age:" << p4.m_Age << endl;
}
```

### 6.关系运算符`==`重载

```C++
class Person
{
public:
    Person(string name, int age)
    {
        this->name = name;
        this->age = age;
    }
    bool operator== (Person &p)//重载==运算符
    {
        return this->name == p.name && this->age == p.age;
    }
private:
    string name;
    int age;
};
```

### 7.函数调用运算符`()`重载-仿函数

```C++
class Myfunc
{
public:
    void operator() (string s)
    {
        cout << s << endl;
    }
};
void test()
{
    Myfunc myfunc;//STL 仿函数
    myfunc("");
}
```

### 8.符号重载总结

* `=` `[]` `()` `->`运算符只能通过**成员函数**进行重载
* `<<` `>>`运算符只能通过**全局函数**结合**友元函数**进行重载
* 不要重载`&&` `||` 运算符，因为无法实现短路规则

## （三）字符串类封装

1. 设计类MyString
2. 成员属性
   * char* pString 维护指向堆区指针
   * int m_Size 字符串长度
3. 成员函数
   * 有参构造
   * 拷贝构造
   * 析构
4. `<<`重载
5. `>>`重载
6. `[]`重载 进行[]字符读写
7. `=`重载 防止浅拷贝问题出现
8. `+`重载 字符串拼接
9. `==`重载 对比


```C++
//MyString.h

#ifndef __MY_STRING_H__
#define __MY_STRING_H__

#include <iostream>
#include <string.h>

using namespace std;

class MyString
{
    //左移运算符
    friend ostream& operator<<(ostream& cout, MyString& myString);

    //右移运算符
    friend istream& operator>>(istream& cin, MyString& myString);

    public:
        //有参构造
        MyString(char* c);

        //拷贝构造
        MyString(const MyString& myString);

        //重载[]
        char& operator[](int index);

        //重载=
        MyString& operator=(MyString& MyString);
        MyString& operator=(char* ch);

        //重载+
        MyString operator+(MyString& str);
        MyString operator+(char* ch);

        //重载==
        bool operator==(MyString& str);
        bool operator==(char* ch);

        //析构函数
        ~MyString();
    private:
        int m_Size;
        char* pString;
};

#endif // !__MY_STRING_H__

```


```C++
#include "MyString.h"

MyString::MyString(char* c)
{
    this->pString = new char[strlen(c)+1];
    strcpy(this->pString, c);
    this->m_Size = strlen(c);
}

MyString::MyString(const MyString& myString)
{
    this->pString = new char[myString.m_Size +1];
    strcpy(this->pString, myString.pString);

    this->m_Size = myString.m_Size;
}

MyString::~MyString()
{
    if(this->pString != NULL)
    {
        delete this->pString;
        pString = NULL;
    }

}

ostream& operator<<(ostream& cout, MyString& str)
{
    cout << "MyString:" << str.pString;
    return cout;
}

istream& operator>>(istream& cin, MyString& str)
{
    if(str.pString != NULL)
    {
        delete[] str.pString;
        str.pString = NULL; 
    }
    char buf[1024];//缓冲区
    cin >> buf;

    //
    str.pString = new char[strlen(buf)+1];
    strcpy(str.pString,buf);
    str.m_Size= strlen(buf);

    return cin;
}



//重载[]
char& MyString::operator[](int index)
{
    return this->pString[index];
}

//重载=
MyString& MyString::operator=(MyString& str)
{
    this->m_Size = str.m_Size;
    this->pString = new char[strlen(str.pString)+1];
    strcpy(this->pString, str.pString);
    return *this;
}

MyString& MyString::operator=(char* ch)
{
    this->m_Size = strlen(ch);
    this->pString = new char[strlen(ch)+1];
    strcpy(this->pString, ch);
    return *this;
}

//重载+
MyString MyString::operator+(MyString& str)
{
    int newSize = this->m_Size + strlen(str.pString) + 1;

    char *temp = new char[newSize];

    memset(temp,0,newSize);
    strcat(temp, this->pString);//strcat将两个字符串
    strcat(temp, str.pString);

    MyString myString(temp);
    delete [] temp;
    return myString;
}


MyString MyString::operator+(char* ch)
{
    int newSize = this->m_Size+strlen(ch)+1;
    char *temp = new char[newSize];

    memset(temp, 0, newSize);
    strcat(temp, this->pString);//strcat将两个字符串
    strcat(temp,ch);

    MyString myString(temp);
    delete[] temp;
    return myString;

}

//重载==
bool MyString::operator==(MyString& str)
{
    if(strcmp(this->pString,str.pString) == 0)
        return true;
    return false;
}


bool MyString::operator==(char* ch)
{
    if(strcmp(this->pString, ch) == 0)
        return true;
    return false;
}
```
