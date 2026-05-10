#include <iostream>
#include <string>
#include <ctime>

using namespace std;


const string CASE_SOLVED = "Solved";
const string CASE_PENDING = "Pending";
const string CASE_COLD = "Cold";

const string ROLE_USER = "User";
const string ROLE_ADMIN = "Admin";

const string ACTION_VIEWED = "Viewed";
const string ACTION_ADDED = "Added";
const string ACTION_MODIFIED = "Modified";
const string ACTION_DELETED = "Deleted";
const string ACTION_STATUS_CHANGED = "Status Changed";
const string ACTION_LOGIN = "Login";
const string ACTION_LOGOUT = "Logout";

const string REPORT_PENDING = "Pending";
const string REPORT_RESOLVED = "Resolved";
const string REPORT_REJECTED = "Rejected";


string getTimestamp()
{
    time_t now = time(nullptr);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buf);
}


struct LogEntry
{
    string timestamp;
    string username;
    string action;
    string target;
    string details;

    LogEntry(const string& user, const string& act, const string& tgt, const string& det = "")
    {
        username = user;
        action = act;
        target = tgt;
        details = det;
        timestamp = getTimestamp();
    }

    void display() const
    {
        cout << "[" << timestamp << "]"
            << "  User: " << username
            << "  |  Action: " << action
            << "  |  Target: " << target;

        if (!details.empty())
        {
            cout << "  |  Details: " << details;
        }

        cout << "\n";
    }
};


class ActivityLogger
{
private:

    static const int MAX_LOGS = 200;
    LogEntry* logs[MAX_LOGS];
    int count;

public:

    ActivityLogger()
    {
        count = 0;
    }

    ~ActivityLogger()
    {
        for (int i = 0; i < count; i++)
        {
            delete logs[i];
        }
    }

    void addLog(const string& username, const string& action, const string& target, const string& details = "")
    {
        if (count >= MAX_LOGS)
        {
            cout << "[Logger] Capacity full. Oldest entry removed.\n";
            delete logs[0];

            for (int i = 0; i < count - 1; i++)
            {
                logs[i] = logs[i + 1];
            }

            count--;
        }

        logs[count] = new LogEntry(username, action, target, details);
        count++;
    }

    void showAllLogs(const string& role) const
    {
        if (role != ROLE_ADMIN)
        {
            cout << "[Access Denied] Only admins can view activity logs.\n";
            return;
        }

        if (count == 0)
        {
            cout << "No activity logs found.\n";
            return;
        }

        cout << "\nActivity Log (" << count << " entries)\n";

        for (int i = 0; i < count; i++)
        {
            logs[i]->display();
        }
    }

    void showLogsByUser(const string& username, const string& role) const
    {
        if (role != ROLE_ADMIN)
        {
            cout << "[Access Denied] Only admins can filter activity logs.\n";
            return;
        }

        cout << "\nLogs for user: " << username << "\n";

        bool found = false;

        for (int i = 0; i < count; i++)
        {
            if (logs[i]->username == username)
            {
                logs[i]->display();
                found = true;
            }
        }

        if (!found)
        {
            cout << "No entries found for user: " << username << "\n";
        }
    }

    void showLogsByAction(const string& action, const string& role) const
    {
        if (role != ROLE_ADMIN)
        {
            cout << "[Access Denied] Only admins can filter activity logs.\n";
            return;
        }

        cout << "\nLogs for action: " << action << "\n";

        bool found = false;

        for (int i = 0; i < count; i++)
        {
            if (logs[i]->action == action)
            {
                logs[i]->display();
                found = true;
            }
        }

        if (!found)
        {
            cout << "No entries found.\n";
        }
    }

    int getCount() const
    {
        return count;
    }
};


class Case
{
private:

    string caseID;
    string location;
    string description;
    string penalSection;
    string status;

public:

    Case(const string& id, const string& loc, const string& desc, const string& penal, const string& st = CASE_PENDING)
    {
        caseID = id;
        location = loc;
        description = desc;
        penalSection = penal;
        status = st;
    }

    string getCaseID()       const { return caseID; }
    string getLocation()     const { return location; }
    string getDescription()  const { return description; }
    string getPenalSection() const { return penalSection; }
    string getStatus()       const { return status; }

    void setLocation(const string& loc) { location = loc; }
    void setDescription(const string& d) { description = d; }
    void setPenalSection(const string& p) { penalSection = p; }

    void updateStatus(const string& newStatus, const string& changedBy, ActivityLogger& logger)
    {
        string detail = "Status: " + status + " -> " + newStatus;

        status = newStatus;

        logger.addLog(changedBy, ACTION_STATUS_CHANGED, "Case #" + caseID, detail);

        cout << "[Case " << caseID << "] Status updated to: " << status << "\n";
    }

