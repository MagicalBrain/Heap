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
	//�ؼ�������
	int n;
	//�ѵĳ���
	int size;
	//�ѵ�����
	int tag;
	//�Ƿ�ΪС����/�󶥶ѣ�0/1��
	int(*prior)(KeyType, KeyType);
	//������������С���ѵ����Ⱥ���
}Heap;

//�󶥶����Ⱥ���
int greatPrior(int x, int y)
{
	return x >= y;
}

//С�������Ⱥ���
int lessPrior(int x, int y)
{
	return x <= y;
}



//����H�е�i����j���Ԫ��
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

//�ѵ�������
void ShiftDown(Heap &H, int pos)
{
	//��Hλ����Ϊpos�Ľڵ���ɸѡ����posΪ������������Ϊ�Ӷ�
	//����ʹ�ø��ڵ�����ȼ��������������ȼ���
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



//�����㷨
void MakeHeap(Heap &H, RcdType *E, int n, int size, int tag, int(*prior)(KeyType, KeyType))
{
	/*
	tag:ΪС/�󶥶ѵı�־��0/1��
	prior:ΪС/�󶥶ѵ����Ⱥ�����lessPrior/greatPrior��
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


//�ѵĳ�ʼ��
Status InitHeap(Heap &H, int size)
{
	H.prior = NULL;
	H.n = 0;
	H.size = size;
	H.rcd = (RcdList)malloc(size * sizeof(RcdType));
	H.tag = -1;
	//�ÿնѵı����Ϊ-1
	return OK;
}

//�ÿպ���
Status SetEmpty(Heap &H)
{
	if (H.n == 0)
		return ERROR;
	H.n = 0;
	//H.rcd = NULL;
	return OK;
}


//�пպ���
Status IsEmpty(Heap H)
{
	if (H.n == 0 || H.rcd == NULL)
		return	OK;
	else
		return ERROR;
}


//�ѵ����ٺ���
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

//��ȡ�ѵ�Ԫ�ظ���
int Num_Heap(Heap H)
{
	return H.n;
}

//��e���ص�i��Ԫ�ص�ֵ
Status GetElem(Heap H, int i, RcdType &e)
{
	if (IsEmpty(H))
		return ERROR;
	else if (i<1 || i>H.n)
		return ERROR;
	e.key = H.rcd[i].key;
	return OK;
}


//��ȡֵ����x��Ԫ�أ�����e����
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


//ɾ���Ѷ����
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


//������
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


//�ѵĲ���
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