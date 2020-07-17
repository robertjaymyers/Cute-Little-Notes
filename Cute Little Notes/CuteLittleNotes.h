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

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CuteLittleNotes.h"

class CuteLittleNotes : public QMainWindow
{
	Q_OBJECT

public:
	CuteLittleNotes(QWidget *parent = Q_NULLPTR);
	void closeEvent(QCloseEvent *event);

private:
	Ui::CuteLittleNotesClass ui;

	// Store executable path for usage in things like Mods folder or preference file.
	// Such that if user opens the program through a .cutelittlenotes file, rather than
	// opening it from the executable directory, the program will still know where to find
	// these important bits of information.
	const QString appExecutablePath = QCoreApplication::applicationDirPath();

	const QString winTitleProgramName = "Cute Little Notes";
	const QString winTitlePlaceholder = "[*]";
	const QString winTitleUntitled = "Untitled";

	bool jotOverrideWasUsed = false;
	QString textJotMarkDone = "DONE";
	QString textJotMarkScrapped = "SCRAPPED";
	QColor colorJotCommentBg = QColor(255, 180, 255, 255);
	QColor colorJotCommentText = QColor(0, 0, 0, 255);
	QColor colorJotListTitleBg = QColor(229, 229, 229, 255);
	QColor colorJotListTitleText = QColor(0, 0, 0, 255);
	QColor colorJotMarkDoneBg = QColor(93, 206, 224, 255);
	QColor colorJotMarkDoneText = QColor(0, 0, 0, 255);
	QColor colorJotMarkScrappedBg = QColor(214, 136, 126, 255);
	QColor colorJotMarkScrappedText = QColor(0, 0, 0, 255);
	const enum class JotPrefType { COLOR, TEXT };

	QString fileCurrent = "";
	QString fileDirLastOpened = appExecutablePath;
	QString fileDirLastSaved = appExecutablePath;

	// ZOOM CODE -- NOT USED
	//int zoomRange = 0; // The base font size range points. Zoom in or out moves this by +1 or -1. Stored for resetting zoom level.
	// END ZOOM CODE


	// Themes are stored and loaded from a map with expected unique name key (theme name + creator name).
	// This is to ensure that the correct theme will be loaded, regardless of mod load order or similar theme name.

	int themeCurrentIndex = 0; // The current theme by list index, based on the themes list.
	const QString themeDefaultRevertName = "Default | Pink by Robert Jay Myers";
	QString themeCurrentName = themeDefaultRevertName;

	QStringList themeNamesList;

	struct themePackage
	{
		QString themeStylesheet;
		QString themeUniqueName = "Untitled";
		QString creatorName = "UnknownCreator";
		double versionNumber = 1.0;
		QString textJotMarkDone = "DONE";
		QString textJotMarkScrapped = "SCRAPPED";
		QColor colorJotCommentBg = QColor(255, 180, 255, 255);
		QColor colorJotCommentText = QColor(0, 0, 0, 255);
		QColor colorJotListTitleBg = QColor(229, 229, 229, 255);
		QColor colorJotListTitleText = QColor(0, 0, 0, 255);
		QColor colorJotMarkDoneBg = QColor(93, 206, 224, 255);
		QColor colorJotMarkDoneText = QColor(0, 0, 0, 255);
		QColor colorJotMarkScrappedBg = QColor(214, 136, 126, 255);
		QColor colorJotMarkScrappedText = QColor(0, 0, 0, 255);
		bool overridesAreEmpty = true;
		QString overrideTextJotMarkDone;
		QString overrideTextJotMarkScrapped;
		QColor overrideColorJotCommentBg;
		QColor overrideColorJotCommentText;
		QColor overrideColorJotListTitleBg;
		QColor overrideColorJotListTitleText;
		QColor overrideColorJotMarkDoneBg;
		QColor overrideColorJotMarkDoneText;
		QColor overrideColorJotMarkScrappedBg;
		QColor overrideColorJotMarkScrappedText;
	};

