//��ӡ�ؼ�·���õ��ļ������� 
void printhead(ALGraph G);
void printi(ALGraph G);
void printvex(ALGraph G);
void printve(ALGraph G, int ve[]);
void printvl(ALGraph G, int vl[]);
void printCritical1(ALGraph G, int ve[], int vl[]);

/*
	������FindInDegree
	������ALGraph G ͼG���ڽӱ�洢�ṹ�� 
	      int indegree[] �洢������ȵ����� 
	����ֵ����
	���ã��󶥵�����
*/
void FindInDegree(ALGraph G, int indegree[]) {
	
	//����ָ��p 
	ArcNode *p;
	
	//�Դ洢��ȵ�indegree���鸳��ֵ0
	for(int i = 0; i < MAX_VERTEX_NUM; i++) {
    	indegree[i] = 0; 
	}//for
	
	//ɨ��ÿ���������Ļ����� 
	for(int i = 0; i < G.vexnum; i++) {
		
		//pָ�򶥵�i���满�������Ԫ��� 
    	p = G.vertices[i].firstarc;
    	
    	//����v�Ļ�����û��ɨ����� 
    	while(p) { //while(p) <=> while(p != NULL) 
    		//ÿ�ҵ�һ������㣬��Ӧ�ڽӵ�����+1 
    		indegree[p->data.adjvex]++;
    		
    		//pָ����һ������� 
    		p = p->nextarc;
    	}//while 
	}//for
}//FindInDegree


//�¼����緢��ʱ�䣬ȫ�ֱ���
int ve[MAX_VERTEX_NUM];

/*
	������TopologicalOrder
	������ALGraph G ͼ���ڽӱ�洢��ʾ
	      Stack &T �������ж���ջ  
	����ֵ��״̬�룬OK��ʾ�����ɹ�,ERROR��ʾ����ʧ�� 
	���ã�������G�����ڽӱ�洢�ṹ����������¼������緢��ʱ��ve(ȫ�ֱ���)��
	      ��G�޻�·������ջT����G��һ����������,�Һ���ֵΪOK,����ΪERROR     
*/
Status TopologicalOrder(ALGraph G, Stack &T) {
	
	//count������ջ����������ֵΪ0
	int i = 0, k = 0, count = 0;
	
	//������飬��Ÿ����㵱ǰ�����
	int indegree[MAX_VERTEX_NUM];
   
	//SΪ����ȶ���ջ�� 
	Stack S;
	
	//ָ�򻡽��Ĺ���ָ��p 
   	ArcNode *p;
   	
   	//�Ը���������Ȳ���������indegree[]
	FindInDegree(G, indegree);
	
	//��ʼ������ȶ���ջS
	InitStack(S);
	
	printf("->��õ��������У�");
	
	//�����ж���i
	for(i = 0; i < G.vexnum; ++i) { 
		
		//�������Ϊ0,��iѹ������ȶ���ջS
		//if(!indegree[i]) <=> if(indegree[i] == 0)
    	if(!indegree[i]) {
    		Push(S, i);
    	}//if
    }//for 
    
    //��ʼ���������ж���ջ
	InitStack(T);
	
	//��ʼ��ve[]=0(��Сֵ���ȼٶ�ÿ���¼������������¼�Լ��)
	for(i = 0; i < G.vexnum; ++i) {
    	ve[i] = 0;
	}//for 
	
	//������ȶ���ջS����
	//while(!StackIsEmpty(S)) <=> while(StackIsEmpty(S) == FALSE)
	while(!StackIsEmpty(S)) {
    
    	//��ջS������������Ķ���j����
		Pop(S, i);
		
		//��ӡ��ջ�����Ϊi�Ķ��� 
    	printf("%d ", G.vertices[i].data);
    	
    	//j�Ŷ���������������ջT(ջ��Ԫ��Ϊ��������ĵ�1��Ԫ��)
    	Push(T, i);
    	
    	//����ջT�Ķ������
    	++count;
    	
    	//��i�Ŷ����ÿ���ڽӵ�
    	for(p = G.vertices[i].firstarc; p; p = p->nextarc) {
       		
			//�ڽӵ����Ϊk
			k = p->data.adjvex;
			
			//k����ȼ�1֮���Ϊ0��������ȶ��㣬��k��ջS
    		if(--indegree[k] == 0) { 
				Push(S, k);
			}//if
			 
			//����k�¼������緢��ʱ��Ҫ����ֱ��ǰ������i�¼���
			//���緢��ʱ���<i,k>��ȨֵԼ��������i���������򣬹�ve[i]���ٸı�
			//*(p->data.info)��<i,k>��Ȩֵ
    		if(ve[i] + *(p->data.info) > ve[k]) {
	 			ve[k] = ve[i] + *(p->data.info);
	 		}//if 
    	}//for
	}//while
	
	//����������������ж��㲻������������˵��ͼG���ڻ�· 
	if(count < G.vexnum) {
    	printf("���������л�·\n");
    	return ERROR;
	}//if
	else { 
    	return OK;
	}//else
}//TopologicalOrder

