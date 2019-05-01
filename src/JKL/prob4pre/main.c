#include <stdio.h>
#include <string.h>
#include <limits.h>
/*--- Boyer-Moore 法による文字列探索 ---*/
char *bm_match(char *pat, char *txt)
{
    char *pt;                  /* txt をなぞるカーソル */
    char *pp;                  /* pat をなぞるカーソル */
    int txt_len = strlen(txt); /* txt の文字数 */
    int pat_len = strlen(pat); /* pat の文字数 */
    int skip[UCHAR_MAX + 1];   /* スキップテーブル */
    int i;
    for (i = 0; i <= UCHAR_MAX; i++) /* スキップテーブルの作成 */
        skip[i] = pat_len;
    for (pp = pat; *pp != '\0'; pp++){
        skip[*pp] = strlen(pp) - 1;
    }
    skip[*(pp - 1)] = pat_len; /* パターンの最後文字の移動距離はパターンの文字数 */
    pt = txt + pat_len - 1;    /* pat の末尾と比較する txt の文字を決定 */
    while (pt < txt + txt_len)
    {                           /* txt の比較する文字の位置が txt の末尾を越えるまで */
        pp = pat + pat_len - 1; /* pat の最後の文字に着目 */
        while (*pt == *pp)
        {
            if (pp == pat)
                return (pt); /* 一致した文字がパターンの最初の文字になれば終了 */
            pp--;
            pt--;
        }
        pt += (skip[*pt] > strlen(pp)) ? skip[*pt] : strlen(pp);
    }
    return (NULL);
}
/*---  ---*/
char *bm_reverse_macth(char *pat, char *txt){
    char *pt;                  /* txt をなぞるカーソル */
    char *pp;                  /* pat をなぞるカーソル */
    int txt_len = strlen(txt); /* txt の文字数 */
    int pat_len = strlen(pat); /* pat の文字数 */
    int skip[UCHAR_MAX + 1];   /* スキップテーブル */
    int i;
    for (i = 0; i <= UCHAR_MAX; i++) /* スキップテーブルの作成 */
        skip[i] = pat_len;
    for (pp = pat; *pp != '\0'; pp++){
        skip[*pp] = strlen(pp) - 1;
    }
    skip[*(pp - 1)] = pat_len; /* パターンの最後文字の移動距離はパターンの文字数 */
    pt = txt + pat_len - 1;    /* pat の末尾と比較する txt の文字を決定 */
    while (pt < txt + txt_len)
    {                           /* txt の比較する文字の位置が txt の末尾を越えるまで */
        pp = pat + pat_len -1; /* pat の最初の文字に着目 */
        while (*pt == *pp)
        {
            if (pp == pat)
                return (pt); /* 一致した文字がパターンの最初の文字になれば終了 */
            pp--;
            pt++;
        }
        pt += (skip[*pt] > strlen(pp)) ? skip[*pt] : strlen(pp);
    }
    return (NULL);
}
int main(void)
{
    char *s;
    char s1[80] = "qwertyui"; /* テキスト */
    char s2[80] = "tre"; /* パターン */
    printf("テキスト：");
    //scanf("%s", s1);
    printf("パターン：");
    //scanf("%s", s2);
    s = bm_reverse_macth(s2, s1); /* 文字列 s1 から文字列 s2 を Boyer-Moore 法で探索 */
    if (s == NULL)
        puts("テキスト中にパターンは存在しません。");
    else
        //printf("s = %s\n", s);
        printf("%ld 文字目に見つかりました。\n", s - s1 + 1);
    return (0);
}