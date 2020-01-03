#include"stdio.h"
#include"stdlib.h"
#include"windows.h" 
#include <graphics.h>
#include <conio.h>
#define MAXVEX 20                      //��󶥵��� 
#define INFINITY 9999
typedef struct {
	int x;
	int y;
	char name[100];
	char describe[200];
}Location;
typedef struct {
	char name[30];
	char password[30];
}LandMessage;

typedef struct {
	int arc[MAXVEX][MAXVEX];
	Location loc[MAXVEX];
	int vexnum;
	int arcnum;
	int landnum;
	int chargernum;
	LandMessage land[MAXVEX];
	LandMessage charger[MAXVEX];
}AdjMatrix;

int Transform(char a[20]) {
	int i = 0, sum = 0;
	while(i < strlen(a)) {
		sum = sum * 10 + (int)a[i++] - 48;
	}
	return sum;
}

int book[MAXVEX], route[MAXVEX];              //route[0]���·������
int shortest[MAXVEX], short_num, short_num2, turn_minimum[MAXVEX], turn_num;

DFS(AdjMatrix *adj, int current, int end, int begin, int t, int option) {
	int i, j;
	if (current == end) {
		if (route[0] < short_num) {
			short_num = route[0];
			short_num2 = t;
			for (i = 2; i < t; i++) {
				shortest[i] = route[i];
			}
		}
		if (t < turn_num) {
			turn_num = t;
			for (i = 2; i < t; i++) {
				turn_minimum[i] = route[i];
			}
		}
		shortest[1] = begin;
		shortest[t] = end;
		turn_minimum[1] = begin;
		turn_minimum[t] = end;
		
		if(option == 1) {
			printf("%d: ", route[0]);
			printf("%s", adj->loc[begin].name);
			for (i = 2; i < t; i++) {			
				printf("-->");
				printf("%s", adj->loc[route[i]].name);
			}
			printf("-->%s\n\n", adj->loc[end].name);
		}
		return;
	}
	for(i = 1; i <= adj->vexnum; i++) {
		book[current] = 1;
		if(current == begin) {
			t = 1;
		}
		if (i == begin) {
			continue;
		}
		route[t] = current;
		while(((adj->arc[i][current] == 0) || (book[i] == 1)) && (i <= adj->vexnum)) {
			i++;
		}
		if ((i > adj->vexnum) || (adj->arc[i][current] == 0) || (book[i] == 1)){
			return;
		}
		route[0] += adj->arc[i][current];
		DFS(adj, i, end, begin, t + 1, option);
		book[i] = 0;
		route[0] -= adj->arc[i][current];
	}
}



AdjMatrix *ReadFromFile(AdjMatrix *adj) { 
	FILE *fp;
	int i = 0, count = 0, t;
	char a[10], b[10];
	fp = fopen("����.txt", "r");
	fscanf(fp, "%s", b);
	fgetc(fp);
	while(!feof(fp)) {
		fscanf(fp, "%s", adj->loc[++i].name);
		fgetc(fp);
		fscanf(fp, "%s", a);
		adj->loc[i].x = Transform(a);
		fgetc(fp);
		fscanf(fp, "%s", a);
		adj->loc[i].y = Transform(a);
		fgetc(fp);
		fscanf(fp, "%s", adj->loc[i].describe);
		fgetc(fp);
	}
	adj->vexnum = Transform(b);
	fclose(fp);
	return adj;
}

AdjMatrix *ReadLandMessage(AdjMatrix *adj) {
	FILE *fp1, *fp2;
	int i;
	fp1 = fopen("����Ա.txt", "r");
	fscanf(fp1, "%d", &adj->chargernum);
	fgetc(fp1);
	for (i = 1; i <= adj->chargernum; i++) {
		fscanf(fp1, "%s", adj->charger[i].name);
		fgetc(fp1);
		fscanf(fp1, "%s", adj->charger[i].password);
		fgetc(fp1);
	}
	fclose(fp1);
	fp2 = fopen("��ͨ�û�.txt", "r");
	fscanf(fp2, "%d", &adj->landnum);
	fgetc(fp2);
	for (i = 1; i <= adj->landnum; i++) {
		fscanf(fp2, "%s", adj->land[i].name);
		fgetc(fp2);
		fscanf(fp2, "%s", adj->land[i].password);
		fgetc(fp2);
	}
	fclose(fp2);
	return adj;
}


