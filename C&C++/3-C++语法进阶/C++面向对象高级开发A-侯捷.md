# 一、概述

1. 目标：培养正规、大气的编程习惯；学习面向对象设计

	* **Object Based（基于对象）：以良好的方式编写C++class**
		* class without pointer members【示例：Complex类】
		* class with pointer members【示例：String类】

	* **Object Oriented（面向对象）：学习Classes之间的关系**
		* 继承（inheritance）
		* 复合（composition）
		* 委托（delegation）

2. 推荐书籍
	
	《C++11 Primer》

	《The C++ Programming Language》

	《Effective C++》

	《Effective C++ Third Edition》

# 二、Object Based（基于对象）：以良好的方式编写C++class

## 1.Complex类：class without pointer members

```C
//complex.h
#include<iostream>

using namespace std;

/**
 * 总结：设计一个好的类需要注意：
 * 1. 构造函数尽量使用初始化列
 * 2. 成员函数尽量使用常函数
 * 3. 函数参数的传递尽量使用【引用】，尽量使用【const】修饰
 * 4. 函数返回值在可以的情况下，尽量使用【引用】
 * 5. 成员变量尽量放到private中，函数绝大部分放到public中
 * 
 */

#ifndef __COMPLEX__//1.Header（头文件）中的防卫声明
#define __COMPLEX__

//<<<<<<<<<<<<<<<<<<<<<<<<布局1：前置声明（forward declarations）<<<<<<<<<<<<<<<<<<<<<<<<



//<<<<<<<<<<<<<<<<<<<<<<<<布局2：类-声明（class declarations）<<<<<<<<<<<<<<<<<<<<<<<
class complex
{
/**
 * 2.函数（构造函数或成员函数）
 * 	a. 若在class body内定义完成，便自动成为【inline】候选人
 * 	b. 成员函数都有隐藏的this指针
 */
public://3.访问级别

	/**
	 * 4.构造函数：
	 * 	a. 考虑添加使用默认实参
	 * 	b. 尽量使用初始化列（initialization list），而不使用赋值（assignments）：赋值会比初始化效率差一些
	 * 	c. 构造函数可以重载
	 * 		注意：complex():re(0),im(0){} 这个构造函数和下边的构造函数重载冲突
	 * 	d. 特殊使用：把构造函数放到private中，单例模式
	 *  */
	complex(double r=0, double i=0) 
	: re(r), im(i)//初始化列表
	{}
	
	/**
	 * 5.const member function（常函数）： 在函数后边加const
	 * 	常对象只能调用常函数：
	 * 		注意：不改变数据内容的都“必须”加上const
	 * 		如果没有加，在用户将complex设置为常对象（说明对象不能改变数据）时，
	 * 		但是没有将用户调用的函数设置为常函数（说明这个函数可以改变），
	 * 		这是矛盾的，编译器会报错！！！
	 * 
	 * 6.参数传递：（pass by value vs. pass by reference - to const）
	 * 	a.使用优先级：引用>指针>值（尽量使用引用，引用比指针更大气），可以提高效率
	 *  b.尽量加const：不改变参数
	 * 
	 * 7. 返回值传递：（return by value vs. return by reference - to const）
 	 * 	尽量使用引用：传递者无需知道接收者是以reference形式接收
 	 * 		例如_doapl函数：这里返回的是object（传递者），但是返回值类型是引用（接收者）
	 * 		
	*/

	double real() const {return re;}//定义
	double imag() const {return im;}

	/**
	 * 9. 操作符重载+=（成员函数、二元操作符）
	 * 		会将this隐藏掉【complex& operator+=(this,const complex&);】
	 * 		c3+=（c2=+c1）：连串使用操作符时，需要考虑返回值是【引用】		
	 */
	complex& operator+=(/*this,*/const complex&);//声明
	

private:
	double re, im;

	/**
	 * 8. 友元函数：可以自由取得private成员
	 * 	注意：相同类的对象可以互相访问私有成员【相同类的各个对象互为友元】
	 */
	friend complex& _doapl(complex*, const complex&);
};


//<<<<<<<<<<<<<<<<<<<<<<<<布局3：类-定义（class definition）<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


inline complex& 
_doapl(complex* ths, const complex& r)
{
	ths->re += r.re;
	ths->im += r.im;
	return *ths;
}


//<<<<<<<<<<<<<<<<<<<<<<<<布局4：全局函数<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
inline double 
imag(const complex& x)
{
	return x.imag();
}

inline double 
real(const complex& x)
{
	return x.real();
}

/**
 * 9. 操作符重载+（二元操作符，非成员函数【无this】）
 * 	注意：这个重载的返回值绝不能是reference，因为返回的必定是local object；
 * 		尽量将这个重载声明为非成员函数：因为成员函数重载，可能会限制参数传递
 * 
 * 10. temp object（临时对象）--> typename();
 * 	示例：complex(real(x) + real(y), imag(x)+imag(y));
 */


inline complex
operator+ (const complex& x, const complex& y)
{
	return complex(real(x) + real(y), imag(x)+imag(y));
}

inline complex
operator+ (const complex& x, double& y)
{
	return complex(real(x) + y, imag(x)+y);
}

inline complex
operator+ (double& x, const complex& y)
{
	return complex(x + real(y), x+imag(y));
}

/**
 * 9.重载运算符+和-（正负、一元运算符、非成员函数）
 * 	注意：+重载的返回值不能使用reference，因为返回值绑定的是const类型
 * 		 -重载的返回值不能使用reference，因为返回值必定是local object
 * 
 */
inline complex
operator+(const complex& x)
{
	return x;
}

inline complex
operator-(const complex& x)
{
	return complex(-real(x), -imag(x));
}

/**
 * cout << c1 << c2;
 * 9.重载运算符<<（二元运算符只会把结果作用的运算符左侧变量）
 * 	注意：【只能是非成员函数】：因为这里的os对象不认识complex，无法使用this指针识别os对象；
 * 		参数：os对象前不能使用const修饰：因为os对象会被修改；
 * 		返回值：不能返回void：因为可能会连串使用操作符<<
 * 
 */

inline ostream&
operator<< (ostream& os, const complex& x)
{
	return os << '(' << real(x) << ',' << imag(x) << ')';
}

#endif
```

