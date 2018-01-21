#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(void)
{
    int num=0,i=0,j=0,top=0,adj[100][100]={0};
    int indegree[100]={0};

    scanf("%d",&num);

    for(i=0;i<num;i++)
    {
        for(j=0;j<num;j++)
        {
            scanf("%d",&adj[i][j]);
            if(adj[i][j]==1) indegree[j]++;
        }
    }

    for(i=0;i<num;i++) // print n number
    {
        top=-1;//用來檢查有沒有indegree為零的node存在

        for(j=0;j<num;j++)
        {
            if(indegree[j]==0)
            {
                indegree[j]=-1;//-1代表已移除
                top=j;
                break;
            }
        }

        if(top==-1)//沒有indegree為零的node存在，代表構成Directed Cycle
        {
            fprintf(stderr,"ERROR: The graph will form a directed circle.\n");
            exit(1);
        }

        for(j=0;j<num;j++)
        {
            indegree[j]-=adj[top][j];
        }

        if(i!=(num-1))
            printf("%d ", top+1);
        else
            printf("%d\n", top+1);
    }

    return 0;
}
