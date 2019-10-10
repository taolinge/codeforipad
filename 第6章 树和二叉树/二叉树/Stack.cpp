//-------------------ջ��˳��洢��ʾ------------------------- 

typedef BiTree SElemType;   //ջ��Ԫ��Ϊ������ָ������ 
typedef struct {          //ջ��˳��洢��ʾ                        
	SElemType *base;            //ջ��ָ�룬��ջ����֮ǰ������֮��base��ֵΪNULL 
	SElemType *top;             //ջ��ָ��
	int stacksize;              //��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ 
}Stack; 

//--------------------------ջ����غ���(���ǵݹ�������ʹ��)----------------------------
/*
	������InitStack_Sq
	������Stack &S ˳��ջ����  
	����ֵ��״̬�룬OK��ʾ�����ɹ� 
	���ã�����һ���յ�˳��ջ 
*/
Status InitStack(Stack &S){
	
	//��̬����˳��ջ���ڴ�ռ䣬������ڴ�ռ��Ƿ�ɹ�����
	//if(!(S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType))))
	//�������൱���������д��룺
	//S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	//if(!S.base)  <=>  if(S.base == NULL) 
	if(!(S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType)))){
		printf("�ڴ����ʧ�ܣ����򼴽��˳���\n");
		exit(OVERFLOW);
	}//if
	
	//���ڸն�̬�������ջ�ǿ�ջ������ջ��ָ���ջ��ָ�붼ָ��ջ��   
	S.top = S.base;
	
	//ջ�Ĵ�С����ջ�ĳ�ʼ����С����STACK_INIT_SIZE 
	S.stacksize = STACK_INIT_SIZE;
	
	//�����ɹ� 
	return OK; 
}//InitStack_Sq

/*
	������DestoryStack_Sq
	������Stack &S ˳��ջ����  
	����ֵ��״̬�룬OK��ʾ�����ɹ� 
	���ã��ͷ�˳��ջS��ռ�ڴ�ռ� 
*/
Status DestoryStack(Stack &S){
	
	//ջ��ָ�뱣�����˳��ջ�ڴ�ռ���׵�ַ 
	free(S.base);
	
	//�����ɹ� 
	return OK; 
}//DestoryStack_Sq

/*
	������StackIsEmpty_Sq
	������Stack S ˳��ջS 
	����ֵ����˳��ջS�ǿ�ջ����1���񷵻�0 
	���ã��ж�˳��ջS�Ƿ�Ϊ��ջ
*/
Status StackIsEmpty(Stack S){
	
	//ջ��ָ���ջ��ָ�붼ָ��ջ�ױ�ʾ��ջ�ǿ�ջ 
	return S.top == S.base; 
}//StackIsEmpty_Sq

/*
	������ReallocStack_Sq
	������Stack &S ˳��ջS���� 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERRROR
	���ã���ջS���ݣ�ÿ����һ�Σ�ջ�Ĵ�С����STACKINCREMENT
*/
Status ReallocStack(Stack &S){
	
	//Ϊ˳��ջ���·����ڴ�(����)����չ�Ŀռ��С��STACKINCREMENT
	/*if(!(S.base = (SElemType *)realloc(S.base, 
	            (STACK_INIT_SIZE + STACKINCREMENT) * sizeof(SElemType))))
	  �������൱�ڣ�
	  S.base = (SElemType *)realloc(S.base, 
	                    (STACK_INIT_SIZE + STACKINCREMENT) * sizeof(SElemType));
	  if(!S.base) <=> if(S.base == NULL)
	*/
	if(!(S.base = (SElemType *)realloc(S.base, 
	           (STACK_INIT_SIZE + STACKINCREMENT) * sizeof(SElemType)))){
		printf("�ڴ����ʧ�ܣ����򼴽��˳���\n");
		exit(OVERFLOW);
	}//if
	
	//��������ǰջ�Ѿ����ˣ�����ջ��ָ��λ�þ���ջ��ָ��+ԭ��ջ�Ĵ�С 
	S.top = S.base + S.stacksize;
	
	//���ݺ�ջ�Ĵ�С������STACKINCREMENT 
	S.stacksize += STACKINCREMENT;
	
	//�����ɹ� 
	return OK; 
}//ReallocStack_Sq

/*
	������Push_Sq
	������Stack &S ˳��ջ����
	      SElemType e �������Ԫ��e 
	����ֵ���ɹ���ȡ˳��ջSջ��Ԫ�ص�ֵ�󷵻�OK�����򷵻�ERRROR
	���ã�����ջ��ѹջ������Ԫ��eΪ�µ�ջ��Ԫ��
*/
Status Push(Stack &S, SElemType e){ 
	
	//��ջʱ����ջ���ˣ���Ҫ׷�Ӵ洢�ռ䣨���ݣ� 
	if(S.top - S.base >= S.stacksize) {  
	    
	    //�������ݺ���
		ReallocStack(S);
	}//if
	
	//����ǰ��ջ��ָ��ָ��ǰջ��Ԫ�ص���һ��λ�� 
	//��e��ֵ��ջ��ָ����ָ�洢�ռ䣨����Ԫ��e����ջ��ָ�����
	//*S.top++ = e;  <=>  *(S.top) = e;  S.top++; 
	*S.top++ = e;
	
}//Push_Sq

