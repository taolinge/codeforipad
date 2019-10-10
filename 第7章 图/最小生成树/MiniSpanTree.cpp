//-------------- ��С������ ----------------------------

//-------------------��������Ķ���------------------------------- 
struct Record{
	VertexType adjvex;   //���� 
	VRType     lowcost;  //��ʹ��� 
}closedge[MAX_VERTEX_NUM];

/*
	������printColsedge
	������Record closedge[] ������С�������ĸ�������closedge 
	      int n ������ 
	����ֵ���� 
	���ã���ӡclosedge���� 
*/
void printColsedge(Record closedge[], MGraph G) {
	
	//��ӡiһ�� 
	
	printf("+----------+");
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("-----+");
	}//for 
	
	printf("\n"); 
	
	printf("|     i    |"); 
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("  %2d |", i);
	}//for 
	
	printf("\n"); 
	
	printf("+----------+");
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("-----+");
	}//for 
	
	printf("\n"); 
	
	//����ֵ 
	printf("|   ����   |"); 
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("  %2d |", G.vexs[i]);
	}//for 
	
	printf("\n"); 
	
	printf("+----------+");
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("-----+");
	}//for 
	
	printf("\n"); 
	
	//��ӡadjvexһ�� 
	
	printf("|  adjvex  |"); 
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf(" %3d |", closedge[i].adjvex);
	}//for 
	
	printf("\n"); 
	
	printf("+----------+");
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("-----+");
	}//for 
	
	printf("\n"); 
	
	//��ӡlowcostһ�� 
	
	printf("|  lowcost |"); 
	
	for(int i = 0; i < G.vexnum; i++) {
		
		if(closedge[i].lowcost != INFINITY) {
			printf(" %3d |", closedge[i].lowcost);
		}//if
		else {
			printf("  �� |"); 
		}//else 
		
	}//for 
	
	printf("\n"); 
	
	printf("+----------+");
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("-----+");
	}//for 
	
	printf("\n"); 
		
}//printColsedge

/*
	������minimum
	������Record closedge[] ������С�������ĸ�������closedge 
	����ֵ��ѡ���������� 
	���ã���closedge������ѡ��������������С����������һ���� 
*/
int minimum(Record closedge[]){
	
	//min�Ǵ�closedge������ѡ������С���۱ߵ���һ��������ͼ�е�λ��
	//reserve�Ǹ�������Ƚϵ���С���ۣ���ʼֵΪ65535��
	//ÿһ�η��ִ��۱�����С�ı���reserve�ᱻ����Ϊ�µ���С���� 
	int reserve = 65535, min = 0;
	
	for(int i = 1; i < MAX_VERTEX_NUM; i++) {
		
		//û�з��ʹ����Ǵ���·�����Ҵ��۸�С���ȼ�¼��С���۵�reserve��С�� 
		if(closedge[i].lowcost < reserve && closedge[i].lowcost > 0){
			
			printf("->���ֱ�reserve = %d��С��Ȩֵ��closedge[%d].lowcost = %d ��\n",
						reserve, i, closedge[i].lowcost);
			
			//reserve����Ϊ�µ���С���� 
			reserve = closedge[i].lowcost;
			
			//min����Ϊ��С���۱ߵ���һ������ͼ�е�λ�� 
			min = i;
		}//if
	}//for
	 
	return min;
}//minimum

