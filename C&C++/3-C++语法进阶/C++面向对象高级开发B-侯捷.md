## һ������

* operator type() const;
* explicit complex(...):initialization list{}
* pointer-like object
* function-like object
* template specialization
* variadic template(since C++11)
* Rvalue reference(since C++11)
* range-base for loop(since C++11)
* Object Modal

## ����ת��������conversion function�� vs. non-explicit-one-argument ctor

### 1.��ʶת������

**��ʽ��**`operator type() const`

```C++
//��Fractionתdouble������תС����
class Fraction
{//
public:
	Fraction(int num, int den = 1)
	:	m_mumerator(num), m_denominator(den) { }
	
	/**
	* �����ʽ����ת���������޷���ֵ������תС����double���ͣ�
	*	ע�⣺����һ��Ҫ��const����Ϊת�����������޸����ݣ�ֻ��ת������
	*/
	operator double() const	
	{				
		return (double) (m_numerator / m_denominator);
	}
private:
	int m_numerator; 	//����
	int m_denominator;	//��ĸ
};

int main()
{
	Fraction f(3,5);
	double d = 4 + f; //����operator double() ��fתΪdouble����������ִ�У���ʶ��+��ʶ��f��
}
```

��ִ��`double d = 4 + f;`ʱ�������������Ҳ�������`operator+`����������ƥ�䣨�����򸡵������������ٳ��Բ����Ƿ���`operator double() const`��ת��������

### 2.��ʶnon-explicit-one-argument-ctor

```C++
class Fraction
{
public:
	Fraction(int num, int den = 1)//ע��two parameter���βΣ� & one argument��ʵ�Σ�
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

��ִ��`Fraction d2=f+4`ʱ����ִ��`operator+`,���������Ҫ���Ĳ�����`Fraction`���ͣ��������ﴫ����`int`,���Ե���`non-explicit ctor`��`4`תΪ`Fraction(4,1)`��Ȼ���ٵ���`operator+`

### 3.�쳣��conversion function vs. non-explicit-one-argument ctor��

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
	* ���ctor����explicit��ctor���operator double()����������
	* ���ctor����explicit���������[Error]conversion from 'double'to 'Fraction' requested
	*/
	Fraction d3 = f+4; //[Error]ambiguous�����壩
}
```
��ע������conversion function��non-explicit-one-argument ctor����������ԣ�������ctorǰ����`explicit`ֻ������ʾ���졣

### 4. ��׼����ת��������ʹ��

![conversion_function](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/conversion_function.png)

## ����pointer-like classes

### 1.��������ָ��

![pointer-like-classes����ָ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/pointer-like-classes%E6%99%BA%E8%83%BD%E6%8C%87%E9%92%88.png)

### 2.���ڵ�������Ҳ��һ������ָ�룩

![pointer-like-class-���ڵ�����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/pointer-like-class-%E5%85%B3%E4%BA%8E%E8%BF%AD%E4%BB%A3%E5%99%A8.png)

## �ġ�function-like classes����ν�º���

![function-like-classes-��ν�º���](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/function-like-classes-%E6%89%80%E8%B0%93%E4%BB%BF%E5%87%BD%E6%95%B0.png)

## �塢ģ����ػ�

### 1.��ģ��(class template)

![class_template](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/class_template.png)

### 2.����ģ��(function template)

![function_template](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/function_template.png)

### 3.��Աģ��(member template)

![member_template](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/member_template.png)

### 4.�������ػ���ƫ�ػ�

![specialization](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/specialization.png)

### 5.ģ��ģ�������template-template parameter��

![template_template_parameter](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/template_template_parameter.png)

#### ˼��������һ��ģ��ģ�������

![not_template_template_parameter](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/not_template_template_parameter.png)

### 6.����������ģ�������variadic templates��-��since C++11��

![variadic_templates](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/variadic_templates.png)

## ����ranged-based for loop��since C++11��

![ranged_based_for_loop](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/ranged_based_for_loop.png)

## �ߡ�reference

![reference](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/reference.png)

## �ˡ�Object Modal������ģ�ͣ�

###  1.��ָ��`vptr`�����`vtbl`����̬�÷�

* ��һ�������麯����ʱ�򣬲����Ƕ��ٸ��麯���������ﶼ��**����ֻ��һ��**ָ��**��ָ��**`vptr`��

* ����������麯��������һ�����麯����

* **��̬��**����������

	1. ������ͨ��ָ��������
	
	2. ���ָ�����������ת��
	
	3. �����麯��
	
![vptr��vtbl](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/vptr%E5%92%8Cvtbl.png)

### 2.����this pointer��ģ�巽������÷�

![����this��ģ�巽�����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%85%B3%E4%BA%8Ethis%E5%8F%8A%E6%A8%A1%E6%9D%BF%E6%96%B9%E6%B3%95%E8%AE%BE%E8%AE%A1.png)

### 3.���ڶ�̬�󶨣�Dynamic Binding��

![Dynamic_Binding](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Dynamic_Binding.png)

















 


