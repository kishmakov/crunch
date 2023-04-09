#include <iostream>
#include <bitset>
#include <iomanip>

#include "wallace.h"

const unsigned randSeed = 20230402;

int main() {

    for (int n = 1; n <= 32; n++) {
        std::cout << std::setw(3) << n << " , ";
        std::cout << std::setw(3) << depthOfWallaceTree(n);
        std::cout << std::endl;
    }

//    std::srand(randSeed);
//
//    for (int i = 0; i < 10; i++) {
//        uint16_t randomX = static_cast<uint16_t>(std::rand() & 0xFFFF);
//        uint16_t randomY = static_cast<uint16_t>(std::rand() & 0xFFFF);
//
//        uint16_t randomXY = randomX * randomY;
//
//        std::cout << "x=" << std::bitset<16>(randomX) << " ";
//        std::cout << "y=" << std::bitset<16>(randomY) << " ";
//        std::cout << "xy=" << std::bitset<16>(randomXY);
//        std::cout << std::endl;
//    }

    return 0;
}
