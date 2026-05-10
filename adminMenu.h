// ============================================================
// HEADER GUARD - Include Guard ka concept
// Agar yeh file already include ho chuki ho toh dobara include
// nahi hogi. Yeh multiple inclusion se bachata hai jo errors
// create kar sakta hai jab ek file baar baar include ho.
// ============================================================
#ifndef ADMINMENU_H
#define ADMINMENU_H

// ============================================================
// QT LIBRARY INCLUDES - Built-in Qt Classes
// Yeh sab Qt framework ki pre-built classes hain.
// Hum inhe include karte hain taake inki functionality use kar sakein.
// ============================================================
#include <QWidget>      // Base class for all UI windows - Admin class isi se inherit karegi
#include <QLabel>       // Screen pe text ya image dikhane ke liye use hoti hai
#include <QPixmap>      // Image file load karne aur hold karne ke liye
#include <QPushButton>  // Clickable button widget - user input ke liye

// ============================================================
// PROJECT KI APNI HEADER FILES - Custom Classes
// Yeh hamare project ki files hain. Har file ek alag feature
// ya window handle karti hai. Yeh SEPARATION OF CONCERNS
// ka concept hai - har cheez ka kaam alag file mein.
// ============================================================
#include "common.h"       // Shared UI helper functions aur custom Button classes - Reusability
#include "file.h"         // FileHandler class - file read/write operations ke liye
#include "crimeRecords.h" // Crime records manage karne wali window ki class
#include "crimeStatus.h"  // Case ka status dekhne wali window ki class
#include "court.h"        // Court proceedings wali window ki class
#include "reports.h"      // Reports aur analytics wali window ki class
#include "officer.h"      // Officers manage karne wali window ki class
#include "activityLog.h"  // System activity logs dekhne wali window ki class
#include "adminReport.h"  // User review karne wali window ki class
#include "logout.h"       // Logout confirmation dialog ki class

// ============================================================
// CLASS DEFINITION - Inheritance ka Concept
// "Admin" class bana rahe hain jo QWidget se publicly INHERIT
// karti hai. Inheritance ka matlab hai ke Admin class ko
// QWidget ki saari properties aur functions automatically
// mil jaate hain - jaise resize(), show(), close() etc.
// Hum sirf extra cheezein add kar rahe hain jo Admin ke
// liye specific hain.
// ============================================================
class Admin : public QWidget
{

    // ============================================================
    // PRIVATE SECTION - Encapsulation ka Concept
    // Private members sirf is class ke andar se access ho sakte hain.
    // Bahar se koi directly in variables ko touch nahi kar sakta.
    // Yeh DATA HIDING / ENCAPSULATION hai - OOP ka core concept.
    // Data ko protect karte hain taake galti se change na ho.
    // ============================================================
private:

    // Background image hold karne ke liye pointer
    // Pointer isliye use kiya ke Qt mein UI elements dynamic
    // memory pe (heap pe) "new" se banaye jaate hain
    QLabel *img;

    // 9 buttons ka array - sidebar ke liye
    // Array isliye ke loop ya index se easily manage ho sakein
    // Yeh sab QPushButton ke pointers hain
    QPushButton *button[9];

    // Pichli window ka pointer store karta hai
    // "Back" button press hone pe is pointer se pichli
    // window ko wapas dikha sakte hain.
    // Yeh ASSOCIATION / COMPOSITION ka concept hai -
    // Admin object ke paas doosre object ka reference hai
    QWidget *previousWindow;

    // ============================================================
    // PUBLIC SECTION
    // Public members ko bahar se bhi access kiya ja sakta hai.
    // Constructor aur functions yahan rakhte hain taake
    // bahar se object banana aur use karna possible ho.
    // ============================================================
public:

    // ============================================================
    // CONSTRUCTOR - Object banana ka special function
    // Constructor woh function hota hai jo class ka naam rakhta hai.
    // Jab "new Admin()" likha jata hai toh yeh automatically call hota hai.
    //
    // "QWidget *prev = nullptr" - DEFAULT PARAMETER ka concept
    // Agar koi value na dein toh prev apne aap nullptr ho jata hai.
    //
    // ": previousWindow(prev)" - MEMBER INITIALIZER LIST ka concept
    // Constructor body shuru hone se pehle member variable
    // ko directly initialize kar deta hai. Yeh zyada efficient hai.
    // ============================================================
    Admin(QWidget *prev = nullptr) : previousWindow(prev)
    {
        // Window ka title set kar rahe hain
        // Yeh title bar mein sabse upar dikhega
        setWindowTitle("ADMIN MENU - CRIME RECORD MANAGEMENT SYSTEM");

        // ============================================================
        // STATIC FUNCTION CALL - UI::setupBackground()
        // "UI::" matlab UI class ka static function call ho raha hai.
        // STATIC FUNCTION ka concept: kisi object ki zaroorat nahi,
        // seedha class ke naam se call hota hai.
        // "this" pass kar rahe hain taake function ko pata chale
        // ke background kis window mein lagani hai.
        // Return value "img" pointer mein store ho rahi hai.
        // ============================================================
        img = UI::setupBackground(this, "backgroundThree.png");

        // ============================================================
        // REUSABLE UI SETUP FUNCTIONS - Code Reusability ka Concept
        // Yeh teeno functions common.h mein define hain aur project
        // ki har window mein use hote hain. Baar baar same code
        // likhne ki bajaye ek jagah function banao aur sab jagah
        // call karo - yeh DRY principle hai (Don't Repeat Yourself)
        // ============================================================
        UI::setupSidebar(this, "[ ADMIN ACCESS ]");   // Left sidebar banata hai
        UI::setupPageHeader(                           // Top header banata hai
            this,
            "ADMIN DASHBOARD",
            "Full system control — select an option from the menu"
            );
        UI::setupFooter(this);                         // Bottom footer bar banata hai

        // ============================================================
        // DYNAMIC OBJECT CREATION - Heap Memory Allocation
        // "new" keyword se object heap pe banta hai.
        // "this" parent pass kiya hai - Qt ka parent-child system:
        // jab parent (Admin window) delete hogi, yeh label
        // automatically delete ho jaega. Memory leak nahi hoga.
        // ============================================================
        QLabel *welcomeText = new QLabel("WELCOME,  ADMINISTRATOR", this);

        // setGeometry(x, y, width, height) - position aur size pixels mein
        // x=380 matlab left se 380px, y=250 matlab upar se 250px
        welcomeText->setGeometry(380, 250, 1180, 40);

        // Text ko horizontally center mein align karo
        welcomeText->setAlignment(Qt::AlignCenter);

        // ============================================================
        // STYLESHEET - CSS jaisi styling
        // Qt mein HTML/CSS jaisi syntax se appearance set hoti hai.
        // MONO ek pre-defined string constant hai common.h mein -
        // font family define karta hai. Yeh bhi reusability hai.
        // String literals side by side rakhne se automatically
        // concatenate ho jaate hain C++ mein.
        // ============================================================
        welcomeText->setStyleSheet
            (
                MONO +                       // common.h se font string - reusability
                "font-size : 32px;"          // Bara font size
                "font-weight : bold;"        // Bold text
                "letter-spacing : 6px;"      // Huroof ke beech space
                "color : #ffcc44;"           // Golden/yellow rang
                "background : transparent;"  // Peeche ka background show hoga
                );

        // Subtitle label - chhoti description ke liye
        // Yeh bhi dynamic object hai, parent "this" hai
        QLabel *welcomeSub = new QLabel("You have full access to manage records, officers, reports, and users.", this);
        welcomeSub->setGeometry(380, 300, 1180, 24); // welcomeText se 50px neeche
        welcomeSub->setAlignment(Qt::AlignCenter);
        welcomeSub->setStyleSheet
            (
                MONO +
                "font-size : 16px;"
                "color : #c0dff5;"           // Light blue rang
                "background : transparent;"
                "font-weight: bold;"
                );

        // ============================================================
        // SIDEBAR BUTTONS - Polymorphism ka Concept
        // Yahan teen alag alag button types use ho rahe hain:
        // 1. Button       - normal action button (common.h mein defined)
        // 2. BackButton   - peeche jaane ka button (common.h mein defined)
        // 3. ClearButton  - red/warning style button (common.h mein defined)
        //
        // Teeno QPushButton se INHERIT karte hain lekin har ek ka
        // look aur feel alag hai - yeh POLYMORPHISM hai.
        // Sab ka constructor: (text, x, y, width, height, parent)
        // Sab x=25 pe hain (left sidebar), aur har ek 60px neeche hai
        // ============================================================
        button[0] = new Button("Manage Records",      25, 170, 270, 40, this); // Crime records ki window
        button[1] = new Button("Manage Officers",     25, 230, 270, 40, this); // Officers ki window
        button[2] = new Button("Case Status",         25, 290, 270, 40, this); // Case status ki window
        button[3] = new Button("Court Proceedings",   25, 350, 270, 40, this); // Court ki window
        button[4] = new Button("Reports & Analytics", 25, 410, 270, 40, this); // Reports ki window
        button[5] = new Button("User Review",         25, 470, 270, 40, this); // User review ki window
        button[6] = new Button("Activity Logs",       25, 530, 270, 40, this); // Activity logs ki window
        button[7] = new BackButton(                   25, 590, 270, 40, this); // Pichli window pe wapas
        button[8] = new ClearButton("LOGOUT",         25, 650, 270, 40, this); // Logout karne ke liye

        // ============================================================
        // SIGNALS & SLOTS - Qt ka Event System (Event-Driven Programming)
        //
        // connect(sender, signal, receiver, slot) ka pattern hai.
        // Jab button click hoga (clicked() SIGNAL emit hoga)
        // toh lambda function (SLOT) call hoga.
        //
        // "[=]" matlab lambda function ke andar outer scope ki
        // saari variables copy ho ke available hain (capture by value).
        //
        // Yeh EVENT-DRIVEN PROGRAMMING ka concept hai - code tab
        // run hota hai jab koi event (click) hota hai, pehle nahi.
        // ============================================================

        // --- Button[0] clicked: Manage Records window kholo ---
        connect(button[0], &QPushButton::clicked, this, [=]()
                {
                    // Static function call - FileHandler class ka
                    // Yeh activity log file mein entry likhta hai
                    FileHandler::appendLog("ADMIN", "Opened Manage Records");

                    // Naya CrimeRecordPage object heap pe banao
                    // "true" pass kiya - matlab admin mode (full access)
                    // Yeh PARAMETERIZED CONSTRUCTOR call hai
                    CrimeRecordPage *page = new CrimeRecordPage(true);

                    // WA_DeleteOnClose: jab yeh window band hogi
                    // toh "delete" apne aap call hoga - memory free hogi
                    // Yeh MEMORY MANAGEMENT ka best practice hai
                    page->setAttribute(Qt::WA_DeleteOnClose);

                    page->showMaximized(); // Full screen mein dikhao
                }
                );

        // --- Button[1] clicked: Manage Officers window kholo ---
        connect(button[1], &QPushButton::clicked, this, [=]()
                {
                    FileHandler::appendLog("ADMIN", "Opened Manage Officers");

                    // Officers class ka object - "true" = admin mode
                    Officers *page = new Officers(true);
                    page->setAttribute(Qt::WA_DeleteOnClose);
                    page->showMaximized();
                }
                );

        // --- Button[2] clicked: Case Status window kholo ---
        connect(button[2], &QPushButton::clicked, this, [=]()
                {
                    FileHandler::appendLog("ADMIN", "Opened Case Status");

                    CaseStatusPage *page = new CaseStatusPage(true); // Admin mode
                    page->setAttribute(Qt::WA_DeleteOnClose);
                    page->showMaximized();
                }
                );

        // --- Button[3] clicked: Court Proceedings window kholo ---
        connect(button[3], &QPushButton::clicked, this, [=]()
                {
                    FileHandler::appendLog("ADMIN", "Opened Court Proceedings");

                    CourtProceedings *page = new CourtProceedings(true);
                    page->setAttribute(Qt::WA_DeleteOnClose);
                    page->showMaximized();
                }
                );

        // --- Button[4] clicked: Reports & Analytics window kholo ---
        connect(button[4], &QPushButton::clicked, this, [=]()
                {
                    FileHandler::appendLog("ADMIN", "Opened Reports & Analytics");

                    // Default constructor use ho raha hai - koi parameter nahi
                    Reports *page = new Reports();
                    page->setAttribute(Qt::WA_DeleteOnClose);
                    page->showMaximized();
                }
                );

        // --- Button[5] clicked: User Review window kholo ---
        connect(button[5], &QPushButton::clicked, this, [=]()
                {
                    FileHandler::appendLog("ADMIN", "Opened User Review");

                    AdminReports *page = new AdminReports();
                    page->setAttribute(Qt::WA_DeleteOnClose);
                    page->showMaximized();
                }
                );

        // --- Button[6] clicked: Activity Logs window kholo ---
        connect(button[6], &QPushButton::clicked, this, [=]()
                {
                    FileHandler::appendLog("ADMIN", "Opened Activity Logs");

                    ActivityLogs *page = new ActivityLogs();
                    page->setAttribute(Qt::WA_DeleteOnClose);
                    page->showMaximized();
                }
                );

        // --- Button[7] clicked: Back - Pichli window pe wapas jao ---
        connect(button[7], &QPushButton::clicked, this, [=]()
                {
                    // NULL CHECK - pehle check karo ke previousWindow exist karta hai
                    // Agar previousWindow nullptr hai aur hum isko call karein
                    // toh program crash ho jaega - isliye yeh check zaroori hai
                    if (previousWindow)
                    {
                        previousWindow->showMaximized(); // Pichli window wapas dikhao
                    }

                    // Chahe previousWindow ho ya na ho, current window band karo
                    this->close();
                }
                );

        // --- Button[8] clicked: Logout Dialog kholo ---
        connect(button[8], &QPushButton::clicked, this, [=]()
                {
                    // LogoutDialog ka naya object banao
                    // "this" parent pass kar rahe hain - LogoutDialog ke
                    // peeche Admin window visible rahegi
                    LogoutDialog *logout = new LogoutDialog(this);
                    logout->showMaximized();
                }
                );
    }

    // ============================================================
    // resizeEvent() - METHOD OVERRIDING ka Concept (Polymorphism)
    //
    // QWidget (parent class) mein resizeEvent() pehle se exist karta hai.
    // Hum isko OVERRIDE kar rahe hain apne custom behavior ke liye.
    // "override" keyword compiler ko confirm karta hai ke yeh
    // intentional override hai - agar function signature galat ho
    // toh compiler error dega.
    //
    // Yeh function automatically call hota hai jab bhi window ki
    // size change ho - maximize, restore, ya manually resize karo.
    // Isko hum khud call nahi karte, Qt framework call karta hai.
    // Yeh VIRTUAL FUNCTION MECHANISM hai jo Qt use karta hai.
    // ============================================================
    void resizeEvent(QResizeEvent *event) override
    {
        // Background image ko window ki nayi size ke saath match karo
        // event->size() se naya width aur height milta hai
        // Taake background image hamesha poori window fill kare
        // chahe window ka size kuch bhi ho
        img->resize(event->size());
    }

};

// Header Guard ka closing - yahan ADMINMENU_H ka define khatam hota hai
#endif