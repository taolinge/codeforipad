
//------------------------------------�����ͷ�ļ�-------------------------------------- 
#include <stdio.h>          //ʹ���˱�׼�⺯�� printf(),scanf()
#include <stdlib.h>         //ʹ���˶�̬�ڴ���亯�� malloc(),free()

//------------------------------------�Զ�����ų���------------------------------------ 
#define OVERFLOW -2         //�ڴ����������
#define OK 1                //��ʾ������ȷ�ĳ��� 
#define ERROR 0             //��ʾ��������ĳ���
#define TRUE 1                 
#define FALSE 0             

//-----------------------------------�Զ�����������------------------------------------- 
typedef int Status;         //��typedef��int���������Ҳ���ڳ����ά�� 
typedef float ElemType;     //��typedef��float���������Ҳ���ڳ����ά��

//һԪ����ʽ��C���Ա�ʾ
typedef struct{   //��ı�ʾ������ʽ������ΪLinkList������Ԫ�� 
	float coef;   //ϵ�� 
	int   expn;   //ָ�� 
}PElemType;       //����������PElemType

typedef struct LNode{
	PElemType data;       //���汻typedef����Ľṹ��������ΪһԪ����ʽ��Ԫ������ 
	struct LNode *next;   //�������ָ���� 
}* Link,* Position; 

typedef struct{  //�������� 
	Link head,tail;  //ͷָ��head��βָ��tail�ֱ�ָ�����������е�ͷ����β��� 
	int len;   //ָʾ��������������Ԫ�صĸ��� 
}LinkList;
 
typedef LinkList Polynomial;  //�ô���ͷ�������������ʾһԪ����ʽ 

//******************************** һԪ����ʽ�Ļ������� ************************************ 

//------------------------------ 1.���Ա�Ļ����㷨 ---------------------------------------- 
Status MakeNode(Link &p, PElemType e){  //���ɽ�� 
	//������pָ��ֵΪe�Ľ��
	if(!(p = (Link)malloc(sizeof(LNode)))){
		printf("�ڴ����ʧ�ܣ�\n");
		exit(OVERFLOW);
	}//if
	p->data = e;
	return TRUE; 
}//MakeNode

void FreeNode(Link &p){  //�ͷŽ�� 
	//�ͷ�p��ָ��Ľ��
	free(p);
	p = NULL; 
}//FreeNode

void InitList(LinkList &L){   //��ʼ���� 
	//����һ���յ���������L
	Link p = NULL;
	if(!(p = (Link)malloc(sizeof(LNode)))){
		printf("�ڴ����ʧ�ܣ�\n");
		exit(OVERFLOW);
	}//if
	else{
		p->next = NULL;
		L.head = L.tail = p;
		L.len = 0;
	}//if     
}//InitList

void ClearList(LinkList &L){  //������� 
	//����������L�óɿձ����ͷ�ԭ����Ľ��ռ�
	Link p = NULL,q = NULL;
	if(L.head != L.tail){  //���ǿձ� 
		p = q = L.head->next;
		L.head->next = NULL;
		while(p != L.tail){
			p = q->next;
			free(q);
			q = p;
		}//while
		free(q);
		L.tail = L.head;
		L.len = 0;
	}//if
}//ClearList

void DestoryList(LinkList &L){  //�������� 
	//������������L��L���ٴ���
	ClearList(L);  //�������
	FreeNode(L.head);
	L.tail = NULL;
	L.len = 0; 
}//DestoryList

void InsFirst(LinkList &L, Link h, Link s){  //������ (�β�����L����Ϊ��Ҫ�޸�L)
    //��֪hΪ���Ա��ͷ��㣬��s��ָ�����ڵ�һ�����֮ǰ 
	s->next = h->next;
	h->next = s;
	if(h == L.tail) { //hָ��β���
	   L.tail = h->next;  //�޸�βָ�� 
	}//if
	L.len++; 
}//InsFirst

