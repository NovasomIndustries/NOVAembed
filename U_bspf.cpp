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


extern  QString FileSystemName;
extern  QString DeployedFileSystemName;
extern  QString FileSystemConfigName;
extern  QString _Board_comboBox;
extern  QString Last_U_BSPFactoryFile;


/*****************************************************************************************************************************************************************************************/
/*                                                                             U BSP Factory                                                                                             */
/*****************************************************************************************************************************************************************************************/

void NOVAembed::on_U_Load_pushButton_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this,tr("Load BSP Factory File"), "/Devel/NOVAsom_SDK/NOVAembed_Settings",tr("BSP Factory Files (*.bspf)"));
    if (fileName.isEmpty())
        return;
    else
    {
        U_load_BSPF_File(fileName);
    }
}

QString U_getvalue(QString strKey, QSettings *settings , QString entry)
{
    return settings->value( strKey + entry, "r").toString();
}

void NOVAembed::U_load_BSPF_File(QString fileName)
{
QString strKeyFunc("U_IOMUX/");
QSettings * func_settings = 0;

    on_U_Default_pushButton_clicked();
    QFileInfo fi(fileName);
    QString base = fi.baseName();
    if ( base != "" )
        ui->U_Current_BSPF_File_label->setText(base+".bspf");

    func_settings = new QSettings( fileName, QSettings::IniFormat );

    ui->U_ECSPI2_SS0_comboBox->setCurrentText(U_getvalue(strKeyFunc, func_settings , "U_ECSPI2_SS0_comboBox"));
    ui->U_ECSPI2_MISO_comboBox->setCurrentText(U_getvalue(strKeyFunc, func_settings , "U_ECSPI2_MISO_comboBox"));
    ui->U_ECSPI2_MOSI_comboBox->setCurrentText(U_getvalue(strKeyFunc, func_settings , "U_ECSPI2_MOSI_comboBox"));
    ui->U_ECSPI2_SCK_comboBox->setCurrentText(U_getvalue(strKeyFunc, func_settings , "U_ECSPI2_SCK_comboBox"));
    ui->U_ECSPI3_MISO_comboBox->setCurrentText(U_getvalue(strKeyFunc, func_settings , "U_ECSPI3_MISO_comboBox"));
    ui->U_ECSPI3_SCK_comboBox->setCurrentText(U_getvalue(strKeyFunc, func_settings , "U_ECSPI3_SCK_comboBox"));
    ui->U_ECSPI3_MOSI_comboBox->setCurrentText(U_getvalue(strKeyFunc, func_settings , "U_ECSPI3_MOSI_comboBox"));
    ui->U_ECSPI3_SS0_comboBox->setCurrentText(U_getvalue(strKeyFunc, func_settings , "U_ECSPI3_SS0_comboBox"));
    ui->U_I2C3_SCL_comboBox->setCurrentText(U_getvalue(strKeyFunc, func_settings , "U_I2C3_SCL_comboBox"));
    ui->U_I2C3_SDA_comboBox->setCurrentText(U_getvalue(strKeyFunc, func_settings , "U_I2C3_SDA_comboBox"));
    ui->U_KHZ32_CLK_OUT_comboBox->setCurrentText(U_getvalue(strKeyFunc, func_settings , "U_SD3_CMD_comboBox"));
    ui->U_GPIO3_IO20_comboBox->setCurrentText(U_getvalue(strKeyFunc, func_settings , "U_GPIO3_IO20_comboBox"));
    ui->U_GPIO1_IO00_comboBox->setCurrentText(U_getvalue(strKeyFunc, func_settings , "U_GPIO1_IO00_comboBox"));
    ui->U_GPIO4_IO29_comboBox->setCurrentText(U_getvalue(strKeyFunc, func_settings , "U_GPIO4_IO29_comboBox"));
    ui->U_I2C1_SDA_comboBox->setCurrentText(U_getvalue(strKeyFunc, func_settings , "U_I2C1_SDA_comboBox"));
    ui->U_I2C1_SCL_comboBox->setCurrentText(U_getvalue(strKeyFunc, func_settings , "U_I2C1_SCL_comboBox"));
    ui->U_SPDIF_OUT_comboBox->setCurrentText(U_getvalue(strKeyFunc, func_settings , "U_SPDIF_OUT_comboBox"));
    ui->U_defaultVideo_comboBox->setCurrentText(U_getvalue(strKeyFunc, func_settings , "U_defaultVideo_comboBox"));


    QString strKeyConf("U_CONF/");
    QSettings * conf_settings = 0;
    conf_settings = new QSettings( fileName, QSettings::IniFormat );

    ui->U_ECSPI2_SS0_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_ECSPI2_SS0_cbit"));
    ui->U_ECSPI2_MISO_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_ECSPI2_MISO_cbit"));
    ui->U_ECSPI2_MOSI_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_ECSPI2_MOSI_cbit"));
    ui->U_ECSPI2_SCK_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_ECSPI2_SCK_cbit"));
    ui->U_ECSPI3_MISO_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_ECSPI3_MISO_cbit"));
    ui->U_ECSPI3_SCK_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_ECSPI3_SCK_cbit"));
    ui->U_ECSPI3_MOSI_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_ECSPI3_MOSI_cbit"));
    ui->U_ECSPI3_SS0_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_ECSPI3_SS0_cbit"));
    ui->U_I2C3_SCL_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_I2C3_SCL_cbit"));
    ui->U_I2C3_SDA_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_I2C3_SDA_cbit"));
    ui->U_KHZ32_CLK_OUT_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_KHZ32_CLK_OUT_cbit"));
    ui->U_GPIO3_IO19_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_GPIO3_IO19_cbit"));
    ui->U_GPIO3_IO20_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_GPIO3_IO20_cbit"));
    ui->U_GPIO1_IO00_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_GPIO1_IO00_cbit"));
    ui->U_GPIO4_IO14_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_GPIO4_IO14_cbit"));
    ui->U_GPIO4_IO26_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_GPIO4_IO26_cbit"));
    ui->U_GPIO4_IO27_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_GPIO4_IO27_cbit"));
    ui->U_GPIO4_IO28_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_GPIO4_IO28_cbit"));
    ui->U_GPIO4_IO29_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_GPIO4_IO29_cbit"));
    ui->U_GPIO6_IO05_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_GPIO6_IO05_cbit"));
    ui->U_I2C1_SDA_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_I2C1_SDA_cbit"));
    ui->U_I2C1_SCL_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_I2C1_SCL_cbit"));
    ui->U_SPDIF_OUT_lineEdit->setText(U_getvalue(strKeyConf, conf_settings , "U_SPDIF_OUT_cbit"));
}

