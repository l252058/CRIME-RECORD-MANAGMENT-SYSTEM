#ifndef FILE_H
#define FILE_H

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>


class FileHandler
{
public:

    // =====================================================
    //  SAVE ONE NEW RECORD  (appends to file)
    //  Format:  caseID|location|type|description|status
    // =====================================================

    static void saveRecord(QString caseID,
                           QString location,
                           QString type,
                           QString description)
    {
        QFile file("crimes.txt");

        if (!file.open(QIODevice::Append | QIODevice::Text))
            return;

        QTextStream out(&file);

        out << caseID      << "|"
            << location    << "|"
            << type        << "|"
            << description << "|"
            << "Pending"   << "\n";

        file.close();
    }


    // =====================================================
    //  LOAD ALL RECORDS  (returns raw pipe-separated lines)
    // =====================================================

    static QStringList loadRecords()
    {
        QStringList records;

        QFile file("crimes.txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return records;

        QTextStream in(&file);

        while (!in.atEnd())
        {
            QString line = in.readLine();

            if (!line.isEmpty())
                records.append(line);
        }

        file.close();
        return records;
    }


    // =====================================================
    //  SAVE ALL RECORDS  (overwrites entire file)
    //  Used by Modify (save changes) and Delete
    // =====================================================

    static void saveAll(QStringList records)
    {
        QFile file("crimes.txt");

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&file);

        for (int i = 0; i < records.size(); i++)
            out << records[i] << "\n";

        file.close();
    }


    // =====================================================
    //  CHECK IF CASE ID ALREADY EXISTS
    //  Used by New (save) to prevent duplicates
    // =====================================================

    static bool caseIDExists(QString id)
    {
        QStringList records = loadRecords();

        for (int i = 0; i < records.size(); i++)
        {
            QStringList parts = records[i].split("|");

            if (parts.size() >= 1 && parts[0] == id)
                return true;
        }

        return false;
    }


    // =====================================================
    //  LOGIN  (reads from users.txt)
    //  Format per user:  name / email / password / ---
    // =====================================================

    static bool loginUser(QString email, QString password)
    {
        QFile file("users.txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;

        QTextStream in(&file);

        while (!in.atEnd())
        {
            QString name         = in.readLine();
            QString fileEmail    = in.readLine();
            QString filePassword = in.readLine();
            QString separator    = in.readLine();

            if (fileEmail == email && filePassword == password)
            {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }
};


#endif // FILE_H