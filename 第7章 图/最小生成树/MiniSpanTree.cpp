//-------------- 最小生成树 ----------------------------

//-------------------辅助数组的定义------------------------------- 
struct Record{
	VertexType adjvex;   //顶点 
	VRType     lowcost;  //最低代价 
}closedge[MAX_VERTEX_NUM];

/*
	函数：printColsedge
	参数：Record closedge[] 计算最小生成树的辅助数组closedge 
	      int n 顶点数 
	返回值：无 
	作用：打印closedge数组 
*/
void printColsedge(Record closedge[], MGraph G) {
	
	//打印i一行 
	
	printf("+----------+");
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("-----+");
	}//for 
	
	printf("\n"); 
	
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
	
	//顶点值 
	printf("|   顶点   |"); 
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("  %2d |", G.vexs[i]);
	}//for 
	
	printf("\n"); 
	
	printf("+----------+");
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("-----+");
	}//for 
	
	printf("\n"); 
	
	//打印adjvex一行 
	
	printf("|  adjvex  |"); 
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf(" %3d |", closedge[i].adjvex);
	}//for 
	
	printf("\n"); 
	
	printf("+----------+");
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("-----+");
	}//for 
	
	printf("\n"); 
	
	//打印lowcost一行 
	
	printf("|  lowcost |"); 
	
	for(int i = 0; i < G.vexnum; i++) {
		
		if(closedge[i].lowcost != INFINITY) {
			printf(" %3d |", closedge[i].lowcost);
		}//if
		else {
			printf("  ∞ |"); 
		}//else 
		
	}//for 
	
	printf("\n"); 
	
	printf("+----------+");
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("-----+");
	}//for 
	
	printf("\n"); 
		
}//printColsedge

/*
	函数：minimum
	参数：Record closedge[] 计算最小生成树的辅助数组closedge 
	返回值：选出顶点的序号 
	作用：从closedge数组中选出符合条件的最小生成树的下一顶点 
*/
int minimum(Record closedge[]){
	
	//min是从closedge数组中选出的最小代价边的另一个顶点在图中的位置
	//reserve是辅助参与比较的最小代价，初始值为65535，
	//每一次发现代价比它更小的边则reserve会被更新为新的最小代价 
	int reserve = 65535, min = 0;
	
	for(int i = 1; i < MAX_VERTEX_NUM; i++) {
		
		//没有访问过但是存在路径并且代价更小（比记录最小代价的reserve还小） 
		if(closedge[i].lowcost < reserve && closedge[i].lowcost > 0){
			
			printf("->发现比reserve = %d更小的权值：closedge[%d].lowcost = %d ！\n",
						reserve, i, closedge[i].lowcost);
			
			//reserve更新为新的最小代价 
			reserve = closedge[i].lowcost;
			
			//min更新为最小代价边的另一顶点在图中的位置 
			min = i;
		}//if
	}//for
	 
	return min;
}//minimum

/* （普里姆算法求最小生成树） 
	函数：MiniSpanTree_PRIM
	参数：MGraph G 图G 
	返回值：无 
	作用：用普里姆算法从第u个顶点出发构造网G的最小生成树T，输出T的各条边
	      记录从定点集U到V-U的代价最小的边的辅助数组定义
*/
void MiniSpanTree_PRIM(MGraph G, VertexType u){
	
	//k是出发顶点u在图中的序号 
	int k = LocateVex(G, u);
	
	//辅助数组初始化
	for(int j = 0; j < G.vexnum; ++j) {  
	    
	    //j指示的顶点不是出发顶点 
		if(j != k){
	    	//{adjvex, lowcost}
	    	//设置邻接点为起始顶点u 
	    	closedge[j].adjvex = u;
	    	
	    	//设置closedge数组初始最小代价，其实就是
			//直接拷贝第G.arcs二维数组的第k行 
	    	closedge[j].lowcost = G.arcs[k][j].adj;
	    }//if
	}//for
	
	//设置出发点u的最小代价为0，此时U={u}  
	closedge[k].lowcost = 0;
	
	printf("\n->最小生成树从顶点%d开始，所以该顶点此时已被加入最小生成树顶点集合！\n\n", G.vexs[k]);
	
	//从顶点u开始生成最小生成树 
	for(int i = 1; i < G.vexnum; ++i) {
		
		printf("\n->这是第%d趟循环：\n" , i);
		
		printf("->更新closedge数组之前，closedge数组的值(adjvex是顶点序号，不是顶点名称，lowcost = 0表示该顶点已被纳入最小生成树的顶点集合)：\n");
	
		//打印closedge数组 
		printColsedge(closedge, G); 
		
		printf("->开始求最小生成树的下一顶点：\n"); 
		
		//求出最小生成树的下一个结点：第k顶点
		//此时closedge[k].lowcost= MIN{ closedge[vi].lowcost 
		//  	| closedge[vi].lowcost > 0, vi ∈V-U} 
		k = minimum(closedge);
		
		printf("->求得最小生成树的下一顶点为：%d，下一顶点序号k = %d, 最小代价为：%d\n", G.vexs[k], k, closedge[k].lowcost);
		
		//输出生成树的边及其权值
		printf("\n->得到最小生成树的一条新边： %2d <--- %2d ---> %2d \n\n", closedge[k].adjvex, 
			closedge[k].lowcost, G.vexs[k]);
		
		//第k顶点并入U集
		closedge[k].lowcost = 0;
		
		//查找k的邻接顶点中代价更小的边对应的邻接顶点 
		//将新顶点并入U后重新选择最小边
		//选出一个顶点k之后需要更新closedge数组中最小边信息
		for(int j = 1; j < G.vexnum; ++j) { 
			
			//发现代价更小的边就更新closedge数组
			//若没有发现则保持原值不变 
		    if(G.arcs[k][j].adj < closedge[j].lowcost){
		    	
		    	printf("从%d的所有邻接顶点中发现有G.arcs[%d][%d].adj = %d 比 closedge[%d].lowcost = %d 更小，更新closedge数组！\n",
						G.vexs[k], k, j, G.arcs[k][j].adj, j, closedge[j].lowcost); 
		    	
		    	//更新closedge数组的邻接点信息adjvex 
			    closedge[j].adjvex = G.vexs[k];
			    
			    //更新closedge数组的最小边信息lowcost 
				closedge[j].lowcost = G.arcs[k][j].adj; 
		    }//if
		}//for 
		
		printf("\n->更新closedge数组之后，closedge数组的值(adjvex是顶点序号，不是顶点名称，lowcost = 0表示该顶点已被纳入最小生成树的顶点集合)：\n");
	
		//打印closedge数组 
		printColsedge(closedge, G); 
		
		system("pause");
	}//for 	  
}//MiniSpanTree_PRIM 


