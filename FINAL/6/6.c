#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node{
    int num;
    struct node *next;
}NODE;

NODE* addqueue(NODE* queue, int number);

int main(void)
{
    int n=0,start=0,end=0,i=0,k=0,diff=0;
    int adj[100][100]={0},distance[100]={-1};
    NODE *queue=NULL,*tmp=NULL;

    memset(distance,-1,100);

    scanf("%d%d%d",&n,&start,&end);
    start--;end--;
    queue=addqueue(queue,start);

    for(i=0;i<n;i++)
    {
        scanf("%d",&diff);
        if((i+diff)<n)  adj[i][i+diff]=1;
        if((i-diff)>=0) adj[i][i-diff]=1;
    }

    distance[start]=0;

    while(queue!=NULL)
    {
        tmp=queue;
        queue=queue->next;

        for(i=0;i<n;i++)
        {
            if((adj[tmp->num][i]==1)&&(distance[i]==-1))
            {
                distance[i]=distance[tmp->num]+1;
                queue=addqueue(queue,i);
            }
        }
        free(tmp);
    }

    printf("%d\n",distance[end]);
    return 0;
}

NODE* addqueue(NODE* queue, int number)
{
    NODE *current=NULL,*ptr=queue,*lastp=NULL;
    current=(NODE*)malloc(sizeof(NODE));
    current->num=number;
    current->next=NULL;

    if(queue==NULL) return current;

    while(ptr!=NULL)
    {
        lastp=ptr;
        ptr=ptr->next;
    }
    lastp->next=current;
    return queue;
}
