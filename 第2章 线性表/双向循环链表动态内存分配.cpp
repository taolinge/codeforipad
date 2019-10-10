
#include <stdio.h>          //ʹ���˱�׼�⺯�� printf(),scanf()
#include <stdlib.h>         //ʹ���˶�̬�ڴ���亯�� malloc(),free()
#define OVERFLOW -2         //�ڴ����������
#define OK 1                //��ʾ������ȷ�ĳ��� 
#define ERROR 0             //��ʾ��������ĳ��� 
typedef int Status;         //��typedef��int���������Ҳ���ڳ����ά��
typedef float ElemType;     //��typedef��float���������Ҳ���ڳ����ά��
typedef struct DuLNode{     //˫��ѭ�������C�������� 
	ElemType data;          //������ 
	struct DuLNode * prior; //ǰ��ָ���� 
	struct DuLNode * next;  //���ָ���� 
}DuLNode,* DuLinkList;

//-------------------------------˫��ѭ���������Ҫ����------------------------------------

/*
	������MallocList_DL
	������DuLinkList &L ˫��ѭ������ͷ����ָ�� 
	����ֵ����
	���ã���������ڴ�ռ�
*/
void MallocList_DL(DuLinkList &L){
	
	/*
		if(!(L = (DuLinkList)malloc(sizeof(DuLNode))))
		�൱���������д��룺
		L = (DuLinkList)malloc(sizeof(DuLNode))
		if(!L) <=> if(L == NULL) 
	*/
	if(!(L = (DuLinkList)malloc(sizeof(DuLNode)))){
		
		printf("�����ڴ�ʧ�ܣ�\n");
		exit(OVERFLOW);            
	}//if
}//MallocList_DL

/*
	������InitList_D
	������DuLinkList &L ˫��ѭ������ͷ����ָ��
	      int n ��ʼ�����ٸ����ݽڵ� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã���ʼ��һ������n������˫��ѭ������
*/ 
Status InitList_DL(DuLinkList &L, int n){
	
	//���մӼ�������Ľ������ֵ 
	ElemType e;
	
	//����ָ��p 
	DuLinkList p;
	
	//������һ��ͷ��㲢����������ͷָ��p��p��ʱָ��ͷ��㣩�ĺ��� 
	MallocList_DL(p);
	
	//ʹͷָ��Lָ��ͷ��� 
	L = p;
	
	//�յ�˫��ѭ������ͷ������һ��ǰ��ָ���һ�����ָ�룬�Ҿ�ָ��ͷ��������� 
    L->prior = L->next = L;
    
    //�Ӽ��̽������ݣ����δ���ÿһ�����ݽڵ� 
	printf("����������ÿ��Ԫ�أ��м��ÿո����:\n");
	for(int i = 0; i < n; i++){
		
		//�Ӽ��̽���Ԫ�ص�ֵ 
		scanf("%f", &e);
		
		//����һ���µ����ݽڵ㲢����������pָ��Ľ��ĺ��� 
		MallocList_DL(p->next);
		
		//����pָ����ĺ�̽���ǰ��ָ��ָ�����ϵ 
		p->next->prior = p;
		
		//pָ������ƶ� 
		p = p->next;
		
		//���µĽ��������Ӽ��̽��յ�Ԫ��ֵ 
		p->data = e;
	}//for
	
	//ʹ���һ�����ĺ��ָ���򱣴�ͷ���ĵ�ַ 
	p->next = L;
	
	//ʹͷ����ǰ��ָ���򱣴�˫��ѭ������βԪ���ĵ�ַ 
	L->prior = p;
	
	//�����ɹ� 
	return OK;  
}//InitList_DL

/*
	������ListIsEmpty_DL
	������DuLinkList L ˫��ѭ������ͷ����ָ��
	����ֵ����˫��ѭ������Ϊ�գ�����1�����򷵻�0
	���ã��ж�˫��ѭ������L�Ƿ�Ϊ�� 
*/ 
int ListIsEmpty_DL(DuLinkList L) {

	//��ͷ����ǰ��ָ����ͺ��ָ����ָ��ͷ�������˵��˫��ѭ�������ǿձ� 
	return L->prior == L->next;  
}//ListIsEmpty_DL

/*
	������ListLength
	������DuLinkList L ˫��ѭ������ͷ����ָ��
	����ֵ��˫��ѭ������L�ı� 
	���ã���ñ� 
*/ 
int ListLength(DuLinkList L) {
	
	//i�Ǽ����� 
	int i = 0;
	
	//����ָ��pָ����Ԫ��� 
	DuLinkList p = L->next;
	
	//pû�е�ͷָ��˵����û�б��������ű� 
	while(p != L) {
		i++;
		p = p->next;
	}//while
	
	//���ر� 
	return i;
}//ListLength

