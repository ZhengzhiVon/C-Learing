#ifndef VIEWDATE_H
#define VIEWDATE_H

class ModelDate;
class ViewDate
{
private:

public:
	ViewDate();
	~ViewDate();
	int Menum();
	void PrintDate(int y, int m, int md, int ow, int mt) const;
	void Event(ModelDate* pmodel);
};
#endif 
