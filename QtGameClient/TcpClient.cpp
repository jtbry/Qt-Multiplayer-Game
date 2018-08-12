#include "TcpClient.h"
// TcpClient.cpp
// Source file for the TcpClient
// Handles server connections etc
// Author: ImpossibleMushroom, https://github.com/ImpossibleMushroom
// Uses QtNetwork and other Qt 5.11 Modules

void TcpClient::handleDisconnect()
{
	emit sendGuiError("Disconnected from server");
	emit clientDisconnected();
}

void TcpClient::handleConnect()
{
	emit clientConnected();
}

bool TcpClient::connectToHost(QString host, quint16 port)
{
	// Connect to given host
	socket->connectToHost(host, port);
	if (socket->waitForConnected(20000)) {
		return true;
	}
	else {
		return false;
	}
}

void TcpClient::sendPlayerToServer(Player player)
{
	QJsonObject jsonPlayerData;
	jsonPlayerData.insert("event", "updatePlayer");
	jsonPlayerData.insert("name", player.getPlayerName());
	jsonPlayerData.insert("pid", player.getPlayerId());
	jsonPlayerData.insert("posX", player.getPlayerPosition().x());
	jsonPlayerData.insert("posY", player.getPlayerPosition().y());
	jsonPlayerData.insert("color", QJsonObject{
		{"red", player.getPlayerColor().red()},
		{"green", player.getPlayerColor().green()},
		{"blue", player.getPlayerColor().blue()}
	});
	QString stringPlayerData = QJsonDocument(jsonPlayerData).toJson(QJsonDocument::Compact);
	socket->write(stringPlayerData.toUtf8()+"\n");
}

QTcpSocket * TcpClient::getSocket()
{
	// Return the TcpClient's socket
	return socket;
}

void TcpClient::readMessage()
{
	QString msgRemovedNewline = QString(socket->readLine()).replace("\n", "");
	QJsonDocument messageJson = QJsonDocument::fromJson(msgRemovedNewline.toUtf8());

	if (messageJson.isNull()) {
		// Handle non json messages
		// All messages are sent in json as of Aug 11th so return
		return;
	}
	else {
		if (messageJson["event"] == QJsonValue::Undefined) {
			return;
		}
		else {
			if (messageJson["event"] == "updatePlayer") {
				// Update an existing player
				emit updateExistingPlayer(messageJson);
			}
			else if (messageJson["event"] == "newPlayerConnected") {
				// Add player to QList<Player>
				emit addNewPlayer(messageJson);
			}
			else if (messageJson["event"] == "playerDisconnected") {
				// Delete player from QList<Player> and delete the object
				emit removePlayer(messageJson);
			}
			else if (messageJson["event"] == "forceUpdate") {
				emit forceUpdatePlayer();
			}
		}
	}
	if (socket->canReadLine()) {
		readMessage();
	}
}

TcpClient::TcpClient()
{
	// Connect slots and signals from the QTcpSocket to appropriate functions
	connect(socket, &QTcpSocket::disconnected, this, &TcpClient::handleDisconnect);
	connect(socket, &QTcpSocket::connected, this, &TcpClient::handleConnect);
	connect(socket, &QTcpSocket::readyRead, this, &TcpClient::readMessage);
}