/*
	������GetElemP_DL
	������DuLinkList &L ˫��ѭ������ͷ����ָ��
	����ֵ�����ҵ���i����㣬�򷵻�һ��ָ��ָ��ýڵ㣬���򷵻�NULL 
	        iΪ0����ͷ���ĵ�ַ 
	���ã���˫��ѭ�������в��ҵ�i����� 
*/ 
DuLinkList GetElemP_DL(DuLinkList L, int i) { 
	
	//�ڿձ��в���Ԫ��û�����壬����Ҫ���ж�˫��ѭ�������Ƿ�Ϊ�� 
	if(ListIsEmpty_DL(L)) {
		printf("˫��ѭ��������û��Ԫ�أ�\n");
	}//if 
	
	//����һ������ָ��p��ָ��ͷ��� 
	DuLinkList p = L;
	
	//������i�Ƿ�Ϸ�����i�Ƿ�Խ��
	if(i < 0 || i > ListLength(L) + 1) {
		return NULL; 
	}//if
	
	//�ҵ���i����� 
	for(int j = 1; j <= i; j++) {
		p = p->next;
	}//for
	
	//����ָ���i������ָ�� 
	return p; 
}//GetElem_DL

/*
	������ListInsert_DL
	������DuLinkList &L ˫��ѭ������ͷ����ָ��
	      int i ����λ��i��i�ĺϷ�ֵΪ1 <= i <= �� + 1 
		  ElemType e  
	����ֵ��˫��ѭ������L�ı� 
	���ã��ڴ�ͷ����˫��ѭ�����Ա�L�е�i��λ��֮ǰ����Ԫ��e
*/ 
Status ListInsert_DL(DuLinkList &L, int i, ElemType e){ 
	
	//���i��ֵ�Ƿ�Ϸ���i�Ƿ�Խ�� 
	if(i < 0){ 
	    printf("�������λ��i���Ϸ�������\n");
	    return ERROR;
    }//if
    
    //p�ǹ���ָ�룬sָ�򱻲�����½�� 
	DuLinkList p, s;
	
	//�ҵ���i��Ԫ�ص�λ��
	//p = NULL��ʾû���ҵ���i����㣬������λ�ò��Ϸ�
	//if(!(p = GetElemP_DL(L, i)))  �൱���������д��룺
	//p = GetElemP_DL(L, i);
	//if(!p)  <=>  if(p == NULL) 
	if(!(p = GetElemP_DL(L, i))) { 
	     return ERROR; 
	}//if
	
	//����һ���µĽ����Ϊ�������㣬��ʹsָ���� 
	MallocList_DL(s);
	
	//��e��ֵ���뵽�½����������� 
	s->data = e;
	
	//����s��p��ǰ�����Ĺ�ϵ 
	s->prior = p->prior;
	
	//����p��ǰ������s�Ĺ�ϵ 
	p->prior->next = s;
	
	//����p��s�Ĺ�ϵ 
	s->next = p;
	
	//����s��p�Ĺ�ϵ 
	p->prior = s;
	
	//�����ɹ�   
	return OK;
	
}//ListInsert_DL

/*
	������ListDelete_DL
	������DuLinkList &L ˫��ѭ������ͷ����ָ��
	      int i ����λ��i��i�ĺϷ�ֵΪi�ĺϷ�ֵΪi <= i <= ��
		  ElemType e  
	����ֵ��˫��ѭ������L�ı� 
	���ã�ɾ����ͷ����˫��ѭ������L�ĵ�i��Ԫ�أ�����e���ر�ɾ������ֵ 
*/  
Status ListDelete_DL(DuLinkList &L, int i, ElemType &e){ 
    
    //�Կձ���ɾ������û�����壬ɾ������֮ǰ��Ҫ�ж������Ƿ�Ϊ�� 
    if(ListIsEmpty_DL(L)) { 
	    printf("˫��ѭ��������û��Ԫ�أ�\n");
	}//if
	
	//p�ǹ���ָ�룬ָ��ɾ����� 
	DuLinkList p;
	
	//���������ҳ���i����㣬����ʹpָ���������Ҳ�����p��ֵΪNULL
	//if(!(p = GetElemP_DL(L, i))) �൱�������������
	//p = GetElemP_DL(L, i)
	//if(!p)  <=>   if(p = NULL)
	if(!(p = GetElemP_DL(L, i))) { 
	   return ERROR;
	}//if
	
	//���汻ɾ������ֵ��e 
	e = p->data;
	
	//��p��ǰ������p�ĺ�̽��������������pָ��Ľ��������и������ 
	p->prior->next = p->next;
	p->next->prior = p->prior;
	
	//�ͷ�pָ������ڴ�ռ� 
	free(p);
	
	//�����ɹ� 
	return OK; 
}//ListDelete_DL

/*
	������Print
	������ElemType e �����ʵ�Ԫ�� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã�����Ԫ��e�ĺ�����ͨ���޸ĸú��������޸�Ԫ�ط��ʷ�ʽ��
	      �ú���ʹ��ʱ��Ҫ��ϱ�������һ��ʹ�á� 
*/  
Status Print(ElemType e){  //Ԫ�ط��ʺ���visit() 
	printf("%6.2f    ",e);
	return OK;
}//Print

