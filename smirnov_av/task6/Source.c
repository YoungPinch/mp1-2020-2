#include <stdio.h>

#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <io.h>
#include <omp.h>

void print_main_menu()
{
	printf("1.������ ���� �� ����������\n");
	printf("2.���� �� �������������\n");
	printf("3.���� ����������\n");
	printf("0.�����\n");
}
void guid()
{
	printf("3421321321\n");
	printf("��� ����������� � ������� ���� ������� 0");
}

struct info
{
	char* name;
	double time;
};

void main()
{
	setlocale(LC_ALL, "Russian");
	int pm1 = 0;
	struct info* sort = (struct info*)malloc(sizeof(struct info) * 10);
	sort[0].name = (char*)malloc(sizeof(char) * 15);
	sort[0].name = "�������";
	sort[0].time = 0.003 - 0.002;
	printf("%s  %lf", sort[0].name,sort[0].time);
	system("pause");

}