# 类型转换、异常、文件

***C++风格的强制转换的好处：***它能更清晰的表名它们要干什么，程序员只要扫一眼这样的代码，就立即知道一个强制转换的目的

## 01/C++风格类型转换

### （1）静态类型转换`static_cast`

* 用于类层次结构中基类（父类）和派生类（子类）之间指针或引用的转换
  * 进行上行转换（把派生类的指针或引用转换成基类表示）是安全的；
  * 进行下行转换（把基类指针或引用转换成派生类表示）时，由于没有动态类型检查，所以是不安全的
* 没有父子关系的类型是无法转换成功的
* 用户基本数据类型之间的转换，如把int转换成char，把char转换成int。这种转换的安全性也要开发人员来保证

```C++
void test01()
{
    //1、内置类型转换
    char a = '';
    double d = static_cast<double>(a);
}
class Base{};
class Son : public Base{};
class Other{}
void test02()
{
    //2、自定义类型转换
    Base *base = NULL;
    Son *son = NULL;
    Other *other = NULL;
    //向下转换--不安全
    son = static_cast<Son*>(base);
    //向上转换--安全
    base = static_cast<Base*>(son);
    //没有父子关系的类型无法转换成功
    other = static_cast<Other*>(base);
}
```

### （2）动态类型转换`dynamic_cast`

* 不支持基本数据类型之间的转换
* 在上行类型转换，`dynamic_cast`和`static_cast`一致
* 在下行类型转换，`dynamic_cast`具有类型检查功能，比`static_cast`更安全
* 如果发生多态，那么父子之间的转换总是安全的

```C++
class Base
{
    virtual void func(){}
};
class Son : public Base
{
    virtual void func(){}
};
void test()
{
    //如果发生多态，那么父子之间的转换总是安全的
    Base *base = new Son;
    Son *son = dynamic_cast<Son*> base;
}
```

### （3）常量类型转换`const_cast`

用来修改类型的`const`属性

* 常量指针被转化成非常量指针，并指向原来的对象
* 常量引用被转化成非常量引用，并指向原来的对象

***注意：***不能直接对非指针和非引用的变量使用`const_cast`去移除它的const

```C++
void test()
{
    //指针之间的转换
    const int *p = NULL;
    //将const int*转为int*
    int *p2 = const_cast<int *>(p);
    const int *p3 = const_cast<const int *>(p2);
    
    //引用之间的转换
    const int a = 10;
    const int &aRef = a;
    int &aRef2 = const_cast<int &>(aRef);
}
```

## 02/异常

### （1）异常基本语法

* C语言处理异常缺陷：返回值没有统一，返回值可以是异常的结果，也可以是正确的结果
* 异常必须要有人处理，如果没有任何处理，程序会自动调用一个terminate函数，让程序中断掉
* ***栈解旋：***异常被抛出后，从try代码块开始，到throw抛出异常前，这期间在栈上构造的所有对象，都会被自动析构，析构的顺序与构造的顺序相反，这一过程称为栈解旋
  
### （2）异常的接口声明

* 为了加强程序的可读性，可以在函数声明中列出可能抛出异常的所有类型。
  * 例如`void func() throw(A,B,C)`，这个函数func能够且只能抛出类型A、B、C及其子类型的异常
* 如果在函数声明中没有包含异常接口声明，可以抛出任何类型的异常
* 一个不抛任何类型异常的函数可声明为：`void func() throw()`
  * 如果一个函数抛出了它的异常接口声明所不允许抛出的异常，`unexcepted`函数会被调用，该函数默认行为调用`terminate`函数中断程序

### （3）异常变量的生命周期

1. `MyException e`会调用拷贝构造
2. `MyException &e`引用方式接收，节省开销（建议）
3. `MyException *e`指针方式接收，抛出`&MyException()`匿名对象，对象被释放掉了，不可以操作`e`了
4. `MyException *e`指针方式接收，抛出`new MyException()`；堆区创建的对象，记得手动释放`delete e`

