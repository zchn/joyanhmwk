#include <stdio.h>

int main(int argc, char *argv[])
{
        FILE *in;
        FILE *out;
        in = fopen(argv[1],"r");
        out = fopen(argv[2],"wb");
        int n,cnt,i;
        fscanf(in,"%x",&cnt);
        fwrite((char *)&cnt,sizeof(cnt),1,out);
        fscanf(in,"%x",&n);
        fwrite((char *)&n,sizeof(n),1,out);
        for(i = 0; i < cnt; i++){
                fscanf(in,"%x",&n);
                fwrite((char *)&n,sizeof(n),1,out);
        }
        fclose(in);
        fclose(out);
        return 0;
}

