
//*********************引入头文件**********************************
#include <stdio.h>
#include <stdlib.h>  //使用了malloc、free函数 

//********************自定义符号常量******************************** 

#define OVERFLOW -2         //内存溢出错误常量
#define ILLEGAL -1          //非法操作错误常量 
#define OK 1                //表示操作正确的常量 
#define ERROR 0             //表示操作错误的常量
#define LIST_INIT_SIZE 100  //线性表存储空间的初始分配量
#define EQ(a,b) ((a)==(b))  //相等 
#define LT(a,b) ((a)< (b))  //小与
#define LQ(a,b) ((a)<= (b)) //小与等于 

//*********************自定义数据类型*******************************

typedef int Status;   //状态码类型为int  
typedef int KeyType;  //关键字类型为int 
typedef struct{       //元素类型 
	
	//关键字域 
	KeyType key;
}ElemType; 

//------------------静态查找表的顺序存储结构------------------- 
typedef struct{
	
	//数据元素存储空间基址，建表时按实际长度分配，0号单元留空
	ElemType *elem; 
	
	//表长度，表中记录数 
	int length;
}SSTable;

//**************************顺序表的主要操作************************* 

//1.--------------------静态查找表的初始化操作---------------------------- 

/*
	函数：InitSSTable_Seq
	参数：SSTable &ST 静态查找表引用 
	返回值：状态码，操作成功返回OK 
	作用：初始化静态查找表,构造一个空静态查找表
*/
Status InitSSTable_Seq(SSTable &ST){

	//申请查找表内存空间，0号单元留空。
	ST.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType) + 1); 
	
	//若内存分配失败，退出程序
	if(!ST.elem){  
		printf("内存申请失败！\n");   
		exit(OVERFLOW); 
	}//if
	
	//设置静态查找表ST的长度为0
	ST.length = 0;
	
	//操作成功 
	return OK;    
}//InitSSTable_Seq

//2.----------------------输入静态查找表元素的操作-------------------

/*
	函数：SSTableInput_Seq
	参数：SSTable &ST 静态查找表引用 
	返回值：状态码，操作成功返回OK 
	作用：顺序表插入元素的函数
*/
Status SSTableInput_Seq(SSTable &ST) {
	
	//n代表元素的个数,i用作循环变量 
    int n, i;
	
	//直到用户输入正确为止 
	while(1){
		
		//先确定元素的个数
    	printf("->您想输入几个元素，请输入个数，最多不可以超过100  "); 
    	scanf("%d", &n);
    	
    	//检查元素个数n是否合法 
    	if(n < 1 || n > 100) { 
    		
    		//如果输入非法数据，就提醒用户重新输入
        	printf("您的输入非法，请重新输入！！！\n");
        }//if
		
		//若输入合法则退出循环 
		break;
    }//while
    
    //输入静态查找表数据
    printf("请输入静态查找表ST的元素，中间用空格隔开，最多不可以超过100个元素\n");
	for(i = 1; i <= n; i++) { 
		
		//初始化每一个元素
		scanf("%d", &ST.elem[i].key); 
    }//for 
    
    //静态查找表个数为元素个数n 
	ST.length = n;
	
	//操作成功 
	return OK;
}//SSTableInput_Seq
 
//3.------------------判断静态查找表是否为空-------------------

/*
	函数：SSTableEmpty_Seq
	参数：SSTable ST 静态查找表ST 
	返回值：状态码，若静态查找表为空表返回TRUE，否则返回FALSE 
	作用：判断静态查找表是否为空 
*/
Status SSTableEmpty_Seq(SSTable ST){
    
    //查看表长是否为0 
	return ST.length == 0;
}//SSTableEmpty_Seq

//4.----------------------静态查找表的输出操作------------------

/*
	函数：Print
	参数：KeyType e 关键字的值e 
	返回值：状态码，操作成功返回OK，否则返回ERROR 
	作用：元素访问函数
*/
Status Print(KeyType e){

	//采用控制台输出方式打印关键字e 
	printf("%3d ", e);
	
	//操作成功 
	return OK;
}//Print

