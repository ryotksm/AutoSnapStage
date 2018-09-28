cd /d %~dp0
mode COM3: BAUD=57600 DATA=8 STOP=1 dtr=off rts=off PARITY=N

for /l %%i in (1,1,16) do (
  for /l %%j in (1,1,24) do (
    echo ";RotateStage(15,5);" >> COM3
    ffmpeg -y -f dshow -video_size 1280x720 -i video="HD 720P Webcam" -s 1280x720 -ss 5 -t 1 -r 1 -f image2 -vcodec png %%i-%%j.png
  )
  echo " ;MoveCamera(500,200); " >> COM3
)
echo " ;MoveCamera(-8000,100); " >> COM3

pause
echo " ;MoveCamera(-100,50); " >> COM3
echo " ;MoveCamera(50,50); " >> COM3

echo " ;MoveCamera(8000,100); " >> COM3
