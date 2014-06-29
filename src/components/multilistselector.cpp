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

#include "multilistselector_p.h"
#include "multilistselector_p_p.h"
#include "variantlistmodel_p.h"
#include <QListView>
#include <QAbstractButton>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QPainter>
#include <QStaticText>
#include <QTextOption>

MultiListSelector::MultiListSelector(QObject *parent) :
    ValueSelector(*new MultiListSelectorPrivate(this), parent)
{
    Q_D(MultiListSelector);

    d->dialog = new MultiListPickDialog;
    d->selector = new MultiListPickSelector(d->dialog, this);
}

MultiListSelector::MultiListSelector(MultiListSelectorPrivate &dd, QObject *parent) :
    ValueSelector(dd, parent)
{
}

MultiListSelector::~MultiListSelector() {}

QVariant MultiListSelector::model() const {
    Q_D(const MultiListSelector);

    return d->modelVariant;
}

void MultiListSelector::setModel(const QVariant &model) {
    Q_D(MultiListSelector);

    if (model == this->model()) {
        return;
    }

    VariantListModel *oldModel = d->variantModel;
    d->variantModel = 0;
    d->modelVariant = model;
    QObject *obj = qvariant_cast<QObject*>(model);
    QAbstractItemModel *itemModel = 0;

    if ((obj) && (itemModel = qobject_cast<QAbstractItemModel*>(obj))) {
        d->dialog->view()->setModel(itemModel);
    }
    else {
        d->variantModel = new VariantListModel(this);
        d->variantModel->setVariant(model);
        d->dialog->view()->setModel(d->variantModel);
        d->dialog->view()->setModelColumn(d->modelColumn);
    }

    if (oldModel) {
        delete oldModel;
    }
}

int MultiListSelector::modelColumn() const {
    Q_D(const MultiListSelector);

    if (QMaemo5ListPickSelector *selector = qobject_cast<QMaemo5ListPickSelector*>(d->selector)) {
        return selector->modelColumn();
    }
}

void MultiListSelector::setModelColumn(int column) {
    Q_D(MultiListSelector);

    d->modelColumn = column;

    if (QMaemo5ListPickSelector *selector = qobject_cast<QMaemo5ListPickSelector*>(d->selector)) {
        selector->setModelColumn(column);
    }
}

QVariantList MultiListSelector::currentIndexes() const {
    Q_D(const MultiListSelector);

    QVariantList list;

    foreach (QModelIndex index, d->dialog->view()->selectionModel()->selectedRows()) {
        list.append(index.row());
    }

    return list;
}

void MultiListSelector::setCurrentIndexes(const QVariantList &rows) {
    Q_D(MultiListSelector);

    foreach (QVariant row, rows) {
        d->dialog->view()->selectionModel()->select(d->dialog->view()->model()->index(row.toInt(), 0), QItemSelectionModel::Select);
    }
}

QString MultiListSelector::currentValueText() const {
    Q_D(const MultiListSelector);

    return d->selector->currentValueText();
}

MultiListPickDialog::MultiListPickDialog(QWidget *parent) :
    QDialog(parent),
    m_view(new QListView(this)),
    m_buttonBox(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Vertical, this)),
    m_grid(new QGridLayout(this))
{
    m_view->setSelectionMode(QListView::MultiSelection);
    m_view->setItemDelegate(new MultiListPickDelegate(m_view));
    m_view->setMinimumHeight(70 * 5);

    this->connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    this->connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    this->connect(Screen::instance(), SIGNAL(currentOrientationChanged(Screen::Orientation)), this, SLOT(onOrientationChanged(Screen::Orientation)));
    this->onOrientationChanged(Screen::instance()->currentOrientation());
}

QListView* MultiListPickDialog::view() const {
    return m_view;
}

void MultiListPickDialog::setView(QListView *view) {
    m_view = view;
}

void MultiListPickDialog::onOrientationChanged(Screen::Orientation orientation) {
    switch (orientation) {
    case Screen::PortraitOrientation:
        this->loadPortraitLayout();
        return;
    default:
        this->loadLandscapeLayout();
        return;
    }
}

void MultiListPickDialog::loadPortraitLayout() {
    m_buttonBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    if (m_grid->isEmpty()) {
        m_grid->addWidget(m_view, 0, 0, Qt::AlignBottom);
        m_grid->addWidget(m_buttonBox, 1, 0, Qt::AlignBottom);
    }
    else {
        m_grid->removeWidget(m_buttonBox);
        m_grid->addWidget(m_buttonBox, 1, 0, Qt::AlignBottom);
    }
}

void MultiListPickDialog::loadLandscapeLayout() {
    m_buttonBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    if (m_grid->isEmpty()) {
        m_grid->addWidget(m_view, 0, 0, Qt::AlignBottom);
        m_grid->addWidget(m_buttonBox, 0, 1, Qt::AlignBottom);
    }
    else {
        m_grid->removeWidget(m_buttonBox);
        m_grid->addWidget(m_buttonBox, 0, 1, Qt::AlignBottom);
    }
}

void MultiListPickDialog::reject() {
    m_view->selectionModel()->select(m_itemSelection, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
    QDialog::reject();
}

void MultiListPickDialog::showEvent(QShowEvent *event) {
    m_itemSelection = m_view->selectionModel()->selection();
    QDialog::showEvent(event);
}

MultiListPickSelector::MultiListPickSelector(MultiListPickDialog *dialog, QObject *parent) :
    QMaemo5ListPickSelector(parent),
    m_dialog(dialog)
{
    this->connect(dialog, SIGNAL(accepted()), this, SLOT(onDialogAccepted()));
}

QWidget* MultiListPickSelector::widget(QWidget *parent) {
    m_dialog->setParent(parent);
    m_dialog->setWindowFlags(Qt::Dialog);

    if (QAbstractButton *button = qobject_cast<QAbstractButton*>(parent)) {
        m_dialog->setWindowTitle(button->text());
    }

    return m_dialog;
}

QString MultiListPickSelector::currentValueText() const {
    QStringList list;

    foreach (QModelIndex index, m_dialog->view()->selectionModel()->selectedRows()) {
        list.append(index.data().toString());
    }

    return list.join(", ");
}

void MultiListPickSelector::onDialogAccepted() {
    emit selected(this->currentValueText());
}

MultiListPickDelegate::MultiListPickDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void MultiListPickDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if ((option.state) & (QStyle::State_Selected)) {
        painter->drawImage(option.rect, QImage("/etc/hildon/theme/images/TouchListBackgroundPressed.png"));
        painter->drawImage(option.rect.right() - 48, option.rect.top() + ((option.rect.height() - 48) / 2),
                           QImage("/usr/share/icons/hicolor/48x48/hildon/widgets_tickmark_grid.png"));
    }
    else {
        painter->drawImage(option.rect, QImage("/etc/hildon/theme/images/TouchListBackgroundNormal.png"));
    }

    QRect rect = option.rect;
    rect.setLeft(rect.left() + 8);
    rect.setRight(rect.right() - 48);

    QStaticText text(index.data().toString());
    text.setTextOption(QTextOption(Qt::AlignCenter));
    text.setTextWidth(rect.width());

    painter->drawStaticText(rect.left(), rect.center().y() - text.size().height() / 2, text);
}

#include "moc_multilistselector_p.cpp"
