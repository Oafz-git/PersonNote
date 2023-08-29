# 函数和类

## （一）函数

### 1.宏函数的缺陷

1. 保证运算完整性-->需要加小括号修饰

```C++
#define MYADD1(x,y) x+y
#define MYADD2(x,y) ((x)+(y))
void test()
{
    int a = 10;
    int b = 20;
    int ret = MYADD1(a,b) * 20;//410，展开后为 x+y*20
    int ret = MYADD2(a,b) * 20;//600
}
```

2. 即使加入括号修饰，有些情况依然出现和预期不符的结果

```C++
#define MYCOMPARE(a,b) (((a)<(b)) ? (a) : (b))
void test()
{
    int a = 10;
    int b = 20;
    int ret = MYCOMPARE(++a,b); //预期结果11，实际12；展开(((++a)<(b)) ? (++a) : (b))
} 
```

3. 宏函数不重视作用域

### 2.内联函数`inline`

1. 内联函数和函数的区别：内联函数会在适当的地方像预定义宏一样展开**以空间换时间**。
2. 函数体必须和声明结合在一起，否则按照普通函数对待。

```C++
inline int func(int a);
inline int func(int a){return++;}
```

3. 成员函数前都会隐藏的加入了`inline`关键字

### 3.函数的默认参数

```C++
int func(int a = 1, int b = 1)
{
    return a + b;
}
```

1. 如果参数列表中有一位置有了默认参数，那么从这个位置起从左到右都必须有默认参数
2. 函数的声明和实现只能有一个默认参数

### 4.函数的占位参数

```C++
int func(int a, int = 10)//占位参数
{
    return a;
}
```

### 5.函数重载

***重载条件***
1. 作用域相同
2. 函数名称相同
3. 函数参数的类型不同或个数不同或顺序不同
4. 函数的返回值不能作为函数重载的条件
5. 引用的重载：加入const和不加const也可以作为重载条件

***注意：***
```C++
//函数出现不加引用和加引用可以同时调用，注意避免二义性
void func(int a){}
void func(int &a){}
void func(const int &a){}
//函数重载遇到函数的默认参数，注意避免二义性
void func(int a, int b = 10){}
void func(int a){}
```

***重载原理***
编译器用不同的参数类型来修饰不同的函数名（不同的编译器修饰为不同的内部名）：
`void func()`可能修饰成`_func`
`void func(int x)`可能修饰成`_func_int`

### 6.externC浅析

用途：在C++下可以运行C语言文件

方式一

```C++
//test.h
void show();

//test.c
void show(){}

//externC.cpp
//#include "test.h"
extern "C" void show();//告诉编译器，下面有个show()函数，不要用C++的方式链接，要用C语言的方式链接
void test()
    {
        show();//_Z4show()
    }
```

方式二

```C++
//test.h
#ifdef __cplusplus
extern "C" {
#endif
void show();
#ifdef __cplusplus
}
#endif

//test.c
void show(){}

//externC.cpp
//#include "test.h"
//extern "C" void show();//告诉编译器，下面有个show()函数，不要用C++的方式链接，要用C语言的方式链接
void test()
    {
        show();//_Z4show()
    }
```

## （二）类和对象

### 1.C语言封装缺点

1. C语言下没有做类型转换的检测
2. 将属性和行为分离

### 2.C++语言封装

1. 将属性（成员变量）和行为（成员函数）作为一个整体，并将这些成员加以权限进行控制
2. C++下struct和class的区别：struct默认权限为public，class默认权限为private
3. 权限：

|public（公共权限）|protected（保护权限）|private（私有权限）|
| :----: | :----: | :----:|
|类内可以访问|类内可以访问|类内可以访问|
|类外可以访问|类外不可以访问|类外不可以访问|
|子类可以访问|子类可以访问|子类不可以访问|

4. 尽量将成员属性设置为私有

好处：

* 自己可以控制属性的读写权限
* 可对用户传入的数据进行操作

## （三） 对象的构造函数和析构函数

### 1.构造函数的写法

1. 没有返回值，也不写void，函数名和类名相同
2. 可以有参数，可以发生重载
3. 由编译器自动调用，且只会调用一次，不需手动调用

