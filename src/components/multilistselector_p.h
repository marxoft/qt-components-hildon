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

#ifndef MULTILISTSELECTOR_P_H
#define MULTILISTSELECTOR_P_H

#include "valueselector_p.h"
#include "screen_p.h"
#include <QDialog>
#include <QMaemo5ListPickSelector>
#include <QStyledItemDelegate>
#include <QItemSelection>

class QListView;
class QDialogButtonBox;
class QGridLayout;
class MultiListSelectorPrivate;

class MultiListSelector : public ValueSelector
{
    Q_OBJECT

    Q_PROPERTY(QVariant model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(int modelColumn READ modelColumn WRITE setModelColumn NOTIFY modelColumnChanged)
    Q_PROPERTY(QVariantList currentIndexes READ currentIndexes WRITE setCurrentIndexes NOTIFY currentIndexesChanged)
    Q_PROPERTY(QString currentValueText READ currentValueText NOTIFY selected)

public:
    explicit MultiListSelector(QObject *parent = 0);
    ~MultiListSelector();

    QVariant model() const;
    void setModel(const QVariant &model);

    int modelColumn() const;
    void setModelColumn(int column);

    QVariantList currentIndexes() const;
    void setCurrentIndexes(const QVariantList &indexes);

    QString currentValueText() const;

signals:
    void modelChanged();
    void modelColumnChanged();
    void currentIndexesChanged();
    void selected(const QString &text);

private:
    MultiListSelector(MultiListSelectorPrivate &dd, QObject *parent = 0);

    Q_DISABLE_COPY(MultiListSelector)
    Q_DECLARE_PRIVATE(MultiListSelector)
};

class MultiListPickDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MultiListPickDialog(QWidget *parent = 0);

    QListView *view() const;
    void setView(QListView *view);

public slots:
    void reject();

private slots:
    void onOrientationChanged(Screen::Orientation orientation);

private:
    void loadPortraitLayout();
    void loadLandscapeLayout();

    void showEvent(QShowEvent *event);

    QListView *m_view;
    QDialogButtonBox *m_buttonBox;
    QGridLayout *m_grid;

    QItemSelection m_itemSelection;

    Q_DISABLE_COPY(MultiListPickDialog)
};

class MultiListPickSelector : public QMaemo5ListPickSelector
{
    Q_OBJECT

public:
    explicit MultiListPickSelector(MultiListPickDialog *dialog, QObject *parent = 0);

    QWidget* widget(QWidget *parent);

    QString currentValueText() const;

private slots:
    void onDialogAccepted();

private:
    MultiListPickDialog *m_dialog;

    Q_DISABLE_COPY(MultiListPickSelector)
};

class MultiListPickDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit MultiListPickDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    Q_DISABLE_COPY(MultiListPickDelegate)
};

QML_DECLARE_TYPE(MultiListSelector)

#endif // MULTILISTSELECTOR_P_H
