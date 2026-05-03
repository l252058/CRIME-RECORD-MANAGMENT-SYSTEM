#ifndef CRIMERECORDS_H
#define CRIMERECORDS_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QTextEdit>

#include "common.h"


class View : public QWidget
{
private:
    Button *refresh;
    QLabel *viewCard;
public:
    View(QWidget *parent = nullptr) : QWidget(parent)
    {
        QLabel *heading = new QLabel("  ALL CRIME RECORDS", this);
        heading->setGeometry(0, 8, 860, 30);
        heading->setStyleSheet
        (
            MONO +
            "font-size   : 15px;"
            "font-weight : bold;"
            "color       : #00eaff;"
            "background  : transparent;"
        );

        refresh = new Button("REFRESH", 1000, 6, 140, 34, this);

        viewCard = new QLabel(this);
        viewCard->setGeometry(0, 50, 1150, 625);
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

    void setDisplayText(const QString &text)
    {
        viewCard->setText(text);
    }

    Button *getRefreshButton()
    {
        return refresh;
    }
};

class Search : public QWidget
{
private:
    Card   *searchCard;
    Box    *caseIDBox;
    Button *searchOne;
    Box    *locationBox;
    Button *searchTwo;
    QLabel *searchResult;
public:

    Search(QWidget *parent = nullptr) : QWidget(parent)
    {
        searchCard = new Card(0, 0, 720, 220, this);

        QLabel *heading = new QLabel("SEARCH CRIME RECORDS", this);
        heading->setGeometry(20, 18, 680, 28);
        heading->setStyleSheet
        (
            MONO +
            "font-size   : 15px;"
            "font-weight : bold;"
            "color       : #00eaff;"
            "background  : transparent;"
        );

        QLabel *line = new QLabel(this);
        line->setGeometry(20, 52, 680, 1);
        line->setStyleSheet("background : rgba(0, 200, 255, 0.20);");

        QLabel *caseIDLabel = new QLabel("Search by Case ID", this);
        caseIDLabel->setGeometry(20, 68, 300, 20);
        caseIDLabel->setStyleSheet
        (
            MONO +
            "font-size   : 15px;"
            "color       : #a0d8f0;"
            "background  : transparent;"
            "font-weight : bold;"
        );

        caseIDBox = new Box(20, 92, 430, 38, "e.g.  CR-001", this);
        searchOne = new Button("Search", 462, 92, 180, 38, this);

        QLabel *locationLabel = new QLabel("Search by Location", this);
        locationLabel->setGeometry(20, 144, 300, 20);
        locationLabel->setStyleSheet
        (
            MONO +
            "font-size   : 15px;"
            "color       : #a0d8f0;"
            "background  : transparent;"
            "font-weight : bold;"
        );

        locationBox = new Box(20, 168, 430, 38, "e.g.  NEWYORK", this);
        searchTwo   = new Button("Search", 462, 168, 180, 38, this);

        searchResult = new QLabel(this);
        searchResult->setGeometry(0, 240, 1100, 450);
        searchResult->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        searchResult->setWordWrap(true);
        searchResult->setStyleSheet
        (
            "background    : rgba(3, 12, 35, 0.92);"
            "border        : 1px solid rgba(0, 200, 255, 0.35);"
            "border-radius : 12px;"
            "color         : #c0dff5;"
            "font-family   : 'Courier New', monospace;"
            "font-size     : 12px;"
            "padding       : 14px;"
        );
        searchResult->setText("Enter a search term above and press Search.");

        QObject::connect(searchOne, &QPushButton::clicked, [this]()
        {
            searchResult->setText("  Searching by Case ID...");
        });

        QObject::connect(searchTwo, &QPushButton::clicked, [this]()
        {
            searchResult->setText("  Searching by Location...");
        });
    }

    QString getCaseIDQuery() const
    {
        return caseIDBox->text().trimmed();
    }

