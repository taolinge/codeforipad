
//*************************引入头文件****************************
#include <stdio.h>
#include <stdlib.h>   

//************************自定义符号常量************************* 

#define OVERFLOW -2         //内存溢出错误常量
#define ILLEGAL -1          //非法操作错误常量 
#define OK 1                //表示操作正确的常量 
#define ERROR 0             //表示操作错误的常量
#define TRUE 1              //表示逻辑正确的常量 
#define FALSE 0             //表示逻辑错误的常量
#define MAXSIZE 20          //一个用作示例的小顺序表的最大长度 
#define EQ(a,b) ((a)==(b))  //相等 
#define LT(a,b) ((a)< (b))  //小与
#define LQ(a,b) ((a)<= (b)) //小与等于   

//**********************自定义数据类型************************

typedef int Status;   //状态标志  
typedef int KeyType;  //定义关键字类型为整数类型
typedef int InfoType; //信息类型
 
typedef struct{       //元素类型 
	KeyType key;  //关键字域
	InfoType otherinfo;  //其他数据项（记录该数据项的初始位置） 
}RedType;   //记录类型 

typedef struct{
	RedType r[MAXSIZE + 1];  //r[0]闲置或用作哨兵单元
	int length;  //顺序表长度 
}SqList; //顺序表类型 

//**********************顺序表的主要操作********************** 

//-------------------1.初始化顺序表---------------------- 

/*
	函数：InitList_Sq
	参数：SqList &L 顺序表引用 
	返回值：状态码，操作成功返回OK 
	作用：根据用户输入创建一棵二叉排序树 
*/
Status InitList_Sq(SqList &L){
	
	printf("您想给顺序表初始化多少个元素？（输入一个不超过20的整数）  ");
	scanf("%d", &L.length);
	
	printf("请输入顺序表的所有元素（用空格隔开）\n");
	for(int i = 1; i <= L.length; ++i) { 
		scanf("%d", &L.r[i].key);
		
		//记录元素的初始位置 
		L.r[i].otherinfo = i;
	}//for 
	
	//操作成功 
	return OK;
}//InitList_Sq 

/*
	函数：CopyList
	参数：SqList L1 复制源
	      SqList &L2 目的地 
	返回值：状态码，操作成功返回OK 
	作用：表的复制和恢复（便于后续演示） 
*/
Status CopyList(SqList L1, SqList &L2){
	
    //将L1复制到L2 
    L2.length = L1.length; 
	
	for(int i = 0; i <= L1.length; ++i) {
		L2.r[i] = L1.r[i];
	}//for 
	
	//操作成功 
	return OK;
}//CopyList

//-----------------------2.遍历顺序表-----------------------

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

//------------------------3.排序算法-----------------------

//-------------------直接插入排序----------------------- 

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
	printf("->本趟排序枢轴记录是:%d\n", L.r[0]); 
	
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
		printf("high移动到%d,交换low = %d处的记录为%d：(-1表示该位置为空)\n",
			high, low, L.r[low]); 
		
		//遍历顺序表，查看交换后的顺序表记录位置的变化 
		ListTraverse_Sq(L, Print);
		
		//低位指针low从前向后移动，直到遇到比枢轴记录 
		//关键字大的记录，此时high指向这条记录 
		while(low < high && L.r[low].key <= pivotkey) { 
			++low;
		}//while
		 
		//将比枢轴记录大的记录移到高端 
		L.r[high] = L.r[low];
		
		//将low位置的记录的关键字修改为-1，-1表示空位置 
		L.r[low].key = -1;
		
		if(low != high) {
			printf("low 移动到%d,交换high = %d处的记录为%d：(-1表示该位置为空)\n"
				, low, high, L.r[high]);
			
			//查看顺序表在元素交换后的变化 
			ListTraverse_Sq(L,Print);
		}//if 
	}//while
	
	//枢轴记录到位
	L.r[low] = L.r[0];
	
	//输出排序后的结果 
	printf("->本趟排序完成后：\n"); 
	ListTraverse_Sq(L, Print);
	
	//输出换行使结果美观 
	printf("\n");
	
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

