/*
ADT Graph {
	
	���ݶ���V��V�Ǿ�����ͬ���Ե�����Ԫ�صļ��ϣ���Ϊ���㼯��
	���ݹ�ϵR��
			R = {VR}
			VR = {<v,w>| v,w��V �� P(v,w), <v,w>��ʾ�� v �� w �Ļ���
 						ν�� P(v,w) �����˻� <v,w>���������Ϣ��}
 	��������P:
 		CreatGraph(&G, V, VR);
 		//��ʼ������V��ͼ�Ķ��㼯��VR��ͼ�л��ļ��ϡ� 
		//�����������V��VR�Ķ��幹��ͼG�� 
		
		DestroyGraph(&G);
		//��ʼ������ͼG���ڡ� 
		//�������������ͼG�� 
		
		LocateVex(G, u);
		//��ʼ������ͼG���ڣ�u��G�ж����й�ͬ���� 
		//�����������G�д��ڶ���u���򷵻ظö�����ͼ��λ�ã����򷵻�������Ϣ��

		GetVex(G, v);
		//��ʼ������ͼG���ڣ�v��G��ĳ�����㡣 
		//�������������v��ֵ��
		
		PutVex(&G, v, value);
		//��ʼ������ͼG���ڣ�v��G��ĳ�����㡣 
		//�����������v��ֵvalue��
		
		FirstAdjVex(G, v); 
		//��ʼ��������ͼG���ڣ�v��G�е�ĳ�����㡣 
		//�������������v�ĵ�һ���ڽӵ㡣���ö�����G��û���ڽӵ㣬�򷵻ؿա�

		NextAdjVex(G, v, w);
		//��ʼ������ͼG���ڣ� v��G�е�ĳ�����㣬w��v���ڽӶ��㡣 
		//�������������v�ģ������w�ģ���һ���ڽӵ㡣
		            ��w��v�����һ���ڽӵ㣬�򷵻ؿա�

		InsertVex(&G, v); 
		//��ʼ������ͼG���ڣ�v��ͼ�еĶ�������ͬ������ 
		//�����������ͼG�������¶���v��

		DeleteVex(&G, v);
		//��ʼ������ͼG���ڣ�v��w��G�е��������� 
		//���������ɾ��G�ж���v������صĻ���

		InsertArc(&G, v, w); 
		//��ʼ������ͼG���ڣ�v��w��G�е��������㡣 
		//�����������G������<v,w>����G������ģ�������Գƻ�<w,v>��

		DeleteArc(&G, v, w);
		//��ʼ������ͼG���ڣ�v��w��G�е��������㡣  
		//�����������G��ɾ����<v,w>����G������ģ���ɾ���Գƻ�<w,v>��

		DFSTraverse(G, v, Visit());
		//��ʼ������ͼG���ڣ�Visit�Ƕ���ĺ����� 
		//�����������ͼ����������ȱ������ڱ��������ж�ÿ��������ú���
		            Visitһ���ҽ�һ�Ρ�һ��Visitʧ�������ʧ�ܡ� 

		BFSTraverse(G, v, Visit());
		//��ʼ������ͼG���ڣ�Visit�Ƕ����Ӧ�ú����� 
		//�����������ͼ���й�����ȱ������ڱ��������ж�ÿ��������ú���
		            Visitһ���ҽ�һ�Ρ�һ��Visitʧ�������ʧ�ܡ� 
}ADT Graph
*/ 

//**********************ͼ���ڽӾ��󣩵���Ҫ����**********************  

/*˵����ͼ��������Ȩֵ���ľ���    ��������� ���öԳƻ����

                                       ��Ȩֵ  0,1�� �� 
                       ����ͼ <------------------------------> ������      
                          |            ȥȨֵ  �ޱ� 0,1          | 
                          |                                      |
        	ȥ�Գƻ����  |  �öԳƻ����         ȥ�Գƻ����   |   �öԳƻ���� 
                          |                                      |
                          |            ��Ȩֵ  0,1�� ��          |
                       ����ͼ <------------------------------> ������
			                           ȥȨֵ  �ޱ� 0,1
*/ 

