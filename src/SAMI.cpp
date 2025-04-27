#include "SAMI.h"

#include <fstream>
#include <iostream>
#include <string>
SAMI::SAMI() {}
void SAMI::convert_to_SAMI(SAMI* sub, const std::string& out_put)
{
	std::ofstream out(out_put);
	out << "<SAMI>\n";
	out << "<BODY>\n";
	for (size_t count = 0; count < sub->m_vector.size(); count++)
	{
		out << "<SYNC Start=" + std::to_string(sub->m_vector[count]->m_start) + "><P>" + sub->m_vector[count]->m_text + "</P></SYNC>\n";
	}
	out << "</BODY>\n";
	out << "</SAMI>\n";
}
