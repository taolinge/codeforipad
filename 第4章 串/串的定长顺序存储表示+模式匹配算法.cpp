/*********************************串的定长顺序存储抽象数据类型ADT定义*****************************************
ADT String 
{
       数据对象：D ={ai | ai∈Characterset,(i=1,2,…,n, n≥0)}
       数据关系：R1 = {＜ai-1,ai＞|ai-1,ai ∈ D,(i=2,3,…,n)}   
       基本操作：
	                StrAssign (&T, chars)
                    初始条件：chars 是字符串常量。
                    操作结果：把 chars 赋为T的值。
                    StrCopy (&T, S)
                    初始条件：串 S 存在。
                    操作结果：由串 S 复制得串T。
                    DestroyString (&S)
                    初始条件：串 S 存在。
                    操作结果：串 S 被销毁。
                    StrEmpty (S)
                    初始条件：串 S 存在。
                    操作结果：若 S 为空串，则返回true，否则返回 false。
                    StrCompare (S, T)
                    初始条件：串 S和T存在。
                    操作结果：若S > T，则返回值> 0；若S = T，则返回值= 0；若S < T，则返回值< 0。
                    StrLength (S)
                    初始条件：串 S 存在。
                    操作结果：返回 S 的元素个数，称为串的长度。
                    Concat (&T, S1, S2)
					初始条件：串 S 1和S2存在。
                    操作结果：用T返回由S1和S2联接而成的新串。
                    SubString (&Sub, S, pos, len)
                    初始条件：串 S 存在，1≤pos≤StrLength(S) 且  0≤len≤StrLength(S)-pos+1。
                    操作结果：用Sub返回串S的第 pos 个字符起长度为len的子串。
                    Index (S, T, pos)
                    初始条件：串S和T存在，T是非空串，1≤pos≤StrLength(S)。
                    操作结果：若主串 S 中存在和串 T 值相同的子串, 则返回它在主串 S 中第pos个字符之后第一次出现的位置;否则函数值为0。
                    Replace (&S, T, V)
					初始条件：串S, T和 V 均已存在，且 T 是非空串。
                    操作结果：用V替换主串S中出现的所有与（模式串）T相等的不重叠的子串。
                    StrInsert (&S, pos, T)
					初始条件：串S和T存在，1≤pos≤StrLength(S)＋1。
                    操作结果：在串S的第pos个字符之前插入串T。
                    StrDelete (&S, pos, len)
					初始条件：串S存在1≤pos≤StrLength(S)-len+1。
                    操作结果：从串S中删除第pos个字符起长度为len的子串。 
                    ClearString (&S)
					初始条件：串S存在。
                    操作结果：将S清为空串。            
} ADT String 
   
    
*************************************************************************************************************/

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>引入头文件<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <stdio.h>   //使用了标准库函数 printf(),scanf()
#include <stdlib.h>  //使用了动态内存分配函数 malloc(),free()
#include <string.h>  //使用了字符串处理函数strlen() 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>自定义符号常量<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 
 
#define OVERFLOW -2         //内存溢出错误常量
#define OK 1                //表示操作正确的常量 
#define ERROR 0             //表示操作错误的常量
#define TRUE 1              //表示逻辑正确的常量 
#define FALSE 0             //表示逻辑错误的常量
#define MAXSTRLEN 255       //最大串长
#define DestoryString ClearString  //DestoryString()和ClearString()作用相同 

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>自定义数据类型<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

typedef int Status;       //状态参量
typedef char ElemType;    //元素类型 

// 串的定长顺序存储C语言表示 
typedef unsigned char SString[MAXSTRLEN + 1]; // 0号单元存放串的长度，1号单元开始存储串值字符序列 
 
//-------------------------------------------串的主要操作--------------------------------------------------

/*
	函数：Print
	参数：ElemType e 待访问元素 
	返回值：无 
	作用：访问元素，也就是打印输出 
*/
void Print(ElemType e){
	printf("%c",e); 
}//Print 

/*
	函数：StrTraverse
	参数：SString T 待访问元素
	      void(* Visit)(ElemType) 函数指针，可以指向一个函数 
	返回值：无 
	作用：（串遍历）打印输出串的内容 
*/
void StrTraverse(SString T, void(* Visit)(ElemType)){ 
	 
	for(int i = 1; i <= T[0]; i++) { 
	    Visit(T[i]);
	}//for
	 
	printf("\n");
}//StrTraverse

