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
extern  QString Last_S_BSPFactoryFile;
extern  QString Last_P_BSPFactoryFile;
extern  QString Last_U_BSPFactoryFile;
extern  QString NumberOfUserPartitions;
extern  QString UserPartition1Size;
extern  QString UserPartition2Size;
extern  QString uSD_Device;
extern  QString CurrentBSPF_Tab;
extern  QString CurrentVideo;
extern  QString AutoRunSelected;
extern  QString AutoRunFolder;

extern  QWidget *PBSP_stab,*UBSP_stab,*SBSP_stab,*TOOL_stab;

extern QString BootValid , FSValid , KernelValid , uSDwriteValid;

QWidget *current_stab;

/*****************************************************************************************************************************************************************************************/
/*                                                                               BKF Tab                                                                                                 */
/*****************************************************************************************************************************************************************************************/

void NOVAembed::on_Video_comboBox_currentIndexChanged(const QString &arg1)
{
    CurrentVideo = arg1;
    storeNOVAembed_ini();
}


void NOVAembed::on_Board_comboBox_currentIndexChanged(const QString &arg1)
{
    _Board_comboBox = arg1;
    ui->FileSystemSelectedlineEdit->setText("");
    ui->uboot_Valid_label->setPixmap(QPixmap(":/Icons/invalid.png"));
    ui->fs_Valid_label->setPixmap(QPixmap(":/Icons/invalid.png"));
    ui->kernel_Valid_label->setPixmap(QPixmap(":/Icons/invalid.png"));
    BootValid = "INVALID";
    FSValid = "INVALID";
    KernelValid = "INVALID";
    ui->frame_5->setEnabled(false);
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

    /* now show tools again */
    ui->tab->insertTab(3,TOOL_stab,"Tools");

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
    {
        update_status_bar("Boot loader for "+ui->Board_comboBox->currentText()+" compiled");
        BootValid = "OK";
        ui->uboot_Valid_label->setPixmap(QPixmap(":/Icons/valid.png"));
    }
    else
    {
        update_status_bar("Error building boot loader for "+ui->Board_comboBox->currentText());
        BootValid = "INVALID";
        ui->uboot_Valid_label->setPixmap(QPixmap(":/Icons/invalid.png"));

    }
    if ((BootValid != "OK") || (FSValid != "OK") || (KernelValid != "OK"))
        ui->frame_5->setEnabled(false);
    else
        ui->frame_5->setEnabled(true);
    storeNOVAembed_ini();
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
    {
        update_status_bar("Kernel configuration done");
        KernelValid = "OK";
    }
    else
    {
        update_status_bar("Configuration error");
        KernelValid = "INVALID";
        ui->kernel_Valid_label->setPixmap(QPixmap(":/Icons/invalid.png"));
    }
    if ((BootValid != "OK") || (FSValid != "OK") || (KernelValid != "OK"))
        ui->Write_uSD_pushButton->setEnabled(false);
    else
        ui->Write_uSD_pushButton->setEnabled(true);
    storeNOVAembed_ini();
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
    {
        update_status_bar("Kernel built succesfully");
        KernelValid = "OK";
        ui->kernel_Valid_label->setPixmap(QPixmap(":/Icons/valid.png"));
    }
    else
    {
        update_status_bar("Kernel Build error");
        KernelValid = "INVALID";
        ui->kernel_Valid_label->setPixmap(QPixmap(":/Icons/invalid.png"));
    }
    if ((BootValid != "OK") || (FSValid != "OK") || (KernelValid != "OK"))
        ui->frame_5->setEnabled(false);
    else
        ui->frame_5->setEnabled(true);
    storeNOVAembed_ini();
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
    {
        update_status_bar("Kernel re-built succesfully");
        KernelValid = "OK";
        ui->kernel_Valid_label->setPixmap(QPixmap(":/Icons/valid.png"));
    }
    else
    {
        update_status_bar("Kernel re-build error");
        KernelValid = "INVALID";
        ui->kernel_Valid_label->setPixmap(QPixmap(":/Icons/invalid.png"));
    }
    if ((BootValid != "OK") || (FSValid != "OK") || (KernelValid != "OK"))
        ui->frame_5->setEnabled(false);
    else
        ui->frame_5->setEnabled(true);
    storeNOVAembed_ini();
}

