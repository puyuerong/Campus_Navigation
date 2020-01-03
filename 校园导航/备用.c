#include"stdio.h"
#include"stdlib.h"
#include"windows.h" 
#define MAXVEX 15                      //��󶥵��� 
#define INFINITY 9999
typedef struct {
	int x;
	int y;
	char name[100];
	char describe[200];
}Location;
typedef struct {
	int arc[MAXVEX][MAXVEX];
	Location loc[MAXVEX];
	int vexnum;
	int arcnum;
}AdjMatrix;

int Transform(char a[20]) {
	int i = 0, sum = 0;
	while(i < strlen(a)) {
		sum = sum * 10 + (int)a[i++] - 48;
	}
	return sum;
}

AdjMatrix *ReadFromFile(AdjMatrix *adj) { 
	FILE *fp;
	int i = 0;
	char a[10];
	fp = fopen("����.txt", "r");
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
	fclose(fp);
	return adj;
}

PrintMap(AdjMatrix *adj) {               //��ͼ���
	int i;
	for (i = 1; i < MAXVEX; i++) {
		printf("%s %d %d %s\n", adj->loc[i].name, adj->loc[i].x, adj->loc[i].y, adj->loc[i].describe);
	}
}

PrintPicture(AdjMatrix *adj) {
	int i;
	for (i = 1; i < MAXVEX; i++) {

	}
}




Description() {                                             //λ����Ϣ����
}



main() 
{
	AdjMatrix *adj;
	FILE *fp;
	int option, t;
	char begin[20], end[20];
	adj = (AdjMatrix*)malloc(sizeof(AdjMatrix));
	adj = ReadFromFile(adj);
	PrintMap(adj);

//	initgraph(640, 480);

  //  line(200, 240, 440, 240);

  // getch();

   //closegraph();



	/*
	printf("\n\n\n\n\n\n\n\t\t-------------------- ��ӭ����У԰����ϵͳ --------------------\n\n");
	Sleep(1000);
	printf("\t\t                                .\n\n");
	Sleep(1000);
	printf("\t\t                                .\n\n");
	Sleep(1000);
	printf("\t\t                                .\n\n");
	Sleep(1000);
	system("cls");
	printf("\n\t\t-------------------- ��ѡ�������Ŀ --------------------\n\n");
	printf("\t                          1��У԰һ��ͼ\n");
	printf("\t                          2���ص���Ϣ��ѯ\n");
	printf("\t                          3��У԰����\n\n");
	
	while(1) {
		printf("option : ");
		scanf("%d", &option);
		switch(option) {
		case 1 : PrintMap(); break;
		case 2 : Description(); break;
		case 3 :
			printf("������ʼ�ص㣺");
			scanf("%s", begin);
			printf("\n����ĩλ�ã�");
			scanf("%s", end);
			break;
		default : printf("���������밴��ȷ��ʽ���루eg��1��\n");
		}
		if ((option == 1) || (option == 2)) {
			break;
		}
	}

*/

} 