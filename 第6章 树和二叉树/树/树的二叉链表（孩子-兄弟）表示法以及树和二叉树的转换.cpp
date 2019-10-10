
//>>>>>>>>>>>>>>>>>>>>>>>>>引入头文件<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <stdio.h>       //使用了标准库函数 
#include <stdlib.h>      //使用了动态内存分配函数 
#include "BiTree.cpp"    //引入二叉树的实现 

//>>>>>>>>>>>>>>>>>>>>>>>自定义符号常量<<<<<<<<<<<<<<<<<<<<<<<<<< 

#define OVERFLOW -2          //内存溢出错误常量
#define OK 1                 //表示操作正确的常量 
#define ERROR 0              //表示操作错误的常量
#define TRUE 1               //表示逻辑真的常量 
#define FALSE 0              //表示逻辑假的常量

//>>>>>>>>>>>>>>>>>>>>>>>自定义数据类型<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef int  Status;      //函数返回值状态码类型 
typedef char TElemType;   //树中结点元素类型 
 
//-------------------树的孩子兄弟表示法----------------------- 
typedef struct CSNode{
     TElemType data;  //数据域,存储结点名称 
     struct CSNode *firstchild, *nextsibling;  //孩子指针域和兄弟指针域 
} CSNode, *CSTree;

//-------------------------------树的主要操作--------------------------------

/*
	函数：CreateCSTree
	参数：CSTree &CT 树的引用 
	返回值：状态码，操作成功返回OK，否则返回ERROR 
	作用：按先根次序输入树中结点的值（一个字符），空格字符表示空树，
	       构造二叉链表表示树T
*/
Status CreateCSTree(CSTree &CT){
	
	//ch保存从键盘接收的字符 
	char ch;
	
	//从键盘接收字符 
	ch = getchar();
	
	//用户输入了空格，表示空子树 
	if(ch == ' ') { 
	    CT = NULL;
	}//if 
	else{ //用户输入的不是空格，需要生成新的结点
	
		//分配根结点空间 
		//if(!(CT = (CSNode *)malloc(sizeof(CSNode))))
		//等效于
		//CT = (CSNode *)malloc(sizeof(CSNode))
		//if(!CT) <=> if(CT == NULL)
		if(!(CT = (CSNode *)malloc(sizeof(CSNode)))){
			printf("内存分配失败！\n");
			exit(OVERFLOW); 
		}//if
		
		//生成根结点 
		CT->data = ch;
		
		//构建左子树
		CreateCSTree(CT->firstchild); 
		
		//构建右子树 
		CreateCSTree(CT->nextsibling);
	}//else
	
	//操作成功 
	return OK; 
}//CreateCSTree

/*
	函数：ExchangeToBiTree
	参数：CSTree &CT 树的引用
	      BiTree &T 二叉树的引用 
	返回值：状态码，操作成功返回OK，否则返回ERROR 
	作用：将一棵用二叉链表表示的树转换为二叉树
*/
Status ExchangeToBiTree(CSTree &CT, BiTree &T){
	
	//若树的根结点为空，那么转换成的二叉树根结点也是空 
	if(!CT) { //if(CT) <=> if(CT != NULL)
	    T = NULL;
	}//if 
	else{
		//分配新的结点空间
		//if(!(T = (BiNode *)malloc(sizeof(BiNode))))
		//相当于以下两行代码
		//T = (BiNode *)malloc(sizeof(BiNode));
		//if(!T) <=> if(T == NULL) 
		if(!(T = (BiNode *)malloc(sizeof(BiNode)))){
			printf("内存分配失败！\n");
			exit(OVERFLOW); 
		}//if
		
		//拷贝树中对应结点到二叉树 
		T->data = CT->data;
		
		//将树的孩子转换为二叉树的左孩子     
		ExchangeToBiTree(CT->firstchild, T->lchild);
		
		//将树的兄弟转换为二叉树的右孩子  
		ExchangeToBiTree(CT->nextsibling,T->rchild);  
	}//else 
	
	//操作成功 
	return OK; 
}//ExchangeToBiTree

/*
	函数：DestoryTree
	参数：CSTree &CT 树的引用 
	返回值：无
	作用：按照树的定义递归地销毁树
*/
void DestoryCSTree(CSTree &CT){
	
	//非空树
	if(CT){  //if(CT) <=> if(CT != NULL)
		
		//孩子子树非空，递归的销毁孩子子树 
		//if(CT->firstchild) <=> if(CT->firstchild != NULL) 
	   	if(CT->firstchild) {
		   DestoryCSTree(CT->firstchild);
		}//if
		 
		//兄弟子树非空，递归的销毁兄弟子树
		//if(CT->nextsibling) <=> if(CT->nextsibling != NULL)
		if(CT->nextsibling) { 
		   DestoryCSTree(CT->nextsibling);
		}//if
		
		//释放根结点
		free(CT);
		
		//指针置空 
		CT = NULL; 
	}//if  
}//DestoryTree

