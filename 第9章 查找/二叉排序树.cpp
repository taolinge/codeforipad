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

//>>>>>>>>>>>>>>>>>>>>>自定义数据类型<<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef int  Status;      //状态标志 
typedef int  KeyType;     //关键字类型
typedef struct{
	
	//关键字 
	KeyType key;
}TElemType;   

//----------------二叉树的二叉链表存储表示-------------------- 
typedef struct BiNode{
	
	//数据域 
	TElemType  data;
	
	//左右孩子结点指针
	struct BiNode  *lchild, *rchild; 
}BiNode, *BiTree;

//-----------------------二叉排序树的主要操作---------------------------

//>>>>>>>>>>>>>>>>>>>>>  1.二叉排序树的构建  <<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	函数：CreateBST
	参数：BiTree &T 二叉排序树引用 
	返回值：状态码，操作成功返回OK 
	作用：根据用户输入创建一棵二叉排序树 
*/
Status CreateBST(BiTree &T){
	
	//二叉排序树插入结点函数声明
	Status InsertBST(BiTree &T, TElemType e);
	
	//二叉排序树顶点总数 
	int num;
	
	//保存输入的关键字 
	TElemType e;
	
	//确定树中的顶点总数 
    printf("您想创建一棵含有几个顶点的二叉排序树，请输入顶点数，并按回车确认：");
    scanf("%d", &num);
    
    //输入关键字 
    printf("请输入%d个整数作为关键字，中间用空格隔开，并按Enter确认\n", num);
    for(int i = 0; i < num; i++) {
    	scanf("%d", &e.key);
     	InsertBST(T, e);
    }//for
    
    //操作成功 
    printf("二叉排序树创建完成\n"); 
    return OK;
}//CreateBST


//>>>>>>>>>>>>>>>>>>>  2.二叉排序树的遍历  <<<<<<<<<<<<<<<<<<<<

/*
	函数：PrintElement
	参数：BiTree &T 二叉排序树引用 
	返回值：状态码，操作成功返回OK 
	作用：元素访问函数，输出关键字key
*/
Status PrintElement(KeyType key) {
	
	//以控制台打印key的方式访问关键字 
	printf(" %d ", key);
	
	//操作成功 
	return OK;
}//PrintElement 

/*
	函数：InOrderTraverse
	参数：BiTree T 二叉排序树T
		  Status(* Visit)(KeyType) 元素访问函数 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：采用二叉链表存储结构，Visit是对数据元素操作的应用函数
	      中序遍历二叉树T的递归算法，对每个数据元素调用函数Visit
*/
Status InOrderTraverse(BiTree T, Status(* Visit)(KeyType)){ 
    
    //根结点不为空 
    //if(T) <=> if(T == NULL) 
	if(T){
		
		//访问左孩子 
		//if(InOrderTraverse(T->lchild, Visit)) <=>
		//if(InOrderTraverse(T->lchild, Visit) == ERROR)
		if(InOrderTraverse(T->lchild, Visit)) { 
		    
		    //访问根结点 
		    //if(Visit(T->data.key)) <=> if(Visit(T->data.key) == ERROR)
			if(Visit(T->data.key)) {
		    	
		    	//访问右孩子
				//if(InOrderTraverse(T->rchild, Visit)) <=>
				//if(InOrderTraverse(T->rchild, Visit) == ERROR) 
		        if(InOrderTraverse(T->rchild, Visit)) {
					
					//操作成功 
					return OK;
				}//if
			}//if
		}//if 
			
		//操作失败 
		return ERROR;
	} //if
	else {
		
		//此结点视为叶子结点的孩子：NULL 
		return OK;
	}//else 
}//InOrderTraverse 

//>>>>>>>>>>>>>>>>>>>>2.二叉排序树的查找算法<<<<<<<<<<<<<<<<<<<<<<<

