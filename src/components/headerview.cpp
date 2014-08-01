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

#include "headerview_p.h"
#include "headerview_p_p.h"
#include <QMoveEvent>
#include <QResizeEvent>
#include <QActionGroup>
#include <QGraphicsOpacityEffect>

HeaderSection::HeaderSection(QObject *parent) :
    QObject(parent),
    d_ptr(new HeaderSectionPrivate(this))
{
}

HeaderSection::HeaderSection(HeaderSectionPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
}

HeaderSection::~HeaderSection() {}

QString HeaderSection::text() const {
    Q_D(const HeaderSection);

    return d->text;
}

void HeaderSection::setText(const QString &text) {
    if (text != this->text()) {
        Q_D(HeaderSection);
        d->text = text;
        emit textChanged();

        if (!d->complete) {
            if (HeaderView *view = qobject_cast<HeaderView*>(this->parent())) {
                view->model()->setData(view->model()->index(this->index(), 0), this->text());
            }
        }
    }
}

int HeaderSection::width() const {
    Q_D(const HeaderSection);

    return d->width;
}

void HeaderSection::setWidth(int width) {
    if (width != this->width()) {
        Q_D(HeaderSection);
        d->width = width;
        emit widthChanged();

        if (d->complete) {
            if (HeaderView *view = qobject_cast<HeaderView*>(this->parent())) {
                view->resizeSection(this->index(), width);
            }
        }
    }
}

QHeaderView::ResizeMode HeaderSection::resizeMode() const {
    Q_D(const HeaderSection);

    return d->resizeMode;
}

void HeaderSection::setResizeMode(QHeaderView::ResizeMode mode) {
    if (mode != this->resizeMode()) {
        Q_D(HeaderSection);
        d->resizeMode = mode;
        emit resizeModeChanged();

        if (d->complete) {
            if (HeaderView *view = qobject_cast<HeaderView*>(this->parent())) {
                view->setResizeMode(this->index(), mode);
            }
        }
    }
}

int HeaderSection::index() const {
    Q_D(const HeaderSection);

    return d->index;
}

bool HeaderSection::isVisible() const {
    Q_D(const HeaderSection);

    return d->visible;
}

void HeaderSection::setVisible(bool visible) {
    if (visible != this->isVisible()) {
        Q_D(HeaderSection);
        d->visible = visible;

        if (d->complete) {
            if (HeaderView *view = qobject_cast<HeaderView*>(this->parent())) {
                view->setSectionHidden(this->index(), !visible);
            }
        }
    }
}

void HeaderSection::classBegin() {}

void HeaderSection::componentComplete() {
    Q_D(HeaderSection);

    d->complete = true;

    if (HeaderView *view = qobject_cast<HeaderView*>(this->parent())) {
        view->resizeSection(this->index(), this->width());
        view->setResizeMode(this->index(), this->resizeMode());
        view->setSectionHidden(this->index(), !this->isVisible());
        this->connect(view, SIGNAL(sectionClicked(int)), this, SLOT(_q_onSectionClicked(int)));
    }
}

void HeaderSectionPrivate::_q_onSectionClicked(int i) {
    if (i == index) {
        Q_Q(HeaderSection);
        emit q->clicked();
    }
}

HeaderView::HeaderView(QWidget *parent) :
    QHeaderView(Qt::Horizontal, parent),
    d_ptr(new HeaderViewPrivate(this))
{
    this->setClickable(true);
    this->setHighlightSections(true);
}

HeaderView::HeaderView(HeaderViewPrivate &dd, QWidget *parent) :
    QHeaderView(Qt::Horizontal, parent),
    d_ptr(&dd)
{
    this->setClickable(true);
    this->setHighlightSections(true);
}

HeaderView::~HeaderView() {}

void HeaderView::setX(int x) {
    if (x != this->x()) {
        this->move(x, this->y());
    }
}

void HeaderView::setY(int y) {
    if (y != this->y()) {
        this->move(this->x(), y);
    }
}

qreal HeaderView::opacity() const {
    if (QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect())) {
        return effect->opacity();
    }

    return 1.0;
}

void HeaderView::setOpacity(qreal opacity) {
    QGraphicsOpacityEffect *effect = qobject_cast<QGraphicsOpacityEffect*>(this->graphicsEffect());

    if (!effect) {
        effect = new QGraphicsOpacityEffect(this);
        this->setGraphicsEffect(effect);
    }

    if (opacity != effect->opacity()) {
        effect->setOpacity(opacity);
        emit opacityChanged();
    }
}

AnchorLine HeaderView::left() const {
    Q_D(const HeaderView);

    return d->left;
}

