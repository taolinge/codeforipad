
//ע�⣺�˵�����ͬ�����ϵĵ��������ϵĵ���������ͷ���ģ�
//      ���Ǵ˵�������ͷ��㣬���롢ɾ���ͺܶ�������������� 

/*
	������InitList
	������LinkList &L ���������� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã�����һ���յĲ���ͷ���ĵ�����L
*/
Status InitList(LinkList &L) {
	
	//û��ͷ���Ŀյ�����ͷָ��Ϊ��
	L = NULL;
	
	//�����ɹ�
	return OK; 
}//InitList 

/*
	������DestoryList
	������LinkList &L ���������� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã������Ա�L�Ѵ�����L����Ϊ�ձ�
*/
Status DestoryList(LinkList &L) {
	
	//����ָ��p 
	LinkList p;
	
	//������L����
	while(L) {
		
		//û��ͷ���ĵ�����ͷָ��Lָ����Ԫ��� 
		//pָ����Ԫ���
    	p = L;
    	
    	//Lָ��p�ĺ�� 
    	L = L->next;
    	
    	//�ͷ���Ԫ���
		free(p);
	}//while
	
	//�����ɹ� 
	return OK; 
}//DestoryList

/*
	������ListEmpty
	������LinkList L ������L
	����ֵ��״̬�룬��LΪ�ձ���TRUE�����򷵻�FALSE
	���ã��жϵ�����L�Ƿ�Ϊ�� 
*/
Status ListEmpty(LinkList L) {
	
	//ͷָ��ֱ��ָ����Ԫ��㣬��ͷָ��ΪNULL��������Ϊ�ա� 
	if(L) { //if(L) <=> if(L != NULL)
    	return FALSE;
    }//if 
	else {
    	return TRUE;
	}//else 
}//ListEmpty

/*
	������ListLength
	������LinkList L ���������� 
	����ֵ������L������Ԫ�ظ���
	���ã��õ��� 
*/
int ListLength(LinkList L) {

	//i��һ������������¼�˱� 
	int i = 0;
	
	//����ָ��pָ���������Ԫ��� 
	LinkList p = L;
	
	//������������������� 
	while(p) { //while(p) <=> while(p != NULL)
		
		//pָ����һ�����
    	p = p->next;
    	
    	//�ҵ�һ����������+1 
     	i++;
	}//while
	
	//���ر� 
	return i;
}//ListLength

/*
	������GetElem
	������LinkList L ����ͷ���ĵ������ͷָ��
	      int i ���ҵ�i��Ԫ��
		  ElemType &e ʹ��e���ص�i��Ԫ�ص�ֵ 
	����ֵ��״̬�룬�ҵ���i��Ԫ�ط���OK�����򷵻�ERROR 
	���ã�����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR
*/
Status GetElem(LinkList L, int i, ElemType &e) {
   
   	//��ʱ��������¼�Ѿ���������Ԫ�ظ��� 
	int j = 1;
	
	//����ָ��pָ��������Ԫ��� 
	LinkList p = L;
	
	//������i��ֵ�Ƿ�Ϸ���i�Ƿ�Խ�� 
	if(i < 1) { 
    	return ERROR;
    }//if
	
	//�ڵ������д�ͷ��ʼ�����ҵ�i��Ԫ�� 
	//û����i��Ԫ�أ�Ҳû����β
	//while(j < i && p) <=> while(j < i && p != NULL)
	while(j < i && p) {
    	
    	//������j+1 
		j++;
		
		//pָ����һ����� 
    	p = p->next;
	}//while
	
	//�ҵ��˵�i��Ԫ�����ڽ�㣬��ʱpָ��ý�� 
	if(j == i) {
    	
    	//���Ƶ�i��Ԫ�ص�ֵ��e 
		e = p->data;
		
		//�����ɹ� 
    	return OK;
   	}//if
   	else { 
    	return ERROR;
    }//else 	
}//GetElem

/*
	������LocateElem
	������LinkList L ����ͷ���ĵ������ͷָ��
	      ElemType e ����Ԫ��e 
		  Status(*compare)(ElemType, ElemType) ����ָ�룬ָ��Ԫ�رȽϺ���compare() 
	����ֵ�����ص�����L�е�1����e�����ϵcompare()������Ԫ�ص�λ��
	        ������������Ԫ�ز����ڣ��򷵻�ֵΪ0�� 
	���ã�����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR
*/
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType)) {
	
	//��ʱ������������   
	int i = 0;
	
	//����ָ��pָ����Ԫ��� 
	LinkList p = L;
	
	//������L�б���ÿһ����㣬����ֵΪe��Ԫ�� 
	while(p) { //while(p) <=> while(p != NULL)
		
		//������+1 
    	i++;
    	
    	//�ҵ�����������Ԫ��
    	//if(compare(p->data, e)) <=> if(compare(p->data, e) != 0)  
    	if(compare(p->data, e)) { 
    		return i;
    	}//if
		
		//pָ����һ����� 
    	p = p->next;
	}//while
	
	//��û���ҵ�ֵΪe�Ľ�㣬����0 
	return 0;
}//LocateElem

