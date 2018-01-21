#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(void)
{
	int adj[700][700],queue[10000]={0},rear=0,front=0;
	int distance[700],num=0,start=0,end=0,diff=0,i=0,j=0,now=0;
	
	memset(distance,-1,sizeof(distance));
	
	scanf("%d %d %d",&num,&start,&end);
	start--;end--;
	
	queue[rear++]=start;
	
	for(i=0;i<num;i++)
	{
		scanf("%d", &diff);
		if((i-diff)>=0) adj[i][i-diff]=1;//注意要大於0 
		if((i+diff)<num) adj[i][i+diff]=1;
	}
	
	distance[start]=0;
	
	while(rear!=front)
	{
		now=queue[front++];
		
		for(i=0;i<num;i++)
		{
			
			if(distance[i]==-1&&adj[now][i]==1)//注意and 
			{
				distance[i]=distance[now]+1;
				queue[rear++]=i;
			}
		}
	}
	
	printf("%d\n",distance[end]);
	
	return 0;
 } 
