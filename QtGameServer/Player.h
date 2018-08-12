#pragma once

// Player.h
// Header file for the Player class
// Keeps player details (health, name etc)
// Author: ImpossibleMushroom, https://github.com/ImpossibleMushroom
// Uses QtNetwork and other Qt 5.11 Modules

#include <iostream>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QDateTime>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QColor>

class Player : public QObject {
	Q_OBJECT
public:
	Player::Player(QTcpSocket* ClientSocket, QString ClientName, QString ClientId); // Constructor
	void updatePlayerJson(QJsonDocument playerJson);

	// Get
	QTcpSocket* getPlayerSocket();
	QString getPlayerId();
	QString getPlayerName();

public slots:
	void readNewMessage();

signals:
	void updatePlayerInList(QJsonDocument playerJson);

private:
	QTcpSocket* playerSocket;
	QString playerName;
	QString playerId;
	QPoint playerPosition;
	QColor playerColor;
};