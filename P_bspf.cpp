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
#include <QDirIterator>

extern  QString FileSystemName;
extern  QString DeployedFileSystemName;
extern  QString FileSystemConfigName;
extern  QString CfgBitDefaultValue;
extern  QString _Board_comboBox;
extern  QString Last_P_BSPFactoryFile;
extern  QString LVDSVideo;
extern  QString Quad;

QString FileNameNoExtension;

void NOVAembed::on_P_Load_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Load BSP Factory File"), "/Devel/NOVAsom_SDK/DtbUserWorkArea/PClass_bspf",tr("BSP Factory Files (*.bspf)"));
    if (fileName.isEmpty())
        return;
    else
    {
        P_load_BSPF_File(fileName);
    }
}

/*****************************************************************************************************************************************************************************************/
/*                                                                             P BSP Factory                                                                                             */
/*****************************************************************************************************************************************************************************************/
/* J13 */
/* ECSPI1 Group */
void NOVAembed::on_P_ECSPI1_MISO_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "ECSPI1_MISO")
    {
        ui->P_ECSPI1_MOSI_comboBox->setCurrentText("ECSPI1_MOSI");
        ui->P_ECSPI1_SS0_comboBox->setCurrentText("ECSPI1_SS0");
        ui->P_ECSPI1_SCK_comboBox->setCurrentText("ECSPI1_SCK");
    }
    if ( arg1 == "AUD4_TXFS")
    {
        ui->P_ECSPI1_MOSI_comboBox->setCurrentText("AUD4_TXD");
        ui->P_ECSPI1_SS0_comboBox->setCurrentText("AUD4_RXD");
        ui->P_ECSPI1_SCK_comboBox->setCurrentText("AUD4_TXC");
        ui->P_ECSPI2_SS1_comboBox->setCurrentText("GPIO5_IO09");
    }
    if ( arg1 == "GPIO5_IO16")
    {
        ui->P_ECSPI1_MOSI_comboBox->setCurrentText("GPIO5_IO15");
        ui->P_ECSPI1_SS0_comboBox->setCurrentText("GPIO5_IO17");
        ui->P_ECSPI1_SCK_comboBox->setCurrentText("GPIO5_IO14");
        ui->P_ECSPI2_SS1_comboBox->setCurrentText("GPIO5_IO09");
    }

}

void NOVAembed::on_P_ECSPI1_MOSI_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "ECSPI1_MOSI")
    {
        ui->P_ECSPI1_MISO_comboBox->setCurrentText("ECSPI1_MISO");
        ui->P_ECSPI1_SS0_comboBox->setCurrentText("ECSPI1_SS0");
        ui->P_ECSPI1_SCK_comboBox->setCurrentText("ECSPI1_SCK");
    }
    if ( arg1 == "AUD4_TXD")
    {
        ui->P_ECSPI1_MISO_comboBox->setCurrentText("AUD4_TXFS");
        ui->P_ECSPI1_SS0_comboBox->setCurrentText("AUD4_RXD");
        ui->P_ECSPI1_SCK_comboBox->setCurrentText("AUD4_TXC");
        ui->P_ECSPI2_SS1_comboBox->setCurrentText("GPIO5_IO09");
    }
    if ( arg1 == "GPIO5_IO15")
    {
        ui->P_ECSPI1_MISO_comboBox->setCurrentText("GPIO5_IO16");
        ui->P_ECSPI1_SS0_comboBox->setCurrentText("GPIO5_IO17");
        ui->P_ECSPI1_SCK_comboBox->setCurrentText("GPIO5_IO14");
        ui->P_ECSPI2_SS1_comboBox->setCurrentText("GPIO5_IO09");
    }
}


void NOVAembed::on_P_ECSPI1_SS0_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "ECSPI1_SS0")
    {
        ui->P_ECSPI1_MISO_comboBox->setCurrentText("ECSPI1_MISO");
        ui->P_ECSPI1_MOSI_comboBox->setCurrentText("ECSPI1_MOSI");
        ui->P_ECSPI1_SCK_comboBox->setCurrentText("ECSPI1_SCK");
    }
    if ( arg1 == "AUD4_RXD")
    {
        ui->P_ECSPI1_MISO_comboBox->setCurrentText("AUD4_TXFS");
        ui->P_ECSPI1_MOSI_comboBox->setCurrentText("AUD4_TXD");
        ui->P_ECSPI1_SCK_comboBox->setCurrentText("AUD4_TXC");
        ui->P_ECSPI2_SS1_comboBox->setCurrentText("GPIO5_IO09");
    }
    if ( arg1 == "GPIO5_IO17")
    {
        ui->P_ECSPI1_MISO_comboBox->setCurrentText("GPIO5_IO16");
        ui->P_ECSPI1_MOSI_comboBox->setCurrentText("GPIO5_IO15");
        ui->P_ECSPI1_SCK_comboBox->setCurrentText("GPIO5_IO14");
        ui->P_ECSPI2_SS1_comboBox->setCurrentText("GPIO5_IO09");
    }
}

void NOVAembed::on_P_ECSPI1_SCK_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "ECSPI1_SCK")
    {
        ui->P_ECSPI1_MISO_comboBox->setCurrentText("ECSPI1_MISO");
        ui->P_ECSPI1_MOSI_comboBox->setCurrentText("ECSPI1_MOSI");
        ui->P_ECSPI1_SS0_comboBox->setCurrentText("ECSPI1_SS0");
    }
    if ( arg1 == "AUD4_TXC")
    {
        ui->P_ECSPI1_MISO_comboBox->setCurrentText("AUD4_TXFS");
        ui->P_ECSPI1_MOSI_comboBox->setCurrentText("AUD4_TXD");
        ui->P_ECSPI1_SS0_comboBox->setCurrentText("AUD4_RXD");
        ui->P_ECSPI2_SS1_comboBox->setCurrentText("GPIO5_IO09");
    }
    if ( arg1 == "GPIO5_IO14")
    {
        ui->P_ECSPI1_MISO_comboBox->setCurrentText("GPIO5_IO16");
        ui->P_ECSPI1_MOSI_comboBox->setCurrentText("GPIO5_IO15");
        ui->P_ECSPI1_SS0_comboBox->setCurrentText("GPIO5_IO17");
        ui->P_ECSPI2_SS1_comboBox->setCurrentText("GPIO5_IO09");
    }
}

/* ECSPI1 / ECSPI22 Group */
void NOVAembed::on_P_ECSPI2_SS1_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "ECSPI1_SS1")
    {
        ui->P_ECSPI1_MISO_comboBox->setCurrentText("ECSPI1_MISO");
        ui->P_ECSPI1_MOSI_comboBox->setCurrentText("ECSPI1_MOSI");
        ui->P_ECSPI1_SCK_comboBox->setCurrentText("ECSPI1_SCK");
        ui->P_ECSPI1_SS0_comboBox->setCurrentText("ECSPI1_SS0");
    }
    if ( arg1 == "ECSPI2_SS1")
    {
        ui->P_ECSPI2_MISO_comboBox->setCurrentText("ECSPI2_MISO");
        ui->P_ECSPI2_MOSI_comboBox->setCurrentText("ECSPI2_MOSI");
        ui->P_ECSPI2_SCK_comboBox->setCurrentText("ECSPI2_SCK");
        ui->P_ECSPI2_SS0_comboBox->setCurrentText("ECSPI2_SS0");
    }
}

/* ECSPI2 Group */
void NOVAembed::on_P_ECSPI2_SS0_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "ECSPI2_SS0")
    {
        ui->P_ECSPI2_MISO_comboBox->setCurrentText("ECSPI2_MISO");
        ui->P_ECSPI2_MOSI_comboBox->setCurrentText("ECSPI2_MOSI");
        ui->P_ECSPI2_SCK_comboBox->setCurrentText("ECSPI2_SCK");
    }
    if ( arg1 == "AUD5_TXFS")
    {
        ui->P_ECSPI2_MISO_comboBox->setCurrentText("AUD5_TXD");
        ui->P_ECSPI2_MOSI_comboBox->setCurrentText("AUD5_TXC");
        ui->P_ECSPI2_SCK_comboBox->setCurrentText("AUD5_RXD");
        ui->P_ECSPI2_SS1_comboBox->setCurrentText("GPIO5_IO09");
        ui->P_ECSPI2_SS1_comboBox->setCurrentText("GPIO5_IO09");
    }
    if ( arg1 == "GPIO5_IO12")
    {
        ui->P_ECSPI2_MISO_comboBox->setCurrentText("GPIO5_IO11");
        ui->P_ECSPI2_MOSI_comboBox->setCurrentText("GPIO5_IO10");
        ui->P_ECSPI2_SCK_comboBox->setCurrentText("GPIO5_IO13");
        ui->P_ECSPI2_SS1_comboBox->setCurrentText("GPIO5_IO09");
    }
}


void NOVAembed::on_P_ECSPI2_MISO_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "ECSPI2_MISO")
    {
        ui->P_ECSPI2_SS0_comboBox->setCurrentText("ECSPI2_SS0");
        ui->P_ECSPI2_MOSI_comboBox->setCurrentText("ECSPI2_MOSI");
        ui->P_ECSPI2_SCK_comboBox->setCurrentText("ECSPI2_SCK");
    }
    if ( arg1 == "AUD5_TXD")
    {
        ui->P_ECSPI2_SS0_comboBox->setCurrentText("AUD5_TXFS");
        ui->P_ECSPI2_MOSI_comboBox->setCurrentText("AUD5_TXC");
        ui->P_ECSPI2_SCK_comboBox->setCurrentText("AUD5_RXD");
        ui->P_ECSPI2_SS1_comboBox->setCurrentText("GPIO5_IO09");
    }
    if ( arg1 == "GPIO5_IO11")
    {
        ui->P_ECSPI2_SS0_comboBox->setCurrentText("GPIO5_IO12");
        ui->P_ECSPI2_MOSI_comboBox->setCurrentText("GPIO5_IO10");
        ui->P_ECSPI2_SCK_comboBox->setCurrentText("GPIO5_IO13");
        ui->P_ECSPI2_SS1_comboBox->setCurrentText("GPIO5_IO09");
    }
}

void NOVAembed::on_P_ECSPI2_MOSI_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "ECSPI2_MOSI")
    {
        ui->P_ECSPI2_SS0_comboBox->setCurrentText("ECSPI2_SS0");
        ui->P_ECSPI2_MISO_comboBox->setCurrentText("ECSPI2_MISO");
        ui->P_ECSPI2_SCK_comboBox->setCurrentText("ECSPI2_SCK");
    }
    if ( arg1 == "AUD5_TXC")
    {
        ui->P_ECSPI2_SS0_comboBox->setCurrentText("AUD5_TXFS");
        ui->P_ECSPI2_MISO_comboBox->setCurrentText("AUD5_TXD");
        ui->P_ECSPI2_SCK_comboBox->setCurrentText("AUD5_RXD");
        ui->P_ECSPI2_SS1_comboBox->setCurrentText("GPIO5_IO09");
    }
    if ( arg1 == "GPIO5_IO10")
    {
        ui->P_ECSPI2_SS0_comboBox->setCurrentText("GPIO5_IO12");
        ui->P_ECSPI2_MISO_comboBox->setCurrentText("GPIO5_IO11");
        ui->P_ECSPI2_SCK_comboBox->setCurrentText("GPIO5_IO13");
        ui->P_ECSPI2_SS1_comboBox->setCurrentText("GPIO5_IO09");
    }
}

void NOVAembed::on_P_ECSPI2_SCK_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "ECSPI2_SCK")
    {
        ui->P_ECSPI2_SS0_comboBox->setCurrentText("ECSPI2_SS0");
        ui->P_ECSPI2_MISO_comboBox->setCurrentText("ECSPI2_MISO");
        ui->P_ECSPI2_MOSI_comboBox->setCurrentText("ECSPI2_MOSI");
    }
    if ( arg1 == "AUD5_RXD")
    {
        ui->P_ECSPI2_SS0_comboBox->setCurrentText("AUD5_TXFS");
        ui->P_ECSPI2_MISO_comboBox->setCurrentText("AUD5_TXD");
        ui->P_ECSPI2_MOSI_comboBox->setCurrentText("AUD5_TXC");
        ui->P_ECSPI2_SS1_comboBox->setCurrentText("GPIO5_IO09");
    }
    if ( arg1 == "GPIO5_IO13")
    {
        ui->P_ECSPI2_SS0_comboBox->setCurrentText("GPIO5_IO12");
        ui->P_ECSPI2_MISO_comboBox->setCurrentText("GPIO5_IO11");
        ui->P_ECSPI2_MOSI_comboBox->setCurrentText("GPIO5_IO10");
        ui->P_ECSPI2_SS1_comboBox->setCurrentText("GPIO5_IO09");
    }
}

