
#include <iostream>
#include <utility>
#include <memory>
#include <vector>
using namespace std;



void makeNext(const char *pat, int *next)
{
	int k = 0;
	next[0] = 0;

	for (int i = 1; i < (int)strlen(pat); ++i)
	{
		while (k > 0 && pat[k] != pat[i])
			k = next[k - 1];

		if (pat[k] == pat[i])
			++k;
		next[i] = k;
	}
}

void kmpsearch(const char *str, const char *pat)
{
	vector<int> next;
	next.resize(strlen(pat));
	makeNext(pat, &next[0]);

	int n = strlen(str);
	int m = strlen(pat);

	int j = 0;
	for (int i = 0; i < n; ++i)
	{
		while (str[i] != pat[j] && j > 0)
		{
			j = next[j];
		}

		if (str[i] == pat[j])
			++j;

		if (m == j)
		{
			cout << "found pattern at index: " <<  i - m + 1 << endl;
			j = next[j - 1];
		}
	}
}

int main()
{
	char *str = "ABABDABACDABABCABAB";
	char *pat = "ABABCABAB";

	kmpsearch(str, pat);

	return 0;
}

