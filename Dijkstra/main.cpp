#include <iostream>
#include <fstream>
#include <stdexcept>
#include <exception>
#include <vector>

using namespace std;

class NoRout : public runtime_error
{
public:
	NoRout(string s)
		: runtime_error(s)
	{
	}
};


double findDijkstra(double** arr, int N, vector<bool>& marked, vector<double>& currPath, int start, int finish, int& curr)
{
	marked[curr - 1] = true;

	if (curr == finish)
	{
		return currPath[curr - 1];
	}
	else
	{
		for (size_t i = 0; i < N; ++i)
		{
			if (marked[i] != true)
			{
				if (arr[curr - 1][i] != UINT_MAX && arr[curr - 1][i] + currPath[curr - 1] < currPath[i])
				{
					currPath[i] = arr[curr - 1][i] + currPath[curr - 1];
				}
			}
		}

		bool isPath = false;

		for (size_t i = 0; i < N; ++i)
		{
			if (marked[i] != true && currPath[i] != UINT_MAX)
			{
				isPath = true;
				break;
			}
		}

		if (!isPath)
		{
			throw NoRout("there is no rout to the given vertex");
		}
		else
		{
			double min = UINT_MAX;
			int minNum = 0;

			for (size_t i = 0; i < N; ++i)
			{
				if (marked[i] != true && currPath[i] < min)
				{

					minNum = i;
					min = currPath[i];
				}
			}

				curr = minNum + 1;
				return findDijkstra(arr, N, marked, currPath, start, finish, curr);
		}
	}
}
 
bool test1()
{
	ifstream in("Graph1.txt");

	int N;
	in >> N;

	double** arr = new double*[N];

	bool passed = false;

	for (size_t i = 0; i < N; ++i)
	{
		arr[i] = new double[N];
	}

	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < N; ++j)
		{
			if (i == j)
			{
				arr[i][j] = 0;
			}
			else
			{
				arr[i][j] = UINT_MAX;
			}
		}
	}

	try
	{
		int vert1, vert2, len;

		while (in >> vert1 >> vert2 >> len)
		{
			arr[vert1 - 1][vert2 - 1] = len;
			arr[vert2 - 1][vert1 - 1] = len;
		}

		for (size_t i = 0; i < N; ++i)
		{
			for (size_t j = 0; j < N; ++j)
			{
				if (arr[i][j] < 0)
				{
					throw out_of_range("wrong distance between vertices");
				}
			}
		}

			int start = 1;
			int finish = 6;

			vector<bool> marked(N);
			vector<double> currPaths(N);

			for (size_t i = 0; i < N; ++i)
			{
				marked[i] = false;
				currPaths[i] = UINT_MAX;
			}

			currPaths[start - 1] = 0;

			int curr = start;

			passed = (findDijkstra(arr, N, marked, currPaths, start, finish, curr) == 13 ? true : false);
		}

	catch (exception& e)
	{
		cout << "Exception: " << e.what() << endl;
	}

	for (size_t i = 0; i < N; ++i) delete[] arr[i];
	delete[] arr;

	return passed;
}

bool test2()
{
	ifstream in("Graph2.txt");

	int N;
	in >> N;

	double** arr = new double*[N];

	bool passed = false;

	for (size_t i = 0; i < N; ++i)
	{
		arr[i] = new double[N];
	}

	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < N; ++j)
		{
			if (i == j)
			{
				arr[i][j] = 0;
			}
			else
			{
				arr[i][j] = UINT_MAX;
			}
		}
	}

	try
	{
		int vert1, vert2, len;

		while (in >> vert1 >> vert2 >> len)
		{
			arr[vert1 - 1][vert2 - 1] = len;
			arr[vert2 - 1][vert1 - 1] = len;
		}

		for (size_t i = 0; i < N; ++i)
		{
			for (size_t j = 0; j < N; ++j)
			{
				if (arr[i][j] < 0)
				{
					throw out_of_range("wrong distance between vertices");
				}
			}
		}

		int start = 1;
		int finish = 8;

		vector<bool> marked(N);
		vector<double> currPaths(N);

		for (size_t i = 0; i < N; ++i)
		{
			marked[i] = false;
			currPaths[i] = UINT_MAX;
		}

		currPaths[start - 1] = 0;

		int curr = start;

		passed = (findDijkstra(arr, N, marked, currPaths, start, finish, curr) == 14 ? true : false);
	}

	catch (exception& e)
	{
		cout << "Exception: " << e.what() << endl;
	}

	for (size_t i = 0; i < N; ++i) delete[] arr[i];
	delete[] arr;

	return passed;
}

int main()
{
	if (!test1())
	{
		cout << "Test 1 failed" << endl;
	}

	if (!test2())
	{
		cout << "Test 2 failed" << endl;
	}

	system("pause");
	return 0;
}