/* ������ķ�㷨����С�������� 
	������MiniSpanTree_PRIM
	������MGraph G ͼG 
	����ֵ���� 
	���ã�������ķ�㷨�ӵ�u���������������G����С������T�����T�ĸ�����
	      ��¼�Ӷ��㼯U��V-U�Ĵ�����С�ıߵĸ������鶨��
*/
void MiniSpanTree_PRIM(MGraph G, VertexType u){
	
	//k�ǳ�������u��ͼ�е���� 
	int k = LocateVex(G, u);
	
	//���������ʼ��
	for(int j = 0; j < G.vexnum; ++j) {  
	    
	    //jָʾ�Ķ��㲻�ǳ������� 
		if(j != k){
	    	//{adjvex, lowcost}
	    	//�����ڽӵ�Ϊ��ʼ����u 
	    	closedge[j].adjvex = u;
	    	
	    	//����closedge�����ʼ��С���ۣ���ʵ����
			//ֱ�ӿ�����G.arcs��ά����ĵ�k�� 
	    	closedge[j].lowcost = G.arcs[k][j].adj;
	    }//if
	}//for
	
	//���ó�����u����С����Ϊ0����ʱU={u}  
	closedge[k].lowcost = 0;
	
	printf("\n->��С�������Ӷ���%d��ʼ�����Ըö����ʱ�ѱ�������С���������㼯�ϣ�\n\n", G.vexs[k]);
	
	//�Ӷ���u��ʼ������С������ 
	for(int i = 1; i < G.vexnum; ++i) {
		
		printf("\n->���ǵ�%d��ѭ����\n" , i);
		
		printf("->����closedge����֮ǰ��closedge�����ֵ(adjvex�Ƕ�����ţ����Ƕ������ƣ�lowcost = 0��ʾ�ö����ѱ�������С�������Ķ��㼯��)��\n");
	
		//��ӡclosedge���� 
		printColsedge(closedge, G); 
		
		printf("->��ʼ����С����������һ���㣺\n"); 
		
		//�����С����������һ����㣺��k����
		//��ʱclosedge[k].lowcost= MIN{ closedge[vi].lowcost 
		//  	| closedge[vi].lowcost > 0, vi ��V-U} 
		k = minimum(closedge);
		
		printf("->�����С����������һ����Ϊ��%d����һ�������k = %d, ��С����Ϊ��%d\n", G.vexs[k], k, closedge[k].lowcost);
		
		//����������ı߼���Ȩֵ
		printf("\n->�õ���С��������һ���±ߣ� %2d <--- %2d ---> %2d \n\n", closedge[k].adjvex, 
			closedge[k].lowcost, G.vexs[k]);
		
		//��k���㲢��U��
		closedge[k].lowcost = 0;
		
		//����k���ڽӶ����д��۸�С�ı߶�Ӧ���ڽӶ��� 
		//���¶��㲢��U������ѡ����С��
		//ѡ��һ������k֮����Ҫ����closedge��������С����Ϣ
		for(int j = 1; j < G.vexnum; ++j) { 
			
			//���ִ��۸�С�ı߾͸���closedge����
			//��û�з����򱣳�ԭֵ���� 
		    if(G.arcs[k][j].adj < closedge[j].lowcost){
		    	
		    	printf("��%d�������ڽӶ����з�����G.arcs[%d][%d].adj = %d �� closedge[%d].lowcost = %d ��С������closedge���飡\n",
						G.vexs[k], k, j, G.arcs[k][j].adj, j, closedge[j].lowcost); 
		    	
		    	//����closedge������ڽӵ���Ϣadjvex 
			    closedge[j].adjvex = G.vexs[k];
			    
			    //����closedge�������С����Ϣlowcost 
				closedge[j].lowcost = G.arcs[k][j].adj; 
		    }//if
		}//for 
		
		printf("\n->����closedge����֮��closedge�����ֵ(adjvex�Ƕ�����ţ����Ƕ������ƣ�lowcost = 0��ʾ�ö����ѱ�������С�������Ķ��㼯��)��\n");
	
		//��ӡclosedge���� 
		printColsedge(closedge, G); 
		
		system("pause");
	}//for 	  
}//MiniSpanTree_PRIM 


