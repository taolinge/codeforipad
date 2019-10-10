
#include <stdio.h>          //使用了标准库函数 printf(),scanf()
#include <stdlib.h>         //使用了动态内存分配函数 malloc(),free()
#define OVERFLOW -2         //内存溢出错误常量
#define OK 1                //表示操作正确的常量 
#define ERROR 0             //表示操作错误的常量 
typedef int Status;         //用typedef给int起个别名，也便于程序的维护
typedef float ElemType;     //用typedef给float起个别名，也便于程序的维护
typedef struct DuLNode{     //双向循环链表的C语言描述 
	ElemType data;          //数据域 
	struct DuLNode * prior; //前驱指针域 
	struct DuLNode * next;  //后继指针域 
}DuLNode,* DuLinkList;

//-------------------------------双向循环链表的主要操作------------------------------------

/*
	函数：MallocList_DL
	参数：DuLinkList &L 双向循环链表头结点的指针 
	返回值：无
	作用：申请结点的内存空间
*/
void MallocList_DL(DuLinkList &L){
	
	/*
		if(!(L = (DuLinkList)malloc(sizeof(DuLNode))))
		相当于以下两行代码：
		L = (DuLinkList)malloc(sizeof(DuLNode))
		if(!L) <=> if(L == NULL) 
	*/
	if(!(L = (DuLinkList)malloc(sizeof(DuLNode)))){
		
		printf("申请内存失败！\n");
		exit(OVERFLOW);            
	}//if
}//MallocList_DL

/*
	函数：InitList_D
	参数：DuLinkList &L 双向循环链表头结点的指针
	      int n 初始化多少个数据节点 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：初始化一个带有n个结点的双向循环链表
*/ 
Status InitList_DL(DuLinkList &L, int n){
	
	//接收从键盘输入的结点数据值 
	ElemType e;
	
	//工作指针p 
	DuLinkList p;
	
	//先申请一个头结点并将其链接在头指针p（p暂时指向头结点）的后面 
	MallocList_DL(p);
	
	//使头指针L指向头结点 
	L = p;
	
	//空的双向循环链表头结点包括一个前驱指针和一个后继指针，且均指向头结点数据域 
    L->prior = L->next = L;
    
    //从键盘接收数据，依次创建每一个数据节点 
	printf("请依次输入每个元素，中间用空格隔开:\n");
	for(int i = 0; i < n; i++){
		
		//从键盘接收元素的值 
		scanf("%f", &e);
		
		//申请一个新的数据节点并将其链接在p指向的结点的后面 
		MallocList_DL(p->next);
		
		//建立p指向结点的后继结点的前驱指针指针域关系 
		p->next->prior = p;
		
		//p指针向后移动 
		p = p->next;
		
		//在新的结点中填入从键盘接收的元素值 
		p->data = e;
	}//for
	
	//使最后一个结点的后继指针域保存头结点的地址 
	p->next = L;
	
	//使头结点的前驱指针域保存双向循环链表尾元结点的地址 
	L->prior = p;
	
	//操作成功 
	return OK;  
}//InitList_DL

/*
	函数：ListIsEmpty_DL
	参数：DuLinkList L 双向循环链表头结点的指针
	返回值：若双向循环链表为空，返回1，否则返回0
	作用：判断双向循环链表L是否为空 
*/ 
int ListIsEmpty_DL(DuLinkList L) {

	//若头结点的前驱指针域和后继指针域都指向头结点自身，说明双向循环链表是空表 
	return L->prior == L->next;  
}//ListIsEmpty_DL

/*
	函数：ListLength
	参数：DuLinkList L 双向循环链表头结点的指针
	返回值：双向循环链表L的表长 
	作用：获得表长 
*/ 
int ListLength(DuLinkList L) {
	
	//i是计数器 
	int i = 0;
	
	//工作指针p指向首元结点 
	DuLinkList p = L->next;
	
	//p没有到头指针说明还没有遍历完整张表 
	while(p != L) {
		i++;
		p = p->next;
	}//while
	
	//返回表长 
	return i;
}//ListLength