/*
	函数：StrAssign
	参数：SString T 定长串，采用我们自定义的数据类型，0号单元存放串长，
	                字符数据从1号单元开始存储。 
		  chars 指向存储字符类型数据的指针，即指向一个已经存在的字符串， 
		        这个串采用C语言默认的方式，数据从0号单元开始存储，以'\0'作为结束标志。 
	返回值：状态码，OK表示操作成功 
	作用：（生成串）生成一个其值等于chars的串T
*/
Status StrAssign(SString T, char *chars){
	
	int i;
	
	//越界判断，判断串长是否超过最大值 
	if(strlen(chars) > MAXSTRLEN){
		return ERROR;
	}   
	else{
		//0号存储单元存储了串的长度 
		T[0] = strlen(chars); 
		
		//复制chars指向的字符串的内容到串T 
		for(i = 1; i <= T[0]; i++) {
			
			//i是从1开始的，所以要-1，因为chars的字符数据是从0开始的
		    T[i] = *(chars + i - 1);  
		}//for 
		 
		return OK;
	}//else 
}//StrAssign

/*
	函数：StrCopy
	参数：SString T 复制后得到的串（目的地） 
		  SString S 被复制的串（源） 
	返回值：无
	作用：（串拷贝）由串S复制得到串T
*/
void StrCopy(SString T, SString S){

	for(int i = 0; i <= S[0]; i++){ 
	    T[i] = S[i]; 
	}//for 
}//StrCopy 

/*
	函数：StrEmpty
	参数：SString S 目标串 
	返回值：状态码，TRUE表示串S是空串，ERROR表示串S不是空串 
	作用：（判空串）若S为空串，则返回TRUE，否则返回FALSE
*/
Status StrEmpty(SString S){
	
	//0号存储单元记录了串的长度 
	if(S[0] == 0) {
		return TRUE;
	}//if
	else {
		return FALSE; 	
	}//else
}//StrEmpty

/*
	函数：StrCompare
	参数：SString S 被比较串1 
	      SString T 被比较串2
	      串S和串T必须存在
	返回值：若S > T，返回值 > 0 ，若S = T，返回值 = 0，若S < T，返回值 < 0
	作用：（串比较）串S和串T比较，判断大小的依据是ASCII码。 
*/
int StrCompare(SString S, SString T){
	
	//如果两串串长相等，则逐个比较每个字符 
	for(int i = 1; i <= S[0] && i <= T[0]; ++i) {
		
		//通过对两个串中对应位置字符的ASCII码值作差进行比较 
		if(S[i] != T[i]) {
			return S[i] - T[i];
		} //if
	} //for
	
	//如果两串串长不相等，则直接返回两串串长之差 
    return S[0] - T[0];
}//StrCompare

/*
	函数：StrLength
	参数：SString S 目标串
	返回值：串S的元素个数
	作用：（求串长）求出串S的长度，即串S中有效字符的个数 
*/
int StrLength(SString S){
	
	//0号存储单元不存储数据，记录的是串的长度 
	return S[0]; 
}//StrLength

/*
	函数：ClearString
	参数：SString S 目标串
	返回值：无
	作用：（清空串）将串S清成空串 
*/
void ClearString(SString S) {
	
	//注意：由于我们判断串是否存在有效字符以及计算有效字符个数的方式是依靠0号单元的值，
	//      所以最简单的清空的方式是直接让存储串长度的0号单元置零 ，但是从1号单元开始的
	//      数据存储单元中可能还存储着一些字符数据，只不过它们已经被废弃了，如果对串进行
	//      追加或者在尾部插入一些字符，就可以覆盖掉这些失效字符，所以无须理会字符失效问题。 
	//      不需要将失效字符处理成'\0'。 
	S[0] = 0;  //令串长为0 
}//ClearString

