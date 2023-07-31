#pragma once
#include <string>
#include "MyAsyncHttpSession.h"
#include "MyViewInterface.h"
class MyModel
{
public:
	MyModel(): view(nullptr)
	{

	}
	~MyModel()
	{
	}

	void setView(MyViewInterface* aView)
	{
		if(aView)
			view = aView;
	}

	void run();

	std::string response;
	MyViewInterface*  view;
};

