#ifndef COURT_H
#define COURT_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QStackedWidget>
#include <QPushButton>

#include "common.h"

// =============================================================================
//  VIEW ALL PANEL
// =============================================================================

class ViewCourt : public QWidget
{
private:

    Button *refresh;
    QLabel *viewCard;

public:

    ViewCourt(QWidget *parent = nullptr) : QWidget(parent)
    {
        // Heading
        QLabel *heading = new QLabel("ALL COURT PROCEEDINGS", this);
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
        refresh = new Button("REFRESH", 820, 6, 140, 32, this);

        // View Card
        viewCard = new QLabel(this);
        viewCard->setGeometry(0, 50, 1150, 550);
        viewCard->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        viewCard->setWordWrap(true);
        viewCard->setStyleSheet
            (
                MONO +
                "font-size     : 12px;"
                "color         : #c0dff5;"
                "background    : rgba(3, 12, 35, 0.92);"
                "border        : 1px solid rgba(0, 200, 255, 0.35);"
                "border-radius : 12px;"
                "padding       : 14px;"
                );
        viewCard->setText("  Click  REFRESH  to load all proceedings.");

        // Connection
        QObject::connect(refresh, &QPushButton::clicked, [this]()
                         {
                             viewCard->setText("  Loading...");
                         });
    }

    void    setDisplayText(const QString &text) { viewCard->setText(text); }
    Button *getRefreshButton()                  { return refresh;          }
};

// =============================================================================
//  FILTER PANEL
// =============================================================================

class FilterCourt : public QWidget
{
private:

    Card   *filterCard;
    Button *ongoingButton;
    Button *onHoldButton;
    Button *verdictButton;
    QLabel *filterResult;

public:

    FilterCourt(QWidget *parent = nullptr) : QWidget(parent)
    {
        // Filter Card
        filterCard = new Card(0, 0, 640, 110, this);

        // Heading
        QLabel *heading = new QLabel("FILTER BY COURT STATUS", this);
        heading->setGeometry(20, 18, 600, 28);
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
        line->setGeometry(20, 52, 600, 1);
        line->setStyleSheet("background : rgba(0, 200, 255, 0.20);");

        // Filter Buttons
        ongoingButton = new Button("  ONGOING",         20,  64, 180, 40, this);
        onHoldButton  = new Button("  ON HOLD",         214, 64, 180, 40, this);
        verdictButton = new Button("  VERDICT REACHED", 408, 64, 210, 40, this);

        ongoingButton->setStyleSheet
            (
                "QPushButton         { background:rgba(0,30,60,0.80); color:#00eaff; font-family:'Courier New',monospace; font-size:12px; font-weight:bold; border:1px solid #00eaff; border-radius:8px; }"
                "QPushButton:hover   { background:#00eaff; color:#000000; }"
                "QPushButton:pressed { opacity:0.7; }"
                );

        onHoldButton->setStyleSheet
            (
                "QPushButton         { background:rgba(0,30,60,0.80); color:#ffcc44; font-family:'Courier New',monospace; font-size:12px; font-weight:bold; border:1px solid #ffcc44; border-radius:8px; }"
                "QPushButton:hover   { background:#ffcc44; color:#000000; }"
                "QPushButton:pressed { opacity:0.7; }"
                );

        verdictButton->setStyleSheet
            (
                "QPushButton         { background:rgba(0,30,60,0.80); color:#44ff99; font-family:'Courier New',monospace; font-size:12px; font-weight:bold; border:1px solid #44ff99; border-radius:8px; }"
                "QPushButton:hover   { background:#44ff99; color:#000000; }"
                "QPushButton:pressed { opacity:0.7; }"
                );

        // Result Area
        filterResult = new QLabel(this);
        filterResult->setGeometry(0, 120, 1150, 480);
        filterResult->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        filterResult->setWordWrap(true);
        filterResult->setStyleSheet
            (
                MONO +
                "font-size     : 12px;"
                "color         : #c0dff5;"
                "background    : rgba(3, 12, 35, 0.92);"
                "border        : 1px solid rgba(0, 200, 255, 0.35);"
                "border-radius : 12px;"
                "padding       : 14px;"
                );
        filterResult->setText("  Press a button above to filter proceedings.");

        // Connections
        QObject::connect(ongoingButton, &QPushButton::clicked, [this]()
                         {
                             filterResult->setText("  Loading Ongoing proceedings...");
                         });

        QObject::connect(onHoldButton, &QPushButton::clicked, [this]()
                         {
                             filterResult->setText("  Loading On Hold proceedings...");
                         });

        QObject::connect(verdictButton, &QPushButton::clicked, [this]()
                         {
                             filterResult->setText("  Loading Verdict Reached proceedings...");
                         });
    }

