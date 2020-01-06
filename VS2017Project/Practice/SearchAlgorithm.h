#pragma once
/*
1.顺序查找：
	基本思想：顺序查找也称为线形查找，属于无序查找算法。从数据结构线形表的一端开始，顺序扫描，依次将扫描到的结点关键字与给定值k相比较，若相等则表示查找成功；若扫描结束仍没有找到关键字等于k的结点，表示查找失败。
	查找成功时的平均查找长度为：（假设每个数据元素的概率相等） ASL = 1/n(1+2+3+…+n) = (n+1)/2 ;
	当查找不成功时，需要n+1次比较，时间复杂度为O(n);
*/	
/*
输入: 数组，查找的值，查找范围
返回: -1：未找到；>-1，则表示位置。

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
2.二分查找：
基本思想：元素必须是有序的，如果是无序的则要先进行排序操作。
也称为是折半查找，属于有序查找算法。用给定值k先与中间结点的关键字比较，中间结点把线形表分成两个子表，若相等则查找成功；若不相等，再根据k与该中间结点关键字的比较结果确定下一步查找哪个子表，这样递归进行，直到查找到或查找结束发现表中没有这样的结点。
最坏情况下，关键词比较次数为log2(n+1)，且期望时间复杂度为O(log2n)；
*/
/*
输入: 数组，查找的值，查找范围
返回: -1：未找到；>-1，则表示位置。

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
3. 二叉树查找算法
*/


