#ifndef OFFICERMENU_H
#define OFFICERMENU_H

#include <QWidget>
#include <QLabel>
#include <QResizeEvent>

#include "common.h"
#include "file.h"

class AddOfficer : public QWidget
{
private:

    Box * officerIdentifierInput;
    Box * officerNameInput;
    Box * officerRankInput;
    Box * officerBadgeInput;
    FeedbackLabel * actionFeedbackLabel;

    void clearFields()
    {
        officerIdentifierInput->clear();
        officerNameInput->clear();
        officerRankInput->clear();
        officerBadgeInput->clear();
        actionFeedbackLabel->clear();
    }

public:

    AddOfficer(QWidget * parent = nullptr) : QWidget(parent)
    {
        new Card(20, 0, 1080, 520, this);

        QLabel* addTitle = new QLabel("ADD NEW OFFICER", this);
        addTitle->setGeometry(40, 18, 1040, 28);
        addTitle->setStyleSheet
        (
            MONO +
            "font-size:18px;"
            "font-weight:bold;"
            "color:#00eaff;"
            "background:transparent;"
        );

        QLabel* addLine = new QLabel(this);
        addLine->setGeometry(40, 52, 1040, 1);
        addLine->setStyleSheet("background:rgba(0, 200, 255, 0.20);");

        QLabel * heading = new QLabel("Register official personnel into the database", this);
        heading->setGeometry(40, 68, 1040, 20);
        heading->setStyleSheet
        (
            MONO +
            "font-size:16px;"
            "color:#a0d8f0;"
            "background:transparent;"
        );

        QLabel * idLabel = new QLabel("Officer ID  *", this);
        idLabel->setGeometry(40, 100, 300, 24);
        idLabel->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "font-weight:bold;"
            "color:#a0d8f0;"
            "background:transparent;"
        );
        officerIdentifierInput = new Box(40, 126, 1040, 38, "e.g.  OFF-001", this);

        QLabel * nameLabel = new QLabel("Full Name  *", this);
        nameLabel->setGeometry(40, 180, 300, 24);
        nameLabel->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "font-weight:bold;"
            "color:#a0d8f0;"
            "background:transparent;"
        );
        officerNameInput = new Box(40, 206, 1040, 38, "e.g.  Ali Hassan", this);

        QLabel * rankLabel = new QLabel("Rank  *", this);
        rankLabel->setGeometry(40, 260, 300, 24);
        rankLabel->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "font-weight:bold;"
            "color:#a0d8f0;"
            "background:transparent;"
        );
        officerRankInput = new Box(40, 286, 1040, 38, "e.g.  Inspector", this);

        QLabel * badgeLabel = new QLabel("Badge Number  *", this);
        badgeLabel->setGeometry(40, 340, 300, 24);
        badgeLabel->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "font-weight:bold;"
            "color:#a0d8f0;"
            "background:transparent;"
        );
        officerBadgeInput = new Box(40, 366, 1040, 38, "e.g.  4421-X", this);

        actionFeedbackLabel = new FeedbackLabel(40, 420, 1040, this);

        Button * saveButton = new Button("SAVE", 40, 460, 180, 44, this);
        ClearButton * clearButton = new ClearButton("CLEAR", 900, 460, 180, 44, this);

        QObject::connect(clearButton, &QPushButton::clicked, [this]()
            {
                clearFields();
            }
        );

        QObject::connect(saveButton, &QPushButton::clicked, [this]()
            {
                QString id = officerIdentifierInput->text().trimmed();
                QString name = officerNameInput->text().trimmed();
                QString rank  = officerRankInput->text().trimmed();
                QString badge = officerBadgeInput->text().trimmed();

                if (id.isEmpty() || name.isEmpty() || rank.isEmpty())
                {
                    actionFeedbackLabel->showError("Required: ID, Name, and Rank.");
                    return;
                }

                if (FileHandler::officerIDExists(id))
                {
                    actionFeedbackLabel->showError("Officer ID already exists.");
                    return;
                }

                FileHandler::saveOfficer(id, name, rank, badge);

                actionFeedbackLabel->showSuccess("Officer registered successfully!");

                clearFields();
            }
        );
    }
};

