#ifndef CRIMESTATUS_H
#define CRIMESTATUS_H

#include <QResizeEvent>
#include "common.h"
#include "file.h"

class Update : public QWidget
{
private:

    Box * caseIdentifierInput;
    Button * loadRecordButton;
    ColoredButton * markSolvedButton;
    ColoredButton * markPendingButton;
    ColoredButton * markColdButton;
    FeedbackLabel * statusFeedbackLabel;
    QString currentCaseID;
    QString selectedStatus;
    bool recordLoaded;

public:

    Update(QWidget * parent = nullptr): QWidget(parent), currentCaseID(""), selectedStatus("Pending"), recordLoaded(false)
    {
        new Card(20, 0, 1080, 400, this);
        
        QLabel* updateStatusTitle = new QLabel("UPDATE CASE STATUS", this);
        updateStatusTitle->setGeometry(40, 18, 1040, 28);
        updateStatusTitle->setStyleSheet
        (
            MONO +
            "font-size:18px;"
            "font-weight:bold;"
            "color:#ffcc44;"
            "background:transparent;"
        );
        
        QLabel* updateStatusLine = new QLabel(this);
        updateStatusLine->setGeometry(40, 52, 1040, 1);
        updateStatusLine->setStyleSheet("background:rgba(255, 200, 0, 0.20);");

        QLabel* caseIDLabel = new QLabel("Case ID", this);
        caseIDLabel->setGeometry(40, 68, 300, 24);
        caseIDLabel->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "font-weight:bold;"
            "color:#a0d8f0;"
            "background:transparent;"
        );

        caseIdentifierInput = new Box(40, 110, 850, 38, "Enter Case ID", this);
        loadRecordButton    = new Button("Load", 900, 110, 180, 38, this);

        statusFeedbackLabel = new FeedbackLabel(40, 160, 1040, this);

        QLabel* statusLabel = new QLabel("New Status", this);
        statusLabel->setGeometry(40, 172, 300, 24);
        statusLabel->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "font-weight:bold;"
            "color:#a0d8f0;"
            "background:transparent;"
        );

        markSolvedButton  = new ColoredButton("SOLVED", 40,  204, 250, 48, "#44ff99", this);
        markPendingButton = new ColoredButton("PENDING", 475, 204, 250, 48, "#ffcc44", this);
        markColdButton    = new ColoredButton("COLD", 840, 204, 250, 52, "#ff6666", this);

        Button * saveButton = new Button("SAVE STATUS", 40, 300, 180, 44, this);
        ClearButton * clearButton = new ClearButton("RESET", 900, 300, 180, 44, this);

        QObject::connect(loadRecordButton, &QPushButton::clicked, [this]()
            {
                QString id = caseIdentifierInput->text().trimmed();

                if (id.isEmpty())
                {
                    statusFeedbackLabel->showError("Enter a Case ID.");
                    return;
                }

                QStringList record = FileHandler::loadRecord(id);

                if (record.isEmpty())
                {
                    statusFeedbackLabel->showError("Case not found.");
                    recordLoaded = false;
                    return;
                }

                currentCaseID  = id;
                selectedStatus = record.value(4, "Pending").trimmed();
                recordLoaded   = true;

                statusFeedbackLabel->showSuccess(QString("Loaded Case: %1 | Status: %2").arg(id, selectedStatus));
            }
        );

        QObject::connect(markSolvedButton, &QPushButton::clicked, [this]()
            {
                selectedStatus = "Solved";
                statusFeedbackLabel->showSuccess("Status selected: Solved");
            }
        );

        QObject::connect(markPendingButton, &QPushButton::clicked, [this]()
            {
                selectedStatus = "Pending";
                statusFeedbackLabel->showNotice("Status selected: Pending");
            }
        );

        QObject::connect(markColdButton, &QPushButton::clicked, [this]()
            {
                selectedStatus = "Cold";
                statusFeedbackLabel->showError("Status selected: Cold");
            }
        );

        QObject::connect(saveButton, &QPushButton::clicked, [this]()
            {
                if (!recordLoaded)
                {
                    statusFeedbackLabel->showError("Load a case first.");
                    return;
                }

                FileHandler::updateStatus(currentCaseID, selectedStatus);
                statusFeedbackLabel->showSuccess("Case status updated successfully!");
            }
        );
        
        QObject::connect(clearButton, &QPushButton::clicked, [this]()
            {
                caseIdentifierInput->clear();
                statusFeedbackLabel->clear();
                recordLoaded = false;
            }
        );
    }
};

