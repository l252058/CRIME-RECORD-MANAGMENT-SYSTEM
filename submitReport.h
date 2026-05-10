#ifndef SUBMITREPORT_H
#define SUBMITREPORT_H

// =============================================================================
//  submitReport.h
//  SubmitCaseReport — user fills in a report and submits it to the admin
//
//  File  : userreports.txt
//  Format: reportID \n userEmail \n caseRef \n subject \n body \n status \n adminComment \n --- \n
//          (8-line blocks)
//
//  Workflow:
//    1. User logs in and opens Submit Case Report
//    2. Fills in Case Reference, Subject, and Details
//    3. Report is saved with status = "Pending" and empty admin comment
//    4. Admin sees it in adminReports.h and can Approve / Reject with a comment
//    5. User sees updated status + comment in myReports.h
// =============================================================================

#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>
#include <QTextEdit>
#include <QWidget>
#include <QDateTime>
#include <utility>

#include "common.h"
#include "file.h"

// =============================================================================
//  UserReportFile — ALL disk I/O for user-submitted reports
//  (defined here so both submitReport.h and myReports.h / adminReports.h can
//   include just this one header — include guard prevents double-definition)
// =============================================================================

class UserReportFile
{
public:

    // -------------------------------------------------------------------------
    //  save — writes one new report with a unique ID; status = "Pending"
    //  reportID is generated from timestamp so it is always unique
    // -------------------------------------------------------------------------

    static QString save(const QString &userEmail,
                        const QString &caseRef,
                        const QString &subject,
                        const QString &body)
    {
        QFile file("userreports.txt");

        if (!file.open(QIODevice::Append | QIODevice::Text))
        {
            return "";
        }

        // Simple unique ID: RPT- + timestamp digits
        QString reportID = "RPT-" +
                           QDateTime::currentDateTime().toString("yyyyMMddhhmmss");

        QTextStream out(&file);

        out << reportID          << "\n"   // [0] report ID
            << userEmail.trimmed() << "\n" // [1] who submitted it
            << caseRef.trimmed() << "\n"   // [2] case reference
            << subject.trimmed() << "\n"   // [3] subject
            << body.trimmed()    << "\n"   // [4] body / details
            << "Pending"         << "\n"   // [5] status
            << ""                << "\n"   // [6] admin comment (empty at first)
            << "---"             << "\n";  // [7] block separator

        file.close();

        FileHandler::appendLog("USER",
                               "Submitted case report [" + reportID + "] re: " + caseRef + " — " + subject);

        return reportID;
    }

    // -------------------------------------------------------------------------
    //  loadAll — returns every report as
    //            { reportID, email, caseRef, subject, body, status, adminComment }
    // -------------------------------------------------------------------------

    static QList<QStringList> loadAll()
    {
        QList<QStringList> reports;

        QFile file("userreports.txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return reports;
        }

        QTextStream in(&file);

        while (!in.atEnd())
        {
            QString reportID     = in.readLine();
            QString email        = in.readLine();
            QString caseRef      = in.readLine();
            QString subject      = in.readLine();
            QString body         = in.readLine();
            QString status       = in.readLine();
            QString adminComment = in.readLine();
            QString sep          = in.readLine();

            if (sep.trimmed() == "---")
            {
                reports.append({ reportID, email, caseRef, subject,
                                body, status, adminComment });
            }
        }

        file.close();

        return reports;
    }

    // -------------------------------------------------------------------------
    //  loadByEmail — returns only reports submitted by the given user
    // -------------------------------------------------------------------------

    static QList<QStringList> loadByEmail(const QString &email)
    {
        const QList<QStringList> all = loadAll();
        QList<QStringList> result;

        for (const QStringList &r : all)
        {
            if (r.value(1).trimmed().toLower() == email.trimmed().toLower())
            {
                result.append(r);
            }
        }

        return result;
    }

    // -------------------------------------------------------------------------
    //  updateStatus — sets status and adminComment for a given reportID
    // -------------------------------------------------------------------------

    static bool updateStatus(const QString &reportID,
                             const QString &newStatus,
                             const QString &adminComment)
    {
        QList<QStringList> all = loadAll();

        bool found = false;

        for (QStringList &r : all)
        {
            if (r.value(0).trimmed() == reportID.trimmed())
            {
                r[5] = newStatus;
                r[6] = adminComment;
                found = true;
                break;
            }
        }

        if (!found)
        {
            return false;
        }

        // Re-write the entire file
        QFile file("userreports.txt");

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return false;
        }

        QTextStream out(&file);

        for (const QStringList &r : std::as_const(all))
        {
            out << r[0] << "\n"   // reportID
                << r[1] << "\n"   // email
                << r[2] << "\n"   // caseRef
                << r[3] << "\n"   // subject
                << r[4] << "\n"   // body
                << r[5] << "\n"   // status
                << r[6] << "\n"   // adminComment
                << "---" << "\n"; // separator
        }

        file.close();

        FileHandler::appendLog("ADMIN",
                               "Updated report [" + reportID + "] → " + newStatus);

