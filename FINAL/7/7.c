#include<stdio.h>
#include<string.h>
#define MAX 150

int top=0;

void push(int *stack,int num)
{
    stack[top++]=num;
}

int pop(int *stack)
{
    return stack[--top];
}

int main(void)
{
    int n=0,i=0,j=0,start=0,end=0,now=0,min=0,end_node=1;
    int adj[MAX][MAX]={0},visit[MAX]={0},lev[MAX],stack[MAX]={0},path[MAX]={0},path_n=0,last=0;

    memset(lev,-1,MAX);

    scanf("%d", &n);
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&adj[i][j]);
        }
    }

    scanf("%d%d",&start,&end);
    start--;end--;

    //設定初始值
    push(stack, start);
    lev[start]=0;//第一個node的距離為零
    last=start;//last紀錄能夠到達end的最短main path node

    while(top>0)
    {
        now=pop(stack);
        path[path_n++]=now;
        visit[now]=end_node=1;

        for(i=0;i<n;i++)
        {
            if(adj[now][i]!=0)
            {
                end_node=0;
                min=i;//取第一個不為零的值設為min的初始值
                break;
            }
        }

        if(end_node==1) break;

        for(i=0;i<n;i++)
        {
            if(adj[now][i]==0)    continue;//adj[now][i]==0時略過

            if(!visit[i]&&adj[now][min]>adj[now][i])    min=i;

            if(lev[i]==-1||(lev[now]+adj[now][i])<lev[i])
            {
                lev[i]=lev[now]+adj[now][i];
                if(i==end)  last=now;
            }
        }
        push(stack,min);
    }

    for(i=0;i<path_n;i++)
    {
        if(path[i]==last)

        {
            printf("%d %d\n",path[i]+1,end+1);
            break;
        }
        else
            printf("%d ",path[i]+1);
    }
    return 0;
}
