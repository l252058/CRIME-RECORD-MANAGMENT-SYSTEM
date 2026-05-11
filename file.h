#ifndef FILE_H
#define FILE_H

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QDateTime>

// =============================================================================
//  FileHandler — ALL file I/O for the Crime Record Management System
//
//  Files used:
//    crimes.txt   — caseID \t location \t type \t description \t status
//    officers.txt — officerID \t name \t rank \t badge \t assignedCase
//    court.txt    — caseID \t accused \t crimeType \t status
//    users.txt    — name \n email \n password \n --- \n  (4-line blocks)
//    logs.txt     — category \t timestamp \t action
// =============================================================================
// --- BACKEND LOGIC ---
// Handles all low-level disk I/O, parsing, and searching for the system.
class FileHandler
{

public:

    // =========================================================================
    //  CRIME RECORDS  (crimes.txt)
    //  Format : caseID \t location \t type \t description \t status
    // =========================================================================

    static void saveRecord(
        const QString & caseID,
        const QString & location,
        const QString & type,
        const QString & description
        )
    {
        QFile file("crimes.txt");

        if (!file.open(QIODevice::Append | QIODevice::Text))
        {
            return;
        }

        QTextStream out(&file);

        out << caseID
            << "\t" << location
            << "\t" << type
            << "\t" << description
            << "\t" << "Pending"
            << "\n";

        file.close();
    }

    static QStringList loadRecords()
    {
        QStringList records;

        QFile file("crimes.txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return records;
        }

        QTextStream in(&file);

        while (!in.atEnd())
        {
            QString line = in.readLine();

            if (!line.trimmed().isEmpty())
            {
                records.append(line);
            }
        }

        file.close();

        return records;
    }

    static void saveAll(const QStringList & records)
    {
        QFile file("crimes.txt");

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return;
        }

        QTextStream out(&file);

        for (const QString & r : records)
        {
            out << r << "\n";
        }

