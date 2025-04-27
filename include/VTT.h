#include "subtitle.h"
#pragma once
class VTT : public subtitle
{
  public:
	VTT();
	static void convert_to_VTT(VTT* sub, const std::string& word);
};
