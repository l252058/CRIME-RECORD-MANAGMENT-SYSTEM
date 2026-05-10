#ifndef CRIMERECORDS_H
#define CRIMERECORDS_H

#include <QMessageBox>
#include <QTextEdit>
#include "common.h"
#include "file.h"

class View : public QWidget
{
private:
    Button *refresh;
    RecordDisplay *display;
    bool isAdminRole;

public:
    View(bool adminRole, QWidget *parent = nullptr) : QWidget(parent), isAdminRole(adminRole)
    {
        QLabel *heading = new QLabel("  ALL CRIME RECORDS", this);
        heading->setGeometry(0, 12, 860, 30);
        heading->setStyleSheet
        (
            MONO +
            "font-size : 20px;"
            "font-weight : bold;"
            "color : #00eaff;"
            "background : transparent;"
        );


        refresh = new Button("REFRESH", 1000, 12, 140, 34, this);
        display = new RecordDisplay(0, 50, 1150, 625, this, "  Click Refresh to load all records.");

        QObject::connect(refresh, &QPushButton::clicked, [this]()
        {
            QStringList records = FileHandler::loadRecords();

            if (records.isEmpty())
            {
                display->setText("  No records found.");
                return;
            }

            QString outputText;

            for (const QString &line : records)
            {
                outputText += DataFormatter::formatCrime(line.split("\t"));
            }

            display->setText(outputText);

            QString role;

            if (isAdminRole)
            {
                role = "ADMIN";
            }
            else
            {
                role = "USER";
            }

            FileHandler::appendLog(role, "Viewed all crime records (" + QString::number(records.size()) + " records)");
        });
    }
};

class Search : public QWidget
{
private:
    Box *caseIDBox;
    Button *searchOne;
    Box *locationBox;
    Button *searchTwo;
    RecordDisplay *searchResult;
    bool isAdminRole;

    void performSearch(int fieldIndex, QLineEdit *inputField)
    {
        QString query = inputField->text().trimmed();

        if (query.isEmpty())
        {
            searchResult->setText("  Enter a search term.");
            return;
        }

        QString outputText;

        for (const QString &line : FileHandler::loadRecords())
        {
            QStringList recordParts = line.split("\t");

            if (recordParts.size() > fieldIndex)
            {
                if (recordParts[fieldIndex].contains(query, Qt::CaseInsensitive))
                {
                    outputText += DataFormatter::formatCrime(recordParts);
                }
            }
        }

        if (outputText.isEmpty())
        {
            searchResult->setText("  No matching records found.");
        }
        else
        {
            searchResult->setText(outputText);
        }

        QString role;

        if (isAdminRole)
        {
            role = "ADMIN";
        }
        else
        {
            role = "USER";
        }

        FileHandler::appendLog(role, "Searched crime records for: " + query);
    }

public:
    Search(bool adminRole, QWidget *parent = nullptr) : QWidget(parent), isAdminRole(adminRole)
    {
        new Card(0, 30, 1150, 220, this);
        QLabel* searchTitle = new QLabel("SEARCH CRIME RECORDS", this);
        searchTitle->setGeometry(20, 35, 1110, 28);
        searchTitle->setStyleSheet
        (
            MONO +
            "font-size:18px;"
            "font-weight:bold;"
            "color:#00eaff;"
            "background:transparent;"
        );
        QLabel* searchLine = new QLabel(this);
        searchLine->setGeometry(20, 60, 1110, 1);
        searchLine->setStyleSheet("background:rgba(0, 200, 255, 0.20);");

        QLabel *caseIdLabel = new QLabel("Search by Case ID", this);
        caseIdLabel->setGeometry(20, 68, 1110, 20);
        caseIdLabel->setStyleSheet
        (
            MONO +
            "font-size : 18px;"
            "font-weight : bold;"
            "color : #a0d8f0;"
            "background : transparent;"
        );

        caseIDBox = new Box(20, 92, 920, 38, "e.g.  CR-001", this);
        searchOne = new Button("Search", 950, 92, 180, 44, this);

        QLabel *locationLabel = new QLabel("Search by Location", this);
        locationLabel->setGeometry(20, 144, 1110, 20);
        locationLabel->setStyleSheet
        (
            MONO +
            "font-size : 18px;"
            "font-weight : bold;"
            "color : #a0d8f0;"
            "background : transparent;"
        );

        locationBox = new Box(20, 168, 920, 38, "e.g.  Karachi", this);
        searchTwo = new Button("Search", 950, 168, 180, 44, this);
        searchResult = new RecordDisplay(0, 260, 1150, 430, this, "  Enter a search term above and press Search.");

        QObject::connect(searchOne, &QPushButton::clicked, [this]()
            {
                performSearch(0, caseIDBox);
            }
        );

        QObject::connect(searchTwo, &QPushButton::clicked, [this]()
            {
                performSearch(1, locationBox);
            }
        );
    }
};

