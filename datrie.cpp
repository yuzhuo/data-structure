
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
			if (tail == substr)
			{
				break;
			}
			else
			{
				int i = 0;
				while (tail[i] == substr[i])
				{
					int q = 1;
					char ch = tail[i];
					while (GetCheckVal(GetArcVal(ch) + q) == 0)
						++q;
					SetBaseVal(cur, )
				}
				
			}
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


