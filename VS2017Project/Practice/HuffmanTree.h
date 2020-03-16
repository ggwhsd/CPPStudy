#pragma once
#include <iostream>
#include <iomanip>//���ͷ�ļ�������һЩ ��������������
//�Ƚϳ��õ���:setw(int);//������ʾ��ȣ�left//right//�������Ҷ��롣 setprecision(int);//���ø������ľ�ȷ�ȡ�
using namespace std;
//http://c.biancheng.net/view/3398.html
//���鷽ʽʵ�ֹ�������
typedef struct {
	int weight;
	int parent;
	int left, right;   
} HTNode;
//HT�����д�ŵĹ���������end��ʾHT�����д�Ž�������λ�ã�s1��s2���ݵ���HT������Ȩ��ֵ��С����������������е�λ��
void SelectMin(HTNode* HT, int end, int &s1, int &s2)
{
	for (int i = 0; i < end; i++)
	{
		if (HT[i].parent == -1)
		{
			s1 = i;
			break;
		}
	}
	for (int i = 0; i < end; i++)
	{
		if (HT[i].parent == -1 && HT[s1].weight > HT[i].weight)
		{
			s1 = i;
		}
	}

	for (int j = 0; j < end; j++)
	{
		if (HT[j].parent == -1 && j != s1)
		{
			s2 = j;
			break;
		}
	}
	for (int j = 0; j < end; j++)
	{
		if (HT[j].parent == -1 && HT[s2].weight > HT[j].weight && j != s1)
			s2 = j;
	}
}


void CreateHuffmanTree(HTNode *huftree, int w[], int end)
{
	for (int i = 0; i < 2 * end - 1; i++)
	{
		huftree[i].parent = -1;
		huftree[i].left = -1;
		huftree[i].right = -1;

	}
	for (int i = 0; i < end; i++)
	{
		huftree[i].weight = w[i];
	}
	//n��Ҷ��Ԫ�أ���Ҫ����2*n-1�����ڵ�
	for (int k = end; k < 2 * end - 1; k++)
	{
		int i1;
		int i2;
		SelectMin(huftree, k, i1, i2);
		huftree[i1].parent = k;
		huftree[i2].parent = k;
		huftree[k].left = i1;
		huftree[k].right = i2;
		huftree[k].weight = huftree[i1].weight + huftree[i2].weight;
		//�µĺϳɽڵ㶼��parent=-1��Ĭ��ֵ��
		
	}
}

void HufTreePrint(HTNode *ht, int n)
{
	cout << "index weight parent lchild rchild" << endl;
	cout << left;
	for (int i = 0; i < n; i++)
	{
		cout << setw(5) << i << " ";
		cout << setw(6) << ht[i].weight << " ";
		cout << setw(6) << ht[i].parent << " ";
		cout << setw(6) << ht[i].left << " ";
		cout << setw(6) << ht[i].right << endl;
	}
}


void testHTnode()
{ 
	int w[] = { 6,3,12,3,44,1,26,33 };
	int len = sizeof(w) / sizeof(int);
	int num = 2 * sizeof(w) / sizeof(int) - 1;
	HTNode *hufftree = new HTNode[num];
	CreateHuffmanTree(hufftree, w, len);
	HufTreePrint(hufftree, num);



}