/* ECSPI3 Group */
void NOVAembed::on_P_ECSPI3_MISO_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "ECSPI3_MISO")
    {
        ui->P_ECSPI3_SS0_comboBox->setCurrentText("ECSPI3_SS0");
        ui->P_ECSPI3_MOSI_comboBox->setCurrentText("ECSPI3_MOSI");
        ui->P_ECSPI3_SCK_comboBox->setCurrentText("ECSPI3_SCK");
    }
    if ( arg1 == "GPIO4_IO23")
    {
        ui->P_ECSPI3_SS0_comboBox->setCurrentText("GPIO4_IO24");
        ui->P_ECSPI3_MOSI_comboBox->setCurrentText("GPIO4_IO22");
        ui->P_ECSPI3_SCK_comboBox->setCurrentText("GPIO4_IO21");
        ui->P_ECSPI3_SS1_comboBox->setCurrentText("GPIO4_IO25");
    }
}

void NOVAembed::on_P_ECSPI3_SCK_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "ECSPI3_SCK")
    {
        ui->P_ECSPI3_SS0_comboBox->setCurrentText("ECSPI3_SS0");
        ui->P_ECSPI3_MOSI_comboBox->setCurrentText("ECSPI3_MOSI");
        ui->P_ECSPI3_MISO_comboBox->setCurrentText("ECSPI3_MISO");
    }
    if ( arg1 == "GPIO4_IO21")
    {
        ui->P_ECSPI3_SS0_comboBox->setCurrentText("GPIO4_IO24");
        ui->P_ECSPI3_MOSI_comboBox->setCurrentText("GPIO4_IO22");
        ui->P_ECSPI3_MISO_comboBox->setCurrentText("GPIO4_IO23");
        ui->P_ECSPI3_SS1_comboBox->setCurrentText("GPIO4_IO25");
    }
}

void NOVAembed::on_P_ECSPI3_MOSI_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "ECSPI3_MOSI")
    {
        ui->P_ECSPI3_SS0_comboBox->setCurrentText("ECSPI3_SS0");
        ui->P_ECSPI3_SCK_comboBox->setCurrentText("ECSPI3_SCK");
        ui->P_ECSPI3_MISO_comboBox->setCurrentText("ECSPI3_MISO");
    }
    if ( arg1 == "GPIO4_IO22")
    {
        ui->P_ECSPI3_SS0_comboBox->setCurrentText("GPIO4_IO24");
        ui->P_ECSPI3_SCK_comboBox->setCurrentText("GPIO4_IO21");
        ui->P_ECSPI3_MISO_comboBox->setCurrentText("GPIO4_IO23");
        ui->P_ECSPI3_SS1_comboBox->setCurrentText("GPIO4_IO25");
    }
}

void NOVAembed::on_P_ECSPI3_SS0_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "ECSPI3_MOSI")
    {
        ui->P_ECSPI3_MOSI_comboBox->setCurrentText("ECSPI3_MOSI");
        ui->P_ECSPI3_SCK_comboBox->setCurrentText("ECSPI3_SCK");
        ui->P_ECSPI3_MISO_comboBox->setCurrentText("ECSPI3_MISO");
    }
    if ( arg1 == "GPIO4_IO24")
    {
        ui->P_ECSPI3_MOSI_comboBox->setCurrentText("GPIO4_IO22");
        ui->P_ECSPI3_SCK_comboBox->setCurrentText("GPIO4_IO21");
        ui->P_ECSPI3_MISO_comboBox->setCurrentText("GPIO4_IO23");
        ui->P_ECSPI3_SS1_comboBox->setCurrentText("GPIO4_IO25");
    }
}

void NOVAembed::on_P_ECSPI3_SS1_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "ECSPI3_SS1")
    {
        ui->P_ECSPI3_MOSI_comboBox->setCurrentText("ECSPI3_MOSI");
        ui->P_ECSPI3_SCK_comboBox->setCurrentText("ECSPI3_SCK");
        ui->P_ECSPI3_MISO_comboBox->setCurrentText("ECSPI3_MISO");
        ui->P_ECSPI3_SS0_comboBox->setCurrentText("ECSPI3_SS0");
        ui->P_ECSPI3_SS1_comboBox->setCurrentText("ECSPI3_SS1");
    }
    if ( arg1 == "GPIO4_IO25")
        ui->P_ECSPI3_SS1_comboBox->setCurrentText("GPIO4_IO25");
}

/* ECSPI4 Group */

void NOVAembed::on_P_ECSPI4_MISO_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "ECSPI4_MISO")
    {
        ui->P_ECSPI4_SS0_comboBox->setCurrentText("ECSPI4_SS0");
        ui->P_ECSPI4_MOSI_comboBox->setCurrentText("ECSPI4_MOSI");
        ui->P_ECSPI4_SCK_comboBox->setCurrentText("ECSPI4_SCK");
    }
    if ( arg1 == "SPDIF_OUT")
    {
        ui->P_ECSPI4_SS0_comboBox->setCurrentText("GPIO3_IO29");

        if ( ui->P_SPDIF_OUT_comboBox->currentText() == "SPDIF_OUT")
            ui->P_SPDIF_OUT_comboBox->setCurrentText("GPIO7_IO12");

        if ( ui->P_ECSPI4_MOSI_comboBox->currentText() != "I2C1_SDA")
            ui->P_ECSPI4_MOSI_comboBox->setCurrentText("GPIO3_IO28");
        if ( ui->P_ECSPI4_SCK_comboBox->currentText() != "I2C1_SCL")
            ui->P_ECSPI4_SCK_comboBox->setCurrentText("GPIO3_IO21");
    }
    if ( arg1 == "GPIO3_IO22")
    {
        ui->P_ECSPI4_SS0_comboBox->setCurrentText("GPIO3_IO29");
        ui->P_ECSPI4_MOSI_comboBox->setCurrentText("GPIO3_IO28");
        ui->P_ECSPI4_SCK_comboBox->setCurrentText("GPIO3_IO21");
    }
}

void NOVAembed::on_P_ECSPI4_MOSI_comboBox_currentIndexChanged(const QString &arg1)
{
        if ( arg1 == "ECSPI4_MOSI")
        {
            ui->P_ECSPI4_SS0_comboBox->setCurrentText("ECSPI4_SS0");
            ui->P_ECSPI4_MISO_comboBox->setCurrentText("ECSPI4_MISO");
            ui->P_ECSPI4_SCK_comboBox->setCurrentText("ECSPI4_SCK");
        }
        if ( arg1 == "I2C1_SDA")
        {
            ui->P_ECSPI4_SS0_comboBox->setCurrentText("GPIO3_IO29");
            if ( ui->P_ECSPI4_MISO_comboBox->currentText() != "SPDIF_OUT")
                ui->P_ECSPI4_MISO_comboBox->setCurrentText("GPIO3_IO22");
            ui->P_ECSPI4_SCK_comboBox->setCurrentText("I2C1_SCL");
            /* P_I2C1_SDA_comboBox become GPIO5_IO26 */
            /* P_I2C1_SCL_comboBox become GPIO5_IO27 */
            ui->P_I2C1_SDA_comboBox->setCurrentText("GPIO5_IO26");
            ui->P_I2C1_SCL_comboBox->setCurrentText("GPIO5_IO27");
        }
        if ( arg1 == "GPIO3_IO28")
        {
            ui->P_ECSPI4_SS0_comboBox->setCurrentText("GPIO3_IO29");
            ui->P_ECSPI4_MISO_comboBox->setCurrentText("GPIO3_IO22");
            ui->P_ECSPI4_SCK_comboBox->setCurrentText("GPIO3_IO21");
        }
}

void NOVAembed::on_P_ECSPI4_SCK_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "ECSPI4_SCK")
    {
        ui->P_ECSPI4_SS0_comboBox->setCurrentText("ECSPI4_SS0");
        ui->P_ECSPI4_MISO_comboBox->setCurrentText("ECSPI4_MISO");
        ui->P_ECSPI4_MOSI_comboBox->setCurrentText("ECSPI4_MOSI");
    }
    if ( arg1 == "I2C1_SCL")
    {
        ui->P_ECSPI4_SS0_comboBox->setCurrentText("GPIO3_IO29");
        if ( ui->P_ECSPI4_MISO_comboBox->currentText() != "SPDIF_OUT")
            ui->P_ECSPI4_MISO_comboBox->setCurrentText("GPIO3_IO22");
        ui->P_ECSPI4_MOSI_comboBox->setCurrentText("I2C1_SDA");
    }
    if ( arg1 == "GPIO3_IO21")
    {
        if ( ui->P_ECSPI4_MISO_comboBox->currentText() == "ECSPI4_MISO")
        {
            ui->P_ECSPI4_MISO_comboBox->setCurrentText("GPIO3_IO22");
            ui->P_ECSPI4_SS0_comboBox->setCurrentText("GPIO3_IO29");
            ui->P_ECSPI4_MOSI_comboBox->setCurrentText("GPIO3_IO28");
        }
    }
}

void NOVAembed::on_P_ECSPI4_SS0_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "ECSPI4_SS0")
    {
        ui->P_ECSPI4_SCK_comboBox->setCurrentText("ECSPI4_SCK");
        ui->P_ECSPI4_MISO_comboBox->setCurrentText("ECSPI4_MISO");
        ui->P_ECSPI4_MOSI_comboBox->setCurrentText("ECSPI4_MOSI");
    }
    if ( arg1 == "GPIO3_IO29")
    {
        ui->P_ECSPI4_SCK_comboBox->setCurrentText("GPIO3_IO21");
        ui->P_ECSPI4_MISO_comboBox->setCurrentText("GPIO3_IO22");
        ui->P_ECSPI4_MOSI_comboBox->setCurrentText("GPIO3_IO28");
    }
}

/* I2C3 Group */

void NOVAembed::on_P_I2C3_SCL_comboBox_currentIndexChanged(const QString &arg1)
{

    if ( arg1 == "I2C3_SCL")
    {
        ui->P_I2C3_SDA_comboBox->setCurrentText("I2C3_SDA");
    }
    if ( arg1 == "GPIO3_IO17")
    {
        ui->P_I2C3_SDA_comboBox->setCurrentText("GPIO3_IO18");
    }
}

void NOVAembed::on_P_I2C3_SDA_comboBox_currentIndexChanged(const QString &arg1)
{

    if ( arg1 == "I2C3_SDA")
    {
        ui->P_I2C3_SCL_comboBox->setCurrentText("I2C3_SCL");

    }
    if ( arg1 == "GPIO3_IO18")
    {
        ui->P_I2C3_SCL_comboBox->setCurrentText("GPIO3_IO17");

    }
}
/* Clock 32 KHz out */

void NOVAembed::on_P_KHZ32_CLK_OUT_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "32KHZ_CLK_OUT")
    {
        ui->P_KHZ32_CLK_OUT_comboBox->setCurrentText("32KHZ_CLK_OUT");

    }
    if ( arg1 == "GPIO1_IO08")
    {
        ui->P_KHZ32_CLK_OUT_comboBox->setCurrentText("GPIO1_IO08");

    }
}

/* SD3 Group */

void NOVAembed::set_sd3_8_IO_helper(void)
{
    if ( ui->P_SD3_CMD_comboBox->currentText() == "SD3_CMD")
        ui->P_SD3_CMD_comboBox->setCurrentText("GPIO7_IO02");
    if ( ui->P_SD3_CLK_comboBox->currentText() == "SD3_CLK")
        ui->P_SD3_CLK_comboBox->setCurrentText("GPIO7_IO03");
    if ( ui->P_SD3_DATA0_comboBox->currentText() == "SD3_DATA0")
        ui->P_SD3_DATA0_comboBox->setCurrentText("GPIO7_IO04");
    if ( ui->P_SD3_DATA1_comboBox->currentText() == "SD3_DATA1")
        ui->P_SD3_DATA1_comboBox->setCurrentText("GPIO7_IO05");
    if ( ui->P_SD3_DATA2_comboBox->currentText() == "SD3_DATA2")
        ui->P_SD3_DATA2_comboBox->setCurrentText("GPIO7_IO06");
    if ( ui->P_SD3_DATA3_comboBox->currentText() == "SD3_DATA3")
        ui->P_SD3_DATA3_comboBox->setCurrentText("GPIO7_IO07");
    if ( ui->P_SD3_DATA4_comboBox->currentText() == "SD3_DATA4")
        ui->P_SD3_DATA4_comboBox->setCurrentText("GPIO7_IO01");
    if ( ui->P_SD3_DATA5_comboBox->currentText() == "SD3_DATA5")
        ui->P_SD3_DATA5_comboBox->setCurrentText("GPIO7_IO00");
    if ( ui->P_SD3_DATA6_comboBox->currentText() == "SD3_DATA6")
        ui->P_SD3_DATA6_comboBox->setCurrentText("GPIO6_IO18");
    if ( ui->P_SD3_DATA7_comboBox->currentText() == "SD3_DATA7")
        ui->P_SD3_DATA7_comboBox->setCurrentText("GPIO6_IO17");
}

