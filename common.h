#ifndef COMMON_H
#define COMMON_H

#include <QApplication>
#include <QAudioOutput>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QLabel>
#include <QLineEdit>
#include <QMediaPlayer>
#include <QPixmap>
#include <QPushButton>
#include <QScrollArea>
#include <QString>
#include <QStringList>
#include <QTextEdit>
#include <QUrl>
#include <QVBoxLayout>
#include <QWidget>

const QString MONO = "font-family: 'Courier New', monospace; ";

void sorting(QList<QStringList>& list, int fieldIndex)
{
    int n = list.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (fieldIndex < list[j].size() && fieldIndex < list[j + 1].size())
            {
                if (list[j + 1][fieldIndex].trimmed().toLower() < list[j][fieldIndex].trimmed().toLower())
                {
                    qSwap(list[j], list[j + 1]);
                }
            }
        }
    }
}

class DataFormatter
{
public:
    static QString formatCrime(const QStringList& p)
    {
        if (p.size() < 5) return "";
        QString id = p[0].trimmed();
        QString location = p[1].trimmed();
        QString type = p[2].trimmed();
        QString desc = p[3].trimmed();
        QString status = p[4].trimmed();

        return "Case ID   : " + id + "\n" +
               "Location  : " + location + "\n" +
               "Type      : " + type + "\n" +
               "Desc      : " + desc + "\n" +
               "Status    : " + status + "\n" +
               "----------------------------------\n";
    }

    static QString formatOfficer(const QStringList& p)
    {
        if (p.size() < 4) return "";
        QString id = p[0].trimmed();
        QString name = p[1].trimmed();
        QString rank = p[2].trimmed();
        QString badge = p[3].trimmed();
        
        QString assigned;
        if (p.size() >= 5 && !p[4].trimmed().isEmpty())
        {
            assigned = p[4].trimmed();
        }
        else
        {
            assigned = "Unassigned";
        }

        return "  Officer ID : " + id + "\n" +
               "  Name       : " + name + "\n" +
               "  Rank       : " + rank + "\n" +
               "  Badge #    : " + badge + "\n" +
               "  Assigned   : " + assigned + "\n" +
               "  --------------------------------------------------\n";
    }

    static QString formatCourt(const QStringList& p)
    {
        if (p.size() < 4) return "";
        QString caseId  = p[0].trimmed();
        QString accused = p[1].trimmed();
        QString crime   = p[2].trimmed();
        QString status  = p[3].trimmed();

        return "  Case ID  : " + caseId + "\n" +
               "  Accused  : " + accused + "\n" +
               "  Crime    : " + crime + "\n" +
               "  Status   : " + status + "\n" +
               "  --------------------------------------------------\n";
    }

    static QString formatStatus(const QStringList& p)
    {
        if (p.size() < 5) return "";
        QString caseId   = p[0].trimmed();
        QString location = p[1].trimmed();
        QString type     = p[2].trimmed();
        QString status   = p[4].trimmed();

        return "  Case ID  : " + caseId + "\n" +
               "  Location : " + location + "\n" +
               "  Type     : " + type + "\n" +
               "  Status   : " + status + "\n" +
               "  --------------------------------------------------\n";
    }

    static QString formatReport(const QStringList& p)
    {
        if (p.size() < 5) return "";
        QString reportId = p[0].trimmed();
        QString user     = p[1].trimmed();
        QString caseRef  = p[2].trimmed();
        QString subject  = p[3].trimmed();
        QString dateTime = p[4].trimmed();

        return "  Report ID : " + reportId + "\n" +
               "  User      : " + user + "\n" +
               "  Case Ref  : " + caseRef + "\n" +
               "  Subject   : " + subject + "\n" +
               "  Date/Time : " + dateTime + "\n" +
               "  --------------------------------------------------\n";
    }
};


class SoundManager
{
public:
    static void play(const QString& soundFile)
    {
        QStringList paths;
        paths << "c:/Users/Ubaid Ullah/Documents/OOP_Project/" + soundFile;
        paths << QApplication::applicationDirPath() + "/" + soundFile;
        paths << QApplication::applicationDirPath() + "/../" + soundFile;
        paths << QApplication::applicationDirPath() + "/../../" + soundFile;
        paths << QApplication::applicationDirPath() + "/../../../" + soundFile;
        paths << QDir::currentPath() + "/" + soundFile;

        QString finalPath;
        for (const QString& p : paths)
        {
            if (QFile::exists(p))
            {
                finalPath = QFileInfo(p).absoluteFilePath();
                break;
            }
        }

        if (finalPath.isEmpty())
        {
            return;
        }

        static QMediaPlayer* player = new QMediaPlayer();
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        static QAudioOutput* audioOutput = new QAudioOutput();
        player->setAudioOutput(audioOutput);
        audioOutput->setVolume(1.0);
        player->setSource(QUrl::fromLocalFile(finalPath));
#else
        player->setVolume(100);
        player->setMedia(QUrl::fromLocalFile(finalPath));
#endif
        player->stop();
        player->play();
    }
};


