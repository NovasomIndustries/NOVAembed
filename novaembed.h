#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

namespace Ui {
class NOVAembed;
}

class NOVAembed : public QMainWindow
{
    Q_OBJECT

public:
    explicit NOVAembed(QWidget *parent = 0);
    ~NOVAembed();

private slots:
    /* Helper Functions */
    void storeNOVAembed_ini();
    void P_load_BSPF_File(QString fileName);
    void U_load_BSPF_File(QString fileName);
    void compile_NewFileSystemFileSystemConfigurationcomboBox();
    void compile_ExtFS_comboBox();
    void local_sleep(int ms);
    int run_script(void);
    int update_status_bar(QString StatusBarContent);
    //void P_disable_all(void);
    void U_disable_all(void);
    void U_enable_all(void);


    /* Helper Functions End */

    void on_actionExit_triggered();

    void on_SelectFileSystem_pushButton_clicked();

    void on_tab_currentChanged(int index);

    void on_KernelXconfig_pushButton_clicked();

    void on_BootLoaderCompile_pushButton_clicked();

    void on_KernelCompile_pushButton_clicked();

    void on_LaunchMenuConfig_pushButton_clicked();

    void on_FileSystemDeploy_pushButton_clicked();

    void on_Board_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_ECSPI1_MISO_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_ECSPI1_MOSI_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_ECSPI1_SS0_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_ECSPI1_SCK_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_ECSPI2_SS0_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_ECSPI2_SS1_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_ECSPI2_MISO_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_ECSPI2_MOSI_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_ECSPI2_SCK_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_ECSPI3_MISO_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_ECSPI3_SCK_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_ECSPI3_MOSI_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_ECSPI3_SS0_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_ECSPI3_SS1_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_ECSPI4_MISO_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_ECSPI4_MOSI_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_ECSPI4_SCK_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_ECSPI4_SS0_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_I2C3_SCL_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_I2C3_SDA_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_KHZ32_CLK_OUT_comboBox_currentIndexChanged(const QString &arg1);

    void set_sd3_IO_helper(void);

    void set_sd3_SD_helper(void);

    void on_P_SD3_CMD_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_SD3_CLK_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_SD3_DATA0_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_SD3_DATA1_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_SD3_DATA2_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_SD3_DATA3_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_SD3_DATA4_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_SD3_DATA5_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_SD3_DATA6_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_SD3_DATA7_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_GPIO3_IO20_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_GPIO1_IO00_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_GPIO4_IO29_comboBox_currentIndexChanged(const QString &arg1);

    void setAUD6_AUDIO(void);

    void setAUD6_IO(void);

    void on_P_AUD6_TXD_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_AUD6_RXD_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_AUD6_TXFS_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_AUD6_TXC_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_I2C1_SDA_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_I2C1_SCL_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_UART1_TXD_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_UART1_RXD_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_SPDIF_OUT_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_UART4_RTS_L_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_UART4_TXD_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_UART4_RXD_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_UART4_CTS_L_comboBox_currentIndexChanged(const QString &arg1);

    void on_P_Save_pushButton_clicked();

    void on_P_Load_pushButton_clicked();

    void on_P_Default_pushButton_clicked();

    void on_UserPartition_comboBox_currentIndexChanged(const QString &arg1);

    void on_Write_uSD_pushButton_clicked();

    void on_CodeBlock_pushButton_clicked();

    void on_Meld_pushButton_clicked();

    void on_MeldChooseFile1_pushButton_clicked();

    void on_MeldChooseFile2_pushButton_clicked();

    void on_P_PD_100K_checkBox_clicked();

    void on_P_PU_100K_checkBox_clicked();

    void on_P_PU_47K_checkBox_clicked();

    void on_P_PU_22K_checkBox_clicked();

    void on_P_PUE_checkBox_clicked();

    void on_P_SPEED_Low_checkBox_clicked();

    void on_P_SPEED_Mid_checkBox_clicked();

    void on_P_SPEED_High_checkBox_clicked();

    void on_P_SRE_Fast_checkBox_clicked();

    void on_P_SRE_Slow_checkBox_clicked();

    void on_P_DSE_Disable_checkBox_clicked();

    void on_P_DSE_34_checkBox_clicked();

    void on_P_DSE_40_checkBox_clicked();

    void on_P_DSE_48_checkBox_clicked();

    void on_P_DSE_60_checkBox_clicked();

    void on_P_DSE_80_checkBox_clicked();

    void on_P_DSE_120_checkBox_clicked();

    void on_P_DSE_240_checkBox_clicked();

    void on_P_PKE_checkBox_clicked();

    void on_P_ODE_checkBox_clicked();

    void on_P_NO_PAD_CTL_checkBox_clicked();

    void on_KernelReCompile_pushButton_clicked();

    void on_QtCreator_pushButton_clicked();

    void on_P_CreateCFGBits_pushButton_clicked();

    void on_P_DecodeCFGBits_pushButton_clicked();

    void on_U_Load_pushButton_clicked();

    void on_U_Save_pushButton_clicked();

    void on_U_Default_pushButton_clicked();

    void on_U_CreateCFGBits_pushButton_clicked();

    void on_U_DecodeCFGBits_pushButton_clicked();

    void on_U_SION_checkBox_clicked();

    void on_U_NO_PAD_CTL_checkBox_clicked();

    void on_U_SPEED_Low_checkBox_clicked();

    void on_U_SPEED_Mid_checkBox_clicked();

    void on_U_SPEED_High_checkBox_clicked();

    void on_U_PUE_checkBox_clicked();

    void on_U_PD_100K_checkBox_clicked();

    void on_U_PU_100K_checkBox_clicked();

    void on_U_PU_47K_checkBox_clicked();

    void on_U_PU_22K_checkBox_clicked();

    void on_U_ODE_checkBox_clicked();

    void on_U_PKE_checkBox_clicked();

    void on_U_DSE_Disable_checkBox_clicked();

    void on_U_DSE_34_checkBox_clicked();

    void on_U_DSE_40_checkBox_clicked();

    void on_U_DSE_48_checkBox_clicked();

    void on_U_DSE_60_checkBox_clicked();

    void on_U_DSE_80_checkBox_clicked();

    void on_U_DSE_120_checkBox_clicked();

    void on_U_DSE_240_checkBox_clicked();

    void on_U_SRE_Fast_checkBox_clicked();

    void on_U_SRE_Slow_checkBox_clicked();

    void on_UserPartition1Size_lineEdit_textChanged(const QString &arg1);

    void on_UserPartition2Size_lineEdit_textChanged(const QString &arg1);

    void on_P_HUM_pushButton_clicked();


    void on_P_QSG_pushButton_clicked();

    void on_LaunchBusyboxMenuConfig_pushButton_clicked();

    void on_uSD_Device_comboBox_currentIndexChanged(const QString &arg1);

    void on_GenerateFileSystem_pushButton_clicked();

    void on_ExtFS_Write_uSD_pushButton_clicked();

    void on_ExtFS_comboBox_currentIndexChanged(const QString &arg1);


    void on_ThisIsReferenceServer_checkBox_clicked(bool checked);

    void on_CheckUpdate_pushButton_clicked();

    void on_Video_comboBox_currentIndexChanged(const QString &arg1);

    void on_KernelMakeDTB_pushButton_clicked();

private:
    Ui::NOVAembed *ui;
};

#endif // MAINWINDOW_H
