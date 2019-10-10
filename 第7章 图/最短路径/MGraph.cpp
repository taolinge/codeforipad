/*
ADT Graph {
	
	数据对象V：V是具有相同特性的数据元素的集合，称为顶点集。
	数据关系R：
			R = {VR}
			VR = {<v,w>| v,w∈V 且 P(v,w), <v,w>表示从 v 到 w 的弧。
 						谓词 P(v,w) 定义了弧 <v,w>的意义或信息。}
 	基本操作P:
 		CreatGraph(&G, V, VR);
 		//初始条件：V是图的顶点集，VR是图中弧的集合。 
		//操作结果：按V和VR的定义构造图G。 
		
		DestroyGraph(&G);
		//初始条件：图G存在。 
		//操作结果：销毁图G。 
		
		LocateVex(G, u);
		//初始条件：图G存在，u和G中顶点有共同特征 
		//操作结果：若G中存在顶点u，则返回该顶点在图中位置；否则返回其它信息。

		GetVex(G, v);
		//初始条件：图G存在，v是G中某个顶点。 
		//操作结果：返回v的值。
		
		PutVex(&G, v, value);
		//初始条件：图G存在，v是G中某个顶点。 
		//操作结果：对v赋值value。
		
		FirstAdjVex(G, v); 
		//初始条件：若图G存在，v是G中的某个顶点。 
		//操作结果：返回v的第一个邻接点。若该顶点在G中没有邻接点，则返回空。

		NextAdjVex(G, v, w);
		//初始条件：图G存在， v是G中的某个顶点，w是v的邻接顶点。 
		//操作结果：返回v的（相对于w的）下一个邻接点。
		            若w是v的最后一个邻接点，则返回空。

		InsertVex(&G, v); 
		//初始条件：图G存在，v和图中的顶点有相同特征。 
		//操作结果：在图G中增添新顶点v。

		DeleteVex(&G, v);
		//初始条件：图G存在，v和w是G中的两个顶点 
		//操作结果：删除G中顶点v及其相关的弧。

		InsertArc(&G, v, w); 
		//初始条件：图G存在，v和w是G中的两个顶点。 
		//操作结果：在G中增添弧<v,w>，若G是无向的，则还增添对称弧<w,v>。

		DeleteArc(&G, v, w);
		//初始条件：图G存在，v和w是G中的两个顶点。  
		//操作结果：在G中删除弧<v,w>，若G是无向的，则还删除对称弧<w,v>。

		DFSTraverse(G, v, Visit());
		//初始条件：图G存在，Visit是顶点的函数。 
		//操作结果：对图进行深度优先遍历，在遍历过程中对每个顶点调用函数
		            Visit一次且仅一次。一旦Visit失败则操作失败。 

		BFSTraverse(G, v, Visit());
		//初始条件：图G存在，Visit是顶点的应用函数。 
		//操作结果：对图进行广度优先遍历，在遍历过程中对每个顶点调用函数
		            Visit一次且仅一次。一旦Visit失败则操作失败。 
}ADT Graph
*/ 

//**********************图（邻接矩阵）的主要操作**********************  

/*说明：图变网，加权值，改距离    有向变无向 ，置对称弧结点

                                       加权值  0,1变 ∞ 
                       有向图 <------------------------------> 有向网      
                          |            去权值  ∞变 0,1          | 
                          |                                      |
        	去对称弧结点  |  置对称弧结点         去对称弧结点   |   置对称弧结点 
                          |                                      |
                          |            加权值  0,1变 ∞          |
                       无向图 <------------------------------> 无向网
			                           去权值  ∞变 0,1
*/ 

/*
	函数：LocateVex
	参数：MGraph G 图G（邻接矩阵存储结构） 
	返回值：若G中存在顶点v，则返回该顶点在图中位置；否则返回-1
	作用：顶点定位函数，在图G中查找顶点v的位置 
*/
int LocateVex(MGraph G, int v){
	
	//遍历邻接矩阵查找顶点v 
	for(int i = 0; i <= G.vexnum; ++i) { 
		
		//若找到结点返回i
		if(G.vexs[i] == v) {
		    return i;
		}//if 
	}//for
	
	//否则返回-1，表示没有找到 
	return -1;
}//LocateVex

