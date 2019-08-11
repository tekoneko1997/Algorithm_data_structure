#include <stdio.h>
#include <string.h>
#define MAX 10 /*---int型スタックを実現する構造体---*/

/*---身体データ型---*/
typedef struct
{
    int height;    /* 身長*/
    double vision; /* 視力*/
} Body;
/*---身体検査データ型---*/
typedef struct
{
    Body body;     /* 身体データ型---*/
    char name[20]; /* 氏名*/
} PhysCheck;
typedef struct
{
    int max;
    int ptr;
    PhysCheck stk[MAX];
} PhysCheckStack; /*---スタックの初期化---*/

int Initialize(PhysCheckStack *s, int max)
{
    s->ptr = 0;
    s->max = max;
    return 0;
} /*---スタックにデータをプッシュ---*/
int Push(PhysCheckStack *s, PhysCheck x)
{
    if (s->ptr >= s->max)
        return -1; /* スタック満杯*/
    s->stk[s->ptr] = x;
    s->ptr++;
    return 0;
} /*---スタックからデータをポップ---*/
int Pop(PhysCheckStack *s, PhysCheck *x)
{
    if (s->ptr <= 0)
        return -1; /* スタックは空*/
    s->ptr--;
    *x = s->stk[s->ptr];
    return (0);
} /*---スタックからデータをピーク---*/
int Peek(PhysCheckStack *s, PhysCheck *x)
{
    if (s->ptr <= 0)
        return -1;
    *x = s->stk[s->ptr - 1];
    return 0;
} /*---スタックの容量---*/
int Capacity(const PhysCheckStack *s) { return s->max; } /*---スタックに積まれているデータ数---*/
int Size(const PhysCheckStack *s) { return s->ptr; }     /*---スタックの全データの表示---*/
void PrintStatus(const PhysCheck *x){
    printf("%s %d %0.2lf", x->name, x->body.height, x->body.vision);
}
void Print(const PhysCheckStack *s)
{
    int i;
    for (i = 0; i < s->ptr; i++)
        PrintStatus(&s->stk[i]);
    putchar('\n');
}

int Search(PhysCheckStack *s, PhysCheck *x)
{
    int i, counter = 0;

    for (i = 0; i < s->ptr; i++)
    {
        if (strstr(s->stk[i].name, x->name) != NULL)
        {
            PrintStatus(&s->stk[i]);
            putchar('\n');
            counter++;
        }
    }

    return counter;
}

int main(void) {
    PhysCheckStack s;

    Initialize(&s, MAX);

    while (1) {
        int menu, search;
        PhysCheck x;
        printf("現在のデータ数:%d/%d\n", Size(&s), Capacity(&s));
        printf("(1)プッシュ (2)ポップ (3)ピーク (4)表示 (5)探索 (0)終了:");
        scanf("%d", &menu);
        // ----------------①

        if (menu == 0) break;

        switch (menu) {
            case 1:
                printf("名前：");
                scanf("%s", x.name);
                printf("身長：");
                scanf("%d", &x.body.height);
                printf("視力：");
                scanf("%lf", &x.body.vision);
                if (Push(&s, x) == -1)
                    puts("\aエラー；プッシュに失敗しました。");
                break;
            case 2:
                if (Pop(&s, &x) == -1)
                    puts("\aエラー：ポップに失敗しました。");
                else {
                    printf("ポップしたデータは ");
                    PrintStatus(&x);
                    printf(" です。\n");
                }
                break;
            case 3:
                if (Peek(&s, &x) == -1)
                    puts("\aエラー：ピークに失敗しました。");
                else {
                    printf("ピークしたデータは ");
                    PrintStatus(&x);
                    printf(" です。\n");
                }
                break;
            case 4:
                Print(&s);
                break;
            case 5:
                printf("パターン：");
                scanf("%s", x.name);
                if ((search = Search(&s, &x)) == 0)
                    puts("パターンは存在しません.");
                else
                    printf("パターンは %d 個見つかりました.\n", search);
                break;
        }
    }
    return 0;
}