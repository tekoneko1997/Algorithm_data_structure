
(1)
    (ア)
    4回
    (イ)
    １回
    (ウ)
    que.max = 5
    que.front = 0
    que.rear = 4
    que.que[1] = 47

(2)
typedef struct
{
    int max;
    int num;
    int front;
    int rear;
    char **que;
} StringsQueue;

int Enque(StringsQueue *q, char *x)
{
    if (q->num >= q->max)
        return -1;
    else
    {
        q->num++;
        q->que[q->rear] = calloc(81, sizeof(char));

        for (int i = 0; x[i] != '\0'; i++){
            q->que[q->rear][i] = x[i];
        }

        q->rear++;

        if (q->rear == q->max){
            q->rear = 0;
        }

        return 0;
    }
}
/*---キューからデータをデキュー---*/
int Deque(StringsQueue *q, char *x)
{
    int i;

    if (q->num <= 0){
        return -1;
    }
    else
    {
        q->num--;

        for (i = 0; i < strlen(q->que[q->front]); i++){
            x[i] = q->que[q->front][i];
        }

        q->que[q->front][i + 1] = '\0';
        q->front++;

        if (q->front == q->max){
            q->front = 0;
        }

        return 0;
    }
}