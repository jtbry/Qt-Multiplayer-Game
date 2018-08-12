#include "Player.h"

// Player.cpp
// Source file for the Player class
// Keeps player details (health, name etc)
// Author: ImpossibleMushroom, https://github.com/ImpossibleMushroom
// Uses QtNetwork and other Qt 5.11 Modules


Player::Player(QTcpSocket * ClientSocket, QString ClientName, QString ClientId)
{
	playerName = ClientName;
	playerId = ClientId;
	playerSocket = ClientSocket;

	connect(playerSocket, &QTcpSocket::readyRead, this, &Player::readNewMessage);
}

void Player::updatePlayerJson(QJsonDocument playerJson)
{
	playerPosition = QPoint(playerJson["posX"].toInt(), playerJson["posY"].toInt());
	playerColor = QColor(playerJson["color"]["red"].toInt(), playerJson["color"]["blue"].toInt(), playerJson["color"]["green"].toInt());
}

QTcpSocket * Player::getPlayerSocket()
{
	return playerSocket;
}

QString Player::getPlayerId()
{
	return playerId;
}

QString Player::getPlayerName()
{
	return playerName;
}

void Player::readNewMessage()
{
	QString msgRemovedNewline = QString(playerSocket->readLine()).replace("\n", "");
	QJsonDocument messageJson = QJsonDocument::fromJson(msgRemovedNewline.toUtf8());

	if (messageJson.isNull()) {
		// Process any sort of non json messages
		// All mesages as of Aug 11 are json so return
		return;
	}
	else {
		if (messageJson["event"] == QJsonValue::Undefined) {
			return;
		}
		else {
			if (messageJson["event"].toString() == "updatePlayer") {
				emit updatePlayerInList(messageJson);
			}
		}
	}

	if(playerSocket->canReadLine()) {
		readNewMessage();
	}
}
