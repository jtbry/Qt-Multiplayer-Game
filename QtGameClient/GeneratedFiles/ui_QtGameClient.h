/********************************************************************************
** Form generated from reading UI file 'QtGameClient.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGAMECLIENT_H
#define UI_QTGAMECLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGameClientClass
{
public:
    QWidget *centralWidget;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLineEdit *targetIp;
    QPushButton *connectBtn;
    QLabel *connectionLbl;
    QLabel *ipAddrlbl;
    QLineEdit *playerName;
    QLabel *playerNameLbl;

    void setupUi(QMainWindow *QtGameClientClass)
    {
        if (QtGameClientClass->objectName().isEmpty())
            QtGameClientClass->setObjectName(QStringLiteral("QtGameClientClass"));
        QtGameClientClass->resize(800, 700);
        QtGameClientClass->setMinimumSize(QSize(800, 700));
        QtGameClientClass->setMaximumSize(QSize(800, 700));
        centralWidget = new QWidget(QtGameClientClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        formLayoutWidget = new QWidget(centralWidget);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(30, 30, 731, 125));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        targetIp = new QLineEdit(formLayoutWidget);
        targetIp->setObjectName(QStringLiteral("targetIp"));

        formLayout->setWidget(3, QFormLayout::FieldRole, targetIp);

        connectBtn = new QPushButton(formLayoutWidget);
        connectBtn->setObjectName(QStringLiteral("connectBtn"));

        formLayout->setWidget(4, QFormLayout::FieldRole, connectBtn);

        connectionLbl = new QLabel(formLayoutWidget);
        connectionLbl->setObjectName(QStringLiteral("connectionLbl"));
        QFont font;
        font.setFamily(QStringLiteral("Segoe UI"));
        font.setPointSize(13);
        connectionLbl->setFont(font);
        connectionLbl->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(0, QFormLayout::FieldRole, connectionLbl);

        ipAddrlbl = new QLabel(formLayoutWidget);
        ipAddrlbl->setObjectName(QStringLiteral("ipAddrlbl"));

        formLayout->setWidget(3, QFormLayout::LabelRole, ipAddrlbl);

        playerName = new QLineEdit(formLayoutWidget);
        playerName->setObjectName(QStringLiteral("playerName"));

        formLayout->setWidget(2, QFormLayout::FieldRole, playerName);

        playerNameLbl = new QLabel(formLayoutWidget);
        playerNameLbl->setObjectName(QStringLiteral("playerNameLbl"));

        formLayout->setWidget(2, QFormLayout::LabelRole, playerNameLbl);

        QtGameClientClass->setCentralWidget(centralWidget);

        retranslateUi(QtGameClientClass);
        QObject::connect(connectBtn, SIGNAL(clicked()), QtGameClientClass, SLOT(connectToGame()));

        QMetaObject::connectSlotsByName(QtGameClientClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtGameClientClass)
    {
        QtGameClientClass->setWindowTitle(QApplication::translate("QtGameClientClass", "QtGameClient", Q_NULLPTR));
        connectBtn->setText(QApplication::translate("QtGameClientClass", "Connect!", Q_NULLPTR));
        connectionLbl->setText(QApplication::translate("QtGameClientClass", "Connect to A Game", Q_NULLPTR));
        ipAddrlbl->setText(QApplication::translate("QtGameClientClass", "Ip Addr", Q_NULLPTR));
        playerNameLbl->setText(QApplication::translate("QtGameClientClass", "Nickname", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtGameClientClass: public Ui_QtGameClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGAMECLIENT_H