/*
	函数：Concat
	参数：SString S1 待连接串1 
	      SString S2 待连接串2 
	      SString T  带回串连接结果 
	返回值：若未截断，则返回TRUE；否则返回FALSE
	作用：（串连接）用T返回S1和S2联接而成的新串 
*/
Status Concat(SString T, SString S1, SString S2){
	
	//i声明在这里不是好的写法，应该将i写在for循环中，有利于缩短i的作用域，及早回收其内存空间。
	//但是由于C语言不兼容这种写法，考虑到兼容性所以将i写在外面。（C++支持这种写法） 
	int i;
	
	//如果S1和S2连接后长度之和没有超过串的最大长度则正常连接，不需要截断
	//否则，就必须截断后再存入串T，使T的长度小于串的最大长度 
	if(S1[0] + S2[0] <= MAXSTRLEN){  //未截断 
		
		//复制串S1到串T 
		for(i = 1; i <= S1[0]; i++) { 
		    T[i] = S1[i];
		}//for
		
		//复制串S2追加到串T后面 
		for(i = 1; i <= S2[0]; i++) { 
		    T[S1[0] + i] = S2[i];
		}
		
		//计算出串T的串长并存入串T的0号存储单元 
		T[0] = S1[0] + S2[0];
		
		return TRUE; //串未被截断 
	}//if
	else{  //截断S2 
	
		//考虑到S1可能也会超出最大串长，先判断
		int S1ActualValue = S1[0]; //串S1实际长度
		 
		if(S1[0] >= MAXSTRLEN) {
			S1ActualValue = MAXSTRLEN;
		}
		
		//复制串S1到串T 
		for(i = 1; i <= S1ActualValue; i++) { 
		    T[i] = S1[i];
		}
		
		//复制串S2追加到串T后面，但此时串S2被截断
		//如果S1已经超出最大串长，则S2不会被复制到T的末尾 
		for(i = 1; i <= MAXSTRLEN - S1[0]; i++) { 
		    T[S1[0] + 1] = S2[i];
		}
		
		//由于串S2被截断，所以串T长度为最大串长，将其存入0号存储单元 
		T[0] = MAXSTRLEN;
		
		return FALSE; //串被截断 
	}//else 
}//Concat 

/*
	函数：SubString
	参数：SString Sub 返回截取的子串 
	      SString S 待截取的主串，截取操作不会影响主串原有的数据 
	      pos 开始截取位置 
		  len 截取子串的长度 
	返回值：状态码， OK表示操作成功 
	作用：（取子串）Sub返回串S的自第pos个字符起长度为len的子串
*/
Status SubString(SString Sub, SString S, int pos, int len){
	
	//i声明在这里不是好的写法，应该将i写在for循环中，有利于缩短i的作用域，及早回收其内存空间。
	//但是由于C语言不兼容这种写法，考虑到兼容性所以将i写在外面。（C++支持这种写法） 
	int i;
	
	//pos或len非法
	if(pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos + 1) {
	    return ERROR;
	}//if 
	
	//复制主串中的指定字符到子串 
	for(i = 1; i <= len; i++) { 
	    Sub[i] = S[pos + i - 1];
	}//for
	
	//设置子串长度 
	Sub[0] = len;
	
	return OK; 
}//SubString 

/*
	函数：Index
	参数：SString S 主串 
	      SString T 子串 非空
	      pos 主串扫描开始位置1 <= pos <= StrLength(S) 
	返回值：子串T在主串S中第pos个字符之后的位置，返回0表示没有找到 
	作用：（串定位）找出子串T在主串S中第pos个字符之后的位置。 
*/
int Index(SString S, SString T, int pos){
	
	//i和j声明在这里不是好的写法，应该将它，它们写在for循环中，有利于缩短作用域，及早回收其内存空间。
	//但是由于C语言不兼容这种写法，考虑到兼容性所以将其写在外面。（C++支持这种写法） 
	int i, j; //i是主串的下标，j是子串的下标 
	
	//必须保证pos的值合法操作才有意义 
	if(1 <= pos && pos <= S[0]){
		i = pos; //i的初始值就是模式匹配的起始扫描位置，也就是pos 
		j = 1;   //j的初始值是第一个字符的存储单元所在位置，也就是0 
		
		//扫描主串，匹配子串 
		while(i <= S[0] && j <= T[0]) {
			
		 	//主串和子串对应位置字符相等则继续比较后继字符
		    if(S[i] == T[j]){   
		    	++i; //主串下标i向右移动 
				++j; //子串下标j向右移动 
		    }//if
			else{   //对应位置字符不相等则下标回退重新开始匹配 
				i = i - j + 2; //下标i回溯 
				j = 1; //下标j回溯 
			}//else
		}//while 
		
		//j超出模式串长度【也就是T[0]】表示模式串和主串匹配成功了 
		if(j > T[0]) { 
		    return i - T[0]; //返回模式串在主串中的首次匹配位置 
		}//if
		else { 
		    return 0; //返回0表示匹配失败，主串中没有匹配到子串 
		}//else
	}//if 
}//Index

