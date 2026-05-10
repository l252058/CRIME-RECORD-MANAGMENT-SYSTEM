#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QMessageBox>

#include "common.h"
#include "file.h"
#include "validity.h"

class ProfilePage : public QWidget
{
private:

    QLabel *img;
    Card   *sideCard;
    Box    *nameBox;
    Box    *emailBox;
    Box    *currentPassBox;
    Box    *newPassBox;
    Box    *confirmPassBox;
    QLabel *feedback;
    Button *saveButton;
    QPushButton *deleteButton;

    QString loggedInEmail;

    void setFeedback(const QString &text, const QString &color)
    {
        feedback->setStyleSheet
        (
            MONO +
            "font-size  : 16px;"
            "color      : " + color + ";"
            "background : transparent;"
            "font-weight: bold;"
        );
        
        feedback->setText("  " + text);
    }

public:

    ProfilePage(const QString &email = "")
        : loggedInEmail(email)
    {
        setWindowTitle("Profile - CRIME RECORD MANAGEMENT SYSTEM");

        img = UI::setupBackground(this, "backgroundThree.png");

        sideCard = new Card(0, 0, 320, 900, this);

        QLabel *title = new QLabel("CRIME RECORD\nMANAGEMENT\nSYSTEM", this);
        title->setGeometry(10, 10, 300, 120);
        title->setAlignment(Qt::AlignCenter);
        title->setWordWrap(true);
        title->setStyleSheet
        (
            MONO +
            "font-size      : 20px;"
            "font-weight    : bold;"
            "letter-spacing : 1px;"
            "color          : #00eaff;"
            "background     : transparent;"
        );

        QLabel *lineOne = new QLabel(this);
        
        lineOne->setGeometry(30, 100, 260, 1);
        
        lineOne->setStyleSheet("background : rgba(0, 200, 255, 0.30);");

        QLabel *tag = new QLabel("[ PROFILE  SETTINGS ]", this);
        
        tag->setGeometry(0, 110, 320, 30);
        
        tag->setAlignment(Qt::AlignCenter);
        
        tag->setStyleSheet
        (
            MONO +
            "font-size      : 20px;"
            "letter-spacing : 4px;"
            "color          : #ffcc44;"
            "font-weight    : bold;"
            "background     : transparent;"
        );

        QLabel *infoTitle = new QLabel("ACCOUNT  INFO", this);
        
        infoTitle->setGeometry(0, 150, 320, 20);
        
        infoTitle->setAlignment(Qt::AlignCenter);
        
        infoTitle->setStyleSheet
        (
            MONO +
            "font-size      : 14px;"
            "letter-spacing : 3px;"
            "color          : #7ab8e0;"
            "background     : transparent;"
            "font-weight    : bold;"
        );

        QLabel *infoRole = new QLabel("ROLE :  USER", this);
        
        infoRole->setGeometry(30, 185, 270, 24);
        
        infoRole->setStyleSheet
        (
            MONO +
            "font-size      : 20px;"
            "letter-spacing : 4px;"
            "font-weight    : bold;"
            "color          : #ffcc44;"
            "background     : transparent;"
        );

        QLabel *infoStatus = new QLabel("STATUS :  ACTIVE", this);
        
        infoStatus->setGeometry(30, 215, 270, 24);
        
        infoStatus->setStyleSheet
        (
            MONO +
            "font-size      : 20px;"
            "letter-spacing : 4px;"
            "font-weight    : bold;"
            "color          : #44ff99;"
            "background     : transparent;"
        );

        QLabel *infoAccess = new QLabel("ACCESS :  LIMITED", this);
        
        infoAccess->setGeometry(30, 245, 270, 24);
        
        infoAccess->setStyleSheet
        (
            MONO +
            "font-size      : 18px;"
            "letter-spacing : 2px;"
            "font-weight    : bold;"
            "color          : #00eaff;"
            "background     : transparent;"
        );

        QLabel *lineTwo = new QLabel(this);
        
        lineTwo->setGeometry(30, 285, 260, 1);
        
        lineTwo->setStyleSheet("background : rgba(0, 200, 255, 0.20);");

        BackButton *bb = new BackButton(25, 300, 270, 44, this);
        bb->raise();
        connect(bb, &QPushButton::clicked, this, &QWidget::close);

        QLabel *pageTitle = new QLabel("PROFILE  SETTINGS", this);
        
        pageTitle->setGeometry(380, 40, 1180, 50);
        
        pageTitle->setStyleSheet
        (
            MONO +
            "font-size      : 36px;"
            "font-weight    : 900;"
            "letter-spacing : 6px;"
            "color          : #ffffff;"
            "background     : transparent;"
        );

        QLabel *pageSubtitle = new QLabel("Manage your account details and password", this);
        
        pageSubtitle->setGeometry(380, 95, 1180, 22);
        
        pageSubtitle->setStyleSheet
        (
            MONO +
            "font-size   : 18px;"
            "font-weight : bold;"
            "color       : #7ab8e0;"
            "background  : transparent;"
        );

        QLabel *headerLine = new QLabel(this);
        
        headerLine->setGeometry(380, 125, 1180, 1);
        
        headerLine->setStyleSheet("background : rgba(0, 200, 255, 0.25);");

        QLabel *avatarCard = new QLabel(this);
        
        avatarCard->setGeometry(380, 140, 230, 90);
        
        avatarCard->setStyleSheet
        (
            "background    : rgba(0, 8, 24, 0.98);"
            "border        : 1px solid #00eaff;"
            "border-radius : 10px;"
        );

        QLabel *avatarIcon = new QLabel("👤", this);
        
        avatarIcon->setGeometry(390, 150, 210, 44);
        
        avatarIcon->setAlignment(Qt::AlignCenter);
        
        avatarIcon->setStyleSheet
        (
            "font-size  : 32px;"
            "background : transparent;"
        );

        QLabel *avatarText = new QLabel("USER ACCOUNT", this);
        
        avatarText->setGeometry(390, 196, 210, 22);
        
        avatarText->setAlignment(Qt::AlignCenter);
        
        avatarText->setStyleSheet
        (
            MONO +
            "font-size      : 12px;"
            "letter-spacing : 3px;"
            "color          : #c0dff5;"
            "background     : transparent;"
            "font-weight    : bold;"
        );

        new Card(380, 250, 1140, 550, this);

        QLabel *detailsHeading = new QLabel("ACCOUNT  DETAILS", this);
        
        detailsHeading->setGeometry(410, 268, 1080, 28);
        
        detailsHeading->setStyleSheet
        (
            MONO +
            "font-size   : 18px;"
            "font-weight : bold;"
            "color       : #00eaff;"
            "background  : transparent;"
        );

        QLabel *detailsLine = new QLabel(this);
        
        detailsLine->setGeometry(410, 300, 1080, 1);
        
        detailsLine->setStyleSheet("background : rgba(0, 200, 255, 0.20);");

        QLabel *nameLabel = new QLabel("Full Name", this);
        
        nameLabel->setGeometry(410, 315, 500, 24);
        
        nameLabel->setStyleSheet
        (
            MONO +
            "font-size   : 20px;"
            "font-weight : bold;"
            "color       : #a0d8f0;"
            "background  : transparent;"
        );

        nameBox = new Box(410, 345, 1080, 42, "Enter your full name", this);

        QLabel *emailLabel = new QLabel("Email Address", this);
        
        emailLabel->setGeometry(410, 405, 500, 24);
        
        emailLabel->setStyleSheet
        (
            MONO +
            "font-size   : 20px;"
            "font-weight : bold;"
            "color       : #a0d8f0;"
            "background  : transparent;"
        );

        emailBox = new Box(410, 435, 1080, 42, "Email", this);
        emailBox->setReadOnly(true);
        
        emailBox->setStyleSheet
        (
            "QLineEdit"
            "{"
            "    background    : rgba(0, 10, 30, 0.70);"
            "    border        : 1px solid rgba(0, 200, 255, 0.20);"
            "    border-radius : 8px;"
            "    color         : #7ab8e0;"
            "    font-family   : 'Courier New', monospace;"
            "    font-size     : 16px;"
            "    font-weight   : bold;"
            "    padding       : 0 12px;"
            "}"
        );

        QLabel *passHeading = new QLabel("CHANGE  PASSWORD", this);
        
        passHeading->setGeometry(410, 495, 1080, 28);
        
        passHeading->setStyleSheet
        (
            MONO +
            "font-size   : 18px;"
            "font-weight : bold;"
            "color       : #ffcc44;"
            "background  : transparent;"
        );

        QLabel *passLine = new QLabel(this);
        
        passLine->setGeometry(410, 525, 1080, 1);
        
        passLine->setStyleSheet("background : rgba(255, 200, 0, 0.20);");

        QLabel *currentLabel = new QLabel("Current Password", this);
        
        currentLabel->setGeometry(410, 540, 500, 24);
        
        currentLabel->setStyleSheet
        (
            MONO +
            "font-size   : 20px;"
            "font-weight : bold;"
            "color       : #a0d8f0;"
            "background  : transparent;"
        );

        currentPassBox = new Box(410, 570, 1080, 42, "Enter your current password", this);
        currentPassBox->setEchoMode(QLineEdit::Password);

        QLabel *newLabel = new QLabel("New Password", this);
        
        newLabel->setGeometry(410, 630, 500, 24);
        
        newLabel->setStyleSheet
        (
            MONO +
            "font-size   : 20px;"
            "font-weight : bold;"
            "color       : #a0d8f0;"
            "background  : transparent;"
        );

        QLabel *confirmLabel = new QLabel("Confirm New Password", this);
        
        confirmLabel->setGeometry(960, 630, 500, 24);
        
        confirmLabel->setStyleSheet
        (
            MONO +
            "font-size   : 20px;"
            "font-weight : bold;"
            "color       : #a0d8f0;"
            "background  : transparent;"
        );

        newPassBox     = new Box(410, 660, 530, 42, "Enter new password",    this);
        newPassBox->setEchoMode(QLineEdit::Password);

        confirmPassBox = new Box(960, 660, 530, 42, "Confirm new password",  this);
        confirmPassBox->setEchoMode(QLineEdit::Password);

        feedback = new QLabel("", this);
        
        feedback->setGeometry(410, 715, 1080, 24);
        
        feedback->setStyleSheet
        (
            MONO +
            "font-size  : 16px;"
            "color      : #00eaff;"
            "background : transparent;"
            "font-weight: bold;"
        );

        saveButton   = new Button("SAVE CHANGES",   410, 745, 240, 44, this);
        
        deleteButton = new ClearButton("DELETE ACCOUNT", 1250, 745, 240, 44, this);



        if (!loggedInEmail.isEmpty())
        {
            emailBox->setText(loggedInEmail);
            
            QString storedName = FileHandler::getUserName(loggedInEmail);
            
            if (!storedName.isEmpty())
            {
                nameBox->setText(storedName);
            }
        }

        connect(saveButton, &QPushButton::clicked, this, [=]()
        {
            QString name    = nameBox->text().trimmed();
            QString current = currentPassBox->text();
            QString newPass = newPassBox->text();
            QString confirm = confirmPassBox->text();

            if (name.isEmpty())
            {
                setFeedback("Name cannot be empty.", "#ff6666");
                return;
            }

            if (!newPass.isEmpty() || !current.isEmpty() || !confirm.isEmpty())
            {
                if (current.isEmpty())
                {
                    setFeedback("Enter current password to change.", "#ffcc44");
                    return;
                }

                PasswordValidator pv;
                pv.setPassword(newPass.toStdString().c_str());
                
                if (!pv.validate())
                {
                    setFeedback(QString(pv.getMessage()), "#ff6666");
                    return;
                }

                if (newPass != confirm)
                {
                    setFeedback("Passwords do not match.", "#ff6666");
                    return;
                }

                bool ok = FileHandler::updateUserPassword(loggedInEmail, current, newPass);
                
                if (!ok)
                {
                    setFeedback("Current password is incorrect.", "#ff6666");
                    return;
                }

                currentPassBox->clear();
                newPassBox->clear();
                confirmPassBox->clear();
            }

            if (FileHandler::updateUserName(loggedInEmail, name))
            {
                setFeedback("Profile updated successfully!", "#44ff99");
            }
            else
            {
                setFeedback("Password updated. Name save failed.", "#ffcc44");
            }

            FileHandler::appendLog("USER", "Profile updated: " + loggedInEmail);
        });

        connect(deleteButton, &QPushButton::clicked, this, [=]()
        {
            setFeedback("Delete account is not available yet.", "#ff6666");
        });
    }

    void resizeEvent(QResizeEvent *) override
    {
        img->resize(size());
    }
};

#endif