Status DelFirst(LinkList &L, Link h, Link &q){ //ɾ����� (�β�����L����Ϊ��Ҫ�޸�L)
	//hָ��L��һ����㣬��h����ͷ��㣬ɾ�������е�һ����㲢��q����
	//������Ϊ��(hָ��β���),q=NULL,����FALSE
	q = h->next;
	if(q){  //����ǿ� 
		h->next = q->next;
		if(!h->next) { //ɾ��β���
		   L.tail = h; //�޸�βָ��
		}//if
		L.len--;
		return OK;    
	}//if 
	else {
		return ERROR;
	}//else 
}//DelFirst 

void Append(LinkList &L, Link s){  //׷�� 
	//��ָ��s(s->dataΪ��һ������Ԫ��)��ָ(�˴���ָ����������NULL��β)��
	//һ�������������������L�����һ�����֮�󣬲��ı�����L��βָ��ָ���µ�β���
	int i = 1;
	L.tail->next = s;
	while(s->next){
		s = s->next;
		i++;
	}//while
	L.tail = s;
	L.len += i;
}//Append 

Position PriorPos(LinkList L, Link p){  //��ȡǰ��λ�� 
	//��֪pָ�����������е�һ����㣬����p��ָ����ֱ��ǰ��λ�ã�����ֱ��ǰ�����򷵻�NULL
	Link q = NULL;
	q = L.head->next;
	if(q == p) {  //��ǰ��
	    return NULL;
	}//if
	else{
		while(q->next != p) {  //q����p��ֱ��ǰ�� 
		    q = q->next;
		}//while
		return q;
	}//else 
}//PriorPos 

void SetCurElem(Link p,PElemType e){   //���ã����£�Ԫ�ص�ֵ 
	//��֪pָ�����������е�һ����㣬��e����p��ָ����е�����Ԫ�ص�ֵ
	p->data=e; 
}//SetCurElem

PElemType GetCurElem(Link p){   //��ȡԪ�ص�ֵ 
	//��֪pָ�����������е�һ����㣬����p��ָ�������Ԫ�ص�ֵ
	return p->data;
}//GetCurElem

Position GetHead(LinkList L){  //���ͷ���λ�� 
	//������������L��ͷ����λ��
	return L.head; 
}//GetHead

Position NextPos(Link p){  //��ú��λ�� 
	//��֪pָ�����������е�һ����㣬����p��ָ���ֱ�Ӻ�̵�λ��
	return p->next; 
}//NextPos

Status ListEmpty(LinkList L){  //�п� 
	//����������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE
	if(L.len) {
	   return FALSE;
	}//if
	else {
	   return TRUE;
	}//else
}//ListEmpty

//--------------------------------2.һԪ����ʽ���㷨------------------------------------------
 
//-----------------------------����ȽϺ���------------------------------
 
int compare(PElemType a, PElemType b){  //�Ƚ�a,bָ��ֵ��С 

	//��a��ָ��ֵ<(��=)(��>) b��ָ��ֵ���ֱ𷵻�-1,0��+1
	if(a.expn < b.expn) {
		return -1;
	}//if  
	else if(a.expn == b.expn) {
		return 0;
	}//else if
	else{
		return 1; 
	}//else       
}//compare
 
//-------------------------------��λ����-------------------------------- 

Status LocateElem(Polynomial P, PElemType e, Position &q, 
              int (*compare)(PElemType ,PElemType)){  //��λ���� 
     /*����������L�д�����e�����ж�����compare()ȡֵΪ0��Ԫ�أ�
	    ��qָʾL�е�һ��ֵΪe�Ľ���λ�ã�������TRUE��
	   ����qָʾ��һ����e�����ж�����compare()ȡֵ>0��Ԫ�ص�ǰ����λ�ã�������FALSE                           */
	Link p = P.head, p1 = NULL;
	do{
		p1 = p;
		p = p->next;
	}while(p && (compare(p->data, e) < 0));  //û����β��p->data.expn < e.expn
	 
	if(!p || compare(p->data, e) > 0){  //����β��compare(p->data,e)>0 
		q = p1;
		return FALSE;
	}//if
	else{  //�ҵ� 
		q = p;
		return TRUE;
	}//else
}//LocateElem

