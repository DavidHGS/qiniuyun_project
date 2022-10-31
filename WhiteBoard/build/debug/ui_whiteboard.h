/********************************************************************************
** Form generated from reading UI file 'whiteboard.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WHITEBOARD_H
#define UI_WHITEBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WhiteBoard
{
public:
    QAction *action_export;
    QAction *action_import;
    QAction *action_rect;
    QAction *action_circle;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_8;
    QRadioButton *radioButton;
    QRadioButton *radioButton_rect;
    QRadioButton *radioButton_circle;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView_whiteBoard;
    QWidget *widget_attribute;
    QHBoxLayout *horizontalLayout_7;
    QTabWidget *tabWidget;
    QWidget *tab_style;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *comboBox_lineWidth;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QPushButton *pushButton_lineColor;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QPushButton *pushButton_3;
    QSpacerItem *verticalSpacer_2;
    QWidget *tab_text;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_5;
    QComboBox *comboBox_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_6;
    QComboBox *comboBox_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *WhiteBoard)
    {
        if (WhiteBoard->objectName().isEmpty())
            WhiteBoard->setObjectName(QStringLiteral("WhiteBoard"));
        WhiteBoard->resize(983, 684);
        action_export = new QAction(WhiteBoard);
        action_export->setObjectName(QStringLiteral("action_export"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/source/export.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_export->setIcon(icon);
        action_import = new QAction(WhiteBoard);
        action_import->setObjectName(QStringLiteral("action_import"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/source/import.jpeg"), QSize(), QIcon::Normal, QIcon::Off);
        action_import->setIcon(icon1);
        action_rect = new QAction(WhiteBoard);
        action_rect->setObjectName(QStringLiteral("action_rect"));
        action_circle = new QAction(WhiteBoard);
        action_circle->setObjectName(QStringLiteral("action_circle"));
        centralWidget = new QWidget(WhiteBoard);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        radioButton = new QRadioButton(centralWidget);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        horizontalLayout_8->addWidget(radioButton);

        radioButton_rect = new QRadioButton(centralWidget);
        radioButton_rect->setObjectName(QStringLiteral("radioButton_rect"));

        horizontalLayout_8->addWidget(radioButton_rect);

        radioButton_circle = new QRadioButton(centralWidget);
        radioButton_circle->setObjectName(QStringLiteral("radioButton_circle"));

        horizontalLayout_8->addWidget(radioButton_circle);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        graphicsView_whiteBoard = new QGraphicsView(centralWidget);
        graphicsView_whiteBoard->setObjectName(QStringLiteral("graphicsView_whiteBoard"));

        horizontalLayout->addWidget(graphicsView_whiteBoard);

        widget_attribute = new QWidget(centralWidget);
        widget_attribute->setObjectName(QStringLiteral("widget_attribute"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_attribute->sizePolicy().hasHeightForWidth());
        widget_attribute->setSizePolicy(sizePolicy);
        horizontalLayout_7 = new QHBoxLayout(widget_attribute);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        tabWidget = new QTabWidget(widget_attribute);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab_style = new QWidget();
        tab_style->setObjectName(QStringLiteral("tab_style"));
        verticalLayout_2 = new QVBoxLayout(tab_style);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(tab_style);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        comboBox_lineWidth = new QComboBox(tab_style);
        comboBox_lineWidth->setObjectName(QStringLiteral("comboBox_lineWidth"));

        horizontalLayout_3->addWidget(comboBox_lineWidth);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 2);

        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(tab_style);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        comboBox = new QComboBox(tab_style);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_4->addWidget(comboBox);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 2);

        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_3 = new QLabel(tab_style);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_5->addWidget(label_3);

        pushButton_lineColor = new QPushButton(tab_style);
        pushButton_lineColor->setObjectName(QStringLiteral("pushButton_lineColor"));
        pushButton_lineColor->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));

        horizontalLayout_5->addWidget(pushButton_lineColor);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 2);

        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_4 = new QLabel(tab_style);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_6->addWidget(label_4);

        pushButton_3 = new QPushButton(tab_style);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        horizontalLayout_6->addWidget(pushButton_3);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 2);

        verticalLayout_2->addLayout(horizontalLayout_6);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        tabWidget->addTab(tab_style, QString());
        tab_text = new QWidget();
        tab_text->setObjectName(QStringLiteral("tab_text"));
        verticalLayout_3 = new QVBoxLayout(tab_text);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_5 = new QLabel(tab_text);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_10->addWidget(label_5);

        comboBox_3 = new QComboBox(tab_text);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));

        horizontalLayout_10->addWidget(comboBox_3);

        horizontalLayout_10->setStretch(0, 1);
        horizontalLayout_10->setStretch(1, 2);

        verticalLayout_3->addLayout(horizontalLayout_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_6 = new QLabel(tab_text);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_9->addWidget(label_6);

        comboBox_2 = new QComboBox(tab_text);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        horizontalLayout_9->addWidget(comboBox_2);

        horizontalLayout_9->setStretch(0, 1);
        horizontalLayout_9->setStretch(1, 2);

        verticalLayout_3->addLayout(horizontalLayout_9);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        tabWidget->addTab(tab_text, QString());

        horizontalLayout_7->addWidget(tabWidget);


        horizontalLayout->addWidget(widget_attribute);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_2);

        WhiteBoard->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(WhiteBoard);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 983, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        WhiteBoard->setMenuBar(menuBar);
        mainToolBar = new QToolBar(WhiteBoard);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        WhiteBoard->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(WhiteBoard);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        WhiteBoard->setStatusBar(statusBar);
        QWidget::setTabOrder(pushButton, pushButton_2);
        QWidget::setTabOrder(pushButton_2, comboBox_lineWidth);
        QWidget::setTabOrder(comboBox_lineWidth, comboBox);
        QWidget::setTabOrder(comboBox, pushButton_lineColor);
        QWidget::setTabOrder(pushButton_lineColor, pushButton_3);
        QWidget::setTabOrder(pushButton_3, tabWidget);
        QWidget::setTabOrder(tabWidget, comboBox_2);

        menuBar->addAction(menu->menuAction());
        menu->addAction(action_export);
        menu->addAction(action_import);

        retranslateUi(WhiteBoard);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(WhiteBoard);
    } // setupUi

    void retranslateUi(QMainWindow *WhiteBoard)
    {
        WhiteBoard->setWindowTitle(QApplication::translate("WhiteBoard", "WhiteBoard", Q_NULLPTR));
        action_export->setText(QApplication::translate("WhiteBoard", "\345\257\274\345\207\272", Q_NULLPTR));
        action_import->setText(QApplication::translate("WhiteBoard", "\345\257\274\345\205\245", Q_NULLPTR));
        action_rect->setText(QApplication::translate("WhiteBoard", "\347\237\251\345\275\242", Q_NULLPTR));
        action_circle->setText(QApplication::translate("WhiteBoard", "\345\234\206\345\275\242", Q_NULLPTR));
        radioButton->setText(QApplication::translate("WhiteBoard", "\346\211\213", Q_NULLPTR));
        radioButton_rect->setText(QApplication::translate("WhiteBoard", "\347\237\251\345\275\242", Q_NULLPTR));
        radioButton_circle->setText(QApplication::translate("WhiteBoard", "\345\234\206", Q_NULLPTR));
        label->setText(QApplication::translate("WhiteBoard", "\347\272\277\345\256\275\357\274\232", Q_NULLPTR));
        comboBox_lineWidth->clear();
        comboBox_lineWidth->insertItems(0, QStringList()
         << QApplication::translate("WhiteBoard", "1px", Q_NULLPTR)
         << QApplication::translate("WhiteBoard", "2px", Q_NULLPTR)
        );
        label_2->setText(QApplication::translate("WhiteBoard", "\347\272\277\345\275\242\357\274\232", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("WhiteBoard", "\345\256\236\347\272\277", Q_NULLPTR)
         << QApplication::translate("WhiteBoard", "\350\231\232\347\272\277", Q_NULLPTR)
        );
        label_3->setText(QApplication::translate("WhiteBoard", "\347\272\277\350\211\262\357\274\232", Q_NULLPTR));
        pushButton_lineColor->setText(QString());
        label_4->setText(QApplication::translate("WhiteBoard", "\345\241\253\345\205\205\357\274\232", Q_NULLPTR));
        pushButton_3->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_style), QApplication::translate("WhiteBoard", "\346\240\267\345\274\217", Q_NULLPTR));
        label_5->setText(QApplication::translate("WhiteBoard", "\345\255\227\344\275\223\357\274\232", Q_NULLPTR));
        comboBox_3->clear();
        comboBox_3->insertItems(0, QStringList()
         << QApplication::translate("WhiteBoard", "\345\276\256\350\275\257\351\233\205\351\273\221", Q_NULLPTR)
         << QApplication::translate("WhiteBoard", "\345\256\213\344\275\223", Q_NULLPTR)
        );
        label_6->setText(QApplication::translate("WhiteBoard", "\345\255\227\345\217\267\357\274\232", Q_NULLPTR));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("WhiteBoard", "1px", Q_NULLPTR)
         << QApplication::translate("WhiteBoard", "2px", Q_NULLPTR)
        );
        tabWidget->setTabText(tabWidget->indexOf(tab_text), QApplication::translate("WhiteBoard", "\346\226\207\346\234\254", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("WhiteBoard", "\351\207\215\345\201\232", Q_NULLPTR));
        pushButton->setText(QApplication::translate("WhiteBoard", "\346\222\244\351\224\200", Q_NULLPTR));
        menu->setTitle(QApplication::translate("WhiteBoard", "\346\226\207\344\273\266", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WhiteBoard: public Ui_WhiteBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WHITEBOARD_H
