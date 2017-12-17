
#include "sign.h"
#include "../stdafx.h"
#include "cryptutil.h"

using namespace std;
using boost::asio::ip::tcp;

int_type calculate_response(int_type x, int_type e, int_type d, int_type n) {
    int_type r = random_smaller_than(n);
    int_type y = pow_modulo((pow_modulo(r, e, n) * x), d, n);
    return (y * inverse_number(r, n)) % n;
} 

int listen(pair<int_type, int_type> publ_key, pair<int_type, int_type> priv_key) {
    cout << "Rozpoczynam nasłuchiwanie :o" << endl;
    char data[DEFAULT_BUFFLEN];
    boost::system::error_code error_code;
    try {
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), SERVER_PORT));
        while ( !error_code ) {
            tcp::socket socket(io_service);
            acceptor.accept(socket);
            cout << "Połączono z klientem" << endl;
            while ( !error_code ) {
                boost::asio::streambuf buffer;
                boost::asio::read_until(socket, buffer, '\n', error_code);
                if (error_code) break;
                istream str(&buffer);
                string message;
                getline(str, message);
                cout << "Otrzymano wiadomość do podpisania:" << message << endl;
                stringstream response;
                long start_time = boost::posix_time::microsec_clock::local_time().time_of_day().total_milliseconds();
                response << calculate_response(string_to_int_type(message), publ_key.second, priv_key.second, priv_key.first) << endl;
                long end_time = boost::posix_time::microsec_clock::local_time().time_of_day().total_milliseconds();
                cout << "Podpisano w " << end_time - start_time << " milisekund" << endl;
                boost::asio::write(socket, boost::asio::buffer(response.str()), error_code);
            }
            cout << "Rozłączono z klientem" << endl;
            error_code.clear();
        }
        error_code.clear();
    } catch (exception& e) {
        cerr << e.what() << endl;
    }
}

int sign() {
    vector<string> publ_key_filenames = {"publ_2048", "publ_4096", "publ_8192", "publ_16384"};
    vector<string> priv_key_filenames = {"priv_2048", "priv_4096", "priv_8192", "priv_16384"};
    vector<pair<int_type, int_type>> publ_keys = vector<pair<int_type, int_type>>(publ_key_filenames.size());
    vector<pair<int_type, int_type>> priv_keys = vector<pair<int_type, int_type>>(publ_key_filenames.size());
    vector<int_type> passwords = read_passwords_from_config_file();
    for (int i=0; i<publ_key_filenames.size() ; ++i) {
        publ_keys[i] = read_key_from_file(publ_key_filenames[i]);
        priv_keys[i] = read_key_from_file(priv_key_filenames[i]);
    }
    cout << "Podaj hasło: ";
    string password;
    cin >> password;
    for (int i=0 ; i<publ_key_filenames.size() ; ++i) {
        if (pow_modulo(string_to_int_type(password), publ_keys[i].second, publ_keys[i].first) == passwords[i]) {
            return listen(publ_keys[i], priv_keys[i]);
        }
    }
    cout << "Hasło nieprawidłowe!" << endl << endl;
}

