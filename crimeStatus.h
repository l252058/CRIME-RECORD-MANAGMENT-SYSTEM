#ifndef CRIMESTATUS_H
#define CRIMESTATUS_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QStackedWidget>
#include <QPushButton>

#include "common.h"

// =============================================================================
//  UPDATE PANEL
// =============================================================================

class Update : public QWidget
{
private:

    Card        *updateCard;
    Box         *caseIDBox;
    Button      *loadButton;
    QPushButton *solvedButton;
    QPushButton *pendingButton;
    QPushButton *coldButton;
    QLabel      *infoLbl;

public:

    Update(QWidget *parent = nullptr) : QWidget(parent)
    {
        // Update Card
        updateCard = new Card(0, 0, 700, 340, this);

        // Heading
        QLabel *title = new QLabel("UPDATE CASE STATUS", this);
        title->setGeometry(20, 18, 660, 28);
        title->setStyleSheet
            (
                MONO +
                "font-size   : 14px;"
                "font-weight : bold;"
                "color       : #ffcc44;"
                "background  : transparent;"
                );

        // Divider Line
        QLabel *line = new QLabel(this);
        line->setGeometry(20, 52, 660, 1);
        line->setStyleSheet("background: rgba(255,200,0,0.20);");

        // Case ID Label
        QLabel *caseID = new QLabel("Case ID", this);
        caseID->setGeometry(20, 68, 300, 22);
        caseID->setStyleSheet
            (
                MONO +
                "font-size   : 14px;"
                "font-weight : bold;"
                "color       : #a0d8f0;"
                "background  : transparent;"
                );

        caseIDBox  = new Box(20, 94, 440, 38, "Enter Case ID", this);
        loadButton = new Button("Load", 472, 94, 100, 38, this);

        // Info Label
        infoLbl = new QLabel("", this);
        infoLbl->setGeometry(20, 140, 660, 22);
        infoLbl->setStyleSheet
            (
                MONO +
                "font-size  : 12px;"
                "color      : #c0dff5;"
                "background : transparent;"
                );

        // New Status Label
        QLabel *status = new QLabel("New Status", this);
        status->setGeometry(20, 172, 300, 22);
        status->setStyleSheet
            (
                MONO +
                "font-size   : 14px;"
                "font-weight : bold;"
                "color       : #a0d8f0;"
                "background  : transparent;"
                );

        // Status Buttons
        solvedButton = new QPushButton("SOLVED", this);
        solvedButton->setGeometry(20, 204, 190, 42);
        solvedButton->setCursor(Qt::PointingHandCursor);
        solvedButton->setStyleSheet
            (
                "QPushButton         { background:rgba(0,30,60,0.80); color:#44ff99; font-family:'Courier New',monospace; font-size:12px; font-weight:bold; border:1px solid #44ff99; border-radius:8px; }"
                "QPushButton:hover   { background:#44ff99; color:#000000; }"
                "QPushButton:pressed { opacity:0.7; }"
                );

        pendingButton = new QPushButton("PENDING", this);
        pendingButton->setGeometry(222, 204, 190, 42);
        pendingButton->setCursor(Qt::PointingHandCursor);
        pendingButton->setStyleSheet
            (
                "QPushButton         { background:rgba(0,30,60,0.80); color:#ffcc44; font-family:'Courier New',monospace; font-size:12px; font-weight:bold; border:1px solid #ffcc44; border-radius:8px; }"
                "QPushButton:hover   { background:#ffcc44; color:#000000; }"
                "QPushButton:pressed { opacity:0.7; }"
                );

        coldButton = new QPushButton("COLD", this);
        coldButton->setGeometry(424, 204, 190, 42);
        coldButton->setCursor(Qt::PointingHandCursor);
        coldButton->setStyleSheet
            (
                "QPushButton         { background:rgba(0,30,60,0.80); color:#ff6666; font-family:'Courier New',monospace; font-size:12px; font-weight:bold; border:1px solid #ff6666; border-radius:8px; }"
                "QPushButton:hover   { background:#ff6666; color:#000000; }"
                "QPushButton:pressed { opacity:0.7; }"
                );

        // Save Button
        Button *saveButton = new Button("Save Changes", 20, 270, 200, 42, this);

        // ── Connections ───────────────────────────────────────────────────────

        QObject::connect(loadButton, &QPushButton::clicked, [this]()
                         {
                             infoLbl->setText("Case loaded successfully.");
                         });

        QObject::connect(solvedButton, &QPushButton::clicked, [this]()
                         {
                             infoLbl->setText("Status set to: SOLVED");
                         });

        QObject::connect(pendingButton, &QPushButton::clicked, [this]()
                         {
                             infoLbl->setText("Status set to: PENDING");
                         });

        QObject::connect(coldButton, &QPushButton::clicked, [this]()
                         {
                             infoLbl->setText("Status set to: COLD");
                         });

        QObject::connect(saveButton, &QPushButton::clicked, [this]()
                         {
                             infoLbl->setText("Changes saved.");
                         });
    }
};

