#ifndef __COMPLEX__//1.Header��ͷ�ļ����еķ�������
#define __COMPLEX__

class complex
{
public://3.���ʼ���
	//2.���������캯������Ա����������class body�ڶ�����ɣ����Զ���Ϊ��inline����ѡ��
	
	/**
	 * 4.���캯����
	 * 	a. �������ʹ��Ĭ��ʵ��
	 * 	b. ����ʹ�ó�ʼ���У�initialization list��������ʹ�ø�ֵ��assignments����
	 * 
	 *  */
	complex(double r=0, double i=0) : re(r), im(i){}
	
	complex& operator+=(const complex&);
	
	double real() const {return re;}//����
	double imag() const {return im;}



private:
	double re, im;


};





#endif