	std::map<QString, themePackage> themePackages_themesList
	{
		{
			"Default - Pink by Robert Jay Myers",
			{
				"QTextEdit{  border-color: #F2F2F2;  border-style: inset;  border-width: 1px;  background-color: #FFFFFF;  color: #000000;}"
				"QScrollBar{  background-color: #F0F0F0;}"
				"QToolBar{  background-color: #F0F0F0;  border-width: 1px 0px 1px 1px;  border-style: outset;  border-color: #B9B9B9;}"
				"QToolBar::separator{  background-color: #D3D3D3;  width: 1px;  height: 1px;  margin: 3px 3px 3px 2px;}"
				"QToolButton:hover{  background-color: #FFB4FF;  border-width: 1px;  border-style: solid;}"
				"QToolButton:hover{  border-color: #000000;}"
				"QToolButton#toolbarButtonActionNew{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/toolbar-icon-new.png);}"
				"QToolButton#toolbarButtonActionOpen{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/toolbar-icon-open.png);}"
				"QToolButton#toolbarButtonActionSave{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/toolbar-icon-save.png);}"
				"QToolButton#toolbarButtonActionComment{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/toolbar-icon-comment.png);}"
				"QToolButton#toolbarButtonActionListTitle{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/toolbar-icon-list-title.png);}"
				"QToolButton#toolbarButtonActionMarkDone{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/toolbar-icon-mark-done.png);}"
				"QToolButton#toolbarButtonActionMarkScrapped{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/toolbar-icon-mark-scrapped.png);}"
				"QMenuBar{  background-color: #FFFFFF;  color: #000000;  border-bottom-width: 1px;  border-bottom-style: solid;  border-color: #F2F2F2;}"
				"QMenuBar::item:selected{  background-color: #FFB4FF;  border-width: 1px;  border-style: solid;}"
				"QMenuBar::item:selected{  color: #000000;}"
				"QMenuBar::item:selected{  border-color: #000000;}"
				"QMenu{  background-color: #F0F0F0;  color: #000000;  border-color: #CCCCCC;  border-width: 1px;  border-style: solid;}"
				"QMenu::separator{  background-color: #D7D7D7;  width: 1px;  height: 1px;  margin: 3px 0px 3px 12px;}"
				"QMenu::item{  background-color: #F0F0F0;  margin: 2px;  padding: 2px 20px 2px 40px;  border: 1px solid transparent;}"
				"QMenu::item:selected{  background-color: #FFB4FF;}"
				"QMenu::item:selected{  color: #000000;}"
				"QMenu::indicator:non-exclusive:checked{  image: url(:/CuteLittleNotes/IconsBuiltIn/menuIconCheckableIsChecked_themeDefaultPink.png);}"
				"QMenu::indicator:non-exclusive:checked{  background-color: #FFB4FF;}"
				"QStatusBar{  background-color: #FFFFFF;  color: #000000;}",
				"Default - Pink",
				"Robert Jay Myers",
				1.0,
				"DONE",
				"SCRAPPED",
				QColor(255, 180, 255, 255),
				QColor(0, 0, 0, 255),
				QColor(229, 229, 229, 255),
				QColor(0, 0, 0, 255),
				QColor(93, 206, 224, 255),
				QColor(0, 0, 0, 255),
				QColor(214, 136, 126, 255),
				QColor(0, 0, 0, 255),
				true,
			}
		},
		{
			"Gray by Robert Jay Myers",
			{
				"QTextEdit{  border-color: #F2F2F2;  border-style: inset;  border-width: 1px;  background-color: #FFFFFF;  color: #000000;}"
				"QScrollBar{  background-color: #F0F0F0;}"
				"QToolBar{  background-color: #F0F0F0;  border-width: 1px 0px 1px 1px;  border-style: outset;  border-color: #B9B9B9;}"
				"QToolBar::separator{  background-color: #D3D3D3;  width: 1px;  height: 1px;  margin: 3px 3px 3px 2px;}"
				"QToolButton:hover{  background-color: #d2d2d2;  border-width: 1px;  border-style: solid;}"
				"QToolButton:hover{  border-color: #000000;}"
				"QToolButton#toolbarButtonActionNew{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/ThemeGray/toolbar-icon-new-theme-gray.png);}"
				"QToolButton#toolbarButtonActionOpen{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/ThemeGray/toolbar-icon-open-theme-gray.png);}"
				"QToolButton#toolbarButtonActionSave{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/ThemeGray/toolbar-icon-save-theme-gray.png);}"
				"QToolButton#toolbarButtonActionComment{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/ThemeGray/toolbar-icon-comment-theme-gray.png);}"
				"QToolButton#toolbarButtonActionListTitle{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/ThemeGray/toolbar-icon-list-title-theme-gray.png);}"
				"QToolButton#toolbarButtonActionMarkDone{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/ThemeGray/toolbar-icon-mark-done-theme-gray.png);}"
				"QToolButton#toolbarButtonActionMarkScrapped{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/ThemeGray/toolbar-icon-mark-scrapped-theme-gray.png);}"
				"QMenuBar{  background-color: #FFFFFF;  color: #000000;  border-bottom-width: 1px;  border-bottom-style: solid;  border-color: #F2F2F2;}"
				"QMenuBar::item:selected{  background-color: #d2d2d2;  border-width: 1px;  border-style: solid;}"
				"QMenuBar::item:selected{  color: #000000;}"
				"QMenuBar::item:selected{  border-color: #000000;}"
				"QMenu{  background-color: #F0F0F0;  color: #000000;  border-color: #CCCCCC;  border-width: 1px;  border-style: solid;}"
				"QMenu::separator{  background-color: #D7D7D7;  width: 1px;  height: 1px;  margin: 3px 0px 3px 12px;}"
				"QMenu::item{  background-color: #F0F0F0;  margin: 2px;  padding: 2px 20px 2px 40px;  border: 1px solid transparent;}"
				"QMenu::item:selected{  background-color: #d2d2d2;}"
				"QMenu::item:selected{  color: #000000;}"
				"QMenu::indicator:non-exclusive:checked{  image: url(:/CuteLittleNotes/IconsBuiltIn/ThemeGray/menuIconCheckableIsChecked_themeGray.png);}"
				"QMenu::indicator:non-exclusive:checked{  background-color: #d2d2d2;}"
				"QStatusBar{  background-color: #FFFFFF;  color: #000000;}",
				"Gray",
				"Robert Jay Myers",
				1.0,
				"DONE",
				"SCRAPPED",
				QColor(210, 210, 210, 255),
				QColor(0, 0, 0, 255),
				QColor(229, 229, 229, 255),
				QColor(0, 0, 0, 255),
				QColor(93, 206, 224, 255),
				QColor(0, 0, 0, 255),
				QColor(214, 136, 126, 255),
				QColor(0, 0, 0, 255),
				true,
			}
		},
		{
			"Baby Blue by Robert Jay Myers",
			{
				"QTextEdit{  border-color: #F2F2F2;  border-style: inset;  border-width: 1px;  background-color: #FFFFFF;  color: #000000;}"
				"QScrollBar{  background-color: #F0F0F0;}"
				"QToolBar{  background-color: #F0F0F0;  border-width: 1px 0px 1px 1px;  border-style: outset;  border-color: #B9B9B9;}"
				"QToolBar::separator{  background-color: #D3D3D3;  width: 1px;  height: 1px;  margin: 3px 3px 3px 2px;}"
				"QToolButton:hover{  background-color: #cce8ff;  border-width: 1px;  border-style: solid;}"
				"QToolButton:hover{  border-color: #99d1ff;}"
				"QToolButton#toolbarButtonActionNew{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/ThemeBabyBlue/toolbarButtonActionNew_themeBabyBlue.png);}"
				"QToolButton#toolbarButtonActionOpen{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/ThemeBabyBlue/toolbarButtonActionOpen_themeBabyBlue.png);}"
				"QToolButton#toolbarButtonActionSave{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/ThemeBabyBlue/toolbarButtonActionSave_themeBabyBlue.png);}"
				"QToolButton#toolbarButtonActionComment{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/ThemeBabyBlue/toolbarButtonActionComment_themeBabyBlue.png);}"
				"QToolButton#toolbarButtonActionListTitle{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/ThemeBabyBlue/toolbarButtonActionListTitle_themeBabyBlue.png);}"
				"QToolButton#toolbarButtonActionMarkDone{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/ThemeBabyBlue/toolbarButtonActionMarkDone_themeBabyBlue.png);}"
				"QToolButton#toolbarButtonActionMarkScrapped{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/ThemeBabyBlue/toolbarButtonActionMarkScrapped_themeBabyBlue.png);}"
				"QMenuBar{  background-color: #FFFFFF;  color: #000000;  border-bottom-width: 1px;  border-bottom-style: solid;  border-color: #F2F2F2;}"
				"QMenuBar::item:selected{  background-color: #cce8ff;  border-width: 1px;  border-style: solid;}"
				"QMenuBar::item:selected{  color: #000000;}"
				"QMenuBar::item:selected{  border-color: #99d1ff;}"
				"QMenu{  background-color: #F0F0F0;  color: #000000;  border-color: #CCCCCC;  border-width: 1px;  border-style: solid;}"
				"QMenu::separator{  background-color: #D7D7D7;  width: 1px;  height: 1px;  margin: 3px 0px 3px 12px;}"
				"QMenu::item{  background-color: #F0F0F0;  margin: 2px;  padding: 2px 20px 2px 40px;  border: 1px solid transparent;}"
				"QMenu::item:selected{  background-color: #90c8f6;}"
				"QMenu::item:selected{  color: #000000;}"
				"QMenu::indicator:non-exclusive:checked{  image: url(:/CuteLittleNotes/IconsBuiltIn/ThemeBabyBlue/menuIconCheckableIsChecked_themeBabyBlue.png);}"
				"QMenu::indicator:non-exclusive:checked{  background-color: #90c8f6;}"
				"QStatusBar{  background-color: #FFFFFF;  color: #000000;}",
				"Baby Blue",
				"Robert Jay Myers",
				1.0,
				"DONE",
				"SCRAPPED",
				QColor(204, 232, 255, 255),
				QColor(0, 0, 0, 255),
				QColor(229, 229, 229, 255),
				QColor(0, 0, 0, 255),
				QColor(93, 206, 224, 255),
				QColor(0, 0, 0, 255),
				QColor(214, 136, 126, 255),
				QColor(0, 0, 0, 255),
				true,
			}
		},
		{
			"Coffee - Dark by Robert Jay Myers",
			{
				"QTextEdit{  border-color: #101010;  border-style: inset;  border-width: 1px;  background-color: #2f2f2f;  color: #e2bb80;}"
				"QScrollBar{  background-color: #2f2f2f;}"
				"QToolBar{  background-color: #2f2f2f;  border-width: 1px 0px 1px 1px;  border-style: outset;  border-color: #101010;}"
				"QToolBar::separator{  background-color: #101010;  width: 1px;  height: 1px;  margin: 3px 3px 3px 2px;}"
				"QToolButton:hover{  background-color: #e2bb80;  border-width: 1px;  border-style: solid;}"
				"QToolButton:hover{  border-color: #000000;}"
				"QToolButton#toolbarButtonActionNew{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/themeCoffeeDark/toolbarButtonActionNew_themeCoffeeDark.png);}"
				"QToolButton#toolbarButtonActionOpen{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/themeCoffeeDark/toolbarButtonActionOpen_themeCoffeeDark.png);}"
				"QToolButton#toolbarButtonActionSave{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/themeCoffeeDark/toolbarButtonActionSave_themeCoffeeDark.png);}"
				"QToolButton#toolbarButtonActionComment{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/themeCoffeeDark/toolbarButtonActionComment_themeCoffeeDark.png);}"
				"QToolButton#toolbarButtonActionListTitle{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/themeCoffeeDark/toolbarButtonActionListTitle_themeCoffeeDark.png);}"
				"QToolButton#toolbarButtonActionMarkDone{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/themeCoffeeDark/toolbarButtonActionMarkDone_themeCoffeeDark.png);}"
				"QToolButton#toolbarButtonActionMarkScrapped{  qproperty-icon: url(:/CuteLittleNotes/IconsBuiltIn/themeCoffeeDark/toolbarButtonActionMarkScrapped_themeCoffeeDark.png);}"
				"QMenuBar{  background-color: #2f2f2f;  color: #e2bb80;  border-bottom-width: 1px;  border-bottom-style: solid;  border-color: #101010;}"
				"QMenuBar::item:selected{  background-color: #e2bb80;  border-width: 1px;  border-style: solid;}"
				"QMenuBar::item:selected{  color: #000000;}"
				"QMenuBar::item:selected{  border-color: #000000;}"
				"QMenu{  background-color: #2f2f2f;  color: #e2bb80;  border-color: #101010;  border-width: 1px;  border-style: solid;}"
				"QMenu::separator{  background-color: #101010;  width: 1px;  height: 1px;  margin: 3px 0px 3px 12px;}"
				"QMenu::item{  background-color: #2f2f2f;  margin: 2px;  padding: 2px 20px 2px 40px;  border: 1px solid transparent;}"
				"QMenu::item:selected{  background-color: #e2bb80;}"
				"QMenu::item:selected{  color: #000000;}"
				"QMenu::indicator:non-exclusive:checked{  image: url(:/CuteLittleNotes/IconsBuiltIn/themeCoffeeDark/menuIconCheckableIsChecked_themeCoffeeDark.png);}"
				"QMenu::indicator:non-exclusive:checked{  background-color: #e2bb80;}"
				"QStatusBar{  background-color: #2f2f2f;  color: #e2bb80;}",
				"Coffee - Dark",
				"Robert Jay Myers",
				1.0,
				"DONE",
				"SCRAPPED",
				QColor(226, 187, 128, 255),
				QColor(0, 0, 0, 255),
				QColor(0, 0, 0, 255),
				QColor(255, 233, 199, 255),
				QColor(79, 108, 71, 255),
				QColor(255, 255, 255, 255),
				QColor(81, 40, 40, 255),
				QColor(255, 255, 255, 255),
				true,
			}
		},
	};

