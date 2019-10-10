//-------------ͼ�����飨�ڽӾ��󣩴洢��ʾ

//һ�������Ȩֵ���Ѵﵽ�����ֵ ��
#define INFINITY 65535

//��󶥵����
#define MAX_VERTEX_NUM 20

//ʹ��ö�����Ͷ���ͼ�����ֻ������� 
typedef enum {
	
	//������ͼ=0��������=1������ͼ=2��������=3��
	DG, DN, UDG, UDN
} GraphKind;

//ָ�������ϵ����Ϊint 
typedef int VRType;

//ָ����������Ϊint 
typedef int VertexType;

typedef struct ArcCell{
	
	//VRType�Ƕ����ϵ���͡�
	//����Ȩͼ����1��0����ʾ������񣬶Դ�Ȩͼ����ΪȨֵ���� 
	VRType adj;
	
	//���޸������ϵĶ���ɾ����infoָ�롣
	//ԭ���ǣ�infoָ����ȫû��Ҫ���ã���Ϊ������ͼ��������
	//        adj����������Ѿ��㹻�洢����������Ϣ�ˡ�
	//        ��������infoָ��ı�����ָ��洢��Ȩֵ���ڴ�ռ䡣
	//        ��������adj������ܴ洢���е�Ȩֵ��Ҳ������������
	//        ����������info֮�󻹻��漰�ܶ��ڴ�ķ��䡢�ͷź�ָ�����
	//        Ϊ��ʹһ����������������ͼ����Ҫ����ͼ�Ĳ�ͬ���Ͷ����ָ��
	//        ִ�в�ͬ�Ĳ�����ȥ��info���Լ򻯲����� 
	 
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; 

typedef struct{
	
	//��������:�洢��ͼ�����еĶ��� 
	VertexType vexs[MAX_VERTEX_NUM];
	
	//�ڽӾ��󣺴洢�˶���֮����ڽӹ�ϵ�Լ�Ȩֵ 
	AdjMatrix arcs; 
	
	//ͼ��ǰ�Ķ������ͻ���
	int vexnum, arcnum;
	
	//ͼ�������־ 
	GraphKind kind;
}MGraph; 
