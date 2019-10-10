
/********************************链队列的抽象数据类型ADT定义*****************************************
   ADT Queue {
     数据对象：D= {ai|ai∈ Elemset,(i=1,2,…,n, n≥0)}
     数据关系：R1 = {＜ai-1, ai＞|ai-1,ai∈ D,(i=2,3,…,n)}   约定a1为队头, an为队尾, 且第一个结点的数据域用于存放元素个数。
    基本操作：
       1. InitQueue(&Q)
          操作结果:构造一个空的队列Q。
       2. DestroyQueue(&Q)
          初始条件: 队列Q已经存在。
          操作结果: 销毁队列Q。 
       3. ClearQueue (&Q)
          初始条件: 队列Q已经存在。
          操作结果: 将队列Q清为空队列。
       4. QueueEmpty(Q)
          初始条件: 队列Q已经存在。
          操作结果:若Q为空队列，则返回TURE;否则返回FALSE。
       5. QueueLength(Q)
          初始条件:队列Q已经存在。
          操作结果:返回Q中的数据元素个数，即队列长度。
       6. GetHead(Q,&e)
          初始条件:队列Q已经存在且非空。
          操作结果:用e返回队列Q中的队头元素。
       7. EnQueue(&Q,e)        // 入队操作
          初始条件:队列Q已经存在。
          操作结果:插入元素e为新的队尾元素。
       8. DeQueue(&Q,&e)      // 出队操作
          初始条件:队列Q已经存在且非空。
          操作结果:删除Q的队头元素，并用e返回其值。
       9. QueueTraverse(Q,visit())
          初始条件:队列Q已经存在且非空。
          操作结果:从队头到队尾依次对Q的每个元素调用函数visit ()。一旦visit ()失败，则操作失败。
}ADT Queue
    
****************************************************************************************************/

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>引入头文件<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <stdio.h>   //使用了标准库函数 printf(),scanf()
#include <stdlib.h>  //使用了动态内存分配函数 malloc(),free()

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>自定义符号常量<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 
 
#define OVERFLOW -2         //内存溢出错误常量
#define OK 1                //表示操作正确的常量 
#define ERROR 0             //表示操作错误的常量
#define TRUE 1              //表示逻辑为真的常量 
#define FALSE 0             //表示逻辑为假的常量

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>自定义数据类型<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef int Status;       //用typedef给int起个别名，也便于程序的维护 
typedef float QElemType;    //用typedef给float起个别名，也便于程序的维护

typedef struct  QNode{  //链队列的C语言表示                  
	 QElemType data;        //数据域 
	 struct QNode * next;   //指针域 
}QNode,* QueuePtr;

typedef struct{
	QueuePtr front;  //队头指针 
	QueuePtr rear;   //队尾指针 
}LinkQueue; 
 
//---------------------------------链队列的主要操作----------------------------------

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>1.初始化链队列<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：MallocQNode
	参数：无 
	返回值：指向新申请结点的指针 
	作用：为链队列结点申请内存的函数 
*/
QueuePtr MallocQNode(){
	
	//工作指针p，指向新申请的结点 
	QueuePtr p;
	
	//if(!(p = (QueuePtr)malloc(sizeof(QNode))))  相当于以下两行代码： 
	//p = (QueuePtr)malloc(sizeof(QNode));
	//if(!p)  <=>  if(p != NULL) 
	//申请结点的内存空间，若失败则提示并退出程序
	if(!(p = (QueuePtr)malloc(sizeof(QNode)))){
		printf("内存分配失败，程序即将退出！\n");
		exit(OVERFLOW);
	}//if
	
	//返回新申请结点的地址 
	return p;
}//MallocQNode