/*
	������ListInsert
	������LinkList &L ���������� 
	      int i �ڵ�i��λ��֮ǰ���� 
		  ElemType e �������Ԫ��e 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERROR�� 
	���ã�����ͷ���ĵ������Ա�L�е�i��λ��֮ǰ����Ԫ��e
*/
Status ListInsert(LinkList &L, int i, ElemType e) {
   
   	//����������¼���ҹ��Ľ���� 
   	int j = 1;
   
   	//p�ǹ���ָ�룬��ʼλ��ָ��������Ԫ��� 
   	//sָ�򱻲����� 
   	LinkList p = L, s;
   
	//������i��ֵ�Ƿ�Ϸ� 
	if(i < 1) { //iԽ�� 
		return ERROR;
	}//if
	
	//�����������㲢ʹsָ���½��
	s = (LinkList)malloc(sizeof(LNode));
	
	//���������ֵe��䵽�½��s���������� 
	s->data = e;
	
	//ע�⣺��������ͷ��㣬������������жϲ���λ���Ƿ��ڱ�ͷ
	//      ������ڱ�ͷ������Ҫ�޸�ͷָ�룬���ڱ�ͷ��������Ҫ�� 
   	if(i == 1) { //���ڱ�ͷ
   		
   		//ֱ�Ӱ�����ԭ�н��ҵ��½����� 
		s->next = L;
     	
     	//ʹͷָ��Lָ��sָ����½�㣬s��Ϊ�µ���Ԫ��� 
		L = s;
   	}//if
	else { //����λ�ò��ڱ�ͷ 
    	
    	//Ѱ�ҵ�i-1�����
		while(p && j < i - 1) {
			
			//pָ����һ����� 
			p = p->next;
			
			//������j+1 
			j++;
		}//while
		
		//û�ҵ���i-1����� 
		if(!p) { //if(!p) <=> if(p != NULL) 
			//����ʧ�� 
			return ERROR;
		}//if
		
		//����i-1��������Ľ��ҵ�sָ��Ľ����� 
		s->next = p->next;
		
		//��sָ��Ľ����ͬ����Ľ��ҵ�ԭ���ĵ�i-1��������
		//s��Ϊ�µĵ�i����㡣 
    	p->next = s;
	}//else 
	
	//�����ɹ� 
	return OK;
}//ListInsert

/*
	������ListDelete
	������LinkList &L ���������� 
	      int i �ڵ�i��λ��֮ǰɾ��
		  ElemType &e ���ر�ɾ����Ԫ��e 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERROR�� 
	���ã��ڲ���ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ�أ�����e������ֵ
*/
Status ListDelete(LinkList &L, int i, ElemType &e) { 
	
	//����������¼���ҹ��Ľ���� 
	int j = 1;
	
	//p�ǹ���ָ�룬��ʼֵָ���������Ԫ���
	//����ָ��qָ��ɾ����� 
	LinkList p = L, q = NULL;
	
	//ע�⣺����ʹ�õ��ǲ���ͷ���ĵ�����ͷָ��ֱ��ָ����Ԫ���
	//      ִ��ɾ������ʱ��Ҫ�ж�ɾ��λ���Ƿ����ڱ�ͷ��
	//      ���ɾ�������ڱ�ͷִ�У�����Ҫ�޸�ͷָ�룬������Ҫ�� 
	if(i == 1) { //��ɾ��������Ԫ���
		
		//ɾ����Ԫ����ɾ��ǰ�ĵڶ���Ԫ�ؽ�㽫��Ϊ�µ���Ԫ��㡣
		//������Ҫ�޸ĵ�����ͷָ��L��ָ��ʹ��ָ��ڶ�����㣬Ϊɾ������׼���� 
    	L = p->next;
    	
    	//���汻ɾ�����p��ֵ��e 
    	e = p->data;
    	
    	//�ͷ���Ԫ�����ڴ�ռ� 
    	free(p);
   	}//if
	else {
		
		//Ѱ�ҵ�i-1����㣬����pָ���� 
		//while(p->next && j < i - 1) <=> while(p->next != NULL && j < i - 1) 
    	while(p->next && j < i - 1) {
    		
    		//pָ����һ����� 
			p = p->next;
			
			//������+1 
			j++;
		}//while
		
		//����Ƿ��ҵ���i-1����㣬��û���ҵ�����ֹ������ִ�� 
    	if(!p->next || j > i - 1) { 
			
			//����ʧ�� 
			return ERROR;
		}//if
		
		//�ҵ��˵�i-1����㣬pָ���i-1����㡣 
		
		//qָ��p�ĺ�̣�����i����㣬Ҳ���Ǳ�ɾ����� 
    	q = p->next;
    	
    	//��qָ��ı�ɾ����㣨��i����㣩����Ľ��ҵ�pָʾ��
		//��i-1�������档Ҳ���ǰ�qָ��ĵ�i�����������и�������� 
     	p->next = q->next;
		
		//���汻ɾ������Ԫ��ֵ 
    	e = q->data;
    	
    	//�ͷ�qָ��ı�ɾ�������ڴ�ռ� 
    	free(q);
   }//else
   
   //�����ɹ� 
   return OK;
}//ListDelete

