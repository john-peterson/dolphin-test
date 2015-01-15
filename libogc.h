#pragma once

#include "main.h"

typedef struct _padstatus {
	u16 button;
	s8 stickX;
	s8 stickY;
	s8 substickX;
	s8 substickY;
	u8 triggerL;
	u8 triggerR;
	u8 analogA;
	u8 analogB;
	s8 err;
} PADStatus;

void __pad_clampstick(s8 *px,s8 *py,s8 max,s8 xy,s8 min);