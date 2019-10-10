/* 
注意：1.程序的执行会花费较长时间，因为6种排序算法各要执行100次； 
2.程序执行的结果具有不可再现性，因为程序的执行结果与CPU、内存的性能和当前状态有关； 
3.请根据执行程序计算机的实际情况来确定待排序元素个数，不能过多也不能过少，
  由于计算机的性能存在差异，教室多媒体电脑的CPU和内存性能会比较差，
  如果长时间无法显示结果（如下），说明该计算机性能较差，请尝试减少元素数量：
				  
	-------------------------------内排序算法效率比较------------------------------
	
	您想给顺序表初始化多少个元素？（输入一个不超过10000的整数）  10000
	
	+------------------------------------------------------------------------------+
	|                                 排序结果                                     |
	+----------+------------------+------------------------------------------------+
	|   排名   |   排序方法名称   |               排序花费时间（毫秒）             |
	+----------+------------------+------------------------------------------------+
	
	【光标在这里闪烁，长时间没反应】 

  如果运行结果很快执行完成且多处存在0值（如下情况），请尝试增加元素数量：
				  
	-------------------------------内排序算法效率比较------------------------------
	
	您想给顺序表初始化多少个元素？（输入一个不超过10000的整数）  2
	
	+------------------------------------------------------------------------------+
	|                                 排序结果                                     |
	+----------+------------------+------------------------------------------------+
	|   排名   |   排序方法名称   |               排序花费时间（毫秒）             |
	+----------+------------------+------------------------------------------------+
	|    1     |   直接插入排序   |                            0                   |
	+----------+------------------+------------------------------------------------+
	|    2     |   折半插入排序   |                            0                   |
	+----------+------------------+------------------------------------------------+
	|    3     |       希尔排序   |                            0                   |
	+----------+------------------+------------------------------------------------+
	|    4     |       起泡排序   |                            0                   |
	+----------+------------------+------------------------------------------------+
	|    5     |       快速排序   |                            0                   |
	+----------+------------------+------------------------------------------------+
	|    6     |       选择排序   |                            0                   |
	+----------+------------------+------------------------------------------------+
	|    7     |       归并排序   |                            0                   |
	+----------+------------------+------------------------------------------------+ 
4.为了公平起见，所有排序算法都会执行100次，每次的数字均由计算机随机生成，最终结果
  取平均值作为排序算法的效率衡量指标，如果想要多次执行，请在出现提示后按下除N或n外
  的其他键，程序会重新执行。 
5.为了方便扩展，当需要增加新的排序算法实现时仅需要修改三处：
  1>修改 SORTNUM 符号常量，每增加一种排序算法该常量的值要增加1
  2>在扩展区域1增加你的算法实现 
  3>在主函数中的扩展区域2按照模板增加你的算法调用 
 */
//*************************引入头文件**************************
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

//*************************自定义符号常量********************* 

#define OVERFLOW -2         //内存溢出错误常量
#define ILLEGAL -1          //非法操作错误常量 
#define OK 1                //表示操作正确的常量 
#define ERROR 0             //表示操作错误的常量
#define TRUE 1              //表示逻辑正确的常量 
#define FALSE 0             //表示逻辑错误的常量
#define MAXSIZE 10000       //一个用作示例的小顺序表的最大长度 
#define EQ(a,b) ((a)==(b))  //相等 
#define LT(a,b) ((a)< (b))  //小与
#define LQ(a,b) ((a)<= (b)) //小与等于   
#define SORTNUM 8           //共有8种排序算法，如果日后需要扩展排序算法种类，请修改这里 

//************************自定义数据类型**********************

typedef int Status;   //状态标志  
typedef int KeyType;  //定义关键字类型为整数类型
typedef int InfoType; //信息类型
 
typedef struct{       //元素类型 
	KeyType key;  //关键字域
	InfoType otherinfo;  //其他数据项（记录该数据项的初始位置） 
}RedType;   //记录类型 

typedef struct{
	RedType r[MAXSIZE+1];  //r[0]闲置或用作哨兵单元
	int length;  //顺序表长度 
}SqList; //顺序表类型 

//--------------------记录排序结果的存储结构-------------------
typedef struct{
	float resultTime;  //排序花费的时间 
	char* name;     //排序方法名称 
}Result; 

