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
	int ret = MessageBoxA(nullptr, buf, "warning", MB_RETRYCANCEL | MB_ICONWARNING);
	if (IDRETRY == ret)
		return true;
	return false;
}

// you'd better surround the two macros by curly brace.
#define YASSERT(b) if (!(b) && Assert(__FILE__, __LINE__, #b )) __asm int 3;
#define YZ_ASSERT2(b, msg) if (!(b) && Assert(__FILE__, __LINE__, msg)) _asm int 3;

class DATrie
{
public:
	DATrie();
	void Insert(std::string word);
	bool Retrieve(std::string word);

private:
	int GetArcVal(char ch);
	char GetArcChar(int val);
	int GetBaseVal(int idx);
	void SetBaseVal(int idx, int val);
	int GetCheckVal(int idx);
	void SetCheckVal(int idx, int val);
	int AddToTails(std::string tail);
	void RemoveTail(int idx);
	std::string GetTail(int idx);
	std::vector<int> CollectNextNodes(int cur);
	int ProbeValidVal(const std::vector<char> &vec);
	void Relocate(int s, int b, const std::vector<char> &vecNext);

private:
	std::vector<int> m_vecBase;
	std::vector<int> m_vecCheck;
	std::map<int, std::string> m_isTails;
};