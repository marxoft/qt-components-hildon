/*
 * Copyright (C) 2015 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "qchhomescreenwidget.h"
#include "qchcloseevent.h"
#include "qchgraphicsview.h"
#include <QDeclarativeItem>
#include <QDeclarativeInfo>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <QCoreApplication>
#include <QSocketNotifier>
#include <QPointer>
#include <QUuid>
#include <QX11Info>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

static QCoreApplication::EventFilter oldEventFilter;
static QList<QchHomescreenWidget*> allDesktopItems;

static Atom atomByName(const char *name) {
    Atom atom = XInternAtom(QX11Info::display(), name, False);
    
    if (!atom) {
        qWarning("Unable to obtain %s atom. This class requires a running Hildon session.", name);
    }

    return atom;
}

enum HomescreenAtoms {
    HildonAppletId               = 0,
    NetWmWindowType              = 1,
    Utf8String                   = 2,
    HildonTypeHomeApplet         = 3,
    HildonAppletSettings         = 4,
    HildonAppletShowSettings     = 5,
    HildonAppletOnCurrentDesktop = 6,
    EnumCount                    = 7
};

static Atom hsAtoms[EnumCount] = { 0, 0, 0, 0, 0, 0, 0 };

static void initAtoms() {
    hsAtoms[HildonAppletId] = atomByName("_HILDON_APPLET_ID");
    hsAtoms[NetWmWindowType] = atomByName("_NET_WM_WINDOW_TYPE");
    hsAtoms[Utf8String] = atomByName("UTF8_STRING");
    hsAtoms[HildonTypeHomeApplet] = atomByName("_HILDON_WM_WINDOW_TYPE_HOME_APPLET");
    hsAtoms[HildonAppletSettings] = atomByName("_HILDON_APPLET_SETTINGS");
    hsAtoms[HildonAppletShowSettings] = atomByName("_HILDON_APPLET_SHOW_SETTINGS");
    hsAtoms[HildonAppletOnCurrentDesktop] = atomByName("_HILDON_APPLET_ON_CURRENT_DESKTOP");
}

bool qt_sendSpontaneousEvent(QObject *receiver, QEvent *event) {
    return QCoreApplication::sendSpontaneousEvent(receiver, event);
}

class QchHomescreenWidgetPrivate
{

public:
    QchHomescreenWidgetPrivate(QchHomescreenWidget *parent) :
        q_ptr(parent),
        view(0),
        root(0),
        socketNotifier(0),
        complete(false),
        isOnCurrentHomescreen(true),
        settingsAvailable(false),
        writePipe(-1)
    {
    }
    
    ~QchHomescreenWidgetPrivate() {
        delete root;
    }
    
    static void children_append(QDeclarativeListProperty<QDeclarativeItem> *list, QDeclarativeItem *item) {        
        if (!item) {
            return;
        }
        
        if (QchHomescreenWidget *widget = qobject_cast<QchHomescreenWidget*>(list->object)) {
            if (QDeclarativeItem *root = widget->d_func()->root) {
                item->setParentItem(root);
            }
        }
    }
    
    static void data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {        
        if (!obj) {
            return;
        }
        
        if (QchHomescreenWidget *widget = qobject_cast<QchHomescreenWidget*>(list->object)) {
            if (obj->isWidgetType()) {
                obj->setParent(widget);
            }
            else if (QDeclarativeItem *root = widget->d_func()->root) {
                obj->setParent(root);
                
                if (QDeclarativeItem *item = qobject_cast<QDeclarativeItem*>(obj)) {
                    item->setParentItem(root);
                }
            }
        }
    }
    
    static bool applicationEventFilter(void *message, long *result) {
        static QPointer<QWidget> lastMouseWidget;
        bool retval = false;

        if (oldEventFilter) {
            retval = oldEventFilter(message, result);
        }

        if (allDesktopItems.isEmpty()) {
            return retval;
        }

        XEvent *ev = reinterpret_cast<XEvent *>(message);

        // Generate a mouse release for a leave Notify (as we don't get the mouse release from X11)
        if (ev->type == ButtonPress) {
            QPoint globalPos( ev->xbutton.x_root, ev->xbutton.y_root);
            QWidget *widget = QWidget::find((WId)ev->xany.window);
            
            if (widget) {
                lastMouseWidget = widget->childAt(widget->mapFromGlobal(globalPos));
                
                if (!lastMouseWidget) {
                    lastMouseWidget = widget;
                }
            }

        }
        else if (ev->type == ButtonRelease) {
            lastMouseWidget = 0;
        }
        else if (ev->type == LeaveNotify) {
            if (lastMouseWidget) {
                // create a mouse up event that lies in Nirvana.
                QPoint pos(-1000, -1000);
                QMouseEvent e(QEvent::MouseButtonRelease, pos, pos, Qt::LeftButton, Qt::NoButton, Qt::NoModifier);
                qt_sendSpontaneousEvent(lastMouseWidget, &e);
                lastMouseWidget = 0;
           }

        }
        else if (ev->type == ClientMessage) {
            XClientMessageEvent *cm = (XClientMessageEvent *)message;
            
            if (cm->message_type == hsAtoms[HildonAppletShowSettings]) {
                for (int i = 0; i < allDesktopItems.size(); ++i) {
                    if (allDesktopItems.at(i)->winId() == ev->xproperty.window) {
                        emit allDesktopItems.at(i)->settingsRequested();
                        retval = true;
                    }
                }
            }
        }
        else if (ev->type == PropertyNotify) {
            if (ev->xproperty.atom == hsAtoms[HildonAppletOnCurrentDesktop]) {
                for (int i = 0; i < allDesktopItems.size(); ++i) {
                    if (allDesktopItems.at(i)->winId() == ev->xproperty.window) {
                        allDesktopItems.at(i)->d_func()->isOnCurrentHomescreen = (ev->xproperty.state == 0);
                        emit allDesktopItems.at(i)->isOnCurrentHomescreenChanged();
                        retval = true;
                    }
                }
            }
        }

        return retval;
    }
    
    void initGraphicsView() {
        Q_Q(QchHomescreenWidget);
        view = new QchGraphicsView(q);
        root = new QDeclarativeItem;
        
        view->addItem(root);
        view->setStyleSheet("background:transparent");
        
        QVBoxLayout *vbox = new QVBoxLayout(q);
        vbox->addWidget(view);
    }
    
    void initWidget() {
        Q_Q(QchHomescreenWidget);
        Q_ASSERT(q->isWindow());
        
        complete = true;
        refCount++;
        
        if (pluginId.isEmpty()) {
            pluginId = QUuid::createUuid().toString().remove("{").remove("}").remove("-");
        }
                
        if (!hsAtoms[0]) {
            initAtoms();
        }

        Display *display = QX11Info::display();

        if (!pluginId.isEmpty()) {
            XChangeProperty(display,
                            q->winId(),
                            hsAtoms[HildonAppletId],
                            hsAtoms[Utf8String], 8, PropModeReplace,
                            reinterpret_cast<const unsigned char *>(pluginId.toUtf8().constData()),
                            pluginId.toUtf8().length());
        }
    
        if (writePipe != -1) {
            socketNotifier = new QSocketNotifier(writePipe, QSocketNotifier::Exception, q);
            q->connect(socketNotifier, SIGNAL(activated(int)), q, SLOT(_q_socketException()));
        }

        // set the X11 atoms to flag our widget as homescreen widget
        if (!pluginId.isEmpty()) {
            XChangeProperty(display,
                            q->winId(),
                            hsAtoms[NetWmWindowType],
                            XA_ATOM, 32, PropModeReplace,
                            reinterpret_cast<const unsigned char *>(&hsAtoms[HildonTypeHomeApplet]),
                            1);

            updateStatus();

            // --- make this window a child of root
            XSetTransientForHint(display, q->winId(),
                                 RootWindow(display, q->x11Info().screen()));

            // --- add an x11 event filter
            if (refCount == 1) {
                oldEventFilter = QCoreApplication::instance()->setEventFilter(applicationEventFilter);
            }

            allDesktopItems.append(q);

            // --- set WM input hints indicating that we don't want focus events
            XWMHints *h = XGetWMHints(display, q->winId());
            XWMHints wm_hints;
            
            if (!h) {
                memset(&wm_hints, 0, sizeof(wm_hints)); // make valgrind happy
                h = &wm_hints;
            }
            
            h->flags |= InputHint;
            h->input = False;

            XSetWMHints(display, q->winId(), h);
            
            if (h != &wm_hints) {
                XFree(h);
            }

            q->setMouseTracking(true);
            q->show();
        }
    }
    
    void updateStatus() {
        if (pluginId.isEmpty()) {
            return;
        }

        Q_Q(QchHomescreenWidget);
        Display *display = QX11Info::display();

        // Set or remove settings property
        if (settingsAvailable) {
            XChangeProperty(display,
                            q->winId(),
                            hsAtoms[HildonAppletSettings],
                            XA_CARDINAL, 32, PropModeReplace,
                            (const unsigned char *) &(settingsAvailable), 1);
        }
        else {
            XDeleteProperty(display,
                            q->winId(),
                            hsAtoms[HildonAppletSettings]);
        }
    }
    
    void _q_onSocketException() {
        Q_Q(QchHomescreenWidget);
        socketNotifier->setEnabled(false);
        q->close();
    }
        
    QchHomescreenWidget *q_ptr;
        
    QchGraphicsView *view;
    QDeclarativeItem *root;
    
    QSocketNotifier *socketNotifier;
    
    bool complete;
        
    bool isOnCurrentHomescreen;
    
    QString pluginId;
    
    bool settingsAvailable;
    
    int writePipe;
    
    static int refCount;
    
    Q_DECLARE_PUBLIC(QchHomescreenWidget)
};

int QchHomescreenWidgetPrivate::refCount = 0;

QchHomescreenWidget::QchHomescreenWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new QchHomescreenWidgetPrivate(this))
{
    Q_D(QchHomescreenWidget);
    d->initGraphicsView();
    setAttribute(Qt::WA_TranslucentBackground, true);
}

QchHomescreenWidget::~QchHomescreenWidget() {
    allDesktopItems.removeOne(this);
}

QDeclarativeListProperty<QDeclarativeItem> QchHomescreenWidget::children() {
    return QDeclarativeListProperty<QDeclarativeItem>(this, 0, QchHomescreenWidgetPrivate::children_append);
}

QDeclarativeListProperty<QObject> QchHomescreenWidget::data() {
    return QDeclarativeListProperty<QObject>(this, 0, QchHomescreenWidgetPrivate::data_append);
}

QString QchHomescreenWidget::pluginId() const {
    Q_D(const QchHomescreenWidget);
    return d->pluginId;
}

void QchHomescreenWidget::setPluginId(const QString &id) {
    if (id != pluginId()) {
        Q_D(QchHomescreenWidget);
        
        if (d->complete) {
            qmlInfo(this) << tr("pluginId cannot be set after component is completed.");
        }
        else {
            d->pluginId = id;
        }
    }
}

bool QchHomescreenWidget::isOnCurrentHomescreen() const {
    Q_D(const QchHomescreenWidget);
    return d->isOnCurrentHomescreen;
}

bool QchHomescreenWidget::settingsAvailable() const {
    Q_D(const QchHomescreenWidget);
    return d->settingsAvailable;
}

void QchHomescreenWidget::setSettingsAvailable(bool enabled) {
    if (enabled != settingsAvailable()) {
        Q_D(QchHomescreenWidget);
        d->settingsAvailable = enabled;
        emit settingsAvailableChanged();
    }
}

int QchHomescreenWidget::writePipe() const {
    Q_D(const QchHomescreenWidget);
    return d->writePipe;
}

void QchHomescreenWidget::setWritePipe(int pipe) {
    if (pipe != writePipe()) {
        Q_D(QchHomescreenWidget);
        
        if (d->complete) {
            qmlInfo(this) << tr("writePipe cannot be set after component is completed.");
        }
        else {
            d->writePipe = pipe;
        }
    }
}

void QchHomescreenWidget::classBegin() {}

void QchHomescreenWidget::componentComplete() {
    Q_D(QchHomescreenWidget);
    d->initWidget();
}

void QchHomescreenWidget::showEvent(QShowEvent *e) {
    QWidget::showEvent(e);
    emit visibleChanged();
}

void QchHomescreenWidget::hideEvent(QHideEvent *e) {
    QWidget::hideEvent(e);
    emit visibleChanged();
}

void QchHomescreenWidget::closeEvent(QCloseEvent *e) {
    QchCloseEvent ce;
    emit closing(&ce);
    
    if (ce.isAccepted()) {
        QWidget::closeEvent(e);
        deleteLater();
    }
    else {
        e->ignore();
    }
}

void QchHomescreenWidget::resizeEvent(QResizeEvent *e) {
    QWidget::resizeEvent(e);
    emit sizeChanged();
}

#include "moc_qchhomescreenwidget.cpp"