    void showInfo(const string& viewedBy, ActivityLogger& logger) const
    {
        logger.addLog(viewedBy, ACTION_VIEWED, "Case #" + caseID);

        cout << "\n----- Case ID: " << caseID << " -----\n";
        cout << "Location      : " << location << "\n";
        cout << "Penal Section : " << penalSection << "\n";
        cout << "Description   : " << description << "\n";
        cout << "Status        : " << status << "\n";
        cout << "-----------------------------\n";
    }
};


class CaseRepository
{
private:

    static const int MAX_CASES = 100;
    Case* cases[MAX_CASES];
    int count;

public:

    CaseRepository()
    {
        count = 0;
    }

    ~CaseRepository()
    {
        for (int i = 0; i < count; i++)
        {
            delete cases[i];
        }
    }

    bool addCase(Case* c, const string& addedBy, ActivityLogger& logger)
    {
        if (count >= MAX_CASES)
        {
            cout << "Repository full.\n";
            return false;
        }

        cases[count] = c;
        count++;

        logger.addLog(addedBy, ACTION_ADDED, "Case #" + c->getCaseID());

        cout << "[Repository] Case " << c->getCaseID() << " added.\n";
        return true;
    }

    Case* findByID(const string& id) const
    {
        for (int i = 0; i < count; i++)
        {
            if (cases[i]->getCaseID() == id)
            {
                return cases[i];
            }
        }

        return nullptr;
    }

    void showByStatus(const string& filter, const string& viewedBy, ActivityLogger& logger) const
    {
        cout << "\nCases with status: " << filter << "\n";

        bool found = false;

        for (int i = 0; i < count; i++)
        {
            if (cases[i]->getStatus() == filter)
            {
                cases[i]->showInfo(viewedBy, logger);
                found = true;
            }
        }

        if (!found)
        {
            cout << "No cases found with that status.\n";
        }
    }

    void showStatusSummary() const
    {
        int solved = 0;
        int pending = 0;
        int cold = 0;

        for (int i = 0; i < count; i++)
        {
            if (cases[i]->getStatus() == CASE_SOLVED)
            {
                solved++;
            }
            if (cases[i]->getStatus() == CASE_PENDING)
            {
                pending++;
            }
            if (cases[i]->getStatus() == CASE_COLD)
            {
                cold++;
            }
        }

        cout << "\nCase Status Summary\n";
        cout << "Solved  : " << solved << "\n";
        cout << "Pending : " << pending << "\n";
        cout << "Cold    : " << cold << "\n";
        cout << "Total   : " << count << "\n";
    }

    int getCount() const
    {
        return count;
    }
};


class UserReport
{
private:

    string reportID;
    string userEmail;
    string caseReference;
    string subject;
    string body;
    string status;
    string adminComment;
    string timestamp;

public:

    UserReport(const string& id, const string& email, const string& caseRef, const string& subj, const string& reportBody)
    {
        reportID = id;
        userEmail = email;
        caseReference = caseRef;
        subject = subj;
        body = reportBody;
        status = REPORT_PENDING;
        adminComment = "";
        timestamp = getTimestamp();
    }

    string getReportID()      const { return reportID; }
    string getUserEmail()     const { return userEmail; }
    string getCaseReference() const { return caseReference; }
    string getSubject()       const { return subject; }
    string getBody()          const { return body; }
    string getStatus()        const { return status; }
    string getAdminComment()  const { return adminComment; }
    string getTimestamp()     const { return timestamp; }

    void updateStatus(const string& newStatus, const string& comment)
    {
        status = newStatus;
        adminComment = comment;

        cout << "[Report " << reportID << "] Status updated to: " << status << "\n";
    }

    void showInfo() const
    {
        cout << "\n----- Report ID: " << reportID << " -----\n";
        cout << "User Email      : " << userEmail << "\n";
        cout << "Case Reference  : " << caseReference << "\n";
        cout << "Subject         : " << subject << "\n";
        cout << "Body            : " << body << "\n";
        cout << "Status          : " << status << "\n";
        cout << "Admin Comment   : " << (adminComment.empty() ? "None" : adminComment) << "\n";
        cout << "Submitted At    : " << timestamp << "\n";
        cout << "-----------------------------\n";
    }
};


class ReportRepository
{
private:

    static const int MAX_REPORTS = 100;
    UserReport* reports[MAX_REPORTS];
    int count;
    int nextID;

public:

    ReportRepository()
    {
        count = 0;
        nextID = 1;
    }

    ~ReportRepository()
    {
        for (int i = 0; i < count; i++)
        {
            delete reports[i];
        }
    }

