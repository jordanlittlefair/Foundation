#include <iostream>
using namespace std;
#include <windows.h>
#include "Include/glew.hpp"

int main()
{
    cout << wglCreateContext(0) << endl;
    glClear(~0);
    return 0;
}
