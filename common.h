#ifndef COMMON_H
#define COMMON_H

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QDir>
#include <QCoreApplication>

const int buttonWidth  = 270;
const int buttonHeight = 48;
const int startY       = 155;
const int gap          = 10;

const QString MONO = "font-family: 'Courier New', monospace;";

// =============================================================================
//  loadPixmap — searches every likely folder automatically
// =============================================================================

inline QPixmap loadPixmap(const QString &filename)
{
    QStringList paths;

    // 1. Same folder as the .exe
    paths << QCoreApplication::applicationDirPath() + "/" + filename;

    // 2. One level up from .exe  (build folder → source folder)
    paths << QCoreApplication::applicationDirPath() + "/../" + filename;

    // 3. Two levels up  (shadow build goes two levels up to reach source)
    paths << QCoreApplication::applicationDirPath() + "/../../" + filename;

    // 4. Three levels up  (some Qt shadow build layouts)
    paths << QCoreApplication::applicationDirPath() + "/../../../" + filename;

    // 5. Current working directory
    paths << QDir::currentPath() + "/" + filename;

    // 6. One level up from working directory
    paths << QDir::currentPath() + "/../" + filename;

    for (const QString &path : paths)
    {
        QPixmap pix(path);
        if (!pix.isNull())
            return pix;
    }

    // Nothing found — return empty pixmap
    return QPixmap();
}

// =============================================================================
//  Card — dark translucent panel
// =============================================================================

class Card : public QWidget
{
public:

    Card(int a, int b, int c, int d, QWidget *parent) : QWidget(parent)
    {
        setGeometry(a, b, c, d);
        setStyleSheet
            (
                "background   : rgba(3, 12, 35, 0.92);"
                "border       : 1px solid rgba(0, 200, 255, 0.35);"
                "border-radius: 12px;"
                );
    }
};

// =============================================================================
//  Button — teal gradient push button
// =============================================================================

class Button : public QPushButton
{
public:

    Button(QString text, int a, int b, int c, int d, QWidget *parent) : QPushButton(text, parent)
    {
        setGeometry(a, b, c, d);
        setStyleSheet
            (
                "QPushButton"
                "{"
                "    background   : qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                "                   stop:0 #004d60, stop:1 #007a8a);"
                "    color        : #e0f8ff;"
                "    font-family  : 'Courier New', monospace;"
                "    font-size    : 13px;"
                "    font-weight  : bold;"
                "    letter-spacing: 3px;"
                "    border       : 1px solid rgba(0, 210, 240, 0.60);"
                "    border-radius: 6px;"
                "}"
                "QPushButton:hover"
                "{"
                "    background   : qlineargradient(x1:0, y1:0, x2:1, y2:0,"
                "                   stop:0 #009ab0, stop:1 #00c8d8);"
                "    border       : 2px solid #00eeff;"
                "    color        : #ffffff;"
                "}"
                "QPushButton:pressed"
                "{"
                "    background   : #003a45;"
                "}"
                );
        setCursor(Qt::PointingHandCursor);
    }
};

// =============================================================================
//  Box — styled QLineEdit input field
// =============================================================================

class Box : public QLineEdit
{
public:

    Box(int a, int b, int c, int d, QString text, QWidget *parent) : QLineEdit(parent)
    {
        setPlaceholderText(text);
        setGeometry(a, b, c, d);
        setStyleSheet
            (
                "QLineEdit"
                "{"
                "    background    : rgba(0, 15, 45, 0.88);"
                "    border        : 1px solid rgba(0, 200, 255, 0.40);"
                "    border-radius : 5px;"
                "    color         : #e0f4ff;"
                "    font-family   : 'Courier New', monospace;"
                "    font-size     : 13px;"
                "    padding       : 0 10px;"
                "}"
                "QLineEdit:focus"
                "{"
                "    border     : 1px solid #00eaff;"
                "    background : rgba(0, 25, 65, 0.95);"
                "}"
                );
    }
};

#endif // COMMON_H