/*
	函数：InputQueueElem
	参数：LinkQueue &Q 链队列引用 
	返回值：状态码，操作成功返回OK 
	作用：为链队列Q输入n个元素
*/
Status InputQueueElem(LinkQueue &Q){
	
	//工作指针p
	QueuePtr p, q;
	
	//接收从键盘上输入的新的队列结点元素 
	QElemType e; 
	
	//n是队列将要存储元素的个数，也就是队列的长度
	//i是个临时变量，供循环使用 
	int n, i;
	
	//先确定队列中要初始化多少个元素n 
	printf("您想为链队列输入几个元素   ");
	scanf("%d", &n);
	
	//为队列初始化每一个元素 
	printf("请依次输入所有元素，用空格隔开:\n");
	for(i = 0; i < n; i++){
		
		//step1:申请新结点内存空间并使p指向此结点 
		p = MallocQNode();
		scanf("%f", &e);
		
		//step2:从键盘接收元素值并存入新结点的数据域 
		p->data = e;
		
		//step3:将新结点添加到队尾 
        Q.rear->next = p;
        
        //step4:修正尾指针的位置，使尾指针指向p指向的新添加的结点 
		Q.rear = p;
	}//for
	
	//step5:新插入的结点后面没有结点，所以将其设为NULL
	Q.rear->next = NULL;
	
	//step6:将计数器修改为初始化元素的个数 
	Q.front->data = n;
	
	//操作成功 
	return OK;
}//InputQueueElem 

/*
	函数：InitQueue
	参数：LinkQueue &Q 链队列引用 
	返回值：状态码，操作成功返回OK 
	作用：构建一个空队列 Q
*/
Status InitQueue(LinkQueue &Q) {
	
	//申请头结点的内存空间，并使队头和队尾指针同时指向它
	Q.front = Q.rear = MallocQNode();
	
	//由于头结点刚刚初始化，后面还没有元素结点 
	Q.front->next = NULL;
	
	//头结点数据域记录了链队列长度
	//由于此时链队列没有数据节点，所以将头结点数据域设为0 
	Q.front->data = 0;
	
	//从键盘输入队列元素初始化队列 
	InputQueueElem(Q);
	
	//操作成功 
	printf("链队列已成功创建！\n");
	return OK;
}//InitQueue 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>2.销毁链队列<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：DestoryQueue
	参数：LinkQueue &Q 链队列引用 
	返回值：状态码，操作成功返回OK 
	作用：销毁队列Q
*/
Status DestoryQueue(LinkQueue &Q){
	
	//从头结点开始向后逐个释放结点内存空间 
	while(Q.front){ //while(Q.front) <=> while(Q.front != NULL)
		
		//队尾指针指向被删除结点的后继结点 
		Q.rear = Q.front->next;
		
		//释放Q.front指向的被删除结点的空间 
		free(Q.front);
		
		//队头指针后移，指向下一个待删除结点 
		Q.front = Q.rear; 
	}//while
	
	//操作成功 
	printf("链队列已成功销毁！\n");
	return OK;
}//DestoryQueue

//>>>>>>>>>>>>>>>>>>>>>>>>>>>3.判断链队列是否为空<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：QueueEmpty
	参数：LinkQueue Q 链队列Q 
	返回值：状态码，若Q为空队列，则返回TRUE;否则返回FALSE
	作用：判断队列Q是否为空 
*/
Status QueueEmpty(LinkQueue Q){
	
	//队头指针和队尾指针均指向链队列头结点表示链队列为空 
	if(Q.rear == Q.front){
		printf("该队列是空队列！\n");
		return TRUE; 
	}//if
	else {
		return FALSE; 
	}//else
}//QueueEmpty

//>>>>>>>>>>>>>>>>>>>>>>>>>>4.获取链队列的长度<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：QueueLength
	参数：LinkQueue Q 链队列Q 
	返回值：队列Q中的数据元素个数，即队列长度
	作用：获取队列Q长度 
*/
int QueueLength(LinkQueue Q) {   
	
	//队列长度保存在链队列头结点的数据域中 
	return Q.front->data; 
}//QueueLength

