#ifndef ADMINMENU_H
#define ADMINMENU_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>

#include "common.h"
#include "file.h"
#include "crimeRecords.h"
#include "crimeStatus.h"
#include "court.h"
#include "reports.h"
#include "officer.h"
#include "activityLog.h"
#include "adminReport.h"
#include "logout.h"

class Admin : public QWidget
{
private:
    QLabel *img;

    QPushButton *button[9];

    QWidget *previousWindow;

public:
    Admin(QWidget *prev = nullptr) : previousWindow(prev)
    {
        setWindowTitle("ADMIN MENU - CRIME RECORD MANAGEMENT SYSTEM");

        img = UI::setupBackground(this, "backgroundThree.png");

        UI::setupSidebar(this, "[ ADMIN ACCESS ]");
        UI::setupPageHeader(this, "ADMIN DASHBOARD", "Full system control — select an option from the menu");
        UI::setupFooter(this);

        QLabel *welcomeText = new QLabel("WELCOME,  ADMINISTRATOR", this);
        welcomeText->setGeometry(380, 250, 1180, 40);
        welcomeText->setAlignment(Qt::AlignCenter);
        welcomeText->setStyleSheet
        (
            MONO +
            "font-size : 32px;"
            "font-weight : bold;"
            "letter-spacing : 6px;"
            "color : #ffcc44;"
            "background : transparent;"
        );

        QLabel *welcomeSub = new QLabel("You have full access to manage records, officers, reports, and users.", this);
        welcomeSub->setGeometry(380, 300, 1180, 24);
        welcomeSub->setAlignment(Qt::AlignCenter);
        welcomeSub->setStyleSheet
        (
            MONO +
            "font-size : 16px;"
            "color : #c0dff5;"
            "background : transparent;"
            "font-weight: bold;"
        );

        // Sidebar Buttons standardized using specific classes
        button[0] = new Button("Manage Records",     25, 170, 270, 40, this);
        button[1] = new Button("Manage Officers",    25, 230, 270, 40, this);
        button[2] = new Button("Case Status",        25, 290, 270, 40, this);
        button[3] = new Button("Court Proceedings",  25, 350, 270, 40, this);
        button[4] = new Button("Reports & Analytics", 25, 410, 270, 40, this);
        button[5] = new Button("User Review",        25, 470, 270, 40, this);
        button[6] = new Button("Activity Logs",       25, 530, 270, 40, this);
        
        button[7] = new BackButton(                  25, 590, 270, 40, this);
        button[8] = new ClearButton("LOGOUT",        25, 650, 270, 40, this);

        connect(button[0], &QPushButton::clicked, this, [=]()
            {
                FileHandler::appendLog("ADMIN", "Opened Manage Records");
                CrimeRecordPage *page = new CrimeRecordPage(true);
                page->setAttribute(Qt::WA_DeleteOnClose);
                page->showMaximized();
            }
        );

        connect(button[1], &QPushButton::clicked, this, [=]()
            {
                FileHandler::appendLog("ADMIN", "Opened Manage Officers");
                Officers *page = new Officers(true);
                page->setAttribute(Qt::WA_DeleteOnClose);
                page->showMaximized();
            }
        );

        connect(button[2], &QPushButton::clicked, this, [=]()
            {
                FileHandler::appendLog("ADMIN", "Opened Case Status");
                CaseStatusPage *page = new CaseStatusPage(true);
                page->setAttribute(Qt::WA_DeleteOnClose);
                page->showMaximized();
            }
        );

        connect(button[3], &QPushButton::clicked, this, [=]()
            {
                FileHandler::appendLog("ADMIN", "Opened Court Proceedings");
                CourtProceedings *page = new CourtProceedings(true);
                page->setAttribute(Qt::WA_DeleteOnClose);
                page->showMaximized();
            }
        );

        connect(button[4], &QPushButton::clicked, this, [=]()
            {
                FileHandler::appendLog("ADMIN", "Opened Reports & Analytics");
                Reports *page = new Reports();
                page->setAttribute(Qt::WA_DeleteOnClose);
                page->showMaximized();
            }
        );

        connect(button[5], &QPushButton::clicked, this, [=]()
            {
                FileHandler::appendLog("ADMIN", "Opened User Review");
                AdminReports *page = new AdminReports();
                page->setAttribute(Qt::WA_DeleteOnClose);
                page->showMaximized();
            }
        );

        connect(button[6], &QPushButton::clicked, this, [=]()
            {
                FileHandler::appendLog("ADMIN", "Opened Activity Logs");
                ActivityLogs *page = new ActivityLogs();
                page->setAttribute(Qt::WA_DeleteOnClose);
                page->showMaximized();
            }
        );

        connect(button[7], &QPushButton::clicked, this, [=]()
            {
                if (previousWindow)
                {
                    previousWindow->showMaximized();
                }
                this->close();
            }
        );

        connect(button[8], &QPushButton::clicked, this, [=]()
            {
                LogoutDialog *logout = new LogoutDialog(this);
                logout->showMaximized();
            }
        );
    }

    void resizeEvent(QResizeEvent * event) override
    {
        img->resize(event->size());
    }
};

#endif