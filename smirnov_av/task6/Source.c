#define _CRT_SECURE_NO_WARNINGS
#define PI 3.1415926535
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>

typedef struct
{
	double res; //��������
	double accuracy; //��������
	double reference; //������
	double differ; //��������
	int n; //���������� ��������� � ����������
}data_f;

void print_functions()
{
	printf("�������� �������:\n");
	printf("1)Sin(x)\n");
	printf("2)Cos(x)\n");
	printf("3)Exp(x)\n");
	printf("4)Arctg(x)\n");
	printf("5)Arcctg(x)\n");
}

void printf_result(data_f result)
{
	printf("����������� ��������: %lf\n", result.res);
	printf("��������� ��������: %lf\n", result.reference);
	printf("�������: %lf\n", result.differ);
	printf("���������� ���������: %d\n", result.n);
}

data_f TSin(double x, double accurancy, int n)
{
	data_f function;
	int i = 0;
	x = x * PI / 180;
	double reference = sin(x);
	double result = x;
	double temp = x;
	int count = 1;

	for (i = 1; fabs(result - reference) > accurancy && i < n; i++)
	{
		temp *= (-1.0) * (x * x) / ((2 * i) * (2 * i + 1));
		result += temp;
		count++;
	}
	function.res = result;
	function.differ = fabs(result - reference);
	function.accuracy = accurancy;
	function.reference = reference;
	function.n = count;
	return function;
}

data_f TCos(double x, double accurancy, int n)
{
	data_f function;
	int i = 0;
	x = x * PI / 180;
	double reference = cos(x);
	double result = 1;
	double temp = 1;
	int count = 1;

	for (i = 1; fabs(result - reference) > accurancy && i < n; i++)
	{
		temp *= (-1.0) * (x * x) / (2 * i * (2 * i - 1));
		result += temp;
		count++;
	}
	function.res = result;
	function.differ = fabs(result - reference);
	function.accuracy = accurancy;
	function.reference = reference;
	function.n = count;
	return function;
}

data_f TExp(double x, double accurancy, int n)
{
	data_f function;
	int i = 0;
	double reference = exp(x);
	double result = 1;
	double temp = 1;
	int count = 1;

	for (i = 1; fabs(result - reference) > accurancy && i < n; i++)
	{
		temp *= 1.0 * x / i;
		result += temp;
		count++;
	}
	function.res = result;
	function.differ = fabs(result - reference);
	function.accuracy = accurancy;
	function.reference = reference;
	function.n = count;
	return function;
}

data_f TArctg(double x, double accurancy, int n)
{
	data_f function;
	int i = 0;
	double reference = atan(x);
	double result = x;
	double temp = x;
	int count = 1;

	for (i = 1; fabs(result - reference) > accurancy && i < n; i++)
	{
		temp *= (-1.0) * (x * x) * (2 * (i - 1) + 1) / (2 * i + 1);
		result += temp;
		count++;
	}
	function.res = result * 180 / PI;
	function.differ = fabs(result - reference);
	function.accuracy = accurancy;
	function.reference = reference * 180 / PI;
	function.n = count;
	return function;
}

data_f TArcctg(double x, double accurancy, int n)
{
	data_f function = TArctg(x, accurancy, n); //���������� ����������� ��� ������ �����
	double reference = PI / 2 - atan(x); //������
	double result = PI / 2 - function.res * PI / 180; //���������� �������� ����������� � �������������
	function.res = result * 180 / PI; //�������� ������������ 
	function.differ = fabs(result - reference); //������� � ���������
	function.reference = reference * 180 / PI; //������
	return function;
}


data_f(*select())() //����� �������
{
	int choice;
	data_f(*funct[])(double x, double accurancy, int n) = { TSin, TCos, TExp, TArctg, TArcctg };

	print_functions();
	scanf_s("%d", &choice);
	while (choice > 5 && choice < 1)
	{
		printf("������ ������ �������, ���������� ��� ���\n");
		scanf_s("%d", &choice);
	}
	return funct[choice - 1];
}