class Sort : public QWidget
{
private:
    Button *caseIDSort;
    Button *locationSort;
    Button *statusSort;
    RecordDisplay *sortResult;
    bool isAdminRole;

    void performSort(int field)
    {
        QStringList rawRecords = FileHandler::loadRecords();
        QList<QStringList> parsedRecords;

        for (const QString &line : rawRecords)
        {
            parsedRecords.append(line.split("\t"));
        }

        pureBubbleSort(parsedRecords, field);

        QString outputText;

        for (const QStringList &recordParts : parsedRecords)
        {
            outputText += DataFormatter::formatCrime(recordParts);
        }

        if (outputText.isEmpty())
        {
            sortResult->setText("  No records found.");
        }
        else
        {
            sortResult->setText(outputText);
        }

        QString role = isAdminRole ? "ADMIN" : "USER";
        QString fieldName = (field == 0) ? "Case ID" : (field == 1 ? "Location" : "Status");
        FileHandler::appendLog(role, "Sorted crime records by " + fieldName);
    }

public:
    Sort(bool adminRole, QWidget *parent = nullptr) : QWidget(parent), isAdminRole(adminRole)
    {
        new Card(0, 20, 1150, 128, this);

        QLabel* sortTitle = new QLabel("SORT CRIME RECORDS", this);
        sortTitle->setGeometry(20, 35, 1150, 28);
        sortTitle->setStyleSheet
        (
            MONO +
            "font-size:18px;"
            "font-weight:bold;"
            "color:#00eaff;"
            "background:transparent;"
        );
        QLabel* sortLine = new QLabel(this);
        sortLine->setGeometry(20, 60, 1150, 1);
        sortLine->setStyleSheet("background:rgba(0, 200, 255, 0.20);");


        caseIDSort   = new Button("BY CASE ID", 20, 80, 250, 48, this);
        locationSort = new Button("BY LOCATION", 425, 80, 250, 48, this);
        statusSort   = new Button("BY STATUS", 880, 80, 250, 48, this);

        sortResult = new RecordDisplay(0, 200, 1150, 450, this, "  Press a sort button above.");

        QObject::connect(caseIDSort, &QPushButton::clicked, [this]()
        {
            performSort(0);
        });

        QObject::connect(locationSort, &QPushButton::clicked, [this]()
        {
            performSort(1);
        });

        QObject::connect(statusSort, &QPushButton::clicked, [this]()
        {
            performSort(4);
        });
    }
};

class Modify : public QWidget
{
private:
    Box *caseIDBox;
    Box *locationBox;
    Box *typeBox;
    DescriptionBox *descriptionBox;
    Button *loadButton;
    FeedbackLabel  *message;
    Button *saveButton;
    ClearButton *deleteButton;
    QString selectedStatus;

public:
    Modify(QWidget *parent = nullptr) : QWidget(parent), selectedStatus("Pending")
    {
        new Card(20, 10, 1140, 670, this);

        QLabel* modifyTitle = new QLabel("MODIFY / DELETE RECORD", this);
        modifyTitle->setGeometry(40, 18, 1100, 28);
        modifyTitle->setStyleSheet
        (
            MONO +
            "font-size:18px;"
            "font-weight:bold;"
            "color:#ffcc44;"
            "background:transparent;"
        );
        QLabel* modifyLine = new QLabel(this);
        modifyLine->setGeometry(40, 52, 1100, 1);
        modifyLine->setStyleSheet("background:rgba(255, 200, 0, 0.20);");

        QLabel *instructionLabel = new QLabel("Enter Case ID to load the record", this);
        instructionLabel->setGeometry(40, 68, 1100, 20);
        instructionLabel->setStyleSheet
        (
            MONO +
            "font-size:16px;"
            "color:#a0d8f0;"
            "background:transparent;"
        );

        caseIDBox = new Box(40, 92, 900, 38, "e.g.  CR-001", this);
        loadButton = new Button("Load Record", 960, 92, 180, 44, this);

        QLabel *editInstructionLabel = new QLabel("Edit the fields below then Save or Delete", this);
        editInstructionLabel->setGeometry(40, 148, 1100, 20);
        editInstructionLabel->setStyleSheet
        (
            MONO +
            "font-size:16px;"
            "color:#a0d8f0;"
            "background:transparent;"
        );

        QLabel *locationLabel = new QLabel(" Location  *", this);
        locationLabel->setGeometry(40, 178, 300, 24);
        locationLabel->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "font-weight:bold;"
            "color:#00eaff;"
            "background:transparent;"
        );
        locationBox = new Box(40, 208, 1100, 38, " ", this);

