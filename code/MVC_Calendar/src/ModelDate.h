#ifndef MODELDATE_H
#define MODELEATE_H

class ViewDate;

class ModelDate
{
private:
	ViewDate* pview;
private:
	int year;
	int month;
	int mday;
	int curweek; // mday;
	int oneweek; // 1 -> 
	int mdays; // month total;

	void Update();
public:
	int GetYear() const;
	int GetMonth() const;
	int GetMday() const;
	int GetCurWeek() const;
	int GetOneWeek() const;
	int GetMdays() const;
public:

	bool Is_Leap() const;
	int GetYM_Day() const ;
	int GetWeek(int d = 1)const;
public:
	ModelDate();
	~ModelDate();
	void SetView(ViewDate* pv);
	void Now();
	void NextMonth();
	void PrivMonth();
	void NextYear();
	void PrevYear();
};
#endif