void NOVAembed::on_U_Save_pushButton_clicked()
{
    QString croped_fileName = QFileDialog::getSaveFileName(this,tr("Save .bspf"), "/Devel/NOVAsom_SDK/NOVAembed_Settings",tr(".bspf (*.bspf)"));
    QString fileName=croped_fileName.section(".",0,0);
    fileName = fileName+".bspf";
    qDebug() << "fileName :"+fileName;

    if (fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),file.errorString());
            return;
        }
        qDebug() << "fileName :"+fileName;

        QTextStream out(&file);
        out << QString("[U_IOMUX]\n");
        out << QString("U_ECSPI2_SS0_comboBox="+ui->U_ECSPI2_SS0_comboBox->currentText()+"\n");
        out << QString("U_ECSPI2_MISO_comboBox="+ui->U_ECSPI2_MISO_comboBox->currentText()+"\n");
        out << QString("U_ECSPI2_MOSI_comboBox="+ui->U_ECSPI2_MOSI_comboBox->currentText()+"\n");
        out << QString("U_ECSPI2_SCK_comboBox="+ui->U_ECSPI2_SCK_comboBox->currentText()+"\n");
        out << QString("U_ECSPI3_MISO_comboBox="+ui->U_ECSPI3_MISO_comboBox->currentText()+"\n");
        out << QString("U_ECSPI3_SCK_comboBox="+ui->U_ECSPI3_SCK_comboBox->currentText()+"\n");
        out << QString("U_ECSPI3_MOSI_comboBox="+ui->U_ECSPI3_MOSI_comboBox->currentText()+"\n");
        out << QString("U_ECSPI3_SS0_comboBox="+ui->U_ECSPI3_SS0_comboBox->currentText()+"\n");
        out << QString("U_I2C3_SCL_comboBox="+ui->U_I2C3_SCL_comboBox->currentText()+"\n");
        out << QString("U_I2C3_SDA_comboBox="+ui->U_I2C3_SDA_comboBox->currentText()+"\n");
        out << QString("U_KHZ32_CLK_OUT_comboBox="+ui->U_KHZ32_CLK_OUT_comboBox->currentText()+"\n");
        out << QString("U_GPIO3_IO20_comboBox="+ui->U_GPIO3_IO20_comboBox->currentText()+"\n");
        out << QString("U_GPIO1_IO00_comboBox="+ui->U_GPIO1_IO00_comboBox->currentText()+"\n");
        out << QString("U_GPIO4_IO29_comboBox="+ui->U_GPIO4_IO29_comboBox->currentText()+"\n");
        out << QString("U_I2C1_SDA_comboBox="+ui->U_I2C1_SDA_comboBox->currentText()+"\n");
        out << QString("U_I2C1_SCL_comboBox="+ui->U_I2C1_SCL_comboBox->currentText()+"\n");
        out << QString("U_SPDIF_OUT_comboBox="+ui->U_SPDIF_OUT_comboBox->currentText()+"\n");
        out << QString("defaultVideo_comboBox="+ui->U_defaultVideo_comboBox->currentText()+"\n");

        out << QString("\n[U_CONF]\n");
        out << QString("U_ECSPI2_SS0_cbit="+ui->U_ECSPI2_SS0_lineEdit->text()+"\n");
        out << QString("U_ECSPI2_MISO_cbit="+ui->U_ECSPI2_MISO_lineEdit->text()+"\n");
        out << QString("U_ECSPI2_MOSI_cbit="+ui->U_ECSPI2_MOSI_lineEdit->text()+"\n");
        out << QString("U_ECSPI2_SCK_cbit="+ui->U_ECSPI2_SCK_lineEdit->text()+"\n");
        out << QString("U_ECSPI3_MISO_cbit="+ui->U_ECSPI3_MISO_lineEdit->text()+"\n");
        out << QString("U_ECSPI3_SCK_cbit="+ui->U_ECSPI3_SCK_lineEdit->text()+"\n");
        out << QString("U_ECSPI3_MOSI_cbit="+ui->U_ECSPI3_MOSI_lineEdit->text()+"\n");
        out << QString("U_ECSPI3_SS0_cbit="+ui->U_ECSPI3_SS0_lineEdit->text()+"\n");
        out << QString("U_I2C3_SCL_cbit="+ui->U_I2C3_SCL_lineEdit->text()+"\n");
        out << QString("U_I2C3_SDA_cbit="+ui->U_I2C3_SDA_lineEdit->text()+"\n");
        out << QString("U_KHZ32_CLK_OUT_cbit="+ui->U_KHZ32_CLK_OUT_lineEdit->text()+"\n");
        out << QString("U_GPIO3_IO19_cbit="+ui->U_GPIO3_IO19_lineEdit->text()+"\n");
        out << QString("U_GPIO3_IO20_cbit="+ui->U_GPIO3_IO20_lineEdit->text()+"\n");
        out << QString("U_GPIO1_IO00_cbit="+ui->U_GPIO1_IO00_lineEdit->text()+"\n");
        out << QString("U_GPIO4_IO14_cbit="+ui->U_GPIO4_IO14_lineEdit->text()+"\n");
        out << QString("U_GPIO4_IO26_cbit="+ui->U_GPIO4_IO26_lineEdit->text()+"\n");
        out << QString("U_GPIO4_IO27_cbit="+ui->U_GPIO4_IO27_lineEdit->text()+"\n");
        out << QString("U_GPIO4_IO28_cbit="+ui->U_GPIO4_IO28_lineEdit->text()+"\n");
        out << QString("U_GPIO4_IO29_cbit="+ui->U_GPIO4_IO29_lineEdit->text()+"\n");
        out << QString("U_GPIO6_IO05_cbit="+ui->U_GPIO6_IO05_lineEdit->text()+"\n");
        out << QString("U_I2C1_SDA_cbit="+ui->U_I2C1_SDA_lineEdit->text()+"\n");
        out << QString("U_I2C1_SCL_cbit="+ui->U_I2C1_SCL_lineEdit->text()+"\n");
        out << QString("U_SPDIF_OUT_cbit="+ui->U_SPDIF_OUT_lineEdit->text()+"\n");

        file.close();
        Last_U_BSPFactoryFile = fileName;
        QFileInfo fi(Last_U_BSPFactoryFile);
        QString base = fi.baseName();
        if ( base != "" )
            ui->U_Current_BSPF_File_label->setText(base+".bspf");
        storeNOVAembed_ini();
    }
}

void NOVAembed::on_U_Default_pushButton_clicked()
{
    ui->U_ECSPI2_SS0_comboBox->setCurrentIndex(0);
    ui->U_ECSPI2_MISO_comboBox->setCurrentIndex(0);
    ui->U_ECSPI2_MOSI_comboBox->setCurrentIndex(0);
    ui->U_ECSPI2_SCK_comboBox->setCurrentIndex(0);
    ui->U_ECSPI3_MISO_comboBox->setCurrentIndex(0);
    ui->U_ECSPI3_SCK_comboBox->setCurrentIndex(0);
    ui->U_ECSPI3_MOSI_comboBox->setCurrentIndex(0);
    ui->U_ECSPI3_SS0_comboBox->setCurrentIndex(0);
    ui->U_I2C3_SCL_comboBox->setCurrentIndex(0);
    ui->U_I2C3_SDA_comboBox->setCurrentIndex(0);
    ui->U_KHZ32_CLK_OUT_comboBox->setCurrentIndex(0);
    ui->U_GPIO3_IO20_comboBox->setCurrentIndex(0);
    ui->U_GPIO1_IO00_comboBox->setCurrentIndex(0);
    ui->U_GPIO4_IO29_comboBox->setCurrentIndex(0);
    ui->U_I2C1_SDA_comboBox->setCurrentIndex(0);
    ui->U_I2C1_SCL_comboBox->setCurrentIndex(0);
    ui->U_SPDIF_OUT_comboBox->setCurrentIndex(0);
    ui->U_defaultVideo_comboBox->setCurrentIndex(0);

    ui->U_ECSPI2_SS0_lineEdit->setText("0x80000000");
    ui->U_ECSPI2_MISO_lineEdit->setText("0x80000000");
    ui->U_ECSPI2_MOSI_lineEdit->setText("0x80000000");
    ui->U_ECSPI2_SCK_lineEdit->setText("0x80000000");
    ui->U_ECSPI3_MISO_lineEdit->setText("0x80000000");
    ui->U_ECSPI3_SCK_lineEdit->setText("0x80000000");
    ui->U_ECSPI3_MOSI_lineEdit->setText("0x80000000");
    ui->U_ECSPI3_SS0_lineEdit->setText("0x80000000");
    ui->U_I2C3_SCL_lineEdit->setText("0x80000000");
    ui->U_I2C3_SDA_lineEdit->setText("0x80000000");
    ui->U_KHZ32_CLK_OUT_lineEdit->setText("0x80000000");
    ui->U_GPIO3_IO20_lineEdit->setText("0x80000000");
    ui->U_GPIO1_IO00_lineEdit->setText("0x80000000");
    ui->U_GPIO4_IO29_lineEdit->setText("0x80000000");
    ui->U_I2C1_SDA_lineEdit->setText("0x80000000");
    ui->U_I2C1_SCL_lineEdit->setText("0x80000000");
    ui->U_SPDIF_OUT_lineEdit->setText("0x80000000");
}

