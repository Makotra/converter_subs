#include "SSA.h"

#include <fstream>
SSA::SSA() {}
std::string cheking_zero(int value)
{
	std::string result;
	if (value < 10)
	{
		result = "0" + std::to_string(value);
	}
	else
	{
		result = std::to_string(value);
	}
	return result;
};
std::string convert_to_ass_time(int time_ms)
{
	int hours = time_ms / 3600000;
	time_ms %= 3600000;
	int minutes = time_ms / 60000;
	time_ms %= 60000;
	int seconds = time_ms / 1000;
	int centiseconds = (time_ms % 1000) / 10;
	return std::to_string(hours) + ":" + cheking_zero(minutes) + ":" + cheking_zero(seconds) + "." + cheking_zero(centiseconds);
}

void SSA::convert_to_Advanced_Sub_Station_Alpha(SSA *sub, std::string &out_put)
{
	std::ofstream out(out_put);
	out << "[Script Info]\n";
	out << "Title: Converted Subtitles\n";
	out << "ScriptType: v4.00+\n";
	out << "\n[Events]\n";
	out << "Format: Marked, Start, End, Style, Name, MarginL, MarginR, MarginV, Effect, Text\n";

	for (size_t i = 0; i < sub->m_vector.size(); ++i)
	{
		std::string start = convert_to_ass_time(sub->m_vector[i]->m_start);
		std::string end = convert_to_ass_time(sub->m_vector[i]->m_end);
		std::string text = sub->m_vector[i]->m_text;

		out << "Dialogue: 0," << start << "," << end << ",Default,,0,0,0,," << text << "\n";
	}
}
