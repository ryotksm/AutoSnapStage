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
  �X�e�[�W����]������B
  degree : ��]�p�x ���̐��͎��v���A���̐��͔����v���B
  speed : ��]���x rpm 1�`200���炢
  �p��
  ;RotateStage(360,200); �����v���ɂ��΂₭1��]
  ;RotateStage(-90,50); �������v���ɂ��΂₭1/4��]

* MoveCamera(step,speed)
  �J�������㉺������B
  step : �ړ���(�ォ�牺�܂łŖ�8000�X�e�b�v)
  speed : 1�`200���炢�Ŏw��B
  �p��
  ;MoveCamera(8000,200); ����ԏォ���ԉ��܂ł��΂₭���~
  ;MoveCamera(-8000,50); ����ԉ������ԏ�܂ł������㏸

;RotateStage(360,200);
