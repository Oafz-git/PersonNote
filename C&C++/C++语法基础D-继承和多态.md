# �̳С���̬

## ��һ���̳к�����

### 1.�����﷨

***���ã�*** ���ü̳п��Լ����ظ�����
***������*** ���ࣨ���ࣩ  �����ࣨ���ࣩ
***�﷨��*** `class ���� ���̳з�ʽ ����`

```C++
class BasePage//����
{
    public:
        void header()
        {
            cout << "����ͷ��" << endl;
        }
}
class GamePage : public BasePage//������
{
    public:
        void content()
        {
            cout << "Game" << endl;
        }
}
class NewsPage : public BasePage
{
    public:
        void content()
        {
            cout << "news" << endl;
        }
}
```

### 2.�̳з�ʽ

![�̳з�ʽ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/�̳з�ʽ.png)

### 3.�̳��еĶ���ģ��

* ������˽�����ԣ�����Ҳ�̳���ȥ�ˣ��������������أ��޷�����
* ����ͨ�� ������Ա������ʾ���ߣ�Developer Command Prompt for VS 2019�����в鿴����ģ��
  * ��ת����ӦĿ¼�£�����`cl /d1 reportSingleClassLayout���� �ļ���`

```C++
class Base
{
public:
    int m_A;
protected:
    int m_B;
private:
    int m_C;
};
class Son : public Base
{
public:
    int m_D;
};
int main()
{
    cout << sizeof(Son) << endl;//16
}
```

### 4.�̳��еĹ��������

* �̳��У��ȵ��ø���Ĺ��죬���������Ĺ��죬�����͹���˳���෴
* �������ó�ʼ���б��﷨��ʾָ�������ø�����ĸ����캯��
* ���಻��̳и����еĹ����������ֻ�и����Լ���֪����ι���������Լ�������

```C++
class Base
{
public:
    Base(int i) 
    {
        cout << "Base" << i << endl;
    }
    ~Base()
    {
        cout << "~Base" << endl;
    }
};
class Son : public Base
{
public:
    Son(int i) : Base(i)//��ʼ���б�
    {
        cout << "Son" << i << endl;
    }
    ~Son()
    {
        cout << "~Son" << endl;
    }
};
```

### 5.�̳���ͬ���ĳ�Ա��̬��Ա����

* �������͸���ӵ��ͬ����Ա�����ȵ�������ĳ�Ա������ͨ����������ø���ĳ�Ա
* ͬ���ĳ�Ա��������������ص������е����а汾���������ø����е������汾�����������򼴿�
* ��̬��Ա����ͨ��Ա�Ĵ���ʽ���ƣ�ֻ�Ǿ�̬��Ա����ͨ���������з���

```C++
class Base
{
public:
    Base()
    {
        this->m_A = 100;
    }
    void func()
    {
        cout << "Base::func" << endl;
    }
    void func(int i)
    {
        cout << "Base::func" << i << endl;
    }
    int m_A;
};
class Son : public Base
{
public:
    Son()
    {
        this->m_A = 200;
    }
    void func()
    {
        cout << "Son::func" << endl;
    }
    int m_A;
};
void test()
{
    Son s;
    cout << s.m_A << endl;//����Son���е�m_A
    cout << "Base: " << s.Base::m_A << endl;//����Base���е�m_A

    //ͬ���ĳ�Ա��������������ص������е����а汾
    s.func(); //����Son���е�func
    s.Base::func();//����Base���е�func
}

```

### 6.��̳��﷨

* class���ࣺ�̳з�ʽ ����1���̳з�ʽ ����2
* �����������У���ͬ���ĳ�Ա������̳к󣬵���ʱ��Ҫ���������������

```C++
class Base1
{
public:
    Base1()
    {
        m_A = 100;
    }
    int m_A;
};
class Base2
{
public:
    Base2()
    {
        m_A = 200;
    }
    int m_A;
};
class Son : public Base1, public Base2
{
public:
    Son()
    {
        m_C = 300;
    }
    int m_C;
};
void test()
{
    Son s;
    //���������У���ͬ���ĳ�Ա������̳к󣬵���ʱ��Ҫ���������������
    cout << s.Base1::m_A << endl;
    cout << s.Base2::m_A << endl;
}
```

### 7.���μ̳к���̳�

![���μ̳�](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/���μ̳�.png)

***���⣺***

