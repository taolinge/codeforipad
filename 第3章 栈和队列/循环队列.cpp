
/********************************循环队列的抽象数据类型ADT定义*****************************************
   ADT Queue {
     数据对象：D= {ai|ai∈ Elemset,(i=1,2,…,n, n≥0)}
     数据关系：R1 = {＜ai-1, ai＞|ai-1,ai∈ D,(i=2,3,…,n)}   约定a1为队头, an为队尾
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

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>引入头文件<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <stdio.h>   //使用了标准库函数 printf(),scanf()
#include <stdlib.h>  //使用了动态内存分配函数 malloc(),free()

//>>>>>>>>>>>>>>>>>>>>>>>>>>>自定义符号常量<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 
 
#define OVERFLOW -2         //内存溢出错误常量
#define OK 1                //表示操作正确的常量 
#define ERROR 0             //表示操作错误的常量
#define MAXQSIZE 100        //队列的最大长度
#define TRUE 1              //表示逻辑为真的常量 
#define FALSE 0             //表示逻辑为假的常量

//>>>>>>>>>>>>>>>>>>>>>>>>>>>自定义数据类型<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef int Status;         //用typedef给int起个别名，也便于程序的维护 
typedef float QElemType;    //用typedef给float起个别名，也便于程序的维护
typedef struct {            //循环队列的C语言描述 

	QElemType *base;        //初始化动态分配存储空间
	int front;              //头指针，若队列不空，指向队头元素 
	int rear; 	            //尾指针，若队列不空，指向队尾元素的下一个位置 
}SqQueue; 
 
//------------------------循环队列的主要操作--------------------------

//>>>>>>>>>>>>>>>>>>>>>>>>1.初始化循环队列<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：InitQueue_Sq
	参数：SqQueue &Q 循环队列引用 
	返回值：状态码，操作成功返回OK 
	作用：构建一个空队列 Q
*/
Status InitQueue_Sq(SqQueue &Q) {
   	
   	//申请内存空间，若失败则提示并退出程序
   	//if(!(Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType))))
   	//相当于以下两行代码：
	//Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType))
	//if(!Q.base)  <=>  if(Q.base == NULL)
	if(!(Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType)))){
		printf("内存分配失败，程序即将退出！\n");
		exit(OVERFLOW);
	}//if
	
	//由于刚申请的空间没有元素入队，所以队列为空 
	//Q.front == Q.rear是队列为空的标志 
	Q.front = Q.rear = 0;
	
	//操作成功 
	printf("循环队列已成功创建！\n");
	return OK;
}//InitQueue_Sq

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>2.销毁循环队列<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：DestoryQueue_Sq
	参数：SqQueue &Q 循环队列引用 
	返回值：状态码，操作成功返回OK 
	作用：销毁循环队列 Q
*/
Status DestoryQueue_Sq(SqQueue &Q) {
	
	//循环队列采用连续的存储空间，直接找到首地址释放空间即可 
	if(Q.base) { 
		free(Q.base);
	}//if
	
	//指针置空，释放掉指针变量本身占用的空间 
	Q.base = NULL;
	
	//队头和队尾指针归零，队列为空 
	Q.front = Q.rear = 0;
	
	//操作成功 
	printf("循环队列已成功销毁！\n");
	return OK;
}//DestoryQueue_Sq

//>>>>>>>>>>>>>>>>>>>>>>3.判断循环队列是否为空<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：QueueEmpty_Sq
	参数：SqQueue Q 循环队列Q 
	返回值：状态码，队列为空返回TRUE，否则返回FALSE 
	作用：判断循环队列 Q是否为空 
*/
Status QueueEmpty_Sq(SqQueue Q) {
	
	//Q.rear == Q.front是队列为空的标志 
	if(Q.rear == Q.front) { 
		return TRUE; 
	}//if 
	else {
		return FALSE;
	}//else  
}//QueueEmpty_Sq

