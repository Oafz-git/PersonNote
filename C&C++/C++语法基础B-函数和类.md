# ��������

## ��һ������

### 1.�꺯����ȱ��

1. ��֤����������-->��Ҫ��С��������

```C++
#define MYADD1(x,y) x+y
#define MYADD2(x,y) ((x)+(y))
void test()
{
    int a = 10;
    int b = 20;
    int ret = MYADD1(a,b) * 20;//410��չ����Ϊ x+y*20
    int ret = MYADD2(a,b) * 20;//600
}
```

2. ��ʹ�����������Σ���Щ�����Ȼ���ֺ�Ԥ�ڲ����Ľ��

```C++
#define MYCOMPARE(a,b) (((a)<(b)) ? (a) : (b))
void test()
{
    int a = 10;
    int b = 20;
    int ret = MYCOMPARE(++a,b); //Ԥ�ڽ��11��ʵ��12��չ��(((++a)<(b)) ? (++a) : (b))
} 
```

3. �꺯��������������

### 2.��������`inline`

1. ���������ͺ����������������������ʵ��ĵط���Ԥ�����һ��չ��**�Կռ任ʱ��**��
2. �������������������һ�𣬷�������ͨ�����Դ���

```C++
inline int func(int a);
inline int func(int a){return++;}
```

3. ��Ա����ǰ�������صļ�����`inline`�ؼ���

### 3.������Ĭ�ϲ���

```C++
int func(int a = 1, int b = 1)
{
    return a + b;
}
```

1. ��������б�����һλ������Ĭ�ϲ�������ô�����λ��������Ҷ�������Ĭ�ϲ���
2. ������������ʵ��ֻ����һ��Ĭ�ϲ���

### 4.������ռλ����

```C++
int func(int a, int = 10)//ռλ����
{
    return a;
}
```

### 5.��������

***��������***
1. ��������ͬ
2. ����������ͬ
3. �������������Ͳ�ͬ�������ͬ��˳��ͬ
4. �����ķ���ֵ������Ϊ�������ص�����
5. ���õ����أ�����const�Ͳ���constҲ������Ϊ��������

***ע�⣺***
```C++
//�������ֲ������úͼ����ÿ���ͬʱ���ã�ע����������
void func(int a){}
void func(int &a){}
void func(const int &a){}
//������������������Ĭ�ϲ�����ע����������
void func(int a, int b = 10){}
void func(int a){}
```

***����ԭ��***
�������ò�ͬ�Ĳ������������β�ͬ�ĺ���������ͬ�ı���������Ϊ��ͬ���ڲ�������
`void func()`�������γ�`_func`
`void func(int x)`�������γ�`_func_int`

### 6.externCǳ��

��;����C++�¿�������C�����ļ�

��ʽһ

```C++
//test.h
void show();

//test.c
void show(){}

//externC.cpp
//#include "test.h"
extern "C" void show();//���߱������������и�show()��������Ҫ��C++�ķ�ʽ���ӣ�Ҫ��C���Եķ�ʽ����
void test()
    {
        show();//_Z4show()
    }
```

��ʽ��

```C++
//test.h
#ifdef __cplusplus
extern "C" {
#endif
void show();
#ifdef __cplusplus
}
#endif

//test.c
void show(){}

//externC.cpp
//#include "test.h"
//extern "C" void show();//���߱������������и�show()��������Ҫ��C++�ķ�ʽ���ӣ�Ҫ��C���Եķ�ʽ����
void test()
    {
        show();//_Z4show()
    }
```

## ��������Ͷ���

### 1.C���Է�װȱ��

1. C������û��������ת���ļ��
2. �����Ժ���Ϊ����

### 2.C++���Է�װ

1. �����ԣ���Ա����������Ϊ����Ա��������Ϊһ�����壬������Щ��Ա����Ȩ�޽��п���
2. C++��struct��class������structĬ��Ȩ��Ϊpublic��classĬ��Ȩ��Ϊprivate
3. Ȩ�ޣ�

|public������Ȩ�ޣ�|protected������Ȩ�ޣ�|private��˽��Ȩ�ޣ�|
| :----: | :----: | :----:|
|���ڿ��Է���|���ڿ��Է���|���ڿ��Է���|
|������Է���|���ⲻ���Է���|���ⲻ���Է���|
|������Է���|������Է���|���಻���Է���|

4. ��������Ա��������Ϊ˽��

�ô���

* �Լ����Կ������ԵĶ�дȨ��
* �ɶ��û���������ݽ��в���

## ������ ����Ĺ��캯������������

### 1.���캯����д��

1. û�з���ֵ��Ҳ��дvoid����������������ͬ
2. �����в��������Է�������
3. �ɱ������Զ����ã���ֻ�����һ�Σ������ֶ�����

