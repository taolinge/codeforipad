
//*******************************************引入头文件*********************************************

#include <stdio.h>   //使用了标准库函数  

//******************************************自定义符号常量******************************************* 

#define DestoryList ClearList  //DestoryList()和ClearList()的操作是一样的 
#define OVERFLOW -2            //内存溢出错误常量
#define ILLEGAL -1             //非法操作错误常量 
#define OK 1                   //表示操作正确的常量 
#define ERROR 0                //表示操作错误的常量 
#define TRUE 1                 //表示逻辑正确的常量 
#define FALSE 0                //表示逻辑错误的常量 

//******************************************自定义数据类型******************************************** 

typedef char ElemType;     //元素类型 
typedef int  Status;       //状态参量类型 

//----------------线性表的静态单链表存储结构--------------------
#define MAXSIZE 1000   //链表的最大长度
typedef struct{
	ElemType data;   //数据域 
	int cur;         //游标，作用相当于指针域 
}component, SLinkList[MAXSIZE]; 
 
//***************************************线性静态单链表的主要操作****************************************** 

/*
	函数：Malloc
	参数：SLinkList L 静态链表首地址 
	返回值：新开辟结点的坐标 
	作用：（申请结点空间）若备用空间链表非空，从备用链表取出一个空闲结点
	       并返回该结点下标，否则返回0
*/
int Malloc(SLinkList L){
	
	//L[0].cur记录了备用链表第一个空闲结点在数组中的位置 
	int i = L[0].cur;  
	
	//cur的值为0相当于指针域为NULL 
	//cur的值为0表示该节点后面没有后继，该节点是链表中的最后一个结点 
	//i的值不是0表示备用链表中还有空闲结点可以使用 
	if(i) { //if(i) <=> if(i != 0)
	
		//备用链表的头结点指向原备用链表的第二个结点
		//i（也就是L[0].cur）指示了第一个空闲结点的位置，
		//所以L[i].cur指示了第二个空闲结点的位置。
		//L[0]是备用链表的头结点，所以L[0].cur = L[i].cur;这句代码 
		//就是从备用链表把第一个空闲结点取走，然后把第二个空闲结点挂回到备用链表上 
	    L[0].cur = L[i].cur;
	}//if
	
	//返回新开辟结点的坐标
	return i;
	
}//Malloc

/*
	函数：InitList
	参数：SLinkList L 静态链表首地址  
	返回值：空表在数组中的位序
	作用：构造一个空链表
*/
int InitList(SLinkList L){
	
	//注意：此时一个数组中存储了两个链表：静态链表数据存储区域和备用链表
	//静态链表的头结点在数组中的位置就是i，但是i不是0，因为0号单元已经规定
	//就是备用链表的头结点。所以L[i].cur是静态链表首元结点。
	//而备用链表的头结点是L[0]，首元结点在数组中的位置是L[0].cur。
	//由于一个数组中同时存储了两个链表，所以要区分开静态链表数据存储区域和 
	//备用链表，尤其要区分两者的头结点和首元结点的位置上的不同。
	//而且要注意：由于静态链表数据存储链表的头结点是从备用链表上取出来的，位置不固定
	//所以在调用的时候要用变量保存头结点在数组中所在的位置，否则后续操作将无法进行 
	
	int i;
	
	//i存储了新开辟结点的坐标 
	i = Malloc(L);
	
	//由于静态链表目前刚刚初始化，除了头结点一个数据节点都没有，所以要
	//把静态链表头结点的指针域【也就是cur】设置为0，意思是后面没有后继结点
	L[i].cur = 0;
	
	//新开辟的第一个结点就是静态链表的头结点，头结点的位置为i
	return i; 
	
}//InitList 

/*
	函数：InitSpace
	参数：SLinkList L 静态链表首地址  
	返回值：无 
	作用：（初始化备用空间）将一维数组L中各分量链成一个备用链表，
	       L[0].cur为头指针，"0"代表空指针
	       这个函数是用来初始化备用链表的，不是用来初始化静态链表的数据存储区域 
*/
void InitSpace(SLinkList L) {
	
	//此时静态链表还未投入使用，所以整个数组都是备用链表的空间 
	for(int i = 0; i < MAXSIZE - 1; ++i) {
		
		//将第i+1个元素的下标（相对地址）存在第i个元素的cur中
	    L[i].cur = i + 1;     
	}//for
	
	//最后一个元素的cur存放0，表示空指针，即该位置为备用链表表尾
	L[MAXSIZE - 1].cur = 0;
	
}//InitSpace