AdjMatrix *ReadFromMatrixFile(AdjMatrix *adj) {
	FILE *fp;
	int i, j;
	fp = fopen("����.txt", "r");
	for(i = 1; i <= adj->vexnum; i++) {
		for(j = 1; j <= adj->vexnum; j++) {
			fscanf(fp, "%d", &adj->arc[i][j]);
			fgetc(fp);
		}
	}
	return adj;
}



PrintMap(AdjMatrix *adj) {               //��ͼ���
	int i;
	for (i = 1; i <= adj->vexnum; i++) {
		printf("%s %d %d %s\n", adj->loc[i].name, adj->loc[i].x, adj->loc[i].y, adj->loc[i].describe);
	}
}

PrintPicture(AdjMatrix *adj) {
	int i, j;
	
/*	for(i = 1; i <= adj->vexnum; i++) {
		for(j = 1; j <= adj->vexnum; j++) {
			printf("%-4d ", adj->arc[i][j]);
		}
		printf("\n");
	}*/
	
	printf("\t                    ͼ���--------------600---------------��ҵ԰��------100----ԡ��\n");
	printf("\t                   /    |                                  /              \n");
	printf("\t                 200    |                                 /400               \n");
	printf("\t                 /      |                                /                \n");
	printf("\t           ���ͺ�-------|------600-------------------ͨԺ                 \n");
	printf("\t             |    \\     |                           /                     \n");
	printf("\t             |     \\____|_____600______________    /200                      \n");
	printf("\t            400          |                     \\ /                       \n");
	printf("\t             |        1000                     ��Ժ                       \n");
	printf("\t             |          |                       |200                       \n");
	printf("\t           ���---------|-------500-----------�Զ���Ժ                    \n");
	printf("\t           /  \\         |                    /                            \n");
	printf("\t          /    \\        |                   /300                             \n");
	printf("\t         /      \\       |                  /                              \n");
	printf("\t        /        \\      |  ___300_________B¥__                              \n");
	printf("\t      700        800    | /             /      \\100                           \n");
	printf("\t      /            \\   ˮ��            /       A¥                        \n");
	printf("\t     /              \\   |   __400_____/       /   \\                        \n");
	printf("\t    /                \\  |  /                 /     \\200                     \n");
	printf("\t   /                  \\ | / ____500_________/       \\                      \n");
	printf("\t  /                    \\|/ /                         \\                     \n");
	printf("\t����¥------300--------����-------------300----------���ʱ���           \n");
}




Description(AdjMatrix *adj) {                                             //λ����Ϣ����
	int i, option;
	for (i = 1; i <= adj->vexnum; i++) {
		if (i % 2 != 0) {
			printf("\n\n");
		}
		printf("%-2d��%-20s", i, adj->loc[i].name);
	}
	printf("\n\n�������λ����ѡ��鿴��ϸ��Ϣ\t option : ");
	while(1) {
		scanf("%d", &option);
		if ((1 <= option) && (option <= 15)) {
			printf("\n\n%s", adj->loc[option].describe);
			break;
		} else {
			printf("���������밴��ȷ��ʽ���루eg��1��\n");
		}
	}
}

