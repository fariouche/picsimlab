/* ########################################################################

   PICsimLab - PIC laboratory simulator

   ########################################################################

   Copyright (c) : 2010-2020  Luis Claudio Gambôa Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */


#ifndef BOARD_UCSIM_H
#define	BOARD_UCSIM_H

#include "board.h"

class bsim_ucsim: virtual public board
{
  public:
      bsim_ucsim(void);
      int DebugInit(int dtyppe) override; 
      lxString GetDebugName(void) override {return "uCsim";};
      void DebugLoop(void) override;
      int CpuInitialized(void) override;
      void MSetSerial(const char * port) override;
      int MInit(const char * processor, const char * fname, float freq) override;
      void MEnd(void) override;
      void MDumpMemory(const char * fname) override;
      void MEraseFlash(void) override;
      void MSetFreq(float freq) override;
      float MGetFreq(void) override;
      float MGetInstClockFreq(void) override;
      int MGetPinCount(void) override;
      lxString MGetPinName(int pin) override;
      void MSetPin(int pin, unsigned char value) override;
      void MSetPinDOV(int pin, unsigned char ovalue) override;      
      void MSetAPin(int pin, float value) override;
      unsigned char MGetPin(int pin) override;  
      const picpin * MGetPinsValues(void) override;  
      void MStep(void) override;
      void MStepResume(void) override;
      void MReset(int flags) override;
 protected:
      void pins_reset(void);
      picpin pins[256];
      unsigned int serialbaud; 
      float serialexbaud;
      float freq;
#ifdef _WIN_
      HANDLE serialfd;
#else
      int serialfd;
#endif      
      int procid; 
      unsigned short ports[4];
};

#endif	/* BOARD_UCSIM_H */
