#ifndef ADMINREPORTS_H
#define ADMINREPORTS_H

// =============================================================================
//  adminReports.h
//  AdminReports — admin page to review ALL user-submitted case reports.
//
//  Admin can:
//    • View all pending / approved / rejected reports with full details
//    • Filter by status (All / Pending / Approved / Rejected)
//    • Type an optional response comment
//    • Click Approve or Reject — status is written back to userreports.txt
//
//  Add to adminMenu.h:
//    #include "adminReports.h"
//    // In button connections section:
//    connect(button[N], &QPushButton::clicked, this, [=]()
//    {
//        FileHandler::appendLog("ADMIN", "Opened User Report Reviews");
//        AdminReports *page = new AdminReports();
//        page->setAttribute(Qt::WA_DeleteOnClose);
//        page->showMaximized();
//    });
//
//  Depends on: UserReportFile  (defined in submitReport.h)
//  Include submitReport.h BEFORE adminReports.h in adminMenu.h
// =============================================================================

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QResizeEvent>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

#include "common.h"
#include "file.h"
#include "submitReport.h"   // brings in UserReportFile

// =============================================================================
//  AdminReports
// =============================================================================

class AdminReports : public QWidget
{
private:

    QLabel      *backgroundImage;
    StatCard    *totalCount;
    StatCard    *pendingCount;
    StatCard    *approvedCount;
    StatCard    *rejectedCount;

    QWidget     *scrollContent;
    QVBoxLayout *scrollLayout;

    QString      activeFilter = "All";  // "All" | "Pending" | "Approved" | "Rejected"

    // ── Build one report review card ─────────────────────────────────────────
    //  Each card has:
    //    • Report metadata
    //    • A text input for admin comment
    //    • Approve + Reject buttons
    // ─────────────────────────────────────────────────────────────────────────

    QWidget *makeReviewCard(const QStringList &r)
    {
        // r = { reportID, email, caseRef, subject, body, status, adminComment }

        QString reportID     = r.value(0, "—");
        QString email        = r.value(1, "—");
        QString caseRef      = r.value(2, "—");
        QString subject      = r.value(3, "—");
        QString body         = r.value(4, "—");
        QString status       = r.value(5, "Pending");
        QString adminComment = r.value(6, "").trimmed();

        bool alreadyActioned = (status == "Approved" || status == "Rejected");

        QString statusColor = "#ffcc44";
        if (status == "Approved") statusColor = "#44ff99";
        if (status == "Rejected") statusColor = "#ff6666";

        Card *card = new Card(0, 0, 1100, (alreadyActioned ? 200 : 240), nullptr);

        // ── Status badge ──────────────────────────────────────────────────────

        QLabel *badge = new QLabel(status.toUpper(), card);
        badge->setGeometry(1060, 14, 100, 26);
        badge->setAlignment(Qt::AlignCenter);
        badge->setStyleSheet(
            MONO +
            "font-size:11px; font-weight:bold; color:#000000;"
            "background:" + statusColor + "; border-radius:4px;"
            );

        // ── Metadata row ──────────────────────────────────────────────────────

        QLabel *idLabel = new QLabel("  ID: " + reportID + "   |   From: " + email, card);
        idLabel->setGeometry(14, 14, 900, 22);
        idLabel->setStyleSheet(
            MONO + "font-size:11px; color:#7ab8e0; background:transparent;"
            );

        QLabel *refLabel = new QLabel("  Case Ref : " + caseRef, card);
        refLabel->setGeometry(14, 40, 500, 22);
        refLabel->setStyleSheet(
            MONO + "font-size:13px; font-weight:bold; color:#00eaff; background:transparent;"
            );

        QLabel *subjLabel = new QLabel("  Subject  : " + subject, card);
        subjLabel->setGeometry(14, 68, 1000, 22);
        subjLabel->setStyleSheet(
            MONO + "font-size:13px; font-weight:bold; color:#ffffff; background:transparent;"
            );

        QString bodyShort = body.length() > 140 ? body.left(140) + "…" : body;
        QLabel *bodyLabel = new QLabel("  Details  : " + bodyShort, card);
        bodyLabel->setGeometry(14, 96, 1100, 22);
        bodyLabel->setStyleSheet(
            MONO + "font-size:12px; color:#c0dff5; background:transparent;"
            );

        QLabel *div = new QLabel(card);
        div->setGeometry(14, 126, 1140, 1);
        div->setStyleSheet("background: rgba(0,200,255,0.15);");

        if (alreadyActioned)
        {
            // Show previous admin comment; no action buttons
            QString commentText = adminComment.isEmpty()
                                      ? "(no comment left)"
                                      : adminComment;
            QLabel *prevComment = new QLabel("  Admin Response : " + commentText, card);
            prevComment->setGeometry(14, 136, 1070, 48);
            prevComment->setWordWrap(true);
            prevComment->setAlignment(Qt::AlignTop | Qt::AlignLeft);
            prevComment->setStyleSheet(
                MONO +
                "font-size:12px; font-weight:bold;"
                "color:" + statusColor + "; background:transparent;"
                );
        }
        else
        {
            // ── Admin comment input ───────────────────────────────────────────

            QLineEdit *commentInput = new QLineEdit(card);
            commentInput->setGeometry(14, 136, 820, 36);
            commentInput->setPlaceholderText("  Optional: type a response or reason for the decision...");
            commentInput->setStyleSheet(
                "QLineEdit"
                "{"
                "    background    : rgba(0, 15, 45, 0.88);"
                "    border        : 1px solid rgba(0, 200, 255, 0.40);"
                "    border-radius : 5px;"
                "    color         : #e0f4ff;"
                "    font-family   : 'Courier New', monospace;"
                "    font-size     : 12px;"
                "    padding       : 0 10px;"
                "}"
                "QLineEdit:focus { border:1px solid #00eaff; background:rgba(0,25,65,0.95); }"
                );

            Button * approveBtn = new Button("APPROVE", 848, 136, 140, 36, card);
            ClearButton * rejectBtn = new ClearButton("REJECT", 1000, 136, 140, 36, card);

            // Connections — capture reportID and commentInput by value/pointer
            connect(approveBtn, &QPushButton::clicked, this,
                    [this, reportID, commentInput]()
                    {
                        QString comment = commentInput->text().trimmed();
                        UserReportFile::updateStatus(reportID, "Approved", comment);
                        FileHandler::appendLog("ADMIN",
                                               "Approved report [" + reportID + "]"
                                                   + (comment.isEmpty() ? "" : " — " + comment));
                        refreshList();
                    });

            connect(rejectBtn, &QPushButton::clicked, this,
                    [this, reportID, commentInput]()
                    {
                        QString comment = commentInput->text().trimmed();
                        UserReportFile::updateStatus(reportID, "Rejected", comment);
                        FileHandler::appendLog("ADMIN",
                                               "Rejected report [" + reportID + "]"
                                                   + (comment.isEmpty() ? "" : " — " + comment));
                        refreshList();
                    });
        }

        return card;
    }

