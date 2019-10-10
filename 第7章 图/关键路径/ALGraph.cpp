/*--------------------图的ADT定义----------------------------------

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

//-----------------------------图的基本操作------------------------------

/*
	函数：LocateVex
	参数：ALGraph G 图G（邻接表存储结构） 
	      VertexType u 顶点u 
	返回值：若G中存在顶点u，则返回该顶点在图中位置；否则返回-1
	初始条件：图G存在，u和G中顶点有相同特征
	作用：在图G中查找顶点u的位置 
*/
int LocateVex(ALGraph G, VertexType u){
	
	//i是临时变量，循环控制用 
	int i;
	
	//与图中每个结点的名称作对比 
	for(i = 0; i < G.vexnum; ++i) {
		
		//在图中找到了结点 
		if(G.vertices[i].data == u) {
			
			//返回顶点在图中的位置 
			return i;
		}//if 
	}//for
	
	//没有在图中找到顶点，返回-1 
	return -1;
}//LocateVex

/*
	函数：CreateGraph
	参数：ALGraph &G 图的引用 
	返回值：状态码，操作成功返回OK。 
	作用：根据用户的输入构造图（四种）。 
*/
Status CreateGraph(ALGraph &G) {
	
	//w是权值
	//i、j、k全是临时变量，循环用 
	int i, j, k, w;
	
	//连接边或弧的2顶点
	VertexType va, vb;
	
	//弧结点 
	ElemType e;
	
	//确定图的类型 
	printf("请输入图的类型(有向图输入0, 有向网输入1,无向图输入2,无向网输入3): ");
	scanf("%d", &G.kind);
	
	//确定图的顶点数和边数 
	printf("请输入图的顶点数,边数: ");
	scanf("%d,%d", &G.vexnum, &G.arcnum);
	
	//从键盘输入顶点值，构造顶点向量 
	printf("请输入%d个顶点的值(用空格隔开):\n", G.vexnum);
	for(i = 0; i < G.vexnum; ++i) {
		
		//输入顶点的值 
		scanf("%d", &G.vertices[i].data);
		getchar(); //吃掉多余字符 
		
		//初始化与该顶点有关的出弧链表
		G.vertices[i].firstarc = NULL;
	}//for
	
	//如果是构造网，则需要继续输入权值，如果是构造图则不需要 
	//枚举变量中{有向图 = 0,有向网 = 1,无向图 = 2,无向网 = 3} 
	//G.kind % 2 != 0 表示构造的是网，否则是图 
	if(G.kind % 2) { //if(G.kind % 2) <=> if(G.kind % 2 != 0)
		printf("请输入每条弧(边)的弧尾、弧头和权值(以逗号作为间隔):\n");
	}//if 
	else { //构造图
		printf("请输入每条弧(边)的弧尾和弧头(以逗号作为间隔):\n");
	}//else
	 
	//构造相关弧链表
	for(k = 0; k < G.arcnum; ++k){
		
		//如果构造的是网，则需要接收权值 
		//if(G.kind % 2) <=> if(G.kind % 2 != 0)
		if(G.kind % 2) {
			scanf("%d,%d,%d", &va, &vb, &w);
		}//if 
		else { //构造的是图，不需要接收权值 
			scanf("%d,%d", &va, &vb);
		}//else
		
		//先处理弧头和弧尾部分，这是图和网都需要执行的公共操作。 
		
		//弧尾
		i = LocateVex(G, va);
		
		//弧头
		j = LocateVex(G, vb);
		
		//给待插表结点e赋值，图没有权值，网有权值。由于所有结点的初始化
		//都用到e，所以这块空间每轮新的循环都需要重置为NULL（清零）。 
		//如果构造的是网，还会连接一小块保存权值的空间，否则保持NULL。 
		e.info = NULL;
		
		//弧头
		e.adjvex = j;
	
		//如果构造的是网，则需要将权值存放到弧的相关信息info中
		//注意：此时info的空间还没有申请到 
		//if(G.kind % 2) <=> if(G.kind % 2 != 0)
		if(G.kind % 2) {
			
			//申请存放权值的空间
			e.info = (InfoType *)malloc(sizeof(int));
			
			//将弧的相关信息填入存放权值的空间中 
			*(e.info) = w;
		}//if
		
		//将弧结点插在第i个顶点的表头
		//本项操作调用的是单链表的插入算法，把G.vertices[i].firstarc当成了头结点
		//采用头插法插入 
		ListInsert(G.vertices[i].firstarc, 1, e);
		
		//如果构造的是无向图或无向网，产生第2个表结点，并插在第j个元素(入弧)的表头
		//第二个表结点与第一个结点沿主对角线（左上至右下）对称 
		if(G.kind >= 2) {
			
			//主对角线对称位置的结点权值不变，所以e.info不变，不必再赋值
			//也就是说：邻接矩阵中沿主对角线对称的两个结点在邻接表中共用一块权值空间 
			e.adjvex = i;
			
			//插在对角线对称位置顶点的表头，也就是第j个位置。 
			ListInsert(G.vertices[j].firstarc, 1, e);
		}//if 
	}//for
	
	//操作成功 
	return OK;
}//CreateGraph

