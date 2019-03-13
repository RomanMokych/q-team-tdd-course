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

#include <time.h>

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

/*
 * Steps:
 *  Create fake client and wather server
 *  Test for empy request
 *  Simple test "31.08.2018;03:00" : "20;181;5.1" with hardcode strings
 *  Parsing request: get day, time
 *  Check valid request
 *  Save data to wather server
 *  Add several client's requests
 *
 */

const static std::string s_invalid_request = "invalid request";
const static std::string s_example_request = "02.09.2018;03:00";

class FakeWatherServer : public IWeatherServer
{

public:
    FakeWatherServer()
    {
        loadWatherDB();
    }

    virtual ~FakeWatherServer() { }

    virtual std::string GetWeather(const std::string& request)
    {

        if(request.empty())
        {
            return "";
        }

        if(request.size() != s_example_request.size())
        {
            return s_invalid_request;
        }

        if(!isTimeValid(request))
        {
            return s_invalid_request;
        }

        return m_wather_db[request];
    }

private:
    bool isTimeValid(const std::string& request)
    {
        int hours = atoi(request.substr(11, 2).c_str());
        if(     hours == 3 ||
                hours == 9 ||
                hours == 15 ||
                hours == 21)
        {
            return true;
        }

        return false;
    }

    void loadWatherDB()
    {
        m_wather_db["31.08.2018;03:00"] = "20;181;5.1";
        m_wather_db["31.08.2018;09:00"] = "23;204;4.9";
        m_wather_db["31.08.2018;15:00"] = "33;193;4.3";
        m_wather_db["31.08.2018;21:00"] = "26;179;4.5";

        m_wather_db["01.09.2018;03:00"] = "19;176;4.2";
        m_wather_db["01.09.2018;09:00"] = "22;131;4.1";
        m_wather_db["01.09.2018;15:00"] = "31;109;4.0";
        m_wather_db["01.09.2018;21:00"] = "24;127;4.1";

        m_wather_db["02.09.2018;03:00"] = "21;158;3.8";
        m_wather_db["02.09.2018;09:00"] = "25;201;3.5";
        m_wather_db["02.09.2018;15:00"] = "34;258;3.7";
        m_wather_db["02.09.2018;21:00"] = "27;299;4.0";

    }

private:
    std::map<std::string, std::string> m_wather_db;
};

class FakeWatherClient : public IWeatherClient
{
public:
    virtual ~FakeWatherClient() { }
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
        std::string response = server.GetWeather(date);
        const double maximumWindSpeed = atof(response.substr(7, 3).c_str());
        return maximumWindSpeed;
    }
};
TEST(WatherServerTest, wather_server_empty_request_emtpy_response)
{
    FakeWatherServer server;

    const std::string request("");
    const std::string response("");


    EXPECT_EQ(server.GetWeather(request), response);
}

TEST(WatherServerTest, wather_server_check_valid_request_format)
{
    FakeWatherServer server;

    const std::string request("02.09.2018;03:00");
    const std::string response("21;158;3.8");


    EXPECT_EQ(server.GetWeather(request), response);
}

TEST(WatherServerTest, wather_server_check_valid_request_format2)
{
    FakeWatherServer server;

    const std::string request("31.08.2018;09:00");
    const std::string response("23;204;4.9");


    EXPECT_EQ(server.GetWeather(request), response);
}

TEST(WatherServerTest, wather_server_request_bad_time_10_00)
{
    FakeWatherServer server;

    const std::string request("31.08.2018;10:00");

    EXPECT_EQ(server.GetWeather(request), s_invalid_request);
}

TEST(WatherServerTest, wather_server_request_bad_time_11_00)
{
    FakeWatherServer server;

    const std::string request("31.08.2018;11:00");

    EXPECT_EQ(server.GetWeather(request), s_invalid_request);
}

TEST(WatherServerTest, wather_server_request_bad_request_length)
{
    FakeWatherServer server;

    const std::string request("31");

    EXPECT_EQ(server.GetWeather(request), s_invalid_request);
}

TEST(WatherServerTest, wather_client_request_MaximumWindSpeed_for_date_02_09_2018__expected_4)
{
    FakeWatherServer server;
    FakeWatherClient client;

    const std::string date("02.09.2018;21:00" );
    const double response = 4.0;

    EXPECT_EQ(client.GetMaximumWindSpeed(server, date), response);
}
