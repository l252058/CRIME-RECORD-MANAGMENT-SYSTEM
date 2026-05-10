#ifndef OFFICERMENU_H
#define OFFICERMENU_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QScrollArea>
#include <QStackedWidget>
#include <QResizeEvent>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QVector>
#include <functional>

#include "common.h"
#include "file.h"

// =============================================================================
//  Shared Stylesheet Helpers
// =============================================================================

inline static QString officerFieldLabelStyle()
{
    return
        MONO +
        "font-size   : 20px;"
        "font-weight : bold;"
        "color       : #a0d8f0;"
        "background  : transparent;";
}

inline static QString officerScrollAreaStyle()
{
    return
        "background    : rgba(3, 12, 35, 0.92);"
        "border        : 1px solid rgba(0, 200, 255, 0.35);"
        "border-radius : 12px;";
}

inline static QString officerResultLabelStyle()
{
    return
        "background  : transparent;"
        "color       : #c0dff5;"
        "font-family : 'Courier New', monospace;"
        "font-weight : bold;"
        "font-size   : 16px;"
        "padding     : 14px;";
}

// =============================================================================
//  ADD OFFICER PANEL
// =============================================================================

class AddOfficer : public QWidget
{
    Q_OBJECT

    Box    * officerIDBox;
    Box    * nameBox;
    Box    * rankBox;
    Box    * badgeBox;
    FeedbackLabel * feedback;

    void clearFields()
    {
        officerIDBox->clear();
        nameBox->clear();
        rankBox->clear();
        badgeBox->clear();
        feedback->clear();
    }

public:

    explicit AddOfficer(QWidget * parent = nullptr) : QWidget(parent)
    {
        new Card(40, 0, 1080, 560, this);
        QLabel* officerTitle1 = new QLabel("ADD NEW OFFICER", this);
        officerTitle1->setGeometry(40, 18, 1040, 28);
        officerTitle1->setStyleSheet(MONO + "font-size:18px; font-weight:bold; color:#00eaff; background:transparent;");
        QLabel* officerLine1 = new QLabel(this);
        officerLine1->setGeometry(40, 52, 1040, 1);
        officerLine1->setStyleSheet("background:rgba(0, 200, 255, 0.20);");

        QLabel * heading = new QLabel("Register official personnel into the database", this);
        heading->setGeometry(40, 68, 1040, 20);
        heading->setStyleSheet(MONO + "font-size:16px; color:#a0d8f0; background:transparent;");

        QLabel * idLabel = new QLabel("Officer ID  *", this);
        idLabel->setGeometry(40, 100, 300, 24);
        idLabel->setStyleSheet(officerFieldLabelStyle());
        officerIDBox = new Box(40, 126, 1040, 38, "e.g.  OFF-001", this);

        QLabel * nameLabel = new QLabel("Full Name  *", this);
        nameLabel->setGeometry(40, 180, 300, 24);
        nameLabel->setStyleSheet(officerFieldLabelStyle());
        nameBox = new Box(40, 206, 1040, 38, "e.g.  Ali Hassan", this);

        QLabel * rankLabel = new QLabel("Rank  *", this);
        rankLabel->setGeometry(40, 260, 300, 24);
        rankLabel->setStyleSheet(officerFieldLabelStyle());
        rankBox = new Box(40, 286, 1040, 38, "e.g.  Inspector", this);

        QLabel * badgeLabel = new QLabel("Badge Number  *", this);
        badgeLabel->setGeometry(40, 340, 300, 24);
        badgeLabel->setStyleSheet(officerFieldLabelStyle());
        badgeBox = new Box(40, 366, 1040, 38, "e.g.  4421-X", this);

        feedback = new FeedbackLabel(40, 420, 1040, this);

        Button * saveButton = new Button("SAVE", 40, 460, 180, 44, this);
        ClearButton * clearButton = new ClearButton("CLEAR", 235, 460, 180, 44, this);

        QObject::connect(clearButton, &QPushButton::clicked, [this](){ clearFields(); });

        QObject::connect(saveButton, &QPushButton::clicked, [this]()
        {
            QString id    = officerIDBox->text().trimmed();
            QString name  = nameBox->text().trimmed();
            QString rank  = rankBox->text().trimmed();
            QString badge = badgeBox->text().trimmed();

            if (id.isEmpty() || name.isEmpty() || rank.isEmpty())
            {
                feedback->showError("Required: ID, Name, and Rank.");
                return;
            }

            if (FileHandler::officerIDExists(id))
            {
                feedback->showError("Officer ID already exists.");
                return;
            }

            FileHandler::saveOfficer(id, name, rank, badge);
            FileHandler::appendLog("ADMIN", QString("Officer added — ID: %1  Name: %2  Rank: %3").arg(id, name, rank));
            
            feedback->showSuccess("Officer registered successfully!");
            
            clearFields();
            
            emit officerAdded();
        });
    }

signals:
    void officerAdded();
};

// =============================================================================
//  ASSIGN / REASSIGN OFFICER PANEL
// =============================================================================

class AssignOfficer : public QWidget
{
    Q_OBJECT
    
    Box           * officerIDBox;
    Box           * caseIDBox;
    QLabel        * currentAssignmentLabel;
    FeedbackLabel * feedback;
    bool            officerLoaded = false;

    void clearFields()
    {
        officerIDBox->clear();
        caseIDBox->clear();
        feedback->clear();
        officerLoaded = false;
        
        currentAssignmentLabel->setText("  Current assignment will appear here after loading.");
    }

public:

    explicit AssignOfficer(QWidget * parent = nullptr) : QWidget(parent)
    {
        new Card(40, 0, 1080, 560, this);
        QLabel* officerTitle2 = new QLabel("ASSIGN / REASSIGN OFFICER", this);
        officerTitle2->setGeometry(40, 18, 1040, 28);
        officerTitle2->setStyleSheet(MONO + "font-size:18px; font-weight:bold; color:#ffcc44; background:transparent;");
        QLabel* officerLine2 = new QLabel(this);
        officerLine2->setGeometry(40, 52, 1040, 1);
        officerLine2->setStyleSheet("background:rgba(255, 200, 0, 0.20);");

        QLabel * officerLabel = new QLabel("Officer ID  *", this);
        officerLabel->setGeometry(40, 100, 300, 24);
        officerLabel->setStyleSheet(officerFieldLabelStyle());
        officerIDBox = new Box(40, 126, 850, 38, "e.g.  OFF-001", this);
        Button * loadButton = new Button("Load", 900, 126, 180, 44, this);

        currentAssignmentLabel = new QLabel("  Current assignment will appear here after loading.", this);
        currentAssignmentLabel->setGeometry(40, 170, 1040, 22);
        currentAssignmentLabel->setStyleSheet(MONO + "font-size:16px; font-weight:bold; color:#ffcc44; background:transparent;");

        QLabel * caseLabel = new QLabel("New Case ID  *", this);
        caseLabel->setGeometry(40, 210, 300, 24);
        caseLabel->setStyleSheet(officerFieldLabelStyle());
        caseIDBox = new Box(40, 236, 1040, 38, "e.g.  CR-001", this);

        QLabel * note = new QLabel(
            "  Load an Officer ID first to see their current assignment.\n"
            "  Enter a new Case ID and click Assign / Reassign to update.", this);
        note->setGeometry(40, 290, 1040, 40);
        note->setStyleSheet(MONO + "font-size:16px; font-weight:bold; color:#7ab8e0; background:transparent;");

        feedback = new FeedbackLabel(40, 340, 1040, this);

        Button * assignButton   = new Button("Assign",   40, 420, 180, 44, this);
        Button * reassignButton = new Button("Reassign", 235, 420, 180, 44, this);

        QObject::connect(loadButton, &QPushButton::clicked, [this]()
        {
            QString id = officerIDBox->text().trimmed();
            
            if (id.isEmpty()) 
            { 
                feedback->showError("Enter an Officer ID to load."); 
                return; 
            }
            
            if (!FileHandler::officerIDExists(id))
            {
                feedback->showError("Officer ID not found.");
                currentAssignmentLabel->setText("  Officer not found.");
                officerLoaded = false; 
                return;
            }
            
            QStringList parts = FileHandler::loadOfficer(id);
            
            if (parts.size() < 4)
            {
                feedback->showError("Officer record is incomplete or corrupted.");
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
            feedback->showSuccess("Officer loaded. Enter a new Case ID to assign.");
        });

        auto doAssign = [this](const QString &action)
        {
            QString officerID = officerIDBox->text().trimmed();
            QString caseID    = caseIDBox->text().trimmed();
            
            if (!officerLoaded) 
            { 
                feedback->showError("Load a valid Officer ID first."); 
                return; 
            }
            
            if (officerID.isEmpty() || caseID.isEmpty())
            { 
                feedback->showError("Officer ID and Case ID are both required."); 
                return; 
            }
            
            if (!FileHandler::officerIDExists(officerID))
            { 
                feedback->showError("Officer ID not found."); 
                return; 
            }
            
            if (!FileHandler::caseIDExists(caseID))
            { 
                feedback->showError("Case ID not found in crime records."); 
                return; 
            }

            FileHandler::assignOfficerToCase(officerID, caseID);
            
            FileHandler::appendLog("ADMIN", QString("Officer %1 — Officer ID: %2 → Case ID: %3").arg(action, officerID, caseID));
            
            feedback->showSuccess(QString("Officer %1 successfully %2 to case %3.").arg(officerID, action.toLower() + "ed", caseID));
            
            currentAssignmentLabel->setText(QString("  Officer: %1   |   Now assigned to: %2").arg(officerID, caseID));
            
            emit officerAssigned();
        };

        QObject::connect(assignButton, &QPushButton::clicked, [doAssign]()
        { 
            doAssign("Assign"); 
        });
        
        QObject::connect(reassignButton, &QPushButton::clicked, [doAssign]()
        { 
            doAssign("Reassign"); 
        });
    }

signals:
    void officerAssigned();
};

// =============================================================================
//  VIEW OFFICERS PANEL
// =============================================================================

class ViewOfficers : public QWidget
{
private:

    Button      * refreshButton;
    QLabel      * resultLabel;
    QScrollArea * scrollArea;
    bool          isAdminRole;

public:

    explicit ViewOfficers(bool adminRole, QWidget * parent = nullptr)
        : QWidget(parent)
        , isAdminRole(adminRole)
    {
        QLabel * heading = new QLabel("ALL OFFICERS", this);
        
        heading->setGeometry(0, 8, 900, 30);
        
        heading->setStyleSheet(MONO + "font-size:18px; font-weight:bold; color:#00eaff; background:transparent;");

        refreshButton = new Button("REFRESH", 965, 6, 180, 44, this);

        scrollArea = new QScrollArea(this);
        
        scrollArea->setGeometry(0, 50, 1150, 480);
        scrollArea->setStyleSheet(officerScrollAreaStyle());
        scrollArea->setWidgetResizable(true);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        resultLabel = new QLabel();
        
        resultLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        resultLabel->setWordWrap(true);
        resultLabel->setStyleSheet(officerResultLabelStyle());
        resultLabel->setText("  Click REFRESH to load all officers.");

        scrollArea->setWidget(resultLabel);

        QObject::connect(refreshButton, &QPushButton::clicked, [this]()
        { 
            loadAndDisplay(); 
        });
    }

    void loadAndDisplay()
    {
        const QStringList records = FileHandler::loadOfficers();

        if (records.isEmpty()) 
        { 
            resultLabel->setText("  No officers found."); 
            return; 
        }

        QString display;
        
        for (const QString & line : records)
        {
            display += DataFormatter::formatOfficer(line.split("\t"));
        }
        
        resultLabel->setText(display);

        QString role = "USER";
        
        if (isAdminRole)
        {
            role = "ADMIN";
        }
        
        FileHandler::appendLog(role, "Viewed officer list.");
    }
};

// =============================================================================
//  OFFICERS PAGE
// =============================================================================

class Officers : public QWidget
{
private:

    QLabel         * backgroundImage;
    QStackedWidget * stack;
    ViewOfficers   * viewPage;
    AddOfficer     * addPage;
    AssignOfficer  * assignPage;
    Button         * viewBtn;
    Button         * addBtn;
    Button         * assignBtn;
    StatCard       * assignedNumber;
    StatCard       * unassignedNumber;
    StatCard       * totalNumber;


