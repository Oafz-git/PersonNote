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
	 * 5.const member function（常函数）： 在函数后边加const
	 * 		注意：不改变数据内容的都“必须”加上const
	 * 		如果没有加，在用户将complex设置为const对象（说明对象不能改变数据）时，
	 * 		但是没有将用户调用的函数设置为const函数（说明这个函数可以改变），
	 * 		这是矛盾的，编译器会报错！！！
	 *
	*/
	
	double real() {return re;}//定义
	double imag() const {return im;}

private:
	double re, im;
};

#endif