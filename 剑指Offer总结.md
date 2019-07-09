# 剑指Offer总结
## 01. 二维数组查找
> 在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。  

### 思路
从左下或右上角开始查找，以左下为例，查找数字比左下角数字大时，右移，比左下角数字小时上移。
```
class Solution {
   public:
    bool Find(vector<vector<int>> array, int target) {
        int rowCount = array.size();
        int colCount = array[0].size();
        int i, j;
        for (i = rowCount - 1, j = 0; i >= 0 && j < colCount;) {
            if (target == array[i][j]) return true;
            if (target < array[i][j]) {
                i--;
                continue;
            }
            if (target > array[i][j]) {
                j++;
                continue;
            }
        }
        return false;
    }
};
```

## 02. 替换空格
> 请实现一个函数，将一个字符串中的每个空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。  

### 思路
统计空格数量和字符串长度，然后从后向前替换。
```
class Solution {
   public:
    void replaceSpace(char *str, int length) {
        int count = 0;
        for (int i = 0; i < length; i++) {
            if (str[i] == ' ') count++;
        }
        for (int i = length - 1; i >= 0; i--) {
            if (str[i] != ' ') {
                str[i + 2 * count] = str[i];
            } else {
                count--;
                str[i + 2 * count] = '%';
                str[i + 2 * count + 1] = '2';
                str[i + 2 * count + 2] = '0';
            }
        }
    }
};
```

## 03. 从尾到头打印链表
> 输入一个链表，按链表值从尾到头的顺序返回一个ArrayList  

### 思路
1. 遍历链表存入stack，再对stack出栈存入vector。
```
class Solution {
   public:
    vector<int> printListFromTailToHead(ListNode *head) {
        std::stack<int> s;
        ListNode *cur = head;
        while (cur != NULL) {
            s.push(cur->val);
            cur = cur->next;
        }

        vector<int> v;
        while (!s.empty()) {
            v.push_back(s.top());
            s.pop();
        }
        return v;
    }
};
```

2. 递归方法
```
class Solution {
   public:
    vector<int> printListFromTailToHead(struct ListNode *head) {
        vector<int> value;
        if (head != NULL) {
            value.insert(value.begin(), head->val);
            if (head->next != NULL) {
                vector<int> tempVec = printListFromTailToHead(head->next);
                if (tempVec.size() > 0)
                    value.insert(value.begin(), tempVec.begin(), tempVec.end());
            }
        }
        return value;
    }
};
```

## 04. 重建二叉树
> 输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。  

### 思路
通过先序确定根节点，找到中序中根节点的位置，在先序和中序中区分左右子树节点，分为左子树先序，左子树中序，右子树先序，右子树中序四个序列，再递归直至重建完成。
```
class Solution {
   public:
    TreeNode *reConstructBinaryTree(vector<int> pre, vector<int> vin) {
        if (pre.size() != vin.size())
            return NULL;
        else {
            int length = pre.size();
            if (length == 0) return NULL;
            TreeNode *root = new TreeNode(pre[0]);
            int rootIndex;
            for (rootIndex = 0; rootIndex < length; rootIndex++) {
                if (vin[rootIndex] == pre[0]) break;
            }
            if (vin[rootIndex] != pre[0]) {
                return NULL;
            }
            int left = rootIndex;
            int right = length - 1 - rootIndex;
            vector<int> preLeft(left), preRight(right), vinLeft(left),
                vinRight(right);
            for (int i = 0; i < length; i++) {
                if (i < rootIndex) {
                    preLeft[i] = pre[i + 1];
                    vinLeft[i] = vin[i];
                } else if (i > rootIndex) {
                    preRight[i - rootIndex - 1] = pre[i];
                    vinRight[i - rootIndex - 1] = vin[i];
                }
            }
            root->left = reConstructBinaryTree(preLeft, vinLeft);
            root->right = reConstructBinaryTree(preRight, vinRight);
            return root;
        }
    }
};
```

## 05. 两个栈实现队列
> 用两个栈来实现一个队列，完成队列的Push和Pop操作，队列中的元素为int类型。  

### 思路
入队：将元素进栈A
出队：判断栈B是否为空，如果为空，则将栈A中所有元素pop，并push进栈B，栈B出栈；
如果不为空，栈B直接出栈。
```
#include <stack>;
using namespace std;

class Solution {
   public:
    void push(int node) { stack1.push(node); }

    int pop() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        int a = stack2.top();
        stack2.pop();
        return a;
    }

   private:
    stack<int> stack1;
    stack<int> stack2;
};
```

## 06. 旋转数组的最小数字
> 把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。 输入一个非减排序的数组的一个旋转，输出旋转数组的最小元素。 例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。 NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。  

### 思路
二分查找，如果中间元素>第一个元素，则最小元素位于中间元素后面。
```
class Solution {
   public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        int low = 0;
        int high = rotateArray.size() - 1;
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (rotateArray[mid] > rotateArray[high]) {
                low = mid + 1;
            } else if (rotateArray[mid] == rotateArray[high]) {
                high = high - 1;
            } else {
                high = mid;
            }
        }
        return rotateArray[low];
    }
};
```

## 07. 斐波那契数列
> 大家都知道斐波那契数列，现在要求输入一个整数n，请你输出斐波那契数列的第n项（从0开始，第0项为0）。n<=39  

### 思路
使用迭代（而非递归），只记录前一个和前前一个。
```
class Solution {
   public:
    int Fibonacci(int n) {
        if (n == 0) {
            return 0;
        } else if (n == 1) {
            return 1;
        }
        int prePre = 0;
        int pre = 1;
        int result = 0;
        for (int i = 2; i <= n; i++) {
            result = prePre + pre;
            prePre = pre;
            pre = result;
        }
        return result;
    }
};
```

##  08. 跳台阶
>  一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法（先后次序不同算不同的结果）。  

### 思路
A.如果两种跳法，1阶或者2阶，那么假定第一次跳的是一阶，那么剩下的是n-1个台阶，跳法是f(n-1); 
B.假定第一次跳的是2阶，那么剩下的是n-2个台阶，跳法是f(n-2) 
C.由a\b假设可以得出总跳法为: f(n) = f(n-1) + f(n-2) 
D.然后通过实际的情况可以得出：只有一阶的时候 f(1) = 1 ,只有两阶的时候可以有 f(2) = 2 
E.可以发现最终得出的是一个斐波那契数列
```
class Solution {
   public:
    int jumpFloor(int number) {
        if (number == 1) {
            return 1;
        } else if (number == 2) {
            return 2;
        } else {
            return jumpFloor(number - 1) + jumpFloor(number - 2);
        }
    }
};
```

## 09. 变态跳台阶
> 一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。求该青蛙跳上一个n级的台阶总共有多少种跳法。  

### 思路
f(n-1) = f(0) + f(1)+f(2)+f(3) + ... + f((n-1)-1) = f(0) + f(1) + f(2) + f(3) + ... + f(n-2) 
f(n) = f(0) + f(1) + f(2) + f(3) + ... + f(n-2) + f(n-1) = f(n-1) + f(n-1) =2*f(n-1)
```
class Solution {
public:
    int jumpFloorII(int number) {
        return 1 << (number - 1);
    }
};
```

## 10. 矩形覆盖
> 我们可以用2**1的小矩形横着或者竖着去覆盖更大的矩形。请问用n个2**1的小矩形无重叠地覆盖一个2*n的大矩形，总共有多少种方法？  

### 思路
斐波那契数列
```
class Solution {
   public:
    int rectCover(int number) {
        if (number <= 2) {
            return number;
        } else {
            int pre = 2;
            int prePre = 1;
            int result = 0;
            for (int i = 3; i <= number; i++) {
                result = pre + prePre;
                prePre = pre;
                pre = result;
            }
            return result;
        }
    }
};
```

##  11. 二进制中1的个数 
>  输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示。  

### 思路
#TODO
如果一个整数不为0，那么这个整数至少有一位是1。如果我们把这个整数减1，那么原来处在整数最右边的1就会变为0，原来在1后面的所有的0都会变成1(如果最右边的1后面还有0的话)。其余所有位将不会受到影响。

举个例子：一个二进制数1100，从右边数起第三位是处于最右边的一个1。减去1后，第三位变成0，它后面的两位0变成了1，而前面的1保持不变，因此得到的结果是1011.我们发现减1的结果是把最右边的一个1开始的所有位都取反了。这个时候如果我们再把原来的整数和减去1之后的结果做与运算，从原来整数最右边一个1那一位开始所有位都会变成0。如1100&1011=1000.也就是说，把一个整数减去1，再和原整数做与运算，会把该整数最右边一个1变成0.那么一个整数的二进制有多少个1，就可以进行多少次这样的操作。
```
public
class Solution {
   public
    int NumberOf1(int n) {
        int count = 0;
        while (n != 0) {
            count++;
            n = n & (n - 1);
        }
        return count;
    }
}
```

