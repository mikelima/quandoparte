#ifndef QP_VIEW_H
#define QP_VIEW_H

#include <QDeclarativeView>

class View : public QDeclarativeView
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = 0);

signals:

public slots:

private:
};

#endif // QP_VIEW_H
