//code

#include <SFML/Network.hpp>
#include <iostream>

using namespace std;

int main()
{
	sf::UdpSocket udpSock;

	sf::IpAddress ip = "127.0.0.1";
	unsigned short port = 54000;

	string message = "Hello";
	double speed = 10.3345;

	sf::Packet packet;

	packet << message << speed;
	udpSock.send(packet, ip, port);

	system("pause");
	return 0;
}