/*
	函数：ClearList
	参数：SLinkList L 静态链表首地址
	      int n 存储数据链表表头结点在数组中的位序 
	返回值：无 
	作用：将线性表L置成空表，由于静态链表的大小在编译的时候就已经确定，
	      所以静态链表的内存不是动态分配的，也就不存在销毁这样的操作了。
		  由于清空操作造成的效果和销毁差不多，两者都可以清空已经存在的数据，
		  只不过清空不可以释放静态链表占用的内存空间，所以可以把清空操作
		  当成是静态链表的销毁操作。 
*/
void ClearList(SLinkList L, int n){
    
	int i = 0, j = 0, k = 0;
	
	//先回收静态链表数据存储链表的头结点，因为这个节点也是从备用链表
	//上面摘下来的，所以这个节点要先收回来。 
	
	//i指示存储数据链表首元结点的位置，由于是要回收头结点，所以要
	//保存首元结点在数组中的位置，否则头结点被回收之后将无法继续
	//回收后面的存储数据的结点。 
	i = L[n].cur;
	
	//L[n].cur指示了数据链表头结点后面的首元结点在数组中的位置
	//想要回收头结点就要把头结点和首元结点的连接切断，所以要
	//将L[n].cur置为0，使头结点从数据链表上脱离下来。 
	L[n].cur = 0;
	
	//k是备用链表第一个空闲结点在数组中的位置，k是起临时保存作用的
	//回收链表之后还要把k指示的结点及其后面的链条挂回到备用链表的后面
	//如果不保存k就会造成备用链表原有空闲结点丢失，在使用过程中可用空间无故变少。 
	k = L[0].cur;
	
	//回收了数据链表头结点之后就要开始回收数据链表的首元结点以及后面的全部结点了。 
	
	//把数据链表的所有未被回收的结点连接到备用链表表头，这些节点将会被回收 
	L[0].cur = i;
	
	//从数据链表的首元结点开始，向后回收每一个结点，直到数据链表表尾。
	//如果某个结点的cur值为0，表示该结点没有后继，即该结点是链表的最后一个结点
	//所以i != 0的意思是最后一个结点还没回收完。因为只有链表最后一个结点的cur为0。 
	while(i){   //while(i)  <=>  while(i != 0)
	
		//j记录了被回收的结点在数组中的位置，最后一趟循环完成后，
		//j指示的位置刚好是数据链表的尾元结点 
		j = i;
		
		//i指向下一个元素
		i = L[i].cur; 
	}//while
	
	//备用链表在结点回收前后面就有一条空闲结点组成的链条，由于我们在回收数据链表
	//结点的空间时已经重置了L[0].cur的值，所以旧的备用链表的空闲结点实际上已经和
	//备用链表的头结点L[0]断开了连接，所以原先在备用链表中的头结点位置已经不被
	//备用链表头结点记录了，如果我们不把它保存起来就会丢掉原有的空闲结点，导致
	//静态链表的空闲结点在使用过程中越变越少，一部分空闲结点不受备用链表头结点管制
	//且这些节点没法回收。所以备用链表的原来的首元结点在数组中的位置在回收前需要 
	//先保存在k变量中，只要找到数组中第k个位置，就可以顺着这个空闲结点找到后面所有的原先
	//已经在备用链表中的空闲结点。现在我们要做的就是把新回收的空闲结点和原有的空闲
	//结点合并到一个链中，统一被备用链表头结点的管理。具体做法就是直接把k指示的
	//原有的空闲结点链条中的首元结点接到新的备用链表尾部，使它们连接在一起就可以了。 
	L[j].cur = k;
	
}//ClearList 

/*
	函数：Free
	参数：SLinkList L 静态链表首地址
	      int k 被回收结点的在数组中的位置 
	返回值：无 
	作用：将下标为k的空闲结点回收到备用链表
*/
void Free(SLinkList L, int k){ 
	
	//L[0].cur存储了备用链表第一个可用结点在数组中的位置
	//L[k].cur = L[0].cur; 这行代码就是把原来的空闲结点组成的链条
	//挂到这个将要回收的结点后面
	L[k].cur = L[0].cur;
	
	//待回收结点k就被加入到了备用链表中，成为了空闲结点链条中的第一个结点。
	//（相当于在备用链表头部插入一个结点）。
	L[0].cur = k;
	
}//Free

/*
	函数：LocateElem
	参数：SLinkList L 静态链表首地址
	      int n 静态链表头结点在数组中的位置
		  ElemType e  查找值为e的元素 
	返回值：如果找到第一个值为e的元素，返回查找到的元素在L中的位序，否则返回0
	作用：在静态单链线性表L中查找第一个值为e的元素
*/
int LocateElem(SLinkList L, int n, ElemType e){
	
	//i指向表中第一个结点 
	int i = L[n].cur;
	
	//在表中顺链查找(若是字符串需要用strcmp()函数比较)
	//while(i && L[i].data != e) <=> while(i != 0 && L[i].data != e) 
	while(i && L[i].data != e) {
	
		//i指向下一个结点
	    i = L[i].cur;  
	}//while
	
	//如果找到了值为e的结点，循环会提前终止，此时i存储的就是值为e的结点在数组中的位置
	//如果没有找到，循环正常结束时i保存了尾元结点的cur，而尾元结点的cur值是0，
	//注：当某个节点cur的值为0时表示该结点是链表的最后一个结点，故后面没有后继。 
	return i;
	
}//LocateElem

/*
	函数：Print
	参数：ElemType e 被访问的元素 
	返回值：无
	作用：访问元素e的函数，通过修改该函数可以修改元素访问方式，
	      该函数使用时需要配合遍历函数一起使用。 
*/
void Print(ElemType e){
	
	//元素访问的方式是打印输出 
	printf(" %c ", e);
	
}//Print 

/*
	函数：ListTraverse
	参数：SLinkList L 静态链表L
	      int n 静态链表数据链表头结点在数组中的位置 
	      Status(* visit)(ElemType) 函数指针，指向元素访问函数。 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：调用元素访问函数完成静态链表的遍历，所谓遍历就是逐一访问线性表中的每个元素。 
*/
void ListTraverse(SLinkList L, int n, void(* Visit)(ElemType)){
	
	//i存储了静态链表数据链表的首元结点在数组中的位置 
	int i = L[n].cur;
	
	//i != 0表示没到静态链表表尾
	while(i){   //while(i) <=> while(i != 0)
	
		//调用Visit()函数访问元素
		Visit(L[i].data);
		
		//i指向下一个元素
		i = L[i].cur;         
	}//while
	
	//输出换行，使程序在控制台上的输出清楚美观 
	printf("\n");
	
}//ListTraverse

