/*
Weather Client

You are going to develop a program that gets the statistics about weather in the current city
using information from a certain server. The goal is to calculate statistics using the data from weather server.

To communicate with the weather server you have to implement interface IWeatherServer,
which provides the raw string from the real server for the requested day and time.

The real server (i.e. "weather.com") gets the requests in this format:
"<date>;<time>", for example:
"31.08.2018;03:00"

The server answers on requests with string like this:
"20;181;5.1"
This string contains the weather for the requested time and means next:
"<air_temperature_in_celsius>;<wind_direction_in_degrees>:<wind_speed>".
Wind direction value may be in range from 0 to 359 inclusively, temperature may be negative.

The task:
1. Implement fake server, because interacting with real network is inacceptable within the unit tests.
To do this, you need to use real server responses. Fortunately, you've collected some results for the several dates from the weather server.
Each line means "<request>" : "<response>":

"31.08.2018;03:00" : "20;181;5.1"
"31.08.2018;09:00" : "23;204;4.9"
"31.08.2018;15:00" : "33;193;4.3"
"31.08.2018;21:00" : "26;179;4.5"

"01.09.2018;03:00" : "19;176;4.2"
"01.09.2018;09:00" : "22;131;4.1"
"01.09.2018;15:00" : "31;109;4.0"
"01.09.2018;21:00" : "24;127;4.1"

"02.09.2018;03:00" : "21;158;3.8"
"02.09.2018;09:00" : "25;201;3.5"
"02.09.2018;15:00" : "34;258;3.7"
"02.09.2018;21:00" : "27;299;4.0"

IMPORTANT:
* Server returns empty string if request is invalid.
* Real server stores weather only for times 03:00, 09:00, 15:00 and 21:00 for every date. Do not use other hours in a day.

2. Implement IWeatherClient using fake server.
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <map>

const static std::map<std::string, std::string> s_weatherMap = {{"31.08.2018;03:00","20;181;5.1"},
                                                                {"31.08.2018;09:00","23;204;4.9"},
                                                                {"31.08.2018;15:00","33;193;4.3"},
                                                                {"31.08.2018;21:00","26;179;4.5"},
                                                                {"01.09.2018;03:00","19;176;4.2"},
                                                                {"01.09.2018;09:00","22;131;4.1"},
                                                                {"01.09.2018;15:00","31;109;4.0"},
                                                                {"01.09.2018;21:00","24;127;4.1"},
                                                                {"02.09.2018;03:00","21;158;3.8"},
                                                                {"02.09.2018;09:00","25;201;3.5"},
                                                                {"02.09.2018;15:00","34;258;3.7"},
                                                                {"02.09.2018;21:00","27;299;4.0"}};

struct Weather
{
    double temperature;
    double windDirection;
    double windSpeed;
};
bool operator==(const Weather& left , const Weather& right)
{
    return left.temperature == right.temperature &&
            left.windDirection == right.windDirection &&
            std::abs(left.windSpeed - right.windSpeed) < 0.01;
}

struct OneDayWeather
{
    Weather nightWeather;
    Weather morningWeather;
    Weather dayWeather;
    Weather eveningWeather;
};
bool operator==(const OneDayWeather& left, const OneDayWeather& right)
{
    return left.nightWeather == right.nightWeather &&
            left.morningWeather == right.morningWeather &&
            left.dayWeather == right.dayWeather &&
            left.eveningWeather == right.eveningWeather;
}

class IWeatherServer
{
public:
    virtual ~IWeatherServer() { }
    // Returns raw response with weather for the given day and time in request
    virtual std::string GetWeather(const std::string& request) = 0;
};

class WeatherServer : public IWeatherServer
{
public:
    virtual ~WeatherServer() { }
    virtual std::string GetWeather(const std::string& request)
    {
        return s_weatherMap.at(request);
    }
};

class WeatherRetriever
{
public:
    static OneDayWeather getOneDayWeather(IWeatherServer& server, const std::string& date)
    {
        OneDayWeather result;
        std::string nightWeatherRequest = date;
        nightWeatherRequest.append(";03:00");
        result.nightWeather = retrieveWeather(server, nightWeatherRequest);

        std::string morningWeatherRequest = date;
        morningWeatherRequest.append(";09:00");
        result.morningWeather = retrieveWeather(server, morningWeatherRequest);

        std::string dayWeatherRequest = date;
        dayWeatherRequest.append(";15:00");
        result.dayWeather = retrieveWeather(server, dayWeatherRequest);

        std::string eveningWeatherRequest = date;
        eveningWeatherRequest.append(";21:00");
        result.eveningWeather = retrieveWeather(server, eveningWeatherRequest);
        return result;
    }
private:
    static Weather retrieveWeather(IWeatherServer& server, std::string& weatherRequest)
    {
        Weather weather;
        std::string weatherString = server.GetWeather(weatherRequest);
        weather.temperature = std::stod(weatherString.substr(0, weatherString.find(';')));
        weatherString = weatherString.substr(weatherString.find(';') + 1);
        weather.windDirection = std::stod(weatherString.substr(0, weatherString.find(';')));
        weatherString = weatherString.substr(weatherString.find(';') + 1);
        weather.windSpeed = std::stod(weatherString);
        return weather;
    }
};

// Implement this interface
class IWeatherClient
{
public:
    virtual ~IWeatherClient() { }
    virtual double GetAverageTemperature(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetMinimumTemperature(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetMaximumTemperature(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetAverageWindDirection(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetMaximumWindSpeed(IWeatherServer& server, const std::string& date) = 0;
};

class WeatherClient : public IWeatherClient
{
public:
    virtual ~WeatherClient() { }
    virtual double GetAverageTemperature(IWeatherServer& server, const std::string& date)
    {
        OneDayWeather allDayWeather = WeatherRetriever::getOneDayWeather(server, date);
        double averageTemperature = (allDayWeather.morningWeather.temperature +
                                     allDayWeather.dayWeather.temperature +
                                     allDayWeather.eveningWeather.temperature +
                                     allDayWeather.nightWeather.temperature) / 4;
        return averageTemperature;
    }
    virtual double GetMinimumTemperature(IWeatherServer& server, const std::string& date)
    {
        OneDayWeather allDayWeather = WeatherRetriever::getOneDayWeather(server, date);
        double result = allDayWeather.nightWeather.temperature;
        if (result > allDayWeather.morningWeather.temperature)
            result = allDayWeather.morningWeather.temperature;
        if (result > allDayWeather.dayWeather.temperature)
            result = allDayWeather.dayWeather.temperature;
        if (result > allDayWeather.eveningWeather.temperature)
            result = allDayWeather.eveningWeather.temperature;
        return result;
    }
    virtual double GetMaximumTemperature(IWeatherServer& server, const std::string& date)
    {
        OneDayWeather allDayWeather = WeatherRetriever::getOneDayWeather(server, date);
        double result = allDayWeather.nightWeather.temperature;
        if (result < allDayWeather.morningWeather.temperature)
            result = allDayWeather.morningWeather.temperature;
        if (result < allDayWeather.dayWeather.temperature)
            result = allDayWeather.dayWeather.temperature;
        if (result < allDayWeather.eveningWeather.temperature)
            result = allDayWeather.eveningWeather.temperature;
        return result;
    }
    virtual double GetAverageWindDirection(IWeatherServer& server, const std::string& date)
    {
        OneDayWeather allDayWeather = WeatherRetriever::getOneDayWeather(server, date);
        double averageWindDirection= (allDayWeather.morningWeather.windDirection +
                                     allDayWeather.dayWeather.windDirection +
                                     allDayWeather.eveningWeather.windDirection +
                                     allDayWeather.nightWeather.windDirection) / 4;
        return averageWindDirection;
    }
    virtual double GetMaximumWindSpeed(IWeatherServer& server, const std::string& date)
    {
        return 0;
    }
};

TEST(WeatherRetriever, retrieve_weather_for_31_08)
{
    std::string day = "31.08.2018";
    WeatherServer server;
    OneDayWeather expected {{20, 181, 5.1}, {23, 204, 4.9}, {33, 193, 4.3}, {26,179,4.5}};
    OneDayWeather actual = WeatherRetriever::getOneDayWeather(server, day);
    EXPECT_EQ(expected, actual);
}

TEST(WeatherClient, av_temp_for_31_08_is25_point_5)
{
    std::string day = "31.08.2018";
    WeatherServer server;
    WeatherClient client;
    EXPECT_EQ(25.5, client.GetAverageTemperature(server, day));
}

TEST(WeatherClient, min_temp_for_01_09_is_19)
{
    std::string day = "01.09.2018";
    WeatherServer server;
    WeatherClient client;
    EXPECT_EQ(19, client.GetMinimumTemperature(server, day));
}

TEST(WeatherClient, max_temp_for_02_09_is_34)
{
    std::string day = "02.09.2018";
    WeatherServer server;
    WeatherClient client;
    EXPECT_EQ(34, client.GetMaximumTemperature(server, day));
}

TEST(WeatherClient, av_wind_direction_for_01_09_is_34)
{
    std::string day = "01.09.2018";
    WeatherServer server;
    WeatherClient client;
    EXPECT_EQ(135.75, client.GetAverageWindDirection(server, day));
}
