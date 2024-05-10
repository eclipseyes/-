#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <windows.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2


typedef int status;
typedef int ElemType; //数据元素类型定义
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

typedef struct LNode {  //单链表（链式结构）结点的定义
	ElemType data;
	struct LNode* next;
}LNode, * LinkList;

typedef struct {    //线性表的管理表定义
	struct {
		char name[30];
		LinkList L;
	} elem[10];
	int length;
}LISTS;


FILE *fp;

//功能函数声明
status InitList(LinkList &L);
status DestroyList(LinkList &L);
status ClearList(LinkList &L);
status ListEmpty(LinkList L);
status ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType &e);
int LocateElem(LinkList L,ElemType e);
status PriorElem(LinkList L,ElemType e,ElemType &pre);
status NextElem(LinkList L,ElemType e,ElemType &next);
status ListInsert(LinkList &L,int i,ElemType e);
status ListDelete(LinkList &L,int i,ElemType &e);
status ListTraverse(LinkList L);
status reverseList(LinkList &L);
status RemoveNthFromEnd(LinkList &L, int n); 
status SaveList(LinkList L,char FileName[]);
status LoadList(LinkList &L,char FileName[]);
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,char ListName[]);
int LocateList(LISTS Lists,char ListName[]);
status sortList(LinkList &L);


