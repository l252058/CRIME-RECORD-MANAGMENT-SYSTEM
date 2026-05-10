#ifndef REPORTS_H
#define REPORTS_H

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QMap>
#include <QDateTime>
#include <QScrollArea>

#include "common.h"
#include "file.h"

// =============================================================================
//  Helper — left-pad a QString to a fixed width
// =============================================================================

static QString padRight(const QString &text, int width)
{
    return text.leftJustified(width, ' ');
}

// =============================================================================
//  REPORTS PAGE
// =============================================================================

class Reports : public QWidget
{
private:

    QLabel  *img;
    Card    *sideCard;

    StatCard *totalNumber;
    StatCard *solvedNumber;
    StatCard *pendingNumber;
    StatCard *coldNumber;


    QLabel  *reportCard;
    Button  *generateBtn;

public:

    Reports()
    {
        setWindowTitle("Reports & Analytics - CRIME RECORD MANAGEMENT SYSTEM");

        // ── Background ────────────────────────────────────────────────────────

        img = new QLabel(this);
        
        img->setPixmap(loadPixmap("backgroundThree.png"));
        
        img->setScaledContents(true);

        // ── Sidebar ──────────────────────────────────────────────────────────

        sideCard = new Card(0, 0, 320, 900, this);

        QLabel * sideTitle = new QLabel("CRIME RECORD\nMANAGEMENT\nSYSTEM", this);
        sideTitle->setGeometry(10, 10, 300, 120);
        sideTitle->setAlignment(Qt::AlignCenter);
        sideTitle->setWordWrap(true);
        sideTitle->setStyleSheet(MONO + "font-size:20px; font-weight:bold; letter-spacing:1px; color:#00eaff; background:transparent;");

        QLabel * dividerOne = new QLabel(this);
        dividerOne->setGeometry(30, 100, 260, 1);
        dividerOne->setStyleSheet("background:rgba(0,200,255,0.30);");

        QLabel * tag = new QLabel("[ REPORTS & ANALYTICS ]", this);
        tag->setGeometry(0, 110, 320, 30);
        tag->setAlignment(Qt::AlignCenter);
        tag->setStyleSheet(MONO + "font-size:18px; letter-spacing:4px; color:#ffcc44; font-weight:bold; background:transparent;");

        // ── Sidebar legend labels ─────────────────────────────────────────────

        auto makeLegLabel = [&](const QString &text, int y, const QString &color)
        {
            QLabel *lbl = new QLabel(text, this);
            
            lbl->setGeometry(30, y, 270, 22);
            
            lbl->setStyleSheet
            (
                MONO +
                "font-size      : 16px; "
                "letter-spacing : 4px; "
                "font-weight    : bold;"
                "color          : " + color + "; "
                "background     : transparent;"
            );
        };

        makeLegLabel("SOLVED",  172, "#44ff99");
        makeLegLabel("PENDING", 200, "#ffcc44");
        makeLegLabel("COLD",    228, "#ff6666");
        totalNumber   = new StatCard(380,  140, "#00eaff", "TOTAL CASES", this);
        solvedNumber  = new StatCard(690,  140, "#44ff99", "SOLVED",      this);
        pendingNumber = new StatCard(1000, 140, "#ffcc44", "PENDING",     this);
        coldNumber    = new StatCard(1310, 140, "#ff6666", "COLD CASES",  this);

        generateBtn = new Button("GENERATE REPORT", 25, 300, 270, 40, this);

        BackButton *bb = new BackButton(25, 360, 270, 44, this);
        bb->raise();

        QObject::connect(bb, &QPushButton::clicked, [this]() { this->close(); });

        // ── Page header ───────────────────────────────────────────────────────

        QLabel * pageTitle = new QLabel("REPORTS & ANALYTICS", this);
        pageTitle->setGeometry(380, 40, 1180, 50);
        pageTitle->setStyleSheet(MONO + "font-size : 44px; font-weight : bold; letter-spacing : 12px; color : #ffffff; background : transparent;");

        QLabel * pageSub = new QLabel("Deep-dive into criminal data and case distributions.", this);
        pageSub->setGeometry(380, 95, 1180, 24);
        pageSub->setStyleSheet(MONO + "font-size : 18px; color : #7ab8e0; background : transparent; font-weight: bold;");

        // ── Report display area ───────────────────────────────────────────────

        QLabel *reportHeading = new QLabel("  DETAILED REPORT", this);
        
        reportHeading->setGeometry(380, 252, 800, 28);
        
        reportHeading->setStyleSheet
        (
            MONO +
            "font-size   : 18px; "
            "font-weight : bold; "
            "color       : #00eaff; "
            "background  : transparent;"
        );

        QScrollArea *scrollArea = new QScrollArea(this);
        
        scrollArea->setGeometry(380, 288, 1140, 480);
        
        scrollArea->setWidgetResizable(true);
        
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        
        scrollArea->setStyleSheet
        (
            "QScrollArea { background:rgba(3, 12, 35, 0.95); border:1px solid rgba(0, 234, 255, 0.35); border-radius:15px; }"
            "QScrollBar:vertical { background:rgba(0,15,45,0.80); width:8px; border-radius:4px; }"
            "QScrollBar::handle:vertical { background:rgba(0,234,255,0.40); border-radius:4px; }"
            "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height:0px; }"
        );

        reportCard = new QLabel();
        
        reportCard->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        
        reportCard->setWordWrap(true);
        
        reportCard->setStyleSheet
        (
            MONO +
            "font-size   : 18px; "
            "font-weight : bold; "
            "color       : #c0dff5;"
            "background  : transparent; "
            "padding     : 20px;"
        );
        
        reportCard->setText("  Click  Generate Report  to load analytics.");

        scrollArea->setWidget(reportCard);

        // ── Footer ────────────────────────────────────────────────────────────

        QLabel *footer = new QLabel("DEPARTMENT OF CRIMINAL JUSTICE    INTERNAL USE ONLY", this);
        
        footer->setGeometry(0, 872, 1600, 18);
        
        footer->setAlignment(Qt::AlignCenter);
        
        footer->setStyleSheet
        (
            MONO +
            "font-size      : 14px; "
            "letter-spacing : 4px; "
            "color          : #7ab8e0;"
            "background     : transparent; "
            "font-weight    : bold;"
        );

        // ── Generate button connection ─────────────────────────────────────────

        connect(generateBtn, &QPushButton::clicked, this, [=]()
        {
            const QStringList records = FileHandler::loadRecords();

            int total   = records.size();
            int solved  = 0;
            int pending = 0;
            int cold    = 0;

            QMap<QString, int> crimeTypeCount;
            QMap<QString, int> locationCount;

            for (const QString &line : records)
            {
                QStringList p = line.split("\t");

                if (p.size() < 5) 
                {
                    continue;
                }

                QString status   = p[4].trimmed().toLower();
                QString type     = p[2].trimmed();
                QString location = p[1].trimmed();

                if (status == "solved")
                {
                    solved++;
                }
                else if (status == "pending")
                {
                    pending++;
                }
                else if (status == "cold")
                {
                    cold++;
                }

                if (!type.isEmpty())
                {
                    crimeTypeCount[type]++;
                }
                
                if (!location.isEmpty())
                {
                    locationCount[location]++;
                }
            }

            totalNumber   ->setValue(total);
        solvedNumber  ->setValue(solved);
        pendingNumber ->setValue(pending);
        coldNumber    ->setValue(cold);

            int assignedOfficers   = FileHandler::countAssignedOfficers();
            int unassignedOfficers = FileHandler::countUnassignedOfficers();
            int totalOfficers      = assignedOfficers + unassignedOfficers;

            int courtOngoing = FileHandler::countCourtByStatus("Ongoing");
            int courtOnHold  = FileHandler::countCourtByStatus("On Hold");
            int courtVerdict = FileHandler::countCourtByStatus("Verdict Reached");

            int userCount = FileHandler::countUsers();
            int userReports = FileHandler::countUserReports();

            QString ts  = QDateTime::currentDateTime().toString("yyyy-MM-dd  hh:mm:ss");
            QString sep = "  " + QString(66, '=') + "\n";
            QString div = "  " + QString(66, '-') + "\n";

            QString report;

            report += sep;
            report += "    CRIME RECORD MANAGEMENT SYSTEM  —  SYSTEM REPORT\n";
            report += "    Generated : " + ts + "\n";
            report += sep + "\n";

            report += "    CASE OVERVIEW\n";
            report += div;

            auto pct = [&](int n) -> QString
            {
                if (total > 0)
                {
                    return QString::number(n * 100 / total) + "%";
                }
                else
                {
                    return "0%";
                }
            };

            report += "    " + padRight("Total Cases", 22) + ": " + QString::number(total)   + "\n";
            report += "    " + padRight("Solved",      22) + ": " + QString::number(solved)  + "  (" + pct(solved)  + ")\n";
            report += "    " + padRight("Pending",     22) + ": " + QString::number(pending) + "  (" + pct(pending) + ")\n";
            report += "    " + padRight("Cold",        22) + ": " + QString::number(cold)    + "  (" + pct(cold)    + ")\n\n";

            report += "    BREAKDOWN BY CRIME TYPE\n";
            report += div;

            if (crimeTypeCount.isEmpty())
            {
                report += "    No records found.\n";
            }
            else
            {
                for (auto it = crimeTypeCount.cbegin(); it != crimeTypeCount.cend(); ++it)
                {
                    report += "    " + padRight(it.key(), 30) + ": " + QString::number(it.value()) + " case(s)\n";
                }
            }

            report += "\n";

            report += "    BREAKDOWN BY LOCATION\n";
            report += div;

            if (locationCount.isEmpty())
            {
                report += "    No records found.\n";
            }
            else
            {
                for (auto it = locationCount.cbegin(); it != locationCount.cend(); ++it)
                {
                    report += "    " + padRight(it.key(), 30) + ": " + QString::number(it.value()) + " case(s)\n";
                }
            }

            report += "\n";

            report += "    OFFICER SUMMARY\n";
            report += div;
            report += "    " + padRight("Total Officers",    22) + ": " + QString::number(totalOfficers)      + "\n";
            report += "    " + padRight("Assigned to Cases", 22) + ": " + QString::number(assignedOfficers)   + "\n";
            report += "    " + padRight("Unassigned",        22) + ": " + QString::number(unassignedOfficers) + "\n\n";

            report += "    COURT PROCEEDINGS SUMMARY\n";
            report += div;
            report += "    " + padRight("Ongoing",         22) + ": " + QString::number(courtOngoing) + "\n";
            report += "    " + padRight("On Hold",         22) + ": " + QString::number(courtOnHold)  + "\n";
            report += "    " + padRight("Verdict Reached", 22) + ": " + QString::number(courtVerdict) + "\n\n";

            report += "    REGISTERED USER ACCOUNTS\n";
            report += div;
            report += "    " + padRight("Total Users",       22) + ": " + QString::number(userCount)    + "\n";
            report += "    " + padRight("User Case Reports",  22) + ": " + QString::number(userReports)  + "\n\n";

            report += sep;
            report += "    END OF REPORT\n";
            report += sep;

            reportCard->setText(report);
            
            FileHandler::appendLog("ADMIN", "Generated system report");
        });
    }

    void resizeEvent(QResizeEvent *)
    {
        img->resize(size());
    }
};

#endif // REPORTS_H