


#include <windows.h>
#include <stdio.h>
#include <time.h>


long long rate = 10000;
int  sorting = 0;



#define UPSET 0 
#define QUICKSORT 1
#define SPEEDDOWN 2
#define SPEEDUP 3
#define BUBBLESORT 4
#define HEAPSORT 5
#define COUNTINGSORT 6
#define INSERTSORT 7 
#define SHELLSORT 8

//定义窗口过程

LRESULT CALLBACK WndProc_Color(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Test_Proc(HWND, UINT, WPARAM, LPARAM);

void quickSort(int *, int *);
void bubbleSort(int *, int *);
void HeapSort(int * arr, int * back);
void CountingSort(int *arr, int *bac, int max);
void InsertSort(int *beg, int *back);
void ShellSort(int *beg, int *back);

int red[900];
int green[900];
int blue[900];
int screen[900];


RECT window;
HWND		hwnd_Color;
static HWND hwndButton[9];
TCHAR* button[9] =
{ TEXT("Upset"), TEXT("QuickSort"), TEXT("Speed Down"), TEXT("Speed Up"),
TEXT("BubbleSort"), TEXT("HeapSort"), TEXT("CountingSort"),
TEXT("InsertSort"), TEXT("ShellSort") };

long long st;

DWORD WINAPI ThreadQuickSort(LPVOID pM)
{

	quickSort(red, red + 899);
	InvalidateRect(hwnd_Color, &window, NULL);
	sorting = 0;
	return 0;
}
DWORD WINAPI ThreadBubbleSort(LPVOID pM)
{


	bubbleSort(red, red + 899);
	InvalidateRect(hwnd_Color, &window, NULL);
	sorting = 0;
	return 0;
}
DWORD WINAPI ThreadHeapSort(LPVOID pM)
{



	HeapSort(red, red + 899);
	InvalidateRect(hwnd_Color, &window, NULL);
	sorting = 0;
	return 0;
}
DWORD WINAPI ThreadCoutingSort(LPVOID pM)
{




	CountingSort(red, red + 899, 256);
	InvalidateRect(hwnd_Color, &window, NULL);
	sorting = 0;
	return 0;
}

DWORD WINAPI ThreadInsertSort(LPVOID pM)
{




	InsertSort(red, red + 899);
	InvalidateRect(hwnd_Color, &window, NULL);
	sorting = 0;
	return 0;
}

DWORD WINAPI ThreadShelltSort(LPVOID pM)
{




	ShellSort(red, red + 899);
	InvalidateRect(hwnd_Color, &window, NULL);
	sorting = 0;
	return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	//声明窗口类名（类名）、窗口句柄、程序的消息消息、两个窗口变量
	static TCHAR szAppName[] = TEXT("Color");
	//HWND		hwnd_Color;		
	MSG			msg;
	WNDCLASS	wndclass;
	srand(time(NULL));

	//具体定义窗口类的属性

	int j;
	for (j = 0; j < 900; ++j)
	{


		blue[j] = 30;
		red[j] = rand() % 256;
		green[j] = 30;
	}

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc_Color;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	//判断并注册窗口类，失败则输出，成功则继续

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	}



	//创建并初始化窗口

	hwnd_Color = CreateWindow(szAppName,
		TEXT("The Color Program"),
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX& ~WS_THICKFRAME,
		400,
		20,
		1000,
		700,
		NULL,
		NULL,
		hInstance,
		NULL);



	//使窗口可视
	ShowWindow(hwnd_Color, iCmdShow);

	//刷新窗口，产生非队列消息WM_PAINT，直接调用窗口过程（回调函数）
	UpdateWindow(hwnd_Color);




	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	//退出程序
	return msg.wParam;
}





