#include <iostream>
#include <cmath>
#include <iomanip> 
#include <cstring>
using namespace std;

int main()
{
	int arr[21][21] = {0}, n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		arr[i][1] = 1;
	}
	for (int x = 2; x <= n; x++)
	{
		for (int y = 2; y <= n; y++)
		{
			arr[x][y] = arr[x - 1][y - 1] + arr[x - 1][y];
		}
	}
	for (int a = 1; a <= n; a++)
	{
		for (int b = 1; b <= a; b++)
		{
			cout << arr[a][b]<<' ';
		}
		cout << endl;
	}
	return 0;
}