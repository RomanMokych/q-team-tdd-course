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

#include <regex>

class IWeatherServer
{
public:
    virtual ~IWeatherServer() { }
    // Returns raw response with weather for the given day and time in request
    virtual std::string GetWeather(const std::string& request) = 0;
};

class WeatherServerStub : public IWeatherServer
{
public:
    void SetWeatherForDate(const std::string& weather, const std::string& date)
    {
        m_stubResponses[date] = weather;
    }

    virtual std::string GetWeather(const std::string& request)
    {
        std::map<std::string, std::string>::iterator it = m_stubResponses.find(request);
        if(it == m_stubResponses.end())
        {
            return "";
        }

        return it->second;
    }

private:
    std::map<std::string, std::string> m_stubResponses;
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

void splitStringsBySeparator(const std::string& targetString, const std::string& separator, std::vector<std::string>& components)
{
    if(targetString.empty())
    {
        return;
    }

    std::regex rgx(separator);

    std::sregex_token_iterator iter(targetString.begin(), targetString.end(), rgx, -1);
    std::sregex_token_iterator end;

    while(iter != end)
    {
        components.push_back(*iter);
        ++iter;
    }
}

class WeatherResponseParser
{
public:
    WeatherResponseParser(std::string weatherResponse):
        temperature(0),
        windDirection(0),
        windSpeed(0)
    {
        std::vector<std::string> responseComponents;
        splitStringsBySeparator(weatherResponse, ";", responseComponents);

        if(responseComponents.size() != 3)
        {
            throw std::runtime_error("Invalid response format.");
        }

        temperature = std::stoi(responseComponents[0].c_str());
        windDirection = std::stoul(responseComponents[1].c_str());
        windSpeed = std::stod(responseComponents[2].c_str());

        if(windDirection > 359)
        {
            throw std::invalid_argument("Wind direction not in range.");
        }
    }

public:
    short temperature;
    unsigned short windDirection;
    double windSpeed;
};

const std::vector<std::string> kAvailableWeatherTime = {"03:00", "09:00", "15:00", "21:00"};

class WeatherClient : public IWeatherClient
{
public:
    virtual double GetAverageTemperature(IWeatherServer& server, const std::string& date)
    {
        double temperatureSum = 0.0;

        for(auto time : kAvailableWeatherTime)
        {
            std::string weatherResponse = server.GetWeather(date + ";" + time);
            WeatherResponseParser responseParser(weatherResponse);
            temperatureSum += responseParser.temperature;

        }

        return temperatureSum / kAvailableWeatherTime.size();
    }

    virtual double GetMinimumTemperature(IWeatherServer& server, const std::string& date)
    {
        std::vector<short> temperatureForDay(kAvailableWeatherTime.size());

        for(auto time : kAvailableWeatherTime)
        {
            std::string weatherResponse = server.GetWeather(date + ";" + time);
            WeatherResponseParser responseParser(weatherResponse);
            temperatureForDay.push_back(responseParser.temperature);
        }

         return *(std::min_element(temperatureForDay.begin(), temperatureForDay.end()));
    }

    virtual double GetMaximumTemperature(IWeatherServer& server, const std::string& date)
    {
        std::vector<short> temperatureForDay(kAvailableWeatherTime.size());

        for(auto time : kAvailableWeatherTime)
        {
            std::string weatherResponse = server.GetWeather(date + ";" + time);
            WeatherResponseParser responseParser(weatherResponse);
            temperatureForDay.push_back(responseParser.temperature);
        }

         return *(std::max_element(temperatureForDay.begin(), temperatureForDay.end()));
    }

    virtual double GetAverageWindDirection(IWeatherServer& server, const std::string& date)
    {
        double windDirectionSum = 0.0;

        for(auto time : kAvailableWeatherTime)
        {
            std::string weatherResponse = server.GetWeather(date + ";" + time);
            WeatherResponseParser responseParser(weatherResponse);
            windDirectionSum += responseParser.windDirection;

        }

        return windDirectionSum / kAvailableWeatherTime.size();
    }

