#include "converter_time.h"
#define milliseconds_in_hour 3600000
#define milliseconds_in_minute 60000
#define milliseconds_in_second 1000
#include <iostream>
void format_time(int time, std::ofstream& out, char separator, bool is_vtt)
{
	int hours = time / milliseconds_in_hour;
	time %= milliseconds_in_hour;
	int minutes = time / milliseconds_in_minute;
	time %= milliseconds_in_minute;
	int seconds = time / milliseconds_in_second;
	int milliseconds = time % 1000;

	std::string result;

	auto two_digits = [](int val)
	{
		return (val < 10 ? "0" : "") + std::to_string(val);
	};

	if (is_vtt and hours == 0)
	{
		result = two_digits(minutes) + ":" + two_digits(seconds) + separator;
	}
	else
	{
		result = two_digits(hours) + ":" + two_digits(minutes) + ":" + two_digits(seconds) + separator;
	}

	std::string ms = std::to_string(milliseconds);
	while (ms.length() < 3)
	{
		ms = "0" + ms;
	}
	result += ms;

	out << result;
}
