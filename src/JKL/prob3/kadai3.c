#include <stdio.h>
#define VMAX 21 /* 視力の最大値 2.1 × 10 */
/*--- 身体データ型 ---*/
typedef struct
{
    int height;    /* 身長 */
    double vision; /* 視力 */
} Body;
/*--- 身体検査データ型 ---*/
typedef struct
{
    Body body;     /* 身体データ型 ---*/
    char name[20]; /* 氏名 */
} PhysCheck;

/*--- 身長の平均値を求める ---*/
double ave_height(PhysCheck *dat)
{
    int n = 0;
    double sum = 0.0;
    while (dat->body.height > 0)
    {
        sum += (dat++)->body.height;
        n++;
    }
    return (sum / n);
}
/*--- 視力の分布を求める ---*/
void dist_vision(PhysCheck *dat, int dist[])
{
    int vision;
    while ((vision = (int)(10 * ((dat++)->body.vision) + 0.5)) > 0)
    {
        if (vision < VMAX)
        {
            ++*(dist + vision);
        }
    }
}
int main(void)
{
    PhysCheck *y, x[] = {
                      {{ 162, 0.3},"AKASAKA Tadao"},
                      {{173, 0.7},"KATOH Tomiaki"},
                      {{175, 2.0},"SAITOH Syouji" },
                      {{ 171, 1.5},"TAKEDA Shinya"},
                      {{168, 0.4},"NAGAHAMA Masaki" },
                      {{ 174, 1.2},"HAMADA Tetsuaki"},
                      {{169, 0.8},"MATSUTOMI Akio" },
                      {{0, 0.0},""} /*フラグ*/
                  };
    int *z, vdist[VMAX] = {}; /* 視力の分布 */
    puts("■□■ 身体検査一覧表 ■□■");
    puts(" 氏名 身長 視力 ");
    puts("----------------------------");
    for (y = x; y->body.height > 0; y++)
        printf("%-18.18s%4d%5.1f\n", y->name, y->body.height, y->body.vision);
    printf("\n 平均身長：%5.1fcm\n", ave_height(x));
    dist_vision(x, vdist); /* 視力の分布を求める */
    printf("\n 視力の分布\n");
    for (z = vdist; z < vdist + VMAX; z++)
        if (*z > 0)
            printf("%3.1f～：%2d 人\n", (z - vdist) / 10.0, *z);
    return (0);
}