### 2.����������д��

1. û�з���ֵ����дvoid����������������ͬ���ں�������ǰ��`~`
2. �������в����������Է�������
3. �ɱ������Զ����ã���ֻ�����һ�Σ������ֶ�����

```C++
class MyClass
{
    public:
        MyClass(){}
        ~MyClass(){}
}
```

### 3.���캯������

1. ���ղ������з��ࣺ�вι��캯�����޲ι��캯����Ĭ�Ϲ��캯����
2. �������ͽ��з��ࣺ��ͨ���캯�����������캯����`const`��`&`���ܶ���

```C++
class Person
{
    public:
        //Ĭ�Ϲ���
        Person(){}
        //�вι���
        Person(int age){m_Age = age;}
        //��������
        Person(const Person &p){m_Age = p.m_Age;}//������const ����& a��
    private:
        int m_Age;
}
```

### 4.���캯������

```C++
void test()
{
    //�޲ι���
    Person p1;
    //�вι���-���ŷ�
    Person p2(10);//�вι������
    Person p3(p2);//�����������
    //�вι���-��ʾ��
    Person p4 = Person(10);//�вι������
    Person p5 = Person(p4);//�����������
    //�вι���-��ʽ��
    Person p6 = 10;//�ȼ��� Person p6 = Person��10��
    Person p7 = p6;
}
```

**ע��**

1. �޲ι��첻���������ŷ�����������Ϊ`Person p()`��һ������������
2. `Person(10)`Ϊ�����������������ص㣺��ǰ��ִ�����ϵͳ�ͻ���
3. �����ÿ������캯��`Person(p)`�����������������󣬱�������Ϊ`Person(p)`��һ������`Person p`

### 5.��������ĵ���ʱ��

1. ʹ��һ���Ѿ������õĶ�������ʼ����һ������

```C++
void test()
{
    Person p1(18);
    Person p2(p1);
}
```

2. ��ֵ���ݵķ�ʽ�������Ĳ�����ֵ

```C++
void doWork(Person p){}
void test()
{
    Person p1;
    doWork(p1);
}
```

3. ��ֵ�ķ�ʽ���ؾֲ�����

```C++
Person doWork()
{
    Person p1;
    return p1;
}
void test()
{
    Person p = doWork();
}
```

### 6.���캯���ĵ��ù���

1. ϵͳ��Ĭ�ϸ�һ�����������3��������Ĭ�Ϲ��캯���������������������캯��
2. ��������Լ��ṩ���вι��캯������ôϵͳ�Ͳ����ṩĬ�Ϲ��캯����������Ȼ���ṩ�������캯��
3. ��������Լ��ṩ�˿������캯������ôϵͳ�Ͳ����ṩ��������ͨ���캯����

### 7.�����ǳ����

```C++
class Person
{
    public:
        Person(char *name, int age)
        {
            m_Name = (char *)malloc(strlen(name)+1);
            strcpy(m_Name, name);
            m_Age = age;
        }
        Person(const Person &p)
        {
            m_Age = p.m_Age;
            //m_Name = p.m_Name;ϵͳ�ṩ��ǳ����
            //�����������ǳ��������������
            m_Name = (char *)malloc(strlen(p.m_Name)+1);
            strcpy(m_Name,p.m_Name);
        }
        ~Person()
        {
            if(m_Name != NULL)
            {
                free(m_Name);
                m_Name = NULL;
            }
        }
        char *m_Name;//����
        int m_Age;//����
}
void test()
{
    Person p1("Tom",18);
    Person p2(p1);
}
```

![�����ǳ����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/�����ǳ����.png)

### 8.��ʼ���б�

��;��������ʼ�����е�����

```C++
class Person
{
    public:
        Person(int a,int b, int c):m_A(a),m_B(b),m_C(c){}
    private:
        int m_A,m_B,m_C;
}
```

### 9.�������Ϊ���Ա

�������������Ϊ�����Ա���ȹ�������������ٹ��������ͷŵ�˳���빹���෴

### 10.`explicit`�ؼ���

��;����ֹ��ʽ����ת����ʽ����ʼ������

### 11.`new` `delete`

C++�н��**��̬�ڴ����**�ķ����ǰѴ���һ����������Ҫ�Ĳ����������һ����Ϊnew����������new����һ������ʱ������**��**��Ϊ��������ڴ沢���ù��캯����ɳ�ʼ��

```C++
Person *person = new Person;//�ڲ���malloc�����ڶ������ж��ڴ��Ƿ���䣬���ù��캯��
//�൱��
Person *person = (Person*)malloc(sizeof(Person));//malloc�����ڶ���
if(person ** null)//�ж��ڴ濪���Ƿ�ɹ�
{
    return 0;
}
person -> Init();//���캯��
```

