
/***************************二叉树的抽象数据类型ADT定义**************************** 
	ADT BinaryTree{
	数据对象D：D是具有相同特性的数据元素的集合。
	数据关系R：
	  若D=Φ，则R=Φ，称BinaryTree为空二叉树；
	  若D≠Φ，则R={H}，H是如下二元关系；
	    （1）在D中存在惟一的称为根的数据元素root，它在关系H下无前驱；
	    （2）若D-{root}≠Φ，则存在D-{root}={D1,Dr}，且D1∩Dr =Φ；
	    （3）若D1≠Φ，则D1中存在惟一的元素x1，<root,x1>∈H，且存在D1上的关系H1 ?H；
		     若Dr≠Φ，则Dr中存在惟一的元素xr，<root,xr>∈H，且存在Dr上的关系Hr ?H；
			 H={<root,x1>,<root,xr>,H1,Hr}；
	    （4）(D1,{H1})是一棵符合本定义的二叉树，称为根的左子树；
		     (Dr,{Hr})是一棵符合本定义的二叉树，称为根的右子树。
	基本操作：
		  InitBiTree( &T )
		    操作结果：构造空二叉树T。
		  DestroyBiTree( &T )
		    初始条件：二叉树T已存在。
		    操作结果：销毁二叉树T。
		  CreateBiTree( &T, definition )
		    初始条件：definition给出二叉树T的定义。
		    操作结果：按definiton构造二叉树T。
		  ClearBiTree( &T )
		    初始条件：二叉树T存在。
		    操作结果：将二叉树T清为空树。
		  BiTreeEmpty( T )
		    初始条件：二叉树T存在。
		    操作结果：若T为空二叉树，则返回TRUE，否则返回FALSE。
		  BiTreeDepth( T )
		    初始条件：二叉树T存在。
		    操作结果：返回T的深度。
		  Root( T )
		    初始条件：二叉树T存在。
		    操作结果：返回T的根。
		  Value( T, e )
		    初始条件：二叉树T存在，e是T中某个结点。
		    操作结果：返回e的值。
		  Assign( T, &e, value )
		    初始条件：二叉树T存在，e是T中某个结点。
		    操作结果：结点e赋值为value。
		  Parent( T, e )
		    初始条件：二叉树T存在，e是T中某个结点。
		    操作结果：若e是T的非根结点，则返回它的双亲，否则返回“空”。
		  LeftChild( T, e )
		    初始条件：二叉树T存在，e是T中某个结点。
		    操作结果：返回e的左孩子。若e无左孩子，则返回“空”。
		  RightChild( T, e )
		    初始条件：二叉树T存在，e是T中某个结点。
		    操作结果：返回e的右孩子。若e无右孩子，则返回“空”。
		  LeftSibling( T, e )
		    初始条件：二叉树T存在，e是T中某个结点。
		    操作结果：返回e的左兄弟。若e是T的左孩子或无左兄弟，则返回“空”。
		  RightSibling( T, e )
		    初始条件：二叉树T存在，e是T中某个结点。
		    操作结果：返回e的右兄弟。若e是T的右孩子或无右兄弟，则返回“空”。
		  InsertChild( T, p, LR, c )
		    初始条件：二叉树T存在，p指向T中某个结点，LR为0或1，非空二叉树c与T不相交且右子树为空。
		    操作结果：根据LR为0或1，插入c为T中p所指结点的左或右子树。p所指结点的原有左或右子树则成为c的右子树。
		  DeleteChild( T, p, LR )
		    初始条件：二叉树T存在，p指向T中某个结点，LR为0或1。
		    操作结果：根据LR为0或1，删除T中p所指结点的左或右子树。
		  PreOrderTraverse( T, visit() )
		    初始条件：二叉树T存在，Visit是对结点操作的应用函数。
		    操作结果：先序遍历T，对每个结点调用函数Visit一次且仅一次。一旦visit()失败，则操作失败。
		  InOrderTraverse( T, visit() )
		    初始条件：二叉树T存在，Visit是对结点操作的应用函数。
		    操作结果：中序遍历T，对每个结点调用函数Visit一次且仅一次。一旦visit()失败，则操作失败。
		  PostOrderTraverse( T, visit() )
		    初始条件：二叉树T存在，Visit是对结点操作的应用函数。
		    操作结果：后序遍历T，对每个结点调用函数Visit一次且仅一次。一旦visit()失败，则操作失败。
		  LevelOrderTraverse( T, visit() )
		    初始条件：二叉树T存在，Visit是对结点操作的应用函数。
		    操作结果：层次遍历T，对每个结点调用函数Visit一次且仅一次。一旦visit()失败，则操作失败。
	}ADT BinaryTree
*/ 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>引入头文件<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <stdio.h>       //使用了标准库函数 
#include <stdlib.h>      //使用了动态内存分配函数 