//>>>>>>>>>>>>>>>>>>>>5.在链队列中插入元素（入队）<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：EnQueue
	参数：LinkQueue &Q 链队列Q的引用
	      QElemType e  被插入的元素e 
	返回值：状态码，操作成功后返回OK。 
	作用：插入元素e为Q的新的队尾元素
*/
Status EnQueue(LinkQueue &Q, QElemType e){

	//申请一个新的结点，并使p指向这个新结点 
	QueuePtr p = MallocQNode(); 
	
	//将待插入元素e保存到新结点数据域 
	p->data = e;
	
	//由于新结点要插在队尾，后面没有其他结点，所以后继指针域的值为NULL 
	p->next = NULL;
	
	//将新结点链入到队尾 
	//队列要求插入操作只能发生在队尾 
	Q.rear->next = p;
	
	//修正队尾指针，使之指向p所指向的新插入的结点 
	Q.rear = p;
	
	//由于插入一个结点，所以存储在头结点中的队列长度+1 
	Q.front->data++;
	
	//插入操作成功 
	return OK; 
}//EnQueue 

//>>>>>>>>>>>>>>>>>>>>>>>6.在链队列中删除元素（出队）<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：DeQueue
	参数：LinkQueue &Q 链队列Q的引用
	      QElemType &e 带回被删除结点的元素e 
	返回值：状态码，操作成功后返回OK。 
	作用：若队列不空,则删除Q的队头元素,用e返回其值
*/
Status DeQueue(LinkQueue &Q, QElemType &e){
	
	//注意队列为空和队列不存在的区别，队列为空，头结点一定存在，
	//队列不存在时头结点一定不存在
	//对空队列执行出队操作没有意义，出队操作执行前要先检查队列是否为空 
	if(QueueEmpty(Q)) { //if(QueueEmpty(Q)) <=> if(QueueEmpty(Q) != TRUE)
		return ERROR;
	}//if
	
	//工作指针p指向队头第一个结点（不是头结点，是头结点的后继）
	//队列要求删除操作只能发生在队头，所以p指向的就是待删除节点 
	QueuePtr p = Q.front->next;
	
	//保存被删除结点的值 
	e = p->data;
	
	//在删除操作执行前修正队头指针的位置，使之在删除结点后指向新的队头结点 
	Q.front->next = p->next;
	
	//若被删除结点恰好是队尾结点，那么该结点被删除后，队列将会变成空队列
	//此时刚好满足空队列条件：Q.rear == Q.front，所以要修正队尾指针的位置，使之指向头结点 
	if(Q.rear == p) { 
	    Q.rear = Q.front;
	}//if
	
	//在队头指针和队尾指针的位置都调整好了之后就可以
	//放心地释放p指向的结点的内存空间了 
	free(p);
	
	//由于从队列中删除了一个结点，头结点存储的队列长度应当-1 
	Q.front->data--;
	
	//操作成功 
	return OK; 
}//DeQueue

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>7.置空链队列<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：ClearQueue
	参数：LinkQueue &Q 链队列Q的引用
	返回值：状态码，操作成功后返回OK。 
	作用：若队列不空,则清空Q
