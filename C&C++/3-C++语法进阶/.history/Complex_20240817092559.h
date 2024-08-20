#ifndef __COMPLEX__//1.Header（头文件）中的防卫声明
#define __COMPLEX__

class complex
{
public://3.访问级别
	//2.函数（构造函数、成员函数）若在class body内定义完成，便自动成为【inline】候选人
	
	/**
	 * 4.构造函数：
	 * 	a. 考虑添加使用默认实参
	 * 	b. 尽量使用初始化列（initialization list），而不使用赋值（assignments）：
	 * 
	 *  */
	complex(double r=0, double i=0) : re(r), im(i){}
	
	complex& operator+=(const complex&);
	
	double real() const {return re;}//定义
	double imag() const {return im;}



private:
	double re, im;


};





#endif