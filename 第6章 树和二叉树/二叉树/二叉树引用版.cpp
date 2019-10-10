
/***************************�������ĳ�����������ADT����**************************** 
	ADT BinaryTree{
	���ݶ���D��D�Ǿ�����ͬ���Ե�����Ԫ�صļ��ϡ�
	���ݹ�ϵR��
	  ��D=������R=������BinaryTreeΪ�ն�������
	  ��D�٦�����R={H}��H�����¶�Ԫ��ϵ��
	    ��1����D�д���Ωһ�ĳ�Ϊ��������Ԫ��root�����ڹ�ϵH����ǰ����
	    ��2����D-{root}�٦��������D-{root}={D1,Dr}����D1��Dr =����
	    ��3����D1�٦�����D1�д���Ωһ��Ԫ��x1��<root,x1>��H���Ҵ���D1�ϵĹ�ϵH1 ?H��
		     ��Dr�٦�����Dr�д���Ωһ��Ԫ��xr��<root,xr>��H���Ҵ���Dr�ϵĹ�ϵHr ?H��
			 H={<root,x1>,<root,xr>,H1,Hr}��
	    ��4��(D1,{H1})��һ�÷��ϱ�����Ķ���������Ϊ������������
		     (Dr,{Hr})��һ�÷��ϱ�����Ķ���������Ϊ������������
	����������
		  InitBiTree( &T )
		    �������������ն�����T��
		  DestroyBiTree( &T )
		    ��ʼ������������T�Ѵ��ڡ�
		    ������������ٶ�����T��
		  CreateBiTree( &T, definition )
		    ��ʼ������definition����������T�Ķ��塣
		    �����������definiton���������T��
		  ClearBiTree( &T )
		    ��ʼ������������T���ڡ�
		    �����������������T��Ϊ������
		  BiTreeEmpty( T )
		    ��ʼ������������T���ڡ�
		    �����������TΪ�ն��������򷵻�TRUE�����򷵻�FALSE��
		  BiTreeDepth( T )
		    ��ʼ������������T���ڡ�
		    �������������T����ȡ�
		  Root( T )
		    ��ʼ������������T���ڡ�
		    �������������T�ĸ���
		  Value( T, e )
		    ��ʼ������������T���ڣ�e��T��ĳ����㡣
		    �������������e��ֵ��
		  Assign( T, &e, value )
		    ��ʼ������������T���ڣ�e��T��ĳ����㡣
		    ������������e��ֵΪvalue��
		  Parent( T, e )
		    ��ʼ������������T���ڣ�e��T��ĳ����㡣
		    �����������e��T�ķǸ���㣬�򷵻�����˫�ף����򷵻ء��ա���
		  LeftChild( T, e )
		    ��ʼ������������T���ڣ�e��T��ĳ����㡣
		    �������������e�����ӡ���e�����ӣ��򷵻ء��ա���
		  RightChild( T, e )
		    ��ʼ������������T���ڣ�e��T��ĳ����㡣
		    �������������e���Һ��ӡ���e���Һ��ӣ��򷵻ء��ա���
		  LeftSibling( T, e )
		    ��ʼ������������T���ڣ�e��T��ĳ����㡣
		    �������������e�����ֵܡ���e��T�����ӻ������ֵܣ��򷵻ء��ա���
		  RightSibling( T, e )
		    ��ʼ������������T���ڣ�e��T��ĳ����㡣
		    �������������e�����ֵܡ���e��T���Һ��ӻ������ֵܣ��򷵻ء��ա���
		  InsertChild( T, p, LR, c )
		    ��ʼ������������T���ڣ�pָ��T��ĳ����㣬LRΪ0��1���ǿն�����c��T���ཻ��������Ϊ�ա�
		    �������������LRΪ0��1������cΪT��p��ָ���������������p��ָ����ԭ��������������Ϊc����������
		  DeleteChild( T, p, LR )
		    ��ʼ������������T���ڣ�pָ��T��ĳ����㣬LRΪ0��1��
		    �������������LRΪ0��1��ɾ��T��p��ָ���������������
		  PreOrderTraverse( T, visit() )
		    ��ʼ������������T���ڣ�Visit�ǶԽ�������Ӧ�ú�����
		    ����������������T����ÿ�������ú���Visitһ���ҽ�һ�Ρ�һ��visit()ʧ�ܣ������ʧ�ܡ�
		  InOrderTraverse( T, visit() )
		    ��ʼ������������T���ڣ�Visit�ǶԽ�������Ӧ�ú�����
		    ����������������T����ÿ�������ú���Visitһ���ҽ�һ�Ρ�һ��visit()ʧ�ܣ������ʧ�ܡ�
		  PostOrderTraverse( T, visit() )
		    ��ʼ������������T���ڣ�Visit�ǶԽ�������Ӧ�ú�����
		    ����������������T����ÿ�������ú���Visitһ���ҽ�һ�Ρ�һ��visit()ʧ�ܣ������ʧ�ܡ�
		  LevelOrderTraverse( T, visit() )
		    ��ʼ������������T���ڣ�Visit�ǶԽ�������Ӧ�ú�����
		    �����������α���T����ÿ�������ú���Visitһ���ҽ�һ�Ρ�һ��visit()ʧ�ܣ������ʧ�ܡ�
	}ADT BinaryTree
*/ 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>����ͷ�ļ�<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <stdio.h>       //ʹ���˱�׼�⺯�� 
#include <stdlib.h>      //ʹ���˶�̬�ڴ���亯�� 

