# ����ת�����쳣���ļ�

***C++����ǿ��ת���ĺô���***���ܸ������ı�������Ҫ��ʲô������ԱֻҪɨһ�������Ĵ��룬������֪��һ��ǿ��ת����Ŀ��

## 01/C++�������ת��

### ��1����̬����ת��`static_cast`

* �������νṹ�л��ࣨ���ࣩ�������ࣨ���ࣩ֮��ָ������õ�ת��
  * ��������ת�������������ָ�������ת���ɻ����ʾ���ǰ�ȫ�ģ�
  * ��������ת�����ѻ���ָ�������ת�����������ʾ��ʱ������û�ж�̬���ͼ�飬�����ǲ���ȫ��
* û�и��ӹ�ϵ���������޷�ת���ɹ���
* �û�������������֮���ת�������intת����char����charת����int������ת���İ�ȫ��ҲҪ������Ա����֤

```C++
void test01()
{
    //1����������ת��
    char a = '';
    double d = static_cast<double>(a);
}
class Base{};
class Son : public Base{};
class Other{}
void test02()
{
    //2���Զ�������ת��
    Base *base = NULL;
    Son *son = NULL;
    Other *other = NULL;
    //����ת��--����ȫ
    son = static_cast<Son*>(base);
    //����ת��--��ȫ
    base = static_cast<Base*>(son);
    //û�и��ӹ�ϵ�������޷�ת���ɹ�
    other = static_cast<Other*>(base);
}
```

### ��2����̬����ת��`dynamic_cast`

* ��֧�ֻ�����������֮���ת��
* ����������ת����`dynamic_cast`��`static_cast`һ��
* ����������ת����`dynamic_cast`�������ͼ�鹦�ܣ���`static_cast`����ȫ
* ���������̬����ô����֮���ת�����ǰ�ȫ��

```C++
class Base
{
    virtual void func(){}
};
class Son : public Base
{
    virtual void func(){}
};
void test()
{
    //���������̬����ô����֮���ת�����ǰ�ȫ��
    Base *base = new Son;
    Son *son = dynamic_cast<Son*> base;
}
```

### ��3����������ת��`const_cast`

�����޸����͵�`const`����

* ����ָ�뱻ת���ɷǳ���ָ�룬��ָ��ԭ���Ķ���
* �������ñ�ת���ɷǳ������ã���ָ��ԭ���Ķ���

***ע�⣺***����ֱ�ӶԷ�ָ��ͷ����õı���ʹ��`const_cast`ȥ�Ƴ�����const

```C++
void test()
{
    //ָ��֮���ת��
    const int *p = NULL;
    //��const int*תΪint*
    int *p2 = const_cast<int *>(p);
    const int *p3 = const_cast<const int *>(p2);
    
    //����֮���ת��
    const int a = 10;
    const int &aRef = a;
    int &aRef2 = const_cast<int &>(aRef);
}
```

## 02/�쳣

### ��1���쳣�����﷨

* C���Դ����쳣ȱ�ݣ�����ֵû��ͳһ������ֵ�������쳣�Ľ����Ҳ��������ȷ�Ľ��
* �쳣����Ҫ���˴������û���κδ���������Զ�����һ��terminate�������ó����жϵ�
* ***ջ������***�쳣���׳��󣬴�try����鿪ʼ����throw�׳��쳣ǰ�����ڼ���ջ�Ϲ�������ж��󣬶��ᱻ�Զ�������������˳���빹���˳���෴����һ���̳�Ϊջ����
  
### ��2���쳣�Ľӿ�����

* Ϊ�˼�ǿ����Ŀɶ��ԣ������ں����������г������׳��쳣���������͡�
  * ����`void func() throw(A,B,C)`���������func�ܹ���ֻ���׳�����A��B��C���������͵��쳣
* ����ں���������û�а����쳣�ӿ������������׳��κ����͵��쳣
* һ�������κ������쳣�ĺ���������Ϊ��`void func() throw()`
  * ���һ�������׳��������쳣�ӿ��������������׳����쳣��`unexcepted`�����ᱻ���ã��ú���Ĭ����Ϊ����`terminate`�����жϳ���

### ��3���쳣��������������

1. `MyException e`����ÿ�������
2. `MyException &e`���÷�ʽ���գ���ʡ���������飩
3. `MyException *e`ָ�뷽ʽ���գ��׳�`&MyException()`�������󣬶����ͷŵ��ˣ������Բ���`e`��
4. `MyException *e`ָ�뷽ʽ���գ��׳�`new MyException()`�����������Ķ��󣬼ǵ��ֶ��ͷ�`delete e`

```C++
class MyException
{
public:
    MyException(){}
    MyException(const MyException &e){}
    ~MyException(){}
}

void doWork()
{
    throw MyException();
}
```
