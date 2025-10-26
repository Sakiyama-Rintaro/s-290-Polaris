package com.example.study_arcgis

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.esri.arcgisruntime.ArcGISRuntimeEnvironment
import com.esri.arcgisruntime.mapping.ArcGISMap
import com.esri.arcgisruntime.mapping.BasemapStyle
import com.esri.arcgisruntime.mapping.Viewpoint
import com.esri.arcgisruntime.mapping.view.MapView
import com.example.study_arcgis.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private val activityMainBinding by lazy{
        ActivityMainBinding.inflate(layoutInflater)
    }

    private val mapView: MapView by lazy{
        activityMainBinding.mapView
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(activityMainBinding.root)

        setupMap()
    }

    override fun onPause(){
        mapView.pause()
        super.onPause()
    }

    override fun onResume(){
        super.onResume()
        mapView.resume()
    }

    override fun onDestroy(){
        mapView.dispose()
        super.onDestroy()
    }

    //マップの設定(onCreate()からの呼び出し)
    private fun setupMap(){

        //APIキーをソースコードに残してはならない
        ArcGISRuntimeEnvironment.setApiKey("AAPK2c1a9c4144a544d2bee9d14a9b724c1da-HNRH8_ISV1hloA3FQliB3xVJht6-_C1ucLMe4N6yGdFIsRH67Se7rsoUgRTX8R")

        //BasemapStyleで地図を作成
        val map = ArcGISMap(BasemapStyle.ARCGIS_TOPOGRAPHIC)

        mapView.map = map

        //視点のViewpoint(緯度, 経度, スケール)
        mapView.setViewpoint(Viewpoint(35.360626,138.727363,200000.0))
    }
}