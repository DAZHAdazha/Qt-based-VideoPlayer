#ifndef ABSOLUTESETSTYLE_H
#define ABSOLUTESETSTYLE_H

#include <QProxyStyle>

// https://stackoverflow.com/questions/11132597/qslider-mouse-direct-jump
class AbsoluteSetStyle : public QProxyStyle {
   public:
    using QProxyStyle::QProxyStyle;

    int styleHint(QStyle::StyleHint hint, const QStyleOption* option = 0, const QWidget* widget = 0,
                  QStyleHintReturn* returnData = 0) const {
        if (hint == QStyle::SH_Slider_AbsoluteSetButtons)
            return (Qt::LeftButton | Qt::MidButton | Qt::RightButton);
        return QProxyStyle::styleHint(hint, option, widget, returnData);
    }
};

#endif  // ABSOLUTESETSTYLE_H