

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
	 * 9. ����������
	 * 	a.��Ԫ��������
	 * 		��Ա�������Ὣthis���ص���complex& operator+=(this,const complex&);��
	 * 		c3+=��c2=+c1��������ʹ�ò�����ʱ����Ҫ���Ƿ���ֵ�ǡ����á�
	 * 		
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

#endif