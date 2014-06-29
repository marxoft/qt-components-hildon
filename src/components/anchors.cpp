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

#include "anchors_p.h"
#include "anchors_p_p.h"
#include <qdeclarativeinfo.h>

static int position(QWidget *widget, AnchorLine::Line line) {
    int ret = 0;

    switch (line) {
    case AnchorLine::Left:
        ret = widget->x();
        break;
    case AnchorLine::Right:
        ret = widget->x() + widget->width();
        break;
    case AnchorLine::Top:
        ret = widget->y();
        break;
    case AnchorLine::Bottom:
        ret = widget->y() + widget->height();
        break;
    case AnchorLine::HCenter:
        ret = widget->x() + widget->width() / 2;
        break;
    case AnchorLine::VCenter:
        ret = widget->y() + widget->height() / 2;
        break;
    default:
        break;
    }

    return ret;
}

//position when origin is 0,0
static int adjustedPosition(QWidget *widget, AnchorLine::Line line) {
    int ret = 0;

    switch (line) {
    case AnchorLine::Left:
        ret = 0;
        break;
    case AnchorLine::Right:
        ret = widget->width();
        break;
    case AnchorLine::Top:
        ret = 0;
        break;
    case AnchorLine::Bottom:
        ret = widget->height();
        break;
    case AnchorLine::HCenter:
        ret = widget->width() / 2;
        break;
    case AnchorLine::VCenter:
        ret = widget->height() / 2;
        break;
    default:
        break;
    }

    return ret;
}

Anchors::Anchors(QWidget *widget, QObject *parent) :
    QObject(parent),
    d_ptr(new AnchorsPrivate(widget, this))
{
}

Anchors::Anchors(AnchorsPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
}

Anchors::~Anchors() {
    Q_D(Anchors);

    d->inDestructor = true;
    d->remDepend(d->fill);
    d->remDepend(d->centerIn);
    d->remDepend(d->left.widget);
    d->remDepend(d->right.widget);
    d->remDepend(d->top.widget);
    d->remDepend(d->bottom.widget);
    d->remDepend(d->horizontalCenter.widget);
    d->remDepend(d->verticalCenter.widget);
}

AnchorLine Anchors::left() const {
    Q_D(const Anchors);

    return d->left;
}

void Anchors::setLeft(const AnchorLine &edge) {
    Q_D(Anchors);

    if ((!d->checkHAnchorValid(edge)) || (d->left == edge)) {
        return;
    }

    d->usedAnchors |= LeftAnchor;

    if (!d->checkHValid()) {
        d->usedAnchors &= ~LeftAnchor;
        return;
    }

    QWidget *oldLeft = d->left.widget;

    d->left = edge;
    d->remDepend(oldLeft);
    d->addDepend(d->left.widget);
    emit leftChanged();
    d->_q_updateHorizontalAnchors();
}

void Anchors::resetLeft() {
    Q_D(Anchors);

    d->usedAnchors &= ~LeftAnchor;
    d->remDepend(d->left.widget);
    d->left = AnchorLine();
    emit leftChanged();
    d->_q_updateHorizontalAnchors();
}

int Anchors::leftMargin() const {
    Q_D(const Anchors);

    return d->leftMargin;
}

void Anchors::setLeftMargin(int offset) {
    Q_D(Anchors);

    d->leftMarginExplicit = true;

    if (d->leftMargin == offset) {
        return;
    }

    d->leftMargin = offset;

    if (d->fill) {
        d->fillChanged();
    }
    else {
        d->_q_updateHorizontalAnchors();
    }

    emit leftMarginChanged();
}

void Anchors::resetLeftMargin() {
    Q_D(Anchors);

    d->leftMarginExplicit = false;

    if (d->leftMargin == d->margins) {
        return;
    }

    d->leftMargin = d->margins;

    if (d->fill) {
        d->fillChanged();
    }
    else {
        d->_q_updateHorizontalAnchors();
    }

    emit leftMarginChanged();
}

AnchorLine Anchors::right() const {
    Q_D(const Anchors);

    return d->right;
}