//************************主函数**************************** 
int main(int argc,char *argv[]){ 

    SqList L1, L2;
	int flag; 
    char MainMenu[]=  "*********************************内排序算法测试*********************************\n"
	                  "\t\t\t\t1.初始化顺序表\n"
	                  "\t\t\t\t2.遍历顺序表\n"
					  "\t\t\t\t3.直接插入排序\n" 
	                  "\t\t\t\t4.折半插入排序\n"
					  "\t\t\t\t5.希尔排序\n" 
	                  "\t\t\t\t6.起泡（改进）排序\n"
	                  "\t\t\t\t7.快速排序\n"
	                  "\t\t\t\t8.选择排序\n"
	                  "\t\t\t\t9.归并排序\n"
	                  "\t\t\t\t10.堆排序\n"
	                  "\t\t\t\t11.还原顺序表的原始顺序\n"
	                  "\t\t\t\t12.退出程序\n"
	                  "请选择您需要的功能："; 
	while(1){
		printf(MainMenu);  //打印菜单 
		switch(scanf("%d", &flag), flag){
			
			//初始化 
			case 1:{
				InitList_Sq(L1);  //初始化顺序表 
                CopyList(L1, L2);  //保存一个L1的备份，用于后续演示
				break;
			}//case
			
			//遍历测试块
			case 2:{
				printf("遍历顺序表([]内数字为其所在位置)：\n");
                ListTraverse_Sq(L1, Print);
				break;
			}//case
			
			//直接插入排序测试块 
			case 3:{
				printf("排序前对顺序表进行遍历([]内数字为其所在位置)：\n");
	            ListTraverse_Sq(L1, Print); 
                InsertSort(L1);
                printf("直接插入排序后遍历顺序表([]内数字为其所在位置)：\n");   
                ListTraverse_Sq(L1, Print);
				break;
			}//case
			
			//折半插入排序测试块
			case 4:{
				printf("\n排序前对顺序表进行遍历([]内数字为其所在位置)：\n");
	            ListTraverse_Sq(L1, Print); 
                BInsertSort(L1);
                printf("折半插入排序后遍历顺序表([]内数字为其所在位置)：\n"); 
                ListTraverse_Sq(L1, Print);
				break;
			}//case
			
			//希尔排序测试块 
			case 5:{
				
				//增量序列
				int dlta[3] = {5, 3, 1}; 
                printf("\n排序前对顺序表进行遍历([]内数字为其所在位置)：\n");
	            ListTraverse_Sq(L1, Print); 
                ShellSort(L1, dlta, 3);
                printf("希尔排序后遍历顺序表([]内数字为其所在位置)：\n");
                ListTraverse_Sq(L1, Print);
				break;
			}//case
			
			//起泡排序（改进）测试块 
			case 6:{
				printf("\n排序前对顺序表进行遍历([]内数字为其所在位置)：\n");
	            ListTraverse_Sq(L1, Print); 
                bubble_sort(L1);
                printf("起泡排序后遍历顺序表([]内数字为其所在位置)：\n");                  
                ListTraverse_Sq(L1, Print);
				break;
			}//case
			
			//快速排序测试块
			case 7:{
				printf("\n排序前对顺序表进行遍历([]内数字为其所在位置)：\n");
	            ListTraverse_Sq(L1, Print); 
                QuickSort(L1);
                printf("快速排序后遍历顺序表([]内数字为其所在位置)：\n");                   
                ListTraverse_Sq(L1, Print);
				break;
			}//case
			
			//选择排序测试块
			case 8:{
				printf("\n排序前对顺序表进行遍历([]内数字为其所在位置)：\n");
	            ListTraverse_Sq(L1, Print); 
                SelectSort(L1);
                printf("选择排序后遍历顺序表([]内数字为其所在位置)：\n");
                ListTraverse_Sq(L1, Print);
				break;
			}//case
			
			//归并排序测试块
			case 9:{
				printf("\n排序前对顺序表进行遍历([]内数字为其所在位置)：\n");
	            ListTraverse_Sq(L1, Print); 
                MergeSort(L1);
                printf("归并排序后遍历顺序表([]内数字为其所在位置)：\n");
                ListTraverse_Sq(L1, Print);
				break;
			}//case
			
			//堆排序测试块
			case 10:{
				printf("\n排序前对顺序表进行遍历([]内数字为其所在位置)：\n");
	            ListTraverse_Sq(L1, Print); 
                HeapSort(L1);
                printf("堆排序后遍历顺序表([]内数字为其所在位置)：\n");
                ListTraverse_Sq(L1, Print);
				break;
			}//case
			
			//恢复L1内容
			case 11:{
				CopyList(L2, L1);
				break;
			}//case
			
			//退出 
			case 12:{
				exit(0);
				break;
			}//case
			
			//非法 
			default:{
				printf("输入非法！\n");
			}//default
		}//switch
		system("PAUSE"); 
		system("cls");
	}//while
	return 0;	
}

