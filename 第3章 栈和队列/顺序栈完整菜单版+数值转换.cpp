/********************************顺序栈的抽象数据类型ADT定义*****************************************
   ADT Stack 
   {
          数据对象：D ={ai | ai∈Elemset,(i=1,2,…,n, n≥0)}
          数据关系：R1 = {＜ai-1,ai＞|ai-1,ai ∈ D,(i=2,3,…,n)}    
                         约定an为栈顶, a1为栈底。
          基本操作：
                       InitStack(&S)
                          操作结果:构造一个空的栈S。
                       DestroyStack(&S)
                          初始条件: 栈S已经存在。
                          操作结果: 销毁栈S。
                       ClearStack(&S)
                          初始条件: 栈S已经存在。
                          操作结果: 将栈S重置为空栈。
                       StackIsEmpty(S)
                          初始条件: 栈S已经存在。
                          操作结果: 若栈S为空栈，则返回TURE;否则返回FALSE。
                       StackLength(S)
                          初始条件: 栈S已经存在。
                          操作结果: 返回栈S中的数据元素个数。
                       GetTop(S, &e)
                          初始条件: 栈S已经存在且非空。
                          操作结果: 用e返回栈S中栈顶元素的值。
                       Push(&S, e)       //入栈操作
                          初始条件: 栈S已经存在。
                          操作结果: 插入元素e为新的栈顶元素。
                       Pop(&S, &e)       //出栈操作
                          初始条件: 栈S已经存在且非空。
                          操作结果: 删除S的栈顶元素并用e返回其值。
                       StackTraverse(S, visit ())
                          初始条件: 栈S已经存在且非空。
                          操作结果: 从栈底到栈顶依次对S的每个元素调用函数visit ()。一旦visit ()失败，则操作失败。      
    }ADT Stack
    
****************************************************************************************************/

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>引入头文件<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <stdio.h>   //使用了标准库函数 
#include <stdlib.h>  //使用了动态内存分配函数 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>自定义符号常量<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 

#define STACK_INIT_SIZE 100  //存储空间初始分配量 
#define STACKINCREMENT 10    //存储空间分配增量 
#define OVERFLOW -2         //内存溢出错误常量
#define OK 1                //表示操作正确的常量 
#define ERROR 0             //表示操作错误的常量

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>自定义数据类型<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef int Status;       //用typedef给int起个别名，也便于程序的维护 
typedef int SElemType;   //用typedef给int起个别名，也便于程序的维护
typedef struct {     //栈的顺序存储表示 
                      
	SElemType *base;            //栈底指针，在栈构造之前和销毁之后，base的值为NULL 
	SElemType *top;             //栈顶指针
	int stacksize;              //当前已分配的存储空间，以元素为单位 
}SqStack; 
 
//-------------------------------------------顺序栈的主要操作-----------------------------------------

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>1.初始化顺序栈<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 

/*
	函数：InitStack_Sq
	参数：SqStack &S 顺序栈引用  
	返回值：状态码，OK表示操作成功 
	作用：构造一个空的顺序栈 
*/
Status InitStack_Sq(SqStack &S){
	
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
	printf("顺序栈S所需内存已分配成功！\n");
	return OK; 
}//InitStack_Sq

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>2.销毁顺序栈<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：DestoryStack_Sq
	参数：SqStack &S 顺序栈引用  
	返回值：状态码，OK表示操作成功 
	作用：释放顺序栈S所占内存空间 
*/
Status DestoryStack_Sq(SqStack &S){
	
	//栈底指针保存的是顺序栈内存空间的首地址 
	free(S.base);
	
	//操作成功 
	printf("顺序栈内存释放成功！\n"); 
	return OK; 
}//DestoryStack_Sq

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>3.置空顺序栈<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：ClearStack_Sq
	参数：SqStack &S 顺序栈引用  
	返回值：状态码，OK表示操作成功 
	作用：将顺序栈S中的元素清空
*/
Status ClearStack_Sq(SqStack &S){
	
	//只需要重新设置栈顶指针到初始位置，保留现有空间
	//栈顶指针和栈底指针都指向栈底表示此栈是空栈 
	S.top = S.base;
	
	//操作成功 
	return OK; 
}//ClearStack_Sq

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>4.判断顺序栈是否为空<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：StackIsEmpty_Sq
	参数：SqStack S 顺序栈S 
	返回值：若顺序栈S是空栈返回1，否返回0 
	作用：判断顺序栈S是否为空栈
*/
Status StackIsEmpty_Sq(SqStack S){
	
	//栈顶指针和栈底指针都指向栈底表示此栈是空栈 
	return S.top == S.base; 
}//StackIsEmpty_Sq

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>5.获取顺序栈的长度<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：StackLength_Sq
	参数：SqStack S 顺序栈S 
	返回值：若顺序栈S是空栈返回1，否返回0 
	作用：判断顺序栈S是否为空栈
