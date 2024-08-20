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
 * 编程思路：
 * 1. 
 * 
 */


#ifndef __COMPLEX__//1.Header（头文件）中的防卫声明
#define __COMPLEX__

//<<<<<<<<<<<<<<<<<<<<<<<<布局1：前置声明（forward declarations）<<<<<<<<<<<<<<<<<<<<<<<<



//<<<<<<<<<<<<<<<<<<<<<<<<布局2：类-声明（class declarations）<<<<<<<<<<<<<<<<<<<<<<<
class complex
{
//2.函数（构造函数或成员函数）若在class body内定义完成，便自动成为【inline】候选人
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
	 * 
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