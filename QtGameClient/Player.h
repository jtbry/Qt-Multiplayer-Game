#pragma once

// Player.h
// Header file for the Player class
// Keeps player details (health, name etc)
// Author: ImpossibleMushroom, https://github.com/ImpossibleMushroom
// Uses QtNetwork and other Qt 5.11 Modules


#include <QtCore>
#include <QPoint>
#include <QColor>

class Player {
public:
	Player();

	void movePlayer(int x, int y);
	void setPlayerName(QString name);
	void setPlayerId(QString pid);
	void updatePlayerJson(QJsonDocument playerJson);

	int getPlayerMoveSize();
	QColor getPlayerColor();
	QPoint getPlayerPosition();
	QString getPlayerName();
	QString getPlayerId();
private:
	QString playerName;
	QString playerId;
	QPoint playerPosition;
	QColor playerColor;
	int playerMoveSize = 10;
};