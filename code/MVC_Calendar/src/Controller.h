#ifndef CONTROLLER_H
#define CONTROLLER_H
class ViewDate;
class ModelDate;

class Controller
{
private:
	ViewDate* pview;
	ModelDate* pmodel;
public:
	Controller();
	~Controller();
	void SetView(ViewDate* pv);
	void SetModel(ModelDate* pm);

	void Run();
	void Now();
	void NextMonth();
	void PrevMonth();
	void NextYear();
	void PrevYear();
};
#endif 