### 2.析构函数的写法

1. 没有返回值，不写void，函数名与类名相同，在函数名称前加`~`
2. 不可以有参数，不可以发生重载
3. 由编译器自动调用，且只会调用一次，不需手动调用

```C++
class MyClass
{
    public:
        MyClass(){}
        ~MyClass(){}
}
```

### 3.构造函数分类

1. 按照参数进行分类：有参构造函数、无参构造函数（默认构造函数）
2. 按照类型进行分类：普通构造函数、拷贝构造函数（`const`和`&`不能丢）

```C++
class Person
{
    public:
        //默认构造
        Person(){}
        //有参构造
        Person(int age){m_Age = age;}
        //拷贝构造
        Person(const Person &p){m_Age = p.m_Age;}//类名（const 类名& a）
    private:
        int m_Age;
}
```

### 4.构造函数调用

```C++
void test()
{
    //无参构造
    Person p1;
    //有参构造-括号法
    Person p2(10);//有参构造调用
    Person p3(p2);//拷贝构造调用
    //有参构造-显示法
    Person p4 = Person(10);//有参构造调用
    Person p5 = Person(p4);//拷贝构造调用
    //有参构造-隐式法
    Person p6 = 10;//等价于 Person p6 = Person（10）
    Person p7 = p6;
}
```

**注意**

1. 无参构造不可以用括号法：编译器认为`Person p()`是一个函数的声明
2. `Person(10)`为构造匿名函数对象，特点：当前行执行完后，系统就回收
3. 不能用拷贝构造函数`Person(p)`来构造匿名函数对象，编译器认为`Person(p)`是一个声明`Person p`

### 5.拷贝构造的调用时机

1. 使用一个已经创建好的对象来初始化另一个对象

```C++
void test()
{
    Person p1(18);
    Person p2(p1);
}
```

2. 以值传递的方式给函数的参数传值

```C++
void doWork(Person p){}
void test()
{
    Person p1;
    doWork(p1);
}
```

3. 以值的方式返回局部对象

```C++
Person doWork()
{
    Person p1;
    return p1;
}
void test()
{
    Person p = doWork();
}
```

### 6.构造函数的调用规则

1. 系统会默认给一个类添加至少3个函数：默认构造函数、析构函数、拷贝构造函数
2. 如果我们自己提供了有参构造函数，那么系统就不会提供默认构造函数，但是依然会提供拷贝构造函数
3. 如果我们自己提供了拷贝构造函数，那么系统就不会提供其他的普通构造函数了

### 7.深拷贝和浅拷贝

```C++
class Person
{
    public:
        Person(char *name, int age)
        {
            m_Name = (char *)malloc(strlen(name)+1);
            strcpy(m_Name, name);
            m_Age = age;
        }
        Person(const Person &p)
        {
            m_Age = p.m_Age;
            //m_Name = p.m_Name;系统提供的浅拷贝
            //利用深拷贝处理浅拷贝带来的问题
            m_Name = (char *)malloc(strlen(p.m_Name)+1);
            strcpy(m_Name,p.m_Name);
        }
        ~Person()
        {
            if(m_Name != NULL)
            {
                free(m_Name);
                m_Name = NULL;
            }
        }
        char *m_Name;//姓名
        int m_Age;//年龄
}
void test()
{
    Person p1("Tom",18);
    Person p2(p1);
}
```

![深拷贝和浅拷贝](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/深拷贝和浅拷贝.png)

### 8.初始化列表

用途：用来初始化类中的属性

```C++
class Person
{
    public:
        Person(int a,int b, int c):m_A(a),m_B(b),m_C(c){}
    private:
        int m_A,m_B,m_C;
}
```

### 9.类对象作为类成员

当其它类对象作为本类成员，先构造其他类对象，再构造自身，释放的顺序与构造相反

### 10.`explicit`关键字

用途：防止隐式类型转换方式来初始化对象

### 11.`new` `delete`

C++中解决**动态内存分配**的方案是把创建一个对象所需要的操作都结合在一个称为new运算符里。当用new创建一个对象时它就在**堆**里为对象分配内存并调用构造函数完成初始化

