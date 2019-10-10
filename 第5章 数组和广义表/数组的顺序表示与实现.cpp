
/* -----------------------数组的抽象数据类型---------------------------- 

ADT Array{
	数据对象：ji = 0, …, bi-1,   i = 1,2,…,n,
	D = {aj1j2…jn|n(>0)称为数据的维数, bi是数组第i维的长度，
		ji是数组元素的第i维下标，aj1j2…jn ∈ ElemSet}
	数据关系：R = {R1, R2, … ,Rn}
	    Ri = {<aj1…ji…jn， aj1…ji+1…jn >|   
	        0<=jk<=bk-1, 0<=k<=n，且k!=i,
	        0<=ji<=bi-2,
	        aj1…ji…jn， aj1…ji+1…jn ∈ D,  i = 1,2,…,n }
	基本操作：
		InitArray(&A, n, bound1, … , boundn)
			操作结果：若维数 n 和各维长度合法，则构造相应的数组A，并返回OK。
		DestroyArray(&A)
	    	操作结果：销毁数组A；
		Value(A, &e, index1, … , indexn)
	    	初始条件：A是n维数组，e为元素变量，随后是n个下标值。
  			操作结果：若各下标不超界，则e赋值为所指定的A的元素值，并返回OK。
		Assign(&A, e, index1, … , indexn)
	    	初始条件：A是n维数组，e为元素变量，随后是n 个下标值。
			操作结果：若下标不超界，则将e的值赋给所指定的A的元素，并返回OK。
} ADT Array
*/

//---------------------- 相关资料 —可变参数 --------------------------------
/* 引用位置：http://blog.csdn.net/ddppqq/article/details/17332161                             
                                 用 VA_LIST 解决C语言中的变参问题
VA_LIST的用法：
函数原型： 
     void va_start( va_list arg_ptr, prev_param ); 
     type va_arg( va_list arg_ptr, type ); 
     void va_end( va_list arg_ptr ); 
     va在这里是variable-argument(可变参数)的意思. 
使用步骤     
 （1）首先在函数里定义一具VA_LIST型的变量，这个变量是指向参数的指针
 （2）然后用VA_START宏初始化变量刚定义的VA_LIST变量，
      这个宏的第二个参数是第一个可变参数的前一个参数，是一个固定的参数。
 （3）然后用VA_ARG返回可变的参数，VA_ARG的第二个参数是你要返回的参数的类型。
 （4）最后用VA_END宏结束可变参数的获取。然后你就可以在函数里使用第二个参数了。
      如果函数有多个可变参数的，依次调用VA_ARG获取各个参数。

使用VA_LIST应该注意的问题：
（1）因为va_start, va_arg, va_end等定义成宏,所以它显得很愚蠢,
     可变参数的类型和个数完全在该函数中由程序代码控制,
	 它并不能智能地识别不同参数的个数和类型. 也就是说,你想实现
	 智能识别可变参数的话是要通过在自己的程序里作判断来实现的.
（2）另外有一个问题,因为编译器对可变参数的函数的原型检查不够严格,
     对编程查错不利.不利于我们写出高质量的代码。

小结：可变参数的函数原理其实很简单，而VA系列是以宏定义来定义的，
      实现跟堆栈相关。我们写一个可变函数的C函数时，有利也有弊,
	  所以在不必要的场合，我们无需用到可变参数，
	  如果在C++里，我们应该利用C++多态性来实现可变参数的功能，
	  尽量避免用C语言的方式来实现。

举例： 下面我们写一个简单的可变参数的函数,该函数至少有一个整数参数,
       第二个参数也是整数,是可选的.函数只是打印这两个参数的值. 
       void simple_va_fun(int i, ...){ 
           va_list arg_ptr; 
           int j=0; 
           va_start(arg_ptr, i); 
           j=va_arg(arg_ptr, int); 
           va_end(arg_ptr); 
           printf("%d %d\n", i, j); 
           return; 
       } 
       我们可以在我们的头文件中这样声明我们的函数: 
           extern void simple_va_fun(int i, ...); 
       我们在程序中可以这样调用: 
           simple_va_fun(100); 
           simple_va_fun(100,200); 
           
	从这个函数的实现可以看到,我们使用可变参数应该有以下步骤: 
       1)首先在函数里定义一个va_list型的变量,这里是arg_ptr,
	     这个变量是指向参数的指针. 
       2)用va_start宏初始化变量arg_ptr,这个宏的第二个参数是
	     第一个可变参数的前一个参数,是一个固定的参数. 
       3)用va_arg返回可变的参数,并赋值给整数j. va_arg的第二个
	     参数是你要返回的参数的类型,这里是int型. 
       4)用va_end宏结束可变参数的获取.然后你就可以在函数里使用第二个参数了.
         如果函数有多个可变参数的,依次调用va_arg获取各个参数. 
*/ 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>引入头文件<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <stdio.h>       //使用了标准库函数 
#include <stdlib.h>      //使用了动态内存分配函数
#include <stdarg.h>      //标准头文件，提供宏va_start、va_arg和va_end,用于存取变长参数表
#include <math.h>        //使用了其中的两个符号常量OVERFLOW和UNDERFLOW 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>自定义符号常量<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 
 
