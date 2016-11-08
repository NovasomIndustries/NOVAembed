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
#include <QNetworkInterface>

extern  QString FileSystemName;
extern  QString DeployedFileSystemName;
extern  QString FileSystemConfigName;
extern  QString _Board_comboBox;
extern  QString LastBSPFactoryFile;
extern  QString NumberOfUserPartitions;
extern  QString UserPartition1Size;
extern  QString UserPartition2Size;
extern  QString uSD_Device;

extern  QString CurrentBSPF_Tab;
extern  QWidget *PBSP_stab,*UBSP_stab,*SBSP_stab,*TOOL_stab;
QWidget *current_stab;

/*****************************************************************************************************************************************************************************************/
/*                                                                               BKF Tab                                                                                                 */
/*****************************************************************************************************************************************************************************************/


void NOVAembed::on_Board_comboBox_currentIndexChanged(const QString &arg1)
{
    _Board_comboBox = arg1;
    if ( arg1 == "S Series")
    {
        CurrentBSPF_Tab = "S BSP Factory";
        current_stab = SBSP_stab;
    }
    if ( arg1 == "U Series")
    {
        CurrentBSPF_Tab = "U BSP Factory";
        current_stab = UBSP_stab;
    }
    if ( arg1 == "P Series")
    {
        CurrentBSPF_Tab = "P BSP Factory";
        current_stab = PBSP_stab;
    }
    /* hide Tools for recompose order */
    ui->tab->removeTab(3);

    ui->tab->removeTab(2);
    ui->tab->insertTab(2,current_stab,CurrentBSPF_Tab);
    qDebug() << CurrentBSPF_Tab;

    /* now show tools again */
    ui->tab->insertTab(3,TOOL_stab,"Tools");

    //ui->Board_comboBox->setCurrentText(arg1);

    compile_NewFileSystemFileSystemConfigurationcomboBox();

    storeNOVAembed_ini();
}

/* Bootloader */
void NOVAembed::on_BootLoaderCompile_pushButton_clicked()
{
    QFile scriptfile("/tmp/script");
    update_status_bar("Compiling boot loader ...");
    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("cd /Devel/NOVAsom_SDK/Utils\n");
    if ( ui->Board_comboBox->currentText() == "S Series")
        out << QString("./umakeS  > /Devel/NOVAsom_SDK/Logs/umakeS.log\n");
    if ( ui->Board_comboBox->currentText() == "P Series")
        out << QString("./umakeP > /Devel/NOVAsom_SDK/Logs/umakeP.log\n");
    if ( ui->Board_comboBox->currentText() == "U Series")
        out << QString("./umakeU > /Devel/NOVAsom_SDK/Logs/umakeU.log\n");
    out << QString("echo $? > /tmp/result\n");

    scriptfile.close();
    if ( run_script() == 0)
        update_status_bar("Finished");
    else
        update_status_bar("Build error");
}

/* Kernel */
void NOVAembed::on_KernelXconfig_pushButton_clicked()
{
    QFile scriptfile("/tmp/script");
    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("cd /Devel/NOVAsom_SDK/Kernel/linux-imx_4.1.15_1.2.0_ga\n");
    out << QString(". ../../Utils/SourceMe\n");
    out << QString("make xconfig\n");
    out << QString("echo $? > /tmp/result\n");

    scriptfile.close();
    if ( run_script() == 0)
        update_status_bar("Kernel configured succesfully");
    else
        update_status_bar("Configuration error");
}

void NOVAembed::on_KernelCompile_pushButton_clicked()
{
    QFile scriptfile("/tmp/script");
    update_status_bar("Compiling linux ...");

    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("cd /Devel/NOVAsom_SDK/Utils\n");
    out << QString("./kmake linux-imx_4.1.15_1.2.0_ga > /Devel/NOVAsom_SDK/Logs/kmake.log\n");
    out << QString("echo $? > /tmp/result\n");

    scriptfile.close();
    if ( run_script() == 0)
        update_status_bar("Kernel built succesfully");
    else
        update_status_bar("Build error");
}

void NOVAembed::on_KernelReCompile_pushButton_clicked()
{
    QFile scriptfile("/tmp/script");
    update_status_bar("ReCompiling linux ...");

    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("cd /Devel/NOVAsom_SDK/Utils\n");
    out << QString("./kremake linux-imx_4.1.15_1.2.0_ga > /Devel/NOVAsom_SDK/Logs/kremake.log\n");
    out << QString("echo $? > /tmp/result\n");

    scriptfile.close();
    if ( run_script() == 0)
        update_status_bar("Kernel re-built succesfully");
    else
        update_status_bar("Build error");
}

/* File System */
void NOVAembed::on_SelectFileSystem_pushButton_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Select the File System Top Directory"),"/Devel/NOVAsom_SDK/FileSystem",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QFileInfo fileInfo(directory );
    QString filesystemname(fileInfo.fileName());
    ui->FileSystemSelectedlineEdit->setText(filesystemname);
    FileSystemName = filesystemname;
    storeNOVAembed_ini();
}

