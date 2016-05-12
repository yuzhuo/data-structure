
#include "datrie.h"
#include "ctype.h"

DATrie::DATrie()
{
	m_vecBase.resize(2);
	m_vecBase[1] = 1;
}

void DATrie::Insert(std::string word)
{
	int cur = 1;
	int next = -1;
	for (int i = 0, n = word.size(); i < n; ++i)
	{
		char ch = word[i];
		next = GetBaseVal(cur) + GetArcVal(ch);
		int cVal = GetCheckVal(next);
		std::string substr = word.substr(i + 1, word.size() - i - 1);
		if (0 == cVal)
		{
			std::string tail = substr;
			tail.push_back('#');
			SetBaseVal(next, -AddToTails(tail));
			break;
		}
		else if (cur != cVal && GetBaseVal(next) < 0) // collision
		{
			std::string tail = GetTail(GetBaseVal(next));
			substr.push_back('#');
			if (tail != substr)
			{
				int i = 0;
				int c = cur;
				while (tail[i] == substr[i])
				{
					int q = 1;
					char ch = tail[i];
					while (GetCheckVal(GetArcVal(ch) + q) == 0)
						++q;
					SetBaseVal(c, q);
					c = GetArcVal(ch) + q;
				}
				
				int qq = 1;
				while (GetCheckVal(GetArcVal(substr[i]) + qq)) == 0 &&
					GetCheckVal(GetArcVal(tail[i] + qq) == 0)
					++qq;
				std::string s1 = substr.substr(i + 1, substr.size() - i - 1);
				SetBaseVal(GetArcVal(substr[i] + qq), -AddToTails(s1));
				std::string s2 = tail.substr(i + 1, tail.size() - i - 1);
				SetBaseVal(GetArcVal(tail[i] + qq) -AddToTails(s2));
			}
			break;
		}
		else if (cur != cVal && GetBaseVal(cur) > 0)
		{
			// most complicated case
		}
		cur = next;
	}
}

int DATrie::GetArcVal(char ch)
{
	YZ_ASSERT (ch >= 'a' && ch <= 'z');

	return ch - 'a' + 1;
}

int DATrie::GetBaseVal(int idx)
{
	return -1;
}

void DATrie::SetBaseVal(int idx, int val)
{
}

int DATrie::GetCheckVal(int idx)
{
	return -1;
}

void DATrie::SetCheckVal(int idx)
{

}

int DATrie::AddToTails(std::string tail)
{
	m_isTails.insert(make_pair(m_isTails.size(), tail));
	return m_isTails.size() - 1;
}

std::string DATrie::GetTail(int idx)
{
	YZ_ASSERT (idx < 0);
	idx = -idx;
	YZ_ASSERT (m_isTails.find(idx) != m_isTails.end());
	return m_isTails[idx];
}


