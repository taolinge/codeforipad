
//������ȱ����õ����е�ʵ�� 

#define MAXQSIZE 100        //���е���󳤶� 
typedef int Status;
typedef int QElemType;

typedef struct {            //ѭ�����е�C�������� 

	QElemType *base;        //��ʼ����̬����洢�ռ�
	int front;              //ͷָ�룬�����в��գ�ָ���ͷԪ�� 
	int rear; 	            //βָ�룬�����в��գ�ָ���βԪ�ص���һ��λ�� 
}SqQueue; 

//----------------------ѭ�����е���Ҫ����------------------------

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
	return OK;
}//InitQueue_Sq

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
	return OK;
}//DestoryQueue_Sq

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