    QString getLocationQuery() const
    {
        return locationBox->text().trimmed();
    }

    void setDisplayText(const QString &text)
    {
        searchResult->setText(text);
    }

    Button *getSearchOneButton()
    {
        return searchOne;
    }

    Button *getSearchTwoButton()
    {
        return searchTwo;
    }
};

class Sort : public QWidget
{
private:

    Card   *sortCard;
    Button *caseIDSort;
    Button *locationSort;
    Button *statusSort;
    QLabel *sortResult;

public:

    Sort(QWidget *parent = nullptr) : QWidget(parent)
    {
        sortCard = new Card(200, 0, 640, 118, this);

        QLabel *heading = new QLabel("SORT CRIME RECORDS", this);
        heading->setGeometry(220, 18, 600, 28);
        heading->setStyleSheet
        (
            MONO +
            "font-size   : 15px;"
            "font-weight : bold;"
            "color       : #00eaff;"
            "background  : transparent;"
        );

        QLabel *line = new QLabel(this);
        line->setGeometry(220, 52, 600, 1);
        line->setStyleSheet("background : rgba(0, 200, 255, 0.20);");

        caseIDSort   = new Button("By Case ID",  220, 68, 190, 42, this);
        locationSort = new Button("By Location", 422, 68, 190, 42, this);
        statusSort   = new Button("By Status",   624, 68, 190, 42, this);

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
        sortResult->setText("Press a sort button above.");

        QObject::connect(caseIDSort, &QPushButton::clicked, [this]()
        {
            sortResult->setText("  Sorting by Case ID...");
        });

        QObject::connect(locationSort, &QPushButton::clicked, [this]()
        {
            sortResult->setText("  Sorting by Location...");
        });

        QObject::connect(statusSort, &QPushButton::clicked, [this]()
        {
            sortResult->setText("  Sorting by Status...");
        });
    }

    void setDisplayText(const QString &text)
    {
        sortResult->setText(text);
    }

    Button *getCaseIDSortButton()
    {
        return caseIDSort;
    }

    Button *getLocationSortButton()
    {
        return locationSort;
    }

    Button *getStatusSortButton()
    {
        return statusSort;
    }
};

class Modify : public QWidget
{
private:

    Card      *modifyCard;
    Box       *caseIDBox;
    Box       *locationBox;
    Box       *typeBox;
    QTextEdit *descriptionBox;
    Button    *loadButton;
    Button    *saveButton;
    Button    *deleteButton;
    QLabel    *message;
    QString    selectedStatus;

public:

    Modify(QWidget *parent = nullptr) : QWidget(parent), selectedStatus("Pending")
    {
        modifyCard = new Card(0, 0, 700, 600, this);

        QLabel *heading = new QLabel("  MODIFY / DELETE RECORD", this);
        heading->setGeometry(20, 18, 680, 28);
        heading->setStyleSheet
        (
            MONO +
            "font-size   : 15px;"
            "font-weight : bold;"
            "color       : #ffcc44;"
            "background  : transparent;"
        );

        QLabel *headingLine = new QLabel(this);
        headingLine->setGeometry(20, 52, 680, 1);
        headingLine->setStyleSheet("background : rgba(255, 200, 0, 0.20);");

        QLabel *caseIDLabel = new QLabel("Enter Case ID to load the record", this);
        caseIDLabel->setGeometry(20, 68, 680, 20);
        caseIDLabel->setStyleSheet
        (
            MONO +
            "font-size  : 12px;"
            "color      : #a0d8f0;"
            "background : transparent;"
        );

        caseIDBox  = new Box(20, 92, 430, 38, "e.g.  CR-001", this);
        loadButton = new Button("  Load Record", 462, 92, 180, 38, this);

        QLabel *editLabel = new QLabel("Edit the fields below then Save or Delete", this);
        editLabel->setGeometry(20, 148, 680, 20);
        editLabel->setStyleSheet
        (
            MONO +
            "font-size  : 12px;"
            "color      : #a0d8f0;"
            "background : transparent;"
        );

        QLabel *locationLabel = new QLabel(" Location  *", this);
        locationLabel->setGeometry(20, 178, 300, 20);
        locationLabel->setStyleSheet
        (
            MONO +
            "font-size   : 15px;"
            "font-weight : bold;"
            "color       : #00eaff;"
            "background  : transparent;"
        );

        locationBox = new Box(20, 202, 670, 38, " ", this);

        QLabel *typeLabel = new QLabel(" Crime Type  *", this);
        typeLabel->setGeometry(20, 252, 300, 20);
        typeLabel->setStyleSheet
        (
            MONO +
            "font-size   : 15px;"
            "font-weight : bold;"
            "color       : #00eaff;"
            "background  : transparent;"
        );

        typeBox = new Box(20, 276, 670, 38, " ", this);

        QLabel *descriptionLabel = new QLabel(" Description", this);
        descriptionLabel->setGeometry(20, 326, 300, 20);
        descriptionLabel->setStyleSheet
        (
            MONO +
            "font-size   : 15px;"
            "font-weight : bold;"
            "color       : #00eaff;"
            "background  : transparent;"
        );

        descriptionBox = new QTextEdit(this);
        descriptionBox->setGeometry(20, 350, 670, 80);
        descriptionBox->setStyleSheet
        (
            "QTextEdit"
            "{"
            "    background    : rgba(0, 15, 45, 0.88);"
            "    border        : 1px solid rgba(0, 200, 255, 0.40);"
            "    border-radius : 5px;"
            "    color         : #e0f4ff;"
            "    font-family   : 'Courier New', monospace;"
            "    font-size     : 13px;"
            "    padding       : 6px;"
            "}"
            "QTextEdit:focus"
            "{"
            "    border : 1px solid #00eaff;"
            "}"
        );

        QLabel *statusLabel = new QLabel("Status", this);
        statusLabel->setGeometry(20, 442, 680, 20);
        statusLabel->setStyleSheet
        (
            MONO +
            "font-size   : 15px;"
            "font-weight : bold;"
            "color       : #7ab8e0;"
            "background  : transparent;"
        );

        QPushButton *pendingButton = new QPushButton("PENDING", this);
        pendingButton->setGeometry(20, 466, 170, 38);
        pendingButton->setCursor(Qt::PointingHandCursor);
        pendingButton->setStyleSheet
        (
            "QPushButton"
            "{"
                "background:rgba(0,30,60,0.80);"
                "color:#ffcc44;"
                "font-family:'Courier New',monospace;"
                "font-size:12px;"
                "font-weight:bold;"
                "border:1px solid #ffcc44;"
                "border-radius:8px;"
            "}"
            "QPushButton:hover"
            "{"
                "background:#ffcc44;"
                "color:#000000;"
            "}"
        );

        QPushButton *solvedButton = new QPushButton("SOLVED", this);
        solvedButton->setGeometry(210, 466, 170, 38);
        solvedButton->setCursor(Qt::PointingHandCursor);
        solvedButton->setStyleSheet
        (
            "QPushButton"
            "{"
                "background:rgba(0,30,60,0.80);"
                "color:#44ff99;"
                "font-family:'Courier New',monospace;"
                "font-size:12px;"
                "font-weight:bold;"
                "border:1px solid #44ff99;"
                "border-radius:8px;"
            "}"
            "QPushButton:hover"
            "{"
                "background:#44ff99;"
                "color:#000000;"
            "}"
        );

        QPushButton *coldButton = new QPushButton("COLD", this);
        coldButton->setGeometry(400, 466, 170, 38);
        coldButton->setCursor(Qt::PointingHandCursor);
        coldButton->setStyleSheet
        (
            "QPushButton"
            "{"
                "background:rgba(0,30,60,0.80);"
                "color:#ff6666;"
                "font-family:'Courier New',monospace;"
                "font-size:12px;"
                "font-weight:bold;"
                "border:1px solid #ff6666; border-radius:8px;"
            "}"
            "QPushButton:hover"
            "{"
                "background:#ff6666;"
                "color:#000000;"
            "}"
        );

        message = new QLabel("", this);
        message->setGeometry(20, 514, 680, 22);
        message->setStyleSheet
        (
            MONO +
            "font-size  : 12px;"
            "color      : #00eaff;"
            "background : transparent;"
        );

        saveButton   = new Button("SAVE CHANGES",  20,  546, 210, 42, this);

        deleteButton = new Button("DELETE RECORD", 244, 546, 210, 42, this);
        deleteButton->setStyleSheet
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

        QObject::connect(pendingButton, &QPushButton::clicked, [this]()
        {
            selectedStatus = "Pending";
            message->setText("  Status selected: Pending");
        });

        QObject::connect(solvedButton, &QPushButton::clicked, [this]()
        {
            selectedStatus = "Solved";
            message->setText("  Status selected: Solved");
        });

        QObject::connect(coldButton, &QPushButton::clicked, [this]()
                         {
                             selectedStatus = "Cold";
                             message->setText("  Status selected: Cold");
                         });

        // Load Button (GUI only)
        QObject::connect(loadButton, &QPushButton::clicked, [this]()
                         {
                             message->setText("  Enter a valid Case ID to load.");
                         });

        // Save Button (GUI only)
        QObject::connect(saveButton, &QPushButton::clicked, [this]()
                         {
                             message->setText("  Load a record first.");
                         });

        // Delete Button (GUI only)
        QObject::connect(deleteButton, &QPushButton::clicked, [this]()
                         {
                             message->setText("  Load a record first.");
                         });
    }