/*
	函数：CreateUDN
	参数：MGraph &G 图的引用 
	返回值：状态码，操作成功返回OK 
	作用：采用数组（邻接矩阵）表示法，构造无向网G
*/
Status CreateUDN(MGraph &G){
	
	//临时变量，从键盘接收顶点名称 
	VertexType v1, v2;
	
	//临时变量i用于保存顶点v1在图中的序号
	//临时变量j用于保存顶点v2在图中的序号 
	//临时变量w用于接收输入的权值 
	int w, i, j;
	
	//确定无向网的顶点数和边数 
	printf("请依次输入无向网G的顶点数，弧数，用逗号隔开\n");
	scanf("%d,%d", &G.vexnum, &G.arcnum);
	
	//从键盘输入各个顶点以构造各顶点向量 
	printf("请依次输入无向网G的顶点名称，用空格隔开\n"); 
	for(int i = 0; i < G.vexnum; ++i) { 
		scanf("%d", &G.vexs[i]);
	}//for
	
	//初始化邻接矩阵各存储单元的值为INFINITY，INFINITY表示两顶点不可达 
	for(int i = 0; i < G.vexnum; ++i) { 
	    for(int j = 0; j < G.vexnum; ++j) { 
	    	G.arcs[i][j].adj = INFINITY;
	    }//for 
	}//for
	
	//输入弧依附的顶点和权值，填充邻接矩阵  
	printf("请依次输入无向网G每条弧依附的两顶点名称及权值，输完一组按回车\n"); 
	for(int k = 0; k < G.arcnum; ++k){
		
		//输入弧依附的两顶点v1和v2 
	    scanf("%d", &v1);
        scanf("%d", &v2);
        
        //输入弧上的权值 
        scanf("%d", &w);
        
        //确定v1,v2在G中的位置i,j 
	    i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		
		//保存权值到邻接矩阵的对应存储单元中 
		G.arcs[i][j].adj = w;
		
		//由于构造的是无向网，所以还需要置<v1,v2>的对称弧<v2,v1> 
		//技巧：结构体直接赋值相当于结构体中各个分量的对应拷贝 
		G.arcs[j][i] = G.arcs[i][j];
	}//for
	
	//操作成功 
	return OK; 
}// CreateUDN

/*
	函数：CreateUDG
	参数：MGraph &G 图的引用 
	返回值：状态码，操作成功返回OK 
	作用：采用数组（邻接矩阵）表示法，构造无向图G 
*/
Status CreateUDG(MGraph &G){
	
	//接收用户从键盘输入的顶点 
	VertexType v1, v2;
	
	//临时变量i用于保存顶点v1在图G中的序号
	//临时变量j用于保存顶点v2在图G中的序号  
	int i, j;
	
	//确定无向图的顶点数和边数，用作循环控制边界 
	printf("请依次输入无向图G的顶点数，弧数，用逗号隔开\n");
	scanf("%d,%d", &G.vexnum, &G.arcnum);
	
	//输入各顶点名称并构造各顶点向量 
	printf("请依次输入无向图G的顶点名称，用空格隔开\n"); 
	for(int i = 0; i < G.vexnum; ++i) {
		scanf("%d", &G.vexs[i]);
	}//for
	
	//初始化邻接矩阵所有存储单元的值为0，0表示两顶点之间不可达 
	for(int i = 0; i < G.vexnum; ++i) {
	    for(int j = 0; j < G.vexnum; ++j) {
	    	G.arcs[i][j].adj = 0;
		}//for
	}//for 
	
	//输入弧依附的顶点，填充邻接矩阵  
	printf("请依次输入无向图G每条弧依附的两顶点名称，输完一组按回车\n"); 
	for(int k = 0; k < G.arcnum; ++k){
		
		//输入弧依附的两顶点v1和v2  
	    scanf("%d", &v1);
        scanf("%d", &v2);
        
        //确定v1,v2在G中的位置i和j 
	    i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		
		//设置v1->v2的值为1，表示v1->v2是可达的 
		G.arcs[i][j].adj = 1;
		
		//由于构造的是无向图，所以还需要置<v1,v2>的对称弧<v2,v1>
		G.arcs[j][i] = G.arcs[i][j]; 
	}//for
	
	//操作成功 
	return OK; 
}// CreateUDG