/*
	函数：StrInsert
	参数：SString S 被插入串 ，存在 
	      SString T 插入的内容， 存在 
	      pos 插入位置，1 <= pos <= StrLength(S) + 1 
	返回值：状态码，完全插入返回TRUE，部分插入返回FALSE 
	作用：（串插入）在串S的第pos个字符之前插入串T 
*/
Status StrInsert(SString S, int pos, SString T){ 

	//i声明在这里不是好的写法，应该将i写在for循环中，有利于缩短i的作用域，及早回收其内存空间。
	//但是由于C语言不兼容这种写法，考虑到兼容性所以将i写在外面。（C++支持这种写法） 
	int i;
	
	//检查pos参数是否合法 
	if(pos < 1 || pos > S[0] + 1) {
	    return ERROR;
	}//if
	
	//检查插入后串的长度是否超过最大串长，如果超过，就部分插入，否则完全插入 
	if(S[0] + T[0] <= MAXSTRLEN){  //完全插入 
	
		//将插入位置后面的字符向后移动T[0]个位置，腾出插入位置 
		for(i = S[0]; i >= pos; i--) { 
		    S[i + T[0]] = S[i];
		}//for 
		
		//将插入内容T复制到腾出的位置上 
		for(i = pos; i < pos + T[0]; i++) {
		    S[i] = T[i - pos + 1];
		}//for
		
		//调整待插入串的串长，增加长度等于插入内容的长度 
		S[0] += T[0];
		
		//完全插入 
		return TRUE;
	}//if 
	else{  //部分插入 
		
		//这段代码也是腾出插入空间，与完全插入不同的地方是：
		//由于主串在插入后会超出最大串长，而插入操作又必须有足够的空间
		//所以只好在腾出空间时将原字符串S中在插入后会超出最大串长的部分舍弃掉。 
		for(i = MAXSTRLEN; i >= pos + T[0]; i--) { 
		    S[i] = S[i - T[0]];
		}//for
		
		//将T的内容复制到串S的pos位置之前已经腾出的空间中 
		for(i = pos; i < pos + T[0] && i <= MAXSTRLEN; i++) {
		    S[i] = T[i - pos + 1];
		}//for
		
		//求出最大串长 
		S[0] = MAXSTRLEN;
		
		//部分插入 
		return FALSE; 
	}//else
}//StrInsert

/*
	函数：StrDelete
	参数：SString S 待删除串 
	      pos 删除起始位置，1 <= pos <= StrLength(S) - len + 1
	      len 被删除内容的长度，也就是待删除字符的个数 
	返回值：状态码，删除成功返回OK，否则返回ERROR 
	作用：（串删除）从串S中删除自第pos个字符起长度为len的子串
*/
Status StrDelete(SString S, int pos, int len){
	
	//i声明在这里不是好的写法，应该将i写在for循环中，有利于缩短i的作用域，及早回收其内存空间。
	//但是由于C语言不兼容这种写法，考虑到兼容性所以将i写在外面。（C++支持这种写法） 
	int i;
	
	//检查参数pos和len是否合法 
	if(pos < 1 || pos > S[0] - len + 1 || len < 0) { 
	    return ERROR; //操作失败 
	}//if
	
	//从S串的pos+len位置开始，将后面的所有字符全部前移len个长度，
	//也就是说要覆盖掉原位置数据，这样就算执行了删除操作，
	//但是S[0]-len ~ S[0]位置的字符并没有真正彻底抹掉或者恢复初始值
	//这段区域中的数据仍然存在，只不过由于顺序定长串的各种操作（主要是读取）
	//全部依赖S[0]存储的串长来作为合法范围的界定，
	//所以即使S[0]后面的内存区域中存有数据也不会被识别、读取和操作，
	//所以即使不在删除操作后清除和重置这些数据，程序也不会出现问题。 
	for(i = pos + len; i <= S[0]; i++) { 
	    S[i - len] = S[i];
	}//for
	
	//删除长度为len的串后，S串的长度应该对应减小len 
	S[0] -= len;
	
	//操作成功 
	return OK; 
}//StrDelete

