#include "landingwidget.hpp"
#include "forms/ui_landingwidget.h"

#include <QApplication>

LandingWidget::LandingWidget(QAction *openSaveAction, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LandingWidget)
{
    ui->setupUi(this);

    ui->applicationNameLabel->setText(qApp->applicationDisplayName());
    ui->applicationIconLabel->setPixmap(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen).pixmap(QSize(144, 144), QIcon::Normal, QIcon::On));

    ui->openSaveButton->setText(openSaveAction->text());
    ui->openSaveButton->setIcon(openSaveAction->icon());
    ui->openSaveButton->setShortcut(openSaveAction->shortcut());
    connect(ui->openSaveButton, &QPushButton::clicked, openSaveAction, &QAction::trigger);
}

LandingWidget::~LandingWidget()
{
    delete ui;
}
