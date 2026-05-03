#ifndef USERMENU_H
#define USERMENU_H

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>

#include "common.h"
#include "crimeRecords.h"
#include "crimeStatus.h"
#include "court.h"
#include "reports.h"
#include "profile.h"

class User : public QWidget
{
private:
    QLabel  *img;
    Card    *menuBar;
    Button  *button[6];
    Button  *logoutButton;
public:

    User()
    {
        setWindowTitle("USER MENU - CRIME RECORD MANAGEMENT SYSTEM");

        img = new QLabel(this);
        img->setPixmap(loadPixmap("backgroundThree.png"));
        img->setScaledContents(true);

        menuBar = new Card(0, 0, 320, 900, this);

        QLabel *title = new QLabel("CRIME RECORD MANAGEMENT\nSYSTEM", this);
        title->setGeometry(0, 30, 320, 60);
        title->setAlignment(Qt::AlignCenter);
        title->setStyleSheet
        (
            MONO +
            "font-size     : 13px;"
            "font-weight   : bold;"
            "letter-spacing: 3px;"
            "color         : #00eaff;"
            "background    : transparent;"
        );

        QLabel *line = new QLabel(this);
        line->setGeometry(30, 100, 260, 1);
        line->setStyleSheet("background: rgba(0,200,255,0.30);");

        QLabel *tag = new QLabel("[ USER  ACCESS ]", this);
        tag->setGeometry(0, 110, 320, 22);
        tag->setAlignment(Qt::AlignCenter);
        tag->setStyleSheet
        (
            MONO +
            "font-size     : 10px;"
            "letter-spacing: 4px;"
            "color         : #7ab8e0;"
            "background    : transparent;"
            "font-weight   : bold;"
        );

        QLabel *pageTitle = new QLabel("USER  DASHBOARD", this);
        pageTitle->setGeometry(380, 40, 900, 50);
        pageTitle->setStyleSheet
        (
            MONO +
            "font-size     : 32px;"
            "font-weight   : 900;"
            "letter-spacing: 6px;"
            "color         : #ffffff;"
            "background    : transparent;"
        );

        QLabel *pageSubtitle = new QLabel("Select an option from the menu to continue", this);
        pageSubtitle->setGeometry(380, 95, 900, 22);
        pageSubtitle->setStyleSheet
        (
            MONO +
            "font-size  : 12px;"
            "color      : #7ab8e0;"
            "background : transparent;"
            "font-weight: bold;"
        );

        QLabel *welcomeText = new QLabel("WELCOME,  USER", this);
        welcomeText->setGeometry(380, 250, 1180, 40);
        welcomeText->setAlignment(Qt::AlignCenter);
        welcomeText->setStyleSheet
        (
            MONO +
            "font-size     : 26px;"
            "font-weight   : bold;"
            "letter-spacing: 6px;"
            "color         : #00eaff;"
            "background    : transparent;"
        );

        QLabel *welcomeSub = new QLabel("You have access to crime records, case status, and reports.", this);
        welcomeSub->setGeometry(380, 300, 1180, 24);
        welcomeSub->setAlignment(Qt::AlignCenter);
        welcomeSub->setStyleSheet
        (
            MONO +
            "font-size  : 13px;"
            "color      : #c0dff5;"
            "background : transparent;"
            "font-weight: bold;"
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

        const char *menuItems[] =
        {
            "  View Crime Records",
            "  View Case Status",
            "  View Court Proceedings",
            "  View Reports",
            "  Profile",
            "  Logout"
        };

        for (int i = 0; i < 6; i++)
        {
            button[i] = new Button(menuItems[i], 25, startY + i * (buttonHeight + gap), buttonWidth, buttonHeight, this);
        }

        button[5]->setStyleSheet
            (
                "QPushButton"
                "{"
                    "background:rgba(80,0,0,0.70);"
                    "color:#ff9999;"
                    "font-family:'Courier New',monospace;"
                    "font-size:13px;"
                    "font-weight:bold;"
                    "letter-spacing:3px;"
                    "border:1px solid rgba(255,80,80,0.45);"
                    "border-radius:6px;"
                    "text-align:left;"
                    "padding-left:14px;"
                "}"
                    "QPushButton:hover"
                "{"
                    "background:rgba(160,0,0,0.80);"
                    "color:#ffffff;"
                    "border:1px solid #ff4444;"
                "}"
                    "QPushButton:pressed"
                "{"
                    "background:#5a0000;"
                "}"
            );

        // 0 — View Crime Records
        connect(button[0], &QPushButton::clicked, this, [=]()
            {
                CrimeRecordPage *page = new CrimeRecordPage(false);
                page->setAttribute(Qt::WA_DeleteOnClose);
                page->showMaximized();
            }
        );

        // 1 — View Case Status
        connect(button[1], &QPushButton::clicked, this, [=]()
            {
                CaseStatusPage *page = new CaseStatusPage(false);
                page->setAttribute(Qt::WA_DeleteOnClose);
                page->showMaximized();
            }
        );

        // 2 — View Court Proceedings
        connect(button[2], &QPushButton::clicked, this, [=]()
            {
                CourtProceedings *page = new CourtProceedings(false);
                page->setAttribute(Qt::WA_DeleteOnClose);
                page->showMaximized();
            }
        );

        // 3 — View Reports
        connect(button[3], &QPushButton::clicked, this, [=]()
            {
                Reports *page = new Reports();
                page->setAttribute(Qt::WA_DeleteOnClose);
                page->showMaximized();
            }
        );

        // 4 — Profile
        connect(button[4], &QPushButton::clicked, this, [=]()
            {
                ProfilePage *page = new ProfilePage();
                page->setAttribute(Qt::WA_DeleteOnClose);
                page->showMaximized();
            }
        );

        //5 - Logout
        connect(button[5], &QPushButton::clicked, this, [=]()
            {
                LogoutDialog *dialog = new LogoutDialog(this);
                dialog->setAttribute(Qt::WA_DeleteOnClose);
                dialog->showMaximized();
            }
        );
    }

    void resizeEvent(QResizeEvent *)
    {
        img->resize(size());
    }
};

#endif