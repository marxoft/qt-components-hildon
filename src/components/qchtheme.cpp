/*
 * Copyright (C) 2016 Stuart Howarth <showarth@marxoft.co.uk>
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

#include "qchtheme.h"
#include <QSettings>

static const QString THEME_DESKTOP_FILE("/etc/hildon/theme/index.theme");

/*!
    \class Theme
    \brief Provides information about the current theme.
    
    \ingroup components
    
    \note Theme is a context property and cannot be created in QML.
    
    \sa Style
*/
QchTheme::QchTheme(QObject *parent) :
    QObject(parent)
{
}

/*!
    \brief The GTK theme name.
*/
QString QchTheme::gtkTheme() const {
    return QSettings(THEME_DESKTOP_FILE, QSettings::IniFormat).value("X-Hildon-Metatheme/GtkTheme").toString();
}

/*!
    \brief The path to the desktop icon.
*/
QString QchTheme::icon() const {
    return QSettings(THEME_DESKTOP_FILE, QSettings::IniFormat).value("Desktop Entry/Icon").toString();
}

/*!
    \brief The icon theme name.
*/
QString QchTheme::iconTheme() const {
    return QSettings(THEME_DESKTOP_FILE, QSettings::IniFormat).value("X-Hildon-Metatheme/IconTheme").toString();
}

/*!
    \brief The theme display name.
*/
QString QchTheme::name() const {
    return QSettings(THEME_DESKTOP_FILE, QSettings::IniFormat).value("Desktop Entry/Name").toString();
}
