/*
借助第1个实验--抽象数据类型三元组的定义、表示与实现，熟悉和掌握C/C++中指针、引用、动态分配存储等相关知识点，熟悉ADT表示与实现的全过程以及程序框架。
 
静态存储分配方案：
参考程序：Triplet_静态存储分配_指针版.cpp 
	相关知识点：
	1、预处理命令--“文件包含”（#include命令）
	（1）作用：将另外一个源文件（被包含文件，称为头文件，常以“.h”作为后缀，其内容可以是函数原型、宏定义、结构体类型定义、全局变量等）的全部内容包含进本源文件之中，避免重复劳动。 
	（2）格式为：#include "文件名"  或 #include <文件名> 。
	     注意两者的区别：若使用尖括号形式（即标准方式），则系统到存放C库函数头文件的目录中寻找要包含的文件；
		                 若使用双撇号形式，则系统先在用户当前目录中寻找要包含的文件，若找不到，再按标准方式查找。
	（3）C语言中的常用头文件： 附后。
			 stdio.h 包含了与标准I/O（standard input & output）库函数(例如：putchar(),getchar(),printf(),scanf(),puts(),gets()，文件I/O函数等)有关的变量定义和宏定义以及对函数的声明。
			 stdlib.h ANSI标准建议在stdlib.h中包含4个动态存储分配函数（calloc(),malloc(),free(),realloc())有关的信息。
			 			注意：在许多C编译系统实现时，往往增加了一些其他函数；许多C编译系统要求使用“malloc.h”,而不是“stdlib.h”，在使用时应查有关手册；ANSI标准要求动态分配系统返回void指针（具有一般性，可以指向任何类型的数据），
						 		但目前有的C编译所提供的这类函数返回char指针。无论哪种情况，都需要用强制类型转换的方法把viod或char指针转换成所需的类型。 
			 ctype.h  使用字符函数（isalnum(),isalpha(),isdigit(),iscntrl(),isgraph(),islower(),isupper()，tolower(),toupper()等）时，要包含此头文件。 
			 string.h 使用字符串函数（strcat(),strchr(),strcmp(),strcpy(),strlen(),strstr()等）时， 要包含此头文件。 
			 math.h 使用数学函数时，要包含此头文件。
	(4) 程序Triplet.cpp中的 "文件包含"
		#include<stdio.h> 
			  
			说明：库函数并不是C语言的一部分，它是由人们根据需要编制并提供用户使用的。不同的编译系统所提供的库函数的数目和函数名以及函数的功能是不完全相同的。ANSI标准提出了一批建议提供的标准库函数。
	2、预处理命令--宏定义
	（1）不带参数的宏定义。用一个指定的标识符（即宏名或宏的名字，一般习惯上用大写字母表示）来代表（或代替）一个字符串，
							其一般格式为: #define 标识符 字符串
							例如： #define  PI  3.1415926 
							在预编译时将宏名替换成所代表的字符串，这一过程称为“宏展开”。注意：不在行末加分号。
	（2）带参数的宏定义。要做参数替换。其定义的一般格式为: 
							#define 宏名（参数表） 字符串
							例如：	#define s(a,b) a*b
									#define MAX(x,y) (X)>(Y)? (X) : (Y)
									赋值语句 "area=S(3,2);"经宏展开后为: area=3*2;
									赋值语句 "t=MAX(a+b,c+d);"经宏展开后为:  t=(a+b)>(c+d)?(a+b):(c+d);
						注意和函数相区别！
	(3)程序Triplet.cpp中的宏定义
		#define OK 1
		#define ERROR 0 
						
	3、用typedef定义类型
		除了可以直接使用C提供的标准类型名（如int、char、float、double、long等）和自己声明的结构体、共用体、指针、枚举类型外，还可以使用typedef声明新的类型名来代替已有的类型名。
		例如：	typedef int INTEGER;  typedef int ElemType;  typedef float REAL;     
                INTEGER i,j; <==> int i, j;    ElemType e1,e2;  <==>  int e1,e2;    	REAL a,b;  <==>  float a,b; 
                typedef struct{
                	int month;
                	int day;
                	int year;
            	}DATE;  //为一个结构体类型声明了新类型名DATE，它代表上面指定的一个结构体类型。
				这时就可以用DATE定义变量：
				DATE  birthday;  // 定义了一个此结构体类型的变量。不要写成： struct DATE  birthday; 
				DATE  *p; // 定义了一个指针变量p， 它是指向此结构体类型数据的指针。 
		程序Triplet.cpp中的typedef用法：
			typedef int Status; // 新类型名Status代表int类型，用于表示函数的返回值类型（返回状态类型） 
			typedef float ElemType; //三元组元素的类型定义为float,可以随时变换成别的类型
			typedef struct
			{
				ElemType e[3];
			}Triplet; // 定义了三元组类型名Triplet，它代表上面指定的结构体类型，换言之，它被定义为上面的结构体类型。 
			main()函数里面：
				Status flag;    <==>   int flag;
				ElemType v0,v1,v2,e;   <==>   float v0,v1,v2,e; 
				Triplet T;   <==>  struct{ ElemType e[3];} T;  // 此处直接定义结构体变量，其其一般形式为：struct { 成员表列 } 变量名表列; 
	4、 静态存储分配与动态存储分配
		（1）静态存储分配：用于存储数据的变量和数组都必须在说明部分进行定义。C编译系统通过定义语句了解它们所需要的存储空间大小，
		              并预先为其分配适当的内存空间。这些空间一经分配，在变量或数组的生存期内是固定不变的。
					  例如：int i，a[10]; // C编译系统为变量i分配连续的2个字节内存空间，为数组a分配连续的2*10=20个字节的内存空间
					        int *p1, *p2;  // 为指针变量p1和p2分配内存空间
							p1 = &i;  // 将变量i的地址赋给指针变量p，指p指向i。不能写成: *p1 = &i;  注意与“int *p1 = &i;”相区别。 
							p2 = a;  // 与“p2 = &a[0];”等价，C语言规定：数组名代表数组中首元素的地址。不能写成： *p2 = a;  注意与“int *p2=a” 相区别。 
	    （2）动态存储分配：在程序执行期间需要空间来存储数据时，通过申请指定的内存空间；当有闲置不用的空间时，可以随时将其释放，由系统另作它用。
						用户可以通过调用C语言提供的标准库函数（malloc()函数、free()函数、calloc()函数等）来实现动态分配，从而得到制定数目的内存空间或释放指定的内存空间。 
		 
	5、指针的使用
	 （1） main()函数中：
	   	 	flag=initTriplet(&T,v0,v1,v2);  // 第1个参数使用“传址”方式，将结构体变量T（三元组）的首地址作为实参传递给 initTriplet()函数的第一个形参（指针类型，即Triplet *T，实际调用该函数时为形参T--指针变量，分配存储空间；然后将相应实参的值 --三元组的首地址赋给它），
				                            // 使执行该函数时的形参--指针T指向待操作的结构体（三元组）；其它三个参数采用“传值”方式（复制）。 
			printf("调用初始化函数后，flag=%d,T的三个值为：%4.2f,%4.2f,%4.2f\n",flag,T.e[0],T.e[1],T.e[2]); // 可以通过.运算符访问得到初始化后的三元组T的各个元素的值。 
	（2） main()函数中：
			if(isAscending(T)) 	printf("该三元组元素为升序\n");
			if(isDescending(T)) printf("该三元组元素为降序\n");
			printf("该三元组中的最大值为：%4.2f,最小值为：%4.2f",getMax(T),getMin(T)); 
			调用各个函数时都使用了“传值”方式，例如第一条语句中的isAscending(T)，将实参T（结构体本身）的内容复制到被调函数的形参T（调用时按Triplet类型为其分配存储空间，然后接受实参的赋值）
	（3）指针类型的形参的使用 
		例如： 
		//三元组的初始化
		Status initTriplet(Triplet *T,ElemType v0,ElemType v1,ElemType v2)
		{
			T->e[0]=v0;   // 使用指向运算符->，通过形参T（Triplet类型的指针）设置三元组的成员--数组e的各个元素的值 
			T->e[1]=v1;
			T->e[2]=v2;
			return OK;
		}
		//用e获取T的第i(1~3)个元素的值
		Status getElem(Triplet T,int i,ElemType *e)
		{
			if(i<1||i>3)
				return ERROR;
			else *e=T.e[i-1];  // 使用.运算符，通过形参T（Triplet类型的结构体变量）得到第i元的值，将其赋给e所指变量。这里第2个参数采用“传址”方式。 
				return OK;
		}
		//置T的第i元的值为e 
		Status putElem(Triplet *T,int i,ElemType e)
		{
			if(i<1||i>3)
				return ERROR;
			else T->e[i-1]=e;
				return OK;
		}
	 
	6、运算符和结合性
		( ) 圆括号    []下标运算符  ->指向（结构体成员）运算符  . 结构体成员运算符  
		-- 自增运算符  ++ 自减运算符         (类型） 类型转换运算符    * （单目）指针运算符，（双目)乘法运算符      % 求余运算符    -（单目）负号运算符，（双目)减法运算符     
		？ ： 条件运算符   ，逗号运算符
		举例：	-i++  <==>   -(i++)    // 单目运算符-和++为同一优先级，结合方向为自右至左
				设 int a; int *p; p = &a; // 把变量a的地址赋给p， 使p指向变量a
				（*p)++  <==> a++  	//  使变量a的值加1。不能写成： *p++ <==> *(p++) ,因为指针运算符*和++为同一优先级别，且结合方向为自右至左；
									//  而且++在p的右侧，是"后加"，因此先对p的原值进行*运算，得到a的值，然后使p的值改变，这样p就不再指向a了。 
                结构体变量.成员名 <==> （*p).成员名  <==>  p->成员名  // 使用指针p访问结构体成员时，最后一种形式更方便、直观。
				p->n     // 得到p指向的结构体变量中的成员n的值
				p->n++ <==> (p->n)++  // 得到p指向的结构体变量中的成员n的值，用完该值后使它加1 。  指向运算符->的优先级别高于++，而且++在p->n右侧 
				++p->n <==> ++(p->n)  // 得到p指向的结构体变量中的成员n的值，并使它加1，然后再使用它。   指向运算符->的优先级别高于++，而且++在p->n左侧
                
参考程序：Triplet_静态存储分配_引用版.cpp
	在此主要说明与相应的指针版之间的不同点。
	1、引用与指针
	（1）关于引用
	作用：对一个变量声明（或建立）一个引用，就是为该变量另起一个名字,因此变量的引用通常被认为是变量的别名；
	本质：对变量声明一个引用，编译系统不给引用单独分配存储单元，引用和它所代表的变量共享同一个存储位置，或者说都代表同一变量单元；
	用法：声明一个引用的格式如下:  
    		类型 & 引用名 = 已定义的变量名;   
    		例如：    
				int i=5；
    			int &j = i； 	//  为变量i声明了一个引用j，j和i共享同一个存储位置（代表同一个存储单元）
								//  在声明一个引用时,必须立即对它进行初始化,即声明它代表哪一个变量。不能声明完成后再赋值。 例如，不能写成：int i=5; int &j; j=i; 
	(2) 关于指针
	本质：指针就是变量的地址；指针变量就是专门存放变量地址的变量。不能将其他类型的数据（如整数）赋给指针变量
	用法：声明指针变量的一般形式如下：
	      [存储类型]    数据类型   *指针名；
	      例如：
		  		int i=5;
				int *i_point=&i;  	// 声明（建立）了一个基类型为int的指针变量i_point(系统为其分配了存储空间), 并将整型变量i的地址给它，即使它指向i。
				// 可以改写为：
				int i=5;
				int *i_point;       //  声明（建立）了一个基类型为int的指针变量i_point(系统为其分配了存储空间), 它还没有具体指向（因为还没有把具体变量的地址赋给它），但可以肯定的是它指向的目标变量必须是整型变量。 
				i_point=&i;        	//  将整型变量i的地址给指针变量i_point，从而使它指向i。
				  
 	2、 initTriplet()的修改（指针版==>引用版） 
	//指针版中的三元组初始化
	Status initTriplet(Triplet *T,ElemType v0,ElemType v1,ElemType v2)
	{
		T->e[0]=v0;
		T->e[1]=v1;
		T->e[2]=v2;
		return OK;
	}
	// 指针版：main()函数中的调用语句，第一个实参和形参的结合方式为：传址 
	flag=initTriplet(&T,v0,v1,v2);	 
	
	//引用版中的三元组初始化
	Status initTriplet(Triplet &T,ElemType v0,ElemType v1,ElemType v2)
	{
		T.e[0]=v0;
		T.e[1]=v1;
		T.e[2]=v2;
		return OK;
	}
	// 引用版 ：main()函数中的调用语句，第一个实参和形参的结合方式仍为：传址 
	flag=initTriplet(T,v0,v1,v2);	 

 	3、 getElem()的修改（指针版==>引用版） 
	//指针版：用e获取T的第i(1~3)个元素的值， 
	Status getElem(Triplet T,int i,ElemType *e)
	{
		if(i<1||i>3)
			return ERROR;
		else *e=T.e[i-1];
			return OK;
	}
    // 指针版：main()中的调用语句
	flag=getElem(T, &e);
	
	//引用版：用e获取T的第i(1~3)个元素的值， 
	Status getElem(Triplet T,int i,ElemType &e)
	{
		if(i<1||i>3)
			return ERROR;
		else e=T.e[i-1];
			return OK;
	}
    // 引用版： main()中的调用语句
	flag=getElem(T, e);
		

动态存储分配方案：
参考程序：Triplet_动态存储分配_引用版.cpp
	1、动态存储分配的三元组类型定义
		typedef ElemType *Triplet;  //声明Triplet为ElemType指针类型  
	2、在main()函数中声明三元组
		Triplet T; //声明Triplet类型的变量，等价于：ElemType *T; 也就是说，T实际上是基类型为ElemType的指针变量
	3、三元组的初始化
	//三元组的初始化
	Status initTriplet(Triplet &T,ElemType v0,ElemType v1,ElemType v2)
	{
		T=(ElemType *)malloc(3*sizeof(ElemType));   // 为三元组申请内存（动态存储分配），若申请成功，则T(ElemType的指针变量)为三元组的起始位置，即第一元的地址（即指向第一元）。
													// 注意malloc()的用法。申请成功，该函数返回void类型的指针；再使用之前，应强制转换为所需要的类型，例如此处的ElemType类型的指针。 
		if(T==NULL) 
		{
			printf("分配内存失败！");
			exit(OVERFLOW);
		}
		T[0]=v0;  // 将三元组的首地址T作为数组名，使用下标方式访问其中的三个元素 
		T[1]=v1;
		T[2]=v2;
		return OK;
	}
	4、main()函数中调用initTriplet()的方法
		flag=initTriplet(T,v0,v1,v2);  // T为基类型为ElemType的指针变量，调用后T便指向刚刚创建的三元组的起始位置 
		printf("调用初始化函数后，flag=%d,T的三个值为：%4.2f,%4.2f,%4.2f\n",flag,T[0],T[1],T[2]);  // 将T作为数组名，用下标方式访问三元的值 

	5、三元组的销毁
	//销毁三元组,静态存储是在程序开始的时候就分配固定的内存单元，整个程序结束后自动释放存储单元，不需销毁 
	//而动态存储单元在程序运行初不分配内存单元在用到时才分配，而当用过后需要用语句释放该内存空间
	Status destroyTriplet(Triplet &T)
	{
		free(T);
		T=NULL;
		printf("分配内存已释放！");
		return OK;
	} 
	6、 main()函数中调用destroyTriplet()的方法
		destroyTriplet(T);

如何修改，转换为指针版？？？？ 
参考程序：Triplet_动态存储分配_指针版.cpp


动态存储分配方案--增加选作内容：
参考程序：Triplet_动态存储分配_引用版_增加选作.cpp
	1、参考程序是在 Triplet_动态存储分配_引用版.cpp的基础上修改而成；
	2、新增3个函数：
	// 新增函数：求两个三元组之和
	Status addTriplet(Triplet T1,Triplet T2,Triplet &T3) 
	{  // 设置三个形参，用第 
		T3[0]=T1[0]+T2[0];  
		T3[1]=T1[1]+T2[1];
		T3[2]=T1[2]+T2[2];
		return OK;
	}
	// 新增函数：求两个三元组之差 
	Status subTriplet(Triplet T1,Triplet T2,Triplet &T3)
	{
		T3[0]=T1[0]-T2[0];  
		T3[1]=T1[1]-T2[1];
		T3[2]=T1[2]-T2[2];
		return OK;
	}
	// 新增函数：为三元组乘比例因子 
	Status zoomTriplet(Triplet &T, int m)
	{
		T[0]*=m;  // 等价于： T1[0]=T1[0]*m; 
		T[1]*=m;
		T[2]*=m;
		return OK;
	} 
	
	3、main()函数修改为：
	int main()
	{
		Status flag;  int m;
		ElemType v0,v1,v2,e;
		Triplet T1, T2, T3;
	
		printf("请输入三元组T1的三个值v0,v1,v2:\n"); 
		scanf("%f,%f,%f",&v0,&v1,&v2);
		flag=initTriplet(T1,v0,v1,v2);  初始化第一个三元组T1 
		printf("调用初始化函数后，flag=%d,T1的三个值为：%4.2f,%4.2f,%4.2f\n",flag,T1[0],T1[1],T1[2]);
		if(isAscending(T1))
		printf("该三元组元素为升序\n");
		if(isDescending(T1))
		printf("该三元组元素为降序\n");
		printf("该三元组中的最大值为：%4.2f,最小值为：%4.2f\n",getMax(T1),getMin(T1));
		
		printf("请输入三元组T2的三个值v0,v1,v2:\n"); 
		scanf("%f,%f,%f",&v0,&v1,&v2);
		flag=initTriplet(T2,v0,v1,v2);  // 初始化第二个三元组T2 
		printf("调用初始化函数后，flag=%d,T2的三个值为：%4.2f,%4.2f,%4.2f\n",flag,T2[0],T2[1],T2[2]);	
		
		flag=initTriplet(T3,0,0,0);  // 初始化第三个三元组T3，用于存放后面T1和T2的相加之和或相减之差 
		flag=addTriplet(T1,T2,T3);   // 调用函数addTriplet()求T1和T2的相加之和，保存在T3之中 
		printf("T1和T2相加之和为：%4.2f,%4.2f,%4.2f\n",T3[0],T3[1],T3[2]);	
		flag=subTriplet(T1,T2,T3);   // 调用函数subTriplet()求T1和T2的相减之和，保存在T3之中，T3原有内容被覆盖 
		printf("T1和T2相减之差为：%4.2f,%4.2f,%4.2f\n",T3[0],T3[1],T3[2]);	
		printf("请输入比例因子:"); 
		scanf("%d",&m);	
		flag=zoomTriplet(T2,m);      // 调用函数zoomTriplet()求T2*m，结果回存在T2之中 
		printf("T2乘以比例因子后的值为：%4.2f,%4.2f,%4.2f\n",T2[0],T2[1],T2[2]);	
				
		destroyTriplet(T1);
		destroyTriplet(T2);
		destroyTriplet(T3);
		
		return OK;
	}  

*/


