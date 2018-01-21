#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct relat
{
	int a,b,weight;
}EDGE;

int num=0,adj[700][700]={0},sub_key[700]={0};

int cmp(void const *a,void const *b)
{
	return ((EDGE*)a)->weight-((EDGE*)b)->weight;
}

int is_cycle(EDGE tmp)
{
	if(sub_key[tmp.a]==sub_key[tmp.b]) return 1;

	int small=0, big=0, i=0;

	small=(sub_key[tmp.a]>=sub_key[tmp.b])?sub_key[tmp.a]:sub_key[tmp.b];
	big=(sub_key[tmp.a]<sub_key[tmp.b])?sub_key[tmp.a]:sub_key[tmp.b];

	for(i=0;i<num;i++)
	{
		if(sub_key[i]==big) sub_key[i]=small;
	}

	return 0;
}

int main(void)
{
	int i=0,j=0,k=0,edge_num=0,choose[700]={0},node;
	EDGE edge[700];


	scanf("%d",&num);

	for(i=0;i<num;i++)
	{
		sub_key[i]=i;
		for(k=0;k<num;k++)
			scanf("%d", &adj[i][k]);
	}

	for(i=0;i<num;i++)
	{
		for(k=i+1;k<num;k++)
		{
			if(adj[i][k]!=0)
			{
				edge[edge_num].a=i;
				edge[edge_num].b=k;
				edge[edge_num].weight=adj[i][k];
				edge_num++;
			}
		}
	}

	qsort(edge,edge_num,sizeof(edge[0]),cmp);

	for(i=0;i<edge_num;i++)
	{
		if(!is_cycle(edge[i]))
			printf("%d %d %d\n",edge[i].a+1,edge[i].b+1,edge[i].weight);
	}

	return 0;
}
