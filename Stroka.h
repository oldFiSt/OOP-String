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
	Stroka();
	Stroka(const char *source);
	~Stroka();

	void add_Text(const char *info);
	int countWords() const;
	int research_Words(const char *sub, int length, int length_sub);

	void change_Words();
	void create_Words();
	bool loadFromFile(const char *filename);
};

#endif