#define OK 1                 //表示操作正确的常量 
#define ERROR 0              //表示操作错误的常量
#define TRUE 1               //表示逻辑真的常量 
#define FALSE 0              //表示逻辑假的常量

#define MAX_ARRAY_DIM 8      //假设数组维数最大值为8

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>自定义数据类型<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef int  Status;      //状态标志 
typedef int  ElemType;    //元素类型 

//---------------------数组的顺序存储表示---------------------- 
typedef struct{
	ElemType * base;      //数组元素基址，由InitArray分配
	//这个指针指向的内存空间用于存放数组中的元素。
	//其大小由数组的维数和维界决定。 
	 
	int dim;              //数组维数
	
	int * bounds;         //数组维界基址，由InitArray分配
	//维界是指数组每一维的长度，比如A[3][4][5]
	//那么需要三个int变量分别存储3、4、5这3个值
	//由于数组维数是不固定的，所以这块内存需动态分配
	 
	int * constants;      //数组印象函数常量基址，由InitArray分配 
	//数组印象函数常量是配合数组的映像函数来定位数组元素的
	//映像常量的值在确定数组维数时就可以确定，提前将它们算出来
	//并储存在一段连续的内存空间中有利于元素定位操作时计算
	//元素的相对位置。 
}Array;

//----------------------数组的基本操作------------------------

