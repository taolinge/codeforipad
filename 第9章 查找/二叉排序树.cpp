//>>>>>>>>>>>>>>>>>>>>>>>>����ͷ�ļ�<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <stdio.h>       //ʹ���˱�׼�⺯�� 
#include <stdlib.h>      //ʹ���˶�̬�ڴ���亯��

//>>>>>>>>>>>>>>>>>>>>>>�Զ�����ų���<<<<<<<<<<<<<<<<<<<<<<<<<<< 
 
#define OVERFLOW -2          //�ڴ����������
#define OK 1                 //��ʾ������ȷ�ĳ��� 
#define ERROR 0              //��ʾ��������ĳ���
#define TRUE 1               //��ʾ�߼���ȷ�ĳ��� 
#define FALSE 0              //��ʾ�߼�����ĳ���
#define EQ(a,b) ((a)==(b))   //��� 
#define LT(a,b) ((a)< (b))   //С��
#define LQ(a,b) ((a)<= (b))  //С����� 

//>>>>>>>>>>>>>>>>>>>>>�Զ�����������<<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef int  Status;      //״̬��־ 
typedef int  KeyType;     //�ؼ�������
typedef struct{
	
	//�ؼ��� 
	KeyType key;
}TElemType;   

//----------------�������Ķ�������洢��ʾ-------------------- 
typedef struct BiNode{
	
	//������ 
	TElemType  data;
	
	//���Һ��ӽ��ָ��
	struct BiNode  *lchild, *rchild; 
}BiNode, *BiTree;

//-----------------------��������������Ҫ����---------------------------

//>>>>>>>>>>>>>>>>>>>>>  1.�����������Ĺ���  <<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	������CreateBST
	������BiTree &T �������������� 
	����ֵ��״̬�룬�����ɹ�����OK 
	���ã������û����봴��һ�ö��������� 
*/
Status CreateBST(BiTree &T){
	
	//���������������㺯������
	Status InsertBST(BiTree &T, TElemType e);
	
	//������������������ 
	int num;
	
	//��������Ĺؼ��� 
	TElemType e;
	
	//ȷ�����еĶ������� 
    printf("���봴��һ�ú��м�������Ķ����������������붥�����������س�ȷ�ϣ�");
    scanf("%d", &num);
    
    //����ؼ��� 
    printf("������%d��������Ϊ�ؼ��֣��м��ÿո����������Enterȷ��\n", num);
    for(int i = 0; i < num; i++) {
    	scanf("%d", &e.key);
     	InsertBST(T, e);
    }//for
    
    //�����ɹ� 
    printf("�����������������\n"); 
    return OK;
}//CreateBST


//>>>>>>>>>>>>>>>>>>>  2.�����������ı���  <<<<<<<<<<<<<<<<<<<<

/*
	������PrintElement
	������BiTree &T �������������� 
	����ֵ��״̬�룬�����ɹ�����OK 
	���ã�Ԫ�ط��ʺ���������ؼ���key
*/
Status PrintElement(KeyType key) {
	
	//�Կ���̨��ӡkey�ķ�ʽ���ʹؼ��� 
	printf(" %d ", key);
	
	//�����ɹ� 
	return OK;
}//PrintElement 

/*
	������InOrderTraverse
	������BiTree T ����������T
		  Status(* Visit)(KeyType) Ԫ�ط��ʺ��� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã����ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	      �������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
*/
Status InOrderTraverse(BiTree T, Status(* Visit)(KeyType)){ 
    
    //����㲻Ϊ�� 
    //if(T) <=> if(T == NULL) 
	if(T){
		
		//�������� 
		//if(InOrderTraverse(T->lchild, Visit)) <=>
		//if(InOrderTraverse(T->lchild, Visit) == ERROR)
		if(InOrderTraverse(T->lchild, Visit)) { 
		    
		    //���ʸ���� 
		    //if(Visit(T->data.key)) <=> if(Visit(T->data.key) == ERROR)
			if(Visit(T->data.key)) {
		    	
		    	//�����Һ���
				//if(InOrderTraverse(T->rchild, Visit)) <=>
				//if(InOrderTraverse(T->rchild, Visit) == ERROR) 
		        if(InOrderTraverse(T->rchild, Visit)) {
					
					//�����ɹ� 
					return OK;
				}//if
			}//if
		}//if 
			
		//����ʧ�� 
		return ERROR;
	} //if
	else {
		
		//�˽����ΪҶ�ӽ��ĺ��ӣ�NULL 
		return OK;
	}//else 
}//InOrderTraverse 

