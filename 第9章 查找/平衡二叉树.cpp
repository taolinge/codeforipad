//>>>>>>>>>>>>>>>>>>>>>>>>引入头文件<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <stdio.h>       //使用了标准库函数 
#include <stdlib.h>      //使用了动态内存分配函数

//>>>>>>>>>>>>>>>>>>>>>>自定义符号常量<<<<<<<<<<<<<<<<<<<<<<<<<<< 
 
#define OVERFLOW -2          //内存溢出错误常量
#define OK 1                 //表示操作正确的常量 
#define ERROR 0              //表示操作错误的常量
#define TRUE 1               //表示逻辑正确的常量 
#define FALSE 0              //表示逻辑错误的常量

#define EQ(a,b) ((a)==(b))   //相等 
#define LT(a,b) ((a)< (b))   //小与
#define LQ(a,b) ((a)<= (b))  //小与等于 

#define LH +1                // 左高
#define EH 0                 // 等高
#define RH -1                // 右高

//>>>>>>>>>>>>>>>>>>>>>自定义数据类型<<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef int Status;          //定义状态码为int类型 

typedef int KeyType;         // 设关键字域为字符型
struct ElemType {            // 数据元素类型
	KeyType key;
};


//-------------------平衡二叉树类型定义---------------------- 

//定义二叉树基本操作的树元素类型
typedef ElemType TElemType;

typedef struct BSTNode {
	
	//数据域 
	ElemType data;
	
	//结点的平衡因子
	int bf;
	
	//左、右孩子指针
	BSTNode *lchild, *rchild;
}BSTNode, *BSTree;

//定义二叉树基本操作的指针类型
typedef BSTree BiTree;

/*
	函数：Print
	参数：TElemType e 被访问的元素 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：访问元素e的函数，通过修改该函数可以修改元素访问方式，
	      该函数使用时需要配合遍历函数一起使用。 
*/
Status PrintElement(TElemType e) {
	
	//采用控制台输出的方式访问元素 
	printf(" %d ", e);
	
	//操作成功 
	return OK;
}//PrintElement

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
	函数：R_Rotate
	参数：BSTree &p 平衡二叉树根指针p 
	返回值：无 
	作用： 对以*p为根的二叉排序树作右旋处理，
	       处理之后p指向新的树根结点，
		   即旋转处理之前的左子树的根结点。 
*/
void R_Rotate(BSTree &p) {
	
	//lc指向p的左子树根结点
	BSTree lc = p->lchild;
	
	//lc的右子树挂到p的左子树上 
	p->lchild = lc->rchild;
	
	//把p挂到lc的右子树上 
	lc->rchild = p;
	
	//p指向新的根结点
	p = lc;
}//R_Rotate

/*
	函数：L_Rotate
	参数：BSTree &p 平衡二叉树根指针p 
	返回值：无 
	作用： 对以*p为根的二叉排序树作左旋处理，
	       处理之后p指向新的树根结点，
		   即旋转处理之前的右子树的根结点。 
*/
void L_Rotate(BSTree &p) {
	
	//rc指向p的右子树根结点
	BSTree rc = p->rchild;
	
	//rc的左子树挂到p的右子树上 
	p->rchild = rc->lchild; 
	
	//把p挂到rc的左子树上
	rc->lchild = p;
	
	//p指向新的根结点
	p = rc;
}//L_Rotate 

