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

#include "websettings_p.h"
#include <QWebSettings>

WebSettings::WebSettings(QObject *parent) :
    QObject(parent),
    m_settings(QWebSettings::globalSettings())
{
}

WebSettings::WebSettings(QWebSettings *settings, QObject *parent) :
    QObject(parent),
    m_settings(settings)
{
}

WebSettings::~WebSettings() {}

bool WebSettings::autoLoadImages() const {
    return m_settings->testAttribute(QWebSettings::AutoLoadImages);
}

void WebSettings::setAutoLoadImages(bool load) {
    m_settings->setAttribute(QWebSettings::AutoLoadImages, load);
}

void WebSettings::resetAutoLoadImages() {
    m_settings->resetAttribute(QWebSettings::AutoLoadImages);
}

bool WebSettings::javaEnabled() const {
    return m_settings->testAttribute(QWebSettings::JavaEnabled);
}

void WebSettings::setJavaEnabled(bool enabled) {
    m_settings->setAttribute(QWebSettings::JavaEnabled, enabled);
}

void WebSettings::resetJavaEnabled() {
    m_settings->resetAttribute(QWebSettings::JavaEnabled);
}

bool WebSettings::javascriptCanAccessClipboard() const {
    return m_settings->testAttribute(QWebSettings::JavascriptCanAccessClipboard);
}

void WebSettings::setJavascriptCanAccessClipboard(bool access) {
    m_settings->setAttribute(QWebSettings::JavascriptCanAccessClipboard, access);
}

void WebSettings::resetJavascriptCanAccessClipboard() {
    m_settings->resetAttribute(QWebSettings::JavascriptCanAccessClipboard);
}

bool WebSettings::javascriptCanOpenWindows() const {
    return m_settings->testAttribute(QWebSettings::JavascriptCanOpenWindows);
}

void WebSettings::setJavascriptCanOpenWindows(bool open) {
    m_settings->setAttribute(QWebSettings::JavascriptCanOpenWindows, open);
}

void WebSettings::resetJavascriptCanOpenWindows() {
    m_settings->resetAttribute(QWebSettings::JavascriptCanOpenWindows);
}

bool WebSettings::javascriptEnabled() const {
    return m_settings->testAttribute(QWebSettings::JavascriptEnabled);
}

void WebSettings::setJavascriptEnabled(bool enabled) {
    m_settings->setAttribute(QWebSettings::JavascriptEnabled, enabled);
}

void WebSettings::resetJavascriptEnabled() {
    m_settings->resetAttribute(QWebSettings::JavascriptEnabled);
}

bool WebSettings::linksIncludedInFocusChain() const {
    return m_settings->testAttribute(QWebSettings::LinksIncludedInFocusChain);
}

void WebSettings::setLinksIncludedInFocusChain(bool included) {
    m_settings->setAttribute(QWebSettings::LinksIncludedInFocusChain, included);
}

void WebSettings::resetLinksIncludedInFocusChain() {
    m_settings->resetAttribute(QWebSettings::LinksIncludedInFocusChain);
}

bool WebSettings::localContentCanAccessRemoteUrls() const {
    return m_settings->testAttribute(QWebSettings::LocalContentCanAccessRemoteUrls);
}

void WebSettings::setLocalContentCanAccessRemoteUrls(bool access) {
    m_settings->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, access);
}

void WebSettings::resetLocalContentCanAccessRemoteUrls() {
    m_settings->resetAttribute(QWebSettings::LocalContentCanAccessRemoteUrls);
}

bool WebSettings::localStorageDatabaseEnabled() const {
    return m_settings->testAttribute(QWebSettings::LocalStorageDatabaseEnabled);
}

void WebSettings::setLocalStorageDatabaseEnabled(bool enabled) {
    m_settings->setAttribute(QWebSettings::LocalStorageDatabaseEnabled, enabled);
}

void WebSettings::resetLocalStorageDatabaseEnabled() {
    m_settings->resetAttribute(QWebSettings::LocalStorageDatabaseEnabled);
}

bool WebSettings::offlineStorageDatabaseEnabled() const {
    return m_settings->testAttribute(QWebSettings::OfflineStorageDatabaseEnabled);
}

void WebSettings::setOfflineStorageDatabaseEnabled(bool enabled) {
    m_settings->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, enabled);
}

void WebSettings::resetOfflineStorageDatabaseEnabled() {
    m_settings->resetAttribute(QWebSettings::OfflineStorageDatabaseEnabled);
}

bool WebSettings::offlineWebApplicationCacheEnabled() const {
    return m_settings->testAttribute(QWebSettings::OfflineWebApplicationCacheEnabled);
}

void WebSettings::setOfflineWebApplicationCacheEnabled(bool enabled) {
    m_settings->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, enabled);
}

void WebSettings::resetOfflineWebApplicationCacheEnabled() {
    m_settings->resetAttribute(QWebSettings::OfflineWebApplicationCacheEnabled);
}

bool WebSettings::pluginsEnabled() const {
    return m_settings->testAttribute(QWebSettings::PluginsEnabled);
}

void WebSettings::setPluginsEnabled(bool enabled) {
    m_settings->setAttribute(QWebSettings::PluginsEnabled, enabled);
}

void WebSettings::resetPluginsEnabled() {
    m_settings->resetAttribute(QWebSettings::PluginsEnabled);
}

bool WebSettings::printElementBackgrounds() const {
    return m_settings->testAttribute(QWebSettings::PrintElementBackgrounds);
}

void WebSettings::setPrintElementBackgrounds(bool enabled) {
    m_settings->setAttribute(QWebSettings::PrintElementBackgrounds, enabled);
}

