#ifndef LANDINGWIDGET_HPP
#define LANDINGWIDGET_HPP

#include <QWidget>

namespace Ui
{
class LandingWidget;
}

class LandingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LandingWidget(QAction *openSaveAction, QWidget *parent = nullptr);
    ~LandingWidget();

private:
    Ui::LandingWidget *ui;
};

#endif // LANDINGWIDGET_HPP