*/
Status ClearQueue(LinkQueue &Q){
	
	//清空、删除（出队）和销毁的区别和联系：
	//联系：三者都存在释放内存空间的操作，且清空和销毁操作会导致
	//      队列中所有存储数据的结点内存空间均被释放 
	//区别：清空操作只释放数据结点的内存空间，不影响头结点。
	//      但是销毁操作会在释放数据结点空间时一并释放掉头结点的内存空间。
	//      删除操作只能删除头结点外的数据结点，并且一次只可以删除一个结点。
	//      另外，只有删除操作可以带回被删除元素的值，另外两种操作不能。 
	
	//对空队列进行清空操作没有意义，所以要先判断队列是否为空 
	//注意队列为空和队列不存在的区别，队列为空，头结点一定存在，
	//队列不存在时头结点一定不存在 
	if(QueueEmpty(Q)) { //if(QueueEmpty(Q)) <=> if(QueueEmpty(Q) != TRUE)
		return ERROR;
	}//if
	
	//工作指针p指向队头结点（不是头结点），q是临时变量 
	QueuePtr p = Q.front->next, q;
	
	//从队头依次删除每个结点 
    while(p){ //while(p)  <=>  while(p != NULL)
    	
    	//使得q指向p指向结点的后继结点 
    	q = p->next;
    	
    	//释放掉p指向结点的空间 
    	free(p);
    	
    	//p向后移动，指向被删除结点的后继结点，该结点成为新的删除目标 
		p = q; 
    }//while
    
    //队列清空后头结点后面没有结点 
    Q.front->next = NULL; 
    
    //此时队列为空队列，所以队头指针和队尾指针都指向头结点 
    Q.rear = Q.front;
    
    //由于队列中的数据节点被清空，所以头结点存储的队列长度清零 
    Q.front->data = 0;
	
	//队列清空操作成功  
    printf("链队列已清空，长度为：%d\n",QueueLength(Q));
	return OK; 
}//ClearQueue 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>8.遍历整个链队列<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：Print
	参数：ElemType e 被访问的元素 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：访问元素e的函数，通过修改该函数可以修改元素访问方式，
	      该函数使用时需要配合遍历函数一起使用。 
*/
Status Print(QElemType e){
	
	//指定元素的访问方式是控制台打印输出 
	printf("%6.2f    ",e);
	
	//操作成功 
	return OK;
}//Print

/*
	函数：QueueTraverse
	参数：LinkQueue Q 链队列Q 
	      Status (* visit)(QElemType) 函数指针，指向元素访问函数。 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：调用元素访问函数按出队顺序完成链队列的遍历，但并未真正执行出队操作 
*/
Status QueueTraverse(LinkQueue Q, Status (* visit)(QElemType)) {   
    
    //对空队列进行遍历操作没有意义，所以遍历操作前要先判断队列是否为空 
    //注意队列为空和队列不存在的区别，队列为空，头结点一定存在，
	//队列不存在时头结点一定不存在  
	if(QueueEmpty(Q)) { //if(QueueEmpty(Q)) <=> if(QueueEmpty(Q) != TRUE)
	    return ERROR;
	}//if
	
	//工作指针p指向队头结点 
	QueuePtr p = Q.front->next;
	
	//从队头结点开始依次访问每个结点，直到队尾 
	while(p) { //while(p)  <=>  while(p != NULL) 
	
		//调用元素访问函数 
		if(!visit(p->data)) { 
			printf("输出发生错误！\n");
			return ERROR;
		}//if
		
		//工作指针p后移，指向下一个元素 
		p = p->next;
	}//while
	
	//输出换行，使结果清楚美观 
	printf("\n");
	
	//操作成功 
	return OK; 
}//QueueTraverse

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>9.获取队头元素的值<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：GetHead
	参数：LinkQueue Q 链队列Q 
	      QElemType &e 带回队头元素的值 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：获取队列Q的队头结点元素值，并用e返回该值，此操作不会导致出队操作 
*/
Status GetHead(LinkQueue Q, QElemType &e){
	
	//对空队列进行获取队头操作没有意义，所以操作前要先判断队列是否为空 
    //注意队列为空和队列不存在的区别，队列为空，头结点一定存在，
	//队列不存在时头结点一定不存在  
	if(QueueEmpty(Q)) { //if(QueueEmpty(Q)) <=> if(QueueEmpty(Q) != TRUE)
	    return ERROR;
	}//if
	
	//保存队头结点元素的值
	//Q.front->next指示的是头结点后面的队头结点 
	e = Q.front->next->data;
	
	//操作成功 
	return OK; 
}//GetHead

