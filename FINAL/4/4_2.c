#include<string.h>
#include<stdio.h>
#include<stdlib.h>

int count=0;

void quicksort(int *number,int left,int right);

int main(void)
{
	char tmp[1000],*ptr=NULL;
	int number[1000]={0};
	fgets(tmp,1000-1,stdin);
	ptr=strtok(tmp," ");

	while(ptr!=NULL)
	{
		number[count++]=atoi(ptr);
		ptr=strtok(NULL," ");
	}

	quicksort(number, 0, count-1);

    return 0;
}


void quicksort(int *number,int left,int right)
{
	int pivot=0,tmp=0,i=0,j=0,k=0;

	if(left<right)
	{
		i=left; j=right+1;
		pivot=number[left];

		do{
			do i++; while(number[i]<pivot);
			do j--; while(number[j]>pivot);

			if(i<j)
			{
				tmp=number[i];
				number[i]=number[j];
				number[j]=tmp;

				for(k=0;k<(count-1);k++)
				{
					printf("%d ", number[k]);
				}
				printf("%d\n", number[k]);
			}
		}while(i<j);

		if(j!=left)
		{
			tmp=number[j];
			number[j]=number[left];
			number[left]=tmp;

			for(k=0;k<(count-1);k++)
			{
				printf("%d ", number[k]);
			}
			printf("%d\n", number[k]);
		}

		quicksort(number,left,j-1);//°O±o­nrecusive 
		quicksort(number,j+1,right);
	}
}