```C++
class MyException
{
public:
    MyException(){}
    MyException(const MyException &e){}
    ~MyException(){}
}

void doWork()
{
    throw MyException();
}
```

### （4）异常在多态中的使用

```C++
class BaseException
{
    virtual void printException() = 0;
}
class NullPointException : public BaseException
{
    virtual void printException()
    {
        cout << "空指针异常" << endl;
    }
}
class OutOfRangeException : public BaseException
{
    virtual void printException()
    {
        cout << "越界异常" << endl;
    }
}
void doWork()
{
    throw NullPointException();
}
void test()
{
    try
    {
        doWork();
    }
    catch(BaseException &e)
    {
        e.printException();
    }
}
```

### （6）系统标准异常的使用`include <stdexcept>`

![系统标准库异常类](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/系统标准库异常类.png)

```C++
//系统标准异常的使用
#include <stdexcept>
class Person
{
public:
    Person(int age)
    {
        if(age < 0 || age > 150)
        {
            throw out_of_range("年龄越界异常！");//
        }
        this->m_Age = age;
    }
    int m_Age;
}
void test()
{
    try
    {
        Person p(151);
    }
    catch(exception &e)
    {
        cout << e.what() << endl;
    }
}
```

## 03/标准输入/输出流

![标准输入/输出流](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/标准输入-输出流.png)

### （1）标准输入流常用函数

1. `cin.get`缓冲区中读取一个字符
2. `cin.get(两个参数)`不读换行符
3. `cin.getline()`读取换行并扔掉
4. `cin.ignore(N)`忽略N个字符
5. `cin.peek`偷窥1个字符然后放回去
6. `cin.putback`把字符放回缓冲区
7. `cin.fail()`缓冲区中的标志位：0代表正常；1代表异常
8. `cin.clear()` `cin.sync()`重置标志位，并刷新缓冲区

### （2）标准输出流常用函数

1. `cout.put()` `cout.write()`利用成员函数输出内容
2. 通过流成员函数-标准化
   1. `int number = 99;`
   2. `cout.width(20);`预留20空间
   3. `cout.fill('*');`填充
   4. `cout.setf(ios::left);`左对齐
   5. `cout.unsetf(ios::dec);`卸载十六进制
   6. `cout.setf(ios::showbase);`设置显示进制-基数
3. 使用控制符-标准化`iomanip`
   1. `cout << setw(20)`预留20空间
   2. `cout << setfill(`~`)`填充
   3. `cout << setiosflags(ios::showbase)`显示进制基数
   4. `cout << setiosflags(ios::left)`设置左对齐
   5. `cout << hex`安装十六进制

### （3）文件的读写

```C++
void test()
{
    //打开文件：参数--文件路径--打开方式
    //ofstream ofs("./test.txt", ios::out | ios::trunc);
    ofstream ofs;
    ofs.open("./test.txt", ios::out | ios::trunc);
    //判断文件是否打开成功
    //if (!ofs)
    if(!ofs.is_open())
    {
        cout << "文件打开失败" << endl;
        return;
    }
    //写文件
    ofs << "aaaa" << endl;
    ofs << "ssss" << endl;
    //关闭文件流
    ofs.close();
}
```

```C++
void test()
{
    //打开文件：参数--文件路径--打开方式
    //ifstream ifs("./test.txt", ios::in);
    ifstream ifs;
    ifs.open("./test.txt", ios::in);
    //判断文件是否打开成功
    //if(!ifs.is_open())
    if (!ifs)
    {
        cout << "文件打开失败" << endl;
        return;
    }
    //读文件
    //第一种方式：按行读取，直到文件末尾
    char buf[1024] = {0};
    //将每行输入读入到缓冲区中
    while (ifs >> buf)
    {
        cout << buf << endl;
    }
    //第二种方式
    char buf[1024] = { 0 };
    while (!ifs.eof())
    {
        ifs.getline(buf,sizeof(buf));
        cout << buf << endl;
    }
    //第三种方式：单个字符读取
    char c;
    while ((c = ifs.get()) != EOF)
    {
        cout << c;
    }

    //关闭流对象
    ifs.close();
}
```
