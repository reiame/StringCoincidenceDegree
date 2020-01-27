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
	bool enqueue(string akd) //将符合条件的字符串加入队列
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
int* Next(string P) //求出KMP算法中所需的特征向量
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
int KMPStrMatching(string T, string P, int* N, int startIndex)		//KMP算法，判断P字符串是否在T字符串中作为子串出现
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
	for (int i = 0; i <floor(capacity*(1-threshold)); i++)	//第一层循环，是依次访问字符串数组中的每个元素
		for (int cursor = 0; cursor < test[i].length(); cursor++)		//第二层循环，是移动光标的位置
			for (int length = 1; length <= test[i].length(); length++)		//第三层循环，是依次增长字串的长度
			{
				temp = test[i].substr(cursor, length);
				for (int j = 0; j < capacity; j++)	//从所有的字符串中依次查找该子串是否出现
					if (KMPStrMatching(test[j], temp, Next(temp), 0) != (-1))
						existence++;	//如果出现了，existence变量+1
				if ((double)existence / (double)capacity > threshold)	//循环结束，看一看出现的频率是否高于阈值
				{
					if (target.check(temp))		//检测是否在队列中出现过，若出现过不再写入链表中
						target.enqueue(temp);
				}
				else 
				{
					existence = 0;
					break; 
				}
				existence = 0;		//一个子串计数结束，重置existence变量
			}
	target.print(); //最后遍历链表，访问所有符合条件的子串
}
int main()
{
	int capa; cout << "请输入字符串总个数："; cin >> capa;
	double thre; cout << "请输入阈值："; cin >> thre; 
	cout << "请批量输入字符串，按空格或回车结束：" << endl;
	string *st=new string[capa];
	for (int i = 0; i < capa; i++)
		cin >> st[i];
	JudgeTheSubstring(st, capa, thre);
}