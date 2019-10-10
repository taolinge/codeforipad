
/**********************************稀疏矩阵三元组表抽象数据类型ADT定义*****************************************
	ADT SpareseMatrix{
		数据对象：D＝{aij|i=1,2,..,m,j=1,2,..,n；aij∈ElemSet，m和n分别称为矩阵的行数和列数 }
		数据关系：R＝{Row,Col}
		　　　　　Row＝{<ai,j,ai,j+1>|1≤i≤m,1≤i≤n-1}
		　　　　　Col＝{<ai,j,ai+1,j>|1≤i≤m-1,1≤j≤n}
		基本操作：
		　　CreateSMatrix(&M)；
		　　　　操作结果：创建稀疏矩阵M。
		　　DestroySMatrix(&M)；
		　　　　初始条件：稀疏矩阵M存在。
		　　　　操作结果：销毁稀疏矩阵M。
		　　PrintSMatrix(M)；
		　　　　初始条件：稀疏矩阵M存在。
		　　　　操作结果：输出稀疏矩阵M。
		　　CopySMatrix(M，&T)；
		　　　　初始条件：稀疏矩阵M存在。
		　　　　操作结果：由稀疏矩阵M复制得到T。
		　　AddSMatrix(M，N，&Q)；
		　　　　初始条件：稀疏矩阵M与N的行数和列数对应相等。
		　　　　操作结果：求稀疏矩阵的和Q=M+N。
		　　SubSMatrix(M，N，&Q)；
		　　　　初始条件：稀疏矩阵M与N的行数和列数对应相等。
		　　　　操作结果：求稀疏矩阵的差Q=M-N。
		　　MultSMatrix(M，N，&Q)；
		　　　　初始条件：稀疏矩阵M的列数等于N的行数。
		　　　　操作结果：求稀疏矩阵乘积Q=M×N。
		　　TransposeSMatrix(M，&T)；
		　　　　初始条件：稀疏矩阵M存在。
		　　　　操作结果：求稀疏矩阵M的转置矩阵T。
	} ADT SpareseMatrix
*/ 


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>引入头文件<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <stdio.h>       //使用了标准库函数 
#include <stdlib.h>      //使用了malloc函数 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>自定义符号常量<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 

#define OVERFLOW -2          //内存溢出错误常量
#define OK 1                 //表示操作正确的常量 
#define ERROR 0              //表示操作错误的常量
#define MAXSIZE 12500        //假设非零元个数的最大值是12500 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>自定义数据类型<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef int  Status;     //状态码类型 
typedef int ElemType;    //存储的元素类型 

//----------------  稀疏矩阵的三元组顺序表存储表示  -------------------- 

typedef struct{
	int       i,j;   //该非零元的行下标和列下标
	ElemType  e;     //对应位置的元素 
}Triple; 

typedef struct{
	Triple data[MAXSIZE + 1]; //非零元三元组表,data[0]未用
	int mu, nu, tu;           //矩阵的行数、列数和非零元个数 
}TSMatrix;

//-------------------------------------------主要操作-----------------------------------------

//------------> 1.创建稀疏矩阵M