## 2.String类：class with pointer members

```C
//String.h

#ifndef __MY_STRING_H__
#define __MY_STRING_H__

#include <string.h>
#include <iostream>

using namespace std;

class String
{
public:
    String(const char* cstr = 0);
    String(const String& str);//copy ctor-----》String s2(s1)    String s2 = s1
    String& operator=(const String& str);//copy op= --------》 s2 = s1 
    ~String();
    char* get_c_str() const{return m_data;}

private:
    char* m_data;
};

inline 
String::String(const char* cstr)
{
    if(cstr)
    {
        cout << "String::String(const char* cstr = 0)1" << endl;
        m_data = new char[strlen(cstr) + 1];
        strcpy(m_data,cstr);
    }
    else
    {//注意1：未指定初值：默认构造函数
        cout << "String::String(const char* cstr = 0)2" << endl;
        m_data = new char[1];
        *m_data = '\0';
    }
}

inline
String::String(const String& str)
{
    cout << "拷贝构造函数" << endl;
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(this->m_data,str.m_data);
}

inline
String& String::operator=(const String& str)
{
    cout << "拷贝赋值函数" << endl;
    if(this == &str)//注意2：自我检测赋值（自己赋值自己）：如果没有这一步，下边的delete会把自身先杀掉
        return *this;
    
    delete[] m_data;//注意3：需要先把之前的指向的内存释放掉
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(this->m_data,str.m_data);
    return *this;
}

inline ostream&
operator<<(ostream& os, const String& str)
{
    return os << str.get_c_str();
}

inline
String::~String()
{
    delete[] m_data;
}

#endif // !__MY_STRING_H__
```

## 3.补充：static--静态成员变量&静态成员函数

```C
class Account
{
public:
// 1.static的作用：将成员变量和成员函数在类中独立出去；
	static double m_rate;
	static void set_rate(const double& x){m_rate = x;}
};
// 2.静态Data必须在类外定义（这里是在分配内存，上边只是声明），可以不用赋初值；
double Account::m_rate = 8.0;

int main()
{
// 3.两种调用方式：通过class那么调用、通过Object调用
	Account::set_rate(5.0);
	
// 4.注意：通过Object调用，不会将对象地址当做参数this
	Account a;
	a.set_rate(7.0);
}
```
# 三、Object Oriented（面向对象）：学习Classes之间的关系

## 1.复合（composition）表示`has-a`

### a.什么是复合关系？

![复合关系](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%A4%8D%E5%90%88%E5%85%B3%E7%B3%BB.png)

