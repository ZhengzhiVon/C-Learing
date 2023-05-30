#include<iostream>
using namespace std;

#include"ModelDate.h"
#include"ViewDate.h"
#include"Controller.h"

class Client
{
public:
	Client():view{}, model{}, contr{}
	{
		contr.SetModel(&model);
		contr.SetView(&view);
		model.SetView(&view);
	}
	~Client() {}
	void Run()
	{
		contr.Run();
	}
private:
	ViewDate view;
	ModelDate model;
	Controller contr;
};
int main()
{
	Client client;
	client.Run();

	return 0;
}
