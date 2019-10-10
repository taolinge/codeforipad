
/********************************ѭ�����еĳ�����������ADT����*****************************************
   ADT Queue {
     ���ݶ���D= {ai|ai�� Elemset,(i=1,2,��,n, n��0)}
     ���ݹ�ϵ��R1 = {��ai-1, ai��|ai-1,ai�� D,(i=2,3,��,n)}   Լ��a1Ϊ��ͷ, anΪ��β
	   1. InitQueue(&Q)
	      �������:����һ���յĶ���Q��
	   2. DestroyQueue(&Q)
	      ��ʼ����: ����Q�Ѿ����ڡ�
	      �������: ���ٶ���Q�� 
	   3. ClearQueue (&Q)
	      ��ʼ����: ����Q�Ѿ����ڡ�
	      �������: ������Q��Ϊ�ն��С�
	   4. QueueEmpty(Q)
	      ��ʼ����: ����Q�Ѿ����ڡ�
	      �������:��QΪ�ն��У��򷵻�TURE;���򷵻�FALSE��
	   5. QueueLength(Q)
	      ��ʼ����:����Q�Ѿ����ڡ�
	      �������:����Q�е�����Ԫ�ظ����������г��ȡ�
	   6. GetHead(Q,&e)
	      ��ʼ����:����Q�Ѿ������ҷǿա�
	      �������:��e���ض���Q�еĶ�ͷԪ�ء�
	   7. EnQueue(&Q,e)        // ��Ӳ���
	      ��ʼ����:����Q�Ѿ����ڡ�
	      �������:����Ԫ��eΪ�µĶ�βԪ�ء�
	   8. DeQueue(&Q,&e)      // ���Ӳ���
	      ��ʼ����:����Q�Ѿ������ҷǿա�
	      �������:ɾ��Q�Ķ�ͷԪ�أ�����e������ֵ��
	   9. QueueTraverse(Q,visit())
	      ��ʼ����:����Q�Ѿ������ҷǿա�
	      �������:�Ӷ�ͷ����β���ζ�Q��ÿ��Ԫ�ص��ú���visit ()��һ��visit ()ʧ�ܣ������ʧ�ܡ�
}ADT Queue
    
****************************************************************************************************/

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>����ͷ�ļ�<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <stdio.h>   //ʹ���˱�׼�⺯�� printf(),scanf()
#include <stdlib.h>  //ʹ���˶�̬�ڴ���亯�� malloc(),free()

//>>>>>>>>>>>>>>>>>>>>>>>>>>>�Զ�����ų���<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 
 
#define OVERFLOW -2         //�ڴ����������
#define OK 1                //��ʾ������ȷ�ĳ��� 
#define ERROR 0             //��ʾ��������ĳ���
#define MAXQSIZE 100        //���е���󳤶�
#define TRUE 1              //��ʾ�߼�Ϊ��ĳ��� 
#define FALSE 0             //��ʾ�߼�Ϊ�ٵĳ���

//>>>>>>>>>>>>>>>>>>>>>>>>>>>�Զ�����������<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef int Status;         //��typedef��int���������Ҳ���ڳ����ά�� 
typedef float QElemType;    //��typedef��float���������Ҳ���ڳ����ά��
typedef struct {            //ѭ�����е�C�������� 

	QElemType *base;        //��ʼ����̬����洢�ռ�
	int front;              //ͷָ�룬�����в��գ�ָ���ͷԪ�� 
	int rear; 	            //βָ�룬�����в��գ�ָ���βԪ�ص���һ��λ�� 
}SqQueue; 
 
//------------------------ѭ�����е���Ҫ����--------------------------

//>>>>>>>>>>>>>>>>>>>>>>>>1.��ʼ��ѭ������<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	������InitQueue_Sq
	������SqQueue &Q ѭ���������� 
	����ֵ��״̬�룬�����ɹ�����OK 
	���ã�����һ���ն��� Q
