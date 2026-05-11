#ifndef MYREPORT_H
#define MYREPORT_H

#include "common.h"
#include "file.h"
#include "submitReport.h"

class MyReports : public QWidget
{
private:

    QLabel *pageBackground;
    StatCard *pendingCount;
    StatCard *approvedCount;
    StatCard *rejectedCount;
    QWidget *scrollContent;
    QVBoxLayout *scrollLayout;
    QString loggedInEmail;

    QWidget *makeReportCard(const QStringList &reportParts)
    {
        QString reportId = reportParts.value(0, "—");
        QString caseRef = reportParts.value(2, "—");
        QString subject = reportParts.value(3, "—");
        QString body = reportParts.value(4, "—");
        QString status = reportParts.value(5, "Pending");
        QString adminComment = reportParts.value(6, "").trimmed();

        QString statusColor = "#ffcc44";
        if (status == "Approved")
        {
            statusColor = "#44ff99";
        }
        if (status == "Rejected")
        {
            statusColor = "#ff6666";
        }

        Card *card = new Card(0, 0, 500, 100, nullptr);

        QLabel *statusBadge = new QLabel(status.toUpper(), card);
        statusBadge->setGeometry(1000, 14, 120, 26);
        statusBadge->setAlignment(Qt::AlignCenter);
        statusBadge->setStyleSheet
        (
            MONO +
            "font-size : 12px; "
            "font-weight : bold; "
            "color : #000000; "
            "background : " + statusColor + "; "
            "border-radius : 4px;"
        );

        QLabel *idLabel = new QLabel("  Report ID : " + reportId, card);
        idLabel->setGeometry(14, 14, 980, 24);
        idLabel->setStyleSheet
        (
            MONO + 
            "font-size : 14px; "
            "color : #7ab8e0; "
            "background : transparent; "
            "font-weight: bold;"
        );

        QLabel *referenceLabel = new QLabel("  Case Ref : " + caseRef, card);
        referenceLabel->setGeometry(14, 44, 980, 24);
        referenceLabel->setStyleSheet
        (
            MONO + 
            "font-size : 16px; "
            "color : #00eaff; "
            "background : transparent; "
            "font-weight: bold;"
        );

        QLabel *subjectLabel = new QLabel("  Subject   : " + subject, card);
        subjectLabel->setGeometry(14, 74, 980, 24);
        subjectLabel->setStyleSheet
        (
            MONO + 
            "font-size : 16px; "
            "color : #ffffff; "
            "background : transparent; "
            "font-weight: bold;"
        );

        QString bodyShort = (body.length() > 140) ? body.left(140) + "..." : body;
        QLabel *detailsLabel = new QLabel("  Details   : " + bodyShort, card);
        detailsLabel->setGeometry(14, 104, 980, 24);
        detailsLabel->setStyleSheet
        (
            MONO + 
            "font-size : 15px; "
            "color : #c0dff5; "
            "background : transparent;"
        );

        QLabel *dividerLine = new QLabel(card);
        dividerLine->setGeometry(14, 136, 1100, 1);
        dividerLine->setStyleSheet("background : rgba(0, 200, 255, 0.15);");

        QString responseText = adminComment.isEmpty() ? "Awaiting review..." : adminComment;
        QLabel *responseLabel = new QLabel("  Admin Response : " + responseText, card);
        responseLabel->setGeometry(14, 146, 1100, 44);
        responseLabel->setWordWrap(true);
        responseLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        responseLabel->setStyleSheet
        (
            MONO + 
            "font-size : 16px; "
            "color : " + statusColor + "; "
            "background : transparent; "
            "font-weight: bold;"
        );

        return card;
    }

    void loadReports()
    {
        QLayoutItem *layoutItem;
        while ((layoutItem = scrollLayout->takeAt(0)) != nullptr) 
        {
            if (layoutItem->widget()) layoutItem->widget()->deleteLater();
            delete layoutItem;
        }

        const QList<QStringList> reports = UserReportFile::loadByEmail(loggedInEmail);

        int pending = 0, approved = 0, rejected = 0;
        for (const QStringList &r : reports) 
        {
            QString status = r.value(5).trimmed();
            if (status == "Pending")  pending++;
            if (status == "Approved") approved++;
            if (status == "Rejected") rejected++;
        }

        pendingCount->setValue(pending);
        approvedCount->setValue(approved);
        rejectedCount->setValue(rejected);

        if (reports.isEmpty()) 
        {
            QLabel *emptyLabel = new QLabel("  You have not submitted any reports yet.");
            emptyLabel->setFixedHeight(60);
            emptyLabel->setStyleSheet(MONO + "font-size : 16px; color : #7ab8e0; background : transparent;");
            scrollLayout->addWidget(emptyLabel);
        } 
        else 
        {
            for (int i = reports.size() - 1; i >= 0; i--) 
            {
                scrollLayout->addWidget(makeReportCard(reports[i]));
            }
        }
        scrollLayout->addStretch();
    }

public:

    MyReports(const QString &email = "") : QWidget(nullptr), loggedInEmail(email)
    {
        setWindowTitle("My Case Reports — CRIME RECORD MANAGEMENT SYSTEM");

        pageBackground = new Background(this, "backgroundThree.png");

        new Sidebar(this, "[ MY REPORTS ]");
        new PageHeader(this, "MY SUBMITTED REPORTS", "Track the status of your submitted reports and view official responses.");
        new Footer(this);

        BackButton *backNavigation = new BackButton(25, 155, 270, 44, this);
        backNavigation->raise();
        connect(backNavigation, &QPushButton::clicked, this, &QWidget::close);

        Button *refreshButton = new Button("REFRESH", 25, 215, 270, 40, this);
        refreshButton->setSound("refreshButtonSound.mp3");
        connect(refreshButton, &QPushButton::clicked, this, &MyReports::loadReports);

        pendingCount  = new StatCard(380, 150, "#ffcc44", "PENDING",  this);
        approvedCount = new StatCard(800, 150, "#44ff99", "APPROVED", this);
        rejectedCount = new StatCard(1300, 150, "#ff6666", "REJECTED", this);

        QLabel *listTitle = new QLabel("  REPORT HISTORY", this);
        listTitle->setGeometry(380, 252, 600, 28);
        listTitle->setStyleSheet(MONO + "font-size : 18px; font-weight : bold; color : #00eaff; background : transparent;");

        QScrollArea *scrollArea = new QScrollArea(this);
        scrollArea->setGeometry(380, 288, 1050, 475);
        scrollArea->setWidgetResizable(true);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setStyleSheet
        (
            "QScrollArea"
            "{"
                "background:rgba(3, 12, 35, 0.95);"
                "border:1px solid rgba(0, 234, 255, 0.35);"
                "border-radius: 15px; "
            "}"
        );

        scrollContent = new QWidget();
        scrollContent->setStyleSheet("background:transparent;");
        
        scrollLayout = new QVBoxLayout(scrollContent);
        scrollLayout->setContentsMargins(15, 15, 15, 15);
        scrollLayout->setSpacing(12);
        
        scrollArea->setWidget(scrollContent);

        loadReports();
    }

    void setEmail(const QString &email)
    {
        loggedInEmail = email;
        loadReports();
    }
    void resizeEvent(QResizeEvent *) override
    {
        pageBackground->resize(size());
    }
};

#endif