#ifndef INTERFACE1_H
#define INTERFACE1_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QResizeEvent>

#include "common.h"
#include "Interface2.h"

class LandingPage : public QWidget
{
private:

    QLabel *background;

public:

    LandingPage()
    {
        setObjectName("mainWindow");
        setWindowTitle("Crime Record Management System");

        background = UI::setupBackground(this, "backgroundOne.png");

        QLabel *topLine = new QLabel("[ TOP SECRET   CLASSIFIED SYSTEM ]", this);
        topLine->setGeometry(470, 42, 660, 30);
        topLine->setAlignment(Qt::AlignCenter);
        topLine->setStyleSheet
        (
            "font-family : 'Courier New', monospace;"
            "font-size : 13px;"
            "font-weight : 900;"
            "letter-spacing : 7px;"
            "color : #00f6ff;"
            "background : rgba(0, 15, 35, 0.72);"
            "border : 1px solid rgba(0, 230, 255, 0.55);"
            "border-radius : 10px;"
        );

        QLabel *titleShadow = new QLabel("CRIME RECORD MANAGEMENT\nSYSTEM", this);
        titleShadow->setGeometry(106, 88, 1400, 210);
        titleShadow->setAlignment(Qt::AlignCenter);
        titleShadow->setStyleSheet
        (
            "font-family : 'Courier New', monospace;"
            "font-size : 72px;"
            "font-weight : 900;"
            "letter-spacing : 2px;"
            "color : rgba(0, 0, 0, 0.90);"
            "background : transparent;"
        );

        QLabel *titleGlow = new QLabel("CRIME RECORD MANAGEMENT\nSYSTEM", this);
        titleGlow->setGeometry(96, 72, 1400, 210);
        titleGlow->setAlignment(Qt::AlignCenter);
        titleGlow->setStyleSheet
        (
            "font-family : 'Courier New', monospace;"
            "font-size : 72px;"
            "font-weight : 900;"
            "letter-spacing : 2px;"
            "color : rgba(0, 234, 255, 0.38);"
            "background : transparent;"
        );

        QLabel *title = new QLabel("CRIME RECORD MANAGEMENT\nSYSTEM", this);
        title->setGeometry(100, 78, 1400, 210);
        title->setAlignment(Qt::AlignCenter);
        title->setStyleSheet
        (
            "font-family : 'Courier New', monospace;"
            "font-size : 72px;"
            "font-weight : 900;"
            "letter-spacing : 2px;"
            "color : #ffffff;"
            "background : transparent;"
        );

        QLabel *subtitleShadow = new QLabel("SECURE ACCESS PORTAL   AUTHORIZED PERSONNEL ONLY", this);
        subtitleShadow->setGeometry(102, 304, 1400, 34);
        subtitleShadow->setAlignment(Qt::AlignCenter);
        subtitleShadow->setStyleSheet
        (
            "font-family : 'Courier New', monospace;"
            "font-size : 16px;"
            "font-weight : 900;"
            "letter-spacing : 5px;"
            "color : rgba(0, 0, 0, 0.90);"
            "background : transparent;"
        );

        QLabel *subtitle = new QLabel("SECURE ACCESS PORTAL   AUTHORIZED PERSONNEL ONLY", this);
        subtitle->setGeometry(100, 300, 1400, 34);
        subtitle->setAlignment(Qt::AlignCenter);
        subtitle->setStyleSheet
        (
            "font-family : 'Courier New', monospace;"
            "font-size : 16px;"
            "font-weight : 900;"
            "letter-spacing : 5px;"
            "color : #e8fbff;"
            "background : rgba(0, 15, 35, 0.62);"
            "border : 1px solid rgba(0, 230, 255, 0.25);"
            "border-radius : 8px;"
        );

        const QString pillLabels[] =
        {
            "SECURE DATA",
            "FAST CASE MANAGEMENT",
            "REAL TIME TRACKING",
            "SMART SEARCH",
            "ORGANIZED REPORTS"
        };

        const int pillWidth  = 230;
        const int pillHeight = 44;
        const int pillGap    = 10;
        const int startX     = (1600 - (5 * pillWidth + 4 * pillGap)) / 2;

        for (int i = 0; i < 5; i++)
        {
            QWidget *pill = new QWidget(this);
            pill->setGeometry(startX + i * (pillWidth + pillGap), 348, pillWidth, pillHeight);
            pill->setStyleSheet
            (
                "background : rgba(0, 28, 60, 0.88);"
                "border : 1px solid rgba(0, 230, 255, 0.70);"
                "border-radius : 22px;"
            );

            QLabel *pillLabel = new QLabel(pillLabels[i], pill);
            pillLabel->setGeometry(0, 0, pillWidth, pillHeight);
            pillLabel->setAlignment(Qt::AlignCenter);
            pillLabel->setStyleSheet
            (
                "font-family : 'Courier New', monospace;"
                "font-size : 15px;"
                "font-weight : 900;"
                "letter-spacing : 2px;"
                "color : #ffffff;"
                "background : transparent;"
            );
        }

        Button *accessButton = new Button("SYSTEM ACCESS", 680, 600, 180, 44, this);
        accessButton->raise();

        QLabel *footer = new QLabel("DEPARTMENT OF CRIMINAL JUSTICE    INTERNAL USE ONLY", this);
        footer->setGeometry(0, 862, 1600, 22);
        footer->setAlignment(Qt::AlignCenter);
        footer->setStyleSheet
        (
            "font-family : 'Courier New', monospace;"
            "font-size : 11px;"
            "font-weight : bold;"
            "letter-spacing : 4px;"
            "color : #d5f5ff;"
            "background : rgba(0, 8, 22, 0.65);"
        );

        QObject::connect(accessButton, &QPushButton::clicked, [this]()
            {
                AuthPage *auth = new AuthPage();
                SoundManager::play("accessButtonSound.mp3");
                auth->setAttribute(Qt::WA_DeleteOnClose);
                auth->showMaximized();
                this->close();
            }
        );
    }

    void resizeEvent(QResizeEvent *event) override
    {
        QWidget::resizeEvent(event);
        background->resize(size());
    }
};

#endif
