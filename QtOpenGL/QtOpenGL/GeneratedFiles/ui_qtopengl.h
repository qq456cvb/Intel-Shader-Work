/********************************************************************************
** Form generated from reading UI file 'qtopengl.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTOPENGL_H
#define UI_QTOPENGL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtOpenGLClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtOpenGLClass)
    {
        if (QtOpenGLClass->objectName().isEmpty())
            QtOpenGLClass->setObjectName(QStringLiteral("QtOpenGLClass"));
        QtOpenGLClass->resize(600, 400);
        menuBar = new QMenuBar(QtOpenGLClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        QtOpenGLClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtOpenGLClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtOpenGLClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtOpenGLClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QtOpenGLClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtOpenGLClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtOpenGLClass->setStatusBar(statusBar);

        retranslateUi(QtOpenGLClass);

        QMetaObject::connectSlotsByName(QtOpenGLClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtOpenGLClass)
    {
        QtOpenGLClass->setWindowTitle(QApplication::translate("QtOpenGLClass", "QtOpenGL", 0));
    } // retranslateUi

};

namespace Ui {
    class QtOpenGLClass: public Ui_QtOpenGLClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTOPENGL_H