void NOVAembed::set_sd3_4L_IO_helper(void)
{
    if ( ui->P_SD3_CMD_comboBox->currentText() == "SD3_CMD")
        ui->P_SD3_CMD_comboBox->setCurrentText("GPIO7_IO02");
    if ( ui->P_SD3_CLK_comboBox->currentText() == "SD3_CLK")
        ui->P_SD3_CLK_comboBox->setCurrentText("GPIO7_IO03");
    if ( ui->P_SD3_DATA0_comboBox->currentText() == "SD3_DATA0")
        ui->P_SD3_DATA0_comboBox->setCurrentText("GPIO7_IO04");
    if ( ui->P_SD3_DATA1_comboBox->currentText() == "SD3_DATA1")
        ui->P_SD3_DATA1_comboBox->setCurrentText("GPIO7_IO05");
    if ( ui->P_SD3_DATA2_comboBox->currentText() == "SD3_DATA2")
        ui->P_SD3_DATA2_comboBox->setCurrentText("GPIO7_IO06");
    if ( ui->P_SD3_DATA3_comboBox->currentText() == "SD3_DATA3")
        ui->P_SD3_DATA3_comboBox->setCurrentText("GPIO7_IO07");
}

void NOVAembed::set_sd3_4H_IO_helper(void)
{
    if ( ui->P_SD3_DATA4_comboBox->currentText() == "SD3_DATA4")
        ui->P_SD3_DATA4_comboBox->setCurrentText("GPIO7_IO01");
    if ( ui->P_SD3_DATA5_comboBox->currentText() == "SD3_DATA5")
        ui->P_SD3_DATA5_comboBox->setCurrentText("GPIO7_IO00");
    if ( ui->P_SD3_DATA6_comboBox->currentText() == "SD3_DATA6")
        ui->P_SD3_DATA6_comboBox->setCurrentText("GPIO6_IO18");
    if ( ui->P_SD3_DATA7_comboBox->currentText() == "SD3_DATA7")
        ui->P_SD3_DATA7_comboBox->setCurrentText("GPIO6_IO17");
}

void NOVAembed::set_sd3_4_SD_helper(void)
{
    ui->P_SD3_CMD_comboBox->setCurrentText("SD3_CMD");
    ui->P_SD3_CLK_comboBox->setCurrentText("SD3_CLK");
    ui->P_SD3_DATA0_comboBox->setCurrentText("SD3_DATA0");
    ui->P_SD3_DATA1_comboBox->setCurrentText("SD3_DATA1");
    ui->P_SD3_DATA2_comboBox->setCurrentText("SD3_DATA2");
    ui->P_SD3_DATA3_comboBox->setCurrentText("SD3_DATA3");
}

void NOVAembed::set_sd3_8_SD_helper(void)
{
    ui->P_SD3_CMD_comboBox->setCurrentText("SD3_CMD");
    ui->P_SD3_CLK_comboBox->setCurrentText("SD3_CLK");
    ui->P_SD3_DATA0_comboBox->setCurrentText("SD3_DATA0");
    ui->P_SD3_DATA1_comboBox->setCurrentText("SD3_DATA1");
    ui->P_SD3_DATA2_comboBox->setCurrentText("SD3_DATA2");
    ui->P_SD3_DATA3_comboBox->setCurrentText("SD3_DATA3");
    ui->P_SD3_DATA4_comboBox->setCurrentText("SD3_DATA4");
    ui->P_SD3_DATA5_comboBox->setCurrentText("SD3_DATA5");
    ui->P_SD3_DATA6_comboBox->setCurrentText("SD3_DATA6");
    ui->P_SD3_DATA7_comboBox->setCurrentText("SD3_DATA7");
}

void NOVAembed::on_P_SD3_CMD_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "SD3_CMD")
        set_sd3_4_SD_helper();

    if ( arg1 == "GPIO7_IO02")
    {
        ui->P_SD3_CMD_comboBox->setCurrentText("GPIO7_IO02");
        if ( ui->P_SD3_CLK_comboBox->currentText() == "FLEXCAN1_RX")
            ui->P_SD3_CLK_comboBox->setCurrentText("GPIO7_IO03");
        set_sd3_4L_IO_helper();
    }
    if ( arg1 == "FLEXCAN1_TX")
    {
        ui->P_SD3_CLK_comboBox->setCurrentText("FLEXCAN1_RX");
        set_sd3_4L_IO_helper();
    }
    if ( arg1 == "UART2_CTS_B")
    {
        ui->P_SD3_DATA4_comboBox->setCurrentText("UART2_RX_DATA");
        ui->P_SD3_DATA5_comboBox->setCurrentText("UART2_TX_DATA");
        ui->P_SD3_CLK_comboBox->setCurrentText("UART2_RTS_B");
        set_sd3_4L_IO_helper();
    }
}


void NOVAembed::on_P_SD3_CLK_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "SD3_CLK")
        set_sd3_4_SD_helper();

    if ( arg1 == "FLEXCAN1_RX")
    {
        ui->P_SD3_CLK_comboBox->setCurrentText("FLEXCAN1_TX");
        set_sd3_4L_IO_helper();
    }
    if ( arg1 == "UART2_RTS_B")
    {
        ui->P_SD3_DATA4_comboBox->setCurrentText("UART2_RX_DATA");
        ui->P_SD3_DATA5_comboBox->setCurrentText("UART2_TX_DATA");
        ui->P_SD3_CMD_comboBox->setCurrentText("UART2_CTS_B");
        set_sd3_4L_IO_helper();
    }
    if ( arg1 == "GPIO7_IO03")
    {
        ui->P_SD3_CLK_comboBox->setCurrentText("GPIO7_IO03");
        if ( ui->P_SD3_CMD_comboBox->currentText() == "FLEXCAN1_TX")
            ui->P_SD3_CMD_comboBox->setCurrentText("GPIO7_IO02");
        set_sd3_4L_IO_helper();
    }
}

void NOVAembed::on_P_SD3_DATA0_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "SD3_DATA0")
        set_sd3_4_SD_helper();

    if ( arg1 == "FLEXCAN2_TX")
    {
        ui->P_SD3_DATA0_comboBox->setCurrentText("FLEXCAN2_TX");
        ui->P_SD3_DATA1_comboBox->setCurrentText("FLEXCAN2_RX");
        set_sd3_4L_IO_helper();
    }
    if ( arg1 == "GPIO7_IO04")
    {
        set_sd3_4L_IO_helper();
    }
}

void NOVAembed::on_P_SD3_DATA1_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "SD3_DATA1")
        set_sd3_4_SD_helper();
    if ( arg1 == "GPIO7_IO05")
    {
        ui->P_SD3_DATA1_comboBox->setCurrentText("GPIO7_IO05");
        set_sd3_4L_IO_helper();
    }
    if ( arg1 == "FLEXCAN2_RX")
    {
        ui->P_SD3_DATA0_comboBox->setCurrentText("FLEXCAN2_TX");
        ui->P_SD3_DATA1_comboBox->setCurrentText("FLEXCAN2_RX");
        set_sd3_4L_IO_helper();
    }
}

void NOVAembed::on_P_SD3_DATA2_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "SD3_DATA2")
        set_sd3_4_SD_helper();
    if ( arg1 == "GPIO7_IO06")
    {
        ui->P_SD3_DATA2_comboBox->setCurrentText("GPIO7_IO06");
        set_sd3_4L_IO_helper();
    }
}

void NOVAembed::on_P_SD3_DATA3_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "SD3_DATA3")
        set_sd3_4_SD_helper();
    if ( arg1 == "GPIO7_IO07")
    {
        ui->P_SD3_DATA3_comboBox->setCurrentText("GPIO7_IO07");
        set_sd3_4L_IO_helper();
    }
}

void NOVAembed::on_P_SD3_DATA4_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "SD3_DATA4")
        set_sd3_8_SD_helper();
    if ( arg1 == "GPIO7_IO01")
    {
        ui->P_SD3_DATA4_comboBox->setCurrentText("GPIO7_IO01");
        set_sd3_8_IO_helper();
    }
    if ( arg1 == "UART2_RX_DATA")
    {
        ui->P_SD3_DATA4_comboBox->setCurrentText("UART2_RX_DATA");
        ui->P_SD3_DATA5_comboBox->setCurrentText("UART2_TX_DATA");
        ui->P_SD3_CMD_comboBox->setCurrentText("UART2_CTS_B");
        ui->P_SD3_CLK_comboBox->setCurrentText("UART2_RTS_B");
        set_sd3_8_IO_helper();
    }
}

void NOVAembed::on_P_SD3_DATA5_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "SD3_DATA5")
        set_sd3_8_SD_helper();
    if ( arg1 == "GPIO7_IO00")
    {
        ui->P_SD3_DATA5_comboBox->setCurrentText("GPIO7_IO00");
        set_sd3_8_IO_helper();
    }
    if ( arg1 == "UART2_TX_DATA")
    {
        ui->P_SD3_DATA4_comboBox->setCurrentText("UART2_RX_DATA");
        ui->P_SD3_DATA5_comboBox->setCurrentText("UART2_TX_DATA");
        ui->P_SD3_CMD_comboBox->setCurrentText("UART2_CTS_B");
        ui->P_SD3_CLK_comboBox->setCurrentText("UART2_RTS_B");
        set_sd3_8_IO_helper();
    }
}



void NOVAembed::on_P_SD3_DATA6_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "SD3_DATA6")
        set_sd3_8_SD_helper();
    if ( arg1 == "GPIO6_IO18")
    {
        ui->P_SD3_DATA6_comboBox->setCurrentText("GPIO6_IO18");
        set_sd3_8_IO_helper();
    }
}

void NOVAembed::on_P_SD3_DATA7_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "SD3_DATA7")
        set_sd3_8_SD_helper();
    if ( arg1 == "GPIO6_IO17")
    {
        ui->P_SD3_DATA7_comboBox->setCurrentText("GPIO6_IO17");
        set_sd3_8_IO_helper();
    }
}
/* J13 END */
/* J9 */

void NOVAembed::on_P_GPIO3_IO20_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "GPIO3_IO20")
        ui->P_GPIO3_IO20_comboBox->setCurrentText("GPIO3_IO20");
    if ( arg1 == "XTALOSC_REF_CLK_24M")
        ui->P_GPIO3_IO20_comboBox->setCurrentText("XTALOSC_REF_CLK_24M");

}

void NOVAembed::on_P_GPIO1_IO00_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "GPIO1_IO00_")
        ui->P_GPIO1_IO00_comboBox->setCurrentText("GPIO1_IO00");
    if ( arg1 == "CCM_CLKO1")
        ui->P_GPIO1_IO00_comboBox->setCurrentText("CCM_CLKO1");
    if ( arg1 == "EPIT1_OUT")
        ui->P_GPIO1_IO00_comboBox->setCurrentText("EPIT1_OUT");
}


void NOVAembed::on_P_GPIO4_IO29_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "GPIO4_IO29")
        ui->P_GPIO4_IO29_comboBox->setCurrentText("GPIO4_IO29");
    if ( arg1 == "PWM1_OUT")
        ui->P_GPIO4_IO29_comboBox->setCurrentText("PWM1_OUT");
    if ( arg1 == "WDOG1_B")
        ui->P_GPIO4_IO29_comboBox->setCurrentText("WDOG1_B");
}

void NOVAembed::setAUD6_AUDIO(void)
{
    ui->P_AUD6_TXD_comboBox->setCurrentText("AUD6_TXD");
    ui->P_AUD6_RXD_comboBox->setCurrentText("AUD6_RXD");
    ui->P_AUD6_TXFS_comboBox->setCurrentText("AUD6_TXFS");
    ui->P_AUD6_TXC_comboBox->setCurrentText("AUD6_TXC");
}

void NOVAembed::setAUD6_IO(void)
{
    ui->P_AUD6_TXD_comboBox->setCurrentText("GPIO4_IO18");
    ui->P_AUD6_RXD_comboBox->setCurrentText("GPIO4_IO20");
    ui->P_AUD6_TXFS_comboBox->setCurrentText("GPIO4_IO19");
    ui->P_AUD6_TXC_comboBox->setCurrentText("GPIO4_IO17");
}

void NOVAembed::on_P_AUD6_TXD_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "AUD6_TXD")
        setAUD6_AUDIO();
    if ( arg1 == "GPIO4_IO18")
        setAUD6_IO();
}


void NOVAembed::on_P_AUD6_RXD_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "AUD6_RXD")
        setAUD6_AUDIO();

    if ( arg1 == "GPIO4_IO20")
        setAUD6_IO();
}

void NOVAembed::on_P_AUD6_TXFS_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "AUD6_TXFS")
        setAUD6_AUDIO();
    if ( arg1 == "GPIO4_IO19")
        setAUD6_IO();
}