void NOVAembed::U_disable_all(void)
{
    ui->U_PUPD_frame->setEnabled(false);
    ui->U_Speed_frame->setEnabled(false);
    ui->U_SRE_frame->setEnabled(false);
    ui->U_DSE_frame->setEnabled(false);
    ui->U_PUE_checkBox->setEnabled(false);
    ui->U_SION_checkBox->setEnabled(false);
    ui->U_ODE_checkBox->setEnabled(false);
    ui->U_PKE_checkBox->setEnabled(false);
    ui->U_HYS_PAD_CTL_checkBox->setEnabled(false);
    ui->U_DSE_Disable_checkBox->setEnabled(false);
    ui->U_NO_PAD_CTL_checkBox->setEnabled(true);
    ui->U_NO_PAD_CTL_checkBox->setChecked(true);
}

void NOVAembed::U_enable_all(void)
{
    ui->U_PUPD_frame->setEnabled(true);
    ui->U_Speed_frame->setEnabled(true);
    ui->U_SRE_frame->setEnabled(true);
    ui->U_DSE_frame->setEnabled(true);
    ui->U_PUE_checkBox->setEnabled(true);
    ui->U_SION_checkBox->setEnabled(true);
    ui->U_ODE_checkBox->setEnabled(true);
    ui->U_PKE_checkBox->setEnabled(true);
    ui->U_HYS_PAD_CTL_checkBox->setEnabled(true);
    ui->U_DSE_Disable_checkBox->setEnabled(true);
    ui->U_NO_PAD_CTL_checkBox->setEnabled(true);
    ui->U_NO_PAD_CTL_checkBox->setChecked(false);
}
void NOVAembed::on_U_CreateCFGBits_pushButton_clicked()
{
    int  value = 0;
     /*
     CONFIG bits definition:
     NO_PAD_CTL                      (1 << 31)
     SION                            (1 << 30)
     PAD_CTL_HYS                     (1 << 16)
     PAD_CTL_PUS_100K_DOWN           (0 << 14)
     PAD_CTL_PUS_47K_UP              (1 << 14)
     PAD_CTL_PUS_100K_UP             (2 << 14)
     PAD_CTL_PUS_22K_UP              (3 << 14)
     PAD_CTL_PUE                     (1 << 13)
     PAD_CTL_PKE                     (1 << 12)
     PAD_CTL_ODE                     (1 << 11)
     PAD_CTL_SPEED_LOW               (1 << 6)
     PAD_CTL_SPEED_MED               (2 << 6)
     PAD_CTL_SPEED_HIGH              (3 << 6)
     PAD_CTL_DSE_DISABLE             (0 << 3)
     PAD_CTL_DSE_34ohm               (7 << 3)
     PAD_CTL_DSE_40ohm               (6 << 3)
     PAD_CTL_DSE_48ohm               (5 << 3)
     PAD_CTL_DSE_60ohm               (4 << 3)
     PAD_CTL_DSE_80ohm               (3 << 3)
     PAD_CTL_DSE_120ohm              (2 << 3)
     PAD_CTL_DSE_240ohm              (1 << 3)
     PAD_CTL_SRE_FAST                (1 << 0)
     PAD_CTL_SRE_SLOW                (0 << 0)

     */

    if ( ui->U_NO_PAD_CTL_checkBox->isChecked() == true )
        value = 1 << 31;
    else
    {
        if ( ui->U_SION_checkBox->isChecked() == true )
            value |= 1 << 30;
        if ( ui->U_HYS_PAD_CTL_checkBox->isChecked() == true )
            value |= 1 << 16;
        if ( ui->U_PUE_checkBox->isChecked() == true )
        {
            value |= 1 << 13;
            if ( ui->U_PD_100K_checkBox->isChecked() == true )
                value |= 0 << 14;
            if ( ui->U_PU_100K_checkBox->isChecked() == true )
                value |= 2 << 14;
            if ( ui->U_PU_47K_checkBox->isChecked() == true )
                value |= 1 << 14;
            if ( ui->U_PU_22K_checkBox->isChecked() == true )
                value |= 3 << 14;
        }
        if ( ui->U_PKE_checkBox->isChecked() == true )
            value |= 1 << 12;
        if ( ui->U_ODE_checkBox->isChecked() == true )
            value |= 1 << 11;
        if ( ui->U_SPEED_Low_checkBox->isChecked() == true )
            value |= 1 << 6;
        if ( ui->U_SPEED_Mid_checkBox->isChecked() == true )
            value |= 2 << 6;
        if ( ui->U_SPEED_High_checkBox->isChecked() == true )
            value |= 3 << 6;
        if ( ui->U_DSE_Disable_checkBox->isChecked() == true )
            value |= 0 << 3;
        else
        {
            if ( ui->U_DSE_34_checkBox->isChecked() == true )
                value |= 7 << 3;
            if ( ui->U_DSE_40_checkBox->isChecked() == true )
                value |= 6 << 3;
            if ( ui->U_DSE_48_checkBox->isChecked() == true )
                value |= 5 << 3;
            if ( ui->U_DSE_60_checkBox->isChecked() == true )
                value |= 4 << 3;
            if ( ui->U_DSE_80_checkBox->isChecked() == true )
                value |= 3 << 3;
            if ( ui->U_DSE_120_checkBox->isChecked() == true )
                value |= 2 << 3;
            if ( ui->U_DSE_240_checkBox->isChecked() == true )
                value |= 1 << 3;
        }
        if ( ui->U_SRE_Fast_checkBox->isChecked() == true )
            value |= 1 << 0;
        if ( ui->U_SRE_Slow_checkBox->isChecked() == true )
            value |= 0 << 0;

     }
     char result[16];
     sprintf(result,"0x%08x",value);
     ui->U_CFG_Bits_lineEdit->setText(result);
}


