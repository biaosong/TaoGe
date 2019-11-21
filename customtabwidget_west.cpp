#include "customtabwidget_west.h"

CustomTabWidget_West::CustomTabWidget_West(QWidget *parent,QString picture)
    :QTabWidget(parent)
{
    this->setFocusPolicy(Qt::NoFocus);
    this->setTabPosition(QTabWidget::West);
    this->tabBar()->setStyle(new CustomTabStyle);
    this->tabBar()->setFont(QFont("Microsoft YaHei",12,QFont::Bold));
}
