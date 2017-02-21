/*
 * Copyright (C) 2017 Stuart Howarth <showarth@marxoft.co.uk>
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

import QtQuick 1.0

/*!
    \class GridLayout
    \brief A QtQuick Grid with some additional method for adding, inserting and removing items.
    
    \ingroup components    
*/
Grid {
    id: root
    
    /*!
        \brief Adds the specified \a item to the layout.
        @param type:Item item
    */
    function addItem(item) {
        item.parent = root;
    }
    
    /*!
        \brief Inserts the specified \a item to the layout before the specified \a index.
        @param type:int index
        @param type:Item item
    */
    function insertItem(index, item) {
        if ((index < 0) || (index >= children.length)) {
            return;
        }
        
        var items = [];
        
        for (var i = children.length - 1; i >= 0; i--) {
            items.unshift(children[i]);
            children[i].parent = null;
        }
        
        items.splice(index, 0, item);
        
        for (var i = 0; i < items.length; i++) {
            items[i].parent = root;
        }
    }
    
    /*!
        \brief Returns the item at the specified \a index, or \c null if \a index is out of range.
        @param type:int index
        @return type:Item item
    */
    function itemAt(index) {
        if ((index >= 0) && (index < children.length)) {
            return children[index];
        }
        
        return null;
    }
    
    /*!
        \brief Removes the specified \a item from the layout and sets its parent to \c null.
        @param type:Item item
    */
    function removeItem(item) {
        for (var i = 0; i < children.length; i++) {
            if (children[i] == item) {
                item.parent = null;
            }
        }
    }
}
