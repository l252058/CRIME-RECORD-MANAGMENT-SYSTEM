#ifndef LOGS_H
#define LOGS_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QStringList>
#include <QMessageBox>

#include "common.h"
#include "file.h"


class ActivityLogs : public QWidget
{
private:

    // ── Constants ─────────────────────────────────────────────────────────────

    static const int sidebarButtonX      = 25;
    static const int sidebarButtonWidth  = 270;
    static const int sidebarButtonHeight = 40;

    // ── Members ───────────────────────────────────────────────────────────────

    QLabel      * backgroundImage;
    StatCard    * totalCountLabel;
    StatCard    * adminCountLabel;
    StatCard    * userCountLabel;
    QWidget     * scrollContentWidget;
    QVBoxLayout * scrollContentLayout;

    // =========================================================================
    //  Widget Builder Helpers
    // =========================================================================

    // ── Build a Single Log Row ────────────────────────────────────────────────

    QWidget * makeLogRow
        (
            const QString & category,
            const QString & timestamp,
            const QString & action,
            const QString & badgeColor
            )
    {
        QWidget * rowWidget = new QWidget();
        rowWidget->setFixedHeight(46);
        rowWidget->setStyleSheet
            (
                "background    : rgba(0, 15, 45, 0.70);"
                "border-bottom : 1px solid rgba(0, 200, 255, 0.10);"
                "border-radius : 4px;"
                );

        QLabel * categoryBadge = new QLabel(category, rowWidget);
        categoryBadge->setGeometry(12, 10, 80, 26);
        categoryBadge->setAlignment(Qt::AlignCenter);
        categoryBadge->setStyleSheet
            (
                MONO +
                "font-size     : 14px;"
                "font-weight   : bold;"
                "color         : #000000;"
                "background    : " + badgeColor + ";"
                               "border-radius : 4px;"
                );

        QLabel * timestampLabel = new QLabel(timestamp, rowWidget);
        timestampLabel->setGeometry(104, 0, 220, 46);
        timestampLabel->setStyleSheet
            (
                MONO +
                "font-size  : 14px;"
                "font-weight: bold;"
                "color      : #7ab8e0;"
                "background : transparent;"
                );

        QLabel * actionLabel = new QLabel(action, rowWidget);
        actionLabel->setGeometry(334, 0, 820, 46);
        actionLabel->setStyleSheet
            (
                MONO +
                "font-size  : 16px;"
                "font-weight: bold;"
                "color      : #c0dff5;"
                "background : transparent;"
                );

        return rowWidget;
    }

    // ── Build a Section Header ────────────────────────────────────────────────

    QLabel * makeSectionHeader(const QString & text, const QString & color)
    {
        QLabel * headerLabel = new QLabel(text);
        headerLabel->setFixedHeight(36);
        headerLabel->setStyleSheet
            (
                MONO +
                "font-size      : 16px;"
                "font-weight    : bold;"
                "letter-spacing : 4px;"
                "color          : " + color + ";"
                          "background     : rgba(0, 30, 70, 0.80);"
                          "border-left    : 3px solid " + color + ";"
                          "padding-left   : 14px;"
                          "border-radius  : 4px;"
                );

        return headerLabel;
    }

    // ── Build a Thin Spacer ───────────────────────────────────────────────────

    QLabel * makeDivider()
    {
        QLabel * dividerLabel = new QLabel();
        dividerLabel->setFixedHeight(10);
        dividerLabel->setStyleSheet("background : transparent;");
        return dividerLabel;
    }

    // ── Build an Empty-State Row ──────────────────────────────────────────────

    QWidget * makeEmptyRow(const QString & message)
    {
        QWidget * emptyRowWidget = new QWidget();
        emptyRowWidget->setFixedHeight(42);
        emptyRowWidget->setStyleSheet
            (
                "background    : rgba(0, 15, 45, 0.50);"
                "border-radius : 4px;"
                );

        QLabel * messageLabel = new QLabel(message, emptyRowWidget);
        messageLabel->setGeometry(16, 0, 1100, 42);
        messageLabel->setStyleSheet
            (
                MONO +
                "font-size  : 16px;"
                "font-weight: bold;"
                "color      : #7ab8e0;"
                "background : transparent;"
                );

        return emptyRowWidget;
    }