```C++
Person *person = new Person;//内部会malloc数据在堆区，判断内存是否分配，调用构造函数
//相当于
Person *person = (Person*)malloc(sizeof(Person));//malloc数据在堆区
if(person ** null)//判断内存开辟是否成功
{
    return 0;
}
person -> Init();//构造函数
```

1. `malloc`和`new`区别：
    |关键字：|malloc|new|
    |----|----|----|
    |类型：|运算符|库函数|
    |返回值：|void*|new出来的对象的指针|
    |判断是否开辟成功|需要|不需要|
    |是否调用构造函数|不会调用|会调用|
    |释放关键字|free|delete|

2. 不要用`void*`去接受new出来的对象，原因是不能够释放

   ```C++
   void test()
   {
        void *p = new Person();
        delete (Person *)p;
   }
   ```

3. 利用new创建数组
   * 利用new在**堆区**创建数组，类中必须要存在默认构造函数，否则无法创建
   * 释放时需要在`delete`后加`[]`

    ```C++
    Person *person = new Person[10];
    delete []person;//释放数组
    ```

    * 如果数组在**栈上**开辟的，那么可以指定利用哪个构造函数来初始化对象

    ```C++
    Person person[3] = {Person(10),Person(10),Person(10)};
    ```

### 12.静态成员变量`static`

* 与一般数据成员不同，无论建立了多少个对象，都只有一个静态数据的拷贝，静态成员变量，属于某个类，**所有对象共享**。
* 在**编译阶段**分配空间，对象还没创建，就已经分配空间了
* 静态成员变量必须在**类中声明，在类外定义**
* 静态数据成员不属于某个对象，在为对象分配空间中不包括静态成员所占空间
* 静态数据成员可以通过**类名**或**对象**来访问
* 静态成员也是有**访问权限**的，私有权限类外访问不到

### 13.静态成员函数`static`

* 可以通过**类名**或**对象**进行访问
* 静态成员函数不可以访问**非静态成员变量**，因为无法区分变量归属于哪个对象
* 静态成员函数可以访问**静态成员变量**，因为都是共享数据
* 非静态成员函数可以访问**静态成员变量**，也可以访问**非静态成员变量**
* 静态成员函数有**访问权限**，私有权限类外访问不到

### 14.单例模式

一个类中只有**唯一**的一个实例对象

```C++
class ChairMan
{
    private:
        //1、为了不创建多个对象，需要将默认构造函数私有化
        ChairMan(){}
        //5、为了使拷贝构造函数不创建多个对象，需要将拷贝拷贝构造函数私有化
        ChairMan(const ChairMan &c){}
        //public:
        //2、为了只创建一个对象，需要将对象共享，并只创建一个对象的指针
        static ChairMan* singleMan;

    public:
        //4、为了不将对象删除，所以需要将对象创建为只读状态，并提供读取函数
        static ChairMan* getInstance()
        {
            return singleMan;
        }

}
    //3、静态成员变量需要在类内声明，在类外定义；
    //并且，这里的ChairMan::作用域，会使编译器认为这行代码在类内，并可以访问私有权限的内容
    ChairMan *ChairMan::singleMan = new ChairMan();

void test()
{
    
    ChairMan::singleMan = NULL;//会将对象删除
    
    ChairMan *c1 = ChairMan::getInstance();
    ChairMan *c2 = new ChairMan(*c1);//拷贝构造函数会创建多个对象
    if(c1 == c2){}//这里c1和c2不相等
}
```

## （四）C++对象模型初探

* 成员变量和成员函数分开存储
* 空类的大小为1
* 一个类中只有**非静态成员变量**属于类的大小，其它都不计算在类内部

### 1.this指针的基本使用

```C++
class Person
{
    public:
        Person(int age)
        {
            //1、this指针指向的是被调用的成员函数所属的对象；this可以解决命名冲突
            this->age = age;
        }
        //
        void showAge()
        {
            cout << this->age << endl;
        }
        //2、链接编程：（1）返回值类型为当前对象的引用；（2）返回值为对象本体--*this
        Person &AddAge(Person &p)
        {
            this->age += p.age;
            return *this;
        }

        int age;
}
void test()
{
    Person p1(18);
    p1.showAge();
    Person p2(10);
    p1.AddAge(p2).AddAge(p2);//链接编程
    p1.showAge();
}
```

