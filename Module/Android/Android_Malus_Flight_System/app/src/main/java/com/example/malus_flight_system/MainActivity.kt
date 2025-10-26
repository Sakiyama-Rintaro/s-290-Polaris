package com.example.malus_flight_system

import android.Manifest
import android.content.Context
import android.content.Intent
import android.content.pm.PackageManager
import android.hardware.usb.UsbDeviceConnection
import android.hardware.usb.UsbManager
import android.location.Location
import android.location.LocationListener
import android.location.LocationManager
import android.os.Bundle
import android.provider.Settings
import android.util.Log
import android.view.View
import android.view.WindowManager
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import java.util.*
import kotlin.concurrent.thread

open class MainActivity : AppCompatActivity(), LocationListener {

    private val spdKey = "SPD"
    private val mapKey = "MAP"
    private val altKey = "ALT"
    private val timerKey = "TIME"
    private lateinit var locationManager: LocationManager
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        window.addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON)
        val fragmentManager = supportFragmentManager
        val fragmentTransaction = fragmentManager.beginTransaction()//トランザクション開始
        fragmentTransaction.add(R.id.map_container, MapFragment())

        fragmentTransaction.commit()//トランザクション終了

        if (ContextCompat.checkSelfPermission(this,
                        Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this,
                    arrayOf(Manifest.permission.ACCESS_FINE_LOCATION),
                    1000)
        } else {
            locationStart()

            if (::locationManager.isInitialized) {
                locationManager.requestLocationUpdates(
                        LocationManager.GPS_PROVIDER,
                        1000,
                        1f,
                        this)
            }

        }


    }


    private fun locationStart() {
        Log.d("debug", "locationStart()")

        // Instances of LocationManager class must be obtained using Context.getSystemService(Class)
        locationManager = getSystemService(Context.LOCATION_SERVICE) as LocationManager

        val locationManager = getSystemService(Context.LOCATION_SERVICE) as LocationManager

        if (locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER)) {
            Log.d("debug", "location manager Enabled")
        } else {
            // to prompt setting up GPS
            val settingsIntent = Intent(Settings.ACTION_LOCATION_SOURCE_SETTINGS)
            startActivity(settingsIntent)
            Log.d("debug", "not gpsEnable, startActivity")
        }

        if (ContextCompat.checkSelfPermission(this,
                        Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this,
                    arrayOf(Manifest.permission.ACCESS_FINE_LOCATION), 1000)

            Log.d("debug", "checkSelfPermission false")
            return
        }

        locationManager.requestLocationUpdates(
                LocationManager.GPS_PROVIDER,
                1000,
                1f,
                this)

    }

    //フルスクリーン↓ by公式リファレンス
    override fun onWindowFocusChanged(hasFocus: Boolean) {
        super.onWindowFocusChanged(hasFocus)
        if (hasFocus) hideSystemUI()
    }

    private fun hideSystemUI() {
        // Enables regular immersive mode.
        // For "lean back" mode, remove SYSTEM_UI_FLAG_IMMERSIVE.
        // Or for "sticky immersive," replace it with SYSTEM_UI_FLAG_IMMERSIVE_STICKY
        window.decorView.systemUiVisibility = (View.SYSTEM_UI_FLAG_IMMERSIVE
                // Set the content to appear under the system bars so that the
                // content doesn't resize when the system bars hide and show.
                or View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                or View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                or View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                // Hide the nav bar and status bar
                or View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                or View.SYSTEM_UI_FLAG_FULLSCREEN)
    }

    //フルスクリーン↑

    private var newLat:Double=0.0
    private var newLon:Double=0.0

    override fun onLocationChanged(location: Location) {
        newLat = location.latitude
        newLon = location.longitude
    }

    private val corrctData = mutableListOf<Byte>()
    private fun check(data: ByteArray, length: Int) { // 確認処理
        if (length == 12) {//繋がってきたとき
            detection(data)
            corrctData.clear()//リセット。（不正データの後に正しいデータが入るとfix関数のclear()が実行されないため。
        } else if (length < 12) {//分離されてきたとき
            correction(length, data)
        }
    }

    private fun correction(length: Int, data: ByteArray) { //データ補正
        for (i in 0 until length) {
            corrctData += data[i]
        }
        if (corrctData.size == 12) {
            detection(corrctData.toByteArray())//mutableList<Byte>で宣言されているため、ByteArrayに統一
            corrctData.clear()
        }
    }


    private fun detection(data: ByteArray) {//誤り検知
        var spdValue: Float
        var altValue: Float
        var txCkSum: Int
        var rxCkSum: Int
        if (data[0].toChar() == 'S') {

            txCkSum = data[4] * 10 + data[5]
            rxCkSum = data[1] + data[2] + data[3]
            if (txCkSum == rxCkSum) {
                spdValue = data[1].toFloat() * 10 + data[2].toFloat() + data[3].toFloat() / 10
                if (data[6].toChar() == 'A') {
                    txCkSum = data[10] * 10 + data[11]
                    rxCkSum = data[7] + data[8] + data[9]
                    if (txCkSum == rxCkSum) {
                        altValue =
                                data[7].toFloat() * 10 + data[8].toFloat() + data[9].toFloat() / 10
                        updateGraph(spdValue, altValue)
                    }
                }
            }
        }
    }

    private fun updateGraph(spdValue: Float, altValue: Float) {
        val fragmentManager = supportFragmentManager
        val fragmentTransaction = fragmentManager.beginTransaction()
        fragmentTransaction.commit()
    }

    fun reset(view: View) { //接続受信待機
        Toast.makeText(this, "Activity: RESET", Toast.LENGTH_LONG).show()
    }


}