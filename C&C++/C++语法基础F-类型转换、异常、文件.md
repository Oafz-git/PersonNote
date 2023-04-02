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

### ��4���쳣�ڶ�̬�е�ʹ��

```C++
class BaseException
{
    virtual void printException() = 0;
}
class NullPointException : public BaseException
{
    virtual void printException()
    {
        cout << "��ָ���쳣" << endl;
    }
}
class OutOfRangeException : public BaseException
{
    virtual void printException()
    {
        cout << "Խ���쳣" << endl;
    }
}
void doWork()
{
    throw NullPointException();
}
void test()
{
    try
    {
        doWork();
    }
    catch(BaseException &e)
    {
        e.printException();
    }
}
```

### ��6��ϵͳ��׼�쳣��ʹ��`include <stdexcept>`

![ϵͳ��׼���쳣��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/ϵͳ��׼���쳣��.png)

```C++
//ϵͳ��׼�쳣��ʹ��
#include <stdexcept>
class Person
{
public:
    Person(int age)
    {
        if(age < 0 || age > 150)
        {
            throw out_of_range("����Խ���쳣��");//
        }
        this->m_Age = age;
    }
    int m_Age;
}
void test()
{
    try
    {
        Person p(151);
    }
    catch(exception &e)
    {
        cout << e.what() << endl;
    }
}
```

## 03/��׼����/�����

![��׼����/�����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/��׼����-�����.png)

### ��1����׼���������ú���

1. `cin.get`�������ж�ȡһ���ַ�
2. `cin.get(��������)`�������з�
3. `cin.getline()`��ȡ���в��ӵ�
4. `cin.ignore(N)`����N���ַ�
5. `cin.peek`͵��1���ַ�Ȼ��Ż�ȥ
6. `cin.putback`���ַ��Żػ�����
7. `cin.fail()`�������еı�־λ��0����������1�����쳣
8. `cin.clear()` `cin.sync()`���ñ�־λ����ˢ�»�����

### ��2����׼��������ú���

1. `cout.put()` `cout.write()`���ó�Ա�����������
2. ͨ������Ա����-��׼��
   1. `int number = 99;`
   2. `cout.width(20);`Ԥ��20�ռ�
   3. `cout.fill('*');`���
   4. `cout.setf(ios::left);`�����
   5. `cout.unsetf(ios::dec);`ж��ʮ������
   6. `cout.setf(ios::showbase);`������ʾ����-����
3. ʹ�ÿ��Ʒ�-��׼��`iomanip`
   1. `cout << setw(20)`Ԥ��20�ռ�
   2. `cout << setfill(`~`)`���
   3. `cout << setiosflags(ios::showbase)`��ʾ���ƻ���
   4. `cout << setiosflags(ios::left)`���������
   5. `cout << hex`��װʮ������

### ��3���ļ��Ķ�д

```C++
void test()
{
    //���ļ�������--�ļ�·��--�򿪷�ʽ
    //ofstream ofs("./test.txt", ios::out | ios::trunc);
    ofstream ofs;
    ofs.open("./test.txt", ios::out | ios::trunc);
    //�ж��ļ��Ƿ�򿪳ɹ�
    //if (!ofs)
    if(!ofs.is_open())
    {
        cout << "�ļ���ʧ��" << endl;
        return;
    }
    //д�ļ�
    ofs << "aaaa" << endl;
    ofs << "ssss" << endl;
    //�ر��ļ���
    ofs.close();
}
```

```C++
void test()
{
    //���ļ�������--�ļ�·��--�򿪷�ʽ
    //ifstream ifs("./test.txt", ios::in);
    ifstream ifs;
    ifs.open("./test.txt", ios::in);
    //�ж��ļ��Ƿ�򿪳ɹ�
    //if(!ifs.is_open())
    if (!ifs)
    {
        cout << "�ļ���ʧ��" << endl;
        return;
    }
    //���ļ�
    //��һ�ַ�ʽ�����ж�ȡ��ֱ���ļ�ĩβ
    char buf[1024] = {0};
    //��ÿ��������뵽��������
    while (ifs >> buf)
    {
        cout << buf << endl;
    }
    //�ڶ��ַ�ʽ
    char buf[1024] = { 0 };
    while (!ifs.eof())
    {
        ifs.getline(buf,sizeof(buf));
        cout << buf << endl;
    }
    //�����ַ�ʽ�������ַ���ȡ
    char c;
    while ((c = ifs.get()) != EOF)
    {
        cout << c;
    }

    //�ر�������
    ifs.close();
}
```
