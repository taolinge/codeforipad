
//>>>>>>>>>>>>>>>>>>>>>>>>>����ͷ�ļ�<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <stdio.h>       //ʹ���˱�׼�⺯�� 
#include <stdlib.h>      //ʹ���˶�̬�ڴ���亯�� 
#include "BiTree.cpp"    //�����������ʵ�� 

//>>>>>>>>>>>>>>>>>>>>>>>�Զ�����ų���<<<<<<<<<<<<<<<<<<<<<<<<<< 

#define OVERFLOW -2          //�ڴ����������
#define OK 1                 //��ʾ������ȷ�ĳ��� 
#define ERROR 0              //��ʾ��������ĳ���
#define TRUE 1               //��ʾ�߼���ĳ��� 
#define FALSE 0              //��ʾ�߼��ٵĳ���

//>>>>>>>>>>>>>>>>>>>>>>>�Զ�����������<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef int  Status;      //��������ֵ״̬������ 
typedef char TElemType;   //���н��Ԫ������ 
 
//-------------------���ĺ����ֵܱ�ʾ��----------------------- 
typedef struct CSNode{
     TElemType data;  //������,�洢������� 
     struct CSNode *firstchild, *nextsibling;  //����ָ������ֵ�ָ���� 
} CSNode, *CSTree;

//-------------------------------������Ҫ����--------------------------------

/*
	������CreateCSTree
	������CSTree &CT �������� 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERROR 
	���ã����ȸ������������н���ֵ��һ���ַ������ո��ַ���ʾ������
	       ������������ʾ��T
*/
Status CreateCSTree(CSTree &CT){
	
	//ch����Ӽ��̽��յ��ַ� 
	char ch;
	
	//�Ӽ��̽����ַ� 
	ch = getchar();
	
	//�û������˿ո񣬱�ʾ������ 
	if(ch == ' ') { 
	    CT = NULL;
	}//if 
	else{ //�û�����Ĳ��ǿո���Ҫ�����µĽ��
	
		//��������ռ� 
		//if(!(CT = (CSNode *)malloc(sizeof(CSNode))))
		//��Ч��
		//CT = (CSNode *)malloc(sizeof(CSNode))
		//if(!CT) <=> if(CT == NULL)
		if(!(CT = (CSNode *)malloc(sizeof(CSNode)))){
			printf("�ڴ����ʧ�ܣ�\n");
			exit(OVERFLOW); 
		}//if
		
		//���ɸ���� 
		CT->data = ch;
		
		//����������
		CreateCSTree(CT->firstchild); 
		
		//���������� 
		CreateCSTree(CT->nextsibling);
	}//else
	
	//�����ɹ� 
	return OK; 
}//CreateCSTree

/*
	������ExchangeToBiTree
	������CSTree &CT ��������
	      BiTree &T ������������ 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERROR 
	���ã���һ���ö��������ʾ����ת��Ϊ������
*/
Status ExchangeToBiTree(CSTree &CT, BiTree &T){
	
	//�����ĸ����Ϊ�գ���ôת���ɵĶ����������Ҳ�ǿ� 
	if(!CT) { //if(CT) <=> if(CT != NULL)
	    T = NULL;
	}//if 
	else{
		//�����µĽ��ռ�
		//if(!(T = (BiNode *)malloc(sizeof(BiNode))))
		//�൱���������д���
		//T = (BiNode *)malloc(sizeof(BiNode));
		//if(!T) <=> if(T == NULL) 
		if(!(T = (BiNode *)malloc(sizeof(BiNode)))){
			printf("�ڴ����ʧ�ܣ�\n");
			exit(OVERFLOW); 
		}//if
		
		//�������ж�Ӧ��㵽������ 
		T->data = CT->data;
		
		//�����ĺ���ת��Ϊ������������     
		ExchangeToBiTree(CT->firstchild, T->lchild);
		
		//�������ֵ�ת��Ϊ���������Һ���  
		ExchangeToBiTree(CT->nextsibling,T->rchild);  
	}//else 
	
	//�����ɹ� 
	return OK; 
}//ExchangeToBiTree

/*
	������DestoryTree
	������CSTree &CT �������� 
	����ֵ����
	���ã��������Ķ���ݹ��������
*/
void DestoryCSTree(CSTree &CT){
	
	//�ǿ���
	if(CT){  //if(CT) <=> if(CT != NULL)
		
		//���������ǿգ��ݹ�����ٺ������� 
		//if(CT->firstchild) <=> if(CT->firstchild != NULL) 
	   	if(CT->firstchild) {
		   DestoryCSTree(CT->firstchild);
		}//if
		 
		//�ֵ������ǿգ��ݹ�������ֵ�����
		//if(CT->nextsibling) <=> if(CT->nextsibling != NULL)
		if(CT->nextsibling) { 
		   DestoryCSTree(CT->nextsibling);
		}//if
		
		//�ͷŸ����
		free(CT);
		
		//ָ���ÿ� 
		CT = NULL; 
	}//if  
}//DestoryTree