/*
	函数：GetElemP_DL
	参数：DuLinkList &L 双向循环链表头结点的指针
	返回值：若找到第i个结点，则返回一个指针指向该节点，否则返回NULL 
	        i为0返回头结点的地址 
	作用：在双向循环链表中查找第i个结点 
*/ 
DuLinkList GetElemP_DL(DuLinkList L, int i) { 
	
	//在空表中查找元素没有意义，所以要先判断双向循环链表是否为空 
	if(ListIsEmpty_DL(L)) {
		printf("双向循环链表中没有元素！\n");
	}//if 
	
	//设置一个工作指针p，指向头结点 
	DuLinkList p = L;
	
	//检查参数i是否合法，即i是否越界
	if(i < 0 || i > ListLength(L) + 1) {
		return NULL; 
	}//if
	
	//找到第i个结点 
	for(int j = 1; j <= i; j++) {
		p = p->next;
	}//for
	
	//返回指向第i个结点的指针 
	return p; 
}//GetElem_DL

/*
	函数：ListInsert_DL
	参数：DuLinkList &L 双向循环链表头结点的指针
	      int i 插入位置i，i的合法值为1 <= i <= 表长 + 1 
		  ElemType e  
	返回值：双向循环链表L的表长 
	作用：在带头结点的双向循环线性表L中第i个位置之前插入元素e
*/ 
Status ListInsert_DL(DuLinkList &L, int i, ElemType e){ 
	
	//检查i的值是否合法，i是否越界 
	if(i < 0){ 
	    printf("您输入的位置i不合法！！！\n");
	    return ERROR;
    }//if
    
    //p是工作指针，s指向被插入的新结点 
	DuLinkList p, s;
	
	//找到第i个元素的位置
	//p = NULL表示没有找到第i个结点，即插入位置不合法
	//if(!(p = GetElemP_DL(L, i)))  相当于以下两行代码：
	//p = GetElemP_DL(L, i);
	//if(!p)  <=>  if(p == NULL) 
	if(!(p = GetElemP_DL(L, i))) { 
	     return ERROR; 
	}//if
	
	//申请一个新的结点作为待插入结点，并使s指向它 
	MallocList_DL(s);
	
	//将e的值填入到新结点的数据域中 
	s->data = e;
	
	//建立s和p的前驱结点的关系 
	s->prior = p->prior;
	
	//建立p的前驱结点和s的关系 
	p->prior->next = s;
	
	//建立p和s的关系 
	s->next = p;
	
	//建立s和p的关系 
	p->prior = s;
	
	//操作成功   
	return OK;
	
}//ListInsert_DL

/*
	函数：ListDelete_DL
	参数：DuLinkList &L 双向循环链表头结点的指针
	      int i 插入位置i，i的合法值为i的合法值为i <= i <= 表长
		  ElemType e  
	返回值：双向循环链表L的表长 
	作用：删除带头结点的双向循环链表L的第i个元素，并用e带回被删除结点的值 
*/  
Status ListDelete_DL(DuLinkList &L, int i, ElemType &e){ 
    
    //对空表做删除操作没有意义，删除操作之前先要判断链表是否为空 
    if(ListIsEmpty_DL(L)) { 
	    printf("双向循环链表中没有元素！\n");
	}//if
	
	//p是工作指针，指向被删除结点 
	DuLinkList p;
	
	//遍历链表找出第i个结点，并且使p指向它，若找不到，p的值为NULL
	//if(!(p = GetElemP_DL(L, i))) 相当于以下两句代码
	//p = GetElemP_DL(L, i)
	//if(!p)  <=>   if(p = NULL)
	if(!(p = GetElemP_DL(L, i))) { 
	   return ERROR;
	}//if
	
	//保存被删除结点的值到e 
	e = p->data;
	
	//将p的前驱结点和p的后继结点连接起来，将p指向的结点从链表中隔离出来 
	p->prior->next = p->next;
	p->next->prior = p->prior;
	
	//释放p指向结点的内存空间 
	free(p);
	
	//操作成功 
	return OK; 
}//ListDelete_DL

/*
	函数：Print
	参数：ElemType e 被访问的元素 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：访问元素e的函数，通过修改该函数可以修改元素访问方式，
	      该函数使用时需要配合遍历函数一起使用。 
*/  
Status Print(ElemType e){  //元素访问函数visit() 
	printf("%6.2f    ",e);
	return OK;
}//Print

