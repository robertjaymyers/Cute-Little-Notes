#include "CuteLittleNotes.h"
#include <QInputDialog>
#include <QDebug>
#include <QTextCursor>
#include <QClipboard>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QColorDialog>
#include <QSettings>
#include <QCloseEvent>
#include <QTextToSpeech>
#include <fstream>
#include <filesystem>

// Possible TODO: Hide existing title bar and create a custom one (this will allow styling)

CuteLittleNotes::CuteLittleNotes(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.textEdit->document()->setDefaultStyleSheet("a{text-decoration:none;}");

	//this->setStyleSheet("QWidget{ background-color: rgb(0, 0, 0); color: rgb(255, 255, 255); }");

	qDebug() << appExecutablePath;

	ui.mainToolBar->setContextMenuPolicy(Qt::PreventContextMenu);
	ui.mainToolBar->insertSeparator(ui.actionComment); // Comment is 1st icon in Jot section of toolbar, so we place separator before it.

	ui.menuPrefComment->menuAction()->setVisible(false);
	ui.menuPrefListTitle->menuAction()->setVisible(false);
	ui.menuPrefMarkDone->menuAction()->setVisible(false);
	ui.menuPrefMarkScrapped->menuAction()->setVisible(false);

	// Give toolbar button instance of action a unique name, so that it can be referenced in stylesheet.
	// This name should be the same as what is in Cute Little Notes Theme Creator, to ensure themes will work correctly.
	ui.mainToolBar->widgetForAction(ui.actionNew)->setObjectName("toolbarButtonActionNew");
	ui.mainToolBar->widgetForAction(ui.actionOpen)->setObjectName("toolbarButtonActionOpen");
	ui.mainToolBar->widgetForAction(ui.actionSave)->setObjectName("toolbarButtonActionSave");
	ui.mainToolBar->widgetForAction(ui.actionComment)->setObjectName("toolbarButtonActionComment");
	ui.mainToolBar->widgetForAction(ui.actionListTitle)->setObjectName("toolbarButtonActionListTitle");
	ui.mainToolBar->widgetForAction(ui.actionMarkDone)->setObjectName("toolbarButtonActionMarkDone");
	ui.mainToolBar->widgetForAction(ui.actionMarkScrapped)->setObjectName("toolbarButtonActionMarkScrapped");

	/*const QString defaultStyleSheet =
		"QTextEdit{  border-color: #F2F2F2;  border-style: inset;  border-width: 1px;  background-color: #FFFFFF;  color: #000000;}"
		"QScrollBar{  background-color: #F0F0F0;}"
		"QToolBar{  background-color: #F0F0F0;  border-width: 1px 0px 1px 1px;  border-style: outset;  border-color: #B9B9B9;}"
		"QToolBar::separator{  background-color: #D3D3D3;  width: 1px;  height: 1px;  margin: 3px 3px 3px 2px;}"
		"QToolButton:hover{  background-color: #FFB4FF;  border-width: 1px;  border-style: solid;}"
		"QToolButton:hover{  border-color: #000000;}"
		"QToolButton#toolbarButtonActionNew{  qproperty-icon: url(:/CuteLittleNotes/Icon-Making/toolbar-icon-new.png);}"
		"QToolButton#toolbarButtonActionOpen{  qproperty-icon: url(:/CuteLittleNotes/Icon-Making/toolbar-icon-open.png);}"
		"QToolButton#toolbarButtonActionSave{  qproperty-icon: url(:/CuteLittleNotes/Icon-Making/toolbar-icon-save.png);}"
		"QToolButton#toolbarButtonActionComment{  qproperty-icon: url(:/CuteLittleNotes/Icon-Making/toolbar-icon-comment.png);}"
		"QToolButton#toolbarButtonActionListTitle{  qproperty-icon: url(:/CuteLittleNotes/Icon-Making/toolbar-icon-list-title.png);}"
		"QToolButton#toolbarButtonActionMarkDone{  qproperty-icon: url(:/CuteLittleNotes/Icon-Making/toolbar-icon-mark-done.png);}"
		"QToolButton#toolbarButtonActionMarkScrapped{  qproperty-icon: url(:/CuteLittleNotes/Icon-Making/toolbar-icon-mark-scrapped.png);}"
		"QMenuBar{  background-color: #FFFFFF;  color: #000000;  border-bottom-width: 1px;  border-bottom-style: solid;  border-color: #F2F2F2;}"
		"QMenuBar::item:selected{  background-color: #FFB4FF;  border-width: 1px;  border-style: solid;}"
		"QMenuBar::item:selected{  color: #000000;}"
		"QMenuBar::item:selected{  border-color: #000000;}"
		"QMenu{  background-color: #F0F0F0;  color: #000000;  border-color: #CCCCCC;  border-width: 1px;  border-style: solid;}"
		"QMenu::separator{  background-color: #D7D7D7;  width: 1px;  height: 1px;  margin: 3px 0px 3px 12px;}"
		"QMenu::item{  background-color: #F0F0F0;  margin: 2px;  padding: 2px 20px 2px 40px;  border: 1px solid transparent;}"
		"QMenu::item:selected{  background-color: #FFB4FF;}"
		"QMenu::item:selected{  color: #000000;}"
		"QMenu::indicator:non-exclusive:checked{  image: url(:/CuteLittleNotes/Icon-Making/menu-icon-checkbox-is-checked-elephant.png);}"
		"QMenu::indicator:non-exclusive:checked{  background-color: #FFB4FF;}"
		"QStatusBar{  background-color: #FFFFFF;  color: #000000;}"
		;

	this->setStyleSheet(defaultStyleSheet);*/

	setWindowTitle(winTitleUntitled + winTitlePlaceholder + " - " + winTitleProgramName);
	statusBarInit();

	if (QApplication::arguments().size() > 1)
	{
		const QString filename = QApplication::arguments().at(1);
		if (!filename.isEmpty())
		{
			std::string fileContents = "";
			std::string line;
			std::ifstream fileRead(filename.toStdString());
			while (std::getline(fileRead, line))
			{
				fileContents += line;
			}
			fileRead.close();

			ui.textEdit->clear();
			ui.textEdit->insertHtml(QString::fromStdString(fileContents));
			fileSetCurrent(filename);
			statusBar()->showMessage(tr("File loaded"), 2000);
			fileDirLastOpened = QFileInfo(filename).path();
		}
	}

	prefLoad();

	if (ui.actionPrefToggleModding->isChecked())
		moddingCheckForContent();

	for (auto& themePackage : themePackages_themesList)
		themeNamesList.append(themePackage.first);

	if (themePackages_themesList.count(themeCurrentName) == 0)
	{
		themeCurrentName = themeDefaultRevertName;
		QMessageBox::warning(this, tr("Theme Loading"), "Theme preference could not be loaded. Cute Little Notes reverted to loading the default theme.\n\nThis is most likely caused by the program attempting to load a mod theme from saved theme preference with mods turned off.");
	}

	for (auto& themePackageInstance : themePackages_themesList)
	{
		if (QFile(appExecutablePath + "/ThemeOverrides/" + themePackageInstance.first + ".ini").exists())
		{
			QSettings settings(appExecutablePath + "/ThemeOverrides/" + themePackageInstance.first + ".ini", QSettings::IniFormat);
			settings.beginGroup("ThemeJotOverrides");
			if (!settings.value("overrideTextJotMarkDone").toString().isEmpty())
				themePackageInstance.second.overrideTextJotMarkDone = settings.value("overrideTextJotMarkDone").toString();
			if (!settings.value("overrideTextJotMarkScrapped").toString().isEmpty())
				themePackageInstance.second.overrideTextJotMarkScrapped = settings.value("overrideTextJotMarkScrapped").toString();
			if (!settings.value("overrideColorJotCommentBg").isNull())
				themePackageInstance.second.overrideColorJotCommentBg = settings.value("overrideColorJotCommentBg").value<QColor>();
			if (!settings.value("overrideColorJotCommentText").isNull())
				themePackageInstance.second.overrideColorJotCommentText = settings.value("overrideColorJotCommentText").value<QColor>();
			if (!settings.value("overrideColorJotListTitleBg").isNull())
				themePackageInstance.second.overrideColorJotListTitleBg = settings.value("overrideColorJotListTitleBg").value<QColor>();
			if (!settings.value("overrideColorJotListTitleText").isNull())
				themePackageInstance.second.overrideColorJotListTitleText = settings.value("overrideColorJotListTitleText").value<QColor>();
			if (!settings.value("overrideColorJotMarkDoneBg").isNull())
				themePackageInstance.second.overrideColorJotMarkDoneBg = settings.value("overrideColorJotMarkDoneBg").value<QColor>();
			if (!settings.value("overrideColorJotMarkDoneText").isNull())
				themePackageInstance.second.overrideColorJotMarkDoneText = settings.value("overrideColorJotMarkDoneText").value<QColor>();
			if (!settings.value("overrideColorJotMarkScrappedBg").isNull())
				themePackageInstance.second.overrideColorJotMarkScrappedBg = settings.value("overrideColorJotMarkScrappedBg").value<QColor>();
			if (!settings.value("overrideColorJotMarkScrappedText").isNull())
				themePackageInstance.second.overrideColorJotMarkScrappedText = settings.value("overrideColorJotMarkScrappedText").value<QColor>();
			settings.endGroup();

			themePackageInstance.second.overridesAreEmpty = false;
		}
	}

	prefSetThemeLoadCurrentTheme();

	ui.actionNew->setShortcut(Qt::Key_N | Qt::ControlModifier);
	ui.actionOpen->setShortcut(Qt::Key_O | Qt::ControlModifier);
	ui.actionSave->setShortcut(Qt::Key_S | Qt::ControlModifier);
	ui.actionSaveAs->setShortcut(Qt::Key_S | Qt::ControlModifier | Qt::ShiftModifier);

	connect(ui.textEdit, SIGNAL(textChanged()), this, SLOT(fileDocumentModified()));
	connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(fileNew()));
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(fileOpen()));
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(fileSaveOps()));
	connect(ui.actionSaveAs, SIGNAL(triggered()), this, SLOT(fileSaveAs()));
	connect(ui.actionSaveAsPlainText, &QAction::triggered, this, &CuteLittleNotes::fileSaveAsPlainText);
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));

	// Menu - Edit
	connect(ui.actionUndo, SIGNAL(triggered()), ui.textEdit, SLOT(undo()));
	connect(ui.actionRedo, SIGNAL(triggered()), ui.textEdit, SLOT(redo()));
	connect(ui.textEdit, &QTextEdit::undoAvailable, ui.actionUndo, [=]() {
		if (ui.actionUndo->isEnabled())
			ui.actionUndo->setEnabled(false);
		else
			ui.actionUndo->setEnabled(true);
	});
	connect(ui.textEdit, &QTextEdit::redoAvailable, ui.actionRedo, [=]() {
		if (ui.actionRedo->isEnabled())
			ui.actionRedo->setEnabled(false);
		else
			ui.actionRedo->setEnabled(true);
	});
	connect(ui.actionFormattingRemoveAll, &QAction::triggered, this, &CuteLittleNotes::editFormattingRemoveAll);

	connect(ui.actionComment, SIGNAL(triggered()), this, SLOT(jotComment()));
	connect(ui.actionListTitle, SIGNAL(triggered()), this, SLOT(jotListTitle()));
	connect(ui.actionMarkDone, SIGNAL(triggered()), this, SLOT(jotMarkDone()));
	connect(ui.actionMarkScrapped, SIGNAL(triggered()), this, SLOT(jotMarkScrapped()));

	connect(ui.actionWordWrap, SIGNAL(triggered()), this, SLOT(toggleWordWrapMode()));
	
	//// ZOOM CODE
	/*ui.actionZoomIn->setShortcut(Qt::Key_Equal | Qt::ControlModifier);
	ui.actionZoomOut->setShortcut(Qt::Key_Minus | Qt::ControlModifier);
	ui.actionZoomReset->setShortcut(Qt::Key_Slash | Qt::ControlModifier);*/

	// Note that min and max range are set based on default font size.
	// If default font size is smaller or larger, it may make sense to change min and max.
	//const int zoomPerOp = 2; // Zoom per operation ratio should be the same for In and Out to avoid inconsistent zooming behavior.
	//connect(ui.actionZoomIn, &QAction::triggered, ui.textEdit, [=]() {
	//	if (zoomRange < (20 * zoomPerOp)) // Don't let range go above maximum for ZoomIn
	//	{
	//		ui.textEdit->zoomIn(zoomPerOp);
	//		zoomRange += zoomPerOp;
	//		qDebug() << zoomRange;
	//	}
	//});
	//connect(ui.actionZoomOut, &QAction::triggered, ui.textEdit, [=]() {
	//	if (zoomRange > (-2 * zoomPerOp)) // Don't let range go below minimum for ZoomOut
	//	{
	//		ui.textEdit->zoomOut(zoomPerOp);
	//		zoomRange -= zoomPerOp;
	//		qDebug() << zoomRange;
	//	}
	//});

	//connect(ui.actionZoomReset, &QAction::triggered, ui.textEdit, [=]() {
	//	if (zoomRange > 0) // Zoom range is positive, so zoom out for reset.
	//	{
	//		ui.textEdit->zoomOut(abs(zoomRange));
	//		zoomRange = 0;
	//		qDebug() << zoomRange;
	//	}
	//	else if (zoomRange < 0) // Zoom range is negative, so zoom in for reset.
	//	{
	//		ui.textEdit->zoomIn(abs(zoomRange));
	//		zoomRange = 0;
	//		qDebug() << zoomRange;
	//	}
	//});
	//// END ZOOM CODE

	toggleToolbarVis(); // Toggle gets called on init to load vis setting.
	connect(ui.actionToolbarToggleVis, &QAction::triggered, this, &CuteLittleNotes::toggleToolbarVis);

	connect(ui.actionPastePlainText, &QAction::triggered, ui.textEdit, [=]() {
		QTextCursor cursor(ui.textEdit->textCursor());
		cursor.beginEditBlock();
		QString clipboardText = QApplication::clipboard()->text();
		ui.textEdit->insertHtml(clipboardText.remove(QRegExp("<[^>]*>")));
		cursor.endEditBlock();
	});

	ui.actionPastePlainText->setShortcut(Qt::Key_V | Qt::ControlModifier | Qt::ShiftModifier);

	// Menu - Preferences
	/*connect(ui.actionPrefCommentSetColor, &QAction::triggered, this, [=]() {
		prefSetColor(colorJotCommentBg);
	});
	connect(ui.actionPrefCommentSetColor, &QAction::triggered, this, [=]() {
		prefSetColor(colorJotCommentText);
	});
	connect(ui.actionPrefListTitleSetColorBg, &QAction::triggered, this, [=]() {
		prefSetColor(colorJotListTitleBg);
	});
	connect(ui.actionPrefListTitleSetColorText, &QAction::triggered, this, [=]() {
		prefSetColor(colorJotListTitleText);
	});
	connect(ui.actionPrefMarkDoneSetColor, &QAction::triggered, this, [=]() {
		prefSetColor(colorJotMarkDone);
	});
	connect(ui.actionPrefMarkDoneSetText, &QAction::triggered, this, [=]() {
		prefSetText(textJotMarkDone);
	});
	connect(ui.actionPrefMarkScrappedSetColor, &QAction::triggered, this, [=]() {
		prefSetColor(colorJotMarkScrapped);
	});
	connect(ui.actionPrefMarkScrappedSetText, &QAction::triggered, this, [=]() {
		prefSetText(textJotMarkScrapped);
	});*/
	connect(ui.actionPrefSetJotOverrides, &QAction::triggered, this, &CuteLittleNotes::prefSetThemeOverride);
	connect(ui.actionPrefDisableOverrides, &QAction::triggered, this, &CuteLittleNotes::prefSetThemeLoadCurrentTheme);
	connect(ui.actionPrefSetTheme, &QAction::triggered, this, &CuteLittleNotes::prefSetTheme);
	connect(ui.actionPrefSaveManual, &QAction::triggered, this, [=]() {
		prefSave();
		statusBar()->showMessage(tr("Preferences saved"), 2000);
	});
}

