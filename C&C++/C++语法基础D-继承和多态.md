# 继承、多态

## （一）继承和派生

### 1.基本语法

***作用：*** 利用继承可以减少重复代码
***类名：*** 基类（父类）  派生类（子类）
***语法：*** `class 子类 ：继承方式 父类`

```C++
class BasePage//基类
{
    public:
        void header()
        {
            cout << "公共头部" << endl;
        }
}
class GamePage : public BasePage//派生类
{
    public:
        void content()
        {
            cout << "Game" << endl;
        }
}
class NewsPage : public BasePage
{
    public:
        void content()
        {
            cout << "news" << endl;
        }
}
```

### 2.继承方式

![继承方式](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/继承方式.png)

### 3.继承中的对象模型

* 父类中私有属性，子类也继承下去了，但被编译器隐藏，无法访问
* 可以通过 开发人员命令提示工具（Developer Command Prompt for VS 2019）进行查看对象模型
  * 跳转至对应目录下，输入`cl /d1 reportSingleClassLayout类名 文件名`

```C++
class Base
{
public:
    int m_A;
protected:
    int m_B;
private:
    int m_C;
};
class Son : public Base
{
public:
    int m_D;
};
int main()
{
    cout << sizeof(Son) << endl;//16
}
```

### 4.继承中的构造和析构

* 继承中，先调用父类的构造，后调用子类的构造，析构和构造顺序相反
* 可以利用初始化列表语法显示指定出调用父类的哪个构造函数
* 子类不会继承父类中的构造和析构，只有父类自己才知道如何构造和析构自己的属性

```C++
class Base
{
public:
    Base(int i) 
    {
        cout << "Base" << i << endl;
    }
    ~Base()
    {
        cout << "~Base" << endl;
    }
};
class Son : public Base
{
public:
    Son(int i) : Base(i)//初始化列表
    {
        cout << "Son" << i << endl;
    }
    ~Son()
    {
        cout << "~Son" << endl;
    }
};
```

### 5.继承中同名的成员或静态成员处理

* 如果子类和父类拥有同名成员，优先调用子类的成员，可以通过作用域调用父类的成员
* 同名的成员函数，子类会隐藏掉父类中的所有版本，如果想调用父类中的其它版本，加上作用域即可
* 静态成员和普通成员的处理方式类似，只是静态成员可以通过类名进行访问

```C++
class Base
{
public:
    Base()
    {
        this->m_A = 100;
    }
    void func()
    {
        cout << "Base::func" << endl;
    }
    void func(int i)
    {
        cout << "Base::func" << i << endl;
    }
    int m_A;
};
class Son : public Base
{
public:
    Son()
    {
        this->m_A = 200;
    }
    void func()
    {
        cout << "Son::func" << endl;
    }
    int m_A;
};
void test()
{
    Son s;
    cout << s.m_A << endl;//调用Son类中的m_A
    cout << "Base: " << s.Base::m_A << endl;//调用Base类中的m_A

    //同名的成员函数，子类会隐藏掉父类中的所有版本
    s.func(); //调用Son类中的func
    s.Base::func();//调用Base类中的func
}

```

### 6.多继承语法

* class子类：继承方式 父类1，继承方式 父类2
* 当两个父类中，有同名的成员被子类继承后，调用时需要加作用域进行区分

```C++
class Base1
{
public:
    Base1()
    {
        m_A = 100;
    }
    int m_A;
};
class Base2
{
public:
    Base2()
    {
        m_A = 200;
    }
    int m_A;
};
class Son : public Base1, public Base2
{
public:
    Son()
    {
        m_C = 300;
    }
    int m_C;
};
void test()
{
    Son s;
    //两个父类中，有同名的成员被子类继承后，调用时需要加作用域进行区分
    cout << s.Base1::m_A << endl;
    cout << s.Base2::m_A << endl;
}
```

### 7.菱形继承和虚继承

![菱形继承](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/菱形继承.png)

***问题：***

1. 羊继承了动物的数据和函数，驼也继承了动物的数据和函数，当草泥马调用函数或数据时，就会产生二义性
2. 草泥马继承自动物的函数和数据两份，我们只需要一份，另一份会被浪费