/*
    函数：CreateSMatrix
    参数：TSMatrix &M 稀疏矩阵引用
    返回值：状态码，操作成功返回OK，操作失败返回ERROR 
    作用：创建具有i(i>1)行j(j>1)列的稀疏矩阵M
*/
Status CreateSMatrix(TSMatrix &M){
	
	//m,n分别是矩阵的行数，列数 
	int m, n;
	
	//非零元素个数 
	ElemType e;
	
	//k是一个标志位，用于临时存储对用户输入的检查结果，
	//如果k的值=1，说明输入发生了错误，需要提示用户重新输入 
	Status k;
	
	//从键盘接收矩阵的行数、列数和非零元个数 
	printf("请输入矩阵的行数、列数、非零元素的个数：");
	scanf("%d,%d,%d" , &M.mu , &M.nu , &M.tu);
	
	//非零元个数不能超过最大值 
	if(M.tu > MAXSIZE) { 
		return ERROR;
	}//if
	
	//0号单元不用 
	M.data[0].i = 0;
	
	//从键盘接收每一个非零元 
	for(int i = 1; i <= M.tu; i++){
		do{
			//从键盘接收一个非零元的行、列和元素值 
			printf("请按行序顺序输入第%d个非零元素所在的行（1-%d），列(1-%d)，和元素值\n（行和列的顺序必须是从小到大，不能打乱顺序随便乱输）：\n", 
				i , M.mu , M.nu);
			scanf("%d,%d,%d", &m , &n , &e);
			
			//将k的值初始化为0，默认用户不需要重新输入 
			k = 0;
			
			//检查行或列的值是否超出范围
			//行和列都是从1开始计算的，0号单元不用，
			//所以 m < 1 和 n < 1 表示行号或列号低于最小值
			//行号m不能大于总行数M.mu，列号不得大于总列数M.nu
			//m > M.mu和n > M.nu表示行号或列号大于最大值 
			if(m < 1 || m > M.mu || n < 1 || n > M.nu){ //超出范围 
				
				//修改k的值为1，提示用户重新输入
				printf("行号或列号输入不正确，行号和列号不得小于1！行号不得大于%d，列号不得大于%d！", M.mu, M.nu);
				k = 1;
			}//if
			
			//检查行或列的顺序是否有错 
			//M.data[i-1].i 表示前面的行号，
			//M.data[i-1].j 表示前面的列号 
			//m < M.data[i-1].i 表示两个不同行元素后面的行号比前面的小，行号顺序不对
			//m == M.data[i-1].i && n <= M.data[i-1].j 表示在同一行的两个元素
			//后面的列号比前面的小，列号顺序不对。
			if(m < M.data[i-1].i || 
					m == M.data[i-1].i && n <= M.data[i-1].j){       
				
				//修改k的值为1，提示用户重新输入 
				printf("行号或列号输入不正确，请按照行号由小到大，列号由小到大的顺序输入！\n");
				k = 1; 
			}//if
			
			//检查输入的非零元素e值是否为0 
			if(e == 0) {
				
				//提示用户重新输入非零值 
				printf("请不要输入零！\n");
				k = 1;
			}//if
		}while(k);
		
		//通过检查后，将行号、列号和非零元素值填入稀疏矩阵三元组表 
		M.data[i].i = m;
		M.data[i].j = n;
		M.data[i].e = e;
	}//for
	
	//操作成功 
	return OK;
}//CreateSMatrix

//------------> 2.销毁稀疏矩阵M 

/*
    函数：DestorySMatrix
    参数：TSMatrix &M 稀疏矩阵引用
    返回值：无
    作用：销毁稀疏矩阵M
*/
void DestorySMatrix(TSMatrix &M){
	
	//直接将总行数、总列数和非零元总数设置成0.
	//已经输入的非零元素信息弃置不用，不必抹掉已用存储空间 
	M.mu = M.nu = M.tu = 0; 
}//DestorySMatrix 

//------------> 3.遍历稀疏矩阵M 

/*
    函数：PrintSMatrix
    参数：TSMatrix M 稀疏矩阵M
    返回值：无
    作用：以三元组表形式输出稀疏矩阵M
*/
void PrintSMatrix(TSMatrix M){
	
	printf("稀疏矩阵M有%d行%d列%d个非零元素。\n", M.mu , M.nu , M.tu);
	printf(" 行  列   元素值\n");
	for(int i = 1; i <= M.tu; i++) { 
		printf("%2d%4d%8d\n", M.data[i].i , M.data[i].j , M.data[i].e);
	}//for 
}//PrintSMatrix

