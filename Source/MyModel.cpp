#include "MyModel.h"


void MyModel::parseData(const std::string& response)
{
    using json = nlohmann::json;
    try {
        json parsed_json = json::parse(response);
        if (!parsed_json.is_array()) {
            std::cerr << "Error: The JSON is not an array of objects." << std::endl;
            return;
        }

        for (const auto& item : parsed_json) {
            if (item.is_object()) {
                const std::string symbol = item["s"];
                data[symbol].close = item["c"];
                data[symbol].low = item["l"];
                data[symbol].high = item["h"];
                data[symbol].open = item["o"];
                data[symbol].totalQuote = item["q"];
                data[symbol].totalTrade = item["v"];
            
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
}


 //MainComponentData
 //SymbolData
 //std::string currentPrice 
 //std::string symbolName

std::vector<SymbolData> MyModel::getMainComponentData()
{
    std::vector<SymbolData> mainComponentData;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        SymbolData sd;
        sd.symbol = it->first;
        sd.currentPrice = it->second.close;
        mainComponentData.push_back(sd);
    }
    return mainComponentData;
}

std::map<std::string, MarketData> MyModel::getData(){
    return data;
}

// message ulastiginda parse etme islemi
void MyModel::onDataReceived(const std::string& message)
{
    parseData(message);
    if (view)
        view->update();
}

