#ifndef USERMENU_H
#define USERMENU_H

#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QWidget>
#include <QResizeEvent>

#include "common.h"
#include "court.h"
#include "crimeRecords.h"
#include "crimeStatus.h"
#include "file.h"
#include "logout.h"
#include "profile.h"
#include "reports.h"
#include "submitReport.h"
#include "myReport.h"

class User : public QWidget
{
private:

    QLabel  *img;
    Card *menuBar;
    QPushButton *button[9];
    QWidget *previousWindow;
    QString  loggedInEmail;

public:

    User(QWidget *prev = nullptr, const QString &email = "") : previousWindow(prev), loggedInEmail(email)
    {
        setWindowTitle("USER MENU - CRIME RECORD MANAGEMENT SYSTEM");

        img = UI::setupBackground(this, "backgroundThree.png");

        UI::setupSidebar(this, "[ USER ACCESS ]");
        UI::setupPageHeader(this, "USER DASHBOARD", "Select an option from the menu to continue");
        UI::setupFooter(this);

        QLabel *welcomeText = new QLabel("WELCOME,  USER", this);

        welcomeText->setGeometry(380, 250, 1180, 40);
        welcomeText->setAlignment(Qt::AlignCenter);
        welcomeText->setStyleSheet
        (
            MONO +
            "font-size : 36px;"
            "font-weight : bold;"
            "letter-spacing : 6px;"
            "color : #00eaff;"
            "background : transparent;"
        );

        QLabel *welcomeSub = new QLabel("You have access to crime records, case status, reports, and case report submission.", this);

        welcomeSub->setGeometry(380, 300, 1180, 24);
        welcomeSub->setAlignment(Qt::AlignCenter);
        welcomeSub->setStyleSheet
        (
            MONO +
            "font-size : 18px;"
            "color : #c0dff5;"
            "background : transparent;"
            "font-weight : bold;"
        );

        QLabel * footer = new QLabel("DEPARTMENT OF CRIMINAL JUSTICE    |    INTERNAL USE ONLY", this);
        footer->setGeometry(0, 872, 1600, 18);
        footer->setAlignment(Qt::AlignCenter);
        footer->setStyleSheet
        (
            MONO +
            "font-size:14px;"
            "letter-spacing:4px;"
            "color:#7ab8e0;"
            "background:transparent;"
            "font-weight:bold;"
        );

        button[0] = new Button("Crime Records", 25, 155, 270, 40, this);
        button[1] = new Button("Case Status", 25, 210, 270, 40, this);
        button[2] = new Button("Court Proceedings", 25, 265, 270, 40, this);
        button[3] = new Button("Reports", 25, 320, 270, 40, this);
        button[4] = new Button("Submit Report", 25, 375, 270, 40, this);
        button[5] = new Button("My Reports", 25, 430, 270, 40, this);
        button[6] = new Button("Profile", 25, 485, 270, 40, this);
        button[7] = new BackButton(                  25, 540, 270, 40, this);
        button[8] = new ClearButton("LOGOUT", 25, 595, 270, 40, this);

        connect(button[0], &QPushButton::clicked, this, [this]()
            {
                FileHandler::appendLog("USER", "Viewed Crime Records");
                CrimeRecordPage *page = new CrimeRecordPage(false);
                page->setAttribute(Qt::WA_DeleteOnClose);
                page->showMaximized();
            }
        );

        connect(button[1], &QPushButton::clicked, this, [this]()
            {
                FileHandler::appendLog("USER", "Viewed Case Status");
                CaseStatusPage *page = new CaseStatusPage(false);
                page->setAttribute(Qt::WA_DeleteOnClose);
                page->showMaximized();
            }
        );

        connect(button[2], &QPushButton::clicked, this, [this]()
            {
                FileHandler::appendLog("USER", "Viewed Court Proceedings");
                CourtProceedings *page = new CourtProceedings(false);
                page->setAttribute(Qt::WA_DeleteOnClose);
                page->showMaximized();
            }
        );

        connect(button[3], &QPushButton::clicked, this, [this]()
            {
                FileHandler::appendLog("USER", "Viewed Reports & Analytics");
                Reports *page = new Reports();
                page->setAttribute(Qt::WA_DeleteOnClose);
                page->showMaximized();
            }
        );

        connect(button[4], &QPushButton::clicked, this, [this]()
            {
                FileHandler::appendLog("USER", "Opened Submit Case Report");
                SubmitCaseReport *page = new SubmitCaseReport(loggedInEmail);
                page->setAttribute(Qt::WA_DeleteOnClose);
                page->showMaximized();
            }
        );

        connect(button[5], &QPushButton::clicked, this, [this]()
            {
                FileHandler::appendLog("USER", "Opened My Reports");
                MyReports *page = new MyReports(loggedInEmail);
                page->setAttribute(Qt::WA_DeleteOnClose);
                page->showMaximized();
            }
        );

        connect(button[6], &QPushButton::clicked, this, [this]()
            {
                FileHandler::appendLog("USER", "Opened Profile Settings");
                ProfilePage *page = new ProfilePage(loggedInEmail);
                page->setAttribute(Qt::WA_DeleteOnClose);
                page->showMaximized();
            }
        );

        connect(button[7], &QPushButton::clicked, this, [this]()
        {
            FileHandler::appendLog("USER", "Went Back to Login");
            if (previousWindow)
            {
                previousWindow->showMaximized();
            }
            this->close();
        });

        connect(button[8], &QPushButton::clicked, this, [this]()
        {
            FileHandler::appendLog("USER", "Initiated Logout");
            LogoutDialog *dialog = new LogoutDialog(this);
            dialog->setAttribute(Qt::WA_DeleteOnClose);
            dialog->showMaximized();
        });
    }

    void resizeEvent(QResizeEvent * event) override
    {
        img->resize(event->size());
    }
};

#endif