## 12. 数值的整数次方
> 给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。  

### 思路
#TODO 简单快速幂
```
#include <math.h>
class Solution {
   public:
    double Power(double base, int exponent) {
        double result = 1.0;
        long long p = abs((long long)exponent);
        while (p) {
            if (p & 1) {
                result *= base;
            }
            base *= base;
            p = p >> 1;
        }
        return exponent < 0 ? 1 / result : result;
    }
};
```

## 13. 调整数组顺序使奇数位于偶数前面
>  输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，所有的偶数位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。  

### 思路
1. 内部交换
```
#include <vector>
class Solution {
   public:
    void reOrderArray(vector<int> &array) {
        int size = array.size();
        for (int i = 0; i < size; i++) {
            if (!(array[i] % 2)) {
                for (int j = i + 1; j < size; j++) {
                    if (array[j] % 2) {
                        int temp = array[j];
                        for (int t = j - 1; t >= i; t--) {
                            array[t + 1] = array[t];
                        }
                        array[i] = temp;
                        i++;
                    }
                }
            }
        }
    }
};
```

2. 空间换时间，分别存储奇数偶数，再合并
```
class Solution {
   public:
    void reOrderArray(vector<int> &array) {
        vector<int> array_temp;
        vector<int>::iterator ib1, ie1;
        ib1 = array.begin();

        for (; ib1 !=
               array.end();) {  //遇见偶数，就保存到新数组，同时从原数组中删除
            if (*ib1 % 2 == 0) {
                array_temp.push_back(*ib1);
                ib1 = array.erase(ib1);
            } else {
                ib1++;
            }
        }
        vector<int>::iterator ib2, ie2;
        ib2 = array_temp.begin();
        ie2 = array_temp.end();

        for (; ib2 != ie2; ib2++)  //将新数组的数添加到老数组
        {
            array.push_back(*ib2);
        }
    }
};
```

## 14. 链表中倒数第k个结点
>  输入一个链表，输出该链表中倒数第k个结点。  

### 思路
两个指针，一个比另一个快k个，知道快指针到链表尾，返回慢指针节点
```
class Solution {
   public:
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        if (!pListHead || k == 0) return nullptr;
        ListNode* cur = pListHead;
        ListNode* rear = cur;
        for (int i = 1; i < k; i++) {
            if (rear->next) {
                rear = rear->next;
            } else {
                return nullptr;
            }
        }
        while (rear->next) {
            rear = rear->next;
            cur = cur->next;
        }
        return cur;
    }
};
```

## 15. 反转链表
>  输入一个链表，反转链表后，输出新链表的表头  

### 思路
从第二个节点开始逐渐移动至头部。
```
class Solution {
   public:
    ListNode* ReverseList(ListNode* pHead) {
        if (!pHead || !(pHead->next)) {
            return pHead;
        }
        ListNode* nHead = pHead;
        ListNode* cur = pHead;
        while (cur->next) {
            ListNode* tmp = cur->next;
            cur->next = tmp->next;
            tmp->next = nHead;
            nHead = tmp;
        }
        return nHead;
    }
};
```

## 16. 合并两个排序的链表
>  输入两个单调递增的链表，输出两个链表合成后的链表，当然我们需要合成后的链表满足单调不减规则。  

### 思路
非递归
```
class Solution {
   public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
        ListNode* nHead = new ListNode(1);
        ListNode* cur = nHead;
        ListNode *t1 = pHead1, *t2 = pHead2;
        while (t1 && t2) {
            if (t1->val <= t2->val) {
                cur->next = t1;
                cur = cur->next;
                t1 = t1->next;
            } else {
                cur->next = t2;
                cur = cur->next;
                t2 = t2->next;
            }
        }
        if (t1) {
            cur->next = t1;
        } else if (t2) {
            cur->next = t2;
        }
        return nHead->next;
    }
};
```

##  17. 树的子结构
> 输入两棵二叉树A，B，判断B是不是A的子结构。（ps：我们约定空树不是任意一个树的子结构）  

### 思路
设置全局变量result为false，首先判断根节点是否相等，相等则递归比较左右子树；根节点不相等则首先递归向左子树和右子树搜索搜索根节点相同的节点。
```
class Solution {
   public:
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2) {
        if (!pRoot2 || !pRoot1) {
            return false;
        } else {
            bool result = false;
            // 数值相等时进一步判断
            if (pRoot1->val == pRoot2->val) {
                result = aux_hasSubtree(pRoot1, pRoot2);
            }
            // 根节点数值不一致时递归向左子树寻找节点数值相同的节点
            if (!result) {
                result = HasSubtree(pRoot1->left, pRoot2);
            }
            // 左子树也未寻找到时递归向右子树寻找
            if (!result) {
                result = HasSubtree(pRoot1->right, pRoot2);
            }
            return result;
        }
    }

    bool aux_hasSubtree(TreeNode* pRoot1, TreeNode* pRoot2) {
        // pRoot1到达叶节点但pRoot2未到达叶节点，为false
        if (!pRoot1 && pRoot2) {
            return false;
        }
        // pRoot2到达叶节点，无论pRoot1是否到达，均为true
        else if (!pRoot2) {
            return true;
        }
        // 都存在但数值不同，为false
        else if (pRoot1 && pRoot2 && pRoot1->val != pRoot2->val) {
            return false;
        }
        // 均存在且数值相同时，递归分别向各自左右子树判断
        else {
            return aux_hasSubtree(pRoot1->left, pRoot2->left) &&
                   aux_hasSubtree(pRoot1->right, pRoot2->right);
        }
    }
};
```

## 18. 二叉树的镜像
>  操作给定的二叉树，将其变换为源二叉树的镜像  

### 思路
递归向下反转二叉树
```
class Solution {
   public:
    void Mirror(TreeNode *pRoot) {
        if (!pRoot) {
            return;
        }
        // 递归调换左右子树指针
        TreeNode *left = pRoot->left, *right = pRoot->right;
        pRoot->left = right;
        pRoot->right = left;
        Mirror(pRoot->left);
        Mirror(pRoot->right);
    }
};
```

##  19. 顺时针打印矩阵
> 输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，例如，如果输入如下4 X 4矩阵： 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 则依次打印出数字1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.  

### 思路
#TODO 顺时针打印就是按圈数循环打印，一圈包含两行或者两列，在打印的时候会出现某一圈中只包含一行，要判断从左向右打印和从右向左打印的时候是否会出现重复打印，同样只包含一列时，要判断从上向下打印和从下向上打印的时候是否会出现重复打印的情况
```
class Solution {
   public:
    vector<int> printMatrix(vector<vector<int> > matrix) {
        vector<int> res;
        res.clear();
        int row = matrix.size();        //行数
        int collor = matrix[0].size();  //列数
        //计算打印的圈数
        int circle = ((row < collor ? row : collor) - 1) / 2 + 1;  //圈数
        for (int i = 0; i < circle; i++) {
            //从左向右打印
            for (int j = i; j < collor - i; j++) res.push_back(matrix[i][j]);
            //从上往下的每一列数据
            for (int k = i + 1; k < row - i; k++)
                res.push_back(matrix[k][collor - 1 - i]);
            //判断是否会重复打印(从右向左的每行数据)
            for (int m = collor - i - 2; (m >= i) && (row - i - 1 != i); m--)
                res.push_back(matrix[row - i - 1][m]);
            //判断是否会重复打印(从下往上的每一列数据)
            for (int n = row - i - 2; (n > i) && (collor - i - 1 != i); n--)
                res.push_back(matrix[n][i]);
        }
        return res;
    }
};
```

##  20. 包含min函数的栈
>  定义栈的数据结构，请在该类型中实现一个能够得到栈中所含最小元素的min函数（时间复杂度应为O(1)）。  

### 思路
采用一个辅助栈，如果当入栈元素小于等于辅助栈栈顶元素时，同时压入两个栈，如果大于辅助栈栈顶元素则只压入存储栈中
```
class Solution {
   public:
    void push(int value) {
        if (realS.empty()) {
            realS.push(value);
            minS.push(value);
        } else {
            if (value <= minS.top()) {
                realS.push(value);
                minS.push(value);
            } else {
                realS.push(value);
            }
        }
    }
    void pop() {
        if (minS.top() == realS.top()) {
            minS.pop();
        }
        realS.pop();
    }
    int top() { return realS.top(); }
    int min() { return minS.top(); }

   private:
    stack<int> minS;
    stack<int> realS;
};
```

## 21. 栈的压入、弹出序列
> 输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。（注意：这两个序列的长度是相等的）  