/*
	函数：ListTraverse_DL
	参数：LinkList L 单链表L的头指针 
	      Status(* visit)(ElemType) 函数指针，指向元素访问函数。 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：依次对双向循环链表的每个元素调用函数visit ()。一旦visit ()失败，则操作失败。
*/
Status ListTraverse_DL(DuLinkList L, Status (* visit)(ElemType)) {

	//对空表的遍历没有意义 
	if(ListIsEmpty_DL(L)) { 
	    printf("双向循环链表中没有元素！\n");
	}//if
	
	//设置一个工作指针并且使之指向首元结点
	DuLinkList p = L->next;
	
	//遍历整个双向循环链表 
	while(p != L){
		
		//一旦visit ()失败，则操作失败。
		//if(!visit(p->data)) <=>  if(visit(p->data) == ERROR)
		if(!visit(p->data)) {
			printf("输出发生错误！\n");
		}//if 
		
		//p后移
		p = p->next;   
	}//while
	
	//输出换行使控制台输出美观 
	printf("\n");
	
	//操作成功 
	return OK; 
}//ListTraverse_DL

/*
	函数：DestoryList_DL
	参数：LinkList L 单链表L的头指针 
	      Status(* visit)(ElemType) 函数指针，指向元素访问函数。 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：依次对双向循环链表的每个元素调用函数visit ()。一旦visit ()失败，则操作失败。
*/
Status DestoryList_DL(DuLinkList &L){
	
	//工作指针q
	DuLinkList q;
	
	//遍历整个链表，释放全部结点的内存空间 
	while(q != L){
		//逐个释放结点的内存空间直至返回头结点 
		q = L->next;
		free(L);
		L = q;
	}//while
	 
	printf("线性单链表内存释放成功！\n");
	
	//操作成功 
	return OK; 
} //DestoryList_DL 

int main(int argc,char *argv[]){
	
	//双向链表头结点指针L	
    DuLinkList L;
    
	//临时变量，接收从键盘接收的元素的值 
	ElemType e;
	
	//n是双向循环链表元素的个数
	//i是临时变量，用于接收插入和删除的变量 
    int n = 0, i;
    
    printf("\n--------------------------------双向循环链表引用版------------------------------\n");
	
	printf("->初始化双向循环链表L\n");
	printf("您想给双向循环链表L设置多少个元素：");         
	scanf("%d", &n);	 
	InitList_DL(L, n);
    printf("->输出双向循环链表L\n");      
	ListTraverse_DL(L, Print);                       
	
	printf("->您想在双向循环链表L的哪个位置之前插入值？\n");
	scanf("%d", &i);
	printf("->您想在双向循环链表L的该位置之前插入的值为多少？\n");
	scanf("%f", &e);
	ListInsert_DL(L,i,e);
	printf("->执行插入操作后双向循环链表L的所有元素为：\n");      
	ListTraverse_DL(L,Print);                    
	
	printf("->您想在双向循环链表L的哪个位置之前删除值？\n");
	scanf("%d",&i);
	ListDelete_DL(L,i,e);
	printf("->被删除的元素为%6.2f\n",e);
	printf("->执行删除操作后双向循环链表L的所有元素为：\n");       
	ListTraverse_DL(L,Print);
    
	printf("->销毁双向循环链表L：");
	DestoryList_DL(L);  
	
	return 0;	
}
/*  -----------------------------------运行结果-------------------------------------- 


	--------------------------------双向循环链表引用版------------------------------

	->初始化双向循环链表L
	您想给双向循环链表L设置多少个元素：10
	请依次输入每个元素，中间用空格隔开:
	1 45 56 78 54 23 56 89 158 56
	->输出双向循环链表L
	  1.00     45.00     56.00     78.00     54.00     23.00     56.00     89.00
	158.00     56.00
	->您想在双向循环链表L的哪个位置之前插入值？
	11
	->您想在双向循环链表L的该位置之前插入的值为多少？
	23
	->执行插入操作后双向循环链表L的所有元素为：
	  1.00     45.00     56.00     78.00     54.00     23.00     56.00     89.00
	158.00     23.00     56.00
	->您想在双向循环链表L的哪个位置之前删除值？
	1
	->被删除的元素为  1.00
	->执行删除操作后双向循环链表L的所有元素为：
	 45.00     56.00     78.00     54.00     23.00     56.00     89.00    158.00
	 23.00     56.00
	->销毁双向循环链表L：线性单链表内存释放成功！
	
	--------------------------------
	Process exited with return value 0
	Press any key to continue . . .
*/ 