        return true;
    }

    // -------------------------------------------------------------------------
    //  count — total number of reports (used by Reports analytics page)
    // -------------------------------------------------------------------------

    static int count()
    {
        return loadAll().size();
    }

    // -------------------------------------------------------------------------
    //  countByStatus — e.g. countByStatus("Pending"), ("Approved"), ("Rejected")
    // -------------------------------------------------------------------------

    static int countByStatus(const QString &status)
    {
        int n = 0;
        for (const QStringList &r : loadAll())
        {
            if (r.value(5).trimmed().toLower() == status.trimmed().toLower())
            {
                n++;
            }
        }
        return n;
    }
};

// =============================================================================
//  SubmitCaseReport — the page the user sees when they click "Submit Case Report"
// =============================================================================

class SubmitCaseReport : public QWidget
{
private:

    QLabel         *img;
    FeedbackLabel  *feedback;
    Box            *caseRefBox;
    Box            *subjectBox;
    DescriptionBox *bodyEdit;
    QPushButton    *submitBtn;
    QPushButton    *clearBtn;

    QString         loggedInEmail;

    void clearForm()
    {
        caseRefBox->clear();
        subjectBox->clear();
        bodyEdit->clear();
    }

public:

    explicit SubmitCaseReport(const QString &email) : QWidget(nullptr), loggedInEmail(email)
    {
        setWindowTitle("Submit Case Report — CRIME RECORD MANAGEMENT SYSTEM");

        img = UI::setupBackground(this, "backgroundThree.png");

        UI::setupSidebar(this, "[ REPORT ]");
        UI::setupPageHeader(this, "SUBMIT CASE REPORT", "Fill in the details below and submit your report to the administrator.");
        UI::setupFooter(this);

        BackButton *bb = new BackButton(25, 155, 270, 44, this);
        bb->raise();
        QObject::connect(bb, &QPushButton::clicked, [this]() { this->close(); });

        // ── Form Card ─────────────────────────────────────────────────────────

        new Card(380, 138, 800, 644, this);

        QLabel *emailLabel = new QLabel("  Submitting as", this);
        emailLabel->setGeometry(400, 158, 200, 20);
        emailLabel->setStyleSheet(MONO + "font-size:14px; font-weight:bold; color:#7ab8e0; background:transparent;");

        QLabel *emailDisplay = new QLabel(loggedInEmail, this);
        emailDisplay->setGeometry(400, 178, 760, 22);
        emailDisplay->setStyleSheet(MONO + "font-size:18px; font-weight:bold; color:#ffcc44; background:transparent;");

        QLabel *caseRefLabel = new QLabel("  Case Reference  *", this);
        caseRefLabel->setGeometry(400, 218, 760, 24);
        caseRefLabel->setStyleSheet(MONO + "font-size:20px; font-weight:bold; color:#00eaff; background:transparent;");

        caseRefBox = new Box(400, 248, 760, 38, "e.g. CR-001", this);

        QLabel *subjectLabel = new QLabel("  Subject  *", this);
        subjectLabel->setGeometry(400, 306, 760, 24);
        subjectLabel->setStyleSheet(MONO + "font-size:20px; font-weight:bold; color:#00eaff; background:transparent;");

        subjectBox = new Box(400, 336, 760, 38, "Brief subject of your report", this);

        QLabel *bodyLabel = new QLabel("  Report Details  *", this);
        bodyLabel->setGeometry(400, 394, 760, 24);
        bodyLabel->setStyleSheet(MONO + "font-size:20px; font-weight:bold; color:#00eaff; background:transparent;");

        bodyEdit   = new DescriptionBox(400, 424, 760, 200, "Describe the incident or issue in detail...", this);

        feedback  = new FeedbackLabel(400, 642, 760, this);
        submitBtn = new Button("SUBMIT", 400, 672, 180, 44, this);
        clearBtn  = new ClearButton("CLEAR", 600, 672, 180, 44, this);

        connect(clearBtn, &QPushButton::clicked, this, &SubmitCaseReport::clearForm);

        connect(submitBtn, &QPushButton::clicked, this, [this]()
                {
                    QString caseRef = caseRefBox->text().trimmed();
                    QString subject = subjectBox->text().trimmed();
                    QString body    = bodyEdit->toPlainText().trimmed();

                    if (caseRef.isEmpty() || subject.isEmpty() || body.isEmpty())
                    {
                        feedback->showError("All marked fields (*) are required.");
                        return;
                    }

                    QString reportID = UserReportFile::save(loggedInEmail, caseRef, subject, body);

                    if (reportID.isEmpty())
                    {
                        feedback->showError("Failed to save report. Disk error.");
                    }
                    else
                    {
                        feedback->showSuccess("Report [" + reportID + "] submitted successfully!");
                        clearForm();
                    }
                });
    }

    void setEmail(const QString &email) { loggedInEmail = email; }

    void resizeEvent(QResizeEvent *) override
    {
        img->resize(size());
    }
};

#endif // SUBMITREPORT_H