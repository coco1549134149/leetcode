// 数独位运算版本
//编译后，在命令列中将单列格式数独放在参数中
//例： sudoku 802609051000800600000000049050200008008563900900007030530000000001008000480705203
#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#define STATUS_MAX_VALUE 511

int init();
int printSudoku(int *prn);
int getNextBlank(int sp);
int check(int sp, int indexV, int indexH, int indexB);
int push(int sp);
int pop();
int tryAns2();
int findNumber(int indexV, int indexH, int indexB, int skipValue);
int markStatus(int indexV, int indexH, int indexB, int number);
int resetStatus(int indexV, int indexH, int indexB, int number);

int sudoku[81];                                // 數獨題目陣列
int tempNum[81];                               // 上一次填数位置
int tempSp = 0;                                 // 上一次填数位置指标

int statusH[9];									//列状态
int statusV[9];									//行状态
int statusB[9];									//九宫格状态

bool test = false;

//int main(int argc, char *argv[]) {
//	int startTime = clock();
//
//	int j;
//	if (argc > 1) for (j = 0; j < 81; j++) sudoku[j] = argv[1][j] - '0';
//	else exit(0);
//
//	printf("------------------\n");
//	printSudoku(sudoku);
//	init();                                     // 初始设定
//	tryAns2();                                   // 测试求解
//	printf("------------------\n");
//	printSudoku(sudoku);
//	printf("------------------\n");
//
//	int endTime = clock();
//	printf("use time,%d\n", (endTime - startTime));
//}

int init() {
	//初始状态值
	for (int i = 0; i < 9; ++i)
	{
		statusH[i] = 0;
		statusV[i] = 0;
		statusB[i] = 0;
	}

	for (int i = 0; i < 81; i++) {
		int indexH = i % 9;      					//第几列，也是行位置
		int indexV = i / 9;							//第几行，也是列位置
		int indexB = ((i / 9) / 3) * 3 + (i % 9) / 3;			//九宫格索引
																// int stationB=((i/9)%3)*3+(i%9)%3;		//九宫格位置
		if (sudoku[i] > 0)
		{
			int number = sudoku[i];
			markStatus(indexV, indexH, indexB, number);
		}
	}
	return 0;
}

int printSudoku(int *prn) {
	// 印出數獨題目(陣列內容)
	for (int i = 0; i < 81; i++) {
		printf("%2d", prn[i]);
		if (i % 9 == 8) printf("\n");
	}
	return 0;
}

int tryAns2() {
	int sp = getNextBlank(-1);                    // 取得第一個空白的位置開始填入數字

	do {
		int indexH = sp % 9;      					//第几列，也是行位置
		int indexV = sp / 9;						//第几行，也是列位置
		int indexB = ((sp / 9) / 3) * 3 + (sp % 9) / 3;		//九宫格索引

		int skipValue = sudoku[sp];				// 上一个位置存在数据，则重置状态数据
		resetStatus(indexV, indexH, indexB, skipValue);

		//搜索一个新数
		int number = findNumber(indexV, indexH, indexB, skipValue);
		//当前数独无法进行了，需要回溯一下
		if (number == -1)
		{
			//回溯上一个位置
			sudoku[sp] = 0;
			sp = pop();
			if (sp == -1)
			{
				printf("not cycle last sp,last sp ==-1");
				return 1;
			}
			continue;
		}

		sudoku[sp] = number;
		// 标记状态
		markStatus(indexV, indexH, indexB, number);
		push(sp);
		sp = getNextBlank(sp);

	} while (sp >= 0 && sp < 81);
}


int findNumber(int indexV, int indexH, int indexB, int skipValue) {
	//获取同行、列、九宮格沒有用到的数字
	int status = statusV[indexV] | statusH[indexH] | statusB[indexB];
	//保证从最小可搜索范围查找,并且保证上一次出现过的不再搜索
	if (skipValue > 0)
	{
		//把末k位变成1
		status = status | ((1 << skipValue) - 1);
	}

	if (status >= STATUS_MAX_VALUE)
	{
		return -1;
	}

	//把右起第一个0变成1
	int nextStatus = status | (status + 1);
	//获取差值
	int difValue = nextStatus^status;
	//获取logn
	for (int i = 0; i < 9; ++i)
	{
		if ((difValue >> i) == 1)
		{
			return i + 1;
		}
	}
}

int getNextBlank(int sp) {
	// 取得下一個空白的位置
	do {
		sp++;
	} while (sp < 81 && sudoku[sp]>0);
	return(sp);
}

// sp 是当前位置索引，indexV 行索引，indexH 列索引，indexB九宫格索引
int check(int sp, int indexV, int indexH, int indexB) {
	// 检查同行、列、九宮格沒有用到的数字，若已经用过返回 1
	int status = statusV[indexV] | statusH[indexH] | statusB[indexB];
	//9个数字都被用了
	if (status >= STATUS_MAX_VALUE)
	{
		return 1;
	}
	int number = sudoku[sp];
	//取右数第k位,若是1表明这个值已经存在了
	return status >> (number - 1) & 1;
}

int push(int sp) {
	// 將指定的位置放入堆疊中
	tempNum[tempSp++] = sp;
	return 0;
}

int pop() {
	// 取出堆疊中的上一個位置
	if (tempSp <= 0) return(-1);
	else return(tempNum[--tempSp]);
}

// 行、列、宫二进制数据指定位置标记为1
int markStatus(int indexV, int indexH, int indexB, int number) {
	if (number < 1)
	{
		return 0;
	}
	//把右数第k(从1计数)位变成1 
	statusV[indexV] |= (1 << (number - 1));
	statusH[indexH] |= (1 << (number - 1));
	statusB[indexB] |= (1 << (number - 1));
}

int resetStatus(int indexV, int indexH, int indexB, int number) {
	if (number < 1)
	{
		return 0;
	}
	//把右数第k位变成0 
	statusV[indexV] &= ~(1 << (number - 1));
	statusH[indexH] &= ~(1 << (number - 1));
	statusB[indexB] &= ~(1 << (number - 1));
}