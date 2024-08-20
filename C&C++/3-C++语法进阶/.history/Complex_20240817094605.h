#ifndef __COMPLEX__//1.Header（头文件）中的防卫声明
#define __COMPLEX__

class complex
{
public://3.访问级别
	//2.函数（构造函数、成员函数）若在class body内定义完成，便自动成为【inline】候选人
	
	/**
	 * 4.构造函数：
	 * 	a. 考虑添加使用默认实参
	 * 	b. 尽量使用初始化列（initialization list），而不使用赋值（assignments）：赋值会比初始化效率差一些
	 * 	c. 构造函数可以重载
	 * 		注意：complex():re(0),im(0){} 这个构造函数和下边的构造函数重载冲突
	 * 	d. 特殊使用：把构造函数放到private中，单例模式
	 *  */
	complex(double r=0, double i=0) : re(r), im(i){}
	
	complex& operator+=(const complex&);//声明
	
	/**
	 * 5.const member function（常量成员函数）：
	 * 	a. 在函数后边加const
	 * 	b. 
	 * 
	 * 
	 * 
	*/
	
	double real() const {return re;}//定义
	double imag() const {return im;}



private:
	double re, im;


};





#endif