/*
	函数：InitArray
	参数：Array &A 数组引用
	      int dim  数组维数
		  ... 可变参数，数组每一维的大小 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：若维数dim和随后的各维长度合法，则构造相应的数组A，并返回OK
*/
Status InitArray(Array &A, int dim, ...){  //初始化数组 
	
	//ap指向可变参数列表 
	va_list ap;
	
	//检查参数维数dim是否合法 
	if(dim < 1 || dim > MAX_ARRAY_DIM) { //维数参数非法
	
		//操作失败 
	    return ERROR;
	}//if
	
	//确定数组的维数 
	A.dim = dim;
	
	//根据维数dim分配数组维界基址的空间 
	//if(!(A.bounds = (int *)malloc(dim * sizeof(int))))
	//相当于以下两行代码：
	//A.bounds = (int *)malloc(dim * sizeof(int))
	//if(!A.bounds) <=>  if(A.bounds == NULL) 
	if(!(A.bounds = (int *)malloc(dim * sizeof(int)))) {
		printf("内存分配失败！\n");
		//math.h头文件中定义OVERFLOW的值为3
		//OVERFLOW表示上溢错误 
		exit(OVERFLOW);
	}//if
	
	//若各维长度合法，则存入A.bounds,并求出A的元素总数elemtotal
	int elemtotal = 1;
	
	//接下来需要根据可变参数传递的每一维的大小计算出数组中的元素总数
	//在这个过程中需要多次读取可变参数的值，所以要调用va_arg宏来
	//循环获取数组每一维的大小bounds，所以va_start宏要放在循环的外面。
	//注：调用va_arg宏获取可变参数之前要调用一下va_start宏。 
	//ap为va_list类型，是可变参数的前一个参数，也就是存放数组维数的dim。
	//在使用可变参数后，对函数的参数列表的声明顺序就有要求了
	//可变参数必须声明成最后一个参数，否则没办法确定传入的值
	//是否应该传给可变参数。而dim必须是可变参数的前一个参数
	//中间不可以有其他参数。 
	//第二个参数就是我们将要在各个操作中使用的可变参数
	va_start(ap, dim);
	
	//根据数组的维数初始化每一维的大小（维界） 
	for(int i = 0; i < dim; ++i){
		
		//调用va_arg宏从可变参数中取出每一维的大小bounds，类型是int 
		A.bounds[i] = va_arg(ap, int);
		
		//A.bounds[i] < 0表示出现了下溢错误，此时应立即终止程序执行
		//可变参数传入的值要进行检查后才可以使用 
		if(A.bounds[i] < 0){
			//math.h头文件中定义UNDERFLOW的值为4
			//UNDERFLOW表示下溢错误 
		    return UNDERFLOW;
		}//if 
		
		//元素总数累乘，比如数组A[3][4][2]的元素总数就是
		//3*4*2 = 24 所以算数组元素总数就是每一维大小相乘。 
		elemtotal *= A.bounds[i]; 
	}//for 
	
	//获取可变参数结束调用va_end宏 
	va_end(ap);
	
	//计算出数组元素总数之后就要申请相同大小的存储数组元素的内存空间，
	//以便容纳数组中的全部元素 
	//if(!(A.base = (ElemType *)malloc(elemtotal * sizeof(ElemType))))
	//相当于以下两行代码：
	//A.base = (ElemType *)malloc(elemtotal * sizeof(ElemType));
	//if(!A.base) <=>  if(A.base == NULL)
	if(!(A.base = (ElemType *)malloc(elemtotal * sizeof(ElemType)))){
		printf("内存分配失败！\n");
		//math.h头文件中定义OVERFLOW的值为3
		//OVERFLOW表示上溢错误
		exit(OVERFLOW);
	}//if
	
	//申请映像函数常量的存储空间，申请存储单元个数等于数组维数 
	if(!(A.constants = (int *)malloc(dim * sizeof(int)))){
		printf("内存分配失败！\n");
		//math.h头文件中定义OVERFLOW的值为3
		//OVERFLOW表示上溢错误
		exit(OVERFLOW);
	}//if
	
	//求映像函数的常数ci,并存入A.constants[i-1],i=1,...,dim
	//映像函数的常数ci的作用是方便的给元素定位，具体公式推导见书上P93
	//只要算出ci的值，就可以轻松得到某个元素在A.base指示的一维存储空间
	//中的相对地址off，然后就可以通过A.base[off]获取元素的值。 
	A.constants[dim - 1] = 1;  //L=1,指针的增减以元素大小为单位
	for(int i = dim - 2; i >= 0; --i) { 
	    A.constants[i] = A.bounds[i + 1] * A.constants[i + 1];
	}//for
	
	//操作成功 
	return OK; 
}//InitArray   

/*
	函数：DestroyArray
	参数：Array &A 数组引用
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：销毁数组A 
*/
Status DestroyArray(Array &A){
	
	//1.释放存储数组元素的A.base指示的内存空间
	
	//检查此段内存区域是否存在 
	if(!A.base) { //if(!A.base) <=>  if(A.base == NULL)
		return ERROR;
	}//if 

	//释放A.base指向的存储区域的内存空间 
	free(A.base);
	
	//A.base指针置空，释放掉指针变量本身的内存空间 
	A.base = NULL; 
	
	//2.释放存储数组维界（每一维大小）的A.bounds指示的内存空间 
	
	//检查此段内存区域是否存在 
	if(!A.bounds) {   //if(!A.bounds)  <=>  if(A.bounds != NULL) 
		return ERROR;
	}//if
	
	//释放A.bounds指向的存储区域的内存空间  
	free(A.bounds);
	
	//A.bounds指针置空，释放掉指针变量本身的内存空间 
	A.bounds = NULL;
	
	//3.释放存储数组映像函数常量的A.constants指示的内存空间 
	
	//检查此段内存区域是否存在
	if(!A.constants) {  //if(!A.constants) <=> if(A.constants == NULL)
		return ERROR;
	}//if
	
	//释放A.constants指向的存储区域的内存空间
	free(A.constants);
	
	//A.constants指针置空，释放掉指针变量本身的内存空间
	A.constants = NULL;
	
	//操作成功
	return OK;
}//DestroyArray 

