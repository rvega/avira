#pragma once

#define VENTANA_WIDTH 934
#define VENTANA_HEIGHT 700

#define CAMARA_HEIGHT 240
#define CAMARA_WIDTH 320

// #define DOS_CAMARA_HEIGHT 480
// #define DOS_CAMARA_WIDTH 640

#define IMAGEN_PEQUENA_WIDTH CAMARA_WIDTH*0.9
#define IMAGEN_PEQUENA_HEIGHT CAMARA_HEIGHT*0.9

#define IMAGEN_GRANDE_WIDTH VENTANA_WIDTH
#define IMAGEN_GRANDE_HEIGHT VENTANA_HEIGHT

#define PADDING_X 20
#define PADDING_Y 30

#define POSICION_1_X PADDING_X
#define POSICION_1_Y PADDING_Y

#define POSICION_2_X (2*PADDING_X + IMAGEN_PEQUENA_WIDTH)
#define POSICION_2_Y (PADDING_Y)

#define POSICION_3_X (3*PADDING_X + 2*IMAGEN_PEQUENA_WIDTH)
#define POSICION_3_Y (PADDING_Y)

#define POSICION_4_X (PADDING_X)
#define POSICION_4_Y (2*PADDING_Y + IMAGEN_PEQUENA_HEIGHT)

#define POSICION_5_X (2*PADDING_X + IMAGEN_PEQUENA_WIDTH)
#define POSICION_5_Y (2*PADDING_Y + IMAGEN_PEQUENA_HEIGHT)

#define POSICION_6_X (3*PADDING_X + 2*IMAGEN_PEQUENA_WIDTH)
#define POSICION_6_Y (2*PADDING_Y + IMAGEN_PEQUENA_HEIGHT)

#define GUI_PADDING 10
#define GUI_WIDTH 155
#define GUI_POS_X 20
#define GUI_POS_Y (2*PADDING_Y + 2*IMAGEN_PEQUENA_HEIGHT + 2*GUI_PADDING)