#define    NO_PAD_CTL                      (unsigned int )(1 << 31)
#define    SION                            (unsigned int )(1 << 30)
#define    PAD_CTL_HYS                     (unsigned int )(1 << 16)
#define    PAD_CTL_PUS_100K_DOWN           (unsigned int )(0 << 14)
#define    PAD_CTL_PUS_47K_UP              (unsigned int )(1 << 14)
#define    PAD_CTL_PUS_100K_UP             (unsigned int )(2 << 14)
#define    PAD_CTL_PUS_22K_UP              (unsigned int )(3 << 14)
#define    PAD_CTL_PUE                     (unsigned int )(1 << 13)
#define    PAD_CTL_PKE                     (unsigned int )(1 << 12)
#define    PAD_CTL_ODE                     (unsigned int )(1 << 11)
#define    PAD_CTL_SPEED_LOW               (unsigned int )(1 << 6)
#define    PAD_CTL_SPEED_MED               (unsigned int )(2 << 6)
#define    PAD_CTL_SPEED_HIGH              (unsigned int )(3 << 6)
#define    PAD_CTL_DSE_DISABLE             (unsigned int )(0 << 3)
#define    PAD_CTL_DSE_34ohm               (unsigned int )(7 << 3)
#define    PAD_CTL_DSE_40ohm               (unsigned int )(6 << 3)
#define    PAD_CTL_DSE_48ohm               (unsigned int )(5 << 3)
#define    PAD_CTL_DSE_60ohm               (unsigned int )(4 << 3)
#define    PAD_CTL_DSE_80ohm               (unsigned int )(3 << 3)
#define    PAD_CTL_DSE_120ohm              (unsigned int )(2 << 3)
#define    PAD_CTL_DSE_240ohm              (unsigned int )(1 << 3)
#define    PAD_CTL_SRE_FAST                (unsigned int )(1 << 0)
#define    PAD_CTL_SRE_SLOW                (unsigned int )(0 << 0)
#define    PAD_DSE_MASK                    (unsigned int )(0xfe)
void NOVAembed::on_U_DecodeCFGBits_pushButton_clicked()
{
    bool ok=1;
    QString a = ui->U_Decoded_CFG_Bits_lineEdit->text().right(8);
    unsigned int value = a.toUInt(&ok,16);
    qDebug()  << "value = 0x" << QString::number(value, 16);

    if ( (unsigned int )(value & NO_PAD_CTL) == NO_PAD_CTL )
    {
        ui->U_NO_PAD_CTL_checkBox->setChecked(true);
        ui->U_DSE_Disable_checkBox->setEnabled(false);
        ui->U_DSE_frame->setEnabled(false);
        ui->U_Speed_frame->setEnabled(false);
        ui->U_SRE_frame->setEnabled(false);
        ui->U_PUE_checkBox->setEnabled(false);
        ui->U_PUPD_frame->setEnabled(false);
        ui->U_ODE_checkBox->setEnabled(false);
        ui->U_PKE_checkBox->setEnabled(false);
        ui->U_SION_checkBox->setEnabled(false);
        ui->U_HYS_PAD_CTL_checkBox->setEnabled(false);
    }
    else
    {
        ui->U_NO_PAD_CTL_checkBox->setChecked(false);
        ui->U_DSE_Disable_checkBox->setEnabled(true);
        ui->U_DSE_frame->setEnabled(true);
        ui->U_Speed_frame->setEnabled(true);
        ui->U_SRE_frame->setEnabled(true);
        ui->U_PUE_checkBox->setEnabled(true);
        ui->U_PUPD_frame->setEnabled(true);
        ui->U_ODE_checkBox->setEnabled(true);
        ui->U_PKE_checkBox->setEnabled(true);
        ui->U_SION_checkBox->setEnabled(true);
        ui->U_HYS_PAD_CTL_checkBox->setEnabled(true);
    }

    ui->U_SION_checkBox->setChecked(false);
    ui->U_HYS_PAD_CTL_checkBox->setChecked(false);
    if ( (unsigned int )(value & SION) == SION )
        ui->U_SION_checkBox->setChecked(true);
    if ( (unsigned int )(value & PAD_CTL_HYS) == PAD_CTL_HYS )
        ui->U_HYS_PAD_CTL_checkBox->setChecked(true);

    ui->U_PU_47K_checkBox->setChecked(false);
    ui->U_PU_100K_checkBox->setChecked(false);
    ui->U_PU_22K_checkBox->setChecked(false);
    ui->U_PD_100K_checkBox->setChecked(false);
    ui->U_PUE_checkBox->setChecked(false);
    ui->U_PKE_checkBox->setChecked(false);

    if ( (unsigned int )(value & PAD_CTL_PUS_47K_UP) == PAD_CTL_PUS_47K_UP )
    {
        ui->U_PU_47K_checkBox->setChecked(true);
        ui->U_PUE_checkBox->setChecked(true);
    }
    else if ( (unsigned int )(value & PAD_CTL_PUS_100K_UP) == PAD_CTL_PUS_100K_UP )
    {
        ui->U_PU_100K_checkBox->setChecked(true);
        ui->U_PUE_checkBox->setChecked(true);
    }
    else if ( (unsigned int )(value & PAD_CTL_PUS_22K_UP) == PAD_CTL_PUS_22K_UP )
    {
        ui->U_PU_22K_checkBox->setChecked(true);
        ui->U_PUE_checkBox->setChecked(true);
    }
    else if ( (unsigned int )(value & PAD_CTL_PUE) == PAD_CTL_PUE )
    {
        ui->U_PD_100K_checkBox->setChecked(true);
        ui->U_PUE_checkBox->setChecked(true);
    }

    if ( (unsigned int )(value & PAD_CTL_PKE) == PAD_CTL_PKE )
    {
        ui->U_PUE_checkBox->setChecked(false);
        ui->U_PUPD_frame->setEnabled(false);
    }
    if ( (unsigned int )(value & PAD_CTL_ODE) == PAD_CTL_ODE )
    {
        ui->U_ODE_checkBox->setChecked(true);
        //ui->PUE_checkBox->setChecked(false);
        //ui->PUPD_frame->setEnabled(false);
    }


    ui->U_SPEED_Low_checkBox->setChecked(false);
    ui->U_SPEED_Mid_checkBox->setChecked(false);
    ui->U_SPEED_High_checkBox->setChecked(false);
    if ( (unsigned int )(value & PAD_CTL_SPEED_LOW) == PAD_CTL_SPEED_LOW )
        ui->U_SPEED_Low_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_SPEED_MED) == PAD_CTL_SPEED_MED )
        ui->U_SPEED_Mid_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_SPEED_HIGH) == PAD_CTL_SPEED_HIGH )
        ui->U_SPEED_High_checkBox->setChecked(true);

    ui->U_DSE_34_checkBox->setChecked(false);
    ui->U_DSE_40_checkBox->setChecked(false);
    ui->U_DSE_48_checkBox->setChecked(false);
    ui->U_DSE_60_checkBox->setChecked(false);
    ui->U_DSE_80_checkBox->setChecked(false);
    ui->U_DSE_120_checkBox->setChecked(false);
    ui->U_DSE_240_checkBox->setChecked(false);
    if ( (unsigned int )(value & PAD_CTL_DSE_34ohm) == PAD_CTL_DSE_34ohm )
        ui->U_DSE_34_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_DSE_40ohm) == PAD_CTL_DSE_40ohm )
        ui->U_DSE_40_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_DSE_48ohm) == PAD_CTL_DSE_48ohm )
        ui->U_DSE_48_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_DSE_60ohm) == PAD_CTL_DSE_60ohm )
        ui->U_DSE_60_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_DSE_80ohm) == PAD_CTL_DSE_80ohm )
        ui->U_DSE_80_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_DSE_120ohm) == PAD_CTL_DSE_120ohm )
        ui->U_DSE_120_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_DSE_240ohm) == PAD_CTL_DSE_240ohm )
        ui->U_DSE_240_checkBox->setChecked(true);
    else
    {
        ui->U_DSE_34_checkBox->setChecked(false);
        ui->U_DSE_40_checkBox->setChecked(false);
        ui->U_DSE_48_checkBox->setChecked(false);
        ui->U_DSE_60_checkBox->setChecked(false);
        ui->U_DSE_80_checkBox->setChecked(false);
        ui->U_DSE_120_checkBox->setChecked(false);
        ui->U_DSE_240_checkBox->setChecked(false);
        ui->U_DSE_Disable_checkBox->setChecked(true);
        ui->U_DSE_frame->setEnabled(false);
    }

    ui->U_SRE_Fast_checkBox->setChecked(false);
    ui->U_SRE_Slow_checkBox->setChecked(false);
    if ( (unsigned int )(value & PAD_CTL_SRE_FAST) == PAD_CTL_SRE_FAST )
    {
        ui->U_SRE_Fast_checkBox->setChecked(true);
    }
    else
    {
        ui->U_SRE_Slow_checkBox->setChecked(true);
    }

}