    void refreshCounts()
    {
        int assigned   = FileHandler::countAssignedOfficers();
        int unassigned = FileHandler::countUnassignedOfficers();
        
        assignedNumber->setValue(assigned);
        unassignedNumber->setValue(unassigned);
        totalNumber->setValue(assigned + unassigned);
    }

    void buildLegend(const QString & text, const QString & color, int y)
    {
        QLabel * legend = new QLabel(text, this);
        
        legend->setGeometry(30, y, 270, 24);
        
        legend->setStyleSheet(MONO + QString("font-size:20px; letter-spacing:4px; font-weight:bold; color:%1; background:transparent;").arg(color));
    }

public:

    explicit Officers(bool isAdmin) : QWidget(nullptr)
    {
        setWindowTitle("Officer Management — CRIME RECORD MANAGEMENT SYSTEM");

        backgroundImage = UI::setupBackground(this, "backgroundThree.png");

        UI::setupSidebar(this, "[ OFFICERS ]");
        UI::setupPageHeader(this, "OFFICER MANAGEMENT", "Manage officers and assign them to cases");
        UI::setupFooter(this);

        buildLegend("ASSIGNED",   "#44ff99", 172);
        buildLegend("UNASSIGNED", "#ff6666", 200);
        buildLegend("TOTAL",      "#c0dff5", 228);

        QLabel * dividerTwo = new QLabel(this);
        
        dividerTwo->setGeometry(30, 264, 260, 1);
        
        dividerTwo->setStyleSheet("background:rgba(0,200,255,0.20);");

        viewBtn = new Button("View Officers", 25, 300, 270, 40, this);

        addBtn    = nullptr;
        assignBtn = nullptr;

        if (isAdmin)
        {
            addBtn = new Button("Add Officer", 25, 360, 270, 40, this);

            assignBtn = new Button("Assign / Reassign", 25, 420, 270, 40, this);
        }

        BackButton *bb = new BackButton(25, isAdmin ? 480 : 360, 270, 44, this);
        bb->raise();

        QObject::connect(bb, &QPushButton::clicked, [this]() { this->close(); });

        assignedNumber   = new StatCard(380, 150, "#44ff99", "ASSIGNED", this);
        unassignedNumber = new StatCard(620, 150, "#ff6666", "UNASSIGNED", this);
        totalNumber      = new StatCard(860, 150, "#c0dff5", "TOTAL FORCE", this);

        stack = new QStackedWidget(this);
        
        stack->setGeometry(380, 250, 1150, 580);
        stack->setStyleSheet("background:transparent;");

        viewPage   = new ViewOfficers(isAdmin, stack);
        addPage    = new AddOfficer(stack);
        assignPage = new AssignOfficer(stack);

        stack->addWidget(viewPage);
        stack->addWidget(addPage);
        stack->addWidget(assignPage);
        stack->setCurrentIndex(0);

        refreshCounts();

        QObject::connect(viewBtn, &QPushButton::clicked, [this]()
        {
            refreshCounts();
            viewPage->loadAndDisplay();
            stack->setCurrentIndex(0);
        });

        if (isAdmin)
        {
            if (addBtn != nullptr)
            {
                if (assignBtn != nullptr)
                {
                    QObject::connect(addBtn, &QPushButton::clicked, [this]()
                    { 
                        refreshCounts(); 
                        stack->setCurrentIndex(1); 
                    });

                    QObject::connect(assignBtn, &QPushButton::clicked, [this]()
                    { 
                        refreshCounts(); 
                        stack->setCurrentIndex(2); 
                    });

                    QObject::connect(addPage, &AddOfficer::officerAdded, [this]()
                    { 
                        refreshCounts(); 
                    });

                    QObject::connect(assignPage, &AssignOfficer::officerAssigned, [this]()
                    { 
                        refreshCounts(); 
                    });
                }
            }
        }
    }

    void resizeEvent(QResizeEvent * event) override
    {
        backgroundImage->resize(event->size());
    }
};

#endif // OFFICERMENU_H