# 第一讲：使用C++标准库

## 一.概述

	1.需要具备的基础：C++基本语法 、如何正确使用模版、templates
	
	2.目标
		a.使用C++标准库
		b.深入认识C++标准库
		c.良好使用C++标准库
		d.扩充C++标准库
		
	3.C++ Standard Library（C++标准库） vs. Standard Template Library（STL，标准模版库）
	
		a.C++标准库的header files不带副名（.h）,例如#include<vector>
		b.新式C header files不带副名（.h）,例如#include<cstdio>
		c.旧式C header files带有副名（.h）,例如#include<stdio.h>
		
		d.新式headers内的组件封装于“namespace std”
		e.旧式header内的组件不封装于“namespace std”
		
	4.C++标准库版本
		Visual C++6.0
		Dev-C++5.11; with GNU 4.9.2
	
	5.常用网页
		CPlusPlus.com/CppReference.com/gcc.gnu.org
	
	6.推荐书籍
		《THE C++ STANDARD LIBRARY》《STL源码分析》

### 1.STL6大部件关系

* **容器**：主要是解决内存问题，用户只需要将数据放进去或取出来就可以；

* **分配器**：容器需要分配器的支持

* **算法**：有一些操作是容器本身做的，但是还有更多的操作是独立出来的，形成的一个个函数（模版函数）；

* **迭代器**（相当于一种泛化指针）：想要使用算法去操作容器，需要容器和算法之间的桥梁

* **仿函数**：作用相当于函数，服务于算法

* **适配器**：可以使容器、迭代器、仿函数进行一些特殊的转换

* **OOP编程**：都是将数据和操作放到类中

* **GP模板编程**：将**数据放**到**容器**中，**操作**放到**算法**中
	

![STL6大部件关系](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/STL6%E5%A4%A7%E9%83%A8%E4%BB%B6%E5%85%B3%E7%B3%BB.png)

### 2.复杂度

通过复杂度来确定选择使用哪一种容器

![复杂度](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%A4%8D%E6%9D%82%E5%BA%A6.png)

### 3.前闭后开区间

![前闭后开区间](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%89%8D%E9%97%AD%E5%90%8E%E5%BC%80%E5%8C%BA%E9%97%B4.png)

## 二、容器结构与分类

![容器结构与分类](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8%E7%BB%93%E6%9E%84%E4%B8%8E%E5%88%86%E7%B1%BB.png)

## 三、各个容器的测试

## 四、分配器的使用测试（std::allocator&std::alloc）




