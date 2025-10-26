#include"mbed.h"
#include"TextOLED.h"

#define addr1 0x01 //対気速度計の無線アドレス
#define addr2 0x02 //回転数計の無線アドレス
#define addr3 0x03 //姿勢センサの無線アドレス
#define addr4 0x04 //心拍計の無線アドレス(前部P)
#define addr5 0x05 //心拍計の無線アドレス(後部P)

#define ReceptLength 5 //twelite受信データ - 1

#define Front_BPM_Integer 103 //前部P 心拍数 校正値
#define Back_BPM_Integer 103  //後部P 心拍数 校正値

Serial pc(USBTX,USBRX);
Serial SD_gps(p9,p10);//tx: openlog rx: gps_lpc1114
Serial Android_twe(p13,p14);//tx: Android rx: twe_lpc1114
Serial sound_ER(p28,p27);//tx: sound_lpc1114 rx: ER_lpc1768

InterruptIn Log_sw(p21);//GPS_logスイッチ
InterruptIn Sound_down(p22);
InterruptIn Sound_up(p23);

AnalogIn alt(p20);

TextOLED oled(p11,p12,p30,p29,p15,p16);

DigitalOut gps_log(p17);

DigitalOut led1(LED1);
DigitalOut led2(LED2);//twe_lpc1114 受信
DigitalOut led3(LED3);//ER_lpc1768 受信
DigitalOut led4(LED4);//ログスイッチ

Ticker ticker_update, ticker_alt;
Timer t;

int sec;//経過時間

int main_log;

int log_count = 0;//ログ回数

double airspeed = 0;//対気速度
int rpm = 0;//回転数
double altitude = 0;//高度
int front_bpm = 0;//前部P心拍数
int back_bpm = 0;//後部P心拍数
double temp = 0;//温度

int rec_bpm_f = 0;
int rec_bpm_b = 0;

int airspeed_2 = 0;
int altitude_2 = 0;

char ele_data, rud_data;//ERマイコンから受け取るデータ

int spdPacket[6];
int altPacket[6];
int spdCk = 0;
int altCk = 0;

char rec_data[6];

//プロトタイプ宣言
void Log_sign_on();
void Log_sign_off();
void recept_from_ER();
void Altitude();
void twe_recieve();
void twe_cal();
void update();
void send_to_android();
void OLED_print();
void SD();
void send_sound_data();

int main()
{
    /*-------タイマースタート-------*/
    t.start();

    gps_log = 0;

    oled.locate(0,0);
    oled.printf("Start TBT!!");

    /*--------ボーレート設定--------*/
    SD_gps.baud(9600);
    Android_twe.baud(9600);
    sound_ER.baud(115200);

    /*-------シリアル通信設定-------*/
    Android_twe.format(8,Serial::None,1);

    /*---------割り込み設定---------*/
    Log_sw.rise(&Log_sign_on);
    Log_sw.fall(&Log_sign_off);
    sound_ER.attach(recept_from_ER,Serial::RxIrq);
    Android_twe.attach(twe_recieve,Serial::RxIrq);
    ticker_update.attach(&update,0.5);
    ticker_alt.attach(&Altitude,0.1);

    while(1){
    }
}

/*-----------------Log取り開始-------------------*/
void Log_sign_on()
{
    led4 = 1;

    SD_gps.printf("Start Logging ! \r\n");

    main_log = 1;

    /*-----------GPS受信開始------------*/
    gps_log = 1;
}

/*-----------------Log取り終了-------------------*/
void Log_sign_off()
{
    led4 = 0;

    SD_gps.printf("Stop Logging ! \r\n");

    main_log = 0;

    /*-----------GPS受信終了------------*/
    gps_log = 0;
}

/*--------------ER_pc1768から受信---------------*/
void recept_from_ER()
{
    led3 = 1;
    ele_data = sound_ER.getc();
    rud_data = sound_ER.getc();

    wait(0.1);
    led3 = 0;
}

/*----------------高度計から受信-----------------*/
void Altitude()
{
    altitude = alt.read()*3.3*1000/1.6/100;
}

/*-----------twe_lpc1768から受信----------------*/
void twe_recieve()
{

    /*twe_lpc1114から送られてくるデータ*/

    // rec_data[0]    : 対気速度データ
    // rec_data[1]    : 回転数データ
    // rec_data[2]    : 姿勢センサデータ
    // rec_data[3]    : 心拍データ(前部P)
    // rec_data[4]    : 心拍データ(後部P)
    // rec_data[5]    : 温度データ

    if(Android_twe.getc() == 'A'){

        led2 = 1;

        for(int i = 0; i < ReceptLength; i++){
            rec_data[i] = Android_twe.getc();
        }
    }

    twe_cal();
}

