/**************************************************************************//**
  \file  halCalibration.s

  \brief Implementation of measurement of mcu clock.

  \author
      Atmel Corporation: http://www.atmel.com \n
      Support email: avr@atmel.com

    Copyright (c) 2008-2012, Atmel Corporation. All rights reserved.
    Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
      1/10/08 A. Khromykh - Created
*******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

/******************************************************************************
Calculates number of cycles during EXTERNAL_TICKS period.
Parameters:
  none
Returns:
  number of the cycles (r25:r24).
******************************************************************************/
.global halMeasurement
.type halMeasurement,@function
halMeasurement:
  push r21

  ; Store SREG
  push r23
  in   r23, 0x3F
  ; Disable interrupts
  cli

  ; local copy cnt
  push r28
  push r29
  ldi  r28, 0    ; cnt = 0
  ldi  r29, 0    ; cnt = 0

  ; r21 = TCNT2
  push r23                        ; save SREG to stack, to clear r23
  lds  r21, 0x00B2
  ; while(TCNT2 == r21);
  __l0:
  lds  r23, 0x00B2
  cp   r23, r21
  breq  __l0

  ; r23++
  inc  r23

  ; measurement
  __l1:
  adiw r28, 0x01               ; cnt ++ (2 cycle)
  lds  r21, 0x00B2             ; read TCNT2
  cp   r21, r23                ; if (TCNT2 == TCNT2old)
  brne __l1                    ;

  pop  r23                     ; load SREG from stack

  ; return cnt
  movw r24, r28

  pop  r29
  pop  r28

  ; Restore SREG
  out  0x3F, r23
  pop  r23
  pop  r21
  ret

; eof halCalibration.s