/*
	函数：DestroyGraph
	参数：ALGraph &G 图的引用 
	返回值：状态码，操作成功返回OK。 
	作用：若图G存在，销毁图G 
*/
Status DestroyGraph(ALGraph &G) {
	
	//i是临时变量，循环控制用 
	int i;
	
	//带回从邻接表中删除的弧结点，如果是网，还需要继续释放存储权值的存储单元的空间 
	ElemType e;
	
	//对于所有顶点
	for(i = 0; i < G.vexnum; ++i) { 
		
		//如果被销毁的是网，还需要继续销毁权值 
		//if(G.kind % 2) <=> if(G.kind % 2 != 0)
		if(G.kind % 2) {
			
			//顶点对应的弧或边链表不空
	   		while(G.vertices[i].firstarc) {
	   			
	   			//删除链表的第1个弧结点，并将值赋给e
	 			ListDelete(G.vertices[i].firstarc, 1, e);
	 			
	 			//释放保存权值的内存空间 
	 			//需要注意：在构造网时为了节约空间，让沿主对角线对称的两个结点 
				//的权值信息指针e.info指向了同一块内存区域。所以释放内存空间的时候
				//要注意已经释放过的内存空间不可以再次释放。所以在释放内存空间之前
				//需要进行判断。但是C语言没有提供判断内存是否被释放的函数。
				//这就需要我们自己写判断条件。观察邻接矩阵不难发现：
				//主对角线上方的结点和沿主对角线对称的下方的结点之间存在一个规律：
				//上方结点的列下标 > 对称位置（下方）结点的列下标
				//由于释放弧结点时是按照顶点顺序从小到大进行的，
				//列下标大的弧结点（上三角）总比列下标小的弧结点（下三角）先释放。 
				//所以判断结点是否被释放的标志就是：顶点序号 > i
	 			if(e.adjvex > i) { 
	   				free(e.info);
	   			}//if
	   		}//while
	   	}//if 
	 	else {//若被销毁的是图，只销毁弧链表就行了 
	 		
	 		//调用单链表销毁函数销毁弧链表
	   		DestoryList(G.vertices[i].firstarc);
	  	}//else
	}//for
	 
	//重置顶点数为0
	G.vexnum = 0;
	
	//重置边或弧数为0
	G.arcnum = 0;
	
	//操作成功
	return OK; 
}//DestroyGraph 

/*
	函数：GetVex
	参数：ALGraph G 图G 
	      int v 某个顶点的序号v 
	返回值：顶点v的值 
	作用：若图G存在，v是G中某个顶点的序号，返回顶点v的值 
*/
VertexType& GetVex(ALGraph G, int v) {
	
	//检查顶点序号v是否越界 
	if(v >= G.vexnum || v < 0) { 
	
		//若越界访问则直接退出程序 
		exit(ERROR);
	}//if
	
	//返回顶点v的值 
	return G.vertices[v].data;
}//GetVex