//-------------------------------------------主函数--------------------------------------------------- 
int main(int argc,char *argv[]){
	
	LinkQueue Q; 
	QElemType e;
	int tmp, tmp1 = 0, i, n;
	while(1){
		printf("\n***************************链队列完整引用版测试程序****************************\n");
	    printf("->1.初始化链队列Q\n");
	    printf("->2.清空链队列Q\n");
	    printf("->3.输出链队列Q的所有元素（遍历）\n");
	    printf("->4.查看链队列的长度（元素个数）\n");
	    printf("->5.获得队头元素的值\n");
	    printf("->6.在链队列中插入一个元素（入队）\n");
	    printf("->7.在链队列中删除一个元素（出队）\n");
	    printf("->8.销毁链队列Q\n");
		printf("->9.退出程序\n"); 
	    while(1){
	    	printf("请输入您想要操作的代号：");
	        scanf("%d", &tmp);
		    switch(tmp){
			    case 1:{
			    	 if(tmp1){ //if(tmp1) <=> if(tmp1 != 0)
			    	 	printf("链队列Q已存在，且含有元素，队列销毁中...\n");
			    	 	DestoryQueue(Q); 
			    	 }//if 
			    	 printf("->初始化链队列Q\n"); 
				     InitQueue(Q);
				     printf("初始化后的链队列包含以下元素：\n");
				     QueueTraverse(Q, Print);
	                 tmp1 = 1;
	                 break;
			    }//case-1
			    case 2:{
			    	 if(!tmp1){ //if(!tmp1) <=> if(tmp1 == 0)
			    	 	printf("链队列Q不存在，您可能还未创建，请在创建(执行操作1)后执行该操作！\n\n");
			    	 	break;
			    	 }//if 
				     printf("->清空链队列Q\n");
				     ClearQueue(Q); 
	                 break;
			    }//case-2
			    case 3:{
			    	 if(!tmp1){ //if(!tmp1) <=> if(tmp1 == 0)
			    	 	printf("链队列Q不存在，您可能还未创建，请在创建(执行操作1)后执行该操作！\n\n");
			    	 	break;
			    	 }//if
				     printf("->链队列Q的所有元素为：\n");
				     QueueTraverse(Q, Print);
	                 break;
			    }//case-3
			    case 4:{
			    	 if(!tmp1){ //if(!tmp1) <=> if(tmp1 == 0)
			    	 	printf("链队列Q不存在，您可能还未创建，请在创建(执行操作1)后执行该操作！\n\n");
			    	 	break;
			    	 }//if
				     printf("链队列Q的长度为%d\n", QueueLength(Q));
	                 break;
			    }//case-4
			    case 5:{ 
			    	 if(!tmp1){ //if(!tmp1) <=> if(tmp1 == 0)
			    	 	printf("链队列Q不存在，您可能还未创建，请在创建(执行操作1)后执行该操作！\n\n");
			    	 	break;
			    	 }//if
				     i = GetHead(Q, e);
				     if(i) { //if(i) <=> if(i != ERROR)
				     	printf("队头元素的值为%6.2f\n", e);
				     }//if 
				     else {
				        printf("队列可能已被清空或被删光元素，此时不存在队头元素！\n");
				     }//else
	                 break;
			   }//case-5
			   case 6:{
			   	     if(!tmp1){ //if(!tmp1) <=> if(tmp1 == 0)
			    	 	printf("链队列Q不存在，您可能还未创建，请在创建(执行操作1)后执行该操作！\n\n");
			    	 	break;
			    	 }//if
				     printf("->对Q执行入队操作\n");
				     printf("您想在队列中插入的元素是：");
				     scanf("%f", &e);
				     EnQueue(Q, e);
				     printf("元素入队后队列为\n");
				     QueueTraverse(Q, Print);
	                 break;
			   }//case-6
			   case 7:{
			   	     if(!tmp1){ //if(!tmp1) <=> if(tmp1 == 0)
			    	 	printf("链队列Q不存在，您可能还未创建，请在创建(执行操作1)后执行该操作！\n\n");
			    	 	break;
			    	 }//if
				     printf("->对Q执行出队操作\n");
				     i = DeQueue(Q, e);
				     if(i){ //if(i) <=> if(i != ERROR)
				     	printf("出队的元素是%6.2f \n", e);
				        printf("元素出队后队列为\n");
				        QueueTraverse(Q, Print);
				     }//if
				     else {
				     	printf("队列可能已被清空或被删光元素，此时没有元素可以出队！\n");
				     }//else 
	                 break;
			   }//case-7
			   case 8:{
			   	     if(!tmp1){ //if(!tmp1) <=> if(tmp1 == 0)
			    	 	printf("链队列Q不存在，您可能还未创建，请在创建(执行操作1)后执行该操作！\n\n");
			    	 	break;
			    	 }//if
			    	 printf("->销毁链队列Q\n"); 
			    	 DestoryQueue(Q); 
			    	 tmp1 = 0;
	                 break;
			   }//case-8
			   case 9:{
	                 printf("程序退出,再见！\n\n");
	                 exit(0);
	                 break;
			   }//case-9
			   default:{
				     printf("您的输入非法，请重新输入！\n\n");
				     break; 
			   }//default
		    }//switch 
		    break;
	    }//while
		system("PAUSE");
		system("cls");  
	}//while 		
	return 0;
}//main