void Anchors::setRight(const AnchorLine &edge) {
    Q_D(Anchors);

    if ((!d->checkHAnchorValid(edge)) || (d->right == edge)) {
        return;
    }

    d->usedAnchors |= RightAnchor;

    if (!d->checkHValid()) {
        d->usedAnchors &= ~RightAnchor;
        return;
    }

    QWidget *oldRight = d->right.widget;
    d->right = edge;
    d->remDepend(oldRight);
    d->addDepend(d->right.widget);
    emit rightChanged();
    d->_q_updateHorizontalAnchors();
}

void Anchors::resetRight() {
    Q_D(Anchors);

    d->usedAnchors &= ~RightAnchor;
    d->remDepend(d->right.widget);
    d->right = AnchorLine();
    emit rightChanged();
    d->_q_updateHorizontalAnchors();
}

int Anchors::rightMargin() const {
    Q_D(const Anchors);

    return d->rightMargin;
}

void Anchors::setRightMargin(int offset) {
    Q_D(Anchors);

    d->rightMarginExplicit = true;

    if (d->rightMargin == offset) {
        return;
    }

    d->rightMargin = offset;

    if (d->fill) {
        d->fillChanged();
    }
    else {
        d->_q_updateHorizontalAnchors();
    }

    emit rightMarginChanged();
}

void Anchors::resetRightMargin() {
    Q_D(Anchors);

    d->rightMarginExplicit = false;

    if (d->rightMargin == d->margins) {
        return;
    }

    d->rightMargin = d->margins;

    if (d->fill) {
        d->fillChanged();
    }
    else {
        d->_q_updateHorizontalAnchors();
    }

    emit rightMarginChanged();
}

AnchorLine Anchors::top() const {
    Q_D(const Anchors);

    return d->top;
}

void Anchors::setTop(const AnchorLine &edge) {
    Q_D(Anchors);

    if (!d->checkVAnchorValid(edge) || d->top == edge) {
        return;
    }

    d->usedAnchors |= TopAnchor;

    if (!d->checkVValid()) {
        d->usedAnchors &= ~TopAnchor;
        return;
    }

    QWidget *oldTop = d->top.widget;
    d->top = edge;
    d->remDepend(oldTop);
    d->addDepend(d->top.widget);
    emit topChanged();
    d->_q_updateVerticalAnchors();
}

void Anchors::resetTop() {
    Q_D(Anchors);

    d->usedAnchors &= ~TopAnchor;
    d->remDepend(d->top.widget);
    d->top = AnchorLine();
    emit topChanged();
    d->_q_updateVerticalAnchors();
}

int Anchors::topMargin() const {
    Q_D(const Anchors);

    return d->topMargin;
}

void Anchors::setTopMargin(int offset) {
    Q_D(Anchors);

    d->topMarginExplicit = true;

    if (d->topMargin == offset) {
        return;
    }

    d->topMargin = offset;

    if (d->fill) {
        d->fillChanged();
    }
    else {
        d->_q_updateVerticalAnchors();
    }

    emit topMarginChanged();
}

void Anchors::resetTopMargin() {
    Q_D(Anchors);

    d->topMarginExplicit = false;

    if (d->topMargin == d->margins) {
        return;
    }

    d->topMargin = d->margins;

    if (d->fill) {
        d->fillChanged();
    }
    else {
        d->_q_updateVerticalAnchors();
    }

    emit topMarginChanged();
}

AnchorLine Anchors::bottom() const {
    Q_D(const Anchors);

    return d->bottom;
}

void Anchors::setBottom(const AnchorLine &edge) {
    Q_D(Anchors);

    if ((!d->checkVAnchorValid(edge)) || (d->bottom == edge)) {
        return;
    }

    d->usedAnchors |= BottomAnchor;

    if (!d->checkVValid()) {
        d->usedAnchors &= ~BottomAnchor;
        return;
    }

    QWidget *oldBottom = d->bottom.widget;
    d->bottom = edge;
    d->remDepend(oldBottom);
    d->addDepend(d->bottom.widget);
    emit bottomChanged();
    d->_q_updateVerticalAnchors();
}

void Anchors::resetBottom() {
    Q_D(Anchors);

    d->usedAnchors &= ~BottomAnchor;
    d->remDepend(d->bottom.widget);
    d->bottom = AnchorLine();
    emit bottomChanged();
    d->_q_updateVerticalAnchors();
}

int Anchors::bottomMargin() const {
    Q_D(const Anchors);

    return d->bottomMargin;
}

