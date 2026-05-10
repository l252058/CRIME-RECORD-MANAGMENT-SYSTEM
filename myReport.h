#ifndef MYREPORTS_H
#define MYREPORTS_H

// =============================================================================
//  myReports.h
//  MyReports — shows ALL reports the logged-in user has submitted,
//              their current status, and any admin comment/response.
//
//  Standardized "Precision" UI refactor for consistency and clarity.
// =============================================================================

#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

#include "common.h"
#include "file.h"
#include "submitReport.h"   // Brings in UserReportFile definition

class MyReports : public QWidget
{
private:

    QLabel      *backgroundImage;
    StatCard    *pendingNumber;
    StatCard    *approvedNumber;
    StatCard    *rejectedNumber;

    QWidget     *scrollContent;
    QVBoxLayout *scrollLayout;

    QString      loggedInEmail;

    // ── Build one styled report card ─────────────────────────────────────────

    QWidget *makeReportCard(const QStringList &r)
    {
        // r = { reportID, email, caseRef, subject, body, status, adminComment }
        QString reportID     = r.value(0, "—");
        QString caseRef      = r.value(2, "—");
        QString subject      = r.value(3, "—");
        QString body         = r.value(4, "—");
        QString status       = r.value(5, "Pending");
        QString adminComment = r.value(6, "").trimmed();

        // Colour-code by status
        QString statusColor = "#ffcc44"; // Pending
        if (status == "Approved") statusColor = "#44ff99";
        if (status == "Rejected") statusColor = "#ff6666";

        Card *card = new Card(0, 0, 1130, 200, nullptr);

        // Status badge (top-right)
        QLabel *badge = new QLabel(status.toUpper(), card);
        badge->setGeometry(1000, 14, 120, 26);
        badge->setAlignment(Qt::AlignCenter);
        badge->setStyleSheet(
            MONO +
            "font-size     : 12px;"
            "font-weight   : bold;"
            "color         : #000000;"
            "background    : " + statusColor + ";"
            "border-radius : 4px;"
        );

        // Content Labels
        auto createRow = [&](const QString &label, const QString &val, int y, const QString &color, int size, bool bold) {
            QLabel *ql = new QLabel("  " + label + " : " + val, card);
            ql->setGeometry(14, y, 980, 24);
            ql->setStyleSheet(MONO + QString("font-size:%1px; color:%2; background:transparent; %3")
                .arg(size).arg(color).arg(bold ? "font-weight:bold;" : ""));
            return ql;
        };

        createRow("Report ID", reportID, 14, "#7ab8e0", 14, true);
        createRow("Case Ref",  caseRef,  44, "#00eaff", 16, true);
        createRow("Subject",   subject,  74, "#ffffff", 16, true);

        QString bodyShort = (body.length() > 140) ? body.left(140) + "..." : body;
        createRow("Details",   bodyShort, 104, "#c0dff5", 15, false);

        // Divider
        QLabel *div = new QLabel(card);
        div->setGeometry(14, 136, 1100, 1);
        div->setStyleSheet("background: rgba(0,200,255,0.15);");

        // Admin response
        QString responseText = adminComment.isEmpty() ? "Awaiting review..." : adminComment;
        QLabel *resLabel = createRow("Admin Response", responseText, 146, statusColor, 16, true);
        resLabel->setGeometry(14, 146, 1100, 44);
        resLabel->setWordWrap(true);
        resLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);

        return card;
    }

    // ── Data Loading ─────────────────────────────────────────────────────────

    void loadReports()
    {
        // Clear layout
        QLayoutItem *item;
        while ((item = scrollLayout->takeAt(0)) != nullptr) {
            if (item->widget()) item->widget()->deleteLater();
            delete item;
        }

        const QList<QStringList> reports = UserReportFile::loadByEmail(loggedInEmail);

        // Update counts
        int pending = 0, approved = 0, rejected = 0;
        for (const QStringList &r : reports) {
            QString s = r.value(5).trimmed();
            if (s == "Pending")  pending++;
            if (s == "Approved") approved++;
            if (s == "Rejected") rejected++;
        }
        pendingNumber ->setValue(pending);
        approvedNumber->setValue(approved);
        rejectedNumber->setValue(rejected);

        if (reports.isEmpty()) {
            QLabel *empty = new QLabel("  You have not submitted any reports yet.");
            empty->setFixedHeight(60);
            empty->setStyleSheet(MONO + "font-size:16px; color:#7ab8e0; background:transparent;");
            scrollLayout->addWidget(empty);
        } else {
            for (int i = reports.size() - 1; i >= 0; i--) {
                scrollLayout->addWidget(makeReportCard(reports[i]));
            }
        }
        scrollLayout->addStretch();
    }

public:

    explicit MyReports(const QString &email = "") : QWidget(nullptr), loggedInEmail(email)
    {
        setWindowTitle("My Case Reports — CRIME RECORD MANAGEMENT SYSTEM");

        backgroundImage = UI::setupBackground(this, "backgroundThree.png");

        UI::setupSidebar(this, "[ MY REPORTS ]");
        UI::setupPageHeader(this, "MY SUBMITTED REPORTS", "Track the status of your submitted reports and view official responses.");
        UI::setupFooter(this);

        BackButton *bb = new BackButton(25, 155, 270, 44, this);
        bb->raise();
        QObject::connect(bb, &QPushButton::clicked, [this]() { this->close(); });

        // Stat Cards
        pendingNumber  = new StatCard(380, 150, "#ffcc44", "PENDING",  this);
        approvedNumber = new StatCard(620, 150, "#44ff99", "APPROVED", this);
        rejectedNumber = new StatCard(860, 150, "#ff6666", "REJECTED", this);

        // Reports List Area
        QLabel *listTitle = new QLabel("REPORT HISTORY", this);
        listTitle->setGeometry(380, 252, 600, 28);
        listTitle->setStyleSheet(MONO + "font-size:18px; color:#00eaff; background:transparent;");

        QScrollArea *scroll = new QScrollArea(this);
        scroll->setGeometry(380, 288, 1180, 550);
        scroll->setWidgetResizable(true);
        scroll->setStyleSheet(
            "QScrollArea { background:rgba(3, 12, 35, 0.95); border:1px solid rgba(0, 234, 255, 0.35); border-radius: 15px; }"
            "QScrollBar:vertical { background:rgba(0,15,45,0.80); width:8px; border-radius:4px; }"
            "QScrollBar::handle:vertical { background:rgba(0,234,255,0.40); border-radius:4px; }"
            "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height:0px; }"
        );

        scrollContent = new QWidget();
        scrollContent->setStyleSheet("background:transparent;");
        scrollLayout = new QVBoxLayout(scrollContent);
        scrollLayout->setContentsMargins(15, 15, 15, 15);
        scrollLayout->setSpacing(12);
        scroll->setWidget(scrollContent);

        Button * refreshBtn = new Button("REFRESH", 25, 215, 270, 40, this);

        // Connections
        connect(refreshBtn, &QPushButton::clicked, this, [=]() {
            FileHandler::appendLog("USER", "Refreshed My Reports");
            loadReports();
        });

        loadReports(); // Initial load
    }

    void setEmail(const QString &email) { loggedInEmail = email; loadReports(); }
    void resizeEvent(QResizeEvent *) override { backgroundImage->resize(size()); }
};

#endif // MYREPORTS_H