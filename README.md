# ボードのDipSWについて

* フラッシュ書き込み時 ``{1,2,3,4} = {ON,ON,OFF,ON}``
* 通常動作時 ``{1,2,3,4} = {ON,OFF,ON,OFF}``


# minicomについて

設定ファイル
``etc/minirc.dfl`` を ``/etc/minicom/`` へコピーする．

root じゃないと ``/dev/ttyUSB0`` を触れないので ``sudo minicom -o`` する．

設定を変更する場合は ``sudo minicom -s -o`` する．

操作は

* メニューを開く ``C-a z``
* 終了 ``C-a x``

というかんじ．