StudentEnterance(AdjMatrix *adj) {
	int option, i, begin, end, mark = 0;
	char a[10];
	route[0] = 0;
	while(1) {
		printf("\n\t\t-------------------- ��ѡ�������Ŀ --------------------\n\n");
		printf("\t                          1��У԰һ��ͼ\n");
		printf("\t                          2���ص���Ϣ��ѯ\n");
		printf("\t                          3��У԰����\n\n");
		while(1) {
			printf("option : ");
			scanf("%d", &option);
			gets(a);
			if ((option == 1) || (option == 2) || (option == 3)) {
				Sleep(500);
				system("cls");
				break;
			} else {
				printf("�������� �밴��ȷ��ʽ���루eg��1��\n");
			}
		}
		switch(option) {
		case 1 : PrintPicture(adj); break;
		case 2 : Description(adj); break;
		case 3 :
			
			for (i = 1; i <= adj->vexnum; i++) {                              //������еص�
				if (i % 2 != 0) {
					printf("\n\n");
				}
				printf("%-2d��%-20s", i, adj->loc[i].name);
			}
			printf("\n\n��������ص���ѡ��:\n\n");
			
			while(1) {                                                       //ѡ����ʼ�ص�
				printf("\t\t��ʼ�ص㣺\t");
				scanf("%d", &begin);
				printf("\n\t\t  �յ㣺\t");
				scanf("%d", &end);
				printf("\n\n\n");
				if ((begin >= 1) && (begin <= adj->vexnum) && (end >= 1) && (end <= adj->vexnum)) {
					route[0] = 0;
					short_num = INFINITY;
					turn_num = INFINITY;
					for (i = 0; i <= adj->vexnum; i++) {
						shortest[i] = 0;
						turn_minimum[i] = 0;
					}						
					for (i = 0; i <= adj->vexnum; i++) {
						book[i] = 0;
					}
					DFS(adj, begin, end, begin, 1, 0);
					break;
				} else {
					printf("�������� �밴��ȷ��ʽ���루eg��1��\n");
				}
			}
			while(1) {
				system("cls");
				printf("��ǰ��ѡ��㣺%s\n��ѡ�յ㣺%s\n", adj->loc[begin].name, adj->loc[end].name);
				printf("\n\n\n\t\t**************************��ѡ�������Ŀ*************************\n\n");
				printf("\t\t                       1�����ȫ������·��\n");
				printf("\t\t                       2��������·��\n");
				printf("\t\t                       3�������ת��������·��\n\n");
				printf("\t\t*****************************************************************\n\n");
				while(1) {                                                         //ѡ�������Ŀ                          
					printf("\noption��");
					scanf("%d", &option);
					if ((option == 1) || (option == 2) || (option == 3)) {
						break;
					} else {
						printf("�������� �밴��ȷ��ʽ���루eg��1��\n");
					}
				}				
				switch(option) {
				case 1 : DFS(adj, begin, end, begin, 1, 1); break;
				case 2 : 
					printf("\n��%s��%s�����·�����£��ܳ�%d\n\n", adj->loc[begin].name, adj->loc[end].name, short_num);
					printf("%s-->", adj->loc[begin].name);
					for (i = 2; i < short_num2; i++) {
						printf("%s-->", adj->loc[shortest[i]].name);
					}
					printf("%s", adj->loc[end].name);
					break;
				case 3 : 
					printf("\n��%s��%s��ת�������ٵ�·�����£�����ת����%d\n\n", adj->loc[begin].name, adj->loc[end].name, turn_num);
					printf("%s-->", adj->loc[begin].name);
					for (i = 2; i < turn_num; i++) {
						printf("%s-->", adj->loc[turn_minimum[i]].name);
					}
					printf("%s", adj->loc[end].name);
					break;
				}
				printf("\n\n1������������\n");
				printf("2�������鿴·��\n");
				printf("3���˳�\n\noption : ");
				while(1) {
					scanf("%d", &option);
					switch(option) {
					case 1 : mark = 1; break;
					case 2 : break;
					case 3 : exit(0); break;
					default : printf("���������밴��ȷ��ʽ���루eg��1��\n");
					}
					if ((option == 1) || (option == 2) || (option == 3)) {
						system("cls");
						break;
					}
				}
				if (mark == 1) {
					break;
				}
			}
		}
		if (mark == 1) {
			mark = 0;
			continue;
		}
		printf("\n\n1��������һ��\n");
		printf("2���˳�\n\noption : ");
		while(1) {
			scanf("%d", &option);
			switch(option) {
			case 1 : break;
			case 2 : exit(0); break;
			default : printf("���������밴��ȷ��ʽ���루eg��1��\n");
			}
			if (option == 1) {
				system("cls");
				break;
			}
		}
	}
}