void Anchors::setBottomMargin(int offset) {
    Q_D(Anchors);

    d->bottomMarginExplicit = true;

    if (d->bottomMargin == offset) {
        return;
    }

    d->bottomMargin = offset;

    if (d->fill) {
        d->fillChanged();
    }
    else {
        d->_q_updateVerticalAnchors();
    }

    emit bottomMarginChanged();
}

void Anchors::resetBottomMargin() {
    Q_D(Anchors);

    d->bottomMarginExplicit = false;

    if (d->bottomMargin == d->margins) {
        return;
    }

    d->bottomMargin = d->margins;

    if (d->fill) {
        d->fillChanged();
    }
    else {
        d->_q_updateVerticalAnchors();
    }

    emit bottomMarginChanged();
}

int Anchors::margins() const {
    Q_D(const Anchors);

    return d->margins;
}

void Anchors::setMargins(int offset) {
    Q_D(Anchors);

    if (d->margins == offset) {
        return;
    }

    d->margins = offset;
    bool updateHorizontal = false;
    bool updateVertical = false;

    if ((!d->rightMarginExplicit) && (d->rightMargin != offset)) {
        d->rightMargin = offset;
        updateHorizontal = true;
        emit rightMarginChanged();
    }

    if ((!d->leftMarginExplicit) && (d->leftMargin != offset)) {
        d->leftMargin = offset;
        updateHorizontal = true;
        emit leftMarginChanged();
    }

    if ((!d->topMarginExplicit) && (d->topMargin != offset)) {
        d->topMargin = offset;
        updateVertical = true;
        emit topMarginChanged();
    }

    if ((!d->bottomMarginExplicit) && (d->bottomMargin != offset)) {
        d->bottomMargin = offset;
        updateVertical = true;
        emit bottomMarginChanged();
    }

    if (d->fill) {
        if ((updateHorizontal) || (updateVertical)) {
            d->fillChanged();
        }
    }
    else {
        if (updateHorizontal) {
            d->_q_updateHorizontalAnchors();
        }

        if (updateVertical) {
            d->_q_updateVerticalAnchors();
        }
    }

    emit marginsChanged();
}

AnchorLine Anchors::horizontalCenter() const {
    Q_D(const Anchors);

    return d->horizontalCenter;
}

void Anchors::setHorizontalCenter(const AnchorLine &edge) {
    Q_D(Anchors);

    if ((!d->checkHAnchorValid(edge)) || (d->horizontalCenter == edge)) {
        return;
    }

    d->usedAnchors |= HCenterAnchor;

    if (!d->checkHValid()) {
        d->usedAnchors &= ~HCenterAnchor;
        return;
    }

    QWidget *oldHCenter = d->horizontalCenter.widget;
    d->horizontalCenter = edge;
    d->remDepend(oldHCenter);
    d->addDepend(d->horizontalCenter.widget);
    emit horizontalCenterChanged();
    d->_q_updateHorizontalAnchors();
}

void Anchors::resetHorizontalCenter() {
    Q_D(Anchors);

    d->usedAnchors &= ~HCenterAnchor;
    d->remDepend(d->horizontalCenter.widget);
    d->horizontalCenter = AnchorLine();
    emit horizontalCenterChanged();
    d->_q_updateHorizontalAnchors();
}

int Anchors::horizontalCenterOffset() const {
    Q_D(const Anchors);

    return d->horizontalCenterOffset;
}

void Anchors::setHorizontalCenterOffset(int offset) {
    Q_D(Anchors);

    if (d->horizontalCenterOffset == offset) {
        return;
    }

    d->horizontalCenterOffset = offset;

    if (d->centerIn) {
        d->centerInChanged();
    }
    else {
        d->_q_updateHorizontalAnchors();
    }

    emit horizontalCenterOffsetChanged();
}

AnchorLine Anchors::verticalCenter() const {
    Q_D(const Anchors);

    return d->verticalCenter;
}

void Anchors::setVerticalCenter(const AnchorLine &edge) {
    Q_D(Anchors);

    if ((!d->checkVAnchorValid(edge)) || (d->verticalCenter == edge)) {
        return;
    }

    d->usedAnchors |= VCenterAnchor;

    if (!d->checkVValid()) {
        d->usedAnchors &= ~VCenterAnchor;
        return;
    }

    QWidget *oldverticalCenter = d->verticalCenter.widget;
    d->verticalCenter = edge;
    d->remDepend(oldverticalCenter);
    d->addDepend(d->verticalCenter.widget);
    emit verticalCenterChanged();
    d->_q_updateVerticalAnchors();
}

