#include <QtCore/QCoreApplication>
#include "TcpServer.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	// Start the game server
	TcpServer GameServer;

	// Listen on localhost:8090
	if (!GameServer.Listen(QHostAddress::LocalHost, 8090)) {
		std::cout << "[ERROR] GameServer could not be started..." << std::endl;
		std::cout << "[Error String]: " << GameServer.GetServerPtr()->errorString().toStdString() << std::endl;
		std::cout << "Press any key to exit...";
		std::cin.get();
		return 1;
	}
	else {
		std::cout << "[SUCCESS] GameServer started..." << std::endl;
		std::cout << "GameServer Ip: " << GameServer.GetServerPtr()->serverAddress().toString().toStdString() << std::endl;
		std::cout << "GameServer Port: " << GameServer.GetServerPtr()->serverPort() << std::endl;
	}

	return a.exec();
}
