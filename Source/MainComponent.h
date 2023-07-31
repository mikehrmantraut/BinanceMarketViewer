#pragma once
#include <JuceHeader.h>
#include <memory>
#include "MyViewInterface.h"
#include "MyModel.h"
//#include <juce_graphics/juce_graphics.h>
//#include <include_juce_gui_basics.cpp>
//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/json_parser.hpp>
//#include <boost/foreach.hpp>
#include <sstream>
#include <juce_core.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>


//class MyTableModel : public juce::TableListBoxModel
//{
//public:
//    MyTableModel(const std::vector<std::string>& symbols, const std::vector<std::string>& prices)
//        : symbols(symbols), prices(prices)
//    {
//    }
//
//    int getNumRows() override
//    {
//        return static_cast<int>(symbols.size());
//    }
//
//    void paintRowBackground(juce::Graphics& g, int rowNumber, int /*width*/, int /*height*/, bool rowIsSelected) override
//    {
//        if (rowIsSelected)
//            g.fillAll(juce::Colours::lightblue);
//    }
//
//    void paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool /*rowIsSelected*/) override
//    {
//        g.setColour(juce::Colours::black);
//        g.setFont(height * 0.7f);
//
//        if (columnId == 1) // Sembol sütunu
//            g.drawText(symbols[rowNumber], 2, 0, width - 4, height, juce::Justification::centredLeft, true);
//        else if (columnId == 2) // Fiyat sütunu
//            g.drawText(prices[rowNumber], 2, 0, width - 4, height, juce::Justification::centredRight, true);
//    }
//
//private:
//    const std::vector<std::string>& symbols;
//    const std::vector<std::string>& prices;
//};





class MainComponent: 
    public juce::Component,
    public juce::TableListBoxModel,
    public juce::AsyncUpdater,
    public MyViewInterface,
    public juce::Timer
{
public:

    MainComponent(std::shared_ptr<MyModel> aModel);
    ~MainComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& event) override;

    virtual void handleAsyncUpdate() override;

    virtual void update() override;
protected:
    //juce::TableListBox table;
    std::vector<std::string> symbols;
    std::vector<std::string> prices;
    /*std::unique_ptr<MyTableModel> tableModel;*/

private:
    //juce::TableListBox tableListBox;
    std::shared_ptr<MyModel> model;
    juce::TableListBox table;
    juce::Font font{ 14.0f };
    
    /*class MyTableModel : public juce::TableListBoxModel
    {
    public:
        MyTableModel(MainComponent& parentComponent);
        int getNumRows() override;
        void paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
        void paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

    private:
        MainComponent& parentComponent;
    };*/
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent);

    // Inherited via TableListBoxModel
    virtual int getNumRows() override;
    virtual void paintRowBackground(juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
    virtual void paintCell(juce::Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

    // Inherited via Timer
    virtual void timerCallback() override;
};

