
/*
	函数：FindInDegree
	参数：ALGraph G 图G（邻接表存储结构） 
	      int indegree[] 存储顶点入度的数组 
	返回值：无
	作用：求顶点的入度
*/
void FindInDegree(ALGraph G, int indegree[]) {
	
	//工作指针p 
	ArcNode *p;
	
	//对存储入度的indegree数组赋初值0
	for(int i = 0; i < G.vexnum; i++) {
    	indegree[i] = 0; 
	}//for
	
	//扫描每个顶点后面的弧链表 
	for(int i = 0; i < G.vexnum; i++) {
		
		//p指向顶点i后面弧链表的首元结点 
    	p = G.vertices[i].firstarc;
    	
    	//顶点v的弧链表没有扫描完毕 
    	while(p) { //while(p) <=> while(p != NULL) 
    		//每找到一个弧结点，对应邻接点的入度+1 
    		indegree[p->data.adjvex]++;
    		
    		//p指向下一个弧结点 
    		p = p->nextarc;
    	}//while 
	}//for
}//FindInDegree

/*
	函数：TopologicalSort
	参数：ALGraph G 有向图G（邻接表存储结构） 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：若G无回路，则输出G的顶点的一个拓扑序列并返回OK，
	      否则返回ERROR。
*/
Status TopologicalSort(ALGraph G) {
	
	//count为已输出顶点数，初值为0
	int i, k, count = 0;
	
	//入度数组，存放各顶点当前入度数
	int indegree[MAX_VERTEX_NUM];
	
	//声明栈S 
	Stack S;
	
	//工作指针p,指向弧结点 
	ArcNode *p; 
	
	//对各顶点求入度并存入数组indegree[]
	FindInDegree(G, indegree);
	
	//初始化零入度顶点栈S
	InitStack(S);
	
	//扫描所有顶点
	for(i = 0; i < G.vexnum; ++i) {
    	
    	//若其入度为0，则将i压入零入度顶点栈S
    	//if(!indegree[i]) <=> if(indegree[i] == 0) 
		if(!indegree[i]) { 
    		Push(S, i); 
    	}//if
    }//for
		 
	//当零入度顶点栈S不空
	//while(!StackIsEmpty(S)) <=> while(StackIsEmpty(S) == FALSE)
	while(!StackIsEmpty(S)) {
		
		//从栈中弹出一个零入度顶点的序号，并将其保存到i
		Pop(S, i);
		
		//输出i号顶点
		printf(" %d ", G.vertices[i].data);
		
		//已输出顶点数+1
		++count;
		
		//扫描i号顶点的每个邻接顶点
		for(p = G.vertices[i].firstarc; p; p = p->nextarc) { 
			
			//i号顶点的邻接点序号为k
			k = p->data.adjvex;
			
			//k的入度减1，若减为0，则将k入栈S
			//if(!(--indegree[k])) <=> if((--indegree[k]) == 0)
			if(!(--indegree[k])) { 
				Push(S, k);
			}//if
		}//for
	}//while
 	
 	
 	//零入度顶点栈S已空，图G还有顶点未输出
	if(count < G.vexnum) {
		printf("此有向图有回路\n");
		return ERROR;
	}//if
	else {
		return OK;
	}//else 
}//TopologicalSort
