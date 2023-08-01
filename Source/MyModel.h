#pragma once
#include <string>
#include "MyAsyncHttpSession.h"
#include "MyViewInterface.h"
#include <nlohmann/json.hpp>

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
	
	void parseData(const std::string& jsonData);
	std::map<std::string, std::string> getData() const;
	std::string response;
	MyViewInterface*  view;
	std::map<std::string, std::string> data;
};