/*
	������CriticalPath
	������ALGraph G ͼ���ڽӱ�洢��ʾ
	����ֵ��״̬�룬OK��ʾ�����ɹ� 
	���ã����G�ĸ���ؼ��   
*/
Status CriticalPath(ALGraph G) {
	
	//�¼���ٷ���ʱ��
	int vl[MAX_VERTEX_NUM];
	
	Stack T;
   	
	int i, j, k, ee, el, dut;
   	
   	//����ָ��p 
   	ArcNode *p;
   	
   	//��������
	if(!TopologicalOrder(G, T)) { 
    	return ERROR;
    }//if
    
    printf("\n->ͨ����������ͼ��û�л���\n");
	
	//j�ĳ�ֵ
	j = ve[0]; 
	
	//�������緢��ʱ��ve[] 
	for(i = 1; i < G.vexnum; i++){
    	
    	//j = Max(ve[]) ��ɵ�����緢��ʱ��
		if(ve[i] > j) {
    		j = ve[i]; 
    	}//if 
	}//for
   	
   	//��ʼ�������¼�����ٷ���ʱ��
	for(i = 0; i < G.vexnum; i++) {
		
		//��ʼ�����ж����¼�����ٷ���ʱ��Ϊ��ɵ�����緢��ʱ��(���ֵ)
    	vl[i] = j; 
	}//for
	
	//������������������vlֵ
	while(!StackIsEmpty(T)) {
		
		//����ջT��Ԫ��,����j,pָ��j�ĺ���¼�k
    	for(Pop(T, j), p = G.vertices[j].firstarc; p; p = p->nextarc) {
			
			//�¼�k����ٷ���ʱ����ȷ��(��Ϊ������������)
    		k = p->data.adjvex;
    		
    		//dut=<j,k>��Ȩֵ
    		dut = *(p->data.info);
    		
    		//�¼�j����ٷ���ʱ��Ҫ����ֱ�Ӻ���¼�k����ٷ���ʱ��
    		//��<j,k>��ȨֵԼ��������k�����������򣬹�vl[k]���ٸı�
    		if(vl[k] - dut < vl[j]) {
				vl[j] = vl[k] - dut;
			}//if 
    	}//for                    
    }//for
    
    //��ӡ��ͷ
	printhead(G); 
    
    //��ӡi
	printi(G);
	
	//��ӡ����ֵ 
	printvex(G); 
    
    //��ӡve
    printve(G, ve);
	
	//��ӡvl
	printvl(G, vl);
	
	//��ӡ�ؼ�·���Ƿ񾭹��˶��� 
	printCritical1(G, ve, vl); 
	
	//��ee��el�͹ؼ��
	printf("\n+------+------+------+------+------+----------+\n");
	printf("|                  ����ߣ�                 |\n");
	printf("+------+------+------+------+------+----------+\n");
	printf("| ��β | ��ͷ | Ȩֵ |  ee  |  el  | �ؼ�� |\n");
	printf("+------+------+------+------+------+----------+\n");
	for(j = 0; j < G.vexnum; ++j) {
		
		//pָ��j���ڽӵ�k 
    	for(p = G.vertices[j].firstarc; p; p = p->nextarc) {
    		
			k = p->data.adjvex;
			
			//dut=<j,k>��Ȩֵ
       		dut = *(p->data.info);
       		
       		//ee=�<j,k>�����翪ʼʱ��(��j��)
    		ee = ve[j];
    		
    		//el=�<j,k>����ٿ�ʼʱ��(��j��)
    		el = vl[k] - dut;
    		
    		//��ӡee��el��ֵ 
    		printf("| %4d | %4d |  %3d |  %3d |  %3d |%s|\n", 
				G.vertices[j].data, G.vertices[k].data, dut, ee, el,
				ee == el ? "    ��    " : "          ");
    		
			printf("+------+------+------+------+------+----------+\n");
    	}//for
	}//for
	
	//�����ɹ� 
	return OK;
}//CriticalPath

