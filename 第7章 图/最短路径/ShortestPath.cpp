//--------------- 最短路径 ------------------- 

//---------------------------迪杰斯特拉算法辅助数组的定义--------------------------------

//P[][]记录了v->v0的最短路径经过哪些路径，
//当P[i][j] = TRUE，说明i->j这样一条边在最短路径上
//当P[i][j] = FALSE，说明i->j不在最短路径上 
typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

//D[]记录了v0到各个顶点的最短距离 
typedef int ShortPathTable[MAX_VERTEX_NUM];

/* （迪斯特拉算法求单源最短路径） 
	函数：ShortestPath_DIJ
	参数：MGraph G 图G 
	      int v0 出发点v0
		  PathMatrix &P 记录最短路径经过哪些路径的P数组
		  ShortPathTable &D 记录v0到各个顶点的最短距离的D数组 
	返回值： 无 
	作用：用Dijkstra算法求有向图G的顶点v0顶点到其余顶点v的最短路径P[v]及其带权长度D[v]
	      若P[v][w]为TRUE，则w是从v0到v当前求得最小路径上的顶点
	      final[v]为TRUE当且仅当v∈S，即已经求得v0到v的最短路径
*/
void ShortestPath_DIJ(MGraph G, int v0, PathMatrix &P, ShortPathTable &D){  //
	
	//临时变量 
	int v, w, j, min;
	
	//final数组的作用是记录各个顶点是否已经找到最短路径 
	Status final[MAX_VERTEX_NUM];
	
	//初始化数据 
	for(v = 0; v < G.vexnum; ++v) {
		
		//final数组中的值为FALSE表示还未求得最短路径 
		final[v] = FALSE;
		
		//将与v相邻的顶点加上权值 
		D[v] = G.arcs[v0][v].adj;
		
		//设P数组的初始值为没有路径
		for(w = 0; w < G.vexnum; ++w) {
		    P[v][w] = FALSE;
		}//for
		
		//D数组有权值即P数组对应位置存在路径 
		//也就是v和v0之间存在路径 
		if(D[v] < INFINITY){
			
			//经过v0 
			P[v][v0] = TRUE;
			
			//经过v 
			P[v][v] = TRUE;
		}//if
	}//for
	
	//v0->v0的距离是0 
	D[v0] = 0;
	
	//v0顶点并入S集 
	final[v0] = TRUE;
	
	//开始主循环，每次求得v0到某个顶点v的最短路径，并加v到S集 
	for(int i = 0; i < G.vexnum; ++i){   //其余G.vexnum-1个顶点 
		
		//当前所知离v0顶点最近距离，设置初始值∞ 
		min = INFINITY;
		
		//扫描所有顶点 
		for(int w = 0; w < G.vexnum; ++w) {
			
			//w顶点没有并入集合S中 
			if(!final[w]) {
				
				//w顶点离v0顶点更近 
			    if(D[w] < min){
			    	
			    	//v记录了离v0最近的顶点 
			    	v = w;
			    	
			    	//min记录了到v0的最短路径 
			    	min = D[w];
			    }//if 
			}//if 
		}//for 
		
		//离v0顶点最近的v加入S集
		final[v] = TRUE;
		
		//更新当前最短路径及距离
		//根据新并入的顶点，更新不在S集的顶点到V0的距离和路径数组 
		for(int w = 0; w < G.vexnum; ++w) {
			
			//修改D[w]和P[w]，w∈V-S 
			if(!final[w] && (min + G.arcs[v][w].adj < D[w])){
				
				//更新D[w] 
		   		D[w] = min + G.arcs[v][w].adj;
		   		
		   		//修改P[w]，v0到w经过的顶点包括v0到v经过的顶点再加上顶点w 
		   		//P[w] = P[v] + [w]
				for(int j = 0; j < G.vexnum; ++j) {
		   	    	P[w][j] = P[v][j];
				}//for
				
				//最短路径经过w点 
		   		P[w][w] = TRUE;    
			}//if
		}//for 
	}//for	
}//ShortestPath_DIJ

//---------------------弗洛伊德算法辅助数组的定义------------------------

//P[][][]记录了最短路径经过了哪些路径 
typedef int PathMatrix1[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];

//D[][]记录了各顶点之间最短路径的值 
typedef int DistanceMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

/* （弗洛伊德算法求各顶点之间的最短路径） 
	函数：ShortestPath_FLOYD
	参数：MGraph G 图G
	      PathMatrix1 &P 记录最短路径经过哪些路径的P数组
	      DistanceMatrix &D 记录了各顶点之间最短路径值的D数组 
	返回值： 无 
	作用：用Floyd算法求有向网G中各对顶点v和w之间的最短路径P[v][w]及其带权长度D[v][w]。
	      若P[v][w][u]为TRUE，则u是从v到w当前求得最短路径上的顶点。
*/
void ShortestPath_FLOYD(MGraph G, PathMatrix1 &P, DistanceMatrix &D){
	
	//各对结点之间的初始已知路径及距离
	for(int v = 0; v < G.vexnum; ++v) {      
		for(int w = 0; w < G.vexnum; ++w){
			
			//顶点v到顶点w的直接距离 
	   		D[v][w] = G.arcs[v][w].adj;
	   		
	   		//路径矩阵的初值为FALSE 
	   		for(int u = 0; u < G.vexnum; ++u) {
	   	    	P[v][w][u] = FALSE;
			}//for
			 
			//从v到w有直接路径 
	   		if(D[v][w]<INFINITY){
	   			
	   			//从v到w的路径经过v和w两点 
	   	   		P[v][w][v] = TRUE;
				P[v][w][w] = TRUE; 
	   		}//if 
		}//for
	}//for 
	
	//从v经u到w的一条路径更短 
	for(int u = 0; u < G.vexnum; ++u) {
		for(int v = 0; v < G.vexnum; ++v) {
	    	for(int w = 0; w < G.vexnum; ++w) {
	    		
	    		//从v经u到w的一条路径更短 
	      		if(D[v][u] + D[u][w] < D[v][w]){ 
				  	
					//更新最短距离 
	      			D[v][w] = D[v][u] + D[u][w];
					
					//从v到w的路径经过从v到u和从u到w的所有路径 
					for(int i = 0; i < G.vexnum; ++i) {
						P[v][w][i] = P[v][u][i] || P[u][w][i];
					}//for 
				}//if
			}//for
		}//for 
	}//for
}//ShortestPath_FLOYD