/*
	函数：CreateDN
	参数：MGraph &G 图的引用 
	返回值：状态码，操作成功返回OK 
	作用：采用数组（邻接矩阵）表示法，构造有向网G 
*/
Status CreateDN(MGraph &G){
	
	//临时变量v1和v2用于接收从键盘输入的两顶点的值 
	VertexType v1, v2;
	
	//临时变量w用于保存用户输入的权值
	//临时变量i用于保存顶点v1在图中的位置
	//临时变量j用于保存顶点v2在图中的位置 
	int w, i, j;
	
	//确定有向网的顶点数和边数，用作循环控制边界 
	printf("请依次输入有向网G的顶点数，弧数，用逗号隔开\n");
	scanf("%d,%d", &G.vexnum, &G.arcnum);
	
	//输入顶点名称构造各顶点向量
	printf("请依次输入有向网G的顶点名称，用空格隔开\n"); 
	for(int i = 0; i < G.vexnum; ++i) { 
		scanf("%d", &G.vexs[i]);
	}//for 
	
	//初始化邻接矩阵各存储单元的值为INFINITY，INFINITY表示两顶点不可达 
	for(int i = 0; i < G.vexnum; ++i) { 
	    for(int j = 0; j < G.vexnum; ++j) { 
	    	G.arcs[i][j].adj = INFINITY;
		}//for
	}//for
	
	//输入弧依附的顶点和权值，填充邻接矩阵 
	printf("请依次输入有向网G每条弧依附的两顶点名称及权值，输完一组按回车\n"); 
	for(int k = 0; k < G.arcnum; ++k) {
	    
		//输入弧依附的两顶点v1和v2 
		scanf("%d", &v1);
        scanf("%d", &v2);
        
        //输入弧上的权值 
        scanf("%d", &w);
		
		//确定v1,v2在G中的位置 
	    i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		
		//保存权值到邻接矩阵的对应存储单元中      
		G.arcs[i][j].adj = w;
	}//for
	
	//操作成功 
	return OK; 
}// CreateDN

/*
	函数：CreateDG
	参数：MGraph &G 图的引用 
	返回值：状态码，操作成功返回OK 
	作用：采用数组（邻接矩阵）表示法，构造有向图G  
*/
Status CreateDG(MGraph &G){
	
	//临时变量v1和v2用于接收从键盘输入的两顶点的值 
	VertexType v1, v2;
	
	//临时变量i用于保存顶点v1在图中的位置
	//临时变量j用于保存顶点v2在图中的位置 
	int i, j;
	
	//确定有向网的顶点数和边数，用作循环控制边界 
	printf("请依次输入有向图G的顶点数，弧数，用逗号隔开\n");
	scanf("%d,%d", &G.vexnum, &G.arcnum);
	
	//输入顶点名称构造各顶点向量
	printf("请依次输入有向图G的顶点名称，用空格隔开\n"); 
	for(int i = 0; i < G.vexnum; ++i) { 
		scanf("%d", &G.vexs[i]);
	}//for
	
	//初始化邻接矩阵所有存储单元的值为0，0表示两顶点之间不可达  
	for(int i = 0; i < G.vexnum; ++i) {
	    for(int j = 0; j < G.vexnum; ++j) {
	    	G.arcs[i][j].adj=0; 
		}//for
	}//for
	
	//输入弧依附的顶点，填充邻接矩阵 
	printf("请依次输入有向图G每条弧依附的两顶点名称，输完一组按回车\n"); 
	for(int k = 0; k < G.arcnum; ++k) { 
	
		//输入弧依附的两顶点v1和v2 
	    scanf("%d", &v1);
        scanf("%d", &v2);
        
        //确定v1,v2在G中的位置i和j 
	    i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		
		//设置v1->v2的值为1，表示v1->v2是可达的
		G.arcs[i][j].adj = 1;
	}//for
	
	//操作成功 
	return OK; 
}// CreateDG