void Anchors::resetVerticalCenter() {
    Q_D(Anchors);

    d->usedAnchors &= ~VCenterAnchor;
    d->remDepend(d->verticalCenter.widget);
    d->verticalCenter = AnchorLine();
    emit verticalCenterChanged();
    d->_q_updateVerticalAnchors();
}

int Anchors::verticalCenterOffset() const {
    Q_D(const Anchors);

    return d->verticalCenterOffset;
}

void Anchors::setVerticalCenterOffset(int offset) {
    Q_D(Anchors);

    if (d->verticalCenterOffset == offset) {
        return;
    }

    d->verticalCenterOffset = offset;

    if (d->centerIn) {
        d->centerInChanged();
    }
    else {
        d->_q_updateVerticalAnchors();
    }

    emit verticalCenterOffsetChanged();
}

QObject* Anchors::centerIn() const {
    Q_D(const Anchors);

    return d->centerIn;
}

void Anchors::setCenterIn(QObject *obj) {
    Q_D(Anchors);

    QWidget *c = qobject_cast<QWidget*>(obj);

    if (d->centerIn == c) {
        return;
    }

    if (!c) {
        QWidget *oldCI = d->centerIn;
        d->centerIn = c;
        d->remDepend(oldCI);
        emit centerInChanged();
        return;
    }

    if ((c != d->widget->parentWidget()) && (c->parentWidget() != d->widget->parentWidget())) {
        qmlInfo(d->widget) << tr("Cannot anchor to an widget that isn't a parent or sibling.");
        return;
    }

    QWidget *oldCI = d->centerIn;
    d->centerIn = c;
    d->remDepend(oldCI);
    d->addDepend(d->centerIn);
    emit centerInChanged();
    d->centerInChanged();
}

void Anchors::resetCenterIn() {
    this->setCenterIn(0);
}

QObject* Anchors::fill() const {
    Q_D(const Anchors);

    return d->fill;
}

void Anchors::setFill(QObject *obj) {
    Q_D(Anchors);

    QWidget *f = qobject_cast<QWidget*>(obj);

    if (d->fill == f) {
        return;
    }

    if (!f) {
        QWidget *oldFill = d->fill;
        d->fill = f;
        d->remDepend(oldFill);
        emit fillChanged();
        return;
    }

    if ((f != d->widget->parentWidget()) && (f->parentWidget() != d->widget->parentWidget())) {
        qmlInfo(d->widget) << tr("Cannot anchor to an widget that isn't a parent or sibling.");
        return;
    }

    QWidget *oldFill = d->fill;
    d->fill = f;
    d->remDepend(oldFill);
    d->addDepend(d->fill);
    emit fillChanged();
    d->fillChanged();
}

void Anchors::resetFill() {
    this->setFill(0);
}

Anchors::AnchorFlags Anchors::usedAnchors() const {
    Q_D(const Anchors);

    return d->usedAnchors;
}

void AnchorsPrivate::fillChanged() {
    if ((!fill) || (!this->isWidgetComplete())) {
        return;
    }

    if (updatingFill < 2) {
        ++updatingFill;

        if (fill == widget->parentWidget()) { //child-parent
            this->setWidgetPos(QPoint(leftMargin, topMargin));
        }
        else if (fill->parentWidget() == widget->parentWidget()) { //siblings
            this->setWidgetPos(QPoint(fill->x() + leftMargin, fill->y() + topMargin));
        }

        this->setWidgetSize(QSize(fill->width() -leftMargin - rightMargin, fill->height() - topMargin - bottomMargin));
        --updatingFill;
    }
    else {
        // ### Make this certain :)
        qmlInfo(widget) << Anchors::tr("Possible anchor loop detected on fill.");
    }
}

