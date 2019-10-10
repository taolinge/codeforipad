
//注意：此单链表不同于书上的单链表，书上的单链表是有头结点的，
//      但是此单链表无头结点，插入、删除和很多操作会有所区别。 

/*
	函数：InitList
	参数：LinkList &L 单链表引用 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：构造一个空的不带头结点的单链表L
*/
Status InitList(LinkList &L) {
	
	//没有头结点的空单链表头指针为空
	L = NULL;
	
	//操作成功
	return OK; 
}//InitList 

/*
	函数：DestoryList
	参数：LinkList &L 单链表引用 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：若线性表L已存在则将L重置为空表。
*/
Status DestoryList(LinkList &L) {
	
	//工作指针p 
	LinkList p;
	
	//单链表L不空
	while(L) {
		
		//没有头结点的单链表头指针L指向首元结点 
		//p指向首元结点
    	p = L;
    	
    	//L指向p的后继 
    	L = L->next;
    	
    	//释放首元结点
		free(p);
	}//while
	
	//操作成功 
	return OK; 
}//DestoryList

/*
	函数：ListEmpty
	参数：LinkList L 单链表L
	返回值：状态码，若L为空表返回TRUE，否则返回FALSE
	作用：判断单链表L是否为空 
*/
Status ListEmpty(LinkList L) {
	
	//头指针直接指向首元结点，若头指针为NULL，则链表为空。 
	if(L) { //if(L) <=> if(L != NULL)
    	return FALSE;
    }//if 
	else {
    	return TRUE;
	}//else 
}//ListEmpty

/*
	函数：ListLength
	参数：LinkList L 单链表引用 
	返回值：返回L中数据元素个数
	作用：得到表长 
*/
int ListLength(LinkList L) {

	//i是一个计数器，记录了表长 
	int i = 0;
	
	//工作指针p指向单链表的首元结点 
	LinkList p = L;
	
	//遍历整个单链表求出表长 
	while(p) { //while(p) <=> while(p != NULL)
		
		//p指向下一个结点
    	p = p->next;
    	
    	//找到一个结点计数器+1 
     	i++;
	}//while
	
	//返回表长 
	return i;
}//ListLength

/*
	函数：GetElem
	参数：LinkList L 不带头结点的单链表的头指针
	      int i 查找第i个元素
		  ElemType &e 使用e带回第i个元素的值 
	返回值：状态码，找到第i个元素返回OK，否则返回ERROR 
	作用：当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR
*/
Status GetElem(LinkList L, int i, ElemType &e) {
   
   	//临时变量，记录已经遍历过的元素个数 
	int j = 1;
	
	//工作指针p指向单链表首元结点 
	LinkList p = L;
	
	//检查参数i的值是否合法：i是否越界 
	if(i < 1) { 
    	return ERROR;
    }//if
	
	//在单链表中从头开始向后查找第i个元素 
	//没到第i个元素，也没到表尾
	//while(j < i && p) <=> while(j < i && p != NULL)
	while(j < i && p) {
    	
    	//计数器j+1 
		j++;
		
		//p指向下一个结点 
    	p = p->next;
	}//while
	
	//找到了第i个元素所在结点，此时p指向该结点 
	if(j == i) {
    	
    	//复制第i个元素的值到e 
		e = p->data;
		
		//操作成功 
    	return OK;
   	}//if
   	else { 
    	return ERROR;
    }//else 	
}//GetElem

/*
	函数：LocateElem
	参数：LinkList L 不带头结点的单链表的头指针
	      ElemType e 查找元素e 
		  Status(*compare)(ElemType, ElemType) 函数指针，指向元素比较函数compare() 
	返回值：返回单链表L中第1个与e满足关系compare()的数据元素的位序。
	        若这样的数据元素不存在，则返回值为0。 
	作用：当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR
*/
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType)) {
	
	//临时变量，计数器   
	int i = 0;
	
	//工作指针p指向首元结点 
	LinkList p = L;
	
	//在链表L中遍历每一个结点，查找值为e的元素 
	while(p) { //while(p) <=> while(p != NULL)
		
		//计数器+1 
    	i++;
    	
    	//找到这样的数据元素
    	//if(compare(p->data, e)) <=> if(compare(p->data, e) != 0)  
    	if(compare(p->data, e)) { 
    		return i;
    	}//if
		
		//p指向下一个结点 
    	p = p->next;
	}//while
	
	//若没有找到值为e的结点，返回0 
	return 0;
}//LocateElem