/*
	函数：PutVex
	参数：ALGraph &G 图G的引用 
	      VertexType v 待修改顶点v 
	      VertexType value 将顶点v的值修改为value
	返回值：状态码，操作成功返回OK，失败返回ERROR 
	作用：若图G存在，v是G中某个顶点，对v赋新值value 
*/
Status PutVex(ALGraph &G, VertexType v, VertexType value) {

	//i记录了在图的邻接表中定位顶点操作得到的v在顶点数组中的下标 
	int i;
	
	//通过定位操作得到下标 
	i = LocateVex(G, v);
	
	//得到下标之后需判断下标是否合法：即图中是否存在顶点v
	//若图中不存在顶点v，定位函数LocateVex返回-1 
	if(i > -1) { //图中存在顶点v
	
		//修改顶点v的值为value 
    	G.vertices[i].data = value;
    	
    	//操作成功 
    	return OK;
	}//if
	
	//操作失败 
	return ERROR;
}//PutVex

/*
	函数：FirstAdjVex
	参数：ALGraph G 图G
	      VertexType v 顶点v 
	返回值：若v在图G中有邻接顶点，返回v的第一个邻接顶点的序号，否则返回-1。 
	作用：若图G存在，v是G中某个顶点,返回v的第一个邻接顶点的序号。
	      若顶点在G中没有邻接顶点，则返回-1
*/
int FirstAdjVex(ALGraph G, VertexType v) {
   
	//工作指针p,指向顶点v弧链表中的顶点 
	ArcNode *p;
   
	//i为顶点v在图G中的序号
	int i;
   
	//通过定位操作找出顶点v的序号 
	i = LocateVex(G, v);
   
	//检查图中是否存在顶点v 
	if(i == -1) {
		return -1; 
	}//if
   
	//工作指针p指向序号i指示的顶点v 
	p = G.vertices[i].firstarc;
   
	//如果v有邻接顶点 
	if(p) { //if(p) <=> if(p != NULL) 
		
		//返回顶点v第一个邻接顶点的序号 
		return p->data.adjvex;
	}//if
	else { //顶点v没有邻接顶点 
	
		//返回-1 
		return -1;
	}//else
}//FirstAdjVex

/*
	函数：equalvex
	参数：ElemType a 顶点A 
	      ElemType b 顶点B 
	返回值：状态码，操作成功返回OK，失败返回ERROR 
	作用：判断两个弧结点是否有相同的邻接点。
	      DeleteArc()、DeleteVex()和NextAdjVex()要调用的函数
*/
Status equalvex(ElemType a, ElemType b) {
	
	//如果顶点A和顶点B的邻接顶点相同 
   	if(a.adjvex == b.adjvex) {
    	
    	//返回1 
		return OK;
	}//if
   	else {
   		
   		//返回0 
   		return ERROR;
   	}//else 
}//equalvex

/*
	函数：NextAdjVex
	参数：ALGraph G 图G 
	      VertexType v v是G中某个顶点
		  VertexType w w是v的邻接顶点 
	返回值：返回v的(相对于w的)下一个邻接顶点的序号。
	        若w是v的最后一个邻接点，则返回-1
	作用：得到顶点v相对于顶点w的下一个邻接顶点的序号。 
*/
int NextAdjVex(ALGraph G, VertexType v, VertexType w) {
	
	//p是工作指针 
	//p1在Point()中用作辅助指针
	LinkList p, p1;
	
	//e保存了弧结点的信息 
	ElemType e;
	
	//找出顶点v在图G中的序号v1
	int v1 = LocateVex(G, v); 
	
	//找出顶点w在图G中的序号，由e.adjvex保存 
   	e.adjvex = LocateVex(G, w);
	
	//p指向顶点v的链表中邻接顶点为w的结点
	p = Point(G.vertices[v1].firstarc, e, equalvex, p1);
	
	//没找到w或w是最后一个邻接点
	if(!p || !p->next) { 
    	return -1;
    }//if 
	else { //找出了与顶点v邻接的顶点w 
		
		//返回v的相对于w的下一个邻接顶点的序号
    	return p->next->data.adjvex;
	}//else 
}//NextAdjVex

