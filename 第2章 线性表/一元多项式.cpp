
//------------------------------------引入的头文件-------------------------------------- 
#include <stdio.h>          //使用了标准库函数 printf(),scanf()
#include <stdlib.h>         //使用了动态内存分配函数 malloc(),free()

//------------------------------------自定义符号常量------------------------------------ 
#define OVERFLOW -2         //内存溢出错误常量
#define OK 1                //表示操作正确的常量 
#define ERROR 0             //表示操作错误的常量
#define TRUE 1                 
#define FALSE 0             

//-----------------------------------自定义数据类型------------------------------------- 
typedef int Status;         //用typedef给int起个别名，也便于程序的维护 
typedef float ElemType;     //用typedef给float起个别名，也便于程序的维护

//一元多项式的C语言表示
typedef struct{   //项的表示，多项式的项作为LinkList的数据元素 
	float coef;   //系数 
	int   expn;   //指数 
}PElemType;       //数据类型名PElemType

typedef struct LNode{
	PElemType data;       //上面被typedef定义的结构体类型作为一元多项式的元素类型 
	struct LNode *next;   //单链表的指针域 
}* Link,* Position; 

typedef struct{  //链表类型 
	Link head,tail;  //头指针head和尾指针tail分别指向线性链表中的头结点和尾结点 
	int len;   //指示线性链表中数据元素的个数 
}LinkList;
 
typedef LinkList Polynomial;  //用带表头结点的有序链表表示一元多项式 

//******************************** 一元多项式的基本操作 ************************************ 

//------------------------------ 1.线性表的基本算法 ---------------------------------------- 
Status MakeNode(Link &p, PElemType e){  //生成结点 
	//分配由p指向值为e的结点
	if(!(p = (Link)malloc(sizeof(LNode)))){
		printf("内存分配失败！\n");
		exit(OVERFLOW);
	}//if
	p->data = e;
	return TRUE; 
}//MakeNode

void FreeNode(Link &p){  //释放结点 
	//释放p所指向的结点
	free(p);
	p = NULL; 
}//FreeNode

void InitList(LinkList &L){   //初始化表 
	//构造一个空的线性链表L
	Link p = NULL;
	if(!(p = (Link)malloc(sizeof(LNode)))){
		printf("内存分配失败！\n");
		exit(OVERFLOW);
	}//if
	else{
		p->next = NULL;
		L.head = L.tail = p;
		L.len = 0;
	}//if     
}//InitList

