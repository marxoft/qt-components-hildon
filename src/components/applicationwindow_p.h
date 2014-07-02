#ifndef APPLICATIONWINDOW_P_H
#define APPLICATIONWINDOW_P_H

#include "window_p.h"

class ApplicationWindow : public Window
{
    Q_OBJECT

    Q_PROPERTY(bool quitApplicationWhenClosed READ quitApplicationWhenClosed WRITE setQuitApplicationWhenClosed NOTIFY quitApplicationWhenClosedChanged)

public:
    explicit ApplicationWindow(QWidget *parent = 0);

    inline static ApplicationWindow* instance() { return self; }

    bool quitApplicationWhenClosed() const;
    void setQuitApplicationWhenClosed(bool quit);

signals:
    void quitApplicationWhenClosedChanged();

private:
    static ApplicationWindow *self;
};

#endif // APPLICATIONWINDOW_P_H
