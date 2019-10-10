//---------------------图的邻接表存储表示---------------------- 

//指定顶点类型是int
typedef int VertexType;

//指定弧的权值类型为int 
typedef int InfoType;

//最大顶点数 
#define MAX_VERTEX_NUM 50

//图的种类标志 
typedef enum {
	
	// {有向图 = 0,有向网 = 1,无向图 = 2,无向网 = 3}
	DG, DN, UDG, UDN
} GraphKind;

//存储边信息的结点

typedef struct ElemType{
	
	//该弧所指向的顶点的位置，也就是从当前顶点出发指向哪个顶点 
	//这个变量存储的是指向顶点在AdjList数组中的下标 
	int adjvex;
	
	//该弧相关信息的指针
	//弧的相关信息就是存放权值的，当图的类型是网的时候这个变量才有意义 
	InfoType *info;
} ElemType;
 
typedef struct ArcNode{  
	
	//除了弧指针外的其他部分均属于data 
	ElemType data;
	
	//指向下一条弧的指针
	struct ArcNode *nextarc;	
} ArcNode;

//存储顶点信息的结点 
typedef struct VNode {
	
	//顶点名称 
	VertexType data;
	
	//指向第一条依附该顶点的弧（存储第一条边结点地址的指针域） 
	ArcNode  *firstarc;
} VNode, AdjList[MAX_VERTEX_NUM];

//图的邻接表存储表示 
typedef struct ALGraph {
	
	//顶点向量，在数组中存储了图中所有的顶点 
	AdjList  vertices;
	
	//图的当前顶点数和弧数(边数)
    int vexnum, arcnum;
    
	//图的种类标志
	GraphKind kind; 
} ALGraph;

//为了复用单链表中的插入、删除等基本操作，采用宏定义方式配合引入的单链表实现
//完成与图的邻接表存储结构的操作对接 

//定义单链表的结点类型是图的表结点的类型
#define LNode ArcNode

//定义单链表结点的指针域是表结点指向下一条弧的指针域
#define next nextarc

//定义指向单链表结点的指针是指向图的表结点的指针 
typedef ArcNode *LinkList;
