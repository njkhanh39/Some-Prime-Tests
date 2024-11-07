#include <iostream>
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <chrono>
#include <time.h>
#include <algorithm>
#include <vector>

using namespace std;
using u64 = uint64_t;
using u128 = __uint128_t;

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(u64 n, int iter = 5) { // returns true if n is probably prime, else returns false.
    if (n < 4)
        return n == 2 || n == 3;

    int s = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    for (int i = 0; i < iter; i++) {
        u64 a = 2 + rand() % (n - 3);
        if (check_composite(n, a, d, s))
            return false;
    }
    return true;
}

bool probablyPrimeFermat(u64 n, int iter=5) {
    if (n < 4)
        return n == 2 || n == 3;

    for (int i = 0; i < iter; i++) {
        u64 a = 2 + rand() % (n - 3);
        if (binpower(a, n - 1, n) != 1)
            return false;
    }
    return true;
}

bool isPrime(u128 x) {
    for (u128 d = 2; d * d <= x; d++) {
        if (x % d == 0)
            return false;
    }
    return x >= 2;
}

void testTrialDiv(u128 num, int length){
    cout << "Trial Division Testing: \n";
     auto t_start = std::chrono::high_resolution_clock::now();

   for(u128 x = num; x<=num+length; ++x){
        cout << isPrime(x);
   }
   cout << '\n';

    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();

    cout << "Time elapsed: " << elapsed_time_ms << " milliseconds" << '\n';
}

void testMiller(u128 num, int length){
    cout << "Miller Testing: \n";
     auto t_start = std::chrono::high_resolution_clock::now();
    int i = 1, cnt = 0;
   for(u128 x = num; x<=num+length; ++x){
        if(MillerRabin(x)){ cout << i <<' ';
            ++cnt;
        }
        ++i;
   }
   cout << '\n';
   cout << "Miller found " << cnt << " primes!\n";
    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();

    cout << "Time elapsed: " << elapsed_time_ms << " milliseconds" << '\n';
}

void testFermat(u128 num, int length){
    cout << "Fermat Testing: \n";
    auto t_start = std::chrono::high_resolution_clock::now();

int i = 1, cnt = 0;
   for(u128 x = num; x<=num+length; ++x){
        if(probablyPrimeFermat(x)){ cout << i << ' ';
        ++cnt;
        }
        ++i;
   }
   cout << '\n';
   cout << "Fermat found " << cnt << " primes!\n";
    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();

    cout << "Time elapsed: " << elapsed_time_ms << " milliseconds" << '\n';
}

int main()
{
     vector<u128> vals = {1027498106806225441, 7050810642549651091,
6155568815813781257, 2912970412537579783, 8348960580061273493, 2407823242081768633,
1383602730909524507, 7116242705310218687, 8042869108487301239, 9015127525509429017};
    
    sort(vals.begin(), vals.end());

    
    for(int i=0; i<10; ++i){
        int range = 1000;
        if(i==9) range = 10000;
        cout << "Batch " << i << ": \n";
        testFermat(vals[i], range);
        testMiller(vals[i], range);
    }
    
    return 0;
}