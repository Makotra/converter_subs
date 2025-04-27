#include "subtitle.h"

#include <regex>
blocks_of_subtitle::blocks_of_subtitle(int start, int end, std::string &text) : m_start(start), m_end(end), m_text(text)
{
}
blocks_of_subtitle::blocks_of_subtitle() : m_start(0), m_end(0), m_text("") {}
void Vector::resize(size_t new_capacity)
{
	auto **new_data = new blocks_of_subtitle *[new_capacity];
	for (size_t i = 0; i < length; ++i)
	{
		new_data[i] = data[i];
	}
	delete[] data;
	data = new_data;
	capacity = new_capacity;
}
Vector::Vector() : data(nullptr), capacity(0), length(0) {}
Vector::~Vector()
{
	for (size_t i = 0; i < length; ++i)
	{
		delete data[i];
	}
	delete[] data;
	data = nullptr;
	length = 0;
	capacity = 0;
}
void Vector::push_back(blocks_of_subtitle *value)
{
	if (length >= capacity)
	{
		size_t new_capacity;
		new_capacity = (capacity == 0) ? 1 : capacity * 2;
		resize(new_capacity);
	}
	data[length++] = value;
}
size_t Vector::size() const
{
	return length;
}
blocks_of_subtitle *Vector::operator[](size_t index) const
{
	return data[index];
}
subtitle::subtitle() = default;
subtitle::~subtitle() = default;
void subtitle::remove_styles()
{
	std::regex tags(R"(<[^>]+>|\\[ibu][0-9]*|\\[Nn])");
	for (size_t i = 0; i < m_vector.size(); ++i)
	{
		m_vector[i]->m_text = std::regex_replace(m_vector[i]->m_text, tags, "");
	}
}
void subtitle::apply_default_style()
{
	for (size_t i = 0; i < m_vector.size(); ++i)
	{
		m_vector[i]->m_text = "<b>" + m_vector[i]->m_text + "</b>";
	}
}

void subtitle::shift_time(int delta, bool shift_start, bool shift_end)
{
	for (size_t i = 0; i < m_vector.size(); ++i)
	{
		if (shift_start)
			m_vector[i]->m_start += delta;
		if (shift_end)
			m_vector[i]->m_end += delta;
	}
}

subtitle subtitle::search_collision(const subtitle& other) const
{
	subtitle result;
	for (size_t i = 0; i < this->m_vector.size(); ++i)
	{
		for (size_t j = 0; j < other.m_vector.size(); ++j)
		{
			int start1 = this->m_vector[i]->m_start;
			int end1 = this->m_vector[i]->m_end;
			int start2 = other.m_vector[j]->m_start;
			int end2 = other.m_vector[j]->m_end;

			if (start1 < end2 and start2 < end1)
			{
				std::string merged_text = this->m_vector[i]->m_text + "\n" + other.m_vector[j]->m_text;
				auto *block = new blocks_of_subtitle(std::min(start1, start2), std::max(end1, end2), merged_text);
				result.m_vector.push_back(block);
			}
		}
	}
	return result;
}