***处理：***

* 使用`virtual`关键字-虚继承
* 在Sheep和Tuo类中继承的内容为`vbptr`（虚基类指针）
  * `v`---`virtual`
  * `b`---`base`
  * `ptr`---`pointer`
  * `vbptr`指向`vbtable`（虚基类表）
  * `vbtable`中有偏移量，通过偏移量可以找到唯一的数据

![虚继承](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/菱形继承和虚继承.png)

```C++
class Animal//虚基类
{
public:
    int m_Age;
};
class Sheep : virtual public Animal{};//虚继承
class Tuo : virtual public Animal{};
class SheepTuo : public Sheep, public Tuo{};
void test()
{
    SheepTuo st;
    st.Sheep::m_Age = 100;
    st.Tuo::m_Age = 200;
    cout << st.m_Age << endl;
}
```

## （二）多态

* 多态性提供了接口与具体实现之间的隔离，从而将“what”和“how”分离开的
* 多态的好处：对扩展性提高，组织性强，可读性强
  * 如果父类中有了虚函数，子类并没有重写父类的虚函数，那么这样的代码是毫无意义的
  * 如果子类不重写父类虚函数，会没有使用多态带来的好处，并是内部结构更加复杂
* 代码编写原则：开闭原则（对扩展进行开放，对修改进行关闭）

### 1.静态联编和动态联编

* 编译时多态（静态多态）：运算符重载和函数重载
* 运行时多态（动态多态）：派生类和虚函数
* 静态多态和动态多态区别：函数地址早绑定（静态联编）还是晚绑定（动态联编）
  * 函数调用，在编译阶段就可以确定函数的调用地址，并产生代码，地址是早绑定
  * 函数调用，不能在编译期间确定，而需要在运行时确定，地址就是晚绑定

* 对于有父子关系的两个类，C++可以不需要通过类型强转

***多态满足的条件***

1. 父类中有虚函数
2. 子类**重写**父类的虚函数
3. （使用）父类的指针或引用指向子对象

***重写***---`virtual`虚函数

1. 子类重新实现父类中的虚函数，必须返回值、函数名、参数一致才称为重写
2. 子类在做重写时，可以不加关键字`virtual`

```C++
class Animal
{
public:
    virtual void speck()//虚函数
    {
        cout << "动物在说话" << endl;
    }
};
class Cat : public Animal
{
public:
    void speck()//重写
    {
        cout << "小猫在说话" << endl;
    }
};
//对于有父子关系的两个类，C++可以不需要通过类型强转
void DoSpeck(Animal& animal)
{
    animal.speck();
}
int main()
{
    Cat cat;
    DoSpeck(cat);//小猫在说话
}
```

### 2.多态原理

1. 当父类中存在虚函数后，内部发生结构变化，多了虚函数表指针`vfptr`，指向虚函数表`vftable`
2. 虚函数表内部记录着虚函数地址
3. 当子类发生重写后，会修改子类中的虚函数表中的函数地址，但不会影响父类中的虚函数表

![多态原理](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/多态原理-虚函数.png)

4. 多态的深度分析

```C++
class Animal
{
public:
    virtual void speak()
    {
        cout << "Animal Speak" << endl;
    }
    virtual void eat(int i)
    {
        cout << "Animal Eat" << i << endl;
    }
};
class Cat : public Animal
{
public:
    void speak()
    {
        cout << "Cat Speak" << endl;
    }
    virtual void eat(int i)
    {
        cout << "Cat Eat" << i << endl;
    }
};

void test()
{
    Animal * animal = new Cat;
    //cat->speak();
    //((void(*)())  (*(int*)*(int*)animal))();Cat Speak--32位调试才能跑
    //((void(*)()) (*((int*)*(int*)animal + 1)))();//Cat Eat--无参
    typedef void(__stdcall* FUNC)(int);
    (FUNC(*((int*)*(int*)animal + 1)))(10);//Cat Eat10--有参
}
```

### 3.抽象类和纯虚函数

* 纯虚函数语法：`virtual void func() = 0;`
* 如果一个类中有**纯虚函数**，那么这个类无法实例化对象，这样的类称为**抽象类**
* 如果子类继承了抽象类，那么子类必须重写父类中的纯虚函数，否则子类也属于抽象类

