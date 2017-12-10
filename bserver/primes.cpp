
#include "../stdafx.h"
#include "primes.h"

using namespace boost::multiprecision;
using namespace boost::random;

inline int_type gcd(int_type a, int_type b)
{
    int_type temp;
    while (b)
    {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

inline bool are_realtively_prime(int_type a, int_type b)
{
    return gcd(a, b) == 1;
}

int_type find_coprime_for(int_type a, int_type minimum)
{
    int_type result = int_type(minimum);
    while (!are_realtively_prime(result, a))
    {
        ++result;
    }
    return result;
}

inline bool is_prime(int_type number)
{
    return miller_rabin_test(number, 2) && miller_rabin_test(number, 25);
}

uniform_int_distribution<int_type> get_distribution_from_number_of_bits(int number_of_bits)
{
    return  uniform_int_distribution<int_type>(int_type(1) << (number_of_bits - 1), (int_type(1) << number_of_bits) - int_type(1));
}

int_type generate_random_prime(int number_of_bits)
{
    int_type number;
    mt19937 generator(clock());
    uniform_int_distribution<int_type> distribution = get_distribution_from_number_of_bits(number_of_bits);
    do {
        number = distribution(generator);
    } while (!is_prime(number));
    return number;
}