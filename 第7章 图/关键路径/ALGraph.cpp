/*--------------------ͼ��ADT����----------------------------------

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

//-----------------------------ͼ�Ļ�������------------------------------

/*
	������LocateVex
	������ALGraph G ͼG���ڽӱ�洢�ṹ�� 
	      VertexType u ����u 
	����ֵ����G�д��ڶ���u���򷵻ظö�����ͼ��λ�ã����򷵻�-1
	��ʼ������ͼG���ڣ�u��G�ж�������ͬ����
	���ã���ͼG�в��Ҷ���u��λ�� 
*/
int LocateVex(ALGraph G, VertexType u){
	
	//i����ʱ������ѭ�������� 
	int i;
	
	//��ͼ��ÿ�������������Ա� 
	for(i = 0; i < G.vexnum; ++i) {
		
		//��ͼ���ҵ��˽�� 
		if(G.vertices[i].data == u) {
			
			//���ض�����ͼ�е�λ�� 
			return i;
		}//if 
	}//for
	
	//û����ͼ���ҵ����㣬����-1 
	return -1;
}//LocateVex

/*
	������CreateGraph
	������ALGraph &G ͼ������ 
	����ֵ��״̬�룬�����ɹ�����OK�� 
	���ã������û������빹��ͼ�����֣��� 
*/
Status CreateGraph(ALGraph &G) {
	
	//w��Ȩֵ
	//i��j��kȫ����ʱ������ѭ���� 
	int i, j, k, w;
	
	//���ӱ߻򻡵�2����
	VertexType va, vb;
	
	//����� 
	ElemType e;
	
	//ȷ��ͼ������ 
	printf("������ͼ������(����ͼ����0, ����������1,����ͼ����2,����������3): ");
	scanf("%d", &G.kind);
	
	//ȷ��ͼ�Ķ������ͱ��� 
	printf("������ͼ�Ķ�����,����: ");
	scanf("%d,%d", &G.vexnum, &G.arcnum);
	
	//�Ӽ������붥��ֵ�����춥������ 
	printf("������%d�������ֵ(�ÿո����):\n", G.vexnum);
	for(i = 0; i < G.vexnum; ++i) {
		
		//���붥���ֵ 
		scanf("%d", &G.vertices[i].data);
		getchar(); //�Ե������ַ� 
		
		//��ʼ����ö����йصĳ�������
		G.vertices[i].firstarc = NULL;
	}//for
	
	//����ǹ�����������Ҫ��������Ȩֵ������ǹ���ͼ����Ҫ 
	//ö�ٱ�����{����ͼ = 0,������ = 1,����ͼ = 2,������ = 3} 
	//G.kind % 2 != 0 ��ʾ�����������������ͼ 
	if(G.kind % 2) { //if(G.kind % 2) <=> if(G.kind % 2 != 0)
		printf("������ÿ����(��)�Ļ�β����ͷ��Ȩֵ(�Զ�����Ϊ���):\n");
	}//if 
	else { //����ͼ
		printf("������ÿ����(��)�Ļ�β�ͻ�ͷ(�Զ�����Ϊ���):\n");
	}//else
	 
	//������ػ�����
	for(k = 0; k < G.arcnum; ++k){
		
		//������������������Ҫ����Ȩֵ 
		//if(G.kind % 2) <=> if(G.kind % 2 != 0)
		if(G.kind % 2) {
			scanf("%d,%d,%d", &va, &vb, &w);
		}//if 
		else { //�������ͼ������Ҫ����Ȩֵ 
			scanf("%d,%d", &va, &vb);
		}//else
		
		//�ȴ���ͷ�ͻ�β���֣�����ͼ��������Ҫִ�еĹ��������� 
		
		//��β
		i = LocateVex(G, va);
		
		//��ͷ
		j = LocateVex(G, vb);
		
		//���������e��ֵ��ͼû��Ȩֵ������Ȩֵ���������н��ĳ�ʼ��
		//���õ�e���������ռ�ÿ���µ�ѭ������Ҫ����ΪNULL�����㣩�� 
		//����������������������һС�鱣��Ȩֵ�Ŀռ䣬���򱣳�NULL�� 
		e.info = NULL;
		
		//��ͷ
		e.adjvex = j;
	
		//������������������Ҫ��Ȩֵ��ŵ����������Ϣinfo��
		//ע�⣺��ʱinfo�Ŀռ仹û�����뵽 
		//if(G.kind % 2) <=> if(G.kind % 2 != 0)
		if(G.kind % 2) {
			
			//������Ȩֵ�Ŀռ�
			e.info = (InfoType *)malloc(sizeof(int));
			
			//�����������Ϣ������Ȩֵ�Ŀռ��� 
			*(e.info) = w;
		}//if
		
		//���������ڵ�i������ı�ͷ
		//����������õ��ǵ�����Ĳ����㷨����G.vertices[i].firstarc������ͷ���
		//����ͷ�巨���� 
		ListInsert(G.vertices[i].firstarc, 1, e);
		
		//��������������ͼ����������������2�����㣬�����ڵ�j��Ԫ��(�뻡)�ı�ͷ
		//�ڶ����������һ����������Խ��ߣ����������£��Գ� 
		if(G.kind >= 2) {
			
			//���Խ��߶Գ�λ�õĽ��Ȩֵ���䣬����e.info���䣬�����ٸ�ֵ
			//Ҳ����˵���ڽӾ����������Խ��߶ԳƵ�����������ڽӱ��й���һ��Ȩֵ�ռ� 
			e.adjvex = i;
			
			//���ڶԽ��߶Գ�λ�ö���ı�ͷ��Ҳ���ǵ�j��λ�á� 
			ListInsert(G.vertices[j].firstarc, 1, e);
		}//if 
	}//for
	
	//�����ɹ� 
	return OK;
}//CreateGraph

