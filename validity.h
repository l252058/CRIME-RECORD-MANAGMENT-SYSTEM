#ifndef VALIDITY_H
#define VALIDITY_H

#include <cstring>
#include <QString>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <functional>
#include <QTimer>
#include <QVBoxLayout>

#ifndef MONO_FONT
#define MONO_FONT "font-family: 'Consolas', 'Monaco', 'Courier New', monospace;"
#endif

// ── Base Validator Classes ───────────────────────────────────────────────────

class Validator
{
protected:
    char* message = nullptr;

    void setMsg(const char* m)
    {
        delete[] message;
        message = new char[strlen(m) + 1];
        strncpy(message, m, strlen(m) + 1);
    }

public:
    Validator() { setMsg(""); }
    virtual ~Validator() { delete[] message; }
    virtual bool validate() = 0;
    const char* getMessage() const { return message; }
};

class EmailValidator : public Validator
{
private:
    char* email = nullptr;
public:
    ~EmailValidator() { delete[] email; }
    void setEmail(const char* input)
    {
        delete[] email;
        if (input) {
            email = new char[strlen(input) + 1];
            strncpy(email, input, strlen(input) + 1);
        } else email = nullptr;
        setMsg("");
    }
    bool validate() override
    {
        if (!email || strlen(email) == 0) { setMsg("Email is empty."); return false; }
        if (!strchr(email, '@')) { setMsg("Missing '@' symbol."); return false; }
        int len = strlen(email);
        if (len < 5 || (strcmp(email + len - 4, ".com") != 0 && strcmp(email + len - 4, ".net") != 0)) {
            setMsg("Email must end with .com or .net"); return false;
        }
        setMsg("Valid Email"); return true;
    }
};

class PasswordValidator : public Validator
{
private:
    char* pass = nullptr;
public:
    ~PasswordValidator() { delete[] pass; }
    void setPassword(const char* input)
    {
        delete[] pass;
        if (input) {
            pass = new char[strlen(input) + 1];
            strncpy(pass, input, strlen(input) + 1);
        } else pass = nullptr;
        setMsg("");
    }
    bool validate() override
    {
        if (!pass || strlen(pass) < 8) { setMsg("Password must be at least 8 characters."); return false; }
        bool hasUpper = false, hasDigit = false;
        for (int i = 0; pass[i] != '\0'; i++) {
            if (pass[i] >= 'A' && pass[i] <= 'Z') hasUpper = true;
            if (pass[i] >= '0' && pass[i] <= '9') hasDigit = true;
        }
        if (!hasUpper) { setMsg("Must have at least one UPPERCASE letter."); return false; }
        if (!hasDigit) { setMsg("Must have at least one digit (0-9)."); return false; }
        setMsg("Strong Password"); return true;
    }
};

class UsernameValidator : public Validator
{
private:
    char* user = nullptr;
public:
    ~UsernameValidator() { delete[] user; }
    void setUsername(const char* input)
    {
        delete[] user;
        if (input) {
            user = new char[strlen(input) + 1];
            strncpy(user, input, strlen(input) + 1);
        } else user = nullptr;
        setMsg("");
    }
    bool validate() override
    {
        if (!user) { setMsg("Username is empty."); return false; }
        int len = strlen(user);
        if (len < 3) { setMsg("Username too short (min 3)."); return false; }
        for (int i = 0; user[i] != '\0'; i++) {
            char c = user[i];
            bool isAlnum = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
            if (!isAlnum && c != '_') { setMsg("Only letters, numbers, and '_' allowed."); return false; }
        }
        setMsg("Valid Username"); return true;
    }
};

// ── Validation Rules Helper (For Create Account) ──────────────────────────────

class ValidationRules
{
public:
    static bool hasMinimumLength(const QString& t, int n) { return t.length() >= n; }
    static bool containsAtSymbol(const QString& t) { return t.contains('@'); }
    static bool containsDotAfterAt(const QString& t) 
    {
        int at = t.indexOf('@');
        return at != -1 && t.indexOf('.', at) != -1;
    }
    static bool hasNoSpaces(const QString& t) { return !t.contains(' '); }
    static bool hasNoLeadingOrTrailingSpaces(const QString& t) { return t.trimmed() == t; }
    static bool hasUppercase(const QString& t) 
    {
        for (QChar c : t) if (c.isUpper()) return true;
        return false;
    }
    static bool hasLowercase(const QString& t) 
    {
        for (QChar c : t) if (c.isLower()) return true;
        return false;
    }
    static bool hasDigit(const QString& t) 
    {
        for (QChar c : t) if (c.isDigit()) return true;
        return false;
    }
    static bool hasSpecialCharacter(const QString& t) 
    {
        QString special = "!@#$%^&*()_+-=[]{}|;:,.<>?";
        for (QChar c : t) if (special.contains(c)) return true;
        return false;
    }
};