/*
    函数：PrintSMatrix
    参数：TSMatrix M 稀疏矩阵M
    返回值：无
    作用：以矩阵形式输出稀疏矩阵M
*/
void PrintSMatrix_1(TSMatrix M){
	
	//k的作用是一个计数器，每输出一个非零元，k的值+1
	int k = 1;
	
	//工作指针p指向稀疏矩阵数据存储区域 
	Triple *p = M.data;
	
	//由于0号单元不用，所以p++表示p指向第一个非零元素
	p++;
	
	for(int i = 1; i <= M.mu; i++){
		for(int j = 1; j <= M.nu; j++){
			//p指向非零元且p所指的元素为当前处理元素 
			//矩阵中的元素有0和非零两种。除了稀疏矩阵M的三元组表中 
			//记载的非零元素，矩阵剩余的元素都是0元素 。
			//k的作用是一个计数器，每输出一个非零元，k的值+1
			//所以k <= M.tu 表示三元组表还没有遍历完成，还有非零元素没输出。
			//p->i == i 待输出元素行下标i和非零元素的行下标i相同
			//p->j == j 待输出元素列下标j和非零元素的列下标j相同
			//p->i == i && p->j == j 表示待输出的元素是非零元素 
			if(k <= M.tu && p->i == i && p->j == j){
				
				//输出非零元
				printf("%3d", p->e);
				
				//p指向下一个非零元素
				p++;
				
				//计数器k+1
				k++; 
			}//if
			else{  //输出0元素 
				printf("%3d", 0);
			}//else
		}//for
		
		//这一行的元素全部输出完成，该换行了 
		printf("\n");
	}//for
}//PrintSMatrix_1

//------------> 4.复制稀疏矩阵M 

/*
    函数：CopySMatrix
    参数：TSMatrix M 被复制的稀疏矩阵M
          TSMatrix &T 复制得到的稀疏矩阵T 
    返回值：无
    作用：由稀疏矩阵M复制得到T
*/
void CopySMatrix(TSMatrix M , TSMatrix &T){
	
	T = M; 
}//CopySMatrix

//------------> 5.求两稀疏矩阵之和

/*
    函数：compare
    参数：int c1 被比较数c1
	      int c2 被比较数c2 
    返回值：当c1<c2时返回-1，c1=c2时返回0 c1>c2时返回1 
    作用：矩阵相加函数会用到,用于比较两数大小 
*/
int compare(int c1 , int c2){
	
	if(c1 < c2){
		return -1;
	}//if
	else if(c1 == c2){
		return 0;
	}//else if
	else{
		return 1;
	}//else 
}//compare