/*
	������Pop_Sq
	������Stack &S ˳��ջ����
	      SElemType &e ���ر�ɾ����Ԫ��ֵe 
	����ֵ��ɾ���ɹ�����OK�����򷵻�ERRROR
	���ã�����ջ����ջ����ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ
*/
Status Pop(Stack &S, SElemType &e){ 
	
	//�ڿ�ջ��ִ�г�ջ����û�����壬����Ҫ�ж�ջ�Ƿ�Ϊ��
	//ע��ջ�Ƿ�Ϊ�պ�ջ�Ƿ���ڲ���һ��������Բ������� 
	//S.base != NULL�ж�ջ�Ƿ�Ϊ�� 
	if(StackIsEmpty(S)) { 
	     return ERROR;
	}//if
	
	//ɾ��ǰ��ջ��ָ��ָ��ǰջ��Ԫ�ص���һ��λ��
	//--S.top;֮��ջ��ָ��պ�ָ��ɾ��Ԫ�� 
	//ջ��ָ��ǰ�ƣ����汻ɾ����Ԫ��ֵ��e
	//e=*--S.top;  <=>  --S.top;   e=*(S.top);
	e = *--S.top;
	
	//�����ɹ� 
	return OK; 
}//Pop_Sq

/*
	������GetTop
	������Stack S ˳��ջS
	����ֵ���ɹ���ȡ˳��ջSջ��Ԫ�ص�ֵ�󷵻�OK�����򷵻�ERRROR
	���ã���e����ջ��Ԫ�ص�ֵ������ջ��Ԫ�ز�����ջ���� 
*/
Status GetTop(Stack S, SElemType &e){
	
	//��ջû��ջ��Ԫ�أ�����Ҫ���ж�ջ�Ƿ�Ϊ�� 
	//ע��ջ�Ƿ�Ϊ�պ�ջ�Ƿ���ڲ���һ��������Բ������� 
	//S.base != NULL�ж�ջ�Ƿ�Ϊ�� 
	if(StackIsEmpty(S)) { 
	     return ERROR;
	}//if
	
	//ע�⣺ջ��ָ��ָ��ջ��Ԫ�ص���һ��λ��
	e = *(S.top - 1);  
	/*   ע�⣺�˴�����ʹ�á�e = *(--S.top); ����ԭ�� 
		 1. --S.top�Լ������ı���ջ��ָ�뱾���ָ��ʹ�ø�ָ����ǰ�ƶ�һλ���൱��ɾ����ԭ��ջ�е����һ��Ԫ�أ����һ��Ԫ�س�ջ���� 
		 2. S.top-1 ������ʾջ��ָ�����һ��λ�ã���û�иı�S.top��ֵ��*(S.top-1)��ʾȡջ��ָ��ǰһ��λ�õ�ֵ����ջ��Ԫ�ص�ֵ  
		 3. ������д����ɵĽ���ǲ�ͬ�ģ�����Ǵ��������㣬����û�в��,����ָ������
			��˳��ṹ��C����������һά���������ģ���ָ����������У����������ʽ�����⺬�� 
			��ָ�������У���ָ�����-1 ����ʾ��ָ�������ָλ�õ�ǰһ��λ�ã�
			�������������ı�ָ����������ֵ�� 
			--ָ�����   ����ʹ�ø�ָ��ָ��ԭ����ָλ�õ���һ��λ��, ���޸���ָ����������ֵ
			��ջ�У�ջ��ָ���ջ��ָ����ָ���λ��������ĺ��壬�����߲��ȼۡ�       
	 */ 
	 
	 //�����ɹ� 
	 return OK; 
}//GetTop_Sq

/*
	������StackLength_Sq
	������Stack S ˳��ջS 
	����ֵ����˳��ջS�ǿ�ջ����1���񷵻�0 
	���ã��ж�˳��ջS�Ƿ�Ϊ��ջ
*/
Status StackLength(Stack S){
	
	//ջ�ĳ��Ⱦ���ջ��ָ���ջ��ָ��֮���Ԫ�ظ��� 
	return (S.top - S.base); 
}//StackLength_Sq

/*
	������Print
	������ElemType e �����ʵ�Ԫ�� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã�����Ԫ��e�ĺ�����ͨ���޸ĸú��������޸�Ԫ�ط��ʷ�ʽ��
	      �ú���ʹ��ʱ��Ҫ��ϱ�������һ��ʹ�á� 
*/
Status Print_Stack(SElemType e){
	printf("%5d  ", e);
	return OK;
}//Print 

/*
	������StackTraverse_Sq
	������Stack S ˳��ջS 
	      Status(* visit)(SElemType) ����ָ�룬ָ��Ԫ�ط��ʺ����� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã�����Ԫ�ط��ʺ�������ջ˳�����˳��ջ�ı���������δ����ִ�г�ջ���� 
*/
Status StackTraverse(Stack S, Status(* visit)(SElemType)) {
	
	//�ڿ�ջ��ִ�б�������û�����壬����Ҫ�ж�ջ�Ƿ�Ϊ��
	//ע��ջ�Ƿ�Ϊ�պ�ջ�Ƿ���ڲ���һ��������Բ������� 
	//S.base != NULL�ж�ջ�Ƿ�Ϊ�� 
	if(StackIsEmpty(S)) {
		printf("��ջ�ǿ�ջ"); 
	    return ERROR;
	}//if
	
	//����Ԫ�ط��ʺ������η���ջ�е�ÿ��Ԫ��
	for(int i = 0; i < StackLength(S); ++i){
		
		//����Ԫ�ط��ʺ�����һ������ʧ�����˳�  
		if(!visit(S.base[i])) {
			return ERROR;
		}//if 
	}//for
	
	//������У��ǿ���̨��ʾ���� 
	printf("\n");
	
	//�����ɹ� 
	return OK;
}//StackTraverse_Sq