### 2.空指针访问成员函数

如果一个对象指针是一个空指针，可以访问没有使用this的一些成员函数；但不可以访问使用this指针的成员函数，程序会down掉（可以加判断防止down掉）

### 3.常函数和常对象

this指针的本质（Person *const this）：是一个指针常量，指针的指向是不可修改的，指针指向的值是可以改的；

1. 常函数
   * 在成员函数声明后加const`const Person *const this`：代表**常函数**，常函数中不可以修改成员属性；
   * 在成员变量前加`mutable`关键字，在常函数中就可以修改成员变量；
2. 常对象
   * 在创建对象前加const`const Person p`：代表**常对象**，常对象不可以修改成员属性；
   * 在成员变量前加`mutable`关键字，常对象可以修改成员变量；
   * 常对象只能调用常函数，不能调用普通成员函数，因为普通成员函数中可以修改成员属性；

```C++
class Person
{
    public:
        void showPerson() const//常函数
        {
            this->m_A = 100;//正确
            this->m_B = 100;//错误，常函数中不能修改属性 
        }

        void showPerson2()//普通成员函数
        {
            this->m_A = 100;//正确
            this->m_B = 100;//正确
        }

        mutable int m_A;//即使是常函数，也可以修改
        int m_B;
}
void test()
{
    const Person p;//常对象
    p.m_A = 100;//错误，常对象不可以修改属性
    p.m_B = 100;//正确

    p.showPerson();//正确
    p.shwoPerson2();//错误：因为普通成员函数中可以修改成员属性；
}
```

## （五）友元`friend`

可以在类的外部访问类的私有成员

### 1.全局函数作为友元函数

```C++
class Building
{
    //全局函数作为友元函数
    friend void goodGay(Building &building);
    public:
        Building()
        {
            this->m_SittingRoom = "客厅";
            this->m_BedRoom = "卧室";
        }
        string m_SittingRoom;
    private:
        string m_BedRoom;
}
void goodGay(Building &building)//全局函数
{
    cout << building.m_SittingRoom << end;//全局函数可以访问public
    cout << building.m_BedRoom << endl;//友元函数可以访问private
}
```

### 2.类作为友元类

1. 友元关系不能被继承
2. 友元关系是单向的：类A是类B的朋友，但类B不一定是类A的朋友
3. 友元关系不具有传递性：类B是类A的朋友，类C是类B的朋友，但类C不一定是类A的朋友。

```C++
class Building;
class goodGay
{
    public:
        goodGay();
        void visit();
    private:
        Building* building;
};
class Building
{
    friend class goodGay;//友元类
    public:
        Building();
        string m_settingRoom;
    private:
        string m_bedRoom;
};
goodGay::goodGay()
{
    this->building = new Building;
}
void goodGay::visit()
{
    cout << this->building->m_SittingRoom << endl;//类可以访问public权限
    cout << this->building->m_bedRoom << endl;//友元类可以访问private权限
}
Building::Building()
{
    this->m_SittingRoom = "客厅";
    this->m_BedRoom = "卧室";
}
```

### 3.成员函数作为友元函数

```C++
class Building;
class goodGay
{
    public:
        goodGay();
        void visit();
        void visit2();
    private:
        Building* building;
};
class Building
{
    friend class goodGay::visit();//成员函数作友元函数
    public:
        Building();
        string m_settingRoom;
    private:
        string m_bedRoom;
};
goodGay::goodGay()
{
    this->building = new Building;
}
void goodGay::visit()
{
    cout << this->building->m_SittingRoom << endl;//类可以访问public权限
    cout << this->building->m_bedRoom << endl;//成员函数作友元函数可以访问private权限
}
void goodGay::visit2()
{
    cout << this->building->m_SittingRoom << endl;//类可以访问public权限
    cout << this->building->m_bedRoom << endl;//成员函数不可以访问private权限
}
Building::Building()
{
    this->m_SittingRoom = "客厅";
    this->m_BedRoom = "卧室";
}
```