void WebSettings::resetPrintElementBackgrounds() {
    m_settings->resetAttribute(QWebSettings::PrintElementBackgrounds);
}

bool WebSettings::privateBrowsingEnabled() const {
    return m_settings->testAttribute(QWebSettings::PrivateBrowsingEnabled);
}

void WebSettings::setPrivateBrowsingEnabled(bool enabled) {
    m_settings->setAttribute(QWebSettings::PrivateBrowsingEnabled, enabled);
}

void WebSettings::resetPrivateBrowsingEnabled() {
    m_settings->resetAttribute(QWebSettings::PrivateBrowsingEnabled);
}

bool WebSettings::zoomTextOnly() const {
    return m_settings->testAttribute(QWebSettings::ZoomTextOnly);
}

void WebSettings::setZoomTextOnly(bool text) {
    m_settings->setAttribute(QWebSettings::ZoomTextOnly, text);
}

void WebSettings::resetZoomTextOnly() {
    m_settings->resetAttribute(QWebSettings::ZoomTextOnly);
}

bool WebSettings::developerExtrasEnabled() const {
    return m_settings->testAttribute(QWebSettings::DeveloperExtrasEnabled);
}

void WebSettings::setDeveloperExtrasEnabled(bool enabled) {
    m_settings->setAttribute(QWebSettings::DeveloperExtrasEnabled, enabled);
}

void WebSettings::resetDeveloperExtrasEnabled() {
    m_settings->resetAttribute(QWebSettings::DeveloperExtrasEnabled);
}

int WebSettings::defaultFixedFontSize() const {
    return m_settings->fontSize(QWebSettings::DefaultFixedFontSize);
}

void WebSettings::setDefaultFixedFontSize(int size) {
    m_settings->setFontSize(QWebSettings::DefaultFixedFontSize, size);
}

void WebSettings::resetDefaultFixedFontSize() {
    m_settings->resetFontSize(QWebSettings::DefaultFixedFontSize);
}

int WebSettings::defaultFontSize() const {
    return m_settings->fontSize(QWebSettings::DefaultFontSize);
}

void WebSettings::setDefaultFontSize(int size) {
    m_settings->setFontSize(QWebSettings::DefaultFontSize, size);
}

void WebSettings::resetDefaultFontSize() {
    m_settings->resetFontSize(QWebSettings::DefaultFontSize);
}

int WebSettings::minimumFontSize() const {
    return m_settings->fontSize(QWebSettings::MinimumFontSize);
}

void WebSettings::setMinimumFontSize(int size) {
    m_settings->setFontSize(QWebSettings::MinimumFontSize, size);
}

void WebSettings::resetMinimumFontSize() {
    m_settings->resetFontSize(QWebSettings::MinimumFontSize);
}

int WebSettings::minimumLogicalFontSize() const {
    return m_settings->fontSize(QWebSettings::MinimumLogicalFontSize);
}

void WebSettings::setMinimumLogicalFontSize(int size) {
    m_settings->setFontSize(QWebSettings::MinimumLogicalFontSize, size);
}

void WebSettings::resetMinimumLogicalFontSize() {
    m_settings->resetFontSize(QWebSettings::MinimumLogicalFontSize);
}

QString WebSettings::cursiveFontFamily() const {
    return m_settings->fontFamily(QWebSettings::CursiveFont);
}

void WebSettings::setCursiveFontFamily(const QString &family) {
    m_settings->setFontFamily(QWebSettings::CursiveFont, family);
}

void WebSettings::resetCursiveFontFamily() {
    m_settings->resetFontFamily(QWebSettings::CursiveFont);
}

QString WebSettings::fantasyFontFamily() const {
    return m_settings->fontFamily(QWebSettings::FantasyFont);
}

void WebSettings::setFantasyFontFamily(const QString &family) {
    m_settings->setFontFamily(QWebSettings::FantasyFont, family);
}

void WebSettings::resetFantasyFontFamily() {
    m_settings->resetFontFamily(QWebSettings::FantasyFont);
}

QString WebSettings::fixedFontFamily() const {
    return m_settings->fontFamily(QWebSettings::FixedFont);
}

void WebSettings::setFixedFontFamily(const QString &family) {
    m_settings->setFontFamily(QWebSettings::FixedFont, family);
}

void WebSettings::resetFixedFontFamily() {
    m_settings->resetFontFamily(QWebSettings::FixedFont);
}

QString WebSettings::sansSerifFontFamily() const {
    return m_settings->fontFamily(QWebSettings::SansSerifFont);
}

void WebSettings::setSansSerifFontFamily(const QString &family) {
    m_settings->setFontFamily(QWebSettings::SansSerifFont, family);
}

void WebSettings::resetSansSerifFontFamily() {
    m_settings->resetFontFamily(QWebSettings::SansSerifFont);
}

QString WebSettings::serifFontFamily() const {
    return m_settings->fontFamily(QWebSettings::SerifFont);
}

void WebSettings::setSerifFontFamily(const QString &family) {
    m_settings->setFontFamily(QWebSettings::SerifFont, family);
}

void WebSettings::resetSerifFontFamily() {
    m_settings->resetFontFamily(QWebSettings::SerifFont);
}

QString WebSettings::standardFontFamily() const {
    return m_settings->fontFamily(QWebSettings::StandardFont);
}

void WebSettings::setStandardFontFamily(const QString &family) {
    m_settings->setFontFamily(QWebSettings::StandardFont, family);
}

void WebSettings::resetStandardFontFamily() {
    m_settings->resetFontFamily(QWebSettings::StandardFont);
}

#include "moc_websettings_p.cpp"