void NOVAembed::on_KernelMakeDTB_pushButton_clicked()
{
    QFile scriptfile("/tmp/script");
    update_status_bar("Making DTBs ...");

    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("cd /Devel/NOVAsom_SDK/Utils\n");
    out << QString("./kmake_dtbs linux-imx_4.1.15_1.2.0_ga > /Devel/NOVAsom_SDK/Logs/kmakedtbs.log\n");
    out << QString("echo $? > /tmp/result\n");

    scriptfile.close();
    if ( run_script() == 0)
        update_status_bar("DTBs re-built succesfully");
    else
        update_status_bar("DTBs Build error");
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
    if ( ui->FileSystemSelectedlineEdit->text() == "")
    {
       update_status_bar("File system name is empty");
       return;
    }
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
    {
        update_status_bar("Buildroot Configuration Finished");
        FSValid = "OK";
        ui->fs_Valid_label->setPixmap(QPixmap(":/Icons/valid.png"));

    }
    else
    {
        update_status_bar("Configuration error");
        FSValid = "INVALID";
        ui->fs_Valid_label->setPixmap(QPixmap(":/Icons/invalid.png"));
    }
    storeNOVAembed_ini();
}



void NOVAembed::on_LaunchBusyboxMenuConfig_pushButton_clicked()
{
    if ( ui->FileSystemSelectedlineEdit->text() == "")
    {
       update_status_bar("File system name is empty");
       return;
    }
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
            //qDebug() << IP;
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
        //qDebug()<<"Valid IP Address";
        ui->iperror_label->setVisible(false);
        QString command1 = "echo \"REFERENCE_SERVER="+IP+"\" > /Devel/NOVAsom_SDK/FileSystem/"+ui->FileSystemSelectedlineEdit->text()+"/board/novasis/NOVAsomP/Init/etc/sysconfig/system_vars";
        QByteArray ba1 = command1.toLatin1();
        const char *c_str1 = ba1.data();
        //qDebug() << 1_str2;
        system(c_str1);
    }
    else
    {
        //qDebug()<<"Invalid IP address";
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
    out << QString("cd /Devel/NOVAsom_SDK/FileSystem/"+ui->FileSystemSelectedlineEdit->text()+"\n");
    if ( ui->Board_comboBox->currentText() == "S Series")
        out << QString("make  > /Devel/NOVAsom_SDK/Logs/FileSystem_Smake.log\n");
    if ( ui->Board_comboBox->currentText() == "P Series")
        out << QString("make > /Devel/NOVAsom_SDK/Logs/FileSystem_Pmake.log\n");
    if ( ui->Board_comboBox->currentText() == "U Series")
        out << QString("make > /Devel/NOVAsom_SDK/Logs/FileSystem_Umake.log\n");
    out << QString("echo $? > /tmp/result\n");

    scriptfile.close();
    if ( run_script() == 0)
    {
        update_status_bar("File system "+ui->FileSystemSelectedlineEdit->text()+" deployed");
        DeployedFileSystemName = FileSystemName = ui->FileSystemSelectedlineEdit->text();
        FSValid = "OK";
        ui->fs_Valid_label->setPixmap(QPixmap(":/Icons/valid.png"));
    }
    else
    {
        update_status_bar("Build error");
        FSValid = "INVALID";
        ui->fs_Valid_label->setPixmap(QPixmap(":/Icons/invalid.png"));
    }
    if ((BootValid != "OK") || (FSValid != "OK") || (KernelValid != "OK"))
        ui->frame_5->setEnabled(false);
    else
        ui->frame_5->setEnabled(true);
    storeNOVAembed_ini();
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

    }
    if ( NumberOfUserPartitions == "1")
    {
                ui->label_78->setVisible(true);
                ui->UserPartition1Size_lineEdit->setVisible(true);
                ui->label_79->setVisible(false);
                ui->UserPartition2Size_lineEdit->setVisible(false);
    }
    if ( NumberOfUserPartitions == "2")
    {
                ui->label_78->setVisible(true);
                ui->UserPartition1Size_lineEdit->setVisible(true);
                ui->label_79->setVisible(true);
                ui->UserPartition2Size_lineEdit->setVisible(true);
    }
    storeNOVAembed_ini();
}


