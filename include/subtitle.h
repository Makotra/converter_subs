#pragma once
#include <string>
class subtitle;
class blocks_of_subtitle
{
	friend class subtitle;
	friend class VTT;
	friend class SubRip;
	friend class SAMI;
	friend class SSA;

//  private:
//	int m_start;
//	int m_end;
//	std::string m_text;

  public:
    int m_start;
	int m_end;
	std::string m_text;
	blocks_of_subtitle();
	blocks_of_subtitle(int start, int end, std::string& text);
};
class Vector
{
  private:
	blocks_of_subtitle** data;
	size_t capacity;
	size_t length;
	void resize(size_t new_capacity);

  public:
	Vector();
	~Vector();
	void push_back(blocks_of_subtitle* value);
	blocks_of_subtitle* operator[](size_t index) const;
	size_t size() const;
};
class subtitle
{
	friend class SubtitleTest;
	template< typename T >
	friend void parsing(std::ifstream& fileName, T& format);

//  protected:
//	Vector m_vector;

  public:
    Vector m_vector;
	subtitle();
	~subtitle();
	void remove_styles();
	void apply_default_style();
	void shift_time(int delta, bool shift_start, bool shift_end);
	subtitle search_collision(const subtitle& other) const;
};