    QString getCaseID()      const { return caseIDBox->text().trimmed();             }
    QString getLocation()    const { return locationBox->text().trimmed();            }
    QString getCrimeType()   const { return typeBox->text().trimmed();                }
    QString getDescription() const { return descriptionBox->toPlainText().trimmed();  }
    QString getStatus()      const { return selectedStatus;                            }

    void setLocation(const QString    &value) { locationBox->setText(value);          }
    void setCrimeType(const QString   &value) { typeBox->setText(value);              }
    void setDescription(const QString &value) { descriptionBox->setPlainText(value);  }
    void setStatus(const QString      &value) { selectedStatus = value;               }

    void setMessage(const QString &text, const QString &color)
    {
        message->setStyleSheet
            (
                MONO +
                "font-size  : 12px;"
                "color      : " + color + ";"
                          "background : transparent;"
                );
        message->setText(text);
    }

    Button *getLoadButton()   { return loadButton;   }
    Button *getSaveButton()   { return saveButton;   }
    Button *getDeleteButton() { return deleteButton; }

    void reset()
    {
        caseIDBox->clear();
        locationBox->clear();
        typeBox->clear();
        descriptionBox->clear();
        selectedStatus = "Pending";
        message->setText("");
    }
};

// =============================================================================
//  CRIME RECORD PAGE
//  isAdmin = true  → all 5 panels (Create, View, Search, Sort, Modify/Delete)
//  isAdmin = false → 3 panels     (View, Search, Sort)
// =============================================================================

class CrimeRecordPage : public QWidget
{
private:

    QLabel    *img;
    Card      *recordBar;

    // Create panel widgets
    Card      *newRecordCard;
    QLabel    *newRecordHeading;
    QLabel    *createLine;
    QLabel    *caseIDLabel;
    Box       *caseIDBox;
    QLabel    *locationLabel;
    Box       *locationBox;
    QLabel    *crimeTypeLabel;
    Box       *typeBox;
    QLabel    *descLabel;
    QTextEdit *descriptionBox;
    QLabel    *footNote;
    QLabel    *feedback;
    Button    *save;
    Button    *clear;

