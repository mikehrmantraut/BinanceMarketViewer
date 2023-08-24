#pragma once
#include <string>
#include <JuceHeader.h>
#include "MyWebSocketSession.h"
#include "MyViewInterface.h"
#include <nlohmann/json.hpp>
#include <juce_graphics/juce_graphics.h>
#include <algorithm>
#include <map>
#include <iostream>
#include "data_listener.h"

// headeri olmayan dosyalardan kullanmak istedigimiz degiskeni
// kullanabiliriz (extern ile)
// dll'lerde de kullanilir.

extern MyWebSocketSession* g_ws;

struct MarketData
{
	std::string close;
	std::string open;
	std::string low;
	std::string high;
	std::string totalTrade;
	std::string totalQuote;
};

struct SymbolData
{
	std::string symbol;
	std::string currentPrice;
};

class MyModel :
	public data_listener
{
public:
	MyModel() : view(nullptr), data()
	{
		auto size = data.size();
		::g_ws->addListener(this);
	}
	~MyModel(){}
	void setView(MyViewInterface* aView) {
		if (aView)
			view = aView;
	}
	std::vector<SymbolData> getMainComponentData();
	virtual void onDataReceived(const std::string &message ) override;
	std::map<std::string, MarketData>getData();

private:
	void parseData(const std::string& response);

private:
	juce::TableListBox table;
	MyViewInterface* view;
	std::map<std::string, MarketData> data;


	
};