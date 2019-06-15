// ����λ����汾
//��������������н����и�ʽ�������ڲ�����
//���� sudoku 802609051000800600000000049050200008008563900900007030530000000001008000480705203
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

int sudoku[81];                                // �����}Ŀ���
int tempNum[81];                               // ��һ������λ��
int tempSp = 0;                                 // ��һ������λ��ָ��

int statusH[9];									//��״̬
int statusV[9];									//��״̬
int statusB[9];									//�Ź���״̬

bool test = false;

int main(int argc, char *argv[]) {
	int startTime = clock();

	int j;
	if (argc > 1) for (j = 0; j < 81; j++) sudoku[j] = argv[1][j] - '0';
	else exit(0);

	printf("------------------\n");
	printSudoku(sudoku);
	init();                                     // ��ʼ�趨
	tryAns2();                                   // �������
	printf("------------------\n");
	printSudoku(sudoku);
	printf("------------------\n");

	int endTime = clock();
	printf("use time,%d\n", (endTime - startTime));
}

int init() {
	//��ʼ״ֵ̬
	for (int i = 0; i < 9; ++i)
	{
		statusH[i] = 0;
		statusV[i] = 0;
		statusB[i] = 0;
	}

	for (int i = 0; i < 81; i++) {
		int indexH = i % 9;      					//�ڼ��У�Ҳ����λ��
		int indexV = i / 9;							//�ڼ��У�Ҳ����λ��
		int indexB = ((i / 9) / 3) * 3 + (i % 9) / 3;			//�Ź�������
																// int stationB=((i/9)%3)*3+(i%9)%3;		//�Ź���λ��
		if (sudoku[i] > 0)
		{
			int number = sudoku[i];
			markStatus(indexV, indexH, indexB, number);
		}
	}
}

int printSudoku(int *prn) {
	// ӡ�������}Ŀ(��Ѓ���)
	for (int i = 0; i < 81; i++) {
		printf("%2d", prn[i]);
		if (i % 9 == 8) printf("\n");
	}
}

int tryAns2() {
	int sp = getNextBlank(-1);                    // ȡ�õ�һ���հ׵�λ���_ʼ���딵��

	do {
		int indexH = sp % 9;      					//�ڼ��У�Ҳ����λ��
		int indexV = sp / 9;						//�ڼ��У�Ҳ����λ��
		int indexB = ((sp / 9) / 3) * 3 + (sp % 9) / 3;		//�Ź�������

		int skipValue = sudoku[sp];				// ��һ��λ�ô������ݣ�������״̬����
		resetStatus(indexV, indexH, indexB, skipValue);

		//����һ������
		int number = findNumber(indexV, indexH, indexB, skipValue);
		//��ǰ�����޷������ˣ���Ҫ����һ��
		if (number == -1)
		{
			//������һ��λ��
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
		// ���״̬
		markStatus(indexV, indexH, indexB, number);
		push(sp);
		sp = getNextBlank(sp);

	} while (sp >= 0 && sp < 81);
}


int findNumber(int indexV, int indexH, int indexB, int skipValue) {
	//��ȡͬ�С��С��Ōm��]���õ�������
	int status = statusV[indexV] | statusH[indexH] | statusB[indexB];
	//��֤����С��������Χ����,���ұ�֤��һ�γ��ֹ��Ĳ�������
	if (skipValue > 0)
	{
		//��ĩkλ���1
		status = status | ((1 << skipValue) - 1);
	}

	if (status >= STATUS_MAX_VALUE)
	{
		return -1;
	}

	//�������һ��0���1
	int nextStatus = status | (status + 1);
	//��ȡ��ֵ
	int difValue = nextStatus^status;
	//��ȡlogn
	for (int i = 0; i < 9; ++i)
	{
		if ((difValue >> i) == 1)
		{
			return i + 1;
		}
	}
}

int getNextBlank(int sp) {
	// ȡ����һ���հ׵�λ��
	do {
		sp++;
	} while (sp < 81 && sudoku[sp]>0);
	return(sp);
}

// sp �ǵ�ǰλ��������indexV ��������indexH ��������indexB�Ź�������
int check(int sp, int indexV, int indexH, int indexB) {
	// ���ͬ�С��С��Ōm��]���õ������֣����Ѿ��ù����� 1
	int status = statusV[indexV] | statusH[indexH] | statusB[indexB];
	//9�����ֶ�������
	if (status >= STATUS_MAX_VALUE)
	{
		return 1;
	}
	int number = sudoku[sp];
	//ȡ������kλ,����1�������ֵ�Ѿ�������
	return status >> (number - 1) & 1;
}

int push(int sp) {
	// ��ָ����λ�÷���ѯB��
	tempNum[tempSp++] = sp;
}

int pop() {
	// ȡ���ѯB�е���һ��λ��
	if (tempSp <= 0) return(-1);
	else return(tempNum[--tempSp]);
}

// �С��С�������������ָ��λ�ñ��Ϊ1
int markStatus(int indexV, int indexH, int indexB, int number) {
	if (number < 1)
	{
		return 0;
	}
	//��������k(��1����)λ���1 
	statusV[indexV] |= (1 << (number - 1));
	statusH[indexH] |= (1 << (number - 1));
	statusB[indexB] |= (1 << (number - 1));
}

int resetStatus(int indexV, int indexH, int indexB, int number) {
	if (number < 1)
	{
		return 0;
	}
	//��������kλ���0 
	statusV[indexV] &= ~(1 << (number - 1));
	statusH[indexH] &= ~(1 << (number - 1));
	statusB[indexB] &= ~(1 << (number - 1));
}