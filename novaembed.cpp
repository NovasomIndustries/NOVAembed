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

/*****************************************************************************************************************************************************************************************/
/*                                                                              Global variables                                                                                         */
/*****************************************************************************************************************************************************************************************/

QString Version = "1.0.4.1 rc5";
QString Configuration = "Standard";
QString FileSystemName = "";
QString DeployedFileSystemName = "";
QString FileSystemConfigName = "";
QString _Board_comboBox = "";
QString Last_U_BSPFactoryFile = "";
QString Last_P_BSPFactoryFile = "";
QString P_UserDTB_Selected = "";
QString Last_P_UserDTB = "";
QString Quad = "";
QString CfgBitDefaultValueDefault = "0x00017059";
QString CfgBitDefaultValue = "0x00017059";
QString NumberOfUserPartitions = "-";
QString UserPartition1Size = "1";
QString UserPartition2Size = "1";
QString uSD_Device = "sdb";
QString CurrentBSPF_Tab = "";
QString CurrentVideo = "";
QString AutoRunSelected = "";
QString AutoRunFolder = "";

extern  void storeNOVAembed_ini();
QWidget *PBSP_stab,*UBSP_stab,*SBSP_stab,*TOOL_stab;

/*****************************************************************************************************************************************************************************************/
/*                                                                                    Code                                                                                               */
/*****************************************************************************************************************************************************************************************/

