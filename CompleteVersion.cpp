#include<iostream>
#include<string.h>
#include<assert.h>
using namespace std;

class Node
{
public:
	string data;
	Node* link;
	Node(string a)
	{
		data = a;
		link = NULL;
	}
};
class List
{
public:
	Node* phead;
public:
	List()
	{
		phead = NULL;
	}
	~List() { }
	bool enqueue(string akd) //�������������ַ����������
	{
		Node* cur = phead;
		if (phead == NULL) phead = new Node(akd);
		else
		{
			while (cur->link != NULL)
			{
				cur = cur->link;
			}
			cur->link = new Node(akd);
		}
		return true;
	}
	bool check(string akd)
	{
		Node* cur = phead;
		while (cur != NULL)
		{
			if (cur->data == akd) return false;
			cur = cur->link;
		}
		return true;
	}
	void print()
	{
		Node* cur = phead;
		while (cur != NULL)
		{
			cout << cur->data << " ";
			cur = cur->link;
		}
		cout << endl;
	}
};
int* Next(string P) //���KMP�㷨���������������
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
			k = N[k - 1];
		if (P[i] == P[k])		N[i] = k + 1;
		else N[i] = 0;
	}
	return N;
} 
int KMPStrMatching(string T, string P, int* N, int startIndex)		//KMP�㷨���ж�P�ַ����Ƿ���T�ַ�������Ϊ�Ӵ�����
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
void JudgeTheSubstring(string* test, int capacity, double threshold)
{
	string temp;
	List target;
	int existence = 0;
	int flag = 1;
	for (int i = 0; i <floor(capacity*(1-threshold)); i++)	//��һ��ѭ���������η����ַ��������е�ÿ��Ԫ��
		for (int cursor = 0; cursor < test[i].length(); cursor++)		//�ڶ���ѭ�������ƶ�����λ��
			for (int length = 1; length <= test[i].length(); length++)		//������ѭ���������������ִ��ĳ���
			{
				temp = test[i].substr(cursor, length);
				for (int j = 0; j < capacity; j++)	//�����е��ַ��������β��Ҹ��Ӵ��Ƿ����
					if (KMPStrMatching(test[j], temp, Next(temp), 0) != (-1))
						existence++;	//��������ˣ�existence����+1
				if ((double)existence / (double)capacity > threshold)	//ѭ����������һ�����ֵ�Ƶ���Ƿ������ֵ
				{
					if (target.check(temp))		//����Ƿ��ڶ����г��ֹ��������ֹ�����д��������
						target.enqueue(temp);
				}
				else 
				{
					existence = 0;
					break; 
				}
				existence = 0;		//һ���Ӵ���������������existence����
			}
	target.print(); //�����������������з����������Ӵ�
}
int main()
{
	int capa; cout << "�������ַ����ܸ�����"; cin >> capa;
	double thre; cout << "��������ֵ��"; cin >> thre; 
	cout << "�����������ַ��������ո��س�������" << endl;
	string *st=new string[capa];
	for (int i = 0; i < capa; i++)
		cin >> st[i];
	JudgeTheSubstring(st, capa, thre);
}