//*****************顺序表的主要操作*********************** 
//-------------------1.初始化顺序表---------------------------- 

/*
	函数：InitList_Sq
	参数：SqList &L 顺序表引用 
	返回值：状态码，操作成功返回OK 
	作用：根据用户输入创建一棵二叉排序树 
*/
Status InitList_Sq(SqList &L){
	
	while(1){
		printf("您想给顺序表初始化多少个元素？（输入一个不超过10000的整数）  ");
		scanf("%d", &L.length);
		
		if(L.length > 0 && L.length <= 10000){
			break;
		}//if
	}//while
	
	//操作成功 
	return OK;
}//InitList_Sq 

/*
	函数：GenerateRandNumber
	参数：SqList &L 顺序表引用 
	返回值：状态码，操作成功返回OK 
	作用：用随机数初始化元素值 
*/
void GenerateRandNumber(SqList &L){
	
	for(int i = 1; i <= L.length; ++i) { 
		
		//用随机数初始化元素值 
		L.r[i].key = (int)(rand() % 20000 + 1);
		
		//记录元素的初始位置
		L.r[i].otherinfo = i; 
	}//for 
}//GenerateRandNumber

//----------------------------------2.遍历顺序表------------------------------------
/*
	函数：Print
	参数：RedType r 被访问记录 
	返回值：状态码，操作成功返回OK 
	作用：元素访问函数
*/
Status Print(RedType r) {
	
	//以控制台输出的方式访问记录 
	printf("%d[%d] ", r.key, r.otherinfo);
	
	//操作成功 
	return OK;
}//Print

/*
	函数：ListTraverse_Sq
	参数：SqList L 顺序表L
	      Status(* Visit)(RedType) 元素访问函数 
	返回值：状态码，操作成功返回OK 
	作用：顺序表遍历
*/
Status ListTraverse_Sq(SqList L, Status(* Visit)(RedType)) {
	
	//循环遍历顺序表中所有记录 
	for(int i = 1; i <= L.length; ++i) {
		
		//访问每个元素一次且仅一次，一旦访问失败则遍历失败 
		//if(!Visit(L.r[i])) <=> if(Visit(L.r[i]) == ERROR) 
		if(!Visit(L.r[i])) { 
			
			//遍历失败 
			return ERROR;
		}//if 
	}//for
	
	//输出空格，使结果美观 
	printf("\n");
	
	//操作成功 
	return OK;
}//ListTraverse_Sq

//----------------------------------3.排序算法------------------------------------

/*
	函数：InsertSort
	参数：SqList &L 顺序表引用 
	返回值：无
	作用：直接插入排序
*/
void InsertSort(SqList &L){
    
    int j;
    
	for(int i = 2; i <= L.length; ++i) {
	    
	    //"<",需将L.r[i]插入有序子集
		if(LT(L.r[i].key, L.r[i-1].key)){
			
			//复制为“哨兵”
		    L.r[0] = L.r[i];
		    
		    //记录后移,腾出插入位置 
			L.r[i] = L.r[i-1];
			for(j = i-2; LT(L.r[0].key, L.r[j].key); --j) {
			   L.r[j + 1] = L.r[j];    
			}//for
			
			//插入到正确位置
			L.r[j + 1] = L.r[0];
		}//if
	}//for
}//InsertSort 

//------------------折半插入排序-------------------- 

/*
	函数：BInsertSort
	参数：SqList &L 顺序表引用 
	返回值：无
	作用：对顺序表L作折半插入排序
*/
void BInsertSort(SqList &L) {
    
    //high、low和m是三个指针。m就是mid 
    int high, low, m;
    
    for(int i = 2; i <= L.length; ++i) {
    	
    	//L.r[0]是哨兵 
        L.r[0] = L.r[i];
        
        //low的初始值是1，low指向第一条记录 
        low = 1;
        
        //high的初始值为i-1，high指向最后一条记录 
		high = i - 1;
        
        //在r[low..high]中折半查找有序插入的位置
		while(low <= high){ 
            
            //折半
            m = (low + high) / 2;
            
            //待查找关键字的值小于mid指向的记录，说明插入点在低半区
            if(LT(L.r[0].key, L.r[m].key)) { 
			    
				//修改high指针到低半区去找 
				high = m - 1;
			}//if
			//待查找关键字的值大于mid指向的记录，说明插入点在高半区
            else {
            	
            	//修改low指针在高半区找 
			    low = m + 1;
			}//else
        }//while
        
        //记录后移,腾出插入位置 
        for(int j = i - 1; j >= high + 1; --j) {
		    L.r[j + 1] = L.r[j];
		}//for
		
		//插入记录 
        L.r[high + 1] = L.r[0];
   }//for
}//BinsertSort