/*
	������LocateVex
	������MGraph G ͼG���ڽӾ���洢�ṹ�� 
	����ֵ����G�д��ڶ���v���򷵻ظö�����ͼ��λ�ã����򷵻�-1
	���ã����㶨λ��������ͼG�в��Ҷ���v��λ�� 
*/
int LocateVex(MGraph G, int v){
	
	//�����ڽӾ�����Ҷ���v 
	for(int i = 0; i <= G.vexnum; ++i) { 
		
		//���ҵ���㷵��i
		if(G.vexs[i] == v) {
		    return i;
		}//if 
	}//for
	
	//���򷵻�-1����ʾû���ҵ� 
	return -1;
}//LocateVex

/*
	������CreateUDN
	������MGraph &G ͼ������ 
	����ֵ��״̬�룬�����ɹ�����OK 
	���ã��������飨�ڽӾ��󣩱�ʾ��������������G
*/
Status CreateUDN(MGraph &G){
	
	//��ʱ�������Ӽ��̽��ն������� 
	VertexType v1, v2;
	
	//��ʱ����i���ڱ��涥��v1��ͼ�е����
	//��ʱ����j���ڱ��涥��v2��ͼ�е���� 
	//��ʱ����w���ڽ��������Ȩֵ 
	int w, i, j;
	
	//ȷ���������Ķ������ͱ��� 
	printf("����������������G�Ķ��������������ö��Ÿ���\n");
	scanf("%d,%d", &G.vexnum, &G.arcnum);
	
	//�Ӽ���������������Թ������������ 
	printf("����������������G�Ķ������ƣ��ÿո����\n"); 
	for(int i = 0; i < G.vexnum; ++i) { 
		scanf("%d", &G.vexs[i]);
	}//for
	
	//��ʼ���ڽӾ�����洢��Ԫ��ֵΪINFINITY��INFINITY��ʾ�����㲻�ɴ� 
	for(int i = 0; i < G.vexnum; ++i) { 
	    for(int j = 0; j < G.vexnum; ++j) { 
	    	G.arcs[i][j].adj = INFINITY;
	    }//for 
	}//for
	
	//���뻡�����Ķ����Ȩֵ������ڽӾ���  
	printf("����������������Gÿ�������������������Ƽ�Ȩֵ������һ�鰴�س�\n"); 
	for(int k = 0; k < G.arcnum; ++k){
		
		//���뻡������������v1��v2 
	    scanf("%d", &v1);
        scanf("%d", &v2);
        
        //���뻡�ϵ�Ȩֵ 
        scanf("%d", &w);
        
        //ȷ��v1,v2��G�е�λ��i,j 
	    i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		
		//����Ȩֵ���ڽӾ���Ķ�Ӧ�洢��Ԫ�� 
		G.arcs[i][j].adj = w;
		
		//���ڹ�����������������Ի���Ҫ��<v1,v2>�ĶԳƻ�<v2,v1> 
		//���ɣ��ṹ��ֱ�Ӹ�ֵ�൱�ڽṹ���и��������Ķ�Ӧ���� 
		G.arcs[j][i] = G.arcs[i][j];
	}//for
	
	//�����ɹ� 
	return OK; 
}// CreateUDN

