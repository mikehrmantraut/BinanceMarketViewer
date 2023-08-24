#pragma once
#include <JuceHeader.h>
#include <juce_graphics/juce_graphics.h>
#include "MyModel.h"

class CryptoDetailWindow :
	public juce::DocumentWindow,
    public juce::TableListBoxModel,
	public juce::AsyncUpdater,
	public MyViewInterface
{
public:
	CryptoDetailWindow(std::shared_ptr<MyModel> aModel, juce::String cryptoSymbol);
	~CryptoDetailWindow();
	void resized() override;
	virtual void handleAsyncUpdate() override;
	virtual void update() override;
	void createTable();
	void closeButtonPressed() override;
private:
	std::shared_ptr<MyModel> model;
	juce::TableListBox table;
	juce::String selectedSymbol;
	MarketData selectedData;
	juce::Font font{15.0f};
	size_t numRows = 0;
private:
	juce::TextButton startRobotButton;
	juce::TextButton stopRobotButton;
	virtual int getNumRows() override;
	virtual void paintRowBackground(juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
	virtual void paintCell(juce::Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CryptoDetailWindow);
};