1. `malloc`��`new`����
    |�ؼ��֣�|malloc|new|
    |----|----|----|
    |���ͣ�|�����|�⺯��|
    |����ֵ��|void*|new�����Ķ����ָ��|
    |�ж��Ƿ񿪱ٳɹ�|��Ҫ|����Ҫ|
    |�Ƿ���ù��캯��|�������|�����|
    |�ͷŹؼ���|free|delete|

2. ��Ҫ��`void*`ȥ����new�����Ķ���ԭ���ǲ��ܹ��ͷ�

   ```C++
   void test()
   {
        void *p = new Person();
        delete (Person *)p;
   }
   ```

3. ����new��������
   * ����new��**����**�������飬���б���Ҫ����Ĭ�Ϲ��캯���������޷�����
   * �ͷ�ʱ��Ҫ��`delete`���`[]`

    ```C++
    Person *person = new Person[10];
    delete []person;//�ͷ�����
    ```

    * ���������**ջ��**���ٵģ���ô����ָ�������ĸ����캯������ʼ������

    ```C++
    Person person[3] = {Person(10),Person(10),Person(10)};
    ```

### 12.��̬��Ա����`static`

* ��һ�����ݳ�Ա��ͬ�����۽����˶��ٸ����󣬶�ֻ��һ����̬���ݵĿ�������̬��Ա����������ĳ���࣬**���ж�����**��
* ��**����׶�**����ռ䣬����û���������Ѿ�����ռ���
* ��̬��Ա����������**���������������ⶨ��**
* ��̬���ݳ�Ա������ĳ��������Ϊ�������ռ��в�������̬��Ա��ռ�ռ�
* ��̬���ݳ�Ա����ͨ��**����**��**����**������
* ��̬��ԱҲ����**����Ȩ��**�ģ�˽��Ȩ��������ʲ���

### 13.��̬��Ա����`static`

* ����ͨ��**����**��**����**���з���
* ��̬��Ա���������Է���**�Ǿ�̬��Ա����**����Ϊ�޷����ֱ����������ĸ�����
* ��̬��Ա�������Է���**��̬��Ա����**����Ϊ���ǹ�������
* �Ǿ�̬��Ա�������Է���**��̬��Ա����**��Ҳ���Է���**�Ǿ�̬��Ա����**
* ��̬��Ա������**����Ȩ��**��˽��Ȩ��������ʲ���

### 14.����ģʽ

һ������ֻ��**Ψһ**��һ��ʵ������

```C++
class ChairMan
{
    private:
        //1��Ϊ�˲��������������Ҫ��Ĭ�Ϲ��캯��˽�л�
        ChairMan(){}
        //5��Ϊ��ʹ�������캯�����������������Ҫ�������������캯��˽�л�
        ChairMan(const ChairMan &c){}
        //public:
        //2��Ϊ��ֻ����һ��������Ҫ����������ֻ����һ�������ָ��
        static ChairMan* singleMan;

    public:
        //4��Ϊ�˲�������ɾ����������Ҫ�����󴴽�Ϊֻ��״̬�����ṩ��ȡ����
        static ChairMan* getInstance()
        {
            return singleMan;
        }

}
    //3����̬��Ա������Ҫ�����������������ⶨ�壻
    //���ң������ChairMan::�����򣬻�ʹ��������Ϊ���д��������ڣ������Է���˽��Ȩ�޵�����
    ChairMan *ChairMan::singleMan = new ChairMan();

void test()
{
    
    ChairMan::singleMan = NULL;//�Ὣ����ɾ��
    
    ChairMan *c1 = ChairMan::getInstance();
    ChairMan *c2 = new ChairMan(*c1);//�������캯���ᴴ���������
    if(c1 == c2){}//����c1��c2�����
}
```

## ���ģ�C++����ģ�ͳ�̽

* ��Ա�����ͳ�Ա�����ֿ��洢
* ����Ĵ�СΪ1
* һ������ֻ��**�Ǿ�̬��Ա����**������Ĵ�С�������������������ڲ�

### 1.thisָ��Ļ���ʹ��

```C++
class Person
{
    public:
        Person(int age)
        {
            //1��thisָ��ָ����Ǳ����õĳ�Ա���������Ķ���this���Խ��������ͻ
            this->age = age;
        }
        //
        void showAge()
        {
            cout << this->age << endl;
        }
        //2�����ӱ�̣���1������ֵ����Ϊ��ǰ��������ã���2������ֵΪ������--*this
        Person &AddAge(Person &p)
        {
            this->age += p.age;
            return *this;
        }

        int age;
}
void test()
{
    Person p1(18);
    p1.showAge();
    Person p2(10);
    p1.AddAge(p2).AddAge(p2);//���ӱ��
    p1.showAge();
}
```

