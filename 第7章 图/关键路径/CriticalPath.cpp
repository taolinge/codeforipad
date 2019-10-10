//打印关键路径用到的几个函数 
void printhead(ALGraph G);
void printi(ALGraph G);
void printvex(ALGraph G);
void printve(ALGraph G, int ve[]);
void printvl(ALGraph G, int vl[]);
void printCritical1(ALGraph G, int ve[], int vl[]);

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
	for(int i = 0; i < MAX_VERTEX_NUM; i++) {
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


//事件最早发生时间，全局变量
int ve[MAX_VERTEX_NUM];

/*
	函数：TopologicalOrder
	参数：ALGraph G 图的邻接表存储表示
	      Stack &T 拓扑序列顶点栈  
	返回值：状态码，OK表示操作成功,ERROR表示操作失败 
	作用：有向网G采用邻接表存储结构，求各顶点事件的最早发生时间ve(全局变量)。
	      若G无回路，则用栈T返回G的一个拓扑序列,且函数值为OK,否则为ERROR     
*/
Status TopologicalOrder(ALGraph G, Stack &T) {
	
	//count是已入栈顶点数，初值为0
	int i = 0, k = 0, count = 0;
	
	//入度数组，存放各顶点当前入度数
	int indegree[MAX_VERTEX_NUM];
   
	//S为零入度顶点栈。 
	Stack S;
	
	//指向弧结点的工作指针p 
   	ArcNode *p;
   	
   	//对各顶点求入度并存入数组indegree[]
	FindInDegree(G, indegree);
	
	//初始化零入度顶点栈S
	InitStack(S);
	
	printf("->求得的拓扑序列：");
	
	//对所有顶点i
	for(i = 0; i < G.vexnum; ++i) { 
		
		//若其入度为0,将i压入零入度顶点栈S
		//if(!indegree[i]) <=> if(indegree[i] == 0)
    	if(!indegree[i]) {
    		Push(S, i);
    	}//if
    }//for 
    
    //初始化拓扑序列顶点栈
	InitStack(T);
	
	//初始化ve[]=0(最小值，先假定每个事件都不受其他事件约束)
	for(i = 0; i < G.vexnum; ++i) {
    	ve[i] = 0;
	}//for 
	
	//当零入度顶点栈S不空
	//while(!StackIsEmpty(S)) <=> while(StackIsEmpty(S) == FALSE)
	while(!StackIsEmpty(S)) {
    
    	//从栈S将已拓扑排序的顶点j弹出
		Pop(S, i);
		
		//打印出栈的序号为i的顶点 
    	printf("%d ", G.vertices[i].data);
    	
    	//j号顶点入逆拓扑排序栈T(栈底元素为拓扑排序的第1个元素)
    	Push(T, i);
    	
    	//对入栈T的顶点计数
    	++count;
    	
    	//对i号顶点的每个邻接点
    	for(p = G.vertices[i].firstarc; p; p = p->nextarc) {
       		
			//邻接点序号为k
			k = p->data.adjvex;
			
			//k的入度减1之后变为0，是零入度顶点，则将k入栈S
    		if(--indegree[k] == 0) { 
				Push(S, k);
			}//if
			 
			//顶点k事件的最早发生时间要受其直接前驱顶点i事件的
			//最早发生时间和<i,k>的权值约束。由于i已拓扑有序，故ve[i]不再改变
			//*(p->data.info)是<i,k>的权值
    		if(ve[i] + *(p->data.info) > ve[k]) {
	 			ve[k] = ve[i] + *(p->data.info);
	 		}//if 
    	}//for
	}//while
	
	//拓扑排序结束后若有顶点不在拓扑序列中说明图G存在回路 
	if(count < G.vexnum) {
    	printf("此有向网有回路\n");
    	return ERROR;
	}//if
	else { 
    	return OK;
	}//else
}//TopologicalOrder

/*
	函数：CriticalPath
	参数：ALGraph G 图的邻接表存储表示
	返回值：状态码，OK表示操作成功 
	作用：输出G的各项关键活动   
*/
Status CriticalPath(ALGraph G) {
	
	//事件最迟发生时间
	int vl[MAX_VERTEX_NUM];
	
	Stack T;
   	
	int i, j, k, ee, el, dut;
   	
   	//工作指针p 
   	ArcNode *p;
   	
   	//产生有向环
	if(!TopologicalOrder(G, T)) { 
    	return ERROR;
    }//if
    
    printf("\n->通过拓扑排序，图中没有环！\n");
	
	//j的初值
	j = ve[0]; 
	
	//计算最早发生时间ve[] 
	for(i = 1; i < G.vexnum; i++){
    	
    	//j = Max(ve[]) 完成点的最早发生时间
		if(ve[i] > j) {
    		j = ve[i]; 
    	}//if 
	}//for
   	
   	//初始化顶点事件的最迟发生时间
	for(i = 0; i < G.vexnum; i++) {
		
		//初始化所有顶点事件的最迟发生时间为完成点的最早发生时间(最大值)
    	vl[i] = j; 
	}//for
	
	//按拓扑逆序求各顶点的vl值
	while(!StackIsEmpty(T)) {
		
		//弹出栈T的元素,赋给j,p指向j的后继事件k
    	for(Pop(T, j), p = G.vertices[j].firstarc; p; p = p->nextarc) {
			
			//事件k的最迟发生时间已确定(因为是逆拓扑排序)
    		k = p->data.adjvex;
    		
    		//dut=<j,k>的权值
    		dut = *(p->data.info);
    		
    		//事件j的最迟发生时间要受其直接后继事件k的最迟发生时间
    		//和<j,k>的权值约束。由于k已逆拓扑有序，故vl[k]不再改变
    		if(vl[k] - dut < vl[j]) {
				vl[j] = vl[k] - dut;
			}//if 
    	}//for                    
    }//for
    
    //打印表头
	printhead(G); 
    
    //打印i
	printi(G);
	
	//打印顶点值 
	printvex(G); 
    
    //打印ve
    printve(G, ve);
	
	//打印vl
	printvl(G, vl);
	
	//打印关键路径是否经过此顶点 
	printCritical1(G, ve, vl); 
	
	//求ee，el和关键活动
	printf("\n+------+------+------+------+------+----------+\n");
	printf("|                  活动（边）                 |\n");
	printf("+------+------+------+------+------+----------+\n");
	printf("| 弧尾 | 弧头 | 权值 |  ee  |  el  | 关键活动 |\n");
	printf("+------+------+------+------+------+----------+\n");
	for(j = 0; j < G.vexnum; ++j) {
		
		//p指向j的邻接点k 
    	for(p = G.vertices[j].firstarc; p; p = p->nextarc) {
    		
			k = p->data.adjvex;
			
			//dut=<j,k>的权值
       		dut = *(p->data.info);
       		
       		//ee=活动<j,k>的最早开始时间(在j点)
    		ee = ve[j];
    		
    		//el=活动<j,k>的最迟开始时间(在j点)
    		el = vl[k] - dut;
    		
    		//打印ee和el的值 
    		printf("| %4d | %4d |  %3d |  %3d |  %3d |%s|\n", 
				G.vertices[j].data, G.vertices[k].data, dut, ee, el,
				ee == el ? "    √    " : "          ");
    		
			printf("+------+------+------+------+------+----------+\n");
    	}//for
	}//for
	
	//操作成功 
	return OK;
}//CriticalPath

/*
	函数：printhead
	参数：ALGraph G 图G（邻接表表示） 
	返回值：无
	作用：打印表头 
*/
void printhead(ALGraph G) {
	
	//第一行 
	printf("\n+-----------");
	
	for(int i = 0; i < G.vexnum - 1; i++) {
		
		printf("------");
	}//for 
	
	printf("-----+\n|");
	
	//第二行：字符数：12
	//中间位置：[(10 + 1) + G.vexnum * (5 + 1) - 1 - 12] / 2 
	// <=> (6 * G.vexnum - 2) / 2
	
	int count = 6 * G.vexnum - 2;
	
	for(int i = 0; i < count / 2 ; i++) {
		
		printf(" ");
	}//for 
	
	printf("顶点（事件）");
	
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
	函数：printi
	参数：ALGraph G 图G（邻接表表示）
	返回值：无
	作用：以表格形式打印i  
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
	函数：printvex
	参数：ALGraph G 图G（邻接表表示）
	返回值：无
	作用：以表格形式打印顶点名称  
*/
void printvex(ALGraph G) {
	
	printf("|   顶点   |"); 
	
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
	函数：printve
	参数：ALGraph G 图G（邻接表表示）
		  int ve[] 事件的最早发生时间ve[] 
	返回值：无
	作用：以表格形式打印ve名称  
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
	函数：printvl
	参数：ALGraph G 图G（邻接表表示）
		  int vl[] 事件的最晚发生时间vl[] 
	返回值：无
	作用：以表格形式打印ve名称  
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
	函数：printCritical1
	参数：ALGraph G 图G（邻接表表示）
	      int ve[] 事件的最早发生时间ve[] 
		  int vl[] 事件的最晚发生时间vl[] 
	返回值：无
	作用：以表格形式打印顶点是否在关键路径上 
*/
void printCritical1(ALGraph G, int ve[], int vl[]) {
	
	printf("| 关键路径 |"); 
	
	for(int i = 0; i < G.vexnum; i++) {
		
		//在关键路径上的顶点加√标记 
		if(ve[i] == vl[i]) { 
    		printf("  √ |");
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
