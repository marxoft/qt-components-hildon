/*
 * Copyright (C) 2014 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 3, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef HEADERVIEW_P_H
#define HEADERVIEW_P_H

#include "anchors_p.h"
#include "modelindex_p.h"
#include <QHeaderView>
#include <QStringListModel>
#include <QDeclarativeParserStatus>
#include <qdeclarative.h>

class HeaderSectionPrivate;
class HeaderViewPrivate;

class HeaderSection : public QObject, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(QHeaderView::ResizeMode resizeMode READ resizeMode WRITE setResizeMode NOTIFY resizeModeChanged)
    Q_PROPERTY(int index READ index CONSTANT)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)

    Q_ENUMS(QHeaderView::ResizeMode)

    Q_INTERFACES(QDeclarativeParserStatus)

public:
    explicit HeaderSection(QObject *parent = 0);
    ~HeaderSection();

    QString text() const;
    void setText(const QString &text);

    int width() const;
    void setWidth(int width);

    QHeaderView::ResizeMode resizeMode() const;
    void setResizeMode(QHeaderView::ResizeMode mode);

    int index() const;

    bool isVisible() const;
    void setVisible(bool visible);

signals:
    void textChanged();
    void widthChanged();
    void resizeModeChanged();
    void indexChanged();
    void visibleChanged();
    void clicked();

protected:
    HeaderSection(HeaderSectionPrivate &dd, QObject *parent = 0);

    virtual void classBegin();
    virtual void componentComplete();

    QScopedPointer<HeaderSectionPrivate> d_ptr;

    Q_DECLARE_PRIVATE(HeaderSection)

    Q_PRIVATE_SLOT(d_func(), void _q_onSectionClicked(int))

private:
    friend class HeaderViewPrivate;

    Q_DISABLE_COPY(HeaderSection)
};

class HeaderView : public QHeaderView, public QDeclarativeParserStatus
{
    Q_OBJECT

    Q_PROPERTY(QWidget* parent READ parentWidget WRITE setParent NOTIFY parentChanged)
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(int width READ width WRITE setFixedWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setFixedHeight NOTIFY heightChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PRIVATE_PROPERTY(HeaderView::d_func(), Anchors* anchors READ anchors CONSTANT FINAL)
    Q_PROPERTY(AnchorLine left READ left CONSTANT FINAL)
    Q_PROPERTY(AnchorLine right READ right CONSTANT FINAL)
    Q_PROPERTY(AnchorLine top READ top CONSTANT FINAL)
    Q_PROPERTY(AnchorLine bottom READ bottom CONSTANT FINAL)
    Q_PROPERTY(AnchorLine horizontalCenter READ horizontalCenter CONSTANT FINAL)
    Q_PROPERTY(AnchorLine verticalCenter READ verticalCenter CONSTANT FINAL)
    Q_PRIVATE_PROPERTY(HeaderView::d_func(), QDeclarativeListProperty<QObject> data READ data)
    Q_PRIVATE_PROPERTY(HeaderView::d_func(), QDeclarativeListProperty<QWidget> children READ children)
    Q_PRIVATE_PROPERTY(HeaderView::d_func(), QDeclarativeListProperty<QObject> actions READ actions)
    Q_PRIVATE_PROPERTY(HeaderView::d_func(), QDeclarativeListProperty<HeaderSection> sections READ sections)
    Q_PRIVATE_PROPERTY(HeaderView::d_func(), bool visible READ qmlVisible WRITE setQmlVisible NOTIFY visibleChanged)
    Q_PRIVATE_PROPERTY(HeaderView::d_func(), bool focus READ hasFocus WRITE setFocus NOTIFY focusChanged)
    Q_PRIVATE_PROPERTY(HeaderView::d_func(), bool clickable READ isClickable WRITE setClickable NOTIFY clickableChanged)
    Q_PRIVATE_PROPERTY(HeaderView::d_func(), bool showSortIndicator READ isSortIndicatorShown WRITE setSortIndicatorShown NOTIFY showSortIndicatorChanged)
    Q_PRIVATE_PROPERTY(HeaderView::d_func(), bool highlightSections READ highlightSections WRITE setHighlightSections NOTIFY highlightSectionsChanged)
    Q_PRIVATE_PROPERTY(HeaderView::d_func(), bool stretchLastSection READ stretchLastSection WRITE setStretchLastSection NOTIFY stretchLastSectionChanged)
    Q_PRIVATE_PROPERTY(HeaderView::d_func(), bool cascadingSectionResizes READ cascadingSectionResizes WRITE setCascadingSectionResizes NOTIFY cascadingSectionResizesChanged)
    Q_PRIVATE_PROPERTY(HeaderView::d_func(), int defaultSectionSize READ defaultSectionSize WRITE setDefaultSectionSize NOTIFY defaultSectionSizeChanged)
    Q_PRIVATE_PROPERTY(HeaderView::d_func(), int minimumSectionSize READ minimumSectionSize WRITE setMinimumSectionSize NOTIFY minimumSectionSizeChanged)
    Q_PRIVATE_PROPERTY(HeaderView::d_func(), Qt::Alignment defaultAlignment READ defaultAlignment WRITE setDefaultAlignment NOTIFY defaultAlignmentChanged)
    Q_PRIVATE_PROPERTY(HeaderView::d_func(), QVariant currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    Q_PRIVATE_PROPERTY(HeaderView::d_func(), Style* style READ style WRITE setStyle RESET resetStyle)

    Q_INTERFACES(QDeclarativeParserStatus)

    Q_CLASSINFO("DefaultProperty", "data")

public:
    explicit HeaderView(QWidget *parent = 0);
    ~HeaderView();

    void setX(int x);
    void setY(int y);

    qreal opacity() const;
    void setOpacity(qreal opacity);

    AnchorLine left() const;
    AnchorLine right() const;
    AnchorLine top() const;
    AnchorLine bottom() const;
    AnchorLine horizontalCenter() const;
    AnchorLine verticalCenter() const;

signals:
    void parentChanged();
    void xChanged();
    void yChanged();
    void widthChanged();
    void heightChanged();
    void opacityChanged();
    void visibleChanged();
    void enabledChanged();
    void focusChanged();
    void labelsChanged();
    void currentIndexChanged();
    void clickableChanged();
    void showSortIndicatorChanged();
    void highlightSectionsChanged();
    void stretchLastSectionChanged();
    void cascadingSectionResizesChanged();
    void defaultSectionSizeChanged();
    void minimumSectionSizeChanged();
    void defaultAlignmentChanged();

protected:
    HeaderView(HeaderViewPrivate &dd, QWidget *parent = 0);

    virtual void changeEvent(QEvent *event);
    virtual void moveEvent(QMoveEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event);
    virtual void focusInEvent(QFocusEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);

    virtual void classBegin();
    virtual void componentComplete();

    QScopedPointer<HeaderViewPrivate> d_ptr;

    Q_DECLARE_PRIVATE(HeaderView)
    
    Q_PRIVATE_SLOT(d_func(), void _q_onStyleChanged())

private:
    Q_DISABLE_COPY(HeaderView)
};

class HeaderLabelModel : public QStringListModel
{
    Q_OBJECT

public:
    explicit HeaderLabelModel(QObject *parent = 0);
    explicit HeaderLabelModel(const QStringList &strings, QObject *parent = 0);

    int columnCount(const QModelIndex &parent) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    Q_DISABLE_COPY(HeaderLabelModel)
};

QML_DECLARE_TYPE(HeaderSection)
QML_DECLARE_TYPE(HeaderView)

#endif // HEADERVIEW_P_H
