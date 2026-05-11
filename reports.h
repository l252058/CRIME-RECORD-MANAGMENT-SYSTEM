#ifndef REPORTS_H
#define REPORTS_H

#include <QMap>
#include <QDateTime>
#include <QTextStream>

#include "common.h"
#include "file.h"

class Reports : public QWidget
{
private:
    QLabel * pageBg;
    Card * sideCard;
    StatCard * totalCard;
    StatCard * solvedCard;
    StatCard * pendingCard;
    StatCard * coldCard;
    QLabel * reportLabel;
    Button * generateBtn;

public:

    Reports()
    {
        setWindowTitle("Reports & Analytics - CRIME RECORD MANAGEMENT SYSTEM");

        pageBg = new Background(this, "backgroundThree.png");

        sideCard = new Card(0, 0, 320, 900, this);

        QLabel * sideTitleLabel = new QLabel("CRIME RECORD\nMANAGEMENT\nSYSTEM", this);
        sideTitleLabel->setGeometry(10, 10, 300, 120);
        sideTitleLabel->setAlignment(Qt::AlignCenter);
        sideTitleLabel->setWordWrap(true);
        sideTitleLabel->setStyleSheet
        (
            MONO +
            "font-size : 20px; "
            "font-weight : bold; "
            "letter-spacing : 1px; "
            "color : #00eaff; "
            "background : transparent;"
        );

        QLabel * sideDividerLine = new QLabel(this);
        sideDividerLine->setGeometry(30, 100, 260, 1);
        sideDividerLine->setStyleSheet
        (
            "background:rgba(0, 200, 255, 0.30);"
        );

        QLabel * moduleTagLabel = new QLabel("[ ANALYTICS ]", this);
        moduleTagLabel->setGeometry(0, 110, 320, 30);
        moduleTagLabel->setAlignment(Qt::AlignCenter);
        moduleTagLabel->setStyleSheet
        (
            MONO +
            "font-size : 20px; "
            "letter-spacing : 4px; "
            "color : #ffcc44; "
            "font-weight : bold; "
            "background : transparent;"
        );

        QLabel * solvedLegend = new QLabel("SOLVED", this);
        solvedLegend->setGeometry(30, 172, 270, 24);
        solvedLegend->setStyleSheet
        (
            MONO +
            "font-size : 20px; "
            "letter-spacing : 4px; "
            "font-weight : bold;"
            "color : #44ff99; "
            "background : transparent;"
        );

        QLabel * pendingLegend = new QLabel("PENDING", this);
        pendingLegend->setGeometry(30, 202, 270, 24);
        pendingLegend->setStyleSheet
        (
            MONO +
            "font-size : 20px; "
            "letter-spacing : 4px; "
            "font-weight : bold;"
            "color : #ffcc44; "
            "background : transparent;"
        );

        QLabel * coldLegend = new QLabel("COLD", this);
        coldLegend->setGeometry(30, 232, 270, 24);
        coldLegend->setStyleSheet
        (
            MONO +
            "font-size : 20px; "
            "letter-spacing : 4px; "
            "font-weight : bold;"
            "color : #ff6666; "
            "background : transparent;"
        );

        totalCard = new StatCard(380, 140, "#00eaff", "TOTAL CASES", this);
        solvedCard = new StatCard(700, 140, "#44ff99", "SOLVED", this);
        pendingCard = new StatCard(1000, 140, "#ffcc44", "PENDING", this);
        coldCard = new StatCard(1300, 140, "#ff6666", "COLD CASES", this);

        generateBtn = new Button("GENERATE REPORT", 25, 300, 270, 40, this);

        BackButton * backButton = new BackButton(25, 360, 270, 44, this);
        backButton->raise();

        QObject::connect(backButton, &QPushButton::clicked, [this]()
        {
            this->close();
        });

        QLabel * headerTitleLabel = new QLabel("REPORTS & ANALYTICS", this);
        headerTitleLabel->setGeometry(380, 40, 1180, 50);
        headerTitleLabel->setStyleSheet
        (
            MONO +
            "font-size : 44px; "
            "font-weight : bold; "
            "letter-spacing : 12px; "
            "color : #ffffff; "
            "background : transparent;"
        );

        QLabel * headerSubtitleLabel = new QLabel("Deep dive into criminal data and case distributions.", this);
        headerSubtitleLabel->setGeometry(380, 95, 1180, 24);
        headerSubtitleLabel->setStyleSheet
        (
            MONO +
            "font-size : 18px; "
            "color : #7ab8e0; "
            "background : transparent; "
            "font-weight : bold;"
        );
        
        QLabel * reportHeadingLabel = new QLabel("  DETAILED REPORT", this);
        reportHeadingLabel->setGeometry(380, 252, 800, 28);
        reportHeadingLabel->setStyleSheet
        (
            MONO +
            "font-size : 18px; "
            "font-weight : bold; "
            "color : #00eaff; "
            "background : transparent;"
        );

        QScrollArea * reportScroll = new QScrollArea(this);
        reportScroll->setGeometry(380, 288, 1140, 480);
        reportScroll->setWidgetResizable(true);
        reportScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        reportScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        reportScroll->setStyleSheet
        (
            "QScrollArea { background:rgba(3, 12, 35, 0.95); border:1px solid rgba(0, 234, 255, 0.35); border-radius:15px; }"
        );

        reportLabel = new QLabel();
        reportLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        reportLabel->setWordWrap(true);
        reportLabel->setStyleSheet
        (
            MONO +
            "font-size  : 18px; "
            "font-weight: bold; "
            "color      : #c0dff5;"
            "background : transparent; "
            "padding    : 20px;"
        );
        
        reportLabel->setText("  Click  Generate Report  to load analytics.");
        reportScroll->setWidget(reportLabel);

        QLabel * footerLabel = new QLabel("DEPARTMENT OF CRIMINAL JUSTICE    INTERNAL USE ONLY", this);
        footerLabel->setGeometry(0, 872, 1600, 18);
        footerLabel->setAlignment(Qt::AlignCenter);
        footerLabel->setStyleSheet
        (
            MONO +
            "font-size : 14px; "
            "letter-spacing : 4px; "
            "color : #7ab8e0;"
            "background : transparent; "
            "font-weight : bold;"
        );

        connect(generateBtn, &QPushButton::clicked, this, [=]()
        {
            // ── Data Gathering ───────────────────────────────────────────────
            int solvedCount  = FileHandler::countByStatus("Solved");
            int pendingCount = FileHandler::countByStatus("Pending");
            int coldCount    = FileHandler::countByStatus("Cold");
            int totalCount   = solvedCount + pendingCount + coldCount;

            totalCard->setValue(totalCount);
            solvedCard->setValue(solvedCount);
            pendingCard->setValue(pendingCount);
            coldCard->setValue(coldCount);

            QMap<QString, int> typeStats = FileHandler::getCrimeTypeStatistics();
            QMap<QString, int> locStats  = FileHandler::getLocationStatistics();

            int offAssigned = FileHandler::countAssignedOfficers();
            int offFree     = FileHandler::countUnassignedOfficers();
            int courtOn     = FileHandler::countCourtByStatus("Ongoing");
            int users       = FileHandler::countUsers();

            // ── Report Building (C++ "cout" Style) ────────────────────────────
            QString finalReport;
            QTextStream out(&finalReport);

            QString sep = "  " + QString(66, '=') + "\n";
            QString div = "  " + QString(66, '-') + "\n";
            QString ts  = QDateTime::currentDateTime().toString("yyyy-MM-dd  hh:mm:ss");

            out << sep;
            out << "    CRIME RECORD MANAGEMENT SYSTEM  —  SYSTEM REPORT\n";
            out << "    Generated : " << ts << "\n";
            out << sep << "\n";

            out << "    CASE OVERVIEW\n";
            out << div;
            
            auto getP = [&](int c)
            {
                if (totalCount > 0)
                {
                    return QString::number(c * 100 / totalCount) + "%";
                }
                return QString("0%");
            };

            out << "    " << QString("Total Cases").leftJustified(22, ' ')   << ": " << totalCount   << "\n";
            out << "    " << QString("Solved Cases").leftJustified(22, ' ')  << ": " << solvedCount  << "  (" << getP(solvedCount) << ")\n";
            out << "    " << QString("Pending Cases").leftJustified(22, ' ') << ": " << pendingCount << "  (" << getP(pendingCount) << ")\n";
            out << "    " << QString("Cold Cases").leftJustified(22, ' ')    << ": " << coldCount    << "  (" << getP(coldCount) << ")\n\n";

            out << "    BREAKDOWN BY CRIME TYPE\n";
            out << div;

            if (typeStats.isEmpty())
            {
                out << "    No records found.\n";
            }
            else
            {
                for (auto it = typeStats.cbegin(); it != typeStats.cend(); ++it)
                {
                    out << "    " << it.key().leftJustified(30, ' ') << " : " << it.value() << " case(s)\n";
                }
            }

            out << "\n    OFFICER & COURT SUMMARY\n";
            out << div;
            out << "    " << QString("Total Officers").leftJustified(22, ' ') << ": " << (offAssigned + offFree) << "\n";
            out << "    " << QString("Ongoing Cases").leftJustified(22, ' ')  << ": " << courtOn << "\n";
            out << "    " << QString("Registered Users").leftJustified(22, ' ') << ": " << users << "\n\n";

            out << sep;
            out << "    END OF REPORT\n";
            out << sep;

            reportLabel->setText(finalReport);
        });
    }

    void resizeEvent(QResizeEvent *)
    {
        pageBg->setGeometry(0, 0, width(), height());
    }
};

#endif // REPORTS_H