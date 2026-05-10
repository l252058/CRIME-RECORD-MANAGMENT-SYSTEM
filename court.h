#ifndef COURT_H
#define COURT_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QScrollArea>
#include <QPushButton>

#include "common.h"
#include "file.h"

// =============================================================================
//  Shared Stylesheet Helpers
// =============================================================================

inline static QString courtFieldLabel()
{
    return MONO + 
           "font-size   : 20px; "
           "font-weight : bold; "
           "color       : #a0d8f0; "
           "background  : transparent;";
}

// =============================================================================
//  VIEW COURT PANEL
// =============================================================================

class ViewCourt : public QWidget
{
private:

    RecordDisplay * resultDisplay;

    void load()
    {
        QStringList records = FileHandler::loadCourt();

        if (records.isEmpty())
        {
            resultDisplay->setText("  No court proceedings found.");
            return;
        }

        QString display;

        for (const QString & line : records)
        {
            display += DataFormatter::formatCourt(line.split("\t"));
        }

        resultDisplay->setText(display);
        
        FileHandler::appendLog("USER", "Viewed all court proceedings");
    }

public:

    explicit ViewCourt(QWidget * parent = nullptr) 
        : QWidget(parent)
    {
        QLabel * heading = new QLabel("ALL COURT PROCEEDINGS", this);
        
        heading->setGeometry(0, 8, 900, 30);
        
        heading->setStyleSheet
        (
            MONO +
            "font-size   : 18px; "
            "font-weight : bold; "
            "color       : #00eaff; "
            "background  : transparent;"
        );

        Button * refreshButton = new Button("REFRESH", 1005, 6, 140, 34, this);

        resultDisplay = new RecordDisplay(0, 50, 1150, 485, this, "  No court proceedings found.");

        QObject::connect(refreshButton, &QPushButton::clicked, [this]() 
        { 
            load(); 
        });
    }

    void activate() 
    { 
        load(); 
    }
};

// =============================================================================
//  FILTER COURT PANEL
// =============================================================================

class FilterCourt : public QWidget
{
private:

    RecordDisplay * filterResult;

    void filterBy(const QString & status)
    {
        QStringList records = FileHandler::loadCourt();
        QString     display;

        for (const QString & line : records)
        {
            QStringList parts = line.split("\t");

            if (parts.size() > 3 && parts[3].trimmed().contains(status, Qt::CaseInsensitive))
            {
                display += DataFormatter::formatCourt(parts);
            }
        }

        if (display.isEmpty())
        {
            filterResult->setText("  No " + status + " proceedings found.");
        }
        else
        {
            filterResult->setText(display);
        }

        FileHandler::appendLog("USER", "Filtered court proceedings by: " + status);
    }

public:

    explicit FilterCourt(QWidget * parent = nullptr) 
        : QWidget(parent)
    {
        new Card(170, 0, 800, 128, this);
        QLabel* courtTitle1 = new QLabel("FILTER BY COURT STATUS", this);
        courtTitle1->setGeometry(190, 18, 760, 28);
        courtTitle1->setStyleSheet(MONO + "font-size:18px; font-weight:bold; color:#00eaff; background:transparent;");
        QLabel* courtLine1 = new QLabel(this);
        courtLine1->setGeometry(190, 52, 760, 1);
        courtLine1->setStyleSheet("background:rgba(0, 200, 255, 0.20);");

        Button * ongoingBtn = new Button("ONGOING", 190, 68, 250, 52, this);
        Button * onHoldBtn  = new Button("ON HOLD", 445, 68, 250, 52, this);
        Button * verdictBtn = new Button("VERDICT REACHED", 700, 68, 250, 52, this);

        filterResult = new RecordDisplay(0, 160, 1150, 385, this, "  Press a button above to filter proceedings.");

        QObject::connect(ongoingBtn, &QPushButton::clicked, [this]() 
        { 
            filterBy("Ongoing"); 
        });

        QObject::connect(onHoldBtn, &QPushButton::clicked, [this]() 
        { 
            filterBy("On Hold"); 
        });

        QObject::connect(verdictBtn, &QPushButton::clicked, [this]() 
        { 
            filterBy("Verdict Reached"); 
        });
    }

    void activate() 
    { 
        filterBy("Ongoing"); 
    }
};

// =============================================================================
//  UPDATE COURT STATUS PANEL
// =============================================================================

class UpdateCourt : public QWidget
{
private:

    Box           * caseIDBox;
    QLabel        * infoLabel;
    FeedbackLabel * feedback;
    QString         selectedStatus;

    void clearAll()
    {
        caseIDBox->clear();
        infoLabel->clear();
        feedback->clear();
        selectedStatus = "";
    }

public:

    explicit UpdateCourt(QWidget * parent = nullptr) 
        : QWidget(parent)
    {
        new Card(40, 0, 1080, 560, this);
        QLabel* courtTitle2 = new QLabel("UPDATE VERDICT / STATUS", this);
        courtTitle2->setGeometry(40, 18, 1040, 28);
        courtTitle2->setStyleSheet(MONO + "font-size:18px; font-weight:bold; color:#ffcc44; background:transparent;");
        QLabel* courtLine2 = new QLabel(this);
        courtLine2->setGeometry(40, 52, 1040, 1);
        courtLine2->setStyleSheet("background:rgba(255, 200, 0, 0.20);");

        QLabel * heading = new QLabel("Modify existing judicial proceedings", this);
        heading->setGeometry(40, 68, 1040, 20);
        heading->setStyleSheet(MONO + "font-size:16px; color:#a0d8f0; background:transparent;");

        caseIDBox       = new Box(40, 110, 850, 38, "Enter Case ID", this);
        Button * loadBtn = new Button("LOAD", 900, 110, 180, 44, this);

        infoLabel = new QLabel("", this);
        infoLabel->setGeometry(40, 160, 1040, 22);
        infoLabel->setStyleSheet(MONO + "font-size:16px; font-weight:bold; color:#c0dff5; background:transparent;");

        Button * ongoingBtn = new Button("ONGOING", 40, 206, 350, 52, this);
        Button * onHoldBtn  = new Button("ON HOLD", 415, 206, 350, 52, this);
        Button * verdictBtn = new Button("VERDICT REACHED", 790, 206, 350, 52, this);

        feedback = new FeedbackLabel(40, 280, 1040, this);
        Button * saveBtn = new Button("SAVE", 40, 330, 350, 52, this);

        QObject::connect(loadBtn, &QPushButton::clicked, [this]()
        {
            QString id = caseIDBox->text().trimmed();
            if (id.isEmpty()) { feedback->showError("Enter a Case ID."); return; }
            QStringList p = FileHandler::loadCourtCase(id);
            if (p.isEmpty()) { feedback->showError("Court case not found."); return; }
            selectedStatus = p.value(3, "Ongoing").trimmed();
            infoLabel->setText("  Loaded: " + p.value(1).trimmed() + " — " + p.value(2).trimmed() + "  |  Current: " + selectedStatus);
            feedback->showInfo("Case loaded. Select a new status and click SAVE.");
        });

        QObject::connect(ongoingBtn, &QPushButton::clicked, [this]() { selectedStatus = "Ongoing"; feedback->showInfo("Status selected: ONGOING"); });
        QObject::connect(onHoldBtn, &QPushButton::clicked, [this]() { selectedStatus = "On Hold"; feedback->showInfo("Status selected: ON HOLD"); });
        QObject::connect(verdictBtn, &QPushButton::clicked, [this]() { selectedStatus = "Verdict Reached"; feedback->showInfo("Status selected: VERDICT REACHED"); });

        QObject::connect(saveBtn, &QPushButton::clicked, [this]()
        {
            QString id = caseIDBox->text().trimmed();
            if (id.isEmpty()) { feedback->showError("Load a case first."); return; }
            if (selectedStatus.isEmpty()) { feedback->showError("Select a status first."); return; }
            if (FileHandler::updateCourtStatus(id, selectedStatus)) {
                FileHandler::appendLog("ADMIN", "Court status updated — Case: " + id + " → " + selectedStatus);
                feedback->showSuccess("Status updated to '" + selectedStatus + "' for case " + id + ".");
                clearAll();
            } else { feedback->showError("Failed to update. Case not found."); }
        });
    }

    void activate() { clearAll(); }
};

// =============================================================================
//  ADD COURT PANEL
// =============================================================================

class AddCourt : public QWidget
{
private:

    Box           * caseIDBox;
    Box           * accusedBox;
    Box           * crimeBox;
    FeedbackLabel * feedback;

    void clearAll()
    {
        caseIDBox->clear();
        accusedBox->clear();
        crimeBox->clear();
        feedback->clear();
    }

public:

    explicit AddCourt(QWidget * parent = nullptr) 
        : QWidget(parent)
    {
        new Card(40, 0, 1080, 560, this);
        QLabel* courtTitle3 = new QLabel("ADD NEW JUDICIAL PROCEEDING", this);
        courtTitle3->setGeometry(40, 18, 1040, 28);
        courtTitle3->setStyleSheet(MONO + "font-size:18px; font-weight:bold; color:#00eaff; background:transparent;");
        QLabel* courtLine3 = new QLabel(this);
        courtLine3->setGeometry(40, 52, 1040, 1);
        courtLine3->setStyleSheet("background:rgba(0, 200, 255, 0.20);");

        QLabel * heading = new QLabel("Register new court cases into the system", this);
        heading->setGeometry(40, 68, 1040, 20);
        heading->setStyleSheet(MONO + "font-size:16px; color:#a0d8f0; background:transparent;");

        caseIDBox  = new Box(40, 110, 1040, 38, "Case ID", this);
        accusedBox = new Box(40, 198, 1040, 38, "Accused Name", this);
        crimeBox   = new Box(40, 286, 1040, 38, "e.g. Attempted Murder", this);

        feedback = new FeedbackLabel(40, 420, 1040, this);

        Button * saveBtn = new Button("SAVE", 40, 460, 180, 44, this);
        ClearButton * clearBtn = new ClearButton("CLEAR", 235, 460, 180, 44, this);

        QObject::connect(clearBtn, &QPushButton::clicked, [this]() { clearAll(); });

        QObject::connect(saveBtn, &QPushButton::clicked, [this]()
        {
            QString id      = caseIDBox->text().trimmed();
            QString accused = accusedBox->text().trimmed();
            QString crime   = crimeBox->text().trimmed();

            if (id.isEmpty() || accused.isEmpty() || crime.isEmpty())
            {
                feedback->showError("All marked fields (*) are required.");
                return;
            }

            if (FileHandler::courtCaseExists(id))
            {
                feedback->showError("Case ID already exists in court records.");
                return;
            }

            FileHandler::saveCourt(id, accused, crime);
            feedback->showSuccess("Judicial record registered successfully!");
            FileHandler::appendLog("ADMIN", "Court proceeding added — Case: " + id + "  Accused: " + accused);
            clearAll();
        });
    }

