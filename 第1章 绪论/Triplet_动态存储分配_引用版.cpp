
/* 抽象数据类型三元组的定义： 
   ADT Triplet
   {
         数据对象：D={e1,e2,e3|e1,e2,e3属于ElemSet (定义了关系运算的某个集合)}
         数据关系：R={<e1，e2>|<e2，e3>}
         基本操作：
         1.创建三元组
		    createTriplet()
			初始条件：无 
            操作结果：已申请好三元组所占的内存空间，并返回带有三元组首地址的指针。 
         2.初始化三元组 
		    initTriplet(*T,v0,v1,v2) 
            初始条件：已成功输入vo,v1,v2的值，并且已经开辟好三元组的内存空间 
            操作结果：元素e1，e2和e3分别被赋予参数v1,v2,v3的值。
         3.销毁三元组 
		    destroyTriplet(*T)
            初始条件：三元组已经存在。
            操作结果：销毁三元组T。
         4.获取第i个元素的值 
		    getElem(*T,i,&e)
            初始条件：三元组已经存在且1<=i<=3.
            操作结果：用e返回三元组的第i个元素。
         5.置三元组第i个元素的值 
		    putElem(*T,i,e)
            初始条件：三元组已经存在且1<=i<=3.
            操作结果：用e值取代三元组的第i个元素。
         6.判断三元组的三个元素是否为升序排列 
		    isAscending(*T)
            初始条件：三元组已经存在。
            操作结果：如果三元组的三个元素按升序排列，则返回TRUE；否则返回FALSE。
         7.判断三元组的三个元素是否为降序排列 
		    isDescending(*T)
            初始条件：三元组已经存在。
            操作结果：如果三元组的三个元素按降序排列，则返回TRUE，否则返回FALSE。
         8.获取三元组三个元素中的最大值
		    getMax(*T,&e)
            初始条件：三元组已经存在。
            操作结果：用e返回的3个元素中的最大值。
         9.获取三元组三个元素中的最小值
            getMin(*T,&e)
            初始条件：三元组已经存在。
            操作结果：用e返回的3个元素中的最小值。 
    } ADT Triplet
*/ 

//*******************************************引入头文件*********************************************
# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

//******************************************自定义符号常量*******************************************
# define OK 1
# define ERROR 0
# define TRUE 1
# define FALSE 0
# define OVERFLOW -1

//******************************************自定义数据类型********************************************
typedef int Status;
typedef int ElemType;
typedef ElemType * Triplet;

//******************************************三元组的主要操作******************************************

/*
	函数：createTriplet
	参数：Triplet &T 三元组引用 
	返回值：无
	作用：创建三元组 
*/
void createTriplet(Triplet &T){
	
	T = (Triplet)malloc(sizeof(ElemType)); 
	if(!T){ //if(!T) <=> if(T == null)
	    printf("申请内存失败！\n");
		exit(OVERFLOW); 
    }//if
}//createTriplet

/*
	函数：InitTriplet
	参数：Triplet &T 三元组引用 
	      ElemType v1 三元组第一个分量 
	      ElemType v2 三元组第二个分量 
	      ElemType v3 三元组第三个分量 
	返回值：状态码，OK表示操作成功 
	作用：初始化三元组 
*/
Status InitTriplet(Triplet &T, ElemType v1,ElemType v2,ElemType v3){
	
	//创建一个三元组 
	createTriplet(T); 
	
	//初始化三元组的三个分量 
	T[0] = v1;
	T[1] = v2;
	T[2] = v3;
	
	//操作成功 
	return OK;
}//InitTriplet

/*
	函数：DestroyTriplet
	参数：Triplet &T 三元组引用 
	返回值：状态码，OK表示操作成功 
	作用：销毁三元组 
*/
Status DestroyTriplet(Triplet &T){
	
	free(T);   //释放内存空间 
	T = NULL;  //指针清零 
	return OK; //操作成功 
}//DestroyTriplet

/*
	函数：getElem
	参数：Triplet T 三元组结构体指针 
	      int i 索引变量，指示三元组中的第几个分量 
	      ElemType &e 带回的元素E 
	返回值：状态码，OK表示操作成功 
	作用：取出三元组第i个分量存储的数据 
*/
Status getElem(Triplet T, int i, ElemType &e){
	
	//检查索引变量i是否越界 
	if(i < 1 || i > 3){
		return ERROR;
	}//if
	
	//取出对应位置元素 
	e = T[i - 1];
	
	//操作成功 
	return OK;
}//getElem

