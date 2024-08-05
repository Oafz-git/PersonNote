	Ŀ¼��
		��һ����primitives
		�ڶ�����std::allocator
		��������malloc/free
		���Ľ���loki::allocator
		���彲��other issues

	����߱�������
		������̬���䲢ʹ��memory
		����ʹ�ù�C++��׼���������containers��

	Ŀ�꣺
		���������C++���Թ�������֪���ȵ��ڴ������
		
	���ߣ�
		��Dev-C++5.11; with GNU 4.9.2��
		��Visual C++ 6.0��
	
	������Դ��
		http://gee.cs.oswego.edu/dl/

# ��һ����primitives���������ߣ�

## һ���ڴ�����ÿһ����

![�ڴ����-ʹ��memory��;��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86-%E4%BD%BF%E7%94%A8memory%E7%9A%84%E9%80%94%E5%BE%84.png)

| ���� | �ͷ� | ���� | �ɷ����� |
|  -  |  -  | - | - |
|malloc()|free()|C����|����|
|new|delete|C++���ʽ��expressions��|����|
|::operator new()|::operator delete()|C++����|��|
|allocator<T>::allocate()|allocator<T>::deallocate()|C++��׼��|��������Ʋ������κ�����|

## �����ĸ�����Ļ����÷�

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
void *p3 = ::operator new(512);		//512bytes�������������õľ���malloc
::operator delete(p3);
```

### 4.allocator

��ע����ӿ����б�׼����ʵ����ҵ��δ��ȫ���أ�

```C++
#ifdef _MSC_VER						//����������������non-static��һ��Ҫͨ��object���ã�����3��int
	int* p4 = allocator<int>().allocate(3, (int*)0);	//(int*)0���ã���ʵ�����á�����
	allocator<int>().deallocate(p4,3);
#endif

#ifdef __BORLANDC__					//����������������non-static,����ͨ��object���ã�����5��int
	int* p4 = allocator<int>().allocate(5);
	allocator<int>().deallocate(p4,5);		//����֪�����������˼��������������5
#endif

#ifdef __GNUC__	
	void* p4 = alloc::allocate(512);		//����������������static����ͨ��ȫ������֮������512bytes
	alloc::deallocate(p4,512);
	
	//--------�ϱ���2.9������֣���߻�������--------
	void* p4 = allocator<int>().allocate(7);	//����������������non-static,����ͨ��object���ã�����7��int
	allocator<int>().deallocate((int*)p4,7);
	
	void* p5 = __gun_cxx::__pool_alloc<int>().allocate(9);//����������������non-static,����ͨ��object���ã�����9��int
	__gun_cxx::__pool_alloc<int>().deallocate((int*)p5,9);
#endif
```

## ����new&delete expressionԴ�������new operator��

![new&delete_expression](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/new&delete_expression.png)

### ���ԣ�Ctor&Dtor�Ƿ���ֱ�ӵ���

* ���캯�����ܱ�ֱ�ӵ���
* �����������Ա�ֱ�ӵ���

![ctor&dtor_directly](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/ctor&dtor_directly.png)

## �ġ�array new & array deleteԴ�����

![arrayNew&arrayDelete](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/arrayNew&arrayDelete.png)

## �塢placement newԴ�����

![�ڴ����-placementNew](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86-placementNew.png)

## ���������ڴ��;�������ַ�ʽ��

![�����ڴ��;�������ַ�ʽ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%88%86%E9%85%8D%E5%86%85%E5%AD%98%E7%9A%84%E9%80%94%E5%BE%84%EF%BC%88%E4%B8%A4%E7%A7%8D%E6%96%B9%E5%BC%8F%EF%BC%89.png)

## �ߡ������ڴ���亯����ʹ�ã���ʽ��

**ע���������صĶ���operator new����**

### 1.����::operator new/::operator delete��ȫ�֣�

![����::operator new/::operator delete](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%86%85%E5%AD%98%E7%AE%A1%E7%90%86-%E9%87%8D%E8%BD%BD%E5%85%A8%E5%B1%80new%E5%92%8Cdelete.png)

### 2.����operator new/operator delete�����ڣ�

![����operatorNew&operatorDelete����ʽ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E9%87%8D%E8%BD%BDoperatorNew&operatorDelete%E7%9A%84%E5%BD%A2%E5%BC%8F.png)

### 3.����array new/array delete(����)

![����arrayNew&arrayDelete](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E9%87%8D%E8%BD%BDarrayNew&arrayDelete%E5%BD%A2%E5%BC%8F.png)

### 4.����placement new/placement delete

![����placementNew&placeDelete](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E9%87%8D%E8%BD%BDplacementNew&placeDelete.png)

![����placementNew�ļ�����ʽ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E9%87%8D%E8%BD%BDplacementNew%E7%9A%84%E5%87%A0%E7%A7%8D%E5%BD%A2%E5%BC%8F.png)

![����placeDelete�ļ�����ʽ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E9%87%8D%E8%BD%BDplaceDelete%E7%9A%84%E5%87%A0%E7%A7%8D%E5%BD%A2%E5%BC%8F.png)

### 5.string�е��ڴ����

![string�е��ڴ����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/string%E4%B8%AD%E7%9A%84%E5%86%85%E5%AD%98%E5%88%86%E9%85%8D%E5%88%86%E6%9E%90.png)

## �ˡ�������ʵ��С�͵��ڴ�������

![������ʵ��С�͵��ڴ�������-�汾1](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%9C%A8%E7%B1%BB%E4%B8%AD%E5%AE%9E%E7%8E%B0%E5%B0%8F%E5%9E%8B%E7%9A%84%E5%86%85%E5%AD%98%E5%88%86%E9%85%8D%E7%AE%A1%E7%90%86-%E7%89%88%E6%9C%AC1.png)

---

![������ʵ��С�͵��ڴ�������-�汾2](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%9C%A8%E7%B1%BB%E4%B8%AD%E5%AE%9E%E7%8E%B0%E5%B0%8F%E5%9E%8B%E7%9A%84%E5%86%85%E5%AD%98%E5%88%86%E9%85%8D%E7%AE%A1%E7%90%86-%E7%89%88%E6%9C%AC2.png)

---

![������ʵ��С�͵��ڴ�������-�汾3](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%9C%A8%E7%B1%BB%E4%B8%AD%E5%AE%9E%E7%8E%B0%E5%B0%8F%E5%9E%8B%E7%9A%84%E5%86%85%E5%AD%98%E5%88%86%E9%85%8D%E7%AE%A1%E7%90%86-%E7%89%88%E6%9C%AC3.png)

---

![������ʵ��С�͵��ڴ�������-�汾4](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%9C%A8%E7%B1%BB%E4%B8%AD%E5%AE%9E%E7%8E%B0%E5%B0%8F%E5%9E%8B%E7%9A%84%E5%86%85%E5%AD%98%E5%88%86%E9%85%8D%E7%AE%A1%E7%90%86-%E7%89%88%E6%9C%AC4.png)

---

![��׼�����ڴ�������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%A0%87%E5%87%86%E5%BA%93%E4%B8%AD%E5%86%85%E5%AD%98%E5%88%86%E9%85%8D%E7%AE%A1%E7%90%86.png)

## �š�C++�������������䣩

![new_handler](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/new_handler.png)

---

![new&delete��default&delete](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/new&delete%E7%9A%84default&delete.png)





