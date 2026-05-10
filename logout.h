#ifndef LOGOUT_H
#define LOGOUT_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>

#include "common.h"

class LogoutDialog : public QWidget
{
private:
    QLabel *img;
public:

    LogoutDialog(QWidget *callerWindow) : QWidget(nullptr)
    {
        setWindowTitle("Logout - CRIME RECORD MANAGEMENT SYSTEM");
        img = UI::setupBackground(this, "backgroundFour.png");
        new Card(560, 320, 480, 260, this);

        QLabel *icon = new QLabel("⚠", this);
        
        icon->setGeometry(560, 348, 480, 44);
        icon->setAlignment(Qt::AlignCenter);
        icon->setStyleSheet
        (
            "font-size : 32px;"
            "color : #ffcc44;"
            "background : transparent;"
        );

        QLabel *title = new QLabel("CONFIRM  LOGOUT", this);
        
        title->setGeometry(560, 400, 480, 32);
        title->setAlignment(Qt::AlignCenter);
        title->setStyleSheet
        (
            MONO +
            "font-size : 24px;"
            "font-weight : bold;"
            "letter-spacing : 6px;"
            "color : #ffffff;"
            "background : transparent;"
        );

        QLabel *subtitle = new QLabel("Are you sure you want to logout?", this);
        
        subtitle->setGeometry(560, 440, 480, 24);
        subtitle->setAlignment(Qt::AlignCenter);
        subtitle->setStyleSheet
        (
            MONO +
            "font-size : 18px;"
            "color : #c0dff5;"
            "background : transparent;"
            "font-weight : bold;"
        );

        QLabel *line = new QLabel(this);
        
        line->setGeometry(600, 475, 400, 1);
        line->setStyleSheet("background : rgba(0, 200, 255, 0.25);");

        ClearButton *yesButton = new ClearButton("YES LOGOUT", 610, 492, 175, 48, this);
        yesButton->setSound("logoutButtonSound.mp3");

        Button *noButton = new Button("NO STAY", 815, 492, 175, 48, this);
        noButton->setSound("backButtonSound.mp3");

        QLabel * footer = new QLabel("DEPARTMENT OF CRIMINAL JUSTICE    |    INTERNAL USE ONLY", this);
        footer->setGeometry(0, 872, 1600, 18);
        footer->setAlignment(Qt::AlignCenter);
        footer->setStyleSheet
        (
            MONO +
            "font-size : 14px;"
            "letter-spacing : 4px;"
            "color : #7ab8e0;"
            "background : transparent;"
            "font-weight : bold;"
        );

        connect(yesButton, &QPushButton::clicked, this, [=]()
            {
                if (callerWindow)
                {
                    if (callerWindow->parentWidget())
                    {
                        callerWindow->parentWidget()->close();
                    }
                    callerWindow->close();
                }
                this->close();
            }
        );

        connect(noButton, &QPushButton::clicked, this, [=]()
            {
                this->close();
            }
        );
    }

    void resizeEvent(QResizeEvent * event) override
    {
        QWidget::resizeEvent(event);
        img->resize(size());
    }
};

#endif