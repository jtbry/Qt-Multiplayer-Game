// TcpServer.cpp
// Source file for the TcpServer class.
// Initializes QTcpServer and then handles all requests to it.
// Author: ImpossibleMushroom, https://github.com/ImpossibleMushroom
// Uses QtNetwork and other Qt 5.11 Modules

#include "TcpServer.h"

TcpServer::TcpServer()
{
	// Sets variables and connects slots as needed
	server = new QTcpServer(this);
	connect(server, &QTcpServer::newConnection, this, &TcpServer::handleNewConnection); // Connect the handleNewConnection slot to signal.
}

bool TcpServer::Listen(const QHostAddress &ip, quint16 port)
{
	// Listen on the ip and port given, return result.
	if (server->isListening()) {
		// If the server is already listening on given ip:port return true
		if (server->serverAddress() == ip && server->serverPort() == port) {
			return true;
		}
		// If the server is not listening on the given ip:port close and reopen
		else {
			server->close();
			if (server->listen(ip, port)) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	else {
		// If the server is not already listening begin listening on given ip:port
		if (server->listen(ip, port)) {
			return true;
		}
		else {
			return false;
		}
	}
}

void TcpServer::updatePlayerInList(QJsonDocument playerJson)
{
	for (int i = 0; i < PlayerList.length(); i++) {
		if (PlayerList.at(i)->getPlayerId() == playerJson["pid"].toString()) {
			PlayerList.at(i)->updatePlayerJson(playerJson);
		}
	}

	// After updating this player's data send it to all clients to update
	for (int i = 0; i < PlayerList.length(); i++) {
		PlayerList.at(i)->getPlayerSocket()->write(playerJson.toJson(QJsonDocument::Compact) + "\n");
	}
}


QTcpServer* TcpServer::GetServerPtr()
{
	// Return the server's QTcpServer ptr.
	return server;
}

void TcpServer::handleNewConnection() 
{
	// Handle a new connection to the server.
	QTcpSocket *Client = server->nextPendingConnection();
	
	if (!Client->waitForReadyRead(10000)) {
		Client->disconnectFromHost();
	}
	else {
		QJsonDocument jsonPlayerData = QJsonDocument::fromJson(Client->readAll());
		if (jsonPlayerData.isNull()) {
			Client->disconnectFromHost();
		}
		else {
			if (jsonPlayerData["name"] == QJsonValue::Undefined) {
				Client->disconnectFromHost();
			}
			else {
				if (jsonPlayerData["pid"] == QJsonValue::Undefined) {
					Client->disconnectFromHost();
				}
				else {
					std::cout << jsonPlayerData["name"].toString().toStdString() << " has connected!" << std::endl;
					Player* newPlayer = new Player(Client, jsonPlayerData["name"].toString(), jsonPlayerData["pid"].toString());
					connect(newPlayer, &Player::updatePlayerInList, this, &TcpServer::updatePlayerInList);
					PlayerList.append(newPlayer);

					// Notify all players that a new player has joined
					QJsonObject jsonPlayerObject = jsonPlayerData.object();
					jsonPlayerObject.insert("event", "newPlayerConnected");
					for (int i = 0; i < PlayerList.length(); i++) {
						PlayerList.at(i)->getPlayerSocket()->write(QJsonDocument(jsonPlayerObject).toJson(QJsonDocument::Compact) + "\n");
					}

					for (int i = 0; i < PlayerList.length(); i++) {
						QJsonObject addPlayer;
						addPlayer.insert("event", "newPlayerConnected");
						addPlayer.insert("name", PlayerList.at(i)->getPlayerName());
						addPlayer.insert("pid", PlayerList.at(i)->getPlayerId());
						Client->write(QJsonDocument(addPlayer).toJson(QJsonDocument::Compact) + "\n");
					}

					QJsonObject forceUpdateEvent;
					forceUpdateEvent.insert("event", "forceUpdate");
					Client->write(QJsonDocument(forceUpdateEvent).toJson(QJsonDocument::Compact) + "\n");
				}
			}
		}
	}
}

