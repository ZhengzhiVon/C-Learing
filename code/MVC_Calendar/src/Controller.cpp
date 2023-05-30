
#include<stdio.h>
#include"ViewDate.h"
#include"ModelDate.h"
#include"Controller.h"

ViewDate* pview;
ModelDate* pmodel;

Controller::Controller() 
	:pview(nullptr), pmodel(nullptr)
{}

Controller::~Controller()
{

}
void Controller::SetView(ViewDate* pv)
{
	pview = pv;
}

void Controller::SetModel(ModelDate* pm)
{
	pmodel = pm;
}

void Controller::Run()
{
	int select = 0;
	do
	{
		select = pview->Menum();
		switch (select)
		{
		case 0: 
			break;
		case 1:
			NextMonth();
			break;
		case 2:
			PrevMonth();
			break;
		case 3:
			NextYear();
			break;
		case 4:
			PrevYear();
			break;
		case 5:
			Now();
			break;
		default:
			printf("select error \n");
			break;
		}

	} while (select != 0);

}
void Controller::Now()
{
	pmodel->Now();
}
void Controller::NextMonth()
{
	pmodel->NextMonth();
}
void Controller::PrevMonth()
{
	pmodel->PrivMonth();
}
void Controller::NextYear()
{
	pmodel->NextYear();
}
void Controller::PrevYear()
{
	pmodel->PrevYear();
}