#include  "HardwareStuff.h"
#include "RotaryEncoder.h"


void AuxRotEncoder::begin(uint8_t encoderSteps)
{
  	this->old_AB = 0;
	  this->encoderSteps = encoderSteps;
    this->previous_butt_state = 0;
    this->lastReadEncoder0Pos = 0;

}
void AuxRotEncoder::UpdateEncoder(uint8_t RA,uint8_t RB)
{
   //update status of A,B and RSW...
   unsigned long now = millis();
  if (this->isEnabled)
	{
		// code from https://www.circuitsathome.com/mcu/reading-rotary-encoder-on-arduino/
		/**/
		this->old_AB <<= 2; //remember previous state

		int8_t ENC_PORT = (RB ? (1 << 1) : 0) |(RA ? (1 << 0) : 0);

		this->old_AB |= (ENC_PORT & 0x03); //add current state

		//this->encoder0Pos += ( this->enc_states[( this->old_AB & 0x0f )]);
		int8_t currentDirection = (this->enc_states[(this->old_AB & 0x0f)]); //-1,0 or 1

		if (currentDirection != 0)
		{
			long prevRotaryPosition = this->encoder0Pos / this->encoderSteps;
			this->encoder0Pos += currentDirection;
			long newRotaryPosition = this->encoder0Pos / this->encoderSteps;

			if (newRotaryPosition != prevRotaryPosition && rotaryAccelerationCoef > 1)
			{
				//additional movements cause acceleration?
				// at X ms, there should be no acceleration.
				unsigned long accelerationLongCutoffMillis = 200;
				// at Y ms, we want to have maximum acceleration
				unsigned long accelerationShortCutffMillis = 4;

				// compute linear acceleration
				if (currentDirection == lastMovementDirection &&
					currentDirection != 0 &&
					lastMovementDirection != 0)
				{
					// ... but only of the direction of rotation matched and there
					// actually was a previous rotation.
					unsigned long millisAfterLastMotion = now - lastMovementAt;

					if (millisAfterLastMotion < accelerationLongCutoffMillis)
					{
						if (millisAfterLastMotion < accelerationShortCutffMillis)
						{
							millisAfterLastMotion = accelerationShortCutffMillis; // limit to maximum acceleration
						}
						if (currentDirection > 0)
						{
							this->encoder0Pos += rotaryAccelerationCoef / millisAfterLastMotion;
						}
						else
						{
							this->encoder0Pos -= rotaryAccelerationCoef / millisAfterLastMotion;
						}
					}
				}
				this->lastMovementAt = now;
				this->lastMovementDirection = currentDirection;
			}

			//respect limits
			if (this->encoder0Pos > (this->_maxEncoderValue))
				this->encoder0Pos = this->_circleValues ? this->_minEncoderValue : this->_maxEncoderValue;
			if (this->encoder0Pos < (this->_minEncoderValue))
				this->encoder0Pos = this->_circleValues ? this->_maxEncoderValue : this->_minEncoderValue;
		}


	}


}



void AuxRotEncoder::setBoundaries(long minEncoderValue, long maxEncoderValue, bool circleValues)
{
	this->_minEncoderValue = minEncoderValue * this->encoderSteps;
	this->_maxEncoderValue = maxEncoderValue * this->encoderSteps;

	this->_circleValues = circleValues;
}

long AuxRotEncoder::readEncoder()
{
	return (this->encoder0Pos / this->encoderSteps);
}

void AuxRotEncoder::setEncoderValue(long newValue)
{
	reset(newValue);
}
long AuxRotEncoder::encoderChanged()
{
	long _encoder0Pos = readEncoder();
	long encoder0Diff = _encoder0Pos - this->lastReadEncoder0Pos;

	this->lastReadEncoder0Pos = _encoder0Pos;

	return encoder0Diff;
}
 

void AuxRotEncoder::reset(long newValue_)
{
	newValue_ = newValue_ * this->encoderSteps;
	this->encoder0Pos = newValue_;
	this->lastReadEncoder0Pos = this->encoder0Pos;
	if (this->encoder0Pos > this->_maxEncoderValue)
		this->encoder0Pos = this->_circleValues ? this->_minEncoderValue : this->_maxEncoderValue;
	if (this->encoder0Pos < this->_minEncoderValue)
		this->encoder0Pos = this->_circleValues ? this->_maxEncoderValue : this->_minEncoderValue;
}


void AuxRotEncoder::enable()
{
	this->isEnabled = true;
}
void AuxRotEncoder::disable()
{
	this->isEnabled = false;
}
 
 void ExtButton::enable()
{
	this->isEnabled = true;
}
void ExtButton::disable()
{
	this->isEnabled = false;
}
void ExtButton::UpdateButton(uint8_t RSW)
{
 
    uint8_t butt_state = !RSW;
    unsigned long now = millis();

  	if (!this->isEnabled)
  	{
		  buttonState = ROT_BUT_DISABLED;
  	}else if (butt_state && !this->previous_butt_state)
    {
      this->previous_butt_state = true;
      Serial.println("Button Pushed");
      
      buttonState = ROT_BUT_PUSHED;
      PressedTick=now;
    }
    else if (!butt_state && this->previous_butt_state)
    {
      this->previous_butt_state = false;
      Serial.println("Button Released");
      buttonState = ROT_BUT_RELEASED;
      ReleasedTick=now;
      //will make it invalid after 100ms.
    }
    else
    {
      buttonState = (butt_state ? ROT_BUT_DOWN : ROT_BUT_UP);
      Serial.println(butt_state ? "BUT_DOWN" : "BUT_UP");
    }
}

int16_t ExtButton::ButtonClicked( )
{
  unsigned long now = millis();
  int16_t result=0;
  switch (buttonState)
  {
    case ROT_BUT_PUSHED:
      //hold.
      //result=true;     
      result=PressedTick-now;
      break;
    case ROT_BUT_RELEASED:
      if (now-ReleasedTick<1000) 
          result=ReleasedTick-PressedTick;        //return the hold time.
      else
      {
           result=0;
      }    
      buttonState=ROT_BUT_UP;
      break;
    default:
      break; 
  }
  return result;
}
 

 