### 思路
模拟堆栈操作：将原数列依次压栈，栈顶元素与所给出栈队列相比，如果相同则出栈，
如果不同则继续压栈，直到原数列中所有数字压栈完毕。
检测栈中是否为空，若空，说明出栈队列可由原数列进行栈操作得到。否则，说明出栈队列不能由原数列进行栈操作得到。
```
class Solution {
   public:
    bool IsPopOrder(vector<int> pushV, vector<int> popV) {
        if (pushV.empty() || popV.empty() || pushV.size() != popV.size())
            return false;
        stack<int> s;
        int j = 0;
        for (int i = 0; i < pushV.size(); ++i) {
            s.push(pushV[i]);
            while (!s.empty() && s.top() == popV[j]) {
                s.pop();
                ++j;
            }
        }
        if (s.empty()) return true;
        return false;
    }
};
```

## 22. 从上往下打印二叉树
>  从上往下打印出二叉树的每个节点，同层节点从左至右打印。  

### 思路
即二叉树的广度遍历，借助辅助队列，从根节点开始，将根节点的左右子节点压入队列，并访问根节点数据，再依次对队列中的每个节点进行同样操作，直至队列为空为止。
```
class Solution {
   public:
    vector<int> PrintFromTopToBottom(TreeNode *root) {
        vector<int> result;
        if (!root) {
            return result;
        } else {
            queue<TreeNode *> q;
            q.push(root);
            while (!q.empty()) {
                if (q.front()->left) {
                    q.push(q.front()->left);
                }
                if (q.front()->right) {
                    q.push(q.front()->right);
                }
                result.push_back(q.front()->val);
                q.pop();
            }
            return result;
        }
    }
};
```

##  23. 二叉搜索树的后续遍历序列
>  输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。  

### 思路
BST的后序序列的合法序列是，对于一个序列S，最后一个元素是x （也就是根），如果去掉最后一个元素的序列为T，那么T满足：T可以分成两段，前一段（左子树）小于x，后一段（右子树）大于x，且这两段（子树）都是合法的后序序列。
```
class Solution {
   public:
    bool VerifySquenceOfBST(vector<int> s) {
        int len = s.size();
        if (len == 0) return false;
        if (len < 2) return true;
        int rootVal = s[len - 1];
        int i = 0;
        while (i < len && s[i] < rootVal) {
            i++;
        }
        for (int j = i; j < len; j++) {
            if (s[j] < rootVal) {
                return false;
            }
        }
        vector<int> left, right;
        for (int k = 0; k < i; k++) {
            left.push_back(s[k]);
        }
        for (int k = i; k < len - 1; k++) {
            right.push_back(s[k]);
        }
        if (left.size() && right.size()) {
            return VerifySquenceOfBST(left) && VerifySquenceOfBST(right);
        } else if (left.size()) {
            return VerifySquenceOfBST(left);
        } else if (right.size()) {
            return VerifySquenceOfBST(right);
        }
        return false;
    }
};
```

##  24. 二叉树中和为某一值的路径
>  输入一颗二叉树的跟节点和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。(注意: 在返回值的list中，数组长度大的数组靠前)  

### 思路
树的深度搜索
```
class Solution {
    vector<vector<int> > result;
    vector<int> tmp;

   public:
    vector<vector<int> > FindPath(TreeNode* root, int expectNumber) {
        if (root) {
            DFS(root, expectNumber);
        }
        return result;
    }

    void DFS(TreeNode* root, int expectNumber) {
        tmp.push_back(root->val);
        if (root->val == expectNumber && !root->left && !root->right) {
            result.push_back(tmp);
        } else {
            if (root->left) {
                DFS(root->left, expectNumber - root->val);
            }
            if (root->right) {
                DFS(root->right, expectNumber - root->val);
            }
        }
        tmp.pop_back();
    }
};
```

## 25. 复杂链表的复制
> 输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针指向任意一个节点），返回结果为复制后复杂链表的head。（注意，输出结果中请不要返回参数中的节点引用，否则判题程序会直接返回空）  

### 思路
1、复制每个节点，如：复制节点A得到A1，将A1插入节点A后面
2、遍历链表，A1->random = A->random->next;
3、将链表拆分成原链表和复制后的链表
```
class Solution {
   public:
    RandomListNode* Clone(RandomListNode* pHead) {
        if (!pHead)
            return nullptr;
        else {
            RandomListNode* cur = pHead;
            while (cur) {
                RandomListNode* tmp = new RandomListNode(cur->label);
                tmp->next = cur->next;
                cur->next = tmp;
                cur = tmp->next;
            }

            cur = pHead;
            while (cur) {
                cur->next->random = cur->random->next;
                cur = cur->next->next;
            }

            cur = pHead;
            RandomListNode* result = pHead->next;
            while (cur->next) {
                RandomListNode* tmp = cur->next;
                cur->next = tmp->next;
                cur = tmp;
            }
            return result;
        }
    }
};
```

##  26. 二叉搜索树与双向链表
> 输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。要求不能创建任何新的结点，只能调整树中结点指针的指向。  

### 思路
1. 递归方法
```
class Solution {
   public:
    TreeNode* Convert(TreeNode* root) {
        if (!root) return nullptr;
        if (!root->left && !root->right) {
            return root;
        }
        TreeNode* left = Convert(root->left);
        TreeNode* p = left;
        while (p && p->right) {
            p = p->right;
        }
        if (p) {
            p->right = root;
            root->left = p;
        }
        TreeNode* right = Convert(root->right);
        if (right) {
            right->left = root;
            root->right = right;
        }
        return left ? left : root;
    }
};
```

2. 非递归方法
1.核心是中序遍历的非递归算法。
2.修改当前遍历节点与前一遍历节点的指针指向。
```
class Solution {
   public:
    TreeNode* Convert(TreeNode* pRootOfTree) {
        if (pRootOfTree == nullptr) return nullptr;
        TreeNode* pre = nullptr;

        convertHelper(pRootOfTree, pre);

        TreeNode* res = pRootOfTree;
        while (res->left) res = res->left;
        return res;
    }

    void convertHelper(TreeNode* cur, TreeNode*& pre) {
        if (cur == nullptr) return;
        convertHelper(cur->left, pre);
        cur->left = pre;
        if (pre) pre->right = cur;
        pre = cur;
        convertHelper(cur->right, pre);
    }
};
```

## 27. 字符串的排列
> 输入一个字符串,按字典序打印出该字符串中字符的所有排列。例如输入字符串abc,则打印出由字符a,b,c所能排列出来的所有字符串abc,acb,bac,bca,cab和cba。  

### 思路
递归法，问题转换为先固定第一个字符，求剩余字符的排列；求剩余字符排列时跟原问题一样。
(1) 遍历出所有可能出现在第一个位置的字符（即：依次将第一个字符同后面所有字符交换）； 
(2) 固定第一个字符，求后面字符的排列*（即：在第1步的遍历过程中，插入递归进行实现）。 
需要注意的几点： 
(1) 先确定递归结束的条件，例如本题中可设begin == str.size() - 1; 
(2) 形如aba或aa等特殊测试用例的情况，vector在进行push_back时是不考虑重复情况的，需要自行控制； 
(3) 输出的排列可能不是按字典顺序排列的，可能导致无法完全通过测试用例，考虑输出前排序，或者递归之后取消复位操作。
```
class Solution {
   public:
    vector<string> Permutation(string str) {
        vector<string> result;
        if (str.empty()) return result;
        Permutation(str, result, 0);
        // 此时得到的result中排列并不是字典顺序，可以单独再排下序
        sort(result.begin(), result.end());
        return result;
    }

    void Permutation(string str, vector<string> &result, int begin) {
        if (begin ==
            str.size() - 1)  // 递归结束条件：索引已经指向str最后一个元素时
        {
            if (find(result.begin(), result.end(), str) == result.end()) {
                // 如果result中不存在str，才添加；避免aa和aa重复添加的情况
                result.push_back(str);
            }
        } else {
            // 第一次循环i与begin相等，相当于第一个位置自身交换，关键在于之后的循环，
            // 之后i !=
            // begin，则会交换两个不同位置上的字符，直到begin==str.size()-1，进行输出；
            for (int i = begin; i < str.size(); ++i) {
                swap(str[i], str[begin]);
                Permutation(str, result, begin + 1);
                swap(
                    str[i],
                    str[begin]);  // 复位，用以恢复之前字符串顺序，达到第一位依次跟其他位交换的目的
            }
        }
    }

    void swap(char &fir, char &sec) {
        char temp = fir;
        fir = sec;
        sec = temp;
    }
};
```

## 28. 数组中出现次数超过一半的数字
> 数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}。由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。如果不存在则输出0。  

