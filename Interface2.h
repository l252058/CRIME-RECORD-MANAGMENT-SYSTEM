#ifndef INTERFACE2_H
#define INTERFACE2_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QString>

#include "common.h"
#include "file.h"
#include "validity.h"
#include "adminMenu.h"
#include "userMenu.h"

class AuthPage : public QWidget
{
private:

    QLabel * img;
    Button * user;
    Button * admin;
    Button * signIn;
    Button * signInTab;
    Button * createAccountTab;
    Button * createAccount;
    Card * adminAccount;
    Card * userAccount;
    Card * userCreateAccount;
    Box * adminEmail;
    Box * adminPassword;
    Box * userEmail;
    Box * userPassword;
    Box * name;
    Box * confirmPassword;
    Box * createEmail;
    Box * createPassword;
    bool isAdmin = false;

    void handleLogin()
    {
        QString email, pass;
        if (isAdmin)
        {
            email = adminEmail->text().trimmed();
            pass  = adminPassword->text();
        }
        else
        {
            email = userEmail->text().trimmed();
            pass  = userPassword->text();
        }

        if (email.isEmpty() || pass.isEmpty())
        {
            QMessageBox::warning(this, "Error", "Please fill in all fields.");
            return;
        }

        if (isAdmin)
        {
            if (FileHandler::loginAdmin(email, pass))
            {
                Admin * menu = new Admin(this);
                menu->setAttribute(Qt::WA_DeleteOnClose);
                menu->showMaximized();
                this->hide();
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
            EmailValidator emailValidator;
            emailValidator.setEmail(email.toStdString().c_str());

            if (!emailValidator.validate())
            {
                QMessageBox::warning(this, "Error", emailValidator.getMessage());
                return;
            }

            if (FileHandler::loginUser(email, pass))
            {
                User * menu = new User(this, email);
                menu->setAttribute(Qt::WA_DeleteOnClose);
                menu->showMaximized();
                this->hide();
            }
            else
            {
                QMessageBox::warning(this, "Access Denied", "Invalid email or password.");
                userPassword->clear();
            }
        }
    }

    void handleSignup()
    {
        QString userName = name->text().trimmed();
        QString userEmail = createEmail->text().trimmed();
        QString userPassword = createPassword->text();
        QString confirmUserPassword = confirmPassword->text();

        if (userPassword != confirmUserPassword)
        {
            QMessageBox::warning(this, "Error", "Passwords do not match!");
            return;
        }

        UsernameValidator usernameValidator;
        usernameValidator.setUsername(userName.toStdString().c_str());
        if (!usernameValidator.validate())
        {
            QMessageBox::warning(this, "Error", usernameValidator.getMessage());
            return;
        }

        EmailValidator emailValidator;
        emailValidator.setEmail(userEmail.toStdString().c_str());
        if (!emailValidator.validate())
        {
            QMessageBox::warning(this, "Error", emailValidator.getMessage());
            return;
        }

        PasswordValidator passwordValidator;
        passwordValidator.setPassword(userPassword.toStdString().c_str());
        if (!passwordValidator.validate())
        {
            QMessageBox::warning(this, "Password Too Weak", passwordValidator.getMessage());
            return;
        }

        if (FileHandler::saveUser(userName, userEmail, userPassword))
        {
            QMessageBox::information(this, "Account Created", "Account created successfully!\nYou may now sign in.");
            name->clear();
            createEmail->clear();
            createPassword->clear();
            confirmPassword->clear();
        }
        else
        {
            QMessageBox::warning(this, "Error", "An account with this email already exists.\nPlease sign in instead.");
        }
    }

public:

    AuthPage()
    {
        setWindowTitle("Crime Record Management System");
        setMinimumSize(900, 600);
        resize(1600, 1000);

        img = new QLabel(this);
        img->setPixmap(loadPixmap("backgroundTwo.png"));
        img->setScaledContents(true);
        img->setGeometry(0, 0, width(), height());

        adminAccount = new Card(980, 230, 500, 310, this);
        userAccount = new Card(980, 230, 500, 310, this);
        userCreateAccount = new Card(980, 230, 500, 400, this);

        adminAccount->hide();
        userAccount->hide();
        userCreateAccount->hide();

        QLabel * badge = new QLabel("// CLASSIFIED ACCESS //", this);
        badge->setGeometry(80, 90, 500, 20);
        badge->setStyleSheet
        (
            "font-family : 'Courier New', monospace;"
            "font-size : 15px;"
            "letter-spacing : 6px;"
            "color : #00dcff;"
            "background : transparent;"
            "font-weight : bold;"
        );

        QLabel * title = new QLabel("CRIME RECORD\nMANAGEMENT\nSYSTEM", this);
        title->setGeometry(80, 115, 700, 250);
        title->setStyleSheet
        (
            "font-family : 'Courier New', monospace;"
            "font-size : 55px;"
            "font-weight : 900;"
            "color : white;"
            "background : transparent;"
        );

        QLabel * line = new QLabel("CLASSIFIED  SYSTEM  ACCESS  PORTAL", this);
        line->setGeometry(40, 300, 500, 400);
        line->setStyleSheet
        (
            "font-family : 'Courier New', monospace;"
            "font-size : 15px;"
            "letter-spacing : 5px;"
            "color : #c8eaff;"
            "background : transparent;"
            "font-weight : bold;"
        );

        QLabel * welcome = new QLabel("WELCOME", this);
        welcome->setGeometry(980, 155, 560, 30);
        welcome->setStyleSheet
        (
            "font-family : 'Courier New', monospace;"
            "font-size : 30px;"
            "letter-spacing : 8px;"
            "font-weight : bold;"
            "color : #00eaff;"
            "background : transparent;"
        );

        QLabel * label = new QLabel("Identify yourself to gain system access.", this);
        label->setGeometry(980, 190, 560, 22);
        label->setStyleSheet
        (
            "font-family : 'Courier New', monospace;"
            "font-size : 18px;"
            "color : #c0dff5;"
            "font-weight : bold;"
            "background : transparent;"
        );

        QLabel * adminSignInTitle = new QLabel("OFFICER  SIGN IN", this);
        adminSignInTitle->setGeometry(1020, 253, 420, 28);
        adminSignInTitle->setStyleSheet
        (
            "font-family : 'Courier New', monospace;"
            "font-size : 18px;"
            "font-weight : bold;"
            "letter-spacing : 4px;"
            "color : #eaf6ff;"
            "background : transparent;"
        );
        adminSignInTitle->hide();

        QLabel * adminSignInSubTitle = new QLabel("Enter your credentials to access the system", this);
        adminSignInSubTitle->setGeometry(1020, 285, 420, 18);
        adminSignInSubTitle->setStyleSheet
        (
            "font-family : 'Courier New', monospace;"
            "font-size : 15px;"
            "color : #eaf6ff;"
            "font-weight : bold;"
            "background : transparent;"
        );
        adminSignInSubTitle->hide();

        QLabel * userSignInTitle = new QLabel("USER  SIGN IN", this);
        userSignInTitle->setGeometry(1020, 285, 420, 26);
        userSignInTitle->setStyleSheet
        (
            "font-family : 'Courier New', monospace;"
            "font-size : 17px;"
            "font-weight : bold;"
            "letter-spacing : 4px;"
            "color : #eaf6ff;"
            "background : transparent;"
        );
        userSignInTitle->hide();

        QLabel * userSignInSubTitle = new QLabel("Enter your credentials to continue", this);
        userSignInSubTitle->setGeometry(1020, 315, 420, 18);
        userSignInSubTitle->setStyleSheet
        (
            "font-family : 'Courier New', monospace;"
            "font-size : 15px;"
            "color : #eaf6ff;"
            "font-weight : bold;"
            "background : transparent;"
        );
        userSignInSubTitle->hide();

        QLabel * createTitle = new QLabel("CREATE  USER  ACCOUNT", this);
        createTitle->setGeometry(1020, 285, 440, 26);
        createTitle->setStyleSheet
        (
            "font-family : 'Courier New', monospace;"
            "font-size : 17px;"
            "font-weight : bold;"
            "letter-spacing : 3px;"
            "color : #eaf6ff;"
            "background : transparent;"
        );
        createTitle->hide();

        QLabel * createSubTitle = new QLabel("Fill in the details to register your credentials", this);
        createSubTitle->setGeometry(1020, 315, 440, 18);
        createSubTitle->setStyleSheet
        (
            "font-family : 'Courier New', monospace;"
            "font-size : 15px;"
            "font-weight : bold;"
            "color : #eaf6ff;"
            "background : transparent;"
        );
        createSubTitle->hide();

        const char * features[] =
        {
            "Stored Criminal Records ",
            "Court Proceeding ",
            "Creation and Modification of Records"
        };

        for (int i = 0; i < 3; i++)
        {
            QLabel * arr = new QLabel(QString("◆ ") + features[i], this);
            arr->setGeometry(80, 650 + i * 38, 550, 30);
            arr->setStyleSheet
            (
                "font-family : 'Courier New', monospace;"
                "font-size : 14px;"
                "color : #d0eeff;"
                "background : transparent;"
            );
        }

        adminEmail = new Box(1020, 315, 420, 40, " OFFICER ENTER YOUR ID/EMAIL ", this);
        adminPassword = new Box(1020, 367, 420, 40, " ENTER YOUR PASSWORD", this);
        adminPassword->setEchoMode(QLineEdit::Password);
        adminEmail->hide();
        adminPassword->hide();

        userEmail = new Box(1020, 350, 420, 40, " USER ENTER YOUR ID/EMAIL ", this);
        userPassword = new Box(1020, 400, 420, 40, " ENTER YOUR PASSWORD ", this);
        userPassword->setEchoMode(QLineEdit::Password);
        userEmail->hide();
        userPassword->hide();

        name = new Box(1020, 345, 420, 40, " ENTER YOUR NAME ", this);
        confirmPassword = new Box(1020, 501, 420, 40, " CONFIRM PASSWORD ", this);
        confirmPassword->setEchoMode(QLineEdit::Password);
        name->hide();
        confirmPassword->hide();

        createEmail = new Box(1020, 397, 420, 40, " USER ENTER YOUR ID/EMAIL ", this);
        createPassword = new Box(1020, 449, 420, 40, " ENTER YOUR PASSWORD", this);
        createPassword->setEchoMode(QLineEdit::Password);
        createEmail->hide();
        createPassword->hide();

        user = new Button(" User ", 30, 390, 130, 40, this);
        admin = new Button(" Admin ", 350, 390, 130, 40, this);
        signIn = new Button(" Sign In ", 1020, 451, 420, 44, this);
        signInTab = new Button(" Sign In ", 990, 240, 230, 34, this);
        createAccountTab = new Button(" Create Account ", 1240, 240, 230, 34, this);
        createAccount = new Button(" Create Account ", 1020, 557, 420, 44, this);

        signIn->setSound("signupButtonSound.mp3");
        createAccount->setSound("creataccountButtonSound.mp3");

        signIn->hide();
        signInTab->hide();
        createAccountTab->hide();
        createAccount->hide();

        ValidationPopup * namePopup = new ValidationPopup(this, "Name Requirements");
        namePopup->addRule("At least 3 characters", [](const QString & t)
           {
               return ValidationRules::hasMinimumLength(t, 3);
           }
        );
        namePopup->addRule("No leading or trailing spaces", [](const QString & t)
           {
               return ValidationRules::hasNoLeadingOrTrailingSpaces(t);
           }
        );
        namePopup->attachTo(name);

        ValidationPopup * createEmailPopup = new ValidationPopup(this, "Email Requirements");
        createEmailPopup->addRule("Contains @", [](const QString & t)
            {
              return ValidationRules::containsAtSymbol(t);
            }
        );
        createEmailPopup->addRule("Contains a dot after @", [](const QString & t)
            {
              return ValidationRules::containsDotAfterAt(t);
            }
        );
        createEmailPopup->addRule("No spaces", [](const QString & t)
            {
              return ValidationRules::hasNoSpaces(t);
            }
        );
        createEmailPopup->attachTo(createEmail);

        ValidationPopup * createPasswordPopup = new ValidationPopup(this, "Password Requirements");
        createPasswordPopup->addRule("At least 8 characters", [](const QString & t)
            {
              return ValidationRules::hasMinimumLength(t, 8);
            }
        );
        createPasswordPopup->addRule("At least one uppercase", [](const QString & t)
            {
              return ValidationRules::hasUppercase(t);
            }
        );
        createPasswordPopup->addRule("At least one lowercase", [](const QString & t)
            {
              return ValidationRules::hasLowercase(t);
            }
        );
        createPasswordPopup->addRule("At least one digit", [](const QString & t)
            {
              return ValidationRules::hasDigit(t);
            }
        );
        createPasswordPopup->addRule("At least one special char", [](const QString & t)
            {
                return ValidationRules::hasSpecialCharacter(t);
            }
        );
        createPasswordPopup->attachTo(createPassword);

        ValidationPopup * confirmPasswordPopup = new ValidationPopup(this, "Confirm Password");
        confirmPasswordPopup->addRule("Passwords match", [this](const QString & t)
            {
                return t == createPassword->text();
            }
        );
        confirmPasswordPopup->attachTo(confirmPassword);

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

        connect(signIn, &QPushButton::clicked, this, [=]()
            {
                handleLogin();
            }
        );

        connect(createAccount, &QPushButton::clicked, this, [=]()
            {
                handleSignup();
            }
        );
    }

    void resizeEvent(QResizeEvent *) override
    {
        img->resize(size());
    }
};

#endif