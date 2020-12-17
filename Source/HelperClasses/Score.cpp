#include "Score.h"

Score::Score(std::string str)
{
	std::string tokens[6] = { "" };
	int token = 0;

	for (int i = 0; i < str.length(); i++)
	{
		char c = str.at(i);
		if (c == ';')
		{
			token++;
			if (token > 5)
			{
				break;
			}
		}
		else
		{
			tokens[token] += c;
		}
	}

	score = std::stoi(tokens[0]);
	day = std::stoi(tokens[1]);
	month = std::stoi(tokens[2]);
	year = std::stoi(tokens[3]);
	hour = std::stoi(tokens[4]);
	minute = std::stoi(tokens[5]);
}

Score::Score(int score)
{
	std::time_t t = std::time(0);
	std::tm* time = std::localtime(&t);

	this->score = score;
	day = time->tm_mday;
	month = time->tm_mon + 1;
	year = time->tm_year + 1900;
	hour = time->tm_hour;
	minute = time->tm_min;
}

int Score::getScore()
{
	return score;
}

std::string Score::toString()
{
	std::string ret = "";
	ret += std::to_string(score) + " (";
	ret += std::to_string(day) + ".";
	ret += std::to_string(month) + ".";
	ret += std::to_string(year) + " ";
	ret += std::to_string(hour) + ":";
	ret += std::to_string(minute) + ")";
	return ret;
}

std::string Score::toFile()
{
	std::string ret = "";
	ret += std::to_string(score) + ";";
	ret += std::to_string(day) + ";";
	ret += std::to_string(month) + ";";
	ret += std::to_string(year) + ";";
	ret += std::to_string(hour) + ";";
	ret += std::to_string(minute) + "\n";
	return ret;
}
