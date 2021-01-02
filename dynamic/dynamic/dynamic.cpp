// dynamic.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <bits\stdc++.h>

using namespace std;
bool **dpbool;///////////////bool dynamic tabulation array
int **dpint;//////////////////int dynamic tabulation array
void printarr(int *arr, int n) {
	for (size_t i = 0; i < n; i++)
	{
		printf("%d: %d\n", i, arr[i]);
	}
}
int minvector(vector<int> &p) {
	int min = INT_MAX;
	for (auto pi:p)
	{
		min = min < pi ? min : pi;
	}
	return min;
}
void initialdpint(int i, int j) {
	dpint = new int*[i];
	for (size_t m = 0; m < i; m++)
	{
		dpint[m] = new int[j];
	}
	for (size_t l1 = 0; l1 < i; l1++)
	{
		for (size_t l2 = 0; l2 < j; l2++)
			dpint[l1][l2] = 0;
	}
	//return dpint;
}
/////////////////dijsktra/////////////////////////
int findmin(int *dist, bool* sptSet, int num) {
	int ret = 0;
	int min = INT_MAX;
	for (size_t i = 0; i < num; i++)
	{		
		if ((min > dist[i]) && sptSet[i] == false) {
			min = dist[i];
			ret = i;
		}
	}
	return ret;
}

int mindistdjs(int arr[9][9], int num) {
	bool *sptSet = new bool[num];
	int *dist = new int[num];
	for (size_t i = 0; i < num; i++)
	{
		sptSet[i] = false;
		dist[i] = INT_MAX;
	}

	dist[0] = 0;
	for (size_t count = 0; count < num-1; count++)
	{
		int u = findmin(dist, sptSet, num);
		for (size_t j = 0; (j < num); j++) {
			//printf("%d, %d\n", u, j);
			if ((arr[u][j] != 0) && (dist[u] != INT_MAX) && (dist[j] > arr[u][j] + dist[u]) && (sptSet[j] == false)) {
				
				dist[j] = arr[u][j] + dist[u];

			}
		}
		sptSet[u] = true;
	}
	printarr(dist, num);
	return dist[num - 1];
}
////////////////////////////////////////////////////////
//Given a set of non - negative integers, and a value sum, determine if there is a subset of the given set with sum equal to given sum.
//
//Example:
//
//Input: set[] = { 3, 34, 4, 12, 5, 2 }, sum = 9
//	Output : True
//	There is a subset(4, 5) with sum 9.
//
//	Input : set[] = { 3, 34, 4, 12, 5, 2 }, sum = 30
//	Output : False
//	There is no subset that add up to 30.
////////////////////////////////////////////////////////
//////////////memoization//////////////////////////////
//通过画二叉树进行递归的思路分析
bool isSubsetWithSum(int *arr, int n, int sum) {
	if (sum == 0)
	{
		return true;
	}
	if (n == 0)
	{
		return false;
	}
	if (arr[n-1] > sum)
	{
		return isSubsetWithSum(arr, n - 1, sum);
	}
	else
	{
		return isSubsetWithSum(arr, n - 1, sum - arr[n-1]) || isSubsetWithSum(arr, n - 1, sum);
	}
}
///////////tabulation///////////////////////////////////
//通过建立表格来实现遍历 
void isSubsetWithSum_tab(int *arr, int n, int sum) {//
	dpbool = new bool*[n];
	for (size_t i = 0; i < n; i++)
	{
		dpbool[i] = new bool[sum+1];
	}
	for (size_t i = 0; i <n; i++)
	{
		dpbool[i][0] = true;
	}
	if (arr[0] < sum)
		dpbool[0][arr[0]] = true;
	for (size_t i = 1; i < n; i++)
	{
		for (size_t j = 0; j < sum + 1; j++)
		{
			int num = arr[i];
			if (num < j) {
				dpbool[i][j] = dpbool[i][j - num];
			}
			else
			{
				dpbool[i][j] = dpbool[i - 1][j] || dpbool[i - 1][j - arr[i]];
			}

		}
	}
	//return dpbool[n - 1][sum];
}
////////////////////////////////////////////////////////
//Given an array of integers and a sum, the task is to print all subsets of given array with sum equal to given sum.
//
//Examples:
//
//Input: arr[] = { 2, 3, 5, 6, 8, 10 }
//	sum = 10
//	Output : 5 2 3
//	2 8
//	10
//
//	Input : arr[] = { 1, 2, 3, 4, 5 }
//	sum = 10
//	Output : 4 3 2 1
//	5 3 2
//	5 4 1
/////////////tabulation////////////////////////////////
vector<vector<int>> pall;
void display2vec(vector<vector<int>> pal) {
	for (auto vp : pal) {
		for (auto vi : vp) {
			printf("%5d", vi);
		}
		printf("\n");
	}
}
void display(vector<int> p) {
	for (auto vi : p) {
		printf("%5d", vi);
	}
	printf("\n");
}
void display2arr(bool** dp, int n1, int n2) {
	for (size_t i = 0; i < n1; i++)
	{
		for (size_t j = 0; j < n2; j++)
		{
			printf("%5d", dp[i][j]);
		}
		printf("\n");
	}
}
void subsetToVector(int *arr, int num, int n, vector<int> &p) {
	if (num < 0)
		return;
	printf("%d\n", n);
	if (num == 0 && n == 0) {
		display(p);
		//pall.push_back(p);
	}
	else if (n == 0 && dpbool[0][num]) {
		p.push_back(arr[0]);
		display(p);
		//pall.push_back(p);
	}
	if (n != 0 && dpbool[n-1][num]) {
		vector<int> bp = p;
		subsetToVector(arr, num, n - 1, bp);
	}
	if (n != 0 && num >= arr[n] && dpbool[n - 1][num - arr[n]]) {
		p.push_back(arr[n]);
		subsetToVector(arr, num - arr[n], n - 1, p);
	}
}