//>>>>>>>>>>>>>>>>>>>>2.�����������Ĳ����㷨<<<<<<<<<<<<<<<<<<<<<<<

/* ���ڶ����������в��ҹؼ��֣� 
	������SearchBST
	������BiTree T ����������T 
	      KeyType key �ؼ���
		  BiTree f ָ��fָ��T��˫�ף����ʼ����ֵΪNULL
		  BiTree &p �����ҳɹ���pָ���ҵ�������Ԫ�ؽ�㣬
		            ����pָ�����·���Ϸ��ʵ����һ�����
	����ֵ��״̬�룬���ҳɹ�����TRUE�����򷵻�FALSE 
	���ã��ڸ�ָ��T��ָ�Ķ����������еݹ�ز�����ؼ��ֵ���key������Ԫ��
*/
Status SearchBST(BiTree T, KeyType key, BiTree f, BiTree &p){
	
	//���Ҳ��ɹ� 
	//if(!T)  <=> if(T == NULL)
	if(!T) {
		
		//pָ����˫�׽�㣬fҲָ��˽��
		//Ҳ���ǲ���·���Ϸ��ʵ����һ�����                     
		p = f;
		
		//����ʧ�� 
		return FALSE;
	}//if
	else if(EQ(key, T->data.key)) {  //���ҳɹ� 
		
		//pָ���ҵ�������Ԫ�ؽ��
		p = T;
		
		//���ҳɹ� 
		return TRUE;
	}//else if
	else if LT(key, T->data.key) { //���������м�������   
		
		//�ݹ�����������м�������
		return SearchBST(T->lchild, key, T, p);
	}//else if 
	else { //���������м������� 
	    
		//�ݹ�����������м�������
		return SearchBST(T->rchild, key, T, p);
	}//else 
}//SearchBST 

/*  
	������InsertBST
	������BiTree &T �������������� 
	      TElemType e ��T�в���Ԫ��e 
	����ֵ��״̬�룬����ɹ�����TRUE�����򷵻�FALSE 
	���ã�������������T�в����ڹؼ��ֵ���e.key������Ԫ��ʱ��
		  ����e������TRUE�����򷵻�FALSE
*/
Status InsertBST(BiTree &T, TElemType e){
	
	//����ָ�� 
	BiTree s, p; 
	
	//�����Ҳ��ɹ���e���뵽������������ 
	if(!SearchBST(T, e.key, NULL, p)){
		
		//����һ���µĽ�㣬���ڴ�Źؼ���e����ʹsָ���� 
		s = (BiTree)malloc(sizeof(BiNode));
		
		//����ڴ������Ƿ�ɹ� 
		if(!s) { //if(!s) <=> if(s == NULL) 
	    	exit(OVERFLOW);
		}//if
		
		//���ؼ���e���浽sָ����½�� 
		s->data = e;
		
		//�ڶ����������в���Ľ��һ����Ҷ�ӽ��
		//Ҷ�ӽ�����Һ���ָ�����ΪNULL 
		s->lchild = s->rchild = NULL;
		
		//������*sΪ�µĸ����
		if(!p) { //if(!p) <=> if(p == NULL)
	    	
	    	//��ָ��Tָ��sָ����½�� 
			T = s;
	    }//if 
	    //������*sΪ����
		else if LT(e.key, p->data.key) { 
			
			//��sָ��Ľ��ҵ�pָ��ı����������ָ������ 
	    	p->lchild = s;
	    }//else if 
	    //������*sΪ�Һ���
		else {
			
			//��sָ��Ľ��ҵ�pָ��ı�������Һ���ָ������ 
	    	p->rchild = s;
		}//else
		
		//����ɹ� 
		return TRUE; 
    }//if
    else {
		
		//�������йؼ�����ͬ�Ľ�㣬���ٲ���
		//����ʧ�� 
    	return FALSE;      
	}//else  
}//InsertBST 

