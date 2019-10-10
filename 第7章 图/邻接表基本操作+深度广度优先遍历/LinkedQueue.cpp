//------------------���е���ʽ�洢��ʾ----------------------- 
typedef int QElemType;   //����Ԫ��Ϊ������ָ������

typedef struct  QNode{  //�����е�C���Ա�ʾ                  
	 QElemType data;        //������ 
	 struct QNode * next;   //ָ���� 
}QNode,* QueuePtr;

typedef struct{
	QueuePtr front;  //��ͷָ�� 
	QueuePtr rear;   //��βָ�� 
}Queue; 

//--------------------------���е���غ���(���ǵݹ�������ʹ��)----------------------------
/*
	������MallocQNode
	�������� 
	����ֵ��ָ�����������ָ�� 
	���ã�Ϊ�����н�������ڴ�ĺ��� 
*/
QueuePtr MallocQNode(){
	
	//����ָ��p��ָ��������Ľ�� 
	QueuePtr p;
	
	//if(!(p = (QueuePtr)malloc(sizeof(QNode))))  �൱���������д��룺 
	//p = (QueuePtr)malloc(sizeof(QNode));
	//if(!p)  <=>  if(p != NULL) 
	//��������ڴ�ռ䣬��ʧ������ʾ���˳�����
	if(!(p = (QueuePtr)malloc(sizeof(QNode)))){
		printf("�ڴ����ʧ�ܣ����򼴽��˳���\n");
		exit(OVERFLOW);
	}//if
	
	//������������ĵ�ַ 
	return p;
}//MallocQNode 

/*
	������InitQueue
	������Queue &Q ���������� 
	����ֵ��״̬�룬�����ɹ�����OK 
	���ã�����һ���ն��� Q
*/
Status InitQueue(Queue &Q) {
	
	//����ͷ�����ڴ�ռ䣬��ʹ��ͷ�Ͷ�βָ��ͬʱָ����
	Q.front = Q.rear = MallocQNode();
	
	//����ͷ���ոճ�ʼ�������滹û��Ԫ�ؽ�� 
	Q.front->next = NULL;
	
	//ͷ����������¼�������г���
	//���ڴ�ʱ������û�����ݽڵ㣬���Խ�ͷ�����������Ϊ0 
	Q.front->data = 0;

	//�����ɹ� 
	return OK;
}//InitQueue 

/*
	������DestoryQueue
	������Queue &Q ���������� 
	����ֵ��״̬�룬�����ɹ�����OK 
	���ã����ٶ���Q
*/
Status DestoryQueue(Queue &Q){
	
	//��ͷ��㿪ʼ�������ͷŽ���ڴ�ռ� 
	while(Q.front){ //while(Q.front) <=> while(Q.front != NULL)
		
		//��βָ��ָ��ɾ�����ĺ�̽�� 
		Q.rear = Q.front->next;
		
		//�ͷ�Q.frontָ��ı�ɾ�����Ŀռ� 
		free(Q.front);
		
		//��ͷָ����ƣ�ָ����һ����ɾ����� 
		Q.front = Q.rear; 
	}//while
	
	//�����ɹ� 
	return OK;
}//DestoryQueue

/*
	������QueueEmpty
	������Queue Q ������Q 
	����ֵ��״̬�룬��QΪ�ն��У��򷵻�TRUE;���򷵻�FALSE
	���ã��ж϶���Q�Ƿ�Ϊ�� 
*/
Status QueueEmpty(Queue Q){
	
	//��ͷָ��Ͷ�βָ���ָ��������ͷ����ʾ������Ϊ�� 
	if(Q.rear == Q.front){
		return TRUE; 
	}//if
	else {
		return FALSE; 
	}//else
}//QueueEmpty

/*
	������EnQueue
	������Queue &Q ������Q������
	      QElemType e  �������Ԫ��e 
	����ֵ��״̬�룬�����ɹ��󷵻�OK�� 
	���ã�����Ԫ��eΪQ���µĶ�βԪ��
*/
Status EnQueue(Queue &Q, QElemType e){

	//����һ���µĽ�㣬��ʹpָ������½�� 
	QueuePtr p = MallocQNode(); 
	
	//��������Ԫ��e���浽�½�������� 
	p->data = e;
	
	//�����½��Ҫ���ڶ�β������û��������㣬���Ժ��ָ�����ֵΪNULL 
	p->next = NULL;
	
	//���½�����뵽��β 
	//����Ҫ��������ֻ�ܷ����ڶ�β 
	Q.rear->next = p;
	
	//������βָ�룬ʹָ֮��p��ָ����²���Ľ�� 
	Q.rear = p;
	
	//���ڲ���һ����㣬���Դ洢��ͷ����еĶ��г���+1 
	Q.front->data++;
	
	//��������ɹ� 
	return OK; 
}//EnQueue 