/*
	函数：Locate 
	参数：Array A 数组A
	      va_list ap 指向保存待定位元素各个维下标的可变参数的指针
		  int &off 带回待定位元素在A.base指示的一维存储空间的相对位置 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：对ap指示的下标对应的元素进行定位，由off带回元素在A.base
	      指示的一维存储空间的相对位置。 
		  实际上就是使用映像函数配合求得的映像常量完成元素的相对定位，
		  得到一个相对位置。 
*/
Status Locate(Array A, va_list ap, int &off){
	
	//ind临时保存从可变参数中取得的的待定位元素的每一维的下标 
	int ind;
	
	//off保存求得的待定位元素的相对位置 
	off = 0;
	
	//根据元素每一维的下标使用映像函数进行定位 
	for(int i = 0; i < A.dim; ++i){
		
		//从可变参数中获取待定位元素在某一维的下标 
		ind = va_arg(ap, int);
		
		//检查下标ind是否越界 
		if(ind < 0 || ind >= A.bounds[i]) { //数组越界 
		    return OVERFLOW;
		}//if
		
		//根据映像函数求出某一维的偏移量，并且累加到off上 
		off += A.constants[i] * ind;
	}//for
	
	//操作成功 
	return OK;
}//Locate

/*
	函数：Value
	参数：Array A 数组A
	      ElemType &e 获取指定下标位置元素的值保存到e 
		  ... 可变参数，传递的是待查找元素各维的下标 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：（按下标从数组A中取值）A是n维数组，e为元素变量，
	      随后的可变参数是n个下标值。若各下标不超界，
		  则e赋值为所指定的数组A的元素值，并返回OK。
*/
Status Value(Array A, ElemType &e, ...){
	
	//声明指向可变参数的指针ap 
	va_list ap;
	
	//off保存了指定下标元素的定位结果，也就是这个元素
	//在A.base指示的一维数组中的位置 
	int off;
	
	//保存定位操作的结果，只要这个结果<=0就说明定位操作失败 
	Status result;
	
	//开始获取e后面的可变参数，并使ap指向可变参数，供定位函数使用 
	va_start(ap, e);
	
	//对指定下标的元素进行定位，获取这个元素在A.base指示的
	//一位数组中的相对位置，如果返回值result<=0，定位失败 
	if((result = Locate(A, ap, off)) <= 0) { //数组越界 
	    return result;
	}//if
	
	//根据定位操作计算出的相对位置，直接将其作为一位数组的下标
	//从A.base中按照一维数组的取法取出对应位置的元素(注意下标从0开始) ，
	//也可以用指针的取法来取得对应位置的元素 
	//e = *(A.base + off);  <=>  e = A.base[off]; 
	e = *(A.base + off);
	
	//结束可变参数的获取。书上没有此行代码，但是建议写上它 
	va_end(ap); 
	
	//操作成功 
	return OK; 
}//Value

/*
	函数：Assign
	参数：Array &A 数组引用 
	      ElemType e 修改指定下标位置元素的值为e 
		  ... 可变参数，传递的是待修改元素各维的下标 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：A是n维数组，e为元素变量，随后是n个下标值
	      若各下标不超界，将e的值赋给所指定的A的元素，并返回OK。
*/
Status Assign(Array &A, ElemType e, ...){
	
	//ap指向存储下标的可变参数 
	va_list ap;
	
	//off存储了定位操作获得的元素在A.base一维数组中的相对位置 
	int off;
	
	//开始获取参数e后面的可变参数，并使ap指向可变参数 
	va_start(ap, e);
	
	//result存储了定位操作的结果，如果这个值<=0表示定位操作失败 
	Status result;
	
	//按可变参数指示的下标执行定位操作，获取元素在A.base指示的
	//一维数组中的相对位置off，操作结果作为返回值赋值给result 
	if((result = Locate(A, ap, off)) <= 0) {  //数组越界 
	    return result;
	}//if
	
	//结束可变参数的获取。书上没有此行代码，但是建议写上它 
	va_end(ap);
	
	//根据定位操作获取的相对位置off，将A.base指示的内存空间中
	//对应位置的值修改为e，也可以使用一维数组的写法：
	//*(A.base + off) = e;   <=>   A.base[off] = e;
	*(A.base + off) = e;
	
	//操作成功 
	return OK; 
}//Assign


