#ifndef SHAREDTEXTBROWSER_H
#define SHAREDTEXTBROWSER_H

#include <QMainWindow>
#include <QTextBrowser>

class SharedTextBrowser : public QTextBrowser
{
    Q_OBJECT

public:
    SharedTextBrowser(QWidget *parent = nullptr);

public slots:
    void appendText(const QString &text);
};

#endif // SHAREDTEXTBROWSER_H