/*
	������printhead
	������ALGraph G ͼG���ڽӱ��ʾ�� 
	����ֵ����
	���ã���ӡ��ͷ 
*/
void printhead(ALGraph G) {
	
	//��һ�� 
	printf("\n+-----------");
	
	for(int i = 0; i < G.vexnum - 1; i++) {
		
		printf("------");
	}//for 
	
	printf("-----+\n|");
	
	//�ڶ��У��ַ�����12
	//�м�λ�ã�[(10 + 1) + G.vexnum * (5 + 1) - 1 - 12] / 2 
	// <=> (6 * G.vexnum - 2) / 2
	
	int count = 6 * G.vexnum - 2;
	
	for(int i = 0; i < count / 2 ; i++) {
		
		printf(" ");
	}//for 
	
	printf("���㣨�¼���");
	
	for(int i = 0; i < count - count / 2; i++) {
		
		printf(" ");
	}//for 
	
	printf("|\n");
	
	printf("+----------+");
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("-----+");
	}//for  
	
	printf("\n"); 
}//printhead

/*
	������printi
	������ALGraph G ͼG���ڽӱ��ʾ��
	����ֵ����
	���ã��Ա����ʽ��ӡi  
*/
void printi(ALGraph G) {
	
	printf("|     i    |"); 
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("  %2d |", i);
	}//for 
	
	printf("\n"); 
	
	printf("+----------+");
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("-----+");
	}//for 
	
	printf("\n");
}//printi

/*
	������printvex
	������ALGraph G ͼG���ڽӱ��ʾ��
	����ֵ����
	���ã��Ա����ʽ��ӡ��������  
*/
void printvex(ALGraph G) {
	
	printf("|   ����   |"); 
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("  %2d |", G.vertices[i]);
	}//for 
	
	printf("\n"); 
	
	printf("+----------+");
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("-----+");
	}//for 
	
	printf("\n");
}//printvex

/*
	������printve
	������ALGraph G ͼG���ڽӱ��ʾ��
		  int ve[] �¼������緢��ʱ��ve[] 
	����ֵ����
	���ã��Ա����ʽ��ӡve����  
*/
void printve(ALGraph G, int ve[]) {
	
	printf("|    ve    |"); 
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("  %2d |", ve[i]);
	}//for 
	
	printf("\n"); 
	
	printf("+----------+");
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("-----+");
	}//for 
	
	printf("\n"); 
}//printve

/*
	������printvl
	������ALGraph G ͼG���ڽӱ��ʾ��
		  int vl[] �¼���������ʱ��vl[] 
	����ֵ����
	���ã��Ա����ʽ��ӡve����  
*/
void printvl(ALGraph G, int vl[]) {
	
	printf("|    vl    |"); 
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("  %2d |", vl[i]);
	}//for 
	
	printf("\n"); 
	
	printf("+----------+");
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("-----+");
	}//for 
	
	printf("\n"); 
}//printvl

/*
	������printCritical1
	������ALGraph G ͼG���ڽӱ��ʾ��
	      int ve[] �¼������緢��ʱ��ve[] 
		  int vl[] �¼���������ʱ��vl[] 
	����ֵ����
	���ã��Ա����ʽ��ӡ�����Ƿ��ڹؼ�·���� 
*/
void printCritical1(ALGraph G, int ve[], int vl[]) {
	
	printf("| �ؼ�·�� |"); 
	
	for(int i = 0; i < G.vexnum; i++) {
		
		//�ڹؼ�·���ϵĶ���ӡ̱�� 
		if(ve[i] == vl[i]) { 
    		printf("  �� |");
    	}//if 
    	else {
    		printf("     |");
    	}//else
	}//for 
	
	printf("\n"); 
	
	printf("+----------+");
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("-----+");
	}//for 
	
	printf("\n");
}//printCritical1