//-------------------希尔排序-------------------------- 

/*
	函数：BInsertSort
	参数：SqList &L 顺序表引用
	      int dk 增量，控制跳跃程度 
	返回值：无
	作用：对顺序表L作一趟希尔插入排序，本算法是和一趟直接插入排序相比，
	      做了以下修改：
		  1.前后记录位置的增量是dk，而不是1 
		  2.r[0]只是暂存单元，不是哨兵，当j<=0时，插入位置已找到
*/
void ShellInsert(SqList &L, int dk){
	
	int j;
	
	//需将L.r[i]插入有序增量子表
	for(int i = dk + 1; i <= L.length; ++i) {
		
		if(LT(L.r[i].key, L.r[i-dk].key)){ 
	    	
			//暂存在L.r[0]
			L.r[0] = L.r[i];
			
			//记录后移，查找插入位置
	    	for(j = i - dk; j > 0 && LT(L.r[0].key, L.r[j].key); j -= dk) {
	        	L.r[j + dk] = L.r[j];
	    	}//for
	    	
	    	//插入
			L.r[j + dk] = L.r[0]; 
       }//if
	}//for
}//ShellInsert

/*
	函数：ShellSort
	参数：SqList &L 顺序表引用 
	      int dlta[] 增量数组
		  int t 增量数组中的元素个数（数组长度） 
	返回值：无
	作用：按增量序列dlta[0..t-1]对顺序表L作希尔排序
*/
void ShellSort(SqList &L, int dlta[], int t){
	
	for(int k = 0; k < t; ++k) { 
		
		//一趟增量为dlta[k]的插入排序
		ShellInsert(L, dlta[k]); 
	}//for    
}//ShellSort 

//-----------------起泡排序（改进） ------------------------------

/*
	函数：bubble_sort
	参数：SqList &L 顺序表引用 
	返回值：无
	作用：将a中整数序列排列成自小至大有序的序列(起泡排序)
*/ 
void bubble_sort(SqList &L){ 
	
    //辅助单元：用于保存交换值的临时变量 
    RedType temp;
    
    //冒泡排序主循环 
    for(int i = 1, change = TRUE; (i <= L.length - 1) && change; ++i){  
    	
    	//每趟冒泡开始前要初始化change的值为false
		//直到确实有交换必要时才更改此值 
		change = FALSE;
		
    	for(int j = 1; j <= L.length - i; ++j) { 
          	
          	//发现相邻两位置元素大小顺序不是我们想要的顺序
			//LT(L.r[j+1].key, L.r[j].key)相当于L.r[j+1].key > L.r[j].key
			//所以这样冒泡出来的结果是升序排列。
			//若想改为降序，只需要修改这里的比较条件就可以了 
			if(LT(L.r[j + 1].key, L.r[j].key)){
          		
          		//交换L.r[j]和L.r[j+1]
				temp = L.r[j];
            	L.r[j] = L.r[j + 1]; 
            	L.r[j + 1] = temp;   
            	
            	//由于这一趟发生了交换，记录可能只是移动了一个位置，
				//但还没有到达最终位置，则有可能还要继续交换（冒泡），
				//所以change要设置为true 
				change = TRUE;
        	}//if
        }//for 
    }//for
}//bubble_sort

//-----------------快速排序--------------------------------------- 

