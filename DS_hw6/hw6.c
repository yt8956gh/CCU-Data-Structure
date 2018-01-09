#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct row
{
    int space[4],num;
}ROW;

int now=0;

void swap(int *sort,int a,int b);
void copy(int num, int *head_card, int *sort);
void insertion(int *sort,int n);
void selection(int *sort,int n);
void selection_rank(int *sort,int n);
void quicksort(int *sort,int left, int right);

int main(void)
{
    int i=0,k=0,small_tmp=0,head_card[10][10],sort[10][2],rank[4][2]={0}; 
    // sort[0] is player number; sort[1] is card number
    int small=0,j=0,score[10]={0},g=0;
    char tmp[100]={'\0'},*ptr=NULL;
    ROW rows[4];
    FILE *input=NULL,*result=NULL;

    input=fopen("input.txt","r");
    result=fopen("result.txt","w");

    memset(head_card,0,sizeof(head_card));
    memset(sort,0,sizeof(sort));

    for(i=0;i<4;i++)
    {
        memset(rows[i].space,0,sizeof(rows[0].space));
        fgets(tmp,100-1,input);
        rows[i].space[0]=atoi(tmp);
        rows[i].num=1;
    }

    for(i=0;i<10;i++)
    {
    	score[i]=66;//initialize
    	
        fgets(tmp,100-1,input);

        ptr=strtok(tmp,","); k=0;

        while(ptr!=NULL)
        {
            head_card[i][k++]=atoi(ptr);
            ptr=strtok(NULL,",");
        }
    }

    for(i=0;i<10;i++)// ten round
    {
        copy(i,(int*)head_card,(int*)sort);

        switch(i%3)
        {
            case 0:
                insertion((int*)sort,10);
                break;
            case 1:
                selection((int*)sort,10);
                break;
            case 2:
                quicksort((int*) sort, 0, 9);
                break;
        }

        for(k=0;k<10;k++)//every number in certain round
        {
            //fprintf(result,"\n[%d:%3d]",sort[k][0],sort[k][1]);

            for(j=0;j<4;j++)
            {
                rank[j][0]=j;
                rank[j][1]=rows[j].space[rows[j].num-1];
            }

            now=sort[k][1];
            selection_rank((int*)rank,4);

            small=rank[0][0];

            for(j=0;j<4;j++)// which row choiced to put head card
            {
                if(rank[j][1]<sort[k][1])
                {
                    small=rank[j][0];
                    //if(rows[rank[j][0]].num!=4) 
                    break;
                }

            }

            if(j==4)
            {
                selection((int*)rank,4);
                small_tmp=0;

                for(j=0;j<4;j++)// rank[x][0]: rows number; rank[x][1]: last number of rows x
                {
                    if(rows[rank[small_tmp][0]].num>rows[rank[j][0]].num)
                        small_tmp=j;
                }
                small=rank[small_tmp][0];
            }

            if(rows[small].space[rows[small].num-1]<sort[k][1])
            {
                if(rows[small].num==4)
                {
                    score[sort[k][0]]-=4;
                    memset(rows[small].space,0,sizeof(rows[0].space));
                    rows[small].space[0]=sort[k][1];
                    rows[small].num=1;
                }
                else
                {
                    rows[small].space[rows[small].num++]=sort[k][1];
                }
            }
            else
            {
                score[sort[k][0]]-=1;
                memset(rows[small].space,0,sizeof(rows[0].space));
                rows[small].space[0]=sort[k][1];
                rows[small].num=1;
            }
        }

        if((i==2)||(i==4)||(i==6))
        {
            fprintf(result,"\nThis is %2d round\n",i+1);

            for(j=0;j<4;j++)
            {
                fprintf(result,"This is %d row:", j+1);
                for(k=0;k<rows[j].num;k++){
                    fprintf(result,"\t%d", rows[j].space[k]); }
                    
                fprintf(result,"\n");
            }

            for(j=0;j<10;j++)
            {
                fprintf(result,"PlayerName: %2d     Point: %2d\n",j+1,score[j]);
            }
        }
    }
    
    return 0;
}


void swap(int *sort,int a,int b)
{
	int tmp[2]={0};
	
    tmp[0]=sort[a*2+0];
    tmp[1]=sort[a*2+1];
    sort[a*2+0]=sort[b*2+0];
    sort[a*2+1]=sort[b*2+1];
    sort[b*2+0]=tmp[0];
    sort[b*2+1]=tmp[1];
}


void copy(int num, int *head_card, int *sort)
{
    int i=0;

    for(i=0;i<10;i++)
    {
        sort[i*2+0]=i;
        sort[i*2+1]=head_card[i*10+num];
    }
}

void insertion(int *sort,int n)
{
    int i=0,next=0,tmp[2]={0};

    for(i=1;i<n;i++)//
    {
    	tmp[0]=sort[i*2+0];
        tmp[1]=sort[i*2+1];
        next=i;//

        while((next>=1)&&(sort[(next-1)*2+1]>tmp[1]))
        {
            sort[next*2+0]=sort[(next-1)*2+0];
            sort[next*2+1]=sort[(next-1)*2+1];

            next--;
        }

        sort[next*2+0]=tmp[0];//
        sort[next*2+1]=tmp[1];
    }

}


void selection(int *sort,int n)
{
    int i=0,j=0,tmp[2]={0},st=0;
    
    for(i=0;i<n;i++)
    {
        st=i;
        
        for(j=(i+1);j<n;j++)
        {         
            if(sort[st*2+1]>sort[j*2+1]) st=j;
        }
        swap((int*)sort, i, st);
    }
}

void selection_rank(int *sort,int n)
{
    int i=0,j=0,tmp[2]={0},st=0;
    int a=0,b=0;
    
    for(i=0;i<n;i++)
    {
        st=i;
        
        for(j=(i+1);j<n;j++)
        {         
            a=now-sort[st*2+1];
            b=now-sort[j*2+1];
            if(a<0) a*=-1;
            if(b<0) b*=-1;
            if(a>b) st=j;
        }
        swap((int*)sort, i, st);
    }
}


void quicksort(int *sort,int left, int right)
{
    int pivot=0,tmp[2]={0},i=0,j=0;

    if(left<right)
    {
        i=left; j=right+1;
        pivot=sort[left*2+1];

        do
        {
            do i++; while(sort[i*2+1]<pivot);
            do j--; while(sort[j*2+1]>pivot);
            if (i<j)//swap
            {
                swap((int*)sort, i, j);
            }
        }while(i<j);

        swap((int*)sort, left, j);
        //sort[j]<pivot will break do-while loop, so sort[j] is last number smaller than pivot.

        quicksort((int*) sort, left, j-1);
        quicksort((int*) sort, j+1, right);
    }
}

