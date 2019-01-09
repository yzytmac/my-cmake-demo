#include <stdio.h>
#include <stdlib.h>

double add(double a,double b)
{
    return a+b;
}

int main(int argc, char const *argv[])
{
    if(argc<3){
        printf("参数个数小于2");
        return 1;
    }
    double res = add(atof(argv[1]),atof(argv[2]));
    printf("结果是%f",res);
    return 0;
}
