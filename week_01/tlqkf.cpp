#include <iostream>
#include <stdio.h>


#define MAX_COUNT 5

using namespace std;

int main()
{
    //변수
    const int Input[5] = { 0,0,0,0,0 };
    int i = 0;

    //입력
    printf("입력 : ");

    for (i = 0;i < MAX_COUNT;i++)
    {
        scanf_s("%d", Input + i);
    }

    //출력
    printf("입력된 값들 : ");
    for (i = 5;i > 0;i--)printf("%d, ",Input[i-1]);
    printf("\n");
    return 0;

}