void NOVAembed::on_U_SION_checkBox_clicked()
{

}

void NOVAembed::on_U_NO_PAD_CTL_checkBox_clicked()
{
    if ( ui->U_NO_PAD_CTL_checkBox->isChecked() == true )
        U_disable_all();
    else
        U_enable_all();
}


void NOVAembed::on_U_SPEED_Low_checkBox_clicked()
{
    if ( ui->U_SPEED_Low_checkBox->isChecked() == true )
    {
        ui->U_SPEED_Mid_checkBox->setChecked(false);
        ui->U_SPEED_High_checkBox->setChecked(false);
    }
}

void NOVAembed::on_U_SPEED_Mid_checkBox_clicked()
{
    if ( ui->U_SPEED_Mid_checkBox->isChecked() == true )
    {
        ui->U_SPEED_Low_checkBox->setChecked(false);
        ui->U_SPEED_High_checkBox->setChecked(false);
    }
}

void NOVAembed::on_U_SPEED_High_checkBox_clicked()
{
    if ( ui->U_SPEED_High_checkBox->isChecked() == true )
    {
        ui->U_SPEED_Low_checkBox->setChecked(false);
        ui->U_SPEED_Mid_checkBox->setChecked(false);
    }
}


void NOVAembed::on_U_SRE_Fast_checkBox_clicked()
{
    if ( ui->U_SRE_Fast_checkBox->isChecked() == true )
        ui->U_SRE_Slow_checkBox->setChecked(false);
}

