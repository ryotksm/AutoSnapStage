#include <DRV8825.h>
// D0 DRV8825-1 STAGE-MOTOR DIR
// D1 DRV8825-1 STAGE-MOTOR STEP
// D2 DRV8825-2 CAMERA-MOTOR DIR
// D3 DRV8825-2 CAMERA-MOTOR STEP
#define D1DIR 2
#define D1STP 3
#define D2DIR 4
#define D2STP 5

// 1回転のステップ数
// プリンタ取り出しモーターの場合5450
// CDヘッド用モーターの場合8000
// 回転角1.8度の場合6400
const int stepsPerResolution1 = 6400;
const int stepsPerResolution2 = 6400;

DRV8825 stageMotor(stepsPerResolution1, D1DIR, D1STP);
DRV8825 cameraMotor(stepsPerResolution2, D2DIR, D2STP);

// シリアル通信用バッファ
char input[256];   // 文字列格納用
int i = 0;  // 文字数のカウンタ

// 入力コマンドを判定
void decodeCommand(char* input) {
  if (strncmp(input, "RotateStage", 11) == 0) {
    Serial.println("RotateStage Command start");
    char* params = &input[12];
    int deg, rpm;
    sscanf(params, "%d,%d", &deg, &rpm);
    stageMotor.setRPM(rpm);
    stageMotor.rotate(deg);
  }
  if (strncmp(input, "MoveStage", 9) == 0) {
    Serial.println("MoveStage Command start");
    char* params = &input[12];
    int stp, rpm;
    sscanf(params, "%d,%d", &stp, &rpm);
    stageMotor.setRPM(rpm);
    stageMotor.move(stp);
  }
  if (strncmp(input, "MoveCamera", 10) == 0) {
    Serial.write("MoveCamera Command start");
    Serial.write("\n");
    char* params = &input[11];
    int stp, rpm;
    sscanf(params, "%d,%d", &stp, &rpm);
    cameraMotor.setRPM(rpm);
    cameraMotor.move(stp);
  }
}

void setup() {
  Serial.begin(57600);
  // Set target motor RPM to 1RPM and microstepping to 1 (full step mode)
  stageMotor.begin(1, 1);
  cameraMotor.begin(1, 1);
}

void loop() {
  // データ受信したとき
  if (Serial.available()) {
    input[i] = Serial.read();
    // 文字数が30以上 or 末尾文字
    if (i > 30 || input[i] == ';') {
      // 末尾に終端文字の挿入
      input[i] = '\0';
      // 受信文字列を送信
      Serial.write(input);
      Serial.write("\n");

      // コマンド解析
      decodeCommand(input);

      // カウンタの初期化
      i = 0;
    }
    else {
      if(input[i]>0x0f)i++;
    }
  }
}