/*
	函数：InsertVex
	参数：ALGraph &G 图G的引用 
	      VertexType v 被插入的顶点v 
	返回值：状态码，操作成功返回OK，否则返回ERROR 
	作用：在图G中增添新顶点v，但不增添与顶点相关的弧。 
*/
Status InsertVex(ALGraph &G, VertexType v) { 

	//加入新的顶点，设置其名称 
	G.vertices[G.vexnum].data = v;
	
	//由于还没有添加邻接弧的信息，所以firstarc的值为空 
	G.vertices[G.vexnum].firstarc = NULL;
	
	//图G的顶点数加1
	G.vexnum++;
	
	//操作成功 
	return OK;
}//InsertVex

/*
	函数：DeleteVex
	参数：ALGraph &G 图G的引用 
	      VertexType v 被删除的顶点v 
	返回值：状态码，操作成功返回OK，否则返回ERROR 
	作用：删除G中顶点v及其相关的弧
*/
Status DeleteVex(ALGraph &G, VertexType v) {
   
   	//i是临时变量，存储了以v为出度的弧或边数
	//j是临时变量，保存顶点v的序号 
	int i, j, k;
   
	//临时变量，用于设置查找以顶点v为邻接顶点的弧结点的条件 
	ElemType e;
   
	//工作指针p，指向找到的以顶点v为邻接顶点的弧结点 
	//工作指针p1指向p的前驱 
	LinkList p, p1;
   
	//j是顶点v的序号
	j = LocateVex(G, v);
   
	//检查在图G中是否找到顶点v 
	if(j < 0) { 
		return ERROR;
	}//if
	
	//i存储了以v为出度的弧或边数（也就是弧链表长度） 
	i = ListLength(G.vertices[j].firstarc);
	
	//边或弧数-i
	G.arcnum -= i;
	
	//如果图G是网，还需要另外销毁保存权值的内存空间 
	if(G.kind % 2) { 
		
		//对应的弧或边链表不空
    	while(G.vertices[j].firstarc) {
    		
    		//删除链表的第1个结点，并将值赋给e
			ListDelete(G.vertices[j].firstarc, 1, e);
			
			//考虑到无向网的权值空间共享问题，所以要先判断
			//权值空间是否已经被释放再执行空间释放操作 
			if(e.info != NULL) {
				//释放e.info指示的动态生成的权值空间
    			free(e.info);
    			e.info == NULL;  //指针置空 
    		}//if
    	}//while
	}//if
	else { //如果是图
		
		//只需要销毁弧或边链表就可以了，不用考虑权值问题 
    	DestoryList(G.vertices[j].firstarc);
    }//else 
   		
   	//顶点数减1
	G.vexnum--;
		
	//保存顶点采用了顺序存储结构，所以删除顶点v之后，后面的顶点需要前移
	for(i = j; i < G.vexnum; i++) { 
    	G.vertices[i] = G.vertices[i + 1];
    }//for 
    
    //之前的操作只是删除了顶点v和其后面的弧链表。还有很多善后工作没有做：
	//1.之前的删除操作只考虑了出度，没考虑入度。我们不仅需要删除掉v指向
	//  其他顶点的信息，还需要删除其他顶点指向顶点v的弧。
	//2.如果顶点v不是顶点数组中的最后一个顶点，由于在删除顶点v后，顶点v
	//  后面的顶点需要做前移操作。此时后面顶点在顶点数组中的位序就会改变
	//  但是与后面顶点相关的弧结点中存储的邻接顶点的位序并未随之更新，
	//  所以我们还需要将这些邻接顶点的弧结点中的邻接顶点的位序全部更新一遍。
	//  保证删除操作后存储的图的邻接信息的正确性。
	//3.如果是网，还需要考虑权值存储空间的释放问题。 
    
    //删除以v为入度的弧或边且必要时修改表结点的顶点位置值
	for(i = 0; i < G.vexnum; i++) {
    	
    	//j保存了顶点v的序号，接下来要利用e找出所有与v邻接的顶点 
		e.adjvex = j;
    	
    	//p指向在G.vertices[i].firstarc指示的弧链表中以v为邻接点的弧结点
		//p1指向p的前驱，若p指向首元结点，则p1为NULL 
    	p = Point(G.vertices[i].firstarc, e, equalvex, p1);
     
     	//顶点i的邻接表上有v为入度的结点
		if(p) { //if(p) <=> if(p != NULL) 
	 		
	 		//p不指向首元结点 
    		if(p1) { //if(p1) <=> if(p1 != NULL)
    			
    			//从链表中删除p所指结点
         		p1->next = p->next;
         	}//if
       		else { // p指向首元结点
       			
       			//头指针指向下一结点
         		G.vertices[i].firstarc = p->next;
        	}//else
        	
        	//有向图或者有向网 
       		if(G.kind < 2) {
       			
       			//边或弧数-1
         		G.arcnum--;
         		
         		//有向网直接释放权值内存空间就行，不用考虑对称位置的问题 
				if(G.kind == DN) { 
					//释放动态生成的权值空间
           			free(p->data.info);
           		}//if
			}//if
			
			//释放v为入度的结点
			free(p);
       	}//if
       	
       	//解决由于结点前移造成后面结点弧的邻接信息不正确的问题 
	    //对于adjvex域>j的结点，其序号-1
	    for(k = j + 1; k <= G.vexnum; k++) {
	    	
	    	//将以顶点v后面顶点为邻接顶点的顶点在图中的序号
			//保存在e.adjvex中 
			e.adjvex = k;
			
			//使p指向以顶点v为入度的弧结点
			//p1指向p的前驱，若p指向头结点,p1=NULL 
	    	p = Point(G.vertices[i].firstarc, e, equalvex, p1);
	    	
	    	//判断是否找到这样的弧结点 
	    	if(p) { //if(p) <=> if(p != NULL)
	    		
	    		//由于顶点v被删除造成v后面的顶点前移。所以存储在弧结点中的
				//序号应该和前移之后的顶点序号保持一致，即序号-1
	    		p->data.adjvex--;
	    	}//if
	    }//for
   }//for
   
   //操作成功 
   return OK;
}//DeleteVex 