*/
Status InitQueue_Sq(SqQueue &Q) {
   	
   	//�����ڴ�ռ䣬��ʧ������ʾ���˳�����
   	//if(!(Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType))))
   	//�൱���������д��룺
	//Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType))
	//if(!Q.base)  <=>  if(Q.base == NULL)
	if(!(Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType)))){
		printf("�ڴ����ʧ�ܣ����򼴽��˳���\n");
		exit(OVERFLOW);
	}//if
	
	//���ڸ�����Ŀռ�û��Ԫ����ӣ����Զ���Ϊ�� 
	//Q.front == Q.rear�Ƕ���Ϊ�յı�־ 
	Q.front = Q.rear = 0;
	
	//�����ɹ� 
	printf("ѭ�������ѳɹ�������\n");
	return OK;
}//InitQueue_Sq

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>2.����ѭ������<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	������DestoryQueue_Sq
	������SqQueue &Q ѭ���������� 
	����ֵ��״̬�룬�����ɹ�����OK 
	���ã�����ѭ������ Q
*/
Status DestoryQueue_Sq(SqQueue &Q) {
	
	//ѭ�����в��������Ĵ洢�ռ䣬ֱ���ҵ��׵�ַ�ͷſռ伴�� 
	if(Q.base) { 
		free(Q.base);
	}//if
	
	//ָ���ÿգ��ͷŵ�ָ���������ռ�õĿռ� 
	Q.base = NULL;
	
	//��ͷ�Ͷ�βָ����㣬����Ϊ�� 
	Q.front = Q.rear = 0;
	
	//�����ɹ� 
	printf("ѭ�������ѳɹ����٣�\n");
	return OK;
}//DestoryQueue_Sq

//>>>>>>>>>>>>>>>>>>>>>>3.�ж�ѭ�������Ƿ�Ϊ��<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	������QueueEmpty_Sq
	������SqQueue Q ѭ������Q 
	����ֵ��״̬�룬����Ϊ�շ���TRUE�����򷵻�FALSE 
	���ã��ж�ѭ������ Q�Ƿ�Ϊ�� 
*/
Status QueueEmpty_Sq(SqQueue Q) {
	
	//Q.rear == Q.front�Ƕ���Ϊ�յı�־ 
	if(Q.rear == Q.front) { 
		return TRUE; 
	}//if 
	else {
		return FALSE;
	}//else  
}//QueueEmpty_Sq

//>>>>>>>>>>>>>>>>>>>>>>>4.��ȡѭ�����еĳ���<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	������QueueLength_Sq
	������SqQueue Q ѭ������Q 
	����ֵ������Q�е�����Ԫ�ظ����������г���
	���ã���ȡ���г��� 
*/
int QueueLength_Sq(SqQueue Q) {
	
    //ע�⣺������ֱ����(Q.rear - Q.front) % MAXQSIZE��ʾ���г��ȣ�
	//��Ϊ���Q.rear - Q.front���������Ǹ�������С��MAXQSIZE��
	//�����ý���ǲ���ȷ�ġ�����һ��Ҫ�ȼ���һ��MAXQSIZE����ģ���� 
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE; 
}//QueueLength_Sq

//>>>>>>>>>>>>>>>>>5.��ѭ�������в���Ԫ�أ���ӣ�<<<<<<<<<<<<<<<<<<<<<<

/*
	������EnQueue_Sq
	������SqQueue Q ѭ������Q
	      QElemType e ������Ԫ��e 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERROR 
	���ã�����Ԫ��eΪQ���µĶ�βԪ��e  
*/
Status EnQueue_Sq(SqQueue &Q, QElemType e) {
	
    //����ѭ������ʹ��˳��洢�ṹ������ʱ��Ҫ�ж϶����Ƿ���
	//�ж϶������ı�־��(Q.rear + 1) % MAXQSIZE == Q.front
	if((Q.rear + 1) % MAXQSIZE == Q.front) {  //������
	
		//����ʧ�� 
	    return ERROR;
	}//if
	
	//��e���뵽��β 
	Q.base[Q.rear] = e;
	
	//ÿ����һ���¶�βԪ�أ�βָ����һ
	Q.rear = (Q.rear + 1) % MAXQSIZE;
	
	//�����ɹ� 
	return OK; 
}//EnQueue_Sq

