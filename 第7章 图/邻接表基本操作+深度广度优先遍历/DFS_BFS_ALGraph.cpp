//------------------------Ԫ�ط��ʺ���----------------------

/*
	������print
	������VertexType v ����v 
	����ֵ����
	���ã�Ԫ�ط��ʺ�����������ʹ�á� 
*/
void print(VertexType v) {
	
	printf(" %d ", v);
		
}//print 


//------------------------������ȱ���---------------------- 

//���ʱ�־����(���ȵ�����󶥵���)
int visited[MAX_VERTEX_NUM];

//���ʺ���(ͨ��ȫ�ֱ����ķ�ʽ���ݿ��Լ��ٲ������ݵĴ���)
void(*VisitFunc)(VertexType v);

/*
	������DFS
	������ALGraph G ͼG 
	      int v ����ͼG�еĵ�v������ 
	����ֵ����
	���ã��ӵ�v����������ݹ��������ȱ���ͼG��
*/
void DFS(ALGraph G, int v) { 
	
	//w����ʱ������ѭ�������� 
	int w;
	
	//���÷��ʱ�־ΪTRUE����ʾ�ö����ѷ���
	visited[v] = TRUE;
	
	//���ʵ�v������
	VisitFunc(G.vertices[v].data);
	
	//���η���v��δ�����ʵ��ڽӵ� 
   	for(w = FirstAdjVex(G, G.vertices[v].data); w >= 0; 
	   	w = NextAdjVex(G, G.vertices[v].data, G.vertices[w].data)) { 
    	
    	//��v����δ���ʵ��ڽӵ�w�ݹ����������ȱ����㷨DFS
		if(!visited[w]) { 
    		DFS(G, w);
    	}//if
	}//for
}//DFS

/*
	������DFS
	������ALGraph G ͼG 
	      void(*Visit)(char*) ָ�����������ָ�� 
	����ֵ����
	���ã���ͼG��������ȱ�����
*/
void DFSTraverse(ALGraph G, void(*Visit)(VertexType)) {

	//ʹ��ȫ�ֱ���VisitFunc��ʹDFS�����躯��ָ�����
	VisitFunc = Visit;
	
	//��ʼ�����ʱ�־����ÿ������ı�־ֵΪFALSE����ʾ���ж��㶼δ������ 
	for(int v = 0; v < G.vexnum; v++) {
    	visited[v] = FALSE;
	}//for
	
	//���η���ͼ��ÿ������ 
	for(int v = 0; v < G.vexnum; v++) { 
    	
    	//����δ���ʵĶ������DFS
		if(!visited[v]) { 
    		DFS(G, v);
    	}//if
	}//for
	
	//������ɺ��У�ʹ������� 
	printf("\n");
}//DFSTraverse

//------------------------������ȱ���----------------------- 

/*
	������BFSTraverse
	������ALGraph G ͼG 
	      void(*Visit)(char*) ָ�����������ָ�� 
	����ֵ����
	���ã���������ȷǵݹ����ͼG��ʹ�ø�������Q�ͷ��ʱ�־����visited��
*/
void BFSTraverse(ALGraph G, void(*Visit)(VertexType)) {
	
	//v����ʱ���� 
	int v, u, w;
	
	//�������� 
	Queue Q;
	
	//���ý����ʱ������ĳ�ʼֵΪFALSE����ʾû�ж��㱻���ʹ� 
	for(v = 0; v < G.vexnum; ++v) { 
    	visited[v] = FALSE;
    }//for
    
    //��ʼ����������Q���õ�һ���ն��� 
	InitQueue(Q);
	
	//�������ͨͼ��ֻҪһ��ѭ���Ϳ��Ա���ȫ������ 
	for(v = 0; v < G.vexnum; v++) { 
    	
    	//v��δ����
		if(!visited[v]) {
			
			//���ö���v�ı�־ΪTRUE����ʾ����v�ѱ����� 
			visited[v] = TRUE;
			
			//���÷��ʺ���Visit���ʶ���v 
       		Visit(G.vertices[v].data);
    		
    		//v�����
			EnQueue(Q, v);
       
       		//���в���
	   		while(!QueueEmpty(Q)) {
        		
        		//��ͷԪ�س��Ӳ���Ϊu
				DeQueue(Q, u);
				
				//����u��δ���ʵ��ڽӶ��� 
         		for(w = FirstAdjVex(G, G.vertices[u].data); w >= 0; 
				 	w = NextAdjVex(G, G.vertices[u].data, G.vertices[w].data)) { 
           			
           			//wΪu����δ���ʵ��ڽӶ���
					if(!visited[w]) {
						
						//���ö���w�ķ��ʱ�־ΪTRUE 
						visited[w] = TRUE;
						
						//���ʶ���w 
             			Visit(G.vertices[w].data);
             			
             			//����w��� 
             			EnQueue(Q, w);
	   				}//if
       			}//for 
     		}//while
		}//if 
	}//for 
	
	//�������� 
	printf("\n");
}//BFSTraverse 