/*
	函数：ListEmpty
	参数：SLinkList L 静态链表L
	      int n 静态链表数据链表头结点在数组中的位置 
	返回值：若L是空表，返回TRUE，否则返回FALSE
	作用：判断静态链表L是否是空表 
*/
Status ListEmpty(SLinkList L, int n) { 

	//n指示了静态链表数据链表头结点在数组中的位置，
	//所以L[n].cur指示了静态链表数据链表首元结点在数组中的位置
	//如果L[n].cur的值为0表示静态链表数据链表头结点后面没有后继。
	//此时静态链表就是只有头结点没有数据节点的空表。 
	if(L[n].cur == 0) { //空表
	
		return TRUE;
	}//if 
	else {
		
		return FALSE;
	}//else
	
}//ListEmpty

/*
	函数：ListLength
	参数：SLinkList L 静态链表L
	      int n 静态链表数据链表头结点在数组中的位置 
	返回值：若L是空表，返回TRUE，否则返回FALSE
	作用：获取静态链表的长度 
*/
int ListLength(SLinkList L, int n){
	
	//i存储了静态链表数据链表的首元结点在数组中的位置 
	//j是记录静态链表长度的计数器 
	int j = 0, i = L[n].cur;
	
	//静态链表不像单链表和顺序表，0号结点的cur存的是备用链表首元结点
	//在数组中的位置，没有存储表长。所以只能遍历整个链表计算表长。
	//没到静态链表尾
	while(i){  //while(i)  <=> while(i != 0)
		
		//i存储了下一结点在数组中的位置 
		i = L[i].cur;
		
		//计数器+1 
		j++; 
	}//while
	
	//计数器在循环后的值就是数据节点的个数，也就是表长 
	return j;
	
}//ListLength 

/*
	函数：GetElem
	参数：SLinkList L 静态链表L
	      int n 静态链表数据链表头结点在数组中的位置
		  int i 得到第i个位置的元素的值 
		  ElemType &e 带回第i个位置的元素e 
	返回值：状态码，OK表示操作成功，ERROR表示操作失败 
	作用：用e返回L中第i个元素的值 
*/
Status GetElem(SLinkList L, int n, int i, ElemType &e) {
    
	//l是临时变量，k存储了第i个结点在数组中的位置（初始值任意）  
	int l, k = n;
	
	//检查参数i是否合法，i是否越界 
	if(i < 1 || i > ListLength(L, n)){
		printf("输入非法！\n");
		return ERROR;
	}//if 
	
	//顺着链表查找第i个结点，循环退出时k保存了第i个结点在数组中的位置 
	for(l = 1; l <= i; l++){
	
		//k记录了下一个结点在数组中的位置 
		k = L[k].cur; 
	}//for
	
	//e保存了第i个元素的值 
	e = L[k].data;
	
	//操作成功 
	return OK; 
}//GetElem

/*
	函数：SetElem
	参数：SLinkList L 静态链表L
	      int n 静态链表数据链表头结点在数组中的位置
		  int i 修改第i个位置的元素的值 
		  ElemType e 修改第i个位置的元素值为e 
	返回值：状态码，OK表示操作成功，ERROR表示操作失败 
	作用：修改L中第i个元素的值为e
*/
Status SetElem(SLinkList L, int n, int i, ElemType e) {
    
    //l是临时变量，k存储了第i个结点在数组中的位置（初始值任意） 
	int l, k = n;
	
	//检查参数i是否合法，i是否越界 
	if(i < 1 || i > ListLength(L, n)){
		printf("输入非法！\n");
		return ERROR;
	}//if
	
	//顺着链表查找第i个结点，循环退出时k保存了第i个结点在数组中的位置 
	for(l = 1; l <= i; l++) {
		
		//k记录了下一个结点在数组中的位置
		k = L[k].cur;
	}//for
	
	//将第i个元素的值设置为k 
	L[k].data = e;
	
	//操作成功 
	return OK;
	
}//SetElem

/*
	函数：PriorElem
	参数：SLinkList L 静态链表L
	      int n 静态链表数据链表头结点在数组中的位置
		  ElemType cur_e  线性表中的数据元素，且不是第一个元素 
		  ElemType &pre_e 带回cur_e的前驱结点的值 
	返回值：状态码，OK表示操作成功，ERROR表示操作失败 
	作用：若cur_e是线性表L中的数据元素，且不是第一个，则用pre_e返回它的前驱；
	      否则操作失败，pre_e无定义
*/
Status PriorElem(SLinkList L, int n, ElemType cur_e, ElemType &pre_e){
	
	//i指示了静态链表数据链表的头结点在数组中的位置
	//j的含义看do-while循环里面的说明 
	int j, i = L[n].cur;
	
	//从数据链表的首元结点开始向后逐个查找，由于静态链表没有设置成双向的， 
	//没有前驱指针域保存结点的前驱信息，所以不能直接用LocateElem函数来定位，
	//我们需要另写代码来取出某个结点的前驱在数组中的位置，并且需要单独设置
	//变量保存结点的前驱，直到遇到值为 cur_e 的结点（找到了）或到达链表末尾（没找到）为止。 
	do{
		//循环结束时：
		//1.如果找到了值为cur_e的元素，那么i存储了值为cur_e的结点在数组的位置
		//  那么j指示的是i所指示结点的前驱结点在数组中的位置。
		//2.如果没有找到，那么i的值为0，j的值为数据链表最后一个结点在数组中的位置。 
		j = i;
		
		//i指示了下一个结点在数组中的位置 
		i = L[i].cur;
	}while(i && cur_e != L[i].data);
	//while(i && cur_e != L[i].data) <=> while(i != 0 && cur_e != L[i].data) 
	
	//i不为0表示链表没有走到末尾，也就是循环中途结束，也就是找到了值为cur_e的结点 
	if(i){  //if(i) <=> if(i != 0)
		
		//取出前驱结点的值并保存到pre_e 
		pre_e = L[j].data;
		
		//操作成功 
		return OK;
	}//if
	
	//操作失败 
	return ERROR;
	
}//PriorElem

