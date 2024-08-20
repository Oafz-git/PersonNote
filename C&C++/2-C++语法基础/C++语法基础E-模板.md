# ģ��

����ģ�壺����һ��ͨ�ú������亯�����ͺ��β����Ͳ������ƶ�����һ�����������������

* C++�ṩ����ģ����ƣ�**����ģ��**��**��ģ��**

* ���ͱ�̣����Ͳ��������ֳ�**����ģ��**

## һ������ģ��

### 1.�����﷨

1. ��������ģ�棺`template<typename T>`T��һ��ͨ�����ͣ����߱�������������ŵĺ��������г�����T����Ҫ����
2. ���ú���ģ�棺
   * �Զ������Ƶ��������ñ������Ƶ���һ�µ�T������ʹ��ģ��--�����Խ�����ʽ����ת��
   * ��ʾָ�����ͣ���ʾ���߱�����T������--���Խ�����ʽ����ת�������ת���ɹ���Ҳ������ʹ�����ģ��
   * ���û�в���������ģ�����ָ����T�����ͣ��ſ���ʹ��

```C++
//����ģ��ʵ��ͨ�ý���������T��һ��ͨ�����ͣ����߱�������������ŵĺ��������г�����T����Ҫ����
template<typename T>
void mySwap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
void mySwap2(){}

void test()
{
    int a = 10;
    int b = 20;
    //1���Զ������Ƶ��������ñ������Ƶ���һ�µ�T������ʹ��ģ��
    mySwap(a,b);
    //2����ʾָ�����ͣ����Խ�����ʽ����ת�������ת���ɹ���Ҳ������ʹ�����ģ��
    mySwap<int>(a,b);
    //3�����û�в���������ģ�����ָ����T�����ͣ��ſ���ʹ��
    mySwap2<int>();
}
```

#### ʾ����ͨ��ѡ��ʵ��int��char����

```C++
//ͨ��ѡ��ʵ��int��char����
template<typename T>
void mySwap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
void mySort(T arr[],int len)
{
    for (int i=0;i<len ;i++)
    {
        int min = i;
        for (int j = i+1; j < len; j++)
        {
            if (arr[min] > arr[j])
            {
                min = j;//��¼��Сֵ�±�
            }
        }
        if (i != min)//��������ֵ����
        {
            mySwap(arr[i],arr[min]);
        }
    }
}

template<typename T>
void printArr(T arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << endl;
    }
}
int test()
{
    int arr[] = {3,6,2,5,1};
    int len = sizeof(arr) / sizeof(int);
    mySort(arr,len);
    printArr(arr,len);

    char charArr[] = "helloworld";
    int charlen = sizeof(charArr) / sizeof(char);
    mySort(charArr,charlen);
    printArr(charArr,charlen);
}
```

### 2.����ģ�����ͨ����������

1. �����ͨ�����ͺ���ģ�����ͬʱ���ã�**���ȵ�����ͨ����**��
2. ����ͨ�����ͺ���ģ�����ͬʱ���õ�����������ǿ�Ƶ��ú���ģ���е����ݣ�����**ʹ�ÿղ����б�**
3. ����ģ���������
4. �������ģ����Բ������õ�ƥ�䣬��ô����ʹ�õ��Ǻ���ģ��

```C++
template<typename T>
void myPrint(T a, T b)
{
    cout << "����ģ��" << endl;
}
template<typename T>
void myPrint(T a, T b, T c)
{
    cout << "����ģ��<T a, T b, T c>" << endl;
}
void myPrint(int a, int b)
{
    cout << "��ͨ����" << endl;
}
void test()
{
    //1�������ͨ�����ͺ���ģ�����ͬʱ���ã����ȵ�����ͨ����
    int a = 10;
    int b = 20;
    myPrint(a,b);
    //2�������ǿ�Ƶ��ú���ģ���е����ݣ�����ʹ�ÿղ����б�
    myPrint<>(a,b);
    //3������ģ��Ҳ���Է�����������
    myPrint(a,b,10);
    //4���������ģ����Բ������õ�ƥ�䣬��ô����ʹ�õ��Ǻ���ģ��
    char c = 'c';
    char d = 'd';
    myPrint(c,d);
}
```

### 3.ģ�����

* �����������ǰѺ���ģ�崦����ܹ������κ����͵ĺ���
* **����ģ��**ͨ���������Ͳ�����ͬ�ĺ���---**ģ�溯��**
* ��������Ժ���ģ�����**���α���**����**����**ʱ��ģ����뱾����б��룬��**����**ʱ�Բ����滻��Ĵ�����б���

### 4.ģ������Լ����廯

***���⣺***
ģ�岢����������ͨ�ô��룬����һЩ�Զ����������ͣ�ģ����ʱ����ʵ��Ч��  
***������***
����ͨ��**���廯**ʵ�ֶ��Զ����������ͽ��в���

```C++
class Person
{
public:
    Person(string name ,int age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }
    string m_Name;
    int m_Age;
};
template<typename T>
bool myCompare(T& a, T& b)
{
    if (a == b)
    {
        return true;
    }
    return false;
}



//ģ����廯��ʽ
template<> 
bool myCompare<Person>(Person& a, Person& b)
{
    cout << "���þ��廯����" << endl;
    if (a.m_Name == b.m_Name && a.m_Age == b.m_Age)
    {
        return true;
    }
    return false;
}
void test()
{
    Person p1("Tom",10);
    Person p2("Jerry", 20);       
    bool ret = myCompare(p1,p2);
    if (ret)
    {
        cout << "���" << endl;
    }
    else
    {
        cout << "�����" << endl;
    }
}
```

## ������ģ��

### 1.�����﷨

* ��ģ�壺template�������һ���࣬��ô������Ϊ��ģ��
* ��ģ�����Ϳ�������Ĭ�ϲ���
* ��ģ�岻��ʹ���Զ������Ƶ���������ʾָ������

```C++
//��ģ�壺template�������һ���࣬��ô������Ϊ��ģ��
//��ģ���е����Ϳ�������Ĭ�ϲ���
template<class NAMETYPE, class AGETYPE = int>
class Person
{
public:
    Person(NAMETYPE name, AGETYPE age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }
    NAMETYPE m_Name;
    AGETYPE m_Age;
};
void test()
{
    Person<string> p("Tom",11);//��ģ�岻��ʹ���Զ������Ƶ���������ʾָ������
    cout << "������" << p.m_Name << "���䣺" << p.m_Age << endl;
}
```

### 2.��ģ���г�Ա�����Ĵ���ʱ��

* ��ģ���е�**��Ա����**��������һ��ʼ�ʹ��������ģ�����**����ʱ**������

```C++
class Person1
{
public:
    void showPeron1(){}
};
class Person2
{
public:
    void showPerson2(){}
};
template<class T>
class Person
{
public:
    void func1()
    {
        obj.showPerson1();
    }
    void func2()
    {
        obj.showPerson2();
    }
    T obj;
};
void test()
{
    Person<Person1> p1;
    p1.func1();
    p1.func2();
}
```

### 3.��ģ����Ϊ�������������ַ�ʽ��

```C++
template<class NAMETYPE, class AGETYPE>
class Person
{
public:
    Person(NAMETYPE name, AGETYPE age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }
    NAMETYPE m_Name;
    AGETYPE m_Age;
};
//1��ָ����������
void doWork1(Person<string,int> & p)
{
    cout << p.m_Name << p.m_Age << endl;
}
//2������ģ�廯
template<class T1, class T2>
void doWork2(Person<T1,T2>& p)
{
    cout << typeid(T1).name() << endl;//�鿴��������
    cout << p.m_Name << p.m_Age << endl;
}
//3�����������ģ�滯
template<class T>
void doWork3(T& p)
{
    cout << p.m_Name << p.m_Age << endl;
}
void test()
{
    Person<string,int> p("A",10);
    doWork3(p);
}
```

### 4.��ģ�������̳е����⼰���

```C++
template<class T>
class Base
{
public:
    T m_A;
}
template<class T1, class T2>
class Son : public Base<T2>
{
public:
    T1 m_B;
}
void test()
{
    Son<int double> s;
}

```

### 5.��ģ�������ʵ��

```C++
template<class T1, class T2>
class Person
{
public:
    Person(T1 name , T2 age);
    void showPerson();
    T1 m_Name;
    T2 m_Age;
};
//���캯��������ʵ��
template <class T1, class T2>
Person<T1,T2>::Person(T1 name ,T2 age){}
//��Ա����������ʵ��
template<class T1, class T2>
void Person<T1,T2>::showPerson() {}
```

#### 6.��ģ��ķ��ļ���д���⼰���

* ��ģ��**�����������ļ���д**����Ϊ��Ա����**����ʱ�������н׶�**��ʹ��ʱ�����Ҫ���� `.cpp`�ſ���
* �����еĳ�Ա������������ʵ��д��һ���ļ��У������ļ��ĺ�׺����Ϊ`.hpp`����

### 7.��ģ�����Ԫ

```C++
template<class T1, class T2> class Person;

//���߱������и�ģ�������
template<class T1, class T2> void printPerson2(Person<T1, T2>& p);

//��ģ�庯����������ʵ��д��һ��
template<class T1, class T2> 
void printPerson3(Person<T1, T2>& p)
{
    cout << p.m_Name << p.m_Age << endl;
}

template<class T1, class T2>
class Person
{
    //1��ȫ�ֺ�������Ԫ������ʵ��
    friend void printPerson(Person<T1, T2>& p)
    {
        cout << p.m_Name << p.m_Age << endl;
    }

    //2��ȫ�ֺ�������Ԫ������ʵ��
    friend void printPerson2<>(Person<T1, T2>& p);

    //3��ȫ�ֺ�������Ԫ������ʵ��
    friend void printPerson3<>(Person<T1, T2>& p);
public:
    Person(T1 name, T2 age)
    {
        this->m_Age = age;  
        this->m_Name = name;
    }
private:
    T1 m_Name;
    T2 m_Age;
};

template <class T1, class T2>
void printPerson2(Person<T1, T2>& p)
{
    cout << p.m_Name << p.m_Age << endl;
}

void test()
{
    Person<string, int> p("sss", 10);
    //printPerson(p);
    //printPerson2(p);
    printPerson3(p);
}
```