//>>>>>>>>>>>>>>>>>>>>>>>>>自定义符号常量<<<<<<<<<<<<<<<<<<<<<<<<<<<< 

#define STACK_INIT_SIZE 50   //顺序栈存储空间初始分配量 
#define STACKINCREMENT 10    //顺序栈存储空间分配增量  
#define OVERFLOW -2          //内存溢出错误常量
#define OK 1                 //表示操作正确的常量 
#define ERROR 0              //表示操作错误的常量
#define TRUE 1               //表示逻辑真的常量 
#define FALSE 0              //表示逻辑假的常量

//>>>>>>>>>>>>>>>>>>>>>>>>>自定义数据类型<<<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef int  Status;      //状态码为int类型，用于保存操作结果（1成功0失败） 
typedef char TElemType;   //二叉树节点数据域的元素类型 

//----------------二叉树的二叉链表存储表示-------------------- 
typedef struct BiNode{
	TElemType  data;
	struct BiNode  *lchild,*rchild;   //孩子结点指针 
}BiNode,*BiTree;

//--------引入栈和队列的实现（实际上应该放在头部，由于编译原因，只好这样了）---------------- 
#include "Queue.cpp"     //引入队列的实现 
#include "Stack.cpp"     //引入栈的实现 
 
//---------------------二叉树的主要操作--------------------------

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>1.构造二叉树<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 

/*
	函数：CreateBiTree
	参数：BiTree &T 二叉树引用 
	返回值：状态码，操作成功返回OK，否则返回ERROR 
	作用：按先序次序输入二叉树中结点的值（一个字符），空格字符表示空树，
	      递归的构造二叉链表表示二叉树T
*/
Status CreateBiTree(BiTree &T){  //按先序序列构造二叉树 
	
	//ch存储从键盘接收的字符 
	char ch;
	
	//从键盘接收字符 
	ch = getchar();
	
	//判断输入的字符是否是空格 
	if(ch == ' ') { //输入空格表示结点为空 
		T = NULL;
	}//if 
	else{ //不是空格，按正常结点对待
	
		//申请结点空间
		//if(!(T = (BiNode *)malloc(sizeof(BiNode))))
		//等效于以下两行代码
		//T = (BiNode *)malloc(sizeof(BiNode));
		//if(!(T = (BiNode *)malloc(sizeof(BiNode)))) 
		if(!(T = (BiNode *)malloc(sizeof(BiNode)))){
			printf("内存分配失败！\n");
			exit(OVERFLOW); 
		}//if
		
		//生成根结点
		T->data = ch;
		
		//递归的构建左子树      
		CreateBiTree(T->lchild);
		
		//递归的构建右子树 
		CreateBiTree(T->rchild);
	}//else
	
	//操作成功 
	return OK; 
}//CreateBiTree

//>>>>>>>>>>>>>>>>>>>>2.二叉树的遍历（4种方法）<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：Print
	参数：TElemType e 被访问的元素 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：访问元素e的函数，通过修改该函数可以修改元素访问方式，
	      该函数使用时需要配合遍历函数一起使用。 