/*
	������DestroyGraph
	������ALGraph &G ͼ������ 
	����ֵ��״̬�룬�����ɹ�����OK�� 
	���ã���ͼG���ڣ�����ͼG 
*/
Status DestroyGraph(ALGraph &G) {
	
	//i����ʱ������ѭ�������� 
	int i;
	
	//���ش��ڽӱ���ɾ���Ļ���㣬�������������Ҫ�����ͷŴ洢Ȩֵ�Ĵ洢��Ԫ�Ŀռ� 
	ElemType e;
	
	//�������ж���
	for(i = 0; i < G.vexnum; ++i) { 
		
		//��������ٵ�����������Ҫ��������Ȩֵ 
		//if(G.kind % 2) <=> if(G.kind % 2 != 0)
		if(G.kind % 2) {
			
			//�����Ӧ�Ļ����������
	   		while(G.vertices[i].firstarc) {
	   			
	   			//ɾ������ĵ�1������㣬����ֵ����e
	 			ListDelete(G.vertices[i].firstarc, 1, e);
	 			
	 			//�ͷű���Ȩֵ���ڴ�ռ� 
	 			//��Ҫע�⣺�ڹ�����ʱΪ�˽�Լ�ռ䣬�������Խ��߶ԳƵ�������� 
				//��Ȩֵ��Ϣָ��e.infoָ����ͬһ���ڴ����������ͷ��ڴ�ռ��ʱ��
				//Ҫע���Ѿ��ͷŹ����ڴ�ռ䲻�����ٴ��ͷš��������ͷ��ڴ�ռ�֮ǰ
				//��Ҫ�����жϡ�����C����û���ṩ�ж��ڴ��Ƿ��ͷŵĺ�����
				//�����Ҫ�����Լ�д�ж��������۲��ڽӾ����ѷ��֣�
				//���Խ����Ϸ��Ľ��������Խ��߶ԳƵ��·��Ľ��֮�����һ�����ɣ�
				//�Ϸ��������±� > �Գ�λ�ã��·����������±�
				//�����ͷŻ����ʱ�ǰ��ն���˳���С������еģ�
				//���±��Ļ���㣨�����ǣ��ܱ����±�С�Ļ���㣨�����ǣ����ͷš� 
				//�����жϽ���Ƿ��ͷŵı�־���ǣ�������� > i
	 			if(e.adjvex > i) { 
	   				free(e.info);
	   			}//if
	   		}//while
	   	}//if 
	 	else {//�������ٵ���ͼ��ֻ���ٻ���������� 
	 		
	 		//���õ��������ٺ������ٻ�����
	   		DestoryList(G.vertices[i].firstarc);
	  	}//else
	}//for
	 
	//���ö�����Ϊ0
	G.vexnum = 0;
	
	//���ñ߻���Ϊ0
	G.arcnum = 0;
	
	//�����ɹ�
	return OK; 
}//DestroyGraph 

