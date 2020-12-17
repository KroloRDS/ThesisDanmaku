#include "HighscoreLoader.h"

const std::string HighscoreLoader::FILE_NAME = "scores.dat";
const std::string HighscoreLoader::EMPTY_LINE = "*";

std::vector<Score*> HighscoreLoader::load()
{
	std::vector<Score*> scores;

	std::string line;
	std::ifstream file(FILE_NAME);
	while (std::getline(file, line))
	{
		Score* score = line.compare(EMPTY_LINE) ? new Score(line) : nullptr;
		scores.push_back(score);
	}

	while (scores.size() < SCORE_ENTRIES * SCORE_MODES)
	{
		scores.push_back(nullptr);
	}

	return scores;
}

void HighscoreLoader::save(int mode, int scoreAmount)
{
	std::vector<Score*> scores = load();

	for (int i = mode * SCORE_ENTRIES; i < (mode + 1) * SCORE_ENTRIES; i++)
	{
		if (scores.at(i) == nullptr || scores.at(i)->getScore() <= scoreAmount)
		{
			scores.insert(scores.begin() + i, new Score(scoreAmount));
			scores.erase(scores.begin() + (mode + 1) * SCORE_ENTRIES);
			break;
		}
	}

	auto it = scores.begin();
	std::ofstream file;
	file.open(FILE_NAME);
	while (it != scores.end())
	{
		std::string buf = (*it) != nullptr ? (*it)->toFile() : EMPTY_LINE + "\n";
		file << buf;
		it++;
	}
	file.close();
}
