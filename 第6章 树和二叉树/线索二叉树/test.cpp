#include <stdio.h>
#include <iostream>
using namespace std;  

typedef int TElemType; 

//----------------原始二叉链表------------------------ 
struct BiNode{
	TElemType  data;
	struct BiNode  *lchild,*rchild;   //孩子结点指针 
};

//--------------------线索二叉树标志位--------------- 
typedef enum{
	Link,   //Link(0)：  指针 0
	Thread  //Thread(1)：线索 1
}PointerTag; 

//----------------线索二叉树（不加左右标志）--------- 
struct BiThrNode1{
	TElemType data;                     //数据域，存储节点数据 
	struct BiThrNode *lchild, *rchild;  //左右孩子指针
};

//-----------------线索二叉树（加左右标志）--------- 
struct BiThrNode{
	TElemType data;                     //数据域，存储节点数据 
	struct BiThrNode *lchild, *rchild;  //左右孩子指针
	PointerTag LTag, RTag;              //左右标志
};

int main() {  
    int a = 1;  
    char b = 'a';  
    float c = 1.0;
    void *p; 
    
    printf("int型变量所占用的大小(字节)：%d\n", sizeof(int));
	printf("float型变量所占用的大小(字节)：%d\n", sizeof(float)); 
	printf("char型变量所占用的大小(字节)：%d\n", sizeof(char)); 
	printf("C++支持（C语言不支持）：boolean型变量所占用的大小(字节)：%d\n", sizeof(bool)); 
	printf("unsigned int型变量所占用的大小(字节)：%d\n", sizeof(unsigned int));
	printf("short型变量所占用的大小(字节)：%d\n", sizeof(short));
	
	p = &a;  
    printf("指向int型变量的指针变量所占用的大小(字节)：%d\n", sizeof(p));  
    p = &b;  
    printf("指向char型变量的指针变量所占用的大小(字节)：%d\n", sizeof(p));  
    p = &c;  
    printf("指向float型变量的指针变量所占用的大小(字节)：%d\n", sizeof(p)); 
	
	printf("枚举类型所占用的大小(字节)：%d\n", sizeof(PointerTag));  
    
    printf("原来的二叉链表结点大小（字节）：%d\n", sizeof(struct BiNode)); 
	printf("线索二叉树结点（不加标志位）大小（字节）：%d\n", sizeof(struct BiThrNode1)); 
	printf("线索二叉树结点（加标志位）大小（字节）：%d\n", sizeof(struct BiThrNode));
	int tagsize = (sizeof(struct BiThrNode) - sizeof(struct BiThrNode1)) / 2;
	printf("标志位在结构体中的大小（字节）：%d\n", tagsize);
	
	PointerTag pt1 = Link;
    PointerTag pt2 = Link;
    
    printf("&pt1=  %d, &pt2= %d\n", &pt1, &pt2);
    
     
    return 0;  
} //main
