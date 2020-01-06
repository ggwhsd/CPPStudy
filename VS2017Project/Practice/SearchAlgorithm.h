#pragma once
/*
1.˳����ң�
	����˼�룺˳�����Ҳ��Ϊ���β��ң�������������㷨�������ݽṹ���α��һ�˿�ʼ��˳��ɨ�裬���ν�ɨ�赽�Ľ��ؼ��������ֵk��Ƚϣ���������ʾ���ҳɹ�����ɨ�������û���ҵ��ؼ��ֵ���k�Ľ�㣬��ʾ����ʧ�ܡ�
	���ҳɹ�ʱ��ƽ�����ҳ���Ϊ��������ÿ������Ԫ�صĸ�����ȣ� ASL = 1/n(1+2+3+��+n) = (n+1)/2 ;
	�����Ҳ��ɹ�ʱ����Ҫn+1�αȽϣ�ʱ�临�Ӷ�ΪO(n);
*/	
/*
����: ���飬���ҵ�ֵ�����ҷ�Χ
����: -1��δ�ҵ���>-1�����ʾλ�á�

*/
int SequenceSearch(int a[], int value, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (a[i] == value)
			return i;
	}
	return -1;
}

void testSequenceSearch()
{
	int a[] = { 0,3,2,7,6,3,1,5,7,0,11,3,15,23 };
	int number = sizeof(a) / sizeof(int);
	int index = SequenceSearch(a, 11, number);
	cout << index << endl;
}

/*
2.���ֲ��ң�
����˼�룺Ԫ�ر���������ģ�������������Ҫ�Ƚ������������
Ҳ��Ϊ���۰���ң�������������㷨���ø���ֵk�����м���Ĺؼ��ֱȽϣ��м�������α�ֳ������ӱ����������ҳɹ���������ȣ��ٸ���k����м���ؼ��ֵıȽϽ��ȷ����һ�������ĸ��ӱ������ݹ���У�ֱ�����ҵ�����ҽ������ֱ���û�������Ľ�㡣
�����£��ؼ��ʱȽϴ���Ϊlog2(n+1)��������ʱ�临�Ӷ�ΪO(log2n)��
*/
/*
����: ���飬���ҵ�ֵ�����ҷ�Χ
����: -1��δ�ҵ���>-1�����ʾλ�á�

*/
int BinarySearch_v1(int a[],int value, int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (a[mid] == value)
			return mid;
		else if (a[mid] > value)
			high = mid - 1;
		else
			low = mid + 1;

	}
	return -1;
}
int BinarySearch_v2(int a[], int value, int low,int high)
{
	int mid = low + (high - low) / 2;    //   <==>  (low+high)/2

	if (low > mid)
		return -1;
	else if (a[mid] == value)
		return mid;
	else if (a[mid] > value)
		return BinarySearch_v2(a, value, low, mid - 1);
	else
		return BinarySearch_v2(a, value, mid + 1, high);
}

void testBinarySearch_v1()
{
	int a[] = { 0,3,2,7,6,3,1,5,7,0,11,3,15,23 };
	sort(begin(a), end(a));
	int number = sizeof(a) / sizeof(int);
	int index = BinarySearch_v1(a, 11, number);
	cout << index << endl;
	index = BinarySearch_v2(a, 11, 0,number-1);
	cout << index << endl;
}

/*
3. �����������㷨
*/


