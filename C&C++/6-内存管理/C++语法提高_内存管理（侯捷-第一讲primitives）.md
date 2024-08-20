	目录：
		第一讲：primitives
		第二讲：std::allocator
		第三讲：malloc/free
		第四讲：loki::allocator
		第五讲：other issues

	所需具备基础：
		曾经动态分配并使用memory
		曾经使用过C++标准库的容器（containers）

	目标：
		从最基础的C++语言构件到高知名度的内存管理器
		
	工具：
		（Dev-C++5.11; with GNU 4.9.2）
		（Visual C++ 6.0）
	
	网络资源：
		http://gee.cs.oswego.edu/dl/

# 第一讲：primitives（基本工具）

## 一、内存分配的每一层面

![内存管理-使用memory的途径](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86-%E4%BD%BF%E7%94%A8memory%E7%9A%84%E9%80%94%E5%BE%84.png)

| 分配 | 释放 | 分类 | 可否重载 |
|  -  |  -  | - | - |
|malloc()|free()|C函数|不可|
|new|delete|C++表达式（expressions）|不可|
|::operator new()|::operator delete()|C++函数|可|
|allocator<T>::allocate()|allocator<T>::deallocate()|C++标准库|可自由设计并搭配任何容器|

## 二、四个层面的基本用法

### 1.malloc & free

```C++
void* p1 = malloc(512); 	//512bytes
free(p1);
```

### 2.new & delete expression

```C++
complex<int>* p2 = new complex<int>;	//one object
delete p2;
```

### 3.  ::operator new() & ::operator delete()

```C++
void *p3 = ::operator new(512);		//512bytes，这个函数里调用的就是malloc
::operator delete(p3);
```

### 4.allocator

【注】其接口虽有标准，但实现商业并未完全遵守；

```C++
#ifdef _MSC_VER						//以下两个函数都是non-static，一定要通过object调用；分配3个int
	int* p4 = allocator<int>().allocate(3, (int*)0);	//(int*)0无用，其实有作用。。。
	allocator<int>().deallocate(p4,3);
#endif

#ifdef __BORLANDC__					//以下两个函数都是non-static,必须通过object调用；分配5个int
	int* p4 = allocator<int>().allocate(5);
	allocator<int>().deallocate(p4,5);		//必须知道容器分配了几个，比如这里的5
#endif

#ifdef __GNUC__	
	void* p4 = alloc::allocate(512);		//以下两个函数都是static，可通过全名调用之；分配512bytes
	alloc::deallocate(p4,512);
	
	//--------上边是2.9版的名字，后边换名字了--------
	void* p4 = allocator<int>().allocate(7);	//以下两个函数都是non-static,必须通过object调用；分配7个int
	allocator<int>().deallocate((int*)p4,7);
	
	void* p5 = __gun_cxx::__pool_alloc<int>().allocate(9);//以下两个函数都是non-static,必须通过object调用；分配9个int
	__gun_cxx::__pool_alloc<int>().deallocate((int*)p5,9);
#endif
```

## 三、new&delete expression源码分析（new operator）

![new&delete_expression](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/new&delete_expression.png)

### 测试：Ctor&Dtor是否能直接调用

* 构造函数不能被直接调用
* 析构函数可以被直接调用

![ctor&dtor_directly](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/ctor&dtor_directly.png)

## 四、array new & array delete源码分析

![arrayNew&arrayDelete](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/arrayNew&arrayDelete.png)

## 五、placement new源码分析

![内存管理-placementNew](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86-placementNew.png)

## 六、分配内存的途径（两种方式）

![分配内存的途径（两种方式）](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%88%86%E9%85%8D%E5%86%85%E5%AD%98%E7%9A%84%E9%80%94%E5%BE%84%EF%BC%88%E4%B8%A4%E7%A7%8D%E6%96%B9%E5%BC%8F%EF%BC%89.png)

## 七、重载内存分配函数的使用（形式）

**注：这里重载的都是operator new函数**

### 1.重载::operator new/::operator delete（全局）

![重载::operator new/::operator delete](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86-%E9%87%8D%E8%BD%BD%E5%85%A8%E5%B1%80new%E5%92%8Cdelete.png)

### 2.重载operator new/operator delete（类内）

![重载operatorNew&operatorDelete的形式](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E9%87%8D%E8%BD%BDoperatorNew&operatorDelete%E7%9A%84%E5%BD%A2%E5%BC%8F.png)

### 3.重载array new/array delete(类内)

![重载arrayNew&arrayDelete](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E9%87%8D%E8%BD%BDarrayNew&arrayDelete%E5%BD%A2%E5%BC%8F.png)

### 4.重载placement new/placement delete

![重载placementNew&placeDelete](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E9%87%8D%E8%BD%BDplacementNew&placeDelete.png)

![重载placementNew的几种形式](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E9%87%8D%E8%BD%BDplacementNew%E7%9A%84%E5%87%A0%E7%A7%8D%E5%BD%A2%E5%BC%8F.png)

![重载placeDelete的几种形式](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E9%87%8D%E8%BD%BDplaceDelete%E7%9A%84%E5%87%A0%E7%A7%8D%E5%BD%A2%E5%BC%8F.png)

### 5.string中的内存分配

![string中的内存分配](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/string%E4%B8%AD%E7%9A%84%E5%86%85%E5%AD%98%E5%88%86%E9%85%8D%E5%88%86%E6%9E%90.png)

## 八、在类中实现小型的内存分配管理

![在类中实现小型的内存分配管理-版本1](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%9C%A8%E7%B1%BB%E4%B8%AD%E5%AE%9E%E7%8E%B0%E5%B0%8F%E5%9E%8B%E7%9A%84%E5%86%85%E5%AD%98%E5%88%86%E9%85%8D%E7%AE%A1%E7%90%86-%E7%89%88%E6%9C%AC1.png)

---

![在类中实现小型的内存分配管理-版本2](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%9C%A8%E7%B1%BB%E4%B8%AD%E5%AE%9E%E7%8E%B0%E5%B0%8F%E5%9E%8B%E7%9A%84%E5%86%85%E5%AD%98%E5%88%86%E9%85%8D%E7%AE%A1%E7%90%86-%E7%89%88%E6%9C%AC2.png)

---

![在类中实现小型的内存分配管理-版本3](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%9C%A8%E7%B1%BB%E4%B8%AD%E5%AE%9E%E7%8E%B0%E5%B0%8F%E5%9E%8B%E7%9A%84%E5%86%85%E5%AD%98%E5%88%86%E9%85%8D%E7%AE%A1%E7%90%86-%E7%89%88%E6%9C%AC3.png)

---

![在类中实现小型的内存分配管理-版本4](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%9C%A8%E7%B1%BB%E4%B8%AD%E5%AE%9E%E7%8E%B0%E5%B0%8F%E5%9E%8B%E7%9A%84%E5%86%85%E5%AD%98%E5%88%86%E9%85%8D%E7%AE%A1%E7%90%86-%E7%89%88%E6%9C%AC4.png)

---

![标准库中内存分配管理](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%A0%87%E5%87%86%E5%BA%93%E4%B8%AD%E5%86%85%E5%AD%98%E5%88%86%E9%85%8D%E7%AE%A1%E7%90%86.png)

## 九、C++基本构建（补充）

![new_handler](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/new_handler.png)

---

![new&delete的default&delete](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/new&delete%E7%9A%84default&delete.png)