AddPasswordMessage(AdjMatrix *adj) {
	FILE *fp;
	char name[20], password[20], a[20];
	int i, option;
	printf("��ѡ��˿ڣ�\n\t1�������\t2����ͨ�û���\n");
	while(1) {
		printf("option : ");
		scanf("%d", &option);
		gets(a);
		if ((option == 1) || (option == 2)) {
			printf("\n������Ҫ��ӵ��û�����\t");
			gets(name);
			printf("                ���룺\t");
			gets(password);
		} else {
			printf("���������밴��ȷ��ʽ���루eg��1��\n");
			continue;
		}
		if (option == 1) {
			fp = fopen("����Ա.txt", "wt");
			fprintf(fp, "%d\n", (adj->chargernum) + 1);
			for (i = 1; i <= adj->chargernum; i++) {
				fprintf(fp, "%s %s\n", adj->charger[i].name, adj->charger[i].password);
			}
			fprintf(fp, "%s %s", name, password);
			fclose(fp);
		} else {
			fp = fopen("��ͨ�û�.txt", "wt");
			fprintf(fp, "%d\n", (adj->landnum) + 1);
			for (i = 1; i <= adj->chargernum; i++) {
				fprintf(fp, "%s %s\n", adj->land[i].name, adj->land[i].password);
			}
			fprintf(fp, "%s %s", name, password);
			fclose(fp);
		}
		printf("\n\t\t��ӳɹ���\n\n");
		adj = ReadLandMessage(adj);
		return;
	}
}
DeletePasswordMessage(AdjMatrix *adj) {
	FILE *fp;
	char name[20], password[20], a[20];
	int i, option, mark;
	printf("��ѡ��˿ڣ�\n\t1�������\t2����ͨ�û���\n");
	while(1) {
		printf("option : ");
		scanf("%d", &option);
		gets(a);
		if ((option == 1) || (option == 2)) {
			printf("\n������Ҫɾ�����û�����\t");
			gets(name);
		} else {
			printf("���������밴��ȷ��ʽ���루eg��1��\n");
			continue;
		}
		if (option == 1) {
			fp = fopen("����Ա.txt", "wt");
			for (i = 1; i <= adj->chargernum; i++) {
				if(strcmp(name, adj->charger[i].name) == 0) {
					mark = 1;
					fprintf(fp, "%d", (adj->chargernum) - 1);
					for (i = 1; i <= adj->chargernum; i++) {
						if(strcmp(name, adj->charger[i].name) == 0) {
							continue;
						}
						fprintf(fp, "\n%s %s", adj->charger[i].name, adj->charger[i].password);
					}
				}
			}
			if (mark == 0) {
				printf("\n���û�������!\n");
			} else {
				printf("\nɾ���ɹ�!\n");
			}
			fclose(fp);
		} else {
			fp = fopen("��ͨ�û�.txt", "wt");
			for (i = 1; i <= adj->landnum; i++) {
				if(strcmp(name, adj->land[i].name) == 0) {
					mark = 1;
					fprintf(fp, "%d", (adj->landnum) - 1);
					for (i = 1; i <= adj->landnum; i++) {
						if(strcmp(name, adj->land[i].name) == 0) {
							continue;
						}
						fprintf(fp, "\n%s %s", adj->land[i].name, adj->land[i].password);
					}
				}
			}
			if (mark == 0) {
				printf("\n���û�������!\n");
			} else {
				printf("\nɾ���ɹ�!\n");
			}
			fclose(fp);
		}
		adj = ReadLandMessage(adj);
		return;
	}
}
CorrectPasswordMessage(AdjMatrix *adj) {
	FILE *fp;
	char name[20], password[20], a[20];
	int i, option, mark = 0;
	printf("��ѡ��˿ڣ�\n\t1�������\t2����ͨ�û���\n");
	while(1) {
		printf("option : ");
		scanf("%d", &option);
		gets(a);
		if ((option == 1) || (option == 2)) {
			printf("\n������Ҫ�޸ĵ��û�����\t");
			gets(name);
		} else {
			printf("���������밴��ȷ��ʽ���루eg��1��\n");
			continue;
		}
		if (option == 1) {
			fp = fopen("����Ա.txt", "wt");
			for (i = 1; i <= adj->chargernum; i++) {
				if(strcmp(name, adj->charger[i].name) == 0) {
					mark = 1;
					printf("\n�����޸ĺ���û�����\t");
					gets(adj->charger[i].name);
					printf("\n�����޸ĺ�����룺\t");
					gets(adj->charger[i].password);
					fprintf(fp, "%d", adj->chargernum);
					for (i = 1; i <= adj->chargernum; i++) {
						fprintf(fp, "\n%s %s", adj->charger[i].name, adj->charger[i].password);
					}
				}
			}
			if (mark == 0) {
				printf("\n���û�������!\n");
			} else {
				printf("\n�޸ĳɹ�!\n");
			}
			fclose(fp);
		} else {
			fp = fopen("��ͨ�û�.txt", "wt");
			for (i = 1; i <= adj->landnum; i++) {
				if(strcmp(name, adj->land[i].name) == 0) {
					mark = 1;
					printf("\n�����޸ĺ���û�����\t");
					gets(adj->land[i].name);
					printf("\n�����޸ĺ�����룺\t");
					gets(adj->land[i].password);
					fprintf(fp, "%d", adj->landnum);
					for (i = 1; i <= adj->landnum; i++) {
						fprintf(fp, "\n%s %s", adj->land[i].name, adj->land[i].password);
					}
				}
			}
			if (mark == 0) {
				printf("\n���û�������!\n");
			} else {
				printf("\n�޸ĳɹ�!\n");
			}
			fclose(fp);
		}
		adj = ReadLandMessage(adj);
		return;
	}
}
SearchPasswordMessage(AdjMatrix *adj) {
	FILE *fp;
	char name[20], password[20], a[20];
	int i, option;
	printf("��ѡ��˿ڣ�\n\t1�������\t2����ͨ�û���\n");
	while(1) {
		printf("option : ");
		scanf("%d", &option);
		gets(a);
		if ((option == 1) || (option == 2)) {
			printf("\n������Ҫ���ҵ��û�����\t");
			gets(name);
		} else {
			printf("���������밴��ȷ��ʽ���루eg��1��\n");
			continue;
		}
		if (option == 1) {
//			fp = fopen("����Ա.txt", "wt");
			for (i = 1; i <= adj->chargernum; i++) {
				if(strcmp(name, adj->charger[i].name) == 0) {	
					printf("\n����Ҫ���ҵ��û���Ϣ������ʾ:\n\n");
					printf("\t�û�����%s", adj->charger[i].name);
					printf("\t���룺%s", adj->charger[i].password);
				}
			}
//			fclose(fp);
		} else {
			for (i = 1; i <= adj->landnum; i++) {
				if(strcmp(name, adj->land[i].name) == 0) {	
					printf("����Ҫ���ҵ��û���Ϣ������ʾ:\n");
					printf("\t�û�����%s", adj->land[i].name);
					printf("\t���룺%s", adj->land[i].password);
				}
			}
		}
		return;
	}
}
AddLocationMessage(AdjMatrix *adj) {
	FILE *fp, *fp1;
	char name[20], produce[20], a[20];
	int i, option, j, begin, end, choice;
	printf("����λ��or·�ߣ�\n\t1��λ��\t2��·��\n");
	while(1) {
		printf("option : ");
		scanf("%d", &option);
		gets(a);
		if ((option == 1) || (option == 2)) {
			break;
		} else {
			printf("���������밴��ȷ��ʽ���루eg��1��\n");
			continue;
		}
	}
	gets(a);
	if (option == 1) {                         //����λ��
		fp = fopen("����.txt", "w");
		printf("����Ҫ�����λ�����ƣ�");
		gets(adj->loc[adj->vexnum + 1].name);
		printf("\n            λ�ý��ܣ�");
		adj->loc[adj->vexnum + 1].x = 0;
		adj->loc[adj->vexnum + 1].y = 0;
		gets(adj->loc[adj->vexnum + 1].describe);
		fprintf(fp, "%d", adj->vexnum + 1);
		for (i = 1; i <= (adj->vexnum) + 1; i++) {
			fprintf(fp, "\n%s %d %d %s", adj->loc[i].name, adj->loc[i].x, adj->loc[i].y, adj->loc[i].describe);
		}
		fclose(fp);
		printf("������·��ͨ��·�� ��ֱ������·�����ȣ� ����ֱ������0\n");
		for (i = 1; i <= adj->vexnum; i++) {
			printf("%-12s", adj->loc[i].name);
			scanf("%d", &adj->arc[i][(adj->vexnum) + 1]);
			adj->arc[(adj->vexnum) + 1][i] = adj->arc[i][(adj->vexnum) + 1];
		}
		adj->arc[(adj->vexnum) + 1][(adj->vexnum) + 1] = 0;
		fp1 = fopen("����.txt", "w");
		
		for (i = 1; i <= adj->vexnum + 1; i++) {
			fprintf(fp1, "%d", adj->arc[i][1]);
			for (j = 2; j <= (adj->vexnum) + 1; j++) {
				fprintf(fp1, " %d", adj->arc[i][j]);
			}
			if (i != ((adj->vexnum) + 1)) {
				fprintf(fp1, "\n");
			}
		} 
		fclose(fp1);
	} else {
		printf("\nҪ�����·����Ϣ��\n\n");
		printf("            ��㣺");
		scanf("%d", &begin);
		printf("            �յ㣺");
		scanf("%d", &end);
		printf("        ·�����ȣ�");
		scanf("%d", &choice);
		adj->arc[begin][end] = adj->arc[end][begin] = choice;
		fp1 = fopen("����.txt", "w");
		for (i = 1; i <= adj->vexnum; i++) {
			fprintf(fp1, "%d", adj->arc[i][1]);
			for (j = 2; j <= adj->vexnum; j++) {
				fprintf(fp1, " %d", adj->arc[i][j]);
			}
			if (i != adj->vexnum) {
				fprintf(fp1, "\n");
			}
		} 
		fclose(fp1);
	}
	adj = ReadFromFile(adj);
	adj = ReadFromMatrixFile(adj);

}
DeleteLocationMessage(AdjMatrix *adj) {
	FILE *fp, *fp1;
	char name[20], produce[20], a[20];
	int i, option, j, begin, end, choice;
	printf("ɾ��λ��or·�ߣ�\n\t1��λ��\t2��·��\n");
	while(1) {
		printf("option : ");
		scanf("%d", &option);
		gets(a);
		if ((option == 1) || (option == 2)) {
			break;
		} else {
			printf("���������밴��ȷ��ʽ���루eg��1��\n");
			continue;
		}
	}
	gets(a);
	if (option == 1) {  
		fp = fopen("����.txt", "w");
		printf("����Ҫɾ����λ�����ƣ�");
		scanf("%d", &choice);
		fprintf(fp, "%d", adj->vexnum - 1);
		for (i = 1; i <= adj->vexnum; i++) {
			if (choice == i) {
				continue;
			}
			fprintf(fp, "\n%s %d %d %s", adj->loc[i].name, adj->loc[i].x, adj->loc[i].y, adj->loc[i].describe);
		}
		fclose(fp);

		fp1 = fopen("����.txt", "w");		
		for (i = 1; i <= adj->vexnum; i++) {
			if (i == choice) {
				continue;
			}
			fprintf(fp1, "%d", adj->arc[i][1]);
			for (j = 2; j <= adj->vexnum; j++) {
				if (j == choice) {
					continue;
				}
				fprintf(fp1, " %d", adj->arc[i][j]);
			}
			if (i != ((adj->vexnum) + 1)) {
				fprintf(fp1, "\n");
			}
		}
		fclose(fp1);
	} else {
		printf("\n\n��ѡ��Ҫɾ����·�ߣ�\n\n");
		printf("              ��㣺");
		scanf("%d", &begin);
		printf("              �յ㣺");
		scanf("%d", &end);
		fp1 = fopen("����.txt", "w");
		adj->arc[end][begin] = adj->arc[begin][end] = 0;
		for (i = 1; i <= adj->vexnum; i++) {
			fprintf(fp1, "%d", adj->arc[i][1]);
			for (j = 2; j <= adj->vexnum; j++) {
				fprintf(fp1, " %d", adj->arc[i][j]);
			}
			if (i != adj->vexnum) {
				fprintf(fp1, "\n");
			}
		} 
		fclose(fp1);
	}
	adj = ReadFromFile(adj);
	adj = ReadFromMatrixFile(adj);
		
}


