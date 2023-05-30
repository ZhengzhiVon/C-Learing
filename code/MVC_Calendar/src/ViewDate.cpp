
#include<stdio.h>
#include"ModelDate.h"
#include"ViewDate.h"

ViewDate::ViewDate() {}
ViewDate::~ViewDate() {}

int ViewDate::Menum()
{
	printf("************欢迎使用yhping的日历***************\n");
	printf("*******************当前日历********************\n");
	printf("**********   0.  按0退出             **********\n");
	printf("**********   1.  获取下一个月的日历  **********\n");
	printf("**********   2.  获取上一个月的日历  **********\n");
	printf("**********   3.  获取下一个年的日历  **********\n");
	printf("**********   4.  获取上一个年的日历  **********\n");
	printf("**********   5.  当前日历            **********\n");
	printf("***********************************************\n");
	int n = 0;
	printf("请输入你的选择-> ");
	scanf_s("%d", &n);
	return n;

}
void ViewDate::PrintDate(int year, int month, int mday,
	int oneweek, int mdays) const
{
	int n = mdays + oneweek;
	int d = 1;
	printf("year : %d month : %d \n", year, month);
	printf("  日   一   二   三   四   五   六\n");
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