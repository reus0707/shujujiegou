#include <stdio.h>
#include <stdlib.h>
#define MAX 10
typedef struct node{
    int value;  //保存数值
    struct node *forward[1];   //数组指向后面的节点
}node;
typedef struct skiplist{
    int level;   //跳表的层数
    struct node *header;   //每一层的头指针
}skiplist;
node * createNode(int level,int value)
{
    node * Node=(node *)malloc(sizeof(node)+level*sizeof(node *)); //申请内存，比层数多两个指针的内存
    Node->value=value;  //赋值
    return Node;
}
skiplist * createSkipList()
{
    int i;
    skiplist *SkipList=(skiplist *)malloc(sizeof(skiplist));   //申请跳跳表内存
    SkipList->level=0;  //层数初始化为0
    SkipList->header=createNode(MAX-1,0);   //建立最大层数的头指针
    for(i=0;i<MAX;i++)
    {
        SkipList->header->forward[i]=NULL;  //将头指针指向空进行初始化
    }
    return SkipList;
}
/*随机生成层数*/
int  InsertListLevel(){
    int k=1;
    while (rand()%3)
        k++;
    k=(k<MAX)?k:MAX;   //最大层数不得大于虽大层数
    printf("随机产生的层数是：%d\n",k);
    return k;
}
int insertNode(skiplist *SkipList,int value)
{
    int i,j;
    node *update[MAX];   //定义一个node指针的数组
    node *p, *q = NULL;
    p=SkipList->header;   //指向最高层数头指针
    int k=SkipList->level;
    for(i=k-1; i >= 0; i--)
    {
        while((q=p->forward[i]) && (q->value<value)){
            p=q;
        }
        update[i]=p;
    }
    if(q && q->value==value)  //如果插入的值和跳表中某一个相等，就不插入
    {
        return 0;
    }
    i=InsertListLevel();   //随机生成层数
    if(i>(SkipList->level))  //如果随机产生的层数大于此时最大的层数
    {
        for(j=SkipList->level; j < i; j++)
        {
            update[j] = SkipList->header;  //把相应的层数的头指针指向待插入的位置
        }
        SkipList->level=i;   //最大层数变成随机产生的数
    }
    q=createNode(i,value);  //申请相应层数的内存
    for(j=0;j<i;j++){
                 q->forward[j]=update[j]->forward[j];   //将相应的数据插入进去，且每一层都插入进去
                 update[j]->forward[j]=q;
    }
    return 1;
}
int deleteNode(skiplist *SkipList,int value)
{
    int i,j;
    node *update[MAX];
    node * p,* q=NULL;
    p=SkipList->header;
    int k=SkipList->level;
    for(j=k-1; j>= 0; j--)
    {
        while((q=p->forward[j]) && q->value<value)//当p指向的不为空，且还没找到比我们待删除的数更大的数就继续找
        {
            p=q;  //将当前的q的指向给p
        }
        update[j]=p;  //找到大于待删除数据后将找到的位置输入到数组里保存起来
    }
    if(q && q->value==value)
    {
        for(i=0; i<SkipList->level; i++)
        {
            if(update[i]->forward[i]==q) //说明是待删除的节点处
            {
                update[i]->forward[i]=q->forward[i];  //做删除前的准备
            }
        }
        free(q);
        for(i=SkipList->level-1; i >= 0; i--)
        {
            if(SkipList->header->forward[i]==NULL)
            {
                SkipList->level--;   //对最大层数进行相应的减少
            }
        }
        return 1;
    }
    else
        return 0;
}
int searchNode(skiplist *SkipList,int value)
{
    int i;
    node *p,*q=NULL;
    p=SkipList->header;
    int k=SkipList->level;
    for(i=k-1; i >= 0; i--)
    {
        while((q=p->forward[i])&&(q->value<=value))
        {
            if(q->value==value)
            {
                return q->value;
            }
            p=q;
        }
    }
    return 0;
}
void coutSkipList(skiplist * SkipList)
{
    int i;
    node *p,*q=NULL;
    int k=SkipList->level;
    for(i=k-1; i >= 0; i--)  //按层数输出
    {
        p=SkipList->header;
        while((q=p->forward[i]))
        {
            printf("%d-->",p->value);
            p=q;
        }
        printf("%d-->NULL!",p->value);
        printf("\n");
    }
    printf("\n");
}
int main()
{
    skiplist * SkipList=createSkipList();
    int num,j,i;
    char c;
    printf("请输入正整数个数：");
    scanf("%d",&num);
    printf("请依次输入正整数：");
    for(i=0;i<num;i++)
    {
        scanf("%d",&j);
        insertNode(SkipList,j);
    }
    printf("跳表输出如下：\n");
    coutSkipList(SkipList);
    printf("***********菜单*************\n");
    printf("***********插入1*************\n");
    printf("***********删除2*************\n");
    printf("***********查询3*************\n");
    printf("***********退出0*************\n");
    printf("请输入您想进行的操作：\n");
    scanf(" %c",&c);
    while(c!='0')
    {
        switch (c)
        {
        case '1':
            printf("请插入内容（仅限正整数！）：");
            scanf("%d",&j);
            if(!insertNode(SkipList,j))
            {
                printf("该元素已存在！\n");
                continue;
            }
            printf("插入后跳表如下：\n");
            coutSkipList(SkipList);
            break;
        case '2':
            printf("请输入想要删除的内容：");
            scanf("%d",&j);
            if(!searchNode(SkipList, j))
                printf("该数据不存在！\n");
            else
            {
                deleteNode(SkipList, j);
                printf("删除内容后的跳表如下：\n");
                coutSkipList(SkipList);
            }
            break;
        case '3':
            printf("请输入查询内容（请输入正整数！）：");
            scanf("%d",&j);
            if(searchNode(SkipList, j))
            {
                printf("搜索内容在跳表中！\n");
                break;
            }
            else
            {
                printf("搜索内容不在跳表中！\n");
            }
        }
        printf("请输入您想进行的操作：\n");
        scanf(" %c",&c);
    }
    return 0;
}
