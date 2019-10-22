/********************************************************************************
** Form generated from reading UI file 'CuteLittleNotes.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUTELITTLENOTES_H
#define UI_CUTELITTLENOTES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CuteLittleNotesClass
{
public:
    QAction *actionSaveAs;
    QAction *actionSave;
    QAction *actionOpen;
    QAction *actionNew;
    QAction *actionWordWrap;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionComment;
    QAction *actionMarkDone;
    QAction *actionMarkScrapped;
    QAction *actionStripFormatting;
    QAction *actionPasteStripFormatting;
    QAction *actionPastePlainText;
    QAction *actionExit;
    QAction *actionSetColorComment;
    QAction *actionSetColorMarkDone;
    QAction *actionSetColorMarkScrapped;
    QAction *actionSetColorTextEditorBackground;
    QAction *actionSetColorTextEditorText;
    QAction *actionSetTextMarkDone;
    QAction *actionSetTextMarkScrapped;
    QAction *actionListTitle;
    QAction *actionPrefCommentSetColor;
    QAction *actionPrefCommentSetText;
    QAction *actionPrefMarkDoneSetColor;
    QAction *actionPrefMarkDoneSetText;
    QAction *actionPrefMarkScrappedSetColor;
    QAction *actionPrefMarkScrappedSetText;
    QAction *actionPrefListTitleSetColorBg;
    QAction *actionPrefListTitleSetColorText;
    QAction *actionPrefSaveManual;
    QAction *actionToolbarToggleVis;
    QAction *actionFormattingRemoveAll;
    QAction *actionSaveAsPlainText;
    QAction *actionPrefSetTheme;
    QAction *actionPrefToggleModding;
    QAction *actionPrefSetJotOverrides;
    QAction *actionPrefDisableOverrides;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;
    QAction *action;
    QMenu *menuEdit;
    QMenu *menuJot;
    QMenu *menuList;
    QMenu *menuPreferences;
    QMenu *menuPrefComment;
    QMenu *menuPrefMarkDone;
    QMenu *menuPrefMarkScrapped;
    QMenu *menuPrefListTitle;
    QMenu *menuPrefOverrideTheme;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CuteLittleNotesClass)
    {
        if (CuteLittleNotesClass->objectName().isEmpty())
            CuteLittleNotesClass->setObjectName(QStringLiteral("CuteLittleNotesClass"));
        CuteLittleNotesClass->setEnabled(true);
        CuteLittleNotesClass->resize(600, 400);
        actionSaveAs = new QAction(CuteLittleNotesClass);
        actionSaveAs->setObjectName(QStringLiteral("actionSaveAs"));
        actionSave = new QAction(CuteLittleNotesClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/CuteLittleNotes/IconsBuiltIn/toolbar-icon-save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon);
        actionOpen = new QAction(CuteLittleNotesClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/CuteLittleNotes/IconsBuiltIn/toolbar-icon-open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionNew = new QAction(CuteLittleNotesClass);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/CuteLittleNotes/IconsBuiltIn/toolbar-icon-new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon2);
        actionWordWrap = new QAction(CuteLittleNotesClass);
        actionWordWrap->setObjectName(QStringLiteral("actionWordWrap"));
        actionWordWrap->setCheckable(true);
        actionWordWrap->setChecked(true);
        actionUndo = new QAction(CuteLittleNotesClass);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        actionUndo->setCheckable(false);
        actionUndo->setEnabled(false);
        actionRedo = new QAction(CuteLittleNotesClass);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        actionRedo->setEnabled(false);
        actionComment = new QAction(CuteLittleNotesClass);
        actionComment->setObjectName(QStringLiteral("actionComment"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/CuteLittleNotes/IconsBuiltIn/toolbar-icon-comment.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionComment->setIcon(icon3);
        actionMarkDone = new QAction(CuteLittleNotesClass);
        actionMarkDone->setObjectName(QStringLiteral("actionMarkDone"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/CuteLittleNotes/IconsBuiltIn/toolbar-icon-mark-done.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMarkDone->setIcon(icon4);
        actionMarkScrapped = new QAction(CuteLittleNotesClass);
        actionMarkScrapped->setObjectName(QStringLiteral("actionMarkScrapped"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/CuteLittleNotes/IconsBuiltIn/toolbar-icon-mark-scrapped.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMarkScrapped->setIcon(icon5);
        actionStripFormatting = new QAction(CuteLittleNotesClass);
        actionStripFormatting->setObjectName(QStringLiteral("actionStripFormatting"));
        actionPasteStripFormatting = new QAction(CuteLittleNotesClass);
        actionPasteStripFormatting->setObjectName(QStringLiteral("actionPasteStripFormatting"));
        actionPasteStripFormatting->setCheckable(true);
        actionPasteStripFormatting->setChecked(true);
        actionPastePlainText = new QAction(CuteLittleNotesClass);
        actionPastePlainText->setObjectName(QStringLiteral("actionPastePlainText"));
        actionExit = new QAction(CuteLittleNotesClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionSetColorComment = new QAction(CuteLittleNotesClass);
        actionSetColorComment->setObjectName(QStringLiteral("actionSetColorComment"));
        actionSetColorMarkDone = new QAction(CuteLittleNotesClass);
        actionSetColorMarkDone->setObjectName(QStringLiteral("actionSetColorMarkDone"));
        actionSetColorMarkScrapped = new QAction(CuteLittleNotesClass);
        actionSetColorMarkScrapped->setObjectName(QStringLiteral("actionSetColorMarkScrapped"));
        actionSetColorTextEditorBackground = new QAction(CuteLittleNotesClass);
        actionSetColorTextEditorBackground->setObjectName(QStringLiteral("actionSetColorTextEditorBackground"));
        actionSetColorTextEditorText = new QAction(CuteLittleNotesClass);
        actionSetColorTextEditorText->setObjectName(QStringLiteral("actionSetColorTextEditorText"));
        actionSetTextMarkDone = new QAction(CuteLittleNotesClass);
        actionSetTextMarkDone->setObjectName(QStringLiteral("actionSetTextMarkDone"));
        actionSetTextMarkScrapped = new QAction(CuteLittleNotesClass);
        actionSetTextMarkScrapped->setObjectName(QStringLiteral("actionSetTextMarkScrapped"));
        actionListTitle = new QAction(CuteLittleNotesClass);
        actionListTitle->setObjectName(QStringLiteral("actionListTitle"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/CuteLittleNotes/IconsBuiltIn/toolbar-icon-list-title.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionListTitle->setIcon(icon6);
        actionPrefCommentSetColor = new QAction(CuteLittleNotesClass);
        actionPrefCommentSetColor->setObjectName(QStringLiteral("actionPrefCommentSetColor"));
        actionPrefCommentSetText = new QAction(CuteLittleNotesClass);
        actionPrefCommentSetText->setObjectName(QStringLiteral("actionPrefCommentSetText"));
        actionPrefMarkDoneSetColor = new QAction(CuteLittleNotesClass);
        actionPrefMarkDoneSetColor->setObjectName(QStringLiteral("actionPrefMarkDoneSetColor"));
        actionPrefMarkDoneSetText = new QAction(CuteLittleNotesClass);
        actionPrefMarkDoneSetText->setObjectName(QStringLiteral("actionPrefMarkDoneSetText"));
        actionPrefMarkScrappedSetColor = new QAction(CuteLittleNotesClass);
        actionPrefMarkScrappedSetColor->setObjectName(QStringLiteral("actionPrefMarkScrappedSetColor"));
        actionPrefMarkScrappedSetText = new QAction(CuteLittleNotesClass);
        actionPrefMarkScrappedSetText->setObjectName(QStringLiteral("actionPrefMarkScrappedSetText"));
        actionPrefListTitleSetColorBg = new QAction(CuteLittleNotesClass);
        actionPrefListTitleSetColorBg->setObjectName(QStringLiteral("actionPrefListTitleSetColorBg"));
        actionPrefListTitleSetColorText = new QAction(CuteLittleNotesClass);
        actionPrefListTitleSetColorText->setObjectName(QStringLiteral("actionPrefListTitleSetColorText"));
        actionPrefSaveManual = new QAction(CuteLittleNotesClass);
        actionPrefSaveManual->setObjectName(QStringLiteral("actionPrefSaveManual"));
        actionToolbarToggleVis = new QAction(CuteLittleNotesClass);
        actionToolbarToggleVis->setObjectName(QStringLiteral("actionToolbarToggleVis"));
        actionToolbarToggleVis->setCheckable(true);
        actionToolbarToggleVis->setChecked(true);
        actionFormattingRemoveAll = new QAction(CuteLittleNotesClass);
        actionFormattingRemoveAll->setObjectName(QStringLiteral("actionFormattingRemoveAll"));
        actionSaveAsPlainText = new QAction(CuteLittleNotesClass);
        actionSaveAsPlainText->setObjectName(QStringLiteral("actionSaveAsPlainText"));
        actionPrefSetTheme = new QAction(CuteLittleNotesClass);
        actionPrefSetTheme->setObjectName(QStringLiteral("actionPrefSetTheme"));
        actionPrefToggleModding = new QAction(CuteLittleNotesClass);
        actionPrefToggleModding->setObjectName(QStringLiteral("actionPrefToggleModding"));
        actionPrefToggleModding->setCheckable(true);
        actionPrefSetJotOverrides = new QAction(CuteLittleNotesClass);
        actionPrefSetJotOverrides->setObjectName(QStringLiteral("actionPrefSetJotOverrides"));
        actionPrefDisableOverrides = new QAction(CuteLittleNotesClass);
        actionPrefDisableOverrides->setObjectName(QStringLiteral("actionPrefDisableOverrides"));
        actionPrefDisableOverrides->setCheckable(true);
        centralWidget = new QWidget(CuteLittleNotesClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        QFont font;
        font.setPointSize(10);
        textEdit->setFont(font);
        textEdit->setStyleSheet(QStringLiteral(""));
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        gridLayout->addWidget(textEdit, 0, 0, 1, 1);

        CuteLittleNotesClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CuteLittleNotesClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        action = new QAction(menuView);
        action->setObjectName(QStringLiteral("action"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuJot = new QMenu(menuBar);
        menuJot->setObjectName(QStringLiteral("menuJot"));
        menuList = new QMenu(menuJot);
        menuList->setObjectName(QStringLiteral("menuList"));
        menuPreferences = new QMenu(menuBar);
        menuPreferences->setObjectName(QStringLiteral("menuPreferences"));
        menuPrefComment = new QMenu(menuPreferences);
        menuPrefComment->setObjectName(QStringLiteral("menuPrefComment"));
        menuPrefMarkDone = new QMenu(menuPreferences);
        menuPrefMarkDone->setObjectName(QStringLiteral("menuPrefMarkDone"));
        menuPrefMarkScrapped = new QMenu(menuPreferences);
        menuPrefMarkScrapped->setObjectName(QStringLiteral("menuPrefMarkScrapped"));
        menuPrefListTitle = new QMenu(menuPreferences);
        menuPrefListTitle->setObjectName(QStringLiteral("menuPrefListTitle"));
        menuPrefOverrideTheme = new QMenu(menuPreferences);
        menuPrefOverrideTheme->setObjectName(QStringLiteral("menuPrefOverrideTheme"));
        CuteLittleNotesClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CuteLittleNotesClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy);
        mainToolBar->setMovable(false);
        mainToolBar->setOrientation(Qt::Horizontal);
        CuteLittleNotesClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CuteLittleNotesClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CuteLittleNotesClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuJot->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuPreferences->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSaveAs);
        menuFile->addSeparator();
        menuFile->addAction(actionSaveAsPlainText);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuView->addAction(actionWordWrap);
        menuView->addAction(actionToolbarToggleVis);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addAction(actionPastePlainText);
        menuEdit->addSeparator();
        menuEdit->addAction(actionFormattingRemoveAll);
        menuJot->addAction(actionComment);
        menuJot->addAction(actionListTitle);
        menuJot->addSeparator();
        menuJot->addAction(menuList->menuAction());
        menuList->addAction(actionMarkDone);
        menuList->addAction(actionMarkScrapped);
        menuPreferences->addAction(menuPrefComment->menuAction());
        menuPreferences->addAction(menuPrefListTitle->menuAction());
        menuPreferences->addSeparator();
        menuPreferences->addAction(menuPrefMarkDone->menuAction());
        menuPreferences->addAction(menuPrefMarkScrapped->menuAction());
        menuPreferences->addSeparator();
        menuPreferences->addAction(menuPrefOverrideTheme->menuAction());
        menuPreferences->addAction(actionPrefSetTheme);
        menuPreferences->addAction(actionPrefToggleModding);
        menuPreferences->addSeparator();
        menuPreferences->addAction(actionPrefSaveManual);
        menuPrefComment->addAction(actionPrefCommentSetColor);
        menuPrefMarkDone->addAction(actionPrefMarkDoneSetColor);
        menuPrefMarkDone->addAction(actionPrefMarkDoneSetText);
        menuPrefMarkScrapped->addAction(actionPrefMarkScrappedSetColor);
        menuPrefMarkScrapped->addAction(actionPrefMarkScrappedSetText);
        menuPrefListTitle->addAction(actionPrefListTitleSetColorBg);
        menuPrefListTitle->addAction(actionPrefListTitleSetColorText);
        menuPrefOverrideTheme->addAction(actionPrefSetJotOverrides);
        menuPrefOverrideTheme->addAction(actionPrefDisableOverrides);
        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionSave);
        mainToolBar->addAction(actionComment);
        mainToolBar->addAction(actionListTitle);
        mainToolBar->addAction(actionMarkDone);
        mainToolBar->addAction(actionMarkScrapped);

        retranslateUi(CuteLittleNotesClass);

        QMetaObject::connectSlotsByName(CuteLittleNotesClass);
    } // setupUi

    void retranslateUi(QMainWindow *CuteLittleNotesClass)
    {
        CuteLittleNotesClass->setWindowTitle(QString());
        actionSaveAs->setText(QApplication::translate("CuteLittleNotesClass", "Save As...", nullptr));
        actionSave->setText(QApplication::translate("CuteLittleNotesClass", "Save", nullptr));
        actionOpen->setText(QApplication::translate("CuteLittleNotesClass", "Open...", nullptr));
        actionNew->setText(QApplication::translate("CuteLittleNotesClass", "New", nullptr));
        actionWordWrap->setText(QApplication::translate("CuteLittleNotesClass", "Word Wrap", nullptr));
        actionUndo->setText(QApplication::translate("CuteLittleNotesClass", "Undo", nullptr));
#ifndef QT_NO_SHORTCUT
        actionUndo->setShortcut(QApplication::translate("CuteLittleNotesClass", "Ctrl+Z", nullptr));
#endif // QT_NO_SHORTCUT
        actionRedo->setText(QApplication::translate("CuteLittleNotesClass", "Redo", nullptr));
#ifndef QT_NO_SHORTCUT
        actionRedo->setShortcut(QApplication::translate("CuteLittleNotesClass", "Ctrl+Y", nullptr));
#endif // QT_NO_SHORTCUT
        actionComment->setText(QApplication::translate("CuteLittleNotesClass", "Comment", nullptr));
        actionMarkDone->setText(QApplication::translate("CuteLittleNotesClass", "Mark Done", nullptr));
        actionMarkScrapped->setText(QApplication::translate("CuteLittleNotesClass", "Mark Scrapped", nullptr));
        actionStripFormatting->setText(QApplication::translate("CuteLittleNotesClass", "Strip Formatting from Selected Text", nullptr));
        actionPasteStripFormatting->setText(QApplication::translate("CuteLittleNotesClass", "Paste Strips Formatting", nullptr));
        actionPastePlainText->setText(QApplication::translate("CuteLittleNotesClass", "Paste as Plain Text", nullptr));
        actionExit->setText(QApplication::translate("CuteLittleNotesClass", "Exit", nullptr));
        actionSetColorComment->setText(QApplication::translate("CuteLittleNotesClass", "Comment", nullptr));
        actionSetColorMarkDone->setText(QApplication::translate("CuteLittleNotesClass", "Mark Done", nullptr));
        actionSetColorMarkScrapped->setText(QApplication::translate("CuteLittleNotesClass", "Mark Scrapped", nullptr));
        actionSetColorTextEditorBackground->setText(QApplication::translate("CuteLittleNotesClass", "Background", nullptr));
        actionSetColorTextEditorText->setText(QApplication::translate("CuteLittleNotesClass", "Text", nullptr));
        actionSetTextMarkDone->setText(QApplication::translate("CuteLittleNotesClass", "Mark Done", nullptr));
        actionSetTextMarkScrapped->setText(QApplication::translate("CuteLittleNotesClass", "Mark Scrapped", nullptr));
        actionListTitle->setText(QApplication::translate("CuteLittleNotesClass", "List Title", nullptr));
        actionPrefCommentSetColor->setText(QApplication::translate("CuteLittleNotesClass", "Set Color", nullptr));
        actionPrefCommentSetText->setText(QApplication::translate("CuteLittleNotesClass", "Set Text", nullptr));
        actionPrefMarkDoneSetColor->setText(QApplication::translate("CuteLittleNotesClass", "Set Color", nullptr));
        actionPrefMarkDoneSetText->setText(QApplication::translate("CuteLittleNotesClass", "Set Text", nullptr));
        actionPrefMarkScrappedSetColor->setText(QApplication::translate("CuteLittleNotesClass", "Set Color", nullptr));
        actionPrefMarkScrappedSetText->setText(QApplication::translate("CuteLittleNotesClass", "Set Text", nullptr));
        actionPrefListTitleSetColorBg->setText(QApplication::translate("CuteLittleNotesClass", "Set Color Bg", nullptr));
        actionPrefListTitleSetColorText->setText(QApplication::translate("CuteLittleNotesClass", "Set Color Text", nullptr));
        actionPrefSaveManual->setText(QApplication::translate("CuteLittleNotesClass", "Save Preferences", nullptr));
#ifndef QT_NO_TOOLTIP
        actionPrefSaveManual->setToolTip(QApplication::translate("CuteLittleNotesClass", "Save Preferences", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionPrefSaveManual->setStatusTip(QApplication::translate("CuteLittleNotesClass", "Preferences are saved automatically on exit, but you can also save them manually.", nullptr));
#endif // QT_NO_STATUSTIP
        actionToolbarToggleVis->setText(QApplication::translate("CuteLittleNotesClass", "Toolbar", nullptr));
        actionFormattingRemoveAll->setText(QApplication::translate("CuteLittleNotesClass", "Remove Special Formatting", nullptr));
#ifndef QT_NO_STATUSTIP
        actionFormattingRemoveAll->setStatusTip(QApplication::translate("CuteLittleNotesClass", "This will remove special formatting, such as text color or background color.", nullptr));
#endif // QT_NO_STATUSTIP
        actionSaveAsPlainText->setText(QApplication::translate("CuteLittleNotesClass", "Save As Plain Text", nullptr));
#ifndef QT_NO_STATUSTIP
        actionSaveAsPlainText->setStatusTip(QApplication::translate("CuteLittleNotesClass", "This will save the file without special formatting, such as text color or background color.", nullptr));
#endif // QT_NO_STATUSTIP
        actionPrefSetTheme->setText(QApplication::translate("CuteLittleNotesClass", "Set Theme", nullptr));
        actionPrefToggleModding->setText(QApplication::translate("CuteLittleNotesClass", "Enable Mods", nullptr));
#ifndef QT_NO_STATUSTIP
        actionPrefToggleModding->setStatusTip(QApplication::translate("CuteLittleNotesClass", "If enabled, the program will check the local Mods folder for content upon loading.", nullptr));
#endif // QT_NO_STATUSTIP
        actionPrefSetJotOverrides->setText(QApplication::translate("CuteLittleNotesClass", "Set Jot Overrides", nullptr));
#ifndef QT_NO_STATUSTIP
        actionPrefSetJotOverrides->setStatusTip(QApplication::translate("CuteLittleNotesClass", "Theme overrides are set and saved relative to the current theme.", nullptr));
#endif // QT_NO_STATUSTIP
        actionPrefDisableOverrides->setText(QApplication::translate("CuteLittleNotesClass", "Disable Overrides", nullptr));
#ifndef QT_NO_STATUSTIP
        actionPrefDisableOverrides->setStatusTip(QApplication::translate("CuteLittleNotesClass", "Disabling overrides will cause any set overrides to be ignored.", nullptr));
#endif // QT_NO_STATUSTIP
        menuFile->setTitle(QApplication::translate("CuteLittleNotesClass", "File", nullptr));
        menuView->setTitle(QApplication::translate("CuteLittleNotesClass", "View", nullptr));
        menuEdit->setTitle(QApplication::translate("CuteLittleNotesClass", "Edit", nullptr));
        menuJot->setTitle(QApplication::translate("CuteLittleNotesClass", "Jot", nullptr));
        menuList->setTitle(QApplication::translate("CuteLittleNotesClass", "List Item", nullptr));
        menuPreferences->setTitle(QApplication::translate("CuteLittleNotesClass", "Preferences", nullptr));
        menuPrefComment->setTitle(QApplication::translate("CuteLittleNotesClass", "Comment", nullptr));
        menuPrefMarkDone->setTitle(QApplication::translate("CuteLittleNotesClass", "Mark Done", nullptr));
        menuPrefMarkScrapped->setTitle(QApplication::translate("CuteLittleNotesClass", "Mark Scrapped", nullptr));
        menuPrefListTitle->setTitle(QApplication::translate("CuteLittleNotesClass", "List Title", nullptr));
        menuPrefOverrideTheme->setTitle(QApplication::translate("CuteLittleNotesClass", "Override Theme", nullptr));
        mainToolBar->setWindowTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class CuteLittleNotesClass: public Ui_CuteLittleNotesClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUTELITTLENOTES_H
