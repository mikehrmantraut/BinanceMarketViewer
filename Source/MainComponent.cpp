#include <nlohmann/json.hpp>
#include "MainComponent.h"
// juce timer
MainComponent::MainComponent(std::shared_ptr<MyModel> aModel)
{
    model = aModel;
    setSize(800, 800);
    addAndMakeVisible(table);
    createTable();
    model->run();
}
MainComponent::~MainComponent()
{
    model.reset();
}
void MainComponent::paint(juce::Graphics& g)
{
}
void MainComponent::createTable()
{
    table.setModel(this);
    table.setColour(juce::ListBox::outlineColourId, juce::Colours::grey);
    table.setOutlineThickness(1);
    // symbol sutunu
    table.getHeader().addColumn(juce::String("SYMBOL"),
        1,
        400,
        50, 400,
        juce::TableHeaderComponent::defaultFlags);
    // price sutunu
    table.getHeader().addColumn(juce::String("PRICE"),
        2,
        400,
        50, 400,
        juce::TableHeaderComponent::defaultFlags);
}
void MainComponent::resized()
{
    table.setBoundsInset(juce::BorderSize<int>(8));
}
void MainComponent::handleAsyncUpdate()
{
    table.updateContent();
    repaint();
}
void MainComponent::update()
{
    triggerAsyncUpdate();
}
int MainComponent::getNumRows()
{
    return model->getSymbols().size();
}
void MainComponent::paintRowBackground(juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected)
{
}
void MainComponent::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    //degerleri yazdiracagimiz yer
    g.setColour(getLookAndFeel().findColour(juce::ListBox::textColourId));
    g.setFont(font);

    auto price = juce::String(model->getPrices().at(rowNumber));
    auto symbol = juce::String(model->getSymbols().at(rowNumber));


    if (columnId == 1)
    {
        g.drawText(symbol, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
    }
    else if (columnId == 2)
    {
        g.drawText(price, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
        flasher.setNewData(price);
        flasher.flash(g, price, 2, 0, rowNumber); 
    }


    g.setColour(getLookAndFeel().findColour(juce::ListBox::backgroundColourId));
    g.fillRect(width - 1, 0, 1, height);
}
