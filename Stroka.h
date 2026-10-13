#ifndef STROKA_H
#define STROKA_H

#include <vector>

class Stroka
{
private:
	char *text;
	int length;
	int wordCount;
	std::vector<std::pair<int, int>> wordStats;

	struct WordInfo
	{
		char *word;
		int count;
		int firstPosition;
	};

	std::vector<WordInfo> words;

public:
	enum SortType
	{
		ALPHABET,
		FIRST_POSITION,
		BY_COUNT
	};
	Stroka();
	Stroka(const char *source);
	~Stroka();

	int research_Words(const char *sub, int length_sub);
	void count_WordStats();

	void change_Words();
	void create_Words();
	bool loadFromFile(const char *filename);
	int count_Words();
	void print_Words(SortType type);
	void analyze();
};

#endif
