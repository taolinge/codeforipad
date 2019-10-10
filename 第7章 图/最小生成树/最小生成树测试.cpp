
//**************************引入头文件*****************************
#include <stdio.h>   //使用了标准库函数 
#include <stdlib.h>  //使用了动态内存分配函数

#include "my_constants.h" //引入自定义的符号常量，主要是状态码 
#include "MGraph.h"       //引入图的邻接矩阵表示法的基本定义 
#include "MGraph.cpp"     //引入图的主要操作
#include "MiniSpanTree.cpp" //引入最小生成树实现 

//----------------------主函数----------------------
int main(int argc, char *argv[]){
    
	printf("\n-------------最小生成树（邻接矩阵）测试程序--------------\n\n"); 
	
	//图G 
	MGraph G; 
	
	//临时变量，保存输入的顶点数 
	int n;
	
	//图的创建
	printf("->测试图的创建（最小生成树操作要求图的类型是无向连通网，请选择3）：\n");
	CreateGraph(G);
	
	//打印邻接矩阵
	printf("\n->创建成功后图的邻接矩阵:\n\n"); 
	PrintAdjMatrix(G);
	
	//若为无向网，求其最小生成树
	if(G.kind == UDN){
		printf("\n->测试普利姆算法求无向网的最小生成树\n");
		MiniSpanTree_PRIM(G, G.vexs[0]);  
		
		printf("\n->测试克鲁斯卡尔算法求无向网的最小生成树\n");
		MiniSpanTree_kruskal(G);  
    }//if 
    else {
    	printf("\n->您生成的不是无向网，无法求最小生成树！\n");
    }//else 
    
    //测试销毁 
    printf("\n->测试销毁图： ");
	DestroyGraph(G); 
	printf("成功！\n");
	
	printf("演示结束，程序退出！\n");
	
	return 0;
} 