*/
Status PrintElement(TElemType e) {
	
	//采用控制台输出的方式访问元素 
	printf(" %c ", e);
	
	//操作成功 
	return OK;
}//PrintElement

//------------------------递归算法----------------------------- 

/*
	函数：PreOrderTraverse
	参数：BiTree T 二叉树T
	      Status(* Visit)(TElemType) 函数指针，指向元素访问函数 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：采用二叉链表存储结构，Visit是对数据元素操作的应用函数
	      先序遍历二叉树T的递归算法，对每个数据元素调用函数Visit 
*/
Status PreOrderTraverse(BiTree T, Status(* Visit)(TElemType)){
   
   	//根节点存在 
   	//if(T) <=> if(T != NULL)
	if(T){
		
		//1.访问根结点
		//if(Visit(T->data)) <=> if(Visit(T->data) != ERROR)
		if(Visit(T->data)) {
			
			//2.访问左孩子（左子树） 
			if(PreOrderTraverse(T->lchild, Visit)) {
				
				//3.访问右孩子（访问右子树） 
				if(PreOrderTraverse(T->rchild, Visit)) {
					return OK;
				}//if 
			}//if
		}//if
		
		return ERROR;
	}//if
	else { 
		return OK;
	}//else 
}//PreOrderTraverse

/*
	函数：InOrderTraverse
	参数：BiTree T 二叉树T
	      Status(* Visit)(TElemType) 函数指针，指向元素访问函数 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：采用二叉链表存储结构，Visit是对数据元素操作的应用函数
	      中序遍历二叉树T的递归算法，对每个数据元素调用函数Visit 
*/
Status InOrderTraverse(BiTree T, Status(* Visit)(TElemType)){
    
    //根节点存在 
	if(T){	//if(T)  <=>  if(T != NULL)
		
		//1.访问左子树 
		if(InOrderTraverse(T->lchild,Visit)) {
			
			//2.访问根节点 
			//if(Visit(T->data)) <=> if(Visit(T->data) != ERROR)
			if(Visit(T->data)) {
				
				//3.访问右子树 
		    	if(InOrderTraverse(T->rchild,Visit)) {
		    		
		        	return OK;
		        }//if
		    }//if 
		}//if 
		
		return ERROR;
	}//if
	else {
		return OK;
	}//else 
}//InOrderTraverse 

/*
	函数：PostOrderTraverse
	参数：BiTree T 二叉树T
	      Status(* Visit)(TElemType) 函数指针，指向元素访问函数 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：采用二叉链表存储结构，Visit是对数据元素操作的应用函数
	      后序遍历二叉树T的递归算法，对每个数据元素调用函数Visit 
*/
Status PostOrderTraverse(BiTree T, Status(* Visit)(TElemType)){
    
    //根结点存在 
	if(T){	//if(T)  <=>  if(T != NULL)
	
		//1.访问左子树 
		if(PostOrderTraverse(T->lchild, Visit)) {
			
			//2.访问右子树 
		    if(PostOrderTraverse(T->rchild, Visit)) {
		        
				//3.访问根结点 
				//if(Visit(T->data)) <=> if(Visit(T->data) != ERROR)
				if(Visit(T->data)) {
					return OK;
				}//if
			}//if
		}//if
		
		return ERROR;
	}//if
	else return OK;
}//PostOrderTraverse

//-----------------------非递归遍历算法---------------------------

