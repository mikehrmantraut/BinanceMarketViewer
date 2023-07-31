#include "MainComponent.h"

MainComponent::MainComponent(std::shared_ptr<MyModel> aModel)
{
    model = aModel;
    setSize(1000, 800);
    
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
}

MainComponent::~MainComponent()
{
    model.reset();

}


void MainComponent::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setFont(juce::Font(16.0f));
    g.setColour(juce::Colours::white);

    // ====================================================================================================
    /* JSON PARSE ICIN DENEDIGIM KODLAR */
    // ====================================================================================================
    
    //std::string part_of_str = model->response.substr(0, 10);
    //boost::property_tree::ptree pt;
    //std::istringstream iss(model->response.c_str());
    //boost::property_tree::read_json(iss, pt);
    //juce::String price = casted_str.get<std::string>("price");
    //std::vector<juce::String> symbols;
    //try {
    //    juce::String all_str{ model->response.c_str()};
    //    boost::property_tree::ptree pt;
    //    std::istringstream iss(all_str.toStdString());
    //    boost::property_tree::read_json(iss, pt);

    //    for (const auto& item : pt) {
    //        juce::String symbol = item.second.get<std::string>("symbol");
    //        symbols.push_back(symbol);
    //    }
    //    if (!symbols.empty()) {
    //        g.drawText(symbols[0], getLocalBounds(), juce::Justification::centred, true);
    //    }
    //}
    //catch (const boost::property_tree::json_parser::json_parser_error& e) {
    //    // Ýstisnayý yakalayacak iþlemler burada yapýlýr
    //    juce::String exc = "Exception Caught: ";
    //    exc += e.what();
    //    g.drawText(exc, getLocalBounds(), juce::Justification::centred, true);
    //}
    // ====================================================================================================
    //std::string part_of_str = model->response;
    //std::string searchStr = "[";
    //std::string searchStr2 = "]";
    //std::string replaceStr = "";
    //size_t pos = part_of_str.find(searchStr);
    //size_t pos2 = part_of_str.find(searchStr2);
    //part_of_str.replace(pos, searchStr.length(), replaceStr);
    //part_of_str.replace(pos2, searchStr2.length(), replaceStr);
    //juce::String juceStr = part_of_str;
    //g.drawText(juceStr, getLocalBounds(), juce::Justification::centred, true);
    //using json = nlohmann::json;
    //std::string part_of_str = model->response;
    //json parsed_json = json::parse(part_of_str);
    //std::vector<std::string> symbols;
    //std::vector<std::string> prices;
    //for (const auto& item : parsed_json) {
    //    symbols.push_back(item["symbol"]);
    //    prices.push_back(item["price"]);
    //}
    // =========================================================================================================
    //struct SymbolData {
    //    std::string symbol;
    //    std::string price;
    //};
    //std::string res = model->response;
    //json data = json::parse(res);
    //try {
    //    // Create a vector to store the SymbolData structs
    //    std::vector<SymbolData> symbolDataVector;
    //    // Iterate through the JSON array and store each element in the vector
    //    for (const auto& item : data) {
    //        SymbolData symbolData;
    //        symbolData.price = item["price"];
    //        symbolData.symbol = item["symbol"];
    //        symbolDataVector.push_back(symbolData);
    //    }
    //    g.drawText(symbolDataVector[0][0], getLocalBounds(), juce::Justification::centred, true);
    //    // Now you have the parsed data stored in the vector
    //    // You can access and use the data as needed
    //    // For example, to print the parsed values:
    //    for (const auto& symbolData : symbolDataVector) {
    //        std::cout << "Symbol: " << symbolData.symbol << ", Price: " << symbolData.price << std::endl;
    //    }
    //}
    //catch (const std::exception& e) {
    //    std::cerr << "Error while parsing JSON: " << e.what() << std::endl;
    //}
    // ========================================================================================================
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
        symbols.clear();
        prices.clear();

        //// cryptocurrency fiyat ve sembolleri icin vektor olusturma
        //std::vector<std::string> symbols;
        //std::vector<std::string> prices;
        //
        // parse edilmis json'daki fiyat ve sembolleri vektorlere ekleme
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
        //tableModel = std::make_unique<MyTableModel>(symbols, prices);
        //table.setModel(tableModel.get());
        //table.updateContent();  
        
        
        // fiyat ve sembolleri direkt ekrana yazdirma
        // sonrasinda tabloya eklenecek
        int y = 0; 
        for (size_t i = 0; i < symbols.size(); ++i) {
            double priceDouble = std::stod(prices[i]);
            std::ostringstream oss;
            // ondalikli kisim cok uzamasin diye eklendi.
            oss << std::fixed << std::setprecision(5) << priceDouble;
            std::string formattedPrice = oss.str();
            std::string symbolAndPrice = symbols[i] + " - " + formattedPrice;
            g.drawText(symbolAndPrice, 0, y, getWidth(), 20, juce::Justification::centred, true);
            y += 20;
        }
    }
    catch (const json::exception& e) {
        std::cerr << "Error: JSON parsing failed. Reason: " << e.what() << std::endl;
        return;
    }
    
}


void MainComponent::resized()
{
    /*table.setBounds(getLocalBounds())*/;
}

void MainComponent::mouseDown(const juce::MouseEvent& event)
{
    model->run();
}

void MainComponent::handleAsyncUpdate()
{
    repaint();
}

void MainComponent::update()
{
    triggerAsyncUpdate();
}
