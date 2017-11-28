#
# This file is part of crash-reporter
#
#  Copyright (C) 2017 Jolla Ltd.
#  Contact: Martin Kampas <martin.kampas@jolla.com>
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public License
#  version 2.1 as published by the Free Software Foundation.
#
#  This program is distributed in the hope that it will be useful, but
#  WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
#  Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public
#  License along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
#  02110-1301 USA
#
#
include(../../crash-reporter-conf.pri)

TEMPLATE = app
TARGET = crash-reporter-storagemon

packagesExist(qt5-boostable) {
    DEFINES += HAS_BOOSTER
    PKGCONFIG += qt5-boostable
} else {
    warning("qt5-boostable not available; startup times will be slower")
}

INCLUDEPATH += . \
               ../libs/coredir \
               ../libs/utils \
               ../libs/logger \
               ../libs/settings \
               ../libs \
               ../libs/notification \

LIBS += ../../lib/libcrashreporter.so \

QT += dbus
QT -= gui

SOURCES += storagemon.cpp

target.path = $$CREPORTER_SYSTEM_LIBEXEC
INSTALLS += target