/*
    函数：AddSMatrix
    参数：TSMatrix M 稀疏矩阵M（加数） 
          TSMatrix N 稀疏矩阵N（另一个加数）
		  TSMatrix &Q 稀疏矩阵Q的引用，带回M+N的和 
    返回值：状态码，操作成功返回OK，否则返回ERROR 
    作用：求稀疏矩阵之和Q = M + N,最终计算结果保存在矩阵Q中
*/
Status AddSMatrix(TSMatrix M, TSMatrix N, TSMatrix &Q){
	
	//m和n分别表示稀疏矩阵M和N的下标
	//q记录了M+N得到的矩阵Q中非零元的个数 
	int m = 1 , n = 1 , q = 0;
	
	//矩阵求和操作要求两个矩阵的行列数必须分别相同 
	//若两个稀疏矩阵的行列数不同，就不能进行相加操作
	if(M.mu != N.mu || M.nu != N.nu){
		return ERROR; 
	}//if
	
	//最终的结果矩阵行数和列数一定分别等于任意一个被加矩阵的行数和列数 
	Q.mu = M.mu;
	Q.nu = M.nu;
	
	//矩阵M和N的元素都没有处理完
	while(m <= M.tu && n <= N.tu){
		
		//比较矩阵M和N行的大小 
		int result_i = compare(M.data[m].i, N.data[n].i); 
		
		if(result_i == -1) { //M.i < N.i 
			//将矩阵M当前的元素赋值给矩阵Q
			Q.data[++q] = M.data[m++];  
		}//if 
		else if(result_i == 0) { //M.i = N.i 
		
			//如果行的大小相同则继续比较矩阵M和N列的大小
			int result_j = compare(M.data[m].j, N.data[n].j);
			
			if(result_j == -1) { //M.j < N.j
			
				//将矩阵M当前的元素赋值给矩阵Q
				Q.data[++q] = M.data[m++]; 
			}//if
			else if(result_j == 0) { //M.j = N.j 
				
				//先将矩阵M对应位置的数据存入矩阵Q 
				Q.data[++q] = M.data[m++];
				
				//矩阵M和矩阵N对应位置元素值相加 
		        Q.data[q].e += N.data[n++].e;
				
				//如果M和N相加得到的和为0，则不将其存入压缩矩阵
				if(Q.data[q].e == 0){ 
					q--;
				}//if
			}//else if
			else { //M.j > N.j
			
				//将矩阵N当前的元素赋值给矩阵Q
				Q.data[++q] = N.data[n++]; 
			}//else
		}//else if
		else {//M.i > N.i 
		
			//将矩阵N的当前元素赋给矩阵Q  
			Q.data[++q] = N.data[n++];
		}//else 
	}//while
	
	//矩阵M的元素没有处理完，但是N已经处理完了，需要继续处理M中剩余的元素 
	while(m <= M.tu){ 
		Q.data[++q] = M.data[m++]; 
	}//while 
	
	//矩阵N的元素没有处理完，但是M已经处理完了，需要继续处理N中剩余的元素  
	while(n <= N.tu){
		Q.data[++q] = N.data[n++]; 
	}//while 
	
	//计数器q记录的是矩阵Q的非零元素个数
	Q.tu = q;
	
	//检查矩阵Q的非零元素个数是否超出最大值 
	if(q > MAXSIZE){
		return ERROR;
	}//if
	
	//操作成功 
	return OK; 
}//AddSMatrix

//------------> 6.求两稀疏矩阵之差 

/*
    函数：SubTSMatrix
    参数：TSMatrix M 稀疏矩阵M（被减数） 
          TSMatrix N 稀疏矩阵N（减数）
		  TSMatrix &Q 稀疏矩阵Q的引用，带回M-N的差 
    返回值：状态码，操作成功返回OK，否则返回ERROR 
    作用：求稀疏矩阵之差Q = M - N,最终计算结果保存在矩阵Q中
*/
Status SubTSMatrix(TSMatrix M , TSMatrix N , TSMatrix &Q){
	
	//减去一个数相当于加上相反数 
	//M.e - N.e  <=> M.e + (-N.e)
	for(int i = 1; i <= N.tu; i++){
		N.data[i].e *= -1;
	}//for
	
	//调用AddSMatrix操作可以完成减法操作 
	return AddSMatrix(M, N, Q);
}//SubTSMatrix 

//------------> 7.求稀疏矩阵的转置

/*
    函数：TransposeSMatrix
    参数：TSMatrix M 稀疏矩阵M（原始矩阵） 
          TSMatrix T 稀疏矩阵T（转置后的矩阵T）
    返回值：状态码，操作成功返回OK，否则返回ERROR 
    作用：求稀疏矩阵M的转置矩阵T
*/
void TransposeSMatrix(TSMatrix M , TSMatrix &T) {
	
	//q是个临时变量，作用相当于计数器 
	int q;
	
	//矩阵转置不会导致矩阵行数、列数和非零元总数发生改变 
	T.mu = M.nu;
	T.nu = M.mu; 
	T.tu = M.tu;
	
	//如果非零元个数不为0 
	if(T.tu != 0){
		q = 1;
		for(int col = 1;col <= M.nu; ++col){
			for(int p = 1; p <= M.tu; ++p){
				if(M.data[p].j == col){
					
					//行列互换 
					T.data[q].i = M.data[p].j;
					T.data[q].j = M.data[p].i;
					T.data[q].e = M.data[p].e;
					++q;
				}//if
			}//for 
		}//for 
	}//if 
}//TransposeSMatrix

