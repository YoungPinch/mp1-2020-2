#include <stdio.h>
#include <locale.h>

/*������ �����:
��������� ������ ������ �� ��� ������� h �� 180 �� 220 ��, ������� w �� 80 �� 120 �� � �������� 5 ��,
��� �������� �� ��� ������� h, �������� d �� 50 �� 90 �� � �������� 15 ��,
��������� ������� � ������ ������ �� ��� ������� w, �������� d � �������� 15 ��,
��� ��������� ����� �� ������ ������� h, ����� ������� w � �������� 1 ��,
���������� ����� � ����� ����� ������ 40 �� �� ���.
������, ��� �������� ��������� ���, ��� � ������, ����� ����� ����� � �����������.
*/

void main()
{
	setlocale(LC_ALL, "Russian");
	const double p_dvp = 0.00082;	//��/��^3  
	const double p_dsp = 0.00072;	//��/��^3 
	const double p_wood = 0.00081;	//��/��^3 
	double high, width, t_back = 0.5;	//������ ������(���) h = 180-220cm w = 80 - 120cm t1(������� ������ ������)
	double depth, t_side = 1.5, t_doors = 1;	//��������(���) + �����(������) h =180-220 d = 50-90(�������) t2(������� �������) t3(������� �����)
	double sum_m, m_back, m_side, m_roofs, m_doors, m_shelf;
	int quantity;

	printf("������� ������(h)(180-220��) ��������� ������ ������ � �� ������(w)(80-120cm): ");
	scanf_s("%lf %lf", &high, &width);

	if ((high <= 220) && (high >= 180) && (width >= 80) && (width <= 120))
	{
		printf("������� �������(50-90cm) ��������: ");
		scanf_s("%lf", &depth);
		if ((depth >= 50) && (depth <= 90))
		{
			quantity = (high - 3) / 41.5; //���-�� �����, ������� ������ � ���� (����� ���-��)
			m_back = p_dvp * high * width * t_back;//����� ������ ������ 
			m_side = p_dsp * 2 * (high - 3) * depth * t_side;//����� �������
			m_roofs = p_dsp * 2 * width * depth * t_side;//����� ������
			m_doors = p_wood * high * width * t_doors; //����� ������ 
			m_shelf = p_dsp * quantity * (t_side * (width - 2 * t_side) * depth); //����� �����
			sum_m = m_back + m_side + m_roofs + m_doors + m_shelf;

			printf("����� ����� � �� = %lf", sum_m);
		}
		else("������� ������� ��� ���������");
	
	}
	else printf("������ ��� ������ �� ������ � �������� ��������\n");

	scanf_s("%lf", &high);
}