/*
	������GetVex
	������ALGraph G ͼG 
	      int v ĳ����������v 
	����ֵ������v��ֵ 
	���ã���ͼG���ڣ�v��G��ĳ���������ţ����ض���v��ֵ 
*/
VertexType& GetVex(ALGraph G, int v) {
	
	//��鶥�����v�Ƿ�Խ�� 
	if(v >= G.vexnum || v < 0) { 
	
		//��Խ�������ֱ���˳����� 
		exit(ERROR);
	}//if
	
	//���ض���v��ֵ 
	return G.vertices[v].data;
}//GetVex

/*
	������PutVex
	������ALGraph &G ͼG������ 
	      VertexType v ���޸Ķ���v 
	      VertexType value ������v��ֵ�޸�Ϊvalue
	����ֵ��״̬�룬�����ɹ�����OK��ʧ�ܷ���ERROR 
	���ã���ͼG���ڣ�v��G��ĳ�����㣬��v����ֵvalue 
*/
Status PutVex(ALGraph &G, VertexType v, VertexType value) {

	//i��¼����ͼ���ڽӱ��ж�λ��������õ���v�ڶ��������е��±� 
	int i;
	
	//ͨ����λ�����õ��±� 
	i = LocateVex(G, v);
	
	//�õ��±�֮�����ж��±��Ƿ�Ϸ�����ͼ���Ƿ���ڶ���v
	//��ͼ�в����ڶ���v����λ����LocateVex����-1 
	if(i > -1) { //ͼ�д��ڶ���v
	
		//�޸Ķ���v��ֵΪvalue 
    	G.vertices[i].data = value;
    	
    	//�����ɹ� 
    	return OK;
	}//if
	
	//����ʧ�� 
	return ERROR;
}//PutVex

/*
	������FirstAdjVex
	������ALGraph G ͼG
	      VertexType v ����v 
	����ֵ����v��ͼG�����ڽӶ��㣬����v�ĵ�һ���ڽӶ������ţ����򷵻�-1�� 
	���ã���ͼG���ڣ�v��G��ĳ������,����v�ĵ�һ���ڽӶ������š�
	      ��������G��û���ڽӶ��㣬�򷵻�-1
*/
int FirstAdjVex(ALGraph G, VertexType v) {
   
	//����ָ��p,ָ�򶥵�v�������еĶ��� 
	ArcNode *p;
   
	//iΪ����v��ͼG�е����
	int i;
   
	//ͨ����λ�����ҳ�����v����� 
	i = LocateVex(G, v);
   
	//���ͼ���Ƿ���ڶ���v 
	if(i == -1) {
		return -1; 
	}//if
   
	//����ָ��pָ�����iָʾ�Ķ���v 
	p = G.vertices[i].firstarc;
   
	//���v���ڽӶ��� 
	if(p) { //if(p) <=> if(p != NULL) 
		
		//���ض���v��һ���ڽӶ������� 
		return p->data.adjvex;
	}//if
	else { //����vû���ڽӶ��� 
	
		//����-1 
		return -1;
	}//else
}//FirstAdjVex

