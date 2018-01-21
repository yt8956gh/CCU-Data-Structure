#include<stdio.h>

int num=0,level=1,visit_num=0;
int adj[100][100];

void prim(int *visit);

int main(void)
{
    int i=0,k=0,tmp=0,min=(2<<20),minX=0,minY=0;
    int visit[100]={0},small=0,big=0;

    scanf("%d",&num);

    for(i=0;i<num;i++)
    {
        for(k=0;k<num;k++)
        {
            scanf("%d",&adj[i][k]);
            if(adj[i][k]&&min>adj[i][k])
            {
                min=adj[i][k];
                minX=i;
                minY=k;
            }
        }
    }

    small=((minX>minY)?minY:minX)+1;
    big=((minX<minY)?minY:minX)+1;
    printf("%d %d %d %d\n",level++,small,big,adj[minX][minY]);

    visit_num=2;
    visit[minX]=visit[minY]=1;
    prim(visit);

    return 0;
}

void prim(int *visit)
{
    int i=0,k=0,min=(2<<20),minX=0,minY=0,small=0,big=0;

    if(visit_num==num) return;

    for(i=0;i<num;i++)
    {
        if(visit[i]==1)
        {
            for(k=0;k<num;k++)
            {
                if(!visit[k]&&adj[k][i]&&adj[k][i]<min)
                {
                    min=adj[k][i];
                    minX=k;
                    minY=i;
                }
            }
        }
    }

    visit[minX]=1;
    small=((minX>minY)?minY:minX)+1;
    big=((minX<minY)?minY:minX)+1;

    printf("%d %d %d %d\n",level++,small,big,adj[minX][minY]);

    visit_num++;
    prim(visit);
}
