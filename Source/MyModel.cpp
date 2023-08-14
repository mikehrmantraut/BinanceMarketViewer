#include "MyModel.h"
void MyModel::run()
{
    MyWebSocketSession ses;
    ses.run([this](const std::string& res)
        {
            response = res;
            parseData(response);
            if (view)
                view->update();
        });
}
void MyModel::timerCallback()
{
    run();
}

void MyModel::parseData(std::string& response)
{
    using json = nlohmann::json;
    try {
        // JSON parsing
        json parsed_json = json::parse(response);
        if (!parsed_json.is_array()) {
            std::cerr << "Error: The JSON is not an array of objects." << std::endl;
            return;
        }
        // Parse JSON and update the vectors
        symbols.clear();
        prices.clear();
        int count = 0;
        for (const auto& item : parsed_json) {
            if (item.is_object()) {
                symbols.push_back(item["s"]);
                prices.push_back(item["c"]);
            }
            else {
                std::cerr << "Error: One of the items is not a JSON object." << std::endl;
                return;
            }
        }
        this->sortData(symbols, prices, ids);
    }
    catch (const json::exception& e) {
        std::cerr << "Error: JSON parsing failed. Reason: " << e.what() << std::endl;
        return;
    }
    ids.clear();
    for (size_t i = 0; i < symbols.size() && i < prices.size(); ++i)
        ids.push_back(i + 1);
}

void MyModel::sortData(std::vector<std::string>& symbols, std::vector<std::string>& prices, std::vector<size_t>& ids)
{
    std::vector<size_t> indices(symbols.size());
    for (size_t i = 0; i < symbols.size(); ++i) {
        indices[i] = i;
    }
    auto customSort = [&](size_t i, size_t j) {
        return symbols[i] < symbols[j];
    };
    std::sort(indices.begin(), indices.end(), customSort);
    std::vector<std::string> sortedSymbols(symbols.size());
    std::vector<std::string> sortedPrices(prices.size());
    std::vector<int> sortedIds(ids.size());
    for (size_t i = 0; i < symbols.size(); ++i) {
        size_t index = indices[i];
        sortedSymbols[i] = symbols[index];
        sortedPrices[i] = prices[index];
    }
    symbols = std::move(sortedSymbols);
    prices = std::move(sortedPrices);
}

const std::vector<std::string>& MyModel::getSymbols() const
{
    return symbols;
}
const std::vector<std::string>& MyModel::getPrices() const
{
    return prices;
}