//>>>>>>>>>>>>>>>>>>>>>>>>>�Զ�����ų���<<<<<<<<<<<<<<<<<<<<<<<<<<<< 

#define STACK_INIT_SIZE 50   //˳��ջ�洢�ռ��ʼ������ 
#define STACKINCREMENT 10    //˳��ջ�洢�ռ��������  
#define OVERFLOW -2          //�ڴ����������
#define OK 1                 //��ʾ������ȷ�ĳ��� 
#define ERROR 0              //��ʾ��������ĳ���
#define TRUE 1               //��ʾ�߼���ĳ��� 
#define FALSE 0              //��ʾ�߼��ٵĳ���

//>>>>>>>>>>>>>>>>>>>>>>>>>�Զ�����������<<<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef int  Status;      //״̬��Ϊint���ͣ����ڱ�����������1�ɹ�0ʧ�ܣ� 
typedef char TElemType;   //�������ڵ��������Ԫ������ 

//----------------�������Ķ�������洢��ʾ-------------------- 
typedef struct BiNode{
	TElemType  data;
	struct BiNode  *lchild,*rchild;   //���ӽ��ָ�� 
}BiNode,*BiTree;

//--------����ջ�Ͷ��е�ʵ�֣�ʵ����Ӧ�÷���ͷ�������ڱ���ԭ��ֻ�������ˣ�---------------- 
#include "Queue.cpp"     //������е�ʵ�� 
#include "Stack.cpp"     //����ջ��ʵ�� 
 
//---------------------����������Ҫ����--------------------------

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>1.���������<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 

/*
	������CreateBiTree
	������BiTree &T ���������� 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERROR 
	���ã��������������������н���ֵ��һ���ַ������ո��ַ���ʾ������
	      �ݹ�Ĺ�����������ʾ������T
*/
Status CreateBiTree(BiTree &T){  //���������й�������� 
	
	//ch�洢�Ӽ��̽��յ��ַ� 
	char ch;
	
	//�Ӽ��̽����ַ� 
	ch = getchar();
	
	//�ж�������ַ��Ƿ��ǿո� 
	if(ch == ' ') { //����ո��ʾ���Ϊ�� 
		T = NULL;
	}//if 
	else{ //���ǿո񣬰��������Դ�
	
		//������ռ�
		//if(!(T = (BiNode *)malloc(sizeof(BiNode))))
		//��Ч���������д���
		//T = (BiNode *)malloc(sizeof(BiNode));
		//if(!(T = (BiNode *)malloc(sizeof(BiNode)))) 
		if(!(T = (BiNode *)malloc(sizeof(BiNode)))){
			printf("�ڴ����ʧ�ܣ�\n");
			exit(OVERFLOW); 
		}//if
		
		//���ɸ����
		T->data = ch;
		
		//�ݹ�Ĺ���������      
		CreateBiTree(T->lchild);
		
		//�ݹ�Ĺ��������� 
		CreateBiTree(T->rchild);
	}//else
	
	//�����ɹ� 
	return OK; 
}//CreateBiTree

