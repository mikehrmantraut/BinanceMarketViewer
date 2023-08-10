#pragma once
#include <JuceHeader.h>
#include <memory>
#include "MyViewInterface.h"
#include "MyModel.h"
#include "Flasher.h"

class MainComponent :
    public juce::Component,
    public juce::TableListBoxModel,
    public juce::AsyncUpdater,
    public MyViewInterface
{
public:
    MainComponent(std::shared_ptr<MyModel> aModel);
    ~MainComponent() override;
    void paint(juce::Graphics&) override;
    void resized() override;
    virtual void handleAsyncUpdate() override;
    virtual void update() override;
    void createTable();

private:
    Flasher flasher;
    std::shared_ptr<MyModel> model;
    juce::TableListBox table;
    juce::Font font{ 28.0f };
    virtual int getNumRows() override;
    virtual void paintRowBackground(juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected) override;
    virtual void paintCell(juce::Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
};