### 思路
1. 使用map记录数字出现的次数
```
class Solution {
   public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        int len = numbers.size();
        if (!len) return 0;
        map<int, int> num;
        for (int i = 0; i < len; i++) {
            map<int, int>::iterator itr = num.find(numbers[i]);
            if (itr != num.end()) {
                itr->second++;
            } else {
                num.insert(std::pair<int, int>(numbers[i], 1));
            }
        }
        map<int, int>::iterator itr = num.begin();
        while (itr != num.end()) {
            if (itr->second > (len / 2)) {
                return itr->first;
            }
            itr++;
        }
        return 0;
    }
};
```

2. 如果有符合条件的数字，则它出现的次数比其他所有数字出现的次数和还要多。
在遍历数组时保存两个值：一是数组中一个数字，一是次数。遍历下一个数字时，若它与之前保存的数字相同，则次数加1，否则次数减1；若次数为0，则保存下一个数字，并将次数置为1。遍历结束后，所保存的数字即为所求。然后再判断它是否符合条件即可。 
```
class Solution {
   public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        if (numbers.empty()) return 0;

        // 遍历每个元素，并记录次数；若与前一个元素相同，则次数加1，否则次数减1
        int result = numbers[0];
        int times = 1;  // 次数

        for (int i = 1; i < numbers.size(); ++i) {
            if (times == 0) {
                // 更新result的值为当前元素，并置次数为1
                result = numbers[i];
                times = 1;
            } else if (numbers[i] == result) {
                ++times;  // 相同则加1
            } else {
                --times;  // 不同则减1
            }
        }

        // 判断result是否符合条件，即出现次数大于数组长度的一半
        times = 0;
        for (int i = 0; i < numbers.size(); ++i) {
            if (numbers[i] == result) ++times;
        }

        return (times > numbers.size() / 2) ? result : 0;
    }
};
```

## 29. 最小的K个数
> 输入n个整数，找出其中最小的K个数。例如输入4,5,1,6,2,7,3,8这8个数字，则最小的4个数字是1,2,3,4,。  

### 思路
利用堆排序，O(N logK)，适合处理海量数据 
(1) 遍历输入数组，将前k个数插入到推中；（利用multiset来做为堆的实现） 
(2) 继续从输入数组中读入元素做为待插入整数，并将它与堆中最大值比较：如果待插入的值比当前已有的最大值小，则用这个数替换当前已有的最大值；如果待插入的值比当前已有的最大值还大，则抛弃这个数，继续读下一个数。 
这样动态维护堆中这k个数，以保证它只储存输入数组中的前k个最小的数，最后输出堆即可。
```
class Solution {
   public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> result;
        int len = input.size();
        if (input.empty() || k <= 0 || len < k) return result;

        multiset<int, greater<int> > leastNumbers;  // 从大到小排序
        multiset<int, greater<int> >::iterator iterGreater;  // 定义迭代器

        vector<int>::iterator iter = input.begin();
        for (; iter != input.end(); ++iter) {
            // 将前k个数直接插入进multiset中，注意是小于K
            if (leastNumbers.size() < k) {
                leastNumbers.insert(*iter);
            } else {
                // 因为设置的从大到小排序，故multiset中第一个位置的元素即为最大值
                iterGreater = leastNumbers.begin();

                // 如果input中当前元素比multiset中最大元素小，则替换；即保持multiset中这k个元素是最小的。
                if (*iter < *(leastNumbers.begin())) {
                    // 替换掉当前最大值
                    leastNumbers.erase(iterGreater);
                    leastNumbers.insert(*iter);
                }
            }
        }

        for (iterGreater = leastNumbers.begin();
             iterGreater != leastNumbers.end(); ++iterGreater) {
            result.push_back(*iterGreater);  // 将multiset中这k个元素输出
        }

        return result;
    }
};
```

## 30. 连续子数组的最大和
> HZ偶尔会拿些专业问题来忽悠那些非计算机专业的同学。今天测试组开完会后,他又发话了:在古老的一维模式识别中,常常需要计算连续子向量的最大和,当向量全为正数的时候,问题很好解决。但是,如果向量中包含负数,是否应该包含某个负数,并期望旁边的正数会弥补它呢？例如:{6,-3,-2,7,-15,1,2,2},连续子向量的最大和为8(从第0个开始,到第3个为止)。给一个数组，返回它的最大连续子序列的和，你会不会被他忽悠住？(子向量的长度至少是1)  

### 思路
动态规划
```
#include <vector>;
using namespace std;

class Solution {
   public:
    int FindGreatestSumOfSubArray(vector<int> array) {
        if (array.empty()) return 0;
        int sum = array[0], tmp = array[0];
        for (int i = 1; i < array.size(); i++) {
            if (tmp < 0) {
                tmp = array[i];
            } else {
                tmp += array[i];
            }
            sum = sum > tmp ? sum : tmp;
        }
        return sum;
    }
};
```

## 31. 整数中1出现的次数（从1到n整数中1出现的次数）
> 求出1~13的整数中1出现的次数,并算出100~1300的整数中1出现的次数？为此他特别数了一下1~13中包含1的数字有1、10、11、12、13因此共出现6次,但是对于后面问题他就没辙了。ACMer希望你们帮帮他,并把问题更加普遍化,可以很快的求出任意非负整数区间中1出现的次数（从1 到 n 中1出现的次数）。  

### 思路
#TODO
```
class Solution {
   public:
    int NumberOf1Between1AndN_Solution(int n) {
        if (n <= 0) return 0;
        int count = 0;
        for (long i = 1; i <= n; i *= 10) {
            long diviver = i * 10;
            count += (n / diviver) * i +
                     Math.min(Math.max(n % diviver - i + 1, 0), i);
        }
        return count;
    }
}
```

## 32. 把数组排成最小的数
> 输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。例如输入数组{3，32，321}，则打印出这三个数字能排成的最小数字为321323。  

### 思路
先将整型数组转换成String数组，然后将String数组排序，最后将排好序的字符串数组拼接出来。
若ab > ba 则 a > b，
若ab < ba 则 a < b，
若ab = ba 则 a = b；

```
class Solution {
   public:
    string PrintMinNumber(vector<int> numbers) {
        string result;
        if (numbers.size() <= 0) return result;
        vector<string> strNum;
        for (int i = 0; i < numbers.size(); i++) {
            stringstream ss;
            ss << numbers[i];
            string s = ss.str();
            strNum.push_back(s);
        }
        sort(strNum.begin(), strNum.end(), compare);
        for (int i = 0; i < strNum.size(); i++) {
            result.append(strNum[i]);
        }
        return result;
    }

    static bool compare(const string &str1, const string &str2) {
        string s1 = str1 + str2;
        string s2 = str2 + str1;
        return s1 < s2;
    }
};
```

## 33. 丑数
> 把只包含质因子2、3和5的数称作丑数（Ugly Number）。例如6、8都是丑数，但14不是，因为它包含质因子7。 习惯上我们把1当做是第一个丑数。求按从小到大的顺序的第N个丑数。  

### 思路
#TODO
```
class Solution {
   public:
    int GetUglyNumber_Solution(int index) {
        if (index < 7) return index;
        int p2 = 0, p3 = 0, p5 = 0, newNum = 1;
        vector<int> arr;
        arr.push_back(newNum);
        while (arr.size() < index) {
            newNum = min(arr[p2] * 2, min(arr[p3] * 3, arr[p5] * 5));
            if (newNum == arr[p2] * 2) p2++;
            if (newNum == arr[p3] * 3) p3++;
            if (newNum == arr[p5] * 5) p5++;
            arr.push_back(newNum);
        }
        return newNum;
    }
};
```

## 34. 第一个只出现一次的字符
> 在一个字符串(0<=字符串长度<=10000，全部由字母组成)中找到第一个只出现一次的字符,并返回它的位置, 如果没有则返回 -1（需要区分大小写）  

### 思路
使用map存储每个字符出现的次数，再通过字符串顺序遍历查找第一个只出现一次的字符
```
class Solution {
   public:
    int FirstNotRepeatingChar(string str) {
        map<char, int> mp;
        for (int i = 0; i < str.size(); i++) {
            mp[str[i]]++;
        }
        for (int i = 0; i < str.size(); i++) {
            if (mp[str[i]] == 1) return i;
        }
        return -1;
    }
};
```

##  35. 数组中的逆序对
> 在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组,求出这个数组中的逆序对的总数P。并将P对1000000007取模的结果输出。 即输出P%1000000007  

