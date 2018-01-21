#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int adj[700][700],visit[700]={0},ans[700]={0};
int art_num=0,num=0;


void dfs(int a, int root)
{
	if(a==root||visit[a]) return;
	
	int i=0;
	
	visit[a]=1;
	
	for(i=0;i<num;i++)
	{
		if(adj[a][i])
		{
			dfs(i,root);
		}	
	}
}

int main(void)
{

	int i=0,k=0;
	char tmp[10000];
	
	
	fgets(tmp,100,stdin);
	
	num=atoi(tmp);
	
	for(i=0;i<num;i++)
	{
		fgets(tmp,10000-1,stdin);
		
		for(k=0;k<num;k++)
		{
			adj[i][k]=tmp[k]-'0';	
		} 
	}
	
	
	for(i=0;i<num;i++)
	{
		memset(visit,0,sizeof(visit));
		
		if(i) dfs(0,i);
		else dfs(1,i); 
		
		
		for(k=0;k<num;k++)
		{
			
			if(k!=i&&visit[k]==0) break; 
		}
		
		if(k!=num) 
		{
			ans[art_num++]=i;
		}
	
	}
	
	
	for(i=0;i<(art_num-1);i++)
	{
		printf("%d ",ans[i]+1);
	}
	
	printf("%d\n",ans[i]+1);
	
	return 0;
}
