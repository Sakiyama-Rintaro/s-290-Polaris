package com.example.androidsystem_for_test

import android.content.Context
import android.hardware.usb.UsbDeviceConnection
import android.hardware.usb.UsbManager
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.TextView
import com.hoho.android.usbserial.driver.UsbSerialDriver
import com.hoho.android.usbserial.driver.UsbSerialPort
import com.hoho.android.usbserial.driver.UsbSerialProber
import java.lang.Thread.sleep
import kotlin.concurrent.thread

class MainActivity : AppCompatActivity() {

    var airspeed: Double = 0.0   //対気速度
    var rpm: Int = 0             //回転数
    var altitude: Double = 0.0   //高度

    private lateinit var port: UsbSerialPort

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)


        //TextViewのインスタンスを取得
        val airspeed_TextView = findViewById<TextView>(R.id.Airspeed)
        val rpm_TextView = findViewById<TextView>(R.id.Rpm)
        val altitude_TextView = findViewById<TextView>(R.id.Altitude)


        //TextView表示
        airspeed_TextView.setText(airspeed.toString())
        rpm_TextView.setText(rpm.toString())
        altitude_TextView.setText(altitude.toString())

    }

    /*---------ボタンクリックイベント----------*/
    fun cone(view: View){//lpc1768とAndroidの接続開始
        Log.i("TAG","cone")
        serialCon()
    }

    fun read(view: View){//lpc1768から情報受信開始
        Log.i("TAG","read")

        thread {//別スレッド(マルチスレッド開始)
            serial()
        }
    }



    fun close(view: View){//lpc1768とAndroidの接続解除
        Log.i("TAG","close")
    }

    private fun serialCon(){
        try{//エラーが発生するかもしれない処理

            var manager = getSystemService(Context.USB_SERVICE) as UsbManager
            var availableDrivers: List<UsbSerialDriver> =
                    UsbSerialProber.getDefaultProber().findAllDrivers(manager)



            if(availableDrivers.isEmpty()){
                Log.i("TAG","Empty")
                return
            }

            Log.i("TAG","Success")

            val driver: UsbSerialDriver = availableDrivers[0]

            val connection: UsbDeviceConnection = manager.openDevice(driver.device)

            if(connection == null){
                Log.i("TAG","Connection == null")
                return
            }

            port = driver.ports[0]

            port.open(connection);

            port.setParameters(115200,8,UsbSerialPort.STOPBITS_1,UsbSerialPort.PARITY_NONE)

            Log.i("TAG","Success_Connect")

            //var auth_TextView_1 = findViewById<TextView>(R.id.Auth_1)
            //auth_TextView_1.text = "Success_Connect"


        } catch(e: Exception){//例外処理
            runOnUiThread{
                //var auth_TextView_2 = findViewById<TextView>(R.id.Auth_2)
                //auth_TextView_2.text = "権限が取得できていません"
            }
        }
    }

    fun serial(){
        //受信データ長
        var data_length = 0
        //32個のByte(8bit)配列 変数名response を用意 実際の受信データが入る
        // 1Byte(8bit)でASCII文字 1文字を表せる
        var recieve_data = ByteArray(32)

        while(true){
            //受信
            sleep(500)
            data_length = port.read(recieve_data,10)

            //受信チェック
            if(data_length == 0){//データなし
                Log.i("TAG","Non_DATA")
            } else {//データあり
                Log.i("TAG","$data_length")
            }

            hantei(data_length,recieve_data)
        }
    }

    fun hantei(data_length: Int,recieve_data: ByteArray){
        if(data_length == 4){//正常時(受信文字数が11文字(11Byte))

            call(recieve_data)//受信データ復号

            return
        } else{
            return
        }
    }

    fun call(recieve_data: ByteArray){
        //val rec_data_TextView = findViewById<TextView>(R.id.Rec_data)
        /*----------受信データ----------*/
        // 1文字目     "A"
        // 2 ~ 5文字目 "対気速度・回転数・高度情報"
        // 6文字目     "チェックサム"

        var rec_airspeed_TextView = findViewById<TextView>(R.id.Airspeed)
        val rec_rpm_TextView = findViewById<TextView>(R.id.Rpm)
        val rec_altitude = findViewById<TextView>(R.id.Altitude)

        //受信文字列    A    H E L L O W O R L D

        Log.i("TAG", "byte: ${recieve_data[0]},${recieve_data[1]},${recieve_data[2]},${recieve_data[3]}")

        if(recieve_data[0].toChar() == 'A'){

            runOnUiThread { rec_airspeed_TextView.text = "${recieve_data[1].toDouble() / 10}"}
            runOnUiThread { rec_rpm_TextView.text = "${recieve_data[2].toInt()}" }
            runOnUiThread { rec_altitude.text = "${recieve_data[3].toDouble() / 10}" }


            /*for (i in 1..10){
                runOnUiThread { rec_data_TextView.text = "${recieve_data[i].toChar()}" }

                sleep(500)


            }*/

        } else {
            Log.i("TAG","Error_DATA !")
        }
    }
}