/* （在二叉排序树中查找关键字） 
	函数：SearchBST
	参数：BiTree T 二叉排序树T 
	      KeyType key 关键字
		  BiTree f 指针f指向T的双亲，其初始调用值为NULL
		  BiTree &p 若查找成功，p指向找到的数据元素结点，
		            否则p指向查找路径上访问的最后一个结点
	返回值：状态码，查找成功返回TRUE，否则返回FALSE 
	作用：在根指针T所指的二叉排序树中递归地查找其关键字等于key的数据元素
*/
Status SearchBST(BiTree T, KeyType key, BiTree f, BiTree &p){
	
	//查找不成功 
	//if(!T)  <=> if(T == NULL)
	if(!T) {
		
		//p指向其双亲结点，f也指向此结点
		//也就是查找路径上访问的最后一个结点                     
		p = f;
		
		//查找失败 
		return FALSE;
	}//if
	else if(EQ(key, T->data.key)) {  //查找成功 
		
		//p指向找到的数据元素结点
		p = T;
		
		//查找成功 
		return TRUE;
	}//else if
	else if LT(key, T->data.key) { //在左子树中继续查找   
		
		//递归地在左子树中继续查找
		return SearchBST(T->lchild, key, T, p);
	}//else if 
	else { //在右子树中继续查找 
	    
		//递归地在右子树中继续查找
		return SearchBST(T->rchild, key, T, p);
	}//else 
}//SearchBST 

/*  
	函数：InsertBST
	参数：BiTree &T 二叉排序树引用 
	      TElemType e 在T中插入元素e 
	返回值：状态码，插入成功返回TRUE，否则返回FALSE 
	作用：当二叉排序树T中不存在关键字等于e.key的数据元素时，
		  插入e并返回TRUE。否则返回FALSE
*/
Status InsertBST(BiTree &T, TElemType e){
	
	//工作指针 
	BiTree s, p; 
	
	//若查找不成功则将e插入到二叉排序树中 
	if(!SearchBST(T, e.key, NULL, p)){
		
		//申请一个新的结点，用于存放关键字e，并使s指向它 
		s = (BiTree)malloc(sizeof(BiNode));
		
		//检查内存申请是否成功 
		if(!s) { //if(!s) <=> if(s == NULL) 
	    	exit(OVERFLOW);
		}//if
		
		//将关键字e保存到s指向的新结点 
		s->data = e;
		
		//在二叉排序树中插入的结点一定是叶子结点
		//叶子结点左右孩子指针域均为NULL 
		s->lchild = s->rchild = NULL;
		
		//被插结点*s为新的根结点
		if(!p) { //if(!p) <=> if(p == NULL)
	    	
	    	//根指针T指向s指向的新结点 
			T = s;
	    }//if 
	    //被插结点*s为左孩子
		else if LT(e.key, p->data.key) { 
			
			//将s指向的结点挂到p指向的被插结点的左孩子指针域上 
	    	p->lchild = s;
	    }//else if 
	    //被插结点*s为右孩子
		else {
			
			//将s指向的结点挂到p指向的被插结点的右孩子指针域上 
	    	p->rchild = s;
		}//else
		
		//插入成功 
		return TRUE; 
    }//if
    else {
		
		//树中已有关键字相同的结点，不再插入
		//插入失败 
    	return FALSE;      
	}//else  
}//InsertBST 

