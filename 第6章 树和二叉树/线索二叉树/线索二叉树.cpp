//>>>>>>>>>>>>>>>>>>>>>>>>>����ͷ�ļ�<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <stdio.h>       //ʹ���˱�׼�⺯�� 
#include <stdlib.h>      //ʹ���˶�̬�ڴ���亯�� 

//>>>>>>>>>>>>>>>>>>>>>>>�Զ�����ų���<<<<<<<<<<<<<<<<<<<<<<<<<< 

#define OVERFLOW -2          //�ڴ����������
#define OK 1                 //��ʾ������ȷ�ĳ��� 
#define ERROR 0              //��ʾ��������ĳ���
#define TRUE 1               //��ʾ�߼���ĳ��� 
#define FALSE 0              //��ʾ�߼��ٵĳ���

//>>>>>>>>>>>>>>>>>>>>>>>�Զ�����������<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef char TElemType;
typedef int Status;

//����NILΪ�ո� 
TElemType NIL = ' ';

//------------------- �������Ķ��������洢��ʾ --------------------
//����ö�����Ͷ���ָ���־λ 
typedef enum{
	Link,   //Link(0)��  ָ�� 0
	Thread  //Thread(1)������ 1
}PointerTag; 

typedef struct BiThrNode{
	TElemType data;                     //�����򣬴洢�ڵ����� 
	struct BiThrNode *lchild, *rchild;  //���Һ���ָ��
	PointerTag LTag, RTag;              //���ұ�־
}BiThrNode, *BiThrTree;

//---------------------------��������������---------------------------- 

/*
	������CreateBiThrTree
	������BiThrTree &T ���������������� 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERROR 
	���ã����������������������н���ֵ����������������T��
	      �ո��ʾ�ս��
*/
Status CreateBiThrTree(BiThrTree &T) {
	
	//����Ӽ��̽��յ��ַ� 
	TElemType ch;
	scanf("%c", &ch);
	
	//�������˿ո���˽ڵ�Ϊ�� 
	if(ch == NIL) {
		T = NULL;	
	}//if 
	else{ //������Ĳ��ǿո��򴴽��½�㲢��ӵ������������ĺ���λ�� 
		//��������洢�ռ� 
		T = (BiThrTree)malloc(sizeof(BiThrNode));
		
		//���ռ�����Ƿ�ɹ� 
		if(!T) { 
			exit(OVERFLOW);
		}//if 
		
		//������㸳ֲ
		T->data = ch;
		
		//�ݹ�ع���������
		CreateBiThrTree(T->lchild);
		
		//�������������־��Ϊָ��
		if(T->lchild) {
			T->LTag = Link; 
		}//if
		
		//�ݹ�ع���������
		CreateBiThrTree(T->rchild);
		
		//�����Һ������ұ�־��Ϊָ��
		if(T->rchild) {
			T->RTag = Link;
		}//if
	}//else
	
	//�����ɹ� 
	return OK; 
}//CreateBiThrTree

//---------------------------- ���������� --------------------------- 

//ȫ�ֱ�����ʼ��ָ��ոշ��ʹ��Ľ��
BiThrTree pre;

/*
	������InThreading
	������BiThrTree p ָ����������������ָ��p 
	����ֵ����
	���ã�ͨ����������ݹ�ض�ͷ����������������������������
	      ������֮��preָ�����һ����㡣
	      �˺����ᱻInOrderThreading�������á�  
*/
void InThreading(BiThrTree p) {
	
	//��������������
	if(p) {
		
		//�ݹ�������������
		InThreading(p->lchild);
		
		//�����Ѿ����ʹ�ǰ����㣬��ʱ�Ϳ������ǰ�������������ˡ�
		//��ǰ����ǰ������preָ��Ľ�㡣�����ǰ���û������
		//��ô���ӵ�ָ����Ϳ����������ǰ������������Ϣ�� 
		
		//����ǰ���û�����ӣ�����ָ������Դ������ 
		if(!p->lchild) {
			
			//���־Ϊǰ������
			p->LTag = Thread;
			
			//����ָ��ָ��ǰ�� 
			p->lchild = pre; 
		}//if
		
		//��ʱ��δ���ʺ�̽�㣬������ȷ����ǰ���pһ����ǰ�����pre 
		//�ĺ�̣�����Ҫ��ǰ�����ĺ��ָ��������������Ϣ 
		 
		//ǰ��û���Һ���
		if(!pre->rchild) {
			
			//ǰ�����ұ�־Ϊ����(���)
			pre->RTag = Thread;
			
			//ǰ���Һ���ָ��ָ������(��ǰ���p)
			pre->rchild = p;
		}//if 
		
		//ʹpreָ��Ľ��p����ǰ�� 
		pre = p;
		
		//�ݹ�������������
		InThreading(p->rchild); 
	}//if 
}//InThreading

