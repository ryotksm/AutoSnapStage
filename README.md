# AutoSnapStage
 This program automatically takes pictures from various angles.

## Arduino

### Serial port setting
Speed:57600bps
Data:8bit
Parity:none
Stop bit:1bit
Flow control:none

### Control command

* RotateStage(degree,speed)
  ステージを回転させる。
  degree : 回転角度 正の数は時計回り、負の数は反時計回り。
  speed : 回転速度 rpm 1～200くらい
  用例
  ;RotateStage(360,200); ←時計回りにすばやく1回転
  ;RotateStage(-90,50); ←反時計回りにすばやく1/4回転

* MoveCamera(step,speed)
  カメラを上下させる。
  step : 移動量(上から下までで約8000ステップ)
  speed : 1～200くらいで指定。
  用例
  ;MoveCamera(8000,200); ←一番上から一番下まですばやく下降
  ;MoveCamera(-8000,50); ←一番下から一番上までゆっくり上昇

;RotateStage(360,200);