/*  -----------------------------------运行结果--------------------------------------
 
	*********************************内排序算法测试*********************************
	                                1.初始化顺序表
	                                2.遍历顺序表
	                                3.直接插入排序
	                                4.折半插入排序
	                                5.希尔排序
	                                6.起泡（改进）排序
	                                7.快速排序
	                                8.选择排序
	                                9.归并排序
	                                10.堆排序
	                                11.还原顺序表的原始顺序
	                                12.退出程序
	请选择您需要的功能：1
	您想给顺序表初始化多少个元素？（输入一个不超过20的整数）  10
	请输入顺序表的所有元素（用空格隔开）
	2 45 8 6 3 12 7 56 4 29
	请按任意键继续. . .
	
	请选择您需要的功能：2
	遍历顺序表([]内数字为其所在位置)：
	2[1] 45[2] 8[3] 6[4] 3[5] 12[6] 7[7] 56[8] 4[9] 29[10]
	请按任意键继续. . .
	
	请选择您需要的功能：3
	排序前对顺序表进行遍历([]内数字为其所在位置)：
	2[1] 45[2] 8[3] 6[4] 3[5] 12[6] 7[7] 56[8] 4[9] 29[10]
	直接插入排序后遍历顺序表([]内数字为其所在位置)：
	2[1] 3[5] 4[9] 6[4] 7[7] 8[3] 12[6] 29[10] 45[2] 56[8]
	请按任意键继续. . .
		
	请选择您需要的功能：11
	请按任意键继续. . .
	
	请选择您需要的功能：4
	排序前对顺序表进行遍历([]内数字为其所在位置)：
	2[1] 45[2] 8[3] 6[4] 3[5] 12[6] 7[7] 56[8] 4[9] 29[10]
	折半插入排序后遍历顺序表([]内数字为其所在位置)：
	2[1] 3[5] 4[9] 6[4] 7[7] 8[3] 12[6] 29[10] 45[2] 56[8]
	请按任意键继续. . .
	
	请选择您需要的功能：11
	请按任意键继续. . .
	
	请选择您需要的功能：5
	排序前对顺序表进行遍历([]内数字为其所在位置)：
	2[1] 45[2] 8[3] 6[4] 3[5] 12[6] 7[7] 56[8] 4[9] 29[10]
	希尔排序后遍历顺序表([]内数字为其所在位置)：
	2[1] 3[5] 4[9] 6[4] 7[7] 8[3] 12[6] 29[10] 45[2] 56[8]
	请按任意键继续. . .
	
	请选择您需要的功能：11
	请按任意键继续. . .
	
	请选择您需要的功能：6
	排序前对顺序表进行遍历([]内数字为其所在位置)：
	2[1] 45[2] 8[3] 6[4] 3[5] 12[6] 7[7] 56[8] 4[9] 29[10]
	起泡排序后遍历顺序表([]内数字为其所在位置)：
	2[1] 3[5] 4[9] 6[4] 7[7] 8[3] 12[6] 29[10] 45[2] 56[8]
	请按任意键继续. . .
	
	请选择您需要的功能：11
	请按任意键继续. . .
	
	请选择您需要的功能：7

	排序前对顺序表进行遍历([]内数字为其所在位置)：
	2[1] 45[2] 8[3] 6[4] 3[5] 12[6] 7[7] 56[8] 4[9] 29[10]
	->本趟排序枢轴记录是:2
	high移动到1,交换low = 1处的记录为-1：(-1表示该位置为空)
	-1[1] 45[2] 8[3] 6[4] 3[5] 12[6] 7[7] 56[8] 4[9] 29[10]
	->本趟排序完成后：
	2[1] 45[2] 8[3] 6[4] 3[5] 12[6] 7[7] 56[8] 4[9] 29[10]
	
	->本趟排序枢轴记录是:45
	high移动到10,交换low = 2处的记录为29：(-1表示该位置为空)
	2[1] 29[10] 8[3] 6[4] 3[5] 12[6] 7[7] 56[8] 4[9] -1[10]
	low 移动到8,交换high = 10处的记录为56：(-1表示该位置为空)
	2[1] 29[10] 8[3] 6[4] 3[5] 12[6] 7[7] -1[8] 4[9] 56[8]
	high移动到9,交换low = 8处的记录为4：(-1表示该位置为空)
	2[1] 29[10] 8[3] 6[4] 3[5] 12[6] 7[7] 4[9] -1[9] 56[8]
	->本趟排序完成后：
	2[1] 29[10] 8[3] 6[4] 3[5] 12[6] 7[7] 4[9] 45[2] 56[8]
	
	->本趟排序枢轴记录是:29
	high移动到8,交换low = 2处的记录为4：(-1表示该位置为空)
	2[1] 4[9] 8[3] 6[4] 3[5] 12[6] 7[7] -1[9] 45[2] 56[8]
	->本趟排序完成后：
	2[1] 4[9] 8[3] 6[4] 3[5] 12[6] 7[7] 29[10] 45[2] 56[8]
	
	->本趟排序枢轴记录是:4
	high移动到5,交换low = 2处的记录为3：(-1表示该位置为空)
	2[1] 3[5] 8[3] 6[4] -1[5] 12[6] 7[7] 29[10] 45[2] 56[8]
	low 移动到3,交换high = 5处的记录为8：(-1表示该位置为空)
	2[1] 3[5] -1[3] 6[4] 8[3] 12[6] 7[7] 29[10] 45[2] 56[8]
	high移动到3,交换low = 3处的记录为-1：(-1表示该位置为空)
	2[1] 3[5] -1[3] 6[4] 8[3] 12[6] 7[7] 29[10] 45[2] 56[8]
	->本趟排序完成后：
	2[1] 3[5] 4[9] 6[4] 8[3] 12[6] 7[7] 29[10] 45[2] 56[8]
	
	->本趟排序枢轴记录是:6
	high移动到4,交换low = 4处的记录为-1：(-1表示该位置为空)
	2[1] 3[5] 4[9] -1[4] 8[3] 12[6] 7[7] 29[10] 45[2] 56[8]
	->本趟排序完成后：
	2[1] 3[5] 4[9] 6[4] 8[3] 12[6] 7[7] 29[10] 45[2] 56[8]
	
	->本趟排序枢轴记录是:8
	high移动到7,交换low = 5处的记录为7：(-1表示该位置为空)
	2[1] 3[5] 4[9] 6[4] 7[7] 12[6] -1[7] 29[10] 45[2] 56[8]
	low 移动到6,交换high = 7处的记录为12：(-1表示该位置为空)
	2[1] 3[5] 4[9] 6[4] 7[7] -1[6] 12[6] 29[10] 45[2] 56[8]
	high移动到6,交换low = 6处的记录为-1：(-1表示该位置为空)
	2[1] 3[5] 4[9] 6[4] 7[7] -1[6] 12[6] 29[10] 45[2] 56[8]
	->本趟排序完成后：
	2[1] 3[5] 4[9] 6[4] 7[7] 8[3] 12[6] 29[10] 45[2] 56[8]
	
	快速排序后遍历顺序表([]内数字为其所在位置)：
	2[1] 3[5] 4[9] 6[4] 7[7] 8[3] 12[6] 29[10] 45[2] 56[8]
	请按任意键继续. . .
	
	请选择您需要的功能：11
	请按任意键继续. . .
	
	请选择您需要的功能：8
	排序前对顺序表进行遍历([]内数字为其所在位置)：
	2[1] 45[2] 8[3] 6[4] 3[5] 12[6] 7[7] 56[8] 4[9] 29[10]
	选择排序后遍历顺序表([]内数字为其所在位置)：
	2[1] 3[5] 4[9] 6[4] 7[7] 8[3] 12[6] 29[10] 45[2] 56[8]
	请按任意键继续. . .
	
	请选择您需要的功能：11
	请按任意键继续. . .
		
	请选择您需要的功能：9
	排序前对顺序表进行遍历([]内数字为其所在位置)：
	2[1] 29[10] 4[9] 3[5] 6[4] 8[3] 7[7] 45[2] 12[6] 56[8]
	归并排序后遍历顺序表([]内数字为其所在位置)：
	2[1] 3[5] 4[9] 6[4] 7[7] 8[3] 12[6] 29[10] 45[2] 56[8]
	请按任意键继续. . .	
	
	请选择您需要的功能：11
	请按任意键继续. . .
	
	请选择您需要的功能：10

	排序前对顺序表进行遍历([]内数字为其所在位置)：
	2[1] 45[2] 8[3] 6[4] 3[5] 12[6] 7[7] 56[8] 4[9] 29[10]
	堆排序后遍历顺序表([]内数字为其所在位置)：
	2[1] 3[5] 4[9] 6[4] 7[7] 8[3] 12[6] 29[10] 45[2] 56[8]
	请按任意键继续. . .
	
	请选择您需要的功能：12
	
	--------------------------------
	Process exited with return value 0
	Press any key to continue . . .	
		
*/ 