/*
	函数：Replace
	参数：SString S 主串，串S必须存在 
	      SString T 用于匹配的模式串T，串T必须存在且非空 
	      SString V 替换成V存储的内容，串V必须存在 
	返回值：状态码，替换成功返回OK，否则返回ERROR 
	作用：（串替换）用V替换主串S中出现的所有与T相等的不重叠子串 
*/
Status Replace(SString S, SString T, SString V){
	
	//从串S的第一个字符起查找串T 
	int i = 1;  //i是主串中查找的下标，控制着查找向下进行 
	
	//由于替换是用在模式匹配成功位置删除串T再插入串V的方式实现的，
	//所以需要有一个标志位记录插入和删除的操作结果，一旦操作出错，
	//就要终止后续的替换操作，已经执行过的替换操作结果仍然保存 
	Status k; 
	
	//判断T是否是空串，ADT定义规定T必须非空 
	if(StrEmpty(T)){ //T是空串
	    return ERROR;
	}//if
	
	//由于主串和子串模式匹配成功的次数可能是多次，所以要循环处理 
	do{
		//首先要找到最新的模式匹配成功位置，
		//i为从上一个i之后找到子串T的位置
		i = Index(S, T, i);
		//串S中存在串T，则将其替换掉 
		if(i){  //if(i) <=> if(i != 0) 
			
			//从串T在串S中匹配成功的位置开始，删除串T的内容 
			k = StrDelete(S, i, StrLength(T));
			if(!k) {
				return ERROR;
			}			
			
			//从串T在串S中匹配成功的位置开始，插入串V的内容 
			k = StrInsert(S, i, V);
			
			//插入操作返回0表示是部分插入 ，即不能完全插入
			if(!k) { //if(!k) <=> if(k == 0) <=> if(k == FALSE)
				//部分插入说明主串已经接近最大串长，在删除串T后
				//由于空间不足无法再插入串V，那么此次和后续的
				//替换操作都会失败，所以循环没必要再继续下去了 
			    return ERROR;
			}//if 
			
			//修改i的值，跳过替换后位置，在插入的串V后面继续查找串T 
			//应该注意到一个问题：若V是T的一个子串的话，那么这种跳过方式
			//就会使一些原本可以匹配的位置被跳过，这样就会成了多次且多遍替换。
			//如果加上这行代码就不会多遍替换，只替换一遍 
			//i += StrLength(V); 
		}//if
	}while(i); //while(i) <=> while(i != 0) 
	
	//替换操作成功 
	return OK;
}//Replace

//-----------------------串的模式匹配算法------------------------------ 

//-----------------BF(朴素)算法-------------------

/*
	函数：Index_BF
	参数：SString S 主串
	      SString T 子串，非空 
	      pos 模式匹配起始位置，1 <= pos <= StrLength(S) 
	返回值：返回子串T在主串S中第pos个字符之后的位置，若不存在，则函数值为0
	作用：（模式匹配BF算法）返回子串T在主串S中第pos个字符之后的位置
*/
int Index_BF(SString S, SString T, int pos){   //BF算法 

	//i是模式匹配在主串中的下标，j是子串中的下标 
	int i = pos, j = 1;
	
	//从主串的pos位置开始进行模式匹配 
	while(i <= S[0] && j <= T[0]){
		
		//主串和子串对应位置字符相同，则继续向后匹配 
		if(S[i] == T[j]){
			++i;
			++j;
		}//if 
		else{ //若对应位置字符不同，i和j回溯 
			i = i - j + 2;
			j = 1;
		}//else
	}//while
	
	//j超出模式串长度T[0]表示模式匹配成功 
	if(j > T[0]) {
		return i-T[0];
	}//if
	else {
		return 0; 
	}//else
}//Index_BF  

//-----------------KMP(改进)算法------------------ 

/*
	函数：getNext
	参数：SString T 定长串
		  next 存储next[]值。 
	返回值：无
	作用：求模式串T的next函数值并存入数组next[]
*/
void getNext(SString T, int next[]){
	
	//T[i]表示后缀的单个字符 T[j]表示前缀的单个字符 
	int i = 1, j = 0;
	
	//next[]定义规定next[1]=0 
	next[1] = 0; 
	    
	while(i < T[0]) {  //T[0]存储的是串的长度，不存数据
	
		//前缀和后缀的字符相等
	    if(j == 0 || T[i] == T[j]){ 
	    	++i;
	    	++j;
	    	next[i] = j; //next[j]的值就是计算出的k 
	    }//if
		else {  //前缀和后缀的字符串不相等 
		    j = next[j]; //j回溯
		}//else 
	}//while
}//getNext 

