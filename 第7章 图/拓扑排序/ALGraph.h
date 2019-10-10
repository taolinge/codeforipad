//---------------------ͼ���ڽӱ�洢��ʾ---------------------- 

//ָ������������int
typedef int VertexType;

//ָ������Ȩֵ����Ϊint 
typedef int InfoType;

//��󶥵��� 
#define MAX_VERTEX_NUM 50

//ͼ�������־ 
typedef enum {
	
	// {����ͼ = 0,������ = 1,����ͼ = 2,������ = 3}
	DG, DN, UDG, UDN
} GraphKind;

//�洢����Ϣ�Ľ��

typedef struct ElemType{
	
	//�û���ָ��Ķ����λ�ã�Ҳ���Ǵӵ�ǰ�������ָ���ĸ����� 
	//��������洢����ָ�򶥵���AdjList�����е��±� 
	int adjvex;
	
	//�û������Ϣ��ָ��
	//���������Ϣ���Ǵ��Ȩֵ�ģ���ͼ������������ʱ����������������� 
	InfoType *info;
} ElemType;
 
typedef struct ArcNode{  
	
	//���˻�ָ������������־�����data 
	ElemType data;
	
	//ָ����һ������ָ��
	struct ArcNode *nextarc;	
} ArcNode;

//�洢������Ϣ�Ľ�� 
typedef struct VNode {
	
	//�������� 
	VertexType data;
	
	//ָ���һ�������ö���Ļ����洢��һ���߽���ַ��ָ���� 
	ArcNode  *firstarc;
} VNode, AdjList[MAX_VERTEX_NUM];

//ͼ���ڽӱ�洢��ʾ 
typedef struct ALGraph {
	
	//�����������������д洢��ͼ�����еĶ��� 
	AdjList  vertices;
	
	//ͼ�ĵ�ǰ�������ͻ���(����)
    int vexnum, arcnum;
    
	//ͼ�������־
	GraphKind kind; 
} ALGraph;

//Ϊ�˸��õ������еĲ��롢ɾ���Ȼ������������ú궨�巽ʽ�������ĵ�����ʵ��
//�����ͼ���ڽӱ�洢�ṹ�Ĳ����Խ� 

//���嵥����Ľ��������ͼ�ı��������
#define LNode ArcNode

//���嵥�������ָ�����Ǳ���ָ����һ������ָ����
#define next nextarc

//����ָ���������ָ����ָ��ͼ�ı����ָ�� 
typedef ArcNode *LinkList;