/*
	������equalvex
	������ElemType a ����A 
	      ElemType b ����B 
	����ֵ��״̬�룬�����ɹ�����OK��ʧ�ܷ���ERROR 
	���ã��ж�����������Ƿ�����ͬ���ڽӵ㡣
	      DeleteArc()��DeleteVex()��NextAdjVex()Ҫ���õĺ���
*/
Status equalvex(ElemType a, ElemType b) {
	
	//�������A�Ͷ���B���ڽӶ�����ͬ 
   	if(a.adjvex == b.adjvex) {
    	
    	//����1 
		return OK;
	}//if
   	else {
   		
   		//����0 
   		return ERROR;
   	}//else 
}//equalvex

/*
	������NextAdjVex
	������ALGraph G ͼG 
	      VertexType v v��G��ĳ������
		  VertexType w w��v���ڽӶ��� 
	����ֵ������v��(�����w��)��һ���ڽӶ������š�
	        ��w��v�����һ���ڽӵ㣬�򷵻�-1
	���ã��õ�����v����ڶ���w����һ���ڽӶ������š� 
*/
int NextAdjVex(ALGraph G, VertexType v, VertexType w) {
	
	//p�ǹ���ָ�� 
	//p1��Point()����������ָ��
	LinkList p, p1;
	
	//e�����˻�������Ϣ 
	ElemType e;
	
	//�ҳ�����v��ͼG�е����v1
	int v1 = LocateVex(G, v); 
	
	//�ҳ�����w��ͼG�е���ţ���e.adjvex���� 
   	e.adjvex = LocateVex(G, w);
	
	//pָ�򶥵�v���������ڽӶ���Ϊw�Ľ��
	p = Point(G.vertices[v1].firstarc, e, equalvex, p1);
	
	//û�ҵ�w��w�����һ���ڽӵ�
	if(!p || !p->next) { 
    	return -1;
    }//if 
	else { //�ҳ����붥��v�ڽӵĶ���w 
		
		//����v�������w����һ���ڽӶ�������
    	return p->next->data.adjvex;
	}//else 
}//NextAdjVex

/*
	������InsertVex
	������ALGraph &G ͼG������ 
	      VertexType v ������Ķ���v 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERROR 
	���ã���ͼG�������¶���v�����������붥����صĻ��� 
*/
Status InsertVex(ALGraph &G, VertexType v) { 

	//�����µĶ��㣬���������� 
	G.vertices[G.vexnum].data = v;
	
	//���ڻ�û������ڽӻ�����Ϣ������firstarc��ֵΪ�� 
	G.vertices[G.vexnum].firstarc = NULL;
	
	//ͼG�Ķ�������1
	G.vexnum++;
	
	//�����ɹ� 
	return OK;
}//InsertVex

