#include<stdio.h>
#include<stdlib.h>

int adj[1010][1010],indegree[1010]={0},num=0;

int main(void)
{

    int i=0,k=0,top=0;

    scanf("%d",&num);

    for(i=0;i<num;i++)
    {
        for(k=0;k<num;k++)
        {
            scanf("%d", &adj[i][k]);
            if(adj[i][k]==1) indegree[k]++;
        }
    }

    for(i=0;i<num;i++)
    {
        top=-1;

        for(k=0;k<num;k++)
        {
            if(indegree[k]==0)
            {
                indegree[k]=-1;
                top=k;
                break;
            }
        }

        for(k=0;k<num;k++)
        {
            indegree[k]-=adj[top][k];
        }

        if(i!=(num-1))
            printf("%d ", top+1);
        else
            printf("%d\n", top+1);
    }

    return 0;
}
