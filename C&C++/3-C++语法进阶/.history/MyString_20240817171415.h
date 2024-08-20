#ifndef __MY_STRING_H__
#define __MY_STRING_H__

#include <string.h>
#include <iostream>

using namespace std;

class String
{
public:
    String(const char* cstr = 0);
    String(const String& str);//copy ctor-----》String s2(s1)    String s2 = s1
    String& operator=(const String& str);//copy op= --------》 s2 = s1 
    ~String();
    char* get_c_str() const{return m_data;}

private:
    char* m_data;
};

inline 
String::String(const char* cstr)
{
    if(cstr)
    {
        cout << "String::String(const char* cstr = 0)1" << endl;
        m_data = new char[strlen(cstr) + 1];
        strcpy(m_data,cstr);
    }
    else
    {//注意1：未指定初值：默认构造函数
        cout << "String::String(const char* cstr = 0)2" << endl;
        m_data = new char[1];
        *m_data = '\0';
    }
}

inline
String::String(const String& str)
{
    cout << "拷贝构造函数" << endl;
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(this->m_data,str.m_data);
}

inline
String& String::operator=(const String& str)
{
    cout << "拷贝赋值函数" << endl;
    if(this == &str)//注意2：自我检测赋值（自己赋值自己）：如果没有这一步，下边的delete会把自身先杀掉
        return *this;
    
    delete[] m_data;//需要先把之前的指向的内存释放掉
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(this->m_data,str.m_data);
    return *this;
}

inline
String::~String()
{
    delete[] m_data;
}

#endif // !__MY_STRING_H__