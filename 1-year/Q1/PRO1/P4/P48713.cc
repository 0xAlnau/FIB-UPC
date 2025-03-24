#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		cout << a;

		bool is_prime = true;
		int j = 2;
		while (is_prime and j * j <= a) {
			if (a % j == 0) is_prime = false;
			++j;
		}

		if (a > 1 and is_prime) cout << " is prime";
		else cout << " is not prime";
		cout << endl;
	}
}
