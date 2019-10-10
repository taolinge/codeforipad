//-------------------栈的顺序存储表示------------------------- 

typedef BiTree SElemType;   //栈的元素为二叉树指针类型 
typedef struct {          //栈的顺序存储表示                        
	SElemType *base;            //栈底指针，在栈构造之前和销毁之后，base的值为NULL 
	SElemType *top;             //栈顶指针
	int stacksize;              //当前已分配的存储空间，以元素为单位 
}Stack; 

//--------------------------栈的相关函数(供非递归后序遍历使用)----------------------------
/*
	函数：InitStack_Sq
	参数：Stack &S 顺序栈引用  
	返回值：状态码，OK表示操作成功 
	作用：构造一个空的顺序栈 
*/
Status InitStack(Stack &S){
	
	//动态申请顺序栈的内存空间，并检查内存空间是否成功分配
	//if(!(S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType))))
	//这句代码相当于以下两行代码：
	//S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	//if(!S.base)  <=>  if(S.base == NULL) 
	if(!(S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType)))){
		printf("内存分配失败，程序即将退出！\n");
		exit(OVERFLOW);
	}//if
	
	//由于刚动态分配完的栈是空栈，所以栈顶指针和栈底指针都指向栈底   
	S.top = S.base;
	
	//栈的大小就是栈的初始化大小参数STACK_INIT_SIZE 
	S.stacksize = STACK_INIT_SIZE;
	
	//操作成功 
	return OK; 
}//InitStack_Sq

/*
	函数：DestoryStack_Sq
	参数：Stack &S 顺序栈引用  
	返回值：状态码，OK表示操作成功 
	作用：释放顺序栈S所占内存空间 
*/
Status DestoryStack(Stack &S){
	
	//栈底指针保存的是顺序栈内存空间的首地址 
	free(S.base);
	
	//操作成功 
	return OK; 
}//DestoryStack_Sq

/*
	函数：StackIsEmpty_Sq
	参数：Stack S 顺序栈S 
	返回值：若顺序栈S是空栈返回1，否返回0 
	作用：判断顺序栈S是否为空栈
*/
Status StackIsEmpty(Stack S){
	
	//栈顶指针和栈底指针都指向栈底表示此栈是空栈 
	return S.top == S.base; 
}//StackIsEmpty_Sq

/*
	函数：ReallocStack_Sq
	参数：Stack &S 顺序栈S引用 
	返回值：状态码，操作成功返回OK，否则返回ERRROR
	作用：将栈S扩容，每扩容一次，栈的大小增加STACKINCREMENT
*/
Status ReallocStack(Stack &S){
	
	//为顺序栈重新分配内存(扩容)，扩展的空间大小是STACKINCREMENT
	/*if(!(S.base = (SElemType *)realloc(S.base, 
	            (STACK_INIT_SIZE + STACKINCREMENT) * sizeof(SElemType))))
	  这句代码相当于：
	  S.base = (SElemType *)realloc(S.base, 
	                    (STACK_INIT_SIZE + STACKINCREMENT) * sizeof(SElemType));
	  if(!S.base) <=> if(S.base == NULL)
	*/
	if(!(S.base = (SElemType *)realloc(S.base, 
	           (STACK_INIT_SIZE + STACKINCREMENT) * sizeof(SElemType)))){
		printf("内存分配失败，程序即将退出！\n");
		exit(OVERFLOW);
	}//if
	
	//由于扩容前栈已经满了，所以栈顶指针位置就是栈底指针+原来栈的大小 
	S.top = S.base + S.stacksize;
	
	//扩容后，栈的大小增加了STACKINCREMENT 
	S.stacksize += STACKINCREMENT;
	
	//操作成功 
	return OK; 
}//ReallocStack_Sq

/*
	函数：Push_Sq
	参数：Stack &S 顺序栈引用
	      SElemType e 被插入的元素e 
	返回值：成功获取顺序栈S栈顶元素的值后返回OK，否则返回ERRROR
	作用：（入栈、压栈）插入元素e为新的栈顶元素
*/
Status Push(Stack &S, SElemType e){ 
	
	//入栈时发现栈满了，就要追加存储空间（扩容） 
	if(S.top - S.base >= S.stacksize) {  
	    
	    //调用扩容函数
		ReallocStack(S);
	}//if
	
	//插入前，栈顶指针指向当前栈顶元素的下一个位置 
	//将e赋值给栈顶指针所指存储空间（插入元素e），栈顶指针后移
	//*S.top++ = e;  <=>  *(S.top) = e;  S.top++; 
	*S.top++ = e;
	
}//Push_Sq

