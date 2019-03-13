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

class WeatherClient : public IWeatherClient
{
public:
    virtual double GetAverageTemperature(IWeatherServer& server, const std::string& date)
    {
        return 0.0;
    }

    virtual double GetMinimumTemperature(IWeatherServer& server, const std::string& date)
    {
        return 0.0;
    }

    virtual double GetMaximumTemperature(IWeatherServer& server, const std::string& date)
    {
        return 0.0;
    }

    virtual double GetAverageWindDirection(IWeatherServer& server, const std::string& date)
    {
        return 0.0;
    }

    virtual double GetMaximumWindSpeed(IWeatherServer& server, const std::string& date)
    {
        return 0.0;
    }
};

class WeatherResponseParser
{
public:
    WeatherResponseParser(std::string weatherResponse)
    {

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

TEST(WeatherResponseParser, Invalid_response_throws_exception)
{
    EXPECT_THROW(WeatherResponseParser parser("wtf_response"), std::runtime_error);
}