/*
	函数：printSet
	参数：int set[] 保存顶点所属集合状态的数组set 
	      MGraph G 图G 
	返回值：无 
	作用：打印set数组 
*/
void printSet(int set[], MGraph G) {
	
	//打印i一行 
	
	printf("+----------+");
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("-----+");
	}//for 
	
	printf("\n"); 
	
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
	
	//顶点值 
	printf("|   顶点   |"); 
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("  %2d |", G.vexs[i]);
	}//for 
	
	printf("\n"); 
	
	printf("+----------+");
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("-----+");
	}//for 
	
	printf("\n"); 
	
	//打印set一行 
	
	printf("|    set   |"); 
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf(" %3d |", set[i]);
	}//for 
	
	printf("\n"); 
	
	printf("+----------+");
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("-----+");
	}//for 
	
	printf("\n"); 
		
}//printSet

/* （克鲁斯卡尔算法求最小生成树） 
	函数：MiniSpanTree_kruskal
	参数：MGraph G 图G 
	返回值：无 
	作用：克鲁斯卡尔算法求最小生成树 
*/
void MiniSpanTree_kruskal(MGraph G) {
	
	int set[MAX_VERTEX_NUM];
	int k = 0, a = 0, b = 0, setb, min = G.arcs[a][b].adj;
	
	//set[]初态，各顶点分别属于各个集合
	for(int i = 0; i < G.vexnum; i++) {
    	set[i] = i; 
	}//for
	
	printf("->set数组初始状态（各顶点分别属于各个集合）：\n");
	printSet(set, G);
	 
	printf("最小代价生成树的各条边及权值为:\n");
	//最小生成树的边数应该有n-1条边，其中n为顶点数 
	while(k < G.vexnum-1) {
		
		printf("\n->这是第%d趟循环，寻找更小权值的边：\n", k + 1);
		
		//寻找最小权值的边
    	for(int i = 0; i < G.vexnum; ++i) { 
    		
    		//无向网，只在上三角查找
    		for(int j = i + 1; j < G.vexnum; ++j) {
				
				//发现比min更小的权值 
				if(G.arcs[i][j].adj < min) {
					
					printf("->发现比min = %d 更小的权值：%d，修改min为该值！\n", min, G.arcs[i][j].adj);
					
					//最小权值
					min = G.arcs[i][j].adj; 
					
					//边的一个顶点
					a = i;
					
					//边的另一个顶点
					b = j;
				}//if
			}//for
		}//for
		
		//边的两顶点不属于同一集合
    	if(set[a] != set[b]) {
    		
    		//输出该边
			printf("->找到一条最小生成树的新边：%d <-- %d --> %d\n", G.vexs[a], G.arcs[a][b].adj, G.vexs[b]);
    	}//if 
    	
    	//重置min为极大值 
		min = G.arcs[a][b].adj = INFINITY;
		
		//边的两顶点不属于同一集合
    	if(set[a] != set[b]) {
    		
    		//边数+1
			k++;
			
			//保存setb的值
			setb = set[b];
			
			//将顶点b所在集合并入顶点a集合中
       		for(int i = 0; i < G.vexnum; i++) {
       			
       			//不可以直接set[i] == set[b]作为比较条件，因为i可能等于b！ 
				//一旦set[b]被修改，那么set[b]后面的元素将无法正确合并  
        		if(set[i] == setb) {
        			printf("->合并顶点%d到顶点%d的集合中，注意set数组的变化。\n", G.vexs[i], G.vexs[a]);
        			set[i] = set[a];
        		}//if
        	}//for 
        	
        	printf("->set数组修改后的值：\n");                                                
			printSet(set, G);
     	}//if 
	}//while
	
	printf("->set数组初最终状态(无向连通网所有顶点应该都在一个集合里)：\n");
	printSet(set, G);
}//MiniSpanTree_kruskal