// =============================================================================
//  VIEW PANEL
// =============================================================================

class StatusView : public QWidget
{
private:

    Button *refresh;
    QLabel *viewCard;

public:

    StatusView(QWidget *parent = nullptr) : QWidget(parent)
    {
        // Heading
        QLabel *heading = new QLabel(" ALL CASES WITH STATUS", this);
        heading->setGeometry(0, 8, 860, 30);
        heading->setStyleSheet
            (
                MONO +
                "font-size   : 15px;"
                "font-weight : bold;"
                "color       : #00eaff;"
                "background  : transparent;"
                );

        // Refresh Button
        refresh = new Button("REFRESH", 1005, 6, 140, 34, this);

        // View Card
        viewCard = new QLabel(this);
        viewCard->setGeometry(0, 50, 1150, 485);
        viewCard->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        viewCard->setWordWrap(true);
        viewCard->setStyleSheet
            (
                "background    : rgba(3, 12, 35, 0.92);"
                "border        : 1px solid rgba(0, 200, 255, 0.35);"
                "border-radius : 12px;"
                "color         : #c0dff5;"
                "font-family   : 'Courier New', monospace;"
                "font-size     : 12px;"
                "padding       : 14px;"
                );
        viewCard->setText("Click  Refresh  to load all records.");

        QObject::connect(refresh, &QPushButton::clicked, [this]()
                         {
                             viewCard->setText("Loading...");
                         });
    }
};

// =============================================================================
//  FILTER PANEL
// =============================================================================

class Filter : public QWidget
{
private:

    Card        *sortCard;
    QPushButton *solvedButton;
    QPushButton *pendingButton;
    QPushButton *coldButton;
    QLabel      *sortResult;

public:

    Filter(QWidget *parent = nullptr) : QWidget(parent)
    {
        // Filter Card
        sortCard = new Card(200, 0, 640, 118, this);

        // Heading
        QLabel *heading = new QLabel("FILTER BY STATUS", this);
        heading->setGeometry(220, 18, 600, 28);
        heading->setStyleSheet
            (
                MONO +
                "font-size   : 15px;"
                "font-weight : bold;"
                "color       : #00eaff;"
                "background  : transparent;"
                );

        // Divider Line
        QLabel *line = new QLabel(this);
        line->setGeometry(220, 52, 600, 1);
        line->setStyleSheet("background : rgba(0, 200, 255, 0.20);");

        // Filter Buttons
        solvedButton = new QPushButton("SOLVED", this);
        solvedButton->setGeometry(220, 68, 190, 42);
        solvedButton->setCursor(Qt::PointingHandCursor);
        solvedButton->setStyleSheet
            (
                "QPushButton         { background:rgba(0,30,60,0.80); color:#44ff99; font-family:'Courier New',monospace; font-size:12px; font-weight:bold; border:1px solid #44ff99; border-radius:8px; }"
                "QPushButton:hover   { background:#44ff99; color:#000000; }"
                "QPushButton:pressed { opacity:0.7; }"
                );

        pendingButton = new QPushButton("PENDING", this);
        pendingButton->setGeometry(422, 68, 190, 42);
        pendingButton->setCursor(Qt::PointingHandCursor);
        pendingButton->setStyleSheet
            (
                "QPushButton         { background:rgba(0,30,60,0.80); color:#ffcc44; font-family:'Courier New',monospace; font-size:12px; font-weight:bold; border:1px solid #ffcc44; border-radius:8px; }"
                "QPushButton:hover   { background:#ffcc44; color:#000000; }"
                "QPushButton:pressed { opacity:0.7; }"
                );

        coldButton = new QPushButton("COLD", this);
        coldButton->setGeometry(624, 68, 190, 42);
        coldButton->setCursor(Qt::PointingHandCursor);
        coldButton->setStyleSheet
            (
                "QPushButton         { background:rgba(0,30,60,0.80); color:#ff6666; font-family:'Courier New',monospace; font-size:12px; font-weight:bold; border:1px solid #ff6666; border-radius:8px; }"
                "QPushButton:hover   { background:#ff6666; color:#000000; }"
                "QPushButton:pressed { opacity:0.7; }"
                );

        // Result Area
        sortResult = new QLabel(this);
        sortResult->setGeometry(0, 128, 1100, 550);
        sortResult->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        sortResult->setWordWrap(true);
        sortResult->setStyleSheet
            (
                "background    : rgba(3, 12, 35, 0.92);"
                "border        : 1px solid rgba(0, 200, 255, 0.35);"
                "border-radius : 12px;"
                "color         : #c0dff5;"
                "font-family   : 'Courier New', monospace;"
                "font-size     : 12px;"
                "padding       : 14px;"
                );
        sortResult->setText("Press a button above");

        QObject::connect(solvedButton, &QPushButton::clicked, [this]()
                         {
                             sortResult->setText("No Solved cases found.");
                         });

        QObject::connect(pendingButton, &QPushButton::clicked, [this]()
                         {
                             sortResult->setText("No Pending cases found.");
                         });

        QObject::connect(coldButton, &QPushButton::clicked, [this]()
                         {
                             sortResult->setText("No Cold cases found.");
                         });
    }