/*
	函数：LeftBalance
	参数：BSTree &T 平衡二叉树根指针T 
	返回值：无
	作用： 对以指针T所指结点为根的二叉树作左平衡旋转处理，
	       本算法结束时，指针T指向新的根结点。 
*/
void LeftBalance(BSTree &T) {
	
	//lc指向*T的左子树根结点
	BSTree lc = T->lchild; 
	
	//检查*T的左子树的平衡度，并作相应平衡处理
	switch(lc->bf) { 
    	
		//新结点插入在*T的左孩子的左子树上，要作单右旋处理
		case LH: 
			
			//右旋转后左子树的根结点变成新的根。
			//相当于从左子树上抽出一层移到了右子树上
			//左子树高度-1，右子树高度+1，
			//此时原来的根结点和原来根结点左子树的根结点左右子树高度相等 
			//所以根结点和左子树根结点的平衡因子修改为EH 
        	T->bf = lc->bf = EH;
        	
        	//在根结点左孩子的左子树上插结点，要做单右旋处理 
        	R_Rotate(T);
        	break;
        		
        //新结点插入在*T的左孩子的右子树上，要作双旋处理
    	case RH: 
    	
    		//rd指向*T的左孩子的右子树根
            BSTree rd = lc->rchild;
			
			//修改*T及其左孩子的平衡因子 
        	switch(rd->bf) { 
        		
        		//rd左子树比右子树高。
            	case LH: 
            		
            		//调整前rd的右子树比T的右子树低1
            		//rd的右子树调整后最终会成为T的左子树 
            		//T原来的右子树不变，所以T在调整后右子树较高 
					T->bf = RH;
					
					//rd的左子树调整前比lc的左子树低1
					//rd的左子树调整后最终成为lc的右子树
					//lc的左子树不变，结点插在了原先rd的左子树上
					//所以此时lc的左子树与右子树（也就是原来lc的左子树）等高 
                	lc->bf = EH;
                    break;
                
				//rd的左右子树等高 
				case EH: 
					
					//rd的左子树最终会成为lc的右子树
					//rd的右子树最终会成为T的左子树
					//所以最终T和lc的左右子树都是平衡的 
					T->bf = lc->bf = EH;
                    break;
                
                //rd右子树比左子树高 
				case RH: 
					
					//旋转后原来rd的右子树与T的右子树同高 
					T->bf = EH;
					
					//旋转后lc的左子树比原来rd的左子树高1 
                    lc->bf = LH;
            }//switch 
            
            //调整后，rd成为根结点，并且平衡因子为EH 
            rd->bf = EH;
            
            //对*T的左子树作左旋平衡处理（这次旋转是为了把平衡因子调整成相同符号） 
            L_Rotate(T->lchild);
			
			//对*T作右旋平衡处理（此次旋转目的是使树恢复平衡） 
            R_Rotate(T); 
	}//switch 
}//LeftBalance

/*
	函数：RightBalance
	参数：BSTree &T 平衡二叉树根指针T 
	返回值：无
	作用： 对以指针T所指结点为根的二叉树作右平衡旋转处理，
	       本算法结束时，指针T指向新的根结点。 
*/
void RightBalance(BSTree &T) {
	
	//rc指向*T的右子树根结点
	BSTree rc = T->rchild; 
	
	//检查*T的右子树的平衡度，并作相应平衡处理
	switch(rc->bf) {
		
		//新结点插入在*T的右孩子的右子树上，要作单左旋处理
    	case RH: 
    		
    		//左旋后，T的右子树的根结点变为新的树根
			//此时相当于从右子树上抽出一层移到左子树上
			//所以这就相当于左子树深度+1，右子树深度-1
			//那么左旋之后左右子树就平衡了，
			//此时原来的根结点和原来根结点右子树的根结点左右子树高度相等 
			//所以根结点和右子树根结点的平衡因子修改为EH 
        	T->bf = rc->bf = EH;
        	
        	//在右孩子的右子树上插入结点，要作单左旋处理
            L_Rotate(T);
            break;
            
        //新结点插入在*T的右孩子的左子树上，要作双旋处理
    	case LH: 
    		
    		//rd指向*T的右孩子的左子树根
            BSTree rd = rc->lchild; 
            
            //修改*T及其右孩子的平衡因子
			switch(rd->bf) {
			 
			 	//rd的右子树比左子树高1 
            	case RH: 
            		
            		//rd的左子树比T的左子树低1
					//rd的左子树最终会成为T的右子树 
					T->bf = LH;
					
					//最终rc会成为新的根结点
					//左右两边平衡 
                	rc->bf = EH;
                    break;
                
                //rd的左右子树两边平衡 
                case EH: 
                	
                	//rd的左子树最终会成为T的右子树
					//rd的右子树最终会成为rc的左子树 
                	//所以最终T和rc的左右子树都是平衡的 
					T->bf = rc->bf = EH; 
                    break;
                
				//rd的左子树比右子树高1 
                case LH:
					 
                	//rd的左子树和T的左子树等高 
					T->bf = EH;
					
					//rd的右子树（低1的一端）最后会成为rc的左子树
					//而rc的右子树和rd的左子树等高
					//所以rc是右子树比左子树高1 
                    rc->bf = RH;
            }//switch
			
			//右旋后恢复平衡，BF=0 
            rd->bf = EH;
            
            //对*T的右子树作右旋平衡处理（调整平衡因子符号，使之相同） 
            R_Rotate(T->rchild);
            
            //对*T作左旋平衡处理（调整树，使之平衡） 
			L_Rotate(T); 
   	}//switch
}//RightBalance

