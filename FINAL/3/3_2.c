#include<stdio.h>


int main(void)
{
    int distance[700][700]={0};
    int num=0,i=0,j=0,k=0,tmp=0;

    scanf("%d", &num);

    for(i=0;i<num;i++)
    {
        for(k=0;k<num;k++)
        {
            scanf("%d",&distance[i][k]);
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
            printf("%d ", distance[i][j]);
        }
        printf("%d\n", distance[i][j]);
    }

    return 0;
}
