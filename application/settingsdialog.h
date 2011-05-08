#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

#ifdef Q_WS_MAEMO_5
class QMaemo5ValueButton;
#endif

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

private:
#ifdef Q_WS_MAEMO_5
    QMaemo5ValueButton *updateIntervalButton;
#endif
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