//------------> 8.求两稀疏矩阵之积 

/*
    函数：MultSMatrix
    参数：TSMatrix M 稀疏矩阵M（因数） 
          TSMatrix N 稀疏矩阵N（因数）
          TSMatrix &Q 稀疏矩阵引用Q （积） 
    返回值：状态码，操作成功返回OK，否则返回ERROR 
    作用：求稀疏矩阵的乘积 Q = M ×N 
*/
Status MultSMatrix(TSMatrix M , TSMatrix N , TSMatrix &Q){
	
	//Nc和Tc分别用于指向矩阵N和矩阵T的临时数组 
	ElemType *Nc , *Tc;
	
	//临时矩阵T，最终的结果就是T的转置 
	TSMatrix T;
	
	//只有矩阵M的列数等于矩阵N的行数时，矩阵的乘法才有意义
	//这是矩阵乘法的运算规则决定的 
	if(M.nu != N.mu) { 
		return ERROR;
	}//if 
	
	//临时矩阵T是Q的转置矩阵（行列总数互换） 
	T.nu = M.mu;
	T.mu = N.nu;
	T.tu = 0;
	
	//Nc为矩阵N一列的临时数组（非压缩,[0]不用） 
	//Nc存储的就是把压缩的矩阵N还原成包含非零元的不被压缩的矩阵 
	Nc = (ElemType *)malloc((N.mu + 1) * sizeof(ElemType));
	
	//Tc为矩阵T一列的临时数组（非压缩,[0]不用）
	//Tc存储了不被压缩的矩阵N与矩阵M做乘法之后的临时结果 
	Tc = (ElemType *)malloc((M.mu + 1) * sizeof(ElemType)); 
	
	//创建临时数组不成功
	if(!Nc || !Tc){ 
		exit(ERROR); 
	}//if 
	
	//开始进行矩阵乘法 
	for(int i = 1; i <= N.nu; i++){
		
		//矩阵Nc的初值为0，Nc将会存储N的某一列转换为行之后的结果 
		for(int j = 1;j <= N.mu; j++){
			Nc[j] = 0;
		}//for
		
		//创建临时数组Tc的初值为0,[0]不用
		for(int j = 1;j <= M.nu; j++){
			Tc[j] = 0; 
		}//for
		
		//矩阵乘法是M的行与N的列上对应的元素去做乘法
		//这一步是要把N的三元组表示的列转变成数组表示的行
		//存储在Nc中，非零元素会覆盖掉初值0。 
		//最终Nc就是把三元组存储的非零元转化成矩阵的某一行
		//Nc中会既存在0元素也存在非零元素，变成真实的矩阵中的形式
		//这种做法的目的是为了方便我们后期的乘法计算 
		for(int j = 1; j <= N.tu; j++){
			
			//属于第i列
			if(N.data[j].j == i){
				//根据其所在行将元素值赋值给相应的Nc
			    Nc[N.data[j].i] = N.data[j].e; 
			}//if 
		}//for
		
		//在得到Nc的值之后，Tc的值就等于Nc的值和稀疏矩阵M中的
		//对应位置的每个值相乘 
		for(int j = 1; j <= M.tu; j++){
			
			//Tc中存N的第i列与M相乘的结果 
			Tc[M.data[j].i] += M.data[j].e * Nc[M.data[j].j];
		}//for
		
		//将Tc数组中的值拷贝到矩阵T中 
		for(int j = 1; j <= M.mu; j++){
			
			//矩阵T是压缩存储的稀疏矩阵，而Tc是不被压缩的矩阵
			//需要从Tc中挑选出非零元素，填入稀疏矩阵T的三元组表 
			if(Tc[j] != 0){
				T.data[++T.tu].e = Tc[j];
				
				//注意：矩阵T的行数应当与矩阵M的总行数相等，
				//      矩阵T的列数应该与矩阵N的总列数相等
				//      但是此时的i代表的却是N的列数，j代表的是M的行数，
				//      所以此时的T并不是最终的矩阵乘法结果，
				//      而是正确结果的转置，所以我们需要再转置
				//      一次就能得到正确的乘法结果了。 
				T.data[T.tu].i = i;
				T.data[T.tu].j = j;
			}//if
		}//for 
	}//for
	
	//非零元素太多
	if(T.tu > MAXSIZE){ 
		return ERROR;	
	}//if
	
	//将T的转置赋给Q，得出矩阵相乘的最终结果 
	TransposeSMatrix(T, Q);
	
	//销毁临时矩阵T
	DestorySMatrix(T);
	
	//释放动态数组Tc和Nc 
	free(Tc); 
	free(Nc);
	
	//操作成功 
	return OK;
}//MultSMatrix 

