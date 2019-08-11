#include <stdio.h>
#include <stdlib.h>
typedef struct
{              /*---キューを実現する構造体---*/
    int max;   /* キューの容量 */
    int num;   /* 現在の要素数 */
    int front; /* 先頭要素カーソル */
    int rear;  /* 末尾要素カーソル */
    int *que;  /* キュー本体（の先頭要素へのポインタ） */
} IntQueue;    /*---キューの初期化---*/

int Initialize(IntQueue *q, int max)
{
    q->num = q->front = q->rear = 0;
    if ((q->que = calloc(max, sizeof(int))) == NULL)
    {
        q->max = 0; /* 配列の確保に失敗*/
        return -1;
    }
    q->max = max;
    return 0;
} /*---キューの後始末---*/
void Terminate(IntQueue *q)
{
    if (q->que != NULL)
    {
        free(q->que); /* 配列を解放*/
        q->max = q->num = q->front = q->rear = 0;
    }
} /*---キューにデータをエンキュー---*/
int Enque(IntQueue *q, int x)
{
    if (q->num >= q->max)
        return -1; /* キューは満杯*/
    else
    {
        q->num++;
        q->que[q->rear++] = x;
        if (q->rear == q->max)
            q->rear = 0;
        return 0;
    }
} /*---キューからデータをデキュー---*/
int Deque(IntQueue *q, int *x)
{
    if (q->num <= 0) /* キューは空*/
        return -1;
    else
    {
        q->num--;
        *x = q->que[q->front++];
        if (q->front == q->max)
            q->front = 0;
        return 0;
    }
} /*---キューからデータをピーク---*/
int Peek(const IntQueue *q, int *x)
{
    if (q->num <= 0)
        return -1;
    *x = q->que[q->front];
    return 0;
} /*---キューの容量---*/
int Capacity(const IntQueue *q) { return (q->max); } /*---キューに蓄えられているデータ数---*/
int Size(const IntQueue *q) { return (q->num); }     /*---全データの表示---*/
void Print(const IntQueue *q)
{
    int i;
    for (i = 0; i < q->num; i++)
        printf("%d ", q->que[(i + q->front) % q->max]);
    putchar('\n');
}
int main(void)
{
    IntQueue que;
    if (Initialize(&que, 5) == -1)
    {
        puts("キューの生成に失敗しました。");
        return 1;
    }
    int i = 0;
    while (1)
    {
        int m, x;
        int lm[]={1,1,1,1,0};
        int lx[]={47, 8, 11, 24};
        m = lm[i];
        x = lx[i];
        printf("現在のデータ数：%d/%d\n", Size(&que), Capacity(&que));
        printf("(1) エンキュー(2) デキュー(3) ピーク(4) 表示(0) 終了：");
        //scanf("%d", &m);

        if (m == 0)
            break;
        switch (m)
        {
        case 1:
            printf("データ：");
            //scanf("%d", &x);
            if (Enque(&que, x) == -1)
                puts("\aエラー:データのエンキューに失敗しました。");
            break;
        case 2:
            if (Deque(&que, &x) == -1)
                puts("\aエラー:デキューに失敗しました。");
            else printf("デキューしたデータは%dです。\n", x);
            break;
        case 3: /* ピーク*/
            if (Peek(&que, &x) == -1)
                puts("\aエラー：ピークに失敗しました。");
            else printf("ピークしたデータは%dです。\n", x);
            break;
        case 4: /* 表示*/
            Print(&que);
            break;
        }
        i ++;
    }
    Terminate(&que);
    return 0;
}