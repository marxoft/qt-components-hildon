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
 
function dateStringFromSecs(s) {
    var date = new Date(s * 1000);
    var day = date.getDate();
    var month = date.getMonth() + 1;
    var year = date.getFullYear();
    
    if (day < 10) {
        day = "0" + day;
    }
    
    if (month < 10) {
        month = "0" + month;
    }
    
    return day + "/" + month + "/" + year;
}

function timeStringFromSecs(s) {
    var date = new Date(s * 1000);
    var hours = date.getHours();
    var mins = date.getMinutes();
    var pm = hours > 11;
    
    if (pm) {
        hours -= 12;
    }
    
    if (mins < 10) {
        mins = "0" + mins;
    }
    
    return hours + ":" + mins + (pm ? " pm" : " am");
}

function durationFromSecs(s) {
    var date = new Date(s * 1000);
    var hours = date.getHours();
    var mins = date.getMinutes();
    var secs = date.getSeconds();
    
    if (hours < 10) {
        hours = "0" + hours;
    }
    
    if (mins < 10) {
        mins = "0" + mins;
    }
    
    if (secs < 10) {
        secs = "0" + secs;
    }
    
    return hours + ":" + mins + ":" + secs;
}

function fileSizeFromBytes(b) {
    var kb = 1024;
    var mb = kb * 1024;
    var gb = mb * 1024;
    
    if (b > gb) {
        return Math.floor(b / gb) + " GB";
    }
    
    if (b > mb) {
        return Math.floor(b / mb) + " MB";
    }
    
    if (b > kb) {
        return Math.floor(b / kb) + " kB";
    }
    
    return b + " B";
}
