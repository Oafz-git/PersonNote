#include "Complex.h"

int main(int argc, const char** argv) {

    const complex c1(2,1);
    c1.imag();
    //c1.real();常对象只能调用常函数

    return 0;
}