NOVAembed::NOVAembed(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NOVAembed)
{
int     copy_required_files = 0;
QString linux_version="linux-imx_4.1.15_1.2.0_ga";

    /* Initialize user area */
    if ( ! QDir("/Devel/NOVAsom_SDK/DtbUserWorkArea").exists() )
    {
        //qDebug() << "mkdir /Devel/NOVAsom_SDK/DtbUserWorkArea";
        QDir().mkdir("/Devel/NOVAsom_SDK/DtbUserWorkArea");
        //qDebug() << "mkdir /Devel/NOVAsom_SDK/DtbUserWorkArea";
        QDir().mkdir("/Devel/NOVAsom_SDK/DtbUserWorkArea/PClass_bspf");
        copy_required_files = 1;
    }
    if ( ! QDir("/Devel/NOVAsom_SDK/DtbUserWorkArea/PClass_bspf").exists() )
    {
        //qDebug() << "mkdir /Devel/NOVAsom_SDK/DtbUserWorkArea/PClass_bspf";
        QDir().mkdir("/Devel/NOVAsom_SDK/DtbUserWorkArea/PClass_bspf");
        copy_required_files = 1;
    }
    if ( copy_required_files == 1 )
    {
        QFile::copy("/Devel/NOVAsom_SDK/Kernel/"+linux_version+"/arch/arm/boot/dts/imx6dl.dtsi", "/Devel/NOVAsom_SDK/DtbUserWorkArea/imx6dl.dtsi");
        QFile::copy("/Devel/NOVAsom_SDK/Kernel/"+linux_version+"/arch/arm/boot/dts/imx6dl-pinfunc.h", "/Devel/NOVAsom_SDK/DtbUserWorkArea/imx6dl-pinfunc.h");
        QFile::copy("/Devel/NOVAsom_SDK/Kernel/"+linux_version+"/arch/arm/boot/dts/imx6qdl.dtsi", "/Devel/NOVAsom_SDK/DtbUserWorkArea/imx6qdl.dtsi");
        QFile::copy("/Devel/NOVAsom_SDK/Kernel/"+linux_version+"/arch/arm/boot/dts/skeleton.dtsi", "/Devel/NOVAsom_SDK/DtbUserWorkArea/skeleton.dtsi");
        QFile::copy("/Devel/NOVAsom_SDK/Kernel/"+linux_version+"/arch/arm/boot/dts/imx6q.dtsi", "/Devel/NOVAsom_SDK/DtbUserWorkArea/imx6q.dtsi");
        QFile::copy("/Devel/NOVAsom_SDK/Kernel/"+linux_version+"/arch/arm/boot/dts/imx6q-pinfunc.h", "/Devel/NOVAsom_SDK/DtbUserWorkArea/imx6q-pinfunc.h");
    }
    QString fileName = "/Devel/NOVAsom_SDK/NOVAembed_Settings/NOVAembed.ini";
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        //qDebug() << "NOVAembed.ini not found";
        QMessageBox::information(this, tr("NOVAembed.ini"),"NOVAembed.ini not found. Creating a new one");
        if ( ! QDir("/Devel/NOVAsom_SDK/NOVAembed_Settings").exists() )
        {
            //qDebug() << "mkdir /Devel/NOVAsom_SDK/NOVAembed_Settings";
            QDir().mkdir("/Devel/NOVAsom_SDK/NOVAembed_Settings");
        }
        storeNOVAembed_ini();
    }
    else
    {
        QString strKeyConf("NOVAembed Configuration/");
        QSettings * config = 0;
        config = new QSettings( fileName, QSettings::IniFormat );
        Configuration = config->value( strKeyConf + "Configuration", "r").toString();

        QString strKeySettings("NOVAembed General Settings/");
        QSettings * settings = 0;
        settings = new QSettings( fileName, QSettings::IniFormat );
        FileSystemName = settings->value( strKeySettings + "FileSystemName", "r").toString();
        DeployedFileSystemName = settings->value( strKeySettings + "DeployedFileSystemName", "r").toString();
        FileSystemConfigName = settings->value( strKeySettings + "FileSystemConfigName", "r").toString();
        _Board_comboBox = settings->value( strKeySettings + "Board_comboBox", "r").toString();
        Last_P_BSPFactoryFile = settings->value( strKeySettings + "Last_P_BSPFactoryFile", "r").toString();
        P_UserDTB_Selected = settings->value( strKeySettings + "P_UserDTB_Selected", "r").toString();
        Last_P_UserDTB = settings->value( strKeySettings + "Last_P_UserDTB", "r").toString();
        CfgBitDefaultValue = settings->value( strKeySettings + "CfgBitDefaultValue", "r").toString();
        if ( CfgBitDefaultValue == "r" )
             CfgBitDefaultValue = CfgBitDefaultValueDefault;
        Last_U_BSPFactoryFile = settings->value( strKeySettings + "Last_U_BSPFactoryFile", "r").toString();
        NumberOfUserPartitions = settings->value( strKeySettings + "NumberOfUserPartitions", "r").toString();
        UserPartition1Size = settings->value( strKeySettings + "UserPartition1Size", "r").toString();
        UserPartition2Size = settings->value( strKeySettings + "UserPartition2Size", "r").toString();
        uSD_Device = settings->value( strKeySettings + "uSD_Device", "r").toString();
        CurrentBSPF_Tab = settings->value( strKeySettings + "CurrentBSPF_Tab", "r").toString();
        CurrentVideo = settings->value( strKeySettings + "CurrentVideo", "r").toString();
        AutoRunSelected = settings->value( strKeySettings + "AutoRunSelected", "r").toString();
        AutoRunFolder = settings->value( strKeySettings + "AutoRunFolder", "r").toString();
        Quad = settings->value( strKeySettings + "Quad", "r").toString();
    }
    //qDebug() << "Last_P_UserDTB "+Last_P_UserDTB;
    if ( ! QDir("/Devel/NOVAsom_SDK/NOVAembed_Settings/PClass_bspf").exists() )
    {
        //qDebug() << "mkdir /Devel/NOVAsom_SDK/NOVAembed_Settings/PClass_bspf";
        QDir().mkdir("/Devel/NOVAsom_SDK/NOVAembed_Settings/PClass_bspf");
    }
    if ( ! QDir("/Devel/NOVAsom_SDK/NOVAembed_Settings/SClass_bspf").exists() )
    {
       // qDebug() << "mkdir /Devel/NOVAsom_SDK/NOVAembed_Settings/SClass_bspf";
        QDir().mkdir("/Devel/NOVAsom_SDK/NOVAembed_Settings/SClass_bspf");
    }
    if ( ! QDir("/Devel/NOVAsom_SDK/NOVAembed_Settings/UClass_bspf").exists() )
    {
        //qDebug() << "mkdir /Devel/NOVAsom_SDK/NOVAembed_Settings/UClass_bspf";
        QDir().mkdir("/Devel/NOVAsom_SDK/NOVAembed_Settings/UClass_bspf");
    }

    ui->setupUi(this);

    ui->FileSystemSelectedlineEdit->setText(FileSystemName);
    ui->UserPartition_comboBox->setCurrentText(NumberOfUserPartitions);
    ui->VersionLabel->setText(Version);
    PBSP_stab=ui->tabBSPFP;
    UBSP_stab=ui->tabBSPFU;
    SBSP_stab=ui->tabBSPFS;
    TOOL_stab=ui->tabTools;
    ui->tab->removeTab(4);
    ui->tab->removeTab(3);
    ui->tab->removeTab(2);
    if ( Configuration == "Standard")
    {
        if (CurrentBSPF_Tab == "P BSP Factory")
        {
            ui->tab->insertTab(2,PBSP_stab,"P BSP Factory");
        }
        else if (CurrentBSPF_Tab == "S BSP Factory")
        {
            ui->tab->insertTab(2,SBSP_stab,"S BSP Factory");
        }
        else if (CurrentBSPF_Tab == "U BSP Factory")
        {
            ui->tab->insertTab(2,UBSP_stab,"U BSP Factory");
        }
        else
        {
            ui->tab->insertTab(2,PBSP_stab,"P BSP Factory");
        }
        ui->tab->insertTab(3,TOOL_stab,"Tools");
    }
    else
    {
        ui->tab->insertTab(2,TOOL_stab,"Tools");
    }

}