void NOVAembed::on_P_AUD6_TXC_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "AUD6_TXC")
        setAUD6_AUDIO();
    if ( arg1 == "GPIO4_IO17")
        setAUD6_IO();
}



void NOVAembed::on_P_I2C1_SDA_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "I2C1_SDA")
    {
        ui->P_I2C1_SDA_comboBox->setCurrentText("I2C1_SDA");
        ui->P_I2C1_SCL_comboBox->setCurrentText("I2C1_SCL");
        /* P_ECSPI4_MOSI_comboBox become GPIO3_IO28 */
        /* P_ECSPI4_SCK_comboBox become GPIO3_IO21 */
        if (ui->P_ECSPI4_MOSI_comboBox->currentText()=="I2C1_SDA" )
        {
            ui->P_ECSPI4_MOSI_comboBox->setCurrentText("GPIO3_IO28");
            ui->P_ECSPI4_SCK_comboBox->setCurrentText("GPIO3_IO21");
        }
    }
    if ( arg1 == "GPIO5_IO26")
    {
        ui->P_I2C1_SDA_comboBox->setCurrentText("GPIO5_IO26");
        ui->P_I2C1_SCL_comboBox->setCurrentText("GPIO5_IO27");
    }
}


void NOVAembed::on_P_I2C1_SCL_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "I2C1_SCL")
    {
        ui->P_I2C1_SDA_comboBox->setCurrentText("I2C1_SDA");
        ui->P_I2C1_SCL_comboBox->setCurrentText("I2C1_SCL");
    }
    if ( arg1 == "GPIO5_IO27")
    {
        ui->P_I2C1_SDA_comboBox->setCurrentText("GPIO5_IO26");
        ui->P_I2C1_SCL_comboBox->setCurrentText("GPIO5_IO27");
    }
}


void NOVAembed::on_P_UART1_TXD_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "UART1_TXD")
    {
        ui->P_UART1_TXD_comboBox->setCurrentText("UART1_TXD");
        ui->P_UART1_RXD_comboBox->setCurrentText("UART1_RXD");
    }
    if ( arg1 == "GPIO5_IO28")
    {
        ui->P_UART1_TXD_comboBox->setCurrentText("GPIO5_IO28");
        ui->P_UART1_RXD_comboBox->setCurrentText("GPIO5_IO29");
    }
}


void NOVAembed::on_P_UART1_RXD_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "UART1_RXD")
    {
        ui->P_UART1_TXD_comboBox->setCurrentText("UART1_TXD");
        ui->P_UART1_RXD_comboBox->setCurrentText("UART1_RXD");
    }
    if ( arg1 == "GPIO5_IO29")
    {
        ui->P_UART1_TXD_comboBox->setCurrentText("GPIO5_IO28");
        ui->P_UART1_RXD_comboBox->setCurrentText("GPIO5_IO29");
    }
}

void NOVAembed::on_P_SPDIF_OUT_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "SPDIF_OUT")
    {
        ui->P_SPDIF_OUT_comboBox->setCurrentText("SPDIF_OUT");
        if ( ui->P_ECSPI4_MISO_comboBox->currentText() == "SPDIF_OUT")
            ui->P_ECSPI4_MISO_comboBox->setCurrentText("GPIO3_IO22");
    }
    if ( arg1 == "GPIO7_IO12")
    {
        ui->P_SPDIF_OUT_comboBox->setCurrentText("GPIO7_IO12");
    }
}

void NOVAembed::on_P_UART4_TXD_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "UART4_TXD")
    {
        ui->P_UART4_TXD_comboBox->setCurrentText("UART4_TXD");
        ui->P_UART4_RXD_comboBox->setCurrentText("UART4_RXD");
        ui->P_UART4_RTS_L_comboBox->setCurrentText("UART4_RTS_L");
        ui->P_UART4_CTS_L_comboBox->setCurrentText("UART4_CTS_L");
    }
    if ( arg1 == "GPIO5_IO30")
    {
        ui->P_UART4_TXD_comboBox->setCurrentText("GPIO5_IO30");
        ui->P_UART4_RXD_comboBox->setCurrentText("GPIO5_IO31");
        ui->P_UART4_RTS_L_comboBox->setCurrentText("GPIO6_IO02");
        ui->P_UART4_CTS_L_comboBox->setCurrentText("GPIO6_IO03");
    }
}


void NOVAembed::on_P_UART4_RXD_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "UART4_RXD")
    {
        ui->P_UART4_TXD_comboBox->setCurrentText("UART4_TXD");
        ui->P_UART4_RXD_comboBox->setCurrentText("UART4_RXD");
        ui->P_UART4_RTS_L_comboBox->setCurrentText("UART4_RTS_L");
        ui->P_UART4_CTS_L_comboBox->setCurrentText("UART4_CTS_L");
    }
    if ( arg1 == "GPIO5_IO31")
    {
        ui->P_UART4_TXD_comboBox->setCurrentText("GPIO5_IO30");
        ui->P_UART4_RXD_comboBox->setCurrentText("GPIO5_IO31");
        ui->P_UART4_RTS_L_comboBox->setCurrentText("GPIO6_IO02");
        ui->P_UART4_CTS_L_comboBox->setCurrentText("GPIO6_IO03");
    }
}

void NOVAembed::on_P_UART4_RTS_L_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "UART4_RTS_L")
    {
        ui->P_UART4_TXD_comboBox->setCurrentText("UART4_TXD");
        ui->P_UART4_RXD_comboBox->setCurrentText("UART4_RXD");
        ui->P_UART4_RTS_L_comboBox->setCurrentText("UART4_RTS_L");
        ui->P_UART4_CTS_L_comboBox->setCurrentText("UART4_CTS_L");
    }
    if ( arg1 == "GPIO6_IO02")
    {
        ui->P_UART4_RTS_L_comboBox->setCurrentText("GPIO6_IO02");
        ui->P_UART4_CTS_L_comboBox->setCurrentText("GPIO6_IO03");
    }
}


void NOVAembed::on_P_UART4_CTS_L_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == "UART4_CTS_L")
    {
        ui->P_UART4_TXD_comboBox->setCurrentText("UART4_TXD");
        ui->P_UART4_RXD_comboBox->setCurrentText("UART4_RXD");
        ui->P_UART4_RTS_L_comboBox->setCurrentText("UART4_RTS_L");
        ui->P_UART4_CTS_L_comboBox->setCurrentText("UART4_CTS_L");
    }
    if ( arg1 == "GPIO6_IO03")
    {
        ui->P_UART4_RTS_L_comboBox->setCurrentText("GPIO6_IO02");
        ui->P_UART4_CTS_L_comboBox->setCurrentText("GPIO6_IO03");
    }
}

/* J9 END */

