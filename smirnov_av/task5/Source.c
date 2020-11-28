#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <io.h>
#include <omp.h>

/*����������� �������� ��������� ��������� � �������� ������ ������ � �������� ��������, ������������� �� �����������/�������� �������.

������� ������:
���� �� ����������, � ������� ���������� ������������� ����������.
����� ����������.
�������� ������:
��������������� ������ ���� ������ � ��������� �������.
����� ����������.
��������� ������ ������������� ������������ ����������� ������� ����� ���������� � �������� ����������� �������� ������.

��������� ������ ������������� ������ � ������������� ����������� ����������, ������� ��������:
����������� ����� ���� �� ��������� ��������;
����������� ������ ������ ����������;
����������� ��������� ���������������� ������ ������ � ��������� �������.
*/

char path[256]; //������ ���� � �����

struct info //��������� ��� �������� ���������� �� ������ ����������
{
	char* name;
	double time;
};

void print_main_menu() 
{
	printf("1.������ ���� �� ����������\n");
	printf("2.���� ����������\n");
	printf("3.���� �� �������������\n");
	printf("0.�����\n");
}

void create_copy(struct _finddata_t* copy_files, struct _finddata_t* files,int count) //�������� � copy_files files
{
	int i = 0;
	for (i = 0; i < count; i++)
		copy_files[i] = files[i];
}

void get_path()
{
	int i = 0;
	while ((getchar()) != '\n');
	printf("������� ���� �� ����������:");
	gets_s(path, 256);
	for (i = 0; i < 255; i++)
		if (path[i] == "\\")
			path[i] = "/";
	strcat(path, "/");
	strcat(path, "*");
}

void print_sorts()
{
	printf("��������� ������������� ��������� ���� ����������:\n");
	printf("1.���������\n");
	printf("2.�������\n");
	printf("3.���������\n");
	printf("4.��������\n");
	printf("5.�����\n");
	printf("6.�����\n");
	printf("7.���������\n");
}

void guid()
{
	printf("�������� �������:\n");
	printf("1.� ������� ���� ������� \"1\"\n");
	printf("2.������� ���� �� ���������� � ����:\"����:\\�������� �����\\�������� �����\\...\\�������� �����\"\n");
	printf("3.�������� ���������� � ����� ������ �� ����������� ��� �������� �������\n");
	printf("�������������� �������:\n");
	printf("� ����� ��������� ������� ������� � ������������ ���������\n");
}

int count_files(char* path)//������� ���-�� ������
{
	int count = 0;
	struct _finddata_t c_file;
	intptr_t hFile;
	if ((hFile = _findfirst(path, &c_file)) == -1L)
		return -1;
	else
	{
		do {
			if (c_file.attrib & _A_SUBDIR)
				continue;
			count++;
		} while (_findnext(hFile, &c_file) == 0);
	}
	_findclose(hFile);
	return count;
}

void BubbleSort(struct _finddata_t* copy_files, int count)
{
	struct _finddata_t temp;
	int i = 0;
	int j = 0;
	for (i = 0; i < count; i++)
	{
		for (j = count - 1; j > i; j--)
		{
			if (copy_files[j].size < copy_files[j - 1].size)
			{
				temp = copy_files[j];
				copy_files[j] = copy_files[j - 1];
				copy_files[j - 1] = temp;
			}
		}
	}
}

void SelectSort(struct _finddata_t* copy_files, int count)
{
	struct _finddata_t temp;
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0; i < count; i++)
	{
		k = i;
		temp = copy_files[i];
		for (j = i+1; j < count; j++)
		{
			if (copy_files[j].size < temp.size)
			{
				k = j;
				temp = copy_files[j];
			}
		}
		copy_files[k] = copy_files[i];
		copy_files[i] = temp;
	}
}

void InsertSort(struct _finddata_t* copy_files, int count)
{
	struct _finddata_t temp;
	int i = 0;
	int j = 0;
	for (i = 0; i < count; i++)
	{
		temp = copy_files[i];
		for (j = i - 1; j >= 0 && temp.size < copy_files[j].size; j--)
			copy_files[j + 1] = copy_files[j];
		copy_files[j + 1] = temp;
	}
}

