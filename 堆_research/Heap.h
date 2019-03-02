#pragma once
#include <iostream>

using namespace std;

#define TRUE 1
#define FALSE 0

#define OK 1
#define ERROR 0
//#define OVERFLOW -1

typedef int Status;

#define KeyType int

typedef struct RcdType {
	KeyType key;
}RcdType, *RcdList;

typedef struct RcdSqList {
	RcdType *rcd;
	int length;
	int size;
}RcdSqList;

typedef struct
{
	RcdType *rcd;
	//关键字数组
	int n;
	//堆的长度
	int size;
	//堆的容量
	int tag;
	//是否为小顶堆/大顶堆（0/1）
	int(*prior)(KeyType, KeyType);
	//函数变量，大小顶堆的优先函数
}Heap;

//大顶堆优先函数
int greatPrior(int x, int y)
{
	return x >= y;
}

//小顶堆优先函数
int lessPrior(int x, int y)
{
	return x <= y;
}



//交换H中的i结点和j结点元素
Status swapHeapElem(Heap &H, int i, int j)
{
	RcdType t;
	if (i <= 0 || i > H.n || j <= 0 || j > H.n)
		return ERROR;
	t = H.rcd[i];
	H.rcd[i] = H.rcd[j];
	H.rcd[j] = t;
	return OK;
}

//堆调整函数
void ShiftDown(Heap &H, int pos)
{
	//对H位置中为pos的节点做筛选，将pos为根的子树调整为子堆
	//最终使得根节点的优先级比起两孩子优先级高
	int c, rc;
	while (pos <= H.n / 2)
	{
		c = pos * 2;
		rc = pos * 2 + 1;
		if (rc <= H.n && H.prior(H.rcd[rc].key, H.rcd[c].key))
			c = rc;
		if (H.prior(H.rcd[pos].key, H.rcd[c].key))
			return;
		swapHeapElem(H, pos, c);
		pos = c;
	}
}



//建堆算法
void MakeHeap(Heap &H, RcdType *E, int n, int size, int tag, int(*prior)(KeyType, KeyType))
{
	/*
	tag:为小/大顶堆的标志域（0/1）
	prior:为小/大顶堆的优先函数（lessPrior/greatPrior）
	*/
	int i;
	//H.rcd = E;
	H.rcd = (RcdList) malloc((n+1) * sizeof(RcdType));
	for (int i = 1; i <= n; i++)
		H.rcd[i] = E[i];
	H.n = n;
	H.size = size;
	H.tag = tag;
	H.prior = prior;
	for (i = n / 2; i >= 0; i--)
		ShiftDown(H, i);
}


//堆的初始化
Status InitHeap(Heap &H, int size)
{
	H.prior = NULL;
	H.n = 0;
	H.size = size;
	H.rcd = (RcdList)malloc(size * sizeof(RcdType));
	H.tag = -1;
	//置空堆的标记域为-1
	return OK;
}

//置空函数
Status SetEmpty(Heap &H)
{
	if (H.n == 0)
		return ERROR;
	H.n = 0;
	//H.rcd = NULL;
	return OK;
}


//判空函数
Status IsEmpty(Heap H)
{
	if (H.n == 0 || H.rcd == NULL)
		return	OK;
	else
		return ERROR;
}


//堆的销毁函数
Status Destory_Heap(Heap &H)
{
	if (H.rcd == NULL)
		return ERROR;
	H.n = 0;
	H.size = 0;
	free(H.rcd);
	//H.rcd = 0;
	return OK;
}

//获取堆的元素个数
int Num_Heap(Heap H)
{
	return H.n;
}

//用e返回第i个元素的值
Status GetElem(Heap H, int i, RcdType &e)
{
	if (IsEmpty(H))
		return ERROR;
	else if (i<1 || i>H.n)
		return ERROR;
	e.key = H.rcd[i].key;
	return OK;
}


//获取值等于x的元素，并用e返回
Status FindElem(Heap H, RcdType x, RcdType &e)
{
	if (IsEmpty(H))
		return ERROR;

	int flag = 0;
	for (int i = 1; i <= H.n; i++)
	{
		if (x.key == H.rcd[i].key)
		{
			e.key = H.rcd[i].key;
			flag = 1;
			break;
		}
	}
	if (flag)
		return OK;
	else
		return ERROR;
}


//删除堆顶结点
Status RemoveFirstHeap(Heap &H, RcdType &e)
{
	if (H.n <= 0)
		return ERROR;
	e = H.rcd[1];
	swapHeapElem(H, 1, H.n);
	H.n--;
	if (H.n > 1)
		ShiftDown(H, 1);
	return OK;
}


//堆排序
void HeapSort(RcdSqList &L)
{
	Heap H;
	H.n = L.length;
	H.size = L.size;
	int i;
	RcdType e;
	MakeHeap(H, L.rcd, L.length, H.size, 1, greatPrior);
	for (i = H.n; i > 0; i--)
	{
		RemoveFirstHeap(H, e);
		L.rcd[i].key = e.key;
	}

	
}


//堆的插入
Status InsertHeap(Heap &H, RcdType e)
{
	int curr;
	if (H.n > H.size - 1)
		return ERROR;
	curr = ++H.n;
	H.rcd[curr] = e;
	while (1 != curr && H.prior(H.rcd[curr].key, H.rcd[curr / 2].key))
	{
		swapHeapElem(H, curr, curr / 2);
		curr /= 2;
	}
	return OK;
}