/*
	函数：SSTableTraverse_Seq
	参数：SSTable ST 静态查找表ST 
		  Status(* Visit)(KeyType) 函数指针，指向元素访问函数 
	返回值：状态码，操作成功返回OK，否则返回ERROR 
	作用：遍历静态查找表函数
*/
Status SSTableTraverse_Seq(SSTable ST, Status(* Visit)(KeyType)){
	
	//访问静态查找表中每一个元素一次且仅一次 
	for(int i = 1; i <= ST.length; ++i) { 
		
		//一旦访问失败则遍历失败
		//if(!Visit(ST.elem[i].key)) <=> if(Visit(ST.elem[i].key) == ERROR)
		if(!Visit(ST.elem[i].key)) {
		    return ERROR;
		}//if 
	}//for 
	
	//输出换行使结果美观 
	printf("\n");
	
	//操作成功 
	return OK;
}//SSTableTraverse_Seq



//5.----------------------顺序表的顺序查找算法------------------ 

/*
	函数：SSTableTraverse_Seq
	参数：SSTable ST 静态查找表ST 
		  KeyType key 被查找的关键字 
	返回值：若找到，则函数值为该元素在表中的位置，否则为0
	作用：在顺序表ST中顺序查找其关键字等于key的数据元素。
*/
int Search_Seq(SSTable ST, KeyType key){
	
	//i是循环变量，存储了关键字在表中的位置 
	int i; 
	
	//0号单元不放被查找数据元素，放关键字，作用相当于"哨兵",
	//好处在于不必时时提防数组越界问题 
	ST.elem[0].key = key;
	
	//从后向前查找，直至找到元素或遇到哨兵为止 
	for(i = ST.length; !EQ(ST.elem[i].key, key); --i);
	
	//返回关键字在表中的位置i 
	return i;  
}//Search_Seq 

//6.-----------------------静态查找表的排序操作-------------------

/*
	函数：SortSSTable_Seq
	参数：SSTable &ST 静态查找表引用 
	返回值：若找到，则函数值为该元素在表中的位置，否则为0
	作用：排序顺序表中元素,使顺序表变为有序表，以便于对有序表进行查找 
*/
Status SortSSTable_Seq(SSTable &ST) {
    //将线性表中的元素排序,使用冒泡法，
	/*传统冒泡排序中每一趟排序操作只能找到一个最大值或最小值,
	  我们考虑利用在每趟排序中进行正向和反向两遍冒泡的方法
	  一次可以得到两个最终值(最大者和最小者),从而使排序趟数几乎减少了一半*/ 
	
	//对空表做排序没意义 
	if(SSTableEmpty_Seq(ST)) { 
		return ERROR; 
	}//if 
	
	int low = 1, high = ST.length, tmp, j;    
    
	while (low < high) {
		
		//正向冒泡,找到最大者 
        for (j = low; j < high; ++j) { 
            if (ST.elem[j].key > ST.elem[j + 1].key){  
                tmp = ST.elem[j].key; 
				ST.elem[j].key = ST.elem[j + 1].key;
				ST.elem[j + 1].key = tmp;  
            }//if   
        }//for 
        
        //修改high值, 前移一位
        --high;
        
        //反向冒泡,找到最小者
        for (j = high; j > low; --j) {
            if (ST.elem[j].key < ST.elem[j - 1].key) {  
                tmp = ST.elem[j].key; 
				ST.elem[j].key = ST.elem[j - 1].key;
				ST.elem[j - 1].key = tmp;  
            }//if
    	}//for
		
		//修改low值,后移一位 
        ++low; 
    }//while  
} //SortSSTable_Seq

//7.----------------------有序表的折半查找算法------------------

