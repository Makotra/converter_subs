#include "subtitle.h"
#pragma once
class SubRip : public subtitle
{
  public:
	SubRip();
	static void convert_to_SubRip(SubRip* sub, const std::string& out_put);
};