/*
	������DestoryBiTree
	������BiTree &T ������������ 
	����ֵ���� 
	���ã����ն���������ݹ�����ٶ�����
*/
void DestoryBiTree(BiTree &T){
	
	//�ǿ��� 
	if(T){  //if(T) <=> if(T != NULL)
	
		//�������ǿ�,�ݹ������������
	   	if(T->lchild)  {
	   		DestoryBiTree(T->lchild);
	   	}//if 
		
		//�������ǿ�,�ݹ������������
		if(T->rchild) {
			DestoryBiTree(T->rchild);
		}//if 
		    
		//�ͷŸ����
		free(T);
		
		//ָ���ÿ� 
		T = NULL; 
	}//if 
}//DestoryTree

/*
	������DestoryTree
	������CSTree &CT �������� 
	      BiTree &T  ������������ 
	����ֵ����
	���ã��������Ͷ�����
*/
void DestoryTree(CSTree &CT, BiTree &T){
	
	//������ 
	DestoryCSTree(CT);
	
	//���ٶ����� 
	DestoryBiTree(T);
	
	printf("\n->���ɵ����Ͷ������ѱ����٣�"); 
}//DestoryTree

//-----------------------------������----------------------------------- 
int main(int argc,char *argv[]){
	printf("----------------------------------  ����Ӧ��  ----------------------------------\n");
	BiTree T=NULL;     //����һ�ö�����
	CSTree CT=NULL;    //����һ����ͨ��
	printf("         ---------------------------���Ľ���----------------------              \n");
	printf("->�밴�����ȸ������������У����п��������ÿո���䣬��ɺ�����س�ȷ��\n"); 
	CreateCSTree(CT);
	printf("         ---------------------------����ת��----------------------              \n");
	printf("->���ڽ��������ת��Ϊ���Ӧ�Ķ�����...\n");
	ExchangeToBiTree(CT,T); 
	printf("->ת������ִ����ϣ�\n");
	printf("\n         -------------------------�������ı���--------------------              ");
	printf("\n\n��������ݹ�  �㷨�����"); PreOrderTraverse(T,PrintElement);
	printf("\n\n��������ݹ�  �㷨�����"); InOrderTraverse(T,PrintElement);
	printf("\n\n��������ݹ�  �㷨�����"); PostOrderTraverse(T,PrintElement); 
	printf("\n\n��������ǵݹ��㷨�����"); PreOrderTraverse1(T,PrintElement);
	printf("\n\n��������ǵݹ��㷨�����"); InOrderTraverse1(T,PrintElement);
	printf("\n\n��������ǵݹ��㷨�����"); PostOrderTraverse1(T,PrintElement);
  	printf("\n\n��������ǵݹ��㷨�����"); LevelOrderTraverse1(T,PrintElement); 
  	printf("\n         -------------------------����������Ϣ--------------------              ");
  	printf("\n�ö������ĸ߶ȣ�%d",BiTreeDepth(T)); 
  	LeafNodeNum(T);
  	printf("\n��������Ҷ�ӽ��ĸ�����%d", LNM);
	printf("\n�������ܽ������%d",NodeSubNum(T) );
	printf("\n\n         -------------------------  ��������  --------------------              ");
	DestoryTree(CT, T); 
	printf("\n->�㷨��ʾ������"); 
	system("pause"); 
	return 0;
}//main

/*-----------------------------------------------���Լ�¼-------------------------------------------------
������PPT P98 ҳ��Ϊ������֤����¼���Թ���
ͨ�����Խ�����׷��֣������ȸ����кͺ�����зֱ�����ת����Ķ����������������������ͬ,
��Ҳ��Դ������ת��������ִ��ԭ�� 
 �����ȸ�����    A B E F C D G H I J K
 ���ĺ������    E F B C I J K H G D A
 ��������������  A B E F C D G H I J K
 ��������������  E F B C I J K H G D A
 
----------------------------------  ����Ӧ��  ----------------------------------

         ---------------------------���Ľ���----------------------

->�밴�����ȸ������������У����п��������ÿո���䣬��ɺ�����س�ȷ��
ABE*F**C*DGHI*J*K******�L   
    //˵�����˴���*�ǿո�Ϊ����ȷ�������˼����ո񽫿ո��滻��*����������ʱ�뽫*�Ļؿո�
	        �L��ʾ�س�ȷ��    ���루��ֱ�Ӹ��ƣ���Ҫ���ƨL����ABE F  C DGHI J K      �L
         ---------------------------����ת��----------------------

->���ڽ��������ת��Ϊ���Ӧ�Ķ�����...

->ת������ִ����ϣ�

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
�������ܽ������11

         -------------------------  ��������  --------------------
->���ɵ����Ͷ������ѱ����٣�
->�㷨��ʾ�������밴���������. . .

*/