/*
	函数：PreOrderTraverse1
	参数：BiTree T 二叉树T
	      Status(* Visit)(TElemType) 函数指针，指向元素访问函数 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：采用二叉链表存储结构，Visit是对数据元素操作的应用函数
	      先序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit 
*/
Status PreOrderTraverse1(BiTree T, Status(* Visit)(TElemType)){
    
    //二叉树非递归遍历需要借用栈来保存回溯点 
	Stack S;
	
	//初始化栈 
	InitStack(S);
	
	//工作指针p指向二叉树根结点 
	BiTree p = T;
	
	//遍历继续的条件：工作指针p不为空或栈不为空
	//while(p || !(StackIsEmpty(S))) 
	//<=> while(p != NULL || StackIsEmpty(S) != 1)
	while(p || !(StackIsEmpty(S))){
		
		//根结点存在 
		if(p){

			//1.访问根结点 
			//if(Visit(p->data)) <=> if(Visit(p->data) != ERROR)
			if(!Visit(p->data)) { 
			    return ERROR;
			}//if 
			
			//根指针进栈
			Push(S, p);
			
			//2.遍历左子树
			p = p->lchild;
		}//if
		else{
			//根指针退栈
			Pop(S, p);
			
			//3.遍历右子树
			p = p->rchild;
		}//else
	}//while
	
	//销毁栈
	DestoryStack(S); 
	
	//操作成功 
	return OK;
} //PreOrderTraverse1

/*
	函数：InOrderTraverse1
	参数：BiTree T 二叉树T
	      Status(* Visit)(TElemType) 函数指针，指向元素访问函数 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：采用二叉链表存储结构，Visit是对数据元素操作的应用函数
	      中序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit 
*/
Status InOrderTraverse1(BiTree T, Status(* Visit)(TElemType)){ 
    
    //二叉树非递归遍历需要借用栈来保存回溯点
	Stack S;
	
	//初始化栈 
	InitStack(S);
	
	//工作指针p指向根结点 
	BiTree p = T;
	
	//遍历继续的条件：工作指针p不为空或栈不为空
	//while(p || !(StackIsEmpty(S))) 
	//<=> while(p != NULL || StackIsEmpty(S) != 1)
	while(p || !(StackIsEmpty(S))) {
		
		//根结点不为空 
		if(p){
			
			//根指针进栈
			Push(S, p); 
			
			//1.遍历左子树
			p = p->lchild;
		}//if
		else{
			//根指针退栈
			Pop(S, p);
			
			//2.访问根结点
			//if(Visit(p->data)) <=> if(Visit(p->data) != ERROR)
			if(!Visit(p->data)) {  
			    return ERROR;
			}//if
			
			//3.遍历右子树
			p = p->rchild; 
		}//else
	}//while
	
	//销毁栈
	DestoryStack(S); 
	
	//操作成功 
	return OK;
} //InOrderTraverse1

/*
	函数：PostOrderTraverse1
	参数：BiTree T 二叉树T
	      Status(* Visit)(TElemType) 函数指针，指向元素访问函数 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：采用二叉链表存储结构，Visit是对数据元素操作的应用函数
	      后序遍历二叉树T的非递归算法，对每个数据元素调用函数Visit 
*/
Status PostOrderTraverse1(BiTree T, Status(* Visit)(TElemType)){
    
    //p和q都是工作指针
	//p指向当前遍历的结点，q指向p最近一次遍历的结点 
	BiTree p = T, q = NULL;
	
	//二叉树非递归遍历需要借用栈来保存回溯点
    Stack s;
    
    //初始化栈 
    InitStack(s);
	
	//遍历继续的条件：工作指针p不为空或栈不为空
	//while(p || !StackIsEmpty(S)) 
	//<=> while(p != NULL || StackIsEmpty(S) != 1)
    while(p || !StackIsEmpty(s)) {
    	
    	//顺着树的根，一直走左分支，直到遇到最左分支的尽头（叶子节点的左孩子）。 
 		while(p){
 			
 			//根结点入栈 
          	Push(s, p);
          	
          	//访问左子树 
         	p = p->lchild;
       	}//while
       	
       	//重置指针q的值为NULL 
       	q = NULL;
       	
       	//栈不为空 
		while(!StackIsEmpty(s)){
			
			//p指向栈顶元素 
			GetTop(s, p);
			
			//这个条件表示p指向了叶子结点或者p的左右子树均被遍历过 
			if(p->rchild == NULL || p->rchild == q){
				
				//访问根结点 
				//if(Visit(p->data)) <=> if(Visit(p->data) != ERROR)
		      	if(!Visit(p->data)) { 
			        return ERROR;    
			    }//if
			    
				if(p == T) {
					return ERROR;
				}//if
				
				//q指向的是p的上一次遍历过的结点
				q = p;
				
				//根指针出栈 
          		Pop(s, p);
			}//if
			else{
				
				//访问右子树 
         		p = p->rchild;
         		
         		//退出内层循环 
				break;				
			}//else
		}//while
    }//while
    
    //销毁栈
	DestoryStack(s); 
	
	//操作成功 
	return OK;
} //PostOrderTraverse1