NOVAembed::~NOVAembed()
{
    delete ui;
}

void NOVAembed::on_actionExit_triggered()
{
    qApp->exit();
}



/*****************************************************************************************************************************************************************************************/
/*                                                                              Helper Functions                                                                                         */
/*****************************************************************************************************************************************************************************************/
/*
    qDebug() << "Hello world.";
    qWarning() << "Uh, oh...";
    qCritical() << "Oh, noes!";
    qFatal( "AAAAAAAAAH!" );
*/

void NOVAembed::storeNOVAembed_ini()
{
    QString fileName = "/Devel/NOVAsom_SDK/NOVAembed_Settings/NOVAembed.ini";
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, tr("NOVAembed.ini"),"Unable to create NOVAembed.ini");
        return;
    }
    QTextStream out(&file);
    out << QString("[NOVAembed Configuration]\n");
    out << QString("Configuration="+Configuration+"\n");
    out << QString("[NOVAembed General Settings]\n");
    out << QString("FileSystemName="+FileSystemName+"\n");
    out << QString("DeployedFileSystemName="+DeployedFileSystemName+"\n");
    out << QString("FileSystemConfigName="+FileSystemConfigName+"\n");
    out << QString("Board_comboBox="+_Board_comboBox+"\n");
    out << QString("Last_U_BSPFactoryFile="+Last_U_BSPFactoryFile+"\n");
    out << QString("Last_P_BSPFactoryFile="+Last_P_BSPFactoryFile+"\n");
    out << QString("CfgBitDefaultValue="+CfgBitDefaultValue+"\n");
    out << QString("P_UserDTB_Selected="+P_UserDTB_Selected+"\n");
    out << QString("Last_P_UserDTB="+Last_P_UserDTB+"\n");
    out << QString("NumberOfUserPartitions="+NumberOfUserPartitions+"\n");
    out << QString("UserPartition1Size="+UserPartition1Size+"\n");
    out << QString("UserPartition2Size="+UserPartition2Size+"\n");
    out << QString("uSD_Device="+uSD_Device+"\n");
    out << QString("AutoRunSelected="+AutoRunSelected+"\n");
    out << QString("AutoRunFolder="+AutoRunFolder+"\n");
    out << QString("CurrentBSPF_Tab="+CurrentBSPF_Tab+"\n");
    out << QString("CurrentVideo="+CurrentVideo+"\n");
    out << QString("Quad="+Quad+"\n");
    file.close();
}

