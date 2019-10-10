
//**************************引入头文件*****************************
#include <stdio.h>   //使用了标准库函数 
#include <stdlib.h>  //使用了动态内存分配函数 

#include "my_constants.h"  //引入自定义的符号常量，主要是状态码 
#include "ALGraph.h"       //引入图的邻接表存储结构定义 
#include "LinkedList.cpp"  //引入单链表实现，用到其中的插入、删除等操作 
#include "LinkedQueue.cpp" //引入链队列实现 
#include "ALGraph.cpp"     //引入图的邻接表存储结构基本操作实现
#include "DFS_BFS_ALGraph.cpp" //引入图的深度优先遍历和广度优先遍历实现 

int main() {
	
	printf("----------------图的邻接表存储表示引用版演示程序------------------\n\n"); 
	
	//临时变量 
	int j, k, n;
	
	//图的邻接表存储方式 
	ALGraph g;
	
	//临时变量 
	VertexType v1, v2;
	
	//创建图g并打印初始状态 
	printf("->测试图G的创建："); 
	CreateGraph(g);
	printf("图G创建成功！\n");
	printf("->打印创建后的图G：\n"); 
	Display(g);
	
	//测试顶点和弧的插入
	printf("->测试顶点和弧的插入：\n"); 
	printf("->插入新顶点，请输入顶点（将作为有向图弧尾）的值: ");
	scanf("%d", &v1);
	InsertVex(g, v1);
	
	printf("->插入与新顶点有关的弧或边，请输入弧或边数: ");
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		
		printf("->请输入新的弧头顶点的值: ");
		scanf("%d", &v2);
		//无向图的对称弧会自动被InsertArc函数创建，
		//无需再次调用InsertArc函数创建对称的弧结点 
		InsertArc(g, v1, v2);
	}//for
	
	//以邻接矩阵形式打印图G，查看插入边之后图G发生了什么变化 
	printf("->插入新的顶点和弧之后，图G的邻接矩阵：\n"); 
	Display(g);
	
	printf("->基于邻接表存储结构的深度优先遍历序列（从%d顶点开始）:\n", g.vertices[0].data);
	DFSTraverse(g, print); 
	printf("\n");
	
	printf("->基于邻接表存储结构的广度优先遍历序列（从%d顶点开始）:\n", g.vertices[0].data);
	BFSTraverse(g, print);
	printf("\n"); 

	//测试无向网弧的删除 
	printf("->测试删除一条边或弧，请输入待删除边或弧的弧尾 弧头(逗号隔开)：");
	scanf("%d,%d", &v1, &v2);
	DeleteArc(g, v1, v2);
	printf("->删除弧后的图G：\n"); 
	Display(g);
	
	//测试修改顶点的值 
	printf("->测试修改顶点的值，请输入原值 新值（逗号隔开）: ");
	scanf("%d,%d", &v1, &v2);
	PutVex(g, v1, v2);
	printf("->修改顶点后的图G：\n"); 
	Display(g);
	
	//测试删除顶点及相关的弧或边
	printf("->测试删除顶点及相关的弧或边，请输入顶点的值: ");
	scanf("%d", &v1);
	DeleteVex(g, v1);
	printf("->删除顶点后的图G：\n"); 
	Display(g);
	
	//测试销毁图G
	printf("->测试销毁图G:"); 
	DestroyGraph(g);
	printf("销毁成功！");
	
	printf("演示结束");
}//main