/*
	函数：LevelOrderTraverse1
	参数：BiTree T 二叉树T
	      Status(* Visit)(TElemType) 函数指针，指向元素访问函数 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：采用二叉链表存储结构，Visit是对数据元素操作的应用函数
	      层序遍历二叉树T的算法，对每个数据元素调用函数Visit 
*/
Status LevelOrderTraverse1(BiTree T, Status(* Visit)(TElemType)){ 
    
    //层序遍历需要用到队列 
	Queue Q;
	
	//工作指针p指向根结点 
	BiTree p = T;
	
	//根结点不为空 
	if(T){ //if(T) <=>  if(T != NULL)
		//初始化队列
	    InitQueue(Q);
	    
	    //根结点入队列
	    EnQueue(Q, T);
		
		//队列不空 
		//while(!QueueEmpty(Q)) <=> while(QueueEmpty(Q) == 0)
		while(!QueueEmpty(Q)){
			
			//根结点出队 
		   	DeQueue(Q, p);
		   	
		   	//访问根结点 
		   	if(!Visit(p->data)) { 
			   return ERROR;
			}//if
			
			//左孩子不为空 
		   	if(p->lchild) {
		   		//左孩子入队列 
		   		EnQueue(Q, p->lchild);   
		   	}//if
		       
		   	if(p->rchild) {
		   		//右孩子入队列 
		   		EnQueue(Q, p->rchild);
		   	}//if 
	   }//while
	   
	   //输出换行，使显示美观 
	   printf("\n");
	   
	   //队列用完之后要销毁，释放其内存空间 
	   DestoryQueue(Q); 
    }//if
    
    //操作成功 
	return OK;
} //LevelOrderTraverse1

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>3.二叉树的信息<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：BiTreeDepth
	参数：BiTree T 二叉树T
	返回值：若二叉树T存在，返回T的深度（高度），否则返回0
	作用：若二叉树T存在，递归地求二叉树T的深度 
*/
int BiTreeDepth(BiTree T){ 
	
	//Thigh是二叉树高度，leftThigh是左子树高度，rightThigh是右子树高度
	int Thigh, leftThigh, rightThigh;
	
	//根结点为空，树高为0 
	if(!T) {
		return 0;
	}//if
	else{
		//根结点不为空，则递归的计算树的高度
		
		//递归的求出左子树高度
		leftThigh = BiTreeDepth(T->lchild);
		
		//递归的求出右子树高度 
		rightThigh = BiTreeDepth(T->rchild);
		
		//左右子树可能高度不相等，按照树的高度定义
		//应取左子树和右子树中高度较大者作为树的高度 
		if(leftThigh >= rightThigh) { 
		   Thigh = leftThigh + 1;
		}//if 
		else { 
		   Thigh = rightThigh + 1;
		}//else
	}//else
	
	//返回树的高度 
	return Thigh;
}//BiTreeDepth

//全局变量LNM记录了二叉树叶子节点的个数 
int LNM = 0;

/*
	函数：LeafNodeNum
	参数：BiTree T 二叉树T
	返回值：若二叉树T存在，返回T的叶子结点个数，否则返回0
	作用：递归求二叉树叶子结点的个数 
*/
int LeafNodeNum(BiTree T){ 
	
	//叶子结点的特征是：左孩子和右孩子指针域均为NULL 
	if(T->lchild == NULL && T->rchild == NULL) { //当前结点是叶子结点 
		LNM++;
	}//if
	else {
		//左孩子不为空 
		if(T->lchild != NULL) {
			
			//递归的统计左子树中叶子结点的数目 
			LeafNodeNum(T->lchild);
		}//if
		
		//右孩子不为空 
		if(T->rchild != NULL) {
			
			//递归的统计右子树中叶子结点的数目 
			LeafNodeNum(T->rchild);
		}//if
	}//else
}//LeafNodeNum

