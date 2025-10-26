#include"mbed.h"

Serial twe(dp16,dp15);
InterruptIn speedcount(dp25);

Ticker t1;

int counter=0;

double kisoku_1 = 0;
int kisoku_2 = 0;

char data;

//プロトタイプ宣言
void spd_c();
void spd_f();
void spd_send();

int main()
{
    twe.baud(115200);
    t1.attach(&spd_f,0.5);
    speedcount.rise(&spd_c);

    twe.printf("Start Airspeed \r\n");

    while(1)
    {
    }
}

void spd_c()//フォトインタラプタ反応回数計測
{
    counter++;
}

void spd_f()//機速の計算
{
    if(counter < 4){
        kisoku_1 = 0;
    }else{
        kisoku_1 = 0.0782*counter + 3.9023;//機速とフォトインタラプタの反応回数の関係式
    }

    spd_send();

    counter = 0;
}

void spd_send()//データ送信用関数
{
    kisoku_2 = (int)(kisoku_1*10);

    data = '0' + kisoku_2;//無線送信の為,数値から文字への変換intからcharへ

    twe.putc(0xA5);//ヘッダ
    twe.putc(0x5A);//ヘッダ
    twe.putc(0x80);//送信するデータ長を指定するコマンド
    twe.putc(0x04);//送信するデータ長(4)

    twe.putc(0x00);//受信機(メイン)ID
    twe.putc(0x00);
    twe.putc(0x00);
    twe.putc(data);//送信したいデータ  

    twe.putc(data);//チェックサム
}
