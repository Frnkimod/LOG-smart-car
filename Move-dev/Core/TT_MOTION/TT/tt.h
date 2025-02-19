// tt.h
// Author: Dereko
// Date: 2025-02-18
#include "../../move/move/move.h"
#ifndef TT_H
#define TT_H
#include "../../Core/move/move/move.h"
#include "../../BSP/42-dev/Emm_V5.h"
#include "../../Core/LG/check/check_line.h"
// Your function prototypes and declarations go here
int TT_main();
void testTT_motion();
void TT_CHECK_motion(int32_t speed, int16_t dir, int32_t angle);

#endif // TT_H
