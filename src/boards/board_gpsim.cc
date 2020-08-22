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


#include "bridge_gpsim.h"

#include "board_gpsim.h"
#include"../picsimlab1.h"


static const unsigned char GPSIM_PORTS[5] = {0, 1, 2, 3, 0xFF};

board_gpsim::board_gpsim(void) {
 char list[2000]; 
 supported_devices= bridge_gpsim_get_processor_list(list,1999);
}

void
board_gpsim::MSetSerial(const char * port) {
 /*
 set_serial (&pic,0, port, 0, 0, 0);
 set_serial (&pic,1, "", 0, 0, 0);
  */ }

int
board_gpsim::MInit(const char * processor, const char * fname, float freq)
{
 int ret = -1;

 String sproc = GetSupportedDevices ();
 
 if (sproc.Contains (processor))
  {

   if (!lxFileExists (fname))
    {
     //create a empty memory
     FILE *fout;
     fout = fopen (fname, "w");
     if (fout)
      {
       fprintf (fout,":020000040000FA\n:00000001FF\n");
       fclose (fout);
      }
     else
      {
       printf ("PICSimlab: Erro creating file %s \n", fname);
       exit (-1);
      }
    }
   ret = bridge_gpsim_init (processor, fname, freq);
  }

 return ret;
}

void
board_gpsim::MEnd(void)
{
 bridge_gpsim_end ();
}

void
board_gpsim::MEraseFlash(void) {
 //erase_flash ();
}

void
board_gpsim::MSetFreq(float freq_)
{
 freq = freq_;
}

float
board_gpsim::MGetFreq(void)
{
 return freq;
}

float
board_gpsim::MGetInstClock(void)
{
 return freq;
}

int
board_gpsim::CpuInitialized(void)
{
 return 1;
}

void
board_gpsim::DebugLoop(void) { }

String
board_gpsim::MGetPinName(int pin)
{
 String pinname = "error";

 if ((pin)&&(pin <= MGetPinCount ()))
  pinname = bridge_gpsim_get_pin_name (pin);

 return pinname;
}

void
board_gpsim::MDumpMemory(const char * fname)
{
 bridge_gpsim_dump_memory (fname);
}

int
board_gpsim::DebugInit(int dtyppe) //argument not used in picm only mplabx
{
 return 0; //!mplabxd_init (this, Window1.Get_debug_port ()) - 1;
}

int
board_gpsim::MGetPinCount(void)
{
 return bridge_gpsim_get_pin_count ();
}

void
board_gpsim::pins_reset(void)
{
 for (int p = 0; p < MGetPinCount (); p++)
  {
   String pname = MGetPinName (p + 1);
   if (pname[0] == 'p')
    {
     pins[p].port = (unsigned char *) &GPSIM_PORTS[pname[4] - 'a'];
     pins[p].pord = pname[5] - '0';
    }
   else
    {
     pins[p].port = (unsigned char *) &GPSIM_PORTS[4];
     pins[p].pord = -1;
    }
   pins[p].avalue = 0;
   pins[p].lvalue = 0;
   pins[p].value = 0;
   pins[p].ptype = PT_CMOS;
   pins[p].dir = PD_IN;
   pins[p].ovalue = 0;
   pins[p].oavalue = 0;
  }
 /*TODO
     pins[7 - 1].value = 0;
     pins[7 - 1].dir = PD_OUT;
     pins[9 - 1].value = 1;
     pins[9 - 1].dir = PD_OUT;
  */
}

void
board_gpsim::MSetPin(int pin, unsigned char value)
{
 bridge_gpsim_set_pin_value (pin, value);
}

void
board_gpsim::MSetPinDOV(int pin, unsigned char ovalue) {
 //set_pin_DOV (pin, ovalue);
}

void
board_gpsim::MSetAPin(int pin, float value) {
 //set_apin (pin, value);
}

unsigned char
board_gpsim::MGetPin(int pin)
{
 return bridge_gpsim_get_pin_value (pin);
}

void
board_gpsim::MReset(int flags)
{
 bridge_gpsim_reset ();
}

const picpin *
board_gpsim::MGetPinsValues(void)
{
 return pins;
}

void
board_gpsim::MStep(void)
{

 bridge_gpsim_step ();

 for (int i = 0; i < MGetPinCount (); i++)
  {
   pins[i].value = bridge_gpsim_get_pin_value (i+1);
   pins[i].dir = bridge_gpsim_get_pin_dir (i+1);
  }
}

void
board_gpsim::MStepResume(void) {
 //if (pic.s2 == 1)step ();
}