/*  
	������Delete
	������BiTree &p ָ������������д�ɾ���Ľ�� 
	����ֵ��״̬�룬ɾ���ɹ�����TRUE�����򷵻�FALSE 
	���ã��Ӷ�����������ɾ�����p�����ؽ�������������������
*/
Status Delete(BiTree &p){
	
	//����ָ��qָ��ɾ����� 
	BiTree q, s;
	
	//��p������Ϊ����ֻ���ؽ�����������
	//�����֧��ɾ��һ��û���Һ��ӵĽ�㣬ֻ��Ҫ�������� 
	//������������ҵ�����˫�׽���ϾͿ��ԡ�
	//������һ�����ɣ�p��һ�����ã����޸ĺ����ᱻ���أ�
	//����pָ��Ľ�㲻������˫�׵����ӻ����Һ��Ӷ���һ���Ĳ���
	//�����ƻ�������������С�Ҵ�Ķ��壬
	//�������迼��p����˫�׵����ӻ����Һ��ӡ� 
	//if(!p->rchild) <=> if(p->rchild == NULL) 
	if(!p->rchild){ 
		
		//qָ��ɾ����� 
		q = p;
		
		//pָ��ɾ��������������� 
		p = p->lchild;
		
		//�ͷű�ɾ�����Ĵ洢�ռ� 
		free(q);
	}//if
	//������Ϊ����ֻ���ؽ�����������
	//���ҷ�֧��ɾ��һ��û�����ӵĽ�㣬ֻ��Ҫ�������� 
	//������������ҵ�����˫�׽���ϾͿ��ԡ�
	//if(!p->lchild) <=> if(p->lchild == NULL)
	else if(!p->lchild) { 
		
		//qָ��ɾ����� 
		q = p;
		
		//pָ��ɾ���������������
		p = p->rchild;
		
		//�ͷű�ɾ�����Ĵ洢�ռ� 
		free(q);
	}//else if
	//�������������գ����鷳�������
	else{ 
		
		//qָ��ɾ����� 
		q = p;
		
		//sָ��p������������� 
		s = p->lchild;
		
		//ת��Ȼ�����ҵ���ͷ 
		//ѭ��������sָ��p��������������������� ��
		//Ҳ���Ǳ�ɾ����ǰ�� 
		//qָ��s��ǰ�� 
		while(s->rchild) {
			
			q = s;
			s = s->rchild;
		}//while
		
		//����û��ȥ��sָ��Ľ����pָ��Ľ����е���
		//����ֻ�滻�����ֵ�� sָ��Ľ�����������˱�ɾ����� 
		//q��ʱҲ����ָ��ɾ����㡣 
		p->data = s->data;
		
		//p����������������Һ��� 
		if(q != p) { //�ؽ�*q�������� 
			
			//���������sָ��Ľ�㽫�ᱻɾ����
			//sָ��Ľ����qָ������Һ��ӣ�
			//��sָ��Ľ��û������������������Ƿ��������� 
			//ɾ����q���Һ���ָ����ͻ��ڳ��� 
			//����Ҫ��s���������������������н��ֵ��>q���ֵ��<s���ֵ��
			//�ӵ�q���������� 
			q->rchild = s->lchild;
		}//if 
		//p�������������û���Һ���
		else { //�ؽ�*q��������
		 
			//���������sָ��Ľ�㽫�ᱻɾ����
			//sָ��Ľ����qָ��������ӣ�
			//��sָ��Ľ��û������������������Ƿ��������� 
			//s��pָ����ֵ����֮����Ҫ��S��������
			//�ӵ�p���������ϣ�Ҳ����q���������� 
			q->lchild = s->lchild; 
		}//else
		
		//�ͷ�sָ��Ľ�� 
		free(s);
	}//else
	
	//ɾ���ɹ� 
	return TRUE; 
}//Delete

/*  
	������DeleteBST
	������BiTree &T �������������� 
	      KeyType key ��ɾ���ؼ��� 
	����ֵ��״̬�룬ɾ���ɹ�����TRUE�����򷵻�FALSE 
	���ã�������������T�д��ڹؼ��ֵ���key������Ԫ��ʱ��
	      ��ɾ��������Ԫ�صĽ�㲢����TRUE�����򷵻�FALSE
*/
Status DeleteBST(BiTree &T, KeyType key){
	
	//�����Ϊ�գ�û��Ҫɨ�����������ˣ�ֱ�ӷ��� 
	if(!T) {
		
		//�����ڹؼ��ֵ���key������Ԫ��
		return ERROR;
	}//if 
	else{
		
		//�ҵ��ؼ��ֵ���key������Ԫ��
		if(EQ(key, T->data.key)){
		    
			printf("�ҵ��ؼ���Ϊ%d�ļ�¼�ˣ�������Ҫɾ������\n", key);
		    //if(Delete(T)) <=> if(Delete(T) == FALSE)
			if(Delete(T)){
		    	printf("ɾ���ɹ���O(��_ ��)O\n");
		    	return OK; 
			}//if 
			else{
				printf("ɾ��ʧ�ܣ��r(�s���t)�q\n");
				return ERROR;
			}
		}//if 
		//��ɾ���ؼ���С�ڵ�ǰ���ؼ��� 
		else if(LT(key, T->data.key)) {
			
			//�ݹ������������ɾ���ؼ��� 
			return DeleteBST(T->lchild, key);
		}//else if 
		//��ɾ���ؼ��ִ��ڵ�ǰ���ؼ��� 
		else {
			
			//�ݹ������������ɾ���ؼ���
			return DeleteBST(T->rchild, key);
		}//else 
	}//else 
}//DeleteBST 

