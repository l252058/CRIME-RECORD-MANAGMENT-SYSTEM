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
    //  CRIME RECORDS  (crimes.txt)
    //  Format: caseID|location|type|description|status
    // =====================================================

    static void saveRecord(QString caseID, QString location,
                           QString type,   QString description)
    {
        QFile file("crimes.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text)) return;
        QTextStream out(&file);
        out << caseID << "|" << location << "|" << type
            << "|" << description << "|" << "Pending" << "\n";
        file.close();
    }

    static QStringList loadRecords()
    {
        QStringList records;
        QFile file("crimes.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return records;
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (!line.isEmpty()) records.append(line);
        }
        file.close();
        return records;
    }

    static void saveAll(QStringList records)
    {
        QFile file("crimes.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
        QTextStream out(&file);
        for (const QString &r : records) out << r << "\n";
        file.close();
    }

    static bool caseIDExists(QString id)
    {
        for (const QString &line : loadRecords()) {
            QStringList p = line.split("|");
            if (p.size() >= 1 && p[0] == id) return true;
        }
        return false;
    }

    static bool updateRecord(QString id, QString location,
                             QString type, QString description, QString status)
    {
        QStringList records = loadRecords();
        bool found = false;
        for (QString &line : records) {
            QStringList p = line.split("|");
            if (p.size() >= 5 && p[0] == id) {
                p[1] = location; p[2] = type;
                p[3] = description; p[4] = status;
                line  = p.join("|");
                found = true;
                break;
            }
        }
        if (found) saveAll(records);
        return found;
    }

    static bool deleteRecord(QString id)
    {
        QStringList records = loadRecords();
        int before = records.size();
        for (int i = records.size() - 1; i >= 0; i--) {
            QStringList p = records[i].split("|");
            if (p.size() >= 1 && p[0] == id) records.removeAt(i);
        }
        if (records.size() < before) { saveAll(records); return true; }
        return false;
    }

    static QStringList loadRecord(QString id)
    {
        for (const QString &line : loadRecords()) {
            QStringList p = line.split("|");
            if (p.size() >= 1 && p[0] == id) return p;
        }
        return QStringList();
    }

    static bool updateStatus(QString id, QString newStatus)
    {
        QStringList records = loadRecords();
        bool found = false;
        for (QString &line : records) {
            QStringList p = line.split("|");
            if (p.size() >= 5 && p[0] == id) {
                p[4] = newStatus;
                line  = p.join("|");
                found = true;
                break;
            }
        }
        if (found) saveAll(records);
        return found;
    }

    // =====================================================
    //  OFFICER RECORDS  (officers.txt)
    //  Format: officerID|name|rank|badge
    // =====================================================

    static void saveOfficer(QString id, QString name, QString rank, QString badge)
    {
        QFile file("officers.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text)) return;
        QTextStream out(&file);
        out << id << "|" << name << "|" << rank << "|" << badge << "\n";
        file.close();
    }

    static QStringList loadOfficers()
    {
        QStringList records;
        QFile file("officers.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return records;
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (!line.isEmpty()) records.append(line);
        }
        file.close();
        return records;
    }

    static void saveAllOfficers(QStringList records)
    {
        QFile file("officers.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
        QTextStream out(&file);
        for (const QString &r : records) out << r << "\n";
        file.close();
    }

    static bool officerIDExists(QString id)
    {
        for (const QString &line : loadOfficers()) {
            QStringList p = line.split("|");
            if (p.size() >= 1 && p[0] == id) return true;
        }
        return false;
    }

    static bool updateOfficer(QString id, QString name, QString rank, QString badge)
    {
        QStringList records = loadOfficers();
        bool found = false;
        for (QString &line : records) {
            QStringList p = line.split("|");
            if (p.size() >= 4 && p[0] == id) {
                p[1] = name; p[2] = rank; p[3] = badge;
                line  = p.join("|");
                found = true;
                break;
            }
        }
        if (found) saveAllOfficers(records);
        return found;
    }

    static bool deleteOfficer(QString id)
    {
        QStringList records = loadOfficers();
        int before = records.size();
        for (int i = records.size() - 1; i >= 0; i--) {
            QStringList p = records[i].split("|");
            if (p.size() >= 1 && p[0] == id) records.removeAt(i);
        }
        if (records.size() < before) { saveAllOfficers(records); return true; }
        return false;
    }

    // =====================================================
    //  COURT PROCEEDINGS  (court.txt)
    //  Format: caseID|accused|crimeType|status
    // =====================================================

    static void saveCourt(QString caseID, QString accused, QString crimeType)
    {
        QFile file("court.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text)) return;
        QTextStream out(&file);
        out << caseID << "|" << accused << "|" << crimeType << "|" << "Ongoing" << "\n";
        file.close();
    }

    static QStringList loadCourt()
    {
        QStringList records;
        QFile file("court.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return records;
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (!line.isEmpty()) records.append(line);
        }
        file.close();
        return records;
    }

    static void saveAllCourt(QStringList records)
    {
        QFile file("court.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
        QTextStream out(&file);
        for (const QString &r : records) out << r << "\n";
        file.close();
    }

    static bool courtCaseExists(QString id)
    {
        for (const QString &line : loadCourt()) {
            QStringList p = line.split("|");
            if (p.size() >= 1 && p[0] == id) return true;
        }
        return false;
    }

    static bool updateCourtStatus(QString id, QString newStatus)
    {
        QStringList records = loadCourt();
        bool found = false;
        for (QString &line : records) {
            QStringList p = line.split("|");
            if (p.size() >= 4 && p[0] == id) {
                p[3] = newStatus;
                line  = p.join("|");
                found = true;
                break;
            }
        }
        if (found) saveAllCourt(records);
        return found;
    }

    // =====================================================
    //  USER ACCOUNTS  (users.txt)
    //  Format per user:  name\nemail\npassword\n---\n
    // =====================================================

    // FIX: Actually saves the new user to users.txt
    static bool saveUser(QString name, QString email, QString password)
    {
        if (emailExists(email)) return false;   // prevent duplicate

        QFile file("users.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text)) return false;
        QTextStream out(&file);
        out << name     << "\n"
            << email    << "\n"
            << password << "\n"
            << "---"    << "\n";
        file.close();
        return true;
    }

    static bool emailExists(QString email)
    {
        QFile file("users.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
        QTextStream in(&file);
        while (!in.atEnd()) {
            in.readLine();                       // name
            QString fileEmail = in.readLine();
            in.readLine();                       // password
            in.readLine();                       // ---
            if (fileEmail == email) { file.close(); return true; }
        }
        file.close();
        return false;
    }

    // FIX: Validates credentials from users.txt
    static bool loginUser(QString email, QString password)
    {
        QFile file("users.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
        QTextStream in(&file);
        while (!in.atEnd()) {
            in.readLine();                           // name
            QString fileEmail    = in.readLine();
            QString filePassword = in.readLine();
            in.readLine();                           // ---
            if (fileEmail == email && filePassword == password) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    static QString getUserName(QString email)
    {
        QFile file("users.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return "";
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString name      = in.readLine();
            QString fileEmail = in.readLine();
            in.readLine(); // password
            in.readLine(); // ---
            if (fileEmail == email) { file.close(); return name; }
        }
        file.close();
        return "";
    }

    static bool updateUserPassword(QString email, QString currentPass, QString newPass)
    {
        QFile file("users.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
        QStringList lines;
        QTextStream in(&file);
        while (!in.atEnd()) lines.append(in.readLine());
        file.close();

        for (int i = 0; i + 3 < lines.size(); i += 4) {
            if (lines[i + 1] == email && lines[i + 2] == currentPass) {
                lines[i + 2] = newPass;
                QFile out("users.txt");
                if (!out.open(QIODevice::WriteOnly | QIODevice::Text)) return false;
                QTextStream ts(&out);
                for (const QString &l : lines) ts << l << "\n";
                out.close();
                return true;
            }
        }
        return false;
    }
};


#endif // FILE_H
