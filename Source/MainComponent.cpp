#include "MainComponent.h"


MainComponent::MainComponent(shared_ptr<MyModel> aModel)
{
    model = aModel;
    setSize(600, 400);
    
    createTable();
    model->run();
    startTimer(1000);
}

// symbol'un arkaplanini fiyat arttiginda yesil,
// azaldiginda kirmizi renge boyayacak class
class Flasher
{
public:
    Flasher(shared_ptr<MyModel> aModel) : model(aModel) {}

private:
    std::shared_ptr<MyModel> model;
    std::map<size_t, int> flashMap;
};


void MainComponent::createTable()
{
    addAndMakeVisible(table);
    table.setModel(this);
    table.setColour(ListBox::outlineColourId, Colours::grey);
    table.setOutlineThickness(1);
    // symbol sutunu
    table.getHeader().addColumn(String("symbol"),
        1,
        200,
        50, 400,
        TableHeaderComponent::defaultFlags);

    // price sutunu
    table.getHeader().addColumn(String("price"),
        2,
        200,
        50, 400,
        juce::TableHeaderComponent::defaultFlags);
}

MainComponent::~MainComponent()
{
    model.reset();

}
void MainComponent::paint(Graphics& g)
{

}

void MainComponent::resized()
{
    table.setBoundsInset(BorderSize<int>(8));
}

void MainComponent::mouseDown(const MouseEvent& event)
{
    
}

void MainComponent::handleAsyncUpdate()
{
    symbols = model->getSymbols();
    prices = model->getPrices();
    table.updateContent();
    repaint();
}

void MainComponent::update()
{
    // json'i parse etme islemi modele tasindi.
    model->parseData(model->response);
    triggerAsyncUpdate();
}


int MainComponent::getNumRows()
{
    return symbols.size();
}
void MainComponent::paintRowBackground(juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected)
{
}


void MainComponent::paintCell(juce::Graphics&g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    //degerleri yazdiracagimiz yer
    g.setColour(getLookAndFeel().findColour(ListBox::textColourId));
    g.setFont(font);

    
    auto price = String(prices.at(rowNumber));
    auto symbol = String(symbols.at(rowNumber));
    if (columnId == 1)
    {
        g.drawText(symbol, 2, 0, width - 4, height, Justification::centredLeft, true);
    }
    else if (columnId == 2)
    {
        g.drawText(price, 2, 0, width - 4, height, Justification::centredLeft, true);
    }

    g.setColour(getLookAndFeel().findColour(ListBox::backgroundColourId));
    g.fillRect(width - 1, 0, 1, height);    
}

void MainComponent::timerCallback()
{
    model->run();
}

