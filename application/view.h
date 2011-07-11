#ifndef QP_VIEW_H
#define QP_VIEW_H

#include <QWidget>

class QDeclarativeView;

class View : public QWidget
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = 0);

signals:

public slots:

private:
    QDeclarativeView *m_view;
};

#endif // QP_VIEW_H