/*
	函数：InsertAVL
	参数：BSTree &T 平衡二叉树根指针T
	      ElemType e 插入新结点数据元素为e
		  Status &taller taller反映T长高与否 
	返回值：状态码，操作成功返回OK 
	作用： 若在平衡的二叉排序树T中不存在和e有相同关键字的结点，
	       则插入一个数据元素为e的新结点，并返回1，否则返回0。
	       若因插入而使二叉排序树失去平衡，则作平衡旋转处理。
*/
Status InsertAVL(BSTree &T, ElemType e, Status &taller) {
 
	//插入新结点，树“长高”，置taller为TRUE
	if(!T) { //if(!T) <=> if(T == NULL) 
		
		//申请新结点空间 
    	T = (BSTree)malloc(sizeof(BSTNode));
    	
    	//将被插入元素e保存到新结点中 
		T->data = e;
		
		//平衡二叉树是特殊的二叉排序树，
		//新结点将作为叶子结点插入 
    	T->lchild = T->rchild = NULL;
    	
    	//新插入的结点不破坏平衡二叉树的平衡状态 
    	T->bf = EH;
    	
    	//树长高 
		taller = TRUE;
	}//if
	else {
		
    	//树中已存在和e有相同关键字的结点则不再插入
		if EQ(e.key, T->data.key) { 
    		
    		//由于没有插入新结点，树没有长高 
			taller = FALSE;
    		
    		//没插入新结点 
			return FALSE;
    	}//if
    	
    	//若e比当前结点的关键字小， 
    	//就应继续在*T的左子树中进行搜索
    	if LT(e.key, T->data.key) {
			
			//如果左子树上递归搜索后没有插入结点e 
			//if(!InsertAVL(T->lchild, e, taller))
			//<=> if(InsertAVL(T->lchild, e, taller) != FALSE)
    		if(!InsertAVL(T->lchild, e, taller)) { 
        		
        		//返回未插入标志 
				return FALSE;
        	}//if
			
			//已插入到*T的左子树中且左子树“长高”
    		if(taller) { //if(taller) <=> if(taller == TRUE)
				
				//检查根结点*T的平衡度
        		switch(T->bf) {
        			
        			//情况1：原本左子树就比右子树高，现在在左子树上
					//再插入一个结点势必会打破平衡二叉树的平衡状态。
					//所以需要作左平衡处理
        			case LH: 
        				
        				//做左平衡处理 
                		LeftBalance(T);
                		
                		//经过左平衡处理之后树没有长高
                    	taller = FALSE;
                    	break;
                    
                    //原本左、右子树等高，现因左子树增高1而使树增高
                    //但是此时左右子树深度的绝对值之差在增加结点之后
					//不会超过1，但是左子树会比右子树高1 
           			case EH: 
           				
           				//设置平衡因子为LH（此时左子树更高一些） 
                    	T->bf = LH;
                    	
                    	//插入之前左右子树等高，插入之后左子树比右子树高1，
						//所以树长高，设置taller = TRUE 
                    	taller = TRUE;
                    	break;
                    
                    //原本右子树比左子树高1，在左子树上插入一个结点后
					//左、右子树等高。所以树没有长高。（树高没变） 
        			case RH: 
        				
        				//在左子树上插入结点后左右子树等高 
						T->bf = EH; 
						
						//插入结点后树没有长高 
                    	taller = FALSE;
        		}//switch
        	}//if 
    	}//if 
    	
    	//若e比当前结点的关键字大， 
    	//就应继续在*T的右子树中进行搜索
    	else { 
    	
    		//如果右子树上递归搜索后没有插入结点e 
    		//if(!InsertAVL(T->rchild, e, taller))
    		// <=> if(InsertAVL(T->rchild, e, taller) == FALSE)
    		if(!InsertAVL(T->rchild, e, taller)) { 
        		
        		//返回未插入标志
				return FALSE;
        	}//if 
        	
        	//已插入到T的右子树且右子树“长高”
    		if(taller) { //if(taller) <=> if(taller == TRUE)
    			
    			//检查T的平衡度
        		switch(T->bf) {
        			
        			//原本左子树比右子树高1，在右子树上插入一个结点后
					//左、右子树等高。树的高度不变 
					case LH:
						
						//左右子树等高 
						T->bf = EH; 
						
						//树的高度不变 
                    	taller = FALSE;
                    	break;
           			
           			//原本左、右子树等高，现因右子树增高1而使树增高
           			//但是此时左右子树深度的绝对值之差在增加结点之后
					//不会超过1，但是右子树会比左子树高1 
					case EH: 
					
						//右子树比左子树高1 
                    	T->bf = RH;
                    	
                    	//在左右等高的树的右子树上插入1个结点造成树长高 
                    	taller = TRUE;
                   		break;
                   	
                   	//原本右子树比左子树高，还要在右子树上继续插入结点，
					//这就破坏了平衡二叉树的平衡状态。所以需要作右平衡处理
                    case RH: 
                    	
                    	//由于平衡二叉树平衡状态被右子树新插入的结点破坏，
						//所以要做有平衡处理 
                		RightBalance(T);
                		
                		//右平衡处理后，树没有长高 
            			taller = FALSE;
        		}//switch 
    		}//if 
		}//else 
	}//else 
	
	//结点成功插入 
	return TRUE;
}//InsertAVL

