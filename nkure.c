#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <string.h>
#include <malloc.h>
int ckolko();
float** sozdArr(int uc, int vs);
float** zapol(float** prt, int r);
void printtt(float** Arr, int uc, char** name, char** name2);
int sortlr(float* mass, float* taz, int n);
float formuls2(float n, int t);
void cas11(float** rezg, int m, char** name, char** name2); 
void cas22(float** rezg, int m, int uc, char** name, char** name2);
int imax(float** rezg, int m, int uc);
int imin(float** rezg, int m, int uc);
void cas33(float** rezg, int uc, char** name);
float cumcrzmm(int t, int uc, float** rezg);
int main()
{
	system("chcp 1251"); system("cls"); int uc = ckolko();
	int vs = 7; char a; float ** iArr = sozdArr(uc, vs); zapol(iArr,uc);

	FILE* file;	file = fopen("1.txt", "r"); 
	char str[20]; 	char** name = (char**)calloc(uc, sizeof(char*));
	for (int q = 0; q < uc; q++) {
		name[q] = (char*)calloc(15, sizeof(char)); //двумерный массив имён
		fgets(str, sizeof(str), file); strcpy(name[q], str); //заполнение значениями
	} 	fclose(file); 
	FILE* fle;	fle = fopen("4.txt", "r"); 	char** vidsp = (char**)calloc(uc, sizeof(char*));
	for (int q = 0; q < 7; q++) {
		vidsp[q] = (char*)calloc(20, sizeof(char)); //двумерный массив видов спорта
		fgets(str, sizeof(str), fle); strcpy(vidsp[q], str); //заполнение значениями
	}	fclose(fle);
	printf("	Вас приветствует справочник по результатам XXII-ого семиборья по Воронежской области\n\n");
	do {
		char c; 
		printf("Выберите интересующее действие: \n1 - Узнать результаты участника соревнований \n2 - Узнать результаты вида состязаний \n3 - Изменение данных участника \n4 - Вывести итоговый рейтинг\n5 - Стереть результаты запросов \n->>>> ");
		scanf("%c", &c); getchar();
		switch (c)
		{
		case '1':
			printf("Введите номер участника (1-%d): ", uc); int m = 0;
			scanf("%d", &m); getchar();
			cas11(iArr, m, vidsp, name);
			break;
		case '2': 
			printf("Введите номер состязания (1-7): "); int m1 = 0;
			scanf("%d", &m1); getchar(); 
			cas22(iArr, m1, uc, name, vidsp);
			break;
		case '3': 
			printtt(iArr, uc, name, vidsp);
			printf("Введите номер участника и вид спорта\n"); int nom, vss;
			scanf("%d", &nom); 	printf("%s", name[nom - 1]);
			scanf("%d", &vss); 	printf("%s", vidsp[vss - 1]);
			printf("\nВнимание! Ввод необъективных результатов повредит итоговый рейтинг!\nУбедитесь в корректности новых данных по таблице выше!");
			printf("\nВведите новые данные >>> "); float temp; scanf("%f", &temp); iArr[nom-1][vss] = temp;
			printf("Теперь результат %.2f по %s принадлежит %s\n", iArr[nom - 1][vss], vidsp[vss - 1], name[nom - 1]);
		case '4': 
			cas33(iArr, uc, name);
			printf("\nЧего желаете узнать: \n1 - общее количество очков, 2 - среднее количество очков, \n3 - минимальное количество очков, 4 -  максимальное количество очков, 5 - пропуск\n>>> ");
			int t;  scanf("%d", &t);	getchar();
			printf("Результат запроса >>> %f очков\n\n", cumcrzmm(t, uc, iArr));
			break;
		case '5':
			system("cls"); break;

		default:
			printf("Некорректный ввод :^)\n"); break;
		}
		printf("Желаете продолжить? Да - 1, Нет - любой другой символ > ");
		scanf("%c", &a);
		getchar();
	} while (a == '1');
	printf("Программа выключена", a);

	return 0;
	return 0;

}
int ckolko() {
	FILE* mf;  char str[60];  char* estr;
	//printf("Открытие файла : ");
	mf = fopen("1.txt", "r");
	if (mf == NULL) { printf("ошибка\n"); return -1; }
	//else printf("выполнено\n");
	int vs1 = 0;
	while (1) {
		estr = fgets(str, sizeof(str), mf);
		if (estr == NULL) {
			if (feof(mf) != 0) {
				//printf("\n Чтение файла закончено\n");     
				break;
			}
			else { printf("\n Ошибка чтения из файла\n");     break; }
		}
		vs1++;
	}
	//printf("Закрытие файла : ");
	if (fclose(mf) == EOF) printf("ошибка\n");
	//else printf("выполнено\n");
	return vs1;
}
float** sozdArr(int uc, int vs) {

	float** iuArr = (float**)calloc(uc, sizeof(float*));
	if (iuArr != NULL) {
		for (int i = 0; i < uc; i++) {
			*(iuArr + i) = (float*)calloc(vs, sizeof(float));
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
		printf("Ошибка открытия файла");
		return 0;
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < 7; j++) { fscanf(in, "%f ", &at);	if (at == 00, 00) break; *(*(prt + i) + j) = at; }
	}
	return prt;
	fclose(in);
}
void printtt(float** Arr, int uc, char** name, char** name2)
{
	printf("Текущая таблица данных по разным дисциплинам для первых 5 участников\n");
	for (int i = 1; i < 8; i++) printf(" %d     ", i);
	puts(" ");
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 7; ++j) printf("%.3f ", *(*(Arr + i) + j));
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
	printf("Запрос на участника: "); printf("%s\n", name2[m - 1]);
	printf("   Вид состязания	|	Результат	|   Набранные баллы	\n");
	printf("------------------------------------------------------------\n");
	float r = 0;  char razm = 'm'; float cumm = 0;
	for (int i = 0; i < 7; i++)
	{
		if (i > 3) razm = 'c';
		r = formuls2(rezg[m - 1][i], i); cumm += formuls2(rezg[m - 1][i], i);
		if (i != 5) printf("    %s |	%0.3f	%c	|	%0.3f	\n", name[i], rezg[m - 1][i], razm, r);
		else printf("    %s |	%0.3f	%c	|	%0.3f		\n", name[i], rezg[m - 1][i], razm, r);
	}printf("\n");
	printf("Общая сумма очков участника соревнований: %0.3f\n\n", cumm);
}
void cas22(float** rezg, int m, int uc, char** name, char** name2) {
	printf("Запрос на вида спорта: "); m--;
	printf("%s\n", name2[m]);
	printf("   Набранные баллы	|	Результат	|       Участник  	\n");
	printf("-------------------------------------------------------------------------\n");
	char razm = 'm'; float r1;
	if (m > 3) razm = 'c'; printf("	");
	for (int i = 0; i < uc; i++) {
		r1 = formuls2(rezg[i][m], m);
		printf("%0.2f		|	%0.3f	%c	|	%s	", r1, rezg[i][m], razm, name[i]);
	}printf("\n\n");
	printf("Рекорд данного вида спорта принадлежит участнику под номером %d - %s, набравшему %0.3f баллов\n\n", imax(rezg, m, uc) + 1, name[imax(rezg, m, uc)], formuls2(rezg[(imax(rezg, m, uc))][m], m));
	printf("Антирекорд данного вида спорта принадлежит участнику под номером %d - %s, набравшему %0.3f баллов\n\n", imin(rezg, m, uc) + 1, name[imin(rezg, m, uc, 1)], formuls2(rezg[(imin(rezg, m, uc))][m], m));
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
	printf("*** *** *** *** ***  Итоги состязаний  *** *** *** ***\n");
	printf("---------------------------------------------------------\n");
	printf("	Место	|	Баллы	|	Спортсмен\n");
	printf("---------------------------------------------------------\n");
	//вычисление баллов
	float* fin_b; int* fin;
	fin_b = (float*)malloc(uc * sizeof(int));//место для суммирования баллов
	fin = (int*)malloc(uc * sizeof(int));//порядок участника
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
	for (int i = 0; i < uc; i++) { printf("%d	|", i + 1); printf("	%.0f	|", fin_b[i]);  printf("	%s	", name[fin[i]]); }//вввывод 
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