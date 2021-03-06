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

#include <settings.h>
#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#ifdef Q_WS_MAEMO_5
#include <QMaemo5ValueButton>
#endif


SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
#ifdef Q_WS_MAEMO_5
    updateIntervalButton(new QMaemo5ValueButton(this)),
#endif
    ui(new Ui::SettingsDialog)
{
    Settings *settings = Settings::instance();

    ui->setupUi(this);

    bool showStationPreference = settings->stationViewPreferred();
    ui->showLastStationCheckBox->setChecked(showStationPreference);
    connect(ui->showLastStationCheckBox, SIGNAL(toggled(bool)),
            SLOT(showStationChanged(bool)));

    bool checkingInterval = settings->checkingInterval();
    ui->periodicUpdateCheckBox->setChecked(checkingInterval > 30000);
    connect(ui->periodicUpdateCheckBox, SIGNAL(toggled(bool)),
            SLOT(periodicUpdateToggled(bool)));
#if 0
#ifdef Q_WS_MAEMO_5
    ui->formLayout->addWidget(updateIntervalButton);
#endif
#endif
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::showStationChanged(bool newValue)
{
    Settings *settings = Settings::instance();
    settings->setStationViewPreferred(newValue);
}

void SettingsDialog::periodicUpdateToggled(bool checked)
{
    Settings *settings = Settings::instance();
    settings->setCheckingInterval(checked ? 120000 : 0);
}
