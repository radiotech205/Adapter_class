#include <iostream>
#include <string>
using namespace std;

class WeatherService
{
public:
    virtual double GetTemperature() = 0;
    virtual double GetWind() = 0;
    virtual double GetFeelsLikeTemperature() = 0;
    virtual void SetPosition(string city) = 0;
    virtual string GetCity() = 0;
};
/*************************/
class RussianWeather  :public WeatherService
{
private:
    string city;
public:
    double GetTemperature()
    {
        if(city == "Moscow")    return 25.0;
        if(city == "St. Peter") return 18.0;

        return 20.0;
    }
    double GetWind()
    {
        if(city == "Moscow")    return 5.0;
        if(city == "St. Peter") return 13.0;

        return 1.0;
    }
    double GetFeelsLikeTemperature()
    {
        if(city == "Moscow")    return 23.0;
        if(city == "St. Peter") return 16.0;

        return 20.0;
    }
    void SetPosition(string city)
    {
        this->city = city;
    }
    string GetCity()    {return this->city;}
};
/**************************/
class USWeatherService
{
public:
    double GetTemperature(double latitude, double longtitude)
    {
        if (latitude == 38.53 && longtitude == 77.02) // Washington
            return 86.0;
        else
            if (latitude == 40.43 && longtitude == 73.59) // New York
                return 95.0;
            else
                return 80.0;
    }
    double GetWind(double latitude, double longtitude)
    {
        if (latitude == 38.53 && longtitude == 77.02) // Washington
            return 1000.0;
        else
            if (latitude == 40.43 && longtitude == 73.59) // New York
                return 2000.0;
            else
                return 1500.0;
    }
};
/**************************/
class USWeatherAdapter : public WeatherService, private USWeatherService
{
private:
    double latitude;
    double longtitude;
public:
    double GetTemperature()
    {
        double tf = USWeatherService::GetTemperature(latitude, longtitude);
        return (tf-32)*5/9; // F -> C
    }
    double GetWind()
    {
        double windFtMin = USWeatherService::GetWind(latitude, longtitude);
        return windFtMin / 196.85; // ft/min -> m/s
    }
    double GetFeelsLikeTemperature()
    {
        return 1.04*GetTemperature()-GetWind()*0.65-0.9;
    }

    void SetPosition(string city)
    {
        if (city == "Washington") {
            latitude = 38.53;
            longtitude = 77.02;
        }
        else
            if (city == "New-York") {
                latitude = 40.43;
                longtitude = 73.59;
            }
    }
    string GetCity()    {return "";}
};
/*******************************/
int main()
{
    WeatherService* service = new RussianWeather();
    service->SetPosition("Moscow");
    //service->SetPosition("St. Peter");

    cout << service->GetCity() << endl;
    cout << service->GetTemperature() << endl;
    cout << service->GetWind() << endl;
    cout << service->GetFeelsLikeTemperature() << endl;

    WeatherService* usService = new USWeatherAdapter();
    usService->SetPosition("New-York");

    cout << "New-York" << endl;
    cout << usService->GetTemperature() << endl;
    cout << usService->GetWind() << endl;
    cout << usService->GetFeelsLikeTemperature() << endl;

    delete service;
    delete usService;
    cout << "Hello World!" << endl;
    return 0;
}
