
#include "../stdafx.h"
#include "../bserver/cryptutil.h"

using namespace std;

int main() {
    string smessage_hash, smessage, sprivate_key, sn;
    int_type message_hash, message, private_key, n;
    cout << "Zweryfikuj podpis!" << endl;
    cout << "Podaj podpisaną wiadomość: ";
    cin >> smessage_hash;message_hash = string_to_int_type(smessage_hash, 10);
    cout << "Podaj wiadomość: ";
    cin >> smessage;message = string_to_int_type(smessage);
    cout << "Podaj klucz prywatny: ";
    cin >> sprivate_key;private_key = string_to_int_type(sprivate_key, 10);
    cout << "Podaj n: ";
    cin >> sn;n = string_to_int_type(sn, 10);
    
    long start_time = boost::posix_time::microsec_clock::local_time().time_of_day().total_milliseconds();
    bool result = pow_modulo(message, private_key, n) == message_hash;
    long end_time = boost::posix_time::microsec_clock::local_time().time_of_day().total_milliseconds();
    if (result) {
        cout << "Wiadomości są zgodne " << end_time - start_time << " milisekund" << endl;
    } else {
        cout << "Wiadomości nie są zgodne" << end_time - start_time << " milisekund" << endl;
    }
}