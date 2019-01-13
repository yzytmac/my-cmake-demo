#include <stdio.h>
#include <stdlib.h>
#include "config.h"

#ifdef USE_MYMATH
    #include "math/MathFunction.h"
#endif

int main(int argc, char const *argv[])
{
    if(argc<3){
        printf("参数个数小于2");
        return 1;
    }
    double res = add(atof(argv[1]),atof(argv[2]));
    printf("%f+%f结果是%f",atof(argv[1]),atof(argv[2]),res);
    return 0;
}
