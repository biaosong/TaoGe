#ifndef CUSTOMTABWIDGET_WEST_H
#define CUSTOMTABWIDGET_WEST_H

#include <QTabWidget>
#include <QProxyStyle>
#include <QStyleOptionTab>
#include <QPainter>
class CustomTabStyle : public QProxyStyle
{
public:
//    QSize sizeFormContents(ContentsType type,const QStyleOption *option, const QSize &size,const QWidget *widget) const
//    {
//        QSize s = QProxyStyle::sizeFromContents(type,option,size,widget);
//        if(type == QStyle::CT_TabBarTab){
//            s.transpose();
//            s.setWidth(180);
//            s.setHeight(40);
//        }
//        return s;
//    }
    QSize sizeFromContents(ContentsType type, const QStyleOption *option,
            const QSize &size, const QWidget *widget) const
        {
            QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
            if (type == QStyle::CT_TabBarTab) {
                s.transpose();
                s.rwidth() = 180; // 设置每个tabBar中item的大小
                s.rheight() = 71;
            }
            return s;
        }

    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
        {
            if (element == CE_TabBarTabLabel) {
                if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option)) {
                    QRect allRect = tab->rect;

                    if (tab->state & QStyle::State_Selected) {
                        painter->save();
                        painter->setPen(0xFFFFFF);
                        painter->setBrush(QBrush(0x2EA2EC));
                        painter->drawRect(allRect.adjusted(0, 0, 0, 0));
                        painter->restore();
                    }else {
                        painter->save();
                        painter->setPen(0xF3F3F3);
                        painter->setBrush(QBrush(0xDEDEDE));
                        painter->drawRect(allRect.adjusted(0, 0, 0, 0));
                        painter->restore();
                    }
                    QTextOption option;
                    option.setAlignment(Qt::AlignCenter);
                    if (tab->state & QStyle::State_Selected) {
                        painter->setPen(0xFFFFFF);
                    }
                    else {
                        painter->setPen(0x5d6373);
                    }

                    painter->drawText(allRect, tab->text, option);
                    return;
                }
            }

            if (element == CE_TabBarTab) {
                QProxyStyle::drawControl(element, option, painter, widget);
            }
        }
};

class CustomTabWidget_West : public QTabWidget
{
    Q_OBJECT
public:
    CustomTabWidget_West(QWidget *parent,QString picture = "");
};



#endif // CUSTOMTABLEWIDGET_WEST_H
