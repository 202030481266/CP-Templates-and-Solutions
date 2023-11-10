#include <iostream>
#include <bitset>

using namespace std;

string toBinary(long long n)
{
    string r;
    while (n != 0){
        r += ( n % 2 == 0 ? "0" : "1" );
        n /= 2;
    }
    return r;
}

int main() {
    long long number;

    cin >> number;

    cout << bs << endl;

    return EXIT_SUCCESS;
}