//----------------------------------------�������-------------------------------------- 

void OrderInsertMerge(Polynomial &P, PElemType e,
          int (*compare)(PElemType ,PElemType)){  //������� 
    
	//�������ж�����compare()��Լ������ֵΪe�Ľ������ϲ�����������L���ʵ�λ��
	Position q = NULL, s = NULL;
	if(LocateElem(P, e, q, compare)){  //L�д��ڸ�ָ���� 
		q->data.coef += e.coef;  //�ı䵱ǰ���ϵ����ֵ 
		if(!q->data.coef){  //ϵ��Ϊ0 
			//ɾ������ʽL�еĵ�ǰ���
			if(!(s = PriorPos(P, q))){  //sΪ��ǰ����ǰ����q��ǰ�� 
				s = P.head; 
			}//if
			DelFirst(P, s, q);
			FreeNode(q);
		}//if 
	}//if 
	else{ //����ָ����������� 
		MakeNode(s, e);   //���ɽ�� 
		InsFirst(P, q, s); 
	}//else
}//OrderInsertMerge

//-----------------------------һԪ����ʽ�Ĵ���������---------------------------------------
 
void createPolyn(Polynomial &P, int m){    //һԪ����ʽ�Ĵ��� 
    //����m���ϵ����ָ����������ʾһԪ����ʽ����������P
    PElemType e;
    Position h = NULL, q = NULL, s = NULL;
	InitList(P);
	h = GetHead(P); //�õ�ͷ����λ�ã�ͷ����λ��Ϊ�����ķ���ֵ 
	e.coef = 0.0;
	e.expn = -1;
	SetCurElem(h, e);  //����ͷ��������Ԫ��
	for(int i = 1; i <= m; ++i){  //��������m��������
	    printf("���������ʽ%d��ϵ����",i); 
		scanf("%f", &e.coef);
		printf("���������ʽ%d��ָ����",i);
		scanf("%d", &e.expn);
		if(!LocateElem(P, e, q, compare)){  //��ǰ�����в����ڸ�ָ���� 
			if(MakeNode(s, e))     //���ɽ�㲢�������� 
			    InsFirst(P, q, s);
		}//if
	}//for 	  
}//createPolyn 

void DestoryPolyn(Polynomial &P){   //һԪ����ʽ������ 
	//����һԪ����ʽP 
	DestoryList(P);
} //AddPolyn

//-------------------------------����һԪ����ʽ����--------------------------------- 

int PolynLength(Polynomial P){
	//����һԪ����ʽ������ 
	return P.len;
}//AddPolyn

//--------------------------------��ӡһԪ����ʽ----------------------------------- 
void Print(PElemType e){
	printf("%.2fx^%d", e.coef, e.expn);
}//Print

void PrintPolyn(Polynomial P, void (*Print)(PElemType)){
	//��ӡ���һԪ����ʽP
	Link q = NULL;
	q = P.head->next;  //qָ���һ�����
	printf("  f(x)=");
	while(q){
		Print(q->data);
		if(q->next && q->next->data.coef > 0){
			printf("+");
		}//if
		q = q->next;
	}//while 
	printf("\n");
}//PrintPolyn

//-----------------------------һԪ����ʽ�����㣨+ - *��-------------------------------- 