/*
	������CreateUDG
	������MGraph &G ͼ������ 
	����ֵ��״̬�룬�����ɹ�����OK 
	���ã��������飨�ڽӾ��󣩱�ʾ������������ͼG 
*/
Status CreateUDG(MGraph &G){
	
	//�����û��Ӽ�������Ķ��� 
	VertexType v1, v2;
	
	//��ʱ����i���ڱ��涥��v1��ͼG�е����
	//��ʱ����j���ڱ��涥��v2��ͼG�е����  
	int i, j;
	
	//ȷ������ͼ�Ķ������ͱ���������ѭ�����Ʊ߽� 
	printf("��������������ͼG�Ķ��������������ö��Ÿ���\n");
	scanf("%d,%d", &G.vexnum, &G.arcnum);
	
	//������������Ʋ�������������� 
	printf("��������������ͼG�Ķ������ƣ��ÿո����\n"); 
	for(int i = 0; i < G.vexnum; ++i) {
		scanf("%d", &G.vexs[i]);
	}//for
	
	//��ʼ���ڽӾ������д洢��Ԫ��ֵΪ0��0��ʾ������֮�䲻�ɴ� 
	for(int i = 0; i < G.vexnum; ++i) {
	    for(int j = 0; j < G.vexnum; ++j) {
	    	G.arcs[i][j].adj = 0;
		}//for
	}//for 
	
	//���뻡�����Ķ��㣬����ڽӾ���  
	printf("��������������ͼGÿ�������������������ƣ�����һ�鰴�س�\n"); 
	for(int k = 0; k < G.arcnum; ++k){
		
		//���뻡������������v1��v2  
	    scanf("%d", &v1);
        scanf("%d", &v2);
        
        //ȷ��v1,v2��G�е�λ��i��j 
	    i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		
		//����v1->v2��ֵΪ1����ʾv1->v2�ǿɴ�� 
		G.arcs[i][j].adj = 1;
		
		//���ڹ����������ͼ�����Ի���Ҫ��<v1,v2>�ĶԳƻ�<v2,v1>
		G.arcs[j][i] = G.arcs[i][j]; 
	}//for
	
	//�����ɹ� 
	return OK; 
}// CreateUDG

/*
	������CreateDN
	������MGraph &G ͼ������ 
	����ֵ��״̬�룬�����ɹ�����OK 
	���ã��������飨�ڽӾ��󣩱�ʾ��������������G 
*/
Status CreateDN(MGraph &G){
	
	//��ʱ����v1��v2���ڽ��մӼ���������������ֵ 
	VertexType v1, v2;
	
	//��ʱ����w���ڱ����û������Ȩֵ
	//��ʱ����i���ڱ��涥��v1��ͼ�е�λ��
	//��ʱ����j���ڱ��涥��v2��ͼ�е�λ�� 
	int w, i, j;
	
	//ȷ���������Ķ������ͱ���������ѭ�����Ʊ߽� 
	printf("����������������G�Ķ��������������ö��Ÿ���\n");
	scanf("%d,%d", &G.vexnum, &G.arcnum);
	
	//���붥�����ƹ������������
	printf("����������������G�Ķ������ƣ��ÿո����\n"); 
	for(int i = 0; i < G.vexnum; ++i) { 
		scanf("%d", &G.vexs[i]);
	}//for 
	
	//��ʼ���ڽӾ�����洢��Ԫ��ֵΪINFINITY��INFINITY��ʾ�����㲻�ɴ� 
	for(int i = 0; i < G.vexnum; ++i) { 
	    for(int j = 0; j < G.vexnum; ++j) { 
	    	G.arcs[i][j].adj = INFINITY;
		}//for
	}//for
	
	//���뻡�����Ķ����Ȩֵ������ڽӾ��� 
	printf("����������������Gÿ�������������������Ƽ�Ȩֵ������һ�鰴�س�\n"); 
	for(int k = 0; k < G.arcnum; ++k) {
	    
		//���뻡������������v1��v2 
		scanf("%d", &v1);
        scanf("%d", &v2);
        
        //���뻡�ϵ�Ȩֵ 
        scanf("%d", &w);
		
		//ȷ��v1,v2��G�е�λ�� 
	    i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		
		//����Ȩֵ���ڽӾ���Ķ�Ӧ�洢��Ԫ��      
		G.arcs[i][j].adj = w;
	}//for
	
	//�����ɹ� 
	return OK; 
}// CreateDN

