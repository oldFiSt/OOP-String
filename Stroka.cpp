#include "Stroka.h"

Stroka::Stroka()
{
	text = nullptr;
	length = 0;
}

Stroka::Stroka(const char *source)
{
	int n = 0;

	for (int i = 0; source[i]; i++)
	{
		n++;
	}

	length = n;
	text = new char[length + 1];

	for (int i = 0; i < length; i++)
	{
		text[i] = source[i];
	}

	text[length] = '\0';
}

Stroka::~Stroka()
{

	for (int i = 0; i < words.size(); i++)
	{
		delete[] words[i].word;
	}

	words.clear();
}

void Stroka::change_Words()
{
	wordStats.clear();
	int start_pos = 0;

	for (int i = 0; text[i]; i++)
	{

		if ((text[i] == '-') && (i > 0) && (i < length - 1) && (text[i - 1] != ' ') && (text[i + 1] != ' '))
		{
			continue;
		}

		if (text[i] == '.' || text[i] == ',')
		{
			if (start_pos < i)
			{
				wordStats.push_back({start_pos, i - 1});
			}

			start_pos = i + 1;
		}

		if (text[i] == ' ')
		{

			if (start_pos < i)
			{
				wordStats.push_back({start_pos, i - 1});
			}

			start_pos = i + 1;
		}
	}

	if (start_pos < length)
	{
		wordStats.push_back({start_pos, length - 1});
	}
}

void Stroka::create_Words()
{
	for (int n = 0; n < wordStats.size(); n++)
	{
		int start = wordStats[n].first;
		int end = wordStats[n].second;

		int length_word = end - start + 1;
		WordInfo info;

		info.word = new char[length_word + 1];

		for (int i = 0; i < length_word; i++)
		{
			info.word[i] = text[start + i];
		}

		info.word[length_word] = '\0';

		info.count = 1;
		info.firstPosition = n;

		words.push_back(info);
	}
}

int Stroka::research_Words(const char *sub, int length_sub)
{

	for (int i = 0; i <= length - length_sub; i++)
	{

		bool flag = true;

		for (int j = 0; j < length_sub; j++)
		{
			if (text[i + j] != sub[j])
			{
				flag = false;
				break;
			}
		}

		if (flag)
		{
			return i;
		}
	}

	return -1;
}