//-----------------------������ȱ���DFS-----------------------------

//���ʱ�־���� 
int visited[MAX_VERTEX_NUM];

//�������� 
Status (*VisitFunc)(int v);

/*
	������Print
	������int v �����ʵĶ���v 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã�Ԫ�ط��ʺ���
*/
Status Print(int v){
	
	//����Ԫ�ط��ʷ�ʽΪ����̨��ӡ 
	printf(" %3d ", v);
	
	//�����ɹ� 
	return OK;
}//Print

/*
	������DFSTraverse
	������MGraph G ͼG
	      int v �����Ϊv�Ķ������ 
	����ֵ����
	���ã��ӵ�v����������ݹ��������ȱ���ͼG
*/
void DFS(MGraph G, int v){
    
    //�Ƚ����ʱ�־�����Ԫ�صķ��ʱ�־��ΪTrue��
	//���������Ϊv�Ķ����ѱ����� 
	visited[v] = TRUE;
	
	//���ʵ�v������
	VisitFunc(G.vexs[v]);
	
	//���η���v�ĸ����ڽӶ��㣨��v���ڽӵ����죩 
	for(int w = FirstAdjVex(G, G.vexs[v]); w >= 0; 
			w = NextAdjVex(G, G.vexs[v], G.vexs[w])){
		
		//��v����δ�����ʵ��ڽӵ�w�ݹ����DFS 
		if(!visited[w]) { 
		    DFS(G, w);
		}//if 
	}//for
}//DFS

/*
	������DFSTraverse
	������MGraph G ͼG
	      Status (*Visit)(int v) ����ָ�룬ָ��Ԫ�ط��ʺ��� 
	����ֵ����
	���ã���ͼG��������ȱ���,����Visit()�������ʽ��
*/
void DFSTraverse(MGraph G, Status (*Visit)(int v)){
	
	//ʹ��ȫ�ֱ���VisitFunc��ʹDFS�����躯��ָ����� 
	VisitFunc = Visit;
	
	//Ԥ�ñ�־����visited����ֵΪFALSE 
	for(int v = 0; v < G.vexnum; ++v) { 
	    visited[v] = FALSE;
	}//for
	
	//������ȱ�����ѭ�� 
	//д��ѭ����Ϊ�˱�֤��ͼ��Ϊ�����ͨ����ʱ�ܶ�
	//ÿ����ͨ�������б��� 
	for(int v = 0; v < G.vexnum; ++v) {
		
		//���ö���δ�����ʣ������DFS()���ʸýڵ�
		if(!visited[v]) {
	    	DFS(G, v); 
		}//if
	}//for 
}//DFSTraverse

//----------------������ȱ��� (��Ҫʹ�ö���)BFS------------ 
//˵�������е���ش��������"SqQueue.cpp"�У����ڶ��е���ϸ�������Ķ����ļ�

/*
	������BFSTraverse
	������MGraph G ͼG
	      Status (*Visit)(int v) ����ָ�룬ָ��Ԫ�ط��ʺ��� 
	����ֵ����
	���ã���������ȷǵݹ����ͼG��ʹ�ø�������Q�ͷ��ʱ�־����visited
*/ 
void BFSTraverse(MGraph G, Status (*Visit)(int v)){
	
	int u;
	
	//������ȱ���ʹ�õ����� 
	SqQueue Q;
	
	//Ԥ�ñ�־����visited����ֵΪFALSE 
	for(int v = 0; v < G.vexnum; ++v) { 
	    visited[v] = FALSE;
	}//for 
	 
	//��ʼ����������Q���õ�һ���ն��� 
	InitQueue_Sq(Q);
	
	//������ȱ�����ѭ�� 
	for(int v = 0; v < G.vexnum; ++v) {
		
		//v��δ����
		if(!visited[v]){
			
			//����v�Ѿ������� 
			visited[v] = TRUE;
			
			//���ʵ�v����
			Visit(G.vexs[v]);
			
			//v�����
			EnQueue_Sq(Q, v);
			
			//���в��� 
			while(!QueueEmpty_Sq(Q)){
				
				//��ͷԪ�س��Ӳ���Ϊu
				DeQueue_Sq(Q, u);
				
				//���η��ʵ�u������ڽӶ��� 
				for(int w = FirstAdjVex(G, G.vexs[u]); w >= 0;
						w = NextAdjVex(G, G.vexs[u], G.vexs[w])){ 
					
					//wΪv��δ���ʵ��ڽӶ���
				    if(!visited[w]){ 
				    	
				    	//���õ�w�����ѱ����� 
					    visited[w] = TRUE;
						
						//���ʵ�w����
			            Visit(G.vexs[w]); 
					}//if 
				}//for 
			}//while 
		}//if
	}//for 
	
	//����ѭ������ 
	DestoryQueue_Sq(Q);
}//BFSTraverse
