## 一、概述

* operator type() const;
* explicit complex(...):initialization list{}
* pointer-like object
* function-like object
* template specialization
* variadic template(since C++11)
* Rvalue reference(since C++11)
* range-base for loop(since C++11)
* Object Modal

## 二、转换函数（conversion function） vs. non-explicit-one-argument ctor

### 1.认识转换函数

**形式：**`operator type() const`

```C++
//将Fraction转double（分数转小数）
class Fraction
{//
public:
	Fraction(int num, int den = 1)
	:	m_mumerator(num), m_denominator(den) { }
	
	/**
	* 这个形式就是转换函数（无返回值）分数转小数（double类型）
	*	注意：这里一定要加const：因为转换函数不会修改数据，只是转换类型
	*/
	operator double() const	
	{				
		return (double) (m_numerator / m_denominator);
	}
private:
	int m_numerator; 	//分子
	int m_denominator;	//分母
};

int main()
{
	Fraction f(3,5);
	double d = 4 + f; //调用operator double() 将f转为double（从左向右执行，先识别+后识别f）
}
```

在执行`double d = 4 + f;`时，编译器由于找不到满足`operator+`的满足类型匹配（整数或浮点数）；会这再尝试查找是否有`operator double() const`的转换函数。

### 2.认识non-explicit-one-argument-ctor

```C++
class Fraction
{
public:
	Fraction(int num, int den = 1)//注：two parameter（形参） & one argument（实参）
	: m_numerator(num), m_denominator(den) { }
	
	Fraction operator+(const Fraction& f)
	{
		return Fraction(...);
	}
private:
	int m_numerator;
	int m_denominator;
};

int main()
{
	Fraction f(3,5);
	Fraction d2 = f + 4;
}
```

在执行`Fraction d2=f+4`时，先执行`operator+`,这个函数需要传的参数是`Fraction`类型，但是这里传的是`int`,所以调用`non-explicit ctor`将`4`转为`Fraction(4,1)`，然后再调用`operator+`

### 3.异常（conversion function vs. non-explicit-one-argument ctor）

```C++
class Fraction
{
public:
	Fraction(int num, int den=1)
	 : m_numerator(num), m_denominator(den) { }
	 
	operator double() const
	{				
		return (double) (m_numerator / m_denominator);
	}

	Fraction operator+(const Fraction& f)
	{
		return Fraction(...);
	}
};

int main()
{
	Fraction f(3,5);
	
	/**
	* 如果ctor不加explicit，ctor会和operator double()产生二义性
	* 如果ctor加上explicit，这里会有[Error]conversion from 'double'to 'Fraction' requested
	*/
	Fraction d3 = f+4; //[Error]ambiguous（二义）
}
```
【注】这里conversion function和non-explicit-one-argument ctor会产生二义性，可以在ctor前加上`explicit`只允许显示构造。

### 4. 标准库中转换函数的使用

![conversion_function](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/conversion_function.png)

## 三、pointer-like classes

### 1.关于智能指针

![pointer-like-classes智能指针](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/pointer-like-classes%E6%99%BA%E8%83%BD%E6%8C%87%E9%92%88.png)

### 2.关于迭代器（也是一种智能指针）

![pointer-like-class-关于迭代器](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/pointer-like-class-%E5%85%B3%E4%BA%8E%E8%BF%AD%E4%BB%A3%E5%99%A8.png)

## 四、function-like classes，所谓仿函数

![function-like-classes-所谓仿函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/function-like-classes-%E6%89%80%E8%B0%93%E4%BB%BF%E5%87%BD%E6%95%B0.png)

## 五、模板和特化

### 1.类模板(class template)

![class_template](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/class_template.png)

### 2.函数模板(function template)

![function_template](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/function_template.png)

### 3.成员模板(member template)

![member_template](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/member_template.png)

### 4.泛化、特化和偏特化

![specialization](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/specialization.png)

### 5.模板模板参数（template-template parameter）

![template_template_parameter](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/template_template_parameter.png)

#### 思考：这是一个模板模板参数吗？

![not_template_template_parameter](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/not_template_template_parameter.png)

### 6.数量不定的模板参数（variadic templates）-（since C++11）

![variadic_templates](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/variadic_templates.png)

## 六、ranged-based for loop（since C++11）

![ranged_based_for_loop](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/ranged_based_for_loop.png)

## 七、reference

![reference](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/reference.png)

## 八、Object Modal（对象模型）

###  1.虚指针`vptr`、虚表`vtbl`及多态用法

* 当一个类有虚函数的时候，不管是多少个虚函数，对象里都会**有且只有一个**指针**虚指针**`vptr`；

* 如果父类有虚函数，子类一定有虚函数；

* **动态绑定**的三个条件

	1. 必须是通过指针来调用
	
	2. 这个指针必须是向上转型
	
	3. 调用虚函数
	
![vptr和vtbl](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/vptr%E5%92%8Cvtbl.png)

### 2.关于this pointer及模板方法设计用法

![关于this及模板方法设计](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%85%B3%E4%BA%8Ethis%E5%8F%8A%E6%A8%A1%E6%9D%BF%E6%96%B9%E6%B3%95%E8%AE%BE%E8%AE%A1.png)

### 3.关于动态绑定（Dynamic Binding）

![Dynamic_Binding](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Dynamic_Binding.png)

















 


