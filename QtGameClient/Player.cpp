#include "Player.h"

Player::Player()
{
	int x = QRandomGenerator::bounded(100, 700);
	int y = QRandomGenerator::bounded(100, 600);
	playerPosition = QPoint(x, y);

	playerColor = QColor(QRandomGenerator::bounded(0, 255), QRandomGenerator::bounded(0, 255), QRandomGenerator::bounded(0, 255));
}

void Player::movePlayer(int x, int y)
{
	playerPosition.setX(playerPosition.x() + x);
	playerPosition.setY(playerPosition.y() + y);
}

void Player::setPlayerName(QString name)
{
	playerName = name;
}

void Player::setPlayerId(QString pid)
{
	playerId = pid;
}

void Player::updatePlayerJson(QJsonDocument playerJson)
{
	playerPosition = QPoint(playerJson["posX"].toInt(), playerJson["posY"].toInt());
	playerColor = QColor(playerJson["color"]["red"].toInt(), playerJson["color"]["blue"].toInt(), playerJson["color"]["green"].toInt());
}

int Player::getPlayerMoveSize()
{
	return playerMoveSize;
}

QColor Player::getPlayerColor()
{
	return playerColor;
}

QPoint Player::getPlayerPosition()
{
	return playerPosition;
}

QString Player::getPlayerName()
{
	return playerName;
}
QString Player::getPlayerId()
{
	return playerId;
}
