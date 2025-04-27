#include "SubRip.h"

#include "converter_time.h"

#include <fstream>
SubRip::SubRip() = default;
void SubRip::convert_to_SubRip(SubRip* sub, const std::string& out_put)
{
	std::ofstream out(out_put);
	for (size_t count = 0; count < sub->m_vector.size(); count++)
	{
		out << count + 1 << std::endl;
		format_time(sub->m_vector[count]->m_start, out, ',', false);
		;
		out << " --> ";
		format_time(sub->m_vector[count]->m_end, out, ',', false);
		;
		out << std::endl;
		out << sub->m_vector[count]->m_text << std::endl << std::endl;
	}
}
