#include <stdio.h>

/*--- 要素数 n の配列 a の要素の並びを逆転 ---*/
void ary_reverse(int *a, int n)
{
    int *b, t;
    int i=1;
    for (b = a + n - 1; a < b; a++, b--)
    {
        t = *a;
        *a = *b;
        *b = t;
        printf("%d",i++);
        printf("t=%d,*a=%d,*b=%d \n",t,*a,*b);
    }
}

int main(void)
{
    int i;
    int x[7];
    int nx = sizeof(x) / sizeof(x[0]);

    printf("%d 個の整数を入力してください。\n", nx);
    for (i = 0; i < nx; i++)
    {
        printf("x[%d] : ", i);
        scanf("%d", &x[i]);
    }
    ary_reverse(x, nx);

    /* 配列 x の要素の並びを逆転 */
    printf("配列の要素の並びを逆転しました。\n");

    for (i = 0; i < nx; i++)
        printf("x[%d] : %d\n", i, x[i]);
    return (0);
}