class Card : public QWidget
{
public:
    Card(int x, int y, int w, int h, QWidget* parent) : QWidget(parent)
    {
        setGeometry(x, y, w, h);
        setStyleSheet
        (
            "background    : rgba(3, 12, 35, 0.95);"
            "border        : 1px solid rgba(0, 234, 255, 0.35);"
            "border-radius : 15px;"
        );
    }
};

class StatCard : public QWidget
{
    QLabel* numLabel;
public:
    StatCard(int x, int y, const QString& color, const QString& caption, QWidget* parent) 
        : QWidget(parent)
    {
        setGeometry(x, y, 230, 90);
        setStyleSheet
        (
            "background    : rgba(3, 12, 35, 0.95);"
            "border        : 1px solid rgba(0, 234, 255, 0.35);"
            "border-radius : 15px;"
        );

        numLabel = new QLabel("0", this);
        numLabel->setGeometry(10, 10, 210, 44);
        numLabel->setAlignment(Qt::AlignCenter);
        numLabel->setStyleSheet(MONO + QString("font-size:32px; font-weight:900; color:%1; background:transparent; border:none;").arg(color));

        QLabel* cap = new QLabel(caption, this);
        cap->setGeometry(10, 56, 210, 22);
        cap->setAlignment(Qt::AlignCenter);
        cap->setStyleSheet(MONO + "font-size:14px; letter-spacing:2px; color:#c0dff5; background:transparent; font-weight:bold; border:none;");
    }

    void setValue(const QString& val) { numLabel->setText(val); }
    void setValue(int val) { numLabel->setText(QString::number(val)); }
    void setText(const QString& val) { numLabel->setText(val); }
};

class Button : public QPushButton
{
private:
    QString soundFile = "clickSound.mp3";
public:
    Button(QString text, int x, int y, int w, int h, QWidget* parent) : QPushButton(text, parent)
    {
        setGeometry(x, y, w, h);
        setCursor(Qt::PointingHandCursor);
        connect(this, &QPushButton::clicked, [this]() { SoundManager::play(soundFile); });
        
        setStyleSheet(
            "QPushButton {"
            "    background     : qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #005f73, stop:1 #0a9396);"
            "    color          : #ffffff;"
            "    font-family    : 'Courier New', monospace;"
            "    font-size      : 18px;"
            "    font-weight    : bold;"
            "    letter-spacing : 2px;"
            "    border         : 1px solid #00eaff;"
            "    border-radius  : 15px;"
            "    text-align     : center;"
            "}"
            "QPushButton:hover   { background: #00eaff; color: #000000; border: 1px solid #ffffff; }"
            "QPushButton:pressed { background: #008b8b; }"
        );
    }
    void setSound(const QString& file) { soundFile = file; }
};

class BackButton : public Button
{
public:
    BackButton(int x, int y, int w, int h, QWidget* parent) : Button("Back", x, y, w, h, parent)
    {
        setSound("backButtonSound.mp3");
        setStyleSheet(
            "QPushButton {"
            "    background     : qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #1a2a44, stop:1 #2c3e50);"
            "    color          : #c0dff5;"
            "    font-family    : 'Courier New', monospace;"
            "    font-size      : 18px;"
            "    font-weight    : bold;"
            "    letter-spacing : 2px;"
            "    border         : 1px solid #34495e;"
            "    border-radius  : 15px;"
            "    text-align     : center;"
            "}"
            "QPushButton:hover   { background: #34495e; color: #ffffff; border: 1px solid #7ab8e0; }"
            "QPushButton:pressed { background: #15202b; }"
        );
    }
};