/*
	������CreateDG
	������MGraph &G ͼ������ 
	����ֵ��״̬�룬�����ɹ�����OK 
	���ã��������飨�ڽӾ��󣩱�ʾ������������ͼG  
*/
Status CreateDG(MGraph &G){
	
	//��ʱ����v1��v2���ڽ��մӼ���������������ֵ 
	VertexType v1, v2;
	
	//��ʱ����i���ڱ��涥��v1��ͼ�е�λ��
	//��ʱ����j���ڱ��涥��v2��ͼ�е�λ�� 
	int i, j;
	
	//ȷ���������Ķ������ͱ���������ѭ�����Ʊ߽� 
	printf("��������������ͼG�Ķ��������������ö��Ÿ���\n");
	scanf("%d,%d", &G.vexnum, &G.arcnum);
	
	//���붥�����ƹ������������
	printf("��������������ͼG�Ķ������ƣ��ÿո����\n"); 
	for(int i = 0; i < G.vexnum; ++i) { 
		scanf("%d", &G.vexs[i]);
	}//for
	
	//��ʼ���ڽӾ������д洢��Ԫ��ֵΪ0��0��ʾ������֮�䲻�ɴ�  
	for(int i = 0; i < G.vexnum; ++i) {
	    for(int j = 0; j < G.vexnum; ++j) {
	    	G.arcs[i][j].adj=0; 
		}//for
	}//for
	
	//���뻡�����Ķ��㣬����ڽӾ��� 
	printf("��������������ͼGÿ�������������������ƣ�����һ�鰴�س�\n"); 
	for(int k = 0; k < G.arcnum; ++k) { 
	
		//���뻡������������v1��v2 
	    scanf("%d", &v1);
        scanf("%d", &v2);
        
        //ȷ��v1,v2��G�е�λ��i��j 
	    i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		
		//����v1->v2��ֵΪ1����ʾv1->v2�ǿɴ��
		G.arcs[i][j].adj = 1;
	}//for
	
	//�����ɹ� 
	return OK; 
}// CreateDG

/*
	������CreateGraph
	������MGraph &G ͼ������ 
	����ֵ��״̬�룬�����ɹ�����OK 
	���ã��������飨�ڽӾ��󣩱�ʾ��������ͼG
*/
Status CreateGraph(MGraph &G){
	
	//���빹��ͼ������ 
	printf("���������빹���ͼ������:����ͼ����0,����������1,����ͼ����2,����������3):");
	scanf("%d", &G.kind);
	
	//����ͼ�Ĳ�ͬ���͵���ͼ�Ĺ��캯�� 
	switch(G.kind){
		case  DG:  return CreateDG(G);  //��������ͼG
		case  DN:  return CreateDN(G);  //����������G
		case UDG:  return CreateUDG(G); //��������ͼG
		case UDN:  return CreateUDN(G); //����������G
		default :  return ERROR;
	}//switch
}//CreateGraph

/*
	������DestroyGraph
	������MGraph &G ͼ������ 
	����ֵ��״̬�룬�����ɹ�����OK 
	���ã�����ͼG
*/
Status DestroyGraph(MGraph &G) {

	//������ 
	if(G.kind % 2) {
	
		//�����ڽӾ������ж���֮�䲻�ɴ� 
		for(int i = 0; i < G.vexnum; i++) {
			for(int j = 0; j < G.vexnum; j++) {
				G.arcs[i][j].adj = INFINITY;
			}//for 
	    }//for 
	}//if
	else { //����ͼ 
		
		//�����ڽӾ������ж���֮�䲻�ɴ� 
		for(int i = 0; i < G.vexnum; i++) {
			for(int j = 0; j < G.vexnum; j++) {
				G.arcs[i][j].adj = 0;
			}//for 
	    }//for 
	}//else
	
	//���ö�����Ϊ0
	G.vexnum = 0;
	
	//���ñ���Ϊ0
	G.arcnum = 0;
}//DestroyGraph

