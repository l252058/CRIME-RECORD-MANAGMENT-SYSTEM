#ifndef LOGS_H
#define LOGS_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>

#include "common.h"

// =============================================================================
//  ACTIVITY LOGS PAGE   (backgroundThree.png)
// =============================================================================

class ActivityLogs : public QWidget
{
private:

    QLabel      *img;
    Card        *sideCard;
    QLabel      *totalNumber;
    QLabel      *adminNumber;
    QLabel      *userNumber;
    Button      *refreshBtn;
    Button      *clearBtn;

    // Scroll area content
    QWidget     *scrollContent;
    QVBoxLayout *scrollLayout;

    // ── Helper — Log Row ──────────────────────────────────────────────────────

    QWidget *makeLogRow(const QString &category, const QString &timestamp, const QString &action, const QString &badgeColor)
    {
        QWidget *row = new QWidget();
        row->setFixedHeight(46);
        row->setStyleSheet
            (
                "background    : rgba(0, 15, 45, 0.70);"
                "border-bottom : 1px solid rgba(0, 200, 255, 0.10);"
                "border-radius : 4px;"
                );

        // Category Badge
        QLabel *badge = new QLabel(category, row);
        badge->setGeometry(12, 10, 80, 26);
        badge->setAlignment(Qt::AlignCenter);
        badge->setStyleSheet
            (
                MONO +
                "font-size     : 10px;"
                "font-weight   : bold;"
                "color         : #000000;"
                "background    : " + badgeColor + ";"
                               "border-radius : 4px;"
                );

        // Timestamp
        QLabel *time = new QLabel(timestamp, row);
        time->setGeometry(104, 0, 200, 46);
        time->setStyleSheet
            (
                MONO +
                "font-size  : 11px;"
                "color      : #7ab8e0;"
                "background : transparent;"
                );

        // Action Text
        QLabel *act = new QLabel(action, row);
        act->setGeometry(314, 0, 820, 46);
        act->setStyleSheet
            (
                MONO +
                "font-size  : 12px;"
                "color      : #c0dff5;"
                "background : transparent;"
                );

        return row;
    }

    // ── Helper — Section Header ───────────────────────────────────────────────

    QLabel *makeSectionHeader(const QString &text, const QString &color)
    {
        QLabel *header = new QLabel(text);
        header->setFixedHeight(36);
        header->setStyleSheet
            (
                MONO +
                "font-size     : 12px;"
                "font-weight   : bold;"
                "letter-spacing: 4px;"
                "color         : " + color + ";"
                          "background    : rgba(0, 30, 70, 0.80);"
                          "border-left   : 3px solid " + color + ";"
                          "padding-left  : 14px;"
                          "border-radius : 4px;"
                );
        return header;
    }

    // ── Helper — Divider ──────────────────────────────────────────────────────

    QLabel *makeDivider()
    {
        QLabel *div = new QLabel();
        div->setFixedHeight(10);
        div->setStyleSheet("background: transparent;");
        return div;
    }

    // ── Helper — Empty State Row ──────────────────────────────────────────────

    QWidget *makeEmptyRow(const QString &message)
    {
        QWidget *row = new QWidget();
        row->setFixedHeight(42);
        row->setStyleSheet("background: rgba(0,15,45,0.50); border-radius:4px;");

        QLabel *lbl = new QLabel(message, row);
        lbl->setGeometry(16, 0, 1100, 42);
        lbl->setStyleSheet
            (
                MONO +
                "font-size  : 12px;"
                "color      : #7ab8e0;"
                "background : transparent;"
                );

        return row;
    }

public:

    ActivityLogs()
    {
        setWindowTitle("Activity Logs - CRIME RECORD MANAGEMENT SYSTEM");

        // Background
        img = new QLabel(this);
        img->setPixmap(loadPixmap("backgroundThree.png"));
        img->setScaledContents(true);

        // Sidebar Card
        sideCard = new Card(0, 0, 320, 900, this);

        // Sidebar Title
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

        // Divider Line
        QLabel *lineOne = new QLabel(this);
        lineOne->setGeometry(30, 100, 260, 1);
        lineOne->setStyleSheet("background: rgba(0,200,255,0.30);");

        // Access Tag
        QLabel *tag = new QLabel("[ ACTIVITY  LOGS ]", this);
        tag->setGeometry(0, 110, 320, 22);
        tag->setAlignment(Qt::AlignCenter);
        tag->setStyleSheet
            (
                MONO +
                "font-size     : 10px;"
                "letter-spacing: 4px;"
                "color         : #ffcc44;"
                "background    : transparent;"
                "font-weight   : bold;"
                );

        // Log Categories Label
        QLabel *legTitle = new QLabel("LOG  CATEGORIES", this);
        legTitle->setGeometry(0, 148, 320, 20);
        legTitle->setAlignment(Qt::AlignCenter);
        legTitle->setStyleSheet
            (
                MONO +
                "font-size     : 10px;"
                "letter-spacing: 3px;"
                "color         : #7ab8e0;"
                "background    : transparent;"
                );

        // Legend — Admin Action
        QLabel *adminLeg = new QLabel("ADMIN ACTION", this);
        adminLeg->setGeometry(30, 172, 270, 22);
        adminLeg->setStyleSheet
            (
                MONO +
                "font-size     : 15px;"
                "letter-spacing: 4px;"
                "font-weight   : bold;"
                "color         : #ffcc44;"
                "background    : transparent;"
                );

        // Legend — User Action
        QLabel *userLeg = new QLabel("USER  ACTION", this);
        userLeg->setGeometry(30, 200, 270, 22);
        userLeg->setStyleSheet
            (
                MONO +
                "font-size     : 15px;"
                "letter-spacing: 4px;"
                "font-weight   : bold;"
                "color         : #00eaff;"
                "background    : transparent;"
                );

        // Legend — System Event
        QLabel *sysLeg = new QLabel("SYSTEM  EVENT", this);
        sysLeg->setGeometry(30, 228, 270, 22);
        sysLeg->setStyleSheet
            (
                MONO +
                "font-size     : 15px;"
                "letter-spacing: 4px;"
                "font-weight   : bold;"
                "color         : #ff6666;"
                "background    : transparent;"
                );

        // Second Divider
        QLabel *lineTwo = new QLabel(this);
        lineTwo->setGeometry(30, 264, 260, 1);
        lineTwo->setStyleSheet("background: rgba(0,200,255,0.20);");

        // Refresh Button
        refreshBtn = new Button("  Refresh Logs", 25, startY + 130, buttonWidth, buttonHeight, this);

        // Clear Button
        clearBtn = new Button("  Clear Logs", 25, startY + 190, buttonWidth, buttonHeight, this);
        clearBtn->setStyleSheet
            (
                "QPushButton"
                "{"
                "    background     : rgba(120, 0, 0, 0.60);"
                "    color          : #ffcccc;"
                "    font-family    : 'Courier New', monospace;"
                "    font-size      : 13px;"
                "    font-weight    : bold;"
                "    letter-spacing : 2px;"
                "    border         : 1px solid rgba(255, 80, 80, 0.50);"
                "    border-radius  : 6px;"
                "    text-align     : left;"
                "    padding-left   : 20px;"
                "}"
                "QPushButton:hover  { background:rgba(180,0,0,0.80); border:1px solid #ff4444; color:#ffffff; }"
                "QPushButton:pressed{ background:#5a0000; }"
                );

        // Back Button
        Button *backBtn = new Button("  <- Back", 25, 840, buttonWidth, buttonHeight, this);
        backBtn->setStyleSheet
            (
                "QPushButton"
                "{"
                "    background     : rgba(80, 0, 0, 0.70);"
                "    color          : #ff9999;"
                "    font-family    : 'Courier New', monospace;"
                "    font-size      : 13px;"
                "    font-weight    : bold;"
                "    letter-spacing : 3px;"
                "    border         : 1px solid rgba(255, 80, 80, 0.45);"
                "    border-radius  : 6px;"
                "    text-align     : left;"
                "    padding-left   : 14px;"
                "}"
                "QPushButton:hover  { background:rgba(160,0,0,0.80); color:#ffffff; border:1px solid #ff4444; }"
                "QPushButton:pressed{ background:#5a0000; }"
                );

        // Page Title
        QLabel *pageTitle = new QLabel("ACTIVITY  LOGS", this);
        pageTitle->setGeometry(380, 40, 1180, 50);
        pageTitle->setStyleSheet
            (
                MONO +
                "font-size     : 32px;"
                "font-weight   : 900;"
                "letter-spacing: 6px;"
                "color         : #ffffff;"
                "background    : transparent;"
                );

        // Page Subtitle
        QLabel *pageSubtitle = new QLabel("Complete audit trail of all admin and user actions", this);
        pageSubtitle->setGeometry(380, 95, 1180, 22);
        pageSubtitle->setStyleSheet
            (
                MONO +
                "font-size  : 12px;"
                "font-weight: bold;"
                "color      : #ffcc44;"
                "background : transparent;"
                );

        // Header Line
        QLabel *headerLine = new QLabel(this);
        headerLine->setGeometry(380, 125, 1180, 1);
        headerLine->setStyleSheet("background: rgba(0,200,255,0.25);");

        // Total Logs Stat Card
        QLabel *totalCard = new QLabel(this);
        totalCard->setGeometry(380, 140, 230, 90);
        totalCard->setStyleSheet("background:rgba(0,20,50,0.85); border:1px solid #00eaff; border-radius:10px;");

        totalNumber = new QLabel("0", this);
        totalNumber->setGeometry(390, 150, 210, 44);
        totalNumber->setAlignment(Qt::AlignCenter);
        totalNumber->setStyleSheet(MONO + "font-size:30px; font-weight:900; color:#00eaff; background:transparent;");

        QLabel *totalText = new QLabel("TOTAL  LOGS", this);
        totalText->setGeometry(390, 196, 210, 22);
        totalText->setAlignment(Qt::AlignCenter);
        totalText->setStyleSheet(MONO + "font-size:11px; letter-spacing:3px; color:#c0dff5; background:transparent;");

        // Admin Actions Stat Card
        QLabel *adminCard = new QLabel(this);
        adminCard->setGeometry(850, 140, 230, 90);
        adminCard->setStyleSheet("background:rgba(0,20,50,0.85); border:1px solid #ffcc44; border-radius:10px;");

        adminNumber = new QLabel("0", this);
        adminNumber->setGeometry(860, 150, 210, 44);
        adminNumber->setAlignment(Qt::AlignCenter);
        adminNumber->setStyleSheet(MONO + "font-size:30px; font-weight:900; color:#ffcc44; background:transparent;");

        QLabel *adminText = new QLabel("ADMIN  ACTIONS", this);
        adminText->setGeometry(860, 196, 210, 22);
        adminText->setAlignment(Qt::AlignCenter);
        adminText->setStyleSheet(MONO + "font-size:11px; letter-spacing:3px; color:#c0dff5; background:transparent;");

        // User Actions Stat Card
        QLabel *userCard = new QLabel(this);
        userCard->setGeometry(1300, 140, 230, 90);
        userCard->setStyleSheet("background:rgba(0,20,50,0.85); border:1px solid #44ff99; border-radius:10px;");

        userNumber = new QLabel("0", this);
        userNumber->setGeometry(1310, 150, 210, 44);
        userNumber->setAlignment(Qt::AlignCenter);
        userNumber->setStyleSheet(MONO + "font-size:30px; font-weight:900; color:#44ff99; background:transparent;");

        QLabel *userText = new QLabel("USER  ACTIONS", this);
        userText->setGeometry(1310, 196, 210, 22);
        userText->setAlignment(Qt::AlignCenter);
        userText->setStyleSheet(MONO + "font-size:11px; letter-spacing:3px; color:#c0dff5; background:transparent;");

        // Log Entries Heading
        QLabel *logHeading = new QLabel("LOG  ENTRIES", this);
        logHeading->setGeometry(380, 252, 800, 28);
        logHeading->setStyleSheet
            (
                MONO +
                "font-size   : 15px;"
                "font-weight : bold;"
                "color       : #00eaff;"
                "background  : transparent;"
                );

        // Footer
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

        // ── Scroll Area ───────────────────────────────────────────────────────

        QScrollArea *scroll = new QScrollArea(this);
        scroll->setGeometry(380, 288, 1180, 560);
        scroll->setWidgetResizable(true);
        scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scroll->setStyleSheet
            (
                "QScrollArea"
                "{"
                "    background    : rgba(3, 12, 35, 0.92);"
                "    border        : 1px solid rgba(0, 200, 255, 0.35);"
                "    border-radius : 12px;"
                "}"
                "QScrollBar:vertical"
                "{"
                "    background    : rgba(0, 15, 45, 0.80);"
                "    width         : 8px;"
                "    border-radius : 4px;"
                "}"
                "QScrollBar::handle:vertical"
                "{"
                "    background    : rgba(0, 200, 255, 0.40);"
                "    border-radius : 4px;"
                "}"
                "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height:0px; }"
                );

        scrollContent = new QWidget();
        scrollContent->setStyleSheet("background: transparent;");

        scrollLayout = new QVBoxLayout(scrollContent);
        scrollLayout->setContentsMargins(12, 12, 12, 12);
        scrollLayout->setSpacing(3);

        // Default placeholder
        scrollLayout->addWidget(makeSectionHeader("  ALL ENTRIES", "#00eaff"));
        scrollLayout->addWidget(makeEmptyRow("  Click  Refresh Logs  to load the activity log."));
        scrollLayout->addStretch();

        scroll->setWidget(scrollContent);

        // ── Button Connections ────────────────────────────────────────────────

        connect(refreshBtn, &QPushButton::clicked, this, [=]()
                {
                    totalNumber->setText("5");
                    adminNumber->setText("3");
                    userNumber->setText("1");

                    QLayoutItem *item;
                    while ((item = scrollLayout->takeAt(0)) != nullptr)
                    {
                        if (item->widget()) item->widget()->deleteLater();
                        delete item;
                    }

                    scrollLayout->addWidget(makeSectionHeader("  ADMIN ACTIONS", "#ffcc44"));
                    scrollLayout->addWidget(makeLogRow("ADMIN", "2025-01-01  10:00", "Added case  CR-001",      "#ffcc44"));
                    scrollLayout->addWidget(makeLogRow("ADMIN", "2025-01-01  10:05", "Modified case  CR-001",   "#ffcc44"));
                    scrollLayout->addWidget(makeLogRow("ADMIN", "2025-01-01  10:15", "Deleted case  CR-002",    "#ffcc44"));
                    scrollLayout->addWidget(makeDivider());

                    scrollLayout->addWidget(makeSectionHeader("  USER ACTIONS", "#00eaff"));
                    scrollLayout->addWidget(makeLogRow("USER",  "2025-01-01  10:10", "Viewed case  CR-001",     "#00eaff"));
                    scrollLayout->addWidget(makeDivider());

                    scrollLayout->addWidget(makeSectionHeader("  SYSTEM EVENTS", "#ff6666"));
                    scrollLayout->addWidget(makeLogRow("SYS",   "2025-01-01  10:20", "System started",          "#ff6666"));
                    scrollLayout->addWidget(makeDivider());

                    scrollLayout->addStretch();
                }
                );

        connect(clearBtn, &QPushButton::clicked, this, [=]()
                {
                    totalNumber->setText("0");
                    adminNumber->setText("0");
                    userNumber->setText("0");

                    QLayoutItem *item;
                    while ((item = scrollLayout->takeAt(0)) != nullptr)
                    {
                        if (item->widget()) item->widget()->deleteLater();
                        delete item;
                    }

                    scrollLayout->addWidget(makeSectionHeader("  ALL ENTRIES", "#00eaff"));
                    scrollLayout->addWidget(makeEmptyRow("  Logs cleared."));
                    scrollLayout->addStretch();
                }
                );

        connect(backBtn, &QPushButton::clicked, this, [=]()
                {
                    this->close();
                }
                );
    }

    void setTotalCount(int n)            { totalNumber->setText(QString::number(n)); }
    void setAdminCount(int n)            { adminNumber->setText(QString::number(n)); }
    void setUserCount(int n)             { userNumber->setText(QString::number(n));  }

    Button *getRefreshButton() { return refreshBtn; }
    Button *getClearButton()   { return clearBtn;   }

    void resizeEvent(QResizeEvent *)
    {
        img->resize(size());
    }
};

#endif // LOGS_H