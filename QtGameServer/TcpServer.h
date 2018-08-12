#pragma once

// TcpServer.h
// Header file for the TcpServer class.
// Initializes QTcpServer and then handles all requests to it.
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
#include <QList>

#include "Player.h"

class TcpServer : public QObject {
	Q_OBJECT 
public:
	TcpServer::TcpServer(); // Constructor
	QTcpServer* GetServerPtr(); // Return the server's QTcpServer ptr.
	bool Listen(const QHostAddress &ip = QHostAddress::Any, quint16 port = 0); // Listen for connections on host and ip
	
	
private slots:
	void handleNewConnection();
	void updatePlayerInList(QJsonDocument playerJson);
private:
	QTcpServer *server = nullptr; // Pointer for class server object
	QList<Player*> PlayerList;
};