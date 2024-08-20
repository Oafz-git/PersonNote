# �������װ����������ء��ַ������װ

**����`[]`,`+`,`<<`,`ǰ��++`,`����++`,`->`,`*`,`=`,`==`,`()`**

## ��һ���������װ������`[]`�����

����`[]`�����������ͨ��`[]`���úͻ�ȡ����

```C++
//MyArray.h
class MyArray//ָ����int����
{
public:
    //Ĭ�Ϲ���
    MyArray();
    //�вι���
    MyArray(int capacity);
    //��������
    MyArray(const MyArray &arr);
    //β��
    void pushBack(int val);
    //����λ����������
    void setData(int index, int val);
    //����λ�û�ȡ����
    int getData(int index);
    //��ȡ�����С
    int getSize();
    //��ȡ��������
    int getCapacity();
    // ����[]�������������Ҫ�������ã���Ϊ�������ò�����Ϊ��ֵ��arr[] = 1000;����ʹ�ã�
    int& operator[] (int index);
    //��������
    ~MyArray();
private:
    //ָ�����������ָ��
    int* pAddress;
    //��������
    int m_Capacity;
    //�����С
    int m_Size;
};
```

```C++
//MyArray.cpp
#include "MyArray.h"
MyArray::MyArray()
{
    cout << "Ĭ�Ϲ��캯������" << endl;
    this->m_Capacity = 100;
    this->m_Size = 0;
    this->pAddress = new int[this->m_Capacity];
}
MyArray::MyArray(int capacity)
{
    cout << "�вι��캯������" << endl;
    this->m_Capacity = capacity;
    this->m_Size = 0;
    this->pAddress = new int[this->m_Capacity];
}
MyArray::MyArray(const MyArray& arr)
{
    cout << "�������캯������" << endl;
    this->m_Size = arr.m_Size;//ע��������Է���arr.m_Size(private)��ͬ����Է���˽������
    this->m_Capacity = arr.m_Capacity;

    //���
    this->pAddress = new int[arr.m_Capacity];
    for (int i = 0; i < arr.m_Size; i++)
    {
        this->pAddress[i] = arr.pAddress[i]; 
    }
}
void MyArray::pushBack(int val)
{
    this->pAddress[this->m_Size] = val;
    this->m_Size++; 
}
void MyArray::setData(int index, int val)
{
    this->pAddress[index] = val;
}
int MyArray::getData(int index)
{
    return this->pAddress[index];
}
int MyArray::getSize()
{
    return this->m_Size;
}
int MyArray::getCapacity()
{
    return this->m_Capacity;
}
int& MyArray::operator[] (int index)
{
    return this->pAddress[index];
}
MyArray::~MyArray()
{
    cout << "������������" << endl;
    if (this->pAddress != NULL)
    {
        delete[] this->pAddress;
        this->pAddress = NULL;
    }
}
```

## ���������������

***���⣺***
�����������ͣ�������֪�������Ӧ����μ��㣨�����ܸı䣩���������Զ����������ͣ�����������֪����

***˵����***
��������أ�operator overloading��ֻ��һ��**�﷨�ϵķ���**��Ҳ������ֻ����һ�ֺ������õķ�ʽ��

* ���ó�Ա�������мӺ����������
* ����ȫ�ֺ������мӺ����������
* ��������ؿ��Խ��к�������

***�﷨��***

* ���������������Ϊȫ�ֺ���������һԪ��һ�����������ڶ�Ԫ����������
* ���������������Ϊ��Ա����������һԪû�в��������ڶ�Ԫ��һ������

### 1.�Ӻ����������

**Ŀ�ģ�** ������`+`���ж�������

```C++
class Person
{
public:
    Person() {}
    Person(int a, int b):m_A(a),m_B(b) {}
    //���ó�Ա�������� �Ӻ����������
    Person operator+(Person &p)
    {
        Person temp;
        temp.m_A = this->m_A + p.m_A;
        temp.m_B = this->m_B + p.m_B;
        return temp;
    }
    int m_A;
    int m_B;
};

//����ȫ�ֺ������� �Ӻ����������
Person operator+(Person& p1, Person& p2)
{
    Person temp;
    temp.m_A = p1.m_A + p2.m_A;
    temp.m_B = p1.m_B + p2.m_B;
    return temp;
}

//�Ӻ���������� ���к�������
Person operator+(Person& p, int a)
{
    Person temp;
    temp.m_A = p.m_A + a;
    temp.m_B = p.m_B + a;
    return temp;
}
```

### 2.�������������

**Ŀ�ģ�** ����ʹ��`cout <<`��`<< endl`�������

```C++
class Person
{
    //��ȫ�ֺ���-������������ر�ΪPerson����Ԫ����������ʹ��Ա����˽�л�
    friend ostream& operator<< (ostream& cout, Person& p);
public:
    Person() {};
    Person(int a, int b)
    {
        this->m_A = a;
        this->m_B = b;
    }
    //void operator<<(ostream &cout){}�������������ֻ��ʹ��ȫ�ֺ������ܳ���cout<<
private:
    int m_A;
    int m_B;
};
//����ֵ��Ҫ��ostream������ʹ��endl
ostream& operator<< (ostream& cout, Person& p)
{
    cout << "p.m_A:" <<p.m_A << "p.m_B:" << p.m_B;
    return cout;
}
```

### 3.`ǰ��++`��`����++`���������

**Ŀ�ģ�** �Լ�д��MyInteger�������ʹ��ǰ��++�ͺ���++

ǰ��++�ͺ���++����ʹ��ǰ��++

```C++
class MyInteger
{
friend ostream& operator<<(ostream& cout, const MyInteger& myInteger);
public:
    //Ĭ�Ϲ��캯��
    MyInteger() { m_Int = 0; }
    //ǰ��++������ֻ�ܷ������ã�����ֵ���ʹ��++����ֻʹ����һ��++
    MyInteger& operator++()
    {
        //�� + 1
        m_Int = m_Int + 1;
        //�󷵻�
        return *this;
    }
    //����++������ֻ�ܷ���ֵ����Ϊ���ص�����ʱ���������ھֲ�����
    MyInteger operator++(int)
    {
        //�� ������ǰ״̬
        MyInteger temp = *this;
        //�� +1 
        m_Int = m_Int + 1;
        //�ٷ���
        return temp;
    }
private:
    int m_Int;
};

//�����const����E0349û������Щ������ƥ���"<<"�������
//������ص���һ����ʱ��������ʱ�������ڴ���ֵ�������ܰ󶨵���ֵ���ã�����Ҫʹ�ó�����ֵ���û���ֵ��������
ostream& operator<<(ostream& cout,const MyInteger& myInteger) 
{
    cout << "m_Int:" <<myInteger.m_Int;
    return cout;
}
void test01()
{
    MyInteger myinteger;
    cout << ++(++myinteger) << endl;
    cout << myinteger << endl;
}
void test02()
{
    MyInteger myinteger;
    cout << myinteger++ << endl;
    cout << myinteger << endl;
}
```

### 4.ָ�����������-����ָ��

**Ŀ�ģ�** �����й�new�����Ķ�����ͷ�
���������ָ�������ָ��һ�����ñ����ͺ�������Ҫ����`->`��`*`

