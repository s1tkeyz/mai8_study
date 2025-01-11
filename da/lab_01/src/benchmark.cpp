#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>

using TByte = uint8_t;
using duration_t = std::chrono::milliseconds;

const std::string DURATION_PREFIX = "ms";
const uint8_t DEC_DIGITS_AMOUNT = 10U;
const uint32_t ARRAY_SIZE = 1000000U;
const uint8_t MAX_BYTE_RADIX = 3U;
const uint8_t BYTE_MAX = 255U;

uint8_t GetRadix(TByte key, uint8_t idx) {
    if(idx == 0) {
        return key % 10;
    }
    if(idx == 1) {
        return (key / 10) % 10;
    }
    else {
        return key / 100;
    }
}

void RadixSort(std::vector<TByte>& array) {
    std::vector<TByte> aux(array.size());

    for(uint8_t rnd = 0U; rnd < MAX_BYTE_RADIX; ++rnd) {
        uint32_t counter[DEC_DIGITS_AMOUNT] = {0U};
        uint32_t j;
        for(j = 0U; j < array.size(); ++j) {
            uint8_t radix = GetRadix(array[j], rnd);
            counter[radix]++;
        }
        for(j = 1U; j < DEC_DIGITS_AMOUNT; ++j) {
            counter[j] += counter[j - 1U];
        }
        for(j = array.size(); j > 0U; --j) {
            uint8_t rdx = GetRadix(array[j - 1U], rnd);
            aux[counter[rdx] - 1U] = array[j - 1U];
            counter[rdx]--;
        }
        aux.swap(array);
    }
}

int main(void) {
    std::srand(std::time(nullptr));

    std::vector<TByte> arr1(ARRAY_SIZE);
    std::vector<TByte> arr2(ARRAY_SIZE);

    for(size_t i = 0; i < ARRAY_SIZE; ++i) {
        TByte r = std::rand() % BYTE_MAX;
        arr1[i] = r;
        arr2[i] = r;
    }

    auto start_ts = std::chrono::system_clock::now();
    RadixSort(arr1);
    auto end_ts = std::chrono::system_clock::now();
    uint64_t radix_ts = std::chrono::duration_cast<duration_t>( end_ts - start_ts ).count();

    start_ts = std::chrono::system_clock::now();
    std::stable_sort(arr2.begin(), arr2.end());
    end_ts = std::chrono::system_clock::now();
    uint64_t stable_ts = std::chrono::duration_cast<duration_t>( end_ts - start_ts ).count();

    std::cout << "[radix] => " << radix_ts << DURATION_PREFIX << '\n';
    std::cout << "[std::stable_sort] => " << stable_ts << DURATION_PREFIX << '\n';

    return EXIT_SUCCESS;
}