    void activate() { clearAll(); }
};

// =============================================================================
//  COURT PROCEEDINGS PAGE
// =============================================================================

class CourtProceedings : public QWidget
{
private:

    QLabel      * backgroundImg;
    StatCard    * ongoingNumber;
    StatCard    * onHoldNumber;
    StatCard    * verdictNumber;

    Button      * btnView;
    Button      * btnFilter;
    Button      * btnUpdate;
    Button      * btnAdd;
    ViewCourt   * panelView;
    FilterCourt * panelFilter;
    UpdateCourt * panelUpdate;
    AddCourt    * panelAdd;
    int           currentPanel = -1;

    void refreshCounts()
    {
        ongoingNumber->setValue(FileHandler::countCourtByStatus("Ongoing"));
        onHoldNumber->setValue(FileHandler::countCourtByStatus("On Hold"));
        verdictNumber->setValue(FileHandler::countCourtByStatus("Verdict Reached"));
    }

    void showPanel(int index)
    {
        if (index == currentPanel) return;
        currentPanel = index;

        panelView  ->setVisible(index == 0);
        panelFilter->setVisible(index == 1);
        panelUpdate->setVisible(index == 2);
        panelAdd   ->setVisible(index == 3);

        refreshCounts();

        switch (index)
        {
            case 0: panelView  ->activate(); break;
            case 1: panelFilter->activate(); break;
            case 2: panelUpdate->activate(); break;
            case 3: panelAdd   ->activate(); break;
            default: break;
        }
    }

public:

    explicit CourtProceedings(bool isAdmin) 
        : QWidget(nullptr)
    {
        setWindowTitle("Court Proceedings — CRIME RECORD MANAGEMENT SYSTEM");

        backgroundImg = UI::setupBackground(this, "backgroundThree.png");

        UI::setupSidebar(this, "[ COURT  SERVICES ]");
        UI::setupPageHeader(this, "COURT PROCEEDINGS", "Track and update the legal progress of all crime cases");
        UI::setupFooter(this);

        ongoingNumber  = new StatCard(380,  150, "#00eaff", "ONGOING",         this);
        onHoldNumber   = new StatCard(620,  150, "#ffcc44", "ON HOLD",         this);
        verdictNumber  = new StatCard(860,  150, "#44ff99", "VERDICT REACHED", this);

        btnView = new Button("VIEW ALL", 25, 300, 270, 40, this);
        btnFilter = new Button("FILTER BY STATUS", 25, 360, 270, 40, this);

        btnUpdate = nullptr;
        btnAdd    = nullptr;

        if (isAdmin)
        {
            btnUpdate = new Button("UPDATE STATUS", 25, 420, 270, 40, this);
            btnAdd = new Button("ADD RECORD", 25, 480, 270, 40, this);
        }

        BackButton *bb = new BackButton(25, isAdmin ? 540 : 420, 270, 44, this);
        bb->raise();
        QObject::connect(bb, &QPushButton::clicked, [this]() { this->close(); });

        panelView   = new ViewCourt(this);
        
        panelView->setGeometry(380, 240, 1180, 600);
        panelView->hide();

        panelFilter = new FilterCourt(this);
        
        panelFilter->setGeometry(380, 240, 1180, 600);
        panelFilter->hide();

        panelUpdate = new UpdateCourt(this);
        
        panelUpdate->setGeometry(380, 240, 1180, 600);
        panelUpdate->hide();

        panelAdd    = new AddCourt(this);
        
        panelAdd->setGeometry(380, 240, 1180, 600);
        panelAdd->hide();

        QObject::connect(btnView, &QPushButton::clicked, [this]() 
        { 
            showPanel(0); 
        });

        QObject::connect(btnFilter, &QPushButton::clicked, [this]() 
        { 
            showPanel(1); 
        });

        if (isAdmin)
        {
            QObject::connect(btnUpdate, &QPushButton::clicked, [this]() 
            { 
                showPanel(2); 
            });

            QObject::connect(btnAdd, &QPushButton::clicked, [this]() 
            { 
                showPanel(3); 
            });
        }

        showPanel(0);
    }

    void resizeEvent(QResizeEvent *) override
    {
        backgroundImg->setGeometry(0, 0, width(), height());
    }
};

#endif // COURT_H