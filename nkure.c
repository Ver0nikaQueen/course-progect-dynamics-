#define _CRT_SECURE_NO_DEPRECATE
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <malloc.h>
//#include <windows.h>
const int col = 50; // ���������� ��������� ����� � ������
const int row = 135; // ���������� �����
int ckolko();
float** sozdArr(int uc);
float** zapol(float** prt, int r);
void printtt(float** Arr, int uc, char** name, char** name2, int t);
int sortlr(float* mass, float* taz, int n);
float formuls2(float n, int t);
void cas11(float** rezg, int m, char** name, char** name2); 
void cas22(float** rezg, int m, int uc, char** name, char** name2);
int imax(float** rezg, int m, int uc);
int imin(float** rezg, int m, int uc);
void cas33(float** rezg, int uc, char** name);
float cumcrzmm(int t, int uc, float** rezg);
char** put_nam( char** name, int uc );
char** put_vids( char** vi, int uc );
int main()
{
	system("chcp 1251"); system("cls"); int uc = ckolko();
	HANDLE cc_na_con = GetStdHandle( STD_OUTPUT_HANDLE );
	SMALL_RECT windowSize = { 0, 0, col - 1, row - 1 };
	SetConsoleWindowInfo( cc_na_con, TRUE, &windowSize );
	SetConsoleTextAttribute( cc_na_con, FOREGROUND_RED |	FOREGROUND_GREEN | FOREGROUND_INTENSITY );
	system( "title ������������� ���������� �� ����������� XXII-��� ��������� �� ����������� �������" );
	char a; float ** iArr = sozdArr(uc); zapol(iArr,uc);
	char** name = (char**)calloc(uc, sizeof(char*));
	put_nam( name, uc );
	char** vidsp = (char**)calloc(uc, sizeof(char*));
	put_vids( vidsp , uc );
	printf("	��� ������������ ���������� �� ����������� XXII-��� ��������� �� ����������� �������\n\n");
	do {
		char c; 
		printf("�������� ������������ ��������: \n0 - ������ �������� ���������� ������������\n1 - ������ ���������� ��������� ������������ \n2 - ������ ���������� ���� ���������� \n3 - ��������� ������ ��������� \n4 - ������� �������� �������\n5 - ������� ���������� �������� \n->>>> ");
		scanf("%c", &c); getchar();
		switch (c)
		{
		case '0':
			printtt( iArr, uc, name, vidsp, uc );
			break;
		case '1':
			printf("������� ����� ��������� (1-%d): ", uc); int m = 0;
			scanf("%d", &m); getchar();
			cas11(iArr, m, vidsp, name);
			break;
		case '2': 
			printf("������� ����� ���������� (1-7): "); int m1 = 0;
			scanf("%d", &m1); getchar(); 
			cas22(iArr, m1, uc, name, vidsp);
			break;
		case '3': 
			printf( "	������� ������ �� ������ ����������� ��� ������ 5 ���������� ��� ���������\n" );
			printtt(iArr, uc, name, vidsp, 5);
			printf("������� ����� ��������� � ��� ������\n"); int nom, vss;
			scanf("%d", &nom); 	printf("%s", name[nom - 1]);
			scanf("%d", &vss); 	printf("%s", vidsp[vss - 1]);
			printf("\n��������! ���� ������������� ����������� �������� �������� �������!\n��������� � ������������ ����� ������ �� ������� ����!");
			printf("\n������� ����� ������ >>> "); float temp; scanf("%f", &temp); iArr[nom-1][vss] = temp;
			printf("������ ��������� %.2f �� %s ����������� %s\n", iArr[nom - 1][vss], vidsp[vss - 1], name[nom - 1]);
		case '4': 
			cas33(iArr, uc, name);
			printf("\n���� ������� ������: \n1 - ����� ���������� �����, 2 - ������� ���������� �����, \n3 - ����������� ���������� �����, 4 -  ������������ ���������� �����, 5 - �������\n>>> ");
			int t;  scanf("%d", &t);	getchar();
			printf("��������� ������� >>> %f �����\n\n", cumcrzmm(t, uc, iArr));
			break;
		case '5':
			system("cls"); break;

		default:
			printf("������������ ���� :^)\n"); break;
		}
		printf("������� ����������? �� - 1, ��� - ����� ������ ������ > ");
		scanf("%c", &a);
		getchar();
	} while (a == '1');
	printf("��������� ���������", a);

	return 0;
	return 0;

}
int ckolko() {
	FILE* mf;  char str[60];  char* estr;
	//printf("�������� ����� : ");
	mf = fopen("1.txt", "r");
	if (mf == NULL) { printf("������\n"); return -1; }
	//else printf("���������\n");
	int vs1 = 0;
	while (1) {
		estr = fgets(str, sizeof(str), mf);
		if (estr == NULL) {
			if (feof(mf) != 0) {
				//printf("\n ������ ����� ���������\n");     
				break;
			}
			else { printf("\n ������ ������ �� �����\n");     break; }
		}
		vs1++;
	}
	//printf("�������� ����� : ");
	if (fclose(mf) == EOF) printf("������\n");
	//else printf("���������\n");
	return vs1;
}
float** sozdArr(int uc) {

	float** iuArr = (float**)calloc(uc, sizeof(float*));
	if (iuArr != NULL) {
		for (int i = 0; i < uc; i++) {
			*(iuArr + i) = (float*)calloc(7, sizeof(float));
		}

		return iuArr;
	}
}
float** zapol(float** prt, int r)
{
	char fname[] = "data2.txt";
	FILE* in; float at;
	in = fopen(fname, "r");
	if (in == NULL) {
		printf("������ �������� �����");
		return 0;
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < 7; j++) { fscanf(in, "%f ", &at);	if (at == 00, 00) break; *(*(prt + i) + j) = at; }
	}
	return prt;
	fclose(in);
}
void printtt(float** Arr, int uc, char** name, char** name2, int t)
{
	printf("	��� ������	");
	for (int i = 0; i < 7; i++) printf("| %.12s	", name2[i] );
	puts("\n --------------------------------------------------------------------------------------------------------------------------------");
	for (int i = 0; i < t; i++)
	{
		printf( " %.15s	", name[i] );
		for (int j = 0; j < 7; ++j) { 
			if (j < 4) printf( "| %.3f m	", *( *( Arr + i ) + j ) ); 
			if (j > 3) printf( "| %.3f c	", *( *( Arr + i ) + j ) );
		}
		printf("\n");
	} printf("\n");
}
int sortlr(float* mass, float* taz, int n)
{
	for (int i = n - 1; i >= 0; i--)
	{
		int noSwap = 1; float tmp, tmp2;
		for (int j = 0; j < i; j++)
		{
			if (mass[j] < mass[j + 1])
			{
				tmp = mass[j];
				mass[j] = mass[j + 1];
				mass[j + 1] = tmp;
				tmp2 = taz[j];
				taz[j] = taz[j + 1];
				taz[j + 1] = tmp2;
				noSwap = 0;
			}
		}
		if (noSwap == 1)
			break;
	}
}
float formuls2(float n, int t)
{
	float a[7] = { 1.84523, 0.188807, 56.0211, 15.9803, 4.99087, 9.23076, 0.11193 };
	float b[7] = { 75, 210, 1.5, 3.8, 42.5, 26.7, 254 };
	float c[7] = { 1.348, 1.41, 1.05, 1.04, 1.81, 1.835, 1.88 };
	if (t < 2) return a[t] * powf(n * 100 - b[t], c[t]);
	if (t > 3) return a[t] * powf(b[t] - n, c[t]);
	if (t < 4 && t > 1) return a[t] * powf(n - b[t], c[t]);
}
void cas11(float** rezg, int m, char** name, char** name2) {
	printf("������ �� ���������: "); printf("%s\n", name2[m - 1]);
	printf("   ��� ����������	|	���������	|   ��������� �����	\n");
	printf("------------------------------------------------------------\n");
	float r = 0;  char razm = 'm'; float cumm = 0;
	for (int i = 0; i < 7; i++)
	{
		if (i > 3) razm = 'c';
		r = formuls2(rezg[m - 1][i], i); cumm += formuls2(rezg[m - 1][i], i);
		if (i != 5) printf("    %s |	%0.3f	%c	|	%0.3f	\n", name[i], rezg[m - 1][i], razm, r);
		else printf("    %s |	%0.3f	%c	|	%0.3f		\n", name[i], rezg[m - 1][i], razm, r);
	}printf("\n");
	printf("����� ����� ����� ��������� ������������: %0.3f\n\n", cumm);
}
void cas22(float** rezg, int m, int uc, char** name, char** name2) {
	printf("������ �� ���� ������: "); m--;
	printf("%s\n", name2[m]);
	printf("   ��������� �����	|	���������	|       ��������  	\n");
	printf("-------------------------------------------------------------------------\n");
	char razm = 'm'; float r1;
	if (m > 3) razm = 'c'; printf("	");
	for (int i = 0; i < uc; i++) {
		r1 = formuls2(rezg[i][m], m);
		printf("%0.2f		|	%0.3f	%c	|	%s	", r1, rezg[i][m], razm, name[i]);
	}printf("\n\n");
	printf("������ ������� ���� ������ ����������� ��������� ��� ������� %d - %s, ���������� %0.3f ������\n\n", imax(rezg, m, uc) + 1, name[imax(rezg, m, uc)], formuls2(rezg[(imax(rezg, m, uc))][m], m));
	printf("���������� ������� ���� ������ ����������� ��������� ��� ������� %d - %s, ���������� %0.3f ������\n\n", imin(rezg, m, uc) + 1, name[imin(rezg, m, uc, 1)], formuls2(rezg[(imin(rezg, m, uc))][m], m));
}
int imax(float** rezg, int m, int uc) {
	int maxx = 0; int ma11 = 0;
	for (int i = 0; i < uc; i++) if (formuls2(rezg[i][m], m) > maxx) { maxx = formuls2(rezg[i][m], m); ma11 = i; }
	return ma11;
}
int imin(float** rezg, int m, int uc) {
	int minn = 9999999; int ma11 = 0;
	for (int i = 0; i < uc; i++) if (formuls2(rezg[i][m], m) < minn) { minn = formuls2(rezg[i][m], m); ma11 = i; }
	return ma11;
}
void cas33(float** rezg, int uc, char** name) {
	printf("\n");
	printf("*** *** *** *** ***  ����� ����������  *** *** *** ***\n");
	printf("---------------------------------------------------------\n");
	printf("	�����	|	�����	|	���������\n");
	printf("---------------------------------------------------------\n");
	//���������� ������
	float* fin_b; int* fin;
	fin_b = (float*)malloc(uc * sizeof(int));//����� ��� ������������ ������
	fin = (int*)malloc(uc * sizeof(int));//������� ���������
	if (fin_b == NULL) { puts("error"); return -1; }
	if (fin == NULL) { puts("error"); return -1; }
	for (int i = 0; i < uc; i++)
	{
		fin[i] = i;
		fin_b[i] = 0;
		for (int j = 0; j < 7; j++) {
			fin_b[i] += formuls2(rezg[i][j], j);
		}
	}
	sortlr(fin_b, fin, uc); printf("	");
	for (int i = 0; i < uc; i++) { printf("%d	|", i + 1); printf("	%.0f	|", fin_b[i]);  printf("	%s	", name[fin[i]]); }//������� 
	free(fin_b); free(fin);
}
float cumcrzmm(int t, int uc, float** rezg) {
	float cum = 0, mint = 99999, maxt = 0, p = 0;
	for (int i = 0; i < uc; i++) {
		p = 0;
		for (int j = 0; j < 7; j++) {
			p += formuls2(rezg[i][j], j);
		}
		cum += p;
		maxt = max(maxt, p);
		mint = min(mint, p);
	}
	if (t == 1) return cum;
	if (t == 2) return (cum / uc);
	if (t == 4) return maxt;
	if (t == 3) return mint;
	if (t == 5) return -1;
}
char** put_nam( char** name, int uc ) {
	FILE* file;	file = fopen( "1.txt", "r" );
	char str [20];
	for (int q = 0; q < uc; q++) {
		name [q] = ( char* ) calloc( 15, sizeof( char ) ); //��������� ������ ���
		fgets( str, sizeof( str ), file ); strcpy( name [q], str ); //���������� ����������
	} 	fclose( file );
}
char** put_vids( char** vi, int uc ) {
	FILE* fle;	fle = fopen( "4.txt", "r" );
	char str [20];
	for (int q = 0; q < 7; q++) {
		vi [q] = ( char* ) calloc( 20, sizeof( char ) ); //��������� ������ ����� ������
		fgets( str, sizeof( str ), fle ); strcpy( vi [q], str ); //���������� ����������
	}	fclose( fle );
}