//>>>>>>>>>>>>>>>>>>>>>>>4.获取循环队列的长度<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：QueueLength_Sq
	参数：SqQueue Q 循环队列Q 
	返回值：队列Q中的数据元素个数，即队列长度
	作用：获取队列长度 
*/
int QueueLength_Sq(SqQueue Q) {
	
    //注意：不可以直接用(Q.rear - Q.front) % MAXQSIZE表示队列长度，
	//因为如果Q.rear - Q.front所得数字是负数或者小于MAXQSIZE，
	//则所得结果是不正确的。所以一定要先加上一个MAXQSIZE再做模运算 
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE; 
}//QueueLength_Sq

//>>>>>>>>>>>>>>>>>5.在循环队列中插入元素（入队）<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：EnQueue_Sq
	参数：SqQueue Q 循环队列Q
	      QElemType e 被插入元素e 
	返回值：状态码，操作成功返回OK，否则返回ERROR 
	作用：插入元素e为Q的新的队尾元素e  
*/
Status EnQueue_Sq(SqQueue &Q, QElemType e) {
	
    //由于循环队列使用顺序存储结构，插入时需要判断队列是否满
	//判断队列满的标志：(Q.rear + 1) % MAXQSIZE == Q.front
	if((Q.rear + 1) % MAXQSIZE == Q.front) {  //队列满
	
		//操作失败 
	    return ERROR;
	}//if
	
	//把e插入到队尾 
	Q.base[Q.rear] = e;
	
	//每插入一个新队尾元素，尾指针增一
	Q.rear = (Q.rear + 1) % MAXQSIZE;
	
	//操作成功 
	return OK; 
}//EnQueue_Sq

//>>>>>>>>>>>>>>>>>>6.在循环队列中删除元素（出队）<<<<<<<<<<<<<<<<<<<

/*
	函数：DeQueue_Sq
	参数：SqQueue Q 循环队列Q
	      QElemType &e 带回被删除的元素e 
	返回值：状态码，操作成功返回OK，否则返回ERROR 
	作用：队列不空,则删除Q的队头元素,用e返回其值
*/
Status DeQueue_Sq(SqQueue &Q, QElemType &e) {
	
	//在空队列中执行出队操作没有意义，所以要先判断队列是否为空 
	//if(QueueEmpty_Sq(Q)) <=> if(QueueEmpty_Sq(Q) == TRUE)
	if(QueueEmpty_Sq(Q)) { //队列空 
	    
	    //操作失败 
		return ERROR;
	}//if
	
	//保存被删除元素的值 
	e = Q.base[Q.front];
	
	//每当删除队头元素时，头指针增1 
	Q.front = (Q.front + 1) % MAXQSIZE;
	
	//操作成功 
	return OK; 
}//DeQueue_Sq

//>>>>>>>>>>>>>>>>>>>>>7.置空循环队列<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：ClearQueue_Sq
	参数：SqQueue &Q 循环队列引用 
	返回值：状态码，操作成功返回OK，否则返回ERROR 
	作用：将Q清空 
*/
Status ClearQueue_Sq(SqQueue &Q) {
	
	//队头队尾指针清零 
	Q.front = Q.rear = 0;
	
	//操作成功    
    printf("链队列已清空，长度为：%d\n", QueueLength_Sq(Q));
	return OK; 
}//ClearQueue_Sq

//>>>>>>>>>>>>>>>>>>>>>>>8.遍历整个循环队列<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：Print
	参数：ElemType e 被访问的元素 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：访问元素e的函数，通过修改该函数可以修改元素访问方式，
	      该函数使用时需要配合遍历函数一起使用。 
*/
Status Print(QElemType e){
	
	//采用控制台输出的方式访问每个元素 
	printf("%6.2f    ", e);
	
	//操作成功 
	return OK;
}//Print

