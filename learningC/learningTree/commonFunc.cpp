

#include "commonFunc.h"

int negtive(int i)
{
	return add(~i, 1);
}

int getsign(int i) //取一个数的符号，看是正还是负
{
	return (i >> 31);
}

int bepositive(int i) //将一个数变为正数，如果本来就是正，则不变；如果是负，则变为相反数。注意对于-2147483648，求负会溢出。
{
	if (i >> 31)
		return negtive(i);
	else
		return i;
}

/*位运算实现加减乘除*/
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
* num1: 减数
* num2: 被减数
*/
int substract(int num1, int num2) {
	int subtractor = add(~num2, 1);// 先求减数的补码（取反加一）
	int result = add(num1, subtractor); // add()即上述加法运算　　
	return result;
}

int subtraction(int a, int b) //减法运算：利用求负操作和加法操作
{
	return add(a, negtive(b));
}
int multiply(int a, int b) {
	//将乘数和被乘数都取绝对值　
	int multiplicand = a < 0 ? add(~a, 1) : a;
	int multiplier = b < 0 ? add(~b, 1) : b;

	//计算绝对值的乘积　　
	int product = 0;
	while (multiplier > 0) {
		if ((multiplier & 0x1) > 0) {// 每次考察乘数的最后一位　　　　
			product = add(product, multiplicand);
		}
		multiplicand = multiplicand << 1;// 每运算一次，被乘数要左移一位　　　　
		multiplier = multiplier >> 1;// 每运算一次，乘数要右移一位（可对照上图理解）　　
	}
	//计算乘积的符号　　
	if ((a ^ b) < 0) {
		product = add(~product, 1);
	}
	return product;
}

/*
* a : 被除数
* b : 除数
*/
//int divide(int a, int b) {
//	// 先取被除数和除数的绝对值    
//	int dividend = a > 0 ? a : add(~a, 1);
//	int divisor = b > 0 ? a : add(~b, 1);
//	int quotient = 0;// 商    
//	int remainder = 0;// 余数    
//	for (int i = 31; i >= 0; i--) {
//		//比较dividend是否大于divisor的(1<<i)次方，不要将dividend与(divisor<<i)比较，而是用(dividend>>i)与divisor比较，
//		//效果一样，但是可以避免因(divisor<<i)操作可能导致的溢出，如果溢出则会可能dividend本身小于divisor，但是溢出导致dividend大于divisor       
//		if ((dividend >> i) >= divisor) {
//			quotient = add(quotient, 1 << i);
//			dividend = substract(dividend, divisor << i);
//		}
//	}
//	// 确定商的符号    
//	if ((a ^ b) < 0) {
//		// 如果除数和被除数异号，则商为负数        
//		quotient = add(~quotient, 1);
//	}
//	// 确定余数符号    
//	remainder = b > 0 ? dividend : add(~dividend, 1);
//	return quotient;// 返回商
//}

int divide(int dividend, int divisor) {
	bool flag = true;
	if (getsign(dividend) == getsign(divisor)) //积的符号判定
		flag = false;

	unsigned int x = bepositive(dividend);
	unsigned int y = bepositive(divisor);

	int ans = 0;
	int i = 31;
	while (i >= 0)
	{
		//比较x是否大于y*(1<<i)=(y<<i)，避免直接比较，因为不确定y*(1<<i)是否溢出  
		if ((x >> i) >= y)  //如果够减
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