/*-----------twelite受信データ 復号--------------*/
void twe_cal() 
{
    /*---------対気速度データ復号----------*/
    pc.printf("Rec_data[0] : %c\r\n",rec_data[0]);
    airspeed = (double)((rec_data[0] -'0') / 10);
    pc.printf("Airspeed : %lf m/s\r\n",airspeed);

    /*-----------回転数データ復号----------*/
    pc.printf("Rec_data[1] : %c\r\n",rec_data[1]);
    rpm = rec_data[1] - '0';
    pc.printf("RPM : %d /m\r\n",rpm);

    /*-----------姿勢角データ復号----------*/


    /*---------心拍データ(前部)復号--------*/
    rec_bpm_f = rec_data[3] - '0';
    front_bpm = rec_bpm_f + Front_BPM_Integer;
    pc.printf("Front BPM : %d bpm\r\n",front_bpm);

    /*---------心拍データ(後部)復号--------*/
    rec_bpm_b = rec_data[4] - '0';
    //back_bpm = rec_bpm_b + Back_BPM_Integer;
    //pc.printf("Back BPM : %d bpm\r\n",back_bpm);

    /*---------温度データ復号----------*/
    temp = (double)((rec_data[5] - '0') / 10);
    pc.printf("Temperature : %lf\r\n",temp);

    wait(0.1);

    led2 = 0;
}

/*-------------シリアル送信(全体)----------------*/
void update()
{
    send_to_android(); //to_Android
    OLED_print();      //to_OLED
    SD();              //to_OpenLog
    send_sound_data(); //to_sound_lpc1114
}

/*---------------Android端末に送信---------------*/
void send_to_android()
{
    // A 0 0 0 X X
    // [0]識別子, [1~3]ペイロード, [4~5]チェックサム

    airspeed_2 = airspeed * 10;
    altitude_2 = altitude * 10;

    /*----対気速度Packet構築----*/
    spdPacket[0] = 'S';

    spdPacket[3] = airspeed_2 % 10;
    airspeed_2 /= 10;
    spdPacket[2] = airspeed_2 % 10;
    airspeed_2 /= 10;
    spdPacket[1] = airspeed_2 % 10;

    spdCk = spdPacket[1] + spdPacket[2] + spdPacket[3];
    spdPacket[4] = spdCk / 10;
    spdPacket[5] = spdCk % 10;

    /*----高度Packet構築----*/
    altPacket[0] = 'A';

    altPacket[3] = altitude_2 % 10;
    altitude_2 /= 10;
    altPacket[2] = altitude_2 % 10;
    altitude_2 /= 10;
    altPacket[1] = altitude_2 % 10;
    
    altCk = altPacket[1] + altPacket[2] + altPacket[3];
    altPacket[4] = altCk / 10;
    altPacket[5] = altCk % 10;

    for(int i = 0; i < 6; i++){
        Android_twe.putc(spdPacket[i]);
    }
    
    for(int i = 0; i < 6; i++){
        Android_twe.putc(altPacket[i]);
    }
}

/*------------------OLEDに送信------------------*/
void OLED_print()
{
    sec = t.read();

    oled.locate(0,0);
    oled.printf("Time:%d",sec);

    oled.locate(8,0);
    oled.printf("sec");

    oled.locate(0,1);
    oled.printf("r%3d",rpm);

    oled.locate(5,1);
    oled.printf("v%2.1f",airspeed);

    oled.locate(11,1);
    oled.printf("h%2.1f",altitude);
}

/*--------OpenLog(SDカード)に送信--------------*/
void SD()
{
    if(main_log == 1){

        log_count++;

        SD_gps.printf("No:%d\r\n",log_count);
        SD_gps.printf("Rpm:%d\r\n",rpm);
        SD_gps.printf("Airspeed:%4.1f m/s\r\n",airspeed);
        SD_gps.printf("Altitude:%3.1f m\r\n",altitude);
        SD_gps.printf("FrontBPM:%d bpm\r\n",front_bpm);
        SD_gps.printf("BackBPM:%d bpm\r\n",back_bpm);
        SD_gps.printf("Temperature:%4.1f\r\n",temp);
        SD_gps.printf("ele_data:%c\r\n",ele_data);
        SD_gps.printf("rud_data:%c\r\n",rud_data);

    }
}

/*------------Sound_lpc1114に送信--------------*/
void send_sound_data()
{
    if(5 <= altitude && altitude < 10){
        sound_ER.putc('A');
    } else if(1 <= altitude && altitude < 5){
        sound_ER.putc('B');
    } else if(altitude < 1){
        sound_ER.putc('C');
    }
}
