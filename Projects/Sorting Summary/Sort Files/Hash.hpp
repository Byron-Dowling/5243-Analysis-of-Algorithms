#include <string>
#include <vector>
using namespace std;

class Hash 
{
public:

    //https://en.wikipedia.org/wiki/Jenkins_hash_function#one-at-a-time
    static unsigned int JOAATHash(string key) {
        unsigned int i = 0;
        unsigned int hash = 0;
        while (i != key.size()) {
            hash += key[i++];
            hash += hash << 10;
            hash ^= hash >> 6;
        }
        hash += hash << 3;
        hash ^= hash >> 11;
        hash += hash << 15;
        return hash;
    }

    //https://en.wikipedia.org/wiki/PJW_hash_function
    static unsigned int ELFHash(string str) {
        unsigned int hash = 0;
        unsigned int x = 0;

        for (int i = 0; i < str.length(); i++) {
            hash = (hash << 4) + str[i];
            if ((x = hash & 0xF0000000L) != 0) {
                hash ^= (x >> 24);
            }
            hash &= ~x;
        }

        return hash;
    }
    //https://en.wikipedia.org/wiki/Robert_Sedgewick_(computer_scientist)
    // Robert Sedgewick hash
    static unsigned int RSHash(string str) {

        unsigned int b = 378551;
        unsigned int a = 63689;
        unsigned int hash = 0;

        for (int i = 0; i < str.length(); i++) {
            hash = hash * a + str[i];
            a = a * b;
        }

        return hash;
    }


    static unsigned int JSHash(string str) {
        unsigned int hash = 1315423911;

        for (int i = 0; i < str.length(); i++) {
            hash ^= ((hash << 5) + str[i] + (hash >> 2));
        }

        return hash;
    }

    //https://en.wikipedia.org/wiki/PJW_hash_function
    static unsigned int PJWHash(string str) {
        unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
        unsigned int ThreeQuarters = (unsigned int)((BitsInUnsignedInt * 3) / 4);
        unsigned int OneEighth = (unsigned int)(BitsInUnsignedInt / 8);
        unsigned int HighBits = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
        unsigned int hash = 0;
        unsigned int test = 0;

        for (int i = 0; i < str.length(); i++) {
            hash = (hash << OneEighth) + str[i];

            if ((test = hash & HighBits) != 0) {
                hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
            }
        }

        return hash;
    }

    static unsigned int BKDRHash(string str) {
        unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
        unsigned int hash = 0;

        for (int i = 0; i < str.length(); i++) {
            hash = (hash * seed) + str[i];
        }

        return hash;
    }


    static unsigned int SDBMHash(string str) {
        unsigned int hash = 0;

        for (int i = 0; i < str.length(); i++) {
            hash = str[i] + (hash << 6) + (hash << 16) - hash;
        }

        return hash;
    }


    static unsigned int DJBHash(string str) {
        unsigned int hash = 5381;

        for (int i = 0; i < str.length(); i++) {
            hash = ((hash << 5) + hash) + str[i];
        }

        return hash;
    }


    static unsigned int DEKHash(string str) {
        unsigned int hash = static_cast<unsigned int>(str.length());

        for (int i = 0; i < str.length(); i++) {
            hash = ((hash << 5) ^ (hash >> 27)) ^ str[i];
        }

        return hash;
    }


    static unsigned int BPHash(string str) {
        unsigned int hash = 0;
        for (int i = 0; i < str.length(); i++) {
            hash = hash << 7 ^ str[i];
        }

        return hash;
    }


    static unsigned int FNVHash(string str) {
        const unsigned int fnv_prime = 0x811C9DC5;
        unsigned int hash = 0;
        for (int i = 0; i < str.length(); i++) {
            hash *= fnv_prime;
            hash ^= str[i];
        }

        return hash;
    }


    static unsigned int APHash(string str) {
        unsigned int hash = 0xAAAAAAAA;

        for (int i = 0; i < str.length(); i++) {
            hash ^= ((i & 1) == 0) ? ((hash << 7) ^ str[i] ^ (hash >> 3)) : (~((hash << 11) ^ str[i] ^ (hash >> 5)));
        }

        return hash;
    }

};