/*
	������PrintAdjMatrix
	������MGraph G ͼG
	����ֵ��״̬�룬�����ɹ�����OK 
	���ã���ӡĳ��ͼ���ڽӾ��� 
*/
Status PrintAdjMatrix(MGraph G){
	
	//������ϽǶ���Ŀհ� 
	printf("      ");
	
	//����ڽӾ���������꣨ȫ�����㣩 
	for(int i = 0; i < G.vexnum; i++) {
		
		printf(" %3d ", G.vexs[i]); 	
	}//for 
	
	printf("\n"); 
	
	//������ϽǶ���Ŀհ� 
	printf("     +");
	
	//���һ������
	for(int i = 0; i < G.vexnum; i++) {
		printf("-----"); 
	}//for 
	
	printf("\n"); 
	
	//����ڽӾ���������꣨ȫ�����㣩������ 
	for(int i = 0; i < G.vexnum; i++) {
		
		//����ڽӾ�����ߵ�����
		printf(" %3d |", G.vexs[i]);  
		
	    for(int j = 0; j < G.vexnum; j++) {
	        if(G.arcs[i][j].adj == INFINITY) {
			    printf("  �� ");
			}//if 
			else {
			    printf(" %3d ", G.arcs[i][j].adj);
			}//else
		}//for 
	    printf("\n     |\n");
	}//for 
}//PrintAdjMatrix

/*
	������GetVex
	������MGraph G ͼG
	      int v v��G��ĳ����������
	����ֵ������v��ֵ
	���ã��õ����Ϊv�Ķ���ֵ 
*/
VertexType& GetVex(MGraph G, int v) {
	
	//������v�Ƿ�Ϸ���v�Ƿ�Խ�� 
	if(v >= G.vexnum || v < 0) { 
    	exit(ERROR);
    }//if
	
	//�������Ϊv�Ķ���ֵ 
	return G.vexs[v];
}//GetVex

/*
	������PutVex
	������MGraph &G ͼ������ 
	      VertexType v v��G��ĳ������
	      VertexType value �����Ϊv�Ķ����ֵ�޸�Ϊvalue 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERROR 
	���ã��޸����Ϊv�Ķ���ֵ 
*/
Status PutVex(MGraph &G, VertexType v, VertexType value) {
	
	//kΪ����v��ͼG�е����
	int k = LocateVex(G, v);
	
	//���ͼ���Ƿ���ڶ���v
	if(k < 0) { 
    	return ERROR;
    }//if
	
	//������v��ֵ��Ϊvalue 
	G.vexs[k] = value;
	
	//�����ɹ� 
	return OK;
}//PutVex 


/*
	������FirstAdjVex
	������MGraph G ͼG
	      VertexType v ����v 
	����ֵ�����ҵ��ڽӵ㣬�����ڽӵ�Ķ���λ�ã����򷵻�-1 
	���ã��󶥵�v��ͼG�еĵ�һ���ڽӵ�
*/
int FirstAdjVex(MGraph G, VertexType v){
	
	//j��ʾ���ɴ��ͼ�У�0��ʾ���ɴ������INFINITY��ʾ���ɴ� 
	int j = 0;
	
	//v�Ƕ��㣬������ţ���Ҫ��λ 
	//k���Ƕ���v�ڶ��������е���� 
	int k = LocateVex(G, v);
	
	//����������INFINITY��ʾ���ɴ� 
	if(G.kind == DN || G.kind == UDN) {
	   j = INFINITY;
	}//if
	
	//�ڶ���v��Ӧ�ĵ�k�в��ҵ�һ���ڽӵ�����i 
	for(int i = 0; i < G.vexnum; ++i) {
		
		//���ҵ�����v�ĵ�һ���ڽӵ��򷵻�i
		//G.arcs[k][i].adj != j ��ʾ����G.arcs[k][i]�ɴ� 
		if(G.arcs[k][i].adj != j) {
	    	return i;
		}//if 
	}//for
	 
	//��δ�ҵ�����-1 
	return -1;
}//FirstAdjVex