/*
	函数：NextElem
	参数：SLinkList L 静态链表L
	      int n 静态链表数据链表头结点在数组中的位置
		  ElemType cur_e  线性表中的数据元素，且不是最后一个 
		  ElemType &next_e 带回cur_e的后继结点的值 
	返回值：状态码，OK表示操作成功，ERROR表示操作失败 
	作用：若cur_e是线性表L中的数据元素，且不是最后一个，则用next_e返回它的后继；
	      否则操作失败。 
*/
Status NextElem(SLinkList L, int n, ElemType cur_e, ElemType &next_e){
	
	//在L中查找第一个值为cur_e的元素的位置
	int i = LocateElem(L, n, cur_e);
	
	//i的值不为0表示静态链表数据链表L中存在值为cur_e的结点，
	//此时i指示了该结点在数组中的位置。 
	if(i){  //if(i) <=> if(i != 0)
		
		//使i保存cur_e的后继结点在数组中的位置 
		i = L[i].cur;
		
		//i的值不为0说明cur_e有后继
		if(i){ //if(i) <=> if(i != 0)
		
			//取出后继元素的值并保存到next_e 
			next_e = L[i].data;
			
			//操作成功，cur_e元素有后继并成功获得后继的值 
			return OK; 
		}//if 
	}//if
	
	//操作失败，L中不存在cur_e元素，cur_e元素无后继 
	return ERROR;
	
}//NextElem

/*
	函数：ListInsert
	参数：SLinkList L 静态链表L
	      int n 静态链表数据链表头结点在数组中的位置
		  int i 在第i个位置之前插入 
		  ElemType e 插入的值为e 
	返回值：状态码，OK表示操作成功，ERROR表示操作失败 
	作用：在静态链表L中第i个元素之前插入新的数据元素e
*/
Status ListInsert(SLinkList L, int n, int i, ElemType e) {
	 
	//l是循环用的临时变量 
	//j指示了新申请结点在数组中的位置
	//k将会用于存储第i-1个结点在数组中的位置(初始值：数据链表头结点在数组中的位置) 
	int l, j, k = n;
	
	//检查i的值是否合法，i是否越界 
	if(i < 1 || i > ListLength(L, n) + 1) { 
	    return ERROR;
	}//if
	
	//从备用链表摘下一个空闲结点，申请一个结点的空间 
	j = Malloc(L);
	
	//检查申请结点是否成功，若申请成功则执行插入操作 
	//申请成功 
	if(j){  //if(j) <=> if(j != 0)
		
		//将e保存到新申请的结点中 
		L[j].data = e;
		
		//找到第i-1个结点 
		for(l = 1; l < i; l++) {
		    
		    //k的初始值为数据链表头结点在数组中的位置
		    //循环结束后k的值是第i-1个结点在数组中的位置  
			k = L[k].cur;
		}//for
		
		//将新的结点插入到原来的链条中第i-1个结点后面，作为新的第i个结点 
		
		//将第i个及其后面的结点链接到新申请的结点后面 
		L[j].cur = L[k].cur;
		
		//将新申请的结点及其后续结点链接到第i-1个结点的后面 
		L[k].cur = j;
		
		//操作成功 
		return OK; 
	}//if
	
	//操作失败 
	return ERROR;
	
}//ListInsert 

/*
	函数：ListDelete
	参数：SLinkList L 静态链表L
	      int n 静态链表数据链表头结点在数组中的位置
		  int i 在第i个位置删除 
		  ElemType &e 带回被删除的值e 
	返回值：状态码，OK表示操作成功，ERROR表示操作失败 
	作用：删除表中第i个位置的数据元素e，并返回其值
*/
Status ListDelete(SLinkList L, int n, int i, ElemType &e) {
	 
	//j将会用于存储第i个结点在数组中的位置 
	//k将会用于存储第i-1个结点在数组中的位置(初始值：数据链表头结点在数组中的位置) 
	int j, k = n;
	
	//检查i的值是否合法，i是否越界 
	if(i < 1 || i > ListLength(L, n)) { 
	   return ERROR;
	}//if
	
	//找到第i-1个结点 
	for(j = 1; j < i; j++) {
	   
	   //k的初始值为数据链表头结点在数组中的位置
	   //循环结束后k的值是第i-1个结点在数组中的位置  
	   k = L[k].cur;
	}//for
	
	//先保存待删除的第i个结点在数组中的位置，j指示了这一位置 
	j = L[k].cur;
	
	//将第i+1个结点在数组中的位置填在第i-1个结点的cur中，
	//将第i个结点从静态链表的数据链表中隔离出来 
	L[k].cur = L[j].cur;
	
	//取出被删除结点中存储的值并保存到e 
	e = L[j].data;
	
	//释放掉被删结点的空间，使之重新回到备用链表中，可以作为空闲结点再次被使用 
	Free(L,j);
	
	//操作成功 
	return OK;		 
}//ListDelete