void NOVAembed::on_UserPartition1Size_lineEdit_textChanged(const QString &arg1)
{
    UserPartition1Size = arg1;
    storeNOVAembed_ini();
}


void NOVAembed::on_UserPartition2Size_lineEdit_textChanged(const QString &arg1)
{
    UserPartition2Size = arg1;
    storeNOVAembed_ini();
}

void NOVAembed::on_uSD_Device_comboBox_currentIndexChanged(const QString &arg1)
{
    uSD_Device = arg1;
    storeNOVAembed_ini();
}

void NOVAembed::on_Write_uSD_pushButton_clicked()
{
    /*uSD_Device_comboBox*/
    QString BoardModel;
    QString NOVAsomParamsName;
    QString sdl_dtb,q_dtb;
    QString UserEnabled = "system";

    uSD_Device = ui->uSD_Device_comboBox->currentText();
    QFile scriptfile("/tmp/script");
    update_status_bar("Writing uSD with "+FileSystemName+" ...");

    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }

    if ( ui->Board_comboBox->currentText() == "S Series")
    {
        BoardModel = "NOVAsomS";
    }
    if ( ui->Board_comboBox->currentText() == "P Series")
    {
        BoardModel = "NOVAsomP";
    }
    if ( ui->Board_comboBox->currentText() == "U Series")
    {
        BoardModel = "NOVAsomU";
    }

    if ( ui->Video_comboBox->currentText() == "HDMI 1920x1080 ( FHD )")
    {
        NOVAsomParamsName = "NOVAsomParams_HDMI_1920x1080";
    }
    if ( ui->Video_comboBox->currentText() == "HDMI 1280x720 ( HD )")
    {
        NOVAsomParamsName = "NOVAsomParams_HDMI_1280x720";
    }
    if ( ui->Video_comboBox->currentText() == "LVDS 1920x1080 ( Dual Channel FHD )")
    {
        NOVAsomParamsName = "NOVAsomParams_LVDS_1920x10802CH";
    }
    if ( ui->Video_comboBox->currentText() == "LVDS 1366x768")
    {
        NOVAsomParamsName = "NOVAsomParams_LVDS_1366x768";
    }
    if ( ui->Video_comboBox->currentText() == "LVDS 1024x768")
    {
        NOVAsomParamsName = "NOVAsomParams_LVDS_1024x768";
    }
    if ( ui->Video_comboBox->currentText() == "LVDS 1024x600")
    {
        NOVAsomParamsName = "NOVAsomParams_LVDS_1024x600";
    }
    if ( ui->Video_comboBox->currentText() == "LVDS 800x600")
    {
        NOVAsomParamsName = "NOVAsomParams_LVDS_800x600";
    }
    if ( ui->Video_comboBox->currentText() == "LVDS 800x480")
    {
        NOVAsomParamsName = "NOVAsomParams_LVDS_800x480";
    }

    UserEnabled = "user";
    QFileInfo fi(ui->UserBSPFselectedlineEdit->text());
    sdl_dtb = "SDL_"+fi.baseName()+".dtb";
    q_dtb = "QUAD_"+fi.baseName()+".dtb";

    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("cd /Devel/NOVAsom_SDK/Utils\n");
    out << QString("cp BootParameters/"+NOVAsomParamsName+" ../Deploy/NOVAsomParams\n");
    out << QString("./uSd_flash "+NumberOfUserPartitions+" "+UserPartition1Size+" "+UserPartition2Size+" /dev/"+uSD_Device+" "+BoardModel+" "+sdl_dtb+" "+q_dtb+" "+ UserEnabled +"> /Devel/NOVAsom_SDK/Logs/uSD_Write\n");
    if (( ui->UserAutoRun_checkBox->isChecked() == true) && (ui->UserAutoRunSelectedlineEdit->text().isEmpty() == false ))
        out << QString("./store_application_storage "+ui->UserAutoRunSelectedlineEdit->text()+" /dev/"+uSD_Device+" >> /Devel/NOVAsom_SDK/Logs/uSD_Write\n");

    out << QString("echo $? > /tmp/result\n");
    scriptfile.close();
    if ( run_script() == 0)
    {
        update_status_bar("uSD successfully written, file system is "+FileSystemName);
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
        update_status_bar("File System "+ui->NewFileSystemSelectedlineEdit->text()+" generated succesfully");
        DeployedFileSystemName = FileSystemName = ui->NewFileSystemSelectedlineEdit->text();
        ui->FileSystemSelectedlineEdit->setText(DeployedFileSystemName);
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
}

