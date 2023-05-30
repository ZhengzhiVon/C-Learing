in#include<time.h>
#include"ViewDate.h"
#include"ModelDate.h"

int ModelDate::GetYear() const 
{
	return year;
}
int ModelDate::GetMonth() const 
{
	return month;
}
int ModelDate::GetMday() const
{
	return mday;
}
int ModelDate::GetCurWeek() const
{
	return curweek;
}
int ModelDate::GetOneWeek() const
{
	return oneweek;
}
int ModelDate::GetMdays() const
{
	return mdays;
}

bool ModelDate::Is_Leap() const
{
	return (year % 4 == 0 && year % 100 == 0) || (year % 400 == 0);
}
int ModelDate::GetYM_Day()const
{
	static const int days[] = { 29,31,28,31,30,31,30,31,31,30,31,30,31 };
		//                      0  1  2  3  4  5  6  7  8  9  10 11 12
	int m = month;
	if (2 == m && Is_Leap())
	{
		m = 0;
	}
	return days[m];
}
int ModelDate::GetWeek(int d) const
{
	int c = year / 100;
	int y = year % 100;
	int m = month;
	if (m == 1 || m == 2)
	{
		m += 12;
	}
	return (y + y / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10 + d - 1) % 7;
}

ModelDate::ModelDate()
{
	// memset(this, 0, sizeof(ModelDate)); exit(1);
	Now();
}
ModelDate::~ModelDate()
{

}
void ModelDate::SetView(ViewDate* pv)
{
	pview = pv;
}
void ModelDate::Update()
{
	curweek = GetWeek(mday);
	mdays = GetYM_Day();
	oneweek = GetWeek(1);
	if (pview != nullptr)
	{
		pview->Event(this);
	}
}
void ModelDate::Now()
{
	time_t te;
	tm  tm_node;
	time(&te);
	localtime_s(&tm_node, &te);
	year = tm_node.tm_year + 1900;
	month = tm_node.tm_mon + 1;
	mday = tm_node.tm_mday;
	Update();
	
}
void ModelDate::NextMonth()
{
	if (++month > 12)
	{
		++year;
		month = 1;
	}
	Update();
}
void ModelDate::PrivMonth()
{
	if (--month < 1)
	{
		if (year > 2) --year;
		month = 12;
	}
	Update();
}
void ModelDate::NextYear()
{
	++year;	// month ; mday; 
	Update();
}
void ModelDate::PrevYear()
{
	if (--year < 1) year = 1;
	Update();
}