LocationOperate(AdjMatrix *adj) {
	int i, option;
	while(1) {
		printf("********************************************************************\n\n");
		for (i = 1; i <= adj->vexnum; i++) {
			if ((i - 1) % 3 == 0) {
				printf("\n");
			}
			printf("%-2d��%-12s\t", i, adj->loc[i].name);
		}
		printf("\n\n********************************************************************\n\n");
		printf("\n\t\t-------------------- �ִ�ص�������ʾ�� ��ѡ�������Ŀ --------------------\n\n");
		printf("\t                          1������λ����Ϣ\n");
		printf("\t                          2��ɾ��λ����Ϣ\n");
		printf("\t                          3��������һ��\n\n");
		while(1) {
			printf("option : ");
			scanf("%d", &option);
			if ((option == 1) || (option == 2) || (option == 3)) {
				Sleep(500);
				system("cls");
			}
			switch(option) {
			case 1 : AddLocationMessage(adj); break;
			case 2 : DeleteLocationMessage(adj); break;	
			case 3 : return;
			default : printf("���������밴��ȷ��ʽ���루eg��1��\n");
			}
			if ((option == 1) || (option == 2) || (option == 3)) {
				break;
			}
		}
		printf("\n\n1��������һ��\n");
		printf("2���˳�\n\noption : ");
		while(1) {
			scanf("%d", &option);
			switch(option) {
			case 1 : break;
			case 2 : exit(0); break;
			default : printf("���������밴��ȷ��ʽ���루eg��1��\n");
			}
			if (option == 1) {
				system("cls");
				break;
			}
		}
	}

}
PasswordOperate(AdjMatrix *adj) {
	int i, option;
	while(1) {
		printf("********************************************************************\n��ͨ�û�\n");
		for (i = 1; i <= adj->landnum; i++) {
			if (i - 1 % 3 == 0) {
				printf("\n");
			}
			printf("%-20s: %-20s\t", adj->land[i].name, adj->land[i].password);
		}
		printf("\n\n\t********************************************************************\n�����\n");
		for (i = 1; i <= adj->chargernum; i++) {
			if (i - 1 % 3 == 0) {
				printf("\n");
			}
			printf("%-10s: %-10s\t", adj->charger[i].name, adj->charger[i].password);
		}
		printf("\n\n\t********************************************************************");

		printf("\n\t\t-------------------- �ִ��û���Ϣ������ʾ�� ��ѡ�������Ŀ --------------------\n\n");
		printf("\t                          1����������\n");
		printf("\t                          2��ɾ������\n");
		printf("\t                          3���޸�����\n");
		printf("\t                          4����������\n");
		printf("\t                          5��������һ��\n\n");
		while(1) {
			printf("option : ");
			scanf("%d", &option);
			if ((option == 1) || (option == 2) || (option == 3) || (option == 4) || (option == 5)) {
				Sleep(500);
				system("cls");
			}
			switch(option) {
			case 1 : AddPasswordMessage(adj); break;
			case 2 : DeletePasswordMessage(adj); break;
			case 3 : CorrectPasswordMessage(adj); break;
			case 4 : SearchPasswordMessage(adj); break;		
			case 5 : return;
			default : printf("���������밴��ȷ��ʽ���루eg��1��\n");
			}
			if ((option == 1) || (option == 2) || (option == 3) || (option == 4) || (option == 5)) {
				break;
			}
		}
		printf("\n\n1��������һ��\n");
		printf("2���˳�\n\noption : ");
		while(1) {
			scanf("%d", &option);
			switch(option) {
			case 1 : break;
			case 2 : exit(0); break;
			default : printf("���������밴��ȷ��ʽ���루eg��1��\n");
			}
			if (option == 1) {
				system("cls");
				break;
			}
		}
	}

}


