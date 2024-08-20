#include "MyString.h"

int main(int argc, const char** argv) {
    String s1("hello");
    String s2(s1);
    s1 = s1;


    return 0;
}