    // ── Build a Stat Card and Return Its Count Label ──────────────────────────


    // ── Build a Sidebar Legend Label ──────────────────────────────────────────

    void buildLegend(const QString & text, const QString & color, int y)
    {
        QLabel * legendLabel = new QLabel(text, this);
        legendLabel->setGeometry(30, y, 270, 22);
        legendLabel->setStyleSheet
            (
                MONO +
                QString
                (
                    "font-size      : 18px;"
                    "letter-spacing : 4px;"
                    "font-weight    : bold;"
                    "color          : %1;"
                    "background     : transparent;"
                    ).arg(color)
                );
    }

    // =========================================================================
    //  Core Logic — Read Logs From Disk and Populate the Scroll Area
    // =========================================================================

    void clearScrollArea()
    {
        QLayoutItem * layoutItem = scrollContentLayout->takeAt(0);

        while (layoutItem != nullptr)
        {
            if (layoutItem->widget() != nullptr)
            {
                layoutItem->widget()->deleteLater();
            }

            delete layoutItem;

            layoutItem = scrollContentLayout->takeAt(0);
        }
    }

    void populateFromFile()
    {
        clearScrollArea();

        const QStringList allLines = FileHandler::loadLogs();

        QStringList adminLines;
        QStringList userLines;
        QStringList systemLines;

        for (const QString & rawLine : allLines)
        {
            // Expected format: "CATEGORY|TIMESTAMP|ACTION"
            QStringList parts = rawLine.split("\t");

            if (parts.size() < 3)
            {
                continue;
            }

            QString category = parts[0].trimmed().toUpper();

            if (category == "ADMIN")
            {
                adminLines.append(rawLine);
            }
            else if (category == "USER")
            {
                userLines.append(rawLine);
            }
            else
            {
                systemLines.append(rawLine);
            }
        }

        // Update stat cards with real counts
        totalCountLabel->setValue(adminLines.size() + userLines.size() + systemLines.size());
        adminCountLabel->setValue(adminLines.size());
        userCountLabel->setValue(userLines.size());

        // ── Admin Section ─────────────────────────────────────────────────────

        scrollContentLayout->addWidget(makeSectionHeader("  ADMIN  ACTIONS", "#ffcc44"));

        if (adminLines.isEmpty())
        {
            scrollContentLayout->addWidget(makeEmptyRow("  No admin actions logged yet."));
        }
        else
        {
            for (const QString & rawLine : adminLines)
            {
                QStringList parts     = rawLine.split("\t");
                QString     timestamp = parts.size() > 1 ? parts[1].trimmed() : "—";
                QString     action    = parts.size() > 2 ? parts[2].trimmed() : "—";

                scrollContentLayout->addWidget(makeLogRow("ADMIN", timestamp, action, "#ffcc44"));
            }
        }

        scrollContentLayout->addWidget(makeDivider());

        // ── User Section ──────────────────────────────────────────────────────

        scrollContentLayout->addWidget(makeSectionHeader("  USER  ACTIONS", "#00eaff"));

        if (userLines.isEmpty())
        {
            scrollContentLayout->addWidget(makeEmptyRow("  No user actions logged yet."));
        }
        else
        {
            for (const QString & rawLine : userLines)
            {
                QStringList parts     = rawLine.split("\t");
                QString     timestamp = parts.size() > 1 ? parts[1].trimmed() : "—";
                QString     action    = parts.size() > 2 ? parts[2].trimmed() : "—";

                scrollContentLayout->addWidget(makeLogRow("USER", timestamp, action, "#00eaff"));
            }
        }

        scrollContentLayout->addWidget(makeDivider());

        // ── System Section ────────────────────────────────────────────────────

        scrollContentLayout->addWidget(makeSectionHeader("  SYSTEM  EVENTS", "#ff6666"));

        if (systemLines.isEmpty())
        {
            scrollContentLayout->addWidget(makeEmptyRow("  No system events logged yet."));
        }
        else
        {
            for (const QString & rawLine : systemLines)
            {
                QStringList parts     = rawLine.split("\t");
                QString     timestamp = parts.size() > 1 ? parts[1].trimmed() : "—";
                QString     action    = parts.size() > 2 ? parts[2].trimmed() : "—";

                scrollContentLayout->addWidget(makeLogRow("SYS", timestamp, action, "#ff6666"));
            }
        }

        scrollContentLayout->addStretch();
    }

public:

    ActivityLogs() : QWidget(nullptr)
    {
        setWindowTitle("Activity Logs — CRIME RECORD MANAGEMENT SYSTEM");

        // ── Background ────────────────────────────────────────────────────────

        backgroundImage = UI::setupBackground(this, "backgroundThree.png");

        // ── Sidebar Card ──────────────────────────────────────────────────────

        new Card(0, 0, 320, 900, this);

        QLabel * sidebarTitle = new QLabel("CRIME RECORD\nMANAGEMENT\nSYSTEM", this);
        sidebarTitle->setGeometry(10, 10, 300, 120);
        sidebarTitle->setAlignment(Qt::AlignCenter);
        sidebarTitle->setWordWrap(true);
        sidebarTitle->setStyleSheet
            (
                MONO +
                "font-size      : 20px;"
                "font-weight    : bold;"
                "letter-spacing : 1px;"
                "color          : #00eaff;"
                "background     : transparent;"
                );

        QLabel * dividerOne = new QLabel(this);
        dividerOne->setGeometry(30, 100, 260, 1);
        dividerOne->setStyleSheet("background : rgba(0, 200, 255, 0.30);");

        QLabel * accessTag = new QLabel("[ ACTIVITY  LOGS ]", this);
        accessTag->setGeometry(0, 110, 320, 30);
        accessTag->setAlignment(Qt::AlignCenter);
        accessTag->setStyleSheet(MONO + "font-size:20px; letter-spacing:4px; color:#ffcc44; background:transparent; font-weight:bold;");

        // ── Sidebar Legends ───────────────────────────────────────────────────
        auto buildLegend = [&](const QString & text, const QString & color, int y) {
            QLabel * legend = new QLabel(text, this);
            legend->setGeometry(30, y, 270, 24);
            legend->setStyleSheet(MONO + QString("font-size:20px; letter-spacing:4px; color:%1; background:transparent; font-weight:bold;").arg(color));
        };
        buildLegend("ADMIN  ACTION", "#ffcc44", 172);
        buildLegend("USER   ACTION", "#00eaff", 200);
        buildLegend("SYSTEM EVENT",  "#ff6666", 228);

        QLabel * dividerTwo = new QLabel(this);
        dividerTwo->setGeometry(30, 264, 260, 1);
        dividerTwo->setStyleSheet("background : rgba(0, 200, 255, 0.20);");

        // ── Sidebar Buttons ───────────────────────────────────────────────────
        Button * refreshButton = new Button("Refresh Logs", sidebarButtonX, 300, sidebarButtonWidth, sidebarButtonHeight, this);
        ClearButton * clearButton = new ClearButton("Clear Logs", sidebarButtonX, 360, sidebarButtonWidth, sidebarButtonHeight, this);
        BackButton *bb = new BackButton(sidebarButtonX, 420, sidebarButtonWidth, sidebarButtonHeight, this);
        bb->raise();

        QObject::connect(bb, &QPushButton::clicked, [this]() { this->close(); });

        // ── Page Heading ──────────────────────────────────────────────────────

        QLabel * pageTitle = new QLabel("ACTIVITY  LOGS", this);
        pageTitle->setGeometry(380, 40, 1180, 50);
        pageTitle->setStyleSheet
            (
                MONO +
                "font-size      : 40px;"
                "font-weight    : 900;"
                "letter-spacing : 6px;"
                "color          : #ffffff;"
                "background     : transparent;"
                );

        QLabel * pageSubtitle = new QLabel("Complete audit trail of all admin and user actions", this);
        pageSubtitle->setGeometry(380, 95, 1180, 22);
        pageSubtitle->setStyleSheet
            (
                MONO +
                "font-size   : 18px;"
                "font-weight : bold;"
                "color       : #ffcc44;"
                "background  : transparent;"
                );

        QLabel * headerDivider = new QLabel(this);
        headerDivider->setGeometry(380, 125, 1180, 1);
        headerDivider->setStyleSheet("background : rgba(0, 200, 255, 0.25);");

        // ── Stat Cards ────────────────────────────────────────────────────────

        totalCountLabel = new StatCard(380,  140, "#00eaff", "TOTAL  LOGS",     this);
        adminCountLabel = new StatCard(850,  140, "#ffcc44", "ADMIN  ACTIONS",  this);
        userCountLabel  = new StatCard(1300, 140, "#44ff99", "USER  ACTIONS",   this);

        // ── Log Entries Heading ───────────────────────────────────────────────

        QLabel * logEntriesHeading = new QLabel("LOG  ENTRIES", this);
        logEntriesHeading->setGeometry(380, 252, 800, 28);
        logEntriesHeading->setStyleSheet
            (
                MONO +
                "font-size   : 18px;"
                "font-weight : bold;"
                "color       : #00eaff;"
                "background  : transparent;"
                );

        // ── Footer ────────────────────────────────────────────────────────────

        QLabel * footerLabel = new QLabel("DEPARTMENT OF CRIMINAL JUSTICE    |    INTERNAL USE ONLY", this);
        footerLabel->setGeometry(0, 872, 1600, 18);
        footerLabel->setAlignment(Qt::AlignCenter);
        footerLabel->setStyleSheet
            (
                MONO +
                "font-size      : 14px;"
                "letter-spacing : 4px;"
                "color          : #7ab8e0;"
                "background     : transparent;"
                "font-weight    : bold;"
                );

        // ── Scroll Area ───────────────────────────────────────────────────────

        QScrollArea * logScrollArea = new QScrollArea(this);
        logScrollArea->setGeometry(380, 288, 1150, 480);
        logScrollArea->setWidgetResizable(true);
        logScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        logScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        logScrollArea->setStyleSheet
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

        scrollContentWidget = new QWidget();
        scrollContentWidget->setStyleSheet("background : transparent;");

        scrollContentLayout = new QVBoxLayout(scrollContentWidget);
        scrollContentLayout->setContentsMargins(12, 12, 12, 12);
        scrollContentLayout->setSpacing(3);

        // Default placeholder until user clicks Refresh
        scrollContentLayout->addWidget(makeSectionHeader("  ALL  ENTRIES", "#00eaff"));
        scrollContentLayout->addWidget(makeEmptyRow("  Click  Refresh Logs  to load the activity log."));
        scrollContentLayout->addStretch();

        logScrollArea->setWidget(scrollContentWidget);

        // ── Refresh Button Connection ─────────────────────────────────────────

        QObject::connect(refreshButton, &QPushButton::clicked, [this]()
                         {
                             populateFromFile();
                         });

        // ── Clear Button Connection ───────────────────────────────────────────

        QObject::connect(clearButton, &QPushButton::clicked, [this]()
                         {
                             QMessageBox::StandardButton reply = QMessageBox::question
                                 (
                                     this,
                                     "Clear Logs",
                                     "Are you sure you want to permanently clear all activity logs?",
                                     QMessageBox::Yes | QMessageBox::No
                                     );

                             if (reply == QMessageBox::No)
                             {
                                 return;
                             }

                             FileHandler::clearLogs();

                             totalCountLabel->setText("0");
                             adminCountLabel->setText("0");
                             userCountLabel->setText("0");

                             clearScrollArea();

                             scrollContentLayout->addWidget(makeSectionHeader("  ALL  ENTRIES", "#00eaff"));
                             scrollContentLayout->addWidget(makeEmptyRow("  Logs cleared successfully."));
                             scrollContentLayout->addStretch();
                         });
    }

    // ── Keep Background Scaled to Window Size ─────────────────────────────────

    void resizeEvent(QResizeEvent * event) override
    {
        backgroundImage->resize(event->size());
    }
};

#endif // LOGS_H