/*
	������NextAdjVex
	������MGraph G ͼG
	      VertexType v ����v 
	����ֵ�����ҵ��ڽӵ㣬�����ڽӵ�Ķ���λ�ã����򷵻�-1 
	���ã��󶥵�v��ͼG��������ڽӵ�w����һ���ڽӵ�
*/
int NextAdjVex(MGraph G, VertexType v, VertexType w){
	
	//j��ʾ���ɴ��ͼ�У�0��ʾ���ɴ������INFINITY��ʾ���ɴ�
	int j = 0;
	
	//k1�Ƕ���v�ڶ��������е�λ�� 
	int k1 = LocateVex(G, v);
	
	//k2�Ƕ���w�ڶ��������е�λ�� 
	int k2 = LocateVex(G, w);
	
	//����������ʹ��INFINITY��ʾ���ɴ� 
	if(G.kind == DN || G.kind == UDN) { 
		j = INFINITY;
	}//if
	
	//��ͼG�в��Ҷ���v����ڶ���w����һ���ڽӵ��λ�� 
	for(int i= k2 + 1; i < G.vexnum; ++i) {
	   
		//���ҵ��򷵻�i 
		if(G.arcs[k1][i].adj != j) {
	    	return i;
		}//if
	}//for
	
	//��δ�ҵ�����-1
	return -1;
}//NextAdjVex

/*
	������InsertVex
	������MGraph &G ͼ������ 
	      VertexType v ����v 
	����ֵ��״̬�룬�����ɹ�����OK 
	���ã���ͼG�������¶���v
*/
Status InsertVex(MGraph &G, VertexType v) {
	
	//j��ʾ���ɴ��ͼ�У�0��ʾ���ɴ������INFINITY��ʾ���ɴ�
	int j = 0;
	
	//����������ʹ��INFINITY��ʾ���ɴ� 
	if(G.kind % 2) { 
    	j = INFINITY;
    }//if
	 
	//�����¶�������
   	G.vexs[G.vexnum] = v;
   
   	//��ʼ���ڽӾ��� 
	for(int i = 0; i <= G.vexnum; i++) {
		
		//��ʼ�������ÿ���洢��ԪΪ���ɴ� 
    	G.arcs[G.vexnum][i].adj = G.arcs[i][G.vexnum].adj = j;
	}//for
	
	//ͼG�Ķ�������1
	G.vexnum++;
	
	//�����ɹ� 
	return OK; 
}//InsertVex

/*
	������DeleteVex
	������MGraph &G ͼ������ 
	      VertexType v ����v 
	����ֵ��״̬�룬�����ɹ�����OK 
	���ã�ɾ��G�ж���v������صĻ�
*/
Status DeleteVex(MGraph &G, VertexType v) {
	
	//m��ʾ���ɴ��ͼ�У�0��ʾ���ɴ������INFINITY��ʾ���ɴ�
	VRType m = 0;
	
	//����������ʹ��INFINITY��ʾ���ɴ� 
	if(G.kind % 2) {
    	m = INFINITY;
	}//if
	
	//kΪ��ɾ������v�����
	int k = LocateVex(G, v);
	
	//���v�Ƿ���ͼG�Ķ���
	if(k < 0) { //v����ͼG�Ķ���
	
		//����ʧ�� 
    	return ERROR;
	}//if
	
	//ɾ���ߵ���Ϣ 
	for(int j = 0; j < G.vexnum; j++) { 
    	
    	//���뻡
		if(G.arcs[j][k].adj != m) {
			
			//ɾ����
			G.arcs[j][k].adj = m; 
			
			//����-1
       		G.arcnum--; 
		}//if
		
		//�г���
		if(G.arcs[k][j].adj != m) {
     		
     		//ɾ����
			G.arcs[k][j].adj = m; 
     		
     		//����-1
			G.arcnum--;
   		}//if 
	}//for 
	
	//���k����Ķ�����������ǰ��
	for(int j = k + 1; j < G.vexnum; j++) {
    	G.vexs[j-1] = G.vexs[j];
	}//for
	
	//�ƶ���ɾ������֮�ҵľ���Ԫ��
	for(int i = 0; i < G.vexnum; i++) {
    	for(int j = k + 1; j < G.vexnum; j++) {
       		G.arcs[i][j - 1] = G.arcs[i][j];
       	}//for
	}//for
	
	//�ƶ���ɾ������֮�µľ���Ԫ��
	for(int i = 0; i < G.vexnum; i++) {
    	for(int j = k + 1; j < G.vexnum; j++) {
    		G.arcs[j - 1][i] = G.arcs[j][i];
    	}//for
	}//for
	
	//ͼ�Ķ�����-1
	G.vexnum--;
	
	//�����ɹ� 
	return OK;
}//DeleteVex