/*
	函数：get_nextval
	参数：SString T 定长串
		  nextval 存储修正后的next数组值。 
	返回值：无
	作用：对求next[]的算法进行改进，求出模式串的next函数
	      修正值并存入数组nextval[]，进一步减少回溯 
*/
void get_nextval(SString T, int nextval[]){
	
	//T[i]表示后缀的单个字符 T[j]表示前缀的单个字符
	int i = 1, j = 0;
	
	//nextval[]定义规定nextval[1]=0 
	nextval[1] = 0;
	
	while(i < T[0]) {    //T[0]存储的是串的长度，不存数据
	
		//前缀和后缀的字符相等
	    if(j == 0 || T[i] == T[j]){  
	    	++i;
	    	++j;
	    	
	    	//KMP算法的主要改进在这里： 
	    	if(T[i] != T[j]) { //如果前后缀字符不相等
	    		
	    	    //nextval[i]的值就是计算出来的k值，和改进前相同 
				nextval[i] = j; 
	    	}//if
			else { //如果相等
				//直接沿用nextval[j]【也就是k位置的nextval[]】的值
	    	    nextval[i] = nextval[j];  
	    	}//else
	    }//if
		else { //前缀和后缀的字符串不相等 
		    j = nextval[j];  //j回溯
		}//else
	}//while
}//get_nextval

/*
	函数：Index_KMP_next
	参数：SString S 主串 
		  SString T 模式串，T非空 
		  pos 模式匹配起始位置，1 <= pos <= StrLength(S)  
		  next 存储next序列的数组 
	返回值：匹配成功时返回模式串在主串中第一次成功匹配的位置，否则返回0 
	作用：利用模式串T的next函数求T在主串S中第pos个字符之后的位置的KMP算法
	      修正值并存入数组nextval[]，进一步减少回溯 
*/
int Index_KMP_next(SString S, SString T, int pos, int next[]){   //KMP算法 
	
	//i是主串下标，j是模式串下标 
	int i = pos, j = 1;
	
	while(i <= S[0] && j <= T[0]) {
		//如果主串和子串对应位置字符相同则继续比较后继字符 
	    if(j == 0 || S[i] == T[j]){
	    	++i;
	    	++j;
	    }//if
	    else { //如果主串和子串失配，i不回溯，j回溯的位置由next[j]的值决定 
	        j = next[j];
	    }//else
	}//while
	
    //j超过模式串长度表示模式匹配成功 
    if(j > T[0]) {
	    return i - T[0]; //返回模式串在主串中第一次成功匹配的位置
	}//if 
	else { //模式匹配失败 
		return 0; 
	}//else 
	
}//Index_KMP_next

/*
	函数：Index_KMP_nextval
	参数：SString S 主串 
		  SString T 模式串，T非空 
		  pos 模式匹配起始位置，1 <= pos <= StrLength(S)  
		  next 存储next序列的数组 
	返回值：匹配成功时返回模式串在主串中第一次成功匹配的位置，否则返回0 
	作用：利用模式串T的next函数求T在主串S中第pos个字符之后的位置的KMP算法
	      修正值并存入数组nextval[]，进一步减少回溯 
*/
int Index_KMP_nextval(SString S, SString T, int pos, int nextval[]){   //KMP算法 
	
	//i是主串下标，j是模式串下标 
	int i = pos, j = 1;
	
	while(i <= S[0] && j <= T[0]) {
		//如果主串和子串对应位置字符相同则继续比较后继字符 
	    if(j == 0 || S[i] == T[j]){
	    	++i;
	    	++j;
	    }//if
	    else { //如果主串和子串失配，i不回溯，j回溯的位置由next[j]的值决定 
	        j = nextval[j];
	    }//else
	}//while  
	 
	//j超过模式串长度表示模式匹配成功 
	if(j > T[0]) {
	    return i - T[0]; //返回模式串在主串中第一次成功匹配的位置
	}//if 
	else { //模式匹配失败 
		return 0; 
	}//else 
	
}//Index_KMP_nextval

//-------------------------------------------主函数--------------------------------------------------- 

