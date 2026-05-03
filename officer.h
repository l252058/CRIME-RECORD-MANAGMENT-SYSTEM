#ifndef REPORTS_H
#define REPORTS_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>

#include "common.h"

// =============================================================================
//  REPORTS & ANALYTICS PAGE   (backgroundThree.png)
// =============================================================================

class Reports : public QWidget
{
private:

    QLabel      *img;
    Card        *sideCard;
    QLabel      *totalNumber;
    QLabel      *solvedNumber;
    QLabel      *pendingNumber;
    QLabel      *coldNumber;
    Button      *generateBtn;

    // Scroll area content widget
    QWidget     *scrollContent;
    QVBoxLayout *scrollLayout;

    // ── Helper — Section Header Row ───────────────────────────────────────────

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

    // ── Helper — Data Row ─────────────────────────────────────────────────────

    QWidget *makeRow(const QString &label, const QString &value, const QString &badgeColor)
    {
        QWidget *row = new QWidget();
        row->setFixedHeight(42);
        row->setStyleSheet
            (
                "background    : rgba(0, 15, 45, 0.70);"
                "border-bottom : 1px solid rgba(0, 200, 255, 0.12);"
                "border-radius : 4px;"
                );

        // Label
        QLabel *lbl = new QLabel(label, row);
        lbl->setGeometry(16, 0, 680, 42);
        lbl->setStyleSheet
            (
                MONO +
                "font-size  : 12px;"
                "color      : #c0dff5;"
                "background : transparent;"
                );

        // Badge
        QLabel *badge = new QLabel(value, row);
        badge->setGeometry(720, 8, 120, 26);
        badge->setAlignment(Qt::AlignCenter);
        badge->setStyleSheet
            (
                MONO +
                "font-size     : 11px;"
                "font-weight   : bold;"
                "color         : #000000;"
                "background    : " + badgeColor + ";"
                               "border-radius : 6px;"
                );

        return row;
    }

    // ── Helper — Divider ──────────────────────────────────────────────────────

    QLabel *makeDivider()
    {
        QLabel *div = new QLabel();
        div->setFixedHeight(12);
        div->setStyleSheet("background: transparent;");
        return div;
    }

public:

    Reports()
    {
        setWindowTitle("Reports & Analytics - CRIME RECORD MANAGEMENT SYSTEM");

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
        QLabel *tag = new QLabel("[ REPORTS & ANALYTICS ]", this);
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

        // Case Status Label
        QLabel *legTitle = new QLabel("CASE STATUS", this);
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

        // Legend Labels
        QLabel *solvedLeg = new QLabel("SOLVED", this);
        solvedLeg->setGeometry(30, 172, 270, 22);
        solvedLeg->setStyleSheet
            (
                MONO +
                "font-size     : 15px;"
                "letter-spacing: 4px;"
                "font-weight   : bold;"
                "color         : #44ff99;"
                "background    : transparent;"
                );

        QLabel *pendingLeg = new QLabel("PENDING", this);
        pendingLeg->setGeometry(30, 200, 270, 22);
        pendingLeg->setStyleSheet
            (
                MONO +
                "font-size     : 15px;"
                "letter-spacing: 4px;"
                "font-weight   : bold;"
                "color         : #ffcc44;"
                "background    : transparent;"
                );

        QLabel *coldLeg = new QLabel("COLD", this);
        coldLeg->setGeometry(30, 228, 270, 22);
        coldLeg->setStyleSheet
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

        // Generate Report Button
        generateBtn = new Button("  Generate Report", 25, startY + 130, buttonWidth, buttonHeight, this);

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
        QLabel *pageTitle = new QLabel("REPORTS & ANALYTICS", this);
        pageTitle->setGeometry(380, 40, 1180, 50);
        pageTitle->setStyleSheet
            (
                MONO +
                "font-size     : 28px;"
                "font-weight   : 900;"
                "letter-spacing: 6px;"
                "color         : #ffffff;"
                "background    : transparent;"
                );

        // Page Subtitle
        QLabel *pageSubtitle = new QLabel("System-wide insights and case statistics", this);
        pageSubtitle->setGeometry(380, 95, 1180, 22);
        pageSubtitle->setStyleSheet
            (
                MONO +
                "font-size  : 12px;"
                "font-weight: bold;"
                "color      : #7ab8e0;"
                "background : transparent;"
                );

        // Header Line
        QLabel *headerLine = new QLabel(this);
        headerLine->setGeometry(380, 125, 1180, 1);
        headerLine->setStyleSheet("background: rgba(0,200,255,0.25);");

        // Total Cases Stat Card
        QLabel *totalCard = new QLabel(this);
        totalCard->setGeometry(380, 140, 230, 90);
        totalCard->setStyleSheet("background:rgba(0,20,50,0.85); border:1px solid #00eaff; border-radius:10px;");

        totalNumber = new QLabel("0", this);
        totalNumber->setGeometry(390, 150, 210, 44);
        totalNumber->setAlignment(Qt::AlignCenter);
        totalNumber->setStyleSheet(MONO + "font-size:30px; font-weight:900; color:#00eaff; background:transparent;");

        QLabel *totalText = new QLabel("TOTAL CASES", this);
        totalText->setGeometry(390, 196, 210, 22);
        totalText->setAlignment(Qt::AlignCenter);
        totalText->setStyleSheet(MONO + "font-size:11px; letter-spacing:3px; color:#c0dff5; background:transparent;");

        // Solved Stat Card
        QLabel *solvedCard = new QLabel(this);
        solvedCard->setGeometry(660, 140, 230, 90);
        solvedCard->setStyleSheet("background:rgba(0,20,50,0.85); border:1px solid #44ff99; border-radius:10px;");

        solvedNumber = new QLabel("0", this);
        solvedNumber->setGeometry(670, 150, 210, 44);
        solvedNumber->setAlignment(Qt::AlignCenter);
        solvedNumber->setStyleSheet(MONO + "font-size:30px; font-weight:900; color:#44ff99; background:transparent;");

        QLabel *solvedText = new QLabel("SOLVED", this);
        solvedText->setGeometry(670, 196, 210, 22);
        solvedText->setAlignment(Qt::AlignCenter);
        solvedText->setStyleSheet(MONO + "font-size:11px; letter-spacing:3px; color:#c0dff5; background:transparent;");

        // Pending Stat Card
        QLabel *pendingCard = new QLabel(this);
        pendingCard->setGeometry(940, 140, 230, 90);
        pendingCard->setStyleSheet("background:rgba(0,20,50,0.85); border:1px solid #ffcc44; border-radius:10px;");

        pendingNumber = new QLabel("0", this);
        pendingNumber->setGeometry(950, 150, 210, 44);
        pendingNumber->setAlignment(Qt::AlignCenter);
        pendingNumber->setStyleSheet(MONO + "font-size:30px; font-weight:900; color:#ffcc44; background:transparent;");

        QLabel *pendingText = new QLabel("PENDING", this);
        pendingText->setGeometry(950, 196, 210, 22);
        pendingText->setAlignment(Qt::AlignCenter);
        pendingText->setStyleSheet(MONO + "font-size:11px; letter-spacing:3px; color:#c0dff5; background:transparent;");

        // Cold Stat Card
        QLabel *coldCard = new QLabel(this);
        coldCard->setGeometry(1220, 140, 230, 90);
        coldCard->setStyleSheet("background:rgba(0,20,50,0.85); border:1px solid #ff6666; border-radius:10px;");

        coldNumber = new QLabel("0", this);
        coldNumber->setGeometry(1230, 150, 210, 44);
        coldNumber->setAlignment(Qt::AlignCenter);
        coldNumber->setStyleSheet(MONO + "font-size:30px; font-weight:900; color:#ff6666; background:transparent;");

        QLabel *coldText = new QLabel("COLD", this);
        coldText->setGeometry(1230, 196, 210, 22);
        coldText->setAlignment(Qt::AlignCenter);
        coldText->setStyleSheet(MONO + "font-size:11px; letter-spacing:3px; color:#c0dff5; background:transparent;");

        // Report Heading
        QLabel *reportHeading = new QLabel("DETAILED REPORT", this);
        reportHeading->setGeometry(380, 252, 800, 28);
        reportHeading->setStyleSheet
            (
                MONO +
                "font-size   : 15px;"
                "font-weight : bold;"
                "color       : #00eaff;"
                "background  : transparent;"
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
                "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical"
                "{"
                "    height : 0px;"
                "}"
                );

        scrollContent = new QWidget();
        scrollContent->setStyleSheet("background: transparent;");

        scrollLayout = new QVBoxLayout(scrollContent);
        scrollLayout->setContentsMargins(14, 14, 14, 14);
        scrollLayout->setSpacing(4);

        // Default placeholder rows
        scrollLayout->addWidget(makeSectionHeader("  CASE OVERVIEW", "#00eaff"));
        scrollLayout->addWidget(makeRow("  Total Cases Registered", "0", "#00eaff"));
        scrollLayout->addWidget(makeRow("  Cases Solved",           "0", "#44ff99"));
        scrollLayout->addWidget(makeRow("  Cases Pending",          "0", "#ffcc44"));
        scrollLayout->addWidget(makeRow("  Cases Cold",             "0", "#ff6666"));
        scrollLayout->addWidget(makeDivider());

        scrollLayout->addWidget(makeSectionHeader("  BREAKDOWN BY CRIME TYPE", "#c0dff5"));
        scrollLayout->addWidget(makeRow("  No data available yet — click Generate Report", "—", "#7ab8e0"));
        scrollLayout->addWidget(makeDivider());

        scrollLayout->addWidget(makeSectionHeader("  BREAKDOWN BY LOCATION", "#c0dff5"));
        scrollLayout->addWidget(makeRow("  No data available yet — click Generate Report", "—", "#7ab8e0"));
        scrollLayout->addWidget(makeDivider());

        scrollLayout->addStretch();

        scroll->setWidget(scrollContent);

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

        // ── Button Connections ────────────────────────────────────────────────

        connect(generateBtn, &QPushButton::clicked, this, [=]()
                {
                    totalNumber->setText("--");
                    solvedNumber->setText("--");
                    pendingNumber->setText("--");
                    coldNumber->setText("--");

                    // Clear old rows
                    QLayoutItem *item;
                    while ((item = scrollLayout->takeAt(0)) != nullptr)
                    {
                        if (item->widget())
                            item->widget()->deleteLater();
                        delete item;
                    }

                    // Rebuild with placeholder data
                    scrollLayout->addWidget(makeSectionHeader("  CASE OVERVIEW", "#00eaff"));
                    scrollLayout->addWidget(makeRow("  Total Cases Registered", "--", "#00eaff"));
                    scrollLayout->addWidget(makeRow("  Cases Solved",           "--", "#44ff99"));
                    scrollLayout->addWidget(makeRow("  Cases Pending",          "--", "#ffcc44"));
                    scrollLayout->addWidget(makeRow("  Cases Cold",             "--", "#ff6666"));
                    scrollLayout->addWidget(makeDivider());

                    scrollLayout->addWidget(makeSectionHeader("  BREAKDOWN BY CRIME TYPE", "#c0dff5"));
                    scrollLayout->addWidget(makeRow("  No records found", "—", "#7ab8e0"));
                    scrollLayout->addWidget(makeDivider());

                    scrollLayout->addWidget(makeSectionHeader("  BREAKDOWN BY LOCATION", "#c0dff5"));
                    scrollLayout->addWidget(makeRow("  No records found", "—", "#7ab8e0"));
                    scrollLayout->addWidget(makeDivider());

                    scrollLayout->addStretch();
                }
                );

        connect(backBtn, &QPushButton::clicked, this, [=]()
                {
                    this->close();
                }
                );
    }

    // ── Public Setters ────────────────────────────────────────────────────────

    void setTotalCount(int n)   { totalNumber->setText(QString::number(n));   }
    void setSolvedCount(int n)  { solvedNumber->setText(QString::number(n));  }
    void setPendingCount(int n) { pendingNumber->setText(QString::number(n)); }
    void setColdCount(int n)    { coldNumber->setText(QString::number(n));    }

    Button *getGenerateButton() { return generateBtn; }

    void resizeEvent(QResizeEvent *)
    {
        img->resize(size());
    }
};

#endif // REPORTS_H