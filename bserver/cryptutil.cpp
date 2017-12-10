
#include "../stdafx.h"
#include "cryptutil.h"

using namespace std;
using namespace boost::multiprecision;

int_type inverse_number(int_type number, int_type range) {
    int_type result;
    mpz_invert(result.backend().data(), number.backend().data(), range.backend().data());
    return result;
}

int_type string_to_int_type(string a) {
    int_type result;
    mpz_set_str(result.backend().data(), a.c_str(), 62);
    return result;
}

int_type string_to_int_type(string a, int base) {
    int_type result;
    mpz_set_str(result.backend().data(), a.c_str(), base);
    return result;
}

pair<int_type, int_type> read_key_from_file(string filename) {
    int_type result1, result2;
    FILE* file = fopen(filename.c_str(), "r");
    mpz_inp_str(result1.backend().data(), file, 10);
    mpz_inp_str(result2.backend().data(), file, 10);
    fclose(file);
    return make_pair(result1, result2);
}

vector<int_type> read_passwords_from_config_file() {
    vector<int_type> result = vector<int_type>(4);
    FILE* file = fopen("config", "r");
    for (int i=0 ; i<result.size() ; ++i) {
        int_type value;
        mpz_inp_str(value.backend().data(), file, 10);
        result[i] = value;
    }
    fclose(file);
    return result;
}

int_type pow_modulo(int_type base, int_type exponent, int_type modulo) {
    int_type result;
    mpz_powm(result.backend().data(), base.backend().data(), exponent.backend().data(), modulo.backend().data());
    return result;
}