class ClearButton : public Button
{
public:
    ClearButton(QString text, int x, int y, int w, int h, QWidget* parent) : Button(text, x, y, w, h, parent)
    {
        setSound("clearButtonSound.mp3");
        setStyleSheet(
            "QPushButton {"
            "    background     : qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #8b0000, stop:1 #b22222);"
            "    color          : #ffffff;"
            "    font-family    : 'Courier New', monospace;"
            "    font-size      : 18px;"
            "    font-weight    : bold;"
            "    letter-spacing : 2px;"
            "    border         : 1px solid #ff4444;"
            "    border-radius  : 15px;"
            "    text-align     : center;"
            "}"
            "QPushButton:hover   { background: #ff4444; color: #ffffff; border: 1px solid #ffffff; }"
            "QPushButton:pressed { background: #5a0000; }"
        );
    }
};

class ColoredButton : public QPushButton
{
private:
    QString soundFile = "clickSound.mp3";
public:
    ColoredButton(QString text, int x, int y, int w, int h, const QString& color, QWidget* parent)
        : QPushButton(text, parent)
    {
        setGeometry(x, y, w, h);
        setCursor(Qt::PointingHandCursor);
        connect(this, &QPushButton::clicked, [this]() { SoundManager::play(soundFile); });

        setStyleSheet(QString(
            "QPushButton {"
            "    background     : rgba(3, 12, 35, 0.95);"
            "    color          : %1;"
            "    font-family    : 'Courier New', monospace;"
            "    font-size      : 18px;"
            "    font-weight    : bold;"
            "    letter-spacing : 2px;"
            "    border         : 1px solid %1;"
            "    border-radius  : 15px;"
            "    text-align     : center;"
            "}"
            "QPushButton:hover   { background: %1; color: #000000; }"
            "QPushButton:pressed { background: rgba(0, 40, 80, 0.95); }"
        ).arg(color));
    }
    void setSound(const QString& file) { soundFile = file; }
};


class Box : public QLineEdit
{
public:
    Box(int x, int y, int w, int h, QString placeholder, QWidget* parent) : QLineEdit(parent)
    {
        setPlaceholderText(placeholder);
        setGeometry(x, y, w, h);
        setStyleSheet(
            "QLineEdit {"
            "    background    : rgba(3, 12, 35, 0.95);"
            "    border        : 1px solid rgba(0, 234, 255, 0.35);"
            "    border-radius : 15px;"
            "    color         : #e0f4ff;"
            "    font-family   : 'Courier New', monospace;"
            "    font-weight   : bold;"
            "    font-size     : 16px;"
            "    padding       : 0 10px;"
            "}"
            "QLineEdit:focus { border: 1px solid #00eaff; background: rgba(0, 25, 65, 0.95); }"
        );
    }
};

class DescriptionBox : public QTextEdit
{
public:
    DescriptionBox(int x, int y, int w, int h, const QString& placeholder, QWidget* parent) 
        : QTextEdit(parent)
    {
        setPlaceholderText(placeholder);
        setGeometry(x, y, w, h);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setStyleSheet(
            "QTextEdit {"
            "    background    : rgba(3, 12, 35, 0.95);"
            "    border        : 1px solid rgba(0, 234, 255, 0.35);"
            "    border-radius : 15px;"
            "    color         : #e0f4ff;"
            "    font-family   : 'Courier New', monospace;"
            "    font-weight   : bold;"
            "    font-size     : 16px;"
            "    padding       : 8px;"
            "}"
            "QTextEdit:focus { border: 1px solid #00eaff; background: rgba(0, 25, 65, 0.95); }"
        );
    }
};

class RecordDisplay : public QScrollArea
{
    QLabel* textLabel;
public:
    RecordDisplay(int x, int y, int w, int h, QWidget* parent, const QString& placeholder = "") : QScrollArea(parent)
    {
        setGeometry(x, y, w, h);
        setWidgetResizable(true);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setStyleSheet(
            "QScrollArea {"
            "    background    : rgba(3, 12, 35, 0.95);"
            "    border        : 1px solid rgba(0, 234, 255, 0.35);"
            "    border-radius : 15px;"
            "}"
        );

        textLabel = new QLabel(this);
        textLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        textLabel->setWordWrap(true);
        textLabel->setText(placeholder);
        textLabel->setStyleSheet(MONO + "font-size:16px; font-weight:bold; color:#c0dff5; padding:15px; background:transparent; border:none;");
        
        setWidget(textLabel);
    }

    void setText(const QString& t) { textLabel->setText(t); }
    void clear() { textLabel->clear(); }
};


class FeedbackLabel : public QLabel
{
public:
    FeedbackLabel(int x, int y, int w, QWidget* parent) : QLabel(parent)
    {
        setGeometry(x, y, w, 22);
        setStyleSheet(MONO + "font-size:16px; color:#c0dff5; background:transparent;");
    }

    void showSuccess(const QString& msg)
    {
        setStyleSheet(MONO + "font-size:16px; color:#44ff99; background:transparent; font-weight:bold;");
        setText("  " + msg);
    }

    void showError(const QString& msg)
    {
        setStyleSheet(MONO + "font-size:16px; color:#ff6666; background:transparent; font-weight:bold;");
        setText("  " + msg);
    }

    void showNotice(const QString& msg)
    {
        setStyleSheet(MONO + "font-size:16px; color:#ffcc44; background:transparent; font-weight:bold;");
        setText("  " + msg);
    }

    void showInfo(const QString& msg)
    {
        setStyleSheet(MONO + "font-size:16px; color:#00eaff; background:transparent; font-weight:bold;");
        setText("  " + msg);
    }
};


class Background : public QLabel
{
public:
    Background(QWidget* p, const QString& fileName) : QLabel(p)
    {
        setGeometry(0, 0, 1600, 900);
        
        QPixmap bgPixmap;
        if (QFile::exists(fileName)) 
        {
            bgPixmap = QPixmap(fileName);
        } 
        else 
        {
            QStringList paths;
            paths << "c:/Users/Ubaid Ullah/Documents/OOP_Project/" + fileName;
            paths << QApplication::applicationDirPath() + "/" + fileName;
            paths << QApplication::applicationDirPath() + "/../" + fileName;
            paths << QApplication::applicationDirPath() + "/../../" + fileName;
            paths << QDir::currentPath() + "/" + fileName;
            paths << QDir::currentPath() + "/../" + fileName;
            paths << "./" + fileName;
            
            for (const QString& p : paths) 
            {
                if (QFile::exists(p)) 
                {
                    bgPixmap = QPixmap(p);
                    break;
                }
            }
        }
        
        setPixmap(bgPixmap);
        setScaledContents(true);
        lower();
        show();
    }
};

class Sidebar : public QWidget
{
public:
    Sidebar(QWidget* p, const QString& tagText) : QWidget(p)
    {
        new Card(0, 0, 320, 1000, this);

        QLabel* title = new QLabel("CRIME RECORD\nMANAGEMENT\nSYSTEM", this);
        title->setGeometry(10, 10, 300, 120);
        title->setAlignment(Qt::AlignCenter);
        title->setWordWrap(true);
        title->setStyleSheet(MONO + "font-size:20px; font-weight:bold; letter-spacing:1px; color:#00eaff; background:transparent;");

        QLabel* line = new QLabel(this);
        line->setGeometry(30, 110, 260, 1);
        line->setStyleSheet("background:rgba(0, 200, 255, 0.30);");

        QLabel* tag = new QLabel(tagText, this);
        tag->setGeometry(0, 120, 320, 30);
        tag->setAlignment(Qt::AlignCenter);
        tag->setStyleSheet(MONO + "font-size:20px; letter-spacing:4px; color:#ffcc44; font-weight:bold; background:transparent;");
    }
};

class PageHeader : public QWidget
{
public:
    PageHeader(QWidget* p, const QString& titleText, const QString& subText) : QWidget(p)
    {
        QLabel* title = new QLabel(titleText, this);
        title->setGeometry(380, 40, 1180, 50);
        title->setStyleSheet(MONO + "font-size:40px; font-weight:900; letter-spacing:6px; color:#ffffff; background:transparent;");

        QLabel* sub = new QLabel(subText, this);
        sub->setGeometry(380, 95, 1180, 22);
        sub->setStyleSheet(MONO + "font-size:18px; font-weight:bold; color:#7ab8e0; background:transparent;");

        QLabel* line = new QLabel(this);
        line->setGeometry(380, 125, 1180, 1);
        line->setStyleSheet("background:rgba(0, 200, 255, 0.25);");
    }
};

class Footer : public QLabel
{
public:
    Footer(QWidget* p) : QLabel("DEPARTMENT OF CRIMINAL JUSTICE    INTERNAL USE ONLY", p)
    {
        setGeometry(0, 872, 1600, 22);
        setAlignment(Qt::AlignCenter);
        setStyleSheet
        (
            MONO + 
            "font-size:14px; "
            "letter-spacing:4px; "
            "color:#7ab8e0; "
            "background:transparent; "
            "font-weight:bold;"
        );
    }
};

#endif
