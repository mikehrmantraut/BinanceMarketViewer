#include "MyModel.h"

void MyModel::run()
{
	MyAsyncHttpSession ses;
	ses.run([this](const std::string& res)
        {
            response = res;
            if (view)
                view->update();
        });
}

void MyModel::parseData(const std::string& jsonData)
{
    using json = nlohmann::json;
    try {
        // JSON formatýna çevirme
        json parsed_json = json::parse(jsonData);

        // JSON formatýný kontrol etme
        if (!parsed_json.is_array()) {
            std::cerr << "Error: The JSON is not an array of objects." << std::endl;
            return;
        }

        // Parse edilmiþ JSON'daki fiyat ve sembolleri vektörlere ekleme
        std::vector<std::string> tmpSymbols;
        std::vector<std::string> tmpPrices;

        for (const auto& item : parsed_json) {
            if (item.is_object()) {
                if (data.find(item["symbol"]) != data.end())
                {
                    data.insert(item["symbol"], item["price"]);
                }
                else
                {
                    auto currentVal = data[item["symbol"]];
                    if (currentVal != item["price"])
                    {
                        try
                        {
                            auto parsedVal = std::stod(currentVal);
                            auto parsedNewVal = std::stod(item["price"].dump());
                        }
                        catch (const std::exception&e)
                        {
                            OutputDebugString("Deger parse edilemedi.");
                        }
                    }
                }
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

std::map<std::string, std::string> MyModel::getData() const
{
    return data;
}


// diff'i  vector indeksiyle flasher'a gonder