/*
	函数：DestoryBiTree
	参数：BiTree &T 二叉树的引用 
	返回值：无 
	作用：按照二叉树定义递归地销毁二叉树
*/
void DestoryBiTree(BiTree &T){
	
	//非空树 
	if(T){  //if(T) <=> if(T != NULL)
	
		//左子树非空,递归的销毁左子树
	   	if(T->lchild)  {
	   		DestoryBiTree(T->lchild);
	   	}//if 
		
		//右子树非空,递归的销毁右子树
		if(T->rchild) {
			DestoryBiTree(T->rchild);
		}//if 
		    
		//释放根结点
		free(T);
		
		//指针置空 
		T = NULL; 
	}//if 
}//DestoryTree

/*
	函数：DestoryTree
	参数：CSTree &CT 树的引用 
	      BiTree &T  二叉树的引用 
	返回值：无
	作用：销毁树和二叉树
*/
void DestoryTree(CSTree &CT, BiTree &T){
	
	//销毁树 
	DestoryCSTree(CT);
	
	//销毁二叉树 
	DestoryBiTree(T);
	
	printf("\n->生成的树和二叉树已被销毁！"); 
}//DestoryTree

//-----------------------------主函数----------------------------------- 
int main(int argc,char *argv[]){
	printf("----------------------------------  树的应用  ----------------------------------\n");
	BiTree T=NULL;     //声明一棵二叉树
	CSTree CT=NULL;    //声明一棵普通树
	printf("         ---------------------------树的建立----------------------              \n");
	printf("->请按树的先根次序输入序列，如有空子树，用空格填充，完成后输入回车确认\n"); 
	CreateCSTree(CT);
	printf("         ---------------------------树的转换----------------------              \n");
	printf("->正在将输入的树转换为其对应的二叉树...\n");
	ExchangeToBiTree(CT,T); 
	printf("->转换操作执行完毕！\n");
	printf("\n         -------------------------二叉树的遍历--------------------              ");
	printf("\n\n先序遍历递归  算法结果："); PreOrderTraverse(T,PrintElement);
	printf("\n\n中序遍历递归  算法结果："); InOrderTraverse(T,PrintElement);
	printf("\n\n后序遍历递归  算法结果："); PostOrderTraverse(T,PrintElement); 
	printf("\n\n先序遍历非递归算法结果："); PreOrderTraverse1(T,PrintElement);
	printf("\n\n中序遍历非递归算法结果："); InOrderTraverse1(T,PrintElement);
	printf("\n\n后序遍历非递归算法结果："); PostOrderTraverse1(T,PrintElement);
  	printf("\n\n层序遍历非递归算法结果："); LevelOrderTraverse1(T,PrintElement); 
  	printf("\n         -------------------------二叉树的信息--------------------              ");
  	printf("\n该二叉树的高度：%d",BiTreeDepth(T)); 
  	LeafNodeNum(T);
  	printf("\n二叉树中叶子结点的个数：%d", LNM);
	printf("\n二叉树总结点数：%d",NodeSubNum(T) );
	printf("\n\n         -------------------------  树的销毁  --------------------              ");
	DestoryTree(CT, T); 
	printf("\n->算法演示结束！"); 
	system("pause"); 
	return 0;
}//main

/*-----------------------------------------------测试记录-------------------------------------------------
树来自PPT P98 页，为方便验证，记录测试过程
通过测试结果容易发现，树的先根序列和后根序列分别与其转换完的二叉树的先序和中序序列相同,
这也是源代码中转换函数的执行原理 
 树的先根序列    A B E F C D G H I J K
 树的后根序列    E F B C I J K H G D A
 二叉树先序序列  A B E F C D G H I J K
 二叉树中序序列  E F B C I J K H G D A
 
----------------------------------  树的应用  ----------------------------------

         ---------------------------树的建立----------------------

->请按树的先根次序输入序列，如有空子树，用空格填充，完成后输入回车确认
ABE*F**C*DGHI*J*K******↙   
    //说明：此处的*是空格，为方便确认输入了几个空格将空格替换成*，测试输入时请将*改回空格
	        ↙表示回车确认    输入（可直接复制，不要复制↙）：ABE F  C DGHI J K      ↙
         ---------------------------树的转换----------------------

->正在将输入的树转换为其对应的二叉树...

->转换操作执行完毕！

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
二叉树总结点数：11

         -------------------------  树的销毁  --------------------
->生成的树和二叉树已被销毁！
->算法演示结束！请按任意键继续. . .

*/
