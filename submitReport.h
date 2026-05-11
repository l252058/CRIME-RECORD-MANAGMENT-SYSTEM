#ifndef SUBMITREPORT_H
#define SUBMITREPORT_H

#include <QDateTime>
#include "common.h"
#include "file.h"


class UserReportFile
{
public:
    static QString save(const QString & userEmail, const QString & caseReference, const QString & reportSubject, const QString & reportBody)
    {
        QFile file("userreports.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text))
        {
            return "";
        }

        QString reportId  = "RPT-" + QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
        QString cleanBody = reportBody.trimmed();
        cleanBody.replace("\n", " ").replace("\t", " ");

        QStringList fields;
        fields << reportId
               << userEmail.trimmed()
               << caseReference.trimmed()
               << reportSubject.trimmed().replace("\t", " ")
               << cleanBody
               << "Pending"
               << "";

        QTextStream out(&file);
        out << fields.join("\t") << "\n";

        file.close();
        return reportId;
    }

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
            QString line = in.readLine();
            if (!line.trimmed().isEmpty())
            {
                reports.append(line.split("\t"));
            }
        }

        file.close();
        return reports;
    }

    static QList<QStringList> loadByEmail(const QString & email)
    {
        const QList<QStringList> allReports = loadAll();
        QList<QStringList> userReports;

        for (const QStringList & report : allReports)
        {
            if (report.size() > 1 && report.value(1).trimmed().toLower() == email.trimmed().toLower())
            {
                userReports.append(report);
            }
        }

        return userReports;
    }

    static bool updateStatus(const QString & reportId, const QString & newStatus, const QString & adminComment)
    {
        QList<QStringList> allReports = loadAll();
        bool isFound = false;

        for (QStringList & report : allReports)
        {
            if (report.size() >= 6 && report.value(0).trimmed() == reportId.trimmed())
            {
                // Ensure we have 7 columns (index 0 to 6)
                while (report.size() < 7)
                {
                    report.append("");
                }
                report[5] = newStatus;
                report[6] = adminComment.trimmed().replace("\n", " ").replace("\t", " ");
                isFound   = true;
                break;
            }
        }

        if (!isFound)
        {
            return false;
        }

        QFile file("userreports.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return false;
        }

        QTextStream out(&file);
        for (const QStringList & r : allReports)
        {
            out << r.join("\t") << "\n";
        }

        file.close();
        return true;
    }

    static int countByStatus(const QString & status)
    {
        int total = 0;
        for (const QStringList & report : loadAll())
        {
            if (report.size() > 5 && report.value(5).trimmed().toLower() == status.trimmed().toLower())
            {
                total++;
            }
        }
        return total;
    }
};

class SubmitCaseReport : public QWidget
{
private:
    QLabel * pageBackground;
    FeedbackLabel  * actionFeedback;
    Box * caseReferenceBox;
    Box * subjectBox;
    DescriptionBox * detailsEdit;
    Button * submitButton;
    ClearButton  * clearButton;
    QString loggedInEmail;

    void resetForm()
    {
        caseReferenceBox->clear();
        subjectBox->clear();
        detailsEdit->clear();
        actionFeedback->setText("");
    }

public:
    explicit SubmitCaseReport(const QString & email) : QWidget(nullptr), loggedInEmail(email)
    {
        setWindowTitle("Submit Case Report — CRIME RECORD MANAGEMENT SYSTEM");

        pageBackground = new Background(this, "backgroundThree.png");

        new Sidebar(this, "[ REPORT ]");
        new PageHeader(this, "SUBMIT CASE REPORT", "Provide the incident details below to alert the administrator.");
        new Footer(this);

        BackButton * backNavigation = new BackButton(25, 155, 270, 44, this);
        backNavigation->raise();
        connect(backNavigation, &QPushButton::clicked, this, &QWidget::close);

        new Card(380, 138, 800, 644, this);

        QLabel * emailHint = new QLabel("  Submitting as", this);
        emailHint->setGeometry(400, 158, 200, 20);
        emailHint->setStyleSheet
        (
            MONO +
            "font-size   : 14px; "
            "font-weight : bold; "
            "color       : #7ab8e0; "
            "background  : transparent;"
        );

        QLabel * emailDisplay = new QLabel(loggedInEmail, this);
        emailDisplay->setGeometry(400, 178, 760, 22);
        emailDisplay->setStyleSheet
        (
            MONO +
            "font-size   : 18px; "
            "font-weight : bold; "
            "color       : #ffcc44; "
            "background  : transparent;"
        );

        QLabel * caseRefLabel = new QLabel("  Case Reference  *", this);
        caseRefLabel->setGeometry(400, 218, 760, 24);
        caseRefLabel->setStyleSheet
        (
            MONO +
            "font-size   : 20px; "
            "font-weight : bold; "
            "color       : #00eaff; "
            "background  : transparent;"
        );

        caseReferenceBox = new Box(400, 248, 760, 38, "e.g. CR-001", this);

        QLabel * subjectLabel = new QLabel("  Subject  *", this);
        subjectLabel->setGeometry(400, 306, 760, 24);
        subjectLabel->setStyleSheet
        (
            MONO +
            "font-size   : 20px; "
            "font-weight : bold; "
            "color       : #00eaff; "
            "background  : transparent;"
        );

        subjectBox = new Box(400, 336, 760, 38, "Brief summary of the incident", this);

        QLabel * bodyLabel = new QLabel("  Report Details  *", this);
        bodyLabel->setGeometry(400, 394, 760, 24);
        bodyLabel->setStyleSheet
        (
            MONO +
            "font-size   : 20px; "
            "font-weight : bold; "
            "color       : #00eaff; "
            "background  : transparent;"
        );

        detailsEdit = new DescriptionBox(400, 424, 760, 200, "Provide full details here...", this);
        actionFeedback = new FeedbackLabel(400, 642, 760, this);
        submitButton = new Button("SUBMIT", 400, 672, 180, 44, this);
        clearButton = new ClearButton("CLEAR", 970, 672, 180, 44, this);

        connect(clearButton, &QPushButton::clicked, this, &SubmitCaseReport::resetForm);

        connect(submitButton, &QPushButton::clicked, this, [this]()
            {
                QString caseReference = caseReferenceBox->text().trimmed();
                QString reportSubject = subjectBox->text().trimmed();
                QString reportBody    = detailsEdit->toPlainText().trimmed();

                if (caseReference.isEmpty() || reportSubject.isEmpty() || reportBody.isEmpty())
                {
                    actionFeedback->showError("Required fields (*) cannot be empty.");
                    return;
                }

                QString reportId = UserReportFile::save(loggedInEmail, caseReference, reportSubject, reportBody);

                if (reportId.isEmpty())
                {
                    actionFeedback->showError("System error: Failed to save report.");
                }
                else
                {
                    actionFeedback->showSuccess("Report [" + reportId + "] submitted successfully!");
                    caseReferenceBox->clear();
                    subjectBox->clear();
                    detailsEdit->clear();
                }
            }
        );
    }

    void resizeEvent(QResizeEvent *) override
    {
        pageBackground->resize(size());
    }
};

#endif