/*
	函数：CreateGraph
	参数：MGraph &G 图的引用 
	返回值：状态码，操作成功返回OK 
	作用：采用数组（邻接矩阵）表示法，构造图G
*/
Status CreateGraph(MGraph &G){
	
	//输入构造图的类型 
	printf("请输入您想构造的图的类型:有向图输入0,有向网输入1,无向图输入2,无向网输入3):");
	scanf("%d", &G.kind);
	
	//根据图的不同类型调用图的构造函数 
	switch(G.kind){
		case  DG:  return CreateDG(G);  //构造有向图G
		case  DN:  return CreateDN(G);  //构造有向网G
		case UDG:  return CreateUDG(G); //构造无向图G
		case UDN:  return CreateUDN(G); //构造无向网G
		default :  return ERROR;
	}//switch
}//CreateGraph

/*
	函数：DestroyGraph
	参数：MGraph &G 图的引用 
	返回值：状态码，操作成功返回OK 
	作用：销毁图G
*/
Status DestroyGraph(MGraph &G) {

	//若是网 
	if(G.kind % 2) {
	
		//重置邻接矩阵所有顶点之间不可达 
		for(int i = 0; i < G.vexnum; i++) {
			for(int j = 0; j < G.vexnum; j++) {
				G.arcs[i][j].adj = INFINITY;
			}//for 
	    }//for 
	}//if
	else { //若是图 
		
		//重置邻接矩阵所有顶点之间不可达 
		for(int i = 0; i < G.vexnum; i++) {
			for(int j = 0; j < G.vexnum; j++) {
				G.arcs[i][j].adj = 0;
			}//for 
	    }//for 
	}//else
	
	//重置顶点数为0
	G.vexnum = 0;
	
	//重置边数为0
	G.arcnum = 0;
}//DestroyGraph

/*
	函数：PrintAdjMatrix
	参数：MGraph G 图G
	返回值：状态码，操作成功返回OK 
	作用：打印某个图的邻接矩阵 
*/
Status PrintAdjMatrix(MGraph G){
	
	//输出左上角多余的空白 
	printf("      ");
	
	//输出邻接矩阵的上坐标（全部顶点） 
	for(int i = 0; i < G.vexnum; i++) {
		
		printf(" %3d ", G.vexs[i]); 	
	}//for 
	
	printf("\n"); 
	
	//输出左上角多余的空白 
	printf("     +");
	
	//输出一条横线
	for(int i = 0; i < G.vexnum; i++) {
		printf("-----"); 
	}//for 
	
	printf("\n"); 
	
	//输出邻接矩阵的左坐标（全部顶点）和内容 
	for(int i = 0; i < G.vexnum; i++) {
		
		//输出邻接矩阵左边的坐标
		printf(" %3d |", G.vexs[i]);  
		
	    for(int j = 0; j < G.vexnum; j++) {
	        if(G.arcs[i][j].adj == INFINITY) {
			    printf("  ∞ ");
			}//if 
			else {
			    printf(" %3d ", G.arcs[i][j].adj);
			}//else
		}//for 
	    printf("\n     |\n");
	}//for 
}//PrintAdjMatrix

/*
	函数：GetVex
	参数：MGraph G 图G
	      int v v是G中某个顶点的序号
	返回值：返回v的值
	作用：得到序号为v的顶点值 
*/
VertexType& GetVex(MGraph G, int v) {
	
	//检查参数v是否合法：v是否越界 
	if(v >= G.vexnum || v < 0) { 
    	exit(ERROR);
    }//if
	
	//返回序号为v的顶点值 
	return G.vexs[v];
}//GetVex

/*
	函数：PutVex
	参数：MGraph &G 图的引用 
	      VertexType v v是G中某个顶点
	      VertexType value 将序号为v的顶点的值修改为value 
	返回值：状态码，操作成功返回OK，否则返回ERROR 
	作用：修改序号为v的顶点值 
*/
Status PutVex(MGraph &G, VertexType v, VertexType value) {
	
	//k为顶点v在图G中的序号
	int k = LocateVex(G, v);
	
	//检查图中是否存在顶点v
	if(k < 0) { 
    	return ERROR;
    }//if
	
	//将顶点v的值置为value 
	G.vexs[k] = value;
	
	//操作成功 
	return OK;
}//PutVex 


