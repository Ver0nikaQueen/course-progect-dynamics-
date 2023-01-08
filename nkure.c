#define _CRT_SECURE_NO_DEPRECATE
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
int ckolko();
int** put( char** name, int uc, float** Arr );
void printtt(float** Arr, char** name, char** name2, int t);
int sortlr(float* mass, float* taz, int n);
float formuls2(float n, int t);
void cas11(float** rezg, int m, char** name, char** name2, int t, int uc); 
float icum( float** rezg, int m );
int imax(float** rezg, int m, int uc);
int imin(float** rezg, int m, int uc);
float * cas33(float** rezg, int uc, char** name, float * ar);
void krit( int t, float* rezg );
char** put_vids( char** vi );
int main()
{
	system("chcp 1251"); 	
	system("cls"); 
	int uc = ckolko(); // расчет количества участников
	float ** iArr = ( float** ) calloc( uc, sizeof( float* ) );// создание массива результатов 
	char** name = (char**)calloc(uc, sizeof(char*)); //создание массива ФИО участников
	put( name, uc, iArr );
	char** vidsp = (char**)calloc(7, sizeof(char*));//создание массива видов состязаний
	put_vids( vidsp );
	printf("	Вас приветствует справочник по результатам XXII-ого семиборья по Воронежской области\n\n");
	char a; //переменная для безотрывных запросов пользователя
	do {
		char c; //номер требуемого запроса от пользователя
		printf("Выберите интересующее действие: \n0 - Узнать исходные результаты соревнований\n1 - Узнать результаты участника соревнований \n2 - Узнать результаты вида состязаний \n3 - Изменение данных участника \n4 - Вывести итоговый рейтинг\n5 - Стереть результаты запросов \n->>>> ");
		scanf("%c", &c); getchar();
		switch (c)
		{
		case '0':
			printtt( iArr, name, vidsp, uc ); //печать исходной таблицы данных
			break;
		case '1':
			printf("Введите номер участника (1-%d): ", uc); 
			int m = 0;
			scanf("%d", &m); getchar();
			cas11(iArr, m, vidsp, name,0,uc); //запрос на конкретного участника
			printf( "Общая сумма очков участника соревнований: %0.3f\n\n", icum(iArr,m-1) );
			break;
		case '2': 
			printf("Введите номер состязания (1-7): "); 
			int m1 = 0;
			scanf("%d", &m1); getchar(); 
			cas11( iArr, m1, name, vidsp, 1, uc );//запрос по виду спорта
			int g = imax( iArr, m1, uc );//вывод индекста максимума
			printf( "Рекорд данного состязания принадлежит участнику под номером %d - %.15s, набравшему %0.3f баллов\n", g + 1, name [g], formuls2( iArr [g][m1], m1 ) );
			g = imin( iArr, m1, uc );//вывод индекста мининмума
			printf( "Антирекорд данного состязания принадлежит участнику под номером %d - %.15s, набравшему %0.3f баллов\n\n", g + 1, name [g], formuls2( iArr [g][m1], m1 ) );
			break;
		case '3': 
			printf( "	Таблица данных по разным дисциплинам для первых 5 участников для сравнения\n" );
			printtt(iArr, name, vidsp, 5);//вывод части таблицы во избежание ошибок
			printf("Введите номер участника и вид спорта\n"); 
			int nom, vss;
			scanf("%d", &nom); 	printf("%s", name[nom - 1]);
			scanf("%d", &vss); 	printf("%s", vidsp[vss - 1]);
			printf("\nВнимание! Ввод необъективных результатов повредит итоговый рейтинг!\nУбедитесь в корректности новых данных по таблице выше!");
			printf("\nВведите новые данные >>> "); float temp; scanf("%f", &temp); iArr[nom-1][vss] = temp;//изменение исходных данных
			printf("Теперь результат %.2f по состязанию %s принадлежит %s\n", iArr[nom - 1][vss], vidsp[vss - 1], name[nom - 1]);
		case '4': 
			printf( "\n");
			int t;  float ar [4] = { 0 };
			float * terr= ar;
			terr=cas33(iArr, uc, name, ar); 
			printf("\nЧего желаете узнать: \n1 - общее количество очков, 2 - среднее количество очков, \n3 - минимальное количество очков, 4 -  максимальное количество очков, 5 - пропуск\n>>> ");
			scanf("%d", &t);	
			getchar();
			krit(t, ar);
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
int ckolko( ) {
	FILE* mf;  char str [60];  char* estr;
	mf = fopen( "data.txt", "r" );//поиск по документу с ФИО
	if (mf == NULL) {
		printf( "ошибка\n" );
		return -1;
	}
	int vs1 = 0;
	while (TRUE) {
		estr = fgets( str, sizeof( str ), mf );
		if (estr == NULL) {
			if (feof( mf ) != 0) {
				//printf("\n Чтение файла закончено\n");     
				break;
			}
			else { printf( "\n Ошибка чтения из файла\n" );     break; }
		}
		vs1++;
	}
	//printf("Закрытие файла : ");
	if (fclose( mf ) == EOF) printf( "ошибка\n" );
	//else printf("выполнено\n");
	return vs1;
}
int** put( char** name, int uc, float** ar ) {
	FILE* file;	file = fopen( "data.txt", "r" );
	char str [20];
	for (int q = 0; q < uc; q++) {
		name [q] = ( char* ) calloc( 15, sizeof( char ) );//выделение памяти под ФИО
		*( ar + q ) = ( float* ) calloc( 7, sizeof( float ) );//двумерный массив результатов
		for (int i = 0; i < 7; i++) {
			fscanf( file, "%f", &ar [q][i] );//заполнение значениями
		}
		fgets( str, sizeof( str ), file );
		strcpy( name [q], str ); //заполнение значениями
	}
	fclose( file );
}
void printtt(float** Arr, char** name, char** name2, int t)
{

	for (int i=0; i< 30;i++) printf( "----" );	printf( "\n\n" );
	printf("   Вид спорта   ");
	for (int i = 0; i < 6; i++) printf("|%.14s", name2[i] ); printf( "|%.13s\n", name2 [6] );//вывод видов спорта
	printf("\n"); for (int i = 0; i < 30; i++) printf( "----" );	printf( "\n\n" );
	for (int i = 0; i < t; i++)
	{
		printf( "%.15s	", name[i] );//ФИО участника
		for (int j = 0; j < 7; ++j) { 
			if (j < 4) printf( "|   %3.3f m   ", *( *( Arr + i ) + j ) ); //значение состязаний
			if (j > 3 && j<6) printf( "|   %3.3f c   ", *( *( Arr + i ) + j ) );//значение состязаний
			if (j==6) printf( "|   %3.3f c", *( *( Arr + i ) + j ) ); // значение состязаний
			if (j==0 || j==1) printf(" ");//табуляция и красивый отступ
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
				tmp = mass[j];//сортировка массива с общими баллами
				mass[j] = mass[j + 1];
				mass[j + 1] = tmp;
				tmp2 = taz[j];//сортировка массива с индексами участников
				taz[j] = taz[j + 1];
				taz[j + 1] = tmp2;
				noSwap = 0;
			}
		}
		if (noSwap == 1)//проверка на отсутствие обмена
			break;
	}
}
float formuls2(float n, int t)
{
	float a[7] = { 1.84523, 0.188807, 56.0211, 15.9803, 4.99087, 9.23076, 0.11193 };
	float b[7] = { 75, 210, 1.5, 3.8, 42.5, 26.7, 254 };
	float c[7] = { 1.348, 1.41, 1.05, 1.04, 1.81, 1.835, 1.88 };
	if (t < 2) return a[t] * powf(n * 100 - b[t], c[t]);// для состязаний, которые высчитываются в сантиметрах
	if (t > 3) return a[t] * powf(b[t] - n, c[t]);//секундах
	if (t < 4 && t > 1) return a[t] * powf(n - b[t], c[t]);//метрах
}
void cas11(float** rezg, int m, char** name, char** name2, int t, int uc) {
	m--;
	printf("Запрос на "); printf("%.15s\n", name2[m]);
	if (t==0) printf( "   Вид состязания	|");
	else printf( "	Участник	|");
	printf("	Результат	|   Набранные баллы\n");
	for (int i = 0; i < 17; i++) printf( "----" );	printf( "\n" );
	float r = 0;  char razm = 'm'; if(t==1 && m>3) razm = 'с'; float ten=0;
	int vs=7; if (t==1) vs=uc;
	for (int i = 0; i < vs; i++)
	{
		if (t == 0) { 
			ten = rezg [m][i]; 
			r = formuls2( ten, i );
			if (i == 4 ) razm = 'c';
		}
		else { 
			ten = rezg [i][m]; 
			r = formuls2( ten, m );
		}
		printf("    %.15s	|	%0.3f	%c	|	%0.2f	\n", name[i], ten, razm, r);
	}printf("\n");
}
int imax(float** rezg, int m, int uc) {
	float maxx = 0; int ma11 = 0;
	for (int i = 0; i < uc; i++) if (formuls2(rezg[i][m], m) > maxx) { 
		maxx = formuls2(rezg[i][m], m); 
		ma11 = i; 
	}
	return ma11;
}
float icum( float** rezg, int m ) {
	float cumm=0;
	for (int i = 0; i < 7; i++) {
		cumm += formuls2( rezg [m][i], i );
	}
	return cumm;
}
int imin(float** rezg, int m, int uc) {
	float minn = 9999999; int ma11 = 0;
	for (int i = 0; i < uc; i++) if (formuls2(rezg[i][m], m) < minn) { 
		minn = formuls2(rezg[i][m], m); 
		ma11 = i; 
	}
	return ma11;
}
float * cas33(float** rezg, int uc, char** name, float * ar) {
	printf("\n");
	printf("*** *** *** *** ***  Итоги состязаний  *** *** *** ***\n");
	printf("---------------------------------------------------------\n");
	printf("	Место	|	Баллы	|	Спортсмен\n");
	printf("---------------------------------------------------------\n");
	//вычисление баллов
	float* fin_b; int* fin;
	fin_b = (float*)malloc(uc * sizeof(int));//место для суммирования баллов
	fin = (int*)malloc(uc * sizeof(int));//порядок участника
	if (fin_b == NULL) { 
		puts("error"); 
		return -1;
	}
	if (fin == NULL) { 
		puts("error"); 
		return -1; 
	}
	for (int i = 0; i < uc; i++)//заполнение новых массивов
	{
		fin[i] = i;
		fin_b[i] = icum(rezg, i);
	}
	sortlr(fin_b, fin, uc); //сортировка
	printf("	");
	for (int i = 0; i < uc; i++) { 
		printf("%d	|", i + 1); 
		printf("	%.0f	|", fin_b[i]);  
		ar [0] += fin_b [i];
		printf("	%s	", name[fin[i]]); 
	
	}//вввывод
	ar[1]=ar[0]/uc; ar [2] = fin_b [uc-1]; ar [3] = fin_b [0];
	return ar;
	free(fin_b); free(fin);
}
void krit(int t, float *ar) {
	char naim[4][13] = { "общее", "среднее", "минимальное", "максимальное" };
	if (t==5) printf("Пропуск так пропуск\n");	
	else printf("Результат запроса  на %s количество очков >>> %0.3f \n",naim[t-1], ar[t-1] );
	
}
char** put_vids( char** vi) {
	FILE* fle;	fle = fopen( "5.txt", "r" );
	char str [20];
	for (int q = 0; q < 7; q++) {
		vi [q] = ( char* ) calloc( 20, sizeof( char ) ); //двумерный массив видов спорта
		fgets( str, sizeof( str ), fle ); strcpy( vi [q], str ); //заполнение значениями
	}	
	return vi;
	fclose( fle );
}