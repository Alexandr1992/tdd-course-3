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

static const char s_responseDataSeprator = ';';

static const std::string s_nineAM = "09:00";
static const std::string s_ninePM = "21:00";
static const std::string s_threeAM = "03:00";
static const std::string s_threePM = "15:00";

struct Weather
{
    short temperature = 0;
    unsigned short windDirection = 0;
    double windSpeed = 0;
    bool operator==(const Weather& right)
    {
        return temperature == right.temperature &&
               windDirection == right.windDirection &&
               std::abs(windSpeed - right.windSpeed) < 0.01;
    }
};

double GetLineDoble(std::istringstream& stream)
{
    std::string value;
    if (!std::getline(stream, value, s_responseDataSeprator))
    {
        throw std::runtime_error("Error parsing");
    }

    return std::stod(value);
}

Weather ParseWeather(const std::string& response)
{
    Weather weather;
    std::istringstream responseStream(response);

    weather.temperature = static_cast<short>(GetLineDoble(responseStream));
    weather.windDirection = static_cast<unsigned short>(GetLineDoble(responseStream));
    if(weather.windDirection > 359)
    {
        throw std::runtime_error("Invalid paserd value for wind direction");
    }

    weather.windSpeed = GetLineDoble(responseStream);

    return weather;
}

class IWeatherServer
{
public:
    virtual ~IWeatherServer() { }
    // Returns raw response with weather for the given day and time in request
    virtual std::string GetWeather(const std::string& request) = 0;
};

class MockWeatherServer : public IWeatherServer
{
public:
    MOCK_METHOD1(GetWeather, std::string(const std::string& request));
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
    virtual double GetAverageTemperature(IWeatherServer& server, const std::string& date) override
    {
        throw std::runtime_error("not implemented");
    }
    virtual double GetMinimumTemperature(IWeatherServer& server, const std::string& date)
    {
        std::set<double> temperatures;
        temperatures.emplace(GetWeatherByDate(server, date + s_responseDataSeprator + s_threeAM).temperature);
        temperatures.emplace(GetWeatherByDate(server, date + s_responseDataSeprator + s_nineAM).temperature);
        temperatures.emplace(GetWeatherByDate(server, date + s_responseDataSeprator + s_threePM).temperature);
        temperatures.emplace(GetWeatherByDate(server, date + s_responseDataSeprator + s_ninePM).temperature);

        return *temperatures.begin();
    }

    virtual double GetMaximumTemperature(IWeatherServer& server, const std::string& date) override
    {
        std::set<double> temperatures;
        temperatures.emplace(GetWeatherByDate(server, date + s_responseDataSeprator + s_threeAM).temperature);
        temperatures.emplace(GetWeatherByDate(server, date + s_responseDataSeprator + s_nineAM).temperature);
        temperatures.emplace(GetWeatherByDate(server, date + s_responseDataSeprator + s_threePM).temperature);
        temperatures.emplace(GetWeatherByDate(server, date + s_responseDataSeprator + s_ninePM).temperature);

        return *temperatures.rbegin();
    }

    virtual double GetAverageWindDirection(IWeatherServer& server, const std::string& date) override
    {
        throw std::runtime_error("not implemented");
    }

    virtual double GetMaximumWindSpeed(IWeatherServer& server, const std::string& date) override
    {
        throw std::runtime_error("not implemented");
    }

private:
    Weather GetWeatherByDate(IWeatherServer& server, const std::string& date)
    {
        std::string response = server.GetWeather(date);
        return ParseWeather(response);
    }
};

TEST(WeatherClient, TestParseTemperatureFromResponse)
{
    Weather weather = ParseWeather("1;1;1");
    EXPECT_EQ(1, weather.temperature);
}

TEST(WeatherClient, TestThrowWhenCannotParseTemperature)
{
    EXPECT_THROW(ParseWeather("1"), std::runtime_error);
}

TEST(WeatherClient, TestParseWindDirectionFromResponse)
{
    Weather weather = ParseWeather("1;1;1");
    EXPECT_EQ(1, weather.windDirection);
}

TEST(WeatherClient, TestParseInvalidWindDirectionFromResponse)
{
    EXPECT_THROW(ParseWeather("1;360;1"), std::runtime_error);
}
TEST(WeatherClient, TestParseWindSpeedFromResponse)
{
    Weather weather = ParseWeather("1;1;1");
    EXPECT_EQ(1, weather.windSpeed);
}

TEST(WeatherClient, TestParseDoubleWindSpeedFromResponse)
{
    Weather weather = ParseWeather("1;1;4.6");
    EXPECT_EQ(4.6, weather.windSpeed);
}

//Test client

TEST(WeatherClient, TestGetMinimumTemperature_21pm)
{
    MockWeatherServer server;
    WeatherClient client;

    EXPECT_CALL(server, GetWeather("31.08.2018;03:00")).WillOnce(testing::Return("20;0;0"));
    EXPECT_CALL(server, GetWeather("31.08.2018;09:00")).WillOnce(testing::Return("6;0;0"));
    EXPECT_CALL(server, GetWeather("31.08.2018;15:00")).WillOnce(testing::Return("7;0;0"));
    EXPECT_CALL(server, GetWeather("31.08.2018;21:00")).WillOnce(testing::Return("5;0;0"));

    EXPECT_EQ(5, client.GetMinimumTemperature(server, "31.08.2018"));
}

TEST(WeatherClient, TestGetMaximumTemperature_3pm)
{
    MockWeatherServer server;
    WeatherClient client;

    EXPECT_CALL(server, GetWeather("31.08.2018;03:00")).WillOnce(testing::Return("20;0;0"));
    EXPECT_CALL(server, GetWeather("31.08.2018;09:00")).WillOnce(testing::Return("6;0;0"));
    EXPECT_CALL(server, GetWeather("31.08.2018;15:00")).WillOnce(testing::Return("30;0;0"));
    EXPECT_CALL(server, GetWeather("31.08.2018;21:00")).WillOnce(testing::Return("5;0;0"));

    EXPECT_EQ(30, client.GetMaximumTemperature(server, "31.08.2018"));
}

