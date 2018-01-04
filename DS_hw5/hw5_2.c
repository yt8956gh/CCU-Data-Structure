#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct edge
{
    int a,b;
    int weight;
}EDGE;

int term_num=0;

int cmp(const void* a,const void* b);

int is_circuit(int *choose_node, int a, int b);

int main(void)
{

    char tmp[1000], *ptr=NULL;
    int i=0, j=0, len=0, edge_num=0, set_num=0;
    int sum=0;
    int adj[1000][1000],choose_node[1000];
    EDGE relation[1000],set[1000];


    memset(adj,0,sizeof(adj));
    memset(choose_node,0,sizeof(choose_node));

    for(i=0;i<1000;i++)
    {
        set[i].a=relation[i].a=0;
        set[i].b=relation[i].b=0;
        set[i].weight=relation[i].weight=0;
    }


    FILE *fp=NULL,*output=NULL,*result=NULL;
    fp=fopen("2input.txt","r");
    output=fopen("output.txt","w");
    result=fopen("result2.txt","w");

    if(fp==NULL)
    {
        fprintf(stderr, "ERROR: The file is not existed\n");
        return 1;
    }

    // get term_num
    fgets(tmp,1000-1,fp);
    term_num=atoi(tmp);

    // read file to adj matrix
    for(i=0;i<term_num;i++)
    {
        fgets(tmp,1000-1,fp);
        len=strlen(tmp);

        if(tmp[len-1]=='\n')
            tmp[len-1]='\0';


        ptr=strtok(tmp," ");
        adj[i][0]=atoi(ptr);

        for(j=1;j<term_num;j++)
        {
            ptr=strtok(NULL," ");
            adj[i][j]=atoi(ptr);
        }
    }

    // ##Transfer adj-matrix to Relation-array##
    // Relation-array records edges' information.
    // Relation format:
    // Two nodes : a, b
    // Edge weight : weight

    for(i=0;i<term_num;i++)
    {
        for(j=i+1;j<term_num;j++)
        {
            if(adj[i][j]!=0)
            {
                relation[edge_num].a=i;
                relation[edge_num].b=j;
                relation[edge_num].weight=adj[i][j];
                edge_num++;
            }
            
        }
    }

    qsort(relation,edge_num,sizeof(EDGE),cmp);

    for(i=0;i<term_num;i++)
    {
        choose_node[i]=i; // choose_node is used to release Union-Find Algorithm
    }

    // Union-Find Algorithm:
    // It make every vertice save a key ,which is minimum vertice in that subtree.
    // That "some vertex have same key" represents that they are in same subtree, vice veresa.
    // A new edge will form a circuit iff. they are in same subtree.

    for(i=0;i<edge_num;i++)
    {
        if((!is_circuit(choose_node,relation[i].a,relation[i].b))||(i==0))
        {
            set[set_num].a=relation[i].a;
            set[set_num].b=relation[i].b;
            set[set_num].weight=relation[i].weight;
            set_num++;
        }
    }

    printf("The edges of Minimum Cost Spanning Tree are:\n\n");
    fprintf(result,"The edges of Minimum Cost Spanning Tree are:\n\n");

    for(i=0;i<set_num;i++)
    {
        printf("Edge %d:<%d %d> cost:%d\n",i+1,set[i].a+1,set[i].b+1,set[i].weight);
        fprintf(result,"Edge %d:<%d %d> cost:%d\n",i+1,set[i].a+1,set[i].b+1,set[i].weight);
        fprintf(output,"Edge %d:<%d %d> cost:%d\n",i+1,set[i].a+1,set[i].b+1,set[i].weight);
        sum+=set[i].weight;
    }

    fprintf(result,"Minimum cost = %d\n",sum);
    printf("Minimum cost = %d\n",sum);

    return 0;
}

int cmp(const void* a,const void* b)
{
    return ((EDGE*)a)->weight - ((EDGE*)b)->weight;
}

int is_circuit(int *choose_node, int a, int b)
{
    int i=0, min=0 ,max=0;

    if(choose_node[a]>choose_node[b])
    {
        max=choose_node[a];
        min=choose_node[b];

    }
    else if(choose_node[b]>choose_node[a])
    {
        max=choose_node[b];
        min=choose_node[a];
    }
    else
        return 1;

    for(i=0;i<term_num;i++)// update all max choose_node with min 
    {
        if(choose_node[i]==max)
            choose_node[i]=min;
    }

    return 0;
}