/*
	������InOrderThreading
	������BiThrTree &Thrt ͷ�������� 
	      BiThrTree T ָ������������������ָ�� 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERROR 
	���ã��������������T��������������������
*/
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T) {
	
	//����ͷ����ڴ�ռ� 
	//if(!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode))))
	//�൱���������д��룺
	//Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
	//if(!Thrt)  <=>  if(Thrt == NULL)
	if(!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode)))) {
		//�ڴ����ʧ��
		exit(OVERFLOW);
	}//if
	
	//��ͷ��㣬���־Ϊָ��
	Thrt->LTag = Link;
	
	//�ұ�־Ϊ����
	Thrt->RTag = Thread;
	
	//��ָ��ָ�������� 
	Thrt->rchild = Thrt;
	
	//���������գ�����ָ��ָ�������� 
	if(!T) { //if(!T) <=> if(T == NULL)
		Thrt->lchild = Thrt;
	}//if 
	else{
		//ͷ������ָ��ָ������
		Thrt->lchild = T;
		
		//pre(ǰ��)�ĳ�ֵָ��ͷ���
		pre = Thrt;
		
		//�����������������������preָ��������������һ�����
		//InThreading(T)�����ݹ������˳�ͷ��������������������� 
		InThreading(T);
		
		//���һ��������ָ��ָ��ͷ���
		pre->rchild = Thrt;
		
		//���һ�������ұ�־Ϊ����
		pre->RTag = Thread;
		
		//ͷ������ָ��ָ��������������һ�����
	 	Thrt->rchild = pre;
	}//else
	
	//�����ɹ� 
	return OK;
}//InOrderThreading

/*
	������Print
	������TElemType c �����ʵ�Ԫ�� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã�����Ԫ��e�ĺ�����ͨ���޸ĸú��������޸�Ԫ�ط��ʷ�ʽ��
	      �ú���ʹ��ʱ��Ҫ��ϱ�������һ��ʹ�á� 
*/
Status Print(TElemType c){
	
	//�Կ���̨����ķ�ʽ����Ԫ�� 
   	printf(" %c ", c);
   	
   	//�����ɹ� 
   	return OK; 
}//Print

/*
	������InOrderTraverse_Thr
	������BiThrTree T ָ������������������ָ��
	      Status(*Visit)(TElemType) ����ָ�룬ָ��Ԫ�ط��ʺ��� 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERROR 
	���ã������������������T(ͷ���)�ķǵݹ��㷨��
*/
Status InOrderTraverse_Thr(BiThrTree T, Status(*Visit)(TElemType)) {
	
	//����ָ��p 
	BiThrTree p;
	
	//pָ�������������ĸ����
	p = T->lchild;
	
	//�������������ʱ��p==T
	while(p != T) {
		
		//�ɸ����һֱ�ҵ���������������
		while(p->LTag == Link) { 
	   		p = p->lchild;
	   	}//while
	   	
	   	//���÷��ʺ������ʴ˽��
		Visit(p->data);
		
		//p->rchild������(���)���Ҳ��Ǳ��������һ�����
		while(p->RTag == Thread && p->rchild != T) {
			p = p->rchild;
			
			//���ʺ�̽��
			Visit(p->data);
		}//while
		
		//��p->rchild��������(���Һ���)��pָ���Һ��ӣ�����ѭ����
		//�����������������ĵ�1�����
	 	p = p->rchild;
	}//while 
	
	//�����ɹ� 
	return OK;      
}//InOrderTraverse_Thr

/*
	������DestroyBiTree
	������BiThrTree &T Tָ����������������� 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERROR 
	���ã��ݹ��������������������DestroyBiThrTree�������á� 
*/
Status DestroyBiTree(BiThrTree &T) {
	
	//�ǿ���
	if(T) { //if(T) <=> if(T != NULL) 
		
		//�����������ݹ������������
		if(T->LTag == Link) {
			DestroyBiTree(T->lchild);
		}//if
	   
	   	//������Һ�����ݹ������������
		if(T->RTag == Link) {
			DestroyBiTree(T->rchild);
		}//if 
	   
	   	//�ͷŸ����
		free(T);
		
		//ָ���ÿ� 
		T = NULL;
	}//if
	
	//�����ɹ� 
	return OK;
}//DestroyBiTree

/*
	������DestroyBiTree
	������BiThrTree &Thrt Thrtָ������������ͷ��� 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERROR 
	���ã�������������Thrt���ڣ��ݹ����������������Thrt�� 
*/
Status DestroyBiThrTree(BiThrTree &Thrt) {
	
	//ͷ������
	if(Thrt) {
		
		//���������ڣ���ݹ�����ͷ���lchild��ָ������������ 
		if(Thrt->lchild) { //if(Thrt->lchild) <=> if(Thrt->lchild != NULL)
			DestroyBiTree(Thrt->lchild);
		}//if 
		
		//�ͷ�ͷ���
		free(Thrt);
		
		//����������Thrtָ�븳0
		Thrt = NULL;
	}//if
	
	//�����ɹ� 
	return OK;
}//DestroyBiThrTree

int main(int argc, char** argv) {
	
	printf("---------------------�������������Գ���-----------------------\n");
	
	BiThrTree H, T;
	
	//ʹ���û���������������������һ��û�б��������Ķ����� 
	printf("�밴�������˳��������������ո��ʾ��������������ɺ󰴻س�ȷ��\n");
	CreateBiThrTree(T);
	
	//���������������������������
	InOrderThreading(H, T);
	
	//��������������������������
	printf("�������(���)����������:\n");
	InOrderTraverse_Thr(H, Print);
	printf("\n");
	
	//��������������
	DestroyBiThrTree(H);
}//main 

/*
---------------------�������������Գ���-----------------------
�밴�������˳��������������ո��ʾ��������������ɺ󰴻س�ȷ��
ABE*F**C*DGHI*J*K******�L   
    //˵�����˴���*�ǿո�Ϊ����ȷ�������˼����ո񽫿ո��滻��*����������ʱ�뽫*�Ļؿո�
	        �L��ʾ�س�ȷ��    ���루��ֱ�Ӹ��ƣ���Ҫ���ƨL����ABE F  C DGHI J K      �L
�������(���)����������:
 E  F  B  C  I  J  K  H  G  D  A

--------------------------------
Process exited with return value 0
Press any key to continue . . .
*/