1. ��̳��˶�������ݺͺ�������Ҳ�̳��˶�������ݺͺ���������������ú���������ʱ���ͻ����������
2. ������̳��Զ���ĺ������������ݣ�����ֻ��Ҫһ�ݣ���һ�ݻᱻ�˷�

***����***

* ʹ��`virtual`�ؼ���-��̳�
* ��Sheep��Tuo���м̳е�����Ϊ`vbptr`�������ָ�룩
  * `v`---`virtual`
  * `b`---`base`
  * `ptr`---`pointer`
  * `vbptr`ָ��`vbtable`��������
  * `vbtable`����ƫ������ͨ��ƫ���������ҵ�Ψһ������

![��̳�](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/���μ̳к���̳�.png)

```C++
class Animal//�����
{
public:
    int m_Age;
};
class Sheep : virtual public Animal{};//��̳�
class Tuo : virtual public Animal{};
class SheepTuo : public Sheep, public Tuo{};
void test()
{
    SheepTuo st;
    st.Sheep::m_Age = 100;
    st.Tuo::m_Age = 200;
    cout << st.m_Age << endl;
}
```

## ��������̬

* ��̬���ṩ�˽ӿ������ʵ��֮��ĸ��룬�Ӷ�����what���͡�how�����뿪��
* ��̬�ĺô�������չ����ߣ���֯��ǿ���ɶ���ǿ
  * ��������������麯�������ಢû����д������麯������ô�����Ĵ����Ǻ��������
  * ������಻��д�����麯������û��ʹ�ö�̬�����ĺô��������ڲ��ṹ���Ӹ���
* �����дԭ�򣺿���ԭ�򣨶���չ���п��ţ����޸Ľ��йرգ�

### 1.��̬����Ͷ�̬����

* ����ʱ��̬����̬��̬������������غͺ�������
* ����ʱ��̬����̬��̬������������麯��
* ��̬��̬�Ͷ�̬��̬���𣺺�����ַ��󶨣���̬���ࣩ������󶨣���̬���ࣩ
  * �������ã��ڱ���׶ξͿ���ȷ�������ĵ��õ�ַ�����������룬��ַ�����
  * �������ã������ڱ����ڼ�ȷ��������Ҫ������ʱȷ������ַ�������

* �����и��ӹ�ϵ�������࣬C++���Բ���Ҫͨ������ǿת

***��̬���������***

1. ���������麯��
2. ����**��д**������麯��
3. ��ʹ�ã������ָ�������ָ���Ӷ���

***��д***---`virtual`�麯��

1. ��������ʵ�ָ����е��麯�������뷵��ֵ��������������һ�²ų�Ϊ��д
2. ����������дʱ�����Բ��ӹؼ���`virtual`

```C++
class Animal
{
public:
    virtual void speck()//�麯��
    {
        cout << "������˵��" << endl;
    }
};
class Cat : public Animal
{
public:
    void speck()//��д
    {
        cout << "Сè��˵��" << endl;
    }
};
//�����и��ӹ�ϵ�������࣬C++���Բ���Ҫͨ������ǿת
void DoSpeck(Animal& animal)
{
    animal.speck();
}
int main()
{
    Cat cat;
    DoSpeck(cat);//Сè��˵��
}
```

### 2.��̬ԭ��

1. �������д����麯�����ڲ������ṹ�仯�������麯����ָ��`vfptr`��ָ���麯����`vftable`
2. �麯�����ڲ���¼���麯����ַ
3. �����෢����д�󣬻��޸������е��麯�����еĺ�����ַ��������Ӱ�츸���е��麯����

![��̬ԭ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/��̬ԭ��-�麯��.png)

4. ��̬����ȷ���

```C++
class Animal
{
public:
    virtual void speak()
    {
        cout << "Animal Speak" << endl;
    }
    virtual void eat(int i)
    {
        cout << "Animal Eat" << i << endl;
    }
};
class Cat : public Animal
{
public:
    void speak()
    {
        cout << "Cat Speak" << endl;
    }
    virtual void eat(int i)
    {
        cout << "Cat Eat" << i << endl;
    }
};

void test()
{
    Animal * animal = new Cat;
    //cat->speak();
    //((void(*)())  (*(int*)*(int*)animal))();Cat Speak--32λ���Բ�����
    //((void(*)()) (*((int*)*(int*)animal + 1)))();//Cat Eat--�޲�
    typedef void(__stdcall* FUNC)(int);
    (FUNC(*((int*)*(int*)animal + 1)))(10);//Cat Eat10--�в�
}
```