void AnchorsPrivate::centerInChanged() {
    if ((!centerIn) || (fill) || (!this->isWidgetComplete())) {
        return;
    }

    if (updatingCenterIn < 2) {
        ++updatingCenterIn;

        if (centerIn == widget->parentWidget()) {
            QPoint p(widget->parentWidget()->width() / 2 - widget->width() / 2 + horizontalCenterOffset,
                     widget->parentWidget()->height() / 2 - widget->height() / 2 + verticalCenterOffset);
            this->setWidgetPos(p);
        }
        else if (centerIn->parentWidget() == widget->parentWidget()) {
            QPoint p(centerIn->x() + centerIn->width() / 2 - widget->width() / 2 + horizontalCenterOffset,
                     centerIn->y() + centerIn->height() / 2 - widget->height() / 2 + verticalCenterOffset);
            this->setWidgetPos(p);
        }

        --updatingCenterIn;
    }
    else {
        // ### Make this certain :)
        qmlInfo(widget) << Anchors::tr("Possible anchor loop detected on centerIn.");
    }
}

void AnchorsPrivate::clearWidget(QWidget *w) {
    if (!w) {
        return;
    }

    if (fill == w) {
        fill = 0;
    }

    if (centerIn == w) {
        centerIn = 0;
    }

    if (left.widget == w) {
        left.widget = 0;
        usedAnchors &= ~Anchors::LeftAnchor;
    }

    if (right.widget == w) {
        right.widget = 0;
        usedAnchors &= ~Anchors::RightAnchor;
    }

    if (top.widget == w) {
        top.widget = 0;
        usedAnchors &= ~Anchors::TopAnchor;
    }

    if (bottom.widget == w) {
        bottom.widget = 0;
        usedAnchors &= ~Anchors::BottomAnchor;
    }

    if (horizontalCenter.widget == w) {
        horizontalCenter.widget = 0;
        usedAnchors &= ~Anchors::HCenterAnchor;
    }

    if (verticalCenter.widget == w) {
        verticalCenter.widget = 0;
        usedAnchors &= ~Anchors::VCenterAnchor;
    }
}

void AnchorsPrivate::addDepend(QWidget *w) {
    if ((!w) || (inDestructor)) {
        return;
    }

    Q_Q(Anchors);

    //TODO: Install event filter instead of connecting to signals.

    if (centerIn) {
        q->connect(widget, SIGNAL(parentChanged()), q, SLOT(centerInChanged()));
        q->connect(w, SIGNAL(xChanged()), q, SLOT(centerInChanged()));
        q->connect(w, SIGNAL(widthChanged()), q, SLOT(centerInChanged()));
        q->connect(w, SIGNAL(yChanged()), q, SLOT(centerInChanged()));
        q->connect(w, SIGNAL(heightChanged()), q, SLOT(centerInChanged()));
    }
    else if (fill) {
        q->connect(widget, SIGNAL(parentChanged()), q, SLOT(fillChanged()));
        q->connect(w, SIGNAL(xChanged()), q, SLOT(fillChanged()));
        q->connect(w, SIGNAL(widthChanged()), q, SLOT(fillChanged()));
        q->connect(w, SIGNAL(yChanged()), q, SLOT(fillChanged()));
        q->connect(w, SIGNAL(heightChanged()), q, SLOT(fillChanged()));
    }
    else {
        if ((usedAnchors & Anchors::LeftAnchor) || (usedAnchors & Anchors::RightAnchor) || (usedAnchors & Anchors::HCenterAnchor)) {
            q->connect(widget, SIGNAL(parentChanged()), q, SLOT(_q_updateHorizontalAnchors()));
            q->connect(w, SIGNAL(xChanged()), q, SLOT(_q_updateHorizontalAnchors()));
            q->connect(w, SIGNAL(widthChanged()), q, SLOT(_q_updateHorizontalAnchors()));
        }

        if ((usedAnchors & Anchors::TopAnchor) || (usedAnchors & Anchors::BottomAnchor) || (usedAnchors & Anchors::VCenterAnchor)) {
            q->connect(widget, SIGNAL(parentChanged()), q, SLOT(_q_updateVerticalAnchors()));
            q->connect(w, SIGNAL(yChanged()), q, SLOT(_q_updateVerticalAnchors()));
            q->connect(w, SIGNAL(heightChanged()), q, SLOT(_q_updateVerticalAnchors()));
        }
    }
}

