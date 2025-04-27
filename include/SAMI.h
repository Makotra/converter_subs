#include "subtitle.h"
#pragma once
class SAMI : public subtitle
{
  public:
	SAMI();
	static void convert_to_SAMI(SAMI* sub, const std::string& out_put);
};
