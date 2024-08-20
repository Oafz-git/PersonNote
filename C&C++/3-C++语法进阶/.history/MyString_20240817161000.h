#ifndef __MY_STRING_H__
#define __MY_STRING_H__

#include<string>

using namespace std;

class String
{
public:
    String(const char* cstr = 0);
    String(const String& str);
    String& operator=(const String& str);
    ~String();
    char* get_c_str() const{return m_data;}

private:
    char* m_data;
};

inline String::String(const char* cstr = 0)
{
    if(cstr)
    {
        m_data = new char[strlen(cstr)];
    }
}

#endif // !__MY_STRING_H__