/*  Partition意为“分割 ” 
	函数：Partition
	参数：SqList &L 顺序表引用 
		  int low 低位指针，保存记录的下标
		  int high 高位指针，保存记录的下标 
	返回值：无
	作用：交换顺序表L中子表r[low..high]的记录，枢轴记录到位，
	      并返回其所在位置。此时在它之前（后）的记录均不大（小）于它。 
*/ 
int Partition(SqList &L, int low, int high) {
	
	//用子表的第一个记录作枢轴记录
	L.r[0] = L.r[low];

	//枢轴记录关键字
	KeyType pivotkey = L.r[low].key;
	 
	//从表的两端交替地向中间扫描，当low = high时，退出循环
	while(low < high){ 
		
		//高位指针high从后向前移动，直到遇到比枢轴记录 
		//关键字小的记录，此时high指向这条记录 
		while(low < high && L.r[high].key >= pivotkey) { 
		     --high;
		}//while
		
		//将比枢轴记录小的记录移到低端
		L.r[low] = L.r[high]; 
		
		//将high位置的记录的关键字修改为-1，-1表示空位置 
		L.r[high].key = -1;

		//低位指针low从前向后移动，直到遇到比枢轴记录 
		//关键字大的记录，此时high指向这条记录 
		while(low < high && L.r[low].key <= pivotkey) { 
			++low;
		}//while
		 
		//将比枢轴记录大的记录移到高端 
		L.r[high] = L.r[low];
		
		//将low位置的记录的关键字修改为-1，-1表示空位置 
		L.r[low].key = -1;

	}//while
	
	//枢轴记录到位
	L.r[low] = L.r[0];
	
	//返回枢轴位置 
	return low;
}//Partition

/*  
	函数：QSort
	参数：SqList &L 顺序表引用 
		  int low 低位指针，保存记录的下标
		  int high 高位指针，保存记录的下标 
	返回值：无
	作用：对顺序表L中的子序列L.r[low..high]作快速排序
*/ 
void QSort(SqList &L, int low, int high){
	
	//pivotloc记录了枢轴元素所在位置 
	int pivotloc; 
	
	//长度大于1 
	if(low < high){
		
		//将L.r[low..high]一分为二
		pivotloc = Partition(L, low, high);
		
		//对低子表递归排序，pivotloc是枢轴位置
		QSort(L, low, pivotloc - 1);
		
		//对高子表递归排序 
		QSort(L, pivotloc + 1, high);    
	}//if 
}//QSort 

/*  
	函数：QuickSort
	参数：SqList &L 顺序表引用 
	返回值：无
	作用：对顺序表L作快速排序
*/ 
void QuickSort(SqList &L){
	
	//对所有记录调用快速排序算法 
	QSort(L, 1, L.length); 
}//QuickSort
 
//-----------------选择排序------------------ 

/*  
	函数：SelectMinKey
	参数：SqList &L 顺序表引用 
		  int i 选择的起始位置 
	返回值：返回在L.r[i..L.length]中key最小的记录的序号
	作用：得到在L.r[i..L.length]中key最小的记录的序号
*/ 
int SelectMinKey(SqList L, int i){
	
	//临时变量，用于保存找到的最小值 
	KeyType min;
	
	//开始假设第i条记录的关键字为最小值 
	int k = i;
	
	//最小值为第i条记录的关键字的值 
	min = L.r[i].key;
	
	//从第i+1条记录开始到最后一条记录结束扫描
	//尝试找出比min更小的关键字 
	for(int j = i + 1; j <= L.length; j++) { 
		
		//找到更小的关键字
	    if(L.r[j].key<min){ 
			
			//k记录了新的最小值的下标 
	    	k = j;
	    	
	    	//min记录了新的最小值 
	    	min = L.r[j].key;
	    }//if
	}//for
	
	//扫描完成后，k记录了最小值所在下标，返回k即可 
	return k;
}//SelectMinKey

/*  
	函数：SelectSort
	参数：SqList &L 顺序表引用 
	返回值：无 
	作用：对顺序表L作简单选择排序
*/
void SelectSort(SqList &L){
	
	//辅助空间：临时变量，交换用
	RedType temp; 
	
	//j记录了在L.r[i..L.length]中选出的key最小的记录所在位置 
	int j;
	
	//选择第i小的记录，并交换到位
	for(int i = 1; i < L.length; ++i) {
		
		//在L.r[i..L.length]中选择key最小的记录
		j = SelectMinKey(L, i);
		
		//若最小值不在当前位置，则需要作交换操作
		//把最小值换过来 
		if(i != j){
			
			//交换操作 
			temp = L.r[i];
			
			//注意：结构体直接赋值相当于结构体各个分量都赋一次值 
			L.r[i] = L.r[j];
			L.r[j] = temp;
		}//if 
	}//for 
}//SelectSort