void AnchorsPrivate::remDepend(QWidget *w) {
    if ((!w) || (inDestructor)) {
        return;
    }

    Q_Q(Anchors);

    q->disconnect(w, SIGNAL(xChanged()), q, SLOT(_q_updateHorizontalAnchors()));
    q->disconnect(w, SIGNAL(widthChanged()), q, SLOT(_q_updateHorizontalAnchors()));
    q->disconnect(w, SIGNAL(yChanged()), q, SLOT(_q_updateVerticalAnchors()));
    q->disconnect(w, SIGNAL(heightChanged()), q, SLOT(_q_updateVerticalAnchors()));
}

bool AnchorsPrivate::isWidgetComplete() const {
    return widgetComplete;
}

void AnchorsPrivate::setWidgetX(int x) {
    updatingMe = true;
    widget->move(x, widget->y());
    updatingMe = false;
}

void AnchorsPrivate::setWidgetY(int y) {
    updatingMe = true;
    widget->move(widget->x(), y);
    updatingMe = false;
}

void AnchorsPrivate::setWidgetPos(const QPoint &pos) {
    updatingMe = true;
    widget->move(pos);
    updatingMe = false;
}

void AnchorsPrivate::setWidgetWidth(int width) {
    updatingMe = true;
    widget->setFixedWidth(width);
    updatingMe = false;
}

void AnchorsPrivate::setWidgetHeight(int height) {
    updatingMe = true;
    widget->setFixedHeight(height);
    updatingMe = false;
}

void AnchorsPrivate::setWidgetSize(const QSize &size) {
    updatingMe = true;
    widget->setFixedSize(size);
    updatingMe = false;
}

bool AnchorsPrivate::checkHValid() const {
    if ((usedAnchors & Anchors::LeftAnchor) &&
            (usedAnchors & Anchors::RightAnchor) &&
            (usedAnchors & Anchors::HCenterAnchor)) {

        qmlInfo(widget) << Anchors::tr("Cannot specify left, right, and horizontalCenter anchors at the same time.");
        return false;
    }

    return true;
}

bool AnchorsPrivate::checkVValid() const {
    if (usedAnchors & Anchors::TopAnchor &&
            usedAnchors & Anchors::BottomAnchor &&
            usedAnchors & Anchors::VCenterAnchor) {

        qmlInfo(widget) << Anchors::tr("Cannot specify top, bottom, and verticalCenter anchors at the same time.");
        return false;

    }

    return true;
}

bool AnchorsPrivate::checkHAnchorValid(AnchorLine anchor) const {
    if (!anchor.widget) {
        qmlInfo(widget) << Anchors::tr("Cannot anchor to a null item.");
        return false;
    }
    else if (anchor.line & AnchorLine::Vertical_Mask) {
        qmlInfo(widget) << Anchors::tr("Cannot anchor a horizontal edge to a vertical edge.");
        return false;
    }
    else if (anchor.widget != widget->parentWidget() && anchor.widget->parentWidget() != widget->parentWidget()){
        qmlInfo(widget) << Anchors::tr("Cannot anchor to an item that isn't a parent or sibling.");
        return false;
    }
    else if (anchor.widget == widget) {
        qmlInfo(widget) << Anchors::tr("Cannot anchor item to self.");
        return false;
    }

    return true;
}

bool AnchorsPrivate::checkVAnchorValid(AnchorLine anchor) const {
    if (!anchor.widget) {
        qmlInfo(widget) << Anchors::tr("Cannot anchor to a null item.");
        return false;
    }
    else if (anchor.line & AnchorLine::Horizontal_Mask) {
        qmlInfo(widget) << Anchors::tr("Cannot anchor a vertical edge to a horizontal edge.");
        return false;
    }
    else if (anchor.widget != widget->parentWidget() && anchor.widget->parentWidget() != widget->parentWidget()){
        qmlInfo(widget) << Anchors::tr("Cannot anchor to an item that isn't a parent or sibling.");
        return false;
    }
    else if (anchor.widget == widget){
        qmlInfo(widget) << Anchors::tr("Cannot anchor item to self.");
        return false;
    }

    return true;
}