/*
	������ListTraverse_DL
	������LinkList L ������L��ͷָ�� 
	      Status(* visit)(ElemType) ����ָ�룬ָ��Ԫ�ط��ʺ����� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã����ζ�˫��ѭ�������ÿ��Ԫ�ص��ú���visit ()��һ��visit ()ʧ�ܣ������ʧ�ܡ�
*/
Status ListTraverse_DL(DuLinkList L, Status (* visit)(ElemType)) {

	//�Կձ�ı���û������ 
	if(ListIsEmpty_DL(L)) { 
	    printf("˫��ѭ��������û��Ԫ�أ�\n");
	}//if
	
	//����һ������ָ�벢��ʹָ֮����Ԫ���
	DuLinkList p = L->next;
	
	//��������˫��ѭ������ 
	while(p != L){
		
		//һ��visit ()ʧ�ܣ������ʧ�ܡ�
		//if(!visit(p->data)) <=>  if(visit(p->data) == ERROR)
		if(!visit(p->data)) {
			printf("�����������\n");
		}//if 
		
		//p����
		p = p->next;   
	}//while
	
	//�������ʹ����̨������� 
	printf("\n");
	
	//�����ɹ� 
	return OK; 
}//ListTraverse_DL

/*
	������DestoryList_DL
	������LinkList L ������L��ͷָ�� 
	      Status(* visit)(ElemType) ����ָ�룬ָ��Ԫ�ط��ʺ����� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã����ζ�˫��ѭ�������ÿ��Ԫ�ص��ú���visit ()��һ��visit ()ʧ�ܣ������ʧ�ܡ�
*/
Status DestoryList_DL(DuLinkList &L){
	
	//����ָ��q
	DuLinkList q;
	
	//�������������ͷ�ȫ�������ڴ�ռ� 
	while(q != L){
		//����ͷŽ����ڴ�ռ�ֱ������ͷ��� 
		q = L->next;
		free(L);
		L = q;
	}//while
	 
	printf("���Ե������ڴ��ͷųɹ���\n");
	
	//�����ɹ� 
	return OK; 
} //DestoryList_DL 

int main(int argc,char *argv[]){
	
	//˫������ͷ���ָ��L	
    DuLinkList L;
    
	//��ʱ���������մӼ��̽��յ�Ԫ�ص�ֵ 
	ElemType e;
	
	//n��˫��ѭ������Ԫ�صĸ���
	//i����ʱ���������ڽ��ղ����ɾ���ı��� 
    int n = 0, i;
    
    printf("\n--------------------------------˫��ѭ���������ð�------------------------------\n");
	
	printf("->��ʼ��˫��ѭ������L\n");
	printf("�����˫��ѭ������L���ö��ٸ�Ԫ�أ�");         
	scanf("%d", &n);	 
	InitList_DL(L, n);
    printf("->���˫��ѭ������L\n");      
	ListTraverse_DL(L, Print);                       
	
	printf("->������˫��ѭ������L���ĸ�λ��֮ǰ����ֵ��\n");
	scanf("%d", &i);
	printf("->������˫��ѭ������L�ĸ�λ��֮ǰ�����ֵΪ���٣�\n");
	scanf("%f", &e);
	ListInsert_DL(L,i,e);
	printf("->ִ�в��������˫��ѭ������L������Ԫ��Ϊ��\n");      
	ListTraverse_DL(L,Print);                    
	
	printf("->������˫��ѭ������L���ĸ�λ��֮ǰɾ��ֵ��\n");
	scanf("%d",&i);
	ListDelete_DL(L,i,e);
	printf("->��ɾ����Ԫ��Ϊ%6.2f\n",e);
	printf("->ִ��ɾ��������˫��ѭ������L������Ԫ��Ϊ��\n");       
	ListTraverse_DL(L,Print);
    
	printf("->����˫��ѭ������L��");
	DestoryList_DL(L);  
	
	return 0;	
}
/*  -----------------------------------���н��-------------------------------------- 


	--------------------------------˫��ѭ���������ð�------------------------------

	->��ʼ��˫��ѭ������L
	�����˫��ѭ������L���ö��ٸ�Ԫ�أ�10
	����������ÿ��Ԫ�أ��м��ÿո����:
	1 45 56 78 54 23 56 89 158 56
	->���˫��ѭ������L
	  1.00     45.00     56.00     78.00     54.00     23.00     56.00     89.00
	158.00     56.00
	->������˫��ѭ������L���ĸ�λ��֮ǰ����ֵ��
	11
	->������˫��ѭ������L�ĸ�λ��֮ǰ�����ֵΪ���٣�
	23
	->ִ�в��������˫��ѭ������L������Ԫ��Ϊ��
	  1.00     45.00     56.00     78.00     54.00     23.00     56.00     89.00
	158.00     23.00     56.00
	->������˫��ѭ������L���ĸ�λ��֮ǰɾ��ֵ��
	1
	->��ɾ����Ԫ��Ϊ  1.00
	->ִ��ɾ��������˫��ѭ������L������Ԫ��Ϊ��
	 45.00     56.00     78.00     54.00     23.00     56.00     89.00    158.00
	 23.00     56.00
	->����˫��ѭ������L�����Ե������ڴ��ͷųɹ���
	
	--------------------------------
	Process exited with return value 0
	Press any key to continue . . .
*/ 