/*
	函数：ListInsert
	参数：LinkList &L 单链表引用 
	      int i 在第i个位置之前插入 
		  ElemType e 被插入的元素e 
	返回值：状态码，操作成功返回OK，否则返回ERROR。 
	作用：不带头结点的单链线性表L中第i个位置之前插入元素e
*/
Status ListInsert(LinkList &L, int i, ElemType e) {
   
   	//计数器，记录查找过的结点数 
   	int j = 1;
   
   	//p是工作指针，初始位置指向单链表首元结点 
   	//s指向被插入结点 
   	LinkList p = L, s;
   
	//检查参数i的值是否合法 
	if(i < 1) { //i越界 
		return ERROR;
	}//if
	
	//创建被插入结点并使s指向新结点
	s = (LinkList)malloc(sizeof(LNode));
	
	//将被插入的值e填充到新结点s的数据域中 
	s->data = e;
	
	//注意：此链表不带头结点，做插入操作需判断插入位置是否在表头
	//      如果是在表头插入需要修改头指针，不在表头插入则不需要。 
   	if(i == 1) { //插在表头
   		
   		//直接把链表原有结点挂到新结点后面 
		s->next = L;
     	
     	//使头指针L指向s指向的新结点，s成为新的首元结点 
		L = s;
   	}//if
	else { //插入位置不在表头 
    	
    	//寻找第i-1个结点
		while(p && j < i - 1) {
			
			//p指向下一个结点 
			p = p->next;
			
			//计数器j+1 
			j++;
		}//while
		
		//没找到第i-1个结点 
		if(!p) { //if(!p) <=> if(p != NULL) 
			//操作失败 
			return ERROR;
		}//if
		
		//将第i-1个结点后面的结点挂到s指向的结点后面 
		s->next = p->next;
		
		//把s指向的结点连同后面的结点挂到原来的第i-1个结点后面
		//s成为新的第i个结点。 
    	p->next = s;
	}//else 
	
	//操作成功 
	return OK;
}//ListInsert

/*
	函数：ListDelete
	参数：LinkList &L 单链表引用 
	      int i 在第i个位置之前删除
		  ElemType &e 带回被删除的元素e 
	返回值：状态码，操作成功返回OK，否则返回ERROR。 
	作用：在不带头结点的单链线性表L中，删除第i个元素，并由e返回其值
*/
Status ListDelete(LinkList &L, int i, ElemType &e) { 
	
	//计数器，记录查找过的结点数 
	int j = 1;
	
	//p是工作指针，初始值指向单链表的首元结点
	//工作指针q指向被删除结点 
	LinkList p = L, q = NULL;
	
	//注意：我们使用的是不带头结点的单链表，头指针直接指向首元结点
	//      执行删除操作时需要判断删除位置是否发生在表头。
	//      如果删除操作在表头执行，就需要修改头指针，否则不需要。 
	if(i == 1) { //被删除的是首元结点
		
		//删除首元结点后，删除前的第二个元素结点将成为新的首元结点。
		//所以需要修改单链表头指针L的指向，使其指向第二个结点，为删除做好准备。 
    	L = p->next;
    	
    	//保存被删除结点p的值到e 
    	e = p->data;
    	
    	//释放首元结点的内存空间 
    	free(p);
   	}//if
	else {
		
		//寻找第i-1个结点，并令p指向它 
		//while(p->next && j < i - 1) <=> while(p->next != NULL && j < i - 1) 
    	while(p->next && j < i - 1) {
    		
    		//p指向下一个结点 
			p = p->next;
			
			//计数器+1 
			j++;
		}//while
		
		//检查是否找到第i-1个结点，若没有找到则终止函数的执行 
    	if(!p->next || j > i - 1) { 
			
			//操作失败 
			return ERROR;
		}//if
		
		//找到了第i-1个结点，p指向第i-1个结点。 
		
		//q指向p的后继，即第i个结点，也就是被删除结点 
    	q = p->next;
    	
    	//将q指向的被删除结点（第i个结点）后面的结点挂到p指示的
		//第i-1个结点后面。也就是把q指向的第i个结点从链表中隔离出来。 
     	p->next = q->next;
		
		//保存被删除结点的元素值 
    	e = q->data;
    	
    	//释放q指向的被删除结点的内存空间 
    	free(q);
   }//else
   
   //操作成功 
   return OK;
}//ListDelete