// ── Real-time Validation Popup ─────────────────────────────────────────────────

class ValidationPopup : public QWidget
{
    struct Rule {
        QString text;
        std::function<bool(const QString&)> check;
        QLabel* label;
    };

    QVBoxLayout* layout;
    QLabel* titleLabel;
    QList<Rule> rules;
    QLineEdit* attachedField = nullptr;

    void updateRules(const QString& text)
    {
        bool allPassed = true;
        for (auto& rule : rules)
        {
            if (rule.check(text))
            {
                rule.label->setText("  \u2714  " + rule.text);
                rule.label->setStyleSheet("font-family:'Courier New',monospace; font-size:14px; font-weight:bold; color:#44ff99; background:transparent; border:none;");
            }
            else
            {
                rule.label->setText("  \u2718  " + rule.text);
                rule.label->setStyleSheet("font-family:'Courier New',monospace; font-size:14px; font-weight:bold; color:#ff5555; background:transparent; border:none;");
                allPassed = false;
            }
        }
        if (allPassed) hide();
    }

    void repositionNextTo(QLineEdit* field)
    {
        if (!field || !field->parentWidget()) return;
        QPoint globalPos = field->parentWidget()->mapToGlobal(field->pos());
        QPoint localPos = parentWidget() ? parentWidget()->mapFromGlobal(globalPos) : globalPos;
        
        int popupWidth = 300;
        int popupHeight = sizeHint().height();
        int x = localPos.x() - popupWidth - 10;
        int y = localPos.y() + (field->height() / 2) - (popupHeight / 2);
        
        if (y < 5) y = 5;
        if (x < 5) x = 5;
        setGeometry(x, y, popupWidth, popupHeight);
    }

public:
    explicit ValidationPopup(QWidget* parent, const QString& title = "Requirements") 
        : QWidget(parent, Qt::Widget)
    {
        setAttribute(Qt::WA_TransparentForMouseEvents, false);
        setStyleSheet("QWidget { background:rgba(3, 12, 35, 0.95); border:1px solid rgba(0, 234, 255, 0.35); border-radius:15px; }");
        
        layout = new QVBoxLayout(this);
        layout->setContentsMargins(14, 10, 14, 10);
        layout->setSpacing(4);
        
        titleLabel = new QLabel(title, this);
        titleLabel->setStyleSheet("font-family:'Courier New',monospace; font-size:14px; font-weight:bold; letter-spacing:2px; color:#00dcff; background:transparent; border:none; padding-bottom:4px;");
        layout->addWidget(titleLabel);
        
        hide();
        raise();
    }

    void addRule(const QString& ruleText, std::function<bool(const QString&)> checker)
    {
        Rule r;
        r.text = ruleText;
        r.check = checker;
        r.label = new QLabel("  \u2718  " + ruleText, this);
        r.label->setStyleSheet("font-family:'Courier New',monospace; font-size:14px; font-weight:bold; color:#ff5555; background:transparent; border:none; padding:1px 0;");
        layout->addWidget(r.label);
        rules.append(r);
        adjustSize();
    }

    void attachTo(QLineEdit* field)
    {
        attachedField = field;
        QObject::connect(field, &QLineEdit::textChanged, this, [this](const QString& text) {
            if (isVisible()) updateRules(text);
        });
        field->installEventFilter(this);
    }

protected:
    bool eventFilter(QObject* obj, QEvent* event) override
    {
        if (obj == attachedField)
        {
            if (event->type() == QEvent::FocusIn)
            {
                repositionNextTo(attachedField);
                updateRules(attachedField->text());
                bool allPassed = true;
                for (auto& rule : rules)
                {
                    if (!rule.check(attachedField->text())) { allPassed = false; break; }
                }
                if (!allPassed) show();
                raise();
            }
            else if (event->type() == QEvent::FocusOut)
            {
                hide();
            }
        }
        return QWidget::eventFilter(obj, event);
    }
};

#endif