        QLabel *crimeTypeLabel = new QLabel(" Crime Type  *", this);
        crimeTypeLabel->setGeometry(40, 262, 300, 24);
        crimeTypeLabel->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "font-weight:bold;"
            "color:#00eaff;"
            "background:transparent;"
        );
        typeBox = new Box(40, 292, 1100, 38, " ", this);

        QLabel *descriptionLabel = new QLabel(" Description", this);
        descriptionLabel->setGeometry(40, 346, 300, 24);
        descriptionLabel->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "font-weight:bold;"
            "color:#00eaff;"
            "background:transparent;"
        );
        descriptionBox = new DescriptionBox(40, 376, 1100, 100, "Detailed crime description...", this);

        QLabel *statusLabel = new QLabel("Status", this);
        statusLabel->setGeometry(40, 492, 1100, 24);
        statusLabel->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "font-weight:bold;"
            "color:#7ab8e0;"
            "background:transparent;"
        );

        ColoredButton *pendngButton = new ColoredButton("PENDING", 40,  526, 250, 48, "#ffcc44", this);
        QObject::connect(pendngButton, &QPushButton::clicked, [this]()
            {
                selectedStatus = "Pending";
                message->showNotice("Status selected: Pending");
            }
        );

        ColoredButton *solvedBtn = new ColoredButton("SOLVED", 475, 526, 250, 48, "#44ff99", this);
        QObject::connect(solvedBtn, &QPushButton::clicked, [this]()
            {
                selectedStatus = "Solved";
                message->showSuccess("Status selected: Solved");
            }
        );

        ColoredButton *coldBtn = new ColoredButton("COLD", 900, 526, 250, 48, "#ff6666", this);
        QObject::connect(coldBtn, &QPushButton::clicked, [this]()
            {
                selectedStatus = "Cold";
                message->showError("Status selected: Cold");
            }
        );

        message = new FeedbackLabel(40, 584, 1100, this);

        saveButton   = new Button("SAVE", 40, 620, 180, 44, this);
        deleteButton = new ClearButton("DELETE", 950, 620, 180, 44, this);

        QObject::connect(loadButton, &QPushButton::clicked, [this]()
        {
            QString caseIdentifier = caseIDBox->text().trimmed();

            if (caseIdentifier.isEmpty())
            {
                message->showError("Enter a Case ID.");
                return;
            }

            QStringList recordParts = FileHandler::loadRecord(caseIdentifier);

            if (recordParts.isEmpty())
            {
                message->showError("Case ID not found.");
                return;
            }

            locationBox->setText(recordParts.value(1));
            typeBox->setText(recordParts.value(2));
            descriptionBox->setText(recordParts.value(3));
            selectedStatus = recordParts.value(4, "Pending");
            message->showSuccess("Record loaded. Edit and press Save.");
        });

        QObject::connect(saveButton, &QPushButton::clicked, [this]()
        {
            QString caseIdentifier = caseIDBox->text().trimmed();
            QString crimeLocation = locationBox->text().trimmed();
            QString crimeType = typeBox->text().trimmed();
            QString crimeDescription = descriptionBox->toPlainText().trimmed();

            if (caseIdentifier.isEmpty() || crimeLocation.isEmpty() || crimeType.isEmpty())
            {
                message->showError("Load a record first.");
                return;
            }

            if (!FileHandler::caseIDExists(caseIdentifier))
            {
                message->showError("Case ID not found.");
                return;
            }

            FileHandler::updateRecord(caseIdentifier, crimeLocation, crimeType, crimeDescription, selectedStatus);
            message->showSuccess("Record updated successfully!");
        });

        QObject::connect(deleteButton, &QPushButton::clicked, [this]()
        {
            QString caseIdentifier = caseIDBox->text().trimmed();

            if (caseIdentifier.isEmpty())
            {
                message->showError("Load a record first.");
                return;
            }

            QMessageBox confirm;

            confirm.setWindowTitle("Confirm Delete");
            confirm.setText("Delete case " + caseIdentifier + "?");
            confirm.setInformativeText("This action cannot be undone.");
            confirm.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            confirm.setDefaultButton(QMessageBox::No);

            if (confirm.exec() != QMessageBox::Yes)
            {
                return;
            }

            if (FileHandler::deleteRecord(caseIdentifier))
            {
                message->showNotice("Record deleted.");
                reset();
            }
            else
            {
                message->showError("Case ID not found.");
            }
        });
    }

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

