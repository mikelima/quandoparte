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

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtCore/QCoreApplication>

#include "../application/stationlistmodel.h"

class AppTest : public QObject
{
    Q_OBJECT

public:
    AppTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
    void testCase2();
    void testCase3();
    void testCase4();
    void testCase5();

private:
    StationListModel *model;
    QString path;
};

AppTest::AppTest()
{
        model = new StationListModel(this);
        path = QCoreApplication::applicationDirPath();
}

void AppTest::initTestCase()
{
}

void AppTest::cleanupTestCase()
{
}

void AppTest::testCase1()
{
    QVERIFY2(false == model->load(path + "/testfiles/missing.qpl"), "File does not exist, should not return ok");
}

void AppTest::testCase2()
{
    QVERIFY2(true == model->load(path + "/testfiles/empty.qpl"), "File cannot be loaeded");
    QVERIFY2(0 == model->rowCount(), "Should be empty");
}

void AppTest::testCase3()
{
    QVERIFY2(false == model->load(path + "/testfiles/malformed1.qpl"), "Tags are wrong, should not return ok");
}

void AppTest::testCase4()
{
    QVERIFY2(true == model->load(path + "/testfiles/emptystation.qpl"), "cannot open file");
}

void AppTest::testCase5()
{
    qDebug() << model->rowCount();
    QVERIFY2(true == model->load(path + "/testfiles/teststation.qpl"), "cannot open file");
    qDebug() << model->rowCount();
    QVERIFY(model->rowCount() == 1);
    QVERIFY(model->item(0)->text() == "Topolinia");
}

QTEST_MAIN(AppTest);

#include "tst_app.moc"