### 思路
归并排序的改进，把数据分成前后两个数组(递归分到每个数组仅有一个数据项)，合并数组，合并时，出现前面的数组值array[I]大于后面数组值array[j]时；则前面数组array[I]~array[mid]都是大于array[j]的，count += mid+1 - i
参考剑指Offer，但是感觉剑指Offer归并过程少了一步拷贝过程。
还有就是测试用例输出结果比较大，对每次返回的count mod(1000000007)求余
```
class Solution {
   public:
    int num = 0;
    int InversePairs(vector<int> data) {
        if (data.size() != 0) {
            MergeSort(data, 0, data.size() - 1);
        }
        return num;
    }

    void MergeSort(vector<int> data, int start, int end) {
        if (start >= end) {
            return;
        } else {
            int mid = (start + end) >> 1;
            MergeSort(data, start, mid);
            MergeSort(data, mid + 1, end);
            Merge(data, start, mid, end);
        }
    }

    void Merge(vector<int> data, int start, int mid, int end) {
        int *tmp = new int[end - start + 1];
        int i = start, j = mid + 1, k = 0;
        while (i <= mid && j <= end) {
            if (data[i] < data[j]) {
                tmp[k++] = data[i++];
            } else {
                tmp[k++] = data[j++];
                num += mid - 1 + 1;
            }
        }
        while (i <= mid) {
            tmp[k++] = data[i++];
        }
        while (j <= end) {
            tmp[k++] = data[j++];
        }
        for (k = 0; k < (end - start + 1); k++) {
            data[start + k] = tmp[k];
        }
    }
};
```

## 36. 两个链表的第一个公共结点
> 输入两个链表，找出它们的第一个公共结点。  

## 思路
找出2个链表的长度，然后让长的先走两个链表的长度差，然后再一起走
（因为2个链表用公共的尾部）
```
class Solution {
   public:
    ListNode *FindFirstCommonNode(ListNode *pHead1, ListNode *pHead2) {
        int len1 = length(pHead1), len2 = length(pHead2);
        ListNode *t1 = pHead1, *t2 = pHead2;
        if (len1 > len2) {
            for (int i = 0; i < (len1 - len2); i++) {
                t1 = t1->next;
            }
        } else if (len2 > len1) {
            for (int i = 0; i < (len2 - len1); i++) {
                t2 = t2->next;
            }
        }
        while (t1 != t2) {
            t1 = t1->next;
            t2 = t2->next;
        }
        return t1;
    }

    int length(ListNode *head) {
        int len = 0;
        ListNode *t = head;
        while (t) {
            len++;
            t = t->next;
        }
        return len;
    }
};
```

## 37. 数字在排序数组中出现的次数
>  统计一个数字在排序数组中出现的次数。  

### 思路
因为data中都是整数，所以可以稍微变一下，不是搜索k的两个位置，而是搜索k-0.5和k+0.5这两个数应该插入的位置，然后相减即可。
```
class Solution {
   public:
    int GetNumberOfK(vector<int> data, int k) {
        return biSearch(data, k + 0.5) - biSearch(data, k - 0.5);
    }

   private:
    int biSearch(const vector<int>& data, double num) {
        int s = 0, e = data.size() - 1;
        while (s <= e) {
            int mid = (e - s) / 2 + s;
            if (data[mid] < num)
                s = mid + 1;
            else if (data[mid] > num)
                e = mid - 1;
        }
        return s;
    }
};
```

## 38. 二叉树的深度
>  输入一棵二叉树，求该树的深度。从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，最长路径的长度为树的深度。  

### 思路
深度=max(左子树深度，右子树深度) + 1
```
class Solution {
   public:
    int TreeDepth(TreeNode *pRoot) {
        if (!pRoot) {
            return 0;
        } else {
            int left = TreeDepth(pRoot->left);
            int right = TreeDepth(pRoot->right);
            return left > right ? 1 + left : 1 + right;
        }
    }
};
```

## 39. 平衡二叉树
> 输入一棵二叉树， 判断二叉树是否为平衡二叉树  

###  思路
计算二叉树深度时判断左右子树深度是否平衡，不平衡直接返回-1
```
class Solution {
   public:
    bool IsBalanced_Solution(TreeNode* pRoot) { return Depth(pRoot) != -1; }

    int Depth(TreeNode* pRoot) {
        if (!pRoot) return 0;
        if (Depth(pRoot->left) == -1 || Depth(pRoot->right) == -1) {
            return -1;
        } else {
            int left = Depth(pRoot->left);
            int right = Depth(pRoot->right);
            if (left - right > 1 || right - left > 1) {
                return -1;
            } else {
                return left > right ? 1 + left : 1 + right;
            }
        }
    }
};
```

## 40. 数组中只出现一次的数字
> 一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字。  

### 思路
位运算中异或的性质：两个相同数字异或=0，一个数和0异或还是它本身
当只有一个数出现一次时，我们把数组中所有的数，依次异或运算，最后剩下的就是落单的数，因为成对儿出现的都抵消了。
```
class Solution {
   public:
    void FindNumsAppearOnce(vector<int> data, int *num1, int *num2) {
        if (data.size() < 2) return;
        int size = data.size();
        int temp = data[0];
        for (int i = 1; i < size; i++) temp = temp ^ data[i];
        if (temp == 0) return;
        int index = 0;
        while ((temp & 1) == 0) {
            temp = temp >> 1;
            ++index;
        }
        *num1 = *num2 = 0;
        for (int i = 0; i < size; i++) {
            if (IsBit(data[i], index))
                *num1 ^= data[i];
            else
                *num2 ^= data[i];
        }
    }
    bool IsBit(int num, int index) {
        num = num >> index;
        return (num & 1);
    }
};
```


## 41. 和为S的连续正数序列
> 小明很喜欢数学,有一天他在做数学作业时,要求计算出9~16的和,他马上就写出了正确答案是100。但是他并不满足于此,他在想究竟有多少种连续的正数序列的和为100(至少包括两个数)。没多久,他就得到另一组连续正数和为100的序列:18,19,20,21,22。现在把问题交给你,你能不能也很快的找出所有和为S的连续正数序列? Good Luck!  

### 思路
双指针技术，就是相当于有一个窗口，窗口的左右两边就是两个指针，我们根据窗口内值之和来确定窗口的位置和宽度。当总和小于sum，大指针继续+，否则小指针+
```
class Solution {
public:
    vector<vector<int> > FindContinuousSequence(int sum) {
        vector<vector<int>> result;
        int low = 1, high = 2;
        while(high > low) {
            int cur = (high + low) * (high - low + 1) / 2;
            if (cur == sum) {
                vector<int> tmp;
                for(int i = low; i <= high; i++) {
                    tmp.push_back(i);
                }
                result.push_back(tmp);
                low ++;
            } else if (cur > sum) {
                low ++;
            } else if (cur < sum) {
                high ++;
            }
        }
        return result;
    }
};
```

## 42. 和为S的两个数字
> 输入一个递增排序的数组和一个数字S，在数组中查找两个数，使得他们的和正好是S，如果有多对数字的和等于S，输出两个数的乘积最小的。  

### 思路
数列满足递增，设两个头尾两个指针i和j， 
若ai + aj == sum，就是答案（相差越远乘积越小） 
若ai + aj > sum，aj肯定不是答案之一（前面已得出 i 前面的数已是不可能），j -= 1 
若ai + aj < sum，ai肯定不是答案之一（前面已得出 j 后面的数已是不可能），i += 1 
O(n)
```
class Solution {
   public:
    vector<int> FindNumbersWithSum(vector<int> array, int sum) {
        int size = array.size(), low = 0, high = size - 1;
        vector<int> tmp;
        if (size < 2) {
            return tmp;
        }
        while (high < size && high > low) {
            if (array[low] + array[high] == sum) {
                tmp.push_back(array[low]);
                tmp.push_back(array[high]);
                return tmp;
            } else if (array[low] + array[high] > sum) {
                high--;
            } else if (array[low] + array[high] < sum) {
                low++;
            }
        }
        return tmp;
    }
};
```

## 43. 左旋转字符串
> 汇编语言中有一种移位指令叫做循环左移（ROL），现在有个简单的任务，就是用字符串模拟这个指令的运算结果。对于一个给定的字符序列S，请你把其循环左移K位后的序列输出。例如，字符序列S=”abcXYZdef”,要求输出循环左移3位后的结果，即“XYZdefabc”。是不是很简单？OK，搞定它！  

### 思路
将字符串复制拼接到尾部，并根据移动位数向右偏移截取
```
class Solution {
   public:
    string LeftRotateString(string str, int n) {
        int len = str.length();
        if (len == 0) return "";
        n = n % len;
        str += str;
        return str.substr(n, len);
    }
};
```

## 44. 翻转单词顺序列
> 牛客最近来了一个新员工Fish，每天早晨总是会拿着一本英文杂志，写些句子在本子上。同事Cat对Fish写的内容颇感兴趣，有一天他向Fish借来翻看，但却读不懂它的意思。例如，“student. a am I”。后来才意识到，这家伙原来把句子单词的顺序翻转了，正确的句子应该是“I am a student.”。Cat对一一的翻转这些单词顺序可不在行，你能帮助他么？  