    // ── Rebuild the scroll list ───────────────────────────────────────────────

    void refreshList()
    {
        // Clear
        QLayoutItem *item = scrollLayout->takeAt(0);
        while (item)
        {
            if (item->widget()) item->widget()->deleteLater();
            delete item;
            item = scrollLayout->takeAt(0);
        }

        const QList<QStringList> all = UserReportFile::loadAll();

        // Recalculate stat cards
        int total = all.size(), pending = 0, approved = 0, rejected = 0;
        for (const QStringList &r : all)
        {
            QString s = r.value(5).trimmed();
            if (s == "Pending")  pending++;
            if (s == "Approved") approved++;
            if (s == "Rejected") rejected++;
        }
        totalCount   ->setValue(total);
        pendingCount ->setValue(pending);
        approvedCount->setValue(approved);
        rejectedCount->setValue(rejected);

        // Filter
        QList<QStringList> filtered;
        for (const QStringList &r : all)
        {
            if (activeFilter == "All" || r.value(5).trimmed() == activeFilter)
            {
                filtered.append(r);
            }
        }

        if (filtered.isEmpty())
        {
            QLabel *empty = new QLabel("  No reports found for filter: " + activeFilter);
            empty->setFixedHeight(48);
            empty->setStyleSheet(
                MONO + "font-size:13px; color:#7ab8e0; background:transparent;"
                );
            scrollLayout->addWidget(empty);
        }
        else
        {
            // Most recent first
            for (int i = filtered.size() - 1; i >= 0; i--)
            {
                scrollLayout->addWidget(makeReviewCard(filtered[i]));
            }
        }

        scrollLayout->addStretch();
    }

    // ── Stat card builder ─────────────────────────────────────────────────────

