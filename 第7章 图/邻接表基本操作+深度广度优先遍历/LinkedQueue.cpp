//------------------队列的链式存储表示----------------------- 
typedef int QElemType;   //队列元素为二叉树指针类型

typedef struct  QNode{  //链队列的C语言表示                  
	 QElemType data;        //数据域 
	 struct QNode * next;   //指针域 
}QNode,* QueuePtr;

typedef struct{
	QueuePtr front;  //队头指针 
	QueuePtr rear;   //队尾指针 
}Queue; 

//--------------------------队列的相关函数(供非递归层序遍历使用)----------------------------
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
	函数：InitQueue
	参数：Queue &Q 链队列引用 
	返回值：状态码，操作成功返回OK 
	作用：构建一个空队列 Q
*/
Status InitQueue(Queue &Q) {
	
	//申请头结点的内存空间，并使队头和队尾指针同时指向它
	Q.front = Q.rear = MallocQNode();
	
	//由于头结点刚刚初始化，后面还没有元素结点 
	Q.front->next = NULL;
	
	//头结点数据域记录了链队列长度
	//由于此时链队列没有数据节点，所以将头结点数据域设为0 
	Q.front->data = 0;

	//操作成功 
	return OK;
}//InitQueue 

/*
	函数：DestoryQueue
	参数：Queue &Q 链队列引用 
	返回值：状态码，操作成功返回OK 
	作用：销毁队列Q
*/
Status DestoryQueue(Queue &Q){
	
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
	return OK;
}//DestoryQueue

/*
	函数：QueueEmpty
	参数：Queue Q 链队列Q 
	返回值：状态码，若Q为空队列，则返回TRUE;否则返回FALSE
	作用：判断队列Q是否为空 
*/
Status QueueEmpty(Queue Q){
	
	//队头指针和队尾指针均指向链队列头结点表示链队列为空 
	if(Q.rear == Q.front){
		return TRUE; 
	}//if
	else {
		return FALSE; 
	}//else
}//QueueEmpty

/*
	函数：EnQueue
	参数：Queue &Q 链队列Q的引用
	      QElemType e  被插入的元素e 
	返回值：状态码，操作成功后返回OK。 
	作用：插入元素e为Q的新的队尾元素
*/
Status EnQueue(Queue &Q, QElemType e){

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

/*
	函数：DeQueue
	参数：Queue &Q 链队列Q的引用
	      QElemType &e 带回被删除结点的元素e 
	返回值：状态码，操作成功后返回OK。 
	作用：若队列不空,则删除Q的队头元素,用e返回其值
*/
Status DeQueue(Queue &Q, QElemType &e){
	
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

/*
	函数：Print
	参数：ElemType e 被访问的元素 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：访问元素e的函数，通过修改该函数可以修改元素访问方式，
	      该函数使用时需要配合遍历函数一起使用。 
*/
Status Print_Queue(QElemType e){
	
	//指定元素的访问方式是控制台打印输出 
	printf("%6.2f    ",e);
	
	//操作成功 
	return OK;
}//Print

/*
	函数：QueueTraverse
	参数：Queue Q 链队列Q 
	      Status (* visit)(QElemType) 函数指针，指向元素访问函数。 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：调用元素访问函数按出队顺序完成链队列的遍历，但并未真正执行出队操作 
*/
Status QueueTraverse(Queue Q, Status (* visit)(QElemType)) {   
    
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

