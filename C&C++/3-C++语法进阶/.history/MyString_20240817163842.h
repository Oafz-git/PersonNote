#ifndef __MY_STRING_H__
#define __MY_STRING_H__

#include <string.h>
#include <iostream>

using namespace std;

class String
{
public:
    String(const char* cstr = 0);
    String(const String& str);//copy ctor
    String& operator=(const String& str);//copy op=
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
    {//未指定初值
        cout << "String::String(const char* cstr = 0)2" << endl;
        m_data = new char[1];
        *m_data = '\0';
    }
}

inline
String::String(const String& str)
{
    m_data = new char[strlen(str.m_data)];
    strcpy(this->m_data,str.m_data);
}

inline
String& String::operator=(const String& str)
{
    m_data = new char[strlen(str.m_data)];
    strcpy(this->m_data,str.m_data);
    return *this;
}

inline
String::~String()
{
    delete[] m_data;
}

#endif // !__MY_STRING_H__