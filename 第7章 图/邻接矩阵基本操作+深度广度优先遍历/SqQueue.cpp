
//广度优先遍历用到队列的实现 

#define MAXQSIZE 100        //队列的最大长度 
typedef int Status;
typedef int QElemType;

typedef struct {            //循环队列的C语言描述 

	QElemType *base;        //初始化动态分配存储空间
	int front;              //头指针，若队列不空，指向队头元素 
	int rear; 	            //尾指针，若队列不空，指向队尾元素的下一个位置 
}SqQueue; 

//----------------------循环队列的主要操作------------------------

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
	return OK;
}//InitQueue_Sq

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
	return OK;
}//DestoryQueue_Sq

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
