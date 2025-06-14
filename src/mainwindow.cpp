#include "mainwindow.hpp"

#include "forms/ui_mainwindow.h"
#include "landingwidget.hpp"

using namespace Qt::Literals::StringLiterals;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , ui{new Ui::MainWindow}
    , m_openSaveAction{new QAction(this)}
{
    m_openSaveAction->setText(tr("Open"));
    m_openSaveAction->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen));
    m_openSaveAction->setShortcut(Qt::CTRL | Qt::Key_O);

    ui->setupUi(this);

    setCentralWidget(new LandingWidget(m_openSaveAction, this));
}

MainWindow::~MainWindow()
{
    delete ui;
}
