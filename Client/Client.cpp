//code

#include <SFML/Network.hpp>
#include <iostream>

using namespace std;

int main()
{
	sf::UdpSocket clientSock;
	sf::UdpSocket cSock;

	//sf::IpAddress ip = sf::IpAddress::getPublicAddress();
	sf::IpAddress ip = "127.0.0.1";
	unsigned short port;
	char message[100];
	//char str[100] = "connecting";
	size_t received;
	cout << "Enter 0 to quit" << endl;

	cout << "Enter a port number: ";
	cin >> port;

	if (clientSock.bind(port) != sf::Socket::Done)
	{
		cout << "There was an error binding to port" << port << endl;
	}
	
	
	//cSock.send(str, 100, ip, port);

	while (message != 0) {
		
		cout << "Message:  ";
		cin >> message;

		clientSock.send(message, 100, ip, port);

		clientSock.receive(message, 100, received, ip, port);
		
		cout << "<Echo> " << message;
		
	}
	
	return 0;
}