void NOVAembed::compile_NewFileSystemFileSystemConfigurationcomboBox()
{
    QString str;
    QDir BuildrootDir("/Devel/NOVAsom_SDK/Utils/Configurations");
    if (ui->Board_comboBox->currentText() == "P Series")
    {
        str = "PClass_Buildroot_*.config";
        ui->Video_comboBox->setVisible(true);
        ui->VideoVisible_label->setVisible(true);
    }
    else if (ui->Board_comboBox->currentText() == "S Series")
    {
        str = "SClass_Buildroot_*.config";
        ui->Video_comboBox->setVisible(true);
        ui->VideoVisible_label->setVisible(true);
    }
    else if (ui->Board_comboBox->currentText() == "U Series")
    {
        str = "UClass_Buildroot_*.config";
        ui->Video_comboBox->setVisible(false);
        ui->VideoVisible_label->setVisible(false);
    }
    else
        str = "Buildroot_*.config";

    QStringList BuildrootnameFilter(str);
    QStringList BuildrootfilesList = BuildrootDir.entryList(BuildrootnameFilter);

    for(int i=0;i<BuildrootfilesList.count();i++)
        ui->NewFileSystemConfigurationcomboBox->removeItem(i);
    for(int i=0;i<BuildrootfilesList.count();i++)
    {
        str = BuildrootfilesList[i];
        /*qDebug() << str;*/
        ui->NewFileSystemConfigurationcomboBox->addItem(str);
    }
    ui->NewFileSystemConfigurationcomboBox->setCurrentIndex(1);
}

void NOVAembed::compile_ExtFS_comboBox()
{
    QString str;
    QDir ExternalFileSystemsDir("/Devel/NOVAsom_SDK/ExternalFileSystems");
    str = "*";

    QStringList ExternalFileSystemsnameFilter(str);
    QStringList ExternalFileSystemsfilesList = ExternalFileSystemsDir.entryList(ExternalFileSystemsnameFilter);

    for(int i=0;i<ExternalFileSystemsfilesList.count();i++)
        ui->ExtFS_comboBox->removeItem(i);
    //qDebug() << "Start of external file system list";
    for(int i=0;i<ExternalFileSystemsfilesList.count();i++)
    {
        str = ExternalFileSystemsfilesList[i];
        if (( str != ".") && (str != ".."))
        {
            //qDebug() << str;
            ui->ExtFS_comboBox->addItem(str);
        }
    }
    ui->ExtFS_comboBox->setCurrentIndex(0);
    QPixmap fspixmap (":/Icons/"+ui->ExtFS_comboBox->currentText()+".png");
    ui->FileSystemLogo->setPixmap(fspixmap);
    //qDebug() << "Pixmap :/Icons/"+ui->ExtFS_comboBox->currentText()+".png";
    //qDebug() << "End of external file system list";

}

void NOVAembed:: local_sleep(int ms)
{
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}

int NOVAembed::run_script(void)
{
    this->setCursor(Qt::WaitCursor);

    system("rm -f /tmp/result");
    system("chmod 777 /tmp/script");
    system("gnome-terminal -e /tmp/script > /Devel/NOVAsom_SDK/Logs/main_log");

    QFile file("/tmp/result");
    while( file.open(QIODevice::ReadOnly) == false )
        local_sleep(100);
    QTextStream stream(&file);
    QString content = stream.readAll();
    file.close();
    content.chop(1);
    this->setCursor(Qt::ArrowCursor);
    //qDebug() << content;

    return content.toInt();
}

int NOVAembed::update_status_bar(QString StatusBarContent)
{
    ui->statusBar->showMessage(StatusBarContent);
    return 0;
}

/*****************************************************************************************************************************************************************************************/
/*                                                                          Helper Functions End                                                                                         */
/*****************************************************************************************************************************************************************************************/

