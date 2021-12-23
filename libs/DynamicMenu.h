#pragma once
#ifndef DYNAMIC_MENU_H
#define DYNAMIC_MENU_H


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <wchar.h>
#include <locale.h>

#define DM_TRUE 1
#define DM_FALSE 0

#define DEBUG_MODE 1

typedef enum position{

	TOP,
	MIDDLE,
	UNDER

}Position;


typedef enum{
	
	DEFAULT_STYLE,
	ASCII_STYLE,
	WIDE_STYLE

}StyleBorder;


typedef enum{

	ONE_ROW,
	ONE_ROW_MOV,
	DOUBLE_ROW,
	DOUBLE_ROW_MOV

}TypeMenu;


typedef enum{

	DOT_STYLE,
	PAR_STYLE,
	BRACKETS_STYLE,
	HOOKS_STYLE

}NumMovStyle;


typedef enum{

	NO_HIDDER,
	HIDDER
}HIDER_ATTR;




typedef struct _DynamicMenu* DynamicMenu;

DynamicMenu createMenu(void);
void printMenu(DynamicMenu menu, const uint8_t positionHeader);
void setNumMovStyle(DynamicMenu menu, NumMovStyle newNumMovStyle);
void setMenuOptins(DynamicMenu menu, const char** menuOptions, uint_fast16_t size);
void setBorderStyle(DynamicMenu menu, StyleBorder newBorderStyle);
void setTypeMenu(DynamicMenu menu, TypeMenu newTypeMenu);
void destroyMenu(DynamicMenu dynamicMenuToDestroy);
void setHeaderAttributes(DynamicMenu menu, HIDER_ATTR newHeader);
#endif // DYNAMIC_MENU_H