    bool submitReport(const string& email, const string& caseRef, const string& subject, const string& body)
    {
        if (count >= MAX_REPORTS)
        {
            cout << "Report repository full.\n";
            return false;
        }

        string id = "RPT-00" + to_string(nextID);
        nextID++;

        reports[count] = new UserReport(id, email, caseRef, subject, body);
        count++;

        cout << "[Report] Submitted with ID: " << id << "\n";
        return true;
    }

    UserReport* findByID(const string& id) const
    {
        for (int i = 0; i < count; i++)
        {
            if (reports[i]->getReportID() == id)
            {
                return reports[i];
            }
        }

        return nullptr;
    }

    void showByEmail(const string& email) const
    {
        cout << "\nReports for: " << email << "\n";

        bool found = false;

        for (int i = 0; i < count; i++)
        {
            if (reports[i]->getUserEmail() == email)
            {
                reports[i]->showInfo();
                found = true;
            }
        }

        if (!found)
        {
            cout << "No reports found for: " << email << "\n";
        }
    }

    void showAll(const string& role) const
    {
        if (role != ROLE_ADMIN)
        {
            cout << "[Access Denied] Only admins can view all reports.\n";
            return;
        }

        if (count == 0)
        {
            cout << "No reports found.\n";
            return;
        }

        cout << "\nAll Reports (" << count << ")\n";

        for (int i = 0; i < count; i++)
        {
            reports[i]->showInfo();
        }
    }

    void showStatusSummary(const string& role) const
    {
        if (role != ROLE_ADMIN)
        {
            cout << "[Access Denied] Only admins can view report summary.\n";
            return;
        }

        int pending = 0;
        int resolved = 0;
        int rejected = 0;

        for (int i = 0; i < count; i++)
        {
            if (reports[i]->getStatus() == REPORT_PENDING)
            {
                pending++;
            }
            if (reports[i]->getStatus() == REPORT_RESOLVED)
            {
                resolved++;
            }
            if (reports[i]->getStatus() == REPORT_REJECTED)
            {
                rejected++;
            }
        }

        cout << "\nReport Status Summary\n";
        cout << "Pending  : " << pending << "\n";
        cout << "Resolved : " << resolved << "\n";
        cout << "Rejected : " << rejected << "\n";
        cout << "Total    : " << count << "\n";
    }

    int getCount() const
    {
        return count;
    }
};


int main()
{
    ActivityLogger   logger;
    CaseRepository   caseRepo;
    ReportRepository reportRepo;

    logger.addLog("admin1", ACTION_LOGIN, "System");
    logger.addLog("officer1", ACTION_LOGIN, "System");

    Case* c1 = new Case("C001", "Lahore", "Armed robbery at bank", "Section 392");
    Case* c2 = new Case("C002", "Karachi", "Cybercrime fraud", "Section 420");
    Case* c3 = new Case("C003", "Islamabad", "Hit and run", "Section 304-A", CASE_SOLVED);
    Case* c4 = new Case("C004", "Faisalabad", "Drug trafficking", "Section 9(c)", CASE_COLD);

    caseRepo.addCase(c1, "admin1", logger);
    caseRepo.addCase(c2, "admin1", logger);
    caseRepo.addCase(c3, "admin1", logger);
    caseRepo.addCase(c4, "admin1", logger);

    caseRepo.showByStatus(CASE_PENDING, "officer1", logger);
    caseRepo.showByStatus(CASE_SOLVED, "officer1", logger);
    caseRepo.showByStatus(CASE_COLD, "officer1", logger);

    c1->updateStatus(CASE_SOLVED, "admin1", logger);
    c2->updateStatus(CASE_COLD, "admin1", logger);

    Case* found = caseRepo.findByID("C001");

    if (found)
    {
        found->showInfo("officer1", logger);
    }

    caseRepo.showStatusSummary();

    reportRepo.submitReport("ali@email.com", "C001", "Witness Info", "I saw the suspect near the bank.");
    reportRepo.submitReport("sara@email.com", "C002", "New Evidence", "Found a suspicious email thread.");
    reportRepo.submitReport("ali@email.com", "C003", "Update Request", "Please update the case status.");

    reportRepo.showByEmail("ali@email.com");

    reportRepo.showAll(ROLE_ADMIN);

    UserReport* r = reportRepo.findByID("RPT-001");

    if (r)
    {
        r->updateStatus(REPORT_RESOLVED, "Case reviewed and closed.");
    }

    reportRepo.showStatusSummary(ROLE_ADMIN);

    logger.addLog("officer1", ACTION_LOGOUT, "System");

    logger.showAllLogs(ROLE_ADMIN);

    logger.showAllLogs(ROLE_USER);

    logger.showLogsByUser("admin1", ROLE_ADMIN);

    logger.showLogsByAction(ACTION_STATUS_CHANGED, ROLE_ADMIN);

    logger.addLog("admin1", ACTION_LOGOUT, "System");

    return 0;
}