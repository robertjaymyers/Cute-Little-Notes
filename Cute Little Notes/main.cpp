#include "CuteLittleNotes.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setWindowIcon(QIcon(":/CuteLittleNotes/IconsBuiltIn/cute-little-notes-app-icon.ico"));
	a.setAttribute(Qt::AA_DontShowIconsInMenus);
	CuteLittleNotes w;
	//w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	w.show();
	return a.exec();
}