/*
	������printSet
	������int set[] ���涥����������״̬������set 
	      MGraph G ͼG 
	����ֵ���� 
	���ã���ӡset���� 
*/
void printSet(int set[], MGraph G) {
	
	//��ӡiһ�� 
	
	printf("+----------+");
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("-----+");
	}//for 
	
	printf("\n"); 
	
	printf("|     i    |"); 
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("  %2d |", i);
	}//for 
	
	printf("\n"); 
	
	printf("+----------+");
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("-----+");
	}//for 
	
	printf("\n"); 
	
	//����ֵ 
	printf("|   ����   |"); 
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("  %2d |", G.vexs[i]);
	}//for 
	
	printf("\n"); 
	
	printf("+----------+");
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("-----+");
	}//for 
	
	printf("\n"); 
	
	//��ӡsetһ�� 
	
	printf("|    set   |"); 
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf(" %3d |", set[i]);
	}//for 
	
	printf("\n"); 
	
	printf("+----------+");
	
	for(int i = 0; i < G.vexnum; i++) {
		
		printf("-----+");
	}//for 
	
	printf("\n"); 
		
}//printSet

/* ����³˹�����㷨����С�������� 
	������MiniSpanTree_kruskal
	������MGraph G ͼG 
	����ֵ���� 
	���ã���³˹�����㷨����С������ 
*/
void MiniSpanTree_kruskal(MGraph G) {
	
	int set[MAX_VERTEX_NUM];
	int k = 0, a = 0, b = 0, setb, min = G.arcs[a][b].adj;
	
	//set[]��̬��������ֱ����ڸ�������
	for(int i = 0; i < G.vexnum; i++) {
    	set[i] = i; 
	}//for
	
	printf("->set�����ʼ״̬��������ֱ����ڸ������ϣ���\n");
	printSet(set, G);
	 
	printf("��С�����������ĸ����߼�ȨֵΪ:\n");
	//��С�������ı���Ӧ����n-1���ߣ�����nΪ������ 
	while(k < G.vexnum-1) {
		
		printf("\n->���ǵ�%d��ѭ����Ѱ�Ҹ�СȨֵ�ıߣ�\n", k + 1);
		
		//Ѱ����СȨֵ�ı�
    	for(int i = 0; i < G.vexnum; ++i) { 
    		
    		//��������ֻ�������ǲ���
    		for(int j = i + 1; j < G.vexnum; ++j) {
				
				//���ֱ�min��С��Ȩֵ 
				if(G.arcs[i][j].adj < min) {
					
					printf("->���ֱ�min = %d ��С��Ȩֵ��%d���޸�minΪ��ֵ��\n", min, G.arcs[i][j].adj);
					
					//��СȨֵ
					min = G.arcs[i][j].adj; 
					
					//�ߵ�һ������
					a = i;
					
					//�ߵ���һ������
					b = j;
				}//if
			}//for
		}//for
		
		//�ߵ������㲻����ͬһ����
    	if(set[a] != set[b]) {
    		
    		//����ñ�
			printf("->�ҵ�һ����С���������±ߣ�%d <-- %d --> %d\n", G.vexs[a], G.arcs[a][b].adj, G.vexs[b]);
    	}//if 
    	
    	//����minΪ����ֵ 
		min = G.arcs[a][b].adj = INFINITY;
		
		//�ߵ������㲻����ͬһ����
    	if(set[a] != set[b]) {
    		
    		//����+1
			k++;
			
			//����setb��ֵ
			setb = set[b];
			
			//������b���ڼ��ϲ��붥��a������
       		for(int i = 0; i < G.vexnum; i++) {
       			
       			//������ֱ��set[i] == set[b]��Ϊ�Ƚ���������Ϊi���ܵ���b�� 
				//һ��set[b]���޸ģ���ôset[b]�����Ԫ�ؽ��޷���ȷ�ϲ�  
        		if(set[i] == setb) {
        			printf("->�ϲ�����%d������%d�ļ����У�ע��set����ı仯��\n", G.vexs[i], G.vexs[a]);
        			set[i] = set[a];
        		}//if
        	}//for 
        	
        	printf("->set�����޸ĺ��ֵ��\n");                                                
			printSet(set, G);
     	}//if 
	}//while
	
	printf("->set���������״̬(������ͨ�����ж���Ӧ�ö���һ��������)��\n");
	printSet(set, G);
}//MiniSpanTree_kruskal
