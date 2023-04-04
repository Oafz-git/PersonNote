# ����������

## ��һ�� helloworld

```C++
#include <iostream>     //��׼���롢�����  input ----���룻output ----����� stdio
using namespace std;    //��׼�����ռ� 
int main()              //������ں���
{
    cout << "hello world" << 12334 << endl;//cout ��׼�������endl��������в�ˢ�»�����
    system("pause");// ����
    return EXIT_SUCCESS;
}
```

1. C++��̵�����˼�룺������󡢷��ͱ��
2. C++���������������ԣ���װ���̳С���̬
3. `::`�����������������`::`ǰû���κ�����������£�����ʹ��ȫ��������

## ������namespace��ʹ��

* ��;�����������ͻ
* ʹ�ã���ű������������ṹ�塢��ȡ�����
* ����������������ȫ����������
* �����ռ����Ƕ�������ռ�
* �����ռ��ǿ��ŵģ��ϲ�����������ʱ�������ռ�����³�Ա

```C++
namespace B
{
    int m_A = 20;
}
namespace B
{
    int m_B = 50;
}
```

* �����ռ��ǿ��������ģ��൱���ڱ���ǰ����һ���ؼ���static
  * ��̬static�����ԣ�
        1. �������ڣ�
        2. ֻ���ڱ��ļ���ʹ��

```C++
namespace 
{
    int m_C = 50;// static int m_C = 50;
}
```

* �����ռ��ǿ����������

```C++
namespace veryLongName
{
    int m_A = 0;
}
namespace veryShortName = veryLongName;//�����
```

## ������using������using����ָ��

```C++
namespace k
{
    int s = 1;    
}
void test1()
{
    //ע�⣺��using�����;ͽ�ԭ��ͬʱ����ʱ����Ҫ���������
    int s = 2;
    using k::s;//using����
    cout << s << endl;
}
void test2()
{
    //ע�⣺��using����ָ��;ͽ�ԭ��ͬʱ����ʱ������ʹ�þͽ�ԭ��    
    int s = 2;
    using namespace k;//using����ָ��
    cout << s << endl;
}
```

## ���ģ�C++��C������ǿ

### 1. ȫ�ֱ��������ǿ

ȫ�ֱ����ض���

### 2. ���������ǿ

* �βα������ͼ��
* �βδ���������
* �����������ķ���ֵ���
* ��������ֵ���

### 3. ����ת�����

```C++
void test()
{
    char *p = (char*)malloc(64);//(char*)��C�����п���û�У���C++�����в��ܶ�ʧ
}
```

### 4. `struct`��ǿ

```C++
    struct Person()
    {
        int age;
        void func(); //C���Ե�struct�в��ܷź�����C++���Ե�struct�п��Էź���        
    }
    void test()
    {
        /*struct*/ Person p;//C���������ṹ��ʱ�����struct��C++�����������ṹ����Բ���struct
    }
```

### 5. bool���͵���ǿ

C������û��bool���ͣ�

### 6. ��Ŀ�������ǿ

```C++
    int a = 10;
    int b = 20;
    *(a > b ? &a : &b) = 100; 
    a > b ? a : b = 100;//��C�����м�������C++�п���ͨ����
    //ԭ��C��������Ŀ���������ֵ��C++��������Ŀ��������ر���
```

### 7. const��ǿ

* ȫ��const���α������յ���������������ʱ�﷨ͨ��������Ҳ�ᱨ��

```C++
const int m_A = 100;//ȫ��const
void test()
{
    m_A = 200;//ֱ���޸ģ�C��C++�����﷨����
    //����޸ģ�
    int *p = &m_A;//C����ͨ��
    int *p = (int*)&m_A;//C++�﷨ͨ��
    *p = 200;//�������б���
}
```

* �ֲ�const���α���

```C++
void test()
{
    const int m_B = 100;//�ֲ�const
    int *p = &m_B;//C�﷨ͨ��
    int *p = (int*)&m_B;//C++�﷨ͨ��
    *p = 200;//C���Կ����޸ģ�C++�����޷��޸ģ���������
    int arr[m_B];//C�﷨�����Գ�ʼ�����飻C++����
}
```

<img src= "https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Cplus01.png" width=67%/>

* const���ε�ȫ�ֱ�����C������Ĭ�ϵ����ⲿ���ӣ����������������ļ���ʹ�ã�
* const���ε�ȫ�ֱ�����C++������Ĭ�ϵ����ڲ����ӣ�����ֻ���ڵ�ǰ�ļ�ʹ�ã�����Ҫ��`extern`�����ȫ�ֱ�����������
  
***`const`�����ڴ����***

1. ��`const`���εı���ȡ��ַʱ
2. `const`ǰ����`extern`���κ�ʱ
3. ʹ�ñ�����ʼ��`const`���εı���ʱ

```C++
void test()
{
    int a = 10;
    const int m_A = a;
    int *p = (int*)&m_A;//������ڴ�
    *p = 20;//���޸�
}
```

4. �����Զ�����������ʹ��`const`ʱ

```C++
struct Person
{
    string name;
    int age;
};
void test()
{
    const Person p;
    Person **p = (Person *)&p;//������ڴ�
    pp->name = "aaa";//���޸�
    pp->age = 10;
}
```

***����ʹ��`const`����`#define`***

1. `const`�����ͣ��ɽ��б��������Ͱ�ȫ��飻`#define`�����ͣ����ɽ������ͼ��
2. `const`�������򣻶�`#define`������������Ĭ�϶��崦���ļ���β�����������ָ������������Ч�ĳ�������ô`#define`�Ͳ�����

## ���壩���û����﷨

### 1. ��;�������������

### 2. �﷨��Type &���� = ԭ��;

### 3. ���ñ����ʼ����һ����ʼ�����Ͳ��ܸı�ָ��

### 4. �����������

```C++
//��ʽһ
int arr[10];
int (&pArr)[10] = arr;
//��ʽ��
//�ȶ�������������ٶ�������
typedef int(ARRAY_TYPE)[10];
ARRAY_TYPE &pArr2 = arr;
```

### 5. �����Ĵ��ݷ�ʽ

* ֵ����
* ��ַ����
* ���ô���

### 6. ���õ�ע������

* �����ķ���ֵ��Ҫ�Ƿ��ؾֲ�����������
* ��������ķ���ֵ��һ�����ã�����static���εı���������ô�������������Ϊ��ֵ��������

### 7. ���õı���

   ��C++�ڲ�ʵ����һ��ָ�볣����������ռ�ռ��С��ָ����ͬ

```C++
Type& aRef = val;//�Զ�ת��Type* const ref = &val,��Ҳ��˵������Ϊʲô�����ʼ��
```

### 8. ָ�������

```C++
struct Person
{
    int age;
};
void allocateSpace(Person *&p)
{
    p = (Person*)malloc(sizeof(Person));
    p->age = 100;
}
void test()
{
    Person *p = NULL;
    allocateSpace(p);
}
```

### 9. ����������

* ���ñ�����һ��Ϸ��Ŀռ䣻���Ǽ���const֮���﷨��ͨ���ˡ�

```C++
int &ref = 10;//����
const int &ref = 10;//��ȷ���������Ż��������� int temp = 10; const int &ref = temp;
```

* ʹ�ó���

```C++
void showValue(const int &a)
{
    a = 1000;//��������const�����Ա���
}
void test()
{
    int a = 100;
    showValue(a);
}
```
