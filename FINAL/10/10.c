#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int n;
int adj[1010][1010]={0};
int visit[1010];

void dfs(int a,int root)//用DFS去trace所有的點，如果沒trace到，該點的visit就會設為0
{
    int i;

    if(visit[a]||a==root) return;

    visit[a]=1;

    for(i=0;i<n;i++)
    {
        if(adj[a][i])
        {
            dfs(i,root);
        }
    }
}
int main()
{
    int i,j,k,ans[1010],z=0;;
    char  tmp[10000];//陣列要大於1010

    fgets(tmp,10,stdin);
    n=atoi(tmp);

    for(i=0;i<n;i++)
    {
        fgets(tmp,10000-1,stdin);

        for(j=0;j<n;j++)
        {
            adj[i][j]=tmp[j]-'0';
        }
    }

    for(k=0;k<n;k++)
    {
        memset(visit,0,sizeof(visit));
        if(k) dfs(0,k);//使得root與trace的第一個node不同
        else dfs(1,k);

        for(i=0;i<n;i++)
        {
            if(i!=k && !visit[i]) break;
            // if(會再非root時出現某一個visit為零)
            // 也就是將k點斷開，如果有沒被DFS trace到的點，則K為關節點
        }

        if(i!=n) ans[z++]=k;

    }

    for(i=0;i<(z-1);i++)
    {
        printf("%d ",ans[i]+1);
    }

    printf("%d\n",ans[i]+1);

    return 0;

}