void NOVAembed::on_UserBSPFSelect_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Select BSPF"), "/Devel/NOVAsom_SDK/DtbUserWorkArea/PClass_bspf",tr("BSPF (*.bspf)"));
    if (fileName.isEmpty())
        return;
    else
    {
        ui->UserBSPFselectedlineEdit->setText(fileName);
        if ( ui->Board_comboBox->currentText() == "S Series")
            Last_S_BSPFactoryFile = ui->UserBSPFselectedlineEdit->text();
        if ( ui->Board_comboBox->currentText() == "P Series")
            Last_P_BSPFactoryFile = ui->UserBSPFselectedlineEdit->text();
        if ( ui->Board_comboBox->currentText() == "U Series")
            Last_U_BSPFactoryFile = ui->UserBSPFselectedlineEdit->text();
        storeNOVAembed_ini();
    }
}

void NOVAembed::on_UserAutoRun_checkBox_toggled(bool checked)
{
    if ( checked == true)
    {
        AutoRunSelected = "true";
        ui->UserAutoRunSelect_pushButton->setEnabled(true);
        ui->UserAutoRunSelectedlineEdit->setEnabled(true);
        ui->UserAutoRunSelectedlineEdit->setText(AutoRunFolder);
        ui->Write_AutoRun_pushButton->setEnabled(true);
    }
    else
    {
        AutoRunSelected = "false";
        ui->UserAutoRunSelect_pushButton->setEnabled(false);
        ui->UserAutoRunSelectedlineEdit->setEnabled(false);
        ui->Write_AutoRun_pushButton->setEnabled(false);
    }
    storeNOVAembed_ini();
}

void NOVAembed::on_UserAutoRunSelect_pushButton_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Select the AutoRun folder"),"/Devel/NOVAsom_SDK",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->UserAutoRunSelectedlineEdit->setText(directory);
    AutoRunFolder = directory;
    ui->Write_AutoRun_pushButton->setEnabled(true);
    storeNOVAembed_ini();
}

void NOVAembed::on_Write_AutoRun_pushButton_clicked()
{
    uSD_Device = ui->uSD_Device_comboBox->currentText();
    QFile scriptfile("/tmp/script");
    update_status_bar("Writing AutoRun using folder "+ui->UserAutoRunSelectedlineEdit->text()+" ...");

    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("cd /Devel/NOVAsom_SDK/Utils\n");
    out << QString("./store_application_storage "+ui->UserAutoRunSelectedlineEdit->text()+" /dev/"+uSD_Device+" >> /Devel/NOVAsom_SDK/Logs/uSD_Write\n");

    out << QString("echo $? > /tmp/result\n");
    scriptfile.close();

    if ( run_script() == 0)
    {
        update_status_bar("AutoRun successfully written with folder "+ui->UserAutoRunSelectedlineEdit->text());
    }
    else
        update_status_bar("AutoRun Write error");
}

/*****************************************************************************************************************************************************************************************/
/*                                                                             BKF Tab END                                                                                               */
/*****************************************************************************************************************************************************************************************/
