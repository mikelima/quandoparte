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

#include "stationlistview.h"
#include "ui_stationlistview.h"

#include "keypressforwarder.h"
#include "settingsdialog.h"

#include <QActionGroup>
#include <QDebug>
#include <QKeyEvent>
#include <QSortFilterProxyModel>
#include <QStringListModel>

StationListView::StationListView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StationListView),
    viewSelectionGroup(new QActionGroup(0)),
    stationListModel(new QStringListModel(this)),
    filterModel(new QSortFilterProxyModel(this)),
    keyPressForwarder(new KeyPressForwarder(this))

{
#ifdef Q_WS_MAEMO_5
    setAttribute(Qt::WA_Maemo5StackedWindow);
    setAttribute(Qt::WA_Maemo5AutoOrientation);
#endif
    ui->setupUi(this);
    viewSelectionGroup->addAction(ui->sortByNameAction);
    viewSelectionGroup->addAction(ui->sortNearFirstAction);
    viewSelectionGroup->addAction(ui->sortRecentFirstAction);
    QStringList stationList;
    stationList << "Savona"
                << "Albisola"
                << "Celle"
                << "Varazze"
                << "Cogoleto"
                << "Arenzano"
                << "Genova Voltri"
                << "Genova Pra"
                << "Genova Pegli"
                << "Genova Sestri Ponente"
                << "Genova Cornigliano"
                << "Genova Sampierdarena"
                << "Genova Borzoli"
                << "Genova Costa di Sestri Ponente"
                << "Genova Granara"
                << "Genova Acquasanta"
                << "Mele"
                << "Campo Ligure"
                << "Rossiglione"
                << "Ovada"
                << "Molare"
                << "Prasco Cremolino"
                << "Visone"
                << "Acqui Terme"
                << "Alice Belcolle"
                << "Mombaruzzo"
                << "Nizza Monferrato"
                << "Castelnuovo Calcea"
                << "Montegrosso"
                << "Vigliano"
                << "Mongardino"
                << "Asti"
                << "Genova Rivarolo"
                << "Genova Bolzaneto"
                << "Genova San Biagio"
                << "Genova Pontedecimo"
                << "Piano Orzzontale dei Giovi"
                << "Mignanego"
                << "Busalla"
                << "Borgo Fornari"
                << "Ronco Scrivia"
                << "Arquata Scrivia"
                << "Serravalle Scrivia"
                << "Novi Ligure"
                << "Alessandria"
                << "Genova Via di Francia"
                << "Genova Piazza Principe"
                << "Genova Brignole"
                << "Genova Sturla"
                << "Genova Quarto dei Mille"
                << "Genova Quinto al Mare"
                << "Genova Nervi"
                << "Bogliasco"
                << "Pontetto"
                << "Pieve Ligure"
                << "Sori"
                << "Mulinetti"
                << "Recco"
                << "Camogli";
    stationListModel->setStringList(stationList);
    filterModel->setSourceModel(stationListModel);
    filterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    ui->listView->setModel(filterModel);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->filterEdit->hide();

    keyPressForwarder->setTarget(ui->filterEdit);
    ui->listView->installEventFilter(keyPressForwarder);

    connect(ui->showAboutAction, SIGNAL(triggered()),
            this, SIGNAL(aboutTriggered()));
    connect(ui->listView,
            SIGNAL(activated(QModelIndex)), SLOT(showStation(QModelIndex)));
    connect(ui->filterEdit, SIGNAL(textChanged(const QString &)),
            SLOT(handleFilterChanges(const QString &)));
}

StationListView::~StationListView()
{
    delete ui;
}

void StationListView::showSettings(void)
{
    qDebug() << "Show Settings";
    SettingsDialog *settingsDialog = new SettingsDialog(this);
    if (settingsDialog->exec() == QDialog::Accepted) {
        // TODO Use new settings
    }

    delete settingsDialog;
}

void StationListView::showStation(const QModelIndex &index)
{
    qDebug() << "Show Station" << index.data();
    emit stationSelected(index.data().toString());
}

void StationListView::handleFilterChanges(const QString &filter)
{
    if (!filter.isEmpty())
        ui->filterEdit->show();
    else
        ui->filterEdit->hide();
    filterModel->setFilterFixedString(filter);
}
