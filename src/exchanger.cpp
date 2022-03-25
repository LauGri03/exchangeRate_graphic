#include <iostream>
#include <nlohmann/json.hpp>
#include "exchanger.h"
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include <ctime>
#include <cstring>
#include <fstream>
#include <curl/curl.h>
#include <set>

//Constuctor, generation of pair(Currency, rate) by date 
Exchanger::exchanger::exchanger(){ 
    nlohmann::json baseFile = getJson();
    std::string date;
    std::vector<std::pair<std::string, long double>> rateData;
    for(auto it : baseFile.at("observations").items()){
			nlohmann::json now = it.value();
            rateData.clear();
            date = now.at("d").get<std::string>();
            now.erase("d"); //Remove the date after pickup to avoid if in for loop
				for(auto& it2 : now.items()){
                        std::tuple<std::string, long double> tu = std::make_pair(it2.key().substr(2,3),stold(it2.value()["v"].get<std::string>())); 
                        rateData.push_back(tu);
                }
            rateData.push_back(std::make_pair("CAD", 1.0000));
            rates.emplace(date, rateData); 
	}    
}

Exchanger::exchanger::~exchanger(){}

//Return vector of pair(Date, Value after conversion) by date 
std::vector<std::pair<std::string,long double>> Exchanger::exchanger::convert(std::string from, std::string to, double value){
    std::vector<std::pair<std::string,long double>> result;
    long double fromValue;
    long double toValue;
    long double resultValue;

    for(auto it : rates){
        
        fromValue = findInRates(it.second,from); //get rates for original and destination currencies
        toValue = findInRates(it.second,to);
        if(fromValue == 0.0000 || toValue == 0.0000){
            continue; //Continue loop if there is no rate for a currency 
        }
        resultValue = (value * fromValue) / toValue; //Conversion of original currency to reference currency (CAD) + conversion from CAD to destination currency
        result.push_back(make_pair(it.first, resultValue));
    }
    
    return result;
}

//Lambda expression to get rate for a given currency for each date 
long double Exchanger::exchanger::findInRates(std::vector<std::pair<std::string, long double>> vec, std::string key){
    auto it = find_if(vec.begin(),vec.end(),
        [&key](const std::pair<std::string, long double>& entry){ 
            return entry.first == key;
        } );
        return it != vec.end() ? it->second : 0.0000;

}

//Get all available currencies (Utilization of set to avoid duplicates)
std::set<std::string> Exchanger::exchanger::getAllCurrencies(){
    std::set<std::string> result; 
    std::vector<std::string> list;

    for(auto it : rates){
        list.clear();
        transform(it.second.begin(), it.second.end(), back_inserter(list),
	    [](const std::pair<std::string, long double>& p) { return p.first; });
        copy(list.begin(), list.end(), inserter(result, result.end()));
    }

    return result;
}

//Get possible destination for a given currencies (Impossible to convert properly if there are no rates for the same day)
std::set<std::string> Exchanger::exchanger::getPossiblesCurrenciesTo(std::string from){
    std::set<std::string> result;
    std::vector<std::string> list;
    
    for(auto it : rates){
        list.clear();
        if (find_if(it.second.begin(),it.second.end(),
            [&from](const std::pair<std::string, long double>& entry){ 
                return entry.first == from;
            }) != it.second.end()) { 
            transform(it.second.begin(), it.second.end(), back_inserter(list),
	        [](const std::pair<std::string, long double>& p) { return p.first; });
            copy(list.begin(), list.end(), inserter(result, result.end()));
        }
    }
    return result;
}

//Return json from Bank of Canada URL
nlohmann::json Exchanger::exchanger::getJson(){
    CURL *curl;
    CURLcode res;
    std::string buffer;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL,"https://www.bankofcanada.ca/valet/observations/group/FX_RATES_DAILY/json?recent=25");
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA, &buffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    
    return nlohmann::json::parse(buffer);
   
}

//https://curl.se/libcurl/
size_t Exchanger::exchanger::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