//-----------------归并排序---------------------- 

/*  
	函数：Merge
	参数：RedType SR[] 被归并数组 
	      RedType TR[] 存放归并结果的数组 
	      int i 记录下标，第一段归并序列的起始位置 
	      int m 记录下标，第一段归并序列的结束位置 
	      int n 记录下标，第二段归并序列的结束位置 
	返回值：无 
	作用：将有序的SR[i..m]和SR[m+1..n]归并为有序的TR[i..n]
	说明：RedType TR[]不应写成RedType &TR[]，因为引用型形参实际上
	      是取实参的地址，从而获得修改实参的能力。而这里给函数
		  传递的是实参数组的首地址，地址是无法再取地址的。 
		  实际上，把实参数组的首地址传给函数后，函数已经获得
		  修改实参数组元素的能力。
*/
void Merge(RedType SR[], RedType TR[], int i, int m, int n){ 
	
	//临时变量 
	int j, k;
	
	//将SR中的记录由小到大地并入TR 
	for(j = m + 1, k = i; i <= m && j <= n; ++k){
		
		//SR[i].key <= SR[j].key
		if(LQ(SR[i].key, SR[j].key)) {
		    TR[k] = SR[i++];
		}//if 
		else {
		    TR[k] = SR[j++];
		}//else 
	}//for
	
	//SR[i..m]还有剩余元素没有归并到TR数组中 
	if(i <= m){
		
		//将剩余的SR[i..m]复制到TR 
		for(int l = 0; l <= m - i; l++) { 
		   TR[k + l] = SR[i + l];
		}//for 
	}//if
	
	//SR[j..n]还有剩余元素没有归并到TR数组中
	if(j <= n){
		
		//将剩余的SR[j..n]复制到TR 
		for(int l = 0; l <= n - j; l++) {
		   TR[k + l] = SR[j + l];  
		}//for
	}//if 
}//Merge 

/*  
	函数：MSort
	参数：RedType SR[] 被归并数组 
	      RedType TR[] 存放归并结果的数组 
	      int s 归并开始位置 
	      int t 归并结束为止 
	返回值：无 
	作用：将SR[s..t]归并排序为TR1[s..t] 
*/
void MSort(RedType SR[], RedType TR1[], int s, int t){ 
	
	RedType TR2[MAXSIZE + 1];
	
	//只有一个元素 
	if(s == t) { 
	    TR1[s] = SR[s];
	}//if 
	else{
		
		//将SR[s..t]平分为SR[s..m]和SR[m+1..t] 
		//m记录了中间位置 
		int m = (s + t) / 2;
		
		//递归地将SR[s..m]归并为有序的TR2[s..m] 
		MSort(SR, TR2, s, m);
		
		//递归地将SR[m+1..t]归并为有序的TR2[m+1..t]
		MSort(SR, TR2, m + 1, t);
		
		//将TR2[s..m]和TR2[m+1..t]归并到TR1[s..t] 
		Merge(TR2, TR1, s, m, t);
	}//else
}//MSort

/*  
	函数：MergeSort
	参数：SqList &L 顺序表 
	返回值：无 
	作用：对顺序表L作归并排序
*/
void MergeSort(SqList &L){
	
	//对所有记录进行归并 
	MSort(L.r, L.r, 1, L.length); 
}//MergeSort

//--------------------------堆排序-------------------------
typedef SqList HeapType; // 堆采用顺序表存储表示

/*  
	函数：MergeSort
	参数：HeapType &H 堆的引用（其实就是个顺序表）
	      int s 堆在顺序表中的开始位置 
		  int m 堆在顺序表中的结束位置 
	返回值：无 
	作用：已知H.r[s..m]中记录的关键字除H.r[s].key之外均满足堆的定义，
	      调整H.r[s]的关键字，使H.r[s..m]成为一个大顶堆
		  (对其中记录的关键字而言)
*/
void HeapAdjust(HeapType &H, int s, int m) {
	
	//临时变量 
	RedType rc = H.r[s];
	
	//沿key较大的孩子结点向下筛选
	for(int j = 2 * s; j <= m; j *= 2) {
	
    	if(j < m && LT(H.r[j].key, H.r[j+1].key)) {
    		
    		//j为key较大的记录的下标
    		++j; 
    	}//if
		
		//rc应插入在位置s上
    	if(!LT(rc.key, H.r[j].key)) {
    		break; 
    	}//if 
    	
		H.r[s] = H.r[j];
		s = j;
	}//for 
	
	//插入
	H.r[s] = rc;
}//HeapAdjust

