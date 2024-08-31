#ifndef _IIC_AUX_ENCODER_HEADER_
#define _IIC_AUX_ENCODER_HEADER_
typedef enum
{
	ROT_BUT_DOWN = 0,
	ROT_BUT_PUSHED = 1,
	ROT_BUT_UP = 2,
	ROT_BUT_RELEASED = 3,
	ROT_BUT_DISABLED = 99,
} ROTButtonState;

class ExtButton
{
  public:

    ExtButton()
    {
        ReleasedTick=0;
        PressedTick=0;
    }
public:
    void    UpdateButton(uint8_t RSW);
    int16_t ButtonClicked();
        void enable();
    void disable();
private:
    uint32_t ReleasedTick;
    uint32_t PressedTick;
    ROTButtonState buttonState;
    bool previous_butt_state;
   bool isEnabled = true;


};

class AuxRotEncoder
{
  public:
    void begin(uint8_t encoderSteps = 4);

    void reset(long newValue = 0);
    void enable();
    void disable();
    long readEncoder();
    void setEncoderValue(long newValue);
    long encoderChanged();
 
    int16_t EncoderButtonClicked()
    {
      return SWButton.ButtonClicked();
    }
    void UpdateEncoder(uint8_t RA,uint8_t RB );
    void UpdateButton(uint8_t RSW)
    {
      SWButton.UpdateButton(RSW);
    }
    void setBoundaries(long minEncoderValue, long maxEncoderValue, bool circleValues);

    unsigned long getAcceleration() { return this->rotaryAccelerationCoef; }
	  void setAcceleration(unsigned long acceleration) { this->rotaryAccelerationCoef = acceleration; }
	  void disableAcceleration() { setAcceleration(0); }
  private:
  	volatile long encoder0Pos = 0;
    volatile int8_t lastMovementDirection = 0; //1 right; -1 left
    volatile unsigned long lastMovementAt = 0;
    unsigned long rotaryAccelerationCoef = 150;

    bool _circleValues = false;
    bool isEnabled = true;

 
    long encoderSteps = 2;

    long _minEncoderValue = -1 << 15;
    long _maxEncoderValue = 1 << 15;

    uint8_t old_AB;
    long lastReadEncoder0Pos;
    bool previous_butt_state;

    ExtButton SWButton;



    int8_t enc_states[16] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
};

#endif