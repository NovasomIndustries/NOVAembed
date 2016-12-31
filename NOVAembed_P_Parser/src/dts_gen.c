#include "../include/NOVAembed_P_parser.h"
#include "../include/header.h"

char    dtsfile_dump[512];
char    dtsifile_dump[16384];
char    file_name[32],file_name_noext[32],dir_name[256];
char    file_name_dts[128],file_name_dtsi[128];

void create_file_names(char *file_in)
{
int     i;
    bzero(dtsfile_dump,sizeof(dtsfile_dump));
    bzero(dtsifile_dump,sizeof(dtsifile_dump));

    sprintf(file_name,"%s",basename(strdup(file_in)));
    sprintf(dir_name,"%s",dirname(strdup(file_in)));

    sprintf(file_name_noext,"%s",file_name);

    for(i=0;i<strlen(file_name_noext);i++)
    {
        if ( file_name_noext[i] == '.')
            file_name_noext[i]=0;
    }
    sprintf(file_name_dts,"/Devel/NOVAsom_SDK/DtbUserWorkArea/%s.dts",file_name_noext);
    sprintf(file_name_dtsi,"/Devel/NOVAsom_SDK/DtbUserWorkArea/%s.dtsi",file_name_noext);

    printf("%s\n",file_in);
    printf("%s\n",file_name);
    printf("%s\n",dir_name);
    printf("%s\n",file_name_noext);
    printf("%s\n",file_name_dts);
    printf("%s\n",file_name_dtsi);

}

void create_dts_file(void)
{
FILE    *fpout_dts;
char    tstr[128];
    sprintf(dtsfile_dump,dts_defs_part1);
    sprintf(tstr,"#include \"%s\"\n",file_name_dtsi);
    strcat(dtsfile_dump,tstr);
    strcat(dtsfile_dump,dts_defs_part2);
    if ( (fpout_dts = fopen(file_name_dts,"w" ) ))
    {
        fwrite(dtsfile_dump, strlen(dtsfile_dump), 1, fpout_dts);
        fclose(fpout_dts);
    }
}

void process_hogs(void)
{
char    hogs[1024];
char    t[128];
    sprintf(hogs,"        pinctrl_hog: hoggrp {\n");
    strcat (hogs,"            fsl,pins = <\n");
    if ( clk32k != NULL)
    {
        sprintf(t,"                %s 0x%s\n",clk32k->hog_pin_name,clk32k->pin_config[0]);
        strcat (hogs,t);
    }
    if ( clk24m != NULL)
    {
        sprintf(t,"                %s 0x%s\n",clk24m->hog_pin_name,clk24m->pin_config[0]);
        strcat (hogs,t);
    }
    if ( ccm_clko1 != NULL)
    {
        sprintf(t,"                %s 0x%s\n",ccm_clko1->hog_pin_name,ccm_clko1->pin_config[0]);
        strcat (hogs,t);
    }
    if ( wdog != NULL)
    {
        sprintf(t,"                %s 0x%s\n",wdog->hog_pin_name,wdog->pin_config[0]);
        strcat (hogs,t);
    }
    strcat (hogs,"          >;\n");
    strcat (hogs,"        };\n");
    strcat(dtsifile_dump,hogs);
}