void NOVAembed::on_U_SRE_Slow_checkBox_clicked()
{
    if ( ui->U_SRE_Slow_checkBox->isChecked() == true )
        ui->U_SRE_Fast_checkBox->setChecked(false);
}

void NOVAembed::on_U_PUE_checkBox_clicked()
{
    if ( ui->U_PUE_checkBox->isChecked() == true )
        ui->U_PUPD_frame->setEnabled(false);
    else
        ui->U_PUPD_frame->setEnabled(true);
}


void NOVAembed::on_U_PD_100K_checkBox_clicked()
{
    if ( ui->U_PD_100K_checkBox->isChecked() == true )
    {
        ui->U_PU_100K_checkBox->setChecked(false);
        ui->U_PU_47K_checkBox->setChecked(false);
        ui->U_PU_22K_checkBox->setChecked(false);
    }
}

void NOVAembed::on_U_PU_100K_checkBox_clicked()
{
    if ( ui->U_PU_100K_checkBox->isChecked() == true )
    {
        ui->U_PD_100K_checkBox->setChecked(false);
        ui->U_PU_47K_checkBox->setChecked(false);
        ui->U_PU_22K_checkBox->setChecked(false);
    }
}

void NOVAembed::on_U_PU_47K_checkBox_clicked()
{
    if ( ui->U_PU_47K_checkBox->isChecked() == true )
    {
        ui->U_PD_100K_checkBox->setChecked(false);
        ui->U_PU_100K_checkBox->setChecked(false);
        ui->U_PU_22K_checkBox->setChecked(false);
    }
}

