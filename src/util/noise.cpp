#include "noise.hpp"

//Slightly modified implementation of Perlin Noise described by Ken Perlin in https://mrl.cs.nyu.edu/~perlin/paper445.pdf and https://mrl.cs.nyu.edu/~perlin/noise/

namespace SHOGUN {

PerlinNoise::PerlinNoise(bool randomize) {
    if (randomize) {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(std::begin(permutation), std::begin(permutation) + 512, g);
    }
}

float PerlinNoise::noise(float x, float y, float z) {
    int X = (int) x % 255,
        Y = (int) y % 255,
        Z = (int) z % 255;
    x -= (int) x;
    y -= (int) y;
    z -= (int) z;

    float u = fade(x),
          v = fade(y),
          w = fade(z);

    int A = permutation[X]+Y, AA = permutation[A]+Z, AB = permutation[A+1]+Z;
    int B = permutation[X+1]+Y, BA = permutation[B]+Z, BB = permutation[B+1]+Z;

    return  interp(
                interp(
                    interp(grad(permutation[AA], x, y, z),
                           grad(permutation[BA], x-1, y, z),
                           u),
                    interp(grad(permutation[AB], x, y-1, z),
                           grad(permutation[BB], x-1, y-1, z),
                           u),
                v),
                interp(
                    interp(grad(permutation[AA+1], x, y, z-1),
                           grad(permutation[BA+1], x-1, y, z-1),
                           u),
                    interp(grad(permutation[AB+1], x, y-1, z-1),
                           grad(permutation[BB+1], x-1, y-1, z-1),
                           u),
                v),
            w);
}

float PerlinNoise::interp(float x, float y, float a) {
    return x + a * (y - x);
}

float PerlinNoise::fade(float a) {
    return a * a * a * (a * ( a * 6 - 15) + 10);
}

float PerlinNoise::grad(int hash, float x, float y, float z) {
    int h = hash % 16;
    float u = h < 8 ? x : y,
          v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}


}