/*
	函数：NodeSubNum
	参数：BiTree T 二叉树T
	返回值：若二叉树T存在，返回T的总结点个数，否则返回0
	作用：统计二叉树的总结点个数
*/
int NodeSubNum(BiTree T){
	
	if(!T) {
		return 0;  //空树或空子树
	}//if 
	else {
		//二叉树总结点数 = 左子树总结点数 + 右子树总结点数 + 自身（1） 
		return NodeSubNum(T->lchild) + NodeSubNum(T->rchild) + 1;
	} 
}//NodeSubNum


//-------------------------------------------主函数--------------------------------------------------- 
int main(int argc, char *argv[]){
	
	printf("----------------------------------二叉树引用版----------------------------------\n");
	BiTree T;     //声明一棵二叉树
	
	printf("         -------------------------二叉树的建立--------------------              \n");
	printf("请输入所要建立二叉树的先序序列(空子树用空格代替)：\n");
	CreateBiTree(T); 
	
	printf("\n         -------------------------二叉树的遍历--------------------              ");
	printf("\n\n先序遍历递归  算法结果：");
	PreOrderTraverse(T,PrintElement);
	
	printf("\n\n中序遍历递归  算法结果：");
	InOrderTraverse(T,PrintElement);
	
	printf("\n\n后序遍历递归  算法结果：");
	PostOrderTraverse(T,PrintElement); 
	
	printf("\n\n先序遍历非递归算法结果：");
	PreOrderTraverse1(T,PrintElement);
	
	printf("\n\n中序遍历非递归算法结果：");
	InOrderTraverse1(T,PrintElement);
	
	printf("\n\n后序遍历非递归算法结果：");
  	PostOrderTraverse1(T,PrintElement);
  	
  	printf("\n\n层序遍历非递归算法结果：");
  	LevelOrderTraverse1(T,PrintElement); 
  	
  	printf("\n         -------------------------二叉树的信息--------------------              ");
  	printf("\n该二叉树的高度：%d",BiTreeDepth(T)); 
  	LeafNodeNum(T);
  	printf("\n二叉树中叶子结点的个数：%d", LNM);
	printf("\n二叉树总结点数：%d",NodeSubNum(T) );
	
	return 0;
}//main

/*-----------------------------------------------测试记录-------------------------------------------------
 
----------------------------------二叉树引用版----------------------------------
         -------------------------二叉树的建立--------------------
请输入所要建立二叉树的先序序列(空子树用空格代替)：
ABE*F**C*DGHI*J*K******↙
//说明：此处的*是空格，为方便确认输入了几个空格将空格替换成*，测试输入时请将*改回空格
 ↙表示回车确认    输入（可直接复制，不要复制↙）：ABE F  C DGHI J K      ↙

         -------------------------二叉树的遍历--------------------

先序遍历递归  算法结果： A  B  E  F  C  D  G  H  I  J  K

中序遍历递归  算法结果： E  F  B  C  I  J  K  H  G  D  A

后序遍历递归  算法结果： F  E  K  J  I  H  G  D  C  B  A

先序遍历非递归算法结果： A  B  E  F  C  D  G  H  I  J  K

中序遍历非递归算法结果： E  F  B  C  I  J  K  H  G  D  A

后序遍历非递归算法结果： F  E  K  J  I  H  G  D  C  B  A

层序遍历非递归算法结果： A  B  E  C  F  D  G  H  I  J  K

         -------------------------二叉树的信息--------------------
该二叉树的高度：9
二叉树中叶子结点的个数：2
二叉树总结点数：11
--------------------------------
Process exited with return value 0
Press any key to continue . . .

*/