/*
	������DeleteVex
	������ALGraph &G ͼG������ 
	      VertexType v ��ɾ���Ķ���v 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERROR 
	���ã�ɾ��G�ж���v������صĻ�
*/
Status DeleteVex(ALGraph &G, VertexType v) {
   
   	//i����ʱ�������洢����vΪ���ȵĻ������
	//j����ʱ���������涥��v����� 
	int i, j, k;
   
	//��ʱ�������������ò����Զ���vΪ�ڽӶ���Ļ��������� 
	ElemType e;
   
	//����ָ��p��ָ���ҵ����Զ���vΪ�ڽӶ���Ļ���� 
	//����ָ��p1ָ��p��ǰ�� 
	LinkList p, p1;
   
	//j�Ƕ���v�����
	j = LocateVex(G, v);
   
	//�����ͼG���Ƿ��ҵ�����v 
	if(j < 0) { 
		return ERROR;
	}//if
	
	//i�洢����vΪ���ȵĻ��������Ҳ���ǻ������ȣ� 
	i = ListLength(G.vertices[j].firstarc);
	
	//�߻���-i
	G.arcnum -= i;
	
	//���ͼG����������Ҫ�������ٱ���Ȩֵ���ڴ�ռ� 
	if(G.kind % 2) { 
		
		//��Ӧ�Ļ����������
    	while(G.vertices[j].firstarc) {
    		
    		//ɾ������ĵ�1����㣬����ֵ����e
			ListDelete(G.vertices[j].firstarc, 1, e);
			
			//���ǵ���������Ȩֵ�ռ乲�����⣬����Ҫ���ж�
			//Ȩֵ�ռ��Ƿ��Ѿ����ͷ���ִ�пռ��ͷŲ��� 
			if(e.info != NULL) {
				//�ͷ�e.infoָʾ�Ķ�̬���ɵ�Ȩֵ�ռ�
    			free(e.info);
    			e.info == NULL;  //ָ���ÿ� 
    		}//if
    	}//while
	}//if
	else { //�����ͼ
		
		//ֻ��Ҫ���ٻ��������Ϳ����ˣ����ÿ���Ȩֵ���� 
    	DestoryList(G.vertices[j].firstarc);
    }//else 
   		
   	//��������1
	G.vexnum--;
		
	//���涥�������˳��洢�ṹ������ɾ������v֮�󣬺���Ķ�����Ҫǰ��
	for(i = j; i < G.vexnum; i++) { 
    	G.vertices[i] = G.vertices[i + 1];
    }//for 
    
    //֮ǰ�Ĳ���ֻ��ɾ���˶���v�������Ļ��������кܶ��ƺ���û������
	//1.֮ǰ��ɾ������ֻ�����˳��ȣ�û������ȡ����ǲ�����Ҫɾ����vָ��
	//  �����������Ϣ������Ҫɾ����������ָ�򶥵�v�Ļ���
	//2.�������v���Ƕ��������е����һ�����㣬������ɾ������v�󣬶���v
	//  ����Ķ�����Ҫ��ǰ�Ʋ�������ʱ���涥���ڶ��������е�λ��ͻ�ı�
	//  ��������涥����صĻ�����д洢���ڽӶ����λ��δ��֮���£�
	//  �������ǻ���Ҫ����Щ�ڽӶ���Ļ�����е��ڽӶ����λ��ȫ������һ�顣
	//  ��֤ɾ��������洢��ͼ���ڽ���Ϣ����ȷ�ԡ�
	//3.�������������Ҫ����Ȩֵ�洢�ռ���ͷ����⡣ 
    
    //ɾ����vΪ��ȵĻ�����ұ�Ҫʱ�޸ı���Ķ���λ��ֵ
	for(i = 0; i < G.vexnum; i++) {
    	
    	//j�����˶���v����ţ�������Ҫ����e�ҳ�������v�ڽӵĶ��� 
		e.adjvex = j;
    	
    	//pָ����G.vertices[i].firstarcָʾ�Ļ���������vΪ�ڽӵ�Ļ����
		//p1ָ��p��ǰ������pָ����Ԫ��㣬��p1ΪNULL 
    	p = Point(G.vertices[i].firstarc, e, equalvex, p1);
     
     	//����i���ڽӱ�����vΪ��ȵĽ��
		if(p) { //if(p) <=> if(p != NULL) 
	 		
	 		//p��ָ����Ԫ��� 
    		if(p1) { //if(p1) <=> if(p1 != NULL)
    			
    			//��������ɾ��p��ָ���
         		p1->next = p->next;
         	}//if
       		else { // pָ����Ԫ���
       			
       			//ͷָ��ָ����һ���
         		G.vertices[i].firstarc = p->next;
        	}//else
        	
        	//����ͼ���������� 
       		if(G.kind < 2) {
       			
       			//�߻���-1
         		G.arcnum--;
         		
         		//������ֱ���ͷ�Ȩֵ�ڴ�ռ���У����ÿ��ǶԳ�λ�õ����� 
				if(G.kind == DN) { 
					//�ͷŶ�̬���ɵ�Ȩֵ�ռ�
           			free(p->data.info);
           		}//if
			}//if
			
			//�ͷ�vΪ��ȵĽ��
			free(p);
       	}//if
       	
       	//������ڽ��ǰ����ɺ����㻡���ڽ���Ϣ����ȷ������ 
	    //����adjvex��>j�Ľ�㣬�����-1
	    for(k = j + 1; k <= G.vexnum; k++) {
	    	
	    	//���Զ���v���涥��Ϊ�ڽӶ���Ķ�����ͼ�е����
			//������e.adjvex�� 
			e.adjvex = k;
			
			//ʹpָ���Զ���vΪ��ȵĻ����
			//p1ָ��p��ǰ������pָ��ͷ���,p1=NULL 
	    	p = Point(G.vertices[i].firstarc, e, equalvex, p1);
	    	
	    	//�ж��Ƿ��ҵ������Ļ���� 
	    	if(p) { //if(p) <=> if(p != NULL)
	    		
	    		//���ڶ���v��ɾ�����v����Ķ���ǰ�ơ����Դ洢�ڻ�����е�
				//���Ӧ�ú�ǰ��֮��Ķ�����ű���һ�£������-1
	    		p->data.adjvex--;
	    	}//if
	    }//for
   }//for
   
   //�����ɹ� 
   return OK;
}//DeleteVex 

