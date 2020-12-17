#pragma once

#include <string>
#include <vector>
#include <ctime>

class Score
{
public:
	Score(std::string);
	Score(int);

	int getScore();
	std::string toString();
	std::string toFile();
private:
	int score = 0;
	int day = 0;
	int month = 0;
	int year = 0;
	int hour = 0;
	int minute = 0;
};

