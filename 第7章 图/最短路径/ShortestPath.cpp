//--------------- ���·�� ------------------- 

//---------------------------�Ͻ�˹�����㷨��������Ķ���--------------------------------

//P[][]��¼��v->v0�����·��������Щ·����
//��P[i][j] = TRUE��˵��i->j����һ���������·����
//��P[i][j] = FALSE��˵��i->j�������·���� 
typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

//D[]��¼��v0�������������̾��� 
typedef int ShortPathTable[MAX_VERTEX_NUM];

/* ����˹�����㷨��Դ���·���� 
	������ShortestPath_DIJ
	������MGraph G ͼG 
	      int v0 ������v0
		  PathMatrix &P ��¼���·��������Щ·����P����
		  ShortPathTable &D ��¼v0�������������̾����D���� 
	����ֵ�� �� 
	���ã���Dijkstra�㷨������ͼG�Ķ���v0���㵽���ඥ��v�����·��P[v]�����Ȩ����D[v]
	      ��P[v][w]ΪTRUE����w�Ǵ�v0��v��ǰ�����С·���ϵĶ���
	      final[v]ΪTRUE���ҽ���v��S�����Ѿ����v0��v�����·��
*/
void ShortestPath_DIJ(MGraph G, int v0, PathMatrix &P, ShortPathTable &D){  //
	
	//��ʱ���� 
	int v, w, j, min;
	
	//final����������Ǽ�¼���������Ƿ��Ѿ��ҵ����·�� 
	Status final[MAX_VERTEX_NUM];
	
	//��ʼ������ 
	for(v = 0; v < G.vexnum; ++v) {
		
		//final�����е�ֵΪFALSE��ʾ��δ������·�� 
		final[v] = FALSE;
		
		//����v���ڵĶ������Ȩֵ 
		D[v] = G.arcs[v0][v].adj;
		
		//��P����ĳ�ʼֵΪû��·��
		for(w = 0; w < G.vexnum; ++w) {
		    P[v][w] = FALSE;
		}//for
		
		//D������Ȩֵ��P�����Ӧλ�ô���·�� 
		//Ҳ����v��v0֮�����·�� 
		if(D[v] < INFINITY){
			
			//����v0 
			P[v][v0] = TRUE;
			
			//����v 
			P[v][v] = TRUE;
		}//if
	}//for
	
	//v0->v0�ľ�����0 
	D[v0] = 0;
	
	//v0���㲢��S�� 
	final[v0] = TRUE;
	
	//��ʼ��ѭ����ÿ�����v0��ĳ������v�����·��������v��S�� 
	for(int i = 0; i < G.vexnum; ++i){   //����G.vexnum-1������ 
		
		//��ǰ��֪��v0����������룬���ó�ʼֵ�� 
		min = INFINITY;
		
		//ɨ�����ж��� 
		for(int w = 0; w < G.vexnum; ++w) {
			
			//w����û�в��뼯��S�� 
			if(!final[w]) {
				
				//w������v0������� 
			    if(D[w] < min){
			    	
			    	//v��¼����v0����Ķ��� 
			    	v = w;
			    	
			    	//min��¼�˵�v0�����·�� 
			    	min = D[w];
			    }//if 
			}//if 
		}//for 
		
		//��v0���������v����S��
		final[v] = TRUE;
		
		//���µ�ǰ���·��������
		//�����²���Ķ��㣬���²���S���Ķ��㵽V0�ľ����·������ 
		for(int w = 0; w < G.vexnum; ++w) {
			
			//�޸�D[w]��P[w]��w��V-S 
			if(!final[w] && (min + G.arcs[v][w].adj < D[w])){
				
				//����D[w] 
		   		D[w] = min + G.arcs[v][w].adj;
		   		
		   		//�޸�P[w]��v0��w�����Ķ������v0��v�����Ķ����ټ��϶���w 
		   		//P[w] = P[v] + [w]
				for(int j = 0; j < G.vexnum; ++j) {
		   	    	P[w][j] = P[v][j];
				}//for
				
				//���·������w�� 
		   		P[w][w] = TRUE;    
			}//if
		}//for 
	}//for	
}//ShortestPath_DIJ

//---------------------���������㷨��������Ķ���------------------------

//P[][][]��¼�����·����������Щ·�� 
typedef int PathMatrix1[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];

//D[][]��¼�˸�����֮�����·����ֵ 
typedef int DistanceMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

/* �����������㷨�������֮������·���� 
	������ShortestPath_FLOYD
	������MGraph G ͼG
	      PathMatrix1 &P ��¼���·��������Щ·����P����
	      DistanceMatrix &D ��¼�˸�����֮�����·��ֵ��D���� 
	����ֵ�� �� 
	���ã���Floyd�㷨��������G�и��Զ���v��w֮������·��P[v][w]�����Ȩ����D[v][w]��
	      ��P[v][w][u]ΪTRUE����u�Ǵ�v��w��ǰ������·���ϵĶ��㡣
*/
void ShortestPath_FLOYD(MGraph G, PathMatrix1 &P, DistanceMatrix &D){
	
	//���Խ��֮��ĳ�ʼ��֪·��������
	for(int v = 0; v < G.vexnum; ++v) {      
		for(int w = 0; w < G.vexnum; ++w){
			
			//����v������w��ֱ�Ӿ��� 
	   		D[v][w] = G.arcs[v][w].adj;
	   		
	   		//·������ĳ�ֵΪFALSE 
	   		for(int u = 0; u < G.vexnum; ++u) {
	   	    	P[v][w][u] = FALSE;
			}//for
			 
			//��v��w��ֱ��·�� 
	   		if(D[v][w]<INFINITY){
	   			
	   			//��v��w��·������v��w���� 
	   	   		P[v][w][v] = TRUE;
				P[v][w][w] = TRUE; 
	   		}//if 
		}//for
	}//for 
	
	//��v��u��w��һ��·������ 
	for(int u = 0; u < G.vexnum; ++u) {
		for(int v = 0; v < G.vexnum; ++v) {
	    	for(int w = 0; w < G.vexnum; ++w) {
	    		
	    		//��v��u��w��һ��·������ 
	      		if(D[v][u] + D[u][w] < D[v][w]){ 
				  	
					//������̾��� 
	      			D[v][w] = D[v][u] + D[u][w];
					
					//��v��w��·��������v��u�ʹ�u��w������·�� 
					for(int i = 0; i < G.vexnum; ++i) {
						P[v][w][i] = P[v][u][i] || P[u][w][i];
					}//for 
				}//if
			}//for
		}//for 
	}//for
}//ShortestPath_FLOYD