void CuteLittleNotes::statusBarInit()
{
	statusBar()->showMessage(tr("Ready"));
}

void CuteLittleNotes::closeEvent(QCloseEvent *event)
{
	if (fileSaveModifCheck())
	{
		prefSave();
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

void CuteLittleNotes::fileDocumentModified()
{
	setWindowModified(ui.textEdit->document()->isModified());
}

void CuteLittleNotes::fileSetCurrent(const QString &filename)
{
	fileCurrent = filename;
	ui.textEdit->document()->setModified(false);
	setWindowModified(false);

	//QString displayName = fileCurrent;
	QString displayName;
	if (fileCurrent.isEmpty())
	{
		displayName = winTitleUntitled;
	}
	else
	{
		displayName = QFileInfo(fileCurrent).fileName();
	}
	setWindowTitle(displayName + winTitlePlaceholder + " - " + winTitleProgramName);
	//setWindowFilePath(displayName + " - " + windowTitleStr);
}

void CuteLittleNotes::fileNew()
{
	if (fileSaveModifCheck())
	{
		ui.textEdit->clear();
		fileSetCurrent(QString());
	}
}

void CuteLittleNotes::fileOpen()
{
	if (fileSaveModifCheck())
	{
		//QString filename = QFileDialog::getOpenFileName(this, tr("Open"), fileDirLastOpened, tr("Cute Little Notes (*.cutelittlenote);;AllFiles (*)"));
		QString filename = QFileDialog::getOpenFileName(this, tr("Open"), fileDirLastOpened, tr("Text Files (*.cutelittlenote *.txt);;AllFiles (*)"));
		if (!filename.isEmpty())
		{
			std::string fileContents = "";
			std::string line;
			std::ifstream fileRead(filename.toStdString());
			while (std::getline(fileRead, line))
			{
				fileContents += line;
			}
			fileRead.close();

			ui.textEdit->clear();
			ui.textEdit->insertHtml(QString::fromStdString(fileContents));
			fileSetCurrent(filename);
			statusBar()->showMessage(tr("File loaded"), 2000);
			fileDirLastOpened = QFileInfo(filename).path();
			applyExistingJotPrefsAll();
		}
	}

	////QString filename = QFileDialog::getOpenFileName(this, tr("Open"), "Notes", tr("Text Document (*.txt);;AllFiles (*)"));
	//QString filename = QFileDialog::getOpenFileName(this, tr("Open"), "Notes", tr("Cute Little Notes (*.cutelittlenote);;AllFiles (*)"));
	//std::string fileContents = "";

	//if (!filename.isEmpty())
	//{
	//	std::string line;
	//	std::ifstream fileRead(filename.toStdString());
	//	while (std::getline(fileRead, line))
	//	{
	//		fileContents += line;
	//	}
	//	fileRead.close();

	//	ui.textEdit->clear();
	//	ui.textEdit->insertHtml(QString::fromStdString(fileContents));
	//	//fileContentsMostRecentlySaved = QString::fromStdString(fileContents);
	//}
}

bool CuteLittleNotes::fileSaveModifCheck()
{
	if (!ui.textEdit->document()->isModified())
		return true;

	const QMessageBox::StandardButton ret
		= QMessageBox::warning(this, tr("Cute Little Notes"),
			tr("The document has been modified.\nDo you want to save your changes?"),
			QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

	switch (ret)
	{
	case QMessageBox::Save:
		return fileSaveOps();
	case QMessageBox::Cancel:
		return false;
	default:
		break;
	}

	return true;
}

bool CuteLittleNotes::fileSaveOps()
{
	if (fileCurrent.isEmpty())
	{
		return fileSaveAs();
	}
	else
	{
		return fileSave(fileCurrent);
	}
}

bool CuteLittleNotes::fileSave(const QString &filename)
{
	std::ofstream fileWrite(filename.toStdString());
	QString textEditContents = ui.textEdit->toHtml();
	if (fileWrite.is_open())
	{
		fileWrite << textEditContents.toStdString();
	}
	else
	{
		return false;
	}
	fileWrite.close();
	fileSetCurrent(filename);
	statusBar()->showMessage(tr("File saved"), 2000);
	fileDirLastSaved = QFileInfo(filename).path();
	return true;

	//if (filenameLastSaved.isEmpty())
	//{
	//	fileSaveAs();
	//}
	//else
	//{
	//	QString textEditContents = ui.textEdit->toHtml();
	//	std::string textEditContentsAsStdStr = textEditContents.toStdString();

	//	std::ofstream fileWrite(filenameLastSaved.toStdString());
	//	if (fileWrite.is_open())
	//	{
	//		fileWrite << textEditContentsAsStdStr;
	//	}
	//	fileWrite.close();

	//	//fileContentsMostRecentlySaved = QString::fromStdString(textEditContentsAsStdStr);

	//	QMessageBox::information(this, "Save Log To File", "Copied log contents to " + filenameLastSaved);
	//}
}

bool CuteLittleNotes::fileSaveAs()
{
	QFileDialog dialog(this, tr("Save As"), fileDirLastSaved, tr("Text Files (*.cutelittlenote *.txt);;AllFiles (*)"));
	dialog.setWindowModality(Qt::WindowModal);
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	if (dialog.exec() != QFileDialog::Accepted)
		return false;
	return fileSave(dialog.selectedFiles().first());

	////QString filename = QFileDialog::getSaveFileName(this, tr("Save As"), "Notes/MyNotes.txt", tr("Text Document (*.txt);;AllFiles (*)"));
	//QString filename = QFileDialog::getSaveFileName(this, tr("Save As"), "Notes/MyNotes.cutelittlenote", tr("Cute Little Notes (*.cutelittlenote);;AllFiles (*)"));

	//if (!filename.isEmpty())
	//{
	//	QString textEditContents = ui.textEdit->toHtml();
	//	std::string textEditContentsAsStdStr = textEditContents.toStdString();
	//	
	//	std::ofstream fileWrite(filename.toStdString());
	//	if (fileWrite.is_open())
	//	{
	//		fileWrite << textEditContentsAsStdStr;
	//	}
	//	fileWrite.close();

	//	filenameLastSaved = filename;
	//	//fileContentsMostRecentlySaved = QString::fromStdString(textEditContentsAsStdStr);

	//	QMessageBox::information(this, "Save Log To File", "Copied log contents to " + filename);
	//	
	//	/*QFile fileWrite(filename);
	//	if (!fileWrite.open(QIODevice::WriteOnly | QIODevice::Text))
	//		return;

	//	QTextStream out(&filename);
	//	out << ui.textEdit->toPlainText();

	//	fileWrite.close();*/

	//	/*else
	//	{
	//		QMessageBox::warning(this, "Save Log To File", "Copy failed, nothing was found in the log to copy to file.");
	//	}*/
	//}
}

void CuteLittleNotes::fileSaveAsPlainText()
{
	QFileDialog dialog(this, tr("Save As Plain Text"), fileDirLastSaved, tr("Text Files (*.cutelittlenote *.txt);;AllFiles (*)"));
	dialog.setWindowModality(Qt::WindowModal);
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	if (dialog.exec() == QFileDialog::Accepted)
	{
		QString filename = dialog.selectedFiles().first();
		std::ofstream fileWrite(filename.toStdString());
		QString textEditContents = ui.textEdit->toPlainText();
		if (fileWrite.is_open())
		{
			fileWrite << textEditContents.toStdString();
			fileWrite.close();
			fileSetCurrent(filename);
			statusBar()->showMessage(tr("File saved"), 2000);
			fileDirLastSaved = QFileInfo(filename).path();
		}
	}
}

void CuteLittleNotes::jotComment()
{
	bool ok;
	QString strToAdd = QInputDialog::getText(this, tr("Insert Comment"), tr("Comment:"), QLineEdit::Normal, "", &ok, Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);

	if (ok && !strToAdd.isEmpty())
	{
		QTextCursor cursor(ui.textEdit->textCursor());
		cursor.beginEditBlock();
		ui.textEdit->insertPlainText(" ");
		ui.textEdit->insertHtml
		(
			"<a href=\"colorJotComment\"><span style=\"background-color:" + colorJotCommentBg.name() +
			"; color:" + colorJotCommentText.name() +
			";\">[" + strToAdd + "]</span></a> "
		);
		cursor.endEditBlock();
		//cursor.beginEditBlock();
		//ui.textEdit->insertPlainText(" ");
		////ui.textEdit->setTextBackgroundColor(QColor(219, 219, 219, 255));
		//ui.textEdit->setTextBackgroundColor(colorJotComment);
		////ui.textEdit->insertHtml("<comment><span style=\"background-color:" + colorJotComment.name() + "\">[" + commentToAdd + "]</span></comment>");
		//ui.textEdit->insertPlainText("[" + commentToAdd + "]");
		//ui.textEdit->setTextBackgroundColor(Qt::white);
		//ui.textEdit->insertPlainText(" ");
		//cursor.endEditBlock();
		////commentsList.append(commentToAdd);
	}
}

void CuteLittleNotes::jotListTitle()
{
	bool ok;
	QString strToAdd = QInputDialog::getText(this, tr("Insert List Title"), tr("List Title:"), QLineEdit::Normal, "", &ok, Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);

	if (ok && !strToAdd.isEmpty())
	{
		QTextCursor cursor(ui.textEdit->textCursor());
		cursor.beginEditBlock();
		ui.textEdit->insertHtml
		(
			"<a href=\"colorJotListTitle\"><h2><span style=\"background-color:" + colorJotListTitleBg.name() + 
			"; color:" + colorJotListTitleText.name() +
			"; font-weight: bold; text-transform: uppercase;\">" + strToAdd + "</span></h2></a><br />"
		);
		cursor.endEditBlock();
	}
}

void CuteLittleNotes::jotMarkDone()
{
	QTextCursor cursor(ui.textEdit->textCursor());
	cursor.beginEditBlock();
	ui.textEdit->insertPlainText(" ");
	ui.textEdit->insertHtml
	(
		"<a href=\"jotMarkDone\"><span style=\"background-color:" + colorJotMarkDoneBg.name() +
		"; color:" + colorJotMarkDoneText.name() +
		";\">" + textJotMarkDone + "</span></a> "
	);
	cursor.endEditBlock();
}

void CuteLittleNotes::jotMarkScrapped()
{
	QTextCursor cursor(ui.textEdit->textCursor());
	cursor.beginEditBlock();
	ui.textEdit->insertPlainText(" ");
	ui.textEdit->insertHtml
	(
		"<a href=\"jotMarkScrapped\"><span style=\"background-color:" + colorJotMarkScrappedBg.name() +
		"; color:" + colorJotMarkScrappedText.name() +
		";\">" + textJotMarkScrapped + "</span></a> "
	);
	cursor.endEditBlock();
}

void CuteLittleNotes::editFormattingRemoveAll()
{
	const QMessageBox::StandardButton formatRemoveChoice
		= QMessageBox::warning(this, tr("Cute Little Notes"),
			tr("Are you sure you want to remove formatting?\nThis operation cannot be undone."),
			QMessageBox::Yes | QMessageBox::No);

	if (formatRemoveChoice == QMessageBox::Yes)
	{
		ui.textEdit->setPlainText(ui.textEdit->toPlainText());
	}
}

void CuteLittleNotes::toggleToolbarVis()
{
	if (ui.actionToolbarToggleVis->isChecked())
	{
		ui.mainToolBar->setHidden(false);
	}
	else if (!ui.actionToolbarToggleVis->isChecked())
	{
		ui.mainToolBar->setHidden(true);
	}
}

void CuteLittleNotes::toggleWordWrapMode()
{
	if (ui.actionWordWrap->isChecked())
	{
		ui.textEdit->setWordWrapMode(QTextOption::WordWrap);
	}
	else if (!ui.actionWordWrap->isChecked())
	{
		ui.textEdit->setWordWrapMode(QTextOption::NoWrap);
	}
}

void CuteLittleNotes::stripFormattingFromSelectedText()
{
	QString selectedTxt = ui.textEdit->textCursor().selectedText();
	QTextCursor cursor(ui.textEdit->textCursor());
	cursor.beginEditBlock();
	cursor.removeSelectedText();
	selectedTxt.remove(QRegExp("<[^>]*>"));
	ui.textEdit->textCursor().insertText(selectedTxt);
	//ui.textEdit->setTextCursor();
	//cursor.selectedText() = cursor.selection().toPlainText();
	cursor.endEditBlock();
}

void CuteLittleNotes::pasteStripFormatting()
{
	QString selectedTxt = ui.textEdit->textCursor().selectedText();
	QTextCursor cursor(ui.textEdit->textCursor());
	cursor.beginEditBlock();
	ui.textEdit->setPlainText(selectedTxt);
	/*cursor.removeSelectedText();
	selectedTxt.remove(QRegExp("<[^>]*>"));*/
	ui.textEdit->textCursor().insertText(selectedTxt);
	cursor.endEditBlock();
}

void CuteLittleNotes::prefSetThemeOverride()
{
	bool ok;
	QString themeProperty = QInputDialog::getItem(
		this,
		tr("Override Theme Jot"),
		tr("Jot Property:"),
		jotOverrideNamesList,
		0,
		false,
		&ok,
		Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);

	if (ok && !themeProperty.isEmpty())
	{
		switch (jotOverrideNamesMap[themeProperty])
		{
		case JotNameEnums::MARK_DONE_TXT:
			if (prefSetOverrideText(textJotMarkDone, "textJotMarkDone"))
				themePackages_themesList[themeCurrentName].overrideTextJotMarkDone = textJotMarkDone;
			break;
		case JotNameEnums::MARK_SCRAPPED_TXT:
			if (prefSetOverrideText(textJotMarkScrapped, "textJotMarkDone"))
				themePackages_themesList[themeCurrentName].overrideTextJotMarkScrapped = textJotMarkScrapped;
			break;
		case JotNameEnums::COMMENT_BG_COL:
			if (prefSetOverrideColor(colorJotCommentBg, "colorJotCommentBg"))
				themePackages_themesList[themeCurrentName].overrideColorJotCommentBg = colorJotCommentBg;
			break;
		case JotNameEnums::COMMENT_TXT_COL:
			if (prefSetOverrideColor(colorJotCommentText, "colorJotCommentText"))
				themePackages_themesList[themeCurrentName].overrideColorJotCommentText = colorJotCommentText;
			break;
		case JotNameEnums::LIST_TITLE_BG_COL:
			if (prefSetOverrideColor(colorJotListTitleBg, "colorJotListTitleBg"))
				themePackages_themesList[themeCurrentName].overrideColorJotListTitleBg = colorJotListTitleBg;
			break;
		case JotNameEnums::LIST_TITLE_TXT_COL:
			if (prefSetOverrideColor(colorJotListTitleText, "colorJotListTitleText"))
				themePackages_themesList[themeCurrentName].overrideColorJotListTitleText = colorJotListTitleText;
			break;
		case JotNameEnums::MARK_DONE_BG_COL:
			if (prefSetOverrideColor(colorJotMarkDoneBg, "colorJotMarkDoneBg"))
				themePackages_themesList[themeCurrentName].overrideColorJotMarkDoneBg = colorJotMarkDoneBg;
			break;
		case JotNameEnums::MARK_DONE_TXT_COL:
			if (prefSetOverrideColor(colorJotMarkDoneText, "colorJotMarkDoneText"))
				themePackages_themesList[themeCurrentName].overrideColorJotMarkDoneText = colorJotMarkDoneText;
			break;
		case JotNameEnums::MARK_SCRAPPED_BG_COL:
			if (prefSetOverrideColor(colorJotMarkScrappedBg, "colorJotMarkScrappedBg"))
				themePackages_themesList[themeCurrentName].overrideColorJotMarkScrappedBg = colorJotMarkScrappedBg;
			break;
		case JotNameEnums::MARK_SCRAPPED_TXT_COL:
			if (prefSetOverrideColor(colorJotMarkScrappedText, "colorJotMarkScrappedText"))
				themePackages_themesList[themeCurrentName].overrideColorJotMarkScrappedText = colorJotMarkScrappedText;
			break;
		}
		applyExistingJotPrefsAll();
	}
}

//void CuteLittleNotes::prefSetColor(QColor &color)
//{
//	QColor colorEdited = QColorDialog::getColor(color, this, "Choose Color");
//	if (colorEdited.isValid())
//	{
//		color = colorEdited;
//	}
//}

bool CuteLittleNotes::prefSetOverrideColor(QColor &color, const QString colorValName)
{
	QColor colorEdited = QColorDialog::getColor(color, this, "Choose Color");
	if (colorEdited.isValid())
	{
		color = colorEdited;
		jotOverrideWasUsed = true;
		themePackages_themesList[themeCurrentName].overridesAreEmpty = false;
		/*QSettings settings(appExecutablePath + "/ThemeOverrides/" + themeCurrentName + ".ini", QSettings::IniFormat);
		settings.beginGroup("ThemeJotOverrides");
		settings.setValue(colorValName, color.name());
		settings.endGroup();
		if (!settings.isWritable())
			qDebug() << "Couldn't save override to file due to permissions.";*/
		return true;
	}
	return false;
}

bool CuteLittleNotes::prefSetOverrideText(QString &text, const QString textValName)
{
	bool ok;
	QString textEdited = QInputDialog::getText(this, tr("Set Text"), tr("Text:"), QLineEdit::Normal, text, &ok, Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
	if (ok && !textEdited.isEmpty())
	{
		text = textEdited;
		jotOverrideWasUsed = true;
		themePackages_themesList[themeCurrentName].overridesAreEmpty = false;
		/*QSettings settings(appExecutablePath + "/ThemeOverrides/" + themeCurrentName + ".ini", QSettings::IniFormat);
		settings.beginGroup("ThemeJotOverrides");
		settings.setValue(textValName, text);
		settings.endGroup();
		if (!settings.isWritable())
			qDebug() << "Couldn't save override to file due to permissions.";*/
		return true;
	}
	return false;
}

//void CuteLittleNotes::prefSetText(QString &text)
//{
//	bool ok;
//	QString textEdited = QInputDialog::getText(this, tr("Set Text"), tr("Text:"), QLineEdit::Normal, text, &ok, Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
//	if (ok && !textEdited.isEmpty())
//		text = textEdited;
//}

void CuteLittleNotes::prefSetTheme()
{
	bool ok;
	QString theme = QInputDialog::getItem(this, tr("Set Theme"), tr("Theme:"), themeNamesList, themeCurrentIndex, false, &ok, Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
	if (ok && !theme.isEmpty())
	{
		themeCurrentName = theme;
		prefSetThemeLoadCurrentTheme();
		//prefSetThemeIcons(themeIconsMap_themesList[themeCurrent]);
	}
}

void CuteLittleNotes::prefSetThemeLoadCurrentTheme()
{
	/*tempPrevTextJotMarkDone = textJotMarkDone;
	tempPrevTextJotMarkScrapped = textJotMarkScrapped;
	tempPrevColorJotCommentBg = colorJotCommentBg;
	tempPrevColorJotCommentText = colorJotCommentText;
	tempPrevColorJotListTitleBg = colorJotListTitleBg;
	tempPrevColorJotListTitleText = colorJotListTitleText;
	tempPrevColorJotMarkDoneBg = colorJotMarkDoneBg;
	tempPrevColorJotMarkDoneText = colorJotMarkDoneText;
	tempPrevColorJotMarkScrappedBg = colorJotMarkScrappedBg;
	tempPrevColorJotMarkScrappedText = colorJotMarkScrappedText;*/

	themeCurrentIndex = themeNamesList.indexOf(themeCurrentName);
	this->setStyleSheet(themePackages_themesList[themeCurrentName].themeStylesheet);
	
	if (themePackages_themesList[themeCurrentName].overrideTextJotMarkDone.isEmpty() ||
		ui.actionPrefDisableOverrides->isChecked())
		textJotMarkDone = themePackages_themesList[themeCurrentName].textJotMarkDone;
	else
		textJotMarkDone = themePackages_themesList[themeCurrentName].overrideTextJotMarkDone;

	if (themePackages_themesList[themeCurrentName].overrideTextJotMarkScrapped.isEmpty() ||
		ui.actionPrefDisableOverrides->isChecked())
		textJotMarkScrapped = themePackages_themesList[themeCurrentName].textJotMarkScrapped;
	else
		textJotMarkScrapped = themePackages_themesList[themeCurrentName].overrideTextJotMarkScrapped;

	if (!themePackages_themesList[themeCurrentName].overrideColorJotCommentBg.isValid() ||
		ui.actionPrefDisableOverrides->isChecked())
		colorJotCommentBg = themePackages_themesList[themeCurrentName].colorJotCommentBg;
	else
		colorJotCommentBg = themePackages_themesList[themeCurrentName].overrideColorJotCommentBg;

	if (!themePackages_themesList[themeCurrentName].overrideColorJotCommentText.isValid() ||
		ui.actionPrefDisableOverrides->isChecked())
		colorJotCommentText = themePackages_themesList[themeCurrentName].colorJotCommentText;
	else
		colorJotCommentText = themePackages_themesList[themeCurrentName].overrideColorJotCommentText;

	if (!themePackages_themesList[themeCurrentName].overrideColorJotListTitleBg.isValid() ||
		ui.actionPrefDisableOverrides->isChecked())
		colorJotListTitleBg = themePackages_themesList[themeCurrentName].colorJotListTitleBg;
	else
		colorJotListTitleBg = themePackages_themesList[themeCurrentName].overrideColorJotListTitleBg;

	if (!themePackages_themesList[themeCurrentName].overrideColorJotListTitleText.isValid() ||
		ui.actionPrefDisableOverrides->isChecked())
		colorJotListTitleText = themePackages_themesList[themeCurrentName].colorJotListTitleText;
	else
		colorJotListTitleText = themePackages_themesList[themeCurrentName].overrideColorJotListTitleText;

	if (!themePackages_themesList[themeCurrentName].overrideColorJotMarkDoneBg.isValid() ||
		ui.actionPrefDisableOverrides->isChecked())
		colorJotMarkDoneBg = themePackages_themesList[themeCurrentName].colorJotMarkDoneBg;
	else
		colorJotMarkDoneBg = themePackages_themesList[themeCurrentName].overrideColorJotMarkDoneBg;

	if (!themePackages_themesList[themeCurrentName].overrideColorJotMarkDoneText.isValid() ||
		ui.actionPrefDisableOverrides->isChecked())
		colorJotMarkDoneText = themePackages_themesList[themeCurrentName].colorJotMarkDoneText;
	else
		colorJotMarkDoneText = themePackages_themesList[themeCurrentName].overrideColorJotMarkDoneText;

	if (!themePackages_themesList[themeCurrentName].overrideColorJotMarkScrappedBg.isValid() ||
		ui.actionPrefDisableOverrides->isChecked())
		colorJotMarkScrappedBg = themePackages_themesList[themeCurrentName].colorJotMarkScrappedBg;
	else
		colorJotMarkScrappedBg = themePackages_themesList[themeCurrentName].overrideColorJotMarkScrappedBg;

	if (!themePackages_themesList[themeCurrentName].overrideColorJotMarkScrappedText.isValid() ||
		ui.actionPrefDisableOverrides->isChecked())
		colorJotMarkScrappedText = themePackages_themesList[themeCurrentName].colorJotMarkScrappedText;
	else
		colorJotMarkScrappedText = themePackages_themesList[themeCurrentName].overrideColorJotMarkScrappedText;

	applyExistingJotPrefsAll();

	/*QString textEditContents = ui.textEdit->toHtml();
	qDebug() << textEditContents;
	textEditContents.replace("background-color:" + tempPrevColorJotCommentBg.name(), "background-color:" + colorJotCommentBg.name());
	textEditContents.replace(" color:" + tempPrevColorJotCommentText.name(), " color:" + colorJotCommentText.name());
	textEditContents.replace("background-color:" + tempPrevColorJotListTitleBg.name(), "background-color:" + colorJotListTitleBg.name());
	textEditContents.replace(" color:" + tempPrevColorJotListTitleText.name(), " color:" + colorJotListTitleText.name());
	textEditContents.replace("background-color:" + tempPrevColorJotMarkDoneBg.name(), "background-color:" + colorJotMarkDoneBg.name());
	textEditContents.replace(" color:" + tempPrevColorJotMarkDoneText.name(), " color:" + colorJotMarkDoneText.name());
	textEditContents.replace("background-color:" + tempPrevColorJotMarkScrappedBg.name(), "background-color:" + colorJotMarkScrappedBg.name());
	textEditContents.replace(" color:" + tempPrevColorJotMarkScrappedText.name(), " color:" + colorJotMarkScrappedText.name());
	qDebug() << textEditContents;
	ui.textEdit->setHtml(textEditContents);*/

	/*this->setStyleSheet(themePackages_themesList[themeCurrent].themeStylesheet);
	textJotMarkDone = themePackages_themesList[themeCurrent].textJotMarkDone;
	textJotMarkScrapped = themePackages_themesList[themeCurrent].textJotMarkScrapped;
	colorJotCommentBg = themePackages_themesList[themeCurrent].colorJotCommentBg;
	colorJotCommentText = themePackages_themesList[themeCurrent].colorJotCommentText;
	colorJotListTitleBg = themePackages_themesList[themeCurrent].colorJotListTitleBg;
	colorJotListTitleText = themePackages_themesList[themeCurrent].colorJotListTitleText;
	colorJotMarkDoneBg = themePackages_themesList[themeCurrent].colorJotMarkDoneBg;
	colorJotMarkDoneText = themePackages_themesList[themeCurrent].colorJotMarkDoneText;
	colorJotMarkScrappedBg = themePackages_themesList[themeCurrent].colorJotMarkScrappedBg;
	colorJotMarkScrappedText = themePackages_themesList[themeCurrent].colorJotMarkScrappedText;*/
}

void CuteLittleNotes::applyExistingJotPrefsAll()
{
	std::string textEditContents = ui.textEdit->toHtml().toStdString();

	textEditContents = applyExistingJotPrefs("<a href=\"colorJotComment\">", ";", textEditContents, { colorJotCommentText.name(), colorJotCommentBg.name() }, JotPrefType::COLOR);
	textEditContents = applyExistingJotPrefs("<a href=\"colorJotListTitle\">", ";", textEditContents, { colorJotListTitleText.name(), colorJotListTitleBg.name() }, JotPrefType::COLOR);
	textEditContents = applyExistingJotPrefs("<a href=\"jotMarkDone\">", ";", textEditContents, { colorJotMarkDoneText.name(), colorJotMarkDoneBg.name() }, JotPrefType::COLOR);
	textEditContents = applyExistingJotPrefs("<a href=\"jotMarkScrapped\">", ";", textEditContents, { colorJotMarkScrappedText.name(), colorJotMarkScrappedBg.name() }, JotPrefType::COLOR);
	textEditContents = applyExistingJotPrefs("<a href=\"jotMarkDone\">", ";", textEditContents, { textJotMarkDone }, JotPrefType::TEXT);
	textEditContents = applyExistingJotPrefs("<a href=\"jotMarkScrapped\">", ";", textEditContents, { textJotMarkScrapped }, JotPrefType::TEXT);

	ui.textEdit->clear();
	ui.textEdit->insertHtml(QString::fromStdString(textEditContents));
	qDebug() << QString::fromStdString(textEditContents);
}

std::string CuteLittleNotes::applyExistingJotPrefs(const std::string strBegin, const std::string strEnd, const std::string &textEditContents, const QStringList replacements, JotPrefType prefType)
{
	std::string textEditContentsEdited = textEditContents;
	int posFound = 0;
	if (prefType == JotPrefType::COLOR)
	{
		const std::string colorTextStyleId = " color:";
		const std::string colorBgStyleId = " background-color:";
		while (textEditContentsEdited.find(strBegin, posFound) != std::string::npos)
		{
			posFound = textEditContentsEdited.find(strBegin, posFound);

			int posBeginColorText = textEditContentsEdited.find(colorTextStyleId, posFound) + colorTextStyleId.length();
			int posEndColorText = textEditContentsEdited.find(strEnd, posBeginColorText) + 1 - strEnd.length();
			textEditContentsEdited.replace(posBeginColorText, posEndColorText - posBeginColorText, replacements[0].toStdString());

			int posBeginColorBg = textEditContentsEdited.find(colorBgStyleId, posFound) + colorBgStyleId.length();
			int posEndColorBg = textEditContentsEdited.find(strEnd, posBeginColorBg) + 1 - strEnd.length();
			textEditContentsEdited.replace(posBeginColorBg, posEndColorBg - posBeginColorBg, replacements[1].toStdString());

			posFound = posEndColorBg;
		}
	}
	else if (prefType == JotPrefType::TEXT)
	{
		const std::string spanId = "<span";
		const std::string bracketBeginId = ">";
		const std::string bracketEndId = "<";
		while (textEditContentsEdited.find(strBegin, posFound) != std::string::npos)
		{
			posFound = textEditContentsEdited.find(strBegin, posFound);

			int posSpanId = textEditContentsEdited.find(spanId, posFound) + spanId.length();
			int posBegin = textEditContentsEdited.find(bracketBeginId, posSpanId) + bracketBeginId.length();
			int posEnd = textEditContentsEdited.find(bracketEndId, posBegin) + 1 - bracketEndId.length();
			textEditContentsEdited.replace(posBegin, posEnd - posBegin, replacements[0].toStdString());

			posFound = posEnd;
		}
	}
	return textEditContentsEdited;
}

//void CuteLittleNotes::prefSetThemeIcons(std::map<ThemeIconsKey, QString> &themeIconsMap)
//{
//	for (auto const& themeIcon : themeIconsMap)
//	{
//		switch (themeIcon.first)
//		{
//		case ThemeIconsKey::FILE_NEW:
//			ui.actionNew->setIcon(QIcon(themeIcon.second));
//			break;
//		case ThemeIconsKey::FILE_OPEN:
//			ui.actionOpen->setIcon(QIcon(themeIcon.second));
//			break;
//		case ThemeIconsKey::FILE_SAVE:
//			ui.actionSave->setIcon(QIcon(themeIcon.second));
//			break;
//		case ThemeIconsKey::JOT_COMMENT:
//			ui.actionComment->setIcon(QIcon(themeIcon.second));
//			break;
//		case ThemeIconsKey::JOT_LIST_TITLE:
//			ui.actionListTitle->setIcon(QIcon(themeIcon.second));
//			break;
//		case ThemeIconsKey::JOT_MARK_DONE:
//			ui.actionMarkDone->setIcon(QIcon(themeIcon.second));
//			break;
//		case ThemeIconsKey::JOT_MARK_SCRAPPED:
//			ui.actionMarkScrapped->setIcon(QIcon(themeIcon.second));
//			break;
//		}
//	}
//	//ui.actionComment->setIcon(QIcon(":/CuteLittleNotes/Icon-Making/ThemeGray/toolbar-icon-comment-theme-gray.png"));
//	//prefSetTheme(themeIconsMap_themeGray);
//	//prefSetTheme(themeIconsMap_themeDefault);
//	//ui.actionComment->setIcon(QIcon("C:/Users/Robert/source/repos/Cute Little Notes/Cute Little Notes/Icon-Making/icon-16.png"));
//}

void CuteLittleNotes::prefLoad()
{
	QSettings settings(appExecutablePath + "/preferences.ini", QSettings::IniFormat);

	/*settings.beginGroup("Colors");
	if (!settings.value("colorJotComment").isNull())
		colorJotComment = settings.value("colorJotComment").value<QColor>();
	if (!settings.value("colorJotListTitleBg").isNull())
		colorJotListTitleBg = settings.value("colorJotListTitleBg").value<QColor>();
	if (!settings.value("colorJotListTitleText").isNull())
		colorJotListTitleText = settings.value("colorJotListTitleText").value<QColor>();
	if (!settings.value("colorJotMarkDone").isNull())
		colorJotMarkDone = settings.value("colorJotMarkDone").value<QColor>();
	if (!settings.value("colorJotMarkScrapped").isNull())
		colorJotMarkScrapped = settings.value("colorJotMarkScrapped").value<QColor>();
	settings.endGroup();

	settings.beginGroup("Text");
	if (!settings.value("textJotMarkDone").toString().isEmpty())
		textJotMarkDone = settings.value("textJotMarkDone").toString();
	if (!settings.value("textJotMarkScrapped").toString().isEmpty())
		textJotMarkScrapped = settings.value("textJotMarkScrapped").toString();
	settings.endGroup();*/

	settings.beginGroup("ThemeCurrent");
	if (!settings.value("themeCurrentName").toString().isEmpty())
		themeCurrentName = settings.value("themeCurrentName").toString();
	settings.endGroup();

	settings.beginGroup("Toggles");
	if (!settings.value("actionToolbarToggleVis").isNull())
		ui.actionToolbarToggleVis->setChecked(settings.value("actionToolbarToggleVis").toBool());
	if (!settings.value("actionPrefToggleModding").isNull())
		ui.actionPrefToggleModding->setChecked(settings.value("actionPrefToggleModding").toBool());
	if (!settings.value("actionPrefDisableOverrides").isNull())
		ui.actionPrefDisableOverrides->setChecked(settings.value("actionPrefDisableOverrides").toBool());
	settings.endGroup();

	settings.beginGroup("FilePathMemory");
	if (!settings.value("fileDirLastOpened").toString().isEmpty())
		fileDirLastOpened = settings.value("fileDirLastOpened").toString();
	if (!settings.value("fileDirLastSaved").toString().isEmpty())
		fileDirLastSaved = settings.value("fileDirLastSaved").toString();
	settings.endGroup();
}

void CuteLittleNotes::prefSave()
{
	/*settings.beginGroup("Colors");
	settings.setValue("colorJotComment", colorJotComment.name());
	settings.setValue("colorJotListTitleBg", colorJotListTitleBg.name());
	settings.setValue("colorJotListTitleText", colorJotListTitleText.name());
	settings.setValue("colorJotMarkDone", colorJotMarkDone.name());
	settings.setValue("colorJotMarkScrapped", colorJotMarkScrapped.name());
	settings.endGroup();

	settings.beginGroup("Text");
	settings.setValue("textJotMarkDone", textJotMarkDone);
	settings.setValue("textJotMarkScrapped", textJotMarkScrapped);
	settings.endGroup();*/

	{
		QSettings settings(appExecutablePath + "/preferences.ini", QSettings::IniFormat);

		settings.beginGroup("ThemeCurrent");
		settings.setValue("themeCurrentName", themeCurrentName);
		settings.endGroup();

		settings.beginGroup("Toggles");
		settings.setValue("actionToolbarToggleVis", ui.actionToolbarToggleVis->isChecked());
		settings.setValue("actionPrefToggleModding", ui.actionPrefToggleModding->isChecked());
		settings.setValue("actionPrefDisableOverrides", ui.actionPrefDisableOverrides->isChecked());
		settings.endGroup();

		settings.beginGroup("FilePathMemory");
		settings.setValue("fileDirLastOpened", fileDirLastOpened);
		settings.setValue("fileDirLastSaved", fileDirLastSaved);
		settings.endGroup();
	}

	if (jotOverrideWasUsed)
	{
		for (auto& themePackageInstance : themePackages_themesList)
		{
			if (!themePackageInstance.second.overridesAreEmpty)
			{
				QSettings settings(appExecutablePath + "/ThemeOverrides/" + themePackageInstance.first + ".ini", QSettings::IniFormat);
				settings.beginGroup("ThemeJotOverrides");
				if (!themePackageInstance.second.overrideTextJotMarkDone.isEmpty())
					settings.setValue("overrideTextJotMarkDone", themePackageInstance.second.overrideTextJotMarkDone);
				if (!themePackageInstance.second.overrideTextJotMarkScrapped.isEmpty())
					settings.setValue("overrideTextJotMarkScrapped", themePackageInstance.second.overrideTextJotMarkScrapped);
				if (themePackageInstance.second.overrideColorJotCommentBg.isValid())
					settings.setValue("overrideColorJotCommentBg", themePackageInstance.second.overrideColorJotCommentBg.name());
				if (themePackageInstance.second.overrideColorJotCommentText.isValid())
					settings.setValue("overrideColorJotCommentText", themePackageInstance.second.overrideColorJotCommentText.name());
				if (themePackageInstance.second.overrideColorJotListTitleBg.isValid())
					settings.setValue("overrideColorJotListTitleBg", themePackageInstance.second.overrideColorJotListTitleBg.name());
				if (themePackageInstance.second.overrideColorJotListTitleText.isValid())
					settings.setValue("overrideColorJotListTitleText", themePackageInstance.second.overrideColorJotListTitleText.name());
				if (themePackageInstance.second.overrideColorJotMarkDoneBg.isValid())
					settings.setValue("overrideColorJotMarkDoneBg", themePackageInstance.second.overrideColorJotMarkDoneBg.name());
				if (themePackageInstance.second.overrideColorJotMarkDoneText.isValid())
					settings.setValue("overrideColorJotMarkDoneText", themePackageInstance.second.overrideColorJotMarkDoneText.name());
				if (themePackageInstance.second.overrideColorJotMarkScrappedBg.isValid())
					settings.setValue("overrideColorJotMarkScrappedBg", themePackageInstance.second.overrideColorJotMarkScrappedBg.name());
				if (themePackageInstance.second.overrideColorJotMarkScrappedText.isValid())
					settings.setValue("overrideColorJotMarkScrappedText", themePackageInstance.second.overrideColorJotMarkScrappedText.name());
				settings.endGroup();
			}
		}
	}
}

void CuteLittleNotes::moddingCheckForContent()
{
	QStringList themesList_mod;

	QDirIterator dirIt(appExecutablePath + "/Mods", QDir::AllDirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
	while (dirIt.hasNext())
	{
		themesList_mod.append(dirIt.next());
		qDebug() << themesList_mod;
	}

	for (auto& theme_mod : themesList_mod)
	{
		//int expectedElementsCount = 0;
		//const int expectedElementsTotal = 8; // 7 icons and 1 info file.
		//QString themeUniqueNameToAdd = "";
		//std::map<ThemeIconsKey, QString> new_ThemeIconsMap_mod;
		themePackage themePackageInstance;

		auto themesIt = std::experimental::filesystem::directory_iterator(theme_mod.toStdString());
		for (auto& themeFile : themesIt)
		{
			if (themeFile.path().filename().string().find("themeInfo.ini") != std::string::npos)
			{
				QSettings settings(QString::fromStdString(themeFile.path().string()), QSettings::IniFormat);
				settings.beginGroup("ModInfo");
				if (!settings.value("creatorName").toString().isEmpty())
					themePackageInstance.creatorName = settings.value("creatorName").toString();
				if (!settings.value("themeUniqueName").toString().isEmpty())
					themePackageInstance.themeUniqueName = settings.value("themeUniqueName").toString();
				if (!settings.value("versionNumber").isNull())
					themePackageInstance.versionNumber = settings.value("versionNumber").toDouble();
				settings.endGroup();

				/*if (!themeUniqueNameToAdd.isEmpty())
					expectedElementsCount++;*/
			}
			else if (themeFile.path().filename().string().find("themeJot.ini") != std::string::npos)
			{
				QSettings settings(QString::fromStdString(themeFile.path().string()), QSettings::IniFormat);
				settings.beginGroup("JotSettings");
				if (!settings.value("textJotMarkDone").toString().isEmpty())
					themePackageInstance.textJotMarkDone = settings.value("textJotMarkDone").toString();
				if (!settings.value("textJotMarkScrapped").toString().isEmpty())
					themePackageInstance.textJotMarkScrapped = settings.value("textJotMarkScrapped").toString();
				if (!settings.value("colorJotCommentBg").isNull())
					themePackageInstance.colorJotCommentBg = settings.value("colorJotCommentBg").value<QColor>();
				if (!settings.value("colorJotCommentText").isNull())
					themePackageInstance.colorJotCommentText = settings.value("colorJotCommentText").value<QColor>();
				if (!settings.value("colorJotListTitleBg").isNull())
					themePackageInstance.colorJotListTitleBg = settings.value("colorJotListTitleBg").value<QColor>();
				if (!settings.value("colorJotListTitleText").isNull())
					themePackageInstance.colorJotListTitleText = settings.value("colorJotListTitleText").value<QColor>();
				if (!settings.value("colorJotMarkDoneBg").isNull())
					themePackageInstance.colorJotMarkDoneBg = settings.value("colorJotMarkDoneBg").value<QColor>();
				if (!settings.value("colorJotMarkDoneText").isNull())
					themePackageInstance.colorJotMarkDoneText = settings.value("colorJotMarkDoneText").value<QColor>();
				if (!settings.value("colorJotMarkScrappedBg").isNull())
					themePackageInstance.colorJotMarkScrappedBg = settings.value("colorJotMarkScrappedBg").value<QColor>();
				if (!settings.value("colorJotMarkScrappedText").isNull())
					themePackageInstance.colorJotMarkScrappedText = settings.value("colorJotMarkScrappedText").value<QColor>();
				settings.endGroup();

				/*if (!themeUniqueNameToAdd.isEmpty())
					expectedElementsCount++;*/
			}
			else if (themeFile.path().filename().string().find(".qss") != std::string::npos)
			{
				std::string fileContents = "";
				std::string line;
				std::ifstream fileRead(themeFile.path().string());
				while (std::getline(fileRead, line))
				{
					fileContents += line;
				}
				fileRead.close();

				// Edit file contents, replacing existing img urls with the new URLs, based on...
				// the file path of the found qss file. 
				// Then add the modified stylesheet to the theme package

				// Path to insert into stylesheet:
				// QFileInfo(path() of qss file) + QFileInfo(baseName() of qss file) + "_images/" + imgName.png

				if (!fileContents.empty())
				{
					const QString imgPath =
						QFileInfo(QString::fromStdString(themeFile.path().string())).path() +
						"/" +
						QFileInfo(QString::fromStdString(themeFile.path().string())).baseName() +
						"_images/"
						;

					fileContents = replaceSubstring("#toolbarButtonActionNew{  qproperty-icon: url(", ")", imgPath.toStdString() + "toolbarButtonActionNew.png", fileContents);
					fileContents = replaceSubstring("#toolbarButtonActionOpen{  qproperty-icon: url(", ")", imgPath.toStdString() + "toolbarButtonActionOpen.png", fileContents);
					fileContents = replaceSubstring("#toolbarButtonActionSave{  qproperty-icon: url(", ")", imgPath.toStdString() + "toolbarButtonActionSave.png", fileContents);
					fileContents = replaceSubstring("#toolbarButtonActionComment{  qproperty-icon: url(", ")", imgPath.toStdString() + "toolbarButtonActionComment.png", fileContents);
					fileContents = replaceSubstring("#toolbarButtonActionListTitle{  qproperty-icon: url(", ")", imgPath.toStdString() + "toolbarButtonActionListTitle.png", fileContents);
					fileContents = replaceSubstring("#toolbarButtonActionMarkDone{  qproperty-icon: url(", ")", imgPath.toStdString() + "toolbarButtonActionMarkDone.png", fileContents);
					fileContents = replaceSubstring("#toolbarButtonActionMarkScrapped{  qproperty-icon: url(", ")", imgPath.toStdString() + "toolbarButtonActionMarkScrapped.png", fileContents);
					fileContents = replaceSubstring("QMenu::indicator:non-exclusive:checked{  image: url(", ")", imgPath.toStdString() + "menuIconCheckableIsChecked.png", fileContents);

					themePackageInstance.themeStylesheet = QString::fromStdString(fileContents);
				}
			}
			/*else if (themeFile.path().filename().string().find("toolbar-icon-new") != std::string::npos)
			{
				new_ThemeIconsMap_mod.insert(std::pair<ThemeIconsKey, QString>(ThemeIconsKey::FILE_NEW, QString::fromStdString(themeFile.path().string())));
				expectedElementsCount++;
			}
			else if (themeFile.path().filename().string().find("toolbar-icon-open") != std::string::npos)
			{
				new_ThemeIconsMap_mod.insert(std::pair<ThemeIconsKey, QString>(ThemeIconsKey::FILE_OPEN, QString::fromStdString(themeFile.path().string())));
				expectedElementsCount++;
			}
			else if (themeFile.path().filename().string().find("toolbar-icon-save") != std::string::npos)
			{
				new_ThemeIconsMap_mod.insert(std::pair<ThemeIconsKey, QString>(ThemeIconsKey::FILE_SAVE, QString::fromStdString(themeFile.path().string())));
				expectedElementsCount++;
			}
			else if (themeFile.path().filename().string().find("toolbar-icon-comment") != std::string::npos)
			{
				new_ThemeIconsMap_mod.insert(std::pair<ThemeIconsKey, QString>(ThemeIconsKey::JOT_COMMENT, QString::fromStdString(themeFile.path().string())));
				expectedElementsCount++;
			}
			else if (themeFile.path().filename().string().find("toolbar-icon-list-title") != std::string::npos)
			{
				new_ThemeIconsMap_mod.insert(std::pair<ThemeIconsKey, QString>(ThemeIconsKey::JOT_LIST_TITLE, QString::fromStdString(themeFile.path().string())));
				expectedElementsCount++;
			}
			else if (themeFile.path().filename().string().find("toolbar-icon-mark-done") != std::string::npos)
			{
				new_ThemeIconsMap_mod.insert(std::pair<ThemeIconsKey, QString>(ThemeIconsKey::JOT_MARK_DONE, QString::fromStdString(themeFile.path().string())));
				expectedElementsCount++;
			}
			else if (themeFile.path().filename().string().find("toolbar-icon-mark-scrapped") != std::string::npos)
			{
				new_ThemeIconsMap_mod.insert(std::pair<ThemeIconsKey, QString>(ThemeIconsKey::JOT_MARK_SCRAPPED, QString::fromStdString(themeFile.path().string())));
				expectedElementsCount++;
			}*/
		}

		//if (expectedElementsCount == expectedElementsTotal)
		//{
		//	//themesList.append(themeUniqueNameToAdd);
		//	themeIconsMap_themesList.push_back(new_ThemeIconsMap_mod);
		//}
		if (!themePackageInstance.themeStylesheet.isEmpty())
		{
			themePackages_themesList.insert(std::pair<QString, themePackage>(themePackageInstance.themeUniqueName + " by " + themePackageInstance.creatorName, themePackageInstance));
			//themePackages_themesList.push_back(themePackageInstance);
			//themesList.append(themeUniqueNameToAdd);
			//themeIconsMap_themesList.push_back(new_ThemeIconsMap_mod);
		}
		else
		{
			/*qDebug() << (expectedElementsTotal - expectedElementsCount) + " expected component(s) not found in " + theme_mod
				+ "\nMake sure all required theme files are present in the format specified in the modding documentation.";*/
			qDebug() << "No stylesheet found as part of mod in " + theme_mod + " Make sure all required theme files are present in the format specified in the modding documentation.";
		}
	}
}

std::string CuteLittleNotes::replaceSubstring(const std::string strBegin, const std::string strEnd, const std::string strMid, const std::string strStylesheet)
{
	int posBegin = strStylesheet.find(strBegin);
	int posEnd = strStylesheet.find(strEnd, posBegin) + 1;

	std::string strStylesheetCopy = strStylesheet;
	strStylesheetCopy.erase(posBegin, posEnd - posBegin);
	strStylesheetCopy.insert(posBegin, (strBegin + strMid + strEnd));

	return strStylesheetCopy;
}