void merge(struct _finddata_t* copy_files, int left, int middle, int right)
{
	int pos1 = left;
	int pos2 = middle + 1;
	int pos3 = 0;
	int size = right - left + 1;
	struct _finddata_t* temp = (struct _finddata_t*)malloc(sizeof(struct _finddata_t) * (size));
	while (pos1 <= middle && pos2 <= right)
	{
		if (copy_files[pos1].size < copy_files[pos2].size)
			temp[pos3++] = copy_files[pos1++];
		else
			temp[pos3++] = copy_files[pos2++];
	}
	while (pos2 <= right)
		temp[pos3++] = copy_files[pos2++];
	while (pos1 <= middle)
		temp[pos3++] = copy_files[pos1++];
	for (pos3 = 0;  pos3< size; pos3++)
		copy_files[left + pos3] = temp[pos3];

	free(temp);
}

void MergeSort(struct _finddata_t* copy_files,int left,int right)
{
	int middle;

	if (left < right)
	{
		middle = (left + right) / 2;
		MergeSort(copy_files, left, middle);
		MergeSort(copy_files, middle + 1, right);
		merge(copy_files,left,middle,right);
	}
}

void QuickSort(struct _finddata_t* copy_files, int count)
{
	int i=0;
	int j = count - 1;
	struct _finddata_t temp;
	struct _finddata_t mid;
	mid = copy_files[count >> 1];

	do {
		while (copy_files[i].size < mid.size)
			i++;
		while (copy_files[j].size > mid.size)
			j--;
		if (i <= j)
		{
			temp = copy_files[i];
			copy_files[i] = copy_files[j];
			copy_files[j] = temp;
			i++;
			j--;
		}
	} while (i <= j);
	if (j > 0)
		QuickSort(copy_files, j);
	if (count > i)
		QuickSort(copy_files + i, count - i);
}

int increment(long inc[], int count)
{
	int p1;
	int p2;
	int p3;
	int	s;

	p1 = p2 = p3 = 1;
	s = -1;
	do {
		if (++s % 2) {
			inc[s] = 8 * p1 - 6 * p2 + 1;
		}
		else {
			inc[s] = 9 * p1 - 9 * p3 + 1;
			p2 *= 2;
			p3 *= 2;
		}
		p1 *= 2;
	} while (3 * inc[s] < count);
	return s > 0 ? --s : 0;
}

void ShellSort(struct _finddata_t* copy_files, int count)
{
	struct _finddata_t temp;
	int inc;
	int i;
	int j;
	int seq[40] = {0};
	int s;

	s = increment(seq, count);
	while (s >= 0)
	{
		inc = seq[s--];

		for (i = inc; i < count; i++)
		{
			temp = copy_files[i];
			for (j = i - inc; (j >= 0) && (copy_files[j].size > temp.size); j -= inc)
				copy_files[j + inc] = copy_files[j];
			copy_files[j + inc] = temp;
		}
	}
}

void CountingSort(struct _finddata_t* copy_files,int count)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int size = 0;
	int max = copy_files[0].size;
	int min = copy_files[0].size;
	int* sizes;
	struct _finddata_t temp;

	for (i = 0; i < count; i++)
	{
		if (max < copy_files[i].size)
			max = copy_files[i].size;
		if (min > copy_files[i].size)
			min = copy_files[i].size;
	}
	size = max - min + 1;
	sizes = (int*)malloc(sizeof(int) * size);
	for (i = 0; i < size; i++)
		sizes[i] = 0;
	for (i = 0; i < count; i++)
		sizes[copy_files[i].size - min]++;
	for (i = 0; i < size; i++)
	{
		while (sizes[i] > 0)
		{
			for (j = 0; j < count; j++)
			{
				if (copy_files[j].size == min + i)
				{
					temp = copy_files[j];
					copy_files[j] = copy_files[k];
					copy_files[k] = temp;
					k++;
					sizes[i]--;
				}
			}
		}
	}
	free(sizes);
}

