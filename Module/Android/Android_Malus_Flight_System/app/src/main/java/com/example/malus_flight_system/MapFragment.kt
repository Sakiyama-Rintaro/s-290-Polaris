package com.example.malus_flight_system

import android.graphics.Color
import android.os.Bundle
import android.util.Log
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.esri.arcgisruntime.ArcGISRuntimeEnvironment
import com.esri.arcgisruntime.geometry.PolylineBuilder
import com.esri.arcgisruntime.geometry.SpatialReference
import com.esri.arcgisruntime.mapping.ArcGISMap
import com.esri.arcgisruntime.mapping.view.Graphic
import com.esri.arcgisruntime.mapping.view.GraphicsOverlay
import com.esri.arcgisruntime.mapping.view.LocationDisplay
import com.esri.arcgisruntime.mapping.view.MapView
import com.esri.arcgisruntime.symbology.SimpleLineSymbol
import com.esri.arcgisruntime.symbology.SimpleRenderer
import kotlin.math.roundToInt




class MapFragment() : Fragment(),LocationDisplay.LocationChangedListener  {
    var mMapView: MapView? = null
    private var mLocationDisplay: LocationDisplay? = null
    lateinit var lineOverlay:GraphicsOverlay
    lateinit var polylineBuilder: PolylineBuilder


    override fun onCreateView(
            inflater: LayoutInflater,
            container: ViewGroup?,
            savedInstanceState: Bundle?
    ): View {
        // Inflate the layout for this fragment
        val view: View = inflater.inflate(R.layout.fragment_map, container, false)
        //APIKeyセット
        ArcGISRuntimeEnvironment.setApiKey("AAPK75bf5576c3044696842788cfd958d408RAs0k5as0_fQMEicoqmuLXJB1cOjBKYh5_S_gBs21iHUco9ifGef6DhFnbrGezLB")
        mMapView= view.findViewById<View>(R.id.mapView) as MapView
        //Mapセット
        val map = ArcGISMap("http://www.arcgis.com/home/item.html?id=41df484a0a204caf96a03d3e4a390867")
        mMapView!!.map = map

        //line
        lineOverlay = GraphicsOverlay()
        val polyLineSymbol = SimpleLineSymbol(SimpleLineSymbol.Style.SOLID, Color.BLUE, 2f)
        lineOverlay.renderer = SimpleRenderer(polyLineSymbol)

        //point,line追加
        mMapView!!.graphicsOverlays.add(lineOverlay)
        //lineBuilderをWGS84(KID:4326)で生成
        polylineBuilder = PolylineBuilder(SpatialReference.create(4326))

        // MapView 上に現在位置を表示するために LocationDisplay を取得
        mLocationDisplay = mMapView!!.locationDisplay
        // LocationDisplay に LocationListner を設定
        mLocationDisplay!!.addLocationChangedListener(this)
        // 現在位置の表示を開始
        mLocationDisplay!!.startAsync()
        mMapView!!.locationDisplay.autoPanMode = LocationDisplay.AutoPanMode.RECENTER
        mMapView!!.locationDisplay.initialZoomScale = 300000.0
        return view
    }
    var oldPointLat=0.0
    var oldPointLon=0.0
    override fun onLocationChanged(locationChangedEvent: LocationDisplay.LocationChangedEvent) {
        if (locationChangedEvent == null) {
            return
        }
        Log.d("oldLat",oldPointLat.toString())
        Log.d("oldLon",oldPointLon.toString())
        var newLon = locationChangedEvent.location.position.x//経度
        var newLat = locationChangedEvent.location.position.y//緯度

        var newPointLon = (newLat * 1000000.0).roundToInt() / 1000000.0//桁丸めるxx.xxxxxx
        var newPointLat = (newLon * 1000000.0).roundToInt() / 1000000.0//桁丸めるxxx.xxxxxx
        Log.d("newLat",newPointLat.toString())
        Log.d("newLon",newPointLon.toString())
        if(newPointLat!=oldPointLat || newPointLon!=oldPointLon ){
            addPolyline(newLon,newLat)
            Log.d("add","added!")
            oldPointLat = newPointLat
            oldPointLon = newPointLon
        }


    }

    override fun onPause() {
        mMapView!!.pause()
        super.onPause()
    }

    override fun onResume() {
        super.onResume()
        mMapView!!.resume()
    }

    fun addPolyline(newPointLon: Double,newPointLat:Double){
        polylineBuilder.addPoint(newPointLon,newPointLat)
        Log.d("xy",newPointLat.toString())
        lineOverlay.graphics.apply {
            clear()
            add(Graphic(polylineBuilder.toGeometry()))
        }
    }
}