/*
	函数：FirstAdjVex
	参数：MGraph G 图G
	      VertexType v 顶点v 
	返回值：若找到邻接点，返回邻接点的顶点位置，否则返回-1 
	作用：求顶点v在图G中的第一个邻接点
*/
int FirstAdjVex(MGraph G, VertexType v){
	
	//j表示不可达，在图中，0表示不可达，在网中INFINITY表示不可达 
	int j = 0;
	
	//v是顶点，不是序号！需要定位 
	//k就是顶点v在顶点数组中的序号 
	int k = LocateVex(G, v);
	
	//若是网，则INFINITY表示不可达 
	if(G.kind == DN || G.kind == UDN) {
	   j = INFINITY;
	}//if
	
	//在顶点v对应的第k行查找第一个邻接点的序号i 
	for(int i = 0; i < G.vexnum; ++i) {
		
		//若找到顶点v的第一个邻接点则返回i
		//G.arcs[k][i].adj != j 表示顶点G.arcs[k][i]可达 
		if(G.arcs[k][i].adj != j) {
	    	return i;
		}//if 
	}//for
	 
	//若未找到返回-1 
	return -1;
}//FirstAdjVex

/*
	函数：NextAdjVex
	参数：MGraph G 图G
	      VertexType v 顶点v 
	返回值：若找到邻接点，返回邻接点的顶点位置，否则返回-1 
	作用：求顶点v在图G中相对于邻接点w的下一个邻接点
*/
int NextAdjVex(MGraph G, VertexType v, VertexType w){
	
	//j表示不可达，在图中，0表示不可达，在网中INFINITY表示不可达
	int j = 0;
	
	//k1是顶点v在顶点数组中的位序 
	int k1 = LocateVex(G, v);
	
	//k2是顶点w在顶点数组中的位序 
	int k2 = LocateVex(G, w);
	
	//若是网，则使用INFINITY表示不可达 
	if(G.kind == DN || G.kind == UDN) { 
		j = INFINITY;
	}//if
	
	//在图G中查找顶点v相对于顶点w的下一个邻接点的位置 
	for(int i= k2 + 1; i < G.vexnum; ++i) {
	   
		//若找到则返回i 
		if(G.arcs[k1][i].adj != j) {
	    	return i;
		}//if
	}//for
	
	//若未找到返回-1
	return -1;
}//NextAdjVex

/*
	函数：InsertVex
	参数：MGraph &G 图的引用 
	      VertexType v 顶点v 
	返回值：状态码，操作成功返回OK 
	作用：在图G中增添新顶点v
*/
Status InsertVex(MGraph &G, VertexType v) {
	
	//j表示不可达，在图中，0表示不可达，在网中INFINITY表示不可达
	int j = 0;
	
	//若是网，则使用INFINITY表示不可达 
	if(G.kind % 2) { 
    	j = INFINITY;
    }//if
	 
	//构造新顶点向量
   	G.vexs[G.vexnum] = v;
   
   	//初始化邻接矩阵 
	for(int i = 0; i <= G.vexnum; i++) {
		
		//初始化矩阵的每个存储单元为不可达 
    	G.arcs[G.vexnum][i].adj = G.arcs[i][G.vexnum].adj = j;
	}//for
	
	//图G的顶点数加1
	G.vexnum++;
	
	//操作成功 
	return OK; 
}//InsertVex