    QLabel *buildStatCard(int x, int y,
                          const QString &borderColor,
                          const QString &textColor,
                          const QString &caption)
    {
        QLabel *card = new QLabel(this);
        card->setGeometry(x, y, 220, 90);
        card->setStyleSheet(
            QString("background:rgba(0,20,50,0.85); border:1px solid %1; border-radius:10px;")
                .arg(borderColor));

        QLabel *number = new QLabel("0", this);
        number->setGeometry(x + 10, y + 10, 200, 44);
        number->setAlignment(Qt::AlignCenter);
        number->setStyleSheet(
            MONO +
            QString("font-size:28px; font-weight:900; color:%1; background:transparent;")
                .arg(textColor));

        QLabel *label = new QLabel(caption, this);
        label->setGeometry(x + 10, y + 56, 200, 22);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet(
            MONO + "font-size:14px; letter-spacing:3px; color:#c0dff5; background:transparent; font-weight:bold;");

        return number;
    }

public:

    AdminReports() : QWidget(nullptr)
    {
        setWindowTitle("User Report Reviews — CRIME RECORD MANAGEMENT SYSTEM");

        backgroundImage = UI::setupBackground(this, "backgroundThree.png");

        UI::setupSidebar(this, "[ USER REVIEW ]");
        UI::setupPageHeader(this, "USER REPORT REVIEWS", "Review, approve, or reject case reports submitted by users.");
        UI::setupFooter(this);

        // Sidebar legend
        auto makeLeg = [this](const QString &text, const QString &color, int y)
        {
            QLabel *l = new QLabel(text, this);
            l->setGeometry(30, y, 270, 22);
            l->setStyleSheet(
                MONO +
                QString("font-size:20px; letter-spacing:4px; font-weight:900;"
                        "color:%1; background:transparent;").arg(color));
        };
        makeLeg("PENDING",  "#ffcc44", 172);
        makeLeg("APPROVED", "#44ff99", 200);
        makeLeg("REJECTED", "#ff6666", 228);

        QLabel *sideDiv2 = new QLabel(this);
        sideDiv2->setGeometry(30, 264, 260, 1);
        sideDiv2->setStyleSheet("background:rgba(0,200,255,0.20);");

        // ── Sidebar filter buttons ────────────────────────────────────────────

        const char *filterLabels[] = { "All Reports", "Pending", "Approved", "Rejected" };
        const char *filterValues[] = { "All",         "Pending", "Approved", "Rejected" };

        for (int i = 0; i < 4; i++)
        {
            Button *fb = new Button(filterLabels[i],
                                    25, 300 + i * 60,
                                    270, 40, this);
            QString fv = filterValues[i];
            connect(fb, &QPushButton::clicked, this, [this, fv]()
                    {
                        activeFilter = fv;
                        refreshList();
                    });
        }

        BackButton *bb = new BackButton(25, 540, 270, 44, this);
        bb->raise();
        connect(bb, &QPushButton::clicked, this, &QWidget::close);

        // ── Stat cards ────────────────────────────────────────────────────────

        totalCount    = new StatCard(380, 150, "#00eaff", "TOTAL",    this);
        pendingCount  = new StatCard(620, 150, "#ffcc44", "PENDING",  this);
        approvedCount = new StatCard(860, 150, "#44ff99", "APPROVED", this);
        rejectedCount = new StatCard(1100, 150, "#ff6666", "REJECTED", this);

        // ── Scroll area ───────────────────────────────────────────────────────

        QLabel *listHeading = new QLabel("  SUBMITTED REPORTS", this);
        listHeading->setGeometry(380, 252, 600, 28);
        listHeading->setStyleSheet(
            MONO + "font-size:18px; font-weight:bold; color:#00eaff; background:transparent;"
            );

        QScrollArea *scroll = new QScrollArea(this);
        scroll->setGeometry(380, 288, 1150, 480);
        scroll->setWidgetResizable(true);
        scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scroll->setStyleSheet(
            "QScrollArea { background:rgba(3,12,35,0.92); border:1px solid rgba(0,200,255,0.35); border-radius:12px; }"
            "QScrollBar:vertical { background:rgba(0,15,45,0.80); width:8px; border-radius:4px; }"
            "QScrollBar::handle:vertical { background:rgba(0,200,255,0.40); border-radius:4px; }"
            "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height:0px; }"
            );

        scrollContent = new QWidget();
        scrollContent->setStyleSheet("background:transparent;");

        scrollLayout = new QVBoxLayout(scrollContent);
        scrollLayout->setContentsMargins(14, 14, 14, 14);
        scrollLayout->setSpacing(10);

        scroll->setWidget(scrollContent);

        // ── Footer ────────────────────────────────────────────────────────────

        UI::setupFooter(this);

        // Auto-load all reports on open
        refreshList();
    }

    void resizeEvent(QResizeEvent *) override { backgroundImage->resize(size()); }
};

#endif // ADMINREPORTS_H