void NOVAembed::on_U_PU_22K_checkBox_clicked()
{
    if ( ui->U_PU_22K_checkBox->isChecked() == true )
    {
        ui->U_PD_100K_checkBox->setChecked(false);
        ui->U_PU_100K_checkBox->setChecked(false);
        ui->U_PU_47K_checkBox->setChecked(false);
    }
}

void NOVAembed::on_U_ODE_checkBox_clicked()
{

}


void NOVAembed::on_U_PKE_checkBox_clicked()
{

}



void NOVAembed::on_U_DSE_Disable_checkBox_clicked()
{
    if ( ui->U_DSE_Disable_checkBox->isChecked() == true )
        ui->U_DSE_frame->setEnabled(false);
    else
        ui->U_DSE_frame->setEnabled(true);
}

void NOVAembed::on_U_DSE_34_checkBox_clicked()
{
    if ( ui->U_DSE_34_checkBox->isChecked() == true )
    {
        ui->U_DSE_40_checkBox->setChecked(false);
        ui->U_DSE_48_checkBox->setChecked(false);
        ui->U_DSE_60_checkBox->setChecked(false);
        ui->U_DSE_80_checkBox->setChecked(false);
        ui->U_DSE_120_checkBox->setChecked(false);
        ui->U_DSE_240_checkBox->setChecked(false);
    }
}

void NOVAembed::on_U_DSE_40_checkBox_clicked()
{
    if ( ui->U_DSE_40_checkBox->isChecked() == true )
    {
        ui->U_DSE_34_checkBox->setChecked(false);
        ui->U_DSE_48_checkBox->setChecked(false);
        ui->U_DSE_60_checkBox->setChecked(false);
        ui->U_DSE_80_checkBox->setChecked(false);
        ui->U_DSE_120_checkBox->setChecked(false);
        ui->U_DSE_240_checkBox->setChecked(false);
    }
}

void NOVAembed::on_U_DSE_48_checkBox_clicked()
{
    if ( ui->U_DSE_48_checkBox->isChecked() == true )
    {
        ui->U_DSE_34_checkBox->setChecked(false);
        ui->U_DSE_40_checkBox->setChecked(false);
        ui->U_DSE_60_checkBox->setChecked(false);
        ui->U_DSE_80_checkBox->setChecked(false);
        ui->U_DSE_120_checkBox->setChecked(false);
        ui->U_DSE_240_checkBox->setChecked(false);
    }
}

void NOVAembed::on_U_DSE_60_checkBox_clicked()
{
    if ( ui->U_DSE_60_checkBox->isChecked() == true )
    {
        ui->U_DSE_34_checkBox->setChecked(false);
        ui->U_DSE_40_checkBox->setChecked(false);
        ui->U_DSE_48_checkBox->setChecked(false);
        ui->U_DSE_80_checkBox->setChecked(false);
        ui->U_DSE_120_checkBox->setChecked(false);
        ui->U_DSE_240_checkBox->setChecked(false);
    }
}

void NOVAembed::on_U_DSE_80_checkBox_clicked()
{
    if ( ui->U_DSE_80_checkBox->isChecked() == true )
    {
        ui->U_DSE_34_checkBox->setChecked(false);
        ui->U_DSE_40_checkBox->setChecked(false);
        ui->U_DSE_48_checkBox->setChecked(false);
        ui->U_DSE_60_checkBox->setChecked(false);
        ui->U_DSE_120_checkBox->setChecked(false);
        ui->U_DSE_240_checkBox->setChecked(false);
    }
}

void NOVAembed::on_U_DSE_120_checkBox_clicked()
{
    if ( ui->U_DSE_120_checkBox->isChecked() == true )
    {
        ui->U_DSE_34_checkBox->setChecked(false);
        ui->U_DSE_40_checkBox->setChecked(false);
        ui->U_DSE_48_checkBox->setChecked(false);
        ui->U_DSE_60_checkBox->setChecked(false);
        ui->U_DSE_80_checkBox->setChecked(false);
        ui->U_DSE_240_checkBox->setChecked(false);
    }
}

void NOVAembed::on_U_DSE_240_checkBox_clicked()
{
    if ( ui->U_DSE_240_checkBox->isChecked() == true )
    {
        ui->U_DSE_34_checkBox->setChecked(false);
        ui->U_DSE_40_checkBox->setChecked(false);
        ui->U_DSE_48_checkBox->setChecked(false);
        ui->U_DSE_60_checkBox->setChecked(false);
        ui->U_DSE_80_checkBox->setChecked(false);
        ui->U_DSE_120_checkBox->setChecked(false);
    }
}

/*****************************************************************************************************************************************************************************************/
/*                                                                             U BSP Factory END                                                                                         */
/*****************************************************************************************************************************************************************************************/

