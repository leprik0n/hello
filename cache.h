#include <iostream>
#include <string>
#include <chrono>
#include <cmath>

using namespace std;

class Cache
        {
                const int LOOPS = 1000;
                unsigned int *buffer;
                int *buf_sizes;
                int size;
                int KBtoSize(int kb);
                void initbuffer(int n);
                void directTest(int n);
                void reverseTest(int n);
                void randomTest(int n);
                public:
                struct Experiment
                {
                    int id;
                    string name;
                    double time;
                };
                Cache(int min_kb, int max_kb);
                Experiment* MakeTest(string travel, int& experimentsSize);
        };

int Cache::KBtoSize(int kb)
{
    return kb * 1024 / sizeof(int);
}

void Cache::initbuffer(int n)
{
    if (buffer != nullptr)
        delete[] buffer;
    buffer = new unsigned int[n];
    for (unsigned int i = 0; i < n; i++)
        buffer[i] = rand() % n;
}

void Cache::directTest(int n)
{
    for (unsigned int loop = 0; loop < LOOPS; loop++)
    {
        for (unsigned int i = 0; i < n; i++)
            int v = buffer[i];
    }
}

void Cache::reverseTest(int n)
{
    for (unsigned int loop = 0; loop < LOOPS; loop++)
    {
        for (int i = n - 1; i >= 0; i--)
            int v = buffer[i];
    }
}

void Cache::randomTest(int n)
{
    for (unsigned int loop = 0; loop < LOOPS; loop++)
    {
        for (int i = 0; i < n; i++)
            int v = buffer[rand() % n];
    }
}

Cache::Experiment* Cache::MakeTest(string travel, int &experimentsSize)
{
    cout << "investigation:" << endl;
    cout << "   travel variant: " << travel << endl;
    cout << "   experiments:" << endl;
    experimentsSize = size;
    Experiment *experiments = new Experiment[size + 1];
    for (int i = 0; i < size; i++)
    {
        int n = KBtoSize(buf_sizes[i]);
        initbuffer(n);
        for (int j = 0; j < n; j++)
            int a = buffer[rand() % n];
        auto start = chrono::high_resolution_clock::now();
        if (travel == "direct") {
            directTest(n);
        }
        else if (travel == "reverse") {
            reverseTest(n);
        }
        else {
            randomTest(n);
        }
        auto finish = std::chrono::high_resolution_clock::now();
        experiments[i].id = i + 1;
        experiments[i].name = travel;
        experiments[i].time = (chrono::duration_cast<chrono::nanoseconds>(finish - start).count() / LOOPS);
        cout << "   - experiment:" << endl;
        cout << "       number: " << (i + 1) << endl;
        cout << "       input data:" << endl;
        cout << "         buffer size: " << buf_sizes[i] << "KB" << endl;
        cout << "       results:" << endl;
        cout << "         duration: " << (chrono::duration_cast<chrono::nanoseconds>(finish - start).count() / LOOPS) << "ns" << endl;
    }
    cout << endl;
    return experiments;
}

Cache::Cache(int min_kb, int max_kb)
{
    size = log2(max_kb / min_kb) + 3;
    buf_sizes = new int[size];
    int n = 0;
    min_kb /= 2;
    while (min_kb <= max_kb * 3 / 2)
    {
        buf_sizes[n++] = min_kb;
        min_kb *= 2;
    }
    buf_sizes[n++] = max_kb * 3 / 2;
    buffer = nullptr;
    cout << endl << "Buffer sizes: ";
    for (unsigned int i = 0; i < n; i++)
        cout << buf_sizes[i] << " ";
    cout << endl;
}

