//------------------------元素访问函数----------------------

/*
	函数：print
	参数：VertexType v 顶点v 
	返回值：无
	作用：元素访问函数，供遍历使用。 
*/
void print(VertexType v) {
	
	printf(" %d ", v);
		
}//print 


//------------------------深度优先遍历---------------------- 

//访问标志数组(长度等于最大顶点数)
int visited[MAX_VERTEX_NUM];

//访问函数(通过全局变量的方式传递可以减少参数传递的次数)
void(*VisitFunc)(VertexType v);

/*
	函数：DFS
	参数：ALGraph G 图G 
	      int v 访问图G中的第v个顶点 
	返回值：无
	作用：从第v个顶点出发递归地深度优先遍历图G。
*/
void DFS(ALGraph G, int v) { 
	
	//w是临时变量，循环控制用 
	int w;
	
	//设置访问标志为TRUE，表示该顶点已访问
	visited[v] = TRUE;
	
	//访问第v个顶点
	VisitFunc(G.vertices[v].data);
	
	//依次访问v的未被访问的邻接点 
   	for(w = FirstAdjVex(G, G.vertices[v].data); w >= 0; 
	   	w = NextAdjVex(G, G.vertices[v].data, G.vertices[w].data)) { 
    	
    	//对v的尚未访问的邻接点w递归调用深度优先遍历算法DFS
		if(!visited[w]) { 
    		DFS(G, w);
    	}//if
	}//for
}//DFS

/*
	函数：DFS
	参数：ALGraph G 图G 
	      void(*Visit)(char*) 指向遍历函数的指针 
	返回值：无
	作用：对图G作深度优先遍历。
*/
void DFSTraverse(ALGraph G, void(*Visit)(VertexType)) {

	//使用全局变量VisitFunc，使DFS不必设函数指针参数
	VisitFunc = Visit;
	
	//初始化访问标志数组每个顶点的标志值为FALSE，表示所有顶点都未被访问 
	for(int v = 0; v < G.vexnum; v++) {
    	visited[v] = FALSE;
	}//for
	
	//依次访问图中每个顶点 
	for(int v = 0; v < G.vexnum; v++) { 
    	
    	//对尚未访问的顶点调用DFS
		if(!visited[v]) { 
    		DFS(G, v);
    	}//if
	}//for
	
	//遍历完成后换行，使输出美观 
	printf("\n");
}//DFSTraverse

//------------------------广度优先遍历----------------------- 

/*
	函数：BFSTraverse
	参数：ALGraph G 图G 
	      void(*Visit)(char*) 指向遍历函数的指针 
	返回值：无
	作用：按广度优先非递归遍历图G。使用辅助队列Q和访问标志数组visited。
*/
void BFSTraverse(ALGraph G, void(*Visit)(VertexType)) {
	
	//v是临时变量 
	int v, u, w;
	
	//声明队列 
	Queue Q;
	
	//设置结点访问标记数组的初始值为FALSE，表示没有顶点被访问过 
	for(v = 0; v < G.vexnum; ++v) { 
    	visited[v] = FALSE;
    }//for
    
    //初始化辅助队列Q，得到一个空队列 
	InitQueue(Q);
	
	//如果是连通图，只要一次循环就可以遍历全部顶点 
	for(v = 0; v < G.vexnum; v++) { 
    	
    	//v尚未访问
		if(!visited[v]) {
			
			//设置顶点v的标志为TRUE，表示顶点v已被访问 
			visited[v] = TRUE;
			
			//调用访问函数Visit访问顶点v 
       		Visit(G.vertices[v].data);
    		
    		//v入队列
			EnQueue(Q, v);
       
       		//队列不空
	   		while(!QueueEmpty(Q)) {
        		
        		//队头元素出队并置为u
				DeQueue(Q, u);
				
				//访问u尚未访问的邻接顶点 
         		for(w = FirstAdjVex(G, G.vertices[u].data); w >= 0; 
				 	w = NextAdjVex(G, G.vertices[u].data, G.vertices[w].data)) { 
           			
           			//w为u的尚未访问的邻接顶点
					if(!visited[w]) {
						
						//设置顶点w的访问标志为TRUE 
						visited[w] = TRUE;
						
						//访问顶点w 
             			Visit(G.vertices[w].data);
             			
             			//顶点w入队 
             			EnQueue(Q, w);
	   				}//if
       			}//for 
     		}//while
		}//if 
	}//for 
	
	//遍历结束 
	printf("\n");
}//BFSTraverse 
