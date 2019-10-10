//-------------图的数组（邻接矩阵）存储表示

//一个输入的权值很难达到的最大值 ∞
#define INFINITY 65535

//最大顶点个数
#define MAX_VERTEX_NUM 20

//使用枚举类型定义图的四种基本类型 
typedef enum {
	
	//（有向图=0，有向网=1，无向图=2，无向网=3）
	DG, DN, UDG, UDN
} GraphKind;

//指定顶点关系类型为int 
typedef int VRType;

//指定顶点类型为int 
typedef int VertexType;

typedef struct ArcCell{
	
	//VRType是顶点关系类型。
	//对无权图，用1或0，表示相邻与否，对带权图，则为权值类型 
	VRType adj;
	
	//我修改了书上的定义删除了info指针。
	//原因是：info指针完全没必要设置，因为无论是图还是网，
	//        adj这个数据域都已经足够存储所有有用信息了。
	//        作者设置info指针的本意是指向存储网权值的内存空间。
	//        但是由于adj本身就能存储网中的权值，也不会引起歧义
	//        而且设置了info之后还会涉及很多内存的分配、释放和指针操作
	//        为了使一个函数适用于四种图，需要根据图的不同类型对这个指针
	//        执行不同的操作。去掉info可以简化操作。 
	 
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; 

typedef struct{
	
	//顶点向量:存储了图中所有的顶点 
	VertexType vexs[MAX_VERTEX_NUM];
	
	//邻接矩阵：存储了顶点之间的邻接关系以及权值 
	AdjMatrix arcs; 
	
	//图当前的顶点数和弧数
	int vexnum, arcnum;
	
	//图的种类标志 
	GraphKind kind;
}MGraph; 
