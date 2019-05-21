#include <stdio.h>
#define MAX 10 /*---int型スタックを実現する構造体---*/

typedef struct
{
    int max;      /* スタックの容量*/
    int ptr;      /* スタックポインタ*/
    int stk[MAX]; /* スタック本体*/
} IntStack;       /*---スタックの初期化---*/
int Initialize(IntStack *s, int max)
{
    s->ptr = 0;
    s->max = max;
    return 0;
} /*---スタックにデータをプッシュ---*/
int Push(IntStack *s, int x)
{
    if (s->ptr >= s->max)
        return -1; /* スタック満杯*/
    s->stk[s->ptr] = x;
    s->ptr++;
    return 0;
} /*---スタックからデータをポップ---*/
int Pop(IntStack *s, int *x)
{
    if (s->ptr <= 0)
        return -1; /* スタックは空*/
    s->ptr--;
    printf("%d",s->ptr);
    *x = s->stk[s->ptr];
    return (0);
} /*---スタックからデータをピーク---*/
int Peek(IntStack *s, int *x)
{
    if (s->ptr <= 0)
        return -1;
    *x = s->stk[s->ptr - 1];
    return 0;
} /*---スタックの容量---*/
int Capacity(const IntStack *s) { return s->max; } /*---スタックに積まれているデータ数---*/
int Size(const IntStack *s) { return s->ptr; }     /*---スタックの全データの表示---*/
void Print(const IntStack *s)
{
    int i;
    for (i = 0; i < s->ptr; i++)
        printf("%d ", s->stk[i]);
    putchar('\n');
}
int main(void)
{
    IntStack s;
    Initialize(&s, MAX);
    int menu[]={2,1,1,1,1,1,1,3,0}, x[]={24,53,11,24,47,38};
    int i =0;
    while (1)
    {
        printf("現在のデータ数：%d/%d\n", Size(&s), Capacity(&s));
        printf("(1) プッシュ(2) ポップ(3) ピーク(4) 表示(0) 終了：");
        //scanf("%d", &menu);
        if (menu[i] == 0)
            break;
        switch (menu[i])
        {
        case 1: /* プッシュ*/
            printf("データ：");
            //scanf("%d", &x);
            if (Push(&s, x[i]) == -1)
                puts("\aエラー：プッシュに失敗しました。");
            break;
        case 2: /* ポップ*/
            if (Pop(&s, &x[i]) == -1)
                puts("\aエラー：ポップに失敗しました。");
            else
            printf("ポップしたデータは%dです。\n", x[i]);
            
            break;
        case 3: /* ピーク*/
            if (Peek(&s, &x[i]) == -1)
                puts("\aエラー：ピークに失敗しました。");
            else
            printf("ピークしたデータは%dです。\n", x[i]);
            
            break;
        case 4: /* 表示*/
            Print(&s);
            
            break;
        }
        i++;
    }
    return 0;
}