    void          setDisplayText(const QString &text) { sortResult->setText(text); }
    QPushButton  *getSolvedButton()                   { return solvedButton;       }
    QPushButton  *getPendingButton()                  { return pendingButton;      }
    QPushButton  *getColdButton()                     { return coldButton;         }
};

// =============================================================================
//  CASE STATUS PAGE
//  isAdmin = true  → shows Update Status panel
//  isAdmin = false → View and Filter only
// =============================================================================

class CaseStatusPage : public QWidget
{
private:

    QLabel         *img;
    Card           *statusCard;
    QStackedWidget *stack;
    StatusView     *viewPage;
    Filter         *filterPage;
    Update         *updatePage;
    Button         *viewBtn;
    Button         *filterBtn;
    Button         *updateBtn;

    int solvedCount  = 0;
    int pendingCount = 0;
    int coldCount    = 0;

public:

    CaseStatusPage(bool isAdmin) : QWidget(nullptr)
    {
        setWindowTitle("Case Status - CRIME RECORD MANAGEMENT SYSTEM");

        // Background
        img = new QLabel(this);
        img->setPixmap(loadPixmap("backgroundThree.png"));
        img->setScaledContents(true);
        img->lower();

        // Sidebar Card
        statusCard = new Card(0, 0, 320, 900, this);

        // Sidebar Title
        QLabel *title = new QLabel("CRIME RECORD\nMANAGEMENT SYSTEM", this);
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
        QLabel *text = new QLabel("[ CASE  STATUS ]", this);
        text->setGeometry(0, 110, 320, 22);
        text->setAlignment(Qt::AlignCenter);
        text->setStyleSheet
            (
                MONO +
                "font-size     : 10px;"
                "letter-spacing: 4px;"
                "color         : #ffcc44;"
                "font-weight   : bold;"
                "background    : transparent;"
                );

        // Status Legend
        QLabel *solvedLegend = new QLabel("SOLVED", this);
        solvedLegend->setGeometry(30, 172, 270, 22);
        solvedLegend->setStyleSheet
            (
                MONO +
                "font-size     : 15px;"
                "letter-spacing: 4px;"
                "font-weight   : bold;"
                "color         : #44ff99;"
                "background    : transparent;"
                );

        QLabel *pendingLegend = new QLabel("PENDING", this);
        pendingLegend->setGeometry(30, 200, 270, 22);
        pendingLegend->setStyleSheet
            (
                MONO +
                "font-size     : 15px;"
                "letter-spacing: 4px;"
                "font-weight   : bold;"
                "color         : #ffcc44;"
                "background    : transparent;"
                );

        QLabel *coldLegend = new QLabel("COLD", this);
        coldLegend->setGeometry(30, 228, 270, 22);
        coldLegend->setStyleSheet
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

        // Sidebar Buttons
        viewBtn   = new Button("View All Cases",   25, 300, 270, 40, this);
        filterBtn = new Button("Filter by Status", 25, 360, 270, 40, this);

        if (isAdmin)
            updateBtn = new Button("Update Status", 25, 420, 270, 40, this);
        else
            updateBtn = nullptr;

        // Page Title
        QLabel *pageTitle = new QLabel("CASE STATUS MANAGEMENT", this);
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
        QLabel *pageSubtitle = new QLabel("Track and update the status of all crime cases", this);
        pageSubtitle->setGeometry(380, 95, 1180, 22);
        pageSubtitle->setStyleSheet
            (
                MONO +
                "font-size   : 15px;"
                "color       : #7ab8e0;"
                "background  : transparent;"
                "font-weight : bold;"
                );

        // Stat Cards
        QLabel *solvedCard = new QLabel(this);
        solvedCard->setGeometry(380, 140, 230, 90);
        solvedCard->setStyleSheet("background:rgba(0,20,50,0.85); border:1px solid #44ff99; border-radius:10px;");

        QLabel *solvedNumber = new QLabel(QString::number(solvedCount), this);
        solvedNumber->setGeometry(390, 150, 210, 44);
        solvedNumber->setAlignment(Qt::AlignCenter);
        solvedNumber->setStyleSheet(MONO + "font-size:30px; font-weight:900; color:#44ff99; background:transparent;");

        QLabel *solvedText = new QLabel("SOLVED", this);
        solvedText->setGeometry(390, 196, 210, 22);
        solvedText->setAlignment(Qt::AlignCenter);
        solvedText->setStyleSheet(MONO + "font-size:11px; letter-spacing:3px; color:#c0dff5; background:transparent;");

        QLabel *pendingCard = new QLabel(this);
        pendingCard->setGeometry(850, 140, 230, 90);
        pendingCard->setStyleSheet("background:rgba(0,20,50,0.85); border:1px solid #ffcc44; border-radius:10px;");

        QLabel *pendingNumber = new QLabel(QString::number(pendingCount), this);
        pendingNumber->setGeometry(860, 150, 210, 44);
        pendingNumber->setAlignment(Qt::AlignCenter);
        pendingNumber->setStyleSheet(MONO + "font-size:30px; font-weight:900; color:#ffcc44; background:transparent;");

        QLabel *pendingText = new QLabel("PENDING", this);
        pendingText->setGeometry(860, 196, 210, 22);
        pendingText->setAlignment(Qt::AlignCenter);
        pendingText->setStyleSheet(MONO + "font-size:11px; letter-spacing:3px; color:#c0dff5; background:transparent;");

        QLabel *coldCard = new QLabel(this);
        coldCard->setGeometry(1300, 140, 230, 90);
        coldCard->setStyleSheet("background:rgba(0,20,50,0.85); border:1px solid #ff6666; border-radius:10px;");

        QLabel *coldNumber = new QLabel(QString::number(coldCount), this);
        coldNumber->setGeometry(1310, 150, 210, 44);
        coldNumber->setAlignment(Qt::AlignCenter);
        coldNumber->setStyleSheet(MONO + "font-size:30px; font-weight:900; color:#ff6666; background:transparent;");

        QLabel *coldText = new QLabel("COLD", this);
        coldText->setGeometry(1310, 196, 210, 22);
        coldText->setAlignment(Qt::AlignCenter);
        coldText->setStyleSheet(MONO + "font-size:11px; letter-spacing:3px; color:#c0dff5; background:transparent;");

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

        // Stack
        stack = new QStackedWidget(this);
        stack->setGeometry(380, 250, 1160, 630);
        stack->setStyleSheet("background:transparent;");

        viewPage   = new StatusView(stack);
        filterPage = new Filter(stack);
        updatePage = new Update(stack);

        stack->addWidget(viewPage);    // index 0
        stack->addWidget(filterPage);  // index 1
        stack->addWidget(updatePage);  // index 2
        stack->setCurrentIndex(0);

        // ── Button Connections ────────────────────────────────────────────────

        QObject::connect(viewBtn, &QPushButton::clicked, [this]()
                         {
                             stack->setCurrentIndex(0);
                         });

        QObject::connect(filterBtn, &QPushButton::clicked, [this]()
                         {
                             stack->setCurrentIndex(1);
                         });

        if (isAdmin && updateBtn)
        {
            QObject::connect(updateBtn, &QPushButton::clicked, [this]()
                             {
                                 stack->setCurrentIndex(2);
                             });
        }
    }

    void resizeEvent(QResizeEvent *)
    {
        img->resize(size());
    }
};

#endif // CRIMESTATUS_H