#pragma once
#include <JuceHeader.h>
#include <memory>
#include "MyViewInterface.h"
#include "MyModel.h"
#include <sstream>
#include <juce_core.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <chrono>
#include <thread>



using namespace std;
using namespace juce;

class MainComponent: 
    public Component,
    public TableListBoxModel,
    public AsyncUpdater,
    public MyViewInterface,
    public Timer
{
public:

    MainComponent(std::shared_ptr<MyModel> aModel);
    ~MainComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void mouseDown(const MouseEvent& event) override;
    void paintRowBackground(Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    virtual void handleAsyncUpdate() override;
    virtual void update() override;

protected:
    vector<string> symbols;
    vector<string> prices;
private:
    shared_ptr<MyModel> model;
    TableListBox table;
    Font font{ 14.0f };
    void createTable();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent);
    
    virtual int getNumRows() override;
    virtual void timerCallback() override;
};


