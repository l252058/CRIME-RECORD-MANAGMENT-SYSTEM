#ifndef ADMINREPORTS_H
#define ADMINREPORTS_H

#include <QResizeEvent>
#include <QLayoutItem>
#include "common.h"
#include "file.h"
#include "submitReport.h"

class AdminReports : public QWidget
{
private:

    QLabel *pageBackground;
    StatCard *totalCount;
    StatCard *pendingCount;
    StatCard *approvedCount;
    StatCard *rejectedCount;
    QWidget *scrollContent;
    QVBoxLayout *scrollLayout;
    Button *allFilter;
    Button *pendingFilter;
    Button *approvedFilter;
    Button *rejectedFilter;
    BackButton *backNavigation;
    QString activeFilter = "All";

    QWidget *makeReviewCard(const QStringList &reportParts)
    {
        QString reportId = reportParts.value(0, "—");
        QString email = reportParts.value(1, "—");
        QString caseRef = reportParts.value(2, "—");
        QString subject = reportParts.value(3, "—");
        QString body = reportParts.value(4, "—");
        QString status = reportParts.value(5, "Pending");
        QString adminComment = reportParts.value(6, "").trimmed();

        bool alreadyActioned = (status == "Approved" || status == "Rejected");

        QString statusColor = "#ffcc44";
        if (status == "Approved")
        {
            statusColor = "#44ff99";
        }
        if (status == "Rejected")
        {
            statusColor = "#ff6666";
        }
        Card *card = new Card(0, 0, 1100, (alreadyActioned ? 200 : 240), nullptr);

        QLabel *statusBadge = new QLabel(status.toUpper(), card);
        statusBadge->setGeometry(960, 14, 120, 26);
        statusBadge->setAlignment(Qt::AlignCenter);
        statusBadge->setStyleSheet
        (
            MONO +
            "font-size  : 11px; "
            "font-weight : bold; "
            "color : #000000; "
            "background: " + statusColor + "; "
            "border-radius : 4px;"
        );

        QLabel *idLabel = new QLabel("  ID: " + reportId + "   |   From: " + email, card);
        idLabel->setGeometry(14, 14, 900, 22);
        idLabel->setStyleSheet
        (
            MONO +
            "font-size : 11px; "
            "color : #7ab8e0; "
            "background : transparent;"
        );

        QLabel *referenceLabel = new QLabel("  Case Ref : " + caseRef, card);
        referenceLabel->setGeometry(14, 40, 500, 22);
        referenceLabel->setStyleSheet
        (
            MONO +
            "font-size : 13px; "
            "font-weight : bold; "
            "color : #00eaff; "
            "background : transparent;"
        );

        QLabel *subjectLabel = new QLabel("  Subject  : " + subject, card);
        subjectLabel->setGeometry(14, 68, 1000, 22);
        subjectLabel->setStyleSheet
        (
            MONO +
            "font-size : 13px; "
            "font-weight : bold; "
            "color : #ffffff; "
            "background : transparent;"
        );

        QString bodyShort = body.length() > 140 ? body.left(140) + "…" : body;
        QLabel *detailsLabel = new QLabel("  Details  : " + bodyShort, card);
        detailsLabel->setGeometry(14, 96, 1100, 22);
        detailsLabel->setStyleSheet
        (
            MONO +
            "font-size : 12px; "
            "color : #c0dff5; "
            "background : transparent;"
        );

        QLabel *dividerLine = new QLabel(card);
        dividerLine->setGeometry(14, 126, 1140, 1);
        dividerLine->setStyleSheet("background : rgba(0, 200, 255, 0.15);");

        if (alreadyActioned)
        {
            QString commentText = adminComment.isEmpty() ? "(no comment left)" : adminComment;
            QLabel *previousComment = new QLabel("  Admin Response : " + commentText, card);
            previousComment->setGeometry(14, 136, 1070, 48);
            previousComment->setWordWrap(true);
            previousComment->setAlignment(Qt::AlignTop | Qt::AlignLeft);
            previousComment->setStyleSheet
            (
                MONO +
                "font-size : 12px; "
                "font-weight : bold; "
                "color : " + statusColor + "; "
                "background : transparent;"
            );
        }
        else
        {
            QLineEdit *commentInput = new QLineEdit(card);
            commentInput->setGeometry(14, 136, 820, 36);
            commentInput->setPlaceholderText("  Optional: type a response or reason for the decision...");
            commentInput->setStyleSheet
            (
                "QLineEdit"
                "{ "
                    "background : rgba(0, 15, 45, 0.88); "
                    "border : 1px solid rgba(0, 200, 255, 0.40); "
                    "border-radius : 5px; "
                    "color : #e0f4ff; "
                    "font-family : 'Courier New', monospace; "
                    "font-size : 12px; "
                    "padding : 0 10px; "
                "} "
                "QLineEdit:focus"
                "{"
                    "border : 1px solid #00eaff;"
                    "background : rgba(0, 25, 65, 0.95);"
                "}"
            );

            Button *approveButton = new Button("APPROVE", 848, 136, 140, 36, card);
            ClearButton *rejectButton = new ClearButton("REJECT", 1000, 136, 140, 36, card);

            connect(approveButton, &QPushButton::clicked, this, [this, reportId, commentInput]()
                {
                    QString comment = commentInput->text().trimmed();
                    UserReportFile::updateStatus(reportId, "Approved", comment);
                    refreshList();
                }
            );

            connect(rejectButton, &QPushButton::clicked, this, [this, reportId, commentInput]()
                {
                    QString comment = commentInput->text().trimmed();
                    UserReportFile::updateStatus(reportId, "Rejected", comment);
                    refreshList();
                }
            );
        }

        return card;
    }

