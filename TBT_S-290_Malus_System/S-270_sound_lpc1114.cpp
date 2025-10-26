#include"mbed.h"

Serial sound(dp16,dp15);

char get_command;

int main()
{
    wait(0.1);
    sound.putc(0x7E);
    sound.putc(0xFF);
    sound.putc(0x06);
    sound.putc(0x09);//起動コマンド
    sound.putc(0x00);
    sound.putc(0x00);
    sound.putc(0x01);
    sound.putc(0xEF);

    wait(1);

    while(1){

        get_command = sound.getc();//main からのシリアルコマンド

        if(get_command == 'A'){//高度 5m以上10m未満

            sound.putc(0x7E);
            sound.putc(0xFF);
            sound.putc(0x06);
            sound.putc(0x0F);//フォルダ指定再生コマンド
            sound.putc(0x00);
            sound.putc(0x01);//フォルダ名「01」
            sound.putc(0x01);//ファイル名「001.mp3」
            sound.putc(0xEF);

        } else if(get_command == 'B'){//高度 1m以上5m未満

            sound.putc(0x7E);
            sound.putc(0xFF);
            sound.putc(0x06);
            sound.putc(0x0F);//フォルダ指定再生コマンド
            sound.putc(0x00);
            sound.putc(0x01);//フォルダ名「01」
            sound.putc(0x02);//ファイル名「002.mp3」
            sound.putc(0xEF);        

        } else if(get_command == 'C'){//高度 1m未満

            sound.putc(0x7E);
            sound.putc(0xFF);
            sound.putc(0x06);
            sound.putc(0x0F);//フォルダ指定再生コマンド
            sound.putc(0x00);
            sound.putc(0x01);//フォルダ名「01」
            sound.putc(0x03);//ファイル名「003.mp3」
            sound.putc(0xEF);        

        }  
    }
}

