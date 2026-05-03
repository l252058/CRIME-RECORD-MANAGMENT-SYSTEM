#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>

#include "common.h"
#include "logout.h"


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
    Button *deleteButton;

public:

    ProfilePage()
    {
        setWindowTitle("Profile - CRIME RECORD MANAGEMENT SYSTEM");

        img = new QLabel(this);
        img->setPixmap(loadPixmap("backgroundThree.png"));
        img->setScaledContents(true);

        sideCard = new Card(0, 0, 320, 800, this);

        QLabel *title = new QLabel("CRIME RECORD MANAGEMENT\nSYSTEM", this);
        title->setGeometry(0, 30, 320, 60);
        title->setAlignment(Qt::AlignCenter);
        title->setStyleSheet
        (
            MONO +
            "font-size     : 13px;"
            "font-weight   : bold;"
            "letter-spacing: 3px;"
            "color         : #00eaff;"
            "background    : transparent;"
        );

        QLabel *lineOne = new QLabel(this);
        lineOne->setGeometry(30, 100, 260, 1);
        lineOne->setStyleSheet("background: rgba(0,200,255,0.30);");

        QLabel *tag = new QLabel("[ PROFILE  SETTINGS ]", this);
        tag->setGeometry(0, 110, 320, 22);
        tag->setAlignment(Qt::AlignCenter);
        tag->setStyleSheet
        (
            MONO +
            "font-size     : 10px;"
            "letter-spacing: 4px;"
            "color         : #ffcc44;"
            "background    : transparent;"
            "font-weight   : bold;"
        );

        QLabel *infoTitle = new QLabel("ACCOUNT  INFO", this);
        infoTitle->setGeometry(0, 148, 320, 20);
        infoTitle->setAlignment(Qt::AlignCenter);
        infoTitle->setStyleSheet
        (
            MONO +
            "font-size     : 10px;"
            "letter-spacing: 3px;"
            "color         : #7ab8e0;"
            "background    : transparent;"
        );

        QLabel *infoRole = new QLabel("ROLE", this);
        infoRole->setGeometry(30, 172, 270, 22);
        infoRole->setStyleSheet
        (
            MONO +
            "font-size     : 15px;"
            "letter-spacing: 4px;"
            "font-weight   : bold;"
            "color         : #ffcc44;"
            "background    : transparent;"
        );

        QLabel *infoStatus = new QLabel("STATUS", this);
        infoStatus->setGeometry(30, 200, 270, 22);
        infoStatus->setStyleSheet
        (
            MONO +
            "font-size     : 15px;"
            "letter-spacing: 4px;"
            "font-weight   : bold;"
            "color         : #44ff99;"
            "background    : transparent;"
        );

        QLabel *infoAccess = new QLabel("ACCESS", this);
        infoAccess->setGeometry(30, 228, 270, 22);
        infoAccess->setStyleSheet
        (
            MONO +
            "font-size     : 15px;"
            "letter-spacing: 4px;"
            "font-weight   : bold;"
            "color         : #00eaff;"
            "background    : transparent;"
        );

        QLabel *lineTwo = new QLabel(this);
        lineTwo->setGeometry(30, 264, 260, 1);
        lineTwo->setStyleSheet("background: rgba(0,200,255,0.20);");

        Button *backButton = new Button("  <- Back", 25, startY + 130, buttonWidth, buttonHeight, this);

        QLabel *pageTitle = new QLabel("PROFILE  SETTINGS", this);
        pageTitle->setGeometry(380, 40, 1180, 50);
        pageTitle->setStyleSheet
        (
            MONO +
            "font-size     : 32px;"
            "font-weight   : 900;"
            "letter-spacing: 6px;"
            "color         : #ffffff;"
            "background    : transparent;"
        );

        QLabel *pageSubtitle = new QLabel("Manage your account details and password", this);
        pageSubtitle->setGeometry(380, 95, 1180, 22);
        pageSubtitle->setStyleSheet
        (
            MONO +
            "font-size  : 15px;"
            "font-weight: bold;"
            "color      : #ffcc44;"
            "background : transparent;"
        );

        QLabel *headerLine = new QLabel(this);
        headerLine->setGeometry(380, 125, 1180, 1);
        headerLine->setStyleSheet("background: rgba(0,200,255,0.25);");

        QLabel *avatarCard = new QLabel(this);
        avatarCard->setGeometry(380, 140, 230, 90);
        avatarCard->setStyleSheet("background:rgba(0,20,50,0.85); border:1px solid #00eaff; border-radius:10px;");

        QLabel *avatarIcon = new QLabel("👤", this);
        avatarIcon->setGeometry(390, 150, 210, 44);
        avatarIcon->setAlignment(Qt::AlignCenter);
        avatarIcon->setStyleSheet("font-size:32px; background:transparent;");

        QLabel *avatarText = new QLabel("ACCOUNT", this);
        avatarText->setGeometry(390, 196, 210, 22);
        avatarText->setAlignment(Qt::AlignCenter);
        avatarText->setStyleSheet(MONO + "font-size:11px; letter-spacing:3px; color:#c0dff5; background:transparent;");

        new Card(380, 250, 860, 550, this);

        QLabel *detailsHeading = new QLabel("ACCOUNT  DETAILS", this);
        detailsHeading->setGeometry(400, 268, 820, 26);
        detailsHeading->setStyleSheet
        (
            MONO +
            "font-size   : 14px;"
            "font-weight : bold;"
            "color       : #00eaff;"
            "background  : transparent;"
        );

        QLabel *detailsLine = new QLabel(this);
        detailsLine->setGeometry(400, 300, 820, 1);
        detailsLine->setStyleSheet("background: rgba(0,200,255,0.20);");

        QLabel *nameLabel = new QLabel("Full Name", this);
        nameLabel->setGeometry(400, 316, 820, 20);
        nameLabel->setStyleSheet
        (
            MONO +
            "font-size   : 13px;"
            "font-weight : bold;"
            "color       : #a0d8f0;"
            "background  : transparent;"
        );

        nameBox = new Box(400, 340, 820, 40, "Enter your full name", this);

        QLabel *emailLabel = new QLabel("Email Address", this);
        emailLabel->setGeometry(400, 394, 820, 20);
        emailLabel->setStyleSheet
        (
            MONO +
            "font-size   : 13px;"
            "font-weight : bold;"
            "color       : #a0d8f0;"
            "background  : transparent;"
        );

        emailBox = new Box(400, 418, 820, 40, "Enter your email", this);

        QLabel *passHeading = new QLabel("CHANGE  PASSWORD", this);
        passHeading->setGeometry(400, 475, 820, 26);
        passHeading->setStyleSheet
        (
            MONO +
            "font-size   : 14px;"
            "font-weight : bold;"
            "color       : #ffcc44;"
            "background  : transparent;"
        );

        QLabel *passLine = new QLabel(this);
        passLine->setGeometry(400, 505, 820, 1);
        passLine->setStyleSheet("background: rgba(255,200,0,0.20);");

        QLabel *currentLabel = new QLabel("Current Password", this);
        currentLabel->setGeometry(400, 520, 820, 20);
        currentLabel->setStyleSheet
        (
            MONO +
            "font-size   : 13px;"
            "font-weight : bold;"
            "color       : #a0d8f0;"
            "background  : transparent;"
        );

        currentPassBox = new Box(400, 544, 820, 40, "Enter current password", this);
        currentPassBox->setEchoMode(QLineEdit::Password);

        QLabel *newLabel = new QLabel("New Password", this);
        newLabel->setGeometry(400, 598, 410, 20);
        newLabel->setStyleSheet
        (
            MONO +
            "font-size   : 13px;"
            "font-weight : bold;"
            "color       : #a0d8f0;"
            "background  : transparent;"
        );

        QLabel *confirmLabel = new QLabel("Confirm New Password", this);
        confirmLabel->setGeometry(820, 598, 410, 20);
        confirmLabel->setStyleSheet
        (
            MONO +
            "font-size   : 13px;"
            "font-weight : bold;"
            "color       : #a0d8f0;"
            "background  : transparent;"
        );

        newPassBox = new Box(400, 622, 400, 40, "Enter new password",   this);
        newPassBox->setEchoMode(QLineEdit::Password);

        confirmPassBox = new Box(820, 622, 400, 40, "Confirm new password", this);
        confirmPassBox->setEchoMode(QLineEdit::Password);

        feedback = new QLabel("", this);
        feedback->setGeometry(700, 725, 820, 22);
        feedback->setStyleSheet
        (
            MONO +
            "font-size  : 12px;"
            "color      : #00eaff;"
            "background : transparent;"
        );

        saveButton = new Button("  SAVE CHANGES", 400, 706, 200, 44, this);

        deleteButton = new Button("  DELETE ACCOUNT", 1000, 706, 220, 44, this);
        deleteButton->setStyleSheet
            (
            "QPushButton"
            "{"
                "background:rgba(120,0,0,0.60);"
                "color:#ffcccc;"
                "font-family:'Courier New',monospace;"
                "font-size:13px;"
                "font-weight:bold;"
                "letter-spacing:2px;"
                "border:1px solid rgba(255,80,80,0.50);"
                "border-radius:6px;"
                "text-align:left;"
                "padding-left:20px;"
            "}"
            "QPushButton:hover"
            "{"
                "background:rgba(180,0,0,0.80);"
                "border:1px solid #ff4444;"
                "color:#ffffff;"
            "}"
            "QPushButton:pressed"
            "{"
                "background:#5a0000;"
            "}"
            );

        connect(saveButton, &QPushButton::clicked, this, [=]()
                {
                    QString name    = nameBox->text().trimmed();
                    QString email   = emailBox->text().trimmed();
                    QString current = currentPassBox->text();
                    QString newPass = newPassBox->text();
                    QString confirm = confirmPassBox->text();

                    if (name.isEmpty() || email.isEmpty())
                    {
                        setFeedback("  Name and email cannot be empty.", "#ff6666");
                        return;
                    }

                    if (!newPass.isEmpty() && newPass != confirm)
                    {
                        setFeedback("  New passwords do not match.", "#ff6666");
                        return;
                    }

                    if (!newPass.isEmpty() && current.isEmpty())
                    {
                        setFeedback("  Enter your current password to change it.", "#ffcc44");
                        return;
                    }

                    setFeedback("  Changes saved successfully!", "#44ff99");
                    currentPassBox->clear();
                    newPassBox->clear();
                    confirmPassBox->clear();
                }
                );

        connect(deleteButton, &QPushButton::clicked, this, [=]()
                {
                    setFeedback("  Delete account is not available yet.", "#ff6666");
                }
                );

        connect(backButton, &QPushButton::clicked, this, [=]()
                {
                    this->close();
                }
                );
    }

    // ── Public Setters ────────────────────────────────────────────────────────

    void setUserName(const QString  &name)
    {
        nameBox->setText(name);
    }
    void setUserEmail(const QString &email)
    {
        emailBox->setText(email);
    }

    QString getUserName() const
    {
        return nameBox->text().trimmed();
    }
    QString getUserEmail() const
    {
        return emailBox->text().trimmed();
    }
    QString getCurrentPassword() const
    {
        return currentPassBox->text();
    }
    QString getNewPassword() const
    {
        return newPassBox->text();
    }

    Button *getSaveButton()
    {
        return saveButton;
    }
    Button *getDeleteButton()
    {
        return deleteButton;
    }

    void setFeedback(const QString &text, const QString &color)
    {
        feedback->setStyleSheet
            (
                MONO +
                "font-size  : 12px;"
                "color      : " + color + ";"
                "background : transparent;"
                );
        feedback->setText(text);
    }

    void resizeEvent(QResizeEvent *)
    {
        img->resize(size());
    }
};

#endif // PROFILE_H