void AddPolyn(Polynomial &Pa, Polynomial &Pb){
	//����ʽ�ӷ���Pa=Pa+Pb ,������������ʽ�Ľ�㹹�ɡ��Ͷ���ʽ��
	Position ha = NULL, hb = NULL, qa = NULL, qb = NULL;
	float sum = 0;
	PElemType a, b;
	ha = GetHead(Pa);
	hb = GetHead(Pb);
	qa = NextPos(ha);
	qb = NextPos(hb); 
	while(qa && qb){
		a = GetCurElem(qa);
		b = GetCurElem(qb);
		switch(compare(a, b)){
			case -1: { //����ʽPA�е�ǰ���ָ��ֵ��С 
				ha = qa;  
				qa = NextPos(ha); 
				break;
			}//case 
			case 0:  { //����ָ��ֵ��� 
				sum = a.coef + b.coef;
				if(sum != 0.0){  //�޸Ķ���ʽPA��ǰ��ϵ��ֵ
				    PElemType e;
					e.coef = sum;
					e.expn = a.expn; 
					SetCurElem(qa, e);
					ha=qa;
				}//if 
				else{     //ɾ������ʽPA�ĵ�ǰ��� 
					DelFirst(Pa, ha, qa);
					FreeNode(qa); 
				}//else
				DelFirst(Pb, hb, qb);
				FreeNode(qb);
				qb = NextPos(hb); 
				qa = NextPos(ha);
				break;
			}//case
			case 1:{   //����ʽPB�е�ǰ����ָ��ֵС 
				DelFirst(Pb, hb, qb);
				InsFirst(Pa, ha, qb);
				qb = NextPos(hb);
				ha = NextPos(ha); 
				break;
			}//case     
		}//switch 
	}//while
	if(!ListEmpty(Pb)){
		Pb.tail = hb;
		Append(Pa, qb);  //����Pb��ʣ���� 
	}//if 
	DestoryPolyn(Pb);  //����Pb 
} //AddPolyn

void Opposite(Polynomial &Pa){  //ϵ��ȡ�� 
	//����ʽPaϵ��ȡ��
	Position p;
	p = Pa.head;
	while(p->next){
		p = p->next;
		p->data.coef *= -1;
	}//while 
}//Opposite

void SubtractPolyn(Polynomial &Pa, Polynomial &Pb){
	//����ʽ������Pa=Pa-Pb��������һԪ����ʽPb 
	Opposite(Pb);      //����ʽPbϵ��ȡ�� 
	AddPolyn(Pa, Pb);   //������ʽ���,������֮������Pb 
} //SubtractPolyn

void MultiplePolyn(Polynomial &Pa, Polynomial &Pb){
	//����ʽ�˷���Pa=Pa*Pb��������һԪ����ʽPb 
	Polynomial Pc;
	Position qa = NULL, qb = NULL;
	PElemType a, b, c;
	InitList(Pc);
	qa = GetHead(Pa);
	qa = qa->next;
	while(qa){
		a = GetCurElem(qa);
		qb = GetHead(Pb);
		qb = qb->next;
		while(qb){
			b = GetCurElem(qb);
			c.coef = a.coef * b.coef;
			c.expn = a.expn + b.expn;
			OrderInsertMerge(Pc, c, compare);
			qb = qb->next;
		}//while
		qa = qa->next;
	}//while
	DestoryPolyn(Pb);  //����Pb
	ClearList(Pa);     //��Pa����Ϊ�ձ�
	Pa.head = Pc.head; 
	Pa.tail = Pc.tail;
	Pa.len = Pc.len;
} //MultiplePolyn

