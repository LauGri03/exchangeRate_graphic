#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <utility>
#include <set>


namespace Exchanger{
    class exchanger{
        private:
            std::map<std::string,std::vector<std::pair<std::string,long double>>> rates;
            long double findInRates(std::vector<std::pair<std::string, long double>> vec, std::string key);
            nlohmann::json getJson();
            static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
        public:
            
            exchanger();
            ~exchanger();
            std::vector<std::pair<std::string,long double>> convert(std::string from, std::string to, double value);
            std::set<std::string> getAllCurrencies();
            std::set<std::string> getPossiblesCurrenciesTo(std::string from);
    };
}