```C++
class Person
{
public:
    Person()
    {
        m_Age = 0;
    }
    Person(int age)
    {
        this->m_Age = age;
    }
    ~Person(){}
    void showAge()
    {
        cout << "m_Age: " << this->m_Age << endl;
    }
private:
    int m_Age;
};
class SmartPointer//����ָ��
{
public:
    SmartPointer(Person* person)
    {
        this->person = person;
    }
    ~SmartPointer()
    {
        if (this->person != NULL)
        {
            delete this->person;
            this->person = NULL;
        }
    }
    //����->�����������ָ��
    Person* operator->()
    {
        return this->person;
    }
    //����*����������ر���-����
    Person& operator*()
    {
        return (*this->person);
    }
private:
    Person* person;
};
void test()
{
    /*Person* person = new Person();
    person->showAge();
    (*person).showAge();
    delete person;*/

    SmartPointer sp = SmartPointer(new Person(18));
    //�����sp������ָ��һ�����ñ����ͺ�������Ҫ����->��*
    sp->showAge();//sp->->showAge();��������Ϊsp->showAge();
    (*sp).showAge();
}
```

### 5.��ֵ�����`=`����

**Ŀ�ģ�** Ϊ�˴�������Ĭ�ϵ�`=`���������ǳ��������

* ϵͳ��Ĭ�ϸ�һ�������4��������Ĭ�Ϲ��졢�������������죨ǳ��������operator=(ǳ����)
* ����ϵͳ�ṩ��`operator=`����м򵥵�ֵ�����������Ա�������ж��������ݣ��ᵼ���ظ��ͷ�--��Ҫ����`operator=`

```C++
class Person
{
public:
    Person(const char* name, int age)
    {
        this->m_Age = age;
        this->m_Name = new char[strlen(name) + 1];
        strcpy(this->m_Name,name);
    }
    Person(const Person &p)
    {
        this->m_Name = new char[strlen(p.m_Name) + 1];
        strcpy(this->m_Name, p.m_Name);
        this->m_Age = p.m_Age;
    }
    //ϵͳ��Ĭ�ϸ�һ���ഴ������3��������Ĭ�Ϲ��졢�������������죨ǳ��������operator=(ǳ����)
    Person& operator=(const Person &person)
    {
        //���ж�ԭ���Ķ����Ƿ������ݣ���������ͷ�
        if (this->m_Name != NULL)
        {
            delete[] this->m_Name;
            this->m_Name = NULL;
        }
        //�����´���name
        this->m_Name = new char[strlen(person.m_Name) + 1];
        strcpy(this->m_Name, person.m_Name);
        this->m_Age = person.m_Age;
        return *this;
    }
    ~Person()
    {
        if(this->m_Name != NULL)
        {
            delete [] this->m_Name;//���������飬[]���ܶ�
            this->m_Name = NULL;
        }
    }
    int m_Age;
    char *m_Name;//ע�������ֵ�Ƕ��������ݣ��������캯����operator=������ǳ��������
};
void test()
{
    Person p1("A", 10);
    Person p2("B", 20);
    p1 = p2;//������Ҫ����=�����
    cout << "p1.m_Name" << p1.m_Name << "age:" << p1.m_Age << endl;
    cout << "p2.m_Name" << p2.m_Name << "age:" << p2.m_Age << endl;
    Person p3(" ", 0);
    p3 = p1 = p2;//��������ص�=����� ��Ҫ���ض���
    cout << "p3.m_Name" << p3.m_Name << "age:" << p3.m_Age << endl;
    Person p4(p3);
    cout << "p4.m_Name" << p4.m_Name << "age:" << p4.m_Age << endl;
}
```

### 6.��ϵ�����`==`����

```C++
class Person
{
public:
    Person(string name, int age)
    {
        this->name = name;
        this->age = age;
    }
    bool operator== (Person &p)//����==�����
    {
        return this->name == p.name && this->age == p.age;
    }
private:
    string name;
    int age;
};
```

### 7.�������������`()`����-�º���

```C++
class Myfunc
{
public:
    void operator() (string s)
    {
        cout << s << endl;
    }
};
void test()
{
    Myfunc myfunc;//STL �º���
    myfunc("");
}
```

### 8.���������ܽ�

* `=` `[]` `()` `->`�����ֻ��ͨ��**��Ա����**��������
* `<<` `>>`�����ֻ��ͨ��**ȫ�ֺ���**���**��Ԫ����**��������
* ��Ҫ����`&&` `||` ���������Ϊ�޷�ʵ�ֶ�·����

## �������ַ������װ

1. �����MyString
2. ��Ա����
   * char* pString ά��ָ�����ָ��
   * int m_Size �ַ�������
3. ��Ա����
   * �вι���
   * ��������
   * ����
4. `<<`����
5. `>>`����
6. `[]`���� ����[]�ַ���д
7. `=`���� ��ֹǳ�����������
8. `+`���� �ַ���ƴ��
9. `==`���� �Ա�


```C++
//MyString.h

#ifndef __MY_STRING_H__
#define __MY_STRING_H__

#include <iostream>
#include <string.h>

using namespace std;

class MyString
{
    //���������
    friend ostream& operator<<(ostream& cout, MyString& myString);

    //���������
    friend istream& operator>>(istream& cin, MyString& myString);

    public:
        //�вι���
        MyString(char* c);

        //��������
        MyString(const MyString& myString);

        //����[]
        char& operator[](int index);

        //����=
        MyString& operator=(MyString& MyString);
        MyString& operator=(char* ch);

        //����+
        MyString operator+(MyString& str);
        MyString operator+(char* ch);

        //����==
        bool operator==(MyString& str);
        bool operator==(char* ch);

        //��������
        ~MyString();
    private:
        int m_Size;
        char* pString;
};

#endif // !__MY_STRING_H__

```


```C++
#include "MyString.h"

MyString::MyString(char* c)
{
    this->pString = new char[strlen(c)+1];
    strcpy(this->pString, c);
    this->m_Size = strlen(c);
}

MyString::MyString(const MyString& myString)
{
    this->pString = new char[myString.m_Size +1];
    strcpy(this->pString, myString.pString);

    this->m_Size = myString.m_Size;
}

MyString::~MyString()
{
    if(this->pString != NULL)
    {
        delete this->pString;
        pString = NULL;
    }

}

ostream& operator<<(ostream& cout, MyString& str)
{
    cout << "MyString:" << str.pString;
    return cout;
}

istream& operator>>(istream& cin, MyString& str)
{
    if(str.pString != NULL)
    {
        delete[] str.pString;
        str.pString = NULL; 
    }
    char buf[1024];//������
    cin >> buf;

    //
    str.pString = new char[strlen(buf)+1];
    strcpy(str.pString,buf);
    str.m_Size= strlen(buf);

    return cin;
}



//����[]
char& MyString::operator[](int index)
{
    return this->pString[index];
}

//����=
MyString& MyString::operator=(MyString& str)
{
    this->m_Size = str.m_Size;
    this->pString = new char[strlen(str.pString)+1];
    strcpy(this->pString, str.pString);
    return *this;
}

MyString& MyString::operator=(char* ch)
{
    this->m_Size = strlen(ch);
    this->pString = new char[strlen(ch)+1];
    strcpy(this->pString, ch);
    return *this;
}

//����+
MyString MyString::operator+(MyString& str)
{
    int newSize = this->m_Size + strlen(str.pString) + 1;

    char *temp = new char[newSize];

    memset(temp,0,newSize);
    strcat(temp, this->pString);//strcat�������ַ���
    strcat(temp, str.pString);

    MyString myString(temp);
    delete [] temp;
    return myString;
}


MyString MyString::operator+(char* ch)
{
    int newSize = this->m_Size+strlen(ch)+1;
    char *temp = new char[newSize];

    memset(temp, 0, newSize);
    strcat(temp, this->pString);//strcat�������ַ���
    strcat(temp,ch);

    MyString myString(temp);
    delete[] temp;
    return myString;

}

//����==
bool MyString::operator==(MyString& str)
{
    if(strcmp(this->pString,str.pString) == 0)
        return true;
    return false;
}


bool MyString::operator==(char* ch)
{
    if(strcmp(this->pString, ch) == 0)
        return true;
    return false;
}
```
