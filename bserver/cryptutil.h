
#ifndef BEZPIECZENSTWO6_CRYPTUTIL_H
#define BEZPIECZENSTWO6_CRYPTUTIL_H

int_type inverse_number(int_type number, int_type range);
int_type string_to_int_type(std::string a);
int_type string_to_int_type(std::string a, int base);
std::pair<int_type, int_type> read_key_from_file(std::string filename);
std::vector<int_type> read_passwords_from_config_file();
int_type pow_modulo(int_type base, int_type exponent, int_type modulo);

#endif //BEZPIECZENSTWO6_CRYPTUTIL_H