        file.close();
    }

    static bool caseIDExists(const QString & id)
    {
        for (const QString & line : loadRecords())
        {
            if (line.split("\t").value(0).trimmed() == id.trimmed())
            {
                return true;
            }
        }

        return false;
    }

    static bool updateRecord(
        const QString & id,
        const QString & location,
        const QString & type,
        const QString & description,
        const QString & status
        )
    {
        QStringList records = loadRecords();

        bool found = false;

        for (QString & line : records)
        {
            QStringList p = line.split("\t");

            if (p.size() >= 5 && p[0].trimmed() == id.trimmed())
            {
                p[1] = location;
                p[2] = type;
                p[3] = description;
                p[4] = status;

                line  = p.join("\t");
                found = true;

                break;
            }
        }

        if (found)
        {
            saveAll(records);
        }

        return found;
    }

    static bool deleteRecord(const QString & id)
    {
        QStringList records = loadRecords();

        int before = records.size();

        for (int i = records.size() - 1; i >= 0; i--)
        {
            if (records[i].split("\t").value(0).trimmed() == id.trimmed())
            {
                records.removeAt(i);
            }
        }

        if (records.size() < before)
        {
            saveAll(records);
            return true;
        }

        return false;
    }

    static QStringList loadRecord(const QString & id)
    {
        for (const QString & line : loadRecords())
        {
            QStringList p = line.split("\t");

            if (p.value(0).trimmed() == id.trimmed())
            {
                return p;
            }
        }

        return QStringList();
    }

    static bool updateStatus(const QString & id, const QString & newStatus)
    {
        QStringList records = loadRecords();

        bool found = false;

        for (QString & line : records)
        {
            QStringList p = line.split("\t");

            if (p.size() >= 5 && p[0].trimmed() == id.trimmed())
            {
                p[4] = newStatus;
                line  = p.join("\t");
                found = true;

                break;
            }
        }

        if (found)
        {
            saveAll(records);
        }

        return found;
    }

    static int countByStatus(const QString & status)
    {
        int count = 0;

        for (const QString & line : loadRecords())
        {
            if (line.split("\t").value(4).trimmed().toLower() == status.trimmed().toLower())
            {
                count++;
            }
        }

        return count;
    }

    static QMap<QString, int> getCrimeTypeStatistics()
    {
        QMap<QString, int> stats;

        for (const QString & line : loadRecords())
        {
            QString type = line.split("\t").value(2).trimmed();

            if (!type.isEmpty())
            {
                stats[type]++;
            }
        }

        return stats;
    }

    static QMap<QString, int> getLocationStatistics()
    {
        QMap<QString, int> stats;

        for (const QString & line : loadRecords())
        {
            QString loc = line.split("\t").value(1).trimmed();

            if (!loc.isEmpty())
            {
                stats[loc]++;
            }
        }

        return stats;
    }

    // =========================================================================
    //  OFFICER RECORDS  (officers.txt)
    //  Format : officerID \t name \t rank \t badge \t assignedCase
    //  Note   : assignedCase is empty string when unassigned
    // =========================================================================

    static void saveOfficer(
        const QString & id,
        const QString & name,
        const QString & rank,
        const QString & badge
        )
    {
        QFile file("officers.txt");

        if (!file.open(QIODevice::Append | QIODevice::Text))
        {
            return;
        }

        QTextStream out(&file);

        // Field 5 (assignedCase) is intentionally left empty — unassigned
        out << id
            << "\t" << name
            << "\t" << rank
            << "\t" << badge
            << "\t"
            << "\n";

        file.close();
    }

    static QStringList loadOfficers()
    {
        QStringList records;

        QFile file("officers.txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return records;
        }

        QTextStream in(&file);

        while (!in.atEnd())
        {
            QString line = in.readLine();

            if (!line.trimmed().isEmpty())
            {
                records.append(line);
            }
        }

        file.close();

        return records;
    }

    static void saveAllOfficers(const QStringList & records)
    {
        QFile file("officers.txt");

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return;
        }

        QTextStream out(&file);

        for (const QString & r : records)
        {
            out << r << "\n";
        }

        file.close();
    }

    static bool officerIDExists(const QString & id)
    {
        for (const QString & line : loadOfficers())
        {
            if (line.split("\t").value(0).trimmed() == id.trimmed())
            {
                return true;
            }
        }

        return false;
    }

    // Returns true if the officer already has a case assigned
    static bool isOfficerAssigned(const QString & id)
    {
        for (const QString & line : loadOfficers())
        {
            QStringList p = line.split("\t");

            if (p.value(0).trimmed() == id.trimmed())
            {
                return !p.value(4).trimmed().isEmpty();
            }
        }

        return false;
    }

    static bool updateOfficer(
        const QString & id,
        const QString & name,
        const QString & rank,
        const QString & badge
        )
    {
        QStringList records = loadOfficers();

        bool found = false;

        for (QString & line : records)
        {
            QStringList p = line.split("\t");

            if (p.size() >= 4 && p[0].trimmed() == id.trimmed())
            {
                p[1] = name;
                p[2] = rank;
                p[3] = badge;

                line  = p.join("\t");
                found = true;

                break;
            }
        }

        if (found)
        {
            saveAllOfficers(records);
        }

        return found;
    }

    static bool deleteOfficer(const QString & id)
    {
        QStringList records = loadOfficers();

        int before = records.size();

        for (int i = records.size() - 1; i >= 0; i--)
        {
            if (records[i].split("\t").value(0).trimmed() == id.trimmed())
            {
                records.removeAt(i);
            }
        }

        if (records.size() < before)
        {
            saveAllOfficers(records);
            return true;
        }

        return false;
    }

    static QStringList loadOfficer(const QString & id)
    {
        for (const QString & line : loadOfficers())
        {
            QStringList p = line.split("\t");

            if (p.value(0).trimmed() == id.trimmed())
            {
                return p;
            }
        }

        return QStringList();
    }

    static bool assignOfficerToCase(const QString & officerID, const QString & caseID)
    {
        if (!officerIDExists(officerID))
        {
            return false;
        }

        QStringList records = loadOfficers();

        bool found = false;

        for (QString & line : records)
        {
            QStringList p = line.split("\t");

            if (p.size() >= 5 && p[0].trimmed() == officerID.trimmed())
            {
                p[4] = caseID;
                line  = p.join("\t");
                found = true;

                break;
            }
        }

        if (found)
        {
            saveAllOfficers(records);
        }

        return found;
    }

    // Fix : only count lines that have 5 fields and a non-empty field[4]
    static int countAssignedOfficers()
    {
        int count = 0;

        for (const QString & line : loadOfficers())
        {
            QStringList p = line.split("\t");

            if (p.size() >= 5 && !p[4].trimmed().isEmpty())
            {
                count++;
            }
        }

        return count;
    }

    // Fix : only count lines that have 5 fields and an empty field[4]
    static int countUnassignedOfficers()
    {
        int count = 0;

        for (const QString & line : loadOfficers())
        {
            QStringList p = line.split("\t");

            if (p.size() >= 5 && p[4].trimmed().isEmpty())
            {
                count++;
            }
        }

        return count;
    }

    // =========================================================================
    //  COURT PROCEEDINGS  (court.txt)
    //  Format : caseID \t accused \t crimeType \t status
    // =========================================================================

    static void saveCourt(
        const QString & caseID,
        const QString & accused,
        const QString & crimeType
        )
    {
        QFile file("court.txt");

        if (!file.open(QIODevice::Append | QIODevice::Text))
        {
            return;
        }

        QTextStream out(&file);

        out << caseID
            << "\t" << accused
            << "\t" << crimeType
            << "\t" << "Ongoing"
            << "\n";

        file.close();
    }

    static QStringList loadCourt()
    {
        QStringList records;

        QFile file("court.txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return records;
        }

        QTextStream in(&file);

        while (!in.atEnd())
        {
            QString line = in.readLine();

            if (!line.trimmed().isEmpty())
            {
                records.append(line);
            }
        }

        file.close();

        return records;
    }

    static void saveAllCourt(const QStringList & records)
    {
        QFile file("court.txt");

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return;
        }

        QTextStream out(&file);

        for (const QString & r : records)
        {
            out << r << "\n";
        }

        file.close();
    }

    static bool courtCaseExists(const QString & id)
    {
        for (const QString & line : loadCourt())
        {
            if (line.split("\t").value(0).trimmed() == id.trimmed())
            {
                return true;
            }
        }

        return false;
    }

    static bool updateCourtStatus(const QString & id, const QString & newStatus)
    {
        QStringList records = loadCourt();

        bool found = false;

        for (QString & line : records)
        {
            QStringList p = line.split("\t");

            if (p.size() >= 4 && p[0].trimmed() == id.trimmed())
            {
                p[3] = newStatus;
                line  = p.join("\t");
                found = true;

                break;
            }
        }

        if (found)
        {
            saveAllCourt(records);
        }

        return found;
    }

    static QStringList loadCourtCase(const QString & id)
    {
        for (const QString & line : loadCourt())
        {
            QStringList p = line.split("\t");

            if (p.value(0).trimmed() == id.trimmed())
            {
                return p;
            }
        }

        return QStringList();
    }

    static int countCourtByStatus(const QString & status)
    {
        int count = 0;

        for (const QString & line : loadCourt())
        {
            if (line.split("\t").value(3).trimmed().toLower() == status.trimmed().toLower())
            {
                count++;
            }
        }

        return count;
    }

    // =========================================================================
    //  USERS  (users.txt)
    //  Format per user : name \n email \n password \n --- \n  (4-line block)
    // =========================================================================

    static bool saveUser(
        const QString & name,
        const QString & email,
        const QString & password
        )
    {
        if (emailExists(email))
        {
            return false;
        }

        QFile file("users.txt");

        if (!file.open(QIODevice::Append | QIODevice::Text))
        {
            return false;
        }

        QTextStream out(&file);

        out << name     << "\n"
            << email    << "\n"
            << password << "\n"
            << "---"    << "\n";

        file.close();

        return true;
    }

    static bool emailExists(const QString & email)
    {
        QFile file("users.txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return false;
        }

        QTextStream in(&file);

        while (!in.atEnd())
        {
            in.readLine();                        // name
            QString fileEmail = in.readLine();    // email
            in.readLine();                        // password
            in.readLine();                        // ---

            if (fileEmail.trimmed() == email.trimmed())
            {
                file.close();
                return true;
            }
        }

        file.close();

        return false;
    }

    static bool loginUser(const QString & email, const QString & password)
    {
        QFile file("users.txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return false;
        }

        QTextStream in(&file);

        while (!in.atEnd())
        {
            in.readLine();
            QString fileEmail    = in.readLine();
            QString filePassword = in.readLine();
            in.readLine();

            if (fileEmail.trimmed()    == email.trimmed() &&
                filePassword.trimmed() == password.trimmed())
            {
                file.close();
                return true;
            }
        }

        file.close();

        return false;
    }

    static bool loginAdmin(const QString & email, const QString & password)
    {
        QFile file("admins.txt");

        // If the file doesn't exist, create it with the master admin account
        // so the system isn't permanently locked out on first run.
        if (!file.exists())
        {
            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QTextStream out(&file);
                out << "admin\tadmin123\n";
                file.close();
            }
        }

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return false;
        }

        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList p = line.split("\t");

            if (p.size() >= 2 && p[0].trimmed() == email.trimmed() && p[1].trimmed() == password.trimmed())
            {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }

    static QString getUserName(const QString & email)
    {
        QFile file("users.txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return "";
        }

        QTextStream in(&file);

        while (!in.atEnd())
        {
            QString name      = in.readLine();
            QString fileEmail = in.readLine();
            in.readLine();
            in.readLine();

            if (fileEmail.trimmed() == email.trimmed())
            {
                file.close();
                return name;
            }
        }

        file.close();

        return "";
    }

    static bool updateUserPassword(
        const QString & email,
        const QString & currentPass,
        const QString & newPass
        )
    {
        QFile file("users.txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return false;
        }

        QStringList lines;
        QTextStream in(&file);

        while (!in.atEnd())
        {
            lines.append(in.readLine());
        }

        file.close();

        for (int i = 0; i + 3 < lines.size(); i += 4)
        {
            if (lines[i + 1].trimmed() == email.trimmed() &&
                lines[i + 2].trimmed() == currentPass.trimmed())
            {
                lines[i + 2] = newPass;

                QFile out("users.txt");

                if (!out.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    return false;
                }

                QTextStream ts(&out);

                for (const QString & l : lines)
                {
                    ts << l << "\n";
                }

                out.close();

                return true;
            }
        }

        return false;
    }

    // Fix : old version counted blank trailing lines as extra users
    static int countUsers()
    {
        QFile file("users.txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return 0;
        }

        QStringList lines;
        QTextStream in(&file);

        while (!in.atEnd())
        {
            QString line = in.readLine();
            lines.append(line);
        }

        file.close();

        int count = 0;

        // Each user block is exactly 4 lines: name, email, password, ---
        // Only count a block if the separator line "---" is actually present
        for (int i = 0; i + 3 < lines.size(); i += 4)
        {
            if (lines[i + 3].trimmed() == "---")
            {
                count++;
            }
        }

        return count;
    }

    // =========================================================================
    //  updateUserName — replaces the stored name for a given email
    //  Returns true if the email was found and the name was updated.
    // =========================================================================

    static bool updateUserName(const QString &email, const QString &newName)
    {
        QFile file("users.txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return false;
        }

        QStringList lines;
        QTextStream in(&file);

        while (!in.atEnd())
        {
            lines.append(in.readLine());
        }

        file.close();

        bool found = false;

        for (int i = 0; i + 3 < lines.size(); i += 4)
        {
            if (lines[i + 1].trimmed() == email.trimmed())
            {
                lines[i] = newName.trimmed();
                found    = true;
                break;
            }
        }

        if (!found)
        {
            return false;
        }

        QFile out("users.txt");

        if (!out.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return false;
        }

        QTextStream ts(&out);

        for (const QString &line : lines)
        {
            ts << line << "\n";
        }

        out.close();

        return true;
    }

    // =========================================================================
    //  countUserReports — counts submitted user reports in userreports.txt
    //  Each report block is exactly 5 lines ending with "---"
    // =========================================================================

    static int countUserReports()
    {
        QFile file("userreports.txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return 0;
        }

        QTextStream in(&file);
        int count = 0;

        while (!in.atEnd())
        {
            in.readLine();
            in.readLine();
            in.readLine();
            in.readLine();

            QString sep = in.readLine();

            if (sep.trimmed() == "---")
            {
                count++;
            }
        }

        file.close();

        return count;
    }
};

#endif // FILE_H