/*
	函数：ListTraverse
	参数：LinkList L 不带头结点单链表L的头指针 
	      int i 在第i个位置之前删除
		  ElemType &e 带回被删除的元素e 
	返回值：状态码，操作成功返回OK，否则返回ERROR。 
	作用：遍历不带头结点的单链表L
*/
Status ListTraverse(LinkList L, Status(*Visit)(ElemType)) {
   
   	//工作指针p指向单链表的首元结点 
   	LinkList p = L;
   
   	//依次对单链表中每个元素调用Visit函数进行访问依次且仅一次。
   	while(p) { //while(p) <=> while(p != NULL) 
   		
   		//一旦Visit失败则操作失败
		//if(!Visit(p->data)) <=> if(Visit(p->data) == ERROR)  
		if(!Visit(p->data)) {
			return ERROR;
		}//if
		
		//p指向下一个结点 
     	p = p->next;
	}//while
	
	//输出换行使打印结果美观 
	printf("\n");
}//ListTraverse
 
/*
	函数：Point
	参数：LinkList L 单链表L的头指针（注意，单链表没有头结点） 
	      ElemType e 在单链表中查找元素e所在位置 
		  Status(*equal)(ElemType, ElemType) 函数指针，指向元素比较函数
		  LinkList &p 带回指向e结点前驱结点的指针 
	返回值：状态码，操作成功返回OK，操作失败返回ERROR 
	作用：查找表L中满足条件的结点。如找到，返回指向该结点的指针，
	      p指向该结点的前驱(若该结点是首元结点，则p=NULL)。
		  如表L中无满足条件的结点，则返回NULL，p无定义。
		  函数equal()的两形参的关键字相等，返回OK；否则返回ERROR
*/
LinkList Point(LinkList L, ElemType e, Status(*equal)(ElemType, ElemType), LinkList &p) {
   
   //i存储了查找元素e得到的位置 
   int i, j;
   
   //查找元素e得到元素的位置i，若i=0则说明单链表中未找到元素e 
   //若找到元素e，则L指向找到的结点 
   i = LocateElem(L, e, equal);
   
   //在单链表中找到元素e 
   if(i) { //if(i) <=> if(i != 0) 
   		
		//若找到的是首元结点
		if(i == 1) {
			
			//首元结点没有前驱 
			p = NULL;
			
			//返回指向首元结点的指针 
			return L;
		}//if
		
		//若找到的不是首元结点
		
		//p指向首元结点 
     	p = L;
     	
     	//p指向找到结点的前驱 
		for(j = 2; j < i; j++) { 
			p = p->next;
		}//for
		
		//返回指向找到的结点的指针 
		return p->next;
   }//if
   
   //在单链表中没找到值为e的结点 
   return NULL;
}//Point

/*
	函数：DeleteElem
	参数：LinkList &L 单链表引用（注意，单链表没有头结点） 
	      ElemType &e e携带比较条件 
		  Status(*equal)(ElemType, ElemType) 函数指针，指向元素比较函数
	返回值：状态码，删除表L中满足条件的结点成功返回TRUE；如无此结点，则返回FALSE。
	作用：删除表L中满足条件的结点，并返回TRUE；如无此结点，则返回FALSE。
		  函数equal()的两形参的关键字相等，返回OK；否则返回ERROR
*/
Status DeleteElem(LinkList &L, ElemType &e, Status(*equal)(ElemType,ElemType)) {
 
	//工作指针p和q 
	LinkList p, q;
	
	//从单链表L中找出符合条件的结点，使q指向此结点，p指向q的前驱 
	//若q指向首元结点，p=NULL 
	q = Point(L, e, equal, p);
	
	//找到此结点，且q指向该结点
	if(q) { //if(q) <=> if(q != NULL) 
		
		//该结点不是首元结点，p指向其前驱
    	if(p) { //if(p) <=> if(p != NULL)
    		
    		//将p作为头指针,删除第2个结点
			ListDelete(p, 2, e);
		}//if 
    	else { // 该结点是首元结点
    		
			ListDelete(L, 1, e);
    		
    		//操作成功 
			return TRUE;
    	}//else 
	}//if
	
	//找不到此结点 
	return FALSE;
}//DeleteElem 