AnchorLine HeaderView::right() const {
    Q_D(const HeaderView);

    return d->right;
}

AnchorLine HeaderView::top() const {
    Q_D(const HeaderView);

    return d->top;
}

AnchorLine HeaderView::bottom() const {
    Q_D(const HeaderView);

    return d->bottom;
}

AnchorLine HeaderView::horizontalCenter() const {
    Q_D(const HeaderView);

    return d->horizontalCenter;
}

AnchorLine HeaderView::verticalCenter() const {
    Q_D(const HeaderView);

    return d->verticalCenter;
}

void HeaderView::changeEvent(QEvent *event) {
    switch (event->type()) {
    case QEvent::ParentChange:
        emit parentChanged();
        break;
    case QEvent::EnabledChange:
        emit enabledChanged();
        break;
    default:
        break;
    }

    QHeaderView::changeEvent(event);
}

void HeaderView::moveEvent(QMoveEvent *event) {
    if (event->pos().x() != event->oldPos().x()) {
        emit xChanged();
    }

    if (event->pos().y() != event->oldPos().y()) {
        emit yChanged();
    }

    QHeaderView::moveEvent(event);
}

void HeaderView::resizeEvent(QResizeEvent *event) {
    if (event->size().width() != event->oldSize().width()) {
        emit widthChanged();
    }

    if (event->size().height() != event->oldSize().height()) {
        emit heightChanged();
    }

    QHeaderView::resizeEvent(event);
}

void HeaderView::showEvent(QShowEvent *event) {
    emit visibleChanged();
    QHeaderView::showEvent(event);
}

void HeaderView::hideEvent(QHideEvent *event) {
    emit visibleChanged();
    QHeaderView::hideEvent(event);
}

void HeaderView::focusInEvent(QFocusEvent *event) {
    emit focusChanged();
    QHeaderView::focusInEvent(event);
}

void HeaderView::focusOutEvent(QFocusEvent *event) {
    emit focusChanged();
    QHeaderView::focusOutEvent(event);
}

void HeaderView::classBegin() {}

void HeaderView::componentComplete() {
    Q_D(HeaderView);

    d->componentComplete();

    HeaderLabelModel *model = new HeaderLabelModel(this);
    QStringList strings;

    foreach (HeaderSection *section, d->sectionList) {
        strings.append(section->text());
    }

    model->setStringList(strings);
    this->setModel(model);

    if (this->parentWidget()) {
        this->setWindowFlags(Qt::Widget);
    }

    if (d->qmlVisible()) {
        this->show();
    }
}

void HeaderViewPrivate::data_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (HeaderView *view = qobject_cast<HeaderView*>(list->object)) {
        view->d_func()->dataList.append(obj);

        if (obj->isWidgetType()) {
            view->d_func()->childrenList.append(qobject_cast<QWidget*>(obj));
        }
    }
}

void HeaderViewPrivate::children_append(QDeclarativeListProperty<QWidget> *list, QWidget *widget) {
    if (!widget) {
        return;
    }

    if (HeaderView *view = qobject_cast<HeaderView*>(list->object)) {
        view->d_func()->childrenList.append(widget);
        view->d_func()->dataList.append(widget);
    }
}

void HeaderViewPrivate::actions_append(QDeclarativeListProperty<QObject> *list, QObject *obj) {
    if (!obj) {
        return;
    }

    if (HeaderView *view = qobject_cast<HeaderView*>(list->object)) {
        view->d_func()->actionList.append(obj);
        view->d_func()->dataList.append(obj);

        if (!view->d_func()->complete) {
            return;
        }

        if (QAction *action = qobject_cast<QAction*>(obj)) {
            view->addAction(action);
        }
        else if (QActionGroup *group = qobject_cast<QActionGroup*>(obj)) {
            view->addActions(group->actions());
        }
    }
}

void HeaderViewPrivate::sections_append(QDeclarativeListProperty<HeaderSection> *list, HeaderSection *section) {
    if (!section) {
        return;
    }

    if (HeaderView *view = qobject_cast<HeaderView*>(list->object)) {
        section->d_func()->index = view->d_func()->dataList.size();
        view->d_func()->sectionList.append(section);
        view->d_func()->dataList.append(section);

        if (view->d_func()->complete) {
            view->model()->insertRow(section->index());
            view->model()->setData(view->model()->index(section->index(), 0), section->text());
        }
    }
}

QDeclarativeListProperty<QObject> HeaderViewPrivate::data() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, HeaderViewPrivate::data_append);
}

QDeclarativeListProperty<QWidget> HeaderViewPrivate::children() {
    return QDeclarativeListProperty<QWidget>(q_func(), 0, HeaderViewPrivate::children_append);
}