### 思路
先对字符串整体进行翻转，再对每个单词进行翻转
```
class Solution {
   public:
    string ReverseSentence(string str) {
        if (str.empty()) return str;
        reverse(str.begin(), str.end());
        int low = 0, high = 0;
        while (low < str.size()) {
            while (str[low] == ' ') {
                low++;
            }
            high = low;
            while (high < str.size() && str[high] != ' ') {
                high++;
            }
            reverse(str.begin() + low, str.begin() + high);
            low = high;
        }
        return str;
    }
};
```

## 45. 扑克牌顺子
> LL今天心情特别好,因为他去买了一副扑克牌,发现里面居然有2个大王,2个小王(一副牌原本是54张^_^)...他随机从中抽出了5张牌,想测测自己的手气,看看能不能抽到顺子,如果抽到的话,他决定去买体育彩票,嘿嘿！！“红心A,黑桃3,小王,大王,方片5”,“Oh My God!”不是顺子.....LL不高兴了,他想了想,决定大\小 王可以看成任何数字,并且A看作1,J为11,Q为12,K为13。上面的5张牌就可以变成“1,2,3,4,5”(大小王分别看作2和4),“So Lucky!”。LL决定去买体育彩票啦。 现在,要求你使用这幅牌模拟上面的过程,然后告诉我们LL的运气如何， 如果牌能组成顺子就输出true，否则就输出false。为了方便起见,你可以认为大小王是0。  

### 思路
Max 记录 最大值
Min 记录 最小值
min ,max 都不记0
满足条件：
1 max - min <5
2 除0外没有重复的数字(牌)
3 数组长度 为5
```
class Solution {
    bool IsContinuous(vector<int> numbers) {
        if (numbers.size() == 5) {
            int max = 0, min = 14;
            int d[14];
            for (int i = 0; i < 14; i++) {
                d[i] = 0;
            }
            for (int i = 0; i < 5; i++) {
                if (numbers[i] == 0) {
                    continue;
                } else {
                    d[numbers[i]]++;
                    if (d[numbers[i]] > 1) {
                        return false;
                    }
                    if (numbers[i] < min) {
                        min = numbers[i];
                    }
                    if (numbers[i] > max) {
                        max = numbers[i];
                    }
                }
            }
            if (max - min < 5) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
};
```

## 46. 孩子们的游戏(圆圈中最后剩下的数)
> 每年六一儿童节,牛客都会准备一些小礼物去看望孤儿院的小朋友,今年亦是如此。HF作为牛客的资深元老,自然也准备了一些小游戏。其中,有个游戏是这样的:首先,让小朋友们围成一个大圈。然后,他随机指定一个数m,让编号为0的小朋友开始报数。每次喊到m-1的那个小朋友要出列唱首歌,然后可以在礼品箱中任意的挑选礼物,并且不再回到圈中,从他的下一个小朋友开始,继续0...m-1报数....这样下去....直到剩下最后一个小朋友,可以不用表演,并且拿到牛客名贵的“名侦探柯南”典藏版(名额有限哦!!^_^)。请你试着想下,哪个小朋友会得到这份礼品呢？(注：小朋友的编号是从0到n-1)  

### 思路
```
class Solution {
   public:
    int LastRemaining_Solution(int n, int m) {
        if (n == 0) {
            return -1;
        } else if (n == 1) {
            return 0;
        } else {
            return (LastRemaining_Solution(n - 1, m) + m) % n;
        }
    }
};
```

## 47. 求1+2+3+...+n
> 求1+2+3+...+n，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。  

### 思路
递归，短路求值远离
```
class Solution {
   public:
    int Sum_Solution(int n) {
        int ans = n;
        ans && (ans += Sum_Solution(n - 1));
        return ans;
    }
};
```

## 48. 不用加减乘除做加法
> 写一个函数，求两个整数之和，要求在函数体内不得使用+、-、*、/四则运算符号。  

### 思路
1. 按位与是查看两个数哪些二进制位都为1，这些都是进位位，结果需左移一位，表示进位后的结果
2. 异或是查看两个数哪些二进制位只有一个为1，这些是非进位位，可以直接加、减，结果表示非进位位进行加操作后的结果
3. n1&n2是查看有没有进位位了，如果有，需要重复step1、step2；如果没有，保留n1、n2上二进制为1的部分，用或将之合为一个数，即为最后结果
```
class Solution {
   public:
    int Add(int num1, int num2) {
        int n1, n2;
        n1 = (num1 & num2) << 1;
        n2 = num1 ^ num2;
        while (n1 & n2) {
            num1 = n1;
            num2 = n2;
            n1 = (num1 & num2) << 1;
            n2 = num1 ^ num2;
        }
        return n1 | n2;
    }
};
```

## 49. 把字符串转换成整数
> 将一个字符串转换成一个整数(实现Integer.valueOf(string)的功能，但是string不符合数字要求时返回0)，要求不能使用字符串转换整数的库函数。 数值为0或者字符串不是一个合法的数值则返回0。  

### 思路
先判断符号，再判断后面是否存在非数字字符
```
class Solution {
   public:
    int StrToInt(string str) {
        int len = str.size();
        for (int i = 1; i < len; i++) {
            if (str[i] < '0' || str[i] > '9') {
                return 0;
            }
        }
        int result = 0, sign = 0;
        if ((str[0] > '0' && str[0] < '9') || str[0] == '+' || str[0] == '-') {
            if (str[0] == '-') {
                sign = -1;
            } else if (str[0] == '+') {
                sign = 1;
            }
            int t = sign == 0 ? 0 : 1;
            for (int i = t; i < len; i++) {
                result += (str[i] - '0') * pow(10, (len - 1 - i));
            }
            return sign == 0 ? result : sign * result;
        } else {
            return 0;
        }
    }
};
```

## 50. 数组中重复的数字
> 在一个长度为n的数组里的所有数字都在0到n-1的范围内。 数组中某些数字是重复的，但不知道有几个数字是重复的。也不知道每个数字重复几次。请找出数组中任意一个重复的数字。 例如，如果输入长度为7的数组{2,3,1,0,2,5,3}，那么对应的输出是第一个重复的数字2。  

### 思路
#TODO
```
class Solution {
   public:
    bool duplicate(int numbers[], int length, int* duplication) {
        int d[length];
        for (int i = 0; i < length; i++) {
            d[i] = 0;
        }
        for (int i = 0; i < length; i++) {
            d[numbers[i]]++;
            if (d[numbers[i]] > 1) {
                *duplication = numbers[i];
                return true;
            }
        }
        return false;
    }
};
```

## 51. 构建乘积数组
> 给定一个数组A[0,1,...,n-1],请构建一个数组B[0,1,...,n-1],其中B中的元素B[i]=A[0]A[1]...A[i-1]A[i+1]...A[n-1]。不能使用除法。  

### 思路

```
class Solution {
   public:
    vector<int> multiply(const vector<int>& A) {
        int len = A.size();
        vector<int> B(len);
        for (int i = 0; i < len; i++) {
            B[i] = 1;
        }
        int ret = 1;
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                B[i] *= (i == j ? 1 : A[i]);
            }
        }
        return B;
    }
};
```

## 52. 正则表达式匹配
> 请实现一个函数用来匹配包括'.'和'**'的正则表达式。模式中的字符'.'表示任意一个字符，而'**'表示它前面的字符可以出现任意次（包含0次）。 在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab**ac**a"匹配，但是与"aa.a"和"ab*a"均不匹配  

### 思路
当模式中的第二个字符不是"*"时：
1、如果字符串第一个字符和模式中的第一个字符相匹配，那么字符串和模式都后移一个字符，然后匹配剩余的。 
2、如果 字符串第一个字符和模式中的第一个字符相不匹配，直接返回false。 

而当模式中的第二个字符是“*”时：
如果字符串第一个字符跟模式第一个字符不匹配，则模式后移2个字符，继续匹配。如果字符串第一个字符跟模式第一个字符匹配，可以有3种匹配方式： 
1、模式后移2字符，相当于x*被忽略； 
2、字符串后移1字符，模式后移2字符； 
3、字符串后移1字符，模式不变，即继续匹配字符下一位，因为*可以匹配多位； 
```
class Solution {
   public:
    bool match(char* str, char* pattern) {
        if (*str == 0 && *pattern == 0) {
            return true;
        } else if (*str != 0 && *pattern == 0) {
            return false;
        }

        if (*(pattern + 1) != '*') {
            if (*str == *pattern || (*pattern == '.' && *str != 0))
                return match(str + 1, pattern + 1);
            else
                return false;
        } else {
            if (*str == *pattern || (*pattern == '.' && *str != 0))
                return match(str, pattern + 2) || match(str + 1, pattern) ||
                       match(str + 1, pattern + 2);
            else
                return match(str, pattern + 2);
        }
    }
};
```

