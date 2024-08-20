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
 * ���˼·��
 * 1. 
 * 
 */


#ifndef __COMPLEX__//1.Header��ͷ�ļ����еķ�������
#define __COMPLEX__

//<<<<<<<<<<<<<<<<<<<<<<<<����1��ǰ��������forward declarations��<<<<<<<<<<<<<<<<<<<<<<<<



//<<<<<<<<<<<<<<<<<<<<<<<<����2����-������class declarations��<<<<<<<<<<<<<<<<<<<<<<<
class complex
{
//2.���������캯�����Ա����������class body�ڶ�����ɣ����Զ���Ϊ��inline����ѡ��
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
	 * 
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