void NOVAembed::save_helper(QString fileName)
{
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
        //qDebug() << "fileName :"+fileName;

        QTextStream out(&file);
        out << QString("[P_IOMUX]\n");
        out << QString("P_ECSPI1_MISO_comboBox="+ui->P_ECSPI1_MISO_comboBox->currentText()+"\n");
        out << QString("P_ECSPI1_MOSI_comboBox="+ui->P_ECSPI1_MOSI_comboBox->currentText()+"\n");
        out << QString("P_ECSPI1_SS0_comboBox="+ui->P_ECSPI1_SS0_comboBox->currentText()+"\n");
        out << QString("P_ECSPI1_SCK_comboBox="+ui->P_ECSPI1_SCK_comboBox->currentText()+"\n");
        out << QString("P_ECSPI2_SS0_comboBox="+ui->P_ECSPI2_SS0_comboBox->currentText()+"\n");
        out << QString("P_ECSPI2_SS1_comboBox="+ui->P_ECSPI2_SS1_comboBox->currentText()+"\n");
        out << QString("P_ECSPI2_MISO_comboBox="+ui->P_ECSPI2_MISO_comboBox->currentText()+"\n");
        out << QString("P_ECSPI2_MOSI_comboBox="+ui->P_ECSPI2_MOSI_comboBox->currentText()+"\n");
        out << QString("P_ECSPI2_SCK_comboBox="+ui->P_ECSPI2_SCK_comboBox->currentText()+"\n");
        out << QString("P_ECSPI3_MISO_comboBox="+ui->P_ECSPI3_MISO_comboBox->currentText()+"\n");
        out << QString("P_ECSPI3_SCK_comboBox="+ui->P_ECSPI3_SCK_comboBox->currentText()+"\n");
        out << QString("P_ECSPI3_MOSI_comboBox="+ui->P_ECSPI3_MOSI_comboBox->currentText()+"\n");
        out << QString("P_ECSPI3_SS0_comboBox="+ui->P_ECSPI3_SS0_comboBox->currentText()+"\n");
        out << QString("P_ECSPI3_SS1_comboBox="+ui->P_ECSPI3_SS1_comboBox->currentText()+"\n");
        out << QString("P_ECSPI4_MISO_comboBox="+ui->P_ECSPI4_MISO_comboBox->currentText()+"\n");
        out << QString("P_ECSPI4_MOSI_comboBox="+ui->P_ECSPI4_MOSI_comboBox->currentText()+"\n");
        out << QString("P_ECSPI4_SCK_comboBox="+ui->P_ECSPI4_SCK_comboBox->currentText()+"\n");
        out << QString("P_ECSPI4_SS0_comboBox="+ui->P_ECSPI4_SS0_comboBox->currentText()+"\n");
        out << QString("P_I2C3_SCL_comboBox="+ui->P_I2C3_SCL_comboBox->currentText()+"\n");
        out << QString("P_I2C3_SDA_comboBox="+ui->P_I2C3_SDA_comboBox->currentText()+"\n");
        out << QString("P_KHZ32_CLK_OUT_comboBox="+ui->P_KHZ32_CLK_OUT_comboBox->currentText()+"\n");
        out << QString("P_SD3_CMD_comboBox="+ui->P_SD3_CMD_comboBox->currentText()+"\n");
        out << QString("P_SD3_CLK_comboBox="+ui->P_SD3_CLK_comboBox->currentText()+"\n");
        out << QString("P_SD3_DATA0_comboBox="+ui->P_SD3_DATA0_comboBox->currentText()+"\n");
        out << QString("P_SD3_DATA1_comboBox="+ui->P_SD3_DATA1_comboBox->currentText()+"\n");
        out << QString("P_SD3_DATA2_comboBox="+ui->P_SD3_DATA2_comboBox->currentText()+"\n");
        out << QString("P_SD3_DATA3_comboBox="+ui->P_SD3_DATA3_comboBox->currentText()+"\n");
        out << QString("P_SD3_DATA4_comboBox="+ui->P_SD3_DATA4_comboBox->currentText()+"\n");
        out << QString("P_SD3_DATA5_comboBox="+ui->P_SD3_DATA5_comboBox->currentText()+"\n");
        out << QString("P_SD3_DATA6_comboBox="+ui->P_SD3_DATA6_comboBox->currentText()+"\n");
        out << QString("P_SD3_DATA7_comboBox="+ui->P_SD3_DATA7_comboBox->currentText()+"\n");
        out << QString("P_GPIO3_IO20_comboBox="+ui->P_GPIO3_IO20_comboBox->currentText()+"\n");
        out << QString("P_GPIO1_IO00_comboBox="+ui->P_GPIO1_IO00_comboBox->currentText()+"\n");
        out << QString("P_GPIO4_IO29_comboBox="+ui->P_GPIO4_IO29_comboBox->currentText()+"\n");
        out << QString("P_AUD6_TXD_comboBox="+ui->P_AUD6_TXD_comboBox->currentText()+"\n");
        out << QString("P_AUD6_RXD_comboBox="+ui->P_AUD6_RXD_comboBox->currentText()+"\n");
        out << QString("P_AUD6_TXFS_comboBox="+ui->P_AUD6_TXFS_comboBox->currentText()+"\n");
        out << QString("P_AUD6_TXC_comboBox="+ui->P_AUD6_TXC_comboBox->currentText()+"\n");
        out << QString("P_I2C1_SDA_comboBox="+ui->P_I2C1_SDA_comboBox->currentText()+"\n");
        out << QString("P_I2C1_SCL_comboBox="+ui->P_I2C1_SCL_comboBox->currentText()+"\n");
        out << QString("P_UART1_TXD_comboBox="+ui->P_UART1_TXD_comboBox->currentText()+"\n");
        out << QString("P_UART1_RXD_comboBox="+ui->P_UART1_RXD_comboBox->currentText()+"\n");
        out << QString("P_SPDIF_OUT_comboBox="+ui->P_SPDIF_OUT_comboBox->currentText()+"\n");
        out << QString("P_UART4_RTS_L_comboBox="+ui->P_UART4_RTS_L_comboBox->currentText()+"\n");
        out << QString("P_UART4_TXD_comboBox="+ui->P_UART4_TXD_comboBox->currentText()+"\n");
        out << QString("P_UART4_RXD_comboBox="+ui->P_UART4_RXD_comboBox->currentText()+"\n");
        out << QString("P_UART4_CTS_L_comboBox="+ui->P_UART4_CTS_L_comboBox->currentText()+"\n");
        out << QString("P_I2C1Speed="+ui->P_I2C1Speed_lineEdit->text()+"\n");
        out << QString("P_I2C3Speed="+ui->P_I2C3Speed_lineEdit->text()+"\n");
        if ( ui->P_SATA_checkBox->isChecked() )
            out << QString("P_SATA_checkBox=true\n");
        else
            out << QString("P_SATA_checkBox=false\n");
        if ( ui->P_PCIe_checkBox->isChecked())
            out << QString("P_PCIe_checkBox=true\n");
        else
            out << QString("P_PCIe_checkBox=false\n");
        out << QString("PrimaryVideo_comboBox="+ui->P_PrimaryVideo_comboBox->currentText()+"\n");
        out << QString("SecondaryVideo_comboBox="+ui->P_SecondaryVideo_comboBox->currentText()+"\n");
        if ( Quad == "true")
            out << QString("Processor=QUAD\n");
        else
            out << QString("Processor=SOLO/DL\n");

        out << QString("\n[P_CONF]\n");
        out << QString("P_ECSPI1_MISO_cbit="+ui->P_ECSPI1_MISO_lineEdit->text()+"\n");
        out << QString("P_ECSPI1_MOSI_cbit="+ui->P_ECSPI1_MOSI_lineEdit->text()+"\n");
        out << QString("P_ECSPI1_SS0_cbit="+ui->P_ECSPI1_SS0_lineEdit->text()+"\n");
        out << QString("P_ECSPI1_SCK_cbit="+ui->P_ECSPI1_SCK_lineEdit->text()+"\n");
        out << QString("P_ECSPI2_SS0_cbit="+ui->P_ECSPI2_SS0_lineEdit->text()+"\n");
        out << QString("P_ECSPI2_SS1_cbit="+ui->P_ECSPI2_SS1_lineEdit->text()+"\n");
        out << QString("P_ECSPI2_MISO_cbit="+ui->P_ECSPI2_MISO_lineEdit->text()+"\n");
        out << QString("P_ECSPI2_MOSI_cbit="+ui->P_ECSPI2_MOSI_lineEdit->text()+"\n");
        out << QString("P_ECSPI2_SCK_cbit="+ui->P_ECSPI2_SCK_lineEdit->text()+"\n");
        out << QString("P_ECSPI3_MISO_cbit="+ui->P_ECSPI3_MISO_lineEdit->text()+"\n");
        out << QString("P_ECSPI3_SCK_cbit="+ui->P_ECSPI3_SCK_lineEdit->text()+"\n");
        out << QString("P_ECSPI3_MOSI_cbit="+ui->P_ECSPI3_MOSI_lineEdit->text()+"\n");
        out << QString("P_ECSPI3_SS0_cbit="+ui->P_ECSPI3_SS0_lineEdit->text()+"\n");
        out << QString("P_ECSPI3_SS1_cbit="+ui->P_ECSPI3_SS1_lineEdit->text()+"\n");
        out << QString("P_ECSPI4_MISO_cbit="+ui->P_ECSPI4_MISO_lineEdit->text()+"\n");
        out << QString("P_ECSPI4_MOSI_cbit="+ui->P_ECSPI4_MOSI_lineEdit->text()+"\n");
        out << QString("P_ECSPI4_SCK_cbit="+ui->P_ECSPI4_SCK_lineEdit->text()+"\n");
        out << QString("P_ECSPI4_SS0_cbit="+ui->P_ECSPI4_SS0_lineEdit->text()+"\n");
        out << QString("P_I2C3_SCL_cbit="+ui->P_I2C3_SCL_lineEdit->text()+"\n");
        out << QString("P_I2C3_SDA_cbit="+ui->P_I2C3_SDA_lineEdit->text()+"\n");
        out << QString("P_KHZ32_CLK_OUT_cbit="+ui->P_KHZ32_CLK_OUT_lineEdit->text()+"\n");
        out << QString("P_SD3_CMD_cbit="+ui->P_SD3_CMD_lineEdit->text()+"\n");
        out << QString("P_SD3_CLK_cbit="+ui->P_SD3_CLK_lineEdit->text()+"\n");
        out << QString("P_SD3_DATA0_cbit="+ui->P_SD3_DATA0_lineEdit->text()+"\n");
        out << QString("P_SD3_DATA1_cbit="+ui->P_SD3_DATA1_lineEdit->text()+"\n");
        out << QString("P_SD3_DATA2_cbit="+ui->P_SD3_DATA2_lineEdit->text()+"\n");
        out << QString("P_SD3_DATA3_cbit="+ui->P_SD3_DATA3_lineEdit->text()+"\n");
        out << QString("P_SD3_DATA4_cbit="+ui->P_SD3_DATA4_lineEdit->text()+"\n");
        out << QString("P_SD3_DATA5_cbit="+ui->P_SD3_DATA5_lineEdit->text()+"\n");
        out << QString("P_SD3_DATA6_cbit="+ui->P_SD3_DATA6_lineEdit->text()+"\n");
        out << QString("P_SD3_DATA7_cbit="+ui->P_SD3_DATA7_lineEdit->text()+"\n");
        out << QString("P_GPIO3_IO19_cbit="+ui->P_GPIO3_IO19_lineEdit->text()+"\n");
        out << QString("P_GPIO3_IO20_cbit="+ui->P_GPIO3_IO20_lineEdit->text()+"\n");
        out << QString("P_GPIO1_IO00_cbit="+ui->P_GPIO1_IO00_lineEdit->text()+"\n");
        out << QString("P_GPIO4_IO14_cbit="+ui->P_GPIO4_IO14_lineEdit->text()+"\n");
        out << QString("P_GPIO4_IO26_cbit="+ui->P_GPIO4_IO26_lineEdit->text()+"\n");
        out << QString("P_GPIO4_IO27_cbit="+ui->P_GPIO4_IO27_lineEdit->text()+"\n");
        out << QString("P_GPIO4_IO28_cbit="+ui->P_GPIO4_IO28_lineEdit->text()+"\n");
        out << QString("P_GPIO4_IO29_cbit="+ui->P_GPIO4_IO29_lineEdit->text()+"\n");
        out << QString("P_GPIO6_IO05_cbit="+ui->P_GPIO6_IO05_lineEdit->text()+"\n");
        out << QString("P_AUD6_TXD_cbit="+ui->P_AUD6_TXD_lineEdit->text()+"\n");
        out << QString("P_AUD6_RXD_cbit="+ui->P_AUD6_RXD_lineEdit->text()+"\n");
        out << QString("P_AUD6_TXFS_cbit="+ui->P_AUD6_TXFS_lineEdit->text()+"\n");
        out << QString("P_AUD6_TXC_cbit="+ui->P_AUD6_TXC_lineEdit->text()+"\n");
        out << QString("P_I2C1_SDA_cbit="+ui->P_I2C1_SDA_lineEdit->text()+"\n");
        out << QString("P_I2C1_SCL_cbit="+ui->P_I2C1_SCL_lineEdit->text()+"\n");
        out << QString("P_UART1_TXD_cbit="+ui->P_UART1_TXD_lineEdit->text()+"\n");
        out << QString("P_UART1_RXD_cbit="+ui->P_UART1_RXD_lineEdit->text()+"\n");
        out << QString("P_SPDIF_OUT_cbit="+ui->P_SPDIF_OUT_lineEdit->text()+"\n");
        out << QString("P_UART4_RTS_L_cbit="+ui->P_UART4_RTS_L_lineEdit->text()+"\n");
        out << QString("P_UART4_TXD_cbit="+ui->P_UART4_TXD_lineEdit->text()+"\n");
        out << QString("P_UART4_RXD_cbit="+ui->P_UART4_RXD_lineEdit->text()+"\n");
        out << QString("P_UART4_CTS_L_cbit="+ui->P_UART4_CTS_L_lineEdit->text()+"\n");

        file.close();
        Last_P_BSPFactoryFile = fileName;
        QFileInfo fi(Last_P_BSPFactoryFile);
        QString base = fi.baseName();
        if ( base != "" )
        {
            FileNameNoExtension = base;
            ui->P_Current_BSPF_File_label->setText(base+".bspf");
        }
        storeNOVAembed_ini();
    }
}

void NOVAembed::on_P_Save_pushButton_clicked()
{
    QString croped_fileName = QFileDialog::getSaveFileName(this,tr("Save .bspf"), "/Devel/NOVAsom_SDK/DtbUserWorkArea/PClass_bspf",tr(".bspf (*.bspf)"));
    QString fileName=croped_fileName.section(".",0,0);
    fileName = fileName+".bspf";
    //qDebug() << "fileName :"+fileName;
    save_helper(fileName);
}



void NOVAembed::on_P_SetCFGbits_pushButton_clicked()
{
    CfgBitDefaultValue = ui->P_Default_lineEdit->text();
    ui->P_ECSPI1_MISO_lineEdit->setText(CfgBitDefaultValue);
    ui->P_ECSPI1_MOSI_lineEdit->setText(CfgBitDefaultValue);
    ui->P_ECSPI1_SS0_lineEdit->setText(CfgBitDefaultValue);
    ui->P_ECSPI1_SCK_lineEdit->setText(CfgBitDefaultValue);
    ui->P_ECSPI2_SS0_lineEdit->setText(CfgBitDefaultValue);
    ui->P_ECSPI2_SS1_lineEdit->setText(CfgBitDefaultValue);
    ui->P_ECSPI2_MISO_lineEdit->setText(CfgBitDefaultValue);
    ui->P_ECSPI2_MOSI_lineEdit->setText(CfgBitDefaultValue);
    ui->P_ECSPI2_SCK_lineEdit->setText(CfgBitDefaultValue);
    ui->P_ECSPI3_MISO_lineEdit->setText(CfgBitDefaultValue);
    ui->P_ECSPI3_SCK_lineEdit->setText(CfgBitDefaultValue);
    ui->P_ECSPI3_MOSI_lineEdit->setText(CfgBitDefaultValue);
    ui->P_ECSPI3_SS0_lineEdit->setText(CfgBitDefaultValue);
    ui->P_ECSPI3_SS1_lineEdit->setText(CfgBitDefaultValue);
    ui->P_ECSPI4_MISO_lineEdit->setText(CfgBitDefaultValue);
    ui->P_ECSPI4_MOSI_lineEdit->setText(CfgBitDefaultValue);
    ui->P_ECSPI4_SCK_lineEdit->setText(CfgBitDefaultValue);
    ui->P_ECSPI4_SS0_lineEdit->setText(CfgBitDefaultValue);
    ui->P_I2C3_SCL_lineEdit->setText(CfgBitDefaultValue);
    ui->P_I2C3_SDA_lineEdit->setText(CfgBitDefaultValue);
    ui->P_KHZ32_CLK_OUT_lineEdit->setText(CfgBitDefaultValue);
    ui->P_SD3_CMD_lineEdit->setText(CfgBitDefaultValue);
    ui->P_SD3_CLK_lineEdit->setText(CfgBitDefaultValue);
    ui->P_SD3_DATA0_lineEdit->setText(CfgBitDefaultValue);
    ui->P_SD3_DATA1_lineEdit->setText(CfgBitDefaultValue);
    ui->P_SD3_DATA2_lineEdit->setText(CfgBitDefaultValue);
    ui->P_SD3_DATA3_lineEdit->setText(CfgBitDefaultValue);
    ui->P_SD3_DATA4_lineEdit->setText(CfgBitDefaultValue);
    ui->P_SD3_DATA5_lineEdit->setText(CfgBitDefaultValue);
    ui->P_SD3_DATA6_lineEdit->setText(CfgBitDefaultValue);
    ui->P_SD3_DATA7_lineEdit->setText(CfgBitDefaultValue);
    ui->P_GPIO3_IO19_lineEdit->setText(CfgBitDefaultValue);
    ui->P_GPIO3_IO20_lineEdit->setText(CfgBitDefaultValue);
    ui->P_GPIO1_IO00_lineEdit->setText(CfgBitDefaultValue);
    ui->P_GPIO4_IO14_lineEdit->setText(CfgBitDefaultValue);
    ui->P_GPIO4_IO26_lineEdit->setText(CfgBitDefaultValue);
    ui->P_GPIO4_IO27_lineEdit->setText(CfgBitDefaultValue);
    ui->P_GPIO4_IO28_lineEdit->setText(CfgBitDefaultValue);
    ui->P_GPIO4_IO29_lineEdit->setText(CfgBitDefaultValue);
    ui->P_GPIO6_IO05_lineEdit->setText(CfgBitDefaultValue);
    ui->P_AUD6_TXD_lineEdit->setText(CfgBitDefaultValue);
    ui->P_AUD6_RXD_lineEdit->setText(CfgBitDefaultValue);
    ui->P_AUD6_TXFS_lineEdit->setText(CfgBitDefaultValue);
    ui->P_AUD6_TXC_lineEdit->setText(CfgBitDefaultValue);
    ui->P_I2C1_SDA_lineEdit->setText(CfgBitDefaultValue);
    ui->P_I2C1_SCL_lineEdit->setText(CfgBitDefaultValue);
    ui->P_UART1_TXD_lineEdit->setText(CfgBitDefaultValue);
    ui->P_UART1_RXD_lineEdit->setText(CfgBitDefaultValue);
    ui->P_SPDIF_OUT_lineEdit->setText(CfgBitDefaultValue);
    ui->P_UART4_RTS_L_lineEdit->setText(CfgBitDefaultValue);
    ui->P_UART4_TXD_lineEdit->setText(CfgBitDefaultValue);
    ui->P_UART4_RXD_lineEdit->setText(CfgBitDefaultValue);
    ui->P_UART4_CTS_L_lineEdit->setText(CfgBitDefaultValue);

    storeNOVAembed_ini();
}