void NOVAembed::on_LaunchMenuConfig_pushButton_clicked()
{
    update_status_bar("Configuring "+FileSystemName+" ...");
    QFile scriptfile("/tmp/script");
    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("cd /Devel/NOVAsom_SDK/FileSystem/"+FileSystemName+"\n");
    out << QString("make menuconfig\n");
    out << QString("echo $? > /tmp/result\n");

    scriptfile.close();
    if ( run_script() == 0)
        update_status_bar("Buildroot Configuration Finished");
    else
        update_status_bar("Configuration error");
}



void NOVAembed::on_LaunchBusyboxMenuConfig_pushButton_clicked()
{
    update_status_bar("Configuring "+FileSystemName+" ...");
    QFile scriptfile("/tmp/script");
    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("cd /Devel/NOVAsom_SDK/FileSystem/"+FileSystemName+"\n");
    out << QString("make busybox-menuconfig\n");
    out << QString("echo $? > /tmp/result\n");

    scriptfile.close();
    if ( run_script() == 0)
        update_status_bar("Busybox Configuration Finished");
    else
        update_status_bar("Configuration error");
}

void NOVAembed::on_ThisIsReferenceServer_checkBox_clicked(bool checked)
{
    QString IP;

    ui->iperror_label->setVisible(false);

    if ( checked == false )
    {
        ui->REFERENCE_SERVER_label->setEnabled(true);
        ui->REFERENCE_SERVER_lineEdit->setEnabled(true);
        IP=ui->REFERENCE_SERVER_lineEdit->text();
    }
    else
    {
        ui->REFERENCE_SERVER_label->setEnabled(false);
        ui->REFERENCE_SERVER_lineEdit->setEnabled(false);
        QNetworkInterface eth1Ip = QNetworkInterface::interfaceFromName("enp0s3");
        QList<QNetworkAddressEntry> entries = eth1Ip.addressEntries();
        if (!entries.isEmpty()) {
            QNetworkAddressEntry entry = entries.first();
            IP=entry.ip().toString();
            qDebug() << IP;
        }
        else
            qDebug() << "IP not found";
    }
    ui->REFERENCE_SERVER_lineEdit->setText(IP);

}

void NOVAembed::on_FileSystemDeploy_pushButton_clicked()
{
    QHostAddress myIP;
    QString IP=ui->REFERENCE_SERVER_lineEdit->text();

    if( myIP.setAddress(ui->REFERENCE_SERVER_lineEdit->text()) )
    {
        qDebug()<<"Valid IP Address";
        ui->iperror_label->setVisible(false);
        QString command = "echo \"REFERENCE_SERVER="+IP+"\" > /Devel/NOVAsom_SDK/FileSystem/"+ui->FileSystemSelectedlineEdit->text()+"/board/novasis/NOVAsomP/Init/etc/default_init/sysconfig/system_vars";
        QByteArray ba = command.toLatin1();
        const char *c_str2 = ba.data();
        qDebug() << c_str2;
        system(c_str2);
    }
    else
    {
        qDebug()<<"Invalid IP address";
        ui->iperror_label->setVisible(true);
        update_status_bar("Invalid IP address");

        return;
    }

    QFile scriptfile("/tmp/script");
    update_status_bar("Compiling "+FileSystemName+" ...");

    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("cd /Devel/NOVAsom_SDK/FileSystem/"+FileSystemName+"\n");
    out << QString("make  > /Devel/NOVAsom_SDK/Logs/FileSystem_umake.log\n");
    out << QString("echo $? > /tmp/result\n");

    scriptfile.close();
    if ( run_script() == 0)
    {
        update_status_bar("File system "+FileSystemName+" deployed");
        DeployedFileSystemName = FileSystemName;
        storeNOVAembed_ini();
    }
    else
        update_status_bar("Build error");
}


/* uSD write */

void NOVAembed::on_UserPartition_comboBox_currentIndexChanged(const QString &arg1)
{
    NumberOfUserPartitions = arg1;
    if ( NumberOfUserPartitions == "-")
    {
                ui->label_78->setVisible(false);
                ui->UserPartition1Size_lineEdit->setVisible(false);
                ui->label_79->setVisible(false);
                ui->UserPartition2Size_lineEdit->setVisible(false);
                qDebug() << "NumberOfUserPartitions :"+NumberOfUserPartitions;

    }
    if ( NumberOfUserPartitions == "1")
    {
                ui->label_78->setVisible(true);
                ui->UserPartition1Size_lineEdit->setVisible(true);
                ui->label_79->setVisible(false);
                ui->UserPartition2Size_lineEdit->setVisible(false);
                qDebug() << "NumberOfUserPartitions :"+NumberOfUserPartitions;
    }
    if ( NumberOfUserPartitions == "2")
    {
                ui->label_78->setVisible(true);
                ui->UserPartition1Size_lineEdit->setVisible(true);
                ui->label_79->setVisible(true);
                ui->UserPartition2Size_lineEdit->setVisible(true);
                qDebug() << "NumberOfUserPartitions :"+NumberOfUserPartitions;
    }
    storeNOVAembed_ini();
}


