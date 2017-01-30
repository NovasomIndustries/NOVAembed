#include "../include/NOVAembed_P_parser.h"
#include "../include/header.h"

char        file_contents[8192];
char        header_defs_dump[8192];
char        iomux_defs_dump[8192];
char        lvds_800x480_ch0_parserinput[1024];
char        lvds_800x480_ch1_parserinput[1024];
char        lvds_800x600_ch0_parserinput[1024];
char        lvds_800x600_ch1_parserinput[1024];
char        lvds_1024x600_ch0_parserinput[1024];
char        lvds_1024x600_ch1_parserinput[1024];
char        lvds_1024x768_ch0_parserinput[1024];
char        lvds_1024x768_ch1_parserinput[1024];


void read_parserinput(void)
{
FILE *fpin;
char    parserinput_dir[]="/Devel/NOVAsom_SDK/Qt/NOVAembed/NOVAembed/NOVAembed_P_Parser/lvds_defs/";
char fname[256];

    printf("%s : enter\n",__func__);
    bzero(lvds_800x480_ch0_parserinput,sizeof(lvds_800x480_ch0_parserinput));
    bzero(lvds_800x480_ch1_parserinput,sizeof(lvds_800x480_ch1_parserinput));
    bzero(lvds_800x600_ch0_parserinput,sizeof(lvds_800x600_ch0_parserinput));
    bzero(lvds_800x600_ch1_parserinput,sizeof(lvds_800x600_ch1_parserinput));
    bzero(lvds_1024x600_ch0_parserinput,sizeof(lvds_1024x600_ch0_parserinput));
    bzero(lvds_1024x600_ch1_parserinput,sizeof(lvds_1024x600_ch1_parserinput));
    bzero(lvds_1024x768_ch0_parserinput,sizeof(lvds_1024x768_ch0_parserinput));
    bzero(lvds_1024x768_ch1_parserinput,sizeof(lvds_1024x768_ch1_parserinput));

    sprintf(fname,"%s/lvds_800x480_ch0_parserinput",parserinput_dir);
    if ( (fpin = fopen(fname,"r" ) ))
    {
        fread(lvds_800x480_ch0_parserinput, sizeof(lvds_800x480_ch0_parserinput), 1, fpin);
        fclose(fpin);
    }
    sprintf(fname,"%s/lvds_800x480_ch1_parserinput",parserinput_dir);
    if ( (fpin = fopen(fname,"r" ) ))
    {
        fread(lvds_800x480_ch1_parserinput, sizeof(lvds_800x480_ch1_parserinput), 1, fpin);
        fclose(fpin);
    }

    sprintf(fname,"%s/lvds_800x600_ch0_parserinput",parserinput_dir);
    if ( (fpin = fopen(fname,"r" ) ))
    {
        fread(lvds_800x600_ch0_parserinput, sizeof(lvds_800x600_ch0_parserinput), 1, fpin);
        fclose(fpin);
    }
    sprintf(fname,"%s/lvds_800x600_ch1_parserinput",parserinput_dir);
    if ( (fpin = fopen(fname,"r" ) ))
    {
        fread(lvds_800x600_ch1_parserinput, sizeof(lvds_800x600_ch1_parserinput), 1, fpin);
        fclose(fpin);
    }

    printf("Here\n");
    sprintf(fname,"%s/lvds_1024x600_ch0_parserinput",parserinput_dir);
    printf("%s\n" ,fname );
    if ( (fpin = fopen(fname,"r" ) ))
    {
        printf("File %s/lvds_1024x600_ch0_parserinput found 1\n" ,parserinput_dir );
        fread(lvds_1024x600_ch0_parserinput, sizeof(lvds_1024x600_ch0_parserinput), 1, fpin);
        printf("File %s/lvds_1024x600_ch0_parserinput found 2\n" ,parserinput_dir );
        fclose(fpin);
    }
    else
        printf("File %s/lvds_1024x600_ch0_parserinput not found\n" ,parserinput_dir );
    sprintf(fname,"%s/lvds_1024x600_ch1_parserinput",parserinput_dir);
    if ( (fpin = fopen(fname,"r" ) ))
    {
        fread(lvds_1024x600_ch1_parserinput, sizeof(lvds_1024x600_ch1_parserinput), 1, fpin);
        fclose(fpin);
    }
    sprintf(fname,"%s/lvds_1024x768_ch0_parserinput",parserinput_dir);
    if ( (fpin = fopen(fname,"r" ) ))
    {
        fread(lvds_1024x768_ch0_parserinput, sizeof(lvds_1024x768_ch0_parserinput), 1, fpin);
        fclose(fpin);
    }
    sprintf(fname,"%s/lvds_1024x768_ch1_parserinput",parserinput_dir);
    if ( (fpin = fopen(fname,"r" ) ))
    {
        fread(lvds_1024x768_ch1_parserinput, sizeof(lvds_1024x768_ch1_parserinput), 1, fpin);
        fclose(fpin);
    }

}

int main(int argc, char *argv[])
{
FILE *fpin;
char    file_name_in[256];

    bzero(file_contents,sizeof(file_contents));
    bzero(header_defs_dump,sizeof(header_defs_dump));
    bzero(iomux_defs_dump,sizeof(iomux_defs_dump));
    read_parserinput();
    if ( argc > 1 )
    {
        sprintf(file_name_in,"%s",argv[1]);
        if ( (fpin = fopen(file_name_in,"r" ) ))
        {
            fread(file_contents, sizeof(file_contents), 1, fpin);
            fclose(fpin);
        }
    }
    parse_special_iomux();
    store_dts_files(file_name_in);
    return 0;
}


