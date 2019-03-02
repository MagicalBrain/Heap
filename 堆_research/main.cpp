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

	printf("***--------菜单--------***\n");
	printf("1：初始化一个空堆\n");
	printf("2：根据输入的数来创建一个堆\n");
	printf("3：测试置空函数\n");
	printf("4：判断堆是否为空\n");
	printf("5：销毁一个堆\n");
	printf("6：访问一个有记录的堆的元素数量\n");
	printf("7：访问一个有记录的堆的第i个元素\n");
	printf("8：在堆中寻找一个与输入的值相等的元素\n");
	printf("9：删除堆顶元素\n");
	printf("a：在堆里插入一个元素\n");
	printf("b：测试堆排序\n");
	printf("#：重现显示本菜单\n");
	printf("0：结束\n");
	printf("***-------------------***\n");


	
	char num;
	int flag = 1;

	while (flag)
	{
		printf("请输入你的选择\n");

		//为了防止输入单个字符的时候，第一个字符后面的都被读进缓冲区，从而导致后面的输入异常
		//num = cin.get();
		//cin.get();
		
		cin.get(num);
		cin.get();

		switch (num)
		{
		case '0':
			flag = 0;
			printf("退出！\n");
			break;
		case '1':
			if (InitHeap(H, n))
				printf("初始化成功！\n");
			else
				printf("初始化失败\n");
			break;
		case '2':
			
			InitHeap(H, size);
			int len;
			int flag;
			printf("元素个数：");
			cin >> len;
			//cin.get();
			printf("大顶堆还是小顶堆？（输入 1/0）：");
			cin >> flag;
			//cin.get();
			if (len < 0 || len>size)
				printf("输入元素个数不合法，堆的容量为20！\n");
			if (flag != 0 && flag != 1)
			{
				printf("顶堆类型参数输入错误！\n");
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
				printf("置空成功！\n");
			else
				printf("置空失败！\n");
			break;
		case '4':
			if (IsEmpty(H))
				printf("是一个空堆！\n");
			else
				printf("堆不为空！\n");
			break;
		case '5':
			if (Destory_Heap(H))
				printf("销毁成功！\n");
			else
				printf("销毁失败！\n");
			break;
		case '6':
			printf("元素个数为：%d\n", Num_Heap(H));
			break;
		case '7':
			int i;
			printf("请输入要访问的元素序号：");
			cin >> i;
			
			if (GetElem(H, i, e))
				printf("元素值为：%d\n", e.key);
			else
				printf("访问错误！\n");
			cin.clear();
			cin.ignore();
			break;
		case '8':
			RcdType x;
			printf("请输入要找的键值：\n");
			cin >> x.key;
			if (FindElem(H, x, e))
				printf("找到了！\n");
			else
				printf("很遗憾，没找到！\n");
			break;
		case '9':
			if (RemoveFirstHeap(H, e))
				printf("删除成功！，其值为：%d\n", e.key);
			else
				printf("删除失败！\n");
			break;
		case 'a':
			printf("请输入要插入的键值：");
			cin >> e.key;
			if (InsertHeap(H, e))
			{
				printf("插入成功！\n");
				output(H);
			}
			else
			{
				printf("插入失败!\n");
				output(H);
			}
			cin.clear();
			cin.ignore();
			break;
		case 'b':
			printf("元素个数：");
			cin >> len;
			if (len < 0 || len>size)
				printf("输入元素个数不合法，堆的容量为20！\n");
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
			printf("***--------菜单--------***\n");
			printf("1：初始化一个空堆\n");
			printf("2：根据输入的数来创建一个堆\n");
			printf("3：测试置空函数\n");
			printf("4：判断堆是否为空\n");
			printf("5：销毁一个堆\n");
			printf("6：访问一个有记录的堆的元素数量\n");
			printf("7：访问一个有记录的堆的第i个元素\n");
			printf("8：在堆中寻找一个与输入的值相等的元素\n");
			printf("9：删除堆顶元素\n");
			printf("a：在堆里插入一个元素\n");
			printf("b：测试堆排序\n");
			printf("#：重现显示本菜单\n");
			printf("0：结束\n");
			printf("***-------------------***\n");
			break;
		
		default:
			
				printf("选择不合法，请重新来过！\n");
				break;
			
		}

	}

	return 0;
}