/*
	函数：InsertArc
	参数：ALGraph &G 图G的引用 
	      VertexType v 图中的顶点w （弧尾） 
	      VertexType w 图中的顶点v （弧头） 
	返回值：状态码，操作成功返回OK，否则返回ERROR 
	作用：在G中增添弧<v,w>，若G是无向的，则还增添对称弧<w,v>
*/
Status InsertArc(ALGraph &G, VertexType v, VertexType w) {
	
	//临时变量，存储了弧结点的信息 
	ElemType e;

	//i是顶点v在图G中的序号 
	int i = LocateVex(G, v);
	
	//j是顶点w在图G中的序号 
	int j = LocateVex(G, w);
	
	//检查顶点v或w是否在图G中存在，若不存在则终止函数向下执行 
	if(i < 0 || j < 0) { 
		return ERROR;
	}//if
	
	//插入一条边之后图G的弧或边的数目加1
	//注意：网中两个顶点之间正向和反向的弧算一条，不要重复添加 
	G.arcnum++;
	
	//在顶点v的弧链表中插入邻接点w的信息 
	e.adjvex = j;
	
	//图没有权值，所以将权值指针e.info的初始值设置为NULL 
	e.info = NULL;
	
	//如果是在网中插入弧，还需要设置弧的权值 
	if(G.kind % 2) { //if(G.kind % 2) <=> if(G.kind % 2 != 0)
	 	
	 	//动态申请存放权值的空间 
    	e.info = (InfoType *)malloc(sizeof(int));
    	
    	//从键盘输入权值的信息 
		printf("请输入弧(边)%d→%d的权值: ", v, w);
    	scanf("%d", &e.info);
	}//if
	
	//将e插在弧尾v的弧链表表头
	ListInsert(G.vertices[i].firstarc, 1, e); 
	
	//在无向图或无向网中插入弧，还要加入反向的另一条弧 
	if(G.kind >= 2) {
		
		//无向图没有权值，两条弧的e.info都是NULL 
		//无向网的两条弧共用一个权值存储单元，e.info不变
    	e.adjvex = i;
    	
    	//将e插在顶点w弧链表的表头
    	ListInsert(G.vertices[j].firstarc, 1, e);
    	
    	//注意：网中两个顶点之间正向和反向的弧算一条，不要重复添加 
	}//if
   	
   	//操作成功 
	return OK;
}//InsertArc