//------------------------------------------主函数--------------------------------------------- 

int main(int argc , char **argv){
	printf("\n----------------------------稀疏矩阵的存储 -> 三元组表--------------------------\n");
	
	TSMatrix A,B,C;
	
	printf("->创建矩阵A：\n");
	CreateSMatrix(A);
	PrintSMatrix(A);
	
	printf("->由矩阵A复制得到矩阵B：\n");
	CopySMatrix(A,B);
	PrintSMatrix_1(B);
	
	DestorySMatrix(B);
	printf("->销毁矩阵B后：\n");
	PrintSMatrix_1(B);
	printf("\n");
	
	printf("->创建矩阵B2：（与矩阵A的行、列数相同，%d行%d列）\n", A.mu, A.nu);
	CreateSMatrix(B);
	PrintSMatrix_1(B);
	
	AddSMatrix(A, B, C);
	printf("->矩阵C1（A+B）：\n");
	PrintSMatrix_1(C); 
	
	SubTSMatrix(A, B, C);
	printf("->矩阵C2（A-B）：\n");
	PrintSMatrix_1(C); 
	
	TransposeSMatrix(A, C);
	printf("->矩阵C3（A的转置）：\n");
	PrintSMatrix_1(C); 
	
	printf("->创建矩阵A2\n");
	CreateSMatrix(A);
	PrintSMatrix_1(A);
	printf("->创建矩阵B3：（行数应与矩阵A2的列数相同=%d）\n", A.nu);
	CreateSMatrix(B);
	PrintSMatrix_1(B);
	MultSMatrix(A, B, C);
	printf("->矩阵C4（A ×B）：\n");
	PrintSMatrix_1(C);
}//main

