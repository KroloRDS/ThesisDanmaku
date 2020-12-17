#pragma once

#include "Score.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

class HighscoreLoader
{
public:
	const static int SCORE_ENTRIES = 10;
	const static int SCORE_MODES = 4;
	static std::vector<Score*> load();
	static void save(int, int);
private:
	static const std::string EMPTY_LINE;
	static const std::string FILE_NAME;
};