## 53. 表示数值的字符串
> 请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。例如，字符串"+100","5e2","-123","3.1416"和"-1E-16"都表示数值。 但是"12e","1a3.14","1.2.3","+-5"和"12e+4.3"都不是。  

### 思路

```
class Solution {
   public:
    bool isNumeric(char* str) {
        // 标记符号、小数点、e是否出现过
        bool sign = false, decimal = false, hasE = false;
        for (int i = 0; i < strlen(str); i++) {
            if (str[i] == 'e' || str[i] == 'E') {
                if (i == strlen(str) - 1) return false;  // e后面一定要接数字
                if (hasE) return false;  // 不能同时存在两个e
                hasE = true;
            } else if (str[i] == '+' || str[i] == '-') {
                // 第二次出现+-符号，则必须紧接在e之后
                if (sign && str[i - 1] != 'e' && str[i - 1] != 'E')
                    return false;
                // 第一次出现+-符号，且不是在字符串开头，则也必须紧接在e之后
                if (!sign && i > 0 && str[i - 1] != 'e' && str[i - 1] != 'E')
                    return false;
                sign = true;
            } else if (str[i] == '.') {
                // e后面不能接小数点，小数点不能出现两次
                if (hasE || decimal) return false;
                decimal = true;
            } else if (str[i] < '0' || str[i] > '9')  // 不合法字符
                return false;
        }
        return true;
    }
};
```

## 54. 字符流中第一个不重复的字符
> 请实现一个函数用来找出字符流中第一个只出现一次的字符。例如，当从字符流中只读出前两个字符"go"时，第一个只出现一次的字符是"g"。当从该字符流中读出前六个字符“google"时，第一个只出现一次的字符是"l"。  

### 思路
```
class Solution {
   public:
    // Insert one char from stringstream
    string s;
    char hash[256] = {0};
    void Insert(char ch) {
        s += ch;
        hash[ch]++;
    }
    // return the first appearence once char in current stringstream
    char FirstAppearingOnce() {
        int size = s.size();
        for (int i = 0; i < size; ++i) {
            if (hash[s[i]] == 1) return s[i];
        }
        return '#';
    }
};
```

## 55. 链表中环的入口结点
> 给一个链表，若其中包含环，请找出该链表的环的入口结点，否则，输出null。  

### 思路
快慢指针，快指针每次向前两次，慢指针每次向前一次。一个指针从相遇点出发，一个从链表头出发，每次前进一步，相遇点为环入口
```
class Solution {
   public:
    ListNode* EntryNodeOfLoop(ListNode* pHead) {
        ListNode *slow = pHead, *fast = pHead;
        if (pHead == nullptr || pHead->next == nullptr) {
            return nullptr;
        }
        do {
            fast = fast->next->next;
            slow = slow->next;
        } while (slow != fast);

        fast = pHead;
        while (slow != fast) {
            fast = fast->next;
            slow = slow->next;
        }
        return fast;
    }
};
```

## 56. 删除链表中重复的结点
> 在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。 例如，链表1->2->3->3->4->4->5 处理后为 1->2->5  

### 思路
```
class Solution {
   public:
    ListNode* deleteDuplication(ListNode* pHead) {
        if (pHead == nullptr || pHead->next == nullptr) {
            return pHead;
        }
        ListNode *cur = pHead, *nex = cur->next;
        if (cur->val == nex->val) {
            nex = nex->next;
            while (nex != nullptr && nex->val == cur->val) {
                nex = nex->next;
            }
            return deleteDuplication(nex);
        } else {
            pHead->next = deleteDuplication(pHead->next);
            return pHead;
        }
    }
};
```

## 57. 二叉树的下一个结点
> 给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。  

### 思路
```
class Solution {
   public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode) {
        if (pNode->right != nullptr) {
            return LeftMost(pNode);
        } else {
            if (pNode->next != nullptr) {
                TreeLinkNode* par = pNode->next;
                if (par->left == pNode) {
                    return par;
                } else {
                    TreeLinkNode* gp = par->next;
                    if (gp == nullptr) {
                        return nullptr;
                    } else {
                        if (gp->left == par) {
                            return gp;
                        } else {
                            return nullptr;
                        }
                    }
                }
            }
        }
        return nullptr;
    }

    TreeLinkNode* LeftMost(TreeLinkNode* pNode) {
        if (pNode->right == nullptr) {
            return nullptr;
        } else {
            TreeLinkNode* rs = pNode->right;
            while (rs->left) {
                rs = rs->left;
            }
            return rs;
        }
    }
};
```

## 58. 对称的二叉树
> 请实现一个函数，用来判断一颗二叉树是不是对称的。注意，如果一个二叉树同此二叉树的镜像是同样的，定义其为对称的。  

### 思路
首先根节点以及其左右子树，左子树的左子树和右子树的右子树相同
左子树的右子树和右子树的左子树相同即可，采用递归
非递归也可，采用栈或队列存取各级子树根节点
```
class Solution {
   public:
    bool isSymmetrical(TreeNode* pRoot) {
        if (pRoot == nullptr ||
            (pRoot->left == nullptr && pRoot->right == nullptr)) {
            return true;
        } else {
            return TreeCmp(pRoot->left, pRoot->right);
        }
    }

    bool TreeCmp(TreeNode* t1, TreeNode* t2) {
        if (t1 == nullptr && t2 == nullptr) {
            return true;
        } else if (t1 == nullptr || t2 == nullptr) {
            return false;
        } else {
            if (t1->val == t2->val) {
                return TreeCmp(t1->left, t2->right) &&
                       TreeCmp(t1->right, t2->left);
            } else {
                return false;
            }
        }
    }
};
```

## 59. 按之字形顺序打印二叉树
> 请实现一个函数按照之字形打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右至左的顺序打印，第三行按照从左到右的顺序打印，其他行以此类推。  

### 思路

```
class Solution {
   public:
    vector<vector<int>> Print(TreeNode* pRoot) {
        int layer = 1;
        stack<TreeNode*> s1, s2;
        if (pRoot == nullptr) {
            vector<vector<int>> v;
            return v;
        } else {
            s1.push(pRoot);
            vector<vector<int>> v;
            while (!s1.empty() || !s2.empty()) {
                if (layer % 2) {
                    vector<int> tmp;
                    while (!s1.empty()) {
                        TreeNode* node = s1.top();
                        tmp.push_back(node->val);
                        if (node->left != nullptr) {
                            s2.push(node->left);
                        }
                        if (node->right != nullptr) {
                            s2.push(node->right);
                        }
                        s1.pop();
                    }
                    v.push_back(tmp);
                    layer++;
                } else {
                    vector<int> tmp;
                    while (!s2.empty()) {
                        TreeNode* node = s2.top();
                        tmp.push_back(node->val);
                        if (node->right != nullptr) {
                            s1.push(node->right);
                        }
                        if (node->left != nullptr) {
                            s1.push(node->left);
                        }
                        s2.pop();
                    }
                    v.push_back(tmp);
                    layer++;
                }
            }
            return v;
        }
    }
};
```

## 60. 把二叉树打印成多行
>  从上到下按层打印二叉树，同一层结点从左至右输出。每一层输出一行。  

### 思路
层次遍历
```
class Solution {
   public:
    vector<vector<int>> Print(TreeNode* pRoot) {
        vector<vector<int>> vec;
        if (pRoot == NULL) return vec;

        queue<TreeNode*> q;
        q.push(pRoot);

        while (!q.empty()) {
            int lo = 0, hi = q.size();
            vector<int> c;
            while (lo++ < hi) {
                TreeNode* t = q.front();
                q.pop();
                c.push_back(t->val);
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
            vec.push_back(c);
        }
        return vec;
    }
};
```

## 61. 序列化二叉树
> 请实现两个函数，分别用来序列化和反序列化二叉树  

### 思路
#TODO
```
class Solution {
   public:
    char *Serialize(TreeNode *root) {
        if (root == NULL) return NULL;
        string str;
        Serialize(root, str);
        char *ret = new char[str.length() + 1];
        int i;
        for (i = 0; i < str.length(); i++) {
            ret[i] = str[i];
        }
        ret[i] = '\0';
        return ret;
    }
    void Serialize(TreeNode *root, string &str) {
        if (root == NULL) {
            str += '#';
            return;
        }
        string r = to_string(root->val);
        str += r;
        str += ',';
        Serialize(root->left, str);
        Serialize(root->right, str);
    }

    TreeNode *Deserialize(char *str) {
        if (str == NULL) return NULL;
        TreeNode *ret = Deserialize(&str);

        return ret;
    }
    TreeNode *Deserialize(char **str) {  //由于递归时，会不断的向后读取字符串
        if (**str == '#') {  //所以一定要用**str,
            ++(*str);  //以保证得到递归后指针str指向未被读取的字符
            return NULL;
        }
        int num = 0;
        while (**str != '\0' && **str != ',') {
            num = num * 10 + ((**str) - '0');
            ++(*str);
        }
        TreeNode *root = new TreeNode(num);
        if (**str == '\0')
            return root;
        else
            (*str)++;
        root->left = Deserialize(str);
        root->right = Deserialize(str);
        return root;
    }
};
```