void single_mode()
{

	double x; //�����
	double accurancy; //��������
	int n; //���������� ���������
	data_f result; // ��������� � ����������� ���������
	data_f(*choice)();//�������� ������ �� �������

	choice = select();
	if (choice == TArctg || choice == TArcctg)
	{
		printf("����� � ������� ����� ��������� ��������(|x|<=1): ");
		scanf_s("%lf", &x);
		while (x < -1 || x>1)
		{
			printf("|x|<=1, ���������� ��� ���:");
			scanf_s("%lf", &x);
		}
	}
	else if (choice == TSin || choice == TCos)
	{
		printf("�������� ����(� ��������): ");
		scanf_s("%lf", &x);
	}
	else
	{
		printf("����� � ������� ����� ��������� ��������: ");
		scanf_s("%lf", &x);
	}
	printf("\n�������� (>= 0.000001): ");
	scanf_s("%lf", &accurancy);
	while (accurancy < 0.000001)
	{
		printf("������� ��������� ��������, ���������� ��� ���:");
		scanf_s("%lf", &accurancy);
	}
	printf("\n����� ��������� ���� (N - �� 1 �� 1000): ");
	scanf_s("%d", &n);
	while (n < 1 || n>1000)
	{
		printf("������ ������ ����� ��������� ����, ���������� ��� ���:");
		scanf_s("%d", &n);
	}
	result = choice(x, accurancy, n);
	printf_result(result);
}


void serial_mode()
{
	double x;
	int i = 0;
	int n;
	data_f result; // ��������� � ����������� ���������
	data_f(*choice)();//�������� ������ �� �������

	choice = select();
	if (choice == TArctg || choice == TArcctg)
	{
		printf("����� � ������� ����� ��������� ��������(|x|<=1): ");
		scanf_s("%lf", &x);
		while (x < -1 || x>1)
		{
			printf("|x|<=1, ���������� ��� ���:");
			scanf_s("%lf", &x);
		}
	}
	else if (choice == TSin || choice == TCos)
	{
		printf("�������� ����(� ��������): ");
		scanf_s("%lf", &x);
	}
	else
	{
		printf("����� � ������� ����� ��������� ��������: ");
		scanf_s("%lf", &x);
	}
	printf("\n����� ��������� ���� (N - �� 1 �� 25): ");
	scanf_s("%d", &n);
	while (n < 1 || n>25)
	{
		printf("������ ������ ����� ��������� ����, ���������� ��� ���:");
		scanf_s("%d", &n);
	}
	printf("N \t\t\t");
	printf("�������� �������\t\t\t\t");
	printf("������� ����� ��������� ���������\n");
	for (i = 1; i <= n; i++)
	{
		result = choice(x, 0.00000000000000001, i); // 2 �������� - ��������, ����� ����������� ������� fabs(result - reference) > accurancy
		printf("%-2d\t %30.7lf           %40.7lf\n", i, result.res, result.differ);
	}

}

void main()
{
	setlocale(LC_ALL, "Russian");
	int mode = 3;

	while (mode != 0)
	{
		printf("�������� ����� ������:\n");
		printf("1)����������� ������ ������� � �������� �����\n");
		printf("2)�������� �����������\n");
		scanf_s("%d", &mode);
		while (mode != 1 && mode != 2)
		{
			printf("������ ������ ������, ���������� ��� ���:");
			scanf_s("%d", &mode);
		}
		switch (mode)
		{
		case 1:
			single_mode();
			break;
		case 2:
			serial_mode();
			break;
		}
		printf("������ �������� �����? 1-�� 0-���\n");
		scanf_s("%d", &mode);
		while (mode != 1 && mode!=0)
		{
			printf("������ ������ ���������� ��� ���\n");
			scanf_s("%d", &mode);
		}
	}
	system("pause");
}