#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct
{
    int max;
    int num;
    int front;
    int rear;
    char **que;
} StringsQueue;

int Initialize(StringsQueue *q, int max)
{
    q->num = q->front = q->rear = 0;
    if ((q->que = calloc(max, sizeof(char *))) == NULL)
    {
        q->max = 0; /* 配列の確保に失敗*/
        return -1;
    }
    q->max = max;
    return 0;
} /*---キューの後始末---*/
void Terminate(StringsQueue *q)
{
    if (q->que != NULL)
    {
        free(q->que); /* 配列を解放*/
        q->max = q->num = q->front = q->rear = 0;
    }
} /*---キューにデータをエンキュー---*/
int Enque(StringsQueue *q, char *x)
{
    int max;
    char **tmp;
    if (q->num >= q->max)
    {
        tmp = calloc(max = q->max + 7, sizeof(char *));

        for (int i = 0; i < q->max; i++)
        {
            tmp[i] = q->que[i];
        }
        free(q->que);
        q->que = tmp;
        q->max += 7;
    }
    q->num++;
    q->que[q->rear] = calloc(81, sizeof(char));

    for (int i = 0; i < strlen(x); i++)
    {
        q->que[q->rear][i] = x[i];
    }

    q->rear++;
    return 0;
}
/*---キューからデータをデキュー---*/
int Deque(StringsQueue *q, char *x)
{
    int i, max;
    char **tmp;
    if (q->num <= 0)
    {
        return -1;
    }
    else
    {
        q->num--;

        for (i = 0; i < strlen(q->que[q->front]); i++)
        {
            x[i] = q->que[q->front][i];
        }

        q->que[q->front][i + 1] = '\0';
        free(q->que[q->front]);
        q->front++;

        if (q->front == q->max)
            q->front = 0;
    }

    if (q->max - q->num >= 15)
    {
        tmp = calloc(max = q->max - 6, sizeof(char *));

        for (i = 0; i < q->num; i++)
        {
            tmp[i] = q->que[(i + q->front) % q->max];
        }
        free(q->que);
        q->que = tmp;
        q->max -= 6;
        q->front = 0;
        q->rear = q->num;
    }
    return 0;
}
/*---キューからデータをピーク---*/
int Peek(const StringsQueue *q, char *x)
{
    if (q->num <= 0)
    {
        return -1;
    }
    x = q->que[q->front];
    return 0;
} /*---キューの容量---*/
int Capacity(const StringsQueue *q) { return (q->max); } /*---キューに蓄えられているデータ数---*/
int Size(const StringsQueue *q) { return (q->num); }     /*---全データの表示---*/
void Print(const StringsQueue *q)
{
    int i;
    for (i = 0; i < q->num; i++)
        printf("%s ", q->que[(i + q->front) % q->max]);
    putchar('\n');
}
char *bm_match(char *pat, char *txt) {
    char *pt;
    char *pp;
    int txt_len = strlen(txt);
    int pat_len = strlen(pat);
    int skip[UCHAR_MAX + 1];
    int i;

    for (i = 0; i <= UCHAR_MAX; i++)
        skip[i] = pat_len;
    for (pp = pat; *pp != '\0'; pp++)
        skip[*pp] = strlen(pp) - 1;
    skip[*(pp - 1)] = pat_len;

    pt = txt + pat_len - 1;
    while (pt < txt + txt_len) {
        pp = pat + pat_len - 1;
        while (*pt == *pp) {
            if (pp == pat) return pt;
            pp--;
            pt--;
        }
        pt += (skip[*pt] > strlen(pp)) ? skip[*pt] : strlen(pp);
    }
    return NULL;
}
int Count(StringsQueue *q, char *x)
{
    int counter = 0;
    int i;
    char *pt;

    for (i = 0; i < q->num; i++)
    {
        pt = q->que[((i + q->front) % q->max)];
        while ((pt = bm_match(x, pt)) != NULL)
        {
            counter++;
            pt++;
        }
    }

    return counter;
}

int main(void)
{
    StringsQueue que;
    if (Initialize(&que, 5) == -1)
    {
        puts("キューの生成に失敗しました。");
        return 1;
    }
    int i = 0;
    while (1)
    {
        int m,count = 0;
        char *x = calloc(81, sizeof(char));

        printf("現在のデータ数：%d/%d\n", Size(&que), Capacity(&que));
        printf("(1)エンキュー (2)デキュー (3)ピーク (4)表示 (5)パターンの計数 (0)終了：");
        scanf("%d", &m);

        if (m == 0)
            break;
        switch (m)
        {
        case 1:
            printf("データ：");
            scanf("%s", x);
            if (Enque(&que, x) == -1)
                puts("\aエラー:データのエンキューに失敗しました。");
            break;
        case 2:
            if (Deque(&que, x) == -1)
                puts("\aエラー:デキューに失敗しました。");
            else
                printf("デキューしたデータは%sです。\n", x);
            break;
        case 3: /* ピーク*/
            if (Peek(&que, x) == -1)
                puts("\aエラー：ピークに失敗しました。");
            else
                printf("ピークしたデータは%sです。\n", x);
            break;
        case 4: /* 表示*/
            Print(&que);
            break;
        case 5:
            printf("パターン：");
            scanf("%s", x);
            count = Count(&que, x);
            if (count != 0)
                printf("パターンは%d個見つかりました。\n", count);
            else
                puts("パターンは存在しません.");
        default:
            break;
        }
        i++;
    }
    Terminate(&que);
    return 0;
}