```C++
//##利用多态实现计算器
class AbstractCalculator//抽象类
{
public:
    virtual int getResult() = 0;//纯虚函数
    // virtual int getResult()//虚函数
    // {
    //     return 0;
    // }
    int m_A;
    int m_B;
};
//加法计算器
class AddCalculator : public AbstractCalculator
{
public:
    int getResult()
    {
        return m_A + m_B;
    }
};
void test()
{
    AbstractCalculator* calculator = new AddCalculator;
    calculator->m_A = 10;
    calculator->m_B = 20;
    cout << calculator->getResult() << endl;
}
```

### 4.虚析构和纯虚析构

* 虚析构解决的问题：当子类有堆区的内容时，释放时不干净，内存泄露
* 纯虚析构：有声明，也必须有实现，在类外实现
* 如果一个类中有纯虚析构，那么这个类属于抽象类

```C++
class Animal
{
public:
    Animal()
    {
        cout << "Animal()" << endl;
    }
    //virtual ~Animal()
    //{//虚析构
    //  cout << "~Animal()" << endl;
    //}
    virtual ~Animal() = 0;//纯虚析构
    virtual void speak()
    {
        cout << "Animal speak()" << endl;
    }
};
Animal::~Animal()
{
    cout << "~Animal()" << endl;
}
class Cat : public Animal
{
public:
    Cat(const char* name)
    {
        this->m_Name = new char[strlen(name) + 1];
        strcpy(this->m_Name, name);

        cout << "Cat()" << endl;
    }
    ~Cat()
    {
        if (this->m_Name != NULL)
        {
            cout << "~Cat()" << endl;
            delete[] this->m_Name;
            this->m_Name = NULL;
        }
    }
    void speak()
    {
        cout << "Cat Speak()" << endl;
    }
    char* m_Name;
};
void test()
{
    Animal* animal = new Cat("DD");
    animal->speak();
    delete[] animal;
}
```

### 5.向上向下类型转换

1. 父类转子类 向下类型转换 不安全
2. 子类转父类 向上类型转换 安全
3. 如果发生多态，那么总是安全的

![向上向下类型转换](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/向上向下类型转换.png)

### 6.多态案例--电脑组装

![多态案例--电脑组装](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/电脑组装案例需求.png)

```C++
//抽象层
//抽象的CPU
class Cpu
{
public:
    virtual void calculate() = 0;
};
//抽象的显卡
class VideoCard
{
public:
    virtual void memory() = 0;
};
//电脑类
class computer
{
public:
    computer(Cpu* cpu, VideoCard* vc)
    {
        this->cpu = cpu;
        this->vc = vc;
    }
    void dowork()
    {
        this->cpu->calculate();
        this->vc->memory();
    }
    ~computer()
    {
        if (this->cpu != NULL)
        {
            delete[] cpu;
            this->cpu = NULL;
        }
        if (this->vc != NULL)
        {
            delete[] vc;
            this->vc = NULL;
        }
    }
    Cpu* cpu;
    VideoCard* vc;
};
//实现层
//inter的CPU
class interCpu : public Cpu
{
    void calculate()
    {
        cout << "interCpu Calculate()" << endl;
    }
};
//inter的显卡
class interVideoCard : public VideoCard
{
    void memory()
    {
        cout << "interVideoCard Memory()" << endl;
    }
};
//联想的CPU
class leCpu : public Cpu
{
    void calculate()
    {
        cout << "leCpu Calculate()" << endl;
    }
};
//联想的显卡
class leVideoCard : public VideoCard
{
    void memory()
    {
        cout << "leVideoCard Memory()" << endl;
    }
* };~~~~
void test()
{
    //组装的第一台电脑
    Cpu* cpu = new interCpu;
    VideoCard* vc = new interVideoCard;
    computer* interCo = new computer(cpu, vc);
    interCo->dowork();
    //组装的第二台电脑
    cout << "------------" << endl;
    Cpu* cpu2 = new leCpu;
    VideoCard* vc2 = new leVideoCard;
    computer* interCo2 = new computer(cpu2, vc2);
    interCo2->dowork();
}
```