class CrimeRecordPage : public QWidget
{
private:

    QLabel *img;
    bool isAdminRole;
    Card *newRecordCard;
    QLabel *newRecordHeading;
    QLabel *createLine;
    QLabel *caseIDLabel;
    Box *caseIDBox;
    QLabel *locationLabel;
    Box *locationBox;
    QLabel *crimeTypeLabel;
    Box *typeBox;
    QLabel *descLabel;
    DescriptionBox *descriptionBox;
    QLabel *footNote;
    FeedbackLabel *feedback;
    Button *save;
    ClearButton *clear;
    QWidget *createPanelContainer;
    View *viewWidget;
    Search *searchWidget;
    Sort *sortWidget;
    Modify *modifyWidget;
    Button *recordButtons[5];

    void hideAllPanels()
    {
        createPanelContainer->hide();
        viewWidget->hide();
        searchWidget->hide();
        sortWidget->hide();
        modifyWidget->hide();
    }

public:
    CrimeRecordPage(bool isAdmin) : isAdminRole(isAdmin)
    {
        setWindowTitle("Crime Records - CRIME RECORD MANAGEMENT SYSTEM");

        img = UI::setupBackground(this, "backgroundThree.png");

        UI::setupSidebar(this, "[ CRIME RECORDS ]");
        UI::setupPageHeader(this, "CRIME RECORD MANAGEMENT", "Manage and track criminal data across the jurisdiction");
        UI::setupFooter(this);

        for (int i = 0; i < 5; i++)
        {
            recordButtons[i] = nullptr;
        }

        if (isAdmin)
        {
            recordButtons[0] = new Button("  Create New Record", 25, 155, 270, 40, this);
            recordButtons[1] = new Button("  View All Records", 25, 215, 270, 40, this);
            recordButtons[2] = new Button("  Search Records", 25, 275, 270, 40, this);
            recordButtons[3] = new Button("  Sort Records", 25, 335, 270, 40, this);
            recordButtons[4] = new Button("  Modify / Delete", 25, 395, 270, 40, this);

            BackButton *bb = new BackButton(25, 455, 270, 44, this);
            bb->raise();
            QObject::connect(bb, &QPushButton::clicked, [this]()
                {
                    this->close();
                }
            );
        }
        else
        {
            recordButtons[0] = new Button("  View All Records", 25, 155, 270, 40, this);
            recordButtons[1] = new Button("  Search Records", 25, 215, 270, 40, this);
            recordButtons[2] = new Button("  Sort Records", 25, 275, 270, 40, this);

            BackButton *bb = new BackButton(25, 335, 270, 44, this);
            bb->raise();
            QObject::connect(bb, &QPushButton::clicked, [this]() { this->close(); });
        }

        createPanelContainer = new QWidget(this);
        createPanelContainer->setGeometry(320, 0, 1280, 900);
        createPanelContainer->hide();

        new Card(80, 130, 710, 650, createPanelContainer);

        QLabel* createTitle = new QLabel("CREATE NEW CRIME RECORD", createPanelContainer);
        createTitle->setGeometry(100, 140, 670, 28);
        createTitle->setStyleSheet
        (
            MONO +
            "font-size:18px;"
            "font-weight:bold;"
            "color:#00eaff;"
            "background:transparent;"
        );
        QLabel* createLine = new QLabel(createPanelContainer);
        createLine->setGeometry(40, 52, 670, 1);
        createLine->setStyleSheet("background:rgba(0, 200, 255, 0.20);");


        QLabel* caseIDLabel = new QLabel(" Case ID  *", createPanelContainer);
        caseIDLabel->setGeometry(100, 180, 300, 24);
        caseIDLabel->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "font-weight:bold;"
            "color:#00eaff;"
            "background:transparent;"
        );