*/
Status StackLength_Sq(SqStack S){
	
	//栈的长度就是栈顶指针和栈底指针之间的元素个数 
	return (S.top - S.base); 
}//StackLength_Sq

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>6.获得栈顶元素的值<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：GetTop
	参数：SqStack S 顺序栈S
	返回值：成功获取顺序栈S栈顶元素的值后返回OK，否则返回ERRROR
	作用：用e返回栈顶元素的值，但是栈顶元素不做出栈操作 
*/
Status GetTop(SqStack S, SElemType &e){
	
	//空栈没有栈顶元素，所以要先判断栈是否为空 
	//注意栈是否为空和栈是否存在不是一个概念，所以不可以用 
	//S.base != NULL判断栈是否为空 
	if(StackIsEmpty_Sq(S)) { 
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

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>7.在顺序栈中插入元素（入栈）<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：ReallocStack_Sq
	参数：SqStack &S 顺序栈S引用 
	返回值：状态码，操作成功返回OK，否则返回ERRROR
	作用：将栈S扩容，每扩容一次，栈的大小增加STACKINCREMENT
*/
Status ReallocStack_Sq(SqStack &S){
	
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
	printf("顺序栈S所需内存已重新分配成功！\n");
	return OK; 
}//ReallocStack_Sq

/*
	函数：Push_Sq
	参数：SqStack &S 顺序栈引用
	      SElemType e 被插入的元素e 
	返回值：成功获取顺序栈S栈顶元素的值后返回OK，否则返回ERRROR
	作用：（入栈、压栈）插入元素e为新的栈顶元素
*/
Status Push_Sq(SqStack &S, SElemType e){ 
	
	//入栈时发现栈满了，就要追加存储空间（扩容） 
	if(S.top - S.base >= S.stacksize) {  
	    
	    //调用扩容函数
		ReallocStack_Sq(S);
	}//if
	
	//插入前，栈顶指针指向当前栈顶元素的下一个位置 
	//将e赋值给栈顶指针所指存储空间（插入元素e），栈顶指针后移
	//*S.top++ = e;  <=>  *(S.top) = e;  S.top++; 
	*S.top++ = e;
	
}//Push_Sq

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>8.在顺序栈中删除元素（出栈）<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：Pop_Sq
	参数：SqStack &S 顺序栈引用
	      SElemType &e 带回被删除的元素值e 
	返回值：删除成功返回OK，否则返回ERRROR
	作用：（出栈，弹栈）若栈不空，则删除S的栈顶元素，用e返回其值
*/
Status Pop_Sq(SqStack &S, SElemType &e){ 
	
	//在空栈中执行出栈操作没有意义，所以要判断栈是否为空
	//注意栈是否为空和栈是否存在不是一个概念，所以不可以用 
	//S.base != NULL判断栈是否为空 
	if(StackIsEmpty_Sq(S)) { 
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

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>9.遍历整个顺序栈<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：Print
	参数：ElemType e 被访问的元素 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：访问元素e的函数，通过修改该函数可以修改元素访问方式，
	      该函数使用时需要配合遍历函数一起使用。 
*/
Status Print(SElemType e){
	printf("%5d  ", e);
	return OK;
}//Print 

/*
	函数：StackTraverse_Sq
	参数：SqStack S 顺序栈S 
	      Status(* visit)(SElemType) 函数指针，指向元素访问函数。 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：调用元素访问函数按出栈顺序完成顺序栈的遍历，但并未真正执行出栈操作 
*/
Status StackTraverse_Sq(SqStack S, Status(* visit)(SElemType)) {
	
	//在空栈中执行遍历操作没有意义，所以要判断栈是否为空
	//注意栈是否为空和栈是否存在不是一个概念，所以不可以用 
	//S.base != NULL判断栈是否为空 
	if(StackIsEmpty_Sq(S)) {
		printf("此栈是空栈"); 
	    return ERROR;
	}//if
	
	//调用元素访问函数依次访问栈中的每个元素
	for(int i = 0; i < StackLength_Sq(S); ++i){
		
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

//-------------------------------------------主函数--------------------------------------------------- 
int main(int argc,char *argv[]){
	SqStack S;
	SElemType e;
	int tmp,tmp1=0,i,n;
	while(1){
		printf("\n*****************************顺序栈完整版测试程序******************************\n");
	    printf("->1.初始化顺序栈S\n");
	    printf("->2.清空顺序栈S\n");
	    printf("->3.输出顺序栈S的所有元素\n");
	    printf("->4.查看栈的长度（元素个数）\n");
	    printf("->5.获得栈顶元素的值\n");
	    printf("->6.在顺序栈中插入元素（入栈）\n");
	    printf("->7.在顺序栈中删除元素（出栈）\n");
	    printf("->8.进位制转换程序\n");
	    printf("->9.销毁顺序栈S\n");
		printf("->10.退出程序\n"); 
	    while(1){
	    	printf("请输入您想要操作的代号：");
	        scanf("%d",&tmp);
		    switch(tmp){
			    case 1:{
			    	 if(tmp1){//若栈已经被初始化并且栈中含有元素
			    	 	printf("顺序栈已经被创建，正在销毁...\n");
			    	 	DestoryStack_Sq(S);
			    	 }//if
				     InitStack_Sq(S);
					 printf("您想为顺序栈S输入几个元素？\n"); 
				     scanf("%d",&n);
				     printf("请输入顺序栈S的所有元素，每个元素用空格隔开：\n");
				     for(i=0;i<n;i++){
				     	scanf("%d",&e);
				     	Push_Sq(S,e);
				     }//for
				     printf("创建后的顺序栈S的结果为：\n");
				     StackTraverse_Sq(S, Print);
				     printf("顺序栈S创建成功！\n");
	                 tmp1=1;
	                 break;
			    }//case 1
			    case 2:{
			    	 if(!tmp1){
			    	 	printf("顺序栈S不存在，您可能还未创建，请在创建(执行操作1)后执行该操作！\n\n");
			    	 	break;
			    	 }//if   
				     ClearStack_Sq(S);
				     printf("栈已清空，长度为%d\n",StackLength_Sq(S));
	                 break;
			    }//case 2
			    case 3:{
			    	 if(!tmp1){
			    	 	printf("顺序栈S不存在，您可能还未创建，请在创建(执行操作1)后执行该操作！\n\n");
			    	 	break;
			    	 }//if
			    	 if(!StackLength_Sq(S)){
			    	 	printf("栈可能已被清空或删光，没有元素可供输出,请初始化后执行操作！\n");
			    	 	break;
			    	 }//if
				     printf("顺序栈S内的全部元素为：\n");
				     StackTraverse_Sq(S, Print);
	                 break;
			    }//case 3
			    case 4:{
			    	 if(!tmp1){
			    	 	printf("顺序栈S不存在，您可能还未创建，请在创建(执行操作1)后执行该操作！\n\n");
			    	 	break;
			    	 }//if
				     printf("顺序栈S的长度为%d\n",StackLength_Sq(S));
	                 break;
			    }//case 4
			    case 5:{	    	 
			    	 if(!tmp1){
			    	 	printf("顺序栈S不存在，您可能还未创建，请在创建(执行操作1)后执行该操作！\n\n");
			    	 	break;
			    	 }//if
			    	 if(!StackLength_Sq(S)){
			    	 	printf("栈可能已被清空或删光，没有元素可供输出,请初始化后执行操作！\n");
			    	 	break;
			    	 }//if
				     if(GetTop(S,e))
					    printf("栈顶元素的值为%5d\n",e);  
	                 break;
			   }//case 5
			   case 6:{
			   	     if(!tmp1){
			    	 	printf("顺序栈S不存在，您可能还未创建，请在创建(执行操作1)后执行该操作！\n\n");
			    	 	break;
			    	 }//if
				     printf("您想为顺序栈S插入几个元素？\n"); 
				     scanf("%d",&n);
				     printf("插入前栈S内的全部元素为：\n");
				     StackTraverse_Sq(S, Print);
				     printf("请依次输入您想插入的所有元素，每个元素用空格隔开：\n");
				     for(i=0;i<n;i++){
				     	scanf("%d",&e);
				     	Push_Sq(S,e);
				     }//for
				     printf("插入后栈S内的全部元素为：\n");
				     StackTraverse_Sq(S, Print);
	                 break;
			   }//case 6
			   case 7:{
			   	     if(!tmp1){
			    	 	printf("顺序栈S不存在，您可能还未创建，请在创建(执行操作1)后执行该操作！\n\n");
			    	 	break;
			    	 }//if
			    	 if(!StackLength_Sq(S)){
			    	 	printf("栈可能已被清空或删光，没有元素可供输出,请初始化后执行操作！\n");
			    	 	break;
			    	 }//if
				     printf("您想在栈中删除几个元素？\n"); 
				     scanf("%d",&n);
				     printf("删除前栈S内的全部元素为：\n");
				     StackTraverse_Sq(S, Print);
				     for(i=0;i<n;i++){
                        Pop_Sq(S,e); 
				     }//for
				     	printf("删除后栈S内的全部元素为：\n");
				        StackTraverse_Sq(S, Print);			        
	                 break;
			   }//case 7
			   case 8:{
			   	     if(!tmp1){
			    	 	free(S.base);
			    	 	break;
			    	 }//if
			    	 int i;
			    	 InitStack_Sq(S);
				     printf("请输入一个十进制整数：\n");
					 scanf("%d",&n);
					 printf("您想把它转化成几进制，请输入一个不超过16的正整数：\n");
					 scanf("%d",&i);
					 if(i<=0||i>16){
					 	printf("您输入的数字不合法\n");
					 	break;
					 }//if
					 while(n){
					 	Push_Sq(S,n%i);
					 	n=n/i;
					 }//while
					 printf("您想要的%d进制数为：",i);
					 while(!StackIsEmpty_Sq(S)){
					 	Pop_Sq(S,e);
					 	switch(e){
					 		case 1:       case 2:       case 3:      case 4:       case 5:
							case 6:       case 7:       case 8:      case 9:
							{           printf("%d",e);   break;  }
							case 10:{   printf("A");      break;  }
							case 11:{   printf("B");      break;  }
							case 12:{   printf("C");      break;  }
							case 13:{   printf("D");      break;  }
							case 14:{   printf("E");      break;  }
							case 15:{   printf("F");      break;  }	
							default :{  printf("程序出现错误！\n"); break;   }
					 	}//switch
					 }//while
					 printf("\n");
					 DestoryStack_Sq(S);
	                 break;
			   }//case 8
			   case 9:{
			   	     if(!tmp1){
			    	 	printf("顺序栈S不存在，您可能还未创建，请在创建(执行操作1)后执行该操作！\n\n");
			    	 	break;
			    	 }//if
				     printf("->销毁顺序栈S："); 
	                 DestoryStack_Sq(S);
	                 tmp1=0;
	                 break;
			   }//case 9
			   case 10:{
	                 printf("程序退出,再见！\n\n");
	                 exit(0);
	                 break;
			   }//case 10
			   default:{
				     printf("您的输入非法，请重新输入！\n\n");
				     break; 
			   }//default
		    }//switch
		    break;  
	    }//while  
	    system("pause"); 
	    system("cls");  //清屏 
		fflush(stdin);  //清空标准输入缓冲区，避免多输入字符（如回车、空格）造成影响 
	}//while 		
	return 0;
}

/*  ---------------------------------  运行结果  ------------------------------------ 

	注：程序中涉及到菜单刷新，这里不再重复截取菜单，只保留输入数据和程序的结果输出 
	
	*****************************顺序栈完整版测试程序******************************
	->1.初始化顺序栈S
	->2.清空顺序栈S
	->3.输出顺序栈S的所有元素
	->4.查看栈的长度（元素个数）
	->5.获得栈顶元素的值
	->6.在顺序栈中插入元素（入栈）
	->7.在顺序栈中删除元素（出栈）
	->8.进位制转换程序
	->9.销毁顺序栈S
	->10.退出程序
	请输入您想要操作的代号：1
	顺序栈S所需内存已分配成功！
	您想为顺序栈S输入几个元素？
	5
	请输入顺序栈S的所有元素，每个元素用空格隔开：
	1 4 5 9 2
	创建后的顺序栈S的结果为：
	    1      4      5      9      2
	顺序栈S创建成功！
	请按任意键继续. . .
	
	请输入您想要操作的代号：3
	顺序栈S内的全部元素为：
	    1      4      5      9      2
	请按任意键继续. . .
	
	请输入您想要操作的代号：4
	顺序栈S的长度为5
	请按任意键继续. . .
	
	请输入您想要操作的代号：5
	栈顶元素的值为    2
	请按任意键继续. . .
	
	请输入您想要操作的代号：6
	您想为顺序栈S插入几个元素？
	2
	插入前栈S内的全部元素为：
	    1      4      5      9      2
	请依次输入您想插入的所有元素，每个元素用空格隔开：
	45 67
	插入后栈S内的全部元素为：
	    1      4      5      9      2     45     67
	请按任意键继续. . .
	
	请输入您想要操作的代号：7
	您想在栈中删除几个元素？
	3
	删除前栈S内的全部元素为：
	    1      4      5      9      2     45     67
	删除后栈S内的全部元素为：
	    1      4      5      9
	请按任意键继续. . .
	
	请输入您想要操作的代号：8
	顺序栈S所需内存已分配成功！
	请输入一个十进制整数：
	45
	您想把它转化成几进制，请输入一个不超过16的正整数：
	16
	您想要的16进制数为：2D
	顺序栈内存释放成功！
	请按任意键继续. . .
	
	请输入您想要操作的代号：2
	栈已清空，长度为0
	请按任意键继续. . .
	请输入您想要操作的代号：3
	栈可能已被清空或删光，没有元素可供输出,请初始化后执行操作！
	请按任意键继续. . .
	
	请输入您想要操作的代号：9
	->销毁顺序栈S：顺序栈内存释放成功！
	请按任意键继续. . .
	
	请输入您想要操作的代号：10
	程序退出,再见！
	
	
	--------------------------------
	Process exited with return value 0
	Press any key to continue . . .

*/
