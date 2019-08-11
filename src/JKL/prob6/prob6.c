#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define String_Max 80

typedef struct {
    int max;
    int ptr;
    char **stk;
} StringsStack;

int Initialize(StringsStack *s, int max) {
    s->ptr = 0;
    if ((s->stk = calloc(max, sizeof(char *))) == NULL) {
        s->max = 0;
        return -1;
    }
    s->max = max;
    return 0;
}

void Terminate(StringsStack *s) {
    if (s->stk != NULL) {
        while (--s->ptr >= 0)
            free(s->stk[s->ptr]);
        free(s->stk[s->ptr]);
    }
    s->max = s->ptr = 0;
}

int Push(StringsStack *s, char *x) {
    if (s->ptr >= s->max) {
        return -1;
    }
    if ((s->stk[s->ptr] = calloc(strlen(x) + 1, sizeof(char))) == NULL){
        return -1;
    }
    strcpy(s->stk[s->ptr], x);
    s->ptr++;
    return 0;
}

int Pop(StringsStack *s, char *x) {
    if (s->ptr <= 0) return -1;
    s->ptr--;
    strcpy(x, s->stk[s->ptr]);
    free(s->stk[s->ptr]);
    return 0;
}

int Peek(StringsStack *s, char *x) {
    if (s->ptr <= 0) return -1;
    strcpy(x, s->stk[s->ptr - 1]);
    return 0;
}

int Capacity(const StringsStack *s) {
    return s->max;
}

int Size(const StringsStack *s) {
    return s->ptr;
}

void Print(const StringsStack *s) {
    int i;

    for (i = 0; i < s->ptr; i++)
        printf("%s\n", s->stk[i]);
}

int Search(StringsStack *s, char *x) {
    for (int i = s->ptr - 1; i >= 0; i--) {
        if (strstr(s->stk[i], x) != NULL){
            return i;
        }
    }
    return -1;
}

int main(void) {
    StringsStack s;
    int max;

    printf("スタックの大きさを入力してください");
    scanf("%d", &max);

    if (Initialize(&s, max) == -1) {
        puts("スタックの生成に失敗しました.\n");
        return 1;
    }

    while (1) {
        int menu, search;
        char x[String_Max];

        printf("現在のデータ数：%d/%d\n", Size(&s), Capacity(&s));
        printf("(1)プッシュ (2)ポップ (3)ピーク (4)表示 (5)探索 (0)終了：");
        scanf("%d", &menu);
        // ----------------①

        if (menu == 0) break;

        switch (menu) {
            case 1:
                printf("プッシュする文字列：");
                scanf("%s", x);
                if (Push(&s, x) == -1)
                    puts("\aエラー：プッシュに失敗しました.\n");
                break;
            case 2:
                if (Pop(&s, x) == -1)
                    puts("\aエラー：ポップに失敗しました.\n");
                else
                    printf("ポップした文字列は%s, ", x);
                break;
            case 3:
                if (Peek(&s, x) == -1)
                    puts("\aエラー：ピークに失敗しました.\n");
                else
                    printf("ピーク下文字列は%s, ", x);
                break;
            case 4:
                Print(&s);
                break;
            case 5:
                printf("パターン：");
                scanf("%s", x);
                if ((search = Search(&s, x)) == 0){
                    puts("パターンは存在しません.");
                }else{
                    printf("パターンは %d 目で見つかりました.\n", search+1);
                }
                break;
        }
    }
        Terminate(&s);
        return 0;
}

/*

    (1)
    0よりも小さい値が渡されたのでcalloc関数でメモリを確保できなかったの原因

    (2)
        (ア)
        s.ptr が0以下になっているので-1が返されてしまい"エラー: ポップに失敗しました"と表示される
        (イ)
        プッシュ関数でプッシュを呼ぶが s.max = 0 で s.ptr = 0 なので、s.ptr が
         s.max 以上という判定になり -1 が返され、「エラー: プッシュに失敗しました」と表示される

    (3)
    (ア)
        5回
    (イ)
        5回

    (4)



*/

