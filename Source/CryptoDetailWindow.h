#pragma once
#include <JuceHeader.h>
#include <juce_graphics/juce_graphics.h>
#include "MyModel.h"
class CryptoDetailWindow : public juce::DocumentWindow
{
public:
	CryptoDetailWindow(const juce::String& cryptoName, const juce::String& cryptoPrice);
	//void createTable();
	void closeButtonPressed() override;
private:
	std::shared_ptr<MyModel> model;
	//juce::TableListBox table;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CryptoDetailWindow);
};