//>>>>>>>>>>>>>>>>>>6.��ѭ��������ɾ��Ԫ�أ����ӣ�<<<<<<<<<<<<<<<<<<<

/*
	������DeQueue_Sq
	������SqQueue Q ѭ������Q
	      QElemType &e ���ر�ɾ����Ԫ��e 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERROR 
	���ã����в���,��ɾ��Q�Ķ�ͷԪ��,��e������ֵ
*/
Status DeQueue_Sq(SqQueue &Q, QElemType &e) {
	
	//�ڿն�����ִ�г��Ӳ���û�����壬����Ҫ���ж϶����Ƿ�Ϊ�� 
	//if(QueueEmpty_Sq(Q)) <=> if(QueueEmpty_Sq(Q) == TRUE)
	if(QueueEmpty_Sq(Q)) { //���п� 
	    
	    //����ʧ�� 
		return ERROR;
	}//if
	
	//���汻ɾ��Ԫ�ص�ֵ 
	e = Q.base[Q.front];
	
	//ÿ��ɾ����ͷԪ��ʱ��ͷָ����1 
	Q.front = (Q.front + 1) % MAXQSIZE;
	
	//�����ɹ� 
	return OK; 
}//DeQueue_Sq

//>>>>>>>>>>>>>>>>>>>>>7.�ÿ�ѭ������<<<<<<<<<<<<<<<<<<<<<<<

/*
	������ClearQueue_Sq
	������SqQueue &Q ѭ���������� 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERROR 
	���ã���Q��� 
*/
Status ClearQueue_Sq(SqQueue &Q) {
	
	//��ͷ��βָ������ 
	Q.front = Q.rear = 0;
	
	//�����ɹ�    
    printf("����������գ�����Ϊ��%d\n", QueueLength_Sq(Q));
	return OK; 
}//ClearQueue_Sq

//>>>>>>>>>>>>>>>>>>>>>>>8.��������ѭ������<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	������Print
	������ElemType e �����ʵ�Ԫ�� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã�����Ԫ��e�ĺ�����ͨ���޸ĸú��������޸�Ԫ�ط��ʷ�ʽ��
	      �ú���ʹ��ʱ��Ҫ��ϱ�������һ��ʹ�á� 
*/
Status Print(QElemType e){
	
	//���ÿ���̨����ķ�ʽ����ÿ��Ԫ�� 
	printf("%6.2f    ", e);
	
	//�����ɹ� 
	return OK;
}//Print

/*
	������QueueTraverse_Sq
	������SqQueue Q ѭ��������Q 
	      Status (* visit)(QElemType) ����ָ�룬ָ��Ԫ�ط��ʺ����� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã�����Ԫ�ط��ʺ���������˳�����ѭ�����еı���������δ����ִ�г��Ӳ��� 
*/
Status QueueTraverse_Sq(SqQueue Q, Status (* visit)(QElemType)) {
	
	//���η���ÿ��Ԫ�� 
	for(int i = 0; i < QueueLength_Sq(Q); i++) {
		
		//һ������ʧ�������ʧ��
		//if(visit(Q.base[i]) != NULL)
		if(!visit(Q.base[i])) {
			return ERROR;
		}//if 
	}//for 
	     
	//�����ɹ� 
	return OK; 
}//QueueTraverse_Sq