/*
	函数：Search_Bin
	参数：SSTable ST 静态查找表ST 
	返回值：若找到，则函数值为该元素在表中的位置，否则为0 
	作用：在有序表ST中折半查找其关键字等于key的数据元素
*/
int Search_Bin(SSTable ST, KeyType key){
	
	//置区间初值
	int low = 1, high = ST.length, mid;
	
	//当low > high时查找结束 
	while(low <= high){
		
		//计算出mid 
		mid = (low + high) / 2;
		
		//找到待查元素
		if(EQ(key, ST.elem[mid].key)) {
		    return mid;
		}//if
		//继续在前半区间进行查找 
	    else if(LT(key,ST.elem[mid].key)) {
	        high = mid - 1;
		}//else if 
	    //继续在后半区间进行查找
		else { 
	        low = mid + 1;
		}//else 
	}//while 
	
	//顺序表中不存在待查元素
	return 0; 
}//Search_Bin 

//8.-----------------------静态查找表的销毁操作--------------------

/*
	函数：DestorySSTable_Seq
	参数：SSTable &ST 静态查找表引用 
	返回值：无 
	作用：销毁静态查找表ST
*/
void DestorySSTable_Seq(SSTable &ST){
    
	//释放静态查找表内存空间 
	free(ST.elem);
	
	//指针置空 
	ST.elem = NULL;
	
	printf("内存空间释放成功!\n");  
} //DestorySSTable_Seq

//***************************************主函数******************************************** 
int main(int argc,char *argv[]){ 

	//声明顺序查找表ST 
    SSTable ST; 
	
	//关键字         
	KeyType key;
	
	//状态标志
	Status flag;
	 
	printf("\n***************************顺序表及有序表查找算法测试***************************\n");
	
	printf("->创建一个静态查找（顺序）表，请按要求进行操作\n"); 
	InitSSTable_Seq(ST);
	SSTableInput_Seq(ST);
	printf("->您创建的静态查找表包含的所有元素如下：\n");
	SSTableTraverse_Seq(ST, Print);
	
	printf("->请输入您想在顺序表中查找的元素：\n");
	scanf("%d", &key);
	flag=Search_Seq(ST, key); 
	if(!flag) { 
	   printf("查找失败！\n"); 
	}//if 
	else {
	   printf("查找成功！该元素在表中的位置为%d,表中该位置元素值为%d。\n",
	   		flag, ST.elem[flag].key);
	}//else
	 
	printf("对顺序表排序，准备进行有序表查找。\n");
	SortSSTable_Seq(ST);
	printf("->排序后顺序表变为有序表，表中所有元素依次是：\n");
	SSTableTraverse_Seq(ST, Print);
	
	printf("->请输入您想在有序表中查找的元素：\n");
	scanf("%d", &key);
	flag=Search_Bin(ST, key); 
	if(!flag) {
	   printf("查找失败！\n"); 
	}//if 
	else {
	   printf("查找成功！该元素在表中的位置为%d,表中该位置元素值为%d。\n",
	   		flag, ST.elem[flag].key);
	}//else
	 
	printf("->销毁静态查找表ST：");
	DestorySSTable_Seq(ST); 
	
	return 0;	
}//main 

/*
	书上P219页 

***************************顺序表及有序表查找算法测试***************************
->创建一个静态查找（顺序）表，请按要求进行操作
->您想输入几个元素，请输入个数，最多不可以超过100  11
请输入静态查找表ST的元素，中间用空格隔开，最多不可以超过100个元素
05 13 19 21 37 56 64 75 80 88 92
->您创建的静态查找表包含的所有元素如下：
  5  13  19  21  37  56  64  75  80  88  92
->请输入您想在顺序表中查找的元素：
12
查找失败！
对顺序表排序，准备进行有序表查找。
->排序后顺序表变为有序表，表中所有元素依次是：
  5  13  19  21  37  56  64  75  80  88  92
->请输入您想在有序表中查找的元素：
88
查找成功！该元素在表中的位置为10,表中该位置元素值为88。
->销毁静态查找表ST：内存空间释放成功!

--------------------------------
Process exited with return value 0
Press any key to continue . . .

*/
