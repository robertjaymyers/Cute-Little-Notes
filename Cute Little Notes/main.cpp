/*
This file is part of Cute Little Notes.
	Cute Little Notes is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	Cute Little Notes is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	You should have received a copy of the GNU General Public License
	along with Cute Little Notes.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "CuteLittleNotes.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setWindowIcon(QIcon(":/CuteLittleNotes/IconsBuiltIn/cute-little-notes-app-icon.ico"));
	a.setAttribute(Qt::AA_DontShowIconsInMenus);
	CuteLittleNotes w;
	w.show();
	return a.exec();
}