ChargerEnterance(AdjMatrix *adj) {
	int option;
	while(1) {
		printf("\n\t\t-------------------- ��ѡ�������Ŀ --------------------\n\n");
		printf("\t                          1��λ����Ϣ�޸�\n");
		printf("\t                          2�������޸�\n\n");
		while(1) {
			printf("option : ");
			scanf("%d", &option);
			if ((option == 1) || (option == 2)) {
				Sleep(500);
				system("cls");
			}
			switch(option) {
			case 1 : LocationOperate(adj); break;
			case 2 : PasswordOperate(adj); break;
			default : printf("���������밴��ȷ��ʽ���루eg��1��\n");
			}
			if ((option == 1) || (option == 2)) {
				break;
			}
		}
	}
}

JudgeForLand(AdjMatrix *adj, int option) {
	char id[20], password[20], mark = 0;
	int i, count = 0;
	while(1) {
		printf("\t\t---------------------------------------------\n");
		printf("\t\t�������û�����\t\t");
		gets(id);
		printf("\n\t\t���������룺\t\t");
		for (i = 0; ; i++) {
			password[i] = getch();
			if (((int)password[i] == 10) || ((int)password[i] == 32) || ((int)password[i] == 13)) {
				password[i] = '\0';
				break;
			}
			if ((int)password[i] == 8) {
				i = i - 2;
				printf("\b \b");
			} else {
            	 printf("*");
			}
		}
		printf("\n\t\t---------------------------------------------\n");
		if (option == 2) {
			for (i = 1; i <= adj->chargernum; i++) {
				if (strcmp(adj->charger[i].name, id) == 0) {
					if (strcmp(adj->charger[i].password, password) == 0) {
						printf("\t\t������ȷ");
						Sleep(200);
						system("cls");
						ChargerEnterance(adj);
						mark = 1;
						break;
					} else {
						break;
					}
				}
			}
		} else {
			for (i = 1; i <= adj->landnum; i++) {
				if (strcmp(adj->land[i].name, id) == 0) {
					if (strcmp(adj->land[i].password, password) == 0) {
						printf("\n\n\n\t\t�� �� �� ȷ ......");
						Sleep(500);
						system("cls");
						StudentEnterance(adj);
						mark = 1;
						break;
					} else {
						break;
					}
				}
			}
		}
		if (mark == 1) {
			break;
		} else {
			count++;
			printf("\n\n�û������������ ���δ��� �˺������� ��ǰʣ�������%d\n\n", 3 - count);
		}
		if (count == 3) {
			printf("�����������Σ� ���Ժ����ԡ�����������\n");
			exit(0);
		}
	}
}