void NOVAembed::on_P_Default_pushButton_clicked()
{
    ui->P_ECSPI1_MISO_comboBox->setCurrentIndex(0);
    ui->P_ECSPI1_MOSI_comboBox->setCurrentIndex(0);
    ui->P_ECSPI1_SS0_comboBox->setCurrentIndex(0);
    ui->P_ECSPI1_SCK_comboBox->setCurrentIndex(0);
    ui->P_ECSPI2_SS0_comboBox->setCurrentIndex(0);
    ui->P_ECSPI2_SS1_comboBox->setCurrentIndex(0);
    ui->P_ECSPI2_MISO_comboBox->setCurrentIndex(0);
    ui->P_ECSPI2_MOSI_comboBox->setCurrentIndex(0);
    ui->P_ECSPI2_SCK_comboBox->setCurrentIndex(0);
    ui->P_ECSPI3_MISO_comboBox->setCurrentIndex(0);
    ui->P_ECSPI3_SCK_comboBox->setCurrentIndex(0);
    ui->P_ECSPI3_MOSI_comboBox->setCurrentIndex(0);
    ui->P_ECSPI3_SS0_comboBox->setCurrentIndex(0);
    ui->P_ECSPI3_SS1_comboBox->setCurrentIndex(0);
    ui->P_ECSPI4_MISO_comboBox->setCurrentIndex(0);
    ui->P_ECSPI4_MOSI_comboBox->setCurrentIndex(0);
    ui->P_ECSPI4_SCK_comboBox->setCurrentIndex(0);
    ui->P_ECSPI4_SS0_comboBox->setCurrentIndex(0);
    ui->P_I2C3_SCL_comboBox->setCurrentIndex(0);
    ui->P_I2C3_SDA_comboBox->setCurrentIndex(0);//
    ui->P_KHZ32_CLK_OUT_comboBox->setCurrentIndex(0);
    ui->P_SD3_CMD_comboBox->setCurrentIndex(0);
    ui->P_SD3_CLK_comboBox->setCurrentIndex(0);
    ui->P_SD3_DATA0_comboBox->setCurrentIndex(0);
    ui->P_SD3_DATA1_comboBox->setCurrentIndex(0);
    ui->P_SD3_DATA2_comboBox->setCurrentIndex(0);
    ui->P_SD3_DATA3_comboBox->setCurrentIndex(0);
    ui->P_SD3_DATA4_comboBox->setCurrentIndex(0);
    ui->P_SD3_DATA5_comboBox->setCurrentIndex(0);
    ui->P_SD3_DATA6_comboBox->setCurrentIndex(0);
    ui->P_SD3_DATA7_comboBox->setCurrentIndex(0);
    ui->P_GPIO3_IO20_comboBox->setCurrentIndex(0);
    ui->P_GPIO1_IO00_comboBox->setCurrentIndex(0);
    ui->P_GPIO4_IO29_comboBox->setCurrentIndex(0);
    ui->P_AUD6_TXD_comboBox->setCurrentIndex(0);
    ui->P_AUD6_RXD_comboBox->setCurrentIndex(0);
    ui->P_AUD6_TXFS_comboBox->setCurrentIndex(0);
    ui->P_AUD6_TXC_comboBox->setCurrentIndex(0);
    ui->P_I2C1_SDA_comboBox->setCurrentIndex(0);
    ui->P_I2C1_SCL_comboBox->setCurrentIndex(0);
    ui->P_UART1_TXD_comboBox->setCurrentIndex(0);
    ui->P_UART1_RXD_comboBox->setCurrentIndex(0);
    ui->P_SPDIF_OUT_comboBox->setCurrentIndex(0);
    ui->P_UART4_RTS_L_comboBox->setCurrentIndex(0);
    ui->P_UART4_TXD_comboBox->setCurrentIndex(0);
    ui->P_UART4_RXD_comboBox->setCurrentIndex(0);
    ui->P_UART4_CTS_L_comboBox->setCurrentIndex(0);
    ui->P_SATA_checkBox->setChecked(false);
    ui->P_PCIe_checkBox->setChecked(true);
    ui->P_PrimaryVideo_comboBox->setCurrentIndex(0);
    ui->P_SecondaryVideo_comboBox->setCurrentIndex(0);
    ui->P_I2C1Speed_lineEdit->setText("100000");
    ui->P_I2C3Speed_lineEdit->setText("100000");
}

QString P_getvalue(QString strKey, QSettings *settings , QString entry)
{
    return settings->value( strKey + entry, "r").toString();
}

void NOVAembed::P_load_BSPF_File(QString fileName)
{
QString strKeyFunc("P_IOMUX/");
QSettings * func_settings = 0;

    QFileInfo fi(fileName);
    QString base = fi.baseName();
    if ( base != "" )
        ui->P_Current_BSPF_File_label->setText(base+".bspf");

    func_settings = new QSettings( fileName, QSettings::IniFormat );

    ui->P_ECSPI1_MISO_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_ECSPI1_MISO_comboBox"));
    ui->P_ECSPI1_MOSI_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_ECSPI1_MOSI_comboBox"));
    ui->P_ECSPI1_SS0_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_ECSPI1_SS0_comboBox"));
    ui->P_ECSPI1_SCK_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_ECSPI1_SCK_comboBox"));
    ui->P_ECSPI2_SS0_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_ECSPI2_SS0_comboBox"));
    ui->P_ECSPI2_SS1_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_ECSPI2_SS1_comboBox"));
    ui->P_ECSPI2_MISO_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_ECSPI2_MISO_comboBox"));
    ui->P_ECSPI2_MOSI_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_ECSPI2_MOSI_comboBox"));
    ui->P_ECSPI2_SCK_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_ECSPI2_SCK_comboBox"));
    ui->P_ECSPI3_MISO_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_ECSPI3_MISO_comboBox"));
    ui->P_ECSPI3_SCK_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_ECSPI3_SCK_comboBox"));
    ui->P_ECSPI3_MOSI_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_ECSPI3_MOSI_comboBox"));
    ui->P_ECSPI3_SS0_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_ECSPI3_SS0_comboBox"));
    ui->P_ECSPI3_SS1_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_ECSPI3_SS1_comboBox"));
    ui->P_ECSPI4_MISO_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_ECSPI4_MISO_comboBox"));
    ui->P_ECSPI4_MOSI_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_ECSPI4_MOSI_comboBox"));
    ui->P_ECSPI4_SCK_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_ECSPI4_SCK_comboBox"));
    ui->P_ECSPI4_SS0_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_ECSPI4_SS0_comboBox"));
    ui->P_I2C3_SCL_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_I2C3_SCL_comboBox"));
    ui->P_I2C3_SDA_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_I2C3_SDA_comboBox"));
    ui->P_KHZ32_CLK_OUT_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_SD3_CMD_comboBox"));
    ui->P_SD3_CMD_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_KHZ32_CLK_OUT_comboBox"));
    ui->P_SD3_CLK_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_SD3_CLK_comboBox"));
    ui->P_SD3_DATA0_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_SD3_DATA0_comboBox"));
    ui->P_SD3_DATA1_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_SD3_DATA1_comboBox"));
    ui->P_SD3_DATA2_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_SD3_DATA2_comboBox"));
    ui->P_SD3_DATA3_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_SD3_DATA3_comboBox"));
    ui->P_SD3_DATA4_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_SD3_DATA4_comboBox"));
    ui->P_SD3_DATA5_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_SD3_DATA5_comboBox"));
    ui->P_SD3_DATA6_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_SD3_DATA6_comboBox"));
    ui->P_SD3_DATA7_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_SD3_DATA7_comboBox"));
    ui->P_GPIO3_IO20_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_GPIO3_IO20_comboBox"));
    ui->P_GPIO1_IO00_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_GPIO1_IO00_comboBox"));
    ui->P_GPIO4_IO29_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_GPIO4_IO29_comboBox"));
    ui->P_AUD6_TXD_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_AUD6_TXD_comboBox"));
    ui->P_AUD6_RXD_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_AUD6_RXD_comboBox"));
    ui->P_AUD6_TXFS_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_AUD6_TXFS_comboBox"));
    ui->P_AUD6_TXC_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_AUD6_TXC_comboBox"));
    ui->P_I2C1_SDA_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_I2C1_SDA_comboBox"));
    ui->P_I2C1_SCL_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_I2C1_SCL_comboBox"));
    ui->P_UART1_TXD_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_UART1_TXD_comboBox"));
    ui->P_UART1_RXD_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_UART1_RXD_comboBox"));
    ui->P_SPDIF_OUT_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_SPDIF_OUT_comboBox"));
    ui->P_UART4_RTS_L_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_UART4_RTS_L_comboBox"));
    ui->P_UART4_TXD_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_UART4_TXD_comboBox"));
    ui->P_UART4_RXD_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_UART4_RXD_comboBox"));
    ui->P_UART4_CTS_L_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "P_UART4_CTS_L_comboBox"));
    if ( P_getvalue(strKeyFunc, func_settings , "P_SATA_checkBox") == "true")
        ui->P_SATA_checkBox->setChecked(true);
    else
        ui->P_SATA_checkBox->setChecked(false);
    if ( P_getvalue(strKeyFunc, func_settings , "P_PCIe_checkBox") == "true")
        ui->P_PCIe_checkBox->setChecked(true);
    else
        ui->P_PCIe_checkBox->setChecked(false);
    ui->P_PrimaryVideo_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "PrimaryVideo_comboBox"));
    ui->P_SecondaryVideo_comboBox->setCurrentText(P_getvalue(strKeyFunc, func_settings , "SecondaryVideo_comboBox"));
    ui->P_I2C1Speed_lineEdit->setText(P_getvalue(strKeyFunc, func_settings , "P_I2C1Speed"));
    ui->P_I2C3Speed_lineEdit->setText(P_getvalue(strKeyFunc, func_settings , "P_I2C3Speed"));


    QString strKeyConf("P_CONF/");
    QSettings * conf_settings = 0;
    conf_settings = new QSettings( fileName, QSettings::IniFormat );

    ui->P_ECSPI1_MISO_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_ECSPI1_MISO_cbit"));
    ui->P_ECSPI1_MOSI_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_ECSPI1_MOSI_cbit"));
    ui->P_ECSPI1_SS0_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_ECSPI1_SS0_cbit"));
    ui->P_ECSPI1_SCK_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_ECSPI1_SCK_cbit"));
    ui->P_ECSPI2_SS0_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_ECSPI2_SS0_cbit"));
    ui->P_ECSPI2_SS1_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_ECSPI2_SS1_cbit"));
    ui->P_ECSPI2_MISO_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_ECSPI2_MISO_cbit"));
    ui->P_ECSPI2_MOSI_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_ECSPI2_MOSI_cbit"));
    ui->P_ECSPI2_SCK_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_ECSPI2_SCK_cbit"));
    ui->P_ECSPI3_MISO_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_ECSPI3_MISO_cbit"));
    ui->P_ECSPI3_SCK_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_ECSPI3_SCK_cbit"));
    ui->P_ECSPI3_MOSI_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_ECSPI3_MOSI_cbit"));
    ui->P_ECSPI3_SS0_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_ECSPI3_SS0_cbit"));
    ui->P_ECSPI3_SS1_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_ECSPI3_SS1_cbit"));
    ui->P_ECSPI4_MISO_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_ECSPI4_MISO_cbit"));
    ui->P_ECSPI4_MOSI_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_ECSPI4_MOSI_cbit"));
    ui->P_ECSPI4_SCK_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_ECSPI4_SCK_cbit"));
    ui->P_ECSPI4_SS0_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_ECSPI4_SS0_cbit"));
    ui->P_I2C3_SCL_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_I2C3_SCL_cbit"));
    ui->P_I2C3_SDA_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_I2C3_SDA_cbit"));
    ui->P_KHZ32_CLK_OUT_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_SD3_CMD_cbit"));
    ui->P_SD3_CMD_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_KHZ32_CLK_OUT_cbit"));
    ui->P_SD3_CLK_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_SD3_CLK_cbit"));
    ui->P_SD3_DATA0_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_SD3_DATA0_cbit"));
    ui->P_SD3_DATA1_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_SD3_DATA1_cbit"));
    ui->P_SD3_DATA2_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_SD3_DATA2_cbit"));
    ui->P_SD3_DATA3_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_SD3_DATA3_cbit"));
    ui->P_SD3_DATA4_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_SD3_DATA4_cbit"));
    ui->P_SD3_DATA5_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_SD3_DATA5_cbit"));
    ui->P_SD3_DATA6_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_SD3_DATA6_cbit"));
    ui->P_SD3_DATA7_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_SD3_DATA7_cbit"));
    ui->P_GPIO3_IO19_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_GPIO3_IO19_cbit"));
    ui->P_GPIO3_IO20_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_GPIO3_IO20_cbit"));
    ui->P_GPIO1_IO00_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_GPIO1_IO00_cbit"));
    ui->P_GPIO4_IO14_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_GPIO4_IO14_cbit"));
    ui->P_GPIO4_IO26_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_GPIO4_IO26_cbit"));
    ui->P_GPIO4_IO27_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_GPIO4_IO27_cbit"));
    ui->P_GPIO4_IO28_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_GPIO4_IO28_cbit"));
    ui->P_GPIO4_IO29_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_GPIO4_IO29_cbit"));
    ui->P_GPIO6_IO05_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_GPIO6_IO05_cbit"));
    ui->P_AUD6_TXD_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_AUD6_TXD_cbit"));
    ui->P_AUD6_RXD_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_AUD6_RXD_cbit"));
    ui->P_AUD6_TXFS_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_AUD6_TXFS_cbit"));
    ui->P_AUD6_TXC_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_AUD6_TXC_cbit"));
    ui->P_I2C1_SDA_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_I2C1_SDA_cbit"));
    ui->P_I2C1_SCL_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_I2C1_SCL_cbit"));
    ui->P_UART1_TXD_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_UART1_TXD_cbit"));
    ui->P_UART1_RXD_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_UART1_RXD_cbit"));
    ui->P_SPDIF_OUT_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_SPDIF_OUT_cbit"));
    ui->P_UART4_RTS_L_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_UART4_RTS_L_cbit"));
    ui->P_UART4_TXD_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_UART4_TXD_cbit"));
    ui->P_UART4_RXD_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_UART4_RXD_cbit"));
    ui->P_UART4_CTS_L_lineEdit->setText(P_getvalue(strKeyConf, conf_settings , "P_UART4_CTS_L_cbit"));


}