/*  
	函数：MergeSort
	参数：HeapType &H 堆的引用（其实就是个顺序表）
	返回值：无 
	作用：对顺序表H进行堆排序。
*/
void HeapSort(HeapType &H) {
	
	//临时变量t，用于交换 
	RedType t;
	
	//把H.r[1..H.length]建成大顶堆
	for(int i = H.length / 2; i > 0; --i) {
    	HeapAdjust(H, i, H.length);
	}//for
	
	//将H.r[1..i-1]重新调整为大顶堆
	for(int i = H.length; i > 1; --i) { 
    	
    	//将堆顶记录和当前未经排序子序列H.r[1..i]中最后一个记录相互交换
		t = H.r[1];
    	H.r[1] = H.r[i];
    	H.r[i] = t;
    	
    	//将H.r[1..i-1]重新调整为大顶堆
    	HeapAdjust(H,1,i-1);
	}//for 
}//HeapSort

//-----------------------对排序算法花费的时间做排序----------------------- 

/*  
	函数：result_sort
	参数：Result r[] 各个排序算法消耗时间的结果 
	返回值：无 
	作用：对排序算法消耗的时间再排序 
*/
void result_sort(Result r[]){ 

	int i = 0, j, flag = 1, n = SORTNUM - 1;
	
	Result temp;
	
	/*外循环控制排序的总趟数*/
	while(i < n && flag == 1){
		
		flag = 0;
		
		/*内循环控制一趟排序的进行*/
		for(j = n; j > i; j--) {
		
			/*相邻元素进行比较，若逆序就交换*/
			if(r[j].resultTime < r[j - 1].resultTime){  
				flag = 1;
				temp = r[j];
				r[j] = r[j-1];
				r[j-1] = temp;
			}//if
		}//for 
		
		i++;
	}//while 
}//result_sort

