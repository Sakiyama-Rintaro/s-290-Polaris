![s-270logo](https://user-images.githubusercontent.com/61620703/133873620-3252d696-a6b6-4d22-a7cf-28cc065be1b1.jpg)

# S-270 Malus 電装システム

## はじめに
初めまして。S-270電装班長を担当したDoritosこと檜山凌祐です。所属学科はシステム理工学部機械制御システム学科です。元々VRに興味があり、何かヒントが得られるのではと思い電装班に入った次第です。<br>
後輩の皆さんにとって、今後の電装システム構築・運用の参考になるようにS-270の電装システムの技術資料をここに残しておきたいと思います。<br>
<br>
このリポジトリでは、**人力飛行機電装システム**において<br>
・Mainプリント基板設計・製作<br>
・計測システム・ソフトウェア設計・製作<br>
・操舵システム・ソフトウェア設計・製作<br>
・各種試験系(回転試験・ER試験・全体接合・TF)<br>
に関することが詰まっています。<br>
<br>

Android周りのシステムに関することは、21代電装班員であるあらじんこと長坂新が詳しくまとめていますので、彼のリポジトリを参考にしてください。
**[arajin.21st.denso.tbt](https://github.com/sin0111/arajin.21st.denso.tbt)**<br>
姿勢角計に関することは、21代電装班員であるくろこと古殿幸助が詳しくまとめていますので、彼のリポジトリを参考にしてください。
**[kuroart.21st.denso.tbt](https://github.com/kuroart/tbt.denso.21st)**<br>
温度計に関することは、22代電装班員であるMAXこと太田秀大が詳しくまとめていますので、彼のリポジトリを参考にしてください。<br>

心拍計に関することは、22代電装班員であるグロスこと山嵜大瑚が詳しくまとめていますので、彼のリポジトリを参考にしてください。
**[gurosu.22nd.denso.tbt](https://github.com/d-goo/gurosu.tbt.denso.22nd)**<br>

## 後輩の皆さんへ
我々21代電装班では、「同期や後輩の為にしっかりと技術資料を残す」という方針で活動していました。それは、教え合いの文化を形成し効率的な技術力アップを図るためであったり、コロナ禍による鳥コン出場断念の無念を後輩達に晴らして欲しいという願いであったりと様々です。<br>
無念については特に気にしなくていいですが、教え合いの文化と技術資料を残す文化だけは、引き継いでいって欲しいなと思っています。僕からの願いです。( ﾟДﾟ)<br>
モノづくりを楽しんで、充実した大学生活を送ってください！！<br>

## リポジトリの説明
**・[TBT_S-270_Malus_System](https://github.com/Ryosuke-123/doritos.tbt.denso.21st/tree/main/TBT_S-270_Malus_System)** //完成品が入っています。プログラム書き込み方法と基板の取り扱いについては、このリポジトリのREADMEを参考にしてください。<br>
**・[Module](https://github.com/Ryosuke-123/doritos.tbt.denso.21st/tree/main/Module)** //単体テストで用いたものが入っています。<br>
**・[Yosan](https://github.com/Ryosuke-123/doritos.tbt.denso.21st/tree/main/Yosan)** //S-270での購入品についてのデータが入っています。<br>
**・[doc](https://github.com/Ryosuke-123/doritos.tbt.denso.21st/tree/main/doc)** //作ったシステムの写真や動画などが入っています。<br>



## 目次
・はじめに<br>
・ソフトウェア・ハードウェア設計ガイド<br>


## 使ったソフト
・GitHub Desktop (GitHub操作用)<br>
・Visual Studio Code (テキストエディタ mbedのコードを書くときに使います)<br>
・LPCISP.exe (lpc1114にプログラムを書きこむときに使います。後で詳細を説明します)<br>
・Tera Term (ターミナル。シリアル通信のデバッグ、Twelite_シリアル通信アプリのモード変更、ER試験等の時に使います<br>
・Realterm (ターミナル。2進数や16進数のデータの確認に使います。Twelite_シリアル通信アプリ_バイナリモード)<br>
・Google Earth Pro (GPSデータのチェックに使います)<br>
・Android Studio (Androidアプリ開発に使います)<br>
・Autodesk Fusion360 (3DCAD。機速計をはじめとする筐体設計に使用します)<br>
・Autodesk Inventor (3DCAD。機速計をはじめとする筐体設計に使用します)<br>
・AutoCAD Mechanical (2DCAD。3DCADだと寸法が確認しづらいので、確認用にこっちも使います。検図チェックお願いします( ﾟДﾟ))<br>
・EAGLE (回路設計CAD。Main基板の設計に使用します。後で詳細を説明します)<br>

## 使用言語
・C/C++ (mbedで使った)<br>
・Kotlin (Androidアプリ開発で使った)<br>

## 使用マイコン(※主要部のみ)
・mbed LPC1768<br>
・mbed LPC1114<br>

# システム全体図
S-270 Malus電装システムの全体図を示します。<br>
各矢印については、<br>
・黒色: シリアル通信(有線) <br>
・緑色: デジタル通信(有線) <br>
・黄色: Zigbee通信(有線) <br>
・赤色: Bluetooth通信(無線) <br>
・青色: モバイルデータ通信(無線) <br>
となっています。<br>
矢印の方向にデータが飛んでいます。<br>
### システム全体図_その1
![S-270_Malus_Sysyem_1](https://user-images.githubusercontent.com/61620703/117617589-b9375c80-b1a7-11eb-8c6b-5be67230124d.jpg)

### システム全体図_その2
![S-270_Malus_System_2](https://user-images.githubusercontent.com/61620703/117617791-01ef1580-b1a8-11eb-99fd-b792ef6264ad.jpg)

## 各計器・部品等の役割
|計器・部品名|役割|
|---|---|
|[機速計](https://github.com/Ryosuke-123/doritos.tbt.denso.21st/blob/main/doc/picture/Airspeed_meter.md)|機体の速度(空気に対する相対速度)を計測する|
|[回転数計](https://github.com/Ryosuke-123/doritos.tbt.denso.21st/blob/main/doc/picture/Cadence_meter.md)|パイロット達がペダルを回す速さを計測する|
|[高度計](https://github.com/Ryosuke-123/doritos.tbt.denso.21st/blob/main/doc/picture/Altimeter.md)|機体の高度を計測する|
|姿勢角計|機体の姿勢情報を計測する|
|心拍計|フライト時におけるパイロット達の心拍数を計測する|
|温度計|サーボモータ付近の温度を計測する|
|[GPS](https://github.com/Ryosuke-123/doritos.tbt.denso.21st/blob/main/doc/picture/GPS.md)|機体の現在位置を計測する|
|SD|機速・回転数・高度・姿勢・心拍数・温度・GPS・舵角等の情報を記録する|
|音システム|機体の高度情報を音で知らせる|
|[舵角計](https://github.com/Ryosuke-123/doritos.tbt.denso.21st/blob/main/doc/picture/Rudder_Angle_meter.md)|ER(サーボモータ)の制御角度を表示する|
|[Android端末](https://github.com/Ryosuke-123/doritos.tbt.denso.21st/blob/main/doc/picture/Android.md)|前部パイロットにフライト情報を表示する|
|[OLED](https://github.com/Ryosuke-123/doritos.tbt.denso.21st/blob/main/doc/picture/OLED.md)|後部パイロットにフライト情報を表示する|
|Li-Poバッテリー電圧監視システム|サーボモータ用Li-Poバッテリーの残り電圧の情報を記録する|

## システムの設計方針
S-270のシステムでは、無線モジュールtweliteを多用し計測系統の多機能化とパイロット安全の充実化を目指しました。<br>

## S-250からの変更点
・姿勢角計の導入<br>
・心拍計(前部P・後部P)の導入<br>
・温度計の導入<br>
・Li-poバッテリー電源監視システムの導入<br>
・フライト監視システムの導入<br>
・自作出力計の廃止と市販出力計Germin Vector3の導入<br>
・Mainプリント基板の実装部品の変更<br>
・操舵方式の変更<br>
となっています。

## 本システムの良かった点
・無線モジュールを使って、計測システムの多機能化が出来た点<br>
・無線モジュールを使って、接合時間の短縮を目指せた点<br>
・Li-Poバッテリー電圧監視システムにより、パイロット安全が向上した点(現在製作中)<br>

## 本システムの悪かった点
・無線モジュールを沢山使用したことにより、コストが大きくなってしまった点<br>
・表面実装部品の採用により、ハードウェア製作難易度が高い点<br>

# システムの詳細
## 通信方式
本システムで採用しているマイコンのlpc1768とlpc1114では、シリアル通信方式として、UART(通信)、SPI(通信)、I2C(通信)があります。<br>
S-270電装システムにおいて、すべてのシリアル通信によるデータ通信は、UART(通信)のみを使用しました(姿勢角計を除く)。<br>
<br>
<各種計器の設計・製作の観点での理由><br>
コストや製作期間の都合上、各種計器はユニバーサル基板を使って作るのですが、このユニバーサル基板はプリント基板よりもノイズが発生しやすいです。故に、同期式通信でノイズに弱いSPIとI2Cよりもリカバリーが効きやすいUARTを採用しました。<br>
<br>
<Mainプリント基板の設計・製作の観点での理由><br>
配線数が増えて面倒だと思ったため。<br>

## 有線と無線の使い分け
S-270は、有線と無線を組み合わせたシステムとなっています。<br>
人力飛行機の電装システムにおける有線と無線のメリット・デメリットをそれぞれ挙げた後、各計器・部品での採用方式について説明します。<br>
<br>
<有線 メリット><br>
・安定した通信ができる<br>
<有線 デメリット><br>
・配線が必要なため、TFや全体接合等の試験系における接合時間が長くなってしまう<br>
<br>
<無線 メリット><br>
・接合時間を短縮できる<br>
<無線 デメリット><br>
・障害物などの影響で安定しないことがある<br>
・コストが上がる<br>
<br>
|計器・部品名|有線 or 無線|採用理由|
|---|---|---|
|[機速計](https://github.com/Ryosuke-123/doritos.tbt.denso.21st/blob/main/doc/picture/Airspeed_meter.md)|無線|接合時間短縮のため|
|[回転数計](https://github.com/Ryosuke-123/doritos.tbt.denso.21st/blob/main/doc/picture/Cadence_meter.md)|無線|接合時間短縮のため|
|[高度計](https://github.com/Ryosuke-123/doritos.tbt.denso.21st/blob/main/doc/picture/Altimeter.md)|有線|コスト削減のため|
|姿勢角計|無線|接合時間短縮のため|
|心拍計|無線|接合時間短縮のため|
|温度計|無線|接合時間短縮のため|
|[舵角計](https://github.com/Ryosuke-123/doritos.tbt.denso.21st/blob/main/doc/picture/Rudder_Angle_meter.md)|有線|通信の信頼性を上げるため|
|[GPS](https://github.com/Ryosuke-123/doritos.tbt.denso.21st/blob/main/doc/picture/GPS.md)|有線|コスト削減のため|
|SD|有線|プリント基板上に乗せられるほどの余裕があったため|
|スピーカー(音システム)|有線||
|[Android端末](https://github.com/Ryosuke-123/doritos.tbt.denso.21st/blob/main/doc/picture/Android.md)|有線|通信の信頼性を上げるため|
|[OLED](https://github.com/Ryosuke-123/doritos.tbt.denso.21st/blob/main/doc/picture/OLED.md)|有線|通信の信頼性を上げるため|
|サーボモータ|有線|通信の信頼性を上げるため|
|ジョイスティック(操縦桿)|有線|通信の信頼性を上げるため|
|Li-Poバッテリー電圧監視システム|無線|接合時間短縮のため|


## 操舵系統に不具合を起こさない設計
パイロットの命が関わる操舵系統で、トラブルが起こらないように設計しました。<br>
具体的には、操舵用マイコンには他のマイコンからデータを送り付けないようにし、データ処理が追い付かず操舵に影響が出ないようにしました。

## パイロット達が安全措置を行える設計
Android端末、OLED、音システム、舵角計、リポバッテリー電圧監視システムを採用し、パイロットや併走艇に乗る全体設計者が機体の状況を常に把握できるようにしました。

## 前部P用表示器と後部P用表示器に映す情報の使い分け
TBTの機体は、他チームの機体と異なり2人乗りです。つまりパイロットが2人居るということです。<br>
実際の航空機において機長と副操縦士が操縦とフライト情報のモニタリングを分けて行うように、TBTのパイロット達にも役割分担をさせましょう。1人で処理できる情報には限りがありますからね( ﾟДﾟ)。<br>
S-270では、以下のようにしました。<br>
<br>
<前部パイロット><br>
<br>
<後部パイロット><br>

# 設計に関する勉強について

## 電装設計&責任者の年間スケジュールについて
S-270では、コロナによる学内活動禁止が繰り返し行われたため、製作スケジュールに大きな影響をもたらしました。(別の要因もありましたが...)<br>
以下に、僕の当初の活動予定と実際の活動状況について示した表を示します。今後の参考にしてください。<br>

|月|予定|記録|
|---|---|---|
|8月|ひたすら勉強、TP(テストピース)作成、運営陣会議|新入生集め|
|9月|P選考、勉強、TP作成|勉強、TP作成、新入生集め、活動方針決定、運営陣会議|
|10月|勉強、TP作成|勉強、TP作成、P選考|
|11月|勉強、TP作成|勉強、TP作成|
|12月|マザボプロトタイプ製作、プリント基板発注|勉強、TP作成|
|1月|Main基板部品実装・ソフトウェア作成、鳥コン書類執筆|勉強、TP作成|
|2月|マザボほぼ完成、CF三昧、利根川精工にサーボ発注|マザボプロトタイプ製作、プリント基板発注|
|3月|マザボ調整・各種計器作成|プリント基板再発注、CF三昧|
|4月|全体接合・回転試験・ER試験準備、マザボ調整|Main基板部品実装・ソフトウェア作成、CF三昧|
|5月|全体接合・回転試験・ER試験準備、マザボ調整|マザボほぼ作成、各種計器作成|
|6月|TF、マザボ調整||
|7月|TF、鳥コン||

## どのように勉強していけば良いかについて