/*
	������InsertArc
	������MGraph &G ͼ������ 
	      VertexType v ����v����β�� 
	      VertexType w ����w����ͷ�� 
	����ֵ��״̬�룬�����ɹ�����OK 
	���ã���G������<v,w>����G������ģ�������Գƻ�<w,v>
*/
Status InsertArc(MGraph &G, VertexType v, VertexType w) {
   
	//��β����v��ͼ�е����v1 
	int v1 = LocateVex(G, v);
	
	//��ͷ����w��ͼ�е����w1 
	int w1 = LocateVex(G, w);
	
	//��鶥��v�Ͷ���w��ͼ���Ƿ���� 
	if(v1 < 0 || w1 < 0) {  //v��w��һ������ͼG�еĶ���
	
		//����ʧ�� 
    	return ERROR;
    }//if 
    
    //���������1
	G.arcnum++;
	
	//�����ͼG����������Ҫ����Ȩֵ 
	//if(G.kind % 2) <=> if(G.kind % 2 != 0)
	if(G.kind % 2) {
    	printf("������˻���ߵ�Ȩֵ: ");
    	scanf("%d", &G.arcs[v1][w1].adj);
	}//if
	else { // ͼ
    	G.arcs[v1][w1].adj = 1;
	}//else 
   
   	//���������ͼ������������Ҫ�öԳƵı� 
	if(G.kind > 1) {
    	G.arcs[w1][v1].adj = G.arcs[v1][w1].adj;
	}//if
	
	//�����ɹ� 
	return OK;
}//InsertArc

/*
	������DeleteArc
	������MGraph &G ͼ������ 
	      VertexType v ����v����β�� 
	      VertexType w ����w����ͷ�� 
	����ֵ��״̬�룬�����ɹ�����OK������ʧ�ܷ���ERROR 
	���ã���G��ɾ����<v,w>����G������ģ���ɾ���Գƻ�<w,v>
*/
Status DeleteArc(MGraph &G, VertexType v, VertexType w) {
   
	//j��ʾ���ɴ��ͼ�У�0��ʾ���ɴ������INFINITY��ʾ���ɴ�
	int j = 0;
   
   	//����������ʹ��INFINITY��ʾ���ɴ� 
	if(G.kind % 2) {
    	j = INFINITY;
	}//if
	
	//��ͷ����v��ͼ�е����v1 
	int v1 = LocateVex(G, v);
	
	//��β����w��ͼ�е����w1 
	int w1 = LocateVex(G, w);
	
	//��鶥��v�Ͷ���w��ͼ���Ƿ���� 
	if(v1 < 0 || w1 < 0) { //v��w��һ������ͼG�еĶ���
    	return ERROR;
    }//if 
    
    //������v�붥��w֮����Ϊ���ɴ� 
	G.arcs[v1][w1].adj = j;
	
	//���������ͼ����������Ҫɾ���Գƻ�<w,v>
	if(G.kind >= 2) {
    	G.arcs[w1][v1].adj = j;
	}//if
	
	//����-1
	G.arcnum--;
	
	//�����ɹ� 
	return OK;
}//DeleteArc
