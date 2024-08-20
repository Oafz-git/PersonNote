#include "MyString.h"

int main(int argc, const char** argv) {
    String s1("hello");
    //String s2(s1);
    String s2 = s1;//拷贝构造函数
    s2 = s1;//拷贝赋值函数
    cout << s1 << endl;


    return 0;
}