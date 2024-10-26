# Pon
気軽に使うことを想定した、ポン出し用ソフトウェアです。  
サンプラー方式ってやつで、32Key?あります。  
お世話になっている方に頼まれ、作成しました。  
「OSSとして公開しても大丈夫でしょうか？」と尋ねたところ快諾していただいたため、公開します。  

## 制限事項
- ファイルオープン時にメモリ上に全サンプルをデコード、リサンプリングをし、再生時にはメモリ上からそのまま読み出して再生します。  
  つまり、使用時のCPU使用率を抑えるためにメモリ使用量を犠牲にしているため、それなりのメモリ容量が必要です。
- ASIOは使えません

## 対応プラットフォーム
SDL2/SDL2_mixerのビルドが可能であるプラットフォーム

## 対応ファイル形式
SDL_mixerで読み込み可能な形式の一部に対応しています。  
Wav(LPCM), MP3, Ogg(Vorbis), Opus, Flac...

## 使い方
### 効果音の読み込み方法
起動すると、無機質な画面にボタンのみが出ます。  
各ボタンに登録したい音声をD&Dすることで登録できます。  
ボタンに音声ファイルが登録されているかはボタンの明るさで判別できます  
次回起動からは前回に登録されていたファイルが自動的に読み込まれます。

### 設定ファイル
TOML形式を使用しています。  
グローバル変数の"files"にそれぞれのファイルパスのリストが載っています。

### 音の鳴らし方
2種類の方法があります。
1. ボタンをクリックします
2. キーボードを押下します。以下のように割り当てられています。
    1. 1段目は「12345678」
    2. 2段目は「QWERTYUI」
    3. 3段目は「ASDFGHJK」
    4. 4段目は「ZXCVBNM,」

### 音の停止
Shiftキーを押下したまま対応したキーボードを押下することで、停止できます。

## 免責事項
このプログラムを用い発生した損害について、作者は一切の責任を負いません。