### 3.������ʹ��麯��

* ���麯���﷨��`virtual void func() = 0;`
* ���һ��������**���麯��**����ô������޷�ʵ�����������������Ϊ**������**
* �������̳��˳����࣬��ô���������д�����еĴ��麯������������Ҳ���ڳ�����

```C++
//##���ö�̬ʵ�ּ�����
class AbstractCalculator//������
{
public:
    virtual int getResult() = 0;//���麯��
    // virtual int getResult()//�麯��
    // {
    //     return 0;
    // }
    int m_A;
    int m_B;
};
//�ӷ�������
class AddCalculator : public AbstractCalculator
{
public:
    int getResult()
    {
        return m_A + m_B;
    }
};
void test()
{
    AbstractCalculator* calculator = new AddCalculator;
    calculator->m_A = 10;
    calculator->m_B = 20;
    cout << calculator->getResult() << endl;
}
```

### 4.�������ʹ�������

* ��������������⣺�������ж���������ʱ���ͷ�ʱ���ɾ����ڴ�й¶
* ������������������Ҳ������ʵ�֣�������ʵ��
* ���һ�������д�����������ô��������ڳ�����

```C++
class Animal
{
public:
    Animal()
    {
        cout << "Animal()" << endl;
    }
    //virtual ~Animal()
    //{//������
    //  cout << "~Animal()" << endl;
    //}
    virtual ~Animal() = 0;//��������
    virtual void speak()
    {
        cout << "Animal speak()" << endl;
    }
};
Animal::~Animal()
{
    cout << "~Animal()" << endl;
}
class Cat : public Animal
{
public:
    Cat(const char* name)
    {
        this->m_Name = new char[strlen(name) + 1];
        strcpy(this->m_Name, name);

        cout << "Cat()" << endl;
    }
    ~Cat()
    {
        if (this->m_Name != NULL)
        {
            cout << "~Cat()" << endl;
            delete[] this->m_Name;
            this->m_Name = NULL;
        }
    }
    void speak()
    {
        cout << "Cat Speak()" << endl;
    }
    char* m_Name;
};
void test()
{
    Animal* animal = new Cat("DD");
    animal->speak();
    delete[] animal;
}
```

### 5.������������ת��

1. ����ת���� ��������ת�� ����ȫ
2. ����ת���� ��������ת�� ��ȫ
3. ���������̬����ô���ǰ�ȫ��

![������������ת��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/������������ת��.png)

### 6.��̬����--������װ

![��̬����--������װ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/������װ��������.png)

```C++
//�����
//�����CPU
class Cpu
{
public:
    virtual void calculate() = 0;
};
//������Կ�
class VideoCard
{
public:
    virtual void memory() = 0;
};
//������
class computer
{
public:
    computer(Cpu* cpu, VideoCard* vc)
    {
        this->cpu = cpu;
        this->vc = vc;
    }
    void dowork()
    {
        this->cpu->calculate();
        this->vc->memory();
    }
    ~computer()
    {
        if (this->cpu != NULL)
        {
            delete[] cpu;
            this->cpu = NULL;
        }
        if (this->vc != NULL)
        {
            delete[] vc;
            this->vc = NULL;
        }
    }
    Cpu* cpu;
    VideoCard* vc;
};
//ʵ�ֲ�
//inter��CPU
class interCpu : public Cpu
{
    void calculate()
    {
        cout << "interCpu Calculate()" << endl;
    }
};
//inter���Կ�
class interVideoCard : public VideoCard
{
    void memory()
    {
        cout << "interVideoCard Memory()" << endl;
    }
};
//�����CPU
class leCpu : public Cpu
{
    void calculate()
    {
        cout << "leCpu Calculate()" << endl;
    }
};
//������Կ�
class leVideoCard : public VideoCard
{
    void memory()
    {
        cout << "leVideoCard Memory()" << endl;
    }
* };~~~~
void test()
{
    //��װ�ĵ�һ̨����
    Cpu* cpu = new interCpu;
    VideoCard* vc = new interVideoCard;
    computer* interCo = new computer(cpu, vc);
    interCo->dowork();
    //��װ�ĵڶ�̨����
    cout << "------------" << endl;
    Cpu* cpu2 = new leCpu;
    VideoCard* vc2 = new leVideoCard;
    computer* interCo2 = new computer(cpu2, vc2);
    interCo2->dowork();
}
```