/*
常用的头文件如下 :
#include <assert.h>    //设定插入点 
#include <ctype.h>     //字符处理 
#include <errno.h>     //定义错误码 
#include <float.h>     //浮点数处理 
#include <fstream.h>    //文件输入／输出 
#include <iomanip.h>    //参数化输入／输出 
#include <iostream.h>   //数据流输入／输出 
#include <limits.h>    //定义各种数据类型最值常量 
#include <locale.h>    //定义本地化函数 
#include <math.h>     //定义数学函数 
#include <stdio.h>     //定义输入／输出函数 
#include <stdlib.h>    //定义杂项函数及内存分配函数 
#include <string.h>    //字符串处理 
#include <strstrea.h>   //基于数组的输入／输出 
#include <time.h>     //定义关于时间的函数 
#include <wchar.h>     //宽字符处理及输入／输出 
#include <wctype.h>    //宽字符分类 
 
标准 C/C++ （同上的不再注释） 
 
#include <algorithm>    //STL 通用算法 
#include <bitset>     //STL 位集容器 
#include <cctype> 
#include <cerrno> 
#include <clocale> 
#include <cmath> 
#include <complex>     //复数类 
#include <cstdio> 
#include <cstdlib> 
#include <cstring> 
#include <ctime> 
#include <deque>      //STL 双端队列容器 
#include <exception>    //异常处理类 
#include <fstream> 
#include <functional>   //STL 定义运算函数（代替运算符） 
#include <limits> 
#include <list>      //STL 线性列表容器 
#include <map>       //STL 映射容器 
#include <iomanip> 
#include <ios>       //基本输入／输出支持 
#include <iosfwd>     //输入／输出系统使用的前置声明 
#include <iostream> 
#include <istream>     //基本输入流 
#include <ostream>     //基本输出流 
#include <queue>      //STL 队列容器 
#include <set>       //STL 集合容器 
#include <sstream>     //基于字符串的流 
#include <stack>      //STL 堆栈容器     
#include <stdexcept>    //标准异常类 
#include <streambuf>    //底层输入／输出支持 
#include <string>     //字符串类 
#include <utility>     //STL 通用模板类 
#include <vector>     //STL 动态数组容器 
#include <cwchar> 
#include <cwctype> 
 
using namespace std; 
 
////////////////////////////////////////////////////////////////////////// 
 
C99 增加 
 
#include <complex.h>   //复数处理 
#include <fenv.h>    //浮点环境 
#include <inttypes.h>  //整数格式转换 
#include <stdbool.h>   //布尔环境 
#include <stdint.h>   //整型环境 
#include <tgmath.h>   //通用类型数学宏

*/ 
#include<stdio.h>
#include<conio.h>

