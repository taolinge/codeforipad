
//*********************����ͷ�ļ�**********************************
#include <stdio.h>
#include <stdlib.h>  //ʹ����malloc��free���� 

//********************�Զ�����ų���******************************** 

#define OVERFLOW -2         //�ڴ����������
#define ILLEGAL -1          //�Ƿ����������� 
#define OK 1                //��ʾ������ȷ�ĳ��� 
#define ERROR 0             //��ʾ��������ĳ���
#define LIST_INIT_SIZE 100  //���Ա�洢�ռ�ĳ�ʼ������
#define EQ(a,b) ((a)==(b))  //��� 
#define LT(a,b) ((a)< (b))  //С��
#define LQ(a,b) ((a)<= (b)) //С����� 

//*********************�Զ�����������*******************************

typedef int Status;   //״̬������Ϊint  
typedef int KeyType;  //�ؼ�������Ϊint 
typedef struct{       //Ԫ������ 
	
	//�ؼ����� 
	KeyType key;
}ElemType; 

//------------------��̬���ұ��˳��洢�ṹ------------------- 
typedef struct{
	
	//����Ԫ�ش洢�ռ��ַ������ʱ��ʵ�ʳ��ȷ��䣬0�ŵ�Ԫ����
	ElemType *elem; 
	
	//���ȣ����м�¼�� 
	int length;
}SSTable;

//**************************˳������Ҫ����************************* 

//1.--------------------��̬���ұ�ĳ�ʼ������---------------------------- 

/*
	������InitSSTable_Seq
	������SSTable &ST ��̬���ұ����� 
	����ֵ��״̬�룬�����ɹ�����OK 
	���ã���ʼ����̬���ұ�,����һ���վ�̬���ұ�
*/
Status InitSSTable_Seq(SSTable &ST){

	//������ұ��ڴ�ռ䣬0�ŵ�Ԫ���ա�
	ST.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType) + 1); 
	
	//���ڴ����ʧ�ܣ��˳�����
	if(!ST.elem){  
		printf("�ڴ�����ʧ�ܣ�\n");   
		exit(OVERFLOW); 
	}//if
	
	//���þ�̬���ұ�ST�ĳ���Ϊ0
	ST.length = 0;
	
	//�����ɹ� 
	return OK;    
}//InitSSTable_Seq

//2.----------------------���뾲̬���ұ�Ԫ�صĲ���-------------------

/*
	������SSTableInput_Seq
	������SSTable &ST ��̬���ұ����� 
	����ֵ��״̬�룬�����ɹ�����OK 
	���ã�˳������Ԫ�صĺ���
*/
Status SSTableInput_Seq(SSTable &ST) {
	
	//n����Ԫ�صĸ���,i����ѭ������ 
    int n, i;
	
	//ֱ���û�������ȷΪֹ 
	while(1){
		
		//��ȷ��Ԫ�صĸ���
    	printf("->�������뼸��Ԫ�أ��������������಻���Գ���100  "); 
    	scanf("%d", &n);
    	
    	//���Ԫ�ظ���n�Ƿ�Ϸ� 
    	if(n < 1 || n > 100) { 
    		
    		//�������Ƿ����ݣ��������û���������
        	printf("��������Ƿ������������룡����\n");
        }//if
		
		//������Ϸ����˳�ѭ�� 
		break;
    }//while
    
    //���뾲̬���ұ�����
    printf("�����뾲̬���ұ�ST��Ԫ�أ��м��ÿո��������಻���Գ���100��Ԫ��\n");
	for(i = 1; i <= n; i++) { 
		
		//��ʼ��ÿһ��Ԫ��
		scanf("%d", &ST.elem[i].key); 
    }//for 
    
    //��̬���ұ����ΪԪ�ظ���n 
	ST.length = n;
	
	//�����ɹ� 
	return OK;
}//SSTableInput_Seq
 
//3.------------------�жϾ�̬���ұ��Ƿ�Ϊ��-------------------

/*
	������SSTableEmpty_Seq
	������SSTable ST ��̬���ұ�ST 
	����ֵ��״̬�룬����̬���ұ�Ϊ�ձ���TRUE�����򷵻�FALSE 
	���ã��жϾ�̬���ұ��Ƿ�Ϊ�� 
*/
Status SSTableEmpty_Seq(SSTable ST){
    
    //�鿴���Ƿ�Ϊ0 
	return ST.length == 0;
}//SSTableEmpty_Seq

//4.----------------------��̬���ұ���������------------------

