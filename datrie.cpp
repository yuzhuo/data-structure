
#include "datrie.h"
#include "ctype.h"

DATrie::DATrie()
{
	m_vecBase.resize(2);
	m_vecBase[1] = 1;
}

void DATrie::Insert(std::string word)
{
	word.push_back('#');
	int cur = 1;
	int next = -1;
	for (int i = 0, n = word.size(); i < n; ++i)
	{
		char ch = word[i];
		next = GetBaseVal(cur) + GetArcVal(ch);
		std::string substr = word.substr(i + 1, word.size() - i - 1);
		if (GetCheckVal(next) == cur && GetBaseVal(next) < 0)
		{
			std::string tail = GetTail(GetBaseVal(next));
			if (tail != substr)
			{
				int j = 0;
				int c = next;
				if (tail[j] == substr[j])
					RemoveTail(GetBaseVal(next));

				while (tail[j] == substr[j])
				{
					char ch = tail[j];
					std::vector<char> vec;
					vec.push_back(ch);
					int q = ProbeValidVal(vec);
					SetBaseVal(c, q);
					SetCheckVal(GetArcVal(ch) + q, c);
					c = GetArcVal(ch) + q;
					++j;
				}

				std::vector<char> vec;
				vec.push_back(substr[j]);
				vec.push_back(tail[j]);
				int qq = ProbeValidVal(vec);
				SetBaseVal(c, qq);
				std::string s1 = substr.substr(j + 1, substr.size() - j - 1);
				SetBaseVal(GetArcVal(substr[j]) + qq, AddToTails(s1));
				SetCheckVal(GetArcVal(substr[j]) + qq, c);
				std::string s2 = tail.substr(j + 1, tail.size() - j - 1);
				SetBaseVal(GetArcVal(tail[j]) + qq, AddToTails(s2));
				SetCheckVal(GetArcVal(tail[j]) + qq, c);
			}
			break;
		}
		else if (GetCheckVal(next) == 0)
		{
			std::string tail = substr;
			SetBaseVal(next, AddToTails(tail));
			SetCheckVal(next, cur);
			break;
		}
		else if (GetCheckVal(next) != cur)
		{
			std::vector<int> vecNext = CollectNextNodes(cur);
			std::vector<char> vecChar;
			for (int j = 0, n = vecNext.size(); j < n; ++j)
				vecChar.push_back(GetArcChar(vecNext[j] - GetBaseVal(cur)));
			vecChar.push_back(ch);

			int q = ProbeValidVal(vecChar);
			vecChar.pop_back();
			Relocate(cur, q, vecChar);
			int chVal = GetArcVal(ch);
			SetBaseVal(GetBaseVal(cur) + chVal, AddToTails(substr));
			SetCheckVal(GetBaseVal(cur) + chVal, cur);
			break;
		}
		cur = next;
	}
}

bool DATrie::Retrieve(std::string word)
{
	word.push_back('#');
	int cur = 1;
	int next = -1;
	int i = 0;
	for (int i = 0, n = word.size(); i < n; ++i)
	{
		std::string substr = word.substr(i + 1, n - i - 1);
		next = GetBaseVal(cur) + GetArcVal(word[i]);
		if (GetCheckVal(next) == cur)
		{
			if (GetBaseVal(next) < 0)
			{
				if (GetTail(GetBaseVal(next)) == substr)
					return true;
				else
					return false;
			}
			else
			{
				cur = next;
				continue;
			}
		}
		else
		{
			return false;
		}
	}
	return false;
}

int DATrie::GetArcVal(char ch)
{
	YASSERT (ch >= 'a' && ch <= 'z' || ch == '#');

	if (ch == '#')
		return 27;
	return ch - 'a' + 1;
}

char DATrie::GetArcChar(int val)
{
	YASSERT(val >= 1 && val <= 27);
	if (val == 27)
		return '#';
	return val + 'a' - 1;
}

int DATrie::GetBaseVal(int idx)
{
	YASSERT (idx >= 0);
	if (idx >= m_vecBase.size())
		return 0;
	return m_vecBase[idx];
}

void DATrie::SetBaseVal(int idx, int val)
{
	YASSERT (idx >= 0);
	if (idx >= m_vecBase.size())
		m_vecBase.resize(idx + 1, 0);
	m_vecBase[idx] = val;
}

int DATrie::GetCheckVal(int idx)
{
	YASSERT (idx >= 0);
	if (idx >= m_vecCheck.size())
		return 0;
	return m_vecCheck[idx];
}

void DATrie::SetCheckVal(int idx, int val)
{
	YASSERT (idx >= 0);
	if (idx >= m_vecCheck.size())
		m_vecCheck.resize(idx + 1);
	m_vecCheck[idx] = val;
}

int DATrie::AddToTails(std::string tail)
{
	// YASSERT (!tail.empty());
	m_isTails.insert(make_pair(m_isTails.size() + 1, tail));
	return -static_cast<int>(m_isTails.size());
}

void DATrie::RemoveTail(int idx)
{
	// m_isTails.erase(-idx);
}

std::string DATrie::GetTail(int idx)
{
	YASSERT (idx < 0);
	idx = -idx;
	YASSERT (m_isTails.find(idx) != m_isTails.end());
	return m_isTails[idx];
}

std::vector<int> DATrie::CollectNextNodes(int cur)
{
	YASSERT (cur > 0);
	std::vector<int> vec;
	for (int i = 0, n = m_vecCheck.size(); i < n; ++i)
	{
		if (m_vecCheck[i] == cur)
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
			if (GetCheckVal(q + GetArcVal(vec[i])) != 0)
				bFind = false;
		}
		++q;
	}
	return q - 1;
}

void DATrie::Relocate(int s, int b, const std::vector<char> &vecNext)
{
	for (int i = 0, n = vecNext.size(); i < n; ++i)
	{
		int val = GetArcVal(vecNext[i]);
		YASSERT (GetCheckVal(b + val) == 0);
		SetCheckVal(b + val, s);
		SetBaseVal(b + val, GetBaseVal(GetBaseVal(s) + val));
		std::vector<int> vec = CollectNextNodes(GetBaseVal(s) + val);
		for (int ii = 0, nn = vec.size(); ii < nn; ++ii)
		{
			SetCheckVal(vec[ii], b + val);
		}
		SetBaseVal(GetBaseVal(s) + val, 0);
		SetCheckVal(GetBaseVal(s) + val, 0);
	}
	SetBaseVal(s, b);
}