        QLabel* locationLabel = new QLabel(" Location  *", createPanelContainer);
        locationLabel->setGeometry(100, 280, 300, 24);
        locationLabel->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "font-weight:bold;"
            "color:#00eaff;"
            "background:transparent;"
        );

        QLabel* crimeTypeLabel = new QLabel(" Crime Type  *", createPanelContainer);
        crimeTypeLabel->setGeometry(100, 380, 300, 24);
        crimeTypeLabel->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "font-weight:bold;"
            "color:#00eaff;"
            "background:transparent;"
        );

        QLabel* descLabel = new QLabel(" Description", createPanelContainer);
        descLabel->setGeometry(100, 480, 300, 24);
        descLabel->setStyleSheet
        (
            MONO +
            "font-size:20px;"
            "font-weight:bold;"
            "color:#00eaff;"
            "background:transparent;"
        );

        caseIDBox = new Box(100, 220, 670, 38, "e.g. CR-001", createPanelContainer);
        locationBox = new Box(100, 320, 670, 38, "e.g. Islamabad", createPanelContainer);
        typeBox = new Box(100, 420, 670, 38, "e.g. Robbery", createPanelContainer);
        descriptionBox = new DescriptionBox(100, 520, 670, 100, "Detailed crime description...", createPanelContainer);

        footNote = new QLabel("  Status is automatically set to 'Pending'", createPanelContainer);
        footNote->setGeometry(260, 640, 670, 22);
        footNote->setStyleSheet
        (
            MONO +
            "font-size:15px;"
            "color:#ffcc44;"
            "background:transparent;"
        );

        feedback = new FeedbackLabel(180, 666, 670, createPanelContainer);
        save  = new Button("SAVE", 100, 700, 180, 44, createPanelContainer);
        clear = new ClearButton("CLEAR", 590, 700, 180, 44, createPanelContainer);

        viewWidget = new View(isAdmin, this);
        viewWidget->setGeometry(340, 110, 1200, 720);
        viewWidget->hide();

        searchWidget = new Search(isAdmin, this);
        searchWidget->setGeometry(340, 110, 1200, 760);
        searchWidget->hide();

        sortWidget = new Sort(isAdmin, this);
        sortWidget->setGeometry(340, 110, 1200, 760);
        sortWidget->hide();

        modifyWidget = new Modify(this);
        modifyWidget->setGeometry(340, 110, 1200, 720);
        modifyWidget->hide();

        if (isAdmin)
        {
            QObject::connect(recordButtons[0], &QPushButton::clicked, [this]()
                {
                    hideAllPanels();
                    createPanelContainer->show();
                }
            );
            QObject::connect(recordButtons[1], &QPushButton::clicked, [this]()
                {
                    hideAllPanels();
                    viewWidget->show();
                }
            );
            QObject::connect(recordButtons[2], &QPushButton::clicked, [this]()
                {
                    hideAllPanels();
                    searchWidget->show();
                }
            );
            QObject::connect(recordButtons[3], &QPushButton::clicked, [this]()
                {
                    hideAllPanels();
                    sortWidget->show();
                }
            );
            QObject::connect(recordButtons[4], &QPushButton::clicked, [this]()
                {
                    hideAllPanels();
                    modifyWidget->reset();
                    modifyWidget->show();
                }
            );
        }
        else
        {
            QObject::connect(recordButtons[0], &QPushButton::clicked, [this]()
            {
                hideAllPanels();
                viewWidget->show();
            });

            QObject::connect(recordButtons[1], &QPushButton::clicked, [this]()
            {
                hideAllPanels();
                searchWidget->show();
            });

            QObject::connect(recordButtons[2], &QPushButton::clicked, [this]()
            {
                hideAllPanels();
                sortWidget->show();
            });
        }

        QObject::connect(clear, &QPushButton::clicked, [this]()
        {
            caseIDBox->clear();
            locationBox->clear();
            typeBox->clear();
            descriptionBox->clear();
            feedback->setText("");
        });

        QObject::connect(save, &QPushButton::clicked, [this]()
            {
                QString caseIdentifier = caseIDBox->text().trimmed();
                QString crimeLocation = locationBox->text().trimmed();
                QString crimeType = typeBox->text().trimmed();
                QString crimeDescription = descriptionBox->toPlainText().trimmed();

                if (caseIdentifier.isEmpty() || crimeLocation.isEmpty() || crimeType.isEmpty())
                {
                    feedback->showError("Case ID, Location and Crime Type are required.");
                    return;
                }

                if (FileHandler::caseIDExists(caseIdentifier))
                {
                    feedback->showError("Case ID already exists. Use a different ID.");
                    return;
                }

                FileHandler::saveRecord(caseIdentifier, crimeLocation, crimeType, crimeDescription);

                feedback->showSuccess("Record saved successfully!");

                caseIDBox->clear();
                locationBox->clear();
                typeBox->clear();
                descriptionBox->clear();
            }
        );
    }

    void resizeEvent(QResizeEvent *) override
    {
        img->setGeometry(0, 0, width(), height());
    }
};

#endif