//>>>>>>>>>>>>>>>>>>>>>9.��ȡ��ͷԪ�ص�ֵ<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
	������GetHead_Sq
	������SqQueue Q ѭ��������Q 
	      QElemType &e ���ض�ͷԪ�ص�ֵ 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã���ȡ��ͷԪ�ص�ֵ����e���ظ�ֵ 
*/
Status GetHead_Sq(SqQueue Q, QElemType &e) {
	
	//�������Ϊ�գ����ȡ������ͷԪ�ص�ֵ������Ҫ���ж϶����Ƿ��
	//if(QueueEmpty_Sq(Q)) <=> if(QueueEmpty_Sq(Q) == TRUE) 
	if(QueueEmpty_Sq(Q)) { //���п�
	
		//�޷���ȡ��ͷԪ�أ�����ʧ�� 
		return ERROR;
	}//if
	
	//��ȡ��ͷԪ�ص�ֵ�����浽e 
    e = Q.base[Q.front];
    
    //�����ɹ� 
	return OK; 
}//GetHead_Sq

//--------------------------������---------------------------------- 
int main(int argc,char *argv[]){
	
	//ѭ������Q 
	SqQueue Q;
	
	//��ʱ����e�����ڱ��������Ԫ�أ���ɾ��Ԫ�غͶ�ͷԪ�� 
	QElemType e;
	
	//n���ڽ��մӼ�������Ķ��г��� 
	int n;
	
	printf("\n----------------------------------ѭ������-----------------------------------\n"); 
	
	printf("->��ʼ��ѭ������\n");
	InitQueue_Sq(Q);
	printf("��ʱ���г���Ϊ��%d\n", QueueLength_Sq(Q));
	
	printf("->������Ӳ���");
	printf("�������뼸��Ԫ��:");
	scanf("%d", &n);
	printf("����������Ԫ�أ��ÿո����\n");
	for(int i = 0; i < n; i++){
		scanf("%f", &e);
		EnQueue_Sq(Q, e);
	}//for
	printf("��Ӻ�Ľ��Ϊ\n");
	QueueTraverse_Sq(Q, Print);
	printf("\n��ʱ���г���Ϊ��%d\n", QueueLength_Sq(Q));
	
	printf("->���Գ��Ӻͻ�ȡ��ͷ����\n");
	GetHead_Sq(Q, e);
	printf("��ͷԪ��Ϊ%6.2f\n", e);
    while(!QueueEmpty_Sq(Q)){
		DeQueue_Sq(Q, e);
		printf("Ԫ��%6.2f����  \n", e);
	}//while
	printf("\n��ʱ���г���Ϊ��%d\n", QueueLength_Sq(Q));
	
	printf("->�������ٶ��в���");
    DestoryQueue_Sq(Q);
    
	return 0;
}//main

/* -----------------------------------���н��------------------------------------- 
	
	----------------------------------ѭ������-----------------------------------
	->��ʼ��ѭ������
	ѭ�������ѳɹ�������
	��ʱ���г���Ϊ��0
	->������Ӳ����������뼸��Ԫ��:10
	����������Ԫ�أ��ÿո����
	2 4 8 9 5 7 6 2 4 1
	��Ӻ�Ľ��Ϊ
	  2.00      4.00      8.00      9.00      5.00      7.00      6.00      2.00
	  4.00      1.00    
	��ʱ���г���Ϊ��10
	->���Գ��Ӻͻ�ȡ��ͷ����
	��ͷԪ��Ϊ  2.00
	Ԫ��  2.00����
	Ԫ��  4.00����
	Ԫ��  8.00����
	Ԫ��  9.00����
	Ԫ��  5.00����
	Ԫ��  7.00����
	Ԫ��  6.00����
	Ԫ��  2.00����
	Ԫ��  4.00����
	Ԫ��  1.00����
	
	��ʱ���г���Ϊ��0
	->�������ٶ��в���ѭ�������ѳɹ����٣�
	
	--------------------------------
	Process exited with return value 0
	Press any key to continue . . .
*/
