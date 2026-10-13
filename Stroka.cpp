#include "Stroka.h"
#include <algorithm>
#include <iostream>
#include <fstream>

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

	delete[] text;

	for (int i = 0; i < words.size(); i++)
	{
		delete[] words[i].word;
	}
}

// отделение слов в строке
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

// создание слов из сохраненных значений
void Stroka::create_Words()
{
	for (int i = 0; i < words.size(); i++)
	{
		delete[] words[i].word;
	}

	words.clear();

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

// поиск подстроки
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

//
void Stroka::count_WordStats()
{
	std::vector<WordInfo> uniqueWords;

	for (int i = 0; i < words.size(); i++)
	{
		bool found = false;

		for (int j = 0; j < uniqueWords.size(); j++)
		{
			bool same = true;
			int k = 0;

			while (words[i].word[k] != '\0' ||
						 uniqueWords[j].word[k] != '\0')
			{

				char a = words[i].word[k];
				char b = uniqueWords[j].word[k];

				if (a >= 'A' && a <= 'Z')
				{
					a += 32;
				}

				if (b >= 'A' && b <= 'Z')
				{
					b += 32;
				}

				if (a != b)
				{
					same = false;
					break;
				}

				k++;
			}

			if (same)
			{
				uniqueWords[j].count++;
				found = true;
				break;
			}
		}

		if (!found)
		{
			WordInfo info;

			int len = 0;

			while (words[i].word[len] != '\0')
			{
				len++;
			}

			info.word = new char[len + 1];

			for (int k = 0; k < len; k++)
			{
				info.word[k] = words[i].word[k];
			}

			info.word[len] = '\0';

			info.count = 1;
			info.firstPosition = words[i].firstPosition;

			uniqueWords.push_back(info);
		}
	}

	for (int i = 0; i < words.size(); i++)
	{
		delete[] words[i].word;
	}

	words.clear();

	words = uniqueWords;
}

int Stroka::count_Words()
{
	int n = 0;

	for (int i = 0; i < words.size(); i++)
	{
		n += words[i].count;
	}

	return n;
}

void Stroka::print_Words(SortType type)
{
	std::vector<WordInfo> temp = words;

	if (type == ALPHABET)
	{
		std::sort(temp.begin(), temp.end(),
							[](const WordInfo &a, const WordInfo &b)
							{
								int i = 0;

								while (a.word[i] != '\0' && b.word[i] != '\0')
								{
									if (a.word[i] < b.word[i])
										return true;

									if (a.word[i] > b.word[i])
										return false;

									i++;
								}

								return a.word[i] == '\0' && b.word[i] != '\0';
							});
	}

	else if (type == FIRST_POSITION)
	{
		std::sort(temp.begin(), temp.end(),
							[](const WordInfo &a, const WordInfo &b)
							{
								return a.firstPosition < b.firstPosition;
							});
	}

	else if (type == BY_COUNT)
	{
		std::sort(temp.begin(), temp.end(),
							[](const WordInfo &a, const WordInfo &b)
							{
								return a.count > b.count;
							});
	}

	for (int i = 0; i < temp.size(); i++)
	{
		std::cout << temp[i].word
							<< " - "
							<< temp[i].count
							<< '\n';
	}
}

void Stroka::analyze()
{
	change_Words();
	create_Words();
	count_Words();
}

bool Stroka::loadFromFile(const char *filename)
{
	std::ifstream file(filename);

	if (!file)
	{
		return false;
	}

	// узнаём размер файла
	file.seekg(0, std::ios::end);
	int size = file.tellg();
	file.seekg(0, std::ios::beg);

	// удаляем старый текст
	delete[] text;

	length = size;
	text = new char[length + 1];

	// читаем весь файл
	file.read(text, length);

	text[length] = '\0';

	file.close();

	return true;
}