/*
	函数：SearchBST
	参数：BSTree T 平衡二叉树根指针T
	      KeyType key 待查找关键字 
	返回值：若查找成功，则返回指向该数据元素结点的指针，否则返回空指针。
	作用： 在根指针T所指二叉排序树中递归地查找某关键字
	       等于key的数据元素
*/
BiTree SearchBST(BiTree T, KeyType key) {
	
	//关键字相等或者根结点为空：查找结束
	if(!T || EQ(key, T->data.key)) { 
		
		//若找到关键字，T指向平衡二叉树中的对应结点
		//若根结点为空，则返回的T为NULL 
    	return T;
    }//if 
	else if LT(key, T->data.key) { //待查找关键字小于当前结点的关键字 
    	
    	//在左子树中继续查找
		return SearchBST(T->lchild, key);
    }//else if 
	else { //待查找关键字大于当前结点的关键字
		
		//在右子树中继续查找
    	return SearchBST(T->rchild, key);
    }//else 
}//SearchBST

/*
	函数：print
	参数：ElemType c 记录 
	返回值：无
	作用：元素访问函数 
*/
void print(ElemType c) {
	
	printf(" %d ", c.key);
}//print

int main() {
	
	printf("------------------------平衡二叉树程序测试--------------------------\n\n"); 
	
	//dt是平衡二叉树根结点的指针
	//p是工作指针，用于记录搜索平衡二叉树找到关键字结点的位置 
	BSTree dt, p;
	
	//记录树的结点个数 
	int n;
	
	//k用于记录树是否长高 
	Status k;
	
	//j是临时变量，用于记录用户输入的待查找关键字的值 
	KeyType j;
	
	//确定关键字个数，作为结点数
	printf("->您想建立一棵带有几个结点的平衡二叉树（请输入一个正整数）："); 
	scanf("%d", &n);
	
	//开辟临时存放关键字的内存空间
	ElemType *r = (ElemType *)malloc(n * sizeof(ElemType));
	
	//初始化记录 
	printf("->请依次输入平衡二叉树中的所有关键字，中间用空格隔开，输入完成之后按回车键确认：\n");
	for(int i = 0; i < n; i++) { 
    	scanf("%d", &r[i]);
	}//for 
	
	//初始化空树
	dt = NULL;
	
	//建平衡二叉树
	for(int i = 0; i < n; i++) { 
    	InsertAVL(dt, r[i], k);
	}//for 
	
	//中序遍历二叉树
	printf("->中序遍历平衡二叉树:\n");
	InOrderTraverse(dt, PrintElement); 
	
	//在平衡二叉树中执行查找操作 
	printf("\n->测试平衡二叉树查找操作\n");
	printf("请输入待查找关键字的值: ");
	scanf("%d", &j);
	p = SearchBST(dt, j); //查找给定关键字的记录
   	
   	//找到了 
	if(p) { //if(p) <=> if(p != NULL)
    	printf("->查找结果：找到关键字%d\n", p->data);
    }//if 
	else {
    	printf("->查找结果：没找到关键字：%d\n", j);
	}//else 
	printf("\n");
	
	//销毁二叉树 
	printf("->销毁平衡二叉树：");
	DestoryBiTree(dt);
	printf("成功！\n");
	
	//释放临时存储空间 
	free(r); 
	
	//程序正常结束 
	printf("->算法演示结束！\n");
	return 0;
}//main

/* 运行结果 
------------------------平衡二叉树程序测试--------------------------

->您想建立一棵带有几个结点的平衡二叉树（请输入一个正整数）：10
->请依次输入平衡二叉树中的所有关键字，中间用空格隔开，输入完成之后按回车键确认：
4 67 8 99 2 33 5 12 1 68
->中序遍历平衡二叉树:
 1  2  4  5  8  12  33  67  68  99
->测试平衡二叉树查找操作
请输入待查找关键字的值: 12
->查找结果：找到关键字12

->销毁平衡二叉树：成功！
->算法演示结束！

--------------------------------
Process exited with return value 0
Press any key to continue . . .
*/
