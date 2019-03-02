#include <iostream>
#include "Heap.h"

using namespace std;

void inputdata(RcdList &E, int n)
{
	E = (RcdList)malloc(n * sizeof(RcdType));
	int num;
	for (int i = 1; i <= n; i++)
	{
		cin >> num;
		E[i].key = num;
		//cout << E[i].key << " ";
	}

	cout << endl;
}

void inputdata(RcdSqList &L, int n)
{
	RcdList E;
	E = (RcdList)malloc(n * sizeof(RcdType));
	int num;
	for (int i = 1; i <= n; i++)
	{
		cin >> num;
		cin.get();
		E[i].key = num;
		//cout << E[i].key << " ";
	}
	L.rcd = E;
	L.length = n;
	cout << endl;
}

Status output(Heap H)
{
	int num = H.n;
	if (IsEmpty(H))
	{
		return ERROR;
	}
		
	for (int i = 1; i <= num; i++)
	{
		cout << H.rcd[i].key << " ";
	}
	cout << endl;
	return OK;
}

Status output(RcdSqList L)
{
	int num = L.length;
	for (int i = 1; i <= num; i++)
	{
		cout << L.rcd[i].key << " ";
	}
	cout << endl;
	return OK;
}

#define n 10
#define size 20

int main()
{
	Heap H;
	RcdList E;
	RcdType e;
	RcdSqList L;

	printf("***--------�˵�--------***\n");
	printf("1����ʼ��һ���ն�\n");
	printf("2�������������������һ����\n");
	printf("3�������ÿպ���\n");
	printf("4���ж϶��Ƿ�Ϊ��\n");
	printf("5������һ����\n");
	printf("6������һ���м�¼�Ķѵ�Ԫ������\n");
	printf("7������һ���м�¼�Ķѵĵ�i��Ԫ��\n");
	printf("8���ڶ���Ѱ��һ���������ֵ��ȵ�Ԫ��\n");
	printf("9��ɾ���Ѷ�Ԫ��\n");
	printf("a���ڶ������һ��Ԫ��\n");
	printf("b�����Զ�����\n");
	printf("#��������ʾ���˵�\n");
	printf("0������\n");
	printf("***-------------------***\n");


	
	char num;
	int flag = 1;

	while (flag)
	{
		printf("���������ѡ��\n");

		//Ϊ�˷�ֹ���뵥���ַ���ʱ�򣬵�һ���ַ�����Ķ����������������Ӷ����º���������쳣
		//num = cin.get();
		//cin.get();
		
		cin.get(num);
		cin.get();

		switch (num)
		{
		case '0':
			flag = 0;
			printf("�˳���\n");
			break;
		case '1':
			if (InitHeap(H, n))
				printf("��ʼ���ɹ���\n");
			else
				printf("��ʼ��ʧ��\n");
			break;
		case '2':
			
			InitHeap(H, size);
			int len;
			int flag;
			printf("Ԫ�ظ�����");
			cin >> len;
			//cin.get();
			printf("�󶥶ѻ���С���ѣ������� 1/0����");
			cin >> flag;
			//cin.get();
			if (len < 0 || len>size)
				printf("����Ԫ�ظ������Ϸ����ѵ�����Ϊ20��\n");
			if (flag != 0 && flag != 1)
			{
				printf("�������Ͳ����������\n");
				//break;
			}
			else
			{
				inputdata(E, len);
				if (flag == 1)
					MakeHeap(H, E, len, size, 1, greatPrior);
				else 
					MakeHeap(H, E, len, size, 0, lessPrior);
				
				output(H);
			}
			cin.clear();
			cin.ignore();
			break;
		case '3':
			if (SetEmpty(H))
				printf("�ÿճɹ���\n");
			else
				printf("�ÿ�ʧ�ܣ�\n");
			break;
		case '4':
			if (IsEmpty(H))
				printf("��һ���նѣ�\n");
			else
				printf("�Ѳ�Ϊ�գ�\n");
			break;
		case '5':
			if (Destory_Heap(H))
				printf("���ٳɹ���\n");
			else
				printf("����ʧ�ܣ�\n");
			break;
		case '6':
			printf("Ԫ�ظ���Ϊ��%d\n", Num_Heap(H));
			break;
		case '7':
			int i;
			printf("������Ҫ���ʵ�Ԫ����ţ�");
			cin >> i;
			
			if (GetElem(H, i, e))
				printf("Ԫ��ֵΪ��%d\n", e.key);
			else
				printf("���ʴ���\n");
			cin.clear();
			cin.ignore();
			break;
		case '8':
			RcdType x;
			printf("������Ҫ�ҵļ�ֵ��\n");
			cin >> x.key;
			if (FindElem(H, x, e))
				printf("�ҵ��ˣ�\n");
			else
				printf("���ź���û�ҵ���\n");
			break;
		case '9':
			if (RemoveFirstHeap(H, e))
				printf("ɾ���ɹ�������ֵΪ��%d\n", e.key);
			else
				printf("ɾ��ʧ�ܣ�\n");
			break;
		case 'a':
			printf("������Ҫ����ļ�ֵ��");
			cin >> e.key;
			if (InsertHeap(H, e))
			{
				printf("����ɹ���\n");
				output(H);
			}
			else
			{
				printf("����ʧ��!\n");
				output(H);
			}
			cin.clear();
			cin.ignore();
			break;
		case 'b':
			printf("Ԫ�ظ�����");
			cin >> len;
			if (len < 0 || len>size)
				printf("����Ԫ�ظ������Ϸ����ѵ�����Ϊ20��\n");
			else
			{
				inputdata(L, len);
				HeapSort(L);
				output(L);
			}
			cin.clear();
			cin.ignore();
			break;
		case 'p':
			InitHeap(H,size);
			output(H);
			break;
		case '#':
			printf("***--------�˵�--------***\n");
			printf("1����ʼ��һ���ն�\n");
			printf("2�������������������һ����\n");
			printf("3�������ÿպ���\n");
			printf("4���ж϶��Ƿ�Ϊ��\n");
			printf("5������һ����\n");
			printf("6������һ���м�¼�Ķѵ�Ԫ������\n");
			printf("7������һ���м�¼�Ķѵĵ�i��Ԫ��\n");
			printf("8���ڶ���Ѱ��һ���������ֵ��ȵ�Ԫ��\n");
			printf("9��ɾ���Ѷ�Ԫ��\n");
			printf("a���ڶ������һ��Ԫ��\n");
			printf("b�����Զ�����\n");
			printf("#��������ʾ���˵�\n");
			printf("0������\n");
			printf("***-------------------***\n");
			break;
		
		default:
			
				printf("ѡ�񲻺Ϸ���������������\n");
				break;
			
		}

	}

	return 0;
}