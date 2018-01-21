#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(void)
{
    int num=0,i=0,j=0,k=0,adj[100][100]={0};
    int distance[100][100]={0};

    scanf("%d",&num);

    for(i=0;i<num;i++)
    {
        for(j=0;j<num;j++)
        {
            scanf("%d",&adj[i][j]);
            distance[i][j]=adj[i][j];
        }
    }

    for(k=0;k<num;k++)
    {
        for(i=0;i<num;i++)
        {
            for(j=0;j<num;j++)
            {
                distance[i][j]=distance[i][j]||(distance[i][k]&&distance[k][j]);
            }
        }
    }

    for(i=0;i<num;i++)
    {
        for(j=0;j<(num-1);j++)
        {
            printf("%d ",distance[i][j]);
        }
        printf("%d\n",distance[i][j]);
    }



    return 0;
}