/*
	������ListTraverse
	������LinkList L ����ͷ��㵥����L��ͷָ�� 
	      int i �ڵ�i��λ��֮ǰɾ��
		  ElemType &e ���ر�ɾ����Ԫ��e 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERROR�� 
	���ã���������ͷ���ĵ�����L
*/
Status ListTraverse(LinkList L, Status(*Visit)(ElemType)) {
   
   	//����ָ��pָ���������Ԫ��� 
   	LinkList p = L;
   
   	//���ζԵ�������ÿ��Ԫ�ص���Visit�������з��������ҽ�һ�Ρ�
   	while(p) { //while(p) <=> while(p != NULL) 
   		
   		//һ��Visitʧ�������ʧ��
		//if(!Visit(p->data)) <=> if(Visit(p->data) == ERROR)  
		if(!Visit(p->data)) {
			return ERROR;
		}//if
		
		//pָ����һ����� 
     	p = p->next;
	}//while
	
	//�������ʹ��ӡ������� 
	printf("\n");
}//ListTraverse
 
/*
	������Point
	������LinkList L ������L��ͷָ�루ע�⣬������û��ͷ��㣩 
	      ElemType e �ڵ������в���Ԫ��e����λ�� 
		  Status(*equal)(ElemType, ElemType) ����ָ�룬ָ��Ԫ�رȽϺ���
		  LinkList &p ����ָ��e���ǰ������ָ�� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã����ұ�L�����������Ľ�㡣���ҵ�������ָ��ý���ָ�룬
	      pָ��ý���ǰ��(���ý������Ԫ��㣬��p=NULL)��
		  ���L�������������Ľ�㣬�򷵻�NULL��p�޶��塣
		  ����equal()�����βεĹؼ�����ȣ�����OK�����򷵻�ERROR
*/
LinkList Point(LinkList L, ElemType e, Status(*equal)(ElemType, ElemType), LinkList &p) {
   
   //i�洢�˲���Ԫ��e�õ���λ�� 
   int i, j;
   
   //����Ԫ��e�õ�Ԫ�ص�λ��i����i=0��˵����������δ�ҵ�Ԫ��e 
   //���ҵ�Ԫ��e����Lָ���ҵ��Ľ�� 
   i = LocateElem(L, e, equal);
   
   //�ڵ��������ҵ�Ԫ��e 
   if(i) { //if(i) <=> if(i != 0) 
   		
		//���ҵ�������Ԫ���
		if(i == 1) {
			
			//��Ԫ���û��ǰ�� 
			p = NULL;
			
			//����ָ����Ԫ����ָ�� 
			return L;
		}//if
		
		//���ҵ��Ĳ�����Ԫ���
		
		//pָ����Ԫ��� 
     	p = L;
     	
     	//pָ���ҵ�����ǰ�� 
		for(j = 2; j < i; j++) { 
			p = p->next;
		}//for
		
		//����ָ���ҵ��Ľ���ָ�� 
		return p->next;
   }//if
   
   //�ڵ�������û�ҵ�ֵΪe�Ľ�� 
   return NULL;
}//Point

/*
	������DeleteElem
	������LinkList &L ���������ã�ע�⣬������û��ͷ��㣩 
	      ElemType &e eЯ���Ƚ����� 
		  Status(*equal)(ElemType, ElemType) ����ָ�룬ָ��Ԫ�رȽϺ���
	����ֵ��״̬�룬ɾ����L�����������Ľ��ɹ�����TRUE�����޴˽�㣬�򷵻�FALSE��
	���ã�ɾ����L�����������Ľ�㣬������TRUE�����޴˽�㣬�򷵻�FALSE��
		  ����equal()�����βεĹؼ�����ȣ�����OK�����򷵻�ERROR
*/
Status DeleteElem(LinkList &L, ElemType &e, Status(*equal)(ElemType,ElemType)) {
 
	//����ָ��p��q 
	LinkList p, q;
	
	//�ӵ�����L���ҳ����������Ľ�㣬ʹqָ��˽�㣬pָ��q��ǰ�� 
	//��qָ����Ԫ��㣬p=NULL 
	q = Point(L, e, equal, p);
	
	//�ҵ��˽�㣬��qָ��ý��
	if(q) { //if(q) <=> if(q != NULL) 
		
		//�ý�㲻����Ԫ��㣬pָ����ǰ��
    	if(p) { //if(p) <=> if(p != NULL)
    		
    		//��p��Ϊͷָ��,ɾ����2�����
			ListDelete(p, 2, e);
		}//if 
    	else { // �ý������Ԫ���
    		
			ListDelete(L, 1, e);
    		
    		//�����ɹ� 
			return TRUE;
    	}//else 
	}//if
	
	//�Ҳ����˽�� 
	return FALSE;
}//DeleteElem 