/*
----------------图的邻接表存储表示引用版演示程序------------------

->测试图G的创建：请输入图的类型(有向图输入0, 有向网输入1,无向图输入2,无向网输入3): 2
请输入图的顶点数,边数: 5,6
请输入5个顶点的值(用空格隔开):
1 2 3 4 5
请输入每条弧(边)的弧尾和弧头(以逗号作为间隔):
1,2
1,4
2,3
2,5
3,4
3,5
图G创建成功！
->打印创建后的图G：
此图为无向图!

图中共有5个顶点，6条弧(边)，它们分别是：
+----+-----------------------------------------------
|顶点|   邻接顶点(和权值)
+----+-----------------------------------------------
|  1 | →4  →2
+----+-----------------------------------------------
|  2 | →5  →3  →1
+----+-----------------------------------------------
|  3 | →5  →4  →2
+----+-----------------------------------------------
|  4 | →3  →1
+----+-----------------------------------------------
|  5 | →3  →2
+----+-----------------------------------------------

->测试顶点和弧的插入：
->插入新顶点，请输入顶点（将作为有向图弧尾）的值: 6
->插入与新顶点有关的弧或边，请输入弧或边数: 2
->请输入新的弧头顶点的值: 1
->请输入新的弧头顶点的值: 2
->插入新的顶点和弧之后，图G的邻接矩阵：
此图为无向图!

图中共有6个顶点，8条弧(边)，它们分别是：
+----+-----------------------------------------------
|顶点|   邻接顶点(和权值)
+----+-----------------------------------------------
|  1 | →6  →4  →2
+----+-----------------------------------------------
|  2 | →6  →5  →3  →1
+----+-----------------------------------------------
|  3 | →5  →4  →2
+----+-----------------------------------------------
|  4 | →3  →1
+----+-----------------------------------------------
|  5 | →3  →2
+----+-----------------------------------------------
|  6 | →2  →1
+----+-----------------------------------------------

->基于邻接表存储结构的深度优先遍历序列（从1顶点开始）:
 1  6  2  5  3  4

->基于邻接表存储结构的广度优先遍历序列（从1顶点开始）:
 1  6  4  2  3  5

->测试删除一条边或弧，请输入待删除边或弧的弧尾 弧头(逗号隔开)：3,4
->删除弧后的图G：
此图为无向图!

图中共有6个顶点，8条弧(边)，它们分别是：
+----+-----------------------------------------------
|顶点|   邻接顶点(和权值)
+----+-----------------------------------------------
|  1 | →6  →4  →2
+----+-----------------------------------------------
|  2 | →6  →5  →3  →1
+----+-----------------------------------------------
|  3 | →5  →2
+----+-----------------------------------------------
|  4 | →3  →1
+----+-----------------------------------------------
|  5 | →3  →2
+----+-----------------------------------------------
|  6 | →2  →1
+----+-----------------------------------------------

->测试修改顶点的值，请输入原值 新值（逗号隔开）: 3,7
->修改顶点后的图G：
此图为无向图!

图中共有6个顶点，8条弧(边)，它们分别是：
+----+-----------------------------------------------
|顶点|   邻接顶点(和权值)
+----+-----------------------------------------------
|  1 | →6  →4  →2
+----+-----------------------------------------------
|  2 | →6  →5  →7  →1
+----+-----------------------------------------------
|  7 | →5  →2
+----+-----------------------------------------------
|  4 | →7  →1
+----+-----------------------------------------------
|  5 | →7  →2
+----+-----------------------------------------------
|  6 | →2  →1
+----+-----------------------------------------------

->测试删除顶点及相关的弧或边，请输入顶点的值: 4
->删除顶点后的图G：
此图为无向图!

图中共有5个顶点，6条弧(边)，它们分别是：
+----+-----------------------------------------------
|顶点|   邻接顶点(和权值)
+----+-----------------------------------------------
|  1 | →6  →2
+----+-----------------------------------------------
|  2 | →6  →5  →7  →1
+----+-----------------------------------------------
|  7 | →5  →2
+----+-----------------------------------------------
|  5 | →7  →2
+----+-----------------------------------------------
|  6 | →2  →1
+----+-----------------------------------------------

->测试销毁图G:销毁成功！演示结束
--------------------------------
Process exited with return value 0
Press any key to continue . . .
*/ 
