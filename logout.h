#ifndef LOGOUT_H
#define LOGOUT_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include "common.h"

class LogoutDialog : public QWidget
{
private:
    QLabel *img;
public:

    LogoutDialog(QWidget *callerWindow) : QWidget(nullptr)
    {
        setWindowTitle("Logout - CRIME RECORD MANAGEMENT SYSTEM");

        img = new QLabel(this);
        img->setPixmap(loadPixmap("backgroundFour.png"));
        img->setScaledContents(true);

        Card *popupCard = new Card(560, 320, 480, 260, this);

        QLabel *icon = new QLabel("?", this);
        icon->setGeometry(560, 348, 480, 44);
        icon->setAlignment(Qt::AlignCenter);
        icon->setStyleSheet
        (
            "font-size  : 32px;"
            "color      : #ffcc44;"
            "background : transparent;"
        );

        QLabel *title = new QLabel("CONFIRM  LOGOUT", this);
        title->setGeometry(560, 400, 480, 30);
        title->setAlignment(Qt::AlignCenter);
        title->setStyleSheet
        (
            MONO +
            "font-size     : 18px;"
            "font-weight   : bold;"
            "letter-spacing: 5px;"
            "color         : #ffffff;"
            "background    : transparent;"
        );

        QLabel *subtitle = new QLabel("Are you sure you want to logout?", this);
        subtitle->setGeometry(560, 438, 480, 22);
        subtitle->setAlignment(Qt::AlignCenter);
        subtitle->setStyleSheet
        (
            MONO +
            "font-size  : 13px;"
            "color      : #c0dff5;"
            "background : transparent;"
        );

        QLabel *line = new QLabel(this);
        line->setGeometry(600, 472, 400, 1);
        line->setStyleSheet("background: rgba(0,200,255,0.25);");

        QPushButton *yesButton = new QPushButton("YES LOGOUT", this);
        yesButton->setGeometry(610, 492, 170, 46);
        yesButton->setCursor(Qt::PointingHandCursor);
        yesButton->setStyleSheet
            (
                "QPushButton"
                "{"
                    "background : rgba(120, 0, 0, 0.70);"
                    "color : #ff9999;"
                    "font-family : 'Courier New', monospace;"
                    "font-size : 13px;"
                    "font-weight : bold;"
                    "letter-spacing : 2px;"
                    "border : 1px solid rgba(255, 80, 80, 0.55);"
                    "border-radius : 8px;"
                "}"
                "QPushButton:hover"
                "{"
                    "background : rgba(180, 0, 0, 0.90);"
                    "color : #ffffff;"
                    "border : 1px solid #ff4444;"
                "}"
                "QPushButton:pressed"
                "{"
                    "background : #5a0000;"
                "}"
            );

        QPushButton *noButton = new QPushButton("NO STAY", this);
        noButton->setGeometry(820, 492, 170, 46);
        noButton->setCursor(Qt::PointingHandCursor);
        noButton->setStyleSheet
            (
                "QPushButton"
                "{"
                    "background : qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #004d60, stop:1 #007a8a);"
                    "color : #e0f8ff;"
                    "font-family : 'Courier New', monospace;"
                    "font-size : 13px;"
                    "font-weight : bold;"
                    "letter-spacing : 2px;"
                    "border : 1px solid rgba(0, 210, 240, 0.60);"
                    "border-radius : 8px;"
                "}"
                "QPushButton:hover"
                "{"
                    "background : qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #009ab0, stop:1 #00c8d8);"
                    "border : 2px solid #00eeff;"
                    "color : #ffffff;"
                "}"
                "QPushButton:pressed"
                "{"
                    "background : #003a45;"
                "}"
            );

        QLabel *footer = new QLabel("DEPARTMENT OF CRIMINAL JUSTICE    INTERNAL USE ONLY", this);
        footer->setGeometry(0, 872, 1600, 18);
        footer->setAlignment(Qt::AlignCenter);
        footer->setStyleSheet
        (
            MONO +
            "font-size     : 10px;"
            "letter-spacing: 4px;"
            "color         : #7ab8e0;"
            "background    : transparent;"
            "font-weight   : bold;"
        );


        connect(yesButton, &QPushButton::clicked, this, [=]()
            {
                if (callerWindow)
                    callerWindow->close();
                this->close();
            }
        );

        connect(noButton, &QPushButton::clicked, this, [=]()
            {
                this->close();
            }
        );
    }

    void resizeEvent(QResizeEvent *)
    {
        img->resize(size());
    }
};

#endif