/*
	函数：DeleteVex
	参数：MGraph &G 图的引用 
	      VertexType v 顶点v 
	返回值：状态码，操作成功返回OK 
	作用：删除G中顶点v及其相关的弧
*/
Status DeleteVex(MGraph &G, VertexType v) {
	
	//m表示不可达，在图中，0表示不可达，在网中INFINITY表示不可达
	VRType m = 0;
	
	//若是网，则使用INFINITY表示不可达 
	if(G.kind % 2) {
    	m = INFINITY;
	}//if
	
	//k为待删除顶点v的序号
	int k = LocateVex(G, v);
	
	//检查v是否是图G的顶点
	if(k < 0) { //v不是图G的顶点
	
		//操作失败 
    	return ERROR;
	}//if
	
	//删除边的信息 
	for(int j = 0; j < G.vexnum; j++) { 
    	
    	//有入弧
		if(G.arcs[j][k].adj != m) {
			
			//删除弧
			G.arcs[j][k].adj = m; 
			
			//弧数-1
       		G.arcnum--; 
		}//if
		
		//有出弧
		if(G.arcs[k][j].adj != m) {
     		
     		//删除弧
			G.arcs[k][j].adj = m; 
     		
     		//弧数-1
			G.arcnum--;
   		}//if 
	}//for 
	
	//序号k后面的顶点向量依次前移
	for(int j = k + 1; j < G.vexnum; j++) {
    	G.vexs[j-1] = G.vexs[j];
	}//for
	
	//移动待删除顶点之右的矩阵元素
	for(int i = 0; i < G.vexnum; i++) {
    	for(int j = k + 1; j < G.vexnum; j++) {
       		G.arcs[i][j - 1] = G.arcs[i][j];
       	}//for
	}//for
	
	//移动待删除顶点之下的矩阵元素
	for(int i = 0; i < G.vexnum; i++) {
    	for(int j = k + 1; j < G.vexnum; j++) {
    		G.arcs[j - 1][i] = G.arcs[j][i];
    	}//for
	}//for
	
	//图的顶点数-1
	G.vexnum--;
	
	//操作成功 
	return OK;
}//DeleteVex

/*
	函数：InsertArc
	参数：MGraph &G 图的引用 
	      VertexType v 顶点v（弧尾） 
	      VertexType w 顶点w（弧头） 
	返回值：状态码，操作成功返回OK 
	作用：在G中增添弧<v,w>，若G是无向的，则还增添对称弧<w,v>
*/
Status InsertArc(MGraph &G, VertexType v, VertexType w) {
   
	//弧尾顶点v在图中的序号v1 
	int v1 = LocateVex(G, v);
	
	//弧头顶点w在图中的序号w1 
	int w1 = LocateVex(G, w);
	
	//检查顶点v和顶点w在图中是否存在 
	if(v1 < 0 || w1 < 0) {  //v或w有一个不是图G中的顶点
	
		//操作失败 
    	return ERROR;
    }//if 
    
    //弧或边数加1
	G.arcnum++;
	
	//如果是图G是网，还需要输入权值 
	//if(G.kind % 2) <=> if(G.kind % 2 != 0)
	if(G.kind % 2) {
    	printf("请输入此弧或边的权值: ");
    	scanf("%d", &G.arcs[v1][w1].adj);
	}//if
	else { // 图
    	G.arcs[v1][w1].adj = 1;
	}//else 
   
   	//如果是无向图或无向网还需要置对称的边 
	if(G.kind > 1) {
    	G.arcs[w1][v1].adj = G.arcs[v1][w1].adj;
	}//if
	
	//操作成功 
	return OK;
}//InsertArc

/*
	函数：DeleteArc
	参数：MGraph &G 图的引用 
	      VertexType v 顶点v（弧尾） 
	      VertexType w 顶点w（弧头） 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：在G中删除弧<v,w>，若G是无向的，则还删除对称弧<w,v>
*/
Status DeleteArc(MGraph &G, VertexType v, VertexType w) {
   
	//j表示不可达，在图中，0表示不可达，在网中INFINITY表示不可达
	int j = 0;
   
   	//若是网，则使用INFINITY表示不可达 
	if(G.kind % 2) {
    	j = INFINITY;
	}//if
	
	//弧头顶点v在图中的序号v1 
	int v1 = LocateVex(G, v);
	
	//弧尾顶点w在图中的序号w1 
	int w1 = LocateVex(G, w);
	
	//检查顶点v和顶点w在图中是否存在 
	if(v1 < 0 || w1 < 0) { //v或w有一个不是图G中的顶点
    	return ERROR;
    }//if 
    
    //将顶点v与顶点w之间设为不可达 
	G.arcs[v1][w1].adj = j;
	
	//如果是无向图或网，还需要删除对称弧<w,v>
	if(G.kind >= 2) {
    	G.arcs[w1][v1].adj = j;
	}//if
	
	//弧数-1
	G.arcnum--;
	
	//操作成功 
	return OK;
}//DeleteArc