void isSubsetWithSumAll_tab(int *arr, int num, int n) {
	dpbool = new bool*[n];
	for (size_t i = 0; i < n; i++)
	{
		dpbool[i] = new bool[num + 1];
		for (size_t j = 0; j < num+1; j++)
		{
			dpbool[i][j] = false;
		}
	}
	for (size_t i = 0; i < n; i++)
	{
		dpbool[i][0] = true;
	}
	dpbool[0][arr[0]] = true;
	for (size_t i = 1; i < n; i++)
	{
		for (size_t j = 1; j < num+1; j++)
		{
			dpbool[i][j] = (j >= arr[i]) ? dpbool[i - 1][j] || dpbool[i - 1][j - arr[i]] : dpbool[i-1][j];
		}
	}
	if (!dpbool[n-1][num])
	{
		printf("Sum can't divided to subsets\n");
		return;
	}
	else
	{
		printf("subsets\n");
	}
	display2arr(dpbool, n, num+1);
	vector<int> p;
	subsetToVector(arr, num, n, p);
}

void isSubsetWithSumAll_mem(int *arr, int num, int n, vector<int> &p) {//num=sum
	if (num == 0) {
		display(p);
		pall.push_back(p);
	}
	else if(num > 0)
	{
		if (n == 0) {
			if (arr[0] == num)
			{
				p.push_back(arr[0]);
				display(p);
				pall.push_back(p);
			}
		}
		else
		{
			vector<int> bp = p;
			isSubsetWithSumAll_mem(arr, num, n - 1, bp);
			p.push_back(arr[n]);
			isSubsetWithSumAll_mem(arr, num - arr[n], n - 1, p);
		}
	}
}
//////////////////////nCr/////////////////////////////////////排列组合非数学方式
//void nCr_tab(int p, int r, vector<int> &pvec) {
//	dpint = new int*[p];
//	for (size_t i = 0; i < p; i++)
//	{
//		dpint[i] = new int[r];
//	}
//
//}
////////////////////find all paths////////////////////////////给定一个无权图，判断从起始点到终点共有几条长度为k的路径
/////////////////mem//////////////////////////////////////////
int countwalks(int arr[4][4], int i, int j, int k) {
	if (k == 0) {
		if (i == j) {
			return 1;
		}
		return 0;
	}
	int resnum = 0;
	for (size_t m = 0; m < 4; m++)
	{
		if (arr[i][m] == 1) {
			resnum += countwalks(arr, m, j, k - 1);
		}
	}
	return resnum;
}
/////////////////////////////tab//////////////////////////
int countwalks_tab(int arr[4][4], int u, int v, int k) {
	int ***nums = new int**[k-1];
	for (size_t i = 0; i < k-1; i++)
	{
		nums[i] = new int*[4];
		for (size_t j = 0; j < 4; j++)
		{
			nums[i][j] = new int[4];
			
		}
	}
	cout << "success" << endl;
	for (size_t i = 0; i < k-1; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			for (size_t m = 0; m < 4; m++) {
				nums[i][j][m] = 0;
				if (i == 0)
				{
					for (size_t nn = 0; nn < 4; nn++)
					{
						if (arr[j][nn] == 1)
							nums[i][j][m] += arr[nn][m];
					}
					
				}
				else
				{
					for (size_t nn = 0; nn < 4; nn++)
					{
						if (nums[i-1][j][nn] == 1)
							nums[i][j][m] += nums[i-1][nn][m];
					}
				}
				
			}
		}
	}
	return nums[k - 2][u][v];
}
///////////////////////////////////////////////////Maximum sum path in a matrix from top to bottom
//////////////////////////////////////////////////顺着矩阵往下走，左下或者右下，取最长路径
///////////////tab////////////////////////////////
int maxSum(int mat[4][4], int n) {
	int max = 0;
	dpint = new int*[4];
	for (size_t i = 0; i < 4; i++)
	{
		dpint[i] = new int[4];

	}
	for (int i = 3; i >= 0; i--)
	{
		for (size_t j = 0; j < 4; j++)
		{
			dpint[i][j] = mat[i][j];

			if(i < 3)
			{
				if (j == 0)
				{
					dpint[i][j] += dpint[i + 1][j + 1];
				}
				else if (j == 3)
				{
					dpint[i][j] += dpint[i + 1][j - 1];
				}
				else
				{
					dpint[i][j] += dpint[i + 1][j - 1] > dpint[i + 1][j + 1] ? dpint[i + 1][j - 1] : dpint[i + 1][j + 1];
				}
			}
		}
		//cout << i << endl;
	}
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			cout << dpint[i][j] << "  ";
		}
		cout << endl;
	}
	max = 0;
	for (size_t i = 0; i < 4; i++)
	{

		max = max > dpint[0][i] ? max : dpint[0][i];
	}
	return max;
}
////////////////////////////////////////////Maximum sum subarray removing at most one element
int maxSumSubarrayRemovingOneEle(int arr[], int n) {
	int left = 0;
	int right = 0;
	int sum = 0;
	int max = 0;
	int min = 0;
	int premax = 0;
	for (size_t i = 0; i < n; i++)
	{
		sum += arr[i];
		if (sum < 0) {
			left++;
			sum = 0;
		}
		else
		{
			max = max > sum ? max : sum;
			if (max == sum)
			{
				
				right = i;
				//premax = max;
			}
		}
	}
	printf("left is %d, right is %d\n", left, right);
	for (size_t i = left; i <= right; i++)
	{
		min = min < arr[i] ? min : arr[i];
	}
	
	return max - min;
}
//////////////////////////////////////////////////////palindrome partion判断切割几次可以全部分为回文串
int minPalPartion(string s) {
	int n = s.length();
	dpbool = new bool*[n];
	for (size_t i = 0; i < n; i++)
	{
		dpbool[i] = new bool[n];
		dpbool[i][i] = true;
	}
	dpint = new int*[n];
	for (size_t i = 0; i < n; i++)
	{
		dpint[i] = new int[n];
		dpint[i][i] = 0;
	}
	for (size_t L = 1; L < n; L++)
	{
		for (size_t i = 0; i < n - L; i++)
		{
			int j = i + L;
			if (L == 1)
			{
				dpbool[i][j] = s[i] == s[j];
			}
			else
			{
				dpbool[i][j] = (s[i] == s[j]) && (dpbool[i + 1][j - 1]);
			}
			if (dpbool[i][j])
			{
				dpint[i][j] = 0;
			}
			else
			{
				vector<int> pint;
				dpint[i][j] = INT_MAX;
				for (size_t k = i; k < j; k++)
				{
					dpint[i][j] = min(dpint[i][j], dpint[i][k] + dpint[k + 1][j] + 1);
				}
			}
		}
	}
	return dpint[0][n - 1];
}
/////////判断按九宫格键盘数字，按n次能按出几种情况
/////////////////////////////mem/////////////////////////
int getCountUtil(char table[4][3], int row, int col, int n) {
	int rows[5] = { 0, 1, 0, -1, 0 };
	int cols[5] = { 1, 0, -1, 0, 0 };
	int count = 0;
	if (n == 1)
	{
		return 1;
	}
	else
	{

		for (size_t i = 0; i < 5; i++)
		{
			int ro = row + rows[i];
			int co = col + cols[i];
			if (ro > -1 && ro < 4 && co > -1 && co < 3 && table[ro][co] != '*' && table[ro][co] != '#') {
				count += getCountUtil(table, ro, co, n - 1);
			}
		}

	}
	return count;
}
int getCount(char table[4][3], int n) {
	int totalCount = 0;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (table[i][j] != '*' && table[i][j] != '#') {
				totalCount += getCountUtil(table, i, j, n);
			}
		}
	}
	return totalCount;
}
//////////////////////////tab///////////////////////////
int getCount_tab(char table[4][3], int n) {
	initialdpint(n, 10);
	int rows[5] = { 0, 1, 0, -1, 0 };
	int cols[5] = { 1, 0, -1, 0, 0 };
	for (size_t i = 0; i < 10; i++)
	{
		dpint[0][i] = 1;
	}
	int ro, co;
	for (size_t mov = 1; mov < n; mov++)
	{
		for (size_t i = 0; i < 4; i++) {
			for (size_t j = 0; j < 3; j++) {
				
				if (table[i][j] != '#' && table[i][j] != '*')
				{
					//dpint[mov][table[i][j] - '0'] = 0;
					for (size_t k = 0; k < 5; k++)
					{
						ro = rows[k] + i;
						co = cols[k] + j;
						if (ro > -1 && ro < 4 && co > -1 && co < 3 && table[ro][co] != '#' && table[ro][co] != '*')
						{
							
							dpint[mov][table[i][j] - '0'] += dpint[mov-1][table[ro][co] - '0'];
						}
					}
				}
			}
		}
	}
	int totalcount = 0;
	for (size_t i = 0; i < 10; i++)
	{
		totalcount += dpint[n - 1][i];
	}
	return totalcount;
}
//////////////////////Matrix Chain Multiplication多个矩阵相乘最小的计算量
///////////////////////////mem////////////////////////////
int MatrixChainOrder(int p[], int i, int j) {
	if (i == j)
	{
		return 0;
	}
	int k = i;
	int min = INT_MAX;
	for (; k < j; k++)
	{
		int count = MatrixChainOrder(p, i, k) + MatrixChainOrder(p, k + 1, j) + p[i] * p[k+1] * p[j+1];
		min = min < count ? min : count;
	}
	return min;
}
///////////////////////////////tab///////////////////////
int MatrixChainOrder_tab(int p[], int n) {
	dpint = new int*[n-1];
	for (size_t i = 0; i < n-1; i++)
	{
		dpint[i] = new int[n-1];
		for (size_t j = 0; j < n-1; j++)
		{
			dpint[i][j] = 0;
		}
	}
	for (int i = n-3;i >= 0;i--)
	{

		for (size_t j = i+1; j < n-1; j++)
		{
			dpint[i][j] += min(dpint[i][j - 1] + p[i] * p[j] * p[j+1], dpint[i + 1][j] + p[i] * p[i + 1] * p[j+1]);
		}
	}
	return dpint[0][n - 2];
}
/////////////////////////////////////////////////最长子序列
///////////////////mem//////////////////////////
int lis(int arrs[], int n) {
	if (n == 1)
		return 1;
	int max_here, res;
	max_here = 1;
	for (size_t i = 1; i < n; i++)
	{
		res = lis(arrs, i);
		if (arrs[n - 1] > arrs[i - 1] && res > max_here - 1)
			max_here = res + 1;
	}
	return max_here;
}
//////////////////////////tab////////////////////
int lis2(int arrs[], int n) {
	if (n == 1)
	{
		return 1;
	}
	int *arrlis = (int*)malloc(sizeof(int) * n);
	arrlis[0] = 1;
	for (size_t i = 1; i < n; i++)
	{
		arrlis[i] = 1;
		for (int j = 0; j < i; j++) {
			if (arrs[i] > arrs[j] && arrlis[j] > arrlis[i] - 1) {
				arrlis[i] = arrlis[j] + 1;
			}
		}

	}
	int max = 0;
	for (int i = 0; i < n; i++)
		max = max > arrlis[i] ? max : arrlis[i];
	return max;
}
/////////////////////knapsack problem背包问题
//////////////////mem///////////////////////
int knapsack(int weight[], int value[], int w, int n) {
	if (w < 0) {
		return -value[n+1];
	}
	if (n < 0)
		return 0;
	return max(knapsack(weight, value, w, n - 1), value[n] + knapsack(weight, value, w - weight[n], n - 1));
}
////////////////////tab///////////////////////////
int knapsack_tab(int weight[], int value[], int w, int n) {
	initialdpint(n, w+1);
	for (size_t i = 0; i < n; i++)
	{
		if (i == 0) {
			for (size_t j = 0; j <= w; j++)
			{
				dpint[i][j] = j > weight[0] ? value[0] : 0;
			}
		}
		else
		{
			for (size_t j = 0; j <= w; j++)
			{
				if (j >= weight[i])
					dpint[i][j] = max(dpint[i - 1][j], value[i] + dpint[i - 1][j - weight[i]]);
				else
				{
					dpint[i][j] = dpint[i - 1][j];
				}
			}
		}

	}
	return dpint[n - 1][w];
}
////////////////////////////////////////k个次数内买卖股票
////////////////////////tab/////////////////////////////
int sellShares(int arrs[], int n, int k) {
	initialdpint(k + 1, n);
	for (size_t i = 0; i < n; i++)
	{
		dpint[0][i] = 0;
	}
	for (size_t i = 1; i <= k; i++)
	{
		int prevbuy = -arrs[0];
		for (size_t j = 1; j < n; j++)
		{
			prevbuy = max(dpint[i - 1][j - 1] - arrs[j - 1], prevbuy);
			dpint[i][j] = max(dpint[i][j - 1], prevbuy + arrs[j]);
		}
	}
	return dpint[k][n-1];
}
void addarrs(int arr[2]) {
	arr[0]++;
	arr[1] = 10;
}
void addptr(int *a) {
	*a += 1;
}
void zerosandones(string str, int arr[2]) {
	arr[0] = 0;
	arr[1] = 0;
	for (auto c : str) {
		arr[c - '0']++;
	}
}
int main()
{
///////////////////dijsktra///////////////////////////
	//int graph[9][9] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
	//{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
	//{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
	//{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
	//{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },
	//{ 0, 0, 4, 14, 10, 0, 2, 0, 0 },
	//{ 0, 0, 0, 0, 0, 2, 0, 1, 6 },
	//{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
	//{ 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
	//int n = mindistdjs(graph, 9);
///////////////////////////////////////////////////////
///////////////////subset////////////////////////////判断是否有相加和为sum
	//int set[] = { 3, 34, 4, 12, 5, 2 };
	//int sum = 9;
	//int n = sizeof(set) / sizeof(set[0]);
	//if (isSubsetWithSum_tab(set, n, sum) == true)
	//	printf("Found a subset with given sum");
	//else
	//	printf("No subset with given sum");
////////////////////////////////////////////////////////
//////////////////subset////////////////////////////////列出全部的相加何为sum
	//int arr[] = { 1, 2, 3, 4, 5, 4 };
	//int n = sizeof(arr) / sizeof(arr[0]);
	//int sum = 10;
	////isSubsetWithSumAll_tab(arr, sum, n);
	//vector<int> p;
	//isSubsetWithSumAll_mem(arr, sum, n, p);
	//printf("success\n");
	//display2vec(pall);
////////////////////////////////////////////////////////
//////////////////////////nCr///////////////////////////

/////////////////////////find all paths////////////////
	//int graph[4][4] = { { 0, 1, 1, 1 },
	//{ 0, 0, 0, 1 },
	//{ 0, 0, 0, 1 },
	//{ 0, 0, 0, 0 } };
	//int u = 0, v = 3, k = 2;
	//cout << countwalks_tab(graph, u, v, k);
////Maximum sum path in a matrix from top to bottom
	//int mat[4][4] = { { 5, 6, 1, 7 },
	//{ -2, 10, 8, -1 },
	//{ 3, -7, -9, 11 },
	//{ 12, -4, 2, 6 } };
	//int n = 4;

	//cout << "Maximum Sum = "
	//	<< maxSum(mat, n);
////Maximum sum subarray removing at most one element
	//int arr[] = { -2, -3, 4, -1, -2, 1, 5, -3 };
	//int n = sizeof(arr) / sizeof(arr[0]);
	//cout << maxSumSubarrayRemovingOneEle(arr, n);
/////////palindrom partition
	//string str = "geek";
	//cout << "Min cuts needed for Palindrome"
	//	" Partitioning is "
	//	<< minPalPartion(str);
	//string s1 = "asd", s2 = "dsadsa";
	//string stmp;
	//cout << s1 + s2 << endl;
	//cout << s1 + stmp << endl;
/////////////////判断按九宫格键盘数字，按n次能按出几种情况
	//char keypad[4][3] = { { '1','2','3' },
	//{ '4','5','6' },
	//{ '7','8','9' },
	//{ '*','0','#' } };
	//printf("Count for numbers of length %d: %d\n", 1, getCount_tab(keypad, 1));
	//printf("Count for numbers of length %d: %d\n", 2, getCount_tab(keypad, 2));
	//printf("Count for numbers of length %d: %d\n", 3, getCount_tab(keypad, 3));
	//printf("Count for numbers of length %d: %d\n", 4, getCount_tab(keypad, 4));
	//printf("Count for numbers of length %d: %d\n", 5, getCount_tab(keypad, 5));
////////////////matrix multiply chain
	//int arr[] = { 10, 20, 30, 40, 30 };
	//int n = sizeof(arr) / sizeof(arr[0]);
	//cout << "Minimum number of multiplications is "
	//	<< MatrixChainOrder_tab(arr, n);
	////cout << "Minimum number of multiplications is "
	////	<< MatrixChainOrder(arr, 0, n - 2);
	////string s1 = "10001";
	////for (auto c:s1)
	////{
	////	if (c == '0')
	////	{
	////		cout << 1 << endl;
	////	}
	////}
/////////////////lis
	//int arr[] = { 1,3,6,7,9,4,10,5,6 };
	//int n = sizeof(arr) / sizeof(arr[0]);
	//printf("Length of lis is %d\n",
	//	lis2(arr, n));
////////////////knapsack
	//int val[] = { 60, 100, 120 };
	//int wt[] = { 10, 20, 30 };
	//int W = 50;
	//int n = sizeof(val) / sizeof(val[0]);
	///*cout << knapsack(wt, val, W, n-1);*/
	//cout << knapsack_tab(wt, val, W, n) << endl;
	////
	//int cc = 5;
	//cout << (int *)*(&cc) << endl;
////////////////////shares
	int arrs[] = { 3,4,5,4,5,7,1,8 };
	cout << sellShares(arrs, 8, 2) << endl;

	//string ss = "0123321";
	//////ss.erase(ss.begin()+2);
	//cout << ss.size() << endl;
	//char ssin[10];
	//_itoa(atoi(&ss[0]),ssin, 10);
	//cout << ssin << endl;
	//string ss2 = "1";
	//ss2.erase(ss2.begin());
	//cout << ss2.size() << endl;
	////string strs[2];
	////strs[0] = "321";
	////strs[1] = ss;
	////cout << strs[1] << strs[0] << endl;
	//
	//time_t start = time(NULL);
	//int a = 99;
	//int c;
	//
	//time_t stop = time(NULL);
	//cout << stop - start << endl;
    return 0;
}

