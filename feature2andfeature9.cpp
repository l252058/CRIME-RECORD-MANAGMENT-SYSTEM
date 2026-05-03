#include <iostream>
#include <string>
#include <ctime>
using namespace std;


//  Enums
enum class CaseStatus { SOLVED, PENDING, COLD };
enum class UserRole { USER, ADMIN };
enum class ActionType { VIEWED, ADDED, MODIFIED, DELETED, STATUS_CHANGED, LOGIN, LOGOUT };
//  Helper: Convert enums to readable strings
string caseStatusToString(CaseStatus s) {
    switch (s) {
    case CaseStatus::SOLVED:  return "Solved";
    case CaseStatus::PENDING: return "Pending";
    case CaseStatus::COLD:    return "Cold";
    }
    return "Unknown";
}

string actionTypeToString(ActionType a) {
    switch (a) {
    case ActionType::VIEWED:         return "Viewed";
    case ActionType::ADDED:          return "Added";
    case ActionType::MODIFIED:       return "Modified";
    case ActionType::DELETED:        return "Deleted";
    case ActionType::STATUS_CHANGED: return "Status Changed";
    case ActionType::LOGIN:          return "Login";
    case ActionType::LOGOUT:         return "Logout";
    }
    return "Unknown";
}

string currentTimestamp() {
    time_t now = time(nullptr);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buf);
}
//  Feature 9 — Activity Log Entry
struct LogEntry {
    string     timestamp;
    string     username;
    ActionType action;
    string     target;      // e.g. "Case #C001" or "Account: ali"
    string     details;     // extra detail string

    LogEntry(const string& user, ActionType act,
        const string& tgt, const string& det = "")
        : username(user), action(act), target(tgt), details(det)
    {
        timestamp = currentTimestamp();
    }

    void display() const {
        cout << "[" << timestamp << "]  "
            << "User: " << username << "  |  "
            << "Action: " << actionTypeToString(action) << "  |  "
            << "Target: " << target;
        if (!details.empty())
            cout << "  |  Details: " << details;
        cout << "\n";
    }
};
//  Feature 9 — Activity Logger
class ActivityLogger {
private:
    static const int MAX_LOGS = 200;
    LogEntry* logs[MAX_LOGS];
    int       count;

public:
    ActivityLogger() : count(0) {}

    ~ActivityLogger() {
        for (int i = 0; i < count; i++)
            delete logs[i];
    }
    // Record a new log entry
    void log(const string& username, ActionType action,
        const string& target, const string& details = "") {
        if (count >= MAX_LOGS) {
            cout << "[Logger] Log capacity full. Oldest entry removed.\n";
            delete logs[0];
            for (int i = 0; i < count - 1; i++)
                logs[i] = logs[i + 1];
            count--;
        }
        logs[count++] = new LogEntry(username, action, target, details);
    }

    // Admin-only: view all logs
    void viewAllLogs(UserRole role) const {
        if (role != UserRole::ADMIN) {
            cout << "[Access Denied] Only admins can view activity logs.\n";
            return;
        }
        if (count == 0) {
            cout << "No activity logs found.\n";
            return;
        }
        cout << "\n========== Activity Log (" << count << " entries) ==========\n";
        for (int i = 0; i < count; i++)
            logs[i]->display();
        cout << "=====================================================\n";
    }

    // Admin-only: filter logs by username
    void viewLogsByUser(const string& username, UserRole role) const {
        if (role != UserRole::ADMIN) {
            cout << "[Access Denied] Only admins can filter activity logs.\n";
            return;
        }
        cout << "\n===== Logs for user: " << username << " =====\n";
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (logs[i]->username == username) {
                logs[i]->display();
                found = true;
            }
        }
        if (!found)
            cout << "No entries found for user: " << username << "\n";
        cout << "==========================================\n";
    }

    // Admin-only: filter logs by action type
    void viewLogsByAction(ActionType action, UserRole role) const {
        if (role != UserRole::ADMIN) {
            cout << "[Access Denied] Only admins can filter activity logs.\n";
            return;
        }
        cout << "\n===== Logs for action: " << actionTypeToString(action) << " =====\n";
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (logs[i]->action == action) {
                logs[i]->display();
                found = true;
            }
        }
        if (!found)
            cout << "No entries found.\n";
        cout << "=============================================\n";
    }

    int getCount() const { return count; }
};
//  Feature 2 — Case (with Status Tracking)
class Case {
private:
    string     caseID;
    string     location;
    string     description;
    string     penal_section;
    CaseStatus status;

public:
    // Constructor
    Case(const string& id, const string& loc,
        const string& desc, const string& penal,
        CaseStatus st = CaseStatus::PENDING)
        : caseID(id), location(loc), description(desc),
        penal_section(penal), status(st) {
    }

    // Accessors
    string     getCaseID()      const { return caseID; }
    string     getLocation()    const { return location; }
    string     getDescription() const { return description; }
    string     getPenalSection()const { return penal_section; }
    CaseStatus getStatus()      const { return status; }

    // Mutators
    void setLocation(const string& loc) { location = loc; }
    void setDescription(const string& d) { description = d; }
    void setPenalSection(const string& p) { penal_section = p; }

