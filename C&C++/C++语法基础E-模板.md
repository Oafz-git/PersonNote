# ģ��

C++����ģ�壺����һ��ͨ�ú������亯�����ͺ��β����Ͳ������ƶ�����һ��������������������ͨ�ú����ͳ�Ϊ**����ģ��**

* C++�ṩ����ģ����ƣ�**����ģ��**��**��ģ��**
* ���ͱ�̣����Ͳ��������ֳ�**����ģ��**

## 01/����ģ������﷨

1. ��������ģ�棺`template<typename T>`T��һ��ͨ�����ͣ����߱�������������ŵĺ��������г�����T����Ҫ����
2. ���ú���ģ�棺
   * �Զ������Ƶ��������ñ������Ƶ���һ�µ�T������ʹ��ģ��--�����Խ�����ʽ����ת��
   * ��ʾָ�����ͣ���ʾ���߱�����T������--���Խ�����ʽ����ת�������ת���ɹ���Ҳ������ʹ�����ģ��
   * ģ�����ָ����T�����ͣ��ſ���ʹ��

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
    //3��ģ�����ָ����T�����ͣ��ſ���ʹ��
    mySwap2<int>();
}
```

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

## 02/����ģ�����ͨ����������

1. �����ͨ�����ͺ���ģ�����ͬʱ���ã����ȵ�����ͨ����
2. �����ǿ�Ƶ��ú���ģ���е����ݣ�����ʹ�ÿղ����б�
3. ����ģ��Ҳ���Է�����������
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

## 03/ģ����ƣ��˽⣩

* �����������ǰѺ���ģ�崦����ܹ������κ����͵ĺ���
* ����ģ��ͨ���������Ͳ������ǵĺ���
* ��������Ժ���ģ��������α��룬�������ĵط���ģ����뱾����б��룬�ڵ��õĵط��Բ����滻��Ĵ�����б���

## 04/ģ������Լ����廯���˽⣩

***���⣺***
ģ�岢����������ͨ�ô��룬����һЩ�Զ����������ͣ�ģ����ʱ����ʵ��Ч��
***������***
����ͨ�����廯ʵ�ֶ��Զ����������ͽ��в���

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
//ģ����廯
template<> bool myCompare<Person>(Person& a, Person& b)
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

## 05/��ģ������﷨

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

## 06/��ģ���г�Ա�����Ĵ���ʱ��

��ģ���еĳ�Ա������������һ��ʼ�ʹ��������ģ���������ʱ������

## 07/��ģ����Ϊ��������


