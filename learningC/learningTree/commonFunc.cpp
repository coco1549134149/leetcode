

#include "commonFunc.h"

int negtive(int i)
{
	return add(~i, 1);
}

int getsign(int i) //ȡһ�����ķ��ţ����������Ǹ�
{
	return (i >> 31);
}

int bepositive(int i) //��һ������Ϊ����������������������򲻱䣻����Ǹ������Ϊ�෴����ע�����-2147483648���󸺻������
{
	if (i >> 31)
		return negtive(i);
	else
		return i;
}

/*λ����ʵ�ּӼ��˳�*/
int add(int num1, int num2) {
	int sum = num1 ^ num2;
	int carry = (num1 & num2) << 1;
	while (carry != 0) {
		int a = sum;
		int b = carry;
		sum = a ^ b;
		carry = (a & b) << 1;
	}
	return sum;
}

/*
* num1: ����
* num2: ������
*/
int substract(int num1, int num2) {
	int subtractor = add(~num2, 1);// ��������Ĳ��루ȡ����һ��
	int result = add(num1, subtractor); // add()�������ӷ����㡡��
	return result;
}

int subtraction(int a, int b) //�������㣺�����󸺲����ͼӷ�����
{
	return add(a, negtive(b));
}
int multiply(int a, int b) {
	//�������ͱ�������ȡ����ֵ��
	int multiplicand = a < 0 ? add(~a, 1) : a;
	int multiplier = b < 0 ? add(~b, 1) : b;

	//�������ֵ�ĳ˻�����
	int product = 0;
	while (multiplier > 0) {
		if ((multiplier & 0x1) > 0) {// ÿ�ο�����������һλ��������
			product = add(product, multiplicand);
		}
		multiplicand = multiplicand << 1;// ÿ����һ�Σ�������Ҫ����һλ��������
		multiplier = multiplier >> 1;// ÿ����һ�Σ�����Ҫ����һλ���ɶ�����ͼ��⣩����
	}
	//����˻��ķ��š���
	if ((a ^ b) < 0) {
		product = add(~product, 1);
	}
	return product;
}

/*
* a : ������
* b : ����
*/
//int divide(int a, int b) {
//	// ��ȡ�������ͳ����ľ���ֵ    
//	int dividend = a > 0 ? a : add(~a, 1);
//	int divisor = b > 0 ? a : add(~b, 1);
//	int quotient = 0;// ��    
//	int remainder = 0;// ����    
//	for (int i = 31; i >= 0; i--) {
//		//�Ƚ�dividend�Ƿ����divisor��(1<<i)�η�����Ҫ��dividend��(divisor<<i)�Ƚϣ�������(dividend>>i)��divisor�Ƚϣ�
//		//Ч��һ�������ǿ��Ա�����(divisor<<i)�������ܵ��µ������������������dividend����С��divisor�������������dividend����divisor       
//		if ((dividend >> i) >= divisor) {
//			quotient = add(quotient, 1 << i);
//			dividend = substract(dividend, divisor << i);
//		}
//	}
//	// ȷ���̵ķ���    
//	if ((a ^ b) < 0) {
//		// ��������ͱ�������ţ�����Ϊ����        
//		quotient = add(~quotient, 1);
//	}
//	// ȷ����������    
//	remainder = b > 0 ? dividend : add(~dividend, 1);
//	return quotient;// ������
//}

int divide(int dividend, int divisor) {
	bool flag = true;
	if (getsign(dividend) == getsign(divisor)) //���ķ����ж�
		flag = false;

	unsigned int x = bepositive(dividend);
	unsigned int y = bepositive(divisor);

	int ans = 0;
	int i = 31;
	while (i >= 0)
	{
		//�Ƚ�x�Ƿ����y*(1<<i)=(y<<i)������ֱ�ӱȽϣ���Ϊ��ȷ��y*(1<<i)�Ƿ����  
		if ((x >> i) >= y)  //�������
		{
			ans = add(ans, (1 << i));
			x = subtraction(x, (y << i));
		}
		i = subtraction(i, 1);
	}
	if (flag)
		ans = negtive(ans);
	return ans;
}