QDeclarativeListProperty<QObject> HeaderViewPrivate::actions() {
    return QDeclarativeListProperty<QObject>(q_func(), 0, HeaderViewPrivate::actions_append);
}

QDeclarativeListProperty<HeaderSection> HeaderViewPrivate::sections() {
    return QDeclarativeListProperty<HeaderSection>(q_func(), 0, HeaderViewPrivate::sections_append);
}

QVariant HeaderViewPrivate::currentIndex() const {
    Q_Q(const HeaderView);

    return QVariant::fromValue<QModelIndex>(q->currentIndex());
}

void HeaderViewPrivate::setCurrentIndex(const QVariant &index) {
    if (index != this->currentIndex()) {
        Q_Q(HeaderView);
        q->setCurrentIndex(index.value<QModelIndex>());
        emit q->currentIndexChanged();
    }
}

bool HeaderViewPrivate::isClickable() const {
    Q_Q(const HeaderView);

    return q->isClickable();
}

void HeaderViewPrivate::setClickable(bool clickable) {
    if (clickable != this->isClickable()) {
        Q_Q(HeaderView);
        q->setClickable(clickable);
        emit q->clickableChanged();
    }
}

bool HeaderViewPrivate::isSortIndicatorShown() const {
    Q_Q(const HeaderView);

    return q->isSortIndicatorShown();
}

void HeaderViewPrivate::setSortIndicatorShown(bool shown) {
    if (shown != this->isSortIndicatorShown()) {
        Q_Q(HeaderView);
        q->setSortIndicatorShown(shown);
        emit q->showSortIndicatorChanged();
    }
}

bool HeaderViewPrivate::highlightSections() const {
    Q_Q(const HeaderView);

    return q->highlightSections();
}

void HeaderViewPrivate::setHighlightSections(bool highlight) {
    if (highlight != this->highlightSections()) {
        Q_Q(HeaderView);
        q->setHighlightSections(highlight);
        emit q->highlightSectionsChanged();
    }
}

bool HeaderViewPrivate::stretchLastSection() const {
    Q_Q(const HeaderView);

    return q->stretchLastSection();
}

void HeaderViewPrivate::setStretchLastSection(bool stretch) {
    if (stretch != this->stretchLastSection()) {
        Q_Q(HeaderView);
        q->setStretchLastSection(stretch);
        emit q->stretchLastSectionChanged();
    }
}

bool HeaderViewPrivate::cascadingSectionResizes() const {
    Q_Q(const HeaderView);

    return q->cascadingSectionResizes();
}

void HeaderViewPrivate::setCascadingSectionResizes(bool resizes) {
    if (resizes != this->cascadingSectionResizes()) {
        Q_Q(HeaderView);
        q->setCascadingSectionResizes(resizes);
        emit q->cascadingSectionResizesChanged();
    }
}

int HeaderViewPrivate::defaultSectionSize() const {
    Q_Q(const HeaderView);

    return q->defaultSectionSize();
}

void HeaderViewPrivate::setDefaultSectionSize(int size) {
    if (size != this->defaultSectionSize()) {
        Q_Q(HeaderView);
        q->setDefaultSectionSize(size);
        emit q->defaultSectionSizeChanged();
    }
}

int HeaderViewPrivate::minimumSectionSize() const {
    Q_Q(const HeaderView);

    return q->minimumSectionSize();
}

void HeaderViewPrivate::setMinimumSectionSize(int size) {
    if (size != this->minimumSectionSize()) {
        Q_Q(HeaderView);
        q->setMinimumSectionSize(size);
        emit q->minimumSectionSizeChanged();
    }
}

Qt::Alignment HeaderViewPrivate::defaultAlignment() const {
    Q_Q(const HeaderView);

    return q->defaultAlignment();
}

void HeaderViewPrivate::setDefaultAlignment(Qt::Alignment alignment) {
    if (alignment != this->defaultAlignment()) {
        Q_Q(HeaderView);
        q->setDefaultAlignment(alignment);
        emit q->defaultAlignmentChanged();
    }
}

HeaderLabelModel::HeaderLabelModel(QObject *parent) :
    QStringListModel(parent)
{
}

HeaderLabelModel::HeaderLabelModel(const QStringList &strings, QObject *parent) :
    QStringListModel(strings, parent)
{
}

int HeaderLabelModel::columnCount(const QModelIndex &parent) const {
    return this->rowCount(parent);
}

QVariant HeaderLabelModel::headerData(int section, Qt::Orientation orientation, int role) const {
    Q_UNUSED(orientation);

    return this->data(this->index(section), role);
}

#include "moc_headerview_p.cpp"
