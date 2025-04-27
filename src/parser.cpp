#include "parser.h"

#include "SAMI.h"
#include "SSA.h"
#include "SubRip.h"
#include "VTT.h"
#include <iostream>
#include <regex>
#define milliseconds_in_hour 3600000
#define milliseconds_in_minute 60000
#define milliseconds_in_second 1000
subtitle* add(std::ifstream& input_file, std::string& word)
{
	if (word.ends_with(".smi"))
	{
		auto* sami = new SAMI();
		parsing(input_file, sami);
		std::cout << "check file: " << sami->m_vector[0] << std::endl;
		SAMI::convert_to_SAMI(sami, word);
		return sami;
	}
	else if (word.ends_with(".srt"))
	{
		auto* srt = new SubRip();
		parsing(input_file, srt);
		SubRip::convert_to_SubRip(srt, word);
		return srt;
	}
	else if (word.ends_with(".ssa") or word.ends_with(".ass"))
	{
		auto* advanced = new SSA();
		parsing(input_file, advanced);
		SSA::convert_to_Advanced_Sub_Station_Alpha(advanced, word);
		return advanced;
	}
	else
	{
		auto* vtt = new VTT();
		parsing(input_file, vtt);
		VTT::convert_to_VTT(vtt, word);
		return vtt;
	}
}
template< typename T >
void parsing(std::ifstream& fileName, T& format)
{
	std::string s;
	int start;
	int end;
	std::string text;
	fileName >> s;
	if (s == "<SAMI>")
	{
		while (getline(fileName, s))
		{
			if (s.find("<SYNC") != std::string::npos)
			{
				if (s.find("End=") != std::string::npos)
				{
					start = std::stoi(s.substr(12, s.find(" ", 6) - 12));
					end = std::stoi(s.substr(s.find("End=") + 4, s.find("<P>") - (s.find("End=") + 5)));
					text = "";
					size_t pos = s.find("<P>");
					while (pos != std::string::npos)
					{
						size_t endPos = s.find("</P>", pos);
						if (endPos == std::string::npos)
						{
							break;
						}
						text += s.substr(pos + 3, endPos - (pos + 3)) + "\n";
						pos = s.find("<P>", endPos);
					}
					if (!text.empty() and text.back() == '\n')
					{
						text.pop_back();
					}
				}
				auto* block = new blocks_of_subtitle(start, end, text);
				format->m_vector.push_back(block);
			}
		}
	}
	else if (s == "1" || s == "WEBVTT")
	{
		std::regex time(R"((\d{2}:\d{2}(?::\d{2})?[.,]\d{3})\s*-->\s*(\d{2}:\d{2}(?::\d{2})?[.,]\d{3}))");
		auto time_to_ms = [](const std::string& t)
		{
			int h = 0, m = 0, s = 0, ms = 0;
			std::string time = t;
			std::replace(time.begin(), time.end(), ',', '.');
			std::sscanf(time.c_str(), "%d:%d:%d.%d", &h, &m, &s, &ms);

			if (time.find(':') == 2 and std::count(time.begin(), time.end(), ':') == 1)
			{
				s = m;
				m = h;
				h = 0;
			}

			return h * 3600000 + m * 60000 + s * 1000 + ms;
		};

		while (getline(fileName, s))
		{
			std::smatch match;
			if (std::regex_match(s, match, time))
			{
				start = time_to_ms(match[1].str());
				end = time_to_ms(match[2].str());

				text.clear();
				while (getline(fileName, s))
				{
					if (s.empty())
						break;
					text += s + '\n';
				}
				if (!text.empty() and text.back() == '\n')
					text.pop_back();

				auto* block = new blocks_of_subtitle(start, end, text);
				format->m_vector.push_back(block);
			}
		}
	}
	else if (s == "[Script")
	{
		while (getline(fileName, s))
		{
			if (s.find("[Events]") != std::string::npos)
			{
				while (getline(fileName, s))
				{
					start = (s[12] - '0') * milliseconds_in_hour + std::stoi(s.substr(14, 2)) * milliseconds_in_minute +
							std::stoi(s.substr(17, 2)) * milliseconds_in_second + std::stoi(s.substr(20, 2)) * 10;
					end = (s[23] - '0') * milliseconds_in_hour + std::stoi(s.substr(25, 2)) * milliseconds_in_minute +
						  std::stoi(s.substr(28, 2)) * milliseconds_in_second + std::stoi(s.substr(31, 3)) * 10;
					int k = 0;
					for (int i = 0; i < 9;)
					{
						if (s[k] == ',')
						{
							i++;
						}
						k++;
					}
					text = s.substr(k, s.size() - k);
					auto* block = new blocks_of_subtitle(start, end, text);
					format->m_vector.push_back(block);
				}
			}
		}
	}
}