## 62. 二叉搜索树的第K个节点
> 给定一棵二叉搜索树，请找出其中的第k小的结点。例如， （5，3，7，2，4，6，8）  中，按结点数值大小顺序第三小结点的值为4。  

### 思路
非递归中序遍历
```
class Solution {
   public:
    TreeNode KthNode(TreeNode root, int k) {
        if (root == null || k == 0) return null;
        Stack<TreeNode> stack = new Stack<TreeNode>();
        int count = 0;
        TreeNode node = root;
        do {
            if (node != null) {
                stack.push(node);
                node = node.left;
            } else {
                node = stack.pop();
                count++;
                if (count == k) return node;
                node = node.right;
            }
        } while (node != null || !stack.isEmpty());
        return null;
    }
};
```

## 63. 数据流中的中位数
> 如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。我们使用Insert()方法读取数据流，使用GetMedian()方法获取当前读取数据的中位数。  

### 思路
简单的办法是采取优先队列priority_queue，优先队列具有队列的所有特性，包括基本操作，只是在这基础上添加了内部的一个排序，它本质是一个堆实现的。把列表分成两半，分别用两个优先级队列来保存，左侧为数字越大优先级越高，右侧为数字越小优先级越高。那么取出两个优先级的top值即可。
```
class Solution {
   private:
    priority_queue<int, vector<int>, less<int> > p;
    priority_queue<int, vector<int>, greater<int> > q;

   public:
    void Insert(int num) {
        if (p.empty() || num <= p.top())
            p.push(num);
        else
            q.push(num);
        if (p.size() == q.size() + 2) q.push(p.top()), p.pop();
        if (p.size() + 1 == q.size()) p.push(q.top()), q.pop();
    }
    double GetMedian() {
        return p.size() == q.size() ? (p.top() + q.top()) / 2.0 : p.top();
    }
};
```

## 64. 滑动窗口的最大值
> 给定一个数组和滑动窗口的大小，找出所有滑动窗口里数值的最大值。例如，如果输入数组{2,3,4,2,6,2,5,1}及滑动窗口的大小3，那么一共存在6个滑动窗口，他们的最大值分别为{4,4,6,6,6,5}； 针对数组{2,3,4,2,6,2,5,1}的滑动窗口有以下6个： {[2,3,4],2,6,2,5,1}， {2,[3,4,2],6,2,5,1}， {2,3,[4,2,6],2,5,1}， {2,3,4,[2,6,2],5,1}， {2,3,4,2,[6,2,5],1}， {2,3,4,2,6,[2,5,1]}。  

### 思路
```
class Solution {
   public:
    vector<int> maxInWindows(const vector<int>& num, unsigned int size) {
        vector<int> res;
        deque<int> s;
        for (unsigned int i = 0; i < num.size(); ++i) {
            while (s.size() && num[s.back()] <= num[i])
                //从后面依次弹出队列中比当前num值小的元素，同时也能保证队列首元素为当前窗口最大值下标
                s.pop_back();
            while (s.size() && i - s.front() + 1 > size)
                //当当前窗口移出队首元素所在的位置，即队首元素坐标对应的num不在窗口中，需要弹出
                s.pop_front();
            s.push_back(i);  //把每次滑动的num下标加入队列
            if (size && i + 1 >= size)
                //当滑动窗口首地址i大于等于size时才开始写入窗口最大值
                res.push_back(num[s.front()]);
        }
        return res;
    }
};
```

## 65. 矩阵中的路径
> 请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一个格子开始，每一步可以在矩阵中向左，向右，向上，向下移动一个格子。如果一条路径经过了矩阵中的某一个格子，则之后不能再次进入这个格子。 例如 a b c e s f c s a d e e 这样的3 X 4 矩阵中包含一条字符串"bcced"的路径，但是矩阵中不包含"abcb"路径，因为字符串的第一个字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入该格子。  

### 思路
分析：回溯算法
这是一个可以用回朔法解决的典型题。首先，在矩阵中任选一个格子作为路径的起点。如果路径上的第i个字符不是ch，那么这个格子不可能处在路径上的
第i个位置。如果路径上的第i个字符正好是ch，那么往相邻的格子寻找路径上的第i+1个字符。除在矩阵边界上的格子之外，其他格子都有4个相邻的格子。
重复这个过程直到路径上的所有字符都在矩阵中找到相应的位置。 
由于回朔法的递归特性，路径可以被开成一个栈。当在矩阵中定位了路径中前n个字符的位置之后，在与第n个字符对应的格子的周围都没有找到第n+1个
字符，这个时候只要在路径上回到第n-1个字符，重新定位第n个字符。 
由于路径不能重复进入矩阵的格子，还需要定义和字符矩阵大小一样的布尔值矩阵，用来标识路径是否已经进入每个格子。 当矩阵中坐标为（row,col）的
格子和路径字符串中相应的字符一样时，从4个相邻的格子(row,col-1),(row-1,col),(row,col+1)以及(row+1,col)中去定位路径字符串中下一个字符
如果4个相邻的格子都没有匹配字符串中下一个的字符，表明当前路径字符串中字符在矩阵中的定位不正确，我们需要回到前一个，然后重新定位。 
一直重复这个过程，直到路径字符串上所有字符都在矩阵中找到合适的位置
```
class Solution {
   public:
    bool hasPath(char *matrix, int rows, int cols, char *str) {
        if (str == NULL || rows <= 0 || cols <= 0) return false;
        bool *isOk = new bool[rows * cols]();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                if (isHsaPath(matrix, rows, cols, str, isOk, i, j)) return true;
        }
        return false;
    }

    bool isHsaPath(char *matrix, int rows, int cols, char *str, bool *isOk,
                   int curx, int cury) {
        if (*str == '\0') return true;
        if (cury == cols) {
            curx++;
            cury = 0;
        }
        if (cury == -1) {
            curx--;
            cury = cols - 1;
        }
        if (curx < 0 || curx >= rows) return false;
        if (isOk[curx * cols + cury] || *str != matrix[curx * cols + cury])
            return false;
        isOk[curx * cols + cury] = true;
        bool sign =
            isHsaPath(matrix, rows, cols, str + 1, isOk, curx - 1, cury) ||
            isHsaPath(matrix, rows, cols, str + 1, isOk, curx + 1, cury) ||
            isHsaPath(matrix, rows, cols, str + 1, isOk, curx, cury - 1) ||
            isHsaPath(matrix, rows, cols, str + 1, isOk, curx, cury + 1);
        isOk[curx * cols + cury] = false;
        return sign;
    }
};
```

## 66. 机器人的运动范围
> 地上有一个m行和n列的方格。一个机器人从坐标0,0的格子开始移动，每一次只能向左，右，上，下四个方向移动一格，但是不能进入行坐标和列坐标的数位之和大于k的格子。 例如，当k为18时，机器人能够进入方格（35,37），因为3+5+3+7 = 18。但是，它不能进入方格（35,38），因为3+5+3+8 = 19。请问该机器人能够达到多少个格子？  

### 思路
DFS，搜索四个方向，vis记录该方格是否被搜索过，预判方格是否合法，合法就从该方格接着搜索
```
const int MAXN = 100;
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};  //四个方向
int vis[MAXN][MAXN] = {0};                       //记录数组
int sum;                                         //记录结果

class Solution {
   public:
    void dfs(int x, int y, int k, int m, int n) {
        vis[x][y] = 1;
        for (int i = 0; i <= 3; ++i) {
            int newx = x + dx[i], newy = y + dy[i];
            //预判方格是否合法，合法就从该方格接着搜索
            if (vis[newx][newy] == 0 && newx >= 0 && newx < m && newy >= 0 &&
                newy < n &&
                (newx % 10 + newx / 10 + newy % 10 + newy / 10 <= k)) {
                ++sum;
                dfs(newx, newy, k, m, n);
            }
        }
    }
    int movingCount(int k, int rows, int cols) {
        if (k < 0) return 0;
        memset(vis, 0, sizeof(vis));
        sum = 1;
        dfs(0, 0, k, rows, cols);
        return sum;
    }
};
```
