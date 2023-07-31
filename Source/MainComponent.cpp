#include "MainComponent.h"

// juce timer 

MainComponent::MainComponent(std::shared_ptr<MyModel> aModel)
{
    model = aModel;
    setSize(600, 400);

    addAndMakeVisible(table);
    table.setModel(this);
    table.setColour(juce::ListBox::outlineColourId, juce::Colours::grey);
    table.setOutlineThickness(1);



    // symbol sutunu
    table.getHeader().addColumn(juce::String("symbol"),
        1,
        200,
        50, 400,
        juce::TableHeaderComponent::defaultFlags);
    
    // price sutunu
    table.getHeader().addColumn(juce::String("price"),
        2,
        200,
        50, 400,
        juce::TableHeaderComponent::defaultFlags);
    model->run();
    startTimer(1000);

    //================================================================
    /* TABLO OLUSTURMAK ICIN DENEDIGIM KODLAR*/
    //================================================================
    //table.setModel(tableModel.get());
    //tableModel.reset(new MyTableModel(symbols, prices));
    /*tableModel = std::make_unique<MyTableModel>(symbols, prices);
    table.setModel(tableModel.get());
    table.setHeader(std::make_unique<juce::TableHeaderComponent>());
    addAndMakeVisible(table);*/
    //================================================================
    
    //symbols = model->getSymbols();
    //prices = model->getPrices();
    //tableListBox.setModel(new MyTableModel(*this));
    //addAndMakeVisible(tableListBox);
}

MainComponent::~MainComponent()
{
    model.reset();

}


void MainComponent::paint(juce::Graphics& g)
{

}


void MainComponent::resized()
{
    table.setBoundsInset(juce::BorderSize<int>(8));
}

void MainComponent::mouseDown(const juce::MouseEvent& event)
{
    
}

void MainComponent::handleAsyncUpdate()
{
    table.updateContent();
    repaint();
}

void MainComponent::update()
{
    using json = nlohmann::json;
    // api'den gelen veriler
    std::string all_str = model->response;
    try {
        // json formatina cevirme
        json parsed_json = json::parse(all_str);

        // json formatini kontrol etme
        if (!parsed_json.is_array()) {
            std::cerr << "Error: The JSON is not an array of objects." << std::endl;
            return;
        }
        // parse edilmis json'daki fiyat ve sembolleri vektorlere ekleme
        symbols.clear();
        prices.clear();
        for (const auto& item : parsed_json) {
            if (item.is_object()) {
                symbols.push_back(item["symbol"]);
                prices.push_back(item["price"]);
            }
            else {
                std::cerr << "Error: One of the items is not a JSON object." << std::endl;
                return;
            }
        }
    }
    catch (const json::exception& e) {
        std::cerr << "Error: JSON parsing failed. Reason: " << e.what() << std::endl;
        return;
    }
    triggerAsyncUpdate();
}

int MainComponent::getNumRows()
{
    return symbols.size();
}
void MainComponent::paintRowBackground(juce::Graphics&, int rowNumber, int width, int height, bool rowIsSelected)
{
    //gri-beyaz kolay okunabilir olmasi
}


void MainComponent::paintCell(juce::Graphics&g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    //degerleri yazdiracagimiz yer
    g.setColour(getLookAndFeel().findColour(juce::ListBox::textColourId));
    g.setFont(font);

    
    auto price = juce::String(prices.at(rowNumber));
    auto symbol = juce::String(symbols.at(rowNumber));
    if (columnId == 1)
    {
        g.drawText(symbol, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
    }
    else if (columnId == 2)
    {
        g.drawText(price, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
    }

    g.setColour(getLookAndFeel().findColour(juce::ListBox::backgroundColourId));
    g.fillRect(width - 1, 0, 1, height);    
}

void MainComponent::timerCallback()
{
    model->run();
}

//MainComponent::MyTableModel::MyTableModel(MainComponent& parentComponent)
//    : parentComponent(parentComponent)
//{
//}
//
//int MainComponent::MyTableModel::getNumRows()
//{
//    return static_cast<int>(parentComponent.symbols.size());
//}
//
//void MainComponent::MyTableModel::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
//{
//    if (rowIsSelected)
//        g.fillAll(juce::Colours::lightblue); // Seçili satýrýn rengini ayarlayabilirsiniz
//}
//
//void MainComponent::MyTableModel::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
//{
//    juce::Font font(g.getCurrentFont());
//    font.setHeight(height * 0.7f);
//    g.setFont(font);
//    g.setColour(juce::Colours::black);
//
//    if (columnId == 1) // Ýkinci sütun (fiyatlar)
//    {
//        g.drawText(parentComponent.prices[rowNumber], 2, 0, width - 4, height, juce::Justification::centred, true);
//    }
//    else // Ýlk sütun (kripto paralar)
//    {
//        g.drawText(parentComponent.symbols[rowNumber], 2, 0, width - 4, height, juce::Justification::centred, true);
//    }
//}