int main(int argc, char *argv[]){
	printf("\n------------------------------- 串的定长存储表示 -------------------------------\n");
	 
	int i,j;
	Status k;
	char s,c[MAXSTRLEN - 1];
	SString t,s1,s2;
	
	//从键盘输入字符，生成定长串 
	printf("测试串生成：\n");
	printf("->请输入字符串1：");  gets(c);
	if(!(StrAssign(s1, c))){
		printf("串长超过MAXSTRLEN(=%d)!\n", MAXSTRLEN);
		exit(0);
	}//if
	printf("->字符串S1的长度为 %d ,是否为空(1是，0非) %d  \n", StrLength(s1), StrEmpty(s1));
	
	//测试串拷贝 
	printf("\n测试串拷贝：\n"); 
	printf("->串S1为：");
	StrTraverse(s1, Print);
	StrCopy(s2, s1);
	printf("->拷贝S1生成的串S2为：");
	StrTraverse(s2, Print);
	
	//测试串比较 
	printf("\n测试串比较：\n");
	printf("->请输入字符串s2: ");  gets(c);
	if(!(StrAssign(s2, c))){
		printf("串长超过MAXSTRLEN(=%d)!\n", MAXSTRLEN);
		exit(0);
	}//if
	printf("->串S1为：");
	StrTraverse(s1, Print);
	printf("->串S2为：");
	StrTraverse(s2, Print);
	i = StrCompare(s1, s2);
	if(i < 0){
		s = '<';
	}//if 
	else if(i = 0) {
		s = '=';
	}//else if
	else {
		s = '>';
	}//else
	printf("->两字符串比较结果：字符串1 %c 字符串2\n", s);
	
	//测试串连接 
	printf("\n测试串连接：\n");
	printf("->串S1为：");
	StrTraverse(s1, Print);
	printf("->串S2为：");
	StrTraverse(s2, Print);
	k = Concat(t, s1, s2);
	printf("->串s1联接串s2得到的串t为：");
	StrTraverse(t, Print);
	if(k == FALSE) {
		printf("串t有截断!\n");
	}//if 
	
	//测试取子串 
	printf("\n测试取子串：\n");
	printf("->串t为：");
	StrTraverse(t, Print);
	printf("->求串t的子串，请输入子串的起始位置，子串长度: ");
	scanf("%d,%d", &i, &j);
	if(SubString(s2, t, i, j)){
		printf("->子串为：");
		StrTraverse(s2, Print); 
	}//if
	
	//测试串删除
	printf("\n测试串删除：\n"); 
	printf("->串t为：");
	StrTraverse(t, Print);
	printf("->从串t的第pos个字符起，删除len个字符，请输入pos,len：");
	scanf("%d,%d", &i, &j);
	StrDelete(t, i, j);
	printf("->删除后的串t：");
	StrTraverse(t, Print);
	
	//测试串插入 
	printf("\n测试串插入：\n");
	printf("->串S2为：");
	StrTraverse(s2, Print);
	printf("->串t为：");
	StrTraverse(t, Print);  
	i = StrLength(s2) / 2;
	StrInsert(s2, i, t);
	printf("->在串s2的第%d个字符之前插入串t后结果为:", i);
	StrTraverse(s2, Print);
	
	//测试串定位 
	printf("\n测试串定位：\n");
	printf("->主串:"); 
	StrTraverse(s2, Print);
	printf("->模式串:"); 
	StrTraverse(t, Print);
	
	i = Index(s2, t, 1);
	printf("->主串的第%d个字母起和模式串第一次匹配\n", i);
	
	//测试取子串
	printf("\n测试取子串：\n");
	printf("->串S2:"); 
	StrTraverse(s2, Print);
	SubString(t, s2, 1, 3);
	printf("->从S2的第%d个位置开始截取长度为%d的子串T为：", 1, 3);
	StrTraverse(t, Print);
	
	//测试串连接 
	printf("\n测试串连接：\n");
	printf("->串T:"); 
	StrTraverse(t, Print);
	printf("->串S1:"); 
	StrTraverse(s1, Print);
	Concat(s2, t, s1); 
	printf("->串T和串S2连接成的新串为：");
	StrTraverse(s2, Print);
	
	//测试串替换
	printf("\n测试串替换：\n");
	printf("->用串S1替换掉串S2中所有值为T的内容，结果为：");
	Replace(s2, t, s1); 
	StrTraverse(s2, Print);
	DestoryString(s2);
	
	//测试清空串 
	printf("\n测试串清空：\n");
	ClearString(s1);
	printf("->清空串后，串S1：");
	StrTraverse(s1, Print);
	printf("->字符串S1的长度为 %d ,是否为空(1是，0非) %d  \n", StrLength(s1), StrEmpty(s1));
	
	fflush(stdin);
	
	//测试模式匹配 
	printf("   ----------- 串的模式匹配算法 -------------  \n"); 
	
	//输入主串和模式串 
	printf("->请输入主串：");    gets(c);
	if(!(StrAssign(s1, c))){
		printf("串长超过MAXSTRLEN(=%d)!\n", MAXSTRLEN);
		exit(0);
	}//if
	
	char p[20 + 1];
	printf("->请输入模式串(长度不超过20): ");  gets(p);
	if(!(StrAssign(s2, p))){
		printf("串长超过20!\n");
		exit(0);
	}//if
	
	//测试BF算法 
	printf("\n->BF模式匹配算法测试：\n");
	k = Index_BF(s1, s2, 1);
	if(!k) {
		printf("->匹配失败，在主串中未发现模式串！\n");
	}//if 
    else {
    	printf("->匹配成功，在主串中发现模式串，模式串在主串中首次匹配的位置为%d！\n", k);
    }//else
    
	//测试KMP算法 ——next
	printf("\n->KMP模式匹配算法测试：\n");
	int next[20 + 1];
	getNext(s2, next);
	printf("->模式串的next序列: "); 
	for(i = 1; i <= StrLength(s2); i++) {
		printf(" %d", next[i]);
	}//for  
	printf("\n");
	i = Index_KMP_next(s1, s2, 1, next);
	if(i != 0) {
		printf("->KMP算法next数组：匹配成功，模式串在主串第%d个字符处首次匹配！\n", i);	
	}//if 
    else {
    	printf("->KMP算法next数组：匹配失败，在主串中未发现模式串！\n");
    }//else
    
    //测试KMP算法 ——nextval 
    int nextval[20 + 1];
    get_nextval(s2, nextval);
	printf("->模式串的nextval序列: "); 
	for(i = 1; i <= StrLength(s2); i++) {
		printf(" %d",nextval[i]);
	} 
	printf("\n");
	
	//执行KMP_nextval算法 
	i = Index_KMP_nextval(s1, s2, 1, nextval);
	if(i != 0) {
		printf("->KMP算法nextval数组：匹配成功，模式串在主串第%d个字符处首次匹配！\n", i);	
	}//if 
    else {
    	printf("->KMP算法nextval数组：匹配失败，在主串中未发现模式串！\n");
    }//else
    
    //测试串销毁 
    printf("\n->测试完毕,销毁主串和模式串！\n"); 
	DestoryString(s1);
    DestoryString(s2);
    
    //程序正常结束 
	return 0;
}//main 