class StatusView : public QWidget
{
private:

    Button * refreshRecordsButton;
    RecordDisplay * allRecordsDisplay;

public:

    StatusView(QWidget * parent = nullptr) : QWidget(parent)
    {
        QLabel* viewTitle = new QLabel("ALL CASES WITH STATUS", this);
        viewTitle->setGeometry(10, 8, 860, 28);
        viewTitle->setStyleSheet
        (
            MONO +
            "font-size:18px;"
            "font-weight:bold;"
            "color:#00eaff;"
            "background:transparent;"
        );

        QLabel* viewLine = new QLabel(this);
        viewLine->setGeometry(0, 42, 860, 1);
        viewLine->setStyleSheet("background:rgba(0, 200, 255, 0.20);");

        refreshRecordsButton = new Button("REFRESH", 1005, 6, 140, 34, this);
        refreshRecordsButton->setSound("refreshButtonSound.mp3");
        allRecordsDisplay = new RecordDisplay(0, 50, 1150, 485, this, " Click REFRESH to load all records.");

        QObject::connect(refreshRecordsButton, &QPushButton::clicked, [this]()
            {
                loadAndDisplay();
            }
        );
    }

    void loadAndDisplay()
    {
        const QStringList records = FileHandler::loadRecords();
        if (records.isEmpty())
        {
            allRecordsDisplay->setText("  No records found.");
            return;
        }
        QString display;
        for (const QString & line : records)
        {
            display += DataFormatter::formatStatus(line.split("\t"));
        }

        allRecordsDisplay->setText(display);
    }
};

class Filter : public QWidget
{
private:

    ColoredButton * filterSolvedButton;
    ColoredButton * filterPendingButton;
    ColoredButton * filterColdButton;
    RecordDisplay * filterResultDisplay;

    void filterByStatus(const QString & status)
    {
        const QStringList records = FileHandler::loadRecords();
        QString           display;

        for (const QString & line : records)
        {
            QStringList parts = line.split("\t");

            if (parts.size() >= 5 && parts[4].trimmed().toLower() == status.toLower())
            {
                display += DataFormatter::formatStatus(parts);
            }
        }

        if (display.isEmpty())
        {
            filterResultDisplay->setText("  No " + status + " cases found.");
        }
        else
        {
            filterResultDisplay->setText(display);
        }
    }

public:

    Filter(QWidget * parent = nullptr) : QWidget(parent)
    {
        new Card(170, 0, 800, 128, this);
        
        QLabel* filterTitle = new QLabel("FILTER BY STATUS", this);
        filterTitle->setGeometry(190, 18, 760, 28);
        filterTitle->setStyleSheet
        (
            MONO +
            "font-size:18px;"
            "font-weight:bold;"
            "color:#00eaff;"
            "background:transparent;"
        );

        QLabel* filterLine = new QLabel(this);
        filterLine->setGeometry(190, 52, 760, 1);
        filterLine->setStyleSheet("background:rgba(0, 200, 255, 0.20);");

        filterSolvedButton  = new ColoredButton("SOLVED",  190, 68, 200, 52, "#44ff99", this);
        filterPendingButton = new ColoredButton("PENDING", 445, 68, 200, 52, "#ffcc44", this);
        filterColdButton    = new ColoredButton("COLD",    700, 68, 200, 52, "#ff6666", this);

        filterResultDisplay = new RecordDisplay(0, 160, 1150, 380, this, "  Press a filter button above to view cases.");

        QObject::connect(filterSolvedButton, &QPushButton::clicked, [this]()
            {
                filterByStatus("Solved");
            }
        );
        QObject::connect(filterPendingButton, &QPushButton::clicked, [this]()
            {
               filterByStatus("Pending");
            }
        );
        QObject::connect(filterColdButton, &QPushButton::clicked, [this]()
            {
               filterByStatus("Cold");
            }
        );
    }
};

class CaseStatusPage : public QWidget
{
private:

    QLabel * pageBackground;
    StatusView * allStatusPanel;
    Filter * statusFilterPanel;
    Update * statusUpdatePanel;
    Button * showViewPanelButton;
    Button * showFilterPanelButton;
    Button * showUpdatePanelButton;
    StatCard * solvedStatCard;
    StatCard * pendingStatCard;
    StatCard * coldStatCard;