class AssignOfficer : public QWidget
{
private:

    Box * officerIdentifierInput;
    Box * caseIdentifierInput;
    QLabel * currentAssignmentLabel;
    FeedbackLabel * actionFeedbackLabel;
    bool officerLoaded = false;

    void clearFields()
    {
        officerIdentifierInput->clear();
        caseIdentifierInput->clear();
        actionFeedbackLabel->clear();
        officerLoaded = false;
        currentAssignmentLabel->setText("Current assignment will appear here after loading.");
    }

public:

    AssignOfficer(QWidget * parent = nullptr) : QWidget(parent)
    {
        new Card(20, 0, 1080, 520, this);

        QLabel* assignTitle = new QLabel("ASSIGN / REASSIGN OFFICER", this);
        assignTitle->setGeometry(40, 18, 1040, 28);
        assignTitle->setStyleSheet
        (
            MONO +
            "font-size:18px;"
            "font-weight:bold;"
            "color:#ffcc44;"
            "background:transparent;"
        );

        QLabel* assignLine = new QLabel(this);
        assignLine->setGeometry(40, 52, 1040, 1);
        assignLine->setStyleSheet("background:rgba(255, 200, 0, 0.20);");

        QLabel * officerLabel = new QLabel("Officer ID  *", this);
        officerLabel->setGeometry(40, 100, 300, 24);
        officerLabel->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "font-weight:bold;"
            "color:#a0d8f0;"
            "background:transparent;"
        );
        officerIdentifierInput = new Box(40, 126, 850, 38, "e.g.  OFF-001", this);
        Button * loadButton = new Button("Load", 900, 126, 180, 38, this);

        currentAssignmentLabel = new QLabel("Current assignment will appear here after loading.", this);
        currentAssignmentLabel->setGeometry(40, 170, 1040, 22);
        currentAssignmentLabel->setStyleSheet
        (
            MONO +
            "font-size:16px;"
            "font-weight:bold;"
            "color:#ffcc44;"
            "background:transparent;"
        );

        QLabel * caseLabel = new QLabel("New Case ID  *", this);
        caseLabel->setGeometry(40, 210, 300, 24);
        caseLabel->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "font-weight:bold;"
            "color:#a0d8f0;"
            "background:transparent;"
        );
        caseIdentifierInput = new Box(40, 236, 1040, 38, "e.g.  CR-001", this);

        QLabel * note = new QLabel("Load an Officer ID first to see their current assignment.\nEnter a new Case ID and click Assign / Reassign to update.", this);
        note->setGeometry(40, 290, 1040, 40);
        note->setStyleSheet
        (
            MONO +
            "font-size:16px;"
            "font-weight:bold;"
            "color:#7ab8e0;"
            "background:transparent;"
        );

        actionFeedbackLabel = new FeedbackLabel(40, 340, 1040, this);

        Button * assignButton   = new Button("Assign",   40, 420, 180, 44, this);
        ClearButton * reassignButton = new ClearButton("Reassign", 900, 420, 180, 44, this);

        QObject::connect(loadButton, &QPushButton::clicked, [this]()
        {
            QString id = officerIdentifierInput->text().trimmed();

            if (id.isEmpty())
            {
                actionFeedbackLabel->showError("Enter an Officer ID to load.");
                return;
            }

            if (!FileHandler::officerIDExists(id))
            {
                actionFeedbackLabel->showError("Officer ID not found.");
                currentAssignmentLabel->setText("  Officer not found.");
                officerLoaded = false;
                return;
            }

            QStringList parts = FileHandler::loadOfficer(id);

            if (parts.size() < 4)
            {
                actionFeedbackLabel->showError("Officer record is incomplete or corrupted.");
                officerLoaded = false;
                return;
            }

            QString current = "Unassigned";
            if (parts.size() >= 5)
            {
                if (!parts[4].trimmed().isEmpty())
                {
                    current = parts[4].trimmed();
                }
            }

            officerLoaded = true;
            currentAssignmentLabel->setText(QString("  Officer: %1   |   Currently assigned to: %2").arg(id, current));
            actionFeedbackLabel->showSuccess("Officer loaded. Enter a new Case ID to assign.");
        });

        auto performAssignmentAction = [this](const QString &action)
        {
            QString officerID = officerIdentifierInput->text().trimmed();
            QString caseID    = caseIdentifierInput->text().trimmed();

            if (!officerLoaded)
            {
                actionFeedbackLabel->showError("Load a valid Officer ID first.");
                return;
            }

            if (officerID.isEmpty() || caseID.isEmpty())
            {
                actionFeedbackLabel->showError("Officer ID and Case ID are both required.");
                return;
            }

            if (!FileHandler::officerIDExists(officerID))
            {
                actionFeedbackLabel->showError("Officer ID not found.");
                return;
            }

            if (!FileHandler::caseIDExists(caseID))
            {
                actionFeedbackLabel->showError("Case ID not found in crime records.");
                return;
            }

            FileHandler::assignOfficerToCase(officerID, caseID);

            actionFeedbackLabel->showSuccess(QString("Officer %1 successfully %2 to case %3.").arg(officerID, action.toLower() + "ed", caseID));
            currentAssignmentLabel->setText(QString("  Officer: %1   |   Now assigned to: %2").arg(officerID, caseID));
        };

        QObject::connect(assignButton, &QPushButton::clicked, [this, performAssignmentAction]()
            {
                performAssignmentAction("Assign");
            }
        );

        QObject::connect(reassignButton, &QPushButton::clicked, [this, performAssignmentAction]()
            {
                performAssignmentAction("Reassign");
            }
        );
    }
};

class ViewOfficers : public QWidget
{
private:

    Button * refreshRecordsButton;
    RecordDisplay * officersDisplay;
    bool isAdminRole;

public:

    ViewOfficers(bool adminRole, QWidget * parent = nullptr): QWidget(parent), isAdminRole(adminRole)
    {
        QLabel * viewTitle = new QLabel("ALL OFFICERS", this);
        viewTitle->setGeometry(0, 8, 900, 30);
        viewTitle->setStyleSheet
        (
            MONO +
            "font-size:18px;"
            "font-weight:bold;"
            "color:#00eaff;"
            "background:transparent;"
        );

        QLabel* viewLine = new QLabel(this);
        viewLine->setGeometry(0, 42, 900, 1);
        viewLine->setStyleSheet("background:rgba(0, 200, 255, 0.20);");

        refreshRecordsButton = new Button("REFRESH", 965, 6, 180, 30, this);
        refreshRecordsButton->setSound("refreshButtonSound.mp3");
        officersDisplay = new RecordDisplay(0, 50, 1150, 480, this, "Click REFRESH to load all officers.");

        QObject::connect(refreshRecordsButton, &QPushButton::clicked, [this]()
            {
                loadAndDisplay();
            }
        );
    }

    void loadAndDisplay()
    {
        const QStringList records = FileHandler::loadOfficers();

        if (records.isEmpty())
        {
            officersDisplay->setText("  No officers found.");
            return;
        }

        QString display;
        for (const QString & line : records)
        {
            display += DataFormatter::formatOfficer(line.split("\t"));
        }

        officersDisplay->setText(display);
    }
};

class Officers : public QWidget
{
private:

    QLabel * pageBackground;
    ViewOfficers * allOfficersPanel;
    AddOfficer * addOfficerPanel;
    AssignOfficer  * assignOfficerPanel;
    Button * showViewPanelButton;
    Button * showAddPanelButton;
    Button * showAssignPanelButton;
    StatCard * assignedStatCard;
    StatCard * unassignedStatCard;
    StatCard * totalForceStatCard;

    void hideAllPanels()
    {
        allOfficersPanel->hide();
        addOfficerPanel->hide();
        assignOfficerPanel->hide();
    }

    void refreshCounts()
    {
        int assigned = FileHandler::countAssignedOfficers();
        int unassigned = FileHandler::countUnassignedOfficers();

        assignedStatCard->setValue(assigned);
        unassignedStatCard->setValue(unassigned);
        totalForceStatCard->setValue(assigned + unassigned);
    }

public:

    explicit Officers(bool isAdmin) : QWidget(nullptr)
    {
        setWindowTitle("Officer Management — CRIME RECORD MANAGEMENT SYSTEM");

        pageBackground = new Background(this, "backgroundThree.png");

        new Sidebar(this, "[ OFFICERS ]");
        new PageHeader(this, "OFFICER MANAGEMENT", "Manage officers and assign them to cases");
        new Footer(this);

        QLabel * assignedLegend = new QLabel("ASSIGNED", this);
        assignedLegend->setGeometry(30, 172, 270, 24);
        assignedLegend->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "letter-spacing:4px;"
            "font-weight:bold;"
            "color:#44ff99;"
            "background:transparent;"
        );

        QLabel * unassignedLegend = new QLabel("UNASSIGNED", this);
        unassignedLegend->setGeometry(30, 200, 270, 24);
        unassignedLegend->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "letter-spacing:4px;"
            "font-weight:bold;"
            "color:#ff6666;"
            "background:transparent;"
        );

        QLabel * totalLegend = new QLabel("TOTAL", this);
        totalLegend->setGeometry(30, 228, 270, 24);
        totalLegend->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "letter-spacing:4px;"
            "font-weight:bold;"
            "color:#c0dff5;"
            "background:transparent;"
        );

        QLabel * sidebarDivider = new QLabel(this);
        sidebarDivider->setGeometry(30, 264, 260, 1);
        sidebarDivider->setStyleSheet("background:rgba(0,200,255,0.20);");

        showViewPanelButton = new Button("View Officers", 25, 300, 270, 40, this);

        showAddPanelButton = nullptr;
        showAssignPanelButton = nullptr;

        if (isAdmin)
        {
            showAddPanelButton    = new Button("Add Officer", 25, 360, 270, 40, this);
            showAssignPanelButton = new Button("Assign / Reassign", 25, 420, 270, 40, this);
        }

        int backBtnY = isAdmin ? 480 : 360;
        BackButton *bb = new BackButton(25, backBtnY, 270, 44, this);
        bb->raise();

        QObject::connect(bb, &QPushButton::clicked, [this]() { this->close(); });

        assignedStatCard = new StatCard(380, 150, "#44ff99", "ASSIGNED", this);
        unassignedStatCard = new StatCard(850, 150, "#ff6666", "UNASSIGNED", this);
        totalForceStatCard = new StatCard(1300, 150, "#c0dff5", "TOTAL FORCE", this);

        allOfficersPanel = new ViewOfficers(isAdmin, this);
        addOfficerPanel = new AddOfficer(this);
        assignOfficerPanel = new AssignOfficer(this);

        allOfficersPanel->setGeometry(380, 250, 1150, 580);
        addOfficerPanel->setGeometry(380, 250, 1150, 580);
        assignOfficerPanel->setGeometry(380, 250, 1150, 580);

        hideAllPanels();
        allOfficersPanel->show();

        refreshCounts();

        QObject::connect(showViewPanelButton, &QPushButton::clicked, [this]()
        {
            hideAllPanels();
            refreshCounts();
            allOfficersPanel->loadAndDisplay();
            allOfficersPanel->show();
        });

        if (isAdmin)
        {
            if (showAddPanelButton != nullptr)
            {
                QObject::connect(showAddPanelButton, &QPushButton::clicked, [this]()
                    {
                        hideAllPanels();
                        refreshCounts();
                        addOfficerPanel->show();
                    }
                );
            }

            if (showAssignPanelButton != nullptr)
            {
                QObject::connect(showAssignPanelButton, &QPushButton::clicked, [this]()
                    {
                        hideAllPanels();
                        refreshCounts();
                        assignOfficerPanel->show();
                    }
                );
            }
        }
    }

    void resizeEvent(QResizeEvent * event) override
    {
        pageBackground->resize(event->size());
    }
};

#endif