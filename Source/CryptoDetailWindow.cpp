#include "CryptoDetailWindow.h"
#include "data_listener.h"
#include <map>

CryptoDetailWindow::CryptoDetailWindow(
    std::shared_ptr<MyModel> aModel,
    juce::String cryptoSymbol): juce::DocumentWindow(cryptoSymbol,
        juce::Desktop::getInstance().getDefaultLookAndFeel()
        .findColour(juce::ResizableWindow::backgroundColourId),
        DocumentWindow::allButtons)
{
    model = aModel;
    selectedSymbol = cryptoSymbol;
    selectedData = {};
    //#if JUCE_IOS || JUCE_ANDROID
    //    setFullScreen(true);
    //#else
    //  setResizable(true, true);
    //  centreWithSize(getWidth(), getHeight());
    //#endif
    
    setResizable(true, true);
    setResizeLimits(300, 300, 1000, 1000);
    centreWithSize(700, 500);

    setVisible(true);
    createTable();
    setUsingNativeTitleBar(true);
    setContentOwned(&table, true);
}

CryptoDetailWindow::~CryptoDetailWindow()
{
    model.reset();
}
void CryptoDetailWindow::resized()
{

}

void CryptoDetailWindow::createTable()
{
    numRows = 1;
    table.setModel(this);
    table.setBounds(0, 20, 700, 150);
    table.setColour(juce::ListBox::outlineColourId, juce::Colours::grey);
    table.setOutlineThickness(1);
    table.getHeader().addColumn(juce::String("Symbol"),1, 100, juce::TableHeaderComponent::defaultFlags);
    table.getHeader().addColumn(juce::String("Close"),2,100 ,juce::TableHeaderComponent::defaultFlags);
    table.getHeader().addColumn(juce::String("Open"),3,100,juce::TableHeaderComponent::defaultFlags);
    table.getHeader().addColumn(juce::String("High"),5,100,juce::TableHeaderComponent::defaultFlags);
    table.getHeader().addColumn(juce::String("Low"),4,100,juce::TableHeaderComponent::defaultFlags);
    table.getHeader().addColumn(juce::String("TotTrade"),6,100,juce::TableHeaderComponent::defaultFlags);
    table.getHeader().addColumn(juce::String("TotQuote"),7,100,juce::TableHeaderComponent::defaultFlags);
    
    DocumentWindow::setVisible(true);

}

void CryptoDetailWindow::closeButtonPressed()
{
    DocumentWindow::setVisible(false);
    // allocate edilen pencere silinmezse leak verir
    delete this;

}

void CryptoDetailWindow::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour(getLookAndFeel().findColour(juce::ListBox::textColourId));
    g.setFont(font);
                    
    std::map<std::string, MarketData> data = model->getData();
    //std::advance arastir
    const std::string& symbol = selectedSymbol.toStdString();
    const MarketData& selectedData = data[symbol];
    auto closePrice = selectedData.close;
    auto lowPrice = selectedData.low;
    auto highPrice = selectedData.high;
    auto openPrice = selectedData.open;
    auto totalTrade = selectedData.totalTrade;
    auto totalQuote = selectedData.totalQuote;

    if(columnId == 1) {
        g.drawText(symbol, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
    }
    else if (columnId == 2){
        g.drawText(closePrice, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
    }
    else if (columnId == 3){
        g.drawText(openPrice, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
    }
    else if (columnId == 4){
        g.drawText(lowPrice, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
    }
    else if (columnId == 5)
    {
        g.drawText(highPrice, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
    }
    else if (columnId == 6)
    {
        g.drawText(totalTrade, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
    }
    else if (columnId == 7)
    {
        g.drawText(totalQuote, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
    }
    
    g.setColour(getLookAndFeel().findColour(juce::ListBox::backgroundColourId));
    g.fillRect(width - 1, 0, 1, height);
}

void CryptoDetailWindow::handleAsyncUpdate()
{
    table.updateContent();
    table.repaint();
}
void CryptoDetailWindow::update()
{
    triggerAsyncUpdate();
}

int CryptoDetailWindow::getNumRows() {
    return numRows;
}

void CryptoDetailWindow::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
}