/*
	������Print
	������KeyType e �ؼ��ֵ�ֵe 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERROR 
	���ã�Ԫ�ط��ʺ���
*/
Status Print(KeyType e){

	//���ÿ���̨�����ʽ��ӡ�ؼ���e 
	printf("%3d ", e);
	
	//�����ɹ� 
	return OK;
}//Print

/*
	������SSTableTraverse_Seq
	������SSTable ST ��̬���ұ�ST 
		  Status(* Visit)(KeyType) ����ָ�룬ָ��Ԫ�ط��ʺ��� 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERROR 
	���ã�������̬���ұ���
*/
Status SSTableTraverse_Seq(SSTable ST, Status(* Visit)(KeyType)){
	
	//���ʾ�̬���ұ���ÿһ��Ԫ��һ���ҽ�һ�� 
	for(int i = 1; i <= ST.length; ++i) { 
		
		//һ������ʧ�������ʧ��
		//if(!Visit(ST.elem[i].key)) <=> if(Visit(ST.elem[i].key) == ERROR)
		if(!Visit(ST.elem[i].key)) {
		    return ERROR;
		}//if 
	}//for 
	
	//�������ʹ������� 
	printf("\n");
	
	//�����ɹ� 
	return OK;
}//SSTableTraverse_Seq



//5.----------------------˳����˳������㷨------------------ 

/*
	������SSTableTraverse_Seq
	������SSTable ST ��̬���ұ�ST 
		  KeyType key �����ҵĹؼ��� 
	����ֵ�����ҵ�������ֵΪ��Ԫ���ڱ��е�λ�ã�����Ϊ0
	���ã���˳���ST��˳�������ؼ��ֵ���key������Ԫ�ء�
*/
int Search_Seq(SSTable ST, KeyType key){
	
	//i��ѭ���������洢�˹ؼ����ڱ��е�λ�� 
	int i; 
	
	//0�ŵ�Ԫ���ű���������Ԫ�أ��Źؼ��֣������൱��"�ڱ�",
	//�ô����ڲ���ʱʱ�������Խ������ 
	ST.elem[0].key = key;
	
	//�Ӻ���ǰ���ң�ֱ���ҵ�Ԫ�ػ������ڱ�Ϊֹ 
	for(i = ST.length; !EQ(ST.elem[i].key, key); --i);
	
	//���عؼ����ڱ��е�λ��i 
	return i;  
}//Search_Seq 

//6.-----------------------��̬���ұ���������-------------------

/*
	������SortSSTable_Seq
	������SSTable &ST ��̬���ұ����� 
	����ֵ�����ҵ�������ֵΪ��Ԫ���ڱ��е�λ�ã�����Ϊ0
	���ã�����˳�����Ԫ��,ʹ˳����Ϊ������Ա��ڶ��������в��� 
*/
Status SortSSTable_Seq(SSTable &ST) {
    //�����Ա��е�Ԫ������,ʹ��ð�ݷ���
	/*��ͳð��������ÿһ���������ֻ���ҵ�һ�����ֵ����Сֵ,
	  ���ǿ���������ÿ�������н�������ͷ�������ð�ݵķ���
	  һ�ο��Եõ���������ֵ(����ߺ���С��),�Ӷ�ʹ������������������һ��*/ 
	
	//�Կձ�������û���� 
	if(SSTableEmpty_Seq(ST)) { 
		return ERROR; 
	}//if 
	
	int low = 1, high = ST.length, tmp, j;    
    
	while (low < high) {
		
		//����ð��,�ҵ������ 
        for (j = low; j < high; ++j) { 
            if (ST.elem[j].key > ST.elem[j + 1].key){  
                tmp = ST.elem[j].key; 
				ST.elem[j].key = ST.elem[j + 1].key;
				ST.elem[j + 1].key = tmp;  
            }//if   
        }//for 
        
        //�޸�highֵ, ǰ��һλ
        --high;
        
        //����ð��,�ҵ���С��
        for (j = high; j > low; --j) {
            if (ST.elem[j].key < ST.elem[j - 1].key) {  
                tmp = ST.elem[j].key; 
				ST.elem[j].key = ST.elem[j - 1].key;
				ST.elem[j - 1].key = tmp;  
            }//if
    	}//for
		
		//�޸�lowֵ,����һλ 
        ++low; 
    }//while  
} //SortSSTable_Seq

//7.----------------------�������۰�����㷨------------------