### 2.��ָ����ʳ�Ա����

���һ������ָ����һ����ָ�룬���Է���û��ʹ��this��һЩ��Ա�������������Է���ʹ��thisָ��ĳ�Ա�����������down�������Լ��жϷ�ֹdown����

### 3.�������ͳ�����

thisָ��ı��ʣ�Person *const this������һ��ָ�볣����ָ���ָ���ǲ����޸ĵģ�ָ��ָ���ֵ�ǿ��Ըĵģ�

1. ������
   * �ڳ�Ա�����������const`const Person *const this`������**������**���������в������޸ĳ�Ա���ԣ�
   * �ڳ�Ա����ǰ��`mutable`�ؼ��֣��ڳ������оͿ����޸ĳ�Ա������
2. ������
   * �ڴ�������ǰ��const`const Person p`������**������**�������󲻿����޸ĳ�Ա���ԣ�
   * �ڳ�Ա����ǰ��`mutable`�ؼ��֣�����������޸ĳ�Ա������
   * ������ֻ�ܵ��ó����������ܵ�����ͨ��Ա��������Ϊ��ͨ��Ա�����п����޸ĳ�Ա���ԣ�

```C++
class Person
{
    public:
        void showPerson() const//������
        {
            this->m_A = 100;//��ȷ
            this->m_B = 100;//���󣬳������в����޸����� 
        }

        void showPerson2()//��ͨ��Ա����
        {
            this->m_A = 100;//��ȷ
            this->m_B = 100;//��ȷ
        }

        mutable int m_A;//��ʹ�ǳ�������Ҳ�����޸�
        int m_B;
}
void test()
{
    const Person p;//������
    p.m_A = 100;//���󣬳����󲻿����޸�����
    p.m_B = 100;//��ȷ

    p.showPerson();//��ȷ
    p.shwoPerson2();//������Ϊ��ͨ��Ա�����п����޸ĳ�Ա���ԣ�
}
```

## ���壩��Ԫ`friend`

����������ⲿ�������˽�г�Ա

### 1.ȫ�ֺ�����Ϊ��Ԫ����

```C++
class Building
{
    //ȫ�ֺ�����Ϊ��Ԫ����
    friend void goodGay(Building &building);
    public:
        Building()
        {
            this->m_SittingRoom = "����";
            this->m_BedRoom = "����";
        }
        string m_SittingRoom;
    private:
        string m_BedRoom;
}
void goodGay(Building &building)//ȫ�ֺ���
{
    cout << building.m_SittingRoom << end;//ȫ�ֺ������Է���public
    cout << building.m_BedRoom << endl;//��Ԫ�������Է���private
}
```

### 2.����Ϊ��Ԫ��

1. ��Ԫ��ϵ���ܱ��̳�
2. ��Ԫ��ϵ�ǵ���ģ���A����B�����ѣ�����B��һ������A������
3. ��Ԫ��ϵ�����д����ԣ���B����A�����ѣ���C����B�����ѣ�����C��һ������A�����ѡ�

```C++
class Building;
class goodGay
{
    public:
        goodGay();
        void visit();
    private:
        Building* building;
};
class Building
{
    friend class goodGay;//��Ԫ��
    public:
        Building();
        string m_settingRoom;
    private:
        string m_bedRoom;
};
goodGay::goodGay()
{
    this->building = new Building;
}
void goodGay::visit()
{
    cout << this->building->m_SittingRoom << endl;//����Է���publicȨ��
    cout << this->building->m_bedRoom << endl;//��Ԫ����Է���privateȨ��
}
Building::Building()
{
    this->m_SittingRoom = "����";
    this->m_BedRoom = "����";
}
```

### 3.��Ա������Ϊ��Ԫ����

```C++
class Building;
class goodGay
{
    public:
        goodGay();
        void visit();
        void visit2();
    private:
        Building* building;
};
class Building
{
    friend class goodGay::visit();//��Ա��������Ԫ����
    public:
        Building();
        string m_settingRoom;
    private:
        string m_bedRoom;
};
goodGay::goodGay()
{
    this->building = new Building;
}
void goodGay::visit()
{
    cout << this->building->m_SittingRoom << endl;//����Է���publicȨ��
    cout << this->building->m_bedRoom << endl;//��Ա��������Ԫ�������Է���privateȨ��
}
void goodGay::visit2()
{
    cout << this->building->m_SittingRoom << endl;//����Է���publicȨ��
    cout << this->building->m_bedRoom << endl;//��Ա���������Է���privateȨ��
}
Building::Building()
{
    this->m_SittingRoom = "����";
    this->m_BedRoom = "����";
}
```
