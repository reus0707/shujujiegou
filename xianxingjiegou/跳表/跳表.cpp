#include <stdio.h>
#include <stdlib.h>
#define MAX 10
typedef struct node{
    int value;  //������ֵ
    struct node *forward[1];   //����ָ�����Ľڵ�
}node;
typedef struct skiplist{
    int level;   //����Ĳ���
    struct node *header;   //ÿһ���ͷָ��
}skiplist;
node * createNode(int level,int value)
{
    node * Node=(node *)malloc(sizeof(node)+level*sizeof(node *)); //�����ڴ棬�Ȳ���������ָ����ڴ�
    Node->value=value;  //��ֵ
    return Node;
}
skiplist * createSkipList()
{
    int i;
    skiplist *SkipList=(skiplist *)malloc(sizeof(skiplist));   //�����������ڴ�
    SkipList->level=0;  //������ʼ��Ϊ0
    SkipList->header=createNode(MAX-1,0);   //������������ͷָ��
    for(i=0;i<MAX;i++)
    {
        SkipList->header->forward[i]=NULL;  //��ͷָ��ָ��ս��г�ʼ��
    }
    return SkipList;
}
/*������ɲ���*/
int  InsertListLevel(){
    int k=1;
    while (rand()%3)
        k++;
    k=(k<MAX)?k:MAX;   //���������ô���������
    printf("��������Ĳ����ǣ�%d\n",k);
    return k;
}
int insertNode(skiplist *SkipList,int value)
{
    int i,j;
    node *update[MAX];   //����һ��nodeָ�������
    node *p, *q = NULL;
    p=SkipList->header;   //ָ����߲���ͷָ��
    int k=SkipList->level;
    for(i=k-1; i >= 0; i--)
    {
        while((q=p->forward[i]) && (q->value<value)){
            p=q;
        }
        update[i]=p;
    }
    if(q && q->value==value)  //��������ֵ��������ĳһ����ȣ��Ͳ�����
    {
        return 0;
    }
    i=InsertListLevel();   //������ɲ���
    if(i>(SkipList->level))  //�����������Ĳ������ڴ�ʱ���Ĳ���
    {
        for(j=SkipList->level; j < i; j++)
        {
            update[j] = SkipList->header;  //����Ӧ�Ĳ�����ͷָ��ָ��������λ��
        }
        SkipList->level=i;   //��������������������
    }
    q=createNode(i,value);  //������Ӧ�������ڴ�
    for(j=0;j<i;j++){
                 q->forward[j]=update[j]->forward[j];   //����Ӧ�����ݲ����ȥ����ÿһ�㶼�����ȥ
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
        while((q=p->forward[j]) && q->value<value)//��pָ��Ĳ�Ϊ�գ��һ�û�ҵ������Ǵ�ɾ��������������ͼ�����
        {
            p=q;  //����ǰ��q��ָ���p
        }
        update[j]=p;  //�ҵ����ڴ�ɾ�����ݺ��ҵ���λ�����뵽�����ﱣ������
    }
    if(q && q->value==value)
    {
        for(i=0; i<SkipList->level; i++)
        {
            if(update[i]->forward[i]==q) //˵���Ǵ�ɾ���Ľڵ㴦
            {
                update[i]->forward[i]=q->forward[i];  //��ɾ��ǰ��׼��
            }
        }
        free(q);
        for(i=SkipList->level-1; i >= 0; i--)
        {
            if(SkipList->header->forward[i]==NULL)
            {
                SkipList->level--;   //��������������Ӧ�ļ���
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
    for(i=k-1; i >= 0; i--)  //���������
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
    printf("������������������");
    scanf("%d",&num);
    printf("������������������");
    for(i=0;i<num;i++)
    {
        scanf("%d",&j);
        insertNode(SkipList,j);
    }
    printf("����������£�\n");
    coutSkipList(SkipList);
    printf("***********�˵�*************\n");
    printf("***********����1*************\n");
    printf("***********ɾ��2*************\n");
    printf("***********��ѯ3*************\n");
    printf("***********�˳�0*************\n");
    printf("������������еĲ�����\n");
    scanf(" %c",&c);
    while(c!='0')
    {
        switch (c)
        {
        case '1':
            printf("��������ݣ�����������������");
            scanf("%d",&j);
            if(!insertNode(SkipList,j))
            {
                printf("��Ԫ���Ѵ��ڣ�\n");
                continue;
            }
            printf("������������£�\n");
            coutSkipList(SkipList);
            break;
        case '2':
            printf("��������Ҫɾ�������ݣ�");
            scanf("%d",&j);
            if(!searchNode(SkipList, j))
                printf("�����ݲ����ڣ�\n");
            else
            {
                deleteNode(SkipList, j);
                printf("ɾ�����ݺ���������£�\n");
                coutSkipList(SkipList);
            }
            break;
        case '3':
            printf("�������ѯ���ݣ�������������������");
            scanf("%d",&j);
            if(searchNode(SkipList, j))
            {
                printf("���������������У�\n");
                break;
            }
            else
            {
                printf("�������ݲ��������У�\n");
            }
        }
        printf("������������еĲ�����\n");
        scanf(" %c",&c);
    }
    return 0;
}
