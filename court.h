#ifndef COURT_H
#define COURT_H

#include <QWidget>
#include <QLabel>
#include <QResizeEvent>

#include "common.h"
#include "file.h"

class ViewCourt : public QWidget
{
private:

    RecordDisplay * allProceedingsRecordDisplay;

    void loadAllProceedingsFromDatabase()
    {
        QStringList records = FileHandler::loadCourt();

        if (records.isEmpty())
        {
            allProceedingsRecordDisplay->setText("No court proceedings found.");
            return;
        }

        QString formattedDisplayString;
        for (const QString & line : records)
        {
            formattedDisplayString += DataFormatter::formatCourt(line.split("\t"));
        }

        allProceedingsRecordDisplay->setText(formattedDisplayString);
    }

public:

    ViewCourt(QWidget * parent = nullptr) : QWidget(parent)
    {
        QLabel* viewTitleLabel = new QLabel("ALL COURT PROCEEDINGS", this);
        viewTitleLabel->setGeometry(0, 8, 900, 30);
        viewTitleLabel->setStyleSheet
        (
            MONO +
            "font-size:18px;"
            "font-weight:bold;"
            "color:#00eaff;"
            "background:transparent;"
        );

        QLabel* viewTitleLine = new QLabel(this);
        viewTitleLine->setGeometry(0, 42, 900, 1);
        viewTitleLine->setStyleSheet
        (
            "background:rgba(0, 200, 255, 0.20);"
        );

        Button * refreshDataButton = new Button("REFRESH", 1005, 6, 140, 34, this);
        allProceedingsRecordDisplay = new RecordDisplay(0, 50, 1150, 485, this, "  Click REFRESH to load data.");

        QObject::connect(refreshDataButton, &QPushButton::clicked, [this]() 
        { 
            loadAllProceedingsFromDatabase(); 
        });
    }

    void refreshData() 
    { 
        loadAllProceedingsFromDatabase(); 
    }
};

class FilterCourt : public QWidget
{
private:

    RecordDisplay * filteredProceedingsRecordDisplay;

    void filterByJudicialStatus(const QString & statusCriteria)
    {
        QStringList rawRecords = FileHandler::loadCourt();
        QString filteredOutput;

        for (const QString & line : rawRecords)
        {
            QStringList recordParts = line.split("\t");
            if (recordParts.size() >= 4 && recordParts[3].trimmed().toLower() == statusCriteria.toLower())
            {
                filteredOutput += DataFormatter::formatCourt(recordParts);
            }
        }

        if (filteredOutput.isEmpty())
        {
            filteredProceedingsRecordDisplay->setText("  No " + statusCriteria + " proceedings found.");
        }
        else
        {
            filteredProceedingsRecordDisplay->setText(filteredOutput);
        }
    }

public:

    FilterCourt(QWidget * parent = nullptr) : QWidget(parent)
    {
        new Card(170, 0, 800, 128, this);

        QLabel* filterHeaderLabel = new QLabel("FILTER PROCEEDINGS BY STATUS", this);
        filterHeaderLabel->setGeometry(190, 18, 760, 28);
        filterHeaderLabel->setStyleSheet
        (
            MONO +
            "font-size:18px;"
            "font-weight:bold;"
            "color:#00eaff;"
            "background:transparent;"
        );

        QLabel* filterHeaderLine = new QLabel(this);
        filterHeaderLine->setGeometry(190, 52, 760, 1);
        filterHeaderLine->setStyleSheet
        (
            "background:rgba(0, 200, 255, 0.20);"
        );

        ColoredButton * ongoingFilterButton = new ColoredButton("ONGOING", 190, 68, 200, 52, "#44ff99", this);
        ColoredButton * holdFilterButton    = new ColoredButton("ON HOLD", 495, 68, 200, 52, "#ffcc44", this);
        ColoredButton * verdictFilterButton = new ColoredButton("VERDICT", 750, 68, 200, 52, "#ff6666", this);

        filteredProceedingsRecordDisplay = new RecordDisplay(0, 160, 1150, 380, this, "  Press a status filter above.");

        QObject::connect(ongoingFilterButton, &QPushButton::clicked, [this]()
            {
                filterByJudicialStatus("Ongoing");
            }
        );
        QObject::connect(holdFilterButton, &QPushButton::clicked, [this]()
            {
               filterByJudicialStatus("On Hold");
            }
        );
        QObject::connect(verdictFilterButton,&QPushButton::clicked, [this]()
            {
               filterByJudicialStatus("Verdict Reached");
            }
        );
    }
};

class UpdateCourt : public QWidget
{
private:

    Box * caseIdentifierInputBox;
    FeedbackLabel * updateActionFeedbackLabel;
    QString currentlyLoadedCaseID;
    QString selectedJudicialStatus;
    bool isProceedingSuccessfullyLoaded = false;

public:

    UpdateCourt(QWidget * parent = nullptr) : QWidget(parent), selectedJudicialStatus("Ongoing")
    {
        new Card(20, 0, 1080, 450, this);

        QLabel* updateTitleLabel = new QLabel("UPDATE PROCEEDING STATUS", this);
        updateTitleLabel->setGeometry(40, 18, 1040, 28);
        updateTitleLabel->setStyleSheet
        (
            MONO +
            "font-size:18px;"
            "font-weight:bold;"
            "color:#ffcc44;"
            "background:transparent;"
        );

        QLabel* updateTitleLine = new QLabel(this);
        updateTitleLine->setGeometry(40, 52, 1040, 1);
        updateTitleLine->setStyleSheet
        (
            "background:rgba(255, 200, 0, 0.20);"
        );

        QLabel* inputLabelCaseID = new QLabel("Case ID", this);
        inputLabelCaseID->setGeometry(40, 68, 300, 24);
        inputLabelCaseID->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "font-weight:bold;"
            "color:#a0d8f0;"
            "background:transparent;"
        );

        caseIdentifierInputBox = new Box(40, 100, 850, 38, "Enter Case ID to load", this);
        Button * loadRecordButton     = new Button("Load", 900, 100, 180, 44, this);

        updateActionFeedbackLabel = new FeedbackLabel(40, 150, 1040, this);

        QLabel* selectionLabelStatus = new QLabel("Select New Status", this);
        selectionLabelStatus->setGeometry(40, 172, 500, 24);
        selectionLabelStatus->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "font-weight:bold;"
            "color:#a0d8f0;"
            "background:transparent;"
        );

        ColoredButton * setOngoingStatusButton = new ColoredButton("ONGOING", 40, 204, 250, 48, "#44ff99", this);
        ColoredButton * setOnHoldStatusButton  = new ColoredButton("ON HOLD", 480, 204, 250, 48, "#ffcc44", this);
        ColoredButton * setVerdictStatusButton = new ColoredButton("VERDICT REACHED", 820, 204, 250, 48, "#ff6666", this);

        Button * commitUpdatesButton    = new Button("SAVE UPDATES", 40, 350, 180, 44, this);
        ClearButton * resetPanelContentButton = new ClearButton("RESET", 880, 350, 180, 44, this);

        QObject::connect(loadRecordButton, &QPushButton::clicked, [this]()
            {
                QString idToSearch = caseIdentifierInputBox->text().trimmed();
                if (idToSearch.isEmpty())
                {
                    updateActionFeedbackLabel->showError("Case ID required.");
                    return;
                }

                QStringList recordData = FileHandler::loadCourtCase(idToSearch);
                if (recordData.isEmpty())
                {
                    updateActionFeedbackLabel->showError("Proceeding not found.");
                    isProceedingSuccessfullyLoaded = false;
                    return;
                }

                currentlyLoadedCaseID = idToSearch;
                selectedJudicialStatus = recordData.value(3, "Ongoing");
                isProceedingSuccessfullyLoaded = true;
                updateActionFeedbackLabel->showSuccess("Loaded: " + idToSearch + " | Current: " + selectedJudicialStatus);
            }
        );

        QObject::connect(setOngoingStatusButton, &QPushButton::clicked, [this]()
            {
                selectedJudicialStatus = "Ongoing";
                updateActionFeedbackLabel->showNotice("Status: Ongoing");
            }
        );
        QObject::connect(setOnHoldStatusButton,  &QPushButton::clicked, [this]()
            {
                selectedJudicialStatus = "On Hold";
                updateActionFeedbackLabel->showNotice("Status: On Hold");
            }
        );
        QObject::connect(setVerdictStatusButton, &QPushButton::clicked, [this]()
            {
               selectedJudicialStatus = "Verdict Reached";
               updateActionFeedbackLabel->showError("Status: Verdict Reached");
            }
        );

        QObject::connect(commitUpdatesButton, &QPushButton::clicked, [this]()
            {
                if (!isProceedingSuccessfullyLoaded)
                {
                    updateActionFeedbackLabel->showError("Load a record first.");
                    return;
                }
                FileHandler::updateCourtStatus(currentlyLoadedCaseID, selectedJudicialStatus);
                updateActionFeedbackLabel->showSuccess("Proceeding updated successfully!");
            }
        );

        QObject::connect(resetPanelContentButton, &QPushButton::clicked, [this]()
            {
                caseIdentifierInputBox->clear();
                updateActionFeedbackLabel->clear();
                isProceedingSuccessfullyLoaded = false;
            }
        );
    }
};

class AddCourt : public QWidget
{
private:

    Box * caseIdentifierInputBox;
    Box * accusedPersonNameInputBox;
    Box * judicialCaseTypeInputBox;
    FeedbackLabel * addActionFeedbackLabel;