void NOVAembed::on_P_CreateCFGBits_pushButton_clicked()
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

   if ( ui->P_NO_PAD_CTL_checkBox->isChecked() == true )
       value = 1 << 31;
   else
   {
       if ( ui->P_SION_checkBox->isChecked() == true )
           value |= 1 << 30;
       if ( ui->P_HYS_PAD_CTL_checkBox->isChecked() == true )
           value |= 1 << 16;
       if ( ui->P_PUE_checkBox->isChecked() == true )
       {
           value |= 1 << 13;
           if ( ui->P_PD_100K_checkBox->isChecked() == true )
               value |= 0 << 14;
           if ( ui->P_PU_100K_checkBox->isChecked() == true )
               value |= 2 << 14;
           if ( ui->P_PU_47K_checkBox->isChecked() == true )
               value |= 1 << 14;
           if ( ui->P_PU_22K_checkBox->isChecked() == true )
               value |= 3 << 14;
       }
       if ( ui->P_PKE_checkBox->isChecked() == true )
           value |= 1 << 12;
       if ( ui->P_ODE_checkBox->isChecked() == true )
           value |= 1 << 11;
       if ( ui->P_SPEED_Low_checkBox->isChecked() == true )
           value |= 1 << 6;
       if ( ui->P_SPEED_Mid_checkBox->isChecked() == true )
           value |= 2 << 6;
       if ( ui->P_SPEED_High_checkBox->isChecked() == true )
           value |= 3 << 6;
       if ( ui->P_DSE_Disable_checkBox->isChecked() == true )
           value |= 0 << 3;
       else
       {
           if ( ui->P_DSE_34_checkBox->isChecked() == true )
               value |= 7 << 3;
           if ( ui->P_DSE_40_checkBox->isChecked() == true )
               value |= 6 << 3;
           if ( ui->P_DSE_48_checkBox->isChecked() == true )
               value |= 5 << 3;
           if ( ui->P_DSE_60_checkBox->isChecked() == true )
               value |= 4 << 3;
           if ( ui->P_DSE_80_checkBox->isChecked() == true )
               value |= 3 << 3;
           if ( ui->P_DSE_120_checkBox->isChecked() == true )
               value |= 2 << 3;
           if ( ui->P_DSE_240_checkBox->isChecked() == true )
               value |= 1 << 3;
       }
       if ( ui->P_SRE_Fast_checkBox->isChecked() == true )
           value |= 1 << 0;
       if ( ui->P_SRE_Slow_checkBox->isChecked() == true )
           value |= 0 << 0;

    }
    char result[16];
    sprintf(result,"0x%08x",value);
    ui->P_CFG_Bits_lineEdit->setText(result);
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


void NOVAembed::on_P_DecodeCFGBits_pushButton_clicked()
{
    bool ok=1;
    QString a = ui->P_Decoded_CFG_Bits_lineEdit->text().right(8);
    unsigned int value = a.toUInt(&ok,16);
    //qDebug()  << "value = 0x" << QString::number(value, 16);

    if ( (unsigned int )(value & NO_PAD_CTL) == NO_PAD_CTL )
    {
        ui->P_NO_PAD_CTL_checkBox->setChecked(true);
        ui->P_DSE_Disable_checkBox->setEnabled(false);
        ui->P_DSE_frame->setEnabled(false);
        ui->P_Speed_frame->setEnabled(false);
        ui->P_SRE_frame->setEnabled(false);
        ui->P_PUE_checkBox->setEnabled(false);
        ui->P_PUPD_frame->setEnabled(false);
        ui->P_ODE_checkBox->setEnabled(false);
        ui->P_PKE_checkBox->setEnabled(false);
        ui->P_SION_checkBox->setEnabled(false);
        ui->P_HYS_PAD_CTL_checkBox->setEnabled(false);
    }
    else
    {
        ui->P_NO_PAD_CTL_checkBox->setChecked(false);
        ui->P_DSE_Disable_checkBox->setEnabled(true);
        ui->P_DSE_frame->setEnabled(true);
        ui->P_Speed_frame->setEnabled(true);
        ui->P_SRE_frame->setEnabled(true);
        ui->P_PUE_checkBox->setEnabled(true);
        ui->P_PUPD_frame->setEnabled(true);
        ui->P_ODE_checkBox->setEnabled(true);
        ui->P_PKE_checkBox->setEnabled(true);
        ui->P_SION_checkBox->setEnabled(true);
        ui->P_HYS_PAD_CTL_checkBox->setEnabled(true);
    }

    ui->P_SION_checkBox->setChecked(false);
    ui->P_HYS_PAD_CTL_checkBox->setChecked(false);
    if ( (unsigned int )(value & SION) == SION )
        ui->P_SION_checkBox->setChecked(true);
    if ( (unsigned int )(value & PAD_CTL_HYS) == PAD_CTL_HYS )
        ui->P_HYS_PAD_CTL_checkBox->setChecked(true);

    ui->P_PU_47K_checkBox->setChecked(false);
    ui->P_PU_100K_checkBox->setChecked(false);
    ui->P_PU_22K_checkBox->setChecked(false);
    ui->P_PD_100K_checkBox->setChecked(false);
    ui->P_PUE_checkBox->setChecked(false);
    ui->P_PKE_checkBox->setChecked(false);

    if ( (unsigned int )(value & PAD_CTL_PUS_47K_UP) == PAD_CTL_PUS_47K_UP )
    {
        ui->P_PU_47K_checkBox->setChecked(true);
        ui->P_PUE_checkBox->setChecked(true);
    }
    else if ( (unsigned int )(value & PAD_CTL_PUS_100K_UP) == PAD_CTL_PUS_100K_UP )
    {
        ui->P_PU_100K_checkBox->setChecked(true);
        ui->P_PUE_checkBox->setChecked(true);
    }
    else if ( (unsigned int )(value & PAD_CTL_PUS_22K_UP) == PAD_CTL_PUS_22K_UP )
    {
        ui->P_PU_22K_checkBox->setChecked(true);
        ui->P_PUE_checkBox->setChecked(true);
    }
    else if ( (unsigned int )(value & PAD_CTL_PUE) == PAD_CTL_PUE )
    {
        ui->P_PD_100K_checkBox->setChecked(true);
        ui->P_PUE_checkBox->setChecked(true);
    }

    if ( (unsigned int )(value & PAD_CTL_PKE) == PAD_CTL_PKE )
    {
        ui->P_PUE_checkBox->setChecked(false);
        ui->P_PUPD_frame->setEnabled(false);
    }
    if ( (unsigned int )(value & PAD_CTL_ODE) == PAD_CTL_ODE )
    {
        ui->P_ODE_checkBox->setChecked(true);
        //ui->PUE_checkBox->setChecked(false);
        //ui->PUPD_frame->setEnabled(false);
    }


    ui->P_SPEED_Low_checkBox->setChecked(false);
    ui->P_SPEED_Mid_checkBox->setChecked(false);
    ui->P_SPEED_High_checkBox->setChecked(false);
    if ( (unsigned int )(value & PAD_CTL_SPEED_LOW) == PAD_CTL_SPEED_LOW )
        ui->P_SPEED_Low_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_SPEED_MED) == PAD_CTL_SPEED_MED )
        ui->P_SPEED_Mid_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_SPEED_HIGH) == PAD_CTL_SPEED_HIGH )
        ui->P_SPEED_High_checkBox->setChecked(true);

    ui->P_DSE_34_checkBox->setChecked(false);
    ui->P_DSE_40_checkBox->setChecked(false);
    ui->P_DSE_48_checkBox->setChecked(false);
    ui->P_DSE_60_checkBox->setChecked(false);
    ui->P_DSE_80_checkBox->setChecked(false);
    ui->P_DSE_120_checkBox->setChecked(false);
    ui->P_DSE_240_checkBox->setChecked(false);
    if ( (unsigned int )(value & PAD_CTL_DSE_34ohm) == PAD_CTL_DSE_34ohm )
        ui->P_DSE_34_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_DSE_40ohm) == PAD_CTL_DSE_40ohm )
        ui->P_DSE_40_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_DSE_48ohm) == PAD_CTL_DSE_48ohm )
        ui->P_DSE_48_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_DSE_60ohm) == PAD_CTL_DSE_60ohm )
        ui->P_DSE_60_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_DSE_80ohm) == PAD_CTL_DSE_80ohm )
        ui->P_DSE_80_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_DSE_120ohm) == PAD_CTL_DSE_120ohm )
        ui->P_DSE_120_checkBox->setChecked(true);
    else if ( (unsigned int )(value & PAD_CTL_DSE_240ohm) == PAD_CTL_DSE_240ohm )
        ui->P_DSE_240_checkBox->setChecked(true);
    else
    {
        ui->P_DSE_34_checkBox->setChecked(false);
        ui->P_DSE_40_checkBox->setChecked(false);
        ui->P_DSE_48_checkBox->setChecked(false);
        ui->P_DSE_60_checkBox->setChecked(false);
        ui->P_DSE_80_checkBox->setChecked(false);
        ui->P_DSE_120_checkBox->setChecked(false);
        ui->P_DSE_240_checkBox->setChecked(false);
        ui->P_DSE_Disable_checkBox->setChecked(true);
        ui->P_DSE_frame->setEnabled(false);
    }

    ui->P_SRE_Fast_checkBox->setChecked(false);
    ui->P_SRE_Slow_checkBox->setChecked(false);
    if ( (unsigned int )(value & PAD_CTL_SRE_FAST) == PAD_CTL_SRE_FAST )
    {
        ui->P_SRE_Fast_checkBox->setChecked(true);
    }
    else
    {
        ui->P_SRE_Slow_checkBox->setChecked(true);
    }
}

void NOVAembed::on_P_PKE_checkBox_clicked()
{
}

void NOVAembed::on_P_ODE_checkBox_clicked()
{
}

