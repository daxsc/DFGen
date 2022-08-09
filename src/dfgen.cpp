#include "dfgen.h"
#include <iostream>
#include <string>
#include "FastNoiseLite.h"
#include <sstream>
#include <cstring>


int chartoint(char s[])
{

    int i, n;
    n = 0;
    for (i = 0; isdigit(s[i]); ++i) {
        n = 10 * n + (s[i] - '0');
    }
    return n;
}

float round(float value, unsigned char prec)
{
    float pow_10 = pow(10.0f, (float)prec);
    return round(value * pow_10) / pow_10;
}

std::string convertToString(char* a, int size)
{
    int i;
    std::string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

extern "C"
{

    EXPORTED char* noise(int argc, char* argv[])
    {
        FastNoiseLite mynoise;
        int size_x = chartoint(argv[0]);
        int size_y = chartoint(argv[1]);
        int seed = chartoint(argv[2]);
        float frequency = atof(argv[3]);
        int octaves = chartoint(argv[4]);
        float lacunarity = atof(argv[5]);
        float gain = atof(argv[6]);
        mynoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        mynoise.SetFractalType(FastNoiseLite::FractalType_FBm);
        mynoise.SetSeed(seed);
        mynoise.SetFrequency(frequency);
        mynoise.SetFractalOctaves(octaves);
        mynoise.SetFractalLacunarity(lacunarity);
        mynoise.SetFractalGain(gain);
        std::string buf = "";

        for (float myy = 0; myy < size_y; myy++) {
        for (float myx = 0; myx < size_x; myx++) {
            float noiseAtCords = mynoise.GetNoise(myy, myx);
            //float rounded = round(noiseAtCords, 2);
            std::string converted = std::to_string(noiseAtCords);
            buf += converted;
            buf += ",";
            }
        }
        char* res = new char[buf.length() + 1 + 8];
        std::stringstream not_str;
        not_str << (void*)res;
        std::string adr = not_str.str();
        buf += adr;
        #ifdef _WIN32
        strcpy_s(res, buf.length() + 1, buf.c_str());
        #else
        strcpy(res, buf.c_str());
        #endif
        return res;
    }

    EXPORTED void del_memory(int argc, char* argv[])
    {
        std::string s(argv[0]);
        unsigned long p = std::stoul(s.c_str(), 0, 16);
        char* ptr = reinterpret_cast<char*>(p);
        delete ptr;
        return;
    }
}