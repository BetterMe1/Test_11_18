#include <iostream>
#include <string>
#include <ctype.h>
#define N 50
typedef struct BiTNode
{
    char data[N];
    int count;
    struct BiTNode *lChild;
    struct BiTNode *rChild;
}BiTNode,*BiTree;

int GetWord(int start,int end,char* pBuf,char* word);       //词汇
void CreateSearchTree(char* item,BiTree& T);                //创建二叉树进行查找
void Printresult(BiTree T);                    //遍历输出
int sum=0;
char temp1[N];
char temp2[N];

int main()
{  
    char fileName[30]="input.txt";  //文件名默认为input.txt
    FILE* pf;
    pf=fopen(fileName,"rb");
    printf("**********************************************************\n");
    printf("成功打开文件--- %s !\n\n",fileName); 
    //读取文件内容
    fseek(pf,0,SEEK_END);
    int len=ftell(pf);
    rewind(pf);
    char *pBuf=new char[len+1];
    pBuf[len]=0;
    fread(pBuf,1,len,pf);
    fclose(pf);
    //读取单词
    printf("%s\n",pBuf);
    printf("**********************************************************\n");
    int i=0;
    char word[N];
    BiTree T=NULL;
    while(i<len)
    {
        i=GetWord(i,len,pBuf,word);
        if(strlen(word)==0)
        {
            break;
        }
        CreateSearchTree(word,T);       
    }
	//输出结果
    printf("\t\t词频统计结果:\n");
    printf("**********************************************************\n");
    Printresult(T);//调用void Printresult(BiTree T)遍历输出
    printf("**********************************************************\n");
    printf("这篇文章单词总数：%d\n",sum-1);
    printf("***********************************************************\n");
    return 0;
}

//词汇
int GetWord(int start,int end,char* pBuf,char* word)
{
    int i;
    int j=0;
    memset(word,0,sizeof(char));
    for(i=start;i<end;i++)
    {
        if(isalpha(pBuf[i]))
        {
            word[j]=pBuf[i];
            j++;
        }
        else
        {
            if(j==0)
            {
                continue;
            }
            word[j]='\0';
            j=0;
            sum++;
            break;
        }
    }
    return i;
}

//创建二叉树进行查找
void CreateSearchTree(char* item,BiTree& T)
{
    strcpy(temp1,item);
    temp1[0]=tolower(item[0]);

    if(T==NULL)
    {
        T=(BiTree)malloc(sizeof(BiTNode));
        strcpy(T->data,item);
        T->count=1;
        T->lChild=NULL;  
        T->rChild=NULL;
    }
    else
    {
        strcpy(temp2,T->data);
        temp2[0]=tolower(T->data[0]);
        if(strcmp(temp1,temp2)==-1)
        {
            CreateSearchTree(item,T->lChild);
        }
        else if(strcmp(temp1,temp2)==1)
        {   
            CreateSearchTree(item,T->rChild);
        }
        else
        {
            T->count++;
        }
    }
}

//遍历输出
void Printresult(BiTree T)
{
    if(T!=NULL)
    {
		Printresult(T->lChild);//递归
        printf("出现的词汇：%-30s 频率:%-9d\t\n",T->data,T->count);
		Printresult(T->rChild);
    }
}


