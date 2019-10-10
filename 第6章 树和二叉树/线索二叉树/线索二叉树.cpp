//>>>>>>>>>>>>>>>>>>>>>>>>>引入头文件<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <stdio.h>       //使用了标准库函数 
#include <stdlib.h>      //使用了动态内存分配函数 

//>>>>>>>>>>>>>>>>>>>>>>>自定义符号常量<<<<<<<<<<<<<<<<<<<<<<<<<< 

#define OVERFLOW -2          //内存溢出错误常量
#define OK 1                 //表示操作正确的常量 
#define ERROR 0              //表示操作错误的常量
#define TRUE 1               //表示逻辑真的常量 
#define FALSE 0              //表示逻辑假的常量

//>>>>>>>>>>>>>>>>>>>>>>>自定义数据类型<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef char TElemType;
typedef int Status;

//定义NIL为空格 
TElemType NIL = ' ';

//------------------- 二叉树的二叉线索存储表示 --------------------
//采用枚举类型定义指针标志位 
typedef enum{
	Link,   //Link(0)：  指针 0
	Thread  //Thread(1)：线索 1
}PointerTag; 

typedef struct BiThrNode{
	TElemType data;                     //数据域，存储节点数据 
	struct BiThrNode *lchild, *rchild;  //左右孩子指针
	PointerTag LTag, RTag;              //左右标志
}BiThrNode, *BiThrTree;

//---------------------------线索二叉树操作---------------------------- 

/*
	函数：CreateBiThrTree
	参数：BiThrTree &T 线索二叉树的引用 
	返回值：状态码，操作成功返回OK，否则返回ERROR 
	作用：按先序输入线索二叉树中结点的值，构造线索二叉树T。
	      空格表示空结点
*/
Status CreateBiThrTree(BiThrTree &T) {
	
	//保存从键盘接收的字符 
	TElemType ch;
	scanf("%c", &ch);
	
	//若输入了空格，则此节点为空 
	if(ch == NIL) {
		T = NULL;	
	}//if 
	else{ //若输入的不是空格则创建新结点并添加到线索二叉树的合适位置 
		//申请根结点存储空间 
		T = (BiThrTree)malloc(sizeof(BiThrNode));
		
		//检查空间分配是否成功 
		if(!T) { 
			exit(OVERFLOW);
		}//if 
		
		//给根结点赋植
		T->data = ch;
		
		//递归地构造左子树
		CreateBiThrTree(T->lchild);
		
		//若有左孩子则将左标志设为指针
		if(T->lchild) {
			T->LTag = Link; 
		}//if
		
		//递归地构造右子树
		CreateBiThrTree(T->rchild);
		
		//若有右孩子则将右标志设为指针
		if(T->rchild) {
			T->RTag = Link;
		}//if
	}//else
	
	//操作成功 
	return OK; 
}//CreateBiThrTree

//---------------------------- 中序线索化 --------------------------- 

//全局变量，始终指向刚刚访问过的结点
BiThrTree pre;

/*
	函数：InThreading
	参数：BiThrTree p 指向线索二叉树结点的指针p 
	返回值：无
	作用：通过中序遍历递归地对头结点外的其他结点进行中序线索化，
	      线索化之后pre指向最后一个结点。
	      此函数会被InOrderThreading函数调用。  
*/
void InThreading(BiThrTree p) {
	
	//线索二叉树不空
	if(p) {
		
		//递归左子树线索化
		InThreading(p->lchild);
		
		//由于已经访问过前驱结点，此时就可以完成前驱结点的线索化了。
		//当前结点的前驱就是pre指向的结点。如果当前结点没有左孩子
		//那么左孩子的指针域就可以拿来存放前驱结点的线索信息。 
		
		//若当前结点没有左孩子，则左指针域可以存放线索 
		if(!p->lchild) {
			
			//左标志为前驱线索
			p->LTag = Thread;
			
			//左孩子指针指向前驱 
			p->lchild = pre; 
		}//if
		
		//此时还未访问后继结点，但可以确定当前结点p一定是前驱结点pre 
		//的后继，所以要把前驱结点的后继指针域填上线索信息 
		 
		//前驱没有右孩子
		if(!pre->rchild) {
			
			//前驱的右标志为线索(后继)
			pre->RTag = Thread;
			
			//前驱右孩子指针指向其后继(当前结点p)
			pre->rchild = p;
		}//if 
		
		//使pre指向的结点p的新前驱 
		pre = p;
		
		//递归右子树线索化
		InThreading(p->rchild); 
	}//if 
}//InThreading

/*
	函数：InOrderThreading
	参数：BiThrTree &Thrt 头结点的引用 
	      BiThrTree T 指向线索二叉树根结点的指针 
	返回值：状态码，操作成功返回OK，否则返回ERROR 
	作用：中序遍历二叉树T，并将其中序线索化。
*/
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T) {
	
	//申请头结点内存空间 
	//if(!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode))))
	//相当于以下两行代码：
	//Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
	//if(!Thrt)  <=>  if(Thrt == NULL)
	if(!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode)))) {
		//内存分配失败
		exit(OVERFLOW);
	}//if
	
	//建头结点，左标志为指针
	Thrt->LTag = Link;
	
	//右标志为线索
	Thrt->RTag = Thread;
	
	//右指针指向结点自身 
	Thrt->rchild = Thrt;
	
	//若二叉树空，则左指针指向结点自身 
	if(!T) { //if(!T) <=> if(T == NULL)
		Thrt->lchild = Thrt;
	}//if 
	else{
		//头结点的左指针指向根结点
		Thrt->lchild = T;
		
		//pre(前驱)的初值指向头结点
		pre = Thrt;
		
		//中序遍历进行中序线索化，pre指向中序遍历的最后一个结点
		//InThreading(T)函数递归地完成了除头结点外其他结点的线索化。 
		InThreading(T);
		
		//最后一个结点的右指针指向头结点
		pre->rchild = Thrt;
		
		//最后一个结点的右标志为线索
		pre->RTag = Thread;
		
		//头结点的右指针指向中序遍历的最后一个结点
	 	Thrt->rchild = pre;
	}//else
	
	//操作成功 
	return OK;
}//InOrderThreading