/* 运行结果 
	

----------------------------稀疏矩阵的存储 -> 三元组表--------------------------
->创建矩阵A：
请输入矩阵的行数、列数、非零元素的个数：3,3,2
请按行序顺序输入第1个非零元素所在的行（1-3），列(1-3)，和元素值
（行和列的顺序必须是从小到大，不能打乱顺序随便乱输）：
1,2,1
请按行序顺序输入第2个非零元素所在的行（1-3），列(1-3)，和元素值
（行和列的顺序必须是从小到大，不能打乱顺序随便乱输）：
2,2,2
稀疏矩阵M有3行3列2个非零元素。
 行  列   元素值
 1   2       1
 2   2       2
->由矩阵A复制得到矩阵B：
  0  1  0
  0  2  0
  0  0  0
->销毁矩阵B后：

->创建矩阵B2：（与矩阵A的行、列数相同，3行3列）
请输入矩阵的行数、列数、非零元素的个数：3,3,1
请按行序顺序输入第1个非零元素所在的行（1-3），列(1-3)，和元素值
（行和列的顺序必须是从小到大，不能打乱顺序随便乱输）：
1,2,1
  0  1  0
  0  0  0
  0  0  0
->矩阵C1（A+B）：
  0  2  0
  0  2  0
  0  0  0
->矩阵C2（A-B）：
  0  0  0
  0  2  0
  0  0  0
->矩阵C3（A的转置）：
  0  0  0
  1  2  0
  0  0  0
->创建矩阵A2
请输入矩阵的行数、列数、非零元素的个数：2,4,6
请按行序顺序输入第1个非零元素所在的行（1-2），列(1-4)，和元素值
（行和列的顺序必须是从小到大，不能打乱顺序随便乱输）：
1,1,1
请按行序顺序输入第2个非零元素所在的行（1-2），列(1-4)，和元素值
（行和列的顺序必须是从小到大，不能打乱顺序随便乱输）：
1,3,3
请按行序顺序输入第3个非零元素所在的行（1-2），列(1-4)，和元素值
（行和列的顺序必须是从小到大，不能打乱顺序随便乱输）：
1,4,-1
请按行序顺序输入第4个非零元素所在的行（1-2），列(1-4)，和元素值
（行和列的顺序必须是从小到大，不能打乱顺序随便乱输）：
2,1,2
请按行序顺序输入第5个非零元素所在的行（1-2），列(1-4)，和元素值
（行和列的顺序必须是从小到大，不能打乱顺序随便乱输）：
2,2,1
请按行序顺序输入第6个非零元素所在的行（1-2），列(1-4)，和元素值
（行和列的顺序必须是从小到大，不能打乱顺序随便乱输）：
2,4,2
  1  0  3 -1
  2  1  0  2
->创建矩阵B3：（行数应与矩阵A2的列数相同=4）
请输入矩阵的行数、列数、非零元素的个数：4,3,10
请按行序顺序输入第1个非零元素所在的行（1-4），列(1-3)，和元素值
（行和列的顺序必须是从小到大，不能打乱顺序随便乱输）：
1,1,4
请按行序顺序输入第2个非零元素所在的行（1-4），列(1-3)，和元素值
（行和列的顺序必须是从小到大，不能打乱顺序随便乱输）：
1,2,1
请按行序顺序输入第3个非零元素所在的行（1-4），列(1-3)，和元素值
（行和列的顺序必须是从小到大，不能打乱顺序随便乱输）：
2,1,-1
请按行序顺序输入第4个非零元素所在的行（1-4），列(1-3)，和元素值
（行和列的顺序必须是从小到大，不能打乱顺序随便乱输）：
2,2,1
请按行序顺序输入第5个非零元素所在的行（1-4），列(1-3)，和元素值
（行和列的顺序必须是从小到大，不能打乱顺序随便乱输）：
2,3,3
请按行序顺序输入第6个非零元素所在的行（1-4），列(1-3)，和元素值
（行和列的顺序必须是从小到大，不能打乱顺序随便乱输）：
3,1,2
请按行序顺序输入第7个非零元素所在的行（1-4），列(1-3)，和元素值
（行和列的顺序必须是从小到大，不能打乱顺序随便乱输）：
3,3,1
请按行序顺序输入第8个非零元素所在的行（1-4），列(1-3)，和元素值
（行和列的顺序必须是从小到大，不能打乱顺序随便乱输）：
4,1,1
请按行序顺序输入第9个非零元素所在的行（1-4），列(1-3)，和元素值
（行和列的顺序必须是从小到大，不能打乱顺序随便乱输）：
4,2,3
请按行序顺序输入第10个非零元素所在的行（1-4），列(1-3)，和元素值
（行和列的顺序必须是从小到大，不能打乱顺序随便乱输）：
4,3,4
  4  1  0
 -1  1  3
  2  0  1
  1  3  4
->矩阵C4（A ×B）：
  9 -2 -1
  9  9 11

--------------------------------
Process exited with return value 0
Press any key to continue . . .

*/