    void clearJudicialEntryForm()
    {
        caseIdentifierInputBox->clear();
        accusedPersonNameInputBox->clear();
        judicialCaseTypeInputBox->clear();
        addActionFeedbackLabel->clear();
    }

public:

    AddCourt(QWidget * parent = nullptr) : QWidget(parent)
    {
        new Card(20, 0, 1080, 520, this);

        QLabel* addTitleLabel = new QLabel("ADD NEW JUDICIAL PROCEEDING", this);
        addTitleLabel->setGeometry(40, 18, 1040, 28);
        addTitleLabel->setStyleSheet
        (
            MONO +
            "font-size:18px;"
            "font-weight:bold;"
            "color:#00eaff;"
            "background:transparent;"
        );

        QLabel* addTitleLine = new QLabel(this);
        addTitleLine->setGeometry(40, 52, 1040, 1);
        addTitleLine->setStyleSheet("background:rgba(0, 200, 255, 0.20);");

        QLabel* instructionLabel = new QLabel("Register new court cases into the system", this);
        instructionLabel->setGeometry(40, 68, 1040, 20);
        instructionLabel->setStyleSheet
        (
            MONO +
            "font-size:16px;"
            "color:#a0d8f0;"
            "background:transparent;"
        );

        QLabel* labelForCaseID = new QLabel("Case ID", this);
        labelForCaseID->setGeometry(40, 110, 300, 24);
        labelForCaseID->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "font-weight:bold;"
            "color:#a0d8f0;"
            "background:transparent;"
        );
        caseIdentifierInputBox = new Box(40, 140, 1040, 38, "e.g. CR-101", this);

        QLabel* labelForAccusedName = new QLabel("Accused Name", this);
        labelForAccusedName->setGeometry(40, 200, 300, 24);
        labelForAccusedName->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "font-weight:bold;"
            "color:#a0d8f0;"
            "background:transparent;"
        );
        accusedPersonNameInputBox = new Box(40, 230, 1040, 38, "Full Name", this);

        QLabel* labelForCaseType = new QLabel("Case Type", this);
        labelForCaseType->setGeometry(40, 290, 300, 24);
        labelForCaseType->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "font-weight:bold;"
            "color:#a0d8f0;"
            "background:transparent;"
        );
        judicialCaseTypeInputBox = new Box(40, 320, 1040, 38, "e.g. Felony / Misdemeanor", this);

        addActionFeedbackLabel = new FeedbackLabel(40, 380, 1040, this);

        Button * saveJudicialRecordButton  = new Button("SAVE", 40, 440, 180, 44, this);
        ClearButton * clearJudicialEntryButton = new ClearButton("CLEAR", 900, 440, 180, 44, this);

        QObject::connect(clearJudicialEntryButton, &QPushButton::clicked, [this]()
            {
                clearJudicialEntryForm();
            }
        );
        QObject::connect(saveJudicialRecordButton, &QPushButton::clicked, [this]()
            {
                QString idToSave   = caseIdentifierInputBox->text().trimmed();
                QString nameToSave = accusedPersonNameInputBox->text().trimmed();
                QString typeToSave = judicialCaseTypeInputBox->text().trimmed();

                if (idToSave.isEmpty() || nameToSave.isEmpty())
                {
                    addActionFeedbackLabel->showError("Missing required fields.");
                    return;
                }

                FileHandler::saveCourt(idToSave, nameToSave, typeToSave);
                addActionFeedbackLabel->showSuccess("Judicial record created!");
                clearJudicialEntryForm();
            }
        );
    }
};

class CourtProceedings : public QWidget
{
private:

    QLabel * pageBackgroundContainer;
    ViewCourt * allProceedingsPanel;
    FilterCourt * statusFilterPanel;
    UpdateCourt * statusUpdatePanel;
    AddCourt * addProceedingPanel;
    Button * showAllProceedingsPanelButton;
    Button * showFilterProceedingsPanelButton;
    Button * showUpdateStatusPanelButton;
    Button * showAddRecordPanelButton;
    StatCard * ongoingProceedingsStatCard;
    StatCard * onHoldProceedingsStatCard;
    StatCard * verdictReachedStatCard;

    void hideAllDisplayPanels()
    {
        allProceedingsPanel->hide();
        statusFilterPanel->hide();
        statusUpdatePanel->hide();
        addProceedingPanel->hide();
    }

    void refreshJudicialStatCounts()
    {
        ongoingProceedingsStatCard->setValue(FileHandler::countCourtByStatus("Ongoing"));
        onHoldProceedingsStatCard->setValue(FileHandler::countCourtByStatus("On Hold"));
        verdictReachedStatCard->setValue(FileHandler::countCourtByStatus("Verdict Reached"));
    }

public:

    CourtProceedings(bool isAdminUser) : QWidget(nullptr)
    {
        setWindowTitle("Court Proceedings — CRIME RECORD MANAGEMENT SYSTEM");

        pageBackgroundContainer = new Background(this, "backgroundThree.png");

        new Sidebar(this, "[ COURT ]");
        new PageHeader(this, "COURT PROCEEDINGS", "Track and update the legal progress of all crime cases");
        new Footer(this);

        QLabel * ongoingStatusLegendLabel = new QLabel("ONGOING", this);
        ongoingStatusLegendLabel->setGeometry(30, 172, 270, 24);
        ongoingStatusLegendLabel->setStyleSheet
        (
            MONO + 
            "font-size:20px;"
            "letter-spacing:4px;"
            "font-weight:bold;"
            "color:#44ff99;"
            "background:transparent;"
        );

        QLabel * onHoldStatusLegendLabel = new QLabel("ON HOLD", this);
        onHoldStatusLegendLabel->setGeometry(30, 202, 270, 24);
        onHoldStatusLegendLabel->setStyleSheet
        (
            MONO + 
            "font-size:20px;"
            "letter-spacing:4px;"
            "font-weight:bold;"
            "color:#ffcc44;"
            "background:transparent;"
        );

        QLabel * verdictStatusLegendLabel = new QLabel("VERDICT", this);
        verdictStatusLegendLabel->setGeometry(30, 232, 270, 24);
        verdictStatusLegendLabel->setStyleSheet
        (
            MONO + 
            "font-size:20px;"
            "letter-spacing:4px;"
            "font-weight:bold;"
            "color:#ff6666;"
            "background:transparent;"
        );

        QLabel * sidebarSeparatorLine = new QLabel(this);
        sidebarSeparatorLine->setGeometry(30, 264, 260, 1);
        sidebarSeparatorLine->setStyleSheet
        (
            "background:rgba(0, 200, 255, 0.20);"
        );

        showAllProceedingsPanelButton = new Button("VIEW ALL", 25, 300, 270, 40, this);
        showFilterProceedingsPanelButton = new Button("FILTER BY STATUS", 25, 360, 270, 40, this);
        showUpdateStatusPanelButton = new Button("UPDATE STATUS", 25, 420, 270, 40, this);

        showAddRecordPanelButton = nullptr;
        if (isAdminUser)
        {
            showAddRecordPanelButton = new Button("ADD RECORD", 25, 480, 270, 40, this);
        }

        int backButtonVerticalPosition = isAdminUser ? 540 : 480;
        BackButton * returnNavigationButton = new BackButton(25, backButtonVerticalPosition, 270, 44, this);
        returnNavigationButton->raise();

        QObject::connect(returnNavigationButton, &QPushButton::clicked, [this]() { this->close(); });

        ongoingProceedingsStatCard = new StatCard(380, 150, "#44ff99", "ONGOING", this);
        onHoldProceedingsStatCard  = new StatCard(850, 150, "#ffcc44", "ON HOLD", this);
        verdictReachedStatCard = new StatCard(1300, 150, "#ff6666", "VERDICT REACHED", this);

        allProceedingsPanel = new ViewCourt(this);
        statusFilterPanel = new FilterCourt(this);
        statusUpdatePanel = new UpdateCourt(this);
        addProceedingPanel = new AddCourt(this);

        allProceedingsPanel->setGeometry(380, 250, 1150, 630);
        statusFilterPanel->setGeometry(380, 250, 1150, 630);
        statusUpdatePanel->setGeometry(380, 250, 1150, 630);
        addProceedingPanel->setGeometry(380, 250, 1150, 630);

        hideAllDisplayPanels();
        allProceedingsPanel->show();

        refreshJudicialStatCounts();

        QObject::connect(showAllProceedingsPanelButton, &QPushButton::clicked, [this]()
            {
                hideAllDisplayPanels();
                refreshJudicialStatCounts();
                allProceedingsPanel->refreshData();
                allProceedingsPanel->show();
            }
        );

        QObject::connect(showFilterProceedingsPanelButton, &QPushButton::clicked, [this]()
            {
                hideAllDisplayPanels();
                refreshJudicialStatCounts();
                statusFilterPanel->show();
            }
        );

        QObject::connect(showUpdateStatusPanelButton, &QPushButton::clicked, [this]()
            {
                hideAllDisplayPanels();
                refreshJudicialStatCounts();
                statusUpdatePanel->show();
            }
        );

        if (isAdminUser && showAddRecordPanelButton)
        {
            QObject::connect(showAddRecordPanelButton, &QPushButton::clicked, [this]()
                {
                    hideAllDisplayPanels();
                    refreshJudicialStatCounts();
                    addProceedingPanel->show();
                }
            );
        }
    }

    void resizeEvent(QResizeEvent * event) override
    {
        pageBackgroundContainer->resize(event->size());
    }
};

#endif