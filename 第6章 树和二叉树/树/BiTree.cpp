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
Status CreateBiTree(BiTree &T){ 
	
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
