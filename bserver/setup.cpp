
#include "../stdafx.h"
#include "setup.h"
#include "primes.h"
#include "cryptutil.h"

using namespace std;
using namespace boost::multiprecision;

void promise_random_prime(int primelength, boost::promise<int_type> &prime) {
    prime.set_value(generate_random_prime(primelength));
}

void generate_rsa_key(int keylength, string private_key_filename, string public_key_filename) {
    ofstream private_key_file, public_key_file;
    private_key_file.open(private_key_filename);
    public_key_file.open(public_key_filename);
    ofstream config;
    long start_time = boost::posix_time::microsec_clock::local_time().time_of_day().total_milliseconds();

    boost::promise<int_type> p_promise, q_promise;
    boost::thread{promise_random_prime, keylength / 2, boost::ref(p_promise)};
    boost::thread{promise_random_prime, keylength / 2, boost::ref(q_promise)};
    int_type p = p_promise.get_future().get();
    int_type q = q_promise.get_future().get();
    int_type n = p * q;
    int_type phi_n = (p - int_type(1)) * (q - int_type(1));
    int_type e;
    e = find_coprime_for(phi_n);
    int_type d = inverse_number(e, phi_n);
    long end_time = boost::posix_time::microsec_clock::local_time().time_of_day().total_milliseconds();
    private_key_file << n << endl << d << endl;
    public_key_file << n << endl << e << endl;
    stringstream password;
    password << "password" << keylength;
    int_type m = string_to_int_type(password.str());
    int_type crypted = pow_modulo(m, e, n);
    config.open("config", ofstream::out | ofstream::app);
    cout << "Klucz o długości " << keylength << " został wygenerowany w " << end_time - start_time << " milisekund" << endl;
    cout << "hasło = " << password.str() << endl;
    config << crypted << endl;
}

int setup() {
    remove("config");
    vector<int> keylengths = {2048, 4096, 8192, 16384};
    vector<boost::thread> threads = vector<boost::thread>(keylengths.size());
    for (int i = 0; i < keylengths.size(); ++i) {
        stringstream priv_key_filename, publ_key_filename;
        priv_key_filename << "priv_" << keylengths[i];
        publ_key_filename << "publ_" << keylengths[i];
        threads[i] = boost::thread(generate_rsa_key, keylengths[i], priv_key_filename.str(), publ_key_filename.str());
    }
    for (int i = 0; i < keylengths.size(); ++i) {
        threads[i].join();
    }
    cout << "Generowanie kluczy zakończone!" << endl << endl;
    return 0;
}