/* ----------------------------------运行结果------------------------------------- 		
	
	------------------------------- 串的定长存储表示 -------------------------------
	测试串生成：
	->请输入字符串1：ABCD
	->字符串S1的长度为 4 ,是否为空(1是，0非) 0
	
	测试串拷贝：
	->串S1为：ABCD
	->拷贝S1生成的串S2为：ABCD
	
	测试串比较：
	->请输入字符串s2: 123456
	->串S1为：ABCD
	->串S2为：123456
	->两字符串比较结果：字符串1 > 字符串2
	
	测试串连接：
	->串S1为：ABCD
	->串S2为：123456
	->串s1联接串s2得到的串t为：ABCD123456
	
	测试取子串：
	->串t为：ABCD123456
	->求串t的子串，请输入子串的起始位置，子串长度: 3,7
	->子串为：CD12345
	
	测试串删除：
	->串t为：ABCD123456
	->从串t的第pos个字符起，删除len个字符，请输入pos,len：4,4
	->删除后的串t：ABC456
	
	测试串插入：
	->串S2为：CD12345
	->串t为：ABC456
	->在串s2的第3个字符之前插入串t后结果为:CDABC45612345
	
	测试串定位：
	->主串:CDABC45612345
	->模式串:ABC456
	->主串的第3个字母起和模式串第一次匹配
	
	测试取子串：
	->串S2:CDABC45612345
	->从S2的第1个位置开始截取长度为3的子串T为：CDA
	
	测试串连接：
	->串T:CDA
	->串S1:ABCD
	->串T和串S2连接成的新串为：CDAABCD
	
	测试串替换：
	->用串S1替换掉串S2中所有值为T的内容，结果为：ABABCDBCD
	
	测试串清空：
	->清空串后，串S1：
	->字符串S1的长度为 0 ,是否为空(1是，0非) 1
	   ----------- 串的模式匹配算法 -------------
	->请输入主串：ababccabcacbab
	->请输入模式串(长度不超过20): abcac
	
	->BF模式匹配算法测试：
	->匹配成功，在主串中发现模式串，模式串在主串中首次匹配的位置为7！
	
	->KMP模式匹配算法测试：
	->模式串的next序列:  0 1 1 1 2
	->KMP算法next数组：匹配成功，模式串在主串第7个字符处首次匹配！
	->模式串的nextval序列:  0 1 1 0 2
	->KMP算法nextval数组：匹配成功，模式串在主串第7个字符处首次匹配！
	
	->测试完毕,销毁主串和模式串！
	
	--------------------------------
	Process exited with return value 0
	Press any key to continue . . .

*/ 
