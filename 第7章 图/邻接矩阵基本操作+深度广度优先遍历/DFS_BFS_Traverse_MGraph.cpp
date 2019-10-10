//-----------------------深度优先遍历DFS-----------------------------

//访问标志数组 
int visited[MAX_VERTEX_NUM];

//函数变量 
Status (*VisitFunc)(int v);

/*
	函数：Print
	参数：int v 被访问的顶点v 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：元素访问函数
*/
Status Print(int v){
	
	//设置元素访问方式为控制台打印 
	printf(" %3d ", v);
	
	//操作成功 
	return OK;
}//Print

/*
	函数：DFSTraverse
	参数：MGraph G 图G
	      int v 从序号为v的顶点出发 
	返回值：无
	作用：从第v个顶点出发递归地深度优先遍历图G
*/
void DFS(MGraph G, int v){
    
    //先将访问标志数组该元素的访问标志改为True，
	//含义是序号为v的顶点已被访问 
	visited[v] = TRUE;
	
	//访问第v个顶点
	VisitFunc(G.vexs[v]);
	
	//依次访问v的各个邻接顶点（向v的邻接点延伸） 
	for(int w = FirstAdjVex(G, G.vexs[v]); w >= 0; 
			w = NextAdjVex(G, G.vexs[v], G.vexs[w])){
		
		//对v的尚未被访问的邻接点w递归调用DFS 
		if(!visited[w]) { 
		    DFS(G, w);
		}//if 
	}//for
}//DFS

/*
	函数：DFSTraverse
	参数：MGraph G 图G
	      Status (*Visit)(int v) 函数指针，指向元素访问函数 
	返回值：无
	作用：对图G作深度优先遍历,调用Visit()函数访问结点
*/
void DFSTraverse(MGraph G, Status (*Visit)(int v)){
	
	//使用全局变量VisitFunc，使DFS不必设函数指针参数 
	VisitFunc = Visit;
	
	//预置标志数组visited所有值为FALSE 
	for(int v = 0; v < G.vexnum; ++v) { 
	    visited[v] = FALSE;
	}//for
	
	//深度优先遍历主循环 
	//写成循环是为了保证在图分为多个连通分量时能对
	//每个连通分量进行遍历 
	for(int v = 0; v < G.vexnum; ++v) {
		
		//若该顶点未被访问，则调用DFS()访问该节点
		if(!visited[v]) {
	    	DFS(G, v); 
		}//if
	}//for 
}//DFSTraverse

//----------------广度优先遍历 (需要使用队列)BFS------------ 
//说明：队列的相关代码包含在"SqQueue.cpp"中，关于队列的详细方法请阅读该文件

/*
	函数：BFSTraverse
	参数：MGraph G 图G
	      Status (*Visit)(int v) 函数指针，指向元素访问函数 
	返回值：无
	作用：按广度优先非递归遍历图G，使用辅助队列Q和访问标志数组visited
*/ 
void BFSTraverse(MGraph G, Status (*Visit)(int v)){
	
	int u;
	
	//广度优先遍历使用到遍历 
	SqQueue Q;
	
	//预置标志数组visited所有值为FALSE 
	for(int v = 0; v < G.vexnum; ++v) { 
	    visited[v] = FALSE;
	}//for 
	 
	//初始化辅助队列Q，得到一个空队列 
	InitQueue_Sq(Q);
	
	//广度优先遍历主循环 
	for(int v = 0; v < G.vexnum; ++v) {
		
		//v尚未访问
		if(!visited[v]){
			
			//设置v已经被访问 
			visited[v] = TRUE;
			
			//访问第v顶点
			Visit(G.vexs[v]);
			
			//v入队列
			EnQueue_Sq(Q, v);
			
			//队列不空 
			while(!QueueEmpty_Sq(Q)){
				
				//队头元素出队并置为u
				DeQueue_Sq(Q, u);
				
				//依次访问第u顶点的邻接顶点 
				for(int w = FirstAdjVex(G, G.vexs[u]); w >= 0;
						w = NextAdjVex(G, G.vexs[u], G.vexs[w])){ 
					
					//w为v尚未访问的邻接顶点
				    if(!visited[w]){ 
				    	
				    	//设置第w顶点已被访问 
					    visited[w] = TRUE;
						
						//访问第w顶点
			            Visit(G.vexs[w]); 
					}//if 
				}//for 
			}//while 
		}//if
	}//for 
	
	//销毁循环队列 
	DestoryQueue_Sq(Q);
}//BFSTraverse