void NOVAembed::on_P_NO_PAD_CTL_checkBox_clicked()
{
    if ( ui->P_NO_PAD_CTL_checkBox->isChecked() == true )
    {
        ui->P_PUPD_frame->setEnabled(false);
        ui->P_Speed_frame->setEnabled(false);
        ui->P_SRE_frame->setEnabled(false);
        ui->P_DSE_frame->setEnabled(false);
        ui->P_PUE_checkBox->setEnabled(false);
        ui->P_SION_checkBox->setEnabled(false);
        ui->P_ODE_checkBox->setEnabled(false);
        ui->P_PKE_checkBox->setEnabled(false);
        ui->P_HYS_PAD_CTL_checkBox->setEnabled(false);
        ui->P_DSE_Disable_checkBox->setEnabled(false);
    }
    else
    {
        ui->P_PUPD_frame->setEnabled(true);
        ui->P_Speed_frame->setEnabled(true);
        ui->P_SRE_frame->setEnabled(true);
        ui->P_DSE_frame->setEnabled(true);
        ui->P_PUE_checkBox->setEnabled(true);
        ui->P_SION_checkBox->setEnabled(true);
        ui->P_ODE_checkBox->setEnabled(true);
        ui->P_PKE_checkBox->setEnabled(true);
        ui->P_HYS_PAD_CTL_checkBox->setEnabled(true);
        ui->P_DSE_Disable_checkBox->setEnabled(true);
    }

}

void NOVAembed::on_P_PUE_checkBox_clicked()
{
    if ( ui->P_PUE_checkBox->isChecked() == true )
    {
        ui->P_ODE_checkBox->setChecked(false);
        ui->P_PKE_checkBox->setChecked(false);
        ui->P_PUPD_frame->setEnabled(true);
    }
    else
    {
        ui->P_PUPD_frame->setEnabled(false);
    }
}


void NOVAembed::on_P_PD_100K_checkBox_clicked()
{
    ui->P_PD_100K_checkBox->setChecked(true);
    ui->P_PU_100K_checkBox->setChecked(false);
    ui->P_PU_47K_checkBox->setChecked(false);
    ui->P_PU_22K_checkBox->setChecked(false);
}


void NOVAembed::on_P_PU_100K_checkBox_clicked()
{
    ui->P_PD_100K_checkBox->setChecked(false);
    ui->P_PU_100K_checkBox->setChecked(true);
    ui->P_PU_47K_checkBox->setChecked(false);
    ui->P_PU_22K_checkBox->setChecked(false);
}


void NOVAembed::on_P_PU_47K_checkBox_clicked()
{
    ui->P_PD_100K_checkBox->setChecked(false);
    ui->P_PU_100K_checkBox->setChecked(false);
    ui->P_PU_47K_checkBox->setChecked(true);
    ui->P_PU_22K_checkBox->setChecked(false);
}



void NOVAembed::on_P_PU_22K_checkBox_clicked()
{
    ui->P_PD_100K_checkBox->setChecked(false);
    ui->P_PU_100K_checkBox->setChecked(false);
    ui->P_PU_47K_checkBox->setChecked(false);
    ui->P_PU_22K_checkBox->setChecked(true);
}


void NOVAembed::on_P_SPEED_Low_checkBox_clicked()
{
    if ( ui->P_SPEED_Low_checkBox->isChecked() == true )
    {
        ui->P_SPEED_Low_checkBox->setChecked(true);
        ui->P_SPEED_Mid_checkBox->setChecked(false);
        ui->P_SPEED_High_checkBox->setChecked(false);
    }
}

void NOVAembed::on_P_SPEED_Mid_checkBox_clicked()
{
    if ( ui->P_SPEED_Mid_checkBox->isChecked() == true )
    {
        ui->P_SPEED_Low_checkBox->setChecked(false);
        ui->P_SPEED_Mid_checkBox->setChecked(true);
        ui->P_SPEED_High_checkBox->setChecked(false);
    }
}

void NOVAembed::on_P_SPEED_High_checkBox_clicked()
{
    if ( ui->P_SPEED_High_checkBox->isChecked() == true )
    {
        ui->P_SPEED_Low_checkBox->setChecked(false);
        ui->P_SPEED_Mid_checkBox->setChecked(false);
        ui->P_SPEED_High_checkBox->setChecked(true);
    }
}




void NOVAembed::on_P_SRE_Fast_checkBox_clicked()
{
    if ( ui->P_SRE_Fast_checkBox->isChecked() == true )
    {
        ui->P_SRE_Fast_checkBox->setChecked(true);
        ui->P_SRE_Slow_checkBox->setChecked(false);
    }
}

void NOVAembed::on_P_SRE_Slow_checkBox_clicked()
{
    if ( ui->P_SRE_Slow_checkBox->isChecked() == true )
    {
        ui->P_SRE_Fast_checkBox->setChecked(false);
        ui->P_SRE_Slow_checkBox->setChecked(true);
    }
}

void NOVAembed::on_P_DSE_Disable_checkBox_clicked()
{
    if ( ui->P_DSE_Disable_checkBox->isChecked() == true )
    {
        ui->P_DSE_34_checkBox->setDisabled(true);
        ui->P_DSE_40_checkBox->setDisabled(true);
        ui->P_DSE_48_checkBox->setDisabled(true);
        ui->P_DSE_60_checkBox->setDisabled(true);
        ui->P_DSE_80_checkBox->setDisabled(true);
        ui->P_DSE_120_checkBox->setDisabled(true);
        ui->P_DSE_240_checkBox->setDisabled(true);
        ui->P_DSE_frame->setEnabled(false);
    }
    else
    {
        ui->P_DSE_34_checkBox->setDisabled(false);
        ui->P_DSE_40_checkBox->setDisabled(false);
        ui->P_DSE_48_checkBox->setDisabled(false);
        ui->P_DSE_60_checkBox->setDisabled(false);
        ui->P_DSE_80_checkBox->setDisabled(false);
        ui->P_DSE_120_checkBox->setDisabled(false);
        ui->P_DSE_240_checkBox->setDisabled(false);


        ui->P_DSE_34_checkBox->setChecked(false);
        ui->P_DSE_40_checkBox->setChecked(false);
        ui->P_DSE_48_checkBox->setChecked(false);
        ui->P_DSE_60_checkBox->setChecked(false);
        ui->P_DSE_80_checkBox->setChecked(false);
        ui->P_DSE_120_checkBox->setChecked(false);
        ui->P_DSE_240_checkBox->setChecked(true);
        ui->P_DSE_frame->setEnabled(true);
    }
}

void NOVAembed::on_P_DSE_34_checkBox_clicked()
{
    if ( ui->P_DSE_34_checkBox->isChecked() == true )
    {
        ui->P_DSE_34_checkBox->setChecked(true);
        ui->P_DSE_40_checkBox->setChecked(false);
        ui->P_DSE_48_checkBox->setChecked(false);
        ui->P_DSE_60_checkBox->setChecked(false);
        ui->P_DSE_80_checkBox->setChecked(false);
        ui->P_DSE_120_checkBox->setChecked(false);
        ui->P_DSE_240_checkBox->setChecked(false);
    }
}

void NOVAembed::on_P_DSE_40_checkBox_clicked()
{
    if ( ui->P_DSE_40_checkBox->isChecked() == true )
    {
        ui->P_DSE_34_checkBox->setChecked(false);
        ui->P_DSE_40_checkBox->setChecked(true);
        ui->P_DSE_48_checkBox->setChecked(false);
        ui->P_DSE_60_checkBox->setChecked(false);
        ui->P_DSE_80_checkBox->setChecked(false);
        ui->P_DSE_120_checkBox->setChecked(false);
        ui->P_DSE_240_checkBox->setChecked(false);
    }
}

void NOVAembed::on_P_DSE_48_checkBox_clicked()
{
    if ( ui->P_DSE_48_checkBox->isChecked() == true )
    {
        ui->P_DSE_34_checkBox->setChecked(false);
        ui->P_DSE_40_checkBox->setChecked(false);
        ui->P_DSE_48_checkBox->setChecked(true);
        ui->P_DSE_60_checkBox->setChecked(false);
        ui->P_DSE_80_checkBox->setChecked(false);
        ui->P_DSE_120_checkBox->setChecked(false);
        ui->P_DSE_240_checkBox->setChecked(false);
    }
}

void NOVAembed::on_P_DSE_60_checkBox_clicked()
{
    if ( ui->P_DSE_60_checkBox->isChecked() == true )
    {
        ui->P_DSE_34_checkBox->setChecked(false);
        ui->P_DSE_40_checkBox->setChecked(false);
        ui->P_DSE_48_checkBox->setChecked(false);
        ui->P_DSE_60_checkBox->setChecked(true);
        ui->P_DSE_80_checkBox->setChecked(false);
        ui->P_DSE_120_checkBox->setChecked(false);
        ui->P_DSE_240_checkBox->setChecked(false);
    }
}

void NOVAembed::on_P_DSE_80_checkBox_clicked()
{
    if ( ui->P_DSE_80_checkBox->isChecked() == true )
    {
        ui->P_DSE_34_checkBox->setChecked(false);
        ui->P_DSE_40_checkBox->setChecked(false);
        ui->P_DSE_48_checkBox->setChecked(false);
        ui->P_DSE_60_checkBox->setChecked(false);
        ui->P_DSE_80_checkBox->setChecked(true);
        ui->P_DSE_120_checkBox->setChecked(false);
        ui->P_DSE_240_checkBox->setChecked(false);
    }
}

void NOVAembed::on_P_DSE_120_checkBox_clicked()
{
    if ( ui->P_DSE_120_checkBox->isChecked() == true )
    {
        ui->P_DSE_34_checkBox->setChecked(false);
        ui->P_DSE_40_checkBox->setChecked(false);
        ui->P_DSE_48_checkBox->setChecked(false);
        ui->P_DSE_60_checkBox->setChecked(false);
        ui->P_DSE_80_checkBox->setChecked(false);
        ui->P_DSE_120_checkBox->setChecked(true);
        ui->P_DSE_240_checkBox->setChecked(false);
    }
}

void NOVAembed::on_P_DSE_240_checkBox_clicked()
{
    if ( ui->P_DSE_240_checkBox->isChecked() == true )
    {
        ui->P_DSE_34_checkBox->setChecked(false);
        ui->P_DSE_40_checkBox->setChecked(false);
        ui->P_DSE_48_checkBox->setChecked(false);
        ui->P_DSE_60_checkBox->setChecked(false);
        ui->P_DSE_80_checkBox->setChecked(false);
        ui->P_DSE_120_checkBox->setChecked(false);
        ui->P_DSE_240_checkBox->setChecked(true);
    }
}

void NOVAembed::on_P_Generate_pushButton_clicked()
{
    QFile scriptfile("/tmp/script");
    QFileInfo fi(Last_P_BSPFactoryFile);
    QString FileNameNoExtension = fi.baseName();

    save_helper(Last_P_BSPFactoryFile);

    update_status_bar("Generating dtb "+FileNameNoExtension+".dtb ...");
    if ( ! scriptfile.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        update_status_bar("Unable to create /tmp/script");
        return;
    }
    QTextStream out(&scriptfile);
    out << QString("#!/bin/sh\n");
    out << QString("[ ! -d /Devel/NOVAsom_SDK/DtbUserWorkArea ] && mkdir /Devel/NOVAsom_SDK/DtbUserWorkArea\n");
    out << QString("cd /Devel/NOVAsom_SDK/Utils\n");
    if ( ui->Board_comboBox->currentText() == "P Series")
    {
        out << QString("/Devel/NOVAsom_SDK/Qt/NOVAembed/NOVAembed/NOVAembed_P_Parser/bin/Debug/NOVAembed_P_Parser /Devel/NOVAsom_SDK/DtbUserWorkArea/PClass_bspf/"+FileNameNoExtension+".bspf > /Devel/NOVAsom_SDK/Logs/P_bspf.log\n");
        out << QString("./user_dtb_compile "+FileNameNoExtension+" P >> /Devel/NOVAsom_SDK/Logs/P_bspf.log\n");
    }
    out << QString("echo $? > /tmp/result\n");

    scriptfile.close();
    if ( run_script() == 0)
        update_status_bar("DTB "+FileNameNoExtension+".dtb compiled, dtb is in /Devel/NOVAsom_SDK/DtbUserWorkArea/"+FileNameNoExtension+".dtb");
    else
        update_status_bar("Error compiling "+FileNameNoExtension+".dtb");
}



void NOVAembed::on_P_QUAD_checkBox_toggled(bool checked)
{
    if ( checked )
    {
        Quad = "true";
        ui->P_SATA_checkBox->setEnabled(true);
    }
    else
    {
        Quad = "false";
        ui->P_SATA_checkBox->setEnabled(false);
        ui->P_SATA_checkBox->setChecked(false);
    }
    storeNOVAembed_ini();

}
/*****************************************************************************************************************************************************************************************/
/*                                                                             P BSP Factory END                                                                                         */
/*****************************************************************************************************************************************************************************************/