//***************************************主函数******************************************** 
int main(int argc,char *argv[]){ 
	printf("\n-------------------------------内排序算法效率比较------------------------------\n\n");  //打印菜单
    SqList L;
	int flag; 
	Result result[SORTNUM];
	float start,end; 
	InitList_Sq(L);  //初始化顺序表
	while(1){
	    printf("\n+------------------------------------------------------------------------------+\n");
	    printf("|                                 排序结果                                     |\n");
	    printf("+----------+------------------+------------------------------------------------+\n");
	    printf("|   排名   |   排序方法名称   |               排序花费时间（毫秒）             |\n"); 
	    printf("+----------+------------------+------------------------------------------------+\n"); 
	
		//执行各排序算法100次,记录下每次执行时间，求得平均值作为最终结果 
		result[0].name = "直接插入排序"; 
		for(int i = 0; i < 100; i++) {
	    	
	    	//生成指定数量的随机数并放置到顺序表中
			GenerateRandNumber(L);
			start = clock();
		    InsertSort(L);
		    end = clock();
		    result[0].resultTime += (end - start);
		}//for 	
		result[0].resultTime = result[0].resultTime / 100;
	    
	    result[1].name = "折半插入排序";
	    for(int i = 0; i < 100; i++) {
	    	
	    	//生成指定数量的随机数并放置到顺序表中
			GenerateRandNumber(L);
			start = clock();
		    BInsertSort(L);
		    end = clock();
		    result[1].resultTime += (end - start);
		}//for
	    result[1].resultTime = result[1].resultTime / 100; 
	    
	    result[2].name = "希尔排序";
	    for(int i = 0; i < 100; i++) {
	    	
	    	//生成指定数量的随机数并放置到顺序表中
			GenerateRandNumber(L);
	    	start = clock();
		    int dlta[3]={5,3,1};  //增量序列 
		    ShellSort(L,dlta,3);
		    end = clock();
		    result[2].resultTime += (end - start);
	    }//for 
	    result[2].resultTime = result[2].resultTime / 100;
	    
	    result[3].name = "起泡排序";
	    for(int i = 0; i < 100; i++) {
	    	
	    	//生成指定数量的随机数并放置到顺序表中
			GenerateRandNumber(L);
	    	start = clock();
		    bubble_sort(L);
		    end = clock();
		    result[3].resultTime += (end - start);
	    }//for 
	    result[3].resultTime = result[3].resultTime / 100;
	    
	    result[4].name = "快速排序";
	    for(int i = 0; i < 100; i++) {
	    	
	    	//生成指定数量的随机数并放置到顺序表中
			GenerateRandNumber(L);
	    	start = clock();
		    QuickSort(L);
		    end = clock();
		    result[4].resultTime += (end - start);
	    }//for 
	    result[4].resultTime = result[4].resultTime / 100;

		result[5].name = "选择排序";
		for(int i = 0; i < 100; i++) {
	    	
	    	//生成指定数量的随机数并放置到顺序表中
			GenerateRandNumber(L);
	    	start = clock();
		    SelectSort(L);
		    end = clock();
		    result[5].resultTime += (end - start);
	    }//for
		result[5].resultTime = result[5].resultTime / 100; 
	    
	    result[6].name = "归并排序";
	    for(int i = 0; i < 100; i++) {
	    	
	    	//生成指定数量的随机数并放置到顺序表中
			GenerateRandNumber(L);
	    	start = clock();
	    	MergeSort(L);
	    	end = clock();
	    	result[6].resultTime += (end - start);
	    }//for 
	    result[6].resultTime = result[6].resultTime / 100;
	    
	    result[7].name = "  堆排序";
	    for(int i = 0; i < 100; i++){
	    	
	    	//生成指定数量的随机数并放置到顺序表中
	    	GenerateRandNumber(L); 
	    	start = clock();
	    	MergeSort(L);
	    	end = clock();
	    	result[7].resultTime += (end - start);
	    }//for 
	    result[7].resultTime = result[7].resultTime / 100;
		 
	    //对排序算法花费的时间做排序 
	    result_sort(result);
	    
	    //输出结果
	    for(int i = 0; i < SORTNUM; i++){
	    	printf("| %4d     |   %12s   |         %20.0f                   |\n",i+1,result[i].name,result[i].resultTime); 
	    	printf("+----------+------------------+------------------------------------------------+\n");
	    }//for
	    
	    printf("想要再演示一次吗？输入N/n退出程序，否则输入任意字符按回车键再次演示");
	    getchar();
	    char ch = getchar();
		if(ch == 'N' || ch == 'n') {
			printf("\n谢谢使用，再见！\n");
			exit(0);
		}//if
		
		system("cls");
		fflush(stdin);
		
	}//while
		
	return 0;	
}//main

/* --------------------------------------运行结果------------------------------------- 

	
-------------------------------内排序算法效率比较------------------------------

您想给顺序表初始化多少个元素？（输入一个不超过10000的整数）  10000

+------------------------------------------------------------------------------+
|                                 排序结果                                     |
+----------+------------------+------------------------------------------------+
|   排名   |   排序方法名称   |               排序花费时间（毫秒）             |
+----------+------------------+------------------------------------------------+
|    1     |       快速排序   |                            1                   |
+----------+------------------+------------------------------------------------+
|    2     |         堆排序   |                            3                   |
+----------+------------------+------------------------------------------------+
|    3     |       归并排序   |                            3                   |
+----------+------------------+------------------------------------------------+
|    4     |       希尔排序   |                           17                   |
+----------+------------------+------------------------------------------------+
|    5     |   折半插入排序   |                           62                   |
+----------+------------------+------------------------------------------------+
|    6     |   直接插入排序   |                           65                   |
+----------+------------------+------------------------------------------------+
|    7     |       选择排序   |                          143                   |
+----------+------------------+------------------------------------------------+
|    8     |       起泡排序   |                          258                   |
+----------+------------------+------------------------------------------------+
想要再演示一次吗？输入N/n退出程序，否则输入任意字符按回车键再次演示
*/