/*  
	函数：Delete
	参数：BiTree &p 指向二叉排序树中待删除的结点 
	返回值：状态码，删除成功返回TRUE，否则返回FALSE 
	作用：从二叉排序树中删除结点p，并重接他的左子树和右子树
*/
Status Delete(BiTree &p){
	
	//工作指针q指向被删除结点 
	BiTree q, s;
	
	//若p右子树为空则只需重接他的左子树
	//在左分支上删除一个没有右孩子的结点，只需要把它下面 
	//的左子树整体挂到它的双亲结点上就可以。
	//这里有一个技巧，p是一个引用，被修改后结果会被带回，
	//所以p指向的结点不论是其双亲的左孩子还是右孩子都是一样的操作
	//不会破坏二叉排序树左小右大的定义，
	//所以无需考虑p是其双亲的左孩子还是右孩子。 
	//if(!p->rchild) <=> if(p->rchild == NULL) 
	if(!p->rchild){ 
		
		//q指向被删除结点 
		q = p;
		
		//p指向被删结点的左子树根结点 
		p = p->lchild;
		
		//释放被删除结点的存储空间 
		free(q);
	}//if
	//左子树为空则只需重接他的右子树
	//在右分支上删除一个没有左孩子的结点，只需要把它下面 
	//的左子树整体挂到它的双亲结点上就可以。
	//if(!p->lchild) <=> if(p->lchild == NULL)
	else if(!p->lchild) { 
		
		//q指向被删除结点 
		q = p;
		
		//p指向被删结点的右子树根结点
		p = p->rchild;
		
		//释放被删除结点的存储空间 
		free(q);
	}//else if
	//左右子树均不空（最麻烦的情况）
	else{ 
		
		//q指向被删除结点 
		q = p;
		
		//s指向p的左子树根结点 
		s = p->lchild;
		
		//转左，然后向右到尽头 
		//循环结束后，s指向p左子树的最右子树根结点 ，
		//也就是被删结点的前驱 
		//q指向s的前驱 
		while(s->rchild) {
			
			q = s;
			s = s->rchild;
		}//while
		
		//这里没有去把s指向的结点与p指向的结点进行调换
		//而是只替换里面的值。 s指向的结点就这样变成了被删除结点 
		//q此时也不再指向被删除结点。 
		p->data = s->data;
		
		//p的左子树根结点有右孩子 
		if(q != p) { //重接*q的右子树 
			
			//这种情况下s指向的结点将会被删除，
			//s指向的结点是q指向结点的右孩子，
			//且s指向的结点没有右子树，但不清楚是否有左子树 
			//删除后q的右孩子指针域就会腾出来 
			//所以要把s的左子树（左子树上所有结点值均>q结点值但<s结点值）
			//接到q的右子树上 
			q->rchild = s->lchild;
		}//if 
		//p的左子树根结点没有右孩子
		else { //重接*q的左子树
		 
			//这种情况下s指向的结点将会被删除，
			//s指向的结点是q指向结点的左孩子，
			//且s指向的结点没有右子树，但不清楚是否有左子树 
			//s和p指向结点值互换之后，需要把S的左子树
			//接到p的左子树上，也就是q的左子树上 
			q->lchild = s->lchild; 
		}//else
		
		//释放s指向的结点 
		free(s);
	}//else
	
	//删除成功 
	return TRUE; 
}//Delete

/*  
	函数：DeleteBST
	参数：BiTree &T 二叉排序树引用 
	      KeyType key 待删除关键字 
	返回值：状态码，删除成功返回TRUE，否则返回FALSE 
	作用：若二叉排序树T中存在关键字等于key的数据元素时，
	      则删除该数据元素的结点并返回TRUE，否则返回FALSE
*/
Status DeleteBST(BiTree &T, KeyType key){
	
	//根结点为空，没必要扫描左右子树了，直接返回 
	if(!T) {
		
		//不存在关键字等于key的数据元素
		return ERROR;
	}//if 
	else{
		
		//找到关键字等于key的数据元素
		if(EQ(key, T->data.key)){
		    
			printf("找到关键字为%d的记录了，接下来要删除它！\n", key);
		    //if(Delete(T)) <=> if(Delete(T) == FALSE)
			if(Delete(T)){
		    	printf("删除成功！O(∩_ ∩)O\n");
		    	return OK; 
			}//if 
			else{
				printf("删除失败！╮(╯▽╰)╭\n");
				return ERROR;
			}
		}//if 
		//待删除关键字小于当前结点关键字 
		else if(LT(key, T->data.key)) {
			
			//递归地在左子树上删除关键字 
			return DeleteBST(T->lchild, key);
		}//else if 
		//待删除关键字大于当前结点关键字 
		else {
			
			//递归地在右子树上删除关键字
			return DeleteBST(T->rchild, key);
		}//else 
	}//else 
}//DeleteBST 