/*--------------------------输入全程记录（便于测试，可直接复制）------------------------------ 

   说明：下面输入的无向图来自教材P174页



-------------最小生成树（邻接矩阵）测试程序--------------

->测试图的创建（最小生成树操作要求图的类型是无向连通网，请选择3）：
请输入您想构造的图的类型:有向图输入0,有向网输入1,无向图输入2,无向网输入3):3
请依次输入无向网G的顶点数，弧数，用逗号隔开
6,10
请依次输入无向网G的顶点名称，用空格隔开
1 2 3 4 5 6
请依次输入无向网G每条弧依附的两顶点名称及权值，输完一组按回车
1 2 6
1 4 5
1 3 1
3 2 5
3 4 5
3 5 6
3 6 4
2 5 3
4 6 2
5 6 6

->创建成功后图的邻接矩阵:

         1    2    3    4    5    6
     +------------------------------
   1 |  ∞    6    1    5   ∞   ∞
     |
   2 |   6   ∞    5   ∞    3   ∞
     |
   3 |   1    5   ∞    5    6    4
     |
   4 |   5   ∞    5   ∞   ∞    2
     |
   5 |  ∞    3    6   ∞   ∞    6
     |
   6 |  ∞   ∞    4    2    6   ∞
     |

->测试普利姆算法求无向网的最小生成树

->最小生成树从顶点1开始，所以该顶点此时已被加入最小生成树顶点集合！


->这是第1趟循环：
->更新closedge数组之前，closedge数组的值(adjvex是顶点序号，不是顶点名称，lowcost = 0表示该顶点已被纳入最小生成树的顶点集合)：
+----------+-----+-----+-----+-----+-----+-----+
|     i    |   0 |   1 |   2 |   3 |   4 |   5 |
+----------+-----+-----+-----+-----+-----+-----+
|   顶点   |   1 |   2 |   3 |   4 |   5 |   6 |
+----------+-----+-----+-----+-----+-----+-----+
|  adjvex  |   0 |   1 |   1 |   1 |   1 |   1 |
+----------+-----+-----+-----+-----+-----+-----+
|  lowcost |   0 |   6 |   1 |   5 |  ∞ |  ∞ |
+----------+-----+-----+-----+-----+-----+-----+
->开始求最小生成树的下一顶点：
->发现比reserve = 65535更小的权值：closedge[1].lowcost = 6 ！
->发现比reserve = 6更小的权值：closedge[2].lowcost = 1 ！
->求得最小生成树的下一顶点为：3，下一顶点序号k = 2, 最小代价为：1

->得到最小生成树的一条新边：  1 <---  1 --->  3

从3的所有邻接顶点中发现有G.arcs[2][1].adj = 5 比 closedge[1].lowcost = 6 更小，更新closedge数组！
从3的所有邻接顶点中发现有G.arcs[2][4].adj = 6 比 closedge[4].lowcost = 65535 更小，更新closedge数组！
从3的所有邻接顶点中发现有G.arcs[2][5].adj = 4 比 closedge[5].lowcost = 65535 更小，更新closedge数组！

->更新closedge数组之后，closedge数组的值(adjvex是顶点序号，不是顶点名称，lowcost = 0表示该顶点已被纳入最小生成树的顶点集合)：
+----------+-----+-----+-----+-----+-----+-----+
|     i    |   0 |   1 |   2 |   3 |   4 |   5 |
+----------+-----+-----+-----+-----+-----+-----+
|   顶点   |   1 |   2 |   3 |   4 |   5 |   6 |
+----------+-----+-----+-----+-----+-----+-----+
|  adjvex  |   0 |   3 |   1 |   1 |   3 |   3 |
+----------+-----+-----+-----+-----+-----+-----+
|  lowcost |   0 |   5 |   0 |   5 |   6 |   4 |
+----------+-----+-----+-----+-----+-----+-----+
请按任意键继续. . .

->这是第2趟循环：
->更新closedge数组之前，closedge数组的值(adjvex是顶点序号，不是顶点名称，lowcost = 0表示该顶点已被纳入最小生成树的顶点集合)：
+----------+-----+-----+-----+-----+-----+-----+
|     i    |   0 |   1 |   2 |   3 |   4 |   5 |
+----------+-----+-----+-----+-----+-----+-----+
|   顶点   |   1 |   2 |   3 |   4 |   5 |   6 |
+----------+-----+-----+-----+-----+-----+-----+
|  adjvex  |   0 |   3 |   1 |   1 |   3 |   3 |
+----------+-----+-----+-----+-----+-----+-----+
|  lowcost |   0 |   5 |   0 |   5 |   6 |   4 |
+----------+-----+-----+-----+-----+-----+-----+
->开始求最小生成树的下一顶点：
->发现比reserve = 65535更小的权值：closedge[1].lowcost = 5 ！
->发现比reserve = 5更小的权值：closedge[5].lowcost = 4 ！
->求得最小生成树的下一顶点为：6，下一顶点序号k = 5, 最小代价为：4

->得到最小生成树的一条新边：  3 <---  4 --->  6

从6的所有邻接顶点中发现有G.arcs[5][3].adj = 2 比 closedge[3].lowcost = 5 更小，更新closedge数组！

->更新closedge数组之后，closedge数组的值(adjvex是顶点序号，不是顶点名称，lowcost = 0表示该顶点已被纳入最小生成树的顶点集合)：
+----------+-----+-----+-----+-----+-----+-----+
|     i    |   0 |   1 |   2 |   3 |   4 |   5 |
+----------+-----+-----+-----+-----+-----+-----+
|   顶点   |   1 |   2 |   3 |   4 |   5 |   6 |
+----------+-----+-----+-----+-----+-----+-----+
|  adjvex  |   0 |   3 |   1 |   6 |   3 |   3 |
+----------+-----+-----+-----+-----+-----+-----+
|  lowcost |   0 |   5 |   0 |   2 |   6 |   0 |
+----------+-----+-----+-----+-----+-----+-----+
请按任意键继续. . .

->这是第3趟循环：
->更新closedge数组之前，closedge数组的值(adjvex是顶点序号，不是顶点名称，lowcost = 0表示该顶点已被纳入最小生成树的顶点集合)：
+----------+-----+-----+-----+-----+-----+-----+
|     i    |   0 |   1 |   2 |   3 |   4 |   5 |
+----------+-----+-----+-----+-----+-----+-----+
|   顶点   |   1 |   2 |   3 |   4 |   5 |   6 |
+----------+-----+-----+-----+-----+-----+-----+
|  adjvex  |   0 |   3 |   1 |   6 |   3 |   3 |
+----------+-----+-----+-----+-----+-----+-----+
|  lowcost |   0 |   5 |   0 |   2 |   6 |   0 |
+----------+-----+-----+-----+-----+-----+-----+
->开始求最小生成树的下一顶点：
->发现比reserve = 65535更小的权值：closedge[1].lowcost = 5 ！
->发现比reserve = 5更小的权值：closedge[3].lowcost = 2 ！
->求得最小生成树的下一顶点为：4，下一顶点序号k = 3, 最小代价为：2

->得到最小生成树的一条新边：  6 <---  2 --->  4


->更新closedge数组之后，closedge数组的值(adjvex是顶点序号，不是顶点名称，lowcost = 0表示该顶点已被纳入最小生成树的顶点集合)：
+----------+-----+-----+-----+-----+-----+-----+
|     i    |   0 |   1 |   2 |   3 |   4 |   5 |
+----------+-----+-----+-----+-----+-----+-----+
|   顶点   |   1 |   2 |   3 |   4 |   5 |   6 |
+----------+-----+-----+-----+-----+-----+-----+
|  adjvex  |   0 |   3 |   1 |   6 |   3 |   3 |
+----------+-----+-----+-----+-----+-----+-----+
|  lowcost |   0 |   5 |   0 |   0 |   6 |   0 |
+----------+-----+-----+-----+-----+-----+-----+
请按任意键继续. . .

->这是第4趟循环：
->更新closedge数组之前，closedge数组的值(adjvex是顶点序号，不是顶点名称，lowcost = 0表示该顶点已被纳入最小生成树的顶点集合)：
+----------+-----+-----+-----+-----+-----+-----+
|     i    |   0 |   1 |   2 |   3 |   4 |   5 |
+----------+-----+-----+-----+-----+-----+-----+
|   顶点   |   1 |   2 |   3 |   4 |   5 |   6 |
+----------+-----+-----+-----+-----+-----+-----+
|  adjvex  |   0 |   3 |   1 |   6 |   3 |   3 |
+----------+-----+-----+-----+-----+-----+-----+
|  lowcost |   0 |   5 |   0 |   0 |   6 |   0 |
+----------+-----+-----+-----+-----+-----+-----+
->开始求最小生成树的下一顶点：
->发现比reserve = 65535更小的权值：closedge[1].lowcost = 5 ！
->求得最小生成树的下一顶点为：2，下一顶点序号k = 1, 最小代价为：5

->得到最小生成树的一条新边：  3 <---  5 --->  2

从2的所有邻接顶点中发现有G.arcs[1][4].adj = 3 比 closedge[4].lowcost = 6 更小，更新closedge数组！

->更新closedge数组之后，closedge数组的值(adjvex是顶点序号，不是顶点名称，lowcost = 0表示该顶点已被纳入最小生成树的顶点集合)：
+----------+-----+-----+-----+-----+-----+-----+
|     i    |   0 |   1 |   2 |   3 |   4 |   5 |
+----------+-----+-----+-----+-----+-----+-----+
|   顶点   |   1 |   2 |   3 |   4 |   5 |   6 |
+----------+-----+-----+-----+-----+-----+-----+
|  adjvex  |   0 |   3 |   1 |   6 |   2 |   3 |
+----------+-----+-----+-----+-----+-----+-----+
|  lowcost |   0 |   0 |   0 |   0 |   3 |   0 |
+----------+-----+-----+-----+-----+-----+-----+
请按任意键继续. . .

->这是第5趟循环：
->更新closedge数组之前，closedge数组的值(adjvex是顶点序号，不是顶点名称，lowcost = 0表示该顶点已被纳入最小生成树的顶点集合)：
+----------+-----+-----+-----+-----+-----+-----+
|     i    |   0 |   1 |   2 |   3 |   4 |   5 |
+----------+-----+-----+-----+-----+-----+-----+
|   顶点   |   1 |   2 |   3 |   4 |   5 |   6 |
+----------+-----+-----+-----+-----+-----+-----+
|  adjvex  |   0 |   3 |   1 |   6 |   2 |   3 |
+----------+-----+-----+-----+-----+-----+-----+
|  lowcost |   0 |   0 |   0 |   0 |   3 |   0 |
+----------+-----+-----+-----+-----+-----+-----+
->开始求最小生成树的下一顶点：
->发现比reserve = 65535更小的权值：closedge[4].lowcost = 3 ！
->求得最小生成树的下一顶点为：5，下一顶点序号k = 4, 最小代价为：3

->得到最小生成树的一条新边：  2 <---  3 --->  5


->更新closedge数组之后，closedge数组的值(adjvex是顶点序号，不是顶点名称，lowcost = 0表示该顶点已被纳入最小生成树的顶点集合)：
+----------+-----+-----+-----+-----+-----+-----+
|     i    |   0 |   1 |   2 |   3 |   4 |   5 |
+----------+-----+-----+-----+-----+-----+-----+
|   顶点   |   1 |   2 |   3 |   4 |   5 |   6 |
+----------+-----+-----+-----+-----+-----+-----+
|  adjvex  |   0 |   3 |   1 |   6 |   2 |   3 |
+----------+-----+-----+-----+-----+-----+-----+
|  lowcost |   0 |   0 |   0 |   0 |   0 |   0 |
+----------+-----+-----+-----+-----+-----+-----+
请按任意键继续. . .

->测试克鲁斯卡尔算法求无向网的最小生成树
->set数组初始状态（各顶点分别属于各个集合）：
+----------+-----+-----+-----+-----+-----+-----+
|     i    |   0 |   1 |   2 |   3 |   4 |   5 |
+----------+-----+-----+-----+-----+-----+-----+
|   顶点   |   1 |   2 |   3 |   4 |   5 |   6 |
+----------+-----+-----+-----+-----+-----+-----+
|    set   |   0 |   1 |   2 |   3 |   4 |   5 |
+----------+-----+-----+-----+-----+-----+-----+
最小代价生成树的各条边及权值为:

->这是第1趟循环，寻找更小权值的边：
->发现比min = 65535 更小的权值：6，修改min为该值！
->发现比min = 6 更小的权值：1，修改min为该值！
->找到一条最小生成树的新边：1 <-- 1 --> 3
->合并顶点3到顶点1的集合中，注意set数组的变化。
->set数组修改后的值：
+----------+-----+-----+-----+-----+-----+-----+
|     i    |   0 |   1 |   2 |   3 |   4 |   5 |
+----------+-----+-----+-----+-----+-----+-----+
|   顶点   |   1 |   2 |   3 |   4 |   5 |   6 |
+----------+-----+-----+-----+-----+-----+-----+
|    set   |   0 |   1 |   0 |   3 |   4 |   5 |
+----------+-----+-----+-----+-----+-----+-----+

->这是第2趟循环，寻找更小权值的边：
->发现比min = 65535 更小的权值：6，修改min为该值！
->发现比min = 6 更小的权值：5，修改min为该值！
->发现比min = 5 更小的权值：3，修改min为该值！
->发现比min = 3 更小的权值：2，修改min为该值！
->找到一条最小生成树的新边：4 <-- 2 --> 6
->合并顶点6到顶点4的集合中，注意set数组的变化。
->set数组修改后的值：
+----------+-----+-----+-----+-----+-----+-----+
|     i    |   0 |   1 |   2 |   3 |   4 |   5 |
+----------+-----+-----+-----+-----+-----+-----+
|   顶点   |   1 |   2 |   3 |   4 |   5 |   6 |
+----------+-----+-----+-----+-----+-----+-----+
|    set   |   0 |   1 |   0 |   3 |   4 |   3 |
+----------+-----+-----+-----+-----+-----+-----+

->这是第3趟循环，寻找更小权值的边：
->发现比min = 65535 更小的权值：6，修改min为该值！
->发现比min = 6 更小的权值：5，修改min为该值！
->发现比min = 5 更小的权值：3，修改min为该值！
->找到一条最小生成树的新边：2 <-- 3 --> 5
->合并顶点5到顶点2的集合中，注意set数组的变化。
->set数组修改后的值：
+----------+-----+-----+-----+-----+-----+-----+
|     i    |   0 |   1 |   2 |   3 |   4 |   5 |
+----------+-----+-----+-----+-----+-----+-----+
|   顶点   |   1 |   2 |   3 |   4 |   5 |   6 |
+----------+-----+-----+-----+-----+-----+-----+
|    set   |   0 |   1 |   0 |   3 |   1 |   3 |
+----------+-----+-----+-----+-----+-----+-----+

->这是第4趟循环，寻找更小权值的边：
->发现比min = 65535 更小的权值：6，修改min为该值！
->发现比min = 6 更小的权值：5，修改min为该值！
->发现比min = 5 更小的权值：4，修改min为该值！
->找到一条最小生成树的新边：3 <-- 4 --> 6
->合并顶点4到顶点3的集合中，注意set数组的变化。
->合并顶点6到顶点3的集合中，注意set数组的变化。
->set数组修改后的值：
+----------+-----+-----+-----+-----+-----+-----+
|     i    |   0 |   1 |   2 |   3 |   4 |   5 |
+----------+-----+-----+-----+-----+-----+-----+
|   顶点   |   1 |   2 |   3 |   4 |   5 |   6 |
+----------+-----+-----+-----+-----+-----+-----+
|    set   |   0 |   1 |   0 |   0 |   1 |   0 |
+----------+-----+-----+-----+-----+-----+-----+

->这是第5趟循环，寻找更小权值的边：
->发现比min = 65535 更小的权值：6，修改min为该值！
->发现比min = 6 更小的权值：5，修改min为该值！

->这是第5趟循环，寻找更小权值的边：
->发现比min = 65535 更小的权值：6，修改min为该值！
->发现比min = 6 更小的权值：5，修改min为该值！
->找到一条最小生成树的新边：2 <-- 5 --> 3
->合并顶点1到顶点2的集合中，注意set数组的变化。
->合并顶点3到顶点2的集合中，注意set数组的变化。
->合并顶点4到顶点2的集合中，注意set数组的变化。
->合并顶点6到顶点2的集合中，注意set数组的变化。
->set数组修改后的值：
+----------+-----+-----+-----+-----+-----+-----+
|     i    |   0 |   1 |   2 |   3 |   4 |   5 |
+----------+-----+-----+-----+-----+-----+-----+
|   顶点   |   1 |   2 |   3 |   4 |   5 |   6 |
+----------+-----+-----+-----+-----+-----+-----+
|    set   |   1 |   1 |   1 |   1 |   1 |   1 |
+----------+-----+-----+-----+-----+-----+-----+
->set数组初最终状态(无向连通网所有顶点应该都在一个集合里)：
+----------+-----+-----+-----+-----+-----+-----+
|     i    |   0 |   1 |   2 |   3 |   4 |   5 |
+----------+-----+-----+-----+-----+-----+-----+
|   顶点   |   1 |   2 |   3 |   4 |   5 |   6 |
+----------+-----+-----+-----+-----+-----+-----+
|    set   |   1 |   1 |   1 |   1 |   1 |   1 |
+----------+-----+-----+-----+-----+-----+-----+

->测试销毁图： 成功！
演示结束，程序退出！

--------------------------------
Process exited with return value 0
Press any key to continue . . .


*/