int main()
{
    printf("\n\n");	
	printf("                           欢迎同学们                        \n");
	printf("                        —————————                      \n");
    printf("\n");
	printf("不过，该文件并非真正意义上的程序文件，而是一个相关知识点的说明文档！\n");
	printf("********************************************************************\n");
	printf("该文档含以下5个程序的注释和相关知识点解读：\n"); 
	printf("    Triplet_静态存储分配_指针版.cpp\n");
	printf("    Triplet_静态存储分配_引用版.cpp\n");
	printf("    Triplet_动态存储分配_引用版_增加选作.cpp\n");
	printf("    Triplet_动态存储分配_引用版.cpp\n");
	printf("    Triplet_动态存储分配_指针版.cpp\n");
	printf("********************************************************************\n");
	printf("目的是： 借助第1个实验--抽象数据类型三元组的定义、表示与实现，\n");
	printf("         通过程序说明和相关知识点解读，\n");
    printf("         帮助同学们熟悉和掌握C/C++中指针、引用、动态分配存储等相关知识点，\n");
    printf("         熟悉ADT表示与实现的全过程以及程序框架。\n");
	printf("********************************************************************\n");
    printf("希望对同学们有所帮助！！\n");
	printf("为了阅读方便，建议使用Devcpp阅读，尽管你可以使用记事本阅读，但不保证格式整齐！\n");
    printf("请点击任意键返回...\n");
    getch();
}