void NOVAembed::on_UserPartition1Size_lineEdit_textChanged(const QString &arg1)
{
    UserPartition1Size = arg1;
    qDebug() << "UserPartition1Size :"+UserPartition1Size;
    storeNOVAembed_ini();
}


void NOVAembed::on_UserPartition2Size_lineEdit_textChanged(const QString &arg1)
{
    UserPartition2Size = arg1;
    qDebug() << "UserPartition2Size :"+UserPartition2Size;
    storeNOVAembed_ini();
}

void NOVAembed::on_uSD_Device_comboBox_currentIndexChanged(const QString &arg1)
{
    uSD_Device = arg1;
    qDebug() << "uSD_Device :"+uSD_Device;
    storeNOVAembed_ini();
}

void NOVAembed::on_Write_uSD_pushButton_clicked()
{
    /*uSD_Device_comboBox*/


    uSD_Device = ui->uSD_Device_comboBox->currentText();
    QFile scriptfile("/tmp/script");
    update_status_bar("Writing uSD ...");

    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("cd /Devel/NOVAsom_SDK/Utils\n");
    if ( ui->Board_comboBox->currentText() == "S Series")
        out << QString("./flashS "+NumberOfUserPartitions+" "+UserPartition1Size+" "+UserPartition2Size+" /dev/"+uSD_Device+"> /Devel/NOVAsom_SDK/Logs/uSD_Write\n");
    if ( ui->Board_comboBox->currentText() == "P Series")
        out << QString("./flashP "+NumberOfUserPartitions+" "+UserPartition1Size+" "+UserPartition2Size+" /dev/"+uSD_Device+" > /Devel/NOVAsom_SDK/Logs/uSD_Write\n");
    if ( ui->Board_comboBox->currentText() == "U Series")
        out << QString("./flashU "+NumberOfUserPartitions+" "+UserPartition1Size+" "+UserPartition2Size+" /dev/"+uSD_Device+" > /Devel/NOVAsom_SDK/Logs/uSD_Write\n");
    out << QString("echo $? > /tmp/result\n");
    scriptfile.close();
    if ( run_script() == 0)
    {
        update_status_bar("uSD successfully written");
        DeployedFileSystemName = FileSystemName;
        storeNOVAembed_ini();
    }
    else
        update_status_bar("Write error");
}




void NOVAembed::on_GenerateFileSystem_pushButton_clicked()
{
    QFile scriptfile("/tmp/script");
    update_status_bar("Creating file system "+ui->NewFileSystemSelectedlineEdit->text()+" ...");

    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("cd /Devel/NOVAsom_SDK/Utils\n");
    out << QString("./SetupFs "+ui->NewFileSystemSelectedlineEdit->text()+" "+ ui->NewFileSystemConfigurationcomboBox->currentText()+"\n");
    out << QString("echo $? > /tmp/result\n");
    scriptfile.close();
    if ( run_script() == 0)
    {
        update_status_bar("File System "+FileSystemName+" generated succesfully");
        DeployedFileSystemName = FileSystemName;
        storeNOVAembed_ini();
    }
    else
        update_status_bar("File System Creation error");
}


/* External file systems */
void NOVAembed::on_ExtFS_Write_uSD_pushButton_clicked()
{
    QFile scriptfile("/tmp/script");
    update_status_bar("Creating file system "+ui->NewFileSystemSelectedlineEdit->text()+" ...");

    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("cd /Devel/NOVAsom_SDK/Utils\n");
    out << QString("./flashP_ExtFs /dev/"+ui->ExtFS_uSD_Device_comboBox->currentText()+" /Devel/NOVAsom_SDK/ExternalFileSystems/"+ ui->ExtFS_comboBox->currentText()+" > /Devel/NOVAsom_SDK/Logs/extfs_log \n");
    out << QString("echo $? > /tmp/result\n");
    scriptfile.close();
    if ( run_script() == 0)
    {
        update_status_bar("File System "+ui->ExtFS_comboBox->currentText()+" written");
    }
    else
        update_status_bar("File System Creation error");
}


void NOVAembed::on_ExtFS_comboBox_currentIndexChanged(const QString &arg1)
{
    QPixmap fspixmap (":/Icons/"+arg1+".png");
    ui->FileSystemLogo->setPixmap(fspixmap);
    //qDebug() << "Pixmap :/Icons/"+arg1+".png";
}

/*****************************************************************************************************************************************************************************************/
/*                                                                             BKF Tab END                                                                                               */
/*****************************************************************************************************************************************************************************************/