void ClearList(LinkList &L){  //清空链表 
	//将线性链表L置成空表，并释放原链表的结点空间
	Link p = NULL,q = NULL;
	if(L.head != L.tail){  //不是空表 
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

void DestoryList(LinkList &L){  //销毁链表 
	//销毁线性链表L，L不再存在
	ClearList(L);  //清空链表
	FreeNode(L.head);
	L.tail = NULL;
	L.len = 0; 
}//DestoryList

void InsFirst(LinkList &L, Link h, Link s){  //插入结点 (形参增加L，因为需要修改L)
    //已知h为线性表的头结点，将s所指结点插在第一个结点之前 
	s->next = h->next;
	h->next = s;
	if(h == L.tail) { //h指向尾结点
	   L.tail = h->next;  //修改尾指针 
	}//if
	L.len++; 
}//InsFirst

Status DelFirst(LinkList &L, Link h, Link &q){ //删除结点 (形参增加L，因为需要修改L)
	//h指向L的一个结点，把h当做头结点，删除链表中第一个结点并以q返回
	//若链表为空(h指向尾结点),q=NULL,返回FALSE
	q = h->next;
	if(q){  //链表非空 
		h->next = q->next;
		if(!h->next) { //删除尾结点
		   L.tail = h; //修改尾指针
		}//if
		L.len--;
		return OK;    
	}//if 
	else {
		return ERROR;
	}//else 
}//DelFirst 

void Append(LinkList &L, Link s){  //追加 
	//将指针s(s->data为第一个数据元素)所指(彼此以指针相链，以NULL结尾)的
	//一串结点链接在线性链表L的最后一个结点之后，并改变链表L的尾指针指向新的尾结点
	int i = 1;
	L.tail->next = s;
	while(s->next){
		s = s->next;
		i++;
	}//while
	L.tail = s;
	L.len += i;
}//Append 

Position PriorPos(LinkList L, Link p){  //获取前驱位置 
	//已知p指向线性链表中的一个结点，返回p所指结点的直接前驱位置，若无直接前驱，则返回NULL
	Link q = NULL;
	q = L.head->next;
	if(q == p) {  //无前驱
	    return NULL;
	}//if
	else{
		while(q->next != p) {  //q不是p的直接前驱 
		    q = q->next;
		}//while
		return q;
	}//else 
}//PriorPos 

void SetCurElem(Link p,PElemType e){   //设置（更新）元素的值 
	//已知p指向线性链表中的一个结点，用e更新p所指结点中的数据元素的值
	p->data=e; 
}//SetCurElem

PElemType GetCurElem(Link p){   //获取元素的值 
	//已知p指向线性链表中的一个结点，返回p所指结点数据元素的值
	return p->data;
}//GetCurElem

Position GetHead(LinkList L){  //获得头结点位置 
	//返回线性链表L中头结点的位置
	return L.head; 
}//GetHead

Position NextPos(Link p){  //获得后继位置 
	//已知p指向线性链表中的一个结点，返回p所指结点直接后继的位置
	return p->next; 
}//NextPos

Status ListEmpty(LinkList L){  //判空 
	//若线性链表L为空表，则返回TRUE，否则返回FALSE
	if(L.len) {
	   return FALSE;
	}//if
	else {
	   return TRUE;
	}//else
}//ListEmpty

//--------------------------------2.一元多项式的算法------------------------------------------
 
//-----------------------------有序比较函数------------------------------
 
int compare(PElemType a, PElemType b){  //比较a,b指数值大小 

	//依a的指数值<(或=)(或>) b的指数值，分别返回-1,0和+1
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
 
//-------------------------------定位函数-------------------------------- 

Status LocateElem(Polynomial P, PElemType e, Position &q, 
              int (*compare)(PElemType ,PElemType)){  //定位函数 
     /*若有序链表L中存在与e满足判定函数compare()取值为0的元素，
	    则q指示L中第一个值为e的结点的位置，并返回TRUE；
	   否则q指示第一个与e满足判定函数compare()取值>0的元素的前驱的位置，并返回FALSE                           */
	Link p = P.head, p1 = NULL;
	do{
		p1 = p;
		p = p->next;
	}while(p && (compare(p->data, e) < 0));  //没到表尾且p->data.expn < e.expn
	 
	if(!p || compare(p->data, e) > 0){  //到表尾或compare(p->data,e)>0 
		q = p1;
		return FALSE;
	}//if
	else{  //找到 
		q = p;
		return TRUE;
	}//else
}//LocateElem

//----------------------------------------按序插入-------------------------------------- 

void OrderInsertMerge(Polynomial &P, PElemType e,
          int (*compare)(PElemType ,PElemType)){  //按序插入 
    
	//按有序判定函数compare()的约定，将值为e的结点插入或合并到升序链表L的适当位置
	Position q = NULL, s = NULL;
	if(LocateElem(P, e, q, compare)){  //L中存在该指数项 
		q->data.coef += e.coef;  //改变当前结点系数的值 
		if(!q->data.coef){  //系数为0 
			//删除多项式L中的当前结点
			if(!(s = PriorPos(P, q))){  //s为当前结点的前驱且q无前驱 
				s = P.head; 
			}//if
			DelFirst(P, s, q);
			FreeNode(q);
		}//if 
	}//if 
	else{ //生成指数项并链入链表 
		MakeNode(s, e);   //生成结点 
		InsFirst(P, q, s); 
	}//else
}//OrderInsertMerge

//-----------------------------一元多项式的创建与销毁---------------------------------------
 
void createPolyn(Polynomial &P, int m){    //一元多项式的创建 
    //输入m项的系数和指数，建立表示一元多项式的有序链表P
    PElemType e;
    Position h = NULL, q = NULL, s = NULL;
	InitList(P);
	h = GetHead(P); //得到头结点的位置，头结点的位置为函数的返回值 
	e.coef = 0.0;
	e.expn = -1;
	SetCurElem(h, e);  //设置头结点的数据元素
	for(int i = 1; i <= m; ++i){  //依次输入m个非零项
	    printf("请输入多项式%d的系数：",i); 
		scanf("%f", &e.coef);
		printf("请输入多项式%d的指数：",i);
		scanf("%d", &e.expn);
		if(!LocateElem(P, e, q, compare)){  //当前链表中不存在该指数项 
			if(MakeNode(s, e))     //生成结点并插入链表 
			    InsFirst(P, q, s);
		}//if
	}//for 	  
}//createPolyn 

void DestoryPolyn(Polynomial &P){   //一元多项式的销毁 
	//销毁一元多项式P 
	DestoryList(P);
} //AddPolyn

//-------------------------------计算一元多项式项数--------------------------------- 

int PolynLength(Polynomial P){
	//返回一元多项式的项数 
	return P.len;
}//AddPolyn

//--------------------------------打印一元多项式----------------------------------- 
void Print(PElemType e){
	printf("%.2fx^%d", e.coef, e.expn);
}//Print

void PrintPolyn(Polynomial P, void (*Print)(PElemType)){
	//打印输出一元多项式P
	Link q = NULL;
	q = P.head->next;  //q指向第一个结点
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

//-----------------------------一元多项式的运算（+ - *）-------------------------------- 

void AddPolyn(Polynomial &Pa, Polynomial &Pb){
	//多项式加法：Pa=Pa+Pb ,利用两个多项式的结点构成“和多项式”
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
			case -1: { //多项式PA中当前结点指数值最小 
				ha = qa;  
				qa = NextPos(ha); 
				break;
			}//case 
			case 0:  { //两者指数值相等 
				sum = a.coef + b.coef;
				if(sum != 0.0){  //修改多项式PA当前的系数值
				    PElemType e;
					e.coef = sum;
					e.expn = a.expn; 
					SetCurElem(qa, e);
					ha=qa;
				}//if 
				else{     //删除多项式PA的当前结点 
					DelFirst(Pa, ha, qa);
					FreeNode(qa); 
				}//else
				DelFirst(Pb, hb, qb);
				FreeNode(qb);
				qb = NextPos(hb); 
				qa = NextPos(ha);
				break;
			}//case
			case 1:{   //多项式PB中当前结点的指数值小 
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
		Append(Pa, qb);  //链接Pb中剩余结点 
	}//if 
	DestoryPolyn(Pb);  //销毁Pb 
} //AddPolyn

void Opposite(Polynomial &Pa){  //系数取反 
	//多项式Pa系数取反
	Position p;
	p = Pa.head;
	while(p->next){
		p = p->next;
		p->data.coef *= -1;
	}//while 
}//Opposite

void SubtractPolyn(Polynomial &Pa, Polynomial &Pb){
	//多项式减法：Pa=Pa-Pb，并销毁一元多项式Pb 
	Opposite(Pb);      //多项式Pb系数取反 
	AddPolyn(Pa, Pb);   //两多项式相加,操作完之后销毁Pb 
} //SubtractPolyn

void MultiplePolyn(Polynomial &Pa, Polynomial &Pb){
	//多项式乘法：Pa=Pa*Pb，并销毁一元多项式Pb 
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
	DestoryPolyn(Pb);  //销毁Pb
	ClearList(Pa);     //将Pa重置为空表
	Pa.head = Pc.head; 
	Pa.tail = Pc.tail;
	Pa.len = Pc.len;
} //MultiplePolyn

//-------------------------------------------主函数--------------------------------------------------- 
int main(int argc,char *argv[]){
    Polynomial P, Q;  //两个多项式
	int m = 0; 
	printf("\n------------------------------- 一元多项式 -------------------------------------\n"); 
    printf("->请输入一元多项式1的非零项个数：");   scanf("%d", &m);
	createPolyn(P, m); 
	printf("->请输入一元多项式2的非零项个数：");   scanf("%d", &m);
	createPolyn(Q, m);
	printf("\n->执行操作前，P、Q 两多项式：\n");
	printf("P : "); PrintPolyn(P, Print);
	printf("Q : "); PrintPolyn(Q, Print);
	AddPolyn(P,Q);       //多项式加法，P+Q 
	printf("\n->两个多项式相加结果P+Q:");     PrintPolyn(P, Print);
	printf("\n->请输入一元多项式3的非零项个数：");  scanf("%d", &m);
	createPolyn(Q, m);
	printf("\n->执行操作前，P、Q 两多项式：\n");
	printf("P : "); PrintPolyn(P, Print);
	printf("Q : "); PrintPolyn(Q, Print);
	SubtractPolyn(P,Q);  //多项式减法，P-Q
	printf("\n->两个多项式相减结果P-Q:");     PrintPolyn(P, Print);
	printf("\n->请输入一元多项式4的非零项个数：");  scanf("%d", &m);
	createPolyn(Q, m);
	printf("\n->执行操作前，P、Q 两多项式：\n");
	printf("P : "); PrintPolyn(P, Print);
	printf("Q : "); PrintPolyn(Q, Print);
	MultiplePolyn(P,Q);  //多项式乘法，P*Q
	printf("\n->两个多项式相乘结果P*Q:\n");   PrintPolyn(P, Print);
	DestoryPolyn(P);   //所有操作完成都会销毁Q，此时只剩下P没被销毁 		
	return 0;
}

/* ---------------------------------  运行结果 ------------------------------------- 

	------------------------------- 一元多项式 -------------------------------------
	
	->请输入一元多项式1的非零项个数：3
	请输入多项式1的系数：1
	请输入多项式1的指数：2
	请输入多项式2的系数：5
	请输入多项式2的指数：4
	请输入多项式3的系数：3
	请输入多项式3的指数：3
	->请输入一元多项式2的非零项个数：3
	请输入多项式1的系数：-3
	请输入多项式1的指数：3
	请输入多项式2的系数：4
	请输入多项式2的指数：2
	请输入多项式3的系数：7
	请输入多项式3的指数：1
	
	->执行操作前，P、Q 两多项式：
	P :   f(x)=1.00x^2+3.00x^3+5.00x^4
	Q :   f(x)=7.00x^1+4.00x^2-3.00x^3
	
	->两个多项式相加结果P+Q:  f(x)=7.00x^1+5.00x^2+5.00x^4
	
	->请输入一元多项式3的非零项个数：3
	请输入多项式1的系数：4
	请输入多项式1的指数：1
	请输入多项式2的系数：2
	请输入多项式2的指数：3
	请输入多项式3的系数：6
	请输入多项式3的指数：6
	
	->执行操作前，P、Q 两多项式：
	P :   f(x)=7.00x^1+5.00x^2+5.00x^4
	Q :   f(x)=4.00x^1+2.00x^3+6.00x^6
	
	->两个多项式相减结果P-Q:  f(x)=3.00x^1+5.00x^2-2.00x^3+5.00x^4-6.00x^6
	
	->请输入一元多项式4的非零项个数：2
	请输入多项式1的系数：1
	请输入多项式1的指数：1
	请输入多项式2的系数：2
	请输入多项式2的指数：2
	
	->执行操作前，P、Q 两多项式：
	P :   f(x)=3.00x^1+5.00x^2-2.00x^3+5.00x^4-6.00x^6
	Q :   f(x)=1.00x^1+2.00x^2
	
	->两个多项式相乘结果P*Q:
	  f(x)=3.00x^2+11.00x^3+8.00x^4+1.00x^5+10.00x^6-6.00x^7-12.00x^8
	
	--------------------------------
	Process exited with return value 0
	Press any key to continue . . .
*/