    // Sub-panels
    View   *viewWidget;
    Search *searchWidget;
    Sort   *sortWidget;
    Modify *modifyWidget;

    // Sidebar buttons (max 5)
    Button *recordButtons[5];

    void hideAllPanels()
    {
        newRecordCard->hide();
        newRecordHeading->hide();
        createLine->hide();
        caseIDLabel->hide();
        caseIDBox->hide();
        locationLabel->hide();
        locationBox->hide();
        crimeTypeLabel->hide();
        typeBox->hide();
        descLabel->hide();
        descriptionBox->hide();
        footNote->hide();
        feedback->hide();
        save->hide();
        clear->hide();

        viewWidget->hide();
        searchWidget->hide();
        sortWidget->hide();
        modifyWidget->hide();
    }

public:

    CrimeRecordPage(bool isAdmin)
    {
        setWindowTitle("Crime Records - CRIME RECORD MANAGEMENT SYSTEM");

        // Background
        img = new QLabel(this);
        img->setPixmap(loadPixmap("backgroundThree.png"));
        img->setScaledContents(true);

        // Sidebar Card
        recordBar = new Card(0, 0, 320, 900, this);

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
        QLabel *sidebarLine = new QLabel(this);
        sidebarLine->setGeometry(30, 100, 260, 1);
        sidebarLine->setStyleSheet("background: rgba(0,200,255,0.30);");

        // Access Tag
        QLabel *tag = new QLabel("[ CRIME RECORDS ]", this);
        tag->setGeometry(0, 110, 320, 22);
        tag->setAlignment(Qt::AlignCenter);
        tag->setStyleSheet
            (
                MONO +
                "font-size     : 10px;"
                "letter-spacing: 4px;"
                "color         : #ffcc44;"
                "background    : transparent;"
                );

        // Page Title
        QLabel *pageTitle = new QLabel("CRIME RECORD MANAGEMENT", this);
        pageTitle->setGeometry(380, 35, 1180, 50);
        pageTitle->setStyleSheet
            (
                MONO +
                "font-size     : 28px;"
                "font-weight   : 900;"
                "letter-spacing: 6px;"
                "color         : #ffffff;"
                "background    : transparent;"
                );

        // Header Line
        QLabel *headerLine = new QLabel(this);
        headerLine->setGeometry(380, 95, 1180, 1);
        headerLine->setStyleSheet("background: rgba(0,200,255,0.25);");

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

        // ── Sidebar Buttons ───────────────────────────────────────────────────

        if (isAdmin)
        {
            const char *adminItems[] =
                {
                    "  Create New Record",
                    "  View All Records",
                    "  Search Records",
                    "  Sort Records",
                    "  Modify / Delete"
                };

            for (int i = 0; i < 5; i++)
            {
                recordButtons[i] = new Button
                    (
                        adminItems[i],
                        25,
                        startY + i * (buttonHeight + gap),
                        buttonWidth,
                        buttonHeight,
                        this
                        );
            }
        }
        else
        {
            const char *userItems[] =
                {
                    "  View All Records",
                    "  Search Records",
                    "  Sort Records"
                };

            for (int i = 0; i < 3; i++)
            {
                recordButtons[i] = new Button
                    (
                        userItems[i],
                        25,
                        startY + i * (buttonHeight + gap),
                        buttonWidth,
                        buttonHeight,
                        this
                        );
            }

            recordButtons[3] = nullptr;
            recordButtons[4] = nullptr;
        }

        // ── Create Panel Widgets ──────────────────────────────────────────────

        newRecordCard = new Card(400, 110, 710, 600, this);
        newRecordCard->hide();

        newRecordHeading = new QLabel("CREATE NEW CRIME RECORD", this);
        newRecordHeading->setGeometry(420, 130, 670, 28);
        newRecordHeading->setStyleSheet
            (
                MONO +
                "font-size   : 15px;"
                "font-weight : bold;"
                "color       : #00eaff;"
                "background  : transparent;"
                );
        newRecordHeading->hide();

        createLine = new QLabel(this);
        createLine->setGeometry(415, 160, 670, 1);
        createLine->setStyleSheet("background : rgba(0, 200, 255, 0.20);");
        createLine->hide();

        caseIDLabel = new QLabel(" Case ID  *", this);
        caseIDLabel->setGeometry(420, 180, 300, 20);
        caseIDLabel->setStyleSheet
            (
                MONO +
                "font-size   : 15px;"
                "font-weight : bold;"
                "color       : #00eaff;"
                "background  : transparent;"
                );
        caseIDLabel->hide();

        caseIDBox = new Box(420, 220, 670, 38, "e.g. CR-001", this);
        caseIDBox->hide();

        locationLabel = new QLabel(" Location  *", this);
        locationLabel->setGeometry(420, 280, 300, 20);
        locationLabel->setStyleSheet
            (
                MONO +
                "font-size   : 15px;"
                "font-weight : bold;"
                "color       : #00eaff;"
                "background  : transparent;"
                );
        locationLabel->hide();

        locationBox = new Box(420, 320, 670, 38, "e.g. Massachusetts", this);
        locationBox->hide();

        crimeTypeLabel = new QLabel(" Crime Type  *", this);
        crimeTypeLabel->setGeometry(420, 380, 300, 20);
        crimeTypeLabel->setStyleSheet
            (
                MONO +
                "font-size   : 15px;"
                "font-weight : bold;"
                "color       : #00eaff;"
                "background  : transparent;"
                );
        crimeTypeLabel->hide();

        typeBox = new Box(420, 420, 670, 38, "e.g. Murder", this);
        typeBox->hide();

        descLabel = new QLabel(" Description", this);
        descLabel->setGeometry(420, 472, 300, 20);
        descLabel->setStyleSheet
            (
                MONO +
                "font-size   : 15px;"
                "font-weight : bold;"
                "color       : #00eaff;"
                "background  : transparent;"
                );
        descLabel->hide();

        descriptionBox = new QTextEdit(this);
        descriptionBox->setGeometry(420, 500, 670, 88);
        descriptionBox->setStyleSheet
            (
                "QTextEdit"
                "{"
                "    background    : rgba(0, 15, 45, 0.88);"
                "    border        : 1px solid rgba(0, 200, 255, 0.40);"
                "    border-radius : 5px;"
                "    color         : #e0f4ff;"
                "    font-family   : 'Courier New', monospace;"
                "    font-size     : 13px;"
                "    padding       : 6px;"
                "}"
                "QTextEdit:focus"
                "{"
                "    border : 1px solid #00eaff;"
                "}"
                );
        descriptionBox->hide();

        footNote = new QLabel("  Status is automatically set to  'Pending'", this);
        footNote->setGeometry(580, 598, 670, 22);
        footNote->setStyleSheet
            (
                MONO +
                "font-size  : 15px;"
                "color      : #ffcc44;"
                "background : transparent;"
                );
        footNote->hide();

        feedback = new QLabel("", this);
        feedback->setGeometry(500, 624, 670, 22);
        feedback->setStyleSheet
            (
                MONO +
                "font-size  : 12px;"
                "color      : #00eaff;"
                "background : transparent;"
                );
        feedback->hide();

        save = new Button("SAVE RECORD", 420, 656, 150, 40, this);
        save->hide();

        clear = new Button("CLEAR", 1000, 656, 100, 40, this);
        clear->setStyleSheet
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
        clear->hide();

        // ── Sub Panels ────────────────────────────────────────────────────────

        viewWidget = new View(this);
        viewWidget->setGeometry(340, 110, 1200, 720);
        viewWidget->hide();

        searchWidget = new Search(this);
        searchWidget->setGeometry(340, 110, 1200, 760);
        searchWidget->hide();

        sortWidget = new Sort(this);
        sortWidget->setGeometry(340, 110, 1200, 760);
        sortWidget->hide();

        modifyWidget = new Modify(this);
        modifyWidget->setGeometry(400, 110, 710, 620);
        modifyWidget->hide();

        // ── Admin Button Connections ──────────────────────────────────────────

        if (isAdmin)
        {
            // Create New Record
            QObject::connect(recordButtons[0], &QPushButton::clicked, [this]()
                             {
                                 hideAllPanels();
                                 newRecordCard->show();
                                 newRecordHeading->show();
                                 createLine->show();
                                 caseIDLabel->show();
                                 caseIDBox->show();
                                 locationLabel->show();
                                 locationBox->show();
                                 crimeTypeLabel->show();
                                 typeBox->show();
                                 descLabel->show();
                                 descriptionBox->show();
                                 footNote->show();
                                 feedback->show();
                                 save->show();
                                 clear->show();
                             });

            // View All Records
            QObject::connect(recordButtons[1], &QPushButton::clicked, [this]()
                             {
                                 hideAllPanels();
                                 viewWidget->show();
                             });

            // Search Records
            QObject::connect(recordButtons[2], &QPushButton::clicked, [this]()
                             {
                                 hideAllPanels();
                                 searchWidget->show();
                             });

            // Sort Records
            QObject::connect(recordButtons[3], &QPushButton::clicked, [this]()
                             {
                                 hideAllPanels();
                                 sortWidget->show();
                             });

            // Modify / Delete
            QObject::connect(recordButtons[4], &QPushButton::clicked, [this]()
                             {
                                 hideAllPanels();
                                 modifyWidget->reset();
                                 modifyWidget->show();
                             });
        }
        else
        {
            // View All Records
            QObject::connect(recordButtons[0], &QPushButton::clicked, [this]()
                             {
                                 hideAllPanels();
                                 viewWidget->show();
                             });

            // Search Records
            QObject::connect(recordButtons[1], &QPushButton::clicked, [this]()
                             {
                                 hideAllPanels();
                                 searchWidget->show();
                             });

            // Sort Records
            QObject::connect(recordButtons[2], &QPushButton::clicked, [this]()
                             {
                                 hideAllPanels();
                                 sortWidget->show();
                             });
        }

        // ── Create Panel Connections ──────────────────────────────────────────

        // Clear Button
        QObject::connect(clear, &QPushButton::clicked, [this]()
                         {
                             caseIDBox->clear();
                             locationBox->clear();
                             typeBox->clear();
                             descriptionBox->clear();
                             feedback->setText("");
                         });

        // Save Button (GUI only — no file I/O)
        QObject::connect(save, &QPushButton::clicked, [this]()
                         {
                             QString id   = caseIDBox->text().trimmed();
                             QString loc  = locationBox->text().trimmed();
                             QString type = typeBox->text().trimmed();

                             if (id.isEmpty() || loc.isEmpty() || type.isEmpty())
                             {
                                 feedback->setStyleSheet
                                     (
                                         MONO +
                                         "font-size  : 12px;"
                                         "color      : #ff6666;"
                                         "background : transparent;"
                                         );
                                 feedback->setText(" Case ID, Location and Crime Type are required.");
                                 return;
                             }

                             feedback->setStyleSheet
                                 (
                                     MONO +
                                     "font-size  : 12px;"
                                     "color      : #44ff99;"
                                     "background : transparent;"
                                     );
                             feedback->setText("  Record saved successfully!");

                             caseIDBox->clear();
                             locationBox->clear();
                             typeBox->clear();
                             descriptionBox->clear();
                         });
    }

    void resizeEvent(QResizeEvent *)
    {
        img->resize(size());
    }
};

#endif // CRIMERECORDS_H