```C
//Adapter
template <class T>
class queue
{
	...
protected:
	deque<T> c; //底层容器
public:
	//以下都是利用c的操作函数完成的
	bool empty() const {return c.empty();}
	size_type size() const {return c.size();}
	void push(const value_type & x){c.push_back(x);}
	...
};
```
### b.composition【复合】关系下的构造和析构（内存角度分析）

![复合关系的构造和析构](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%A4%8D%E5%90%88%E5%85%B3%E7%B3%BB%E7%9A%84%E6%9E%84%E9%80%A0%E5%92%8C%E6%9E%90%E6%9E%84.png)

**构造由内向外：** container的构造函数首先调用component的default构造函数，后才执行自己

`Container::Container(...) : Component() {...};`

【注意】如果component需要参数，用户需要自己给构造函数

**析构由外到内：** container的析构函数首先执行自己，然后才调用component的析构函数

`Container::~Container(...) {... ~Component()};`

## 2.委托（Deletagion）--Composition by reference(pointer)

### 什么是委托关系？

![委托关系](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%A7%94%E6%89%98%E5%85%B3%E7%B3%BB.png)

```C++
// String.hpp---Handle---定义
class StringRep;
class String
{
public:
	String();
	String(const char* s);
	String(const String& s);
	String &operator= (const String& s);
	~String();
	...
private:
	StringRep* rep;//pImpl-->通过指针实现函数定义
};


// String.cpp---Body---实现"background: aliceblue"
#include "String.cpp"
namespace
{
	class StringRep
	{
	friend class String;
		StringRep(const char* s);
		~StringRep();
		int count;
		char* rep;
	};
}
String::String(){...}
...
```
## 3.继承（Inheritance）--表示`is-a`

### a.什么是继承关系？

![继承关系](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BB%A7%E6%89%BF%E5%85%B3%E7%B3%BB.png)

```C++
struct _List_node_base
{
	_List_node_base* _M_next;
	_List_node_base* _M_prev;
};
template<typename _Tp>
struct _List_node
	: public _List_node_base	//public继承：这里只由数据的继承，父类没有函数
{
	_Tp _M_data;
}
```

### b.Inheritance（继承）关系下的构造和析构（从内存角度分析）

![继承关系下的构造和析构](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BB%A7%E6%89%BF%E5%85%B3%E7%B3%BB%E4%B8%8B%E7%9A%84%E6%9E%84%E9%80%A0%E5%92%8C%E6%9E%90%E6%9E%84.png)

**构造由内到外**：Derived的构造函数首先调用Base的default构造函数，然后执行自己

`Derived::Derived(...) : Base() {...};`

**析构由外到内**：Derived的析构函数首先执行自己，然后才调用Base的析构函数

**【注意】base class的dtor必须是virtual，否则会出现undefined behavior**

`Derived::~Derived(...) {... ~Base()};`

### c.Inheritance（继承）with virtual functions（虚函数）

**继承需要搭配虚函数才能达到强有力的效果**，在继承关系中，父类中所有的东西都会被继承下来：**数据**被继承下来，占用了**内存**的一部分，**函数**被继承下来， 是继承了**调用权**（子类可以调用父类的函数）

***

**那么父类的函数，需不需要被重新定义呢？**

从这个角度，父类的函数可以分为三种：

* **non-virtual函数（非虚函数）**：你不希望derived class重新定义（override，复写）它；

* **virtual函数（虚函数）**：你希望derived class重新定义（override）它，且你对它已有默认定义；

* **pure virtual函数（纯虚函数）**：你希望derived class一定要重新定义（override）它，你对它没有默认定义；（注：其实纯虚函数可以由定义）

***

**形状（shape）：世界上并没有叫形状的形状，只有椭圆等；形状是一个抽象的概念，那么可以在这个抽象的层次做些什么呢？（该如何思考呢？）**

![继承搭配虚函数-shape](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BB%A7%E6%89%BF%E6%90%AD%E9%85%8D%E8%99%9A%E5%87%BD%E6%95%B0-shape.png)

1. **bjectID()**：在运行过程中，给没一个产生的对象一个ID，这个产生ID的过程，不管是椭圆还是方形，都是流水号，所以不需要让子类实现它，只需要父类定义它就可以了，那么把它定义为非虚函数

2. **error()**：在执行过程中，可能会报错，设计的父类可以给一个默认的报错形式；但是在设计椭圆或方形时，可能不同的子类可以由更好的报错形式，父类允许子类重新定义error（），所以父类定义为虚函数

3. **draw()**：这个必须要让所有的子类重新定义，因为父类不知道如何定义它，需要将它定义为纯虚函数

通过上述，可知继承要搭配虚函数才能达到最好的效果。