//>>>>>>>>>>>>>>>>>>>>2.�������ı�����4�ַ�����<<<<<<<<<<<<<<<<<<<<<<<<

/*
	������Print
	������TElemType e �����ʵ�Ԫ�� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã�����Ԫ��e�ĺ�����ͨ���޸ĸú��������޸�Ԫ�ط��ʷ�ʽ��
	      �ú���ʹ��ʱ��Ҫ��ϱ�������һ��ʹ�á� 
*/
Status PrintElement(TElemType e) {
	
	//���ÿ���̨����ķ�ʽ����Ԫ�� 
	printf(" %c ", e);
	
	//�����ɹ� 
	return OK;
}//PrintElement

//------------------------�ݹ��㷨----------------------------- 

/*
	������PreOrderTraverse
	������BiTree T ������T
	      Status(* Visit)(TElemType) ����ָ�룬ָ��Ԫ�ط��ʺ��� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã����ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	      �������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit 
*/
Status PreOrderTraverse(BiTree T, Status(* Visit)(TElemType)){
   
   	//���ڵ���� 
   	//if(T) <=> if(T != NULL)
	if(T){
		
		//1.���ʸ����
		//if(Visit(T->data)) <=> if(Visit(T->data) != ERROR)
		if(Visit(T->data)) {
			
			//2.�������ӣ��������� 
			if(PreOrderTraverse(T->lchild, Visit)) {
				
				//3.�����Һ��ӣ������������� 
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
	������InOrderTraverse
	������BiTree T ������T
	      Status(* Visit)(TElemType) ����ָ�룬ָ��Ԫ�ط��ʺ��� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã����ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	      �������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit 
*/
Status InOrderTraverse(BiTree T, Status(* Visit)(TElemType)){
    
    //���ڵ���� 
	if(T){	//if(T)  <=>  if(T != NULL)
		
		//1.���������� 
		if(InOrderTraverse(T->lchild,Visit)) {
			
			//2.���ʸ��ڵ� 
			//if(Visit(T->data)) <=> if(Visit(T->data) != ERROR)
			if(Visit(T->data)) {
				
				//3.���������� 
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
	������PostOrderTraverse
	������BiTree T ������T
	      Status(* Visit)(TElemType) ����ָ�룬ָ��Ԫ�ط��ʺ��� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã����ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	      �������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit 
*/
Status PostOrderTraverse(BiTree T, Status(* Visit)(TElemType)){
    
    //�������� 
	if(T){	//if(T)  <=>  if(T != NULL)
	
		//1.���������� 
		if(PostOrderTraverse(T->lchild, Visit)) {
			
			//2.���������� 
		    if(PostOrderTraverse(T->rchild, Visit)) {
		        
				//3.���ʸ���� 
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

//-----------------------�ǵݹ�����㷨---------------------------

/*
	������PreOrderTraverse1
	������BiTree T ������T
	      Status(* Visit)(TElemType) ����ָ�룬ָ��Ԫ�ط��ʺ��� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã����ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	      �������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit 
*/
Status PreOrderTraverse1(BiTree T, Status(* Visit)(TElemType)){
    
    //�������ǵݹ������Ҫ����ջ��������ݵ� 
	Stack S;
	
	//��ʼ��ջ 
	InitStack(S);
	
	//����ָ��pָ������������ 
	BiTree p = T;
	
	//��������������������ָ��p��Ϊ�ջ�ջ��Ϊ��
	//while(p || !(StackIsEmpty(S))) 
	//<=> while(p != NULL || StackIsEmpty(S) != 1)
	while(p || !(StackIsEmpty(S))){
		
		//�������� 
		if(p){

			//1.���ʸ���� 
			//if(Visit(p->data)) <=> if(Visit(p->data) != ERROR)
			if(!Visit(p->data)) { 
			    return ERROR;
			}//if 
			
			//��ָ���ջ
			Push(S, p);
			
			//2.����������
			p = p->lchild;
		}//if
		else{
			//��ָ����ջ
			Pop(S, p);
			
			//3.����������
			p = p->rchild;
		}//else
	}//while
	
	//����ջ
	DestoryStack(S); 
	
	//�����ɹ� 
	return OK;
} //PreOrderTraverse1

/*
	������InOrderTraverse1
	������BiTree T ������T
	      Status(* Visit)(TElemType) ����ָ�룬ָ��Ԫ�ط��ʺ��� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã����ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	      �������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit 
*/
Status InOrderTraverse1(BiTree T, Status(* Visit)(TElemType)){ 
    
    //�������ǵݹ������Ҫ����ջ��������ݵ�
	Stack S;
	
	//��ʼ��ջ 
	InitStack(S);
	
	//����ָ��pָ������ 
	BiTree p = T;
	
	//��������������������ָ��p��Ϊ�ջ�ջ��Ϊ��
	//while(p || !(StackIsEmpty(S))) 
	//<=> while(p != NULL || StackIsEmpty(S) != 1)
	while(p || !(StackIsEmpty(S))) {
		
		//����㲻Ϊ�� 
		if(p){
			
			//��ָ���ջ
			Push(S, p); 
			
			//1.����������
			p = p->lchild;
		}//if
		else{
			//��ָ����ջ
			Pop(S, p);
			
			//2.���ʸ����
			//if(Visit(p->data)) <=> if(Visit(p->data) != ERROR)
			if(!Visit(p->data)) {  
			    return ERROR;
			}//if
			
			//3.����������
			p = p->rchild; 
		}//else
	}//while
	
	//����ջ
	DestoryStack(S); 
	
	//�����ɹ� 
	return OK;
} //InOrderTraverse1

/*
	������PostOrderTraverse1
	������BiTree T ������T
	      Status(* Visit)(TElemType) ����ָ�룬ָ��Ԫ�ط��ʺ��� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã����ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	      �������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit 
*/
Status PostOrderTraverse1(BiTree T, Status(* Visit)(TElemType)){
    
    //p��q���ǹ���ָ��
	//pָ��ǰ�����Ľ�㣬qָ��p���һ�α����Ľ�� 
	BiTree p = T, q = NULL;
	
	//�������ǵݹ������Ҫ����ջ��������ݵ�
    Stack s;
    
    //��ʼ��ջ 
    InitStack(s);
	
	//��������������������ָ��p��Ϊ�ջ�ջ��Ϊ��
	//while(p || !StackIsEmpty(S)) 
	//<=> while(p != NULL || StackIsEmpty(S) != 1)
    while(p || !StackIsEmpty(s)) {
    	
    	//˳�����ĸ���һֱ�����֧��ֱ�����������֧�ľ�ͷ��Ҷ�ӽڵ�����ӣ��� 
 		while(p){
 			
 			//�������ջ 
          	Push(s, p);
          	
          	//���������� 
         	p = p->lchild;
       	}//while
       	
       	//����ָ��q��ֵΪNULL 
       	q = NULL;
       	
       	//ջ��Ϊ�� 
		while(!StackIsEmpty(s)){
			
			//pָ��ջ��Ԫ�� 
			GetTop(s, p);
			
			//���������ʾpָ����Ҷ�ӽ�����p�������������������� 
			if(p->rchild == NULL || p->rchild == q){
				
				//���ʸ���� 
				//if(Visit(p->data)) <=> if(Visit(p->data) != ERROR)
		      	if(!Visit(p->data)) { 
			        return ERROR;    
			    }//if
			    
				if(p == T) {
					return ERROR;
				}//if
				
				//qָ�����p����һ�α������Ľ��
				q = p;
				
				//��ָ���ջ 
          		Pop(s, p);
			}//if
			else{
				
				//���������� 
         		p = p->rchild;
         		
         		//�˳��ڲ�ѭ�� 
				break;				
			}//else
		}//while
    }//while
    
    //����ջ
	DestoryStack(s); 
	
	//�����ɹ� 
	return OK;
} //PostOrderTraverse1

/*
	������LevelOrderTraverse1
	������BiTree T ������T
	      Status(* Visit)(TElemType) ����ָ�룬ָ��Ԫ�ط��ʺ��� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã����ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	      �������������T���㷨����ÿ������Ԫ�ص��ú���Visit 
*/
Status LevelOrderTraverse1(BiTree T, Status(* Visit)(TElemType)){ 
    
    //���������Ҫ�õ����� 
	Queue Q;
	
	//����ָ��pָ������ 
	BiTree p = T;
	
	//����㲻Ϊ�� 
	if(T){ //if(T) <=>  if(T != NULL)
		//��ʼ������
	    InitQueue(Q);
	    
	    //����������
	    EnQueue(Q, T);
		
		//���в��� 
		//while(!QueueEmpty(Q)) <=> while(QueueEmpty(Q) == 0)
		while(!QueueEmpty(Q)){
			
			//�������� 
		   	DeQueue(Q, p);
		   	
		   	//���ʸ���� 
		   	if(!Visit(p->data)) { 
			   return ERROR;
			}//if
			
			//���Ӳ�Ϊ�� 
		   	if(p->lchild) {
		   		//��������� 
		   		EnQueue(Q, p->lchild);   
		   	}//if
		       
		   	if(p->rchild) {
		   		//�Һ�������� 
		   		EnQueue(Q, p->rchild);
		   	}//if 
	   }//while
	   
	   //������У�ʹ��ʾ���� 
	   printf("\n");
	   
	   //��������֮��Ҫ���٣��ͷ����ڴ�ռ� 
	   DestoryQueue(Q); 
    }//if
    
    //�����ɹ� 
	return OK;
} //LevelOrderTraverse1

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>3.����������Ϣ<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	������BiTreeDepth
	������BiTree T ������T
	����ֵ����������T���ڣ�����T����ȣ��߶ȣ������򷵻�0
	���ã���������T���ڣ��ݹ���������T����� 
*/
int BiTreeDepth(BiTree T){ 
	
	//Thigh�Ƕ������߶ȣ�leftThigh���������߶ȣ�rightThigh���������߶�
	int Thigh, leftThigh, rightThigh;
	
	//�����Ϊ�գ�����Ϊ0 
	if(!T) {
		return 0;
	}//if
	else{
		//����㲻Ϊ�գ���ݹ�ļ������ĸ߶�
		
		//�ݹ������������߶�
		leftThigh = BiTreeDepth(T->lchild);
		
		//�ݹ������������߶� 
		rightThigh = BiTreeDepth(T->rchild);
		
		//�����������ܸ߶Ȳ���ȣ��������ĸ߶ȶ���
		//Ӧȡ���������������и߶Ƚϴ�����Ϊ���ĸ߶� 
		if(leftThigh >= rightThigh) { 
		   Thigh = leftThigh + 1;
		}//if 
		else { 
		   Thigh = rightThigh + 1;
		}//else
	}//else
	
	//�������ĸ߶� 
	return Thigh;
}//BiTreeDepth

//ȫ�ֱ���LNM��¼�˶�����Ҷ�ӽڵ�ĸ��� 
int LNM = 0;

/*
	������LeafNodeNum
	������BiTree T ������T
	����ֵ����������T���ڣ�����T��Ҷ�ӽ����������򷵻�0
	���ã��ݹ��������Ҷ�ӽ��ĸ��� 
*/
int LeafNodeNum(BiTree T){ 
	
	//Ҷ�ӽ��������ǣ����Ӻ��Һ���ָ�����ΪNULL 
	if(T->lchild == NULL && T->rchild == NULL) { //��ǰ�����Ҷ�ӽ�� 
		LNM++;
	}//if
	else {
		//���Ӳ�Ϊ�� 
		if(T->lchild != NULL) {
			
			//�ݹ��ͳ����������Ҷ�ӽ�����Ŀ 
			LeafNodeNum(T->lchild);
		}//if
		
		//�Һ��Ӳ�Ϊ�� 
		if(T->rchild != NULL) {
			
			//�ݹ��ͳ����������Ҷ�ӽ�����Ŀ 
			LeafNodeNum(T->rchild);
		}//if
	}//else
}//LeafNodeNum

/*
	������NodeSubNum
	������BiTree T ������T
	����ֵ����������T���ڣ�����T���ܽ����������򷵻�0
	���ã�ͳ�ƶ��������ܽ�����
*/
int NodeSubNum(BiTree T){
	
	if(!T) {
		return 0;  //�����������
	}//if 
	else {
		//�������ܽ���� = �������ܽ���� + �������ܽ���� + ����1�� 
		return NodeSubNum(T->lchild) + NodeSubNum(T->rchild) + 1;
	} 
}//NodeSubNum


//-------------------------------------------������--------------------------------------------------- 
int main(int argc, char *argv[]){
	
	printf("----------------------------------���������ð�----------------------------------\n");
	BiTree T;     //����һ�ö�����
	
	printf("         -------------------------�������Ľ���--------------------              \n");
	printf("��������Ҫ��������������������(�������ÿո����)��\n");
	CreateBiTree(T); 
	
	printf("\n         -------------------------�������ı���--------------------              ");
	printf("\n\n��������ݹ�  �㷨�����");
	PreOrderTraverse(T,PrintElement);
	
	printf("\n\n��������ݹ�  �㷨�����");
	InOrderTraverse(T,PrintElement);
	
	printf("\n\n��������ݹ�  �㷨�����");
	PostOrderTraverse(T,PrintElement); 
	
	printf("\n\n��������ǵݹ��㷨�����");
	PreOrderTraverse1(T,PrintElement);
	
	printf("\n\n��������ǵݹ��㷨�����");
	InOrderTraverse1(T,PrintElement);
	
	printf("\n\n��������ǵݹ��㷨�����");
  	PostOrderTraverse1(T,PrintElement);
  	
  	printf("\n\n��������ǵݹ��㷨�����");
  	LevelOrderTraverse1(T,PrintElement); 
  	
  	printf("\n         -------------------------����������Ϣ--------------------              ");
  	printf("\n�ö������ĸ߶ȣ�%d",BiTreeDepth(T)); 
  	LeafNodeNum(T);
  	printf("\n��������Ҷ�ӽ��ĸ�����%d", LNM);
	printf("\n�������ܽ������%d",NodeSubNum(T) );
	
	return 0;
}//main

/*-----------------------------------------------���Լ�¼-------------------------------------------------
 
----------------------------------���������ð�----------------------------------
         -------------------------�������Ľ���--------------------
��������Ҫ��������������������(�������ÿո����)��
ABE*F**C*DGHI*J*K******�L
//˵�����˴���*�ǿո�Ϊ����ȷ�������˼����ո񽫿ո��滻��*����������ʱ�뽫*�Ļؿո�
 �L��ʾ�س�ȷ��    ���루��ֱ�Ӹ��ƣ���Ҫ���ƨL����ABE F  C DGHI J K      �L

         -------------------------�������ı���--------------------

��������ݹ�  �㷨����� A  B  E  F  C  D  G  H  I  J  K

��������ݹ�  �㷨����� E  F  B  C  I  J  K  H  G  D  A

��������ݹ�  �㷨����� F  E  K  J  I  H  G  D  C  B  A

��������ǵݹ��㷨����� A  B  E  F  C  D  G  H  I  J  K

��������ǵݹ��㷨����� E  F  B  C  I  J  K  H  G  D  A

��������ǵݹ��㷨����� F  E  K  J  I  H  G  D  C  B  A

��������ǵݹ��㷨����� A  B  E  C  F  D  G  H  I  J  K

         -------------------------����������Ϣ--------------------
�ö������ĸ߶ȣ�9
��������Ҷ�ӽ��ĸ�����2
�������ܽ������11
--------------------------------
Process exited with return value 0
Press any key to continue . . .

*/
