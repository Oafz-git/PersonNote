#ifndef __MY_STRING_H__
#define __MY_STRING_H__

#include <string.h>
#include <iostream>

using namespace std;

class String
{
public:
    String(const char* cstr = 0);
    // String(const String& str);
    // String& operator=(const String& str);
    ~String();
    char* get_c_str() const{return m_data;}

private:
    char* m_data;
};

inline 
String::String(const char* cstr = 0)
{
    if(cstr)
    {
        m_data = new char[strlen(cstr) + 1];
        strcpy(m_data,cstr);
    }
    else
    {//未指定初值
        cout << "String::String(const char* cstr = 0)" << endl;
        m_data = new char[1];
        *m_data = '\0';
    }
}

inline
String::~String()
{
    delete[] m_data;
}

#endif // !__MY_STRING_H__