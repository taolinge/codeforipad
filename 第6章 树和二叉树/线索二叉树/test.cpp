#include <stdio.h>
#include <iostream>
using namespace std;  

typedef int TElemType; 

//----------------ԭʼ��������------------------------ 
struct BiNode{
	TElemType  data;
	struct BiNode  *lchild,*rchild;   //���ӽ��ָ�� 
};

//--------------------������������־λ--------------- 
typedef enum{
	Link,   //Link(0)��  ָ�� 0
	Thread  //Thread(1)������ 1
}PointerTag; 

//----------------�������������������ұ�־��--------- 
struct BiThrNode1{
	TElemType data;                     //�����򣬴洢�ڵ����� 
	struct BiThrNode *lchild, *rchild;  //���Һ���ָ��
};

//-----------------�����������������ұ�־��--------- 
struct BiThrNode{
	TElemType data;                     //�����򣬴洢�ڵ����� 
	struct BiThrNode *lchild, *rchild;  //���Һ���ָ��
	PointerTag LTag, RTag;              //���ұ�־
};

int main() {  
    int a = 1;  
    char b = 'a';  
    float c = 1.0;
    void *p; 
    
    printf("int�ͱ�����ռ�õĴ�С(�ֽ�)��%d\n", sizeof(int));
	printf("float�ͱ�����ռ�õĴ�С(�ֽ�)��%d\n", sizeof(float)); 
	printf("char�ͱ�����ռ�õĴ�С(�ֽ�)��%d\n", sizeof(char)); 
	printf("C++֧�֣�C���Բ�֧�֣���boolean�ͱ�����ռ�õĴ�С(�ֽ�)��%d\n", sizeof(bool)); 
	printf("unsigned int�ͱ�����ռ�õĴ�С(�ֽ�)��%d\n", sizeof(unsigned int));
	printf("short�ͱ�����ռ�õĴ�С(�ֽ�)��%d\n", sizeof(short));
	
	p = &a;  
    printf("ָ��int�ͱ�����ָ�������ռ�õĴ�С(�ֽ�)��%d\n", sizeof(p));  
    p = &b;  
    printf("ָ��char�ͱ�����ָ�������ռ�õĴ�С(�ֽ�)��%d\n", sizeof(p));  
    p = &c;  
    printf("ָ��float�ͱ�����ָ�������ռ�õĴ�С(�ֽ�)��%d\n", sizeof(p)); 
	
	printf("ö��������ռ�õĴ�С(�ֽ�)��%d\n", sizeof(PointerTag));  
    
    printf("ԭ���Ķ����������С���ֽڣ���%d\n", sizeof(struct BiNode)); 
	printf("������������㣨���ӱ�־λ����С���ֽڣ���%d\n", sizeof(struct BiThrNode1)); 
	printf("������������㣨�ӱ�־λ����С���ֽڣ���%d\n", sizeof(struct BiThrNode));
	int tagsize = (sizeof(struct BiThrNode) - sizeof(struct BiThrNode1)) / 2;
	printf("��־λ�ڽṹ���еĴ�С���ֽڣ���%d\n", tagsize);
	
	PointerTag pt1 = Link;
    PointerTag pt2 = Link;
    
    printf("&pt1=  %d, &pt2= %d\n", &pt1, &pt2);
    
     
    return 0;  
} //main