/*
	������InsertArc
	������ALGraph &G ͼG������ 
	      VertexType v ͼ�еĶ���w ����β�� 
	      VertexType w ͼ�еĶ���v ����ͷ�� 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERROR 
	���ã���G������<v,w>����G������ģ�������Գƻ�<w,v>
*/
Status InsertArc(ALGraph &G, VertexType v, VertexType w) {
	
	//��ʱ�������洢�˻�������Ϣ 
	ElemType e;

	//i�Ƕ���v��ͼG�е���� 
	int i = LocateVex(G, v);
	
	//j�Ƕ���w��ͼG�е���� 
	int j = LocateVex(G, w);
	
	//��鶥��v��w�Ƿ���ͼG�д��ڣ�������������ֹ��������ִ�� 
	if(i < 0 || j < 0) { 
		return ERROR;
	}//if
	
	//����һ����֮��ͼG�Ļ���ߵ���Ŀ��1
	//ע�⣺������������֮������ͷ���Ļ���һ������Ҫ�ظ���� 
	G.arcnum++;
	
	//�ڶ���v�Ļ������в����ڽӵ�w����Ϣ 
	e.adjvex = j;
	
	//ͼû��Ȩֵ�����Խ�Ȩֵָ��e.info�ĳ�ʼֵ����ΪNULL 
	e.info = NULL;
	
	//����������в��뻡������Ҫ���û���Ȩֵ 
	if(G.kind % 2) { //if(G.kind % 2) <=> if(G.kind % 2 != 0)
	 	
	 	//��̬������Ȩֵ�Ŀռ� 
    	e.info = (InfoType *)malloc(sizeof(int));
    	
    	//�Ӽ�������Ȩֵ����Ϣ 
		printf("�����뻡(��)%d��%d��Ȩֵ: ", v, w);
    	scanf("%d", &e.info);
	}//if
	
	//��e���ڻ�βv�Ļ������ͷ
	ListInsert(G.vertices[i].firstarc, 1, e); 
	
	//������ͼ���������в��뻡����Ҫ���뷴�����һ���� 
	if(G.kind >= 2) {
		
		//����ͼû��Ȩֵ����������e.info����NULL 
		//������������������һ��Ȩֵ�洢��Ԫ��e.info����
    	e.adjvex = i;
    	
    	//��e���ڶ���w������ı�ͷ
    	ListInsert(G.vertices[j].firstarc, 1, e);
    	
    	//ע�⣺������������֮������ͷ���Ļ���һ������Ҫ�ظ���� 
	}//if
   	
   	//�����ɹ� 
	return OK;
}//InsertArc

