package com.example.point_display_arcgis

import android.net.Uri
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.ImageView
import android.widget.LinearLayout
import com.esri.arcgisruntime.ArcGISRuntimeEnvironment
import com.esri.arcgisruntime.geometry.Point
import com.esri.arcgisruntime.geometry.SpatialReferences
import com.esri.arcgisruntime.mapping.ArcGISMap
import com.esri.arcgisruntime.mapping.BasemapStyle
import com.esri.arcgisruntime.mapping.Viewpoint
import com.esri.arcgisruntime.mapping.view.Graphic
import com.esri.arcgisruntime.mapping.view.GraphicsOverlay
import com.esri.arcgisruntime.mapping.view.MapView
import com.esri.arcgisruntime.symbology.SimpleLineSymbol
import com.esri.arcgisruntime.symbology.SimpleMarkerSymbol
import com.example.point_display_arcgis.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private val activityMainBinding by lazy {
        ActivityMainBinding.inflate(layoutInflater)
    }

    private val mapView: MapView by lazy {
        activityMainBinding.mapView
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(activityMainBinding.root)
        setupMap()

        addGraphics()

        /*-----Display plane symbol------*/
        //val image_Plane: ImageView = findViewById(R.id.image_plane)
        //image_Plane.setImageResource(R.drawable.plane)
    }

    override fun onResume(){
        super.onResume()
        mapView.resume()
    }

    override fun onPause() {
        super.onPause()
        mapView.pause()
    }

    override fun onDestroy() {
        super.onDestroy()
        mapView.dispose()
    }

    private fun setupMap(){

        //set API key
        ArcGISRuntimeEnvironment.setApiKey("AAPK2c1a9c4144a544d2bee9d14a9b724c1da-HNRH8_ISV1hloA3FQliB3xVJht6-_C1ucLMe4N6yGdFIsRH67Se7rsoUgRTX8R")

        //create a map
        val map = ArcGISMap(BasemapStyle.ARCGIS_TOPOGRAPHIC)

        mapView.map = map
        //琵琶湖(緯度: 北緯35度20分0秒, 経度: 東経136度10分0秒)
        mapView.setViewpoint(Viewpoint(35.2000,136.1000,72000.0))


    }

    private fun addGraphics(){
        //create a graphics overlay
        val graphicsOverlay = GraphicsOverlay()
        mapView.graphicsOverlays.add(graphicsOverlay)

        CreatePictureMarkerSymbolFromUrl(graphicsOverlay)


        //select point graphic
        //Point(latitude, longitude, spatial reference)
        val point = Point(136.1000, 35.2000, SpatialReferences.getWgs84())

        //figure of point graphic
        //should use "STYLE_PATH"
        val simpleMarkerSymbol = SimpleMarkerSymbol(SimpleMarkerSymbol.Style.CIRCLE, -0xa8cd, 10f)
        val blueOutlineSymbol = SimpleLineSymbol(SimpleLineSymbol.Style.SOLID, -0xff9c01, 2f)
        simpleMarkerSymbol.outline = blueOutlineSymbol

        val pointGraphic = Graphic(point, simpleMarkerSymbol)

        //add the point graphic to the graphic overlay
        graphicsOverlay.graphics.add(pointGraphic)
    }

    //create picture marker symbol
    private fun CreatePictureMarkerSymbolFromUrl(graphicsOverlay: GraphicsOverlay){
        val symbolUri = Uri()
    }
}
