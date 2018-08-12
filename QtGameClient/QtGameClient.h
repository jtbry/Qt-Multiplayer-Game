#pragma once

#include <QtWidgets/QMainWindow>
#include <iostream>
#include "ui_QtGameClient.h"
#include <QTcpSocket>
#include "TcpClient.h"
#include <QPainter>
#include <QDebug>
#include <QRandomGenerator>
#include <QKeyEvent>
#include <QPushButton>
#include <Quuid>
#include <QMessageBox>

class QtGameClient : public QMainWindow
{
	Q_OBJECT
signals:
	void emitPlayer(Player player);
public slots:
	void displayError(QString txt);
	void connectToGame();
	void clientDisconnect();
	void clientConnect();
	void addNewPlayer(QJsonDocument playerJson);
	void updateExistingPlayer(QJsonDocument playerJson);
	void forceUpdatePlayer();
public:
	QtGameClient(QWidget *parent = Q_NULLPTR);
	void paintEvent(QPaintEvent *);
	void keyPressEvent(QKeyEvent *key);
private:
	TcpClient* localClient = new TcpClient();
	bool isConnectedToServer = false;
	Ui::QtGameClientClass ui;
	Player localPlayer;
	QList<Player*> AllPlayers;
};
