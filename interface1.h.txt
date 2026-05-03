#ifndef INTERFACE1_H
#define INTERFACE1_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>

#include "common.h"
#include "Interface2.h"

class LandingPage : public QWidget
{
private:

    QLabel *background;   // making it memebr to achieve the resizing

public:

    LandingPage()
    {
        setObjectName("mainWindow");
        setWindowTitle("Crime Record Management System");

        background = new QLabel(this);
        background->setScaledContents(true);
        background->setPixmap(loadPixmap("backgroundOne.png"));
        background->lower();

        QLabel *topLine = new QLabel("[ TOP SECRET   CLASSIFIED SYSTEM ]", this);
        topLine->setGeometry(0, 42, 1600, 20);
        topLine->setAlignment(Qt::AlignCenter);
        topLine->setStyleSheet
        (
            "font-family: 'Courier New', monospace;"
            "font-size: 11px;"
            "letter-spacing: 7px;"
            "color: #00dcff;"
            "background: transparent;"
        );

        QLabel *title = new QLabel("CRIME Record MANAGEMENT\nSYSTEM", this);
        title->setGeometry(100, 75, 1400, 210);
        title->setAlignment(Qt::AlignCenter);
        title->setStyleSheet
        (
            "font-family: 'Courier New', monospace;"
            "font-size: 66px;"
            "font-weight: 900;"
            "color: #ffffff;"
            "background: transparent;"
        );

        QLabel *subtitle = new QLabel("SECURE ACCESS PORTAL   AUTHORIZED PERSONNEL ONLY", this);
        subtitle->setGeometry(100, 300, 1400, 26);
        subtitle->setAlignment(Qt::AlignCenter);
        subtitle->setStyleSheet
        (
            "font-family: 'Courier New', monospace;"
            "font-size: 14px;"
            "letter-spacing: 5px;"
            "color: #c8eaff;"
            "background: transparent;"
        );

        const QString pillLabels[] =
        {
            QString::fromUtf8("🛡 Secure Data"),
            QString::fromUtf8("⚡ Fast Case Management"),
            QString::fromUtf8("📊 Real Time Tracking"),
            QString::fromUtf8("🔎 Smart Search"),
            QString::fromUtf8("📈 Organized Reports")
        };

        const int pillWidth  = 230;
        const int pillHeight = 44;
        const int gap        = 10;
        const int startX     = (1600 - (5 * pillWidth + 4 * gap)) / 2;

        for (int i = 0; i < 5; i++)
        {
            QWidget *pill = new QWidget(this);
            pill->setGeometry(startX + i * (pillWidth + gap), 338, pillWidth, pillHeight);
            pill->setStyleSheet
            (
                "background: rgba(0, 50, 90, 0.70);"
                "border: 1px solid rgba(0, 200, 255, 0.45);"
                "border-radius: 22px;"
            );

            QLabel *pillLabel = new QLabel(pillLabels[i], pill);
            pillLabel->setGeometry(0, 0, pillWidth, pillHeight);
            pillLabel->setAlignment(Qt::AlignCenter);
            pillLabel->setStyleSheet
            (
                "font-family: 'Courier New', monospace;"
                "font-size: 13px;"
                "color: #e8f6ff;"
                "background: transparent;"
            );
        }

        Button *accessButton = new Button("SYSTEM ACCESS", 680, 600, 160, 40, this);
        accessButton->raise();

        QLabel *footer = new QLabel("DEPARTMENT OF CRIMINAL JUSTICE    INTERNAL USE ONLY", this);
        footer->setGeometry(0, 862, 1600, 18);
        footer->setAlignment(Qt::AlignCenter);
        footer->setStyleSheet
        (
            "font-family: 'Courier New', monospace;"
            "font-size: 10px;"
            "letter-spacing: 4px;"
            "color: #7ab8e0;"
            "background: transparent;"
        );

        QObject::connect(accessButton, &QPushButton::clicked, [this]()
        {
            AuthPage *auth = new AuthPage();
            auth->setAttribute(Qt::WA_DeleteOnClose);
            auth->showMaximized();
            this->close();
        });
    }

    void resizeEvent(QResizeEvent *)
    {
        background->resize(size());
    }
};

#endif