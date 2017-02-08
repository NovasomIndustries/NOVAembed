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
    out << QString("meld\n");
    scriptfile.close();
    run_script();
}

void NOVAembed::on_QtCreator_pushButton_clicked()
{
    system("qtcreator");

}
