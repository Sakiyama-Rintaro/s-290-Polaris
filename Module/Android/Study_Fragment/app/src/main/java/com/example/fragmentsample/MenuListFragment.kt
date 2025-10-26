package com.example.fragmentsample

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ListView
import android.widget.SimpleAdapter

// TODO: Rename parameter arguments, choose names that match
// the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
private const val ARG_PARAM1 = "param1"
private const val ARG_PARAM2 = "param2"

/**
 * A simple [Fragment] subclass.
 * Use the [MenuListFragment.newInstance] factory method to
 * create an instance of this fragment.
 */
class MenuListFragment : Fragment() {
    // TODO: Rename and change types of parameters
    private var param1: String? = null
    private var param2: String? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        arguments?.let {
            param1 = it.getString(ARG_PARAM1)
            param2 = it.getString(ARG_PARAM2)
        }
    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        //フラグメントで表示する画面をXMLファイルからインフレート(inflate)する。
        val view = inflater.inflate(R.layout.fragment_menu_list, container, false)
        //画面部品ListViewを取得
        val lvMenu = view.findViewById<ListView>(R.id.lvMenu)
        //SimpleAdapterで使用するMustableListオブジェクトを用意
        val menuList: MutableList<MutableMap<String, String>> = mutableListOf()

        //menuListデータ生成処理
        var menu = mutableMapOf("name" to "からあげ定食", "price" to "800円")
        menuList.add(menu)
        menu = mutableMapOf("name" to "ハンバーグ定食", "price" to "850円")
        menuList.add(menu)
        menu = mutableMapOf("name" to "生姜焼き定食", "price" to "1000円")
        menuList.add(menu)
        menu = mutableMapOf("name" to "ステーキ定食", "price" to "750円")
        menuList.add(menu)
        menu = mutableMapOf("name" to "野菜炒め定食", "price" to "900円")
        menuList.add(menu)
        menu = mutableMapOf("name" to "とんかつ定食", "price" to "900円")
        menuList.add(menu)
        menu = mutableMapOf("name" to "ミンチかつ定食", "price" to "900円")
        menuList.add(menu)
        menu = mutableMapOf("name" to "コロッケ定食", "price" to "850円")
        menuList.add(menu)

        //SimpleAdapter第4引数from用データの用意
        val from = arrayOf("name","price")
        //SimpleAdapter第5引数to用データの用意
        val to = intArrayOf(android.R.id.text1,android.R.id.text2)
        //SimpleAdapterを生成
        val adapter = SimpleAdapter(activity,menuList,android.R.layout.simple_list_item_2, from, to)
        //アダプタの登録
        lvMenu.adapter = adapter
        //インフレートされた画面を戻り値として返す
        return view

        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_menu_list, container, false)
    }

    companion object {
        /**
         * Use this factory method to create a new instance of
         * this fragment using the provided parameters.
         *
         * @param param1 Parameter 1.
         * @param param2 Parameter 2.
         * @return A new instance of fragment MenuListFragment.
         */
        // TODO: Rename and change types and number of parameters
        @JvmStatic
        fun newInstance(param1: String, param2: String) =
            MenuListFragment().apply {
                arguments = Bundle().apply {
                    putString(ARG_PARAM1, param1)
                    putString(ARG_PARAM2, param2)
                }
            }
    }
}