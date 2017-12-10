
#include "../stdafx.h"

using namespace std;
using boost::asio::ip::tcp;

int main(int argc, const char** argv) {
    if (argc != 2) {
        cout << "Użycie: Pierwszy parametr to adres serwera" << endl;
        return 1;
    }
    try {
        cout << "Próbuję połączyć z serwerem " << argv[1] << endl;
        boost::system::error_code error_code;
        char data[DEFAULT_BUFFLEN];
        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(argv[1], boost::lexical_cast<string>(SERVER_PORT));
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);
        cout << "Połączono z serwerem" << endl;
        while (!error_code) {
            string message;
            cout << "Podaj wiadomość do podpisania(exit aby wyjść): ";
            cin >> message;
            if (message == "exit") return 0;
            message.append("\n");
            boost::asio::write(socket, boost::asio::buffer(message), error_code);
            if (error_code) break;

            boost::asio::streambuf buffer;
            boost::asio::read_until(socket, buffer, '\n', error_code);
            istream str(&buffer);
            string response;
            getline(str, response);
            cout << "Odpowiedź: " << response << endl;
        }
    } catch (exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}