void main(void)
{
	int count_of_sorts = 0; //���-�� �������������� ����������(��� ���������� ��������� sorts) 
	int choice = 0;//����� ����������
	int ch1 = 0; //������������ ��� ������� ����� ����������
	int pm1 =0;//����� � ����
	int type = 0;//��� ���������� �� ����������� ��� ��������
	int count_of_files = 0;
	int i = 0;
	int j = 0;
	struct info* sorts = (struct info*)malloc(sizeof(struct info) * 14); // 14 ������ ��� ���� �� ���-�� ����� ������������ ������ ���������� �� 2 ����
	int count = -1; //������������ ��� �������� �� ������� ������ � ���������� � ������������ ���������� ����
	double t1, t2;
	struct _finddata_t* files; //�������� ���������, ���� ����������� ��� ������ � ������
	struct _finddata_t* copy_files;//���������, ������� ������������ � �����������(����� files)
	intptr_t hFile;
	setlocale(LC_ALL, "Russian");
	print_main_menu();
	scanf_s("%d", &pm1);
	system("cls");
	while (pm1 != 0)
	{
		switch (pm1)
		{
		case 1:
			while (count == -1)
			{
				get_path();
				count = count_files(path);
				if (count == -1)
				{
					printf("������ ����� ���� ��� � ���������� ����������� �����, ���������� ��� ���, ��� ����� ���� ������� Enter");
					path[0] = '\0';
				}
			}
			files = (struct _finddata_t*)malloc(count * sizeof(struct _finddata_t));
			hFile = _findfirst(path, &files[0]);
			printf("Listing of .c files\n\n");
			printf("FILE         DATE %24c   SIZE\n", ' ');
			printf("----         ---- %24c   ----\n", ' ');
			do {
				if (files[i].attrib & _A_SUBDIR)
					continue;
				char buffer[30];
				ctime_s(buffer, _countof(buffer), &files[i].time_write);
				printf("%-12.12s %.24s %10ld\n", files[i].name, buffer, files[i].size);
				i++;
				count_of_files++;
			} while (_findnext(hFile, &files[i]) == 0);
			_findclose(hFile);
			copy_files = (struct _finddata_t*)malloc(count * sizeof(struct _finddata_t));//�������� ������ ��� ����� �������� ������
			do {
				create_copy(copy_files, files, count);
				printf("�������� ����������:\n");
				printf("1-���������\n");
				printf("2-�������\n");
				printf("3-���������\n");
				printf("4-��������\n");
				printf("5-�����\n");
				printf("6-�����\n");
				printf("7-���������\n");
				scanf_s("%d", &choice);
				while ((choice > 7) || (choice < 1))
				{
					printf("������ ������ ����������, ���������� ��� ���: ");
					scanf_s("%d", &choice);
				}
				system("cls");
				switch (choice)
				{
				case 1:
					printf("�� ������� ���������� \"���������\"\n");
					t1 = omp_get_wtime();
					BubbleSort(copy_files, count);
					t2 = omp_get_wtime();
					sorts[count_of_sorts].name = (char*)malloc(sizeof(char) * 15);
					sorts[count_of_sorts].name = "���������";
					sorts[count_of_sorts].time = t2-t1;
					break;
				case 2:
					printf("�� ������� ���������� \"�������\"\n");
					t1 = omp_get_wtime();
					SelectSort(copy_files, count);
					t2 = omp_get_wtime();
					sorts[count_of_sorts].name = (char*)malloc(sizeof(char) * 15);
					sorts[count_of_sorts].name = "�������";
					sorts[count_of_sorts].time = t2 - t1;
					break;
				case 3:
					printf("�� ������� ���������� \"���������\"\n");
					t1 = omp_get_wtime();
					InsertSort(copy_files, count);
					t2 = omp_get_wtime();
					sorts[count_of_sorts].name = (char*)malloc(sizeof(char) * 15);
					sorts[count_of_sorts].name = "���������";
					sorts[count_of_sorts].time = t2 - t1;
					break;
				case 4:
					printf("�� ������� ���������� \"��������\"\n");
					t1 = omp_get_wtime();
					MergeSort(copy_files, 0, count - 1);
					t2 = omp_get_wtime();
					sorts[count_of_sorts].name = (char*)malloc(sizeof(char) * 15);
					sorts[count_of_sorts].name = "���������";
					sorts[count_of_sorts].time = t2 - t1;
					break;
				case 5:
					printf("�� ������� ���������� \"�����\"\n");
					t1 = omp_get_wtime();
					QuickSort(copy_files, count);
					t2 = omp_get_wtime();
					sorts[count_of_sorts].name = (char*)malloc(sizeof(char) * 15);
					sorts[count_of_sorts].name = "�����";
					sorts[count_of_sorts].time = t2 - t1;
					break;
				case 6:
					printf("�� ������� ���������� \"�����\"\n");
					t1 = omp_get_wtime();
					ShellSort(copy_files, count);
					t2 = omp_get_wtime();
					sorts[count_of_sorts].name = (char*)malloc(sizeof(char) * 15);
					sorts[count_of_sorts].name = "�����";
					sorts[count_of_sorts].time = t2 - t1;
					break;
				case 7:
					printf("�� ������� ���������� \"���������\"\n");
					t1 = omp_get_wtime();
					CountingSort(copy_files, count);
					t2 = omp_get_wtime();
					sorts[count_of_sorts].name = (char*)malloc(sizeof(char) * 15);
					sorts[count_of_sorts].name = "���������";
					sorts[count_of_sorts].time = t2 - t1;
					break;
				}
				printf("�������� ��� ����������:1-�� ����������� 2-�� ��������\n");
				scanf_s("%d", &type);
				while (type != 1 && type != 2)
				{
					printf("������ ������ ���� ����������, ���������� ��� ���: ");
					scanf_s("%d", &type);
				}
				printf("Listing of .c files\n\n");
				printf("FILE       %10c    SIZE\n", ' ');
				printf("----       %10c    ----\n", ' ');
				if (type == 1)
				{
					for (i = 0; i < count; i++)
						printf("%-12.12s %15ld\n", copy_files[i].name, copy_files[i].size);
				}
				else if (type == 2)
				{
					for (i = count - 1; i >= 0; i--)
						printf("%-12.12s %15ld\n", copy_files[i].name, copy_files[i].size);
				}
				printf("����� ���������� ���������:%lf (���)\n", (t2 - t1));
				printf("���������� ������:%d\n", count_of_files);
				printf("������ �������� ����������?1-�� 2-���\n");
				scanf_s("%d", &ch1);
				while (ch1 != 1 && ch1 != 2)
				{
					printf("������ ����� ���������� ��� ���\n");
					scanf_s("%d", &ch1);
				}
				count_of_sorts++;
			} while (ch1 != 2);
			printf("����������:   �����(���):\n");
			for (i = 0; i < count_of_sorts; i++)
				printf("%-12.12s  %lf\n", sorts[i].name, sorts[i].time);
			printf("��� ���������� ������ ��������� ������� 0\n");
			scanf_s("%d", &pm1);
			free(sorts);
			free(copy_files);
			free(files);
			return;
		case 2:
			print_sorts();
			printf("��� ����������� � ������� ���� ������� 0\n");
			scanf_s("%d", &pm1);
			system("cls");
			if (pm1 == 0)
			{
				print_main_menu();
				scanf_s("%d", &pm1);
			}
			break;
		case 3:
			guid();
			printf("��� ����������� � ������� ���� ������� 0\n");
			scanf_s("%d", &pm1);
			if (pm1 == 0)
			{
				print_main_menu();
				scanf_s("%d", &pm1);
			}
			break;
		case 0:
			return;
		default:
			printf("������ ������ � ����, ���������� ��� ���\n");
			print_main_menu();
			scanf_s("%d", &pm1);
			system("cls");
			break;
		}
	}
	system("pause");
}