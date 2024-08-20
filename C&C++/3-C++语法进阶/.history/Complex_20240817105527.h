

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
	 * 9. 操作符重载
	 * 	a.二元操作符：
	 * 		成员函数，会将this隐藏掉【complex& operator+=(this,const complex&);】
	 * 		c3+=（c2=+c1）：连串使用操作符时，需要考虑返回值是【引用】
	 * 		
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

#endif