    void refreshList()
    {
        QLayoutItem *layoutItem = scrollLayout->takeAt(0);
        while (layoutItem)
        {
            if (layoutItem->widget())
            {
                layoutItem->widget()->deleteLater();
            }
            delete layoutItem;
            layoutItem = scrollLayout->takeAt(0);
        }

        const QList<QStringList> allReports = UserReportFile::loadAll();
        int total = 0, pending = 0, approved = 0, rejected = 0;

        for (const QStringList &report : allReports)
        {
            QString status = report.value(5).trimmed();
            total++;
            if (status == "Pending")
            {
                pending++;
            }
            if (status == "Approved")
            {
                approved++;
            }
            if (status == "Rejected")
            {
                rejected++;
            }
        }

        totalCount->setValue(total);
        pendingCount->setValue(pending);
        approvedCount->setValue(approved);
        rejectedCount->setValue(rejected);

        QList<QStringList> filtered;
        for (const QStringList &report : allReports)
        {
            if (activeFilter == "All" || report.value(5).trimmed() == activeFilter)
            {
                filtered.append(report);
            }
        }

        if (filtered.isEmpty())
        {
            QLabel *emptyLabel = new QLabel("  No reports found for filter: " + activeFilter);
            emptyLabel->setFixedHeight(48);
            emptyLabel->setStyleSheet(MONO + "font-size : 13px; color : #7ab8e0; background : transparent;");
            scrollLayout->addWidget(emptyLabel);
        }
        else
        {
            for (int i = filtered.size() - 1; i >= 0; i--)
            {
                scrollLayout->addWidget(makeReviewCard(filtered[i]));
            }
        }

        scrollLayout->addStretch();
    }

public:

    AdminReports() : QWidget(nullptr)
    {
        setWindowTitle("User Report Reviews — CRIME RECORD MANAGEMENT SYSTEM");

        pageBackground = new Background(this, "backgroundThree.png");

        new Sidebar(this, "[ USER REVIEW ]");
        new PageHeader(this, "USER REPORT REVIEWS", "Review, approve, or reject case reports submitted by users.");
        new Footer(this);

        QLabel *pendingLegend = new QLabel("PENDING", this);
        pendingLegend->setGeometry(30, 172, 270, 22);
        pendingLegend->setStyleSheet(MONO + "font-size : 20px; letter-spacing : 4px; font-weight : 900; color : #ffcc44; background : transparent;");

        QLabel *approvedLegend = new QLabel("APPROVED", this);
        approvedLegend->setGeometry(30, 200, 270, 22);
        approvedLegend->setStyleSheet(MONO + "font-size : 20px; letter-spacing : 4px; font-weight : 900; color : #44ff99; background : transparent;");

        QLabel *rejectedLegend = new QLabel("REJECTED", this);
        rejectedLegend->setGeometry(30, 228, 270, 22);
        rejectedLegend->setStyleSheet(MONO + "font-size : 20px; letter-spacing : 4px; font-weight : 900; color : #ff6666; background : transparent;");

        QLabel *sideDividerLine = new QLabel(this);
        sideDividerLine->setGeometry(30, 264, 260, 1);
        sideDividerLine->setStyleSheet("background : rgba(0, 200, 255, 0.20);");

        allFilter = new Button("All Reports", 25, 300, 270, 40, this);
        connect(allFilter, &QPushButton::clicked, this, [this]()
            {
                activeFilter = "All";
                refreshList();
            }
        );

        pendingFilter = new Button("Pending", 25, 360, 270, 40, this);
        connect(pendingFilter, &QPushButton::clicked, this, [this]()
            {
                activeFilter = "Pending";
                refreshList();
            }
        );

        approvedFilter = new Button("Approved", 25, 420, 270, 40, this);
        connect(approvedFilter, &QPushButton::clicked, this, [this]()
            {
               activeFilter = "Approved";
               refreshList();
            }
        );

        rejectedFilter = new Button("Rejected", 25, 480, 270, 40, this);
        connect(rejectedFilter, &QPushButton::clicked, this, [this]()
            {
               activeFilter = "Rejected";
               refreshList();
            }
        );

        backNavigation = new BackButton(25, 540, 270, 44, this);
        backNavigation->raise();
        connect(backNavigation, &QPushButton::clicked, this, &QWidget::close);

        totalCount = new StatCard(380, 150, "#00eaff", "TOTAL", this);
        pendingCount  = new StatCard(700, 150, "#ffcc44", "PENDING", this);
        approvedCount = new StatCard(1000, 150, "#44ff99", "APPROVED", this);
        rejectedCount = new StatCard(1300, 150, "#ff6666", "REJECTED", this);

        QLabel *listHeading = new QLabel("  SUBMITTED REPORTS", this);
        listHeading->setGeometry(380, 252, 600, 28);
        listHeading->setStyleSheet(MONO + "font-size : 18px; font-weight : bold; color : #00eaff; background : transparent;");

        QScrollArea *scrollArea = new QScrollArea(this);
        scrollArea->setGeometry(380, 288, 1150, 480);
        scrollArea->setWidgetResizable(true);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setStyleSheet
        (
            "QScrollArea "
            "{"
                "background : rgba(3, 12, 35, 0.92); "
                "border : 1px solid rgba(0, 200, 255, 0.35); "
                "border-radius  : 12px; "
            "} "
        );

        scrollContent = new QWidget();
        scrollContent->setStyleSheet("background : transparent;");

        scrollLayout = new QVBoxLayout(scrollContent);
        scrollLayout->setContentsMargins(14, 14, 14, 14);
        scrollLayout->setSpacing(10);

        scrollArea->setWidget(scrollContent);

        refreshList();
    }

    void resizeEvent(QResizeEvent *) override
    {
        pageBackground->resize(size());
    }
};

#endif