/*
	������DeQueue
	������Queue &Q ������Q������
	      QElemType &e ���ر�ɾ������Ԫ��e 
	����ֵ��״̬�룬�����ɹ��󷵻�OK�� 
	���ã������в���,��ɾ��Q�Ķ�ͷԪ��,��e������ֵ
*/
Status DeQueue(Queue &Q, QElemType &e){
	
	//ע�����Ϊ�պͶ��в����ڵ����𣬶���Ϊ�գ�ͷ���һ�����ڣ�
	//���в�����ʱͷ���һ��������
	//�Կն���ִ�г��Ӳ���û�����壬���Ӳ���ִ��ǰҪ�ȼ������Ƿ�Ϊ�� 
	if(QueueEmpty(Q)) { //if(QueueEmpty(Q)) <=> if(QueueEmpty(Q) != TRUE)
		return ERROR;
	}//if
	
	//����ָ��pָ���ͷ��һ����㣨����ͷ��㣬��ͷ���ĺ�̣�
	//����Ҫ��ɾ������ֻ�ܷ����ڶ�ͷ������pָ��ľ��Ǵ�ɾ���ڵ� 
	QueuePtr p = Q.front->next;
	
	//���汻ɾ������ֵ 
	e = p->data;
	
	//��ɾ������ִ��ǰ������ͷָ���λ�ã�ʹ֮��ɾ������ָ���µĶ�ͷ��� 
	Q.front->next = p->next;
	
	//����ɾ�����ǡ���Ƕ�β��㣬��ô�ý�㱻ɾ���󣬶��н����ɿն���
	//��ʱ�պ�����ն���������Q.rear == Q.front������Ҫ������βָ���λ�ã�ʹָ֮��ͷ��� 
	if(Q.rear == p) { 
	    Q.rear = Q.front;
	}//if
	
	//�ڶ�ͷָ��Ͷ�βָ���λ�ö���������֮��Ϳ���
	//���ĵ��ͷ�pָ��Ľ����ڴ�ռ��� 
	free(p);
	
	//���ڴӶ�����ɾ����һ����㣬ͷ���洢�Ķ��г���Ӧ��-1 
	Q.front->data--;
	
	//�����ɹ� 
	return OK; 
}//DeQueue

/*
	������Print
	������ElemType e �����ʵ�Ԫ�� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã�����Ԫ��e�ĺ�����ͨ���޸ĸú��������޸�Ԫ�ط��ʷ�ʽ��
	      �ú���ʹ��ʱ��Ҫ��ϱ�������һ��ʹ�á� 
*/
Status Print_Queue(QElemType e){
	
	//ָ��Ԫ�صķ��ʷ�ʽ�ǿ���̨��ӡ��� 
	printf("%6.2f    ",e);
	
	//�����ɹ� 
	return OK;
}//Print

/*
	������QueueTraverse
	������Queue Q ������Q 
	      Status (* visit)(QElemType) ����ָ�룬ָ��Ԫ�ط��ʺ����� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã�����Ԫ�ط��ʺ���������˳����������еı���������δ����ִ�г��Ӳ��� 
*/
Status QueueTraverse(Queue Q, Status (* visit)(QElemType)) {   
    
    //�Կն��н��б�������û�����壬���Ա�������ǰҪ���ж϶����Ƿ�Ϊ�� 
    //ע�����Ϊ�պͶ��в����ڵ����𣬶���Ϊ�գ�ͷ���һ�����ڣ�
	//���в�����ʱͷ���һ��������  
	if(QueueEmpty(Q)) { //if(QueueEmpty(Q)) <=> if(QueueEmpty(Q) != TRUE)
	    return ERROR;
	}//if
	
	//����ָ��pָ���ͷ��� 
	QueuePtr p = Q.front->next;
	
	//�Ӷ�ͷ��㿪ʼ���η���ÿ����㣬ֱ����β 
	while(p) { //while(p)  <=>  while(p != NULL) 
	
		//����Ԫ�ط��ʺ��� 
		if(!visit(p->data)) { 
			printf("�����������\n");
			return ERROR;
		}//if
		
		//����ָ��p���ƣ�ָ����һ��Ԫ�� 
		p = p->next;
	}//while
	
	//������У�ʹ���������� 
	printf("\n");
	
	//�����ɹ� 
	return OK; 
}//QueueTraverse

