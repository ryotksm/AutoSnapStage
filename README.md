# AutoSnapStage
 被写体の回転とカメラの上下動で、いろいろな角度から自動的に写真を撮るシステムです。

## Arduino
制御用にAE-ATMEGA328-miniを使用しています。  
モータードライバにはDRV8825を使用しています。  
カメラ用のステッピングモーターはDVD-ROMから取り出したものです。  
ステージ用のステッピングモーターはプリンタから取り出したものです。  
回路図はそのうち書くかもしれません。  

### Serial port setting
Speed:57600bps  
Data:8bit  
Parity:none  
Stop bit:1bit  
Flow control:none  

### Control command
';'セミコロンで区切ってコマンドを指定します。
* RotateStage(degree,speed)  
  ステージを回転させる。  
  degree : 回転角度 正の数は時計回り、負の数は反時計回り。  
  speed : 回転速度 rpm 1～200くらい  
  使用例  
  ;RotateStage(360,200); ←時計回りにすばやく1回転  
  ;RotateStage(-90,50); ←反時計回りにすばやく1/4回転  

* MoveCamera(step,speed)  
  カメラを上下させる。  
  step : 移動量(上から下までで約8000ステップ)  
  speed : 1～200くらいで指定。  
  使用例  
  ;MoveCamera(8000,200); ←一番上から一番下まですばやく下降  
  ;MoveCamera(-8000,50); ←一番下から一番上までゆっくり上昇  

### libraries 
  laurb9/StepperDriver  
  https://github.com/laurb9/StepperDriver  