//-------------------------------------------������--------------------------------------------------- 
int main(int argc,char *argv[]){
    Polynomial P, Q;  //��������ʽ
	int m = 0; 
	printf("\n------------------------------- һԪ����ʽ -------------------------------------\n"); 
    printf("->������һԪ����ʽ1�ķ����������");   scanf("%d", &m);
	createPolyn(P, m); 
	printf("->������һԪ����ʽ2�ķ����������");   scanf("%d", &m);
	createPolyn(Q, m);
	printf("\n->ִ�в���ǰ��P��Q ������ʽ��\n");
	printf("P : "); PrintPolyn(P, Print);
	printf("Q : "); PrintPolyn(Q, Print);
	AddPolyn(P,Q);       //����ʽ�ӷ���P+Q 
	printf("\n->��������ʽ��ӽ��P+Q:");     PrintPolyn(P, Print);
	printf("\n->������һԪ����ʽ3�ķ����������");  scanf("%d", &m);
	createPolyn(Q, m);
	printf("\n->ִ�в���ǰ��P��Q ������ʽ��\n");
	printf("P : "); PrintPolyn(P, Print);
	printf("Q : "); PrintPolyn(Q, Print);
	SubtractPolyn(P,Q);  //����ʽ������P-Q
	printf("\n->��������ʽ������P-Q:");     PrintPolyn(P, Print);
	printf("\n->������һԪ����ʽ4�ķ����������");  scanf("%d", &m);
	createPolyn(Q, m);
	printf("\n->ִ�в���ǰ��P��Q ������ʽ��\n");
	printf("P : "); PrintPolyn(P, Print);
	printf("Q : "); PrintPolyn(Q, Print);
	MultiplePolyn(P,Q);  //����ʽ�˷���P*Q
	printf("\n->��������ʽ��˽��P*Q:\n");   PrintPolyn(P, Print);
	DestoryPolyn(P);   //���в�����ɶ�������Q����ʱֻʣ��Pû������ 		
	return 0;
}

/* ---------------------------------  ���н�� ------------------------------------- 

	------------------------------- һԪ����ʽ -------------------------------------
	
	->������һԪ����ʽ1�ķ����������3
	���������ʽ1��ϵ����1
	���������ʽ1��ָ����2
	���������ʽ2��ϵ����5
	���������ʽ2��ָ����4
	���������ʽ3��ϵ����3
	���������ʽ3��ָ����3
	->������һԪ����ʽ2�ķ����������3
	���������ʽ1��ϵ����-3
	���������ʽ1��ָ����3
	���������ʽ2��ϵ����4
	���������ʽ2��ָ����2
	���������ʽ3��ϵ����7
	���������ʽ3��ָ����1
	
	->ִ�в���ǰ��P��Q ������ʽ��
	P :   f(x)=1.00x^2+3.00x^3+5.00x^4
	Q :   f(x)=7.00x^1+4.00x^2-3.00x^3
	
	->��������ʽ��ӽ��P+Q:  f(x)=7.00x^1+5.00x^2+5.00x^4
	
	->������һԪ����ʽ3�ķ����������3
	���������ʽ1��ϵ����4
	���������ʽ1��ָ����1
	���������ʽ2��ϵ����2
	���������ʽ2��ָ����3
	���������ʽ3��ϵ����6
	���������ʽ3��ָ����6
	
	->ִ�в���ǰ��P��Q ������ʽ��
	P :   f(x)=7.00x^1+5.00x^2+5.00x^4
	Q :   f(x)=4.00x^1+2.00x^3+6.00x^6
	
	->��������ʽ������P-Q:  f(x)=3.00x^1+5.00x^2-2.00x^3+5.00x^4-6.00x^6
	
	->������һԪ����ʽ4�ķ����������2
	���������ʽ1��ϵ����1
	���������ʽ1��ָ����1
	���������ʽ2��ϵ����2
	���������ʽ2��ָ����2
	
	->ִ�в���ǰ��P��Q ������ʽ��
	P :   f(x)=3.00x^1+5.00x^2-2.00x^3+5.00x^4-6.00x^6
	Q :   f(x)=1.00x^1+2.00x^2
	
	->��������ʽ��˽��P*Q:
	  f(x)=3.00x^2+11.00x^3+8.00x^4+1.00x^5+10.00x^6-6.00x^7-12.00x^8
	
	--------------------------------
	Process exited with return value 0
	Press any key to continue . . .
*/