bool AnchorsPrivate::calcStretch(const AnchorLine &edge1,
                                 const AnchorLine &edge2,
                                 int offset1,
                                 int offset2,
                                 AnchorLine::Line line,
                                 int &stretch) {

    bool edge1IsParent = (edge1.widget == widget->parentWidget());
    bool edge2IsParent = (edge2.widget == widget->parentWidget());
    bool edge1IsSibling = (edge1.widget->parentWidget() == widget->parentWidget());
    bool edge2IsSibling = (edge2.widget->parentWidget() == widget->parentWidget());
    bool invalid = false;

    if ((edge2IsParent && edge1IsParent) || (edge2IsSibling && edge1IsSibling)) {
        stretch = (position(edge2.widget, edge2.line) + offset2)
                - (position(edge1.widget, edge1.line) + offset1);
    }
    else if (edge2IsParent && edge1IsSibling) {
        stretch = (position(edge2.widget, edge2.line) + offset2)
                - (position(widget->parentWidget(), line)
                   + position(edge1.widget, edge1.line) + offset1);
    }
    else if (edge2IsSibling && edge1IsParent) {
        stretch = (position(widget->parentWidget(), line) + position(edge2.widget, edge2.line) + offset2)
                - (position(edge1.widget, edge1.line) + offset1);
    }
    else {
        invalid = true;
    }

    return invalid;
}

void AnchorsPrivate::onWidgetCompleted() {
    widgetComplete = true;
    this->update();
}

void AnchorsPrivate::update() {
    this->fillChanged();
    this->centerInChanged();

    if (usedAnchors & AnchorLine::Horizontal_Mask) {
        this->_q_updateHorizontalAnchors();
    }

    if (usedAnchors & AnchorLine::Vertical_Mask) {
        this->_q_updateVerticalAnchors();
    }
}

void AnchorsPrivate::_q_updateVerticalAnchors() {
    if ((fill) || (centerIn) || (!this->isWidgetComplete())) {
        return;
    }

    if (updatingVerticalAnchor < 2) {
        ++updatingVerticalAnchor;

        if (usedAnchors & Anchors::TopAnchor) {
            //Handle stretching
            bool invalid = true;
            int height = 0;

            if (usedAnchors & Anchors::BottomAnchor) {
                invalid = this->calcStretch(top, bottom, topMargin, -bottomMargin, AnchorLine::Top, height);
            }
            else if (usedAnchors & Anchors::VCenterAnchor) {
                invalid = this->calcStretch(top, verticalCenter, topMargin, verticalCenterOffset, AnchorLine::Top, height);
                height *= 2;
            }

            if (!invalid) {
                this->setWidgetHeight(height);
            }

            //Handle top
            if (top.widget == widget->parentWidget()) {
                this->setWidgetY(adjustedPosition(top.widget, top.line) + topMargin);
            }
            else if (top.widget->parentWidget() == widget->parentWidget()) {
                this->setWidgetY(position(top.widget, top.line) + topMargin);
            }
        }
        else if (usedAnchors & Anchors::BottomAnchor) {
            //Handle stretching (top + bottom case is handled above)
            if (usedAnchors & Anchors::VCenterAnchor) {
                int height = 0;
                bool invalid = this->calcStretch(verticalCenter, bottom, verticalCenterOffset, -bottomMargin,
                                                 AnchorLine::Top, height);
                if (!invalid) {
                    this->setWidgetHeight(height * 2);
                }
            }

            //Handle bottom
            if (bottom.widget == widget->parentWidget()) {
                this->setWidgetY(adjustedPosition(bottom.widget, bottom.line) - widget->height() - bottomMargin);
            }
            else if (bottom.widget->parentWidget() == widget->parentWidget()) {
                this->setWidgetY(position(bottom.widget, bottom.line) - widget->height() - bottomMargin);
            }
        }
        else if (usedAnchors & Anchors::VCenterAnchor) {
            //(stetching handled above)
            //Handle verticalCenter
            if (verticalCenter.widget == widget->parentWidget()) {
                this->setWidgetY(adjustedPosition(verticalCenter.widget, verticalCenter.line)
                                 - widget->height() / 2 + verticalCenterOffset);
            }
            else if (verticalCenter.widget->parentWidget() == widget->parentWidget()) {
                this->setWidgetY(position(verticalCenter.widget, verticalCenter.line) - widget->height() / 2 + verticalCenterOffset);
            }
        }

        --updatingVerticalAnchor;
    }
    else {
        // ### Make this certain :)
        qmlInfo(widget) << Anchors::tr("Possible anchor loop detected on vertical anchor.");
    }
}

