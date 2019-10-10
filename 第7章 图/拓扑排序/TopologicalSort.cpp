
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
	for(int i = 0; i < G.vexnum; i++) {
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

/*
	������TopologicalSort
	������ALGraph G ����ͼG���ڽӱ�洢�ṹ�� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã���G�޻�·�������G�Ķ����һ���������в�����OK��
	      ���򷵻�ERROR��
*/
Status TopologicalSort(ALGraph G) {
	
	//countΪ���������������ֵΪ0
	int i, k, count = 0;
	
	//������飬��Ÿ����㵱ǰ�����
	int indegree[MAX_VERTEX_NUM];
	
	//����ջS 
	Stack S;
	
	//����ָ��p,ָ�򻡽�� 
	ArcNode *p; 
	
	//�Ը���������Ȳ���������indegree[]
	FindInDegree(G, indegree);
	
	//��ʼ������ȶ���ջS
	InitStack(S);
	
	//ɨ�����ж���
	for(i = 0; i < G.vexnum; ++i) {
    	
    	//�������Ϊ0����iѹ������ȶ���ջS
    	//if(!indegree[i]) <=> if(indegree[i] == 0) 
		if(!indegree[i]) { 
    		Push(S, i); 
    	}//if
    }//for
		 
	//������ȶ���ջS����
	//while(!StackIsEmpty(S)) <=> while(StackIsEmpty(S) == FALSE)
	while(!StackIsEmpty(S)) {
		
		//��ջ�е���һ������ȶ������ţ������䱣�浽i
		Pop(S, i);
		
		//���i�Ŷ���
		printf(" %d ", G.vertices[i].data);
		
		//�����������+1
		++count;
		
		//ɨ��i�Ŷ����ÿ���ڽӶ���
		for(p = G.vertices[i].firstarc; p; p = p->nextarc) { 
			
			//i�Ŷ�����ڽӵ����Ϊk
			k = p->data.adjvex;
			
			//k����ȼ�1������Ϊ0����k��ջS
			//if(!(--indegree[k])) <=> if((--indegree[k]) == 0)
			if(!(--indegree[k])) { 
				Push(S, k);
			}//if
		}//for
	}//while
 	
 	
 	//����ȶ���ջS�ѿգ�ͼG���ж���δ���
	if(count < G.vexnum) {
		printf("������ͼ�л�·\n");
		return ERROR;
	}//if
	else {
		return OK;
	}//else 
}//TopologicalSort