/*
	函数：putElem
	参数：Triplet &T 三元组引用
	      int i 索引变量，指示三元组中的第几个分量 
	      ElemType &e 带回的元素E 
	返回值：状态码，OK表示操作成功 
	作用：修改三元组第i个分量的值 
*/
Status putElem(Triplet &T, int i, ElemType e){
	
	//检查索引变量是否正确 
	if(i < 1 || i > 3) {
		return ERROR;
	}//if
	
	//修改元素的值 
	T[i - 1] = e;
	
	//操作成功 
	return OK;
}//putElem

/*
	函数：isAscending
	参数：Triplet T 三元组结构体指针 
	返回值：如果三元组的三个元素按升序排列，则返回TRUE；否则返回FALSE。
	作用：判断三元组是否升序排列 
*/
Status isAscending(Triplet T){
	
	return T[0] <= T[1] && T[1] <= T[2];
}//isAscending

/*
	函数：isDescending
	参数：Triplet T 三元组结构体指针 
	返回值：如果三元组的三个元素按降序排列，则返回TRUE；否则返回FALSE。
	作用：判断三元组是否降序排列 
*/
Status isDescending(Triplet T){
	
	return T[0] >= T[1] && T[1] >= T[2];
}//isDescending

/*
	函数：getMax
	参数：Triplet T 三元组结构体指针
	      ElemType &e 带回三元组中三个分量的最大值 
	返回值：状态码，OK表示操作成功
	作用：获得三元组中三个分量的最大值 
*/
Status getMax(Triplet T, ElemType &e){
	
	//通过三目条件运算符求得最大值 
	e = T[0] >= T[1] ? (T[0] >= T[2] ? T[0] : T[2]) : (T[1] >= T[2] ? T[1] : T[2]);
	
	//操作成功 
	return OK;
}//getMax

/*
	函数：getMin
	参数：Triplet T 三元组结构体指针
	      ElemType &e 带回三元组中三个分量的最小值 
	返回值：状态码，OK表示操作成功
	作用：获得三元组中三个分量的最小值 
*/
Status getMin(Triplet T, ElemType &e){
	
	//通过三目条件运算符求得最小值
	e = T[0] <= T[1] ? (T[0] <= T[2] ? T[0] : T[2]) : (T[1] <= T[2] ? T[1] : T[2]);
	
	//操作成功 
	return OK;
}//getMin

//-------------------------------------------主函数--------------------------------------------------- 
int main(){
	
	Triplet T;
	ElemType v0, v1, v2, e;
	Status flag, temp, temp1;
	
	printf("请输入v0，v1，v2:");
	scanf("%d,%d,%d", &v0, &v1, &v2);
	flag = InitTriplet(T, v0, v1, v2);
	printf("调用初始化函数后，flag=%d(1:成功) T的三个值为:%d %d %d\n", flag, T[0], T[1], T[2]);
	
	printf("您想查找三元组第几个元素的值(1-3)：\n");
	scanf("%d", &temp);
	getElem(T, temp, e);
	printf("三元组第%d个元素的值：%d\n", temp, e);
	
	printf("您想重置三元组第几个元素的值(1-3)：\n");
    scanf("%d", &temp);
    printf("您想重置三元组第%d个元素的值为多少?：\n", temp);
    scanf("%d", &temp1);
    putElem(T, temp, temp1);
	printf("三元组第%d个元素重置后的值：%d\n", temp, T[temp-1]);
	printf("重置第%d个元素后三元组的三个值为：%4d,%4d,%4d\n", temp, T[0], T[1], T[2]);
	
	if(isAscending(T)) //判断三元组是否为升序 
	   printf("该三元组元素为升序！\n");
	else if(isDescending(T)) //再判断三元组是否为降序 
	   printf("该三元组元素为降序！\n");
	else  //若以上两条件均不符合则提示用户既不是升序也不是降序 
	   printf("该三元组元素既不是升序也不是降序！\n");
	
	//输出三元组的最大值和最小值 
	getMax(T, e);
	printf("该三元组中的最大值为：%4d\n", e); 
	getMin(T, e);
	printf("该三元组中的最小值为：%4d\n", e); 
	
	printf("销毁三元组\n"); 
    DestroyTriplet(T); 
	
	return 0;
}

/*******************************测试记录************************************* 
	请输入v0，v1，v2:1,2,5
	调用初始化函数后，flag=1(1:成功) T的三个值为:1 2 5
	您想查找三元组第几个元素的值(1-3)：
	3
	三元组第3个元素的值：5
	您想重置三元组第几个元素的值(1-3)：
	2
	您想重置三元组第2个元素的值为多少?：
	56
	三元组第2个元素重置后的值：56
	重置第2个元素后三元组的三个值为：   1,  56,   5
	该三元组元素既不是升序也不是降序！
	该三元组中的最大值为：  56
	该三元组中的最小值为：   1
	
	--------------------------------
	Process exited after 18.11 seconds with return value 0
	请按任意键继续. . .
*/ 
