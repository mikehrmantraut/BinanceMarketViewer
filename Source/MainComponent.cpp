#include "MainComponent.h"
MainComponent::MainComponent(std::shared_ptr<MyModel> aModel)
{
    model = aModel;
    setSize(800, 800);
    addAndMakeVisible(table);
    createTable();
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
    table.getHeader().addColumn(juce::String("SYMBOL"),
        1,400,50, 400,
        juce::TableHeaderComponent::defaultFlags);
    table.getHeader().addColumn(juce::String("PRICE"),
        2,
        400,
        50, 400,
        juce::TableHeaderComponent::defaultFlags);
}

void MainComponent::resized(){
    table.setBoundsInset(juce::BorderSize<int>(8));
}
void MainComponent::handleAsyncUpdate(){
    table.updateContent();
    repaint();
}
void MainComponent::update(){
    triggerAsyncUpdate();
}
int MainComponent::getNumRows(){
    
    int numRows = model->getMainComponentData().size();
    return numRows;
}

void MainComponent::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    auto alternateColour = getLookAndFeel().findColour(juce::ListBox::backgroundColourId)
        .interpolatedWith(getLookAndFeel().findColour(juce::ListBox::textColourId), 0.03f);
    if (rowIsSelected)
        g.fillAll(juce::Colours::lightblue);
    else if (rowNumber % 2)
        g.fillAll(alternateColour);
}
void MainComponent::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour(getLookAndFeel().findColour(juce::ListBox::textColourId));
    g.setFont(font);

    std::vector<SymbolData> dataVector = model->getMainComponentData();

    auto symbol = juce::String(dataVector.at(rowNumber).symbol);
    auto price = juce::String(dataVector.at(rowNumber).currentPrice);

    if (columnId == 1){
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

void MainComponent::cellDoubleClicked(int rowNumber, int columnId, const juce::MouseEvent&){
    auto data = model->getMainComponentData();
    auto it = std::next(data.begin(), rowNumber);
    const std::string& cryptoSymbol = it->symbol;
    auto juceSymbol = juce::String(cryptoSymbol);
    new CryptoDetailWindow(model, juceSymbol);
    
}