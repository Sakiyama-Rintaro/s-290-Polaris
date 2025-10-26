## はじめに
S-270 Malus電装システムにおけるMain基板のシステムを再現するために必要なことが書かれています。参考にしてください。<br>

## 各ファイルについて
・S-270_Malus_board.zip : Fusion PCBにて発注するデータ<br>
・S-270_Malus_Main_board.sch : メイン基板回路図<br>
・S-270_Malus_Main_board.brd : メイン基板配線図<br>
・S-270_Malus_Main_board_sch.png : メイン基板回路図写真<br>
・S-270_Malus_Main_board_brd.png : メイン基板配線図写真<br>
・S-270_Malus_board_parts : プリント基板に使った部品一覧 <br>
・Android_System_for_test : Androidプログラム。数字表示するだけ<br>
・S-270_main_lpc1768.cpp : 計測用マイコンプログラム<br>
・S-270_ER_lpc1768.cpp : 操舵用マイコンプログラム<br>
・S-270_twe_lpc1114.cpp : 無線モジュール用マイコンプログラム<br>
・S-270_gps_lpc1114.cpp : GPS用マイコンプログラム<br>
・S-270_sound_lpc1114.cpp : 音システム用マイコンプログラム<br>
・S-270_airspeed_meter_lpc1114 : 対気速度計用マイコンプログラム(送信機)<br>
・S-270_cadence_meter_lpc1114 : 回転数計用マイコンプログラム(送信機)<br>

## 目次
・基板準備<br>
・部品実装<br>
・自作書き込み機の準備<br>
・書き込みソフトウェアの準備<br>

## 基板準備
### Step1
リポジトリから「S-270_Malus_board.zipファイル」をダウンロードする。<br>

### Step2
Fusion PCBのサイト[(Click Here)](https://www.fusionpcb.jp/fusion_pcb.html)に行き、ダウンロードしたzipファイルをアップロードする。<br>
  (設定) <br>
  ・材質: FR-4 TG130 <br>
  ・層数: 二層 <br>
  ・寸法: 80.0 * 100.0 <br>
  ・製造枚数: 好きな枚数 <br>
  ・異種面付けの種類: 1 <br>
  ・板厚: 1.60 <br>
  ・レジスト色: 好きな色 <br>
  ・基板の表面処理: HASL(有鉛半田レベラー) <br>
  ・最小ソルダレジストダムの幅: 0.4mm↑ <br>
  ・銅箔厚: 1oz. <br>
  ・最小穴径: 0.3mm <br>
  ・最小パターン幅/パターン間隔: 6/6 mil <br>
  ・端面スルーホール: なし <br>
  ・インピーダンス制御: なし <br>
  
### Step3
ページの指示に従って、発注をかける。<br>

## 部品実装
届いた基板に部品を実装しましょう。<br>
使用する部品は、「S-270_Malus_board_parts.xlsx」に記載されています。<br>

## 自作書き込み機の準備
### lpc1114FDH28(表面実装版lpc1114)用書き込み機
S-270で使った書き込み機の写真とその回路配線についての写真を下に示します。<br>
<写真><br>
![lpc1114_programmer](https://user-images.githubusercontent.com/61620703/118811460-01612800-b8e8-11eb-9755-34ed2f5c0a9b.jpg)
<回路図><br>
![lpc1114_programmer](https://user-images.githubusercontent.com/61620703/118357052-0ace5580-b5b3-11eb-8273-8315cef4a634.jpg)


### 表面実装版twelite用書き込み機
S-270で使った書き込み機の写真とその回路配線についての写真を下に示します。<br>
<写真><br>
![twelite_programmer](https://user-images.githubusercontent.com/61620703/118811677-3ec5b580-b8e8-11eb-96ca-d5ded7b4645e.jpg)
<回路図><br>
![twelite_programmer](https://user-images.githubusercontent.com/61620703/118358004-c5605700-b5b7-11eb-98b4-29df20715a88.png)

## 書き込み用ソフトウェアの準備
lpc1114FDH28とtweliteへのプログラム書き込みには、それぞれ専用のソフトウェアが必要です。<br>
まずは、必要なソフトウェアをダウンロードしましょう。<br>
<br>
・LPCISP.exe(lpc1114FDH28への書き込みに必要) [Click!](https://synapse.kyoto/tips/LPC1114/page002.html)<br>
・TWE-Programmer.exe(tweliteへの書き込みに必要) [Click!](https://mono-wireless.com/jp/products/TWE-APPS/LiteProg/index.html)<br>
・Tera Term(tweliteに書き込む「シリアル通信アプリ」のターミナル設定に必要) [Click!](https://forest.watch.impress.co.jp/library/software/utf8teraterm/)<br>
<br>

### lpc1114FDH28への書き込み

### tweliteへの書き込みと設定

・Device ID: 0x00<br>
・UART band: 115200<br>
・UART mode: Binary formatted<br>
