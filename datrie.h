#pragma once

#include <vector>
#include <map>
#include <string>
#include "windows.h"

inline bool Assert(PCSTR file, int line, PCSTR msg)
{
	//if (std::string(file).size() + std::string(msg).size() + 5 > 255)
	//	Assert(nullptr, -1, "msg is too long.");

	char buf[256];
	sprintf_s(buf, 256, "file: %s, line: %d, msg: %s", file, line, msg);
	MessageBoxA(nullptr, buf, "warning", MB_OK | MB_ICONWARNING);
	return true;
}

#define YASSERT(b) (!(b) && Assert(__FILE__, __LINE__, #b ))
#define YZ_ASSERT2(b, msg) (!(b) && Assert(__FILE__, __LINE__, msg))

class DATrie
{
public:
	DATrie();
	void Insert(std::string word);

private:
	int GetArcVal(char ch);
	char GetArcChar(int val);
	int GetBaseVal(int idx);
	void SetBaseVal(int idx, int val);
	int GetCheckVal(int idx);
	void SetCheckVal(int idx, int val);
	int AddToTails(std::string tail);
	std::string GetTail(int idx);
	std::vector<int> CollectNextNodes(int cur);
	int ProbeValidVal(const std::vector<char> &vec);
	void Relocate(int s, int b, const std::vector<char> &vecNext);

private:
	std::vector<int> m_vecBase;
	std::vector<int> m_vecCheck;
	std::map<int, std::string> m_isTails;
};