/*
	函数：difference
	参数：SLinkList space 
	      int &S  
	返回值：无 
	作用：（求集合(A-B)∪(B-A)）依次输入集合A和B的元素，在一维数组L中建立表示
	      集合(A-B)∪(B-A) 的链表，S为其头指针。
	      假设备用空间足够大，L[0].cur为其头指针
*/
void difference(SLinkList space, int &S) {

	//m用于保存从键盘接收的集合A元素的个数
	//n用于保存从键盘接收的集合B元素的个数
	//i和j都是临时变量 
	//r保存了集合A的尾元结点在数组中的位置，在静态链表中是集合A和B元素的分界线 
	//p和k的作用看后续说明 
	int m, n, i, r, p, k;
	
	//临时变量，用于保存从键盘输入的集合B的元素值 
	ElemType b; 
	
	//初始化备用链表
	InitSpace(space);
	
	//生成静态链表S数据链表的头结点
	S = Malloc(space);
	
	//r暂时指向S的当前最后结点
	r = S;
	
	//从键盘接收A和B的元素个数
	printf("->请输入集合A和B的元素个数（逗号隔开）："); 
	scanf("%d,%d%*c", &m, &n);
	
	//从键盘接收集合A的每个元素，并使用它们建立的静态链表  
	printf("->请输入集合A中的元素(共%d个)空格隔开\n", m);
	for(int j = 1; j <=m; ++j){
		
		//从备用链表摘下一个空闲结点，申请一个结点的空间 
		i = Malloc(space);
		
		//从键盘输入A的元素值并保存到新申请结点的数据域中 
		scanf("%c", &space[i].data);  getchar();
		
		//将这个新结点链接到链表最后一个结点后面，成为新的尾元结点 
		space[r].cur = i;
		
		//使r指向新的尾元结点，但是r仅仅暂时指向尾元结点，待集合B元素输入后
		//r将有可能不再指向静态链表尾元结点，而是作为静态链表S中集合A和B元素的分界线 
		r = i;
	}//for
	
	//设置静态链表A尾元结点的指针为空
	space[r].cur = 0;
	
	//从键盘接收集合B的每个元素，若不在当前表中，则插入，否则删除
	//可以考虑用基本操作替换掉插入和删除部分的代码 
	printf("->请输入集合B中的元素(共%d个)空格隔开\n",n);
	for(int j = 1; j <= n; ++j){
		
		//从键盘接收集合B的元素值 
		scanf("%c", &b);   getchar();
		
		//p保存了静态链表S的头结点在数组中的位置 
		p = S;
		
		//k指向集合A的首元结点 
		k = space[S].cur;
		
		//在当前表中查找
		//由于r指向静态链表S数据链表的尾元结点，所以space[r].cur的值为0
		//while(k != space[r].cur && space[k].data != b)
		// <=> while(k != 0 && space[k].data != b)    
		while(k != space[r].cur && space[k].data != b){  
			
			//若在静态链表S中找到找到值为b的结点，说明集合A中已经存在值b
			//循环退出时，k指示了值为b的结点在数组中的位置，
			//p指示了k指向的结点的前驱结点在数组中的位置
			//若没有找到值为b的元素，链表会一直扫描到末尾，k的值为0
			//p指示了静态链表S数据链表的尾元结点 
			p = k;
			
			//指针后移，类似于单链表中的p=p->next;
			k = space[k].cur;
		} //while
		
		//当前表中不存在该元素，插入在r所指结点之后，且r的位置不变
		//if(k == space[r].cur) <=> if(k == 0) 
		if(k == space[r].cur){
			
			//从备用链表摘下一个空闲结点，申请一个新的结点的空间 
			i = Malloc(space);
			
			//将从键盘接收的集合B的元素值存入新结点的数据域 
			space[i].data = b;
			
			//将新结点的指针域置为空
			//因为r指示尾元结点，所以space[r].cur值为0，
			//所以space[i].cur = space[r].cur;相当于space[i].cur = 0; 
			space[i].cur = space[r].cur;
			
			//将新结点插入到r后面，但是r的值不能变，因为r前面的是集合A的元素 
			//r的后面是集合B的元素，所以r是静态链表中集合A和集合B元素的分界线 
			space[r].cur = i; 
			
			//由代码可以看出，集合B元素的插入并不是发生在静态链表数据链表的末尾，
			//而是发生在r位置之后，所以它的效果就相当于集合A的元素采用尾插法，
			//集合B的元素采用头插法，所以输出时可以看到，集合A的元素是正序输出
			//集合B的元素是逆序输出，注意观察调试时输出的结果。 
			
		} //if
		else{ //当前元素已在表中，删除之
			
			//k指示了值为b的结点在数组中的位置，所以space[k].cur指示该节点的后继
			//p指示了k指向的结点的前驱结点在数组中的位置
			//这句代码的作用是：将k的后继接到k的前驱后面，将k从数据链表中隔离出来 
			space[p].cur = space[k].cur;
			
			//释放掉k所指的结点空间，使之回归备用链表，供后续操作使用 
			Free(space, k);
			
			//r起着集合A和B元素分界线的作用，r指向集合A最后一个元素。
			//删除操作总是删除集合A中的元素，所以删除位置k的值有可能取到r。 
			//如果删除了k位置的结点，k位置的结点将会回归到备用链表中，
			//但是r却没有改变，那么此时r将会指向一个被回收的结点。
			//假如此次删除操作后紧接着发生一次插入操作，那么插入操作将会
			//发生在备用链表中，这显然是错误的，没有达到我们想要的结果。
			//若想解决这个问题，就必须在删除操作完成后及时将r的值改变，
			//使其指向被删除结点的前驱结点。 
			//所以若删除的是r所指结点，则需要修改尾指针，使r仍然指向集合A的最后一个元素。 
			if(r == k) { //k指示了被删除结点在数组中的位置
				
				//此时，p指向k指向结点的前驱，应该让r指向这个结点 
			    r = p;
			}//if 
		}//else
	}//for
}//difference

