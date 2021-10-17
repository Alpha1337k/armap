#include "Armap.hpp"
#include <map>
#include <chrono>

#ifdef MINE
#define CON Armap
#else
#define CON std::map
#endif

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096


#define COUNT 5000 //000

int main(int argc, char **argv)
{
    if (argc != 2)
        return 0;
    const int seed = atoi(argv[1]);
    CON<int, int> data;
	srand(seed);

	for (int i = 0; i < COUNT; ++i)
	{
        data[rand() % COUNT] = rand() % COUNT;
	}

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	long sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand() % COUNT;
		sum += data[access];
	}

    for (size_t i = 0; i < 1000; i++)
    {
        long s = 0;
        for (int i = 0; i < 40000; i++)
        {
            int access = rand() % COUNT;
            s += data[access];
        }
    }
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    
    std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  
    size_t x = 0;
    for (CON<int, int>::iterator i = data.begin(); i != data.end() ;i++)
    {
        std::cout << x << " --k: " << i->first << " v: " << i->second << std::endl;
        x++;
    }
    std::cout << duration.count() << "us" << std::endl;
    std::cout << data.size() << std::endl;
    std::cout << "should be constant with the same seed: " << sum << std::endl;
}