    void hideAllPanels()
    {
        allStatusPanel->hide();
        statusFilterPanel->hide();
        statusUpdatePanel->hide();
    }

    void refreshStatCards()
    {
        const QStringList records = FileHandler::loadRecords();

        int solved  = 0;
        int pending = 0;
        int cold    = 0;

        for (const QString & line : records)
        {
            QStringList p = line.split("\t");
            
            if (p.size() >= 5)
            {
                QString st = p[4].trimmed().toLower();
                
                if (st == "solved")
                {
                    solved++;
                }
                else if (st == "pending")
                {
                    pending++;
                }
                else if (st == "cold")
                {
                    cold++;
                }
            }
        }

        solvedStatCard->setValue(solved);
        pendingStatCard->setValue(pending);
        coldStatCard->setValue(cold);
    }


public:

    explicit CaseStatusPage(bool isAdmin) : QWidget(nullptr)
    {
        setWindowTitle("Case Status Management — CRIME RECORD MANAGEMENT SYSTEM");

        pageBackground = new Background(this, "backgroundThree.png");

        new Sidebar(this, "[ CASE STATUS ]");
        
        new PageHeader(this, "CASE STATUS MANAGEMENT", "Track and update the resolution progress of all criminal cases");
        
        new Footer(this);

        QLabel* solvedLegend = new QLabel("SOLVED", this);
        solvedLegend->setGeometry(30, 172, 270, 24);
        solvedLegend->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "letter-spacing:4px;"
            "font-weight:bold;"
            "color:#44ff99;"
            "background:transparent;"
        );

        QLabel* pendingLegend = new QLabel("PENDING", this);
        pendingLegend->setGeometry(30, 202, 270, 24);
        pendingLegend->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "letter-spacing:4px;"
            "font-weight:bold;"
            "color:#ffcc44;"
            "background:transparent;"
        );

        QLabel* coldLegend = new QLabel("COLD", this);
        coldLegend->setGeometry(30, 232, 270, 24);
        coldLegend->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "letter-spacing:4px;"
            "font-weight:bold;"
            "color:#ff6666;"
            "background:transparent;"
        );

        solvedStatCard  = new StatCard(380, 150, "#44ff99", "SOLVED",   this);
        pendingStatCard = new StatCard(850, 150, "#ffcc44", "PENDING",  this);
        coldStatCard    = new StatCard(1300, 150, "#ff6666", "COLD CASE",this);

        showViewPanelButton   = new Button("View Status", 25, 300, 270, 40, this);
        showFilterPanelButton = new Button("Filter Cases", 25, 360, 270, 40, this);

        showUpdatePanelButton = nullptr;
        if (isAdmin)
        {
            showUpdatePanelButton = new Button("Update Status", 25, 420, 270, 40, this);
        }

        BackButton *bb = new BackButton(25, isAdmin ? 480 : 420, 270, 44, this);
        bb->raise();

        QObject::connect(bb, &QPushButton::clicked, [this]()
            {
                this->close();
            }
        );

        allStatusPanel    = new StatusView(this);
        statusFilterPanel = new Filter(this);
        statusUpdatePanel = new Update(this);

        allStatusPanel->setGeometry(380, 250, 1150, 630);
        statusFilterPanel->setGeometry(380, 250, 1150, 630);
        statusUpdatePanel->setGeometry(380, 250, 1150, 630);

        hideAllPanels();
        allStatusPanel->show();

        refreshStatCards();

        QObject::connect(showViewPanelButton, &QPushButton::clicked, [this]()
            {
                hideAllPanels();
                refreshStatCards();
                allStatusPanel->loadAndDisplay();
                allStatusPanel->show();
            }
        );

        QObject::connect(showFilterPanelButton, &QPushButton::clicked, [this]()
            {
                hideAllPanels();
                refreshStatCards();
                statusFilterPanel->show();
            }
        );

        if (showUpdatePanelButton != nullptr)
        {
            QObject::connect(showUpdatePanelButton, &QPushButton::clicked, [this]()
                {
                    hideAllPanels();
                    statusUpdatePanel->show();
                }
            );
        }
    }

    void resizeEvent(QResizeEvent * event) override
    {
        pageBackground->resize(event->size());
    }
};

#endif