void process_sf(void)
{
char    sf[1024];
char    t[128];
    if ( pwm != NULL )
    {
        sprintf(sf,"        %s: %s{\n",pwm->pinctrl0_name,pwm->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",pwm->pwm_pin_name,pwm->pin_config[0]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"      };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( epit1 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",epit1->pinctrl0_name,epit1->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",epit1->epit_pin_name,epit1->pin_config[0]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"      };\n");

        strcat(dtsifile_dump,sf);
    }
    if ( sdcard != NULL )
    {
        sprintf(sf,"        %s: %s{\n",sdcard->pinctrl0_name,sdcard->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",sdcard->cmd_pin_name,sdcard->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard->clk_pin_name,sdcard->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard->data0_pin_name,sdcard->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard->data1_pin_name,sdcard->pin_config[3]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard->data2_pin_name,sdcard->pin_config[4]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard->data3_pin_name,sdcard->pin_config[5]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard->data4_pin_name,sdcard->pin_config[6]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard->data5_pin_name,sdcard->pin_config[7]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard->data6_pin_name,sdcard->pin_config[8]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",sdcard->data7_pin_name,sdcard->pin_config[9]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( spdif != NULL )
    {
        sprintf(sf,"        %s: %s{\n",spdif->pinctrl0_name,spdif->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",spdif->spdif_pin_name,spdif->pin_config[0]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( can1 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",can1->pinctrl0_name,can1->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",can1->cantx_pin_name,can1->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",can1->canrx_pin_name,can1->pin_config[1]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( can2 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",can2->pinctrl0_name,can2->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",can2->cantx_pin_name,can2->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",can2->canrx_pin_name,can2->pin_config[1]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( i2c1b != NULL )
    {
        sprintf(sf,"        %s: %s{\n",i2c1b->pinctrl0_name,i2c1b->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",i2c1b->sda_pin_name,i2c1b->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",i2c1b->scl_pin_name,i2c1b->pin_config[1]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( uart1 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",uart1->pinctrl0_name,uart1->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",uart1->uart_txd_pin_name,uart1->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",uart1->uart_txd_pin_name,uart1->pin_config[1]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( uart2_2 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",uart2_2->pinctrl0_name,uart2_2->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",uart2_2->uart_txd_pin_name,uart2_2->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",uart2_2->uart_txd_pin_name,uart2_2->pin_config[1]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( uart4_2 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",uart4_2->pinctrl0_name,uart4_2->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",uart4_2->uart_txd_pin_name,uart4_2->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",uart4_2->uart_txd_pin_name,uart4_2->pin_config[1]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( uart2_4 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",uart2_4->pinctrl0_name,uart2_4->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",uart2_4->uart_txd_pin_name,uart2_4->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",uart2_4->uart_txd_pin_name,uart2_4->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",uart2_4->uart_rts_pin_name,uart2_4->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",uart2_4->uart_cts_pin_name,uart2_4->pin_config[3]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( uart4_4 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",uart4_4->pinctrl0_name,uart4_4->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",uart4_4->uart_txd_pin_name,uart4_4->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",uart4_4->uart_txd_pin_name,uart4_4->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",uart4_4->uart_rts_pin_name,uart4_4->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",uart4_4->uart_cts_pin_name,uart4_4->pin_config[3]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }

    if ( audio4 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",audio4->pinctrl0_name,audio4->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",audio4->aud_rxd_pin_name,audio4->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",audio4->aud_txc_pin_name,audio4->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",audio4->aud_txd_pin_name,audio4->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",audio4->aud_txfs_pin_name,audio4->pin_config[3]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( audio5 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",audio5->pinctrl0_name,audio5->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",audio5->aud_rxd_pin_name,audio5->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",audio5->aud_txc_pin_name,audio5->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",audio5->aud_txd_pin_name,audio5->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",audio5->aud_txfs_pin_name,audio5->pin_config[3]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( audio6 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",audio6->pinctrl0_name,audio6->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",audio6->aud_rxd_pin_name,audio6->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",audio6->aud_txc_pin_name,audio6->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",audio6->aud_txd_pin_name,audio6->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",audio6->aud_txfs_pin_name,audio6->pin_config[3]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }

    if ( ecspi1_5 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",ecspi1_5->pinctrl0_name,ecspi1_5->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",ecspi1_5->mosi_pin_name,ecspi1_5->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi1_5->miso_pin_name,ecspi1_5->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi1_5->sclk_pin_name,ecspi1_5->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi1_5->ss0_pin_name,ecspi1_5->pin_config[3]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi1_5->ss1_pin_name,ecspi1_5->pin_config[4]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( ecspi1_4 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",ecspi1_4->pinctrl0_name,ecspi1_4->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",ecspi1_4->mosi_pin_name,ecspi1_4->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi1_4->miso_pin_name,ecspi1_4->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi1_4->sclk_pin_name,ecspi1_4->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi1_4->ss0_pin_name,ecspi1_4->pin_config[3]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }

    if ( ecspi2_5 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",ecspi2_5->pinctrl0_name,ecspi2_5->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",ecspi2_5->mosi_pin_name,ecspi2_5->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi2_5->miso_pin_name,ecspi2_5->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi2_5->sclk_pin_name,ecspi2_5->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi2_5->ss0_pin_name,ecspi2_5->pin_config[3]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi2_5->ss1_pin_name,ecspi2_5->pin_config[4]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( ecspi2_4 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",ecspi2_4->pinctrl0_name,ecspi2_4->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",ecspi2_4->mosi_pin_name,ecspi2_4->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi2_4->miso_pin_name,ecspi2_4->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi2_4->sclk_pin_name,ecspi2_4->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi2_4->ss0_pin_name,ecspi2_4->pin_config[3]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }

    if ( ecspi3_5 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",ecspi3_5->pinctrl0_name,ecspi3_5->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",ecspi3_5->mosi_pin_name,ecspi3_5->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi3_5->miso_pin_name,ecspi3_5->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi3_5->sclk_pin_name,ecspi3_5->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi3_5->ss0_pin_name,ecspi3_5->pin_config[3]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi3_5->ss1_pin_name,ecspi3_5->pin_config[4]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( ecspi3_4 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",ecspi3_4->pinctrl0_name,ecspi3_4->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",ecspi3_4->mosi_pin_name,ecspi3_4->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi3_4->miso_pin_name,ecspi3_4->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi3_4->sclk_pin_name,ecspi3_4->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi3_4->ss0_pin_name,ecspi3_4->pin_config[3]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }

    if ( ecspi4 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",ecspi4->pinctrl0_name,ecspi4->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",ecspi4->mosi_pin_name,ecspi4->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi4->miso_pin_name,ecspi4->pin_config[1]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi4->sclk_pin_name,ecspi4->pin_config[2]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",ecspi4->ss0_pin_name,ecspi4->pin_config[3]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    if ( i2c1a != NULL )
    {
        sprintf(sf,"        %s: %s{\n",i2c1a->pinctrl0_name,i2c1a->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",i2c1a->sda_pin_name,i2c1a->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",i2c1a->scl_pin_name,i2c1a->pin_config[1]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }

    if ( i2c3 != NULL )
    {
        sprintf(sf,"        %s: %s{\n",i2c3->pinctrl0_name,i2c3->grp_name);
        strcat(sf,"            fsl,pins = <\n");
        sprintf(t,"                %s 0x%s\n",i2c3->sda_pin_name,i2c3->pin_config[0]);
        strcat (sf,t);
        sprintf(t,"                %s 0x%s\n",i2c3->scl_pin_name,i2c3->pin_config[1]);
        strcat (sf,t);
        strcat (sf,"          >;\n");
        strcat (sf,"        };\n");
        strcat(dtsifile_dump,sf);
    }
    sprintf (sf,"    };\n");
    strcat (sf," };\n");
    strcat(dtsifile_dump,sf);
}


void process_special_devs(void)
{
char    t[1024];

    if ( iomux->pcie == 1 )
    {
        sprintf(t,pcie_enabled_defs);
    }
    else
    {
        sprintf(t,pcie_disabled_defs);
    }
    strcat(dtsifile_dump,t);
    if (( iomux->spdif1 == 1 ) || ( iomux->spdif2 == 1 ))
    {
        sprintf(t,spdif_enabled_defs);
    }
    strcat(dtsifile_dump,t);
}

void process_videos_header(void)
{
char    mxcfb[1024];
    sprintf(mxcfb,"    mxcfb1: fb@0 {\n            compatible = \"fsl,mxc_sdc_fb\";\n            disp_dev = \"hdmi\";\n            interface_pix_fmt = \"RGB24\";\n");
    if (strstr(file_contents,"HDMIVideo_comboBox=HDMI 1920x1080"))
        strcat(mxcfb,"            mode_str =\"1920x1080M@60\";\n");
    else
        strcat(mxcfb,"            mode_str =\"1280x720M@60\";\n");
    strcat(mxcfb,"            default_bpp = <24>;\n            int_clk = <0>;\n            late_init = <0>;\n            status = \"okay\";\n    };\n");
    strcat(dtsifile_dump,mxcfb);

    sprintf(mxcfb,"    mxcfb2: fb@1 {\n            compatible = \"fsl,mxc_sdc_fb\";\n            disp_dev = \"ldb\";\n");
    strcat(mxcfb,"            interface_pix_fmt = \"RGB666\";\n");
    strcat(mxcfb,"            default_bpp = <16>;\n            int_clk = <0>;\n            late_init = <0>;\n            status = \"disabled\";\n    };\n");
    strcat(dtsifile_dump,mxcfb);

    sprintf(mxcfb,"    mxcfb3: fb@2 {\n            compatible = \"fsl,mxc_sdc_fb\";\n            disp_dev = \"ldb\";\n");
    strcat(mxcfb,"            interface_pix_fmt = \"RGB666\";\n");
    strcat(mxcfb,"            default_bpp = <16>;\n            int_clk = <0>;\n            late_init = <0>;\n            status = \"disabled\";\n    };\n};\n");
    strcat(dtsifile_dump,mxcfb);
}

void process_lvds_channels(void)
{
char    ldb[1024];
    sprintf(ldb,"&ldb {\n");
    strcat(ldb,"	status = \"okay\";\n");
    strcat(ldb,"	lvds-channel@0 {\n		fsl,data-mapping = \"spwg\";\n		fsl,data-width = <18>;\n		primary;\n		status = \"okay\";\n		crtc = \"ipu1-di0\";\n");
    strcat(ldb,"		display-timings {\n			native-mode = <&timing0>;\n			timing0: lvds0 {\n");
    strcat(ldb,"				clock-frequency = <33000000>;\n");
    strcat(ldb,"				hactive = <1024>;\n");
    strcat(ldb,"				vactive = <768>;\n");
    strcat(ldb,"				hback-porch = <220>;\n");
    strcat(ldb,"				hfront-porch = <40>;\n");
    strcat(ldb,"				vback-porch = <21>;\n");
    strcat(ldb,"				vfront-porch = <7>;\n");
    strcat(ldb,"				hsync-len = <60>;\n");
    strcat(ldb,"				vsync-len = <10>;\n");
    strcat(ldb,"			};\n");
    strcat(ldb,"		};\n");
    strcat(ldb,"	};\n");
    strcat(dtsifile_dump,ldb);
    sprintf(ldb,"	lvds-channel@1 {\n");
    strcat(ldb,"		fsl,data-mapping = \"spwg\";\n		fsl,data-width = <18>;\n		status = \"okay\";\n		crtc = \"ipu1-di1\";\n");
    strcat(ldb,"		display-timings {\n			native-mode = <&timing1>;\n			timing1: lvds1 {\n");
    strcat(ldb,"				clock-frequency = <33000000>;\n");
    strcat(ldb,"				hactive = <1024>;\n");
    strcat(ldb,"				vactive = <768>;\n");
    strcat(ldb,"				hback-porch = <220>;\n");
    strcat(ldb,"				hfront-porch = <40>;\n");
    strcat(ldb,"				vback-porch = <21>;\n");
    strcat(ldb,"				vfront-porch = <7>;\n");
    strcat(ldb,"				hsync-len = <60>;\n");
    strcat(ldb,"				vsync-len = <10>;\n");
    strcat(ldb,"			};\n");
    strcat(ldb,"		};\n");
    strcat(ldb,"	};  \n");
    strcat(dtsifile_dump,ldb);
    sprintf(ldb,"};\n");
    strcat(dtsifile_dump,ldb);
}

void create_dtsi_file(void)
{
FILE    *fpout_dtsi;

    sprintf(dtsifile_dump,dtsi_header1_defs);
    process_videos_header();
    strcat(dtsifile_dump,dtsi_header2_defs);
    strcat(dtsifile_dump,iomux_defs);
    process_hogs();
    process_sf();
    process_special_devs();
    process_lvds_channels();
    if ( (fpout_dtsi = fopen(file_name_dtsi,"w" ) ))
    {
        fwrite(dtsifile_dump, strlen(dtsifile_dump), 1, fpout_dtsi);
        fclose(fpout_dtsi);
    }
}

void store_dts_files(char *file_in)
{
    create_file_names(file_in);
    create_dts_file();
    create_dtsi_file();
    printf("dtsfile_dump len : %d\n",(int )strlen(dtsfile_dump));
    printf("dtsifile_dump len : %d\n",(int )strlen(dtsifile_dump));
}
