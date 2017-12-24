#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    int value;
    struct node *right;
    struct node *left;
};

typedef struct node NODE;

NODE *parent=NULL;

NODE *insert(NODE *header, int number);
NODE *search(NODE *header, int n);
NODE *delete(NODE *find, NODE *header);
void print_infix(NODE *header);
void levelorder(NODE *header);


int main(void)
{
    char *choice=NULL, *number=NULL, tmp[1000];
    int len=0;
    NODE *header=NULL, *find=NULL;

    printf("There are these functions below in this program\n");
    printf("(i) Insert Node\n");
    printf("(s) search Node\n");
    printf("(d) delete Node\n");
    printf("(p) Print Infix Order\n");
    printf("(v) Print Level Order\n");
    printf("(q) Quit\n");

    while(fgets(tmp, 1000-1, stdin))
    {
        len=strlen(tmp);

        if(tmp[len-1]=='\n')
            tmp[len-1]='\0';

        choice=strtok(tmp, " ");
        number=strtok(NULL, " ");

        if((choice!=NULL)&&(number==NULL))
        {
            switch(*choice)
            {
            case 'p':
                print_infix(header);
                printf("\n");
                break;

            case 'v':
                levelorder(header);
                printf("\n");
                break;

            case 'q':
                return 1;

            default:
                fprintf(stderr, "Syntax Error\n");
                break;
            }
        }
        else if((choice!=NULL)&&(number!=NULL))
        {
            switch(*choice)
            {
            case 'i':

                header=insert(header, atoi(number));//在main中的number是char型態
                break;

            case 's':

                find=search(header, atoi(number));

                if(find==NULL)
                    fprintf(stderr, "The %s is not found\n", number);
                else
                    printf("The number is existing\n");

                break;

            case 'd':

                find=search(header, atoi(number));

                if(find!=NULL)
                {
                    header=delete(find, header);

                    if(search(header, atoi(number))==NULL)//用Search確認是否已刪除
                        printf("Delete %s successfully\n", number);
                }
                else
                    fprintf(stderr, "DELETE ERROR: The %s is not found\n", number);
                break;

            default:

                fprintf(stderr, "Syntax Error\n");
                break;
            }
        }
        else
        {
            fprintf(stderr, "Syntax Error\n");
        }

        printf("--------------------------------\n");
    }

    return 0;
}


NODE *insert(NODE *header, int number)
{
    NODE *current=NULL;

    if(header==NULL)
    {
        current=(NODE *)malloc(sizeof(current));
        current->right=NULL;
        current->left=NULL;
        current->value=number;
        printf("Insert %d successfully\n", number);
        return current;
    }

    if(header->value>number)
    {
        header->left=insert(header->left, number);
        return header;//return original child to its parent
    }
    else if(header->value<number)
    {
        header->right=insert(header->right, number);
        return header;//return original child to its parent
    }
    else
    {
        fprintf(stderr, "The number is existing\n");
        return NULL;
    }
}


NODE *search(NODE *header, int number)
{
    if(header==NULL)
        return NULL;
    else
    {
        if(header->value>number)//to left
        {
            parent=header;
            return search(header->left, number);
        }
        else if(header->value<number)//to right
        {
            parent=header;
            return search(header->right, number);
        }
        else
            return header;
    }
}


void print_infix(NODE *header)
{
    if(header!=NULL)
    {
        print_infix(header->left);
        printf("%3d ", header->value);
        print_infix(header->right);
    }
}


NODE *delete(NODE *find, NODE *header)
{
    NODE *ptr=NULL, *lastp=NULL, *tmp=NULL;

    if(header!=NULL)
    {
        if((header->right==NULL)&&(header->left==NULL))
        {
            free(header);
            return NULL;
        }

        if((find->left==NULL)&&(find->right==NULL))// case 1: No child node at all
        {
            if(parent->left==find)
                parent->left=NULL;

            else //if(parent->right==find)
                parent->right=NULL;

            free(find);
            return header;
        }

        if(find->right!=NULL)// case 2: Two child node or only right node
        {

            if(find->right->left==NULL)//Deleted處理右子樹左為空的special case
            {
                find->value=find->right->value;

                if(find->right->right==NULL)//Deleted右子樹左右都為空
                {
                    free(find->right);
                    find->right=NULL;
                }
                else//Deleted右子樹左都為空, 右不為空
                {
                    tmp=find->right;
                    find->right=find->right->right;
                    // 因為deleted->right->right還有接序下去，所以刪除節點deleted->right之後，
                    // 還要把deleted接上剩下的右子樹deleted->right->right
                    free(tmp);
                }

                return header;
            }
            else//Deleted右子樹左都為空, 右不為空
                lastp=ptr=find->right;


        }
        else if(find->left!=NULL)// case 3: Only left node
        {
            lastp=find;
            ptr=find->left;
        }

        while(ptr->left!=NULL)
        {
            lastp=ptr;
            ptr=ptr->left;
        }

        find->value=ptr->value;
        lastp->left=NULL;

        if(ptr->right!=NULL)// 避免free掉"有右子樹的末端節點"
        {
            find=search(header, ptr->value);
            tmp=delete(find, header);
        }
        else
            free(ptr);

        return header;
    }

    return header;
}


void levelorder(NODE *header)
{
    NODE *queue[1000], *ptr=header;
    int rear=0, front=1, i=0;

    for(i=0; i<1000; i++)
    {
        queue[i]=NULL;
    }

    queue[rear++]=header;// insert first node

    while(ptr!=NULL)
    {
        printf("%3d ", ptr->value);

        if(ptr->left!=NULL)
        {
            queue[rear%1000]=ptr->left;
            rear=(rear+1)%1000;
        }

        if(ptr->right!=NULL)
        {
            queue[rear]=ptr->right;
            rear=(rear+1)%1000;
        }

        ptr=queue[front];
        front=(front+1)%1000;
    }
}
