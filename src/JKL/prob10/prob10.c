/*  再帰に対する理解を深めるための真に再帰的な関数2 */
#include <stdio.h>
#include <string.h>
#define String_Max 78 /*---真に再帰的な関数recur2 ---*/

void recur2(char *st){
    int n = strlen(st);
    if (n > 0)
    {
        recur2(st + 1);
        if (n > 1)
            recur2(st + 2);
        else
            recur2(st + 1);
        printf("%c", *st);
    }
}

int main(void)
{
    char x[String_Max];
    printf("文字列をを入力せよ：");
    scanf("%s", x);
    recur2(x);
    printf("\n");
    return (0);
}