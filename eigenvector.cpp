#include<string.h>
#include<iostream>
#include<assert.h>
using namespace std;
int* Next(string P)
{
	int m = P.length();
	assert(m > 0);
	int* N = new int[m];
	assert(N != 0);
	N[0] = 0;
	for (int i = 1; i < m; i++)
	{
		int k = N[i - 1];
		while (k > 0 && P[i] != P[k])
		{
			k = N[k - 1];
		}
		if (P[i] == P[k])		N[i] = k + 1;
		else N[i] = 0;
	}
	return N;
}
int KMPStrMatching(string T, string P, int* N, int startIndex)
{
	int lastIndex = T.length() - P.length();
	if ((lastIndex - startIndex) < 0)
		return -1;
	int i; int j = 0;
	for (i = startIndex; i < T.length(); i++)
	{
		while (P[j] != T[i] && j > 0)
			j = N[j - 1];
		if (P[j] == T[i]) j++;
		if (j == P.length()) return (i - j + 1);
	}
	return -1;
}
int length(int* a)
{
	int i = 0, j = 0;
	while (a[i] != NULL)
	{
		j++;
		i++;
	}
	return j;
}
int* append(int* a, int b)
{
	int* f = new int[length(a)+b];
	for (int i = 0; i < length(a); i++)
	{
		f[i] = a[i];
	}
	return f;
}
int main()
{
	string *c=new string[2];
	string a = "acabaabaabcacabab";
	string b = "baabca";
	/*int* n = Next(a);
	for (int i = 0; i < a.length(); i++)
		cout << n[i];
	cout << endl;
	cout << KMPStrMatching(a, b, n, 0) << endl;
	*/
/*	int* n = new int[3];
	for (int i = 0; i < 3; i++)
		n[i] = i + 1;
	n = append(n, 4);
	for (int i = 3; i < 7; i++)
		n[i] = i + 1;
	for (int i = 0; i < 7; i++)
		cout << n[i];*/
	cout << sizeof(c)<<endl;
	cout << sizeof(b);
}