/*
	函数：DeleteArc
	参数：ALGraph &G 图G的引用 
	      VertexType v 图中的顶点w （弧尾） 
	      VertexType w 图中的顶点v （弧头） 
	返回值：状态码，操作成功返回OK，否则返回ERROR 
	作用：在G中删除弧<v,w>，若G是无向的，则还删除对称弧<w,v>
*/
Status DeleteArc(ALGraph &G, VertexType v, VertexType w) {
	
	//k记录了删除操作的结果 
	Status k;
	
	//临时变量e存储了查找邻接点的比较条件 
	ElemType e;
	
	//i是顶点v(弧尾)在图G中的序号
	int i = LocateVex(G, v);
	
	//j是顶点w(弧头)在图G中的序号
	int j = LocateVex(G, w);
	
	//检查i和j是否合法 
	if(i < 0 || j < 0 || i == j) { 
    	return ERROR;
    }//if
    
    //删除<v,w>这条弧 
	
	//设置在顶点v的弧链表中插入的弧结点的邻接点的序号为j 
	e.adjvex = j;
	
	//从顶点v的弧链表中删除邻接顶点w的弧结点 
	k = DeleteElem(G.vertices[i].firstarc, e, equalvex);
	
	//删除弧<v,w>成功
	if(k) { //if(k) <=> if(k != ERROR) 
    	
    	//图中弧或边数减1
		G.arcnum--;
    	
    	//如果是网，还需要释放权值存储单元的空间 
		if(G.kind % 2) {
    		free(e.info);
    	}//if
    	
    	//如果是无向网或无向图则还需要删除对称弧<w,v>
    	if(G.kind >= 2) {
    		
    		//设置w的邻接点为v 
    		e.adjvex = i;
    		
    		//删除w到v的弧 
    		DeleteElem(G.vertices[j].firstarc, e, equalvex);
    	}//if
    	
    	//操作成功 
		return OK;
	}//if
	else { // 没找到待删除的弧
    	return ERROR;
	}//else
}//DeleteArc

/*
	函数：Display
	参数：ALGraph &G 图G的引用 
	      VertexType v 图中的顶点w （弧尾） 
	      VertexType w 图中的顶点v （弧头） 
	返回值：状态码，操作成功返回OK，否则返回ERROR 
	作用：以邻接矩阵形式输出邻接表 
*/
void Display(ALGraph G) {
	
	//工作指针p 
	ArcNode *p;
   
	//打印图的类型 
	switch(G.kind) {
    	case DG: printf("此图为有向图!\n");
				 break;
    	case DN: printf("此图为有向网!\n");
				 break;
    	case UDG:printf("此图为无向图!\n");
	    		 break;
    	case UDN:printf("此图为无向网!\n");
	}//switch
	 
    //打印图的总顶点数，总边数以及每条边 
	printf("\n图中共有%d个顶点，%d条弧(边)，它们分别是：\n", G.vexnum, G.arcnum);
	printf("+----+-----------------------------------------------\n");
	printf("|顶点|   邻接顶点(和权值)  \n");
	printf("+----+-----------------------------------------------\n");
   	for(int i = 0; i < G.vexnum; i++){
    	
    	printf("| %2d |", G.vertices[i].data);
    	
    	//p指向某个顶点弧链表的首元结点 
		p = G.vertices[i].firstarc;
    	
    	//遍历整个弧链表 
		while(p) { //while(p) <=> while(p != NULL) 
        		
    		//打印弧头和弧尾的信息 
			printf(" →%d ", G.vertices[p->data.adjvex].data);
     		
     		//如果图G是网，还需要打印出权值 
			if(G.kind % 2) {
       			printf(",权值:%d ", *(p->data.info));
       		}//if 
			
			//p指向弧链表下一个结点 
			p = p->nextarc;
		}//while
		
		//输出完一个顶点之后换行
		printf("\n+----+-----------------------------------------------\n");
	}//for
	
	//输出换行，使结果美观 
	printf("\n");
}//Display