int main(void)
{
    //设置程序框
    system("mode con cols50 lines=20");
    system("title 线性表：链式存储结构");
    system("color 9F");
    //初始化线性表集
    LISTS Lists;      //线性表集合的定义Lists
    Lists.length=1;
    int op=1;         //选择操作
    int cur=0;        //现在处理的线性表的逻辑序数
    int val;
    int res;
    int pos;
    int pre;
    int next;
    int IsEmpty;
    char filename[30];
    char listname[30];
    for(int i=0;i<10;i++)
    {
        Lists.elem[i].L=NULL;
    }
    strcpy(Lists.elem[0].name,"list");

    //--------------------菜单主体-------------------------
    while(op)
    {
        fflush(stdout); // 确保在清屏之前刷新所有标准输出
        system("cls");//清空命令行窗口
        printf("\n\n");
        printf("   \t\t\t线性表链式结构菜单\t\t\n\n");
        printf("   \t\t\t\t\t最多在10个线性表间进行操作，初始表名称为“list”\t\t\t\n");
        printf("---------------------线性表内操作--------------------------------\n");
        printf("1.初始化线性表      \t\t\t\t2.销毁线性表\n");
        printf("3.清空线性表        \t\t\t\t4.线性表判空\n");
        printf("5.求线性表的表长    \t\t\t\t6.获取元素\n");
        printf("7.查找元素          \t\t\t\t8.获取前驱元素\n");
        printf("9.获取后继元素      \t\t\t\t10.插入元素\n");
        printf("11.删除元素         \t\t\t\t12.遍历线性表\n");
        printf("13.线性表存储       \t\t\t\t14.线性表读取\n");
        printf("15.添加线性表       \t\t\t\t16.移除线性表\n");
        printf("17.查找线性表       \t\t\t\t18.更换操作线性表\n");
        printf("19.链表翻转     \t\t\t\t20.删除链表的倒数第n个结点\n");
		    printf("21.从小到大排序"); 
        printf("\n\t\t\t\t\t\t\t0.退出\t\t\t\n");
        printf("当前操作的线性表：线性表%d:%s",cur+1,Lists.elem[cur].name);
        if(Lists.elem[cur].L==NULL) printf("(未初始化)");
        printf("\n");
        printf("请输入数字0~21进行操作\n");
        scanf("%d",&op);//设置op的值，以便后续进行操作选择
        while(getchar()!='\n') continue;
        printf("\n");
        switch(op)
        {
            case 0:
               break;
            case 1:
               //初始化线性表
               if(InitList(Lists.elem[cur].L)==OK)
                  printf("线性表初始化成功！");
               else
                  printf("初始化失败，该线性表已存在！\n");
               break;
            case 2:
               //销毁线性表
               if(DestroyList(Lists.elem[cur].L)==OK)
                  printf("线性表销毁成功！");
               else
                  printf("销毁失败，该线性表不存在！\n");
               break;
            case 3:
               //清空线性表
                if(ClearList(Lists.elem[cur].L)==OK)
                  printf("线性表清空成功！");
               else
                  printf("清空失败，该线性表不存在！\n");
               break;
            case 4:
               //线性表的判空
               
               IsEmpty=ListEmpty(Lists.elem[cur].L);
               if(IsEmpty==INFEASIBLE) 
                 printf("判断失败，线性表不存在！");
               else if(IsEmpty==TRUE)
                 printf("线性表为空！");
               else
                 printf("线性表不为空！");
               break;
            case 5:
              //求线性表的表长
              if(ListLength(Lists.elem[cur].L)==INFEASIBLE)
                printf("线性表不存在！");
              else
                printf("线性表表长为%d",ListLength(Lists.elem[cur].L));
              break;
            case 6:
               //获取元素
               if(Lists.elem[cur].L==NULL)
               {
                 printf("线性表不存在!");
                 break;
               }
               printf("正在进行获取元素操作,请输入获取元素逻辑次序(第一个为1):");
               scanf("%d",&pos);
               res=GetElem(Lists.elem[cur].L,pos,val);
               if(res==INFEASIBLE)
                 printf("线性表不存在！");
               else if(res==ERROR)
                 printf("获取元素值失败，请检查下标值是否合法！");
               else 
                 printf("您查找的元素值为%d",val);
               break;
            case 7:
               //查找元素
               if(Lists.elem[cur].L==NULL)
               {
                 printf("线性表不存在!");
                 break;
               }
               printf("正在进行查找元素操作，请输入查找元素数值：");
               scanf("%d",&val);
               pos=LocateElem(Lists.elem[cur].L,val);
               if(pos==INFEASIBLE)
                 printf("线性表不存在！");
               else if(pos==0)
                 printf("该元素在线性表中不存在！");
               else 
                 printf("您查找的元素在线性表中的位置序号为%d",pos);
               break;
            case 8:
              //获取前驱元素的值
              if(Lists.elem[cur].L==NULL)
               {
                 printf("线性表不存在!");
                 break;
               }
               printf("正在进行获取前驱元素操作，请输入元素的值：");
               scanf("%d",&val);
               if(PriorElem(Lists.elem[cur].L,val,pre)==INFEASIBLE)
                 printf("线性表不存在！");
               else if(PriorElem(Lists.elem[cur].L,val,pre)==ERROR)
                 printf("获取元素值失败，请检查该元素是否在线性表中或是否无前继元素！");
               else 
                 printf("您查找的前驱元素值为%d",pre);
               break;
            case 9:
              //获取后继元素的值
              if(Lists.elem[cur].L==NULL)
               {
                 printf("线性表不存在!");
                 break;
               }
               printf("正在进行获取后继元素操作，请输入元素的值：");
               scanf("%d",&val);
               if(NextElem(Lists.elem[cur].L,val,next)==INFEASIBLE)
                 printf("线性表不存在！");
               else if(NextElem(Lists.elem[cur].L,val,next)==ERROR)
                 printf("获取元素值失败，请检查该元素是否在线性表中或无后继元素！");
               else 
                 printf("您查找的后继元素值为%d",next);
               break;
            case 10:
              //插入元素
              if(Lists.elem[cur].L==NULL)
               {
                 printf("线性表不存在!");
                 break;
               }
              printf("正在进行插入元素操作...\n");
              printf("请输入插入元素的值：");
              scanf("%d",&val);
              printf("请输入插入的位置序号：");
              scanf("%d",&pos);
              res=ListInsert(Lists.elem[cur].L,pos,val);
              if(res==INFEASIBLE)
                printf("线性表不存在！");
              else if(res==ERROR)
                printf("插入失败，请检查下标值是否合法或线性表内存是否充足！");
              else
                printf("元素插入成功！");
              break;
            case 11:
              //删除元素
              if(Lists.elem[cur].L==NULL)
               {
                 printf("线性表不存在!");
                 break;
               }
              printf("正在进行删除元素操作...\n");
              printf("请输入删除元素的值：");
              scanf("%d",&val);
              printf("请输入删除的位置序号：");
              scanf("%d",&pos);
              res=ListDelete(Lists.elem[cur].L,pos,val);
              if(res==INFEASIBLE)
                printf("线性表不存在！");
              else if(res==ERROR)
                printf("删除失败，请检查下标值是否合法或线性表内存是否充足！");
              else
                printf("元素删除成功！");
              break;
            case 12:
              //遍历线性表
              if(ListTraverse(Lists.elem[cur].L)==INFEASIBLE)
                printf("线性表不存在！");
              else 
                printf("遍历成功！");
              break;
            case 13:
              //线性表的数据元素写入文件
              if(Lists.elem[cur].L==NULL)
              {
                printf("线性表不存在，数据无法写入！");
                break;
              }
              printf("正在进行线性表的数据元素写入文件操作...\n");
              printf("请输入存储数据文件名:");
              scanf("%s",filename);
              if(SaveList(Lists.elem[cur].L,filename)==OK)
                printf("数据已经成功写入文件！");
              else 
                printf("数据写入失败，线性表不存在！");
              break;
            case 14:
              //文件数据写入线性表
              if(Lists.elem[cur].L!=NULL)
              {
                printf("线性表已存在，数据无法写入！");
                break;
              }
              printf("正在进行文件数据写入线性表操作...\n");
              printf("请输入导入数据文件名:");
              scanf("%s",filename);
              if(LoadList(Lists.elem[cur].L,filename)==OK)
                printf("数据已经成功写入线性表！");
              else 
                printf("数据写入失败，线性表已存在！");
              break;
            case 15:
              //添加线性表
              if(Lists.length>=10)
              {
                printf("线性表数目已经达到上限，无法添加！");
                break;
              }
              printf("当前共有%d个线性表\n",Lists.length);
              for(int i=0;i<Lists.length;i++)
              printf("线性表%d:%s\n",i+1,Lists.elem[i].name);
              printf("正在进行添加线性表操作...\n");
              printf("请输入添加线性表名称！");
              scanf("%s",listname);
              if(AddList(Lists,listname)==OK)
                printf("添加成功！");
              else
                printf("添加失败，输入名称与现有名称重复！");
              break;
            case 16:
              //删除线性表
              if(Lists.length==0)
              {
                printf("线性表集中没有线性表，无法完成删除操作！");
                break;
              }
              printf("当前共有%d个线性表\n",Lists.length);
              for(int i=0;i<Lists.length;i++)
              printf("线性表%d:%s\n",i+1,Lists.elem[i].name);
              printf("正在进行删除线性表操作...若删除当前线性表，此后将默认处理第一个线性表\n");
              printf("请输入删除线性表名称！");
              scanf("%s",listname); 
              pos=LocateList(Lists,listname);
              if(pos>0 && pos<cur+1)
                cur--;//如果删除线性表比处理线性表序号更小，需要更新处理线性表序号
              else if(pos==cur+1)
                cur=0;//若删除当前线性表，此后将默认处理第一个线性表
              if(RemoveList(Lists,listname)==OK)
                  printf("删除成功！");               
              else
                printf("删除失败，未找到该线性表！");
              break;
            case 17:
             //查找指定线性表
              printf("正在进行查找线性表操作...\n");
              printf("请输入查找线性表名称！");
              scanf("%s",listname); 
              if(LocateList(Lists,listname)>0)
                printf("该线性表位置序号为%d",LocateList(Lists,listname));
              else 
                printf("该线性表不存在于线性表集中或未初始化！");            
              break;
            case 18:
             //更换操作线性表
             if(Lists.length==0)
             {
               printf("线性表集中没有线性表，无法完成操作！");
               break;
             }
             printf("正在进行更换操作线性表操作...\n");
             printf("请输入想要操作的线性表名称：");
             scanf("%s",listname);
             if(LocateList(Lists,listname)==0)
                printf("该线性表不存在于线性表集中！");
             else
             {
                cur=LocateList(Lists,listname)-1;
                printf("定位成功！");
             }
             break;
            case 19:
              //翻转链表
                if(reverseList(Lists.elem[cur].L)==INFEASIBLE)
					        printf("线性表不存在或为空！");
				        else
					        printf("翻转成功！");
				        break; 
            case 20:
              //删除倒数第n个结点
              if(Lists.elem[cur].L==NULL||ListEmpty(Lists.elem[cur].L))
                printf("线性表不存在或为空！");
              else
              {
                printf("正在进行删除结点操作...\n");
                printf("请输入要删除结点序号（倒序）：");
                scanf("%d",&pos);
                res=RemoveNthFromEnd(Lists.elem[cur].L,pos);
                if(res==ERROR)
                {
                  printf("删除失败，请检查下标值是否合法\n");
                }
                else 
                  printf("删除结点成功！");
              }
              break;
			        case 21:
				        //从小到大排序
				        if( sortList(Lists.elem[cur].L)==INFEASIBLE )
					        printf("线性表不存在或为空！");
				        else
					        printf("排序成功！");
				        break; 
            default:
              //输入op错误
              printf("请输入正确的选项！");
 
        }
        if(op!=0)
        {
            printf("\n\n按任意键进行下一个操作\n\n");
            system("pause");
        }
    }
    printf("已经退出程序!");
    return 0;
}
/***************************************************************
*函数名称：IntitList
*函数功能：实现线性表的初始化
*功能说明：如果线性表L不存在，操作结果是构造一个空的线性表，返回OK，否则返回INFEASIBLE。
****************************************************************/
status InitList(LinkList &L)
{
    if(L!=NULL) return INFEASIBLE;
    else 
    {
        L=(LinkList)malloc(sizeof(LNode));
        L->next=NULL;
        return OK;
    }
}
/***************************************************************
*函数名称：DestroyList
*函数功能：实现线性表的销毁
*功能说明：如果线性表L存在，该操作释放线性表的空间，使线性表成为未初始化状态，返回OK；
          否则对于一个未初始的线性表，是不能进行销毁操作的，返回INFEASIBLE。
****************************************************************/
status DestroyList(LinkList &L)
{
    LinkList p;
    if(L==NULL) return INFEASIBLE;
    else
    {
        while(L!=NULL)
        {
            p=L;
            L=L->next;
            free(p);
        }
        return OK;
    }
}
/***************************************************************
*函数名称：ClearList
*函数功能：实现线性表的清空
*功能说明：若线性表L不存在，返回INFEASIBLE。否则清空线性表L，返回OK；
****************************************************************/
status ClearList(LinkList &L)
{
    LinkList p,q;
    if(L==NULL) return INFEASIBLE;
    else
    {
        
        p=L->next;
        while(p!=NULL)
        {
            q=p->next;
            free(p);
            p=q;
        }
        L->next=NULL;
        return OK;
    }

}
/***************************************************************
*函数名称：ListEmpty
*函数功能：实现线性表的判空
*功能说明：若线性表L不存在，则返回INFEASIBLE；若线性表L长度为0，则返回TRUE；不为0则返回FALSE。
****************************************************************/
status ListEmpty(LinkList L)
{
    if(L==NULL) return INFEASIBLE;
    else
    {
        if(L->next==NULL) return TRUE;
        else return FALSE;
    }
}
/***************************************************************
*函数名称：ListLength
*函数功能：实现线性表的求表长
*功能说明：若线性表L不存在，返回INFEASIBLE；否则返回线性表L的长度。
****************************************************************/
int ListLength(LinkList L)
{
    LinkList p;
    int list_length=0;
    if(L==NULL) return INFEASIBLE;
    else
    {
        p=L->next;
        while(p)
        {
            p=p->next;
            list_length++;
        }
        return list_length;
    }
}
/***************************************************************
*函数名称：GetElem
*函数功能：实现线性表第i个元素的获取
*功能说明：若线性表L不存在，返回INFEASIBLE；若i<1或者i超过线性表L的长度，
          则返回ERROR；若获取成功，则将值赋给e，并返回OK。
****************************************************************/
status GetElem(LinkList L,int i,ElemType &e)
{
    int location;
    LinkList p;
    if(L==NULL) return INFEASIBLE;
    else
    {
        if(i<1) return ERROR;
        else
        {
            p=L;
            for(location=0;location<i;location++) 
            {
                p=p->next;
                if(p==NULL) return ERROR;
            }
            e=p->data;
            return OK;
        }
    }
}
/***************************************************************
*函数名称：LocateElem
*函数功能：实现线性表中元素的查找
*功能说明：如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；
        如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE（即-1）。
****************************************************************/
status LocateElem(LinkList L,ElemType e)
{
    int location=1;
    LinkList p;
    if(L==NULL) return INFEASIBLE;
    else
    {
        p=L->next;
        while(p)
        {
            if(p->data==e) return location;
            p=p->next;
            location++;
        }
        return ERROR;
    }
}
/***************************************************************
*函数名称：PriorElem
*函数功能：实现线性表元素前驱的获取
*功能说明：若线性表L不存在，返回INFEASIBLE；若没有找到指定元素e的前驱，
          则查找失败，返回ERROR；若查找成功，则将值赋给pre，并返回OK
****************************************************************/
status PriorElem(LinkList L,ElemType e,ElemType &pre)
{
    LinkList p,q;
    if(L==NULL) return INFEASIBLE;
    else
    {
        p=L;
        q=p->next;
        while(q)
        {
            if(q->data==e&&p!=L)
            {
                pre=p->data;
                return OK;
            }
            p=q;
            q=q->next;
        }
        return ERROR;
    }
}
/***************************************************************
*函数名称：NextElem
*函数功能：实现线性表元素后继的获取
*功能说明：若线性表L不存在，返回INFEASIBLE；若没有找到指定元素e的后继，
          则查找失败，返回ERROR；若查找成功，则将值赋给next，并返回OK
****************************************************************/
status NextElem(LinkList L,ElemType e,ElemType &next)
{
    LinkList p,q;
    if(L==NULL) return INFEASIBLE;
    else
    {
        p=L;
        q=p->next;
        while(q)
        {
            if(p!=L&&p->data==e)
            {
                next=q->data;
                return OK;
            }
            p=q;
            q=q->next;
        }
        return ERROR;
    }
}
/***************************************************************
*函数名称：ListInsert
*函数功能：实现线性表的插入操作
*功能说明：如果线性表L不存在，返回INFEASIBLE；
          否则在线性表L的第i个元素前插入新的元素e，插入成功返回OK，失败返回ERROR
****************************************************************/
status ListInsert(LinkList &L,int i,ElemType e)
{
    LinkList p,q;
    LinkList node;
    int location=0;
    if(L==NULL) return INFEASIBLE;
    else
    {
        if(i<1) return ERROR;
        p=L;
        q=p->next;
        if(q==NULL&&i==1)//表头插入
        {
            node=(LinkList)malloc(sizeof(LNode));
            node->data=e;
            node->next=p->next;
            p->next=node;
            return OK;
        }
        while(q)
        {
            location++;
            if(location==i)
            {
                node=(LinkList)malloc(sizeof(LNode));
                node->data=e;
                node->next=p->next;
                p->next=node;
                return OK;
            }
            p=q;
            q=q->next;
        }
        if(location+1==i)//表尾插入
        {
            node=(LinkList)malloc(sizeof(LNode));
            node->data=e;
            node->next=p->next;
            p->next=node;
            return OK;
        }
        return ERROR;
    }
}
/***************************************************************
*函数名称：ListDelete
*函数功能：实现线性表的删除操作
*功能说明：若线性表L不存在，返回INFEASIBLE；否则删除线性表L的第i个元素，
          若删除成功则将删除的值赋给e并返回OK，若删除失败则返回ERROR
****************************************************************/
status ListDelete(LinkList &L,int i,ElemType &e)
{
    LinkList p,q;
    LinkList node;
    int location=0;
    if(L==NULL) return INFEASIBLE;
    else
    {
        if(i<1) return ERROR;
        p=L;
        q=p->next;
        while(q)
        {
            location++;
            if(location==i)
            {
                e=q->data;
                p->next=q->next;
                free(q);
                return OK;
            }
            p=q;
            q=q->next;
        }
        return ERROR;
    }
}
/***************************************************************
*函数名称：ListTraverse
*函数功能：实现线性表的遍历操作
*功能说明：若线性表L不存在，返回INFEASIBLE；否则输出线性表的每一个元素，并返回OK
****************************************************************/
status ListTraverse(LinkList L)
{
    LinkList p;
    if(L==NULL) return INFEASIBLE;
    else
    {
        p=L->next;
        while(p)
        {
            printf("%d ",p->data);
            p=p->next;
        }
        return OK;
    }
}
/***************************************************************
*函数名称：reverseList
*函数功能：实现线性表的翻转操作
*功能说明：若线性表L不存在，返回INFEASIBLE；否则实现线性表的翻转，并返回OK
****************************************************************/
status reverseList(LinkList &L)
{
   if(L==NULL) return INFEASIBLE;
   else
   {
      LinkList p,q;
      p=L->next;
      L->next=NULL;
      while(p)
      {
        q=p->next;
        p->next=L->next;
        L->next=p;
        p=q;
      }
      return OK;
   }
}
/***************************************************************
*函数名称：RemoveNthFromEnd
*函数功能：删除链表的倒数第n个结点
*功能说明：若线性表L不存在或者为空，返回INFEASIBLE；如果输入的n值无效，则输出ERROR；否则删除该链表的倒数第n个结点，并返回OK
****************************************************************/
status RemoveNthFromEnd(LinkList &L, int n)
{
  int val;
  int len=ListLength(L);
  if(L==NULL||ListEmpty(L)==TRUE) return INFEASIBLE;
  else
  {
    if(n>len||n<1) return ERROR;
    else
    {
      ListDelete(L,len-n+1,val);
      return OK;
    }
  }
} 
/***************************************************************
*函数名称：SaveList
*函数功能：实现线性表的数据元素写入文件操作
*功能说明：如果线性表L不存在，返回INFEASIBLE；
          否则将线性表L的全部元素写入到文件名为FileName的文件中，返回OK
****************************************************************/
status SaveList(LinkList L,char FileName[])
{
    FILE *fp;
    LinkList p;
    if(L==NULL) return INFEASIBLE;
    else
    {
        fp=fopen(FileName,"w");
        p=L->next;
        while(p)
        {
            fprintf(fp,"%d ",p->data);
            p=p->next;
        }
        fclose(fp);
        return OK;
    }
}
/***************************************************************
*函数名称：LoadList
*函数功能：实现文件数据写入线性表操作
*功能说明：如果线性表L存在，表示L中已经有数据，读入数据会覆盖原数据造成数据丢失，
          返回INFEASIBLE；否则将文件名为FileName的数据读入到线性表L中，返回OK。
****************************************************************/
status LoadList(LinkList &L,char FileName[])
{
    FILE *fp;
    LinkList p,q;
    int temp;
    if(L!=NULL) return INFEASIBLE;
    else
    {
        fp=fopen(FileName,"r");
        L=(LinkList)malloc(sizeof(LNode));
        L->next=NULL;
        p=L;
        while(fscanf(fp,"%d",&temp)!=EOF)
        {
            q=(LinkList)malloc(sizeof(LNode));
            q->data=temp;
            q->next=p->next;
            p->next=q;
            p=q;
        }
        return OK;
    }
}
/***************************************************************
*函数名称：AddList
*函数功能：实现增加一个新的线性表
*功能说明：Lists是一个以顺序表形式管理的线性表的集合，
          在集合中增加一个新的空线性表。增加成功返回OK，否则返回ERROR。
****************************************************************/
status AddList(LISTS &Lists,char ListName[])
{
    for(int i=0;i<Lists.length;i++)
    {
        if(strcmp(ListName,Lists.elem[i].name)==0)
        return ERROR;
    }
    Lists.length++;
    strcpy(Lists.elem[Lists.length-1].name,ListName);
    Lists.elem[Lists.length-1].L=NULL;
    InitList(Lists.elem[Lists.length-1].L);
    return OK;
}
/***************************************************************
*函数名称：RemoveList
*函数功能：实现移除一个指定的线性表
*功能说明：Lists是一个以顺序表形式管理的线性表的集合，
          在集合中查找名称为ListName的线性表，有则删除，返回OK，无则返回ERROR。
****************************************************************/
status RemoveList(LISTS &Lists,char ListName[])
{
    int flag=0;
    int index;
    for(int i=0;i<Lists.length;i++)
    {
        if(strcmp(Lists.elem[i].name,ListName)==0)
        {
            flag=1;
            index=i;
            break;
        }
    }
    if(!flag) return ERROR;
    DestroyList(Lists.elem[index].L);
    for(int j=index;j<Lists.length-1;j++)
    {
        strcpy(Lists.elem[j].name,Lists.elem[j+1].name);
        Lists.elem[j].L=Lists.elem[j+1].L;
    }
    Lists.length--;
    return OK;
}
/***************************************************************
*函数名称：LocateList
*函数功能：实现查找一个指定的线性表
*功能说明：Lists是一个以顺序表形式管理的线性表的集合，
          在集合中查找名称为ListName的线性表，有则返回线性表的逻辑序号，无则返回0
****************************************************************/
int LocateList(LISTS Lists,char ListName[])
{
     for(int i=0;i<Lists.length;i++)
    {
        if(strcmp(Lists.elem[i].name,ListName)==0 && Lists.elem[i].L!=NULL)
          return i+1;
    }
    return 0;
}
/*******************************************************************
*函数名称：sortList
*功能：将L由小到大排序
*功能说明：如果线性表不存在返回INFEASIBLE,将线性表元素由小到大排序之后返回OK
********************************************************************/
status sortList(LinkList &L )
{
    LinkList p, q;
    if(!L) return INFEASIBLE;
    else{
        if(L->next==NULL) return ERROR;
        int n = ListLength(L);
        int i, j, temp;
        for(i = 0,p = L -> next; i < n-1; i++,p = p -> next)
        {
            for(j = i + 1,q = p -> next; j < n; j++,q = q -> next)
            {
                if(p -> data > q -> data)
				        {
                    temp = p -> data;
                    p -> data = q -> data;
                    q -> data = temp;
                }
            }
        }
        return OK;
    }
}