## 4.面向对象的几个应用（设计模式几种经典应用）

### a.模板设计模式（Template Method）【Inheritance + virtual】

* **继承搭配虚函数使用：**

* **场景：将关键执行部分延缓到子类中决定如何执行**

![模板设计模式-继承&虚函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%A8%A1%E6%9D%BF%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F-%E7%BB%A7%E6%89%BF&%E8%99%9A%E5%87%BD%E6%95%B0.png)

```C++
//模拟上边过程
#include<iostream>
using namespace std;

class CDocument
{
public:
	void OnFileOpen()
	{
		//这是个算法，每个cout输出代表一个实际动作
		cout << "dialog..." << endl;
		cout << "check file status ..." << endl;
		cout << "open file..." << endl;
		Serialize();//调用
		cout << "close file..." << endl;
		cout << "update all views..." << endl;
	}
	virtual void Serialize() { };
};

//
class CMyDoc : public CDocument
{
public:
	virtual void Serialize()
	{
		//只有应用程序本身才知道如何读取自己的文件（格式）
		cout << "CMyDoc::Serialize()" << endl;
	}
};

//
int main()
{
	CMyDoc myDoc;//假设对应【File/Open】
	myDoc.OnFileOpen();
}

```

### b.从内存角度分析Inheritance+Composition关系下的构造和析构

* **继承搭配组合使用，分为两种情况：**

![继承&组合-1](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BB%A7%E6%89%BF&%E7%BB%84%E5%90%88-1.png)

第一种：Derived（子类）继承Base（父类），（子类）同时包含了Component类

* 从内存角度分析，Derived既有Base的成分，同时包含了Component

* 那么谁先分配内存呢？或者说谁的构造函数先被执行呢？

	* Derived的构造函数首先调用Base的default构造函数，然后调用Component的default的构造函数，最后才执行自己

`Derived::Derived(...) : Base(), Component() { ... };`

![继承&组合-2](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BB%A7%E6%89%BF&%E7%BB%84%E5%90%88-2.png)

第二种：Derived（子类）继承Base（父类），（父类）包含了Component

* 从内存角度分析，Derived继承了Base的成分，Base包含了Component

* 由内到外调用：先调用Component的default构造函数，再调用Base的default构造函数，最后调用Derived的构造函数。

### c.观察者模式（Observer）【Delegation+Inheritance】

* **将继承和委托搭配起来使用**

![委托&继承-1](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%A7%94%E6%89%98&%E7%BB%A7%E6%89%BF-1.png)

* 通过attach()将Observer对象**注册**到Subject对象中；

* 在外部调用set_val()修改值的同时，**通知**各个观察者；

### d.组合模式（Composite）【Deletation+Inheritance】

* **将继承和委托搭配起来使用**

理解：设想一下Linux中文件和目录的设计，目录也是一种文件，同时是一种容器，可以存放文件，也可以存放目录。那么该如何抽象出同时存放文件（Primitive）和目录（Composite）的文件系统呢？

![委托&继承-2](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%A7%94%E6%89%98&%E7%BB%A7%E6%89%BF-2.png)

### e.原型模式/克隆模式（Prototype）【Deletation+Inheritance】

场景：当父类（提前创建好的）需要一个继承体系并且需要【未来】才能创建子类：这样父类是不知道未来的子类是什么【即class name还没有出现】，父类不能使用new来创建子类，那该怎么实现呢？

* 先让子类创建自身生成原型，再让父类看到子类，最后复制子类，这样就相当于创建了。

* 当子类创建好后，父类如何才能看到呢？

	* 需要由父类创建好空间，由子类将创建好的对象放上去，放上去之后就属于上边的空间，父类就可以看到了

![委托&继承-3](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%A7%94%E6%89%98&%E7%BB%A7%E6%89%BF-3.png)

1. 先调用`-LandSatImage()`构造函数创建对象【原型】，在创建过程中，调用`addPrototype()`将对象放到父类空间，即将子类放到`prototypes[10]`中；

2. 通过放到父类的【原型】调用`findAndClone()`遍历调用`clone()`在创建对象作出副本；

**思考：** 如果没有【原型】，是否可以将`clone()`设为静态函数创建对象呢？
	
不行，因为通过静态函数创建对象，需要class name，这里获取不到class name；

3. 在`clone()`中是通过`#LandSatImage(int)`构造函数创建对象的：`-LandSatImage()`这个构造函数是创建【原型】的，并且这两个构造函数是通过参数int区别的。


















