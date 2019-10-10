/*
      设计实现抽象数据类型“三元组 （Triplet）” 。 
   每个三元组由任意三个实数的序列构成，基本操作包括：
   创建一个三元组，取三元组的任意一个分量，置三元组
   的任意一个分量，求三元组的最大分量、最小分量，
   显示三元组，销毁三元组等。
      
   方法1：用结构体封装需要定义的数据类型，如定义三元组ADT时，
	首先用结构体封装“三元组”的三个分量。
	并利用typedef对结构体重新命名。
*/
#include<stdio.h>
#define OK 1
#define ERROR 0

typedef int Status;
typedef float ElemType;  //三元组元素的类型先定义为int,可以随时变换成别的类型 
typedef struct
{
	ElemType e[3];
}Triplet;

//三元组的初始化
Status initTriplet(Triplet *T,ElemType v0,ElemType v1,ElemType v2)
{
	T->e[0]=v0;
	T->e[1]=v1;
	T->e[2]=v2;
	return OK;
}
//销毁三元组,静态存储是在程序开始的时候就分配固定的内存单元，整个程序结束后自动释放存储单元，不需销毁 
//而动态存储单元在程序运行初不分配内存单元在用到时才分配，而当用过后需要用语句释放该内存空间
Status destroyTriplet(Triplet *T)
{
	return OK;
}
//用e获取T的第i(1~3)个元素的值， 
Status getElem(Triplet T,int i,ElemType *e)
{
	if(i<1||i>3)
		return ERROR;
	else *e=T.e[i-1];
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
//如果T的三个元素按升序排列，则返回1，否则返回0
Status isAscending(Triplet *T)
{
	return (T.e[0]<=T.e[1])&&(T.e[1]<=T.e[2]);
} 
//如果T的三个元素按降序排列，则返回1，否则返回0
Status isDescending(Triplet T)
{
	return (T.e[0]>=T.e[1])&&(T.e[1]>=T.e[2]);
} 
//用e返回指向T的最大元素的值
ElemType getMax(Triplet T)
{
	ElemType e;
	if(T.e[0]>T.e[1])
	   e=T.e[0];
	   else
	   	 e=T.e[1];
    if(T.e[2]>e)
       e=T.e[2];
    return e;
} 
//用e返回指向T的最小元素的值
ElemType getMin(Triplet T)
{
	ElemType e;
	if(T.e[0]<T.e[1])
	     e=T.e[0];
	   else
	   	 e=T.e[1];
    if(T.e[2]<e)
    	 e=T.e[2];
    return e;
} 

int main()
{

	Status flag;
	ElemType v0,v1,v2;
	Triplet T;
	printf("请进入三元组的三个值v0,v1,v2:\n"); 
	scanf("%f,%f,%f",&v0,&v1,&v2);
	flag=initTriplet(&T,v0,v1,v2);
	printf("调用初始化函数后，flag=%d,T的三个值为：%4.2f,%4.2f,%4.2f\n",flag,T.e[0],T.e[1],T.e[2]);
	if(isAscending(T)) 	printf("该三元组元素为升序\n");
	if(isDescending(T)) printf("该三元组元素为降序\n");
	printf("该三元组中的最大值为：%4.2f,最小值为：%4.2f",getMax(T),getMin(T));
	return OK;
} 
 

