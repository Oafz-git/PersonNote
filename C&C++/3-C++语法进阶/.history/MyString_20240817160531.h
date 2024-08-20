#ifndef __MY_STRING_H__
#define __MY_STRING_H__

class String
{
public:
    String(const char* cstr = 0);
    String(const String& str);
    String& operator=(const String& str);
    ~String();

private:
    char* m_data;
};

#endif // !__MY_STRING_H__