    void    setDisplayText(const QString &text) { filterResult->setText(text);  }
    Button *getOngoingButton()                  { return ongoingButton;          }
    Button *getOnHoldButton()                   { return onHoldButton;           }
    Button *getVerdictButton()                  { return verdictButton;          }
};

// =============================================================================
//  UPDATE STATUS PANEL  (Admin only)
// =============================================================================

class UpdateCourt : public QWidget
{
private:

    Card   *updateCard;
    Box    *caseIDBox;
    Button *loadButton;
    QLabel *infoLbl;
    QLabel *updateMsg;

    QPushButton *ongoingButton;
    QPushButton *onHoldButton;
    QPushButton *verdictButton;

public:

    UpdateCourt(QWidget *parent = nullptr) : QWidget(parent)
    {
        // Update Card
        updateCard = new Card(0, 0, 700, 360, this);

        // Heading
        QLabel *title = new QLabel("UPDATE COURT STATUS", this);
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
        QLabel *caseIDLbl = new QLabel("Case ID", this);
        caseIDLbl->setGeometry(20, 68, 300, 22);
        caseIDLbl->setStyleSheet
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
        QLabel *statusLbl = new QLabel("New Court Status", this);
        statusLbl->setGeometry(20, 172, 300, 22);
        statusLbl->setStyleSheet
            (
                MONO +
                "font-size   : 14px;"
                "font-weight : bold;"
                "color       : #a0d8f0;"
                "background  : transparent;"
                );

        // Status Buttons
        ongoingButton = new QPushButton("  ONGOING", this);
        ongoingButton->setGeometry(20, 210, 170, 48);
        ongoingButton->setCursor(Qt::PointingHandCursor);
        ongoingButton->setStyleSheet
            (
                "QPushButton         { background:rgba(0,30,60,0.80); color:#00eaff; font-family:'Courier New',monospace; font-size:12px; font-weight:bold; border:1px solid #00eaff; border-radius:8px; }"
                "QPushButton:hover   { background:#00eaff; color:#000000; }"
                "QPushButton:pressed { opacity:0.7; }"
                );

        onHoldButton = new QPushButton("  ON HOLD", this);
        onHoldButton->setGeometry(210, 210, 170, 48);
        onHoldButton->setCursor(Qt::PointingHandCursor);
        onHoldButton->setStyleSheet
            (
                "QPushButton         { background:rgba(0,30,60,0.80); color:#ffcc44; font-family:'Courier New',monospace; font-size:12px; font-weight:bold; border:1px solid #ffcc44; border-radius:8px; }"
                "QPushButton:hover   { background:#ffcc44; color:#000000; }"
                "QPushButton:pressed { opacity:0.7; }"
                );

        verdictButton = new QPushButton("  VERDICT REACHED", this);
        verdictButton->setGeometry(400, 210, 200, 48);
        verdictButton->setCursor(Qt::PointingHandCursor);
        verdictButton->setStyleSheet
            (
                "QPushButton         { background:rgba(0,30,60,0.80); color:#44ff99; font-family:'Courier New',monospace; font-size:12px; font-weight:bold; border:1px solid #44ff99; border-radius:8px; }"
                "QPushButton:hover   { background:#44ff99; color:#000000; }"
                "QPushButton:pressed { opacity:0.7; }"
                );

        // Update Message
        updateMsg = new QLabel("", this);
        updateMsg->setGeometry(20, 300, 660, 22);
        updateMsg->setStyleSheet
            (
                MONO +
                "font-size  : 12px;"
                "color      : #00eaff;"
                "background : transparent;"
                );

        // Connections
        QObject::connect(loadButton, &QPushButton::clicked, [this]()
                         {
                             infoLbl->setText("  Loading record...");
                         });

        QObject::connect(ongoingButton, &QPushButton::clicked, [this]()
                         {
                             updateMsg->setText("  Status set to: ONGOING");
                         });

        QObject::connect(onHoldButton, &QPushButton::clicked, [this]()
                         {
                             updateMsg->setText("  Status set to: ON HOLD");
                         });

        QObject::connect(verdictButton, &QPushButton::clicked, [this]()
                         {
                             updateMsg->setText("  Status set to: VERDICT REACHED");
                         });
    }

    QString      getCaseID()          const { return caseIDBox->text().trimmed(); }
    Button      *getLoadButton()            { return loadButton;                  }
    QPushButton *getOngoingButton()         { return ongoingButton;               }
    QPushButton *getOnHoldButton()          { return onHoldButton;                }
    QPushButton *getVerdictButton()         { return verdictButton;               }

