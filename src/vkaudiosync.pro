#  VKAudioSync
#  Copyright (C) 2011 Denis Medved <thebucefal@gmail.com>
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
QT += qt webkit network xml thread debug

TEMPLATE = app

TARGET = vkaudiosync

DESTDIR = bin

MOC_DIR = build

OBJECTS_DIR = build

TRANSLATIONS += \
	translations/main_en.ts \
	translations/main_ru.ts

RESOURCES += \
	icons.qrc

DEFINES += "VK_APPLICATION_ID=$(shell cat VK_APPLICATION_ID.txt)" # application id mast put to VK_APPLICATION_ID file

HEADERS += \
	audioitemdelegate.h \
	audiolistmodel.h \
	mainwindow.h \
	appsettings.h \
	synchservice.h \
	downloader.h \
	vk/vkservice.h

FORMS += \
	ui/mainwindow.ui

SOURCES += \
	audioitemdelegate.cpp \
	audiolistmodel.cpp \
	main.cpp \
	mainwindow.cpp \
	appsettings.cpp \
	synchservice.cpp \
	downloader.cpp \
	vk/vkservice.cpp

OTHER_FILES += \
	share/applications/vkaudiosync.desktop \
	../README \
	../AUTHORS \
	../.gitignore

unix {
	target.path = /usr/bin

	applications.path = /usr/share/applications
	applications.files = share/applications/vkaudiosync.desktop

	icons.path = /usr/share/icons/hicolor/64x64/apps
	icons.files = share/icons/hicolor/64x64/apps/*

	data.path = /usr/share/vkaudiosync
	data.files = share/vkaudiosync/*

	INSTALLS += target applications icons data
}