int main(int argc, char **argv){
	Array A;
	printf("\n--------------------------------数组顺序存储表示-------------------------------\n\n"); 
	//i,j,k是临时变量 
	int i, j, k;
	
	//p是工作指针 
	int *p;
	
	//设置数组的维数为3 
	int dim = 3;
	
	//设置数组每一维的大小分别为3,4,2，也就是：A[3][4][2]
	int bound1 = 3, bound2 = 4, bound3 = 2;
	
	//e保存从键盘输入的元素值和带回的元素值 
	ElemType e, *p1;
	
	//构造一个3*4*2的三维数组
	InitArray(A, dim, bound1, bound2, bound3);

	//输出数组A的维界基址 
	p = A.bounds;
	printf("数组A的维界（每一维大小）基址：A.bounds=[");
	for(int i = 0; i < dim; i++){
		printf(" %d ", *(p + i));
	}//for
	printf("]\n");
	
	//输出数组A印象函数常量基址 
	p = A.constants;
	printf("数组印象函数常量基址：A.constants=[");  
	for(int i = 0; i < dim; i++){
		printf(" %d ", *(p + i));
	}//for
	printf("]\n");
	
	//数组元素赋初值 
	for(int i = 0; i < bound1; i++){
		for(int j = 0; j < bound2; j++){
			for(int k = 0; k < bound3; k++){
				
				//调用赋值函数Assign初始化数组A
				//第一个参数是数组A
				//第二个参数是初始化的元素值
				//从第三个参数开始到最后的是3个下标（可变参数） 
				Assign(A, i * 100 + j * 10 + k, i, j, k);
			}//for-k
		}//for-j
	}//for-i
	
	//输出矩阵的所有元素
	printf("A[%d][%d][%d]矩阵元素如下：\n", bound1, bound2, bound3);
	for(int i = 0; i < bound1; i++){
		for(int j = 0; j < bound2; j++){
			for(int k = 0; k < bound3; k++){
				
				//取出A[i][j][k]位置的元素 
				Value(A, e, i, j, k);
				
				//输出
				printf("A[%d][%d][%d]=%2d\t", i, j, k, e); 
			}//for-k 
			printf("\n"); 
		}//for-j
		printf("\n");
	}//for-i
	
	printf("A.dim=%d\n", A.dim);
	
	DestroyArray(A);
}//main

/*  -----------------------------------运行结果------------------------------------ 

--------------------------------数组顺序存储表示-------------------------------

数组A的维界（每一维大小）基址：A.bounds=[ 3  4  2 ]
数组印象函数常量基址：A.constants=[ 8  2  1 ]
A[3][4][2]矩阵元素如下：
A[0][0][0]= 0   A[0][0][1]= 1
A[0][1][0]=10   A[0][1][1]=11
A[0][2][0]=20   A[0][2][1]=21
A[0][3][0]=30   A[0][3][1]=31

A[1][0][0]=100  A[1][0][1]=101
A[1][1][0]=110  A[1][1][1]=111
A[1][2][0]=120  A[1][2][1]=121
A[1][3][0]=130  A[1][3][1]=131

A[2][0][0]=200  A[2][0][1]=201
A[2][1][0]=210  A[2][1][1]=211
A[2][2][0]=220  A[2][2][1]=221
A[2][3][0]=230  A[2][3][1]=231

A.dim=3

--------------------------------
Process exited with return value 0
Press any key to continue . . .
*/

