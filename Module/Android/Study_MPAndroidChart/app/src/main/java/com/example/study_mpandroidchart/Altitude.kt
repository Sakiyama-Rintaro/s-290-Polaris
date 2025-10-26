package com.example.study_mpandroidchart

import android.graphics.Color
import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.github.mikephil.charting.charts.BarChart
import com.github.mikephil.charting.components.XAxis
import com.github.mikephil.charting.components.YAxis
import com.github.mikephil.charting.data.BarData
import com.github.mikephil.charting.data.BarDataSet
import com.github.mikephil.charting.data.BarEntry
import com.github.mikephil.charting.interfaces.datasets.IBarDataSet

class Altitude : Fragment() {

    var value:Float=0f
    companion object {//インスタンス生成
    private const val Key = "ALT"//bundle用Key設定
        fun createInstance(value:Float): Altitude {
            val altFrag = Altitude()//Fragmentインスタンス生成
            val args = Bundle()//bundleインスタンス生成
            args.putFloat(Key, value)//データ設定
            altFrag.arguments = args
            return altFrag
        }
    }

    private lateinit var chart: BarChart
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val bundle = arguments
        if (bundle != null) {
            value = bundle.getFloat(Key)//データ取得
        }
        getBarData(value)

    }

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        // Inflate the layout for this fragment
        val view: View = inflater.inflate(R.layout.fragment_altitude, container, false)
        //以下View設定

        chart = view.findViewById(R.id.altView)

        //表示データ取得
        val data = BarData(getBarData(value))
        chart.data = data

        //縦軸(左)設定
        val left: YAxis = chart.axisLeft
        left.axisMinimum = 0f
        left.axisMaximum = 10f
        left.labelCount = 5
        left.setDrawTopYLabelEntry(true)
        left.setDrawGridLines(true)

        //縦軸(右)設定
        val right: YAxis = chart.axisRight
        right.setDrawLabels(false)
        right.setDrawGridLines(false)
        right.setDrawZeroLine(false)
        right.setDrawTopYLabelEntry(false)

        //横軸設定
        val bottomAxis: XAxis = chart.xAxis
        bottomAxis.position = XAxis.XAxisPosition.BOTTOM
        bottomAxis.setDrawLabels(false)
        bottomAxis.setDrawGridLines(false)
        bottomAxis.setDrawAxisLine(false)

        //オプション設定
        chart.setDrawValueAboveBar(false)
        chart.description.isEnabled = false
        chart.isClickable = false
        data.setValueTextSize(20f)//値テキストサイズ


        //凡例設定
        chart.legend.isEnabled = false
        chart.setScaleEnabled(false)
        return view
    }
    private fun getBarData(value: Float): List<IBarDataSet>? {
        //表示させるデータ
        val entries: ArrayList<BarEntry> = ArrayList()
        entries.add(BarEntry(0f, value))
        val bars: MutableList<IBarDataSet> = ArrayList()
        val dataSet = BarDataSet(entries, "bar")

        //ハイライトさせない
        dataSet.isHighlightEnabled = false
        var color:String
        if (value in 1.0..5.0){
            color = "#00AA90"
        }else {
            color = "#CB1B45"
        }
        dataSet.color = Color.parseColor(color)//バー色
        bars.add(dataSet)
        return bars
    }

}