    void setInfo(const QString &text)
    {
        infoLbl->setText(text);
    }

    void setMessage(const QString &text, const QString &color)
    {
        updateMsg->setStyleSheet
            (
                MONO +
                "font-size  : 12px;"
                "color      : " + color + ";"
                          "background : transparent;"
                );
        updateMsg->setText(text);
    }
};

// =============================================================================
//  ADD COURT RECORD PANEL
// =============================================================================

class AddCourt : public QWidget
{
private:

    Card   *addCard;
    Box    *caseIDBox;
    Box    *accusedBox;
    Box    *crimeBox;
    QLabel *feedback;
    Button *saveButton;
    Button *clearButton;

public:

    AddCourt(QWidget *parent = nullptr) : QWidget(parent)
    {
        // Add Card
        addCard = new Card(0, 0, 710, 420, this);

        // Heading
        QLabel *heading = new QLabel("ADD COURT PROCEEDING", this);
        heading->setGeometry(20, 18, 670, 28);
        heading->setStyleSheet
            (
                MONO +
                "font-size   : 15px;"
                "font-weight : bold;"
                "color       : #00eaff;"
                "background  : transparent;"
                );

        // Divider Line
        QLabel *headingLine = new QLabel(this);
        headingLine->setGeometry(20, 52, 670, 1);
        headingLine->setStyleSheet("background : rgba(0, 200, 255, 0.20);");

        // Case ID Label
        QLabel *idLabel = new QLabel("Case ID  *", this);
        idLabel->setGeometry(20, 68, 300, 22);
        idLabel->setStyleSheet
            (
                MONO +
                "font-size   : 14px;"
                "font-weight : bold;"
                "color       : #a0d8f0;"
                "background  : transparent;"
                );

        caseIDBox = new Box(20, 94, 670, 38, "e.g.  CR-001", this);

        // Accused Name Label
        QLabel *accusedLabel = new QLabel("Accused Name  *", this);
        accusedLabel->setGeometry(20, 148, 300, 22);
        accusedLabel->setStyleSheet
            (
                MONO +
                "font-size   : 14px;"
                "font-weight : bold;"
                "color       : #a0d8f0;"
                "background  : transparent;"
                );

        accusedBox = new Box(20, 174, 670, 38, "e.g.  Ali Hassan", this);

        // Crime Type Label
        QLabel *crimeLabel = new QLabel("Crime Type  *", this);
        crimeLabel->setGeometry(20, 228, 300, 22);
        crimeLabel->setStyleSheet
            (
                MONO +
                "font-size   : 14px;"
                "font-weight : bold;"
                "color       : #a0d8f0;"
                "background  : transparent;"
                );

        crimeBox = new Box(20, 254, 670, 38, "e.g.  Murder", this);

        // Note
        QLabel *note = new QLabel("Initial status will be set to  Ongoing  automatically.", this);
        note->setGeometry(20, 308, 670, 22);
        note->setStyleSheet
            (
                MONO +
                "font-size  : 12px;"
                "color      : #ffcc44;"
                "background : transparent;"
                );

        // Feedback
        feedback = new QLabel("", this);
        feedback->setGeometry(20, 336, 670, 22);
        feedback->setStyleSheet
            (
                MONO +
                "font-size  : 12px;"
                "color      : #00eaff;"
                "background : transparent;"
                );

        // Buttons
        saveButton  = new Button("SAVE RECORD", 20,  368, 200, 44, this);
        clearButton = new Button("CLEAR",       234, 368, 120, 44, this);

        clearButton->setStyleSheet
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
                "    border-radius  : 8px;"
                "    text-align     : left;"
                "    padding-left   : 20px;"
                "}"
                "QPushButton:hover"
                "{"
                "    background : rgba(180, 0, 0, 0.80);"
                "    border     : 1px solid #ff4444;"
                "    color      : #ffffff;"
                "}"
                "QPushButton:pressed"
                "{"
                "    background : #5a0000;"
                "}"
                );

        // Connections
        QObject::connect(clearButton, &QPushButton::clicked, [this]()
                         {
                             caseIDBox->clear();
                             accusedBox->clear();
                             crimeBox->clear();
                             feedback->setText("");
                         });