/* ----------------------------------运行结果------------------------------------- 
	
	***************************链队列完整引用版测试程序****************************
	->1.初始化链队列Q
	->2.清空链队列Q
	->3.输出链队列Q的所有元素（遍历）
	->4.查看链队列的长度（元素个数）
	->5.获得队头元素的值
	->6.在链队列中插入一个元素（入队）
	->7.在链队列中删除一个元素（出队）
	->8.销毁链队列Q
	->9.退出程序
	请输入您想要操作的代号：1
	->初始化链队列Q
	您想为链队列输入几个元素   10
	请依次输入所有元素，用空格隔开:
	2 45 6 98 4 23 5 9 8 49
	链队列已成功创建！
	初始化后的链队列包含以下元素：
	  2.00     45.00      6.00     98.00      4.00     23.00      5.00      9.00
	  8.00     49.00
	请按任意键继续. . .
	
	请输入您想要操作的代号：3
	->链队列Q的所有元素为：
	  2.00     45.00      6.00     98.00      4.00     23.00      5.00      9.00
	  8.00     49.00
	请按任意键继续. . .
	
	请输入您想要操作的代号：4
	链队列Q的长度为10
	请按任意键继续. . .
	
	请输入您想要操作的代号：5
	队头元素的值为  2.00
	请按任意键继续. . .
	
	请输入您想要操作的代号：6
	->对Q执行入队操作
	您想在队列中插入的元素是：69
	元素入队后队列为
	  2.00     45.00      6.00     98.00      4.00     23.00      5.00      9.00
	  8.00     49.00     69.00
	请按任意键继续. . .
	
	请输入您想要操作的代号：7
	->对Q执行出队操作
	出队的元素是  2.00 
	元素出队后队列为
	 45.00      6.00     98.00      4.00     23.00      5.00      9.00      8.00
	 49.00     69.00
	请按任意键继续. . .
	
	请输入您想要操作的代号：2
	->清空链队列Q
	链队列已清空，长度为：0
	请按任意键继续. . .
	
	请输入您想要操作的代号：3
	->链队列Q的所有元素为：
	该队列是空队列！
	请按任意键继续. . .
	
	请输入您想要操作的代号：4
	链队列Q的长度为0
	请按任意键继续. . .
	
	请输入您想要操作的代号：8
	->销毁链队列Q
	链队列已成功销毁！
	请按任意键继续. . .

	请输入您想要操作的代号：9
	程序退出,再见！
	
	
	--------------------------------
	Process exited with return value 0
	Press any key to continue . . .
*/ 