//-------------------------------------------主函数--------------------------------------------------- 
int main(){
	
	BiTree T = NULL, p = NULL;     
	KeyType key; 
	Status flag;     
	TElemType e;
	char ch;
	char menu_main[] = "\n--------------------------------二叉排序树引用版--------------------------------\n"
	                   "\t\t\t1.构建一棵二叉排序树。\n" 
	                   "\t\t\t2.在二叉排序树中查找关键字\n"
                       "\t\t\t3.在二叉排序树中插入关键字\n" 
					   "\t\t\t4.在二叉排序树中删除关键字\n"
                       "\t\t\t5.中序遍历二叉排序树\n"  
					   "\t\t\t6.退出程序\n\n"
	                   "请选择您所要执行的操作："; 
	while(1){
		printf(menu_main);
		//逗号表达式以最后一个表达式值为准 
		switch(ch = getchar(), ch){  //接受一个字符到键盘 
			case '1':{
				CreateBST(T);
				printf("您创建的二叉排序树的中序遍历序列如下：");
				InOrderTraverse(T, PrintElement); 
				break;
			}//case
			case '2':{
				if(!T){
					printf("二叉排序树还未建立，请先建立后再操作！\n");
					break;
				}//if
				printf("请输入您想要查找的关键字(整数)：");
				scanf("%d", &key); 
				flag=SearchBST(T, key, NULL, p);
				if(!flag)
				    printf("查找失败！\n");
				else
				    printf("查找成功！\n"); 
				break;
			}//case
			case '3':{
				if(!T){
					printf("二叉排序树还未建立，请先建立后再操作！\n");
					break;
				}//if
				printf("请输入您想要插入的关键字(整数)：");
				scanf("%d", &e.key); 
				flag=InsertBST(T, e);
				if(!flag)
				    printf("插入失败！\n");
				else
				    printf("插入成功！\n"); 
				printf("插入操作后二叉排序树的中序遍历序列如下：");
				InOrderTraverse(T, PrintElement);
				break;
			}//case
			case '4':{
				if(!T){
					printf("二叉排序树还未建立，请先建立后再操作！\n");
					break;
				}//if
				printf("请输入您想要删除的关键字(整数)：");
			    scanf("%d", &key); 
				DeleteBST(T, key);
				printf("删除操作后二叉排序树的中序遍历序列如下：");
				InOrderTraverse(T, PrintElement);
				break;
			}//case
			case '5':{
				printf("二叉排序树的中序遍历序列：");
				InOrderTraverse(T, PrintElement); 
				break;
			}//case
			case '6':{
				exit(0);
				break;
			}//case
			default :{
				printf("输入非法，请输入数字1-6！\n");
			}//default
		}//switch
		printf("\n");
		system("pause");
		system("cls");
		fflush(stdin); 
	}//while 		
	return 0;
}//main

/*


--------------------------------二叉排序树引用版--------------------------------
                        1.构建一棵二叉排序树。
                        2.在二叉排序树中查找关键字
                        3.在二叉排序树中插入关键字
                        4.在二叉排序树中删除关键字
                        5.中序遍历二叉排序树
                        6.退出程序

请选择您所要执行的操作：1
您想创建一棵含有几个顶点的二叉排序树，请输入顶点数，并按回车确认：10
请输入10个整数作为关键字，中间用空格隔开，并按Enter确认
22 34 12 3 100 56 77 43 23 2 1
二叉排序树创建完成
您创建的二叉排序树的中序遍历序列如下： 2  3  12  22  23  34  43  56  77  100
请按任意键继续. . .

请选择您所要执行的操作：5
二叉排序树的中序遍历序列： 2  3  12  22  23  34  43  56  77  100
请按任意键继续. . .


请选择您所要执行的操作：2
请输入您想要查找的关键字(整数)：12
查找成功！

请按任意键继续. . .

请选择您所要执行的操作：3
请输入您想要插入的关键字(整数)：23
插入失败！
插入操作后二叉排序树的中序遍历序列如下： 2  3  12  22  23  34  43  56  77  100
请按任意键继续. . .

请选择您所要执行的操作：4
请输入您想要删除的关键字(整数)：4
删除操作后二叉排序树的中序遍历序列如下： 2  3  12  22  23  34  43  56  77  100
请按任意键继续. . .

请选择您所要执行的操作：6

--------------------------------
Process exited with return value 0
Press any key to continue . . .
*/ 
