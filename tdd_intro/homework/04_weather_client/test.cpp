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
"<air_temperature_in_celsius>;<wind_direction_in_degrees>;<wind_speed>".
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

#include <algorithm>
#include <iterator>
#include <regex>

class IWeatherServer
{
public:
    virtual ~IWeatherServer() { }
    // Returns raw response with weather for the given day and time in request
    virtual std::string GetWeather(const std::string& request) = 0;
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

class ServerMock : public IWeatherServer
{
public:
    std::string GetWeather(const std::string& request)
    {
        if (request == "31.08.2018;03:00")
            return "20;181;5.1";
        if (request == "31.08.2018;09:00")
            return "23;204;4.9";
        if (request == "31.08.2018;15:00")
            return "33;193;4.3";
        if (request == "31.08.2018;21:00")
            return "26;179;4.5";
        if (request == "01.09.2018;03:00")
            return "19;176;4.2";
        if (request == "01.09.2018;09:00")
            return "22;131;4.1";
        if (request == "01.09.2018;15:00")
            return "31;109;4.0";
        if (request == "01.09.2018;21:00")
            return "24;127;4.1";
        if (request == "02.09.2018;03:00")
            return "21;158;3.8";
        if (request == "02.09.2018;09:00")
            return "25;201;3.5";
        if (request == "02.09.2018;15:00")
            return "34;258;3.7";
        if (request == "02.09.2018;21:00")
            return "27;299;4.0";

        return ""; //Server returns empty string if request is invalid.
    }
};

// Implement this interface
class ConcreteWeatherClient : public IWeatherClient
{
public:
    double GetAverageTemperature(IWeatherServer& server, const std::string& date)
    {
        double sumTemperature = 0;
        for (std::string time : times_of_date)
        {
            sumTemperature += SplitToValues(server.GetWeather(date + ";" + time), ";").temperature;
        }

        return sumTemperature / times_of_date.size();
    }
    double GetMinimumTemperature(IWeatherServer& server, const std::string& date)
    {
        std::vector<double> temperatures;
        for (std::string time : times_of_date)
        {
            temperatures.push_back(SplitToValues(server.GetWeather(date + ";" + time), ";").temperature);
        }

        return *(std::min_element(temperatures.begin(), temperatures.end()));
    }
    double GetMaximumTemperature(IWeatherServer& server, const std::string& date)
    {
        std::vector<double> temperatures;
        for (std::string time : times_of_date)
        {
            temperatures.push_back(SplitToValues(server.GetWeather(date + ";" + time), ";").temperature);
        }

        return *(std::max_element(temperatures.begin(), temperatures.end()));
    }
    double GetAverageWindDirection(IWeatherServer& server, const std::string& date)
    {
        double sumWindDirection = 0;
        for (std::string time : times_of_date)
        {
            sumWindDirection += SplitToValues(server.GetWeather(date + ";" + time), ";").wind_direction;
        }

        return sumWindDirection / times_of_date.size();
    }
    double GetMaximumWindSpeed(IWeatherServer& server, const std::string& date)
    {
        std::vector<double> wind_speeds;
        for (std::string time : times_of_date)
        {
            wind_speeds.push_back(SplitToValues(server.GetWeather(date + ";" + time), ";").wind_speed);
        }

        return *(std::max_element(wind_speeds.begin(), wind_speeds.end()));
    }

private:
    struct Values{
        int temperature;
        int wind_direction;
        double wind_speed;
    };
    const std::vector<std::string> times_of_date = {"03:00", "09:00", "15:00", "21:00"};

    Values SplitToValues(const std::string& input, const std::string& regex) {
        if (input.empty())
        {
            throw std::invalid_argument("Nothing to split.");
        }

        // passing -1 as the submatch index parameter performs splitting
        std::regex re(regex);
        std::vector<std::string> splittedStrings(3);
        std::copy(std::sregex_token_iterator(input.begin(), input.end(), re, -1),
                 std::sregex_token_iterator(),
                 splittedStrings.data());
        Values result;
        result.temperature = std::atoi(splittedStrings[0].c_str());
        result.wind_direction = std::atoi(splittedStrings[1].c_str());
        result.wind_speed = std::stod(splittedStrings[2].c_str());

        return result;
    }

};

TEST(WeatherClient, get_proper_maximum_wind_speed_in_31_08_2018)
{
    ServerMock server;
    ConcreteWeatherClient client;

    EXPECT_EQ(client.GetMaximumWindSpeed(server, "31.08.2018"), 5.1);
}

TEST(WeatherClient, get_proper_average_wind_direction_in_01_09_2018)
{
    ServerMock server;
    ConcreteWeatherClient client;

    EXPECT_EQ(client.GetAverageWindDirection(server, "01.09.2018"), 135.75);
}

TEST(WeatherClient, get_maximum_temperature_in_02_09_2018)
{
    ServerMock server;
    ConcreteWeatherClient client;

    EXPECT_EQ(client.GetMaximumTemperature(server, "02.09.2018"), 34);
}

TEST(WeatherClient, get_maximum_temperature_in_31_08_2018)
{
    ServerMock server;
    ConcreteWeatherClient client;

    EXPECT_EQ(client.GetMaximumTemperature(server, "31.08.2018"), 33);
}

TEST(WeatherClient, get_minimum_temperature_in_01_09_2018)
{
    ServerMock server;
    ConcreteWeatherClient client;

    EXPECT_EQ(client.GetMinimumTemperature(server, "01.09.2018"), 19);
}

TEST(WeatherClient, get_minimum_temperature_in_02_09_2018)
{
    ServerMock server;
    ConcreteWeatherClient client;

    EXPECT_EQ(client.GetMinimumTemperature(server, "02.09.2018"), 21);
}

TEST(WeatherClient, get_average_temperature_with_invalid_value)
{
    ServerMock server;
    ConcreteWeatherClient client;

    EXPECT_THROW(client.GetAverageTemperature(server, "01.09.3087"), std::invalid_argument);
}

TEST(WeatherClient, get_proper_average_temperature_in_01_09_2018)
{
    ServerMock server;
    ConcreteWeatherClient client;

    EXPECT_EQ(client.GetAverageTemperature(server, "01.09.2018"), 24);
}

TEST(WeatherClient, get_proper_average_temperature_in_31_08_2018)
{
    ServerMock server;
    ConcreteWeatherClient client;

    EXPECT_EQ(client.GetAverageTemperature(server, "31.08.2018"), 25.5);
}

TEST(WeatherServer, get_weather_at_3_00)
{
    ServerMock server;
    EXPECT_EQ(server.GetWeather("31.08.2018;03:00"), "20;181;5.1");
}

TEST(WeatherServer, invalid_get_weather_request)
{
    ServerMock server;
    EXPECT_EQ(server.GetWeather("31.08.2018;"), "");
}
