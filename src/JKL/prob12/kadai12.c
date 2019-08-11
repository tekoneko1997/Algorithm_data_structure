#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define swap(type, x, y) \
    do                   \
    {                    \
        type t;          \
        t = x;           \
        x = y;           \
        y = t;           \
    } while (0)
#define ASCENDING 0  /* 昇順 */
#define DESCENDING 1 /* 降順 */
/*--- 会員データ ---*/
typedef struct
{
    int no;        /* 番号 */
    char name[20]; /* 氏名 */
} Member;
/*--- 会員の番号の昇順比較関数 ---*/
int AscendingMemberNoCmp(const Member *x, const Member *y)
{
    return x->no < y->no ? -1 : x->no > y->no ? 1 : 0;
}
/*--- 会員の番号の降順比較関数 ---*/
int DescendingMemberNoCmp(const Member *x, const Member *y)
{
    return x->no < y->no ? 1 : x->no > y->no ? -1 : 0;
}
/*--- 会員の氏名の昇順比較関数 ---*/
int AscendingMemberNameCmp(const Member *x, const Member *y)
{
    return strcmp(x->name, y->name);
}
/*--- 会員の氏名の降順比較関数 ---*/
int DescendingMemberNameCmp(const Member *x, const Member *y)
{
    return strcmp(y->name, x->name);
}
/*--- 会員データ（番号と氏名）の表示（改行あり）---*/
void PrintLnMember(const Member *x)
{
    printf("%d %s\n", x->no, x->name);
}

/*--- 全データの表示 ---*/
void Print(const Member *data, int n)
{
    int i;
    for (i = 0; i < n; i++)
        PrintLnMember(data + i);
}
Member *middle3(Member *a, Member *b, Member *c, int compare(const Member *y, const Member *z))
{
    if (compare(a, b) >= 0)
        if (compare(b, c) >= 0)
            return b;
        else if (compare(a, c) <= 0)
            return a;
        else
            return c;
    else if (compare(a, c) > 0)
        return a;
    else if (compare(b, c) > 0)
        return c;
    else
        return b;
}
/* --- シェルソート --- */
void shell(Member *a, int n, int compare(const Member *x, const Member *y), int order)
{
    int i, j, h;

    for (h = 1; h < n / 9; h = h * 3 + 1)
        ;

    for (; h > 0; h /= 3)
    {
        for (i = h; i < n; i++)
        {
            Member tmp = a[i];
            if (order == 0)
                for (j = i - h; j >= 0 && compare(a + j, &tmp) > 0; j -= h)
                    a[j + h] = a[j];
            else
                for (j = i - h; j >= 0 && compare(a + j, &tmp) < 0; j -= h)
                    a[j + h] = a[j];
            a[j + h] = tmp;
        }
    }
}
/* --- クイックソート --- */
void quick(Member *a, int left, int right, int compare(const Member *y, const Member *z)) {
    int pl = left;
    int pr = right;
    int size = right - left + 1;
    Member x = a[(pl + pr) / 2];

    if (size >= 5) {
       x = *middle3(a + pl, &x, a + pr, compare);
    } else {
        shell(a, right + 1, compare, ASCENDING);
    }

    do {
        while (compare(&x, a + pl) > 0) pl++;
        while (compare(a + pr, &x) > 0) pr--;
        if (pl <= pr) {
            swap(Member, a[pl], a[pr]);
            pl++;
            pr--;
        }
    } while (pl <= pr);
    // ----------------------------------------1
    if (left < pr) quick(a, left, pr, compare);
    if (pl < right) quick(a, pl, right, compare);
}
/*--- メニュー ---*/
typedef enum
{
    TERMINATE,
    ASCEND_NO,
    ASCEND_NAME,
    DESCEND_NO,
    DESCEND_NAME,
    PRINT_ALL
} Menu;
/*--- メニュー選択 ---*/
Menu SelectMenu(void)
{
    int i, ch;
    char *mstring[] = {
        "番号で昇順ソート", "名前で昇順ソート",
        "番号で降順ソート", "名前で降順ソート",
        "データを表示"};
    do
    {
        for (i = TERMINATE; i < PRINT_ALL; i++)
        {
            printf("(%2d) %-18.18s ", i + 1, mstring[i]);
            if ((i % 3) == 2)
                putchar('\n');
        }
        printf("( 0) 終了 ：");
        scanf("%d", &ch);
    } while (ch < TERMINATE || ch > PRINT_ALL);
    return (Menu)ch;
}
/*--- メイン ---*/
int main(void)
{
    Menu menu;
    Member data[] = {
        {5, "watanabe"}, {7, "satoshi"}, {6, "noyuri"}, {0, "daisuke"}, {0, "motoko"}, {4, "agemi"}, {9, "ito"}, {2, "ohta"}, {1, "takashi"}, {3, "kouji"}};
    int ndata = sizeof(data) / sizeof(data[0]);
    do
    {
        switch (menu = SelectMenu())
        {
        case ASCEND_NO: /* 番号で昇順にソート */
            quick(data, 0, ndata - 1, AscendingMemberNoCmp);
            break;
        case ASCEND_NAME: /* 名前で昇順にソート */
            quick(data, 0, ndata - 1, AscendingMemberNameCmp);
            break;
        case DESCEND_NO: /* 番号で降順にソート */
            quick(data, 0, ndata - 1, DescendingMemberNoCmp);
            break;
        case DESCEND_NAME: /* 名前で降順にソート */
            quick(data, 0, ndata - 1, DescendingMemberNameCmp);
            break;
        case PRINT_ALL: /* 全データを表示 */
            Print(data, ndata);
            break;
        }
    } while (menu != TERMINATE);
    return 0;
}