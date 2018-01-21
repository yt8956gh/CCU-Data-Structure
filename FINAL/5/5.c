#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{
    int a, b, weight;
}relation;

int cmp(const void* a, const void* b)
{
    return ((relation*)a)->weight-((relation*)b)->weight;
}

int is_circuit(int a, int b, int *subtree_key, int num)
{
    int small=0, big=0, i=0;
    if(subtree_key[a]==subtree_key[b]) return 1;

    small=(subtree_key[a]>subtree_key[b])?subtree_key[b]:subtree_key[a];
    big=(subtree_key[a]<subtree_key[b])?subtree_key[b]:subtree_key[a];

    for(i=0;i<num;i++)
    {
        if(subtree_key[i]==big) subtree_key[i]=small;
    }

    return 0;//記得要return 0 回去，要不然沒辦法跑set
}

int main(void)
{
    int num=0, adj[100][100]={0}, subtree_key[100]={0};
    int i=0, j=0, edge_num=0,set_num=0;
    relation edge[100], set[100];

    for(i=0;i<num;i++)
    {
        edge[i].a=edge[i].b=edge[i].weight=0;
        set[i].a=set[i].b=set[i].weight=0;
    }

    scanf("%d", &num);

    for(i=0;i<num;i++){
        for(j=0;j<num;j++){
            scanf("%d", &adj[i][j]);}}

    for(i=0;i<num;i++)
    {
        for(j=(i+1);j<num;j++)
        {
            if(adj[i][j])
            {
                edge[edge_num].a=i;
                edge[edge_num].b=j;
                edge[edge_num].weight=adj[i][j];
                edge_num++;
            }
        }
    }

    qsort(edge, edge_num, sizeof(edge[0]), cmp);

    for(i=0;i<num;i++)
        subtree_key[i]=i;

    for(i=0;i<edge_num;i++)
    {
        if(!is_circuit(edge[i].a, edge[i].b, subtree_key, num))
        {
            set[set_num].a=edge[i].a+1;
            set[set_num].b=edge[i].b+1;
            set[set_num].weight=edge[i].weight;
            set_num++;
        }
    }

    for(i=0;i<set_num;i++)
        printf("%d %d %d\n", set[i].a, set[i].b, set[i].weight);

    return 0;
}