inline AnchorLine::Line reverseAnchorLine(AnchorLine::Line line) {
    if (line == AnchorLine::Left) {
        return AnchorLine::Right;
    }
    else if (line == AnchorLine::Right) {
        return AnchorLine::Left;
    }
    else {
        return line;
    }
}

void AnchorsPrivate::_q_updateHorizontalAnchors() {
    if ((fill) || (centerIn) || (!this->isWidgetComplete())) {
        return;
    }

    if (updatingHorizontalAnchor < 3) {
        ++updatingHorizontalAnchor;

        int effectiveRightMargin, effectiveLeftMargin, effectiveHorizontalCenterOffset;
        AnchorLine effectiveLeft, effectiveRight, effectiveHorizontalCenter;
        Anchors::Anchor effectiveLeftAnchor, effectiveRightAnchor;

        effectiveLeftAnchor = Anchors::LeftAnchor;
        effectiveRightAnchor = Anchors::RightAnchor;
        effectiveLeft = left;
        effectiveRight = right;
        effectiveHorizontalCenter = horizontalCenter;
        effectiveLeftMargin = leftMargin;
        effectiveRightMargin = rightMargin;
        effectiveHorizontalCenterOffset = horizontalCenterOffset;

        if (usedAnchors & effectiveLeftAnchor) {
            //Handle stretching
            bool invalid = true;
            int width = 0;

            if (usedAnchors & effectiveRightAnchor) {
                invalid = this->calcStretch(effectiveLeft, effectiveRight, effectiveLeftMargin, -effectiveRightMargin, AnchorLine::Left, width);
            }
            else if (usedAnchors & Anchors::HCenterAnchor) {
                invalid = this->calcStretch(effectiveLeft, effectiveHorizontalCenter, effectiveLeftMargin, effectiveHorizontalCenterOffset, AnchorLine::Left, width);
                width *= 2;
            }

            if (!invalid) {
                this->setWidgetWidth(width);
            }

            //Handle left
            if (effectiveLeft.widget == widget->parentWidget()) {
                this->setWidgetX(adjustedPosition(effectiveLeft.widget, effectiveLeft.line) + effectiveLeftMargin);
            }
            else if (effectiveLeft.widget->parentWidget() == widget->parentWidget()) {
                this->setWidgetX(position(effectiveLeft.widget, effectiveLeft.line) + effectiveLeftMargin);
            }
        }
        else if (usedAnchors & effectiveRightAnchor) {
            //Handle stretching (left + right case is handled in updateLeftAnchor)
            if (usedAnchors & Anchors::HCenterAnchor) {
                int width = 0;
                bool invalid = this->calcStretch(effectiveHorizontalCenter, effectiveRight, effectiveHorizontalCenterOffset, -effectiveRightMargin,
                                                 AnchorLine::Left, width);
                if (!invalid) {
                    this->setWidgetWidth(width * 2);
                }
            }

            //Handle right
            if (effectiveRight.widget == widget->parentWidget()) {
                this->setWidgetX(adjustedPosition(effectiveRight.widget, effectiveRight.line) - widget->width() - effectiveRightMargin);
            }
            else if (effectiveRight.widget->parentWidget() == widget->parentWidget()) {
                this->setWidgetX(position(effectiveRight.widget, effectiveRight.line) - widget->width() - effectiveRightMargin);
            }
        }
        else if (usedAnchors & Anchors::HCenterAnchor) {
            //Handle hCenter
            if (effectiveHorizontalCenter.widget == widget->parentWidget()) {
                this->setWidgetX(adjustedPosition(effectiveHorizontalCenter.widget, effectiveHorizontalCenter.line) - widget->width() / 2 + effectiveHorizontalCenterOffset);
            }
            else if (effectiveHorizontalCenter.widget->parentWidget() == widget->parentWidget()) {
                this->setWidgetX(position(effectiveHorizontalCenter.widget, effectiveHorizontalCenter.line) - widget->width() / 2 + effectiveHorizontalCenterOffset);
            }
        }

        --updatingHorizontalAnchor;
    }
    else {
        // ### Make this certain :)
        qmlInfo(widget) << Anchors::tr("Possible anchor loop detected on horizontal anchor.");
    }
}

#include "moc_anchors_p.cpp"
