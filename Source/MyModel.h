#pragma once
#include <string>
#include <JuceHeader.h>
#include "MyWebSocketSession.h"
#include "MyViewInterface.h"
#include <nlohmann/json.hpp>
#include <juce_graphics/juce_graphics.h>

class MyModel :
	public juce::Timer,
	public juce::Component

{
public:
	MyModel() : view(nullptr){}
	~MyModel(){}
	void setView(MyViewInterface* aView)
	{
		if (aView)
			view = aView;
	}
	void run();
	const std::vector<std::string>& getSymbols() const;
	const std::vector<std::string>& getPrices() const;
	std::string response;
	MyViewInterface* view;

private:
	juce::TableListBox table;
	std::vector<std::string> symbols;
	std::vector<std::string> prices;
	virtual void timerCallback() override;
	void parseData(std::string response);

};