#ifndef INTERFACE2_H
#define INTERFACE2_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>

#include "common.h"
#include "adminMenu.h"
#include "userMenu.h"

// =============================================================================
//  PAGE 2 — AUTH PAGE   (backgroundTwo.png)
// =============================================================================

class AuthPage : public QWidget
{
private:

    QLabel *img;
    Button *user;
    Button *admin;
    Button *signIn;
    Button *signInTab;
    Button *createAccountTab;
    Button *createAccount;
    Card   *adminAccount;
    Card   *userAccount;
    Card   *userCreateAccount;
    Box    *adminEmail;
    Box    *adminPassword;
    Box    *userEmail;
    Box    *userPassword;
    Box    *name;
    Box    *confirmPassword;
    Box    *createEmail;
    Box    *createPassword;
    bool    isAdmin = false;

public:

    AuthPage()
    {
        setWindowTitle("Crime Record Management System");
        setMinimumSize(900, 600);
        resize(1600, 1000);

        // Background
        img = new QLabel(this);
        img->setPixmap(loadPixmap("backgroundTwo.png"));
        img->setScaledContents(true);
        img->setGeometry(0, 0, width(), height());

        // Cards
        adminAccount = new Card(980, 230, 500, 310, this);
        adminAccount->hide();

        userAccount = new Card(980, 230, 500, 310, this);
        userAccount->hide();

        userCreateAccount = new Card(980, 230, 500, 400, this);
        userCreateAccount->hide();

        // Badge
        QLabel *badge = new QLabel("// CLASSIFIED ACCESS //", this);
        badge->setGeometry(80, 90, 500, 20);
        badge->setStyleSheet
            (
                "font-family: 'Courier New', monospace;"
                "font-size: 15px;"
                "letter-spacing: 6px;"
                "color: #00dcff;"
                "background: transparent;"
                "font-weight: bold;"
                );

        // Main Title
        QLabel *title = new QLabel("CRIME RECORD\nMANAGEMENT\nSYSTEM", this);
        title->setGeometry(80, 115, 700, 250);
        title->setStyleSheet
            (
                "font-family: 'Courier New', monospace;"
                "font-size: 55px;"
                "font-weight: 900;"
                "color: white;"
                "background: transparent;"
                "line-height: 60px;"
                );

        // Subtitle
        QLabel *line = new QLabel("CLASSIFIED  SYSTEM  ACCESS  PORTAL", this);
        line->setGeometry(40, 300, 500, 400);
        line->setStyleSheet
            (
                "font-family: 'Courier New', monospace;"
                "font-size : 15px;"
                "letter-spacing : 5px;"
                "color : #c8eaff;"
                "background : transparent;"
                "font-weight : bold;"
                );

        // Welcome
        QLabel *welcome = new QLabel("WELCOME", this);
        welcome->setGeometry(980, 155, 560, 30);
        welcome->setStyleSheet
            (
                "font-family: 'Courier New', monospace;"
                "font-size : 30px;"
                "letter-spacing: 8px;"
                "font-weight : bold;"
                "color : #00eaff;"
                "background : transparent;"
                );

        // Identify Label
        QLabel *label = new QLabel("Identify yourself to gain system access.", this);
        label->setGeometry(980, 190, 560, 22);
        label->setStyleSheet
            (
                "font-family: 'Courier New', monospace;"
                "font-size : 18px;"
                "color : #c0dff5;"
                "font-weight : bold;"
                "background : transparent;"
                );

        // Admin Sign In Title
        QLabel *adminSignInTitle = new QLabel("OFFICER  SIGN IN", this);
        adminSignInTitle->setGeometry(1020, 253, 420, 28);
        adminSignInTitle->setStyleSheet
            (
                "font-family: 'Courier New', monospace;"
                "font-size     : 18px;"
                "font-weight   : bold;"
                "letter-spacing: 4px;"
                "color         : #eaf6ff;"
                "background    : transparent;"
                );
        adminSignInTitle->hide();

        // Admin Sign In Subtitle
        QLabel *adminSignInSubTitle = new QLabel("Enter your credentials to access the system", this);
        adminSignInSubTitle->setGeometry(1020, 285, 420, 18);
        adminSignInSubTitle->setStyleSheet
            (
                "font-family: 'Courier New', monospace;"
                "font-size  : 11px;"
                "color      : #eaf6ff;"
                "background : transparent;"
                );
        adminSignInSubTitle->hide();

        // User Sign In Title
        QLabel *userSignInTitle = new QLabel("USER  SIGN IN", this);
        userSignInTitle->setGeometry(1020, 285, 420, 26);
        userSignInTitle->setStyleSheet
            (
                "font-family: 'Courier New', monospace;"
                "font-size     : 17px;"
                "font-weight   : bold;"
                "letter-spacing: 4px;"
                "color         : #eaf6ff;"
                "background    : transparent;"
                );
        userSignInTitle->hide();

        // User Sign In Subtitle
        QLabel *userSignInSubTitle = new QLabel("Enter your credentials to continue", this);
        userSignInSubTitle->setGeometry(1020, 315, 420, 18);
        userSignInSubTitle->setStyleSheet
            (
                "font-family: 'Courier New', monospace;"
                "font-size : 11px;"
                "color : #eaf6ff;"
                "background : transparent;"
                );
        userSignInSubTitle->hide();

        // Create Account Title
        QLabel *createTitle = new QLabel("CREATE  USER  ACCOUNT", this);
        createTitle->setGeometry(1020, 285, 440, 26);
        createTitle->setStyleSheet
            (
                "font-family: 'Courier New', monospace;"
                "font-size     : 17px;"
                "font-weight   : bold;"
                "letter-spacing: 3px;"
                "color         : #eaf6ff;"
                "background    : transparent;"
                );
        createTitle->hide();

        // Create Account Subtitle
        QLabel *createSubTitle = new QLabel("Fill in the details to register your credentials", this);
        createSubTitle->setGeometry(1020, 315, 440, 18);
        createSubTitle->setStyleSheet
            (
                "font-family: 'Courier New', monospace;"
                "font-size  : 11px;"
                "color      : #eaf6ff;"
                "background : transparent;"
                );
        createSubTitle->hide();

        // Feature List
        const char *features[] =
            {
                "Stored Criminal Records ",
                "Court Proceeding ",
                "Creation and Modification of Records"
            };

        for (int i = 0; i < 3; i++)
        {
            QLabel *arr = new QLabel(QString("◆ ") + features[i], this);
            arr->setGeometry(80, 650 + i * 38, 550, 30);
            arr->setStyleSheet
                (
                    "font-family: 'Courier New', monospace;"
                    "font-size  : 14px;"
                    "color      : #d0eeff;"
                    "background : transparent;"
                    );
        }

        // Input Boxes
        adminEmail = new Box(1020, 315, 420, 40, " OFFICER ENTER YOUR ID/EMAIL ", this);
        adminEmail->hide();

        adminPassword = new Box(1020, 367, 420, 40, " ENTER YOUR PASSWORD", this);
        adminPassword->setEchoMode(QLineEdit::Password);
        adminPassword->hide();

        userEmail = new Box(1020, 350, 420, 40, " USER ENTER YOUR ID/EMAIL ", this);
        userEmail->hide();

        userPassword = new Box(1020, 400, 420, 40, " ENTER YOUR PASSWORD ", this);
        userPassword->setEchoMode(QLineEdit::Password);
        userPassword->hide();

        name = new Box(1020, 345, 420, 40, " ENTER YOUR NAME ", this);
        name->hide();

        confirmPassword = new Box(1020, 501, 420, 40, " CONFIRM PASSWORD ", this);
        confirmPassword->setEchoMode(QLineEdit::Password);
        confirmPassword->hide();

        createEmail = new Box(1020, 397, 420, 40, " USER ENTER YOUR ID/EMAIL ", this);
        createEmail->hide();

        createPassword = new Box(1020, 449, 420, 40, " ENTER YOUR PASSWORD", this);
        createPassword->setEchoMode(QLineEdit::Password);
        createPassword->hide();

        // Role Buttons
        user  = new Button("User",  30,  390, 130, 40, this);
        admin = new Button("Admin", 350, 390, 130, 40, this);

        // Action Buttons
        signIn = new Button(" Sign In ", 1020, 451, 420, 44, this);
        signIn->hide();

        signInTab = new Button(" Sign In ", 990, 240, 230, 34, this);
        signInTab->hide();

        createAccountTab = new Button(" Create Account ", 1240, 240, 230, 34, this);
        createAccountTab->hide();

        createAccount = new Button(" Create Account ", 1020, 557, 420, 44, this);
        createAccount->hide();

        // ── User Button ───────────────────────────────────────────────────────

        connect(user, &QPushButton::clicked, this, [=]()
                {
                    userSignInTitle->show();
                    userSignInSubTitle->show();
                    userAccount->show();
                    userEmail->show();
                    userPassword->show();
                    signIn->show();
                    signInTab->show();
                    createAccountTab->show();

                    adminAccount->hide();
                    adminEmail->hide();
                    adminPassword->hide();
                    adminSignInTitle->hide();
                    adminSignInSubTitle->hide();

                    name->hide();
                    confirmPassword->hide();
                    createEmail->hide();
                    createPassword->hide();
                    createAccount->hide();
                    createTitle->hide();
                    createSubTitle->hide();
                    userCreateAccount->hide();

                    isAdmin = false;
                }
                );

        // ── Admin Button ──────────────────────────────────────────────────────

        connect(admin, &QPushButton::clicked, this, [=]()
                {
                    adminSignInTitle->show();
                    adminSignInSubTitle->show();
                    adminAccount->show();
                    adminEmail->show();
                    adminPassword->show();
                    signIn->show();

                    userAccount->hide();
                    userEmail->hide();
                    userPassword->hide();
                    userSignInTitle->hide();
                    userSignInSubTitle->hide();

                    name->hide();
                    confirmPassword->hide();
                    createEmail->hide();
                    createPassword->hide();
                    createAccount->hide();
                    createTitle->hide();
                    createSubTitle->hide();
                    userCreateAccount->hide();
                    signInTab->hide();
                    createAccountTab->hide();

                    isAdmin = true;
                }
                );

        // ── Sign In Tab ───────────────────────────────────────────────────────

        connect(signInTab, &QPushButton::clicked, this, [=]()
                {
                    userSignInTitle->show();
                    userSignInSubTitle->show();
                    userAccount->show();
                    userEmail->show();
                    userPassword->show();
                    signIn->show();

                    adminAccount->hide();
                    adminEmail->hide();
                    adminPassword->hide();
                    adminSignInTitle->hide();
                    adminSignInSubTitle->hide();
                    userCreateAccount->hide();
                    name->hide();
                    confirmPassword->hide();
                    createEmail->hide();
                    createPassword->hide();
                    createAccount->hide();
                    createTitle->hide();
                    createSubTitle->hide();
                }
                );

        // ── Create Account Tab ────────────────────────────────────────────────

        connect(createAccountTab, &QPushButton::clicked, this, [=]()
                {
                    createTitle->show();
                    createSubTitle->show();
                    userCreateAccount->show();
                    name->show();
                    confirmPassword->show();
                    createEmail->show();
                    createPassword->show();
                    createAccount->show();

                    userAccount->hide();
                    userEmail->hide();
                    userPassword->hide();
                    userSignInTitle->hide();
                    userSignInSubTitle->hide();
                    signIn->hide();
                    adminAccount->hide();
                    adminEmail->hide();
                    adminPassword->hide();
                    adminSignInTitle->hide();
                    adminSignInSubTitle->hide();
                }
                );

        // ── Sign In Button ────────────────────────────────────────────────────

        connect(signIn, &QPushButton::clicked, this, [=]()
                {
                    if (isAdmin)
                    {
                        std::string enteredEmail    = adminEmail->text().toStdString();
                        std::string enteredPassword = adminPassword->text().toStdString();

                        if (enteredEmail.empty() || enteredPassword.empty())
                        {
                            QMessageBox::warning(this, "Error", "Please fill in all fields.");
                            return;
                        }

                        if (enteredEmail == "admin" && enteredPassword == "admin123")
                        {
                            Admin *menu = new Admin();
                            menu->setAttribute(Qt::WA_DeleteOnClose);
                            menu->showMaximized();
                            this->close();
                        }
                        else
                        {
                            QMessageBox::warning(this, "Access Denied", "Invalid admin credentials.");
                            adminEmail->clear();
                            adminPassword->clear();
                        }
                    }
                    else
                    {
                        std::string enteredEmail    = userEmail->text().toStdString();
                        std::string enteredPassword = userPassword->text().toStdString();

                        if (enteredEmail.empty() || enteredPassword.empty())
                        {
                            QMessageBox::warning(this, "Error", "Please fill in all fields.");
                            return;
                        }

                        if
                            (
                                enteredEmail.find('@') == std::string::npos ||
                                enteredEmail.find('.') == std::string::npos
                                )
                        {
                            QMessageBox::warning(this, "Error", "Please enter a valid email address.");
                            return;
                        }

                        User *menu = new User();
                        menu->setAttribute(Qt::WA_DeleteOnClose);
                        menu->showMaximized();
                        this->close();
                    }
                }
                );

        // ── Create Account Button ─────────────────────────────────────────────

        connect(createAccount, &QPushButton::clicked, this, [=]()
                {
                    std::string userName    = name->text().toStdString();
                    std::string userMail    = createEmail->text().toStdString();
                    std::string userPass    = createPassword->text().toStdString();
                    std::string userConfirm = confirmPassword->text().toStdString();

                    if (userName.empty())
                    {
                        QMessageBox::warning(this, "Error", "Name cannot be empty.");
                        return;
                    }

                    if
                        (
                            userMail.find('@') == std::string::npos ||
                            userMail.find('.') == std::string::npos
                            )
                    {
                        QMessageBox::warning(this, "Error", "Please enter a valid email address.");
                        return;
                    }

                    if (userPass.length() < 6)
                    {
                        QMessageBox::warning(this, "Error", "Password must be at least 6 characters.");
                        return;
                    }

                    if (userPass != userConfirm)
                    {
                        QMessageBox::warning(this, "Error", "Passwords do not match.");
                        return;
                    }

                    QMessageBox::information(this, "Success", "Account created. You may now sign in.");

                    name->clear();
                    createEmail->clear();
                    createPassword->clear();
                    confirmPassword->clear();
                }
                );
    }

    void resizeEvent(QResizeEvent *)
    {
        img->resize(size());
    }
};

#endif // INTERFACE2_H