/*
	函数：Pop_Sq
	参数：Stack &S 顺序栈引用
	      SElemType &e 带回被删除的元素值e 
	返回值：删除成功返回OK，否则返回ERRROR
	作用：（出栈，弹栈）若栈不空，则删除S的栈顶元素，用e返回其值
*/
Status Pop(Stack &S, SElemType &e){ 
	
	//在空栈中执行出栈操作没有意义，所以要判断栈是否为空
	//注意栈是否为空和栈是否存在不是一个概念，所以不可以用 
	//S.base != NULL判断栈是否为空 
	if(StackIsEmpty(S)) { 
	     return ERROR;
	}//if
	
	//删除前，栈顶指针指向当前栈顶元素的下一个位置
	//--S.top;之后，栈顶指针刚好指向被删除元素 
	//栈顶指针前移，保存被删除的元素值到e
	//e=*--S.top;  <=>  --S.top;   e=*(S.top);
	e = *--S.top;
	
	//操作成功 
	return OK; 
}//Pop_Sq

/*
	函数：GetTop
	参数：Stack S 顺序栈S
	返回值：成功获取顺序栈S栈顶元素的值后返回OK，否则返回ERRROR
	作用：用e返回栈顶元素的值，但是栈顶元素不做出栈操作 
*/
Status GetTop(Stack S, SElemType &e){
	
	//空栈没有栈顶元素，所以要先判断栈是否为空 
	//注意栈是否为空和栈是否存在不是一个概念，所以不可以用 
	//S.base != NULL判断栈是否为空 
	if(StackIsEmpty(S)) { 
	     return ERROR;
	}//if
	
	//注意：栈顶指针指向栈顶元素的下一个位置
	e = *(S.top - 1);  
	/*   注意：此处不能使用“e = *(--S.top); ”的原因 
		 1. --S.top自减操作改变了栈顶指针本身的指向，使得该指针向前移动一位，相当于删除了原来栈中的最后一个元素（最后一个元素出栈）； 
		 2. S.top-1 仅仅表示栈顶指针的上一个位置，并没有改变S.top的值，*(S.top-1)表示取栈顶指针前一个位置的值，即栈顶元素的值  
		 3. 这两种写法造成的结果是不同的，如果是纯代数运算，两者没有差别,但在指向数组
			（顺序结构在C语言中是用一维数组描述的）的指针变量运算中，这两个表达式有特殊含义 
			在指针运算中，“指针变量-1 ”表示该指针变量所指位置的前一个位置，
			这种做法并不改变指针变量本身的值。 
			--指针变量   不仅使得该指针指向原来所指位置的上一个位置, 还修改了指针变量本身的值
			在栈中，栈顶指针和栈底指针所指向的位置有特殊的含义，故两者不等价。       
	 */ 
	 
	 //操作成功 
	 return OK; 
}//GetTop_Sq

/*
	函数：StackLength_Sq
	参数：Stack S 顺序栈S 
	返回值：若顺序栈S是空栈返回1，否返回0 
	作用：判断顺序栈S是否为空栈
*/
Status StackLength(Stack S){
	
	//栈的长度就是栈顶指针和栈底指针之间的元素个数 
	return (S.top - S.base); 
}//StackLength_Sq

/*
	函数：Print
	参数：ElemType e 被访问的元素 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：访问元素e的函数，通过修改该函数可以修改元素访问方式，
	      该函数使用时需要配合遍历函数一起使用。 
*/
Status Print_Stack(SElemType e){
	printf("%5d  ", e);
	return OK;
}//Print 

/*
	函数：StackTraverse_Sq
	参数：Stack S 顺序栈S 
	      Status(* visit)(SElemType) 函数指针，指向元素访问函数。 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：调用元素访问函数按出栈顺序完成顺序栈的遍历，但并未真正执行出栈操作 
*/
Status StackTraverse(Stack S, Status(* visit)(SElemType)) {
	
	//在空栈中执行遍历操作没有意义，所以要判断栈是否为空
	//注意栈是否为空和栈是否存在不是一个概念，所以不可以用 
	//S.base != NULL判断栈是否为空 
	if(StackIsEmpty(S)) {
		printf("此栈是空栈"); 
	    return ERROR;
	}//if
	
	//调用元素访问函数依次访问栈中的每个元素
	for(int i = 0; i < StackLength(S); ++i){
		
		//调用元素访问函数，一旦访问失败则退出  
		if(!visit(S.base[i])) {
			return ERROR;
		}//if 
	}//for
	
	//输出换行，是控制台显示美观 
	printf("\n");
	
	//操作成功 
	return OK;
}//StackTraverse_Sq
