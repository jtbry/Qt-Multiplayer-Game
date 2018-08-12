#pragma once

// TcpClient.h
// Header file for the TcpClient
// Handles server connections etc
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
#include "Player.h"

class TcpClient : public QObject {
	Q_OBJECT
signals:
	void forceUpdatePlayer();
	void sendGuiError(QString txt);
	void addNewPlayer(QJsonDocument playerJson);
	void removePlayer(QJsonDocument playerJson);
	void updateExistingPlayer(QJsonDocument playerJson);
	void clientConnected();
	void clientDisconnected();
public slots:
	void readMessage();
	void sendPlayerToServer(Player player);
public:
	TcpClient();
	void handleDisconnect();
	void handleConnect();
	bool connectToHost(QString host, quint16 port);
	QTcpSocket* getSocket();
private:
	QTcpSocket * socket = new QTcpSocket();
};