	const QStringList jotOverrideNamesList =
	{
		"Jot Mark Done Text",
		"Jot Mark Scrapped Text",
		"Jot Comment Background Color",
		"Jot Comment Text Color",
		"Jot List Title Background Color",
		"Jot List Title Text Color",
		"Jot Mark Done Background Color",
		"Jot Mark Done Text Color",
		"Jot Mark Scrapped Background Color",
		"Jot Mark Scrapped Text Color"
	};

	const enum class JotNameEnums
	{
		MARK_DONE_TXT,
		MARK_SCRAPPED_TXT,
		COMMENT_BG_COL,
		COMMENT_TXT_COL,
		LIST_TITLE_BG_COL,
		LIST_TITLE_TXT_COL,
		MARK_DONE_BG_COL,
		MARK_DONE_TXT_COL,
		MARK_SCRAPPED_BG_COL,
		MARK_SCRAPPED_TXT_COL
	};

	std::map<QString, JotNameEnums> jotOverrideNamesMap =
	{
		{jotOverrideNamesList[0], JotNameEnums::MARK_DONE_TXT},
		{jotOverrideNamesList[1], JotNameEnums::MARK_SCRAPPED_TXT},
		{jotOverrideNamesList[2], JotNameEnums::COMMENT_BG_COL},
		{jotOverrideNamesList[3], JotNameEnums::COMMENT_TXT_COL},
		{jotOverrideNamesList[4], JotNameEnums::LIST_TITLE_BG_COL},
		{jotOverrideNamesList[5], JotNameEnums::LIST_TITLE_TXT_COL},
		{jotOverrideNamesList[6], JotNameEnums::MARK_DONE_BG_COL},
		{jotOverrideNamesList[7], JotNameEnums::MARK_DONE_TXT_COL},
		{jotOverrideNamesList[8], JotNameEnums::MARK_SCRAPPED_BG_COL},
		{jotOverrideNamesList[9], JotNameEnums::MARK_SCRAPPED_TXT_COL},
	};

