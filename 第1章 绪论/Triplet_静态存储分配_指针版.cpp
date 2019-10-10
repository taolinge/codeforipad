/*
      ���ʵ�ֳ����������͡���Ԫ�� ��Triplet���� �� 
   ÿ����Ԫ������������ʵ�������й��ɣ���������������
   ����һ����Ԫ�飬ȡ��Ԫ�������һ������������Ԫ��
   ������һ������������Ԫ�������������С������
   ��ʾ��Ԫ�飬������Ԫ��ȡ�
      
   ����1���ýṹ���װ��Ҫ������������ͣ��綨����Ԫ��ADTʱ��
	�����ýṹ���װ����Ԫ�顱������������
	������typedef�Խṹ������������
*/
#include<stdio.h>
#define OK 1
#define ERROR 0

typedef int Status;
typedef float ElemType;  //��Ԫ��Ԫ�ص������ȶ���Ϊint,������ʱ�任�ɱ������ 
typedef struct
{
	ElemType e[3];
}Triplet;

//��Ԫ��ĳ�ʼ��
Status initTriplet(Triplet *T,ElemType v0,ElemType v1,ElemType v2)
{
	T->e[0]=v0;
	T->e[1]=v1;
	T->e[2]=v2;
	return OK;
}
//������Ԫ��,��̬�洢���ڳ���ʼ��ʱ��ͷ���̶����ڴ浥Ԫ����������������Զ��ͷŴ洢��Ԫ���������� 
//����̬�洢��Ԫ�ڳ������г��������ڴ浥Ԫ���õ�ʱ�ŷ��䣬�����ù�����Ҫ������ͷŸ��ڴ�ռ�
Status destroyTriplet(Triplet *T)
{
	return OK;
}
//��e��ȡT�ĵ�i(1~3)��Ԫ�ص�ֵ�� 
Status getElem(Triplet T,int i,ElemType *e)
{
	if(i<1||i>3)
		return ERROR;
	else *e=T.e[i-1];
		return OK;
}
//��T�ĵ�iԪ��ֵΪe 
Status putElem(Triplet *T,int i,ElemType e)
{
	if(i<1||i>3)
		return ERROR;
	else T->e[i-1]=e;
		return OK;
}
//���T������Ԫ�ذ��������У��򷵻�1�����򷵻�0
Status isAscending(Triplet *T)
{
	return (T.e[0]<=T.e[1])&&(T.e[1]<=T.e[2]);
} 
//���T������Ԫ�ذ��������У��򷵻�1�����򷵻�0
Status isDescending(Triplet T)
{
	return (T.e[0]>=T.e[1])&&(T.e[1]>=T.e[2]);
} 
//��e����ָ��T�����Ԫ�ص�ֵ
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
//��e����ָ��T����СԪ�ص�ֵ
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
	printf("�������Ԫ�������ֵv0,v1,v2:\n"); 
	scanf("%f,%f,%f",&v0,&v1,&v2);
	flag=initTriplet(&T,v0,v1,v2);
	printf("���ó�ʼ��������flag=%d,T������ֵΪ��%4.2f,%4.2f,%4.2f\n",flag,T.e[0],T.e[1],T.e[2]);
	if(isAscending(T)) 	printf("����Ԫ��Ԫ��Ϊ����\n");
	if(isDescending(T)) printf("����Ԫ��Ԫ��Ϊ����\n");
	printf("����Ԫ���е����ֵΪ��%4.2f,��СֵΪ��%4.2f",getMax(T),getMin(T));
	return OK;
} 
 