/*****************************************************************************************************************************************************************************************/
/*                                                                           Top tab switches                                                                                            */
/*****************************************************************************************************************************************************************************************/
void NOVAembed::on_tab_currentChanged(int index)
{
    switch ( index)
    {
    case 0 : // Welcome Tab
        update_status_bar("Welcome");
        break;
    case 1 : // BKF Tab
        /* File system config files */
        ui->Board_comboBox->setCurrentText(_Board_comboBox);
        ui->Video_comboBox->setCurrentText(CurrentVideo);
        ui->UserPartition_comboBox->setCurrentText(NumberOfUserPartitions);
        compile_NewFileSystemFileSystemConfigurationcomboBox();
        compile_ExtFS_comboBox();

        on_ThisIsReferenceServer_checkBox_clicked(true);
        ui->iperror_label->setVisible(false);
        ui->REFERENCE_SERVER_label->setEnabled(false);
        ui->REFERENCE_SERVER_lineEdit->setEnabled(false);
        ui->ThisIsReferenceServer_checkBox->setChecked(true);

        if (P_UserDTB_Selected == "true")
        {
            ui->UserDTB_checkBox->setChecked(true);
            ui->UserDTBSelect_pushButton->setEnabled(true);
            ui->UserDTBSelectedlineEdit->setEnabled(true);
            ui->UserDTBSelectedlineEdit->setText(Last_P_UserDTB);
            ui->UserDTBSelectedlineEdit->setText(Last_P_UserDTB);
        }
        else
        {
            ui->UserDTB_checkBox->setChecked(false);
            ui->UserDTBSelect_pushButton->setEnabled(false);
            ui->UserDTBSelectedlineEdit->setEnabled(false);
            ui->UserDTBSelectedlineEdit->setText(Last_P_UserDTB);
        }

        if ( AutoRunSelected == "true" )
        {
            ui->UserAutoRun_checkBox->setChecked(true);
            ui->UserAutoRunSelect_pushButton->setEnabled(true);
            ui->UserAutoRunSelectedlineEdit->setEnabled(true);
            ui->UserAutoRunSelectedlineEdit->setText(AutoRunFolder);
        }
        else
        {
            ui->UserAutoRun_checkBox->setChecked(false);
            ui->UserAutoRunSelect_pushButton->setEnabled(false);
            ui->UserAutoRunSelectedlineEdit->setEnabled(false);
            ui->UserAutoRunSelectedlineEdit->setText(AutoRunFolder);
        }


        update_status_bar("BKF");
        ui->UserPartition1Size_lineEdit->setText(UserPartition1Size);
        ui->UserPartition2Size_lineEdit->setText(UserPartition2Size);

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
        ui->uSD_Device_comboBox->setCurrentText(uSD_Device);
        break;
    case 2 : // BSP Factory
        if (CurrentBSPF_Tab == "P BSP Factory")
        {
            ui->P_SATA_checkBox->setChecked(false);
            ui->P_PCIe_checkBox->setChecked(true);
            ui->P_PUPD_frame->setEnabled(false);
            ui->P_Speed_frame->setEnabled(false);
            ui->P_SRE_frame->setEnabled(false);
            ui->P_DSE_frame->setEnabled(false);
            ui->P_PUE_checkBox->setEnabled(false);
            ui->P_SION_checkBox->setEnabled(false);
            ui->P_ODE_checkBox->setEnabled(false);
            ui->P_PKE_checkBox->setEnabled(false);
            ui->P_DSE_Disable_checkBox->setEnabled(false);
            ui->P_HYS_PAD_CTL_checkBox->setEnabled(false);
            ui->P_NO_PAD_CTL_checkBox->setChecked(true);
            ui->P_I2C1Speed_lineEdit->setText("100000");
            ui->P_I2C3Speed_lineEdit->setText("100000");

            if ( Quad == "true")
            {
                    ui->P_QUAD_checkBox->setChecked(true);
            }
            else
            {
                    ui->P_QUAD_checkBox->setChecked(false);
                    ui->P_SATA_checkBox->setEnabled(false);
                    ui->P_SATA_checkBox->setChecked(false);
            }
            ui->P_Default_lineEdit->setText(CfgBitDefaultValue);
            ui->P_Decoded_CFG_Bits_lineEdit->setText("0x00000000");
            P_load_BSPF_File(Last_P_BSPFactoryFile);
            QFileInfo fi(Last_P_BSPFactoryFile);
            if ( ! fi.exists())
            {
                on_P_Default_pushButton_clicked();
                update_status_bar("BSP Factory : File "+fi.baseName()+".bspf not found, reverting to default");
            }
            else
            {
                QString base = fi.baseName();
                if ( base != "" )
                    ui->P_Current_BSPF_File_label->setText(base+".bspf");
                update_status_bar("BSP Factory : Loaded file "+Last_P_BSPFactoryFile);
            }
        }
        else if (CurrentBSPF_Tab == "S BSP Factory")
        {
            qDebug() << "S BSP Factory";
        }
        else if (CurrentBSPF_Tab == "U BSP Factory")
        {
            ui->U_PUPD_frame->setEnabled(false);
            ui->U_Speed_frame->setEnabled(false);
            ui->U_SRE_frame->setEnabled(false);
            ui->U_DSE_frame->setEnabled(false);
            ui->U_PUE_checkBox->setEnabled(false);
            ui->U_SION_checkBox->setEnabled(false);
            ui->U_ODE_checkBox->setEnabled(false);
            ui->U_PKE_checkBox->setEnabled(false);
            ui->U_DSE_Disable_checkBox->setEnabled(false);
            ui->U_HYS_PAD_CTL_checkBox->setEnabled(false);
            ui->U_NO_PAD_CTL_checkBox->setChecked(true);
            U_load_BSPF_File(Last_U_BSPFactoryFile);
            QFileInfo fi(Last_U_BSPFactoryFile);
            if ( ! fi.exists())
            {
                on_U_Default_pushButton_clicked();
                update_status_bar("BSP Factory : File "+fi.baseName()+".bspf not found, reverting to default");
            }
            else
            {
                QString base = fi.baseName();
                if ( base != "" )
                    ui->U_Current_BSPF_File_label->setText(base+".bspf");
                update_status_bar("BSP Factory : Loaded file "+Last_U_BSPFactoryFile);
            }
        }
        else
        {
            P_load_BSPF_File(Last_P_BSPFactoryFile);
            QFileInfo fi(Last_P_BSPFactoryFile);
            if ( ! fi.exists())
            {
                on_P_Default_pushButton_clicked();
                update_status_bar("BSP Factory : File "+fi.baseName()+".bspf not found, reverting to default");
            }
            else
            {
                QString base = fi.baseName();
                if ( base != "" )
                    ui->P_Current_BSPF_File_label->setText(base+".bspf");
                update_status_bar("BSP Factory : Loaded file "+Last_P_BSPFactoryFile);
            }
        }
        break;
    }
}

/*****************************************************************************************************************************************************************************************/
/*                                                                          Top tab switches END                                                                                         */
/*****************************************************************************************************************************************************************************************/


void NOVAembed::on_CheckUpdate_pushButton_clicked()
{
    update_status_bar("Checking updates");

    QFile scriptfile("/tmp/script");
    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("cd /Devel/NOVAsom_SDK/Utils\n");
    out << QString("./CheckGitHubRepo\n");
    out << QString("echo $? > /tmp/result\n");

    scriptfile.close();
    int result = run_script();
    if (  result >= 0)
    {
        //qDebug() << result;
        if ( result > 0 )
        {
            QString s = QString::number(result);
            if ( result > 1 )
                update_status_bar("Found "+s+" updates, system updated");
            else
                update_status_bar("Found "+s+" update, system updated");
        }
        else
            update_status_bar("No updates found");
    }
    else
        update_status_bar("Update error");
}