LRESULT CALLBACK WndProc_Color(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	int i = 0, j;
	HPEN hpen;
	HANDLE han;

	switch (message)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &window);
		for (i = 0; i < 1; ++i)
		{
			hwndButton[i] = CreateWindow(TEXT("button"),
				button[i],
				WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_VCENTER,
				450 + 110 * i, 10,
				110, 50,
				hwnd, (HMENU)i,
				((LPCREATESTRUCT)lParam)->hInstance, NULL);
		}
		for (i; i < 5; ++i)
		{
			hwndButton[i] = CreateWindow(TEXT("button"),
				button[i],
				WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_VCENTER,
				-100 + 220 * i, 75,
				110, 50,
				hwnd, (HMENU)i,
				((LPCREATESTRUCT)lParam)->hInstance, NULL);
		}
		for (i; i < 9; ++i)
		{
			hwndButton[i] = CreateWindow(TEXT("button"),
				button[i],
				WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_VCENTER,
				-980 + 220 * i, 550,
				110, 50,
				hwnd, (HMENU)i,
				((LPCREATESTRUCT)lParam)->hInstance, NULL);
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		i = 0;
		for (i = 0; i < 900; ++i)
		{
			hpen = CreatePen(PS_SOLID, 0, RGB(red[i], 10, 10));
			SelectObject(hdc, hpen);
			MoveToEx(hdc, i + 50, 150, NULL);
			LineTo(hdc, i + 50, 500);
			DeleteObject(hpen);
		}
		EndPaint(hwnd, &ps);
		return 0;

	case WM_LBUTTONDOWN:
		return 0;
	case WM_DRAWITEM:
		return 0;
	case WM_COMMAND:
		if (HIWORD(wParam) == 0)
		{
			switch (LOWORD(wParam))
			{
			case UPSET:
				if (!sorting)
					for (j = 0; j < 900; ++j)
					{


						blue[j] = 30;
						red[j] = rand() % 256;
						green[j] = 30;
					}
				InvalidateRect(hwnd_Color, &window, 0);
				break;
			case QUICKSORT:
				if (!sorting)
				{
					sorting = 1;
					han = (HANDLE)_beginthreadex(NULL, 1000000000, ThreadQuickSort, NULL, 0, NULL);
				}
				st = 0;
				while (st < rate)++st;
				InvalidateRect(hwnd_Color, &window, NULL);
				break;
			case SPEEDDOWN:
				rate *= 5;
				break;
			case SPEEDUP:
				rate /= 5;
				if (rate == 0)rate = 1;
				break;
			case BUBBLESORT:
				if (!sorting)
				{
					sorting = 1;
					han = (HANDLE)_beginthreadex(NULL, 1000000000, ThreadBubbleSort, NULL, 0, NULL);
				}
				InvalidateRect(hwnd_Color, &window, NULL);
				break;
			case HEAPSORT:
				if (!sorting)
				{
					sorting = 1;
					han = (HANDLE)_beginthreadex(NULL, 1000000000, ThreadHeapSort, NULL, 0, NULL);
				}
				InvalidateRect(hwnd_Color, &window, NULL);
				break;
			case COUNTINGSORT:
				if (!sorting)
				{
					sorting = 1;
					han = (HANDLE)_beginthreadex(NULL, 1000000000, ThreadCoutingSort, NULL, 0, NULL);
				}
				InvalidateRect(hwnd_Color, &window, NULL);
				break;
			case INSERTSORT:
				if (!sorting)
				{
					sorting = 1;
					han = (HANDLE)_beginthreadex(NULL, 1000000000, ThreadInsertSort, NULL, 0, NULL);
				}
				InvalidateRect(hwnd_Color, &window, NULL);
				break;
			case SHELLSORT:
				if (!sorting)
				{
					sorting = 1;
					han = (HANDLE)_beginthreadex(NULL, 1000000000, ThreadShelltSort, NULL, 0, NULL);
				}
				InvalidateRect(hwnd_Color, &window, NULL);
				break;
			}
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	if (HIWORD(wParam) == 0) InvalidateRect(hwnd_Color, &window, NULL);
	return DefWindowProc(hwnd, message, wParam, lParam);
}
/*-----------------------------------------------------------------------------------*/
void swap(int *x, int *y)
{
	int t = *x;
	*x = *y;
	*y = t;
}

void quickSort(int *beg, int *back)
{
	if (beg >= back)return;
	int *pos = beg;
	int *mov = beg;
	int mid = *back;
	while (mov < back)
	{
		if (*mov > mid)
		{
			++mov;
		}
		else
		{
			swap(pos, mov);
			InvalidateRect(hwnd_Color, &window, 0);
			//st = GetTickCount();
			//while (GetTickCount() - st < 1);
			st = 0;
			while (st < rate)
			{
				++st;
			}
			++mov;
			++pos;
		}
	}
	swap(pos, back);
	quickSort(beg, pos - 1);
	quickSort(pos + 1, back);
}
void bubbleSort(int *beg, int *back)
{
	int len = back - beg + 1;
	int size = back - beg + 1;
	int i, j;
	for (i = 0; i <= size - 1; ++i)
	{
		for (j = 0; j <= size - 1 - i; ++j)
		{
			if (beg[j]>beg[j + 1])
			{
				swap(beg + j, beg + j + 1);
				InvalidateRect(hwnd_Color, &window, NULL);
				//st = GetTickCount();
				st = 0;
				while (st < rate)
				{
					++st;
				}
			}
		}
	}
	InvalidateRect(hwnd_Color, &window, NULL);
}
int parent(int i) { return i / 2 - 1; }
int left(int i) { return 2 * i - 1; }
int right(int i) { return 2 * i + 1 - 1; }
void MaxHeap(int *arr, int i, int len)
{
	int key;
	if (left(i + 1) <= len)
	{
		key = left(i + 1);
		if (right(i + 1) <= len && *(arr + left(i + 1)) < *(arr + right(i + 1))) key = right(i + 1);
		if (*(arr + i) < (*(arr + key)))
		{
			swap(arr + i, arr + key);

			InvalidateRect(hwnd_Color, &window, NULL);
			st = 0;
			while (st < rate)++st;

			MaxHeap(arr, key, len);
		}
	}
}

void HeapSort(int * arr, int * back)
{
	int len = back - arr + 1;
	for (int i = len - (len / 2) - 1; i >= 0; --i)
	{
		MaxHeap(arr, i, len);
	}
	for (int i = len - 1; i > 1; )
	{
		swap(arr, arr + i);

		InvalidateRect(hwnd_Color, &window, NULL);
		st = 0;
		while (st < rate)++st;		--i;

		MaxHeap(arr, 0, i);
	}
	swap(arr, arr + 1);
}

void CountingSort(int *arr, int *bac, int max)
{
	int len = bac - arr + 1;
	int *chart = (int*)malloc((sizeof(int))*(max + 1));
	int *result = (int*)malloc((sizeof(int))*(len + 1));
	for (int i = 0; i <= max; ++i)
	{
		*(chart + i) = 0;
	}
	for (int i = 0; i < len; ++i)
	{
		++chart[*(arr + i)];
	}
	for (int i = 1; i < max; ++i)
	{
		chart[i] += chart[i - 1];
	}
	for (int i = len - 1; i >= 0; --i)
	{
		*(result + chart[*(arr + i)] - 1) = *(arr + i);
		--chart[*(arr + i)];
	}
	//for (int i = len - 1; i >= 0; --i)
	//{
	//	*(arr + i) = *(result + i);
	//	InvalidateRect(hwnd_Color, &window, NULL);
	//	st = 0;
	//	while (st < rate)++st;
	//}
	for (int i = 0; i <len; ++i)
	{
		*(arr + i) = *(result + i);
		InvalidateRect(hwnd_Color, &window, NULL);
		st = 0;
		while (st < rate)++st;
	}
	free(result);
	free(chart);
}

void InsertSort(int *beg, int *back)
{
	int i, j;
	int temp;
	int len = back - beg + 1;
	for (i = 1; i < len; i++) {
		temp = beg[i];
		for (j = i - 1; j >= 0; j--)
			if (beg[j] > temp)
			{
				beg[j + 1] = beg[j];
				InvalidateRect(hwnd_Color, &window, NULL);
				st = 0;
				while (st < rate)++st;
			}
			else break;
			beg[j + 1] = temp;
			InvalidateRect(hwnd_Color, &window, NULL);
			st = 0;
			while (st < rate)++st;
	}

}

void ShellSort(int *beg, int *back)
{
	int gap, i, j;
	int len = back - beg + 1;
	int temp;
	for (gap = len >> 1; gap > 0; gap >>= 1)
		for (i = gap; i < len; i++) {
			temp = beg[i];
			for (j = i - gap; j >= 0 && beg[j] > temp; j -= gap)
			{
				beg[j + gap] = beg[j];
				InvalidateRect(hwnd_Color, &window, NULL);
				st = 0;
				while (st < rate)++st;

			}
			beg[j + gap] = temp;
			InvalidateRect(hwnd_Color, &window, NULL);
			st = 0;
			while (st < rate)++st;

		}
}