	void applyExistingJotPrefsAll();
	std::string applyExistingJotPrefs(const std::string strBegin, const std::string strEnd, const std::string &textEditContents, const QStringList replacements, JotPrefType prefType);

private slots:
	void statusBarInit();
	void fileDocumentModified();
	void fileSetCurrent(const QString &filename);
	void fileNew();
	void fileOpen();
	bool fileSaveModifCheck();
	bool fileSaveOps();
	bool fileSave(const QString &filename);
	bool fileSaveAs();
	void fileSaveAsPlainText();
	void jotComment();
	void jotListTitle();
	void jotMarkDone();
	void jotMarkScrapped();
	void editFormattingRemoveAll();
	void toggleToolbarVis();
	void toggleWordWrapMode();
	void stripFormattingFromSelectedText();
	void pasteStripFormatting();
	void prefSetThemeOverride();
	bool prefSetOverrideColor(QColor &color, const QString colorValName);
	bool prefSetOverrideText(QString &text, const QString textValName);
	void prefSetTheme();
	void prefSetThemeLoadCurrentTheme();
	void prefLoad();
	void prefSave();
	void moddingCheckForContent();
	std::string replaceSubstring(const std::string strBegin, const std::string strEnd, const std::string strMid, const std::string strStylesheet);
};
