//Code

#include <SFML/Network.hpp>
#include <iostream>

using namespace std;

int main()
{
	sf::UdpSocket sock; //socket
	sf::UdpSocket serSock;
	size_t received;
	char message[100];
	//sf::IpAddress ip = sf::IpAddress::getPublicAddress();
	sf::IpAddress ip = "127.0.0.1";
	unsigned short port = sf::UdpSocket::AnyPort();
	char str[100];

	vector<sf::IpAddress> ips={};
	vector<unsigned short> ports={};

	/*cout << sf::IpAddress::getPublicAddress() << endl;

	if (sock.bind(54000) != sf::Socket::Done)
	{
		cout << "There was an error binding to port 54000." << endl;
	}
	cout << "Enter 0 to quit" << endl;
	*/
	
	while (message != "0") {

		sock.receive(message, 100, received, ip, port);
		
		//cout << "<server> " << message << endl;
		
		sock.send(message, 100, ip, port);
	}

	system("pause");

}