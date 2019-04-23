#include <stdio.h>
#define VMAX 21 /* 視力の最大値 2.1 × 10 */
#define HMAX 25 // 最大身長 208cm

/*--- 身体検査データ型 ---*/
typedef struct
{
    char name[20]; /* 氏名 */
    int height;    /* 身長 */
    double vision; /* 視力 */
} PhysCheck;
/*--- 身長の平均値を求める ---*/
double ave_height(PhysCheck *dat)
{
    int n = 0;
    double sum = 0.0;
    while (dat->height > 0)
    {
        sum += (dat++)->height;
        n++;
    }
    return (sum / n);
}
/*--- 視力の分布を求める ---*/
void dist_vision(PhysCheck *dat, int dist[])
{
    int vision;
    while ((vision = (int)(10 * ((dat++)->vision) + 0.5)) > 0)
    {
        if (vision < VMAX)
            ++*(dist + vision);
    }
}
/*--- 身長の分布を求める ---*/
void dist_height(PhysCheck *dat, int hdist[])
{
    int height;
    while ((height = (dat++)->height - 100) > 0)
    {
        if(height/8 < HMAX)
        ++*(hdist + height/8);
    }
}
int main(void)
{
    PhysCheck *y, x[] = {
                      {"AKASAKA Tadao", 162, 0.3},
                      {"KATOH Tomiaki", 173, 0.7},
                      {"SAITOH Syouji", 175, 2.0},
                      {"TAKEDA Shinya", 171, 1.5},
                      {"NAGAHAMA Masaki", 168, 0.4},
                      {"HAMADA Tetsuaki", 174, 1.2},
                      {"MATSUTOMI Akio", 169, 0.8},
                      {"", 0, 0.0} /*フラグ*/
                  };
    int *z, vdist[VMAX] = {}, hdist[HMAX] = {};
    puts("■□■ 身体検査一覧表 ■□■");
    puts(" 氏名 身長 視力 ");
    puts("----------------------------");
    for (y = x; y->height > 0; y++)
        printf("%-18.18s%4d%5.1f\n", y->name, y->height, y->vision);
    printf("\n 平均身長：%5.1fcm\n", ave_height(x));
    dist_vision(x, vdist); /* 視力の分布を求める */
    printf("\n 視力の分布\n");
    for (z = vdist; z < vdist + VMAX; z++)
    {
        if (*z > 0)
        {
            printf("%3.1f～：%2d 人\n", (z - vdist) / 10.0, *z);
        }
    }
    dist_height(x, hdist);
    printf("\n身長の分布\n");
    for (z = hdist; z < hdist + VMAX; z++){
        if (*z > 0){
            printf("%3d〜：%2d人\n", (int)(z - hdist)*8+100, *z);
        }
    }
    return (0);
}