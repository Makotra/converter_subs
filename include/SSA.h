#include "subtitle.h"
#pragma once
class SSA : public subtitle
{
  public:
	SSA();
	static void convert_to_Advanced_Sub_Station_Alpha(SSA* sub, std::string& word);
};
