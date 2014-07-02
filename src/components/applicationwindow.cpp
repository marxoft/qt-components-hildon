#include "applicationwindow_p.h"
#include "pagestack_p_p.h"
#include <QApplication>
#include <QDebug>

ApplicationWindow* ApplicationWindow::self = 0;

ApplicationWindow::ApplicationWindow(QWidget *parent) :
    Window(parent)
{
    if (!self) {
        self = this;
        PageStack::instance()->d_func()->stack.append(this);
    }
    else {
        qWarning() << "You should only create one instance of ApplicationWindow per application";
    }

    this->setAttribute(Qt::WA_Maemo5StackedWindow, true);
}

bool ApplicationWindow::quitApplicationWhenClosed() const {
    return QApplication::quitOnLastWindowClosed();
}

void ApplicationWindow::setQuitApplicationWhenClosed(bool quit) {
    if (quit != this->quitApplicationWhenClosed()) {
        QApplication::setQuitOnLastWindowClosed(quit);
        emit quitApplicationWhenClosedChanged();
    }
}