    // Feature 2: Update case status
    void updateStatus(CaseStatus newStatus, const string& changedBy,
        ActivityLogger& logger) {
        string detail = "Status: " + caseStatusToString(status)
            + " -> " + caseStatusToString(newStatus);
        status = newStatus;
        logger.log(changedBy, ActionType::STATUS_CHANGED, "Case #" + caseID, detail);
        cout << "[Case " << caseID << "] Status updated to: "
            << caseStatusToString(status) << "\n";
    }

    // Display case info
    void displayInfo(const string& viewedBy, ActivityLogger& logger) const {
        logger.log(viewedBy, ActionType::VIEWED, "Case #" + caseID);
        cout << "\n----- Case ID: " << caseID << " -----\n";
        cout << "Location     : " << location << "\n";
        cout << "Penal Section: " << penal_section << "\n";
        cout << "Description  : " << description << "\n";
        cout << "Status       : " << caseStatusToString(status) << "\n";
        cout << "-----------------------------\n";
    }
};

// Simple Case Repository
class CaseRepository {
private:
    static const int MAX_CASES = 100;
    Case* cases[MAX_CASES];
    int   count;

public:
    CaseRepository() : count(0) {}

    ~CaseRepository() {
        for (int i = 0; i < count; i++)
            delete cases[i];
    }

    // Add a case (logs the action)
    bool addCase(Case* c, const string& addedBy, ActivityLogger& logger) {
        if (count >= MAX_CASES) {
            cout << "Repository full.\n";
            return false;
        }
        cases[count++] = c;
        logger.log(addedBy, ActionType::ADDED, "Case #" + c->getCaseID());
        cout << "[Repository] Case " << c->getCaseID() << " added.\n";
        return true;
    }

    // Find case by ID
    Case* findByID(const string& id) const {
        for (int i = 0; i < count; i++)
            if (cases[i]->getCaseID() == id)
                return cases[i];
        return nullptr;
    }

    // Feature 2: Filter & display by status
    void displayByStatus(CaseStatus filter, const string& viewedBy,
        ActivityLogger& logger) const {
        cout << "\n===== Cases with status: "
            << caseStatusToString(filter) << " =====\n";
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (cases[i]->getStatus() == filter) {
                cases[i]->displayInfo(viewedBy, logger);
                found = true;
            }
        }
        if (!found)
            cout << "No cases found with that status.\n";
        cout << "===========================================\n";
    }

    // Feature 2: Display status summary
    void displayStatusSummary() const {
        int solved = 0, pending = 0, cold = 0;
        for (int i = 0; i < count; i++) {
            switch (cases[i]->getStatus()) {
            case CaseStatus::SOLVED:  solved++;  break;
            case CaseStatus::PENDING: pending++; break;
            case CaseStatus::COLD:    cold++;    break;
            }
        }
        cout << "\n===== Case Status Summary =====\n";
        cout << "Solved  : " << solved << "\n";
        cout << "Pending : " << pending << "\n";
        cout << "Cold    : " << cold << "\n";
        cout << "Total   : " << count << "\n";
        cout << "================================\n";
    }

    int getCount() const { return count; }
};
int main() {
    ActivityLogger logger;
    CaseRepository repo;

    // Simulate logins
    logger.log("admin1", ActionType::LOGIN, "System");
    logger.log("officer1", ActionType::LOGIN, "System");

    //  Feature2 + Feature9
    Case* c1 = new Case("C001", "Lahore", "Armed robbery at bank", "Section 392");
    Case* c2 = new Case("C002", "Karachi", "Cybercrime fraud", "Section 420");
    Case* c3 = new Case("C003", "Islamabad", "Hit and run", "Section 304-A",
        CaseStatus::SOLVED);
    Case* c4 = new Case("C004", "Faisalabad", "Drug trafficking", "Section 9(c)",
        CaseStatus::COLD);

    repo.addCase(c1, "admin1", logger);
    repo.addCase(c2, "admin1", logger);
    repo.addCase(c3, "admin1", logger);
    repo.addCase(c4, "admin1", logger);

    // View cases by status
    repo.displayByStatus(CaseStatus::PENDING, "officer1", logger);
    repo.displayByStatus(CaseStatus::SOLVED, "officer1", logger);
    repo.displayByStatus(CaseStatus::COLD, "officer1", logger);

    //  Update statuses
    c1->updateStatus(CaseStatus::SOLVED, "admin1", logger);
    c2->updateStatus(CaseStatus::COLD, "admin1", logger);

    //View a single case
    Case* found = repo.findByID("C001");
    if (found) found->displayInfo("officer1", logger);

    //Status summary
    repo.displayStatusSummary();

    // Simulate logout
    logger.log("officer1", ActionType::LOGOUT, "System");

    //  Admin views full log
    logger.viewAllLogs(UserRole::ADMIN);

    // Non-admin tries to view log 
    logger.viewAllLogs(UserRole::USER);

    // Filter by user
    logger.viewLogsByUser("admin1", UserRole::ADMIN);

    //  Filter by action type
    logger.viewLogsByAction(ActionType::STATUS_CHANGED, UserRole::ADMIN);

    //Simulate logout admin
    logger.log("admin1", ActionType::LOGOUT, "System");

    return 0;
}