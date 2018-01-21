#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(void)
{
    int num=0,i=0,j=0,top=0,adj[100][100]={0};
    int indegree[100]={0},outdegree[100]={0};

    scanf("%d",&num);

    for(i=0;i<num;i++)
    {
        for(j=0;j<num;j++)
        {
            scanf("%d",&adj[i][j]);
            if(adj[i][j]==1)
            {
                outdegree[i]++;
                indegree[j]++;
            }
        }
    }

    for(i=0;i<num;i++)
    {
        printf("%d %d %d\n",i+1,indegree[i],outdegree[i]);
    }

    return 0;
}