/*
	������Search_Bin
	������SSTable ST ��̬���ұ�ST 
	����ֵ�����ҵ�������ֵΪ��Ԫ���ڱ��е�λ�ã�����Ϊ0 
	���ã��������ST���۰������ؼ��ֵ���key������Ԫ��
*/
int Search_Bin(SSTable ST, KeyType key){
	
	//�������ֵ
	int low = 1, high = ST.length, mid;
	
	//��low > highʱ���ҽ��� 
	while(low <= high){
		
		//�����mid 
		mid = (low + high) / 2;
		
		//�ҵ�����Ԫ��
		if(EQ(key, ST.elem[mid].key)) {
		    return mid;
		}//if
		//������ǰ��������в��� 
	    else if(LT(key,ST.elem[mid].key)) {
	        high = mid - 1;
		}//else if 
	    //�����ں��������в���
		else { 
	        low = mid + 1;
		}//else 
	}//while 
	
	//˳����в����ڴ���Ԫ��
	return 0; 
}//Search_Bin 

//8.-----------------------��̬���ұ�����ٲ���--------------------

/*
	������DestorySSTable_Seq
	������SSTable &ST ��̬���ұ����� 
	����ֵ���� 
	���ã����پ�̬���ұ�ST
*/
void DestorySSTable_Seq(SSTable &ST){
    
	//�ͷž�̬���ұ��ڴ�ռ� 
	free(ST.elem);
	
	//ָ���ÿ� 
	ST.elem = NULL;
	
	printf("�ڴ�ռ��ͷųɹ�!\n");  
} //DestorySSTable_Seq

//***************************************������******************************************** 
int main(int argc,char *argv[]){ 

	//����˳����ұ�ST 
    SSTable ST; 
	
	//�ؼ���         
	KeyType key;
	
	//״̬��־
	Status flag;
	 
	printf("\n***************************˳������������㷨����***************************\n");
	
	printf("->����һ����̬���ң�˳�򣩱��밴Ҫ����в���\n"); 
	InitSSTable_Seq(ST);
	SSTableInput_Seq(ST);
	printf("->�������ľ�̬���ұ����������Ԫ�����£�\n");
	SSTableTraverse_Seq(ST, Print);
	
	printf("->������������˳����в��ҵ�Ԫ�أ�\n");
	scanf("%d", &key);
	flag=Search_Seq(ST, key); 
	if(!flag) { 
	   printf("����ʧ�ܣ�\n"); 
	}//if 
	else {
	   printf("���ҳɹ�����Ԫ���ڱ��е�λ��Ϊ%d,���и�λ��Ԫ��ֵΪ%d��\n",
	   		flag, ST.elem[flag].key);
	}//else
	 
	printf("��˳�������׼�������������ҡ�\n");
	SortSSTable_Seq(ST);
	printf("->�����˳����Ϊ�������������Ԫ�������ǣ�\n");
	SSTableTraverse_Seq(ST, Print);
	
	printf("->������������������в��ҵ�Ԫ�أ�\n");
	scanf("%d", &key);
	flag=Search_Bin(ST, key); 
	if(!flag) {
	   printf("����ʧ�ܣ�\n"); 
	}//if 
	else {
	   printf("���ҳɹ�����Ԫ���ڱ��е�λ��Ϊ%d,���и�λ��Ԫ��ֵΪ%d��\n",
	   		flag, ST.elem[flag].key);
	}//else
	 
	printf("->���پ�̬���ұ�ST��");
	DestorySSTable_Seq(ST); 
	
	return 0;	
}//main 

/*
	����P219ҳ 

***************************˳������������㷨����***************************
->����һ����̬���ң�˳�򣩱��밴Ҫ����в���
->�������뼸��Ԫ�أ��������������಻���Գ���100  11
�����뾲̬���ұ�ST��Ԫ�أ��м��ÿո��������಻���Գ���100��Ԫ��
05 13 19 21 37 56 64 75 80 88 92
->�������ľ�̬���ұ����������Ԫ�����£�
  5  13  19  21  37  56  64  75  80  88  92
->������������˳����в��ҵ�Ԫ�أ�
12
����ʧ�ܣ�
��˳�������׼�������������ҡ�
->�����˳����Ϊ�������������Ԫ�������ǣ�
  5  13  19  21  37  56  64  75  80  88  92
->������������������в��ҵ�Ԫ�أ�
88
���ҳɹ�����Ԫ���ڱ��е�λ��Ϊ10,���и�λ��Ԫ��ֵΪ88��
->���پ�̬���ұ�ST���ڴ�ռ��ͷųɹ�!

--------------------------------
Process exited with return value 0
Press any key to continue . . .

*/