//-------------------------------------------������--------------------------------------------------- 
int main(){
	
	BiTree T = NULL, p = NULL;     
	KeyType key; 
	Status flag;     
	TElemType e;
	char ch;
	char menu_main[] = "\n--------------------------------�������������ð�--------------------------------\n"
	                   "\t\t\t1.����һ�ö�����������\n" 
	                   "\t\t\t2.�ڶ����������в��ҹؼ���\n"
                       "\t\t\t3.�ڶ����������в���ؼ���\n" 
					   "\t\t\t4.�ڶ�����������ɾ���ؼ���\n"
                       "\t\t\t5.�����������������\n"  
					   "\t\t\t6.�˳�����\n\n"
	                   "��ѡ������Ҫִ�еĲ�����"; 
	while(1){
		printf(menu_main);
		//���ű��ʽ�����һ�����ʽֵΪ׼ 
		switch(ch = getchar(), ch){  //����һ���ַ������� 
			case '1':{
				CreateBST(T);
				printf("�������Ķ�������������������������£�");
				InOrderTraverse(T, PrintElement); 
				break;
			}//case
			case '2':{
				if(!T){
					printf("������������δ���������Ƚ������ٲ�����\n");
					break;
				}//if
				printf("����������Ҫ���ҵĹؼ���(����)��");
				scanf("%d", &key); 
				flag=SearchBST(T, key, NULL, p);
				if(!flag)
				    printf("����ʧ�ܣ�\n");
				else
				    printf("���ҳɹ���\n"); 
				break;
			}//case
			case '3':{
				if(!T){
					printf("������������δ���������Ƚ������ٲ�����\n");
					break;
				}//if
				printf("����������Ҫ����Ĺؼ���(����)��");
				scanf("%d", &e.key); 
				flag=InsertBST(T, e);
				if(!flag)
				    printf("����ʧ�ܣ�\n");
				else
				    printf("����ɹ���\n"); 
				printf("����������������������������������£�");
				InOrderTraverse(T, PrintElement);
				break;
			}//case
			case '4':{
				if(!T){
					printf("������������δ���������Ƚ������ٲ�����\n");
					break;
				}//if
				printf("����������Ҫɾ���Ĺؼ���(����)��");
			    scanf("%d", &key); 
				DeleteBST(T, key);
				printf("ɾ���������������������������������£�");
				InOrderTraverse(T, PrintElement);
				break;
			}//case
			case '5':{
				printf("����������������������У�");
				InOrderTraverse(T, PrintElement); 
				break;
			}//case
			case '6':{
				exit(0);
				break;
			}//case
			default :{
				printf("����Ƿ�������������1-6��\n");
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


--------------------------------�������������ð�--------------------------------
                        1.����һ�ö�����������
                        2.�ڶ����������в��ҹؼ���
                        3.�ڶ����������в���ؼ���
                        4.�ڶ�����������ɾ���ؼ���
                        5.�����������������
                        6.�˳�����

��ѡ������Ҫִ�еĲ�����1
���봴��һ�ú��м�������Ķ����������������붥�����������س�ȷ�ϣ�10
������10��������Ϊ�ؼ��֣��м��ÿո����������Enterȷ��
22 34 12 3 100 56 77 43 23 2 1
�����������������
�������Ķ�������������������������£� 2  3  12  22  23  34  43  56  77  100
�밴���������. . .

��ѡ������Ҫִ�еĲ�����5
����������������������У� 2  3  12  22  23  34  43  56  77  100
�밴���������. . .


��ѡ������Ҫִ�еĲ�����2
����������Ҫ���ҵĹؼ���(����)��12
���ҳɹ���

�밴���������. . .

��ѡ������Ҫִ�еĲ�����3
����������Ҫ����Ĺؼ���(����)��23
����ʧ�ܣ�
����������������������������������£� 2  3  12  22  23  34  43  56  77  100
�밴���������. . .

��ѡ������Ҫִ�еĲ�����4
����������Ҫɾ���Ĺؼ���(����)��4
ɾ���������������������������������£� 2  3  12  22  23  34  43  56  77  100
�밴���������. . .

��ѡ������Ҫִ�еĲ�����6

--------------------------------
Process exited with return value 0
Press any key to continue . . .
*/ 