/*
	������DeleteArc
	������ALGraph &G ͼG������ 
	      VertexType v ͼ�еĶ���w ����β�� 
	      VertexType w ͼ�еĶ���v ����ͷ�� 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERROR 
	���ã���G��ɾ����<v,w>����G������ģ���ɾ���Գƻ�<w,v>
*/
Status DeleteArc(ALGraph &G, VertexType v, VertexType w) {
	
	//k��¼��ɾ�������Ľ�� 
	Status k;
	
	//��ʱ����e�洢�˲����ڽӵ�ıȽ����� 
	ElemType e;
	
	//i�Ƕ���v(��β)��ͼG�е����
	int i = LocateVex(G, v);
	
	//j�Ƕ���w(��ͷ)��ͼG�е����
	int j = LocateVex(G, w);
	
	//���i��j�Ƿ�Ϸ� 
	if(i < 0 || j < 0 || i == j) { 
    	return ERROR;
    }//if
    
    //ɾ��<v,w>������ 
	
	//�����ڶ���v�Ļ������в���Ļ������ڽӵ�����Ϊj 
	e.adjvex = j;
	
	//�Ӷ���v�Ļ�������ɾ���ڽӶ���w�Ļ���� 
	k = DeleteElem(G.vertices[i].firstarc, e, equalvex);
	
	//ɾ����<v,w>�ɹ�
	if(k) { //if(k) <=> if(k != ERROR) 
    	
    	//ͼ�л��������1
		G.arcnum--;
    	
    	//�������������Ҫ�ͷ�Ȩֵ�洢��Ԫ�Ŀռ� 
		if(G.kind % 2) {
    		free(e.info);
    	}//if
    	
    	//�����������������ͼ����Ҫɾ���Գƻ�<w,v>
    	if(G.kind >= 2) {
    		
    		//����w���ڽӵ�Ϊv 
    		e.adjvex = i;
    		
    		//ɾ��w��v�Ļ� 
    		DeleteElem(G.vertices[j].firstarc, e, equalvex);
    	}//if
    	
    	//�����ɹ� 
		return OK;
	}//if
	else { // û�ҵ���ɾ���Ļ�
    	return ERROR;
	}//else
}//DeleteArc

/*
	������Display
	������ALGraph &G ͼG������ 
	      VertexType v ͼ�еĶ���w ����β�� 
	      VertexType w ͼ�еĶ���v ����ͷ�� 
	����ֵ��״̬�룬�����ɹ�����OK�����򷵻�ERROR 
	���ã����ڽӾ�����ʽ����ڽӱ� 
*/
void Display(ALGraph G) {
	
	//����ָ��p 
	ArcNode *p;
   
	//��ӡͼ������ 
	switch(G.kind) {
    	case DG: printf("��ͼΪ����ͼ!\n");
				 break;
    	case DN: printf("��ͼΪ������!\n");
				 break;
    	case UDG:printf("��ͼΪ����ͼ!\n");
	    		 break;
    	case UDN:printf("��ͼΪ������!\n");
	}//switch
	 
    //��ӡͼ���ܶ��������ܱ����Լ�ÿ���� 
	printf("\nͼ�й���%d�����㣬%d����(��)�����Ƿֱ��ǣ�\n", G.vexnum, G.arcnum);
	printf("+----+-----------------------------------------------\n");
	printf("|����|   �ڽӶ���(��Ȩֵ)  \n");
	printf("+----+-----------------------------------------------\n");
   	for(int i = 0; i < G.vexnum; i++){
    	
    	printf("| %2d |", G.vertices[i].data);
    	
    	//pָ��ĳ�����㻡�������Ԫ��� 
		p = G.vertices[i].firstarc;
    	
    	//�������������� 
		while(p) { //while(p) <=> while(p != NULL) 
        		
    		//��ӡ��ͷ�ͻ�β����Ϣ 
			printf(" ��%d ", G.vertices[p->data.adjvex].data);
     		
     		//���ͼG����������Ҫ��ӡ��Ȩֵ 
			if(G.kind % 2) {
       			printf(",Ȩֵ:%d ", *(p->data.info));
       		}//if 
			
			//pָ��������һ����� 
			p = p->nextarc;
		}//while
		
		//�����һ������֮����
		printf("\n+----+-----------------------------------------------\n");
	}//for
	
	//������У�ʹ������� 
	printf("\n");
}//Display
