#include <ostream>
#include <iostream>
//using namespace std;


int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	int n, q;
	std::cin >> n;
	std::cin >> q;
	int **arr = new int *[n];
	int queries[q];
	std::cin.sync();
	for (int i = 0; i < n; i++) {
		int k;
		std::cin >> k;
		*(arr + i) = new int[k];
		for (int j = 0; j < k; j++)
			std::cin >> *(*(arr + i) + j);
		std::cin.sync();
	}
	int qprog = 0;
	while (q-- > 0) {
		int i, j;
		std::cin >> i;
		std::cin >> j;
		queries[qprog++] = *((*(arr + i)) + j);
		std::cin.sync();
	}
	for (int a : queries)
		std::cout << a << std::endl;
	for (int nums = 0; nums < n; nums++)
		delete [] *(arr + nums);
	delete [] arr;
	return 0;
}