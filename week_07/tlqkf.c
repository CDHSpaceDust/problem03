#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
    char str[100];
    int num;
    char cr;
    float f;
    
    printf("Enter a number: ");
    fgets(str, sizeof(str), stdin); // 문자열로 입력 받음
    num = atoi(str); // 문자열을 정수로 변환
    printf("The number is %d\n", num);
    num += 1;
    printf("number + 1 : %d\n", num);
    return 0;

}



/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

StrToInt(str) 
{
    //void 포인터를 활용해봅시다 (우와!)
}

int main() {
    char option[100];
    char str[100];

    printf("input type : ");
    printf("int");
    printf("char");
    printf("float");
    printf("string");
    fgets(str, sizeof(str), stdin);

    if (option == "int") 
    {

    }
}*/