    virtual double GetMaximumWindSpeed(IWeatherServer& server, const std::string& date)
    {
        std::vector<double> windSpeedForDay(kAvailableWeatherTime.size());

        for(auto time : kAvailableWeatherTime)
        {
            std::string weatherResponse = server.GetWeather(date + ";" + time);
            WeatherResponseParser responseParser(weatherResponse);
            windSpeedForDay.push_back(responseParser.windSpeed);
        }

         return *(std::max_element(windSpeedForDay.begin(), windSpeedForDay.end()));
    }
};

// Tests and todo list:

TEST(WeatherServerStub, Responses_with_stub_data)
{
    WeatherServerStub stubServer;

    std::string expectedResponse_1 = "some_weather";
    std::string weatherRequest_1 = "some_request";
    std::string expectedResponse_2 = "some_weather_2";
    std::string weatherRequest_2 = "some_request_2";

    stubServer.SetWeatherForDate(expectedResponse_1, weatherRequest_1);
    stubServer.SetWeatherForDate(expectedResponse_2, weatherRequest_2);

    EXPECT_EQ(expectedResponse_1, stubServer.GetWeather(weatherRequest_1));
    EXPECT_EQ(expectedResponse_2, stubServer.GetWeather(weatherRequest_2));
    EXPECT_EQ("", stubServer.GetWeather("not_stub_request"));
}

TEST(Utils, Split_strings_by_separator)
{
    std::vector<std::string> actualResult;

    splitStringsBySeparator("1;2;3", ";", actualResult);
    std::vector<std::string> expectedResult = {"1", "2", "3"};
    EXPECT_EQ(expectedResult, actualResult);

    actualResult = {};
    splitStringsBySeparator("", ";", actualResult);
    expectedResult = {};
    EXPECT_EQ(expectedResult, actualResult);
}

TEST(WeatherResponseParser, Validate_response)
{
    EXPECT_THROW(WeatherResponseParser parser(""), std::runtime_error);
    EXPECT_THROW(WeatherResponseParser parser("wtf_response"), std::runtime_error);

    EXPECT_THROW(WeatherResponseParser parser("w;t;f"), std::invalid_argument);
    EXPECT_THROW(WeatherResponseParser parser("20;t;f"), std::invalid_argument);
    EXPECT_THROW(WeatherResponseParser parser("20;180;f"), std::invalid_argument);

    // validate wind direction range
    EXPECT_THROW(WeatherResponseParser parser("20;700;20.5"), std::invalid_argument);

    WeatherResponseParser parser("-5;90;13.5");
    EXPECT_EQ(-5, parser.temperature);
    EXPECT_EQ(90, parser.windDirection);
    EXPECT_EQ(13.5, parser.windSpeed);
}

TEST(WeatherClient, GetMinimumTemperature)
{
    WeatherServerStub stubServer;
    stubServer.SetWeatherForDate("50;0;0", "02.09.2018;03:00");
    stubServer.SetWeatherForDate("-20;0;0", "02.09.2018;09:00");
    stubServer.SetWeatherForDate("0;0;0", "02.09.2018;15:00");
    stubServer.SetWeatherForDate("10;0;0", "02.09.2018;21:00");

    WeatherClient client;
    EXPECT_EQ(-20, client.GetMinimumTemperature(stubServer, "02.09.2018"));
}

TEST(WeatherClient, GetMaximumTemperature)
{
    WeatherServerStub stubServer;
    stubServer.SetWeatherForDate("50;0;0", "02.09.2018;03:00");
    stubServer.SetWeatherForDate("-20;0;0", "02.09.2018;09:00");
    stubServer.SetWeatherForDate("0;0;0", "02.09.2018;15:00");
    stubServer.SetWeatherForDate("10;0;0", "02.09.2018;21:00");

    WeatherClient client;
    EXPECT_EQ(50, client.GetMaximumTemperature(stubServer, "02.09.2018"));
}

TEST(WeatherClient, GetAverageTemperature)
{
    WeatherServerStub stubServer;
    stubServer.SetWeatherForDate("50;0;0", "02.09.2018;03:00");
    stubServer.SetWeatherForDate("-20;0;0", "02.09.2018;09:00");
    stubServer.SetWeatherForDate("0;0;0", "02.09.2018;15:00");
    stubServer.SetWeatherForDate("10;0;0", "02.09.2018;21:00");

    WeatherClient client;
    EXPECT_EQ(10, client.GetAverageTemperature(stubServer, "02.09.2018"));
}

TEST(WeatherClient, GetMaximumWindSpeed)
{
    WeatherServerStub stubServer;
    stubServer.SetWeatherForDate("0;0;15.2", "02.09.2018;03:00");
    stubServer.SetWeatherForDate("0;0;0", "02.09.2018;09:00");
    stubServer.SetWeatherForDate("0;0;15.3", "02.09.2018;15:00");
    stubServer.SetWeatherForDate("0;0;12.5", "02.09.2018;21:00");

    WeatherClient client;
    EXPECT_EQ(15.3, client.GetMaximumWindSpeed(stubServer, "02.09.2018"));
}

TEST(WeatherClient, GetAverageWindDirection)
{
    WeatherServerStub stubServer;
    stubServer.SetWeatherForDate("0;150;0", "02.09.2018;03:00");
    stubServer.SetWeatherForDate("0;100;0", "02.09.2018;09:00");
    stubServer.SetWeatherForDate("0;170;0", "02.09.2018;15:00");
    stubServer.SetWeatherForDate("0;90;0", "02.09.2018;21:00");

    WeatherClient client;
    EXPECT_EQ(127.5, client.GetAverageWindDirection(stubServer, "02.09.2018"));
}
