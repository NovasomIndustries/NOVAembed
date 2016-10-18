#include "novaembed.h"
#include "ui_novaembed.h"
#include <QFileDialog>
#include <QTreeView>
#include <QDebug>
#include <QDir>
#include <QStatusBar>
#include <QMessageBox>
#include <QPixmap>
#include <QSettings>
#include <QUrl>
#include <QtCore>
#include <QDesktopServices>
//#include <QHostInfo>
#include <QDirIterator>
QString fileName1, fileName2;

void NOVAembed::on_CodeBlock_pushButton_clicked()
{
    system("codeblocks");
}

void NOVAembed::on_Meld_pushButton_clicked()
{
    QFile scriptfile("/tmp/script");
    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("echo 0 > /tmp/result\n");
    out << QString("meld "+ui->MeldFile1_lineEdit->text()+" "+ui->MeldFile2_lineEdit->text() +"\n");
    scriptfile.close();
    run_script();
}


void NOVAembed::on_MeldChooseFile1_pushButton_clicked()
{
    QString fileName1 = QFileDialog::getOpenFileName(this,tr("Load BSP Factory File"), "/Devel/NOVAsom_SDK/NOVAembed_Settings",tr("BSP Factory Files (*.bspf)"));
    if (fileName1.isEmpty())
        return;
    else
    {
        ui->MeldFile1_lineEdit->setText(fileName1);
    }
}

void NOVAembed::on_MeldChooseFile2_pushButton_clicked()
{
    QString fileName2 = QFileDialog::getOpenFileName(this,tr("Load BSP Factory File"), "/Devel/NOVAsom_SDK/NOVAembed_Settings",tr("BSP Factory Files (*.bspf)"));
    if (fileName2.isEmpty())
        return;
    else
    {
        ui->MeldFile2_lineEdit->setText(fileName2);
    }
}

void NOVAembed::on_QtCreator_pushButton_clicked()
{
    system("qtcreator");

}
