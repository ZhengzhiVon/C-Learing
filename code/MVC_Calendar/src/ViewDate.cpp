
#include<stdio.h>
#include"ModelDate.h"
#include"ViewDate.h"

ViewDate::ViewDate() {}
ViewDate::~ViewDate() {}

int ViewDate::Menum()
{
	printf("************��ӭʹ��yhping������***************\n");
	printf("*******************��ǰ����********************\n");
	printf("**********   0.  ��0�˳�             **********\n");
	printf("**********   1.  ��ȡ��һ���µ�����  **********\n");
	printf("**********   2.  ��ȡ��һ���µ�����  **********\n");
	printf("**********   3.  ��ȡ��һ���������  **********\n");
	printf("**********   4.  ��ȡ��һ���������  **********\n");
	printf("**********   5.  ��ǰ����            **********\n");
	printf("***********************************************\n");
	int n = 0;
	printf("���������ѡ��-> ");
	scanf_s("%d", &n);
	return n;

}
void ViewDate::PrintDate(int year, int month, int mday,
	int oneweek, int mdays) const
{
	int n = mdays + oneweek;
	int d = 1;
	printf("year : %d month : %d \n", year, month);
	printf("  ��   һ   ��   ��   ��   ��   ��\n");
	for (int i = 1; i <= n; ++i)
	{
		if (i <= oneweek)
		{
			printf("%5c", ' ');
		}
		else
		{
			printf("%5d", d++);
		}
		if (i % 7 == 0) printf("\n");
	}
	printf("\n");

}
void ViewDate::Event(ModelDate* pmodel)
{
	PrintDate(pmodel->GetYear(), pmodel->GetMonth(),
		pmodel->GetMday(), pmodel->GetOneWeek(),
		pmodel->GetMdays());

}