/*
	函数：Print
	参数：TElemType c 被访问的元素 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：访问元素e的函数，通过修改该函数可以修改元素访问方式，
	      该函数使用时需要配合遍历函数一起使用。 
*/
Status Print(TElemType c){
	
	//以控制台输出的方式访问元素 
   	printf(" %c ", c);
   	
   	//操作成功 
   	return OK; 
}//Print

/*
	函数：InOrderTraverse_Thr
	参数：BiThrTree T 指向线索二叉树根结点的指针
	      Status(*Visit)(TElemType) 函数指针，指向元素访问函数 
	返回值：状态码，操作成功返回OK，否则返回ERROR 
	作用：中序遍历线索二叉树T(头结点)的非递归算法。
*/
Status InOrderTraverse_Thr(BiThrTree T, Status(*Visit)(TElemType)) {
	
	//工作指针p 
	BiThrTree p;
	
	//p指向线索二叉树的根结点
	p = T->lchild;
	
	//空树或遍历结束时，p==T
	while(p != T) {
		
		//由根结点一直找到二叉树的最左结点
		while(p->LTag == Link) { 
	   		p = p->lchild;
	   	}//while
	   	
	   	//调用访问函数访问此结点
		Visit(p->data);
		
		//p->rchild是线索(后继)，且不是遍历的最后一个结点
		while(p->RTag == Thread && p->rchild != T) {
			p = p->rchild;
			
			//访问后继结点
			Visit(p->data);
		}//while
		
		//若p->rchild不是线索(是右孩子)，p指向右孩子，返回循环，
		//找这棵子树中序遍历的第1个结点
	 	p = p->rchild;
	}//while 
	
	//操作成功 
	return OK;      
}//InOrderTraverse_Thr

/*
	函数：DestroyBiTree
	参数：BiThrTree &T T指向线索二叉树根结点 
	返回值：状态码，操作成功返回OK，否则返回ERROR 
	作用：递归地销毁线索二叉树，被DestroyBiThrTree函数调用。 
*/
Status DestroyBiTree(BiThrTree &T) {
	
	//非空树
	if(T) { //if(T) <=> if(T != NULL) 
		
		//如果有左孩子则递归地销毁左子树
		if(T->LTag == Link) {
			DestroyBiTree(T->lchild);
		}//if
	   
	   	//如果有右孩子则递归地销毁右子树
		if(T->RTag == Link) {
			DestroyBiTree(T->rchild);
		}//if 
	   
	   	//释放根结点
		free(T);
		
		//指针置空 
		T = NULL;
	}//if
	
	//操作成功 
	return OK;
}//DestroyBiTree

/*
	函数：DestroyBiTree
	参数：BiThrTree &Thrt Thrt指向线索二叉树头结点 
	返回值：状态码，操作成功返回OK，否则返回ERROR 
	作用：若线索二叉树Thrt存在，递归地销毁线索二叉树Thrt。 
*/
Status DestroyBiThrTree(BiThrTree &Thrt) {
	
	//头结点存在
	if(Thrt) {
		
		//若根结点存在，则递归销毁头结点lchild所指的线索二叉树 
		if(Thrt->lchild) { //if(Thrt->lchild) <=> if(Thrt->lchild != NULL)
			DestroyBiTree(Thrt->lchild);
		}//if 
		
		//释放头结点
		free(Thrt);
		
		//线索二叉树Thrt指针赋0
		Thrt = NULL;
	}//if
	
	//操作成功 
	return OK;
}//DestroyBiThrTree

int main(int argc, char** argv) {
	
	printf("---------------------线索二叉树测试程序-----------------------\n");
	
	BiThrTree H, T;
	
	//使用用户输入的先序遍历序列生成一棵没有被线索化的二叉树 
	printf("请按先序遍历顺序输入二叉树，空格表示空子树，输入完成后按回车确认\n");
	CreateBiThrTree(T);
	
	//在中序遍历过程中线索化二叉树
	InOrderThreading(H, T);
	
	//按中序遍历序列输出线索二叉树
	printf("中序遍历(输出)线索二叉树:\n");
	InOrderTraverse_Thr(H, Print);
	printf("\n");
	
	//销毁线索二叉树
	DestroyBiThrTree(H);
}//main 

/*
---------------------线索二叉树测试程序-----------------------
请按先序遍历顺序输入二叉树，空格表示空子树，输入完成后按回车确认
ABE*F**C*DGHI*J*K******↙   
    //说明：此处的*是空格，为方便确认输入了几个空格将空格替换成*，测试输入时请将*改回空格
	        ↙表示回车确认    输入（可直接复制，不要复制↙）：ABE F  C DGHI J K      ↙
中序遍历(输出)线索二叉树:
 E  F  B  C  I  J  K  H  G  D  A

--------------------------------
Process exited with return value 0
Press any key to continue . . .
*/