main() 
{
	AdjMatrix *adj;
	FILE *fp;
	int option, t, i, mark = 0;
	char a[10];
	adj = (AdjMatrix*)malloc(sizeof(AdjMatrix));
	adj = ReadFromFile(adj);
	adj = ReadFromMatrixFile(adj);
	adj = ReadLandMessage(adj);
	for (i = 0; i <= adj->vexnum; i++) {
		book[i] = 0;
	}
//	adj->vexnum = 14;
	printf("\n\n\n\n\n\n\n\t\t-------------------- ��ӭ����У԰����ϵͳ --------------------\n\n");
	Sleep(1000);
	printf("\t\t                                .\n\n");
	Sleep(1000);
	printf("\t\t                                .\n\n");
	Sleep(1000);
	printf("\t\t                                .\n\n");
	while (1) {
		Sleep(1000);
		system("cls");
		printf("\n\t\t-------------------- ��ѡ���¼�� --------------------\n\n");
		printf("\t                          1����ͨ�û���¼\n");
		printf("\t                          2������Ա��¼\n");
		while(1) {
			printf("option : ");
			scanf("%d", &option);
			if ((option == 1) || (option == 2)) {
					Sleep(500);
					system("cls");
					break;
			} else {
				printf("���������밴��ȷ��ʽ���루eg��1��\n");
			}
		}
		gets(a);
		JudgeForLand(adj, option);
	}

} 