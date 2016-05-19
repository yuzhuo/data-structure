


#include "datrie.h"
#include <set>
#include <iostream>
#include "stdlib.h"
#include "stdio.h"
#include <algorithm>
#include "time.h"

void check(char ch)
{
	static std::set<char> charSet;
	static int line = 0;
	if (ch == '\n')
		++line;

	charSet.insert(ch);
	YASSERT (ch >= 'a' && ch <= 'z' || ch == '\n' || ch == '\r' || ch >= 'A' && ch <= 'Z');
}

std::string getLine(FILE *file)
{
	std::string str;
	char ch = -1;
	while ((ch = fgetc(file)) != EOF)
	{
		if (ch != '\n')
			str.push_back(ch);
		else
			break;
	}
	return str;
}

int main()
{
	time_t start = time(NULL);
	char buf[128];
	ctime_s(buf, 128, &start);
	printf("start: %s", buf);

	FILE *file = NULL;
	FILE *file2 = NULL;
	fopen_s(&file, "cet-4.txt", "r");
	fopen_s(&file2, "cet-6.txt", "r");
	// FILE *out;
	// fopen_s(&out, "cet-4_dup.txt", "wb");

	if (file == NULL)
		return -1;

	//char ch = -1;
	//while ((ch = fgetc(file)) != EOF)
	//{
	//	check(ch);
	//}
	//return 0;

	DATrie trie;

	std::set<std::string> cet6Set;
	std::string cet6_word = getLine(file2);
	int line2 = 0;
	while (cet6_word.length() != 0)
	{
		std::transform(cet6_word.begin(), cet6_word.end(), cet6_word.begin(), ::tolower);
		cet6Set.insert(cet6_word);
		cet6_word.clear();
		cet6_word = getLine(file2);
		++line2;
	}

	std::set<std::string> cet4Set;
	std::string str = getLine(file);
	int line = 0;
	while (str.length() != 0)
	{
		// fprintf(out, "%s\n", str.c_str());
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		trie.Insert(str);
		cet4Set.insert(str);
		str.clear();
		str = getLine(file);
		++line;
	}
	printf("line: %d\n", line);
	for (auto it = cet4Set.begin(); it != cet4Set.end(); ++it)
	{
		if (!trie.Retrieve(*it))
		{
			YASSERT (true);
		}
	}
	for (auto it = cet6Set.begin(); it != cet6Set.end(); ++it)
	{
		if (cet4Set.find(*it) != cet4Set.end())
		{
			YASSERT (trie.Retrieve(*it));
		}
		else
		{
			YASSERT (!trie.Retrieve(*it));
		}
	}


	fclose(file);
	// fclose(out);

	time_t end = time(NULL);
	ctime_s(buf, 128, &end);
	printf("end: %s", buf);
	system("pause");

	return 0;
}