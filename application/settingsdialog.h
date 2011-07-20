#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

/*

Copyright (C) 2011 Luciano Montanaro <mikelima@cirulla.net>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to
the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA.

*/

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

private slots:
    void showStationChanged(bool);

    void periodicUpdateToggled(bool checked);

private:
#ifdef Q_WS_MAEMO_5
    QMaemo5ValueButton *updateIntervalButton;
#endif
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