        QObject::connect(saveButton, &QPushButton::clicked, [this]()
                         {
                             feedback->setText("  Saving...");
                         });
    }

    QString getCaseID()    const { return caseIDBox->text().trimmed();   }
    QString getAccused()   const { return accusedBox->text().trimmed();  }
    QString getCrimeType() const { return crimeBox->text().trimmed();    }

    void setFeedback(const QString &text, const QString &color)
    {
        feedback->setStyleSheet
            (
                MONO +
                "font-size  : 12px;"
                "color      : " + color + ";"
                          "background : transparent;"
                );
        feedback->setText(text);
    }

    void clearFields()
    {
        caseIDBox->clear();
        accusedBox->clear();
        crimeBox->clear();
        feedback->setText("");
    }

    Button *getSaveButton()  { return saveButton;  }
    Button *getClearButton() { return clearButton; }
};

// =============================================================================
//  COURT PROCEEDINGS MAIN WINDOW
// =============================================================================

class CourtProceedings : public QWidget
{
private:

    QLabel *img;
    Card   *sideCard;
    Button *sideButton[4];

    QLabel *ongoingNumber;
    QLabel *onHoldNumber;
    QLabel *verdictNumber;

    ViewCourt   *panelView;
    FilterCourt *panelFilter;
    UpdateCourt *panelUpdate;
    AddCourt    *panelAdd;

public:

    CourtProceedings(bool isAdmin) : QWidget(nullptr)
    {
        setWindowTitle("Court Proceedings - CRIME RECORD MANAGEMENT SYSTEM");

        // Background
        img = new QLabel(this);
        img->setPixmap(loadPixmap("backgroundThree.png"));
        img->setScaledContents(true);
        img->lower();

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
        QLabel *tag = new QLabel("[ COURT PROCEEDINGS ]", this);
        tag->setGeometry(0, 110, 320, 22);
        tag->setAlignment(Qt::AlignCenter);
        tag->setStyleSheet
            (
                MONO +
                "font-size     : 10px;"
                "letter-spacing: 4px;"
                "color         : #ffcc44;"
                "font-weight   : bold;"
                "background    : transparent;"
                );

        // Status Legend
        QLabel *ongoingLeg = new QLabel("ONGOING", this);
        ongoingLeg->setGeometry(30, 172, 270, 22);
        ongoingLeg->setStyleSheet
            (
                MONO +
                "font-size     : 15px;"
                "letter-spacing: 4px;"
                "font-weight   : bold;"
                "color         : #00eaff;"
                "background    : transparent;"
                );

        QLabel *onHoldLeg = new QLabel("ON HOLD", this);
        onHoldLeg->setGeometry(30, 200, 270, 22);
        onHoldLeg->setStyleSheet
            (
                MONO +
                "font-size     : 15px;"
                "letter-spacing: 4px;"
                "font-weight   : bold;"
                "color         : #ffcc44;"
                "background    : transparent;"
                );

        QLabel *verdictLeg = new QLabel("VERDICT REACHED", this);
        verdictLeg->setGeometry(30, 228, 270, 22);
        verdictLeg->setStyleSheet
            (
                MONO +
                "font-size     : 15px;"
                "letter-spacing: 4px;"
                "font-weight   : bold;"
                "color         : #44ff99;"
                "background    : transparent;"
                );

        // Second Divider
        QLabel *lineTwo = new QLabel(this);
        lineTwo->setGeometry(30, 264, 260, 1);
        lineTwo->setStyleSheet("background: rgba(0,200,255,0.20);");

        // Sidebar Buttons
        sideButton[0] = new Button("View All",         25, 300, 270, 40, this);
        sideButton[1] = new Button("Filter by Status", 25, 360, 270, 40, this);

        if (isAdmin)
        {
            sideButton[2] = new Button("Update Status", 25, 420, 270, 40, this);
            sideButton[3] = new Button("Add Record",    25, 480, 270, 40, this);
        }
        else
        {
            sideButton[2] = nullptr;
            sideButton[3] = nullptr;
        }

        // Page Title
        QLabel *pageTitle = new QLabel("COURT PROCEEDINGS", this);
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
        QLabel *pageSubtitle = new QLabel("Track and update the legal progress of all crime cases", this);
        pageSubtitle->setGeometry(380, 95, 1180, 22);
        pageSubtitle->setStyleSheet
            (
                MONO +
                "font-size   : 12px;"
                "font-weight : bold;"
                "color       : #7ab8e0;"
                "background  : transparent;"
                );

        // Stat Cards
        QLabel *ongoingCard = new QLabel(this);
        ongoingCard->setGeometry(380, 140, 230, 90);
        ongoingCard->setStyleSheet("background:rgba(0,20,50,0.85); border:1px solid #00eaff; border-radius:10px;");

        ongoingNumber = new QLabel("0", this);
        ongoingNumber->setGeometry(390, 150, 210, 44);
        ongoingNumber->setAlignment(Qt::AlignCenter);
        ongoingNumber->setStyleSheet(MONO + "font-size:30px; font-weight:900; color:#00eaff; background:transparent;");

        QLabel *ongoingText = new QLabel("ONGOING", this);
        ongoingText->setGeometry(390, 196, 210, 22);
        ongoingText->setAlignment(Qt::AlignCenter);
        ongoingText->setStyleSheet(MONO + "font-size:11px; letter-spacing:3px; color:#c0dff5; background:transparent;");

        QLabel *onHoldCard = new QLabel(this);
        onHoldCard->setGeometry(850, 140, 230, 90);
        onHoldCard->setStyleSheet("background:rgba(0,20,50,0.85); border:1px solid #ffcc44; border-radius:10px;");

        onHoldNumber = new QLabel("0", this);
        onHoldNumber->setGeometry(860, 150, 210, 44);
        onHoldNumber->setAlignment(Qt::AlignCenter);
        onHoldNumber->setStyleSheet(MONO + "font-size:30px; font-weight:900; color:#ffcc44; background:transparent;");

        QLabel *onHoldText = new QLabel("ON HOLD", this);
        onHoldText->setGeometry(860, 196, 210, 22);
        onHoldText->setAlignment(Qt::AlignCenter);
        onHoldText->setStyleSheet(MONO + "font-size:11px; letter-spacing:3px; color:#c0dff5; background:transparent;");

        QLabel *verdictCard = new QLabel(this);
        verdictCard->setGeometry(1300, 140, 230, 90);
        verdictCard->setStyleSheet("background:rgba(0,20,50,0.85); border:1px solid #44ff99; border-radius:10px;");

        verdictNumber = new QLabel("0", this);
        verdictNumber->setGeometry(1310, 150, 210, 44);
        verdictNumber->setAlignment(Qt::AlignCenter);
        verdictNumber->setStyleSheet(MONO + "font-size:30px; font-weight:900; color:#44ff99; background:transparent;");

        QLabel *verdictText = new QLabel("VERDICT REACHED", this);
        verdictText->setGeometry(1310, 196, 210, 22);
        verdictText->setAlignment(Qt::AlignCenter);
        verdictText->setStyleSheet(MONO + "font-size:11px; letter-spacing:3px; color:#c0dff5; background:transparent;");

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

        // Panels
        panelView   = new ViewCourt(this);
        panelFilter = new FilterCourt(this);
        panelUpdate = new UpdateCourt(this);
        panelAdd    = new AddCourt(this);

        panelView->setGeometry(380, 248, 1180, 610);
        panelFilter->setGeometry(380, 248, 1180, 610);
        panelUpdate->setGeometry(380, 248, 1180, 610);
        panelAdd->setGeometry(380, 248, 1180, 610);

        panelView->show();
        panelFilter->hide();
        panelUpdate->hide();
        panelAdd->hide();

        // Button Connections
        QObject::connect(sideButton[0], &QPushButton::clicked, [this]()
                         {
                             panelView->show();
                             panelFilter->hide();
                             panelUpdate->hide();
                             panelAdd->hide();
                         });

        QObject::connect(sideButton[1], &QPushButton::clicked, [this]()
                         {
                             panelView->hide();
                             panelFilter->show();
                             panelUpdate->hide();
                             panelAdd->hide();
                         });

        if (isAdmin && sideButton[2] && sideButton[3])
        {
            QObject::connect(sideButton[2], &QPushButton::clicked, [this]()
                             {
                                 panelView->hide();
                                 panelFilter->hide();
                                 panelUpdate->show();
                                 panelAdd->hide();
                             });

            QObject::connect(sideButton[3], &QPushButton::clicked, [this]()
                             {
                                 panelView->hide();
                                 panelFilter->hide();
                                 panelUpdate->hide();
                                 panelAdd->show();
                             });
        }
    }

    void resizeEvent(QResizeEvent *)
    {
        img->resize(size());
    }

    ViewCourt   *getViewPanel()   { return panelView;   }
    FilterCourt *getFilterPanel() { return panelFilter; }
    UpdateCourt *getUpdatePanel() { return panelUpdate; }
    AddCourt    *getAddPanel()    { return panelAdd;    }

    void setOngoingCount(int n)  { ongoingNumber->setText(QString::number(n)); }
    void setOnHoldCount(int n)   { onHoldNumber->setText(QString::number(n));  }
    void setVerdictCount(int n)  { verdictNumber->setText(QString::number(n)); }
};

#endif // COURT_H