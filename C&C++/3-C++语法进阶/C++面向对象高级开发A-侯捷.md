# һ������

1. Ŀ�꣺�������桢�����ı��ϰ�ߣ�ѧϰ����������

	* **Object Based�����ڶ��󣩣������õķ�ʽ��дC++class**
		* class without pointer members��ʾ����Complex�ࡿ
		* class with pointer members��ʾ����String�ࡿ

	* **Object Oriented��������󣩣�ѧϰClasses֮��Ĺ�ϵ**
		* �̳У�inheritance��
		* ���ϣ�composition��
		* ί�У�delegation��

2. �Ƽ��鼮
	
	��C++11 Primer��

	��The C++ Programming Language��

	��Effective C++��

	��Effective C++ Third Edition��

# ����Object Based�����ڶ��󣩣������õķ�ʽ��дC++class

## 1.Complex�ࣺclass without pointer members

```C
//complex.h
#include<iostream>

using namespace std;

/**
 * �ܽ᣺���һ���õ�����Ҫע�⣺
 * 1. ���캯������ʹ�ó�ʼ����
 * 2. ��Ա��������ʹ�ó�����
 * 3. ���������Ĵ��ݾ���ʹ�á����á�������ʹ�á�const������
 * 4. ��������ֵ�ڿ��Ե�����£�����ʹ�á����á�
 * 5. ��Ա���������ŵ�private�У��������󲿷ַŵ�public��
 * 
 */

#ifndef __COMPLEX__//1.Header��ͷ�ļ����еķ�������
#define __COMPLEX__

//<<<<<<<<<<<<<<<<<<<<<<<<����1��ǰ��������forward declarations��<<<<<<<<<<<<<<<<<<<<<<<<



//<<<<<<<<<<<<<<<<<<<<<<<<����2����-������class declarations��<<<<<<<<<<<<<<<<<<<<<<<
class complex
{
/**
 * 2.���������캯�����Ա������
 * 	a. ����class body�ڶ�����ɣ����Զ���Ϊ��inline����ѡ��
 * 	b. ��Ա�����������ص�thisָ��
 */
public://3.���ʼ���

	/**
	 * 4.���캯����
	 * 	a. �������ʹ��Ĭ��ʵ��
	 * 	b. ����ʹ�ó�ʼ���У�initialization list��������ʹ�ø�ֵ��assignments������ֵ��ȳ�ʼ��Ч�ʲ�һЩ
	 * 	c. ���캯����������
	 * 		ע�⣺complex():re(0),im(0){} ������캯�����±ߵĹ��캯�����س�ͻ
	 * 	d. ����ʹ�ã��ѹ��캯���ŵ�private�У�����ģʽ
	 *  */
	complex(double r=0, double i=0) 
	: re(r), im(i)//��ʼ���б�
	{}
	
	/**
	 * 5.const member function������������ �ں�����߼�const
	 * 	������ֻ�ܵ��ó�������
	 * 		ע�⣺���ı��������ݵĶ������롱����const
	 * 		���û�мӣ����û���complex����Ϊ������˵�������ܸı����ݣ�ʱ��
	 * 		����û�н��û����õĺ�������Ϊ��������˵������������Ըı䣩��
	 * 		����ì�ܵģ��������ᱨ������
	 * 
	 * 6.�������ݣ���pass by value vs. pass by reference - to const��
	 * 	a.ʹ�����ȼ�������>ָ��>ֵ������ʹ�����ã����ñ�ָ������������������Ч��
	 *  b.������const�����ı����
	 * 
	 * 7. ����ֵ���ݣ���return by value vs. return by reference - to const��
 	 * 	����ʹ�����ã�����������֪������������reference��ʽ����
 	 * 		����_doapl���������ﷵ�ص���object�������ߣ������Ƿ���ֵ���������ã������ߣ�
	 * 		
	*/

	double real() const {return re;}//����
	double imag() const {return im;}

	/**
	 * 9. ����������+=����Ա��������Ԫ��������
	 * 		�Ὣthis���ص���complex& operator+=(this,const complex&);��
	 * 		c3+=��c2=+c1��������ʹ�ò�����ʱ����Ҫ���Ƿ���ֵ�ǡ����á�		
	 */
	complex& operator+=(/*this,*/const complex&);//����
	

private:
	double re, im;

	/**
	 * 8. ��Ԫ��������������ȡ��private��Ա
	 * 	ע�⣺��ͬ��Ķ�����Ի������˽�г�Ա����ͬ��ĸ�������Ϊ��Ԫ��
	 */
	friend complex& _doapl(complex*, const complex&);
};


//<<<<<<<<<<<<<<<<<<<<<<<<����3����-���壨class definition��<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


inline complex& 
_doapl(complex* ths, const complex& r)
{
	ths->re += r.re;
	ths->im += r.im;
	return *ths;
}


//<<<<<<<<<<<<<<<<<<<<<<<<����4��ȫ�ֺ���<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
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
 * 9. ����������+����Ԫ���������ǳ�Ա��������this����
 * 	ע�⣺������صķ���ֵ��������reference����Ϊ���صıض���local object��
 * 		�����������������Ϊ�ǳ�Ա��������Ϊ��Ա�������أ����ܻ����Ʋ�������
 * 
 * 10. temp object����ʱ����--> typename();
 * 	ʾ����complex(real(x) + real(y), imag(x)+imag(y));
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
 * 9.���������+��-��������һԪ��������ǳ�Ա������
 * 	ע�⣺+���صķ���ֵ����ʹ��reference����Ϊ����ֵ�󶨵���const����
 * 		 -���صķ���ֵ����ʹ��reference����Ϊ����ֵ�ض���local object
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
 * 9.���������<<����Ԫ�����ֻ��ѽ�����õ��������������
 * 	ע�⣺��ֻ���Ƿǳ�Ա����������Ϊ�����os������ʶcomplex���޷�ʹ��thisָ��ʶ��os����
 * 		������os����ǰ����ʹ��const���Σ���Ϊos����ᱻ�޸ģ�
 * 		����ֵ�����ܷ���void����Ϊ���ܻ�����ʹ�ò�����<<
 * 
 */

inline ostream&
operator<< (ostream& os, const complex& x)
{
	return os << '(' << real(x) << ',' << imag(x) << ')';
}

#endif
```

## 2.String�ࣺclass with pointer members

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
    String(const String& str);//copy ctor-----��String s2(s1)    String s2 = s1
    String& operator=(const String& str);//copy op= --------�� s2 = s1 
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
    {//ע��1��δָ����ֵ��Ĭ�Ϲ��캯��
        cout << "String::String(const char* cstr = 0)2" << endl;
        m_data = new char[1];
        *m_data = '\0';
    }
}

inline
String::String(const String& str)
{
    cout << "�������캯��" << endl;
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(this->m_data,str.m_data);
}

inline
String& String::operator=(const String& str)
{
    cout << "������ֵ����" << endl;
    if(this == &str)//ע��2�����Ҽ�⸳ֵ���Լ���ֵ�Լ��������û����һ�����±ߵ�delete���������ɱ��
        return *this;
    
    delete[] m_data;//ע��3����Ҫ�Ȱ�֮ǰ��ָ����ڴ��ͷŵ�
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

## 3.���䣺static--��̬��Ա����&��̬��Ա����

```C
class Account
{
public:
// 1.static�����ã�����Ա�����ͳ�Ա���������ж�����ȥ��
	static double m_rate;
	static void set_rate(const double& x){m_rate = x;}
};
// 2.��̬Data���������ⶨ�壨�������ڷ����ڴ棬�ϱ�ֻ�������������Բ��ø���ֵ��
double Account::m_rate = 8.0;

int main()
{
// 3.���ֵ��÷�ʽ��ͨ��class��ô���á�ͨ��Object����
	Account::set_rate(5.0);
	
// 4.ע�⣺ͨ��Object���ã����Ὣ�����ַ��������this
	Account a;
	a.set_rate(7.0);
}
```
# ����Object Oriented��������󣩣�ѧϰClasses֮��Ĺ�ϵ

## 1.���ϣ�composition����ʾ`has-a`

### a.ʲô�Ǹ��Ϲ�ϵ��

![���Ϲ�ϵ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%A4%8D%E5%90%88%E5%85%B3%E7%B3%BB.png)

```C
//Adapter
template <class T>
class queue
{
	...
protected:
	deque<T> c; //�ײ�����
public:
	//���¶�������c�Ĳ���������ɵ�
	bool empty() const {return c.empty();}
	size_type size() const {return c.size();}
	void push(const value_type & x){c.push_back(x);}
	...
};
```
### b.composition�����ϡ���ϵ�µĹ�����������ڴ�Ƕȷ�����

![���Ϲ�ϵ�Ĺ��������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%A4%8D%E5%90%88%E5%85%B3%E7%B3%BB%E7%9A%84%E6%9E%84%E9%80%A0%E5%92%8C%E6%9E%90%E6%9E%84.png)

**�����������⣺** container�Ĺ��캯�����ȵ���component��default���캯�������ִ���Լ�

`Container::Container(...) : Component() {...};`

��ע�⡿���component��Ҫ�������û���Ҫ�Լ������캯��

**�������⵽�ڣ�** container��������������ִ���Լ���Ȼ��ŵ���component����������

`Container::~Container(...) {... ~Component()};`

## 2.ί�У�Deletagion��--Composition by reference(pointer)

### ʲô��ί�й�ϵ��

![ί�й�ϵ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%A7%94%E6%89%98%E5%85%B3%E7%B3%BB.png)

```C++
// String.hpp---Handle---����
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
	StringRep* rep;//pImpl-->ͨ��ָ��ʵ�ֺ�������
};


// String.cpp---Body---ʵ��"background: aliceblue"
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
## 3.�̳У�Inheritance��--��ʾ`is-a`

### a.ʲô�Ǽ̳й�ϵ��

![�̳й�ϵ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BB%A7%E6%89%BF%E5%85%B3%E7%B3%BB.png)

```C++
struct _List_node_base
{
	_List_node_base* _M_next;
	_List_node_base* _M_prev;
};
template<typename _Tp>
struct _List_node
	: public _List_node_base	//public�̳У�����ֻ�����ݵļ̳У�����û�к���
{
	_Tp _M_data;
}
```

### b.Inheritance���̳У���ϵ�µĹ�������������ڴ�Ƕȷ�����

![�̳й�ϵ�µĹ��������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BB%A7%E6%89%BF%E5%85%B3%E7%B3%BB%E4%B8%8B%E7%9A%84%E6%9E%84%E9%80%A0%E5%92%8C%E6%9E%90%E6%9E%84.png)

**�������ڵ���**��Derived�Ĺ��캯�����ȵ���Base��default���캯����Ȼ��ִ���Լ�

`Derived::Derived(...) : Base() {...};`

**�������⵽��**��Derived��������������ִ���Լ���Ȼ��ŵ���Base����������

**��ע�⡿base class��dtor������virtual����������undefined behavior**

`Derived::~Derived(...) {... ~Base()};`

### c.Inheritance���̳У�with virtual functions���麯����

**�̳���Ҫ�����麯�����ܴﵽǿ������Ч��**���ڼ̳й�ϵ�У����������еĶ������ᱻ�̳�������**����**���̳�������ռ����**�ڴ�**��һ���֣�**����**���̳������� �Ǽ̳���**����Ȩ**��������Ե��ø���ĺ�����

***

**��ô����ĺ������費��Ҫ�����¶����أ�**

������Ƕȣ�����ĺ������Է�Ϊ���֣�

* **non-virtual���������麯����**���㲻ϣ��derived class���¶��壨override����д������

* **virtual�������麯����**����ϣ��derived class���¶��壨override�����������������Ĭ�϶��壻

* **pure virtual���������麯����**����ϣ��derived classһ��Ҫ���¶��壨override�����������û��Ĭ�϶��壻��ע����ʵ���麯�������ɶ��壩

***

**��״��shape���������ϲ�û�н���״����״��ֻ����Բ�ȣ���״��һ������ĸ����ô�������������Ĳ����Щʲô�أ��������˼���أ���**

![�̳д����麯��-shape](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BB%A7%E6%89%BF%E6%90%AD%E9%85%8D%E8%99%9A%E5%87%BD%E6%95%B0-shape.png)

1. **bjectID()**�������й����У���ûһ�������Ķ���һ��ID���������ID�Ĺ��̣���������Բ���Ƿ��Σ�������ˮ�ţ����Բ���Ҫ������ʵ������ֻ��Ҫ���ඨ�����Ϳ����ˣ���ô��������Ϊ���麯��

2. **error()**����ִ�й����У����ܻᱨ����Ƶĸ�����Ը�һ��Ĭ�ϵı�����ʽ�������������Բ����ʱ�����ܲ�ͬ����������ɸ��õı�����ʽ�����������������¶���error���������Ը��ඨ��Ϊ�麯��

3. **draw()**���������Ҫ�����е��������¶��壬��Ϊ���಻֪����ζ���������Ҫ��������Ϊ���麯��

ͨ����������֪�̳�Ҫ�����麯�����ܴﵽ��õ�Ч����

## 4.�������ļ���Ӧ�ã����ģʽ���־���Ӧ�ã�

### a.ģ�����ģʽ��Template Method����Inheritance + virtual��

* **�̳д����麯��ʹ�ã�**

* **���������ؼ�ִ�в����ӻ��������о������ִ��**

![ģ�����ģʽ-�̳�&�麯��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%A8%A1%E6%9D%BF%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F-%E7%BB%A7%E6%89%BF&%E8%99%9A%E5%87%BD%E6%95%B0.png)

```C++
//ģ���ϱ߹���
#include<iostream>
using namespace std;

class CDocument
{
public:
	void OnFileOpen()
	{
		//���Ǹ��㷨��ÿ��cout�������һ��ʵ�ʶ���
		cout << "dialog..." << endl;
		cout << "check file status ..." << endl;
		cout << "open file..." << endl;
		Serialize();//����
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
		//ֻ��Ӧ�ó������֪����ζ�ȡ�Լ����ļ�����ʽ��
		cout << "CMyDoc::Serialize()" << endl;
	}
};

//
int main()
{
	CMyDoc myDoc;//�����Ӧ��File/Open��
	myDoc.OnFileOpen();
}

```

### b.���ڴ�Ƕȷ���Inheritance+Composition��ϵ�µĹ��������

* **�̳д������ʹ�ã���Ϊ���������**

![�̳�&���-1](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BB%A7%E6%89%BF&%E7%BB%84%E5%90%88-1.png)

��һ�֣�Derived�����ࣩ�̳�Base�����ࣩ�������ࣩͬʱ������Component��

* ���ڴ�Ƕȷ�����Derived����Base�ĳɷ֣�ͬʱ������Component

* ��ô˭�ȷ����ڴ��أ�����˵˭�Ĺ��캯���ȱ�ִ���أ�

	* Derived�Ĺ��캯�����ȵ���Base��default���캯����Ȼ�����Component��default�Ĺ��캯��������ִ���Լ�

`Derived::Derived(...) : Base(), Component() { ... };`

![�̳�&���-2](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BB%A7%E6%89%BF&%E7%BB%84%E5%90%88-2.png)

�ڶ��֣�Derived�����ࣩ�̳�Base�����ࣩ�������ࣩ������Component

* ���ڴ�Ƕȷ�����Derived�̳���Base�ĳɷ֣�Base������Component

* ���ڵ�����ã��ȵ���Component��default���캯�����ٵ���Base��default���캯����������Derived�Ĺ��캯����

### c.�۲���ģʽ��Observer����Delegation+Inheritance��

* **���̳к�ί�д�������ʹ��**

![ί��&�̳�-1](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%A7%94%E6%89%98&%E7%BB%A7%E6%89%BF-1.png)

* ͨ��attach()��Observer����**ע��**��Subject�����У�

* ���ⲿ����set_val()�޸�ֵ��ͬʱ��**֪ͨ**�����۲��ߣ�

### d.���ģʽ��Composite����Deletation+Inheritance��

* **���̳к�ί�д�������ʹ��**

��⣺����һ��Linux���ļ���Ŀ¼����ƣ�Ŀ¼Ҳ��һ���ļ���ͬʱ��һ�����������Դ���ļ���Ҳ���Դ��Ŀ¼����ô����γ����ͬʱ����ļ���Primitive����Ŀ¼��Composite�����ļ�ϵͳ�أ�

![ί��&�̳�-2](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%A7%94%E6%89%98&%E7%BB%A7%E6%89%BF-2.png)

### e.ԭ��ģʽ/��¡ģʽ��Prototype����Deletation+Inheritance��

�����������ࣨ��ǰ�����õģ���Ҫһ���̳���ϵ������Ҫ��δ�������ܴ������ࣺ���������ǲ�֪��δ����������ʲô����class name��û�г��֡������಻��ʹ��new���������࣬�Ǹ���ôʵ���أ�

* �������ഴ����������ԭ�ͣ����ø��࿴�����࣬��������࣬�������൱�ڴ����ˡ�

* �����ഴ���ú󣬸�����β��ܿ����أ�

	* ��Ҫ�ɸ��ഴ���ÿռ䣬�����ཫ�����õĶ������ȥ������ȥ֮��������ϱߵĿռ䣬����Ϳ��Կ�����

![ί��&�̳�-3](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%A7%94%E6%89%98&%E7%BB%A7%E6%89%BF-3.png)

1. �ȵ���`-LandSatImage()`���캯����������ԭ�͡����ڴ��������У�����`addPrototype()`������ŵ�����ռ䣬��������ŵ�`prototypes[10]`�У�

2. ͨ���ŵ�����ġ�ԭ�͡�����`findAndClone()`��������`clone()`�ڴ�����������������

**˼����** ���û�С�ԭ�͡����Ƿ���Խ�`clone()`��Ϊ��̬�������������أ�
	
���У���Ϊͨ����̬��������������Ҫclass name�������ȡ����class name��

3. ��`clone()`����ͨ��`#LandSatImage(int)`���캯����������ģ�`-LandSatImage()`������캯���Ǵ�����ԭ�͡��ģ��������������캯����ͨ������int����ġ�


















