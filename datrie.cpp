
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
				int j = 0;
				int c = cur;
				while (tail[j] == substr[j])
				{
					char ch = tail[j];
					std::vector<char> vec;
					vec.push_back(ch);
					int q = ProbeValidVal(vec);
					SetBaseVal(c, q);
					c = GetArcVal(ch) + q;
					++j;
				}
				
				std::vector<char> vec;
				vec.push_back(substr[j]);
				vec.push_back(tail[j]);
				int qq = ProbeValidVal(vec);
				std::string s1 = substr.substr(j + 1, substr.size() - j - 1);
				SetBaseVal(GetArcVal(substr[j] + qq), -AddToTails(s1));
				std::string s2 = tail.substr(j + 1, tail.size() - j - 1);
				SetBaseVal(GetArcVal(tail[j] + qq), -AddToTails(s2));
			}
			break;
		}
		else if (cur != cVal && GetBaseVal(cur) > 0)
		{
			std::vector<int> vecNext = CollectNextNodes(cur);
			std::vector<char> vecChar;
			for (int j = 0, n = vecNext.size(); j < n; ++j)
				vecChar.push_back(GetArcChar(vecNext[j] - cur));
			vecChar.push_back(ch);

			int q = ProbeValidVal(vecChar);
			Relocate(cur, q, vecNext);
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

char DATrie::GetArcChar(int val)
{
	return val + 'a' - 1;
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

void DATrie::SetCheckVal(int idx, int val)
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

std::vector<int> DATrie::CollectNextNodes(int idx)
{
	std::vector<int> vec;
	for (int i = 0, n = m_vecCheck.size(); i < n; ++i)
	{
		if (m_vecCheck[i] == idx)
			vec.push_back(i);
	}
	return vec;
}

int DATrie::ProbeValidVal(const std::vector<char> &vec)
{
	int q = 1;
	bool bFind = false;
	while (!bFind)
	{
		bFind = true;
		for (int i = 0, n = vec.size(); i < n; ++i)
		{
			if (GetCheckVal(q + vec[i]) != 0)
				bFind = false;
		}
		++q;
	}
	return q - 1;
}

void DATrie::Relocate(int s, int b, const std::vector<int> &vecNext)
{
	for (int i = 0, n = vecNext.size(); i < n; ++i)
	{
		char ch = vecNext[i];
		YZ_ASSERT (GetCheckVal(b + ch));
		SetCheckVal(b + ch, s);
		SetBaseVal(b + ch, GetBaseVal(GetBaseVal(s) + ch));
		std::vector<int> vec = CollectNextNodes(GetBaseVal(s) + ch);
		for (int ii = 0, nn = vec.size(); ii < nn; ++ii)
		{
			SetCheckVal(vec[ii] + GetBaseVal(GetBaseVal(s) + ch), b + ch);
		}
		SetCheckVal(GetBaseVal(s) + ch, 0);
	}
}

