#include <iostream>
#include <string>
#include <chrono>
#include <cmath>
#include "cache.h"

using namespace std;

int main()
{
    int min_kb, max_kb;
    string travel;
    cout << "Enter min and max sizes of cache (in KB): ";
    cin >> min_kb >> max_kb;
    Cache cache(min_kb, max_kb);
    int directSize, reversesize, randomSize;
    Cache::Experiment *direct = cache.MakeTest("direct", directSize);
    Cache::Experiment *reverse = cache.MakeTest("reverse", reversesize);
    Cache::Experiment *random = cache.MakeTest( "random", randomSize);
}
