#include "sharedtextbrowser.h"


SharedTextBrowser::SharedTextBrowser(QWidget *parent) : QTextBrowser(parent)
{
}

void SharedTextBrowser::appendText(const QString &text)
{
    append(text);
}