//**********************************************主函数******************************************** 
int main(int argc,char *argv[]){ 
    printf("\n---------------------------------静态链表引用版---------------------------------\n");
	
	//备用链表头结点地址 
	SLinkList L;
	
	//La是静态链表A的头结点的在数组中的位置
	//Lb是静态链表B的头结点的在数组中的位置 
	int La, Lb;
	
	//m是从键盘接收的静态链表A的元素个数
	//n是从键盘接收的静态链表B的元素个数 
	int m, n; 
	
	//-------------------------------初始化备用链表----------------------------- 
	printf("->初始化备用链表\n");
	InitSpace(L);
	printf("->备用链表初始化完成。\n\n");
	
	//-------------------------------初始化静态链表A---------------------------- 
	La = InitList(L);
	printf("->初始化静态链表A的头结点完成！\n");
	
	printf("->静态链表A是否为空：");
	if(ListEmpty(L, La) == TRUE) {
		printf("是\n"); 
	}//if 
	else {
		printf("否\n"); 
	}//else
	
	printf("->静态链表A的表长：%d\n", ListLength(L, La)); 
	
	printf("->请输入静态链表A的元素个数（整数），输入后按回车确认："); 
	scanf("%d", &m); getchar(); 
	
	//从键盘接收集合A的每个元素，并使用它们建立的静态链表  
	printf("->请输入静态链表A中的元素(共%d个)空格隔开\n", m);
	for(int i = 1; i <= m; i++) {
		
		//先申请一个新的空闲结点，得到其在数组中的位置 
		int j = Malloc(L);
		
		//从键盘接收新的数据
		ElemType e;
		scanf("%c", &e); getchar();
		
		//将新结点插入到链表中
		ListInsert(L, La, i, e);  
	}//for
	
	printf("->静态链表A初始化之后所有结点元素值如下：\n");
	ListTraverse(L, La, Print);  
	
	printf("->静态链表A是否为空：");
	if(ListEmpty(L, La) == TRUE) {
		printf("是\n"); 
	}//if 
	else {
		printf("否\n"); 
	}//else
	
	printf("->静态链表A的表长：%d\n", ListLength(L, La)); 
	
	//------------------------------初始化静态链表B-------------------------- 
	Lb = InitList(L);
	printf("\n->初始化静态链表B的头结点完成！\n");
	
	printf("->静态链表B是否为空：");
	if(ListEmpty(L, Lb) == TRUE) {
		printf("是\n"); 
	}//if 
	else {
		printf("否\n"); 
	}//else
	
	printf("->静态链表B的表长：%d\n", ListLength(L, Lb)); 
	
	printf("->请输入静态链表B的元素个数（整数），输入后按回车确认："); 
	scanf("%d", &n); getchar();
	
	//从键盘接收集合B的每个元素，并使用它们建立的静态链表  
	printf("->请输入静态链表B中的元素(共%d个)空格隔开\n", n);
	for(int i = 1; i <= n; i++) {
		
		//先申请一个新的空闲结点，得到其在数组中的位置 
		int j = Malloc(L);
		
		//从键盘接收新的数据
		ElemType e;
		scanf("%c", &e); getchar();
		
		//将新结点插入到链表中
		ListInsert(L, Lb, i, e);
	}//for
	
	printf("->静态链表B初始化之后所有结点元素值如下：\n");
	ListTraverse(L, Lb, Print);  
	
	printf("->静态链表B是否为空：");
	if(ListEmpty(L, Lb) == TRUE) {
		printf("是\n"); 
	}//if 
	else {
		printf("否\n"); 
	}//else
	
	printf("->静态链表B的表长：%d\n", ListLength(L, Lb)); 
	
	//--------------------------测试从链表中取值------------------- 
	printf("\n->您想取静态链表A第几个位置的值(1-%d):", m);
	int position = 1;
	scanf("%d", &position); getchar();
	printf("->静态链表A第%d个的值为：", position);
	int result = 0;
	ElemType elem;
	result = GetElem(L, La, position, elem);
	if(result == ERROR) {
		printf("没找到！\n");
	}//if 
	else {
		printf("%c\n", elem); 
	}//else
	
	printf("\n->您想取静态链表B第几个位置的值（1-%d）:", n);
	scanf("%d", &position); getchar();
	printf("->静态链表B第%d个的值为：", position);
	result = 0;
	result = GetElem(L, Lb, position, elem);
	if(result == ERROR) {
		printf("没找到！\n");
	}//if 
	else {
		printf("%c\n", elem); 
	}//else
	
	//---------------------------测试按值查找-----------------------------------
	printf("->您想在静态链表A中查找的值为：");
	scanf("%c", &elem); getchar();
	result = LocateElem(L, La, elem);
	if(result == 0) {
		printf("->没有在静态链表A中找到您输入的值：%c\n", elem);
	}//if
	else {
		printf("->找到了，值为%c的结点在数组中的位序是：%d\n", elem, result);
	}//else 
	
	printf("\n->您想在静态链表B中查找的值为：");
	scanf("%c", &elem); getchar();
	result = LocateElem(L, Lb, elem);
	if(result == 0) {
		printf("->没有在静态链表B中找到您输入的值：%c\n", elem);
	}//if
	else {
		printf("->找到了，值为%c的结点在数组中的位序是：%d\n", elem, result);
	}//else 
	
	//---------------------------测试设置值-----------------------------------
	printf("\n->修改前静态链表A所有结点元素值如下：\n");
	ListTraverse(L, La, Print);  

	printf("->您想修改静态链表A中哪个位置的值，请输入位序（1-%d）：", m);
	scanf("%d", &position); getchar();
	printf("\n->您想要将这个位置的值修改为多少？");
	scanf("%c", &elem); getchar();
	result = SetElem(L, La, position, elem);
	if(result == ERROR) {
		printf("->修改失败！\n");
	}//if
	else {
		printf("->修改成功！\n");
	}//else 
	
	printf("\n->修改后静态链表A所有结点元素值如下：\n");
	ListTraverse(L, La, Print);
	
	printf("\n->修改前静态链表B所有结点元素值如下：\n");
	ListTraverse(L, Lb, Print);
	
	printf("->您想修改静态链表B中哪个位置的值，请输入位序（1-%d）：", n);
	scanf("%d", &position); getchar();
	printf("\n->您想要将这个位置的值修改为多少？");
	scanf("%c", &elem); getchar();
	result = SetElem(L, Lb, position, elem);
	if(result == ERROR) {
		printf("->修改失败！\n");
	}//if
	else {
		printf("->修改成功！\n");
	}//else 

	printf("->静态链表B所有结点元素值如下：\n");
	ListTraverse(L, Lb, Print);
	printf("\n"); 
	
	//--------------------测试找前驱和找后继的操作-------------------------- 
	printf("\n->静态链表A所有结点元素值如下：\n");
	ListTraverse(L, La, Print);  

	printf("->您想找静态链表A中哪个结点的前驱结点和后继结点，请输入元素的值：");
	scanf("%c", &elem); getchar();
	
	ElemType pre_e = -1;
	result = PriorElem(L, La, elem, pre_e);
	if(result == ERROR && pre_e == -1) {
		printf("->没有找到该结点前驱！\n"); 
	}//if 
	else {
		printf("->该结点前驱的元素值为：%c\n", pre_e); 
	}//else
	
	ElemType next_e = -1;
	result = NextElem(L, La, elem, next_e);
	if(result == ERROR && next_e == -1) {
		printf("->没有找到该结点后继！\n"); 
	}//if 
	else {
		printf("->该结点后继的元素值为：%c\n", next_e); 
	}//else
	
	printf("->静态链表B所有结点元素值如下：\n");
	ListTraverse(L, Lb, Print);
	
	printf("->您想找静态链表B中哪个结点的前驱结点和后继结点，请输入元素的值：");
	scanf("%c", &elem); getchar();
	
	pre_e = -1;
	result = PriorElem(L, Lb, elem, pre_e);
	if(result == ERROR && pre_e == -1) {
		printf("->没有找到该结点前驱！\n"); 
	}//if 
	else {
		printf("->该结点前驱的元素值为：%c\n", pre_e); 
	}//else
	
	next_e = -1;
	result = NextElem(L, Lb, elem, next_e);
	if(result == ERROR && next_e == -1) {
		printf("->没有找到该结点后继！\n"); 
	}//if 
	else {
		printf("->该结点后继的元素值为：%c\n", next_e); 
	}//else
	
	//---------------------------测试插入操作------------------------
	printf("\n->插入操作前静态链表A所有结点元素值如下：\n");
	ListTraverse(L, La, Print);  
	
	printf("->您想要在静态链表A的哪个位置插入，请输入位序(1-%d)：", m); 
	scanf("%d", &position); getchar();
	printf("\n->您想要在这个位置插入的值为多少：");
	scanf("%c", &elem); getchar();
	
	result = ListInsert(L, La, position, elem);
	
	if(result == ERROR) {
		printf("->插入操作失败！\n"); 
	}//if
	else {
		printf("->插入操作成功！\n");
	}//else
	
	printf("->插入操作后静态链表A所有结点元素值如下：\n");
	ListTraverse(L, La, Print);
	
	printf("\n->插入操作前静态链表B所有结点元素值如下：\n");
	ListTraverse(L, Lb, Print);  
	
	printf("->您想要在静态链表B的哪个位置插入，请输入位序(1-%d)：", n); 
	scanf("%d", &position); getchar();
	printf("\n->您想要在这个位置插入的值为多少：");
	scanf("%c", &elem); getchar();
	
	result = ListInsert(L, Lb, position, elem);
	
	if(result == ERROR) {
		printf("->插入操作失败！\n"); 
	}//if
	else {
		printf("->插入操作成功！\n");
	}//else
	
	printf("->插入操作后静态链表B所有结点元素值如下：\n");
	ListTraverse(L, Lb, Print);  
	
	//---------------------------测试删除操作----------------------------
	
	printf("\n->删除操作前静态链表A所有结点元素值如下：\n");
	ListTraverse(L, La, Print);  
	
	printf("->您想要在静态链表A的哪个位置删除，请输入位序(1-%d)：", m); 
	scanf("%d", &position); getchar();
	
	result = ListDelete(L, La, position, elem);
	
	if(result == ERROR) {
		printf("->删除操作失败！\n"); 
	}//if
	else {
		printf("->删除操作成功！被删除的元素值为：%c\n", elem);
	}//else
	
	printf("->删除操作后静态链表A所有结点元素值如下：\n");
	ListTraverse(L, La, Print);
	
	printf("\n->删除操作前静态链表B所有结点元素值如下：\n");
	ListTraverse(L, Lb, Print);  
	
	printf("->您想要在静态链表B的哪个位置删除，请输入位序(1-%d)：", n); 
	scanf("%d", &position); getchar();
	
	result = ListDelete(L, Lb, position, elem);
	
	if(result == ERROR) {
		printf("->删除操作失败！\n"); 
	}//if
	else {
		printf("->删除操作成功！被删除的元素值为：%c\n", elem);
	}//else
	
	printf("->删除操作后静态链表B所有结点元素值如下：\n");
	ListTraverse(L, Lb, Print);  

	//--------------------测试集合 (A-B)∪(B-A)的求解--------------------
	printf("\n->测试求集合 (A-B)∪(B-A)：\n"); 
	SLinkList space;
	int S;
    difference(space, S); 
    printf("\n->不属于集合A ∩B的元素如下：（注意集合B元素的输出顺序：逆向输出）\n");
	ListTraverse(space, S, Print);  
	return 0;	
}

/* ---------------------------------运行结果-----------------------------------------
 

---------------------------------静态链表引用版---------------------------------
->初始化备用链表
->备用链表初始化完成。

->初始化静态链表A的头结点完成！
->静态链表A是否为空：是
->静态链表A的表长：0
->请输入静态链表A的元素个数（整数），输入后按回车确认：5
->请输入静态链表A中的元素(共5个)空格隔开
1 2 3 4 5
->静态链表A初始化之后所有结点元素值如下：
 1  2  3  4  5
->静态链表A是否为空：否
->静态链表A的表长：5

->初始化静态链表B的头结点完成！
->静态链表B是否为空：是
->静态链表B的表长：0
->请输入静态链表B的元素个数（整数），输入后按回车确认：5
->请输入静态链表B中的元素(共5个)空格隔开
6 7 8 9 0
->静态链表B初始化之后所有结点元素值如下：
 6  7  8  9  0
->静态链表B是否为空：否
->静态链表B的表长：5

->您想取静态链表A第几个位置的值(1-5):2
->静态链表A第2个的值为：2

->您想取静态链表B第几个位置的值（1-5）:3
->静态链表B第3个的值为：8
->您想在静态链表A中查找的值为：3
->找到了，值为3的结点在数组中的位序是：7

->您想在静态链表B中查找的值为：4
->没有在静态链表B中找到您输入的值：4

->修改前静态链表A所有结点元素值如下：
 1  2  3  4  5
->您想修改静态链表A中哪个位置的值，请输入位序（1-5）：2

->您想要将这个位置的值修改为多少？9
->修改成功！

->修改后静态链表A所有结点元素值如下：
 1  9  3  4  5

->修改前静态链表B所有结点元素值如下：
 6  7  8  9  0
->您想修改静态链表B中哪个位置的值，请输入位序（1-5）：3

->您想要将这个位置的值修改为多少？1
->修改成功！
->静态链表B所有结点元素值如下：
 6  7  1  9  0


->静态链表A所有结点元素值如下：
 1  9  3  4  5
->您想找静态链表A中哪个结点的前驱结点和后继结点，请输入元素的值：2
->没有找到该结点前驱！
->没有找到该结点后继！
->静态链表B所有结点元素值如下：
 6  7  1  9  0
->您想找静态链表B中哪个结点的前驱结点和后继结点，请输入元素的值：0
->该结点前驱的元素值为：9
->没有找到该结点后继！

->插入操作前静态链表A所有结点元素值如下：
 1  9  3  4  5
->您想要在静态链表A的哪个位置插入，请输入位序(1-5)：1

->您想要在这个位置插入的值为多少：4
->插入操作成功！
->插入操作后静态链表A所有结点元素值如下：
 4  1  9  3  4  5

->插入操作前静态链表B所有结点元素值如下：
 6  7  1  9  0
->您想要在静态链表B的哪个位置插入，请输入位序(1-5)：2

->您想要在这个位置插入的值为多少：8
->插入操作成功！
->插入操作后静态链表B所有结点元素值如下：
 6  8  7  1  9  0

->删除操作前静态链表A所有结点元素值如下：
 4  1  9  3  4  5
->您想要在静态链表A的哪个位置删除，请输入位序(1-5)：1
->删除操作成功！被删除的元素值为：4
->删除操作后静态链表A所有结点元素值如下：
 1  9  3  4  5

->删除操作前静态链表B所有结点元素值如下：
 6  8  7  1  9  0
->您想要在静态链表B的哪个位置删除，请输入位序(1-5)：2
->删除操作成功！被删除的元素值为：8
->删除操作后静态链表B所有结点元素值如下：
 6  7  1  9  0

->测试求集合 (A-B)∪(B-A)：
->请输入集合A和B的元素个数（逗号隔开）：5,5
->请输入集合A中的元素(共5个)空格隔开
1 2 3 4 5
->请输入集合B中的元素(共5个)空格隔开
3 4 5 6 7

->不属于集合A ∩B的元素如下：（注意集合B元素的输出顺序：逆向输出）
 1  2  7  6

--------------------------------
Process exited with return value 0
Press any key to continue . . .
*/ 