/*
	函数：QueueTraverse_Sq
	参数：SqQueue Q 循环链队列Q 
	      Status (* visit)(QElemType) 函数指针，指向元素访问函数。 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：调用元素访问函数按出队顺序完成循环队列的遍历，但并未真正执行出队操作 
*/
Status QueueTraverse_Sq(SqQueue Q, Status (* visit)(QElemType)) {
	
	//依次访问每个元素 
	for(int i = 0; i < QueueLength_Sq(Q); i++) {
		
		//一旦访问失败则遍历失败
		//if(visit(Q.base[i]) != NULL)
		if(!visit(Q.base[i])) {
			return ERROR;
		}//if 
	}//for 
	     
	//操作成功 
	return OK; 
}//QueueTraverse_Sq

//>>>>>>>>>>>>>>>>>>>>>9.获取队头元素的值<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：GetHead_Sq
	参数：SqQueue Q 循环链队列Q 
	      QElemType &e 带回队头元素的值 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：获取队头元素的值并由e带回该值 
*/
Status GetHead_Sq(SqQueue Q, QElemType &e) {
	
	//如果队列为空，则获取不到队头元素的值，所以要先判断队列是否空
	//if(QueueEmpty_Sq(Q)) <=> if(QueueEmpty_Sq(Q) == TRUE) 
	if(QueueEmpty_Sq(Q)) { //队列空
	
		//无法获取队头元素，操作失败 
		return ERROR;
	}//if
	
	//获取队头元素的值并保存到e 
    e = Q.base[Q.front];
    
    //操作成功 
	return OK; 
}//GetHead_Sq

//--------------------------主函数---------------------------------- 
int main(int argc,char *argv[]){
	
	//循环队列Q 
	SqQueue Q;
	
	//临时变量e，用于保存待插入元素，被删除元素和队头元素 
	QElemType e;
	
	//n用于接收从键盘输入的队列长度 
	int n;
	
	printf("\n----------------------------------循环队列-----------------------------------\n"); 
	
	printf("->初始化循环队列\n");
	InitQueue_Sq(Q);
	printf("此时队列长度为：%d\n", QueueLength_Sq(Q));
	
	printf("->测试入队操作");
	printf("您想输入几个元素:");
	scanf("%d", &n);
	printf("请输入所有元素，用空格隔开\n");
	for(int i = 0; i < n; i++){
		scanf("%f", &e);
		EnQueue_Sq(Q, e);
	}//for
	printf("入队后的结果为\n");
	QueueTraverse_Sq(Q, Print);
	printf("\n此时队列长度为：%d\n", QueueLength_Sq(Q));
	
	printf("->测试出队和获取队头操作\n");
	GetHead_Sq(Q, e);
	printf("队头元素为%6.2f\n", e);
    while(!QueueEmpty_Sq(Q)){
		DeQueue_Sq(Q, e);
		printf("元素%6.2f出队  \n", e);
	}//while
	printf("\n此时队列长度为：%d\n", QueueLength_Sq(Q));
	
	printf("->测试销毁队列操作");
    DestoryQueue_Sq(Q);
    
	return 0;
}//main

/* -----------------------------------运行结果------------------------------------- 
	
	----------------------------------循环队列-----------------------------------
	->初始化循环队列
	循环队列已成功创建！
	此时队列长度为：0
	->测试入队操作您想输入几个元素:10
	请输入所有元素，用空格隔开
	2 4 8 9 5 7 6 2 4 1
	入队后的结果为
	  2.00      4.00      8.00      9.00      5.00      7.00      6.00      2.00
	  4.00      1.00    
	此时队列长度为：10
	->测试出队和获取队头操作
	队头元素为  2.00
	元素  2.00出队
	元素  4.00出队
	元素  8.00出队
	元素  9.00出队
	元素  5.00出队
	元素  7.00出队
	元素  6.00出队
	元素  2.00出队
	元素  4.00出队
	元素  1.00出队
	
	此时队列长度为：0
	->测试销毁队列操作循环队列已成功销毁！
	
	--------------------------------
	Process exited with return value 0
	Press any key to continue . . .
*/
