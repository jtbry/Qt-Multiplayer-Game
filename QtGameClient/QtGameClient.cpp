#include "QtGameClient.h"

QtGameClient::QtGameClient(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(localClient, &TcpClient::sendGuiError, this, &QtGameClient::displayError);
	connect(localClient, &TcpClient::clientDisconnected, this, &QtGameClient::clientDisconnect);
	connect(localClient, &TcpClient::clientConnected, this, &QtGameClient::clientConnect);
	connect(localClient, &TcpClient::addNewPlayer, this, &QtGameClient::addNewPlayer);
	connect(localClient, &TcpClient::updateExistingPlayer, this, &QtGameClient::updateExistingPlayer);
	connect(localClient, &TcpClient::forceUpdatePlayer, this, &QtGameClient::forceUpdatePlayer);
	connect(this, &QtGameClient::emitPlayer, localClient, &TcpClient::sendPlayerToServer);
}

void QtGameClient::connectToGame()
{
	this->findChild<QPushButton*>("connectBtn")->setDisabled(true);
	QString targetIp = this->findChild<QLineEdit*>("targetIp")->text();
	QString playerName = this->findChild<QLineEdit*>("playerName")->text();
	QString playerId = QUuid::createUuid().toString();

	QJsonObject jsonPlayerData;
	
	jsonPlayerData.insert("name", playerName);
	jsonPlayerData.insert("pid", playerId);

	if (!localClient->connectToHost(targetIp, 8090)) {
		QMessageBox::critical(this, "QtGameClient: Connection Failed", "Connection to " + targetIp + " failed!\nError: " + localClient->getSocket()->error(), QMessageBox::Ok);
		this->findChild<QPushButton*>("connectBtn")->setDisabled(false);
	}
	else {
		localPlayer.setPlayerName(playerName);
		localPlayer.setPlayerId(playerId);
		localClient->getSocket()->write(QJsonDocument(jsonPlayerData).toJson(QJsonDocument::Compact));
		this->setWindowTitle(localPlayer.getPlayerName() + " playing");
	}

}

void QtGameClient::clientDisconnect()
{
	isConnectedToServer = false;
	this->findChild<QWidget*>("centralWidget")->show();
	this->findChild<QWidget*>("centralWidget")->setDisabled(false);
	this->findChild<QPushButton*>("connectBtn")->setDisabled(false);
}

void QtGameClient::clientConnect()
{
	isConnectedToServer = true;
	this->findChild<QWidget*>("centralWidget")->hide();
	this->findChild<QWidget*>("centralWidget")->setDisabled(true);
}

void QtGameClient::addNewPlayer(QJsonDocument playerJson)
{
	if (playerJson["pid"] != localPlayer.getPlayerId()) {
		Player* newPlayer = new Player();
		newPlayer->setPlayerName(playerJson["name"].toString());
		newPlayer->setPlayerId(playerJson["pid"].toString());
		AllPlayers.append(newPlayer);
	}
	forceUpdatePlayer();
	this->update();
}

void QtGameClient::updateExistingPlayer(QJsonDocument playerJson)
{
	for (int i = 0; i < AllPlayers.length(); i++) {
		if (AllPlayers.at(i)->getPlayerId() == playerJson["pid"].toString()) {
			AllPlayers.at(i)->updatePlayerJson(playerJson);
		}
	}
	this->update();
}

void QtGameClient::forceUpdatePlayer()
{
	localClient->sendPlayerToServer(localPlayer);
	this->update();
}

void QtGameClient::paintEvent(QPaintEvent *)
{
	if (isConnectedToServer) {
		QFontMetrics FontMetrics(QFont("MS Shell Dlg 2", 8));
		QPainter painter(this);

		// Draw Local Player
		painter.setBrush(localPlayer.getPlayerColor());
		painter.setPen(localPlayer.getPlayerColor());
		painter.drawEllipse(localPlayer.getPlayerPosition().x(), localPlayer.getPlayerPosition().y(), 20, 20);
		painter.setFont(QFont("MS Shell Dlg 2", 8));
		painter.drawText(localPlayer.getPlayerPosition().x()-(FontMetrics.width(localPlayer.getPlayerName())/2), localPlayer.getPlayerPosition().y()-4, localPlayer.getPlayerName());

		// Draw Other Players
		for (int i = 0; i < AllPlayers.length(); i++) {
			auto iPlayer = AllPlayers.at(i);
			painter.setBrush(iPlayer->getPlayerColor());
			painter.setPen(iPlayer->getPlayerColor());
			painter.drawEllipse(iPlayer->getPlayerPosition().x(), iPlayer->getPlayerPosition().y(), 20, 20);
			painter.setFont(QFont("MS Shell Dlg 2", 8));
			painter.drawText(iPlayer->getPlayerPosition().x() - (FontMetrics.width(iPlayer->getPlayerName()) / 2), iPlayer->getPlayerPosition().y() - 4, iPlayer->getPlayerName());
		}
	}
}

void QtGameClient::keyPressEvent(QKeyEvent * key)
{
	if (isConnectedToServer) {
		if (key->key() == Qt::Key_Up) {
			localPlayer.movePlayer(0, localPlayer.getPlayerMoveSize() * -1);
			emit emitPlayer(localPlayer);
			this->update();
		}
		if (key->key() == Qt::Key_Down) {
			localPlayer.movePlayer(0, localPlayer.getPlayerMoveSize());
			emit emitPlayer(localPlayer);
			this->update();
		}
		if (key->key() == Qt::Key_Left) {
			localPlayer.movePlayer(localPlayer.getPlayerMoveSize()*-1, 0);
			emit emitPlayer(localPlayer);
			this->update();
		}
		if (key->key() == Qt::Key_Right) {
			localPlayer.movePlayer(localPlayer.getPlayerMoveSize(), 0);
			emit emitPlayer(localPlayer);
			this->update();
		}
	}
}

void QtGameClient::displayError(QString txt) {
	QMessageBox::critical(this, "QtGameClient: Error", txt);
}