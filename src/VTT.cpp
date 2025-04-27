#include "VTT.h"

#include "converter_time.h"

#include <fstream>

VTT::VTT() = default;

void VTT::convert_to_VTT(VTT* sub, const std::string& out_put)
{
	std::ofstream out(out_put);
	out << "WEBVTT\n\n";

	for (size_t count = 0; count < sub->m_vector.size(); count++)
	{
		format_time(sub->m_vector[count]->m_start, out, '.', true);
		out << " --> ";
		format_time(sub->m_vector[count]->m_end, out, '.', true);
		out << std::endl;
		out << sub->m_vector[count]->m_text << std::endl << std::endl;
	}
}
