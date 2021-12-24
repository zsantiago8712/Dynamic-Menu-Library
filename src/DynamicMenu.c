#include "../libs/DynamicMenu.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>



static uint8_t getBiggestString(const char** array, const uint8_t start, const uint8_t end);
static void printOptionsOneRow(DynamicMenu menu);
static void getNumMoveStyle(uint8_t index, NumMovStyle style, uint8_t isSelected);
static void printHeader(DynamicMenu menu, const uint8_t positionHeader);
static char* freeString(char* string);
static char** freeStringArray(char** array, const uint_fast16_t size);
static char** createStringArray(char** array, const uint_fast16_t size);
static void printTopOrEnd(DynamicMenu menu, uint16_t isTop);
static void getBorderStyle(StyleBorder border, wchar_t borderStyle[4], Position position);
static void pustSpaces(uint8_t sizeWord, uint8_t sizeMenu);
static void getSizeOfMenu(DynamicMenu menu);
static void printOptionsDoubleRow(DynamicMenu menu);
#define RED "\x1B[31m"

#define PRINT_MEM_ERROR fprintf(stderr,"ERROR: %s %d MEMEORY ERROR", __FILE__, __LINE__);
#define PRINT_WARNING_INVALID_OPTION printf("ERROR INVALID OPTION %s %s %d", RED, __FILE__, __LINE__);



#define CHECK_IS_EMPTY(strct) \
	if(!strct)                \
	{				          \
		PRINT_MEM_ERROR       \
		exit(EXIT_FAILURE);   \
	}                         \


struct _DynamicMenu{
	
	StyleBorder styleBorder;
	TypeMenu typeMenu;
	NumMovStyle numMovStyle;
	HIDER_ATTR hiderAttr;	

	char** menuOptions;
	uint_fast8_t numMenuOptions;
	uint_fast16_t menuSize; 
};



DynamicMenu createMenu(void){

	DynamicMenu newMenu = malloc(sizeof(struct _DynamicMenu));
	CHECK_IS_EMPTY(newMenu);
	

	setlocale(LC_ALL, "");

	newMenu->menuOptions = createStringArray(newMenu->menuOptions, 4);
	newMenu->numMenuOptions = 4;
	newMenu->typeMenu = ONE_ROW;
	newMenu->numMovStyle = DOT_STYLE;
	newMenu->styleBorder = DEFAULT_STYLE;
	newMenu->menuSize = 0;
	newMenu->hiderAttr = HIDDER;

	return newMenu;
}


void destroyMenu(DynamicMenu dynamicMenuToDestroy){
	
#if DEBUG_MODE
	puts("destroyMenu");
#endif

	dynamicMenuToDestroy->menuOptions = freeStringArray(dynamicMenuToDestroy->menuOptions, dynamicMenuToDestroy->numMenuOptions);
	free(dynamicMenuToDestroy);
	dynamicMenuToDestroy = NULL;

}


void setTypeMenu(DynamicMenu menu, TypeMenu newTypeMenu){

	CHECK_IS_EMPTY(menu);
	menu->typeMenu = newTypeMenu;
}


void setBorderStyle(DynamicMenu menu, StyleBorder newBorderStyle){

	CHECK_IS_EMPTY(menu);
	menu->styleBorder = newBorderStyle;
}

void setHeaderAttributes(DynamicMenu menu, HIDER_ATTR newHeader){

	CHECK_IS_EMPTY(menu);
	menu->hiderAttr = newHeader;
}

void setMenuOptins(DynamicMenu menu, const char** menuOptions, uint_fast16_t size){

	CHECK_IS_EMPTY(menu);
	CHECK_IS_EMPTY(menuOptions);
	
	if(size > menu->numMenuOptions){
		menu->numMenuOptions = size;
		menu->menuOptions = createStringArray(menu->menuOptions, size);
	}

	for(uint8_t i = 0; i < size; i++)
		menu->menuOptions[i] = strdup(menuOptions[i]);
	
}


void setNumMovStyle(DynamicMenu menu, NumMovStyle newNumMovStyle){
	
	CHECK_IS_EMPTY(menu);

	if((menu->typeMenu == ONE_ROW && newNumMovStyle == PAR_STYLE) || (menu->typeMenu == ONE_ROW && newNumMovStyle == DOT_STYLE)){
		
		menu->numMovStyle = newNumMovStyle;
		return;
	}else if((menu->typeMenu == DOUBLE_ROW && newNumMovStyle == PAR_STYLE) || (menu->typeMenu == DOUBLE_ROW && newNumMovStyle == DOT_STYLE)){

		menu->numMovStyle = newNumMovStyle;
		return;
	}else if ((menu->typeMenu == ONE_ROW_MOV && newNumMovStyle == BRACKETS_STYLE) || (menu->typeMenu == ONE_ROW_MOV && newNumMovStyle == HOOKS_STYLE)) {
	
		menu->numMovStyle = newNumMovStyle;
		return;
	
	}else if ((menu->typeMenu == DOUBLE_ROW_MOV && newNumMovStyle == BRACKETS_STYLE) || (menu->typeMenu == DOUBLE_ROW_MOV && newNumMovStyle == HOOKS_STYLE)) {
		
		menu->numMovStyle = newNumMovStyle;
		return;
	}


	PRINT_WARNING_INVALID_OPTION
}



void printMenu(DynamicMenu menu, const uint8_t positionHeader){

	CHECK_IS_EMPTY(menu);

	getSizeOfMenu(menu);
	printTopOrEnd(menu, TOP);
	if(menu->hiderAttr){
		printHeader(menu, positionHeader);
		printTopOrEnd(menu, MIDDLE);
	}

	if(menu->typeMenu == ONE_ROW || menu->typeMenu == ONE_ROW_MOV)
		printOptionsOneRow(menu);
	else if(menu->typeMenu == DOUBLE_ROW || menu->typeMenu == DOUBLE_ROW_MOV)
		printOptionsDoubleRow(menu);

	printTopOrEnd(menu, UNDER);
}



static void printHeader(DynamicMenu menu, const uint8_t positionHeader){
	
	wchar_t border[4];
	getBorderStyle(menu->styleBorder, border, MIDDLE);
	
	float middle = ceil((float)(menu->menuSize - strlen(menu->menuOptions[positionHeader])) / 2);

	wprintf(L"%lc", border[0]);
	for (uint8_t i = 0; i <=  menu->menuSize - strlen(menu->menuOptions[positionHeader]); i++) {
			
		if(i == middle)
			printf("%s", menu->menuOptions[positionHeader]);
		else
			printf(" ");

	}
	wprintf(L"%lc\n", border[2]);
	
}


static void printOptionsOneRow(DynamicMenu menu){

	wchar_t border[4];
	uint8_t extraSpaces = 0;
	uint8_t indexNum = 0;

	if(!menu->hiderAttr)
		indexNum = 1;

	getBorderStyle(menu->styleBorder, border, MIDDLE);

	wprintf(L"%lc", border[0]);
	if(menu->typeMenu == ONE_ROW_MOV){
		getNumMoveStyle(menu->hiderAttr, menu->numMovStyle, DM_TRUE);
		extraSpaces = 5;
	}else{
		getNumMoveStyle(menu->hiderAttr + indexNum , menu->numMovStyle, DM_FALSE);
		extraSpaces = 3;
	}
	
	printf("%s", menu->menuOptions[menu->hiderAttr]);
	pustSpaces(strlen(menu->menuOptions[menu->hiderAttr]) + extraSpaces, menu->menuSize);

	for(uint8_t i = menu->hiderAttr + 1; i < menu->numMenuOptions; i++){
		
		wprintf(L"%lc\n%lc", border[0], border[0]);	
		getNumMoveStyle(i + indexNum, menu->numMovStyle, DM_FALSE);
		wprintf(L"%s", menu->menuOptions[i]);
		pustSpaces(strlen(menu->menuOptions[i]) + extraSpaces, menu->menuSize);
		
			
	}
	wprintf(L"%lc\n", border[0]);

}


static void printOptionsDoubleRow(DynamicMenu menu){
	
	wchar_t border[4];
	uint8_t extraSpaces = 0;
	uint8_t indexNum = 0;
	uint_fast16_t separetor = getBiggestString((const char**) menu->menuOptions, (uint8_t)ceilf((float)menu->numMenuOptions  / 2) , menu->numMenuOptions);
	uint8_t indexRightRow = ceilf((float) menu->numMenuOptions / 2);
	

	getBorderStyle(menu->styleBorder, border, MIDDLE);
	if(!menu->hiderAttr)
		indexNum = 1;


	wprintf(L"%lc", border[0]);
	if(menu->typeMenu == DOUBLE_ROW_MOV){
		
		separetor += 7;
		getNumMoveStyle(menu->hiderAttr, menu->numMovStyle, DM_TRUE);
		extraSpaces = 6;
	}else{
		separetor += 5;
		getNumMoveStyle(menu->hiderAttr + indexNum, menu->numMovStyle, DM_FALSE);
		extraSpaces = 4;
	}
	
		
	printf("%s", menu->menuOptions[menu->hiderAttr]);
	pustSpaces(strlen(menu->menuOptions[menu->hiderAttr]) + extraSpaces, menu->menuSize - separetor);
	wprintf(L"%lc", border[0]);
	getNumMoveStyle(indexRightRow + indexNum, menu->numMovStyle, DM_FALSE);
	printf("%s", menu->menuOptions[indexRightRow]);
	pustSpaces(strlen(menu->menuOptions[indexRightRow]) + extraSpaces, separetor + 1);
	wprintf(L"%lc\n", border[0]);
	indexRightRow++;

	for(uint8_t i = menu->hiderAttr + 1; i < (uint8_t)ceil((float)menu->numMenuOptions / 2); i++){
		
		wprintf(L"%lc", border[0]);
		getNumMoveStyle(i + indexNum, menu->numMovStyle, DM_FALSE);
		printf("%s", menu->menuOptions[i]);
		pustSpaces(strlen(menu->menuOptions[i]) + extraSpaces, menu->menuSize - separetor);
		wprintf(L"%lc", border[0]);

		if(indexRightRow < menu->numMenuOptions){
			
			getNumMoveStyle(indexRightRow + indexNum, menu->numMovStyle, DM_FALSE);
			printf("%s", menu->menuOptions[indexRightRow]);
			pustSpaces(strlen(menu->menuOptions[indexRightRow]) + extraSpaces, separetor + 1);
			indexRightRow++;
		}else 
			pustSpaces(0, separetor + 1);
			
		wprintf(L"%lc\n", border[0]);
	}

}


static void pustSpaces(uint8_t sizeWord, uint8_t sizeMenu){

	for(uint8_t i = 0; i < sizeMenu - sizeWord - 1; i++)
		printf(" ");
}

static void getNumMoveStyle(uint8_t index, NumMovStyle style, uint8_t isSelected){

	if(style == DOT_STYLE)
		printf(" %hhu. ", index);
	else if(style == PAR_STYLE)
		printf(" %hhu) ", index);

	else if(style == BRACKETS_STYLE){
		
		if(isSelected)
			printf(" [██] ");
		else
			printf(" [  ] ");
	}
	else if(style == HOOKS_STYLE){

		if(isSelected)
			printf(" {██} ");
		else
			printf(" {  } ");	
	}
} 

static void getSizeOfMenu(DynamicMenu menu){
	
	uint_fast8_t rigthRow = 0;
	uint_fast8_t leftRow = 0;
	uint8_t max = menu->numMenuOptions - 1;
	const uint_fast8_t start = 0;


	if(menu->typeMenu == DOUBLE_ROW || menu->typeMenu == DOUBLE_ROW_MOV){

		max = ceil((float)menu->numMenuOptions / 2) + 1;
		rigthRow = strlen(menu->menuOptions[max]);
		for(uint8_t i = max; i <= menu->numMenuOptions - 1; i++){
			
			if(rigthRow < strlen(menu->menuOptions[i]))
				rigthRow = strlen(menu->menuOptions[i]);
			
		}
		rigthRow += 17;
	}
	

	leftRow = strlen(menu->menuOptions[start]);
	for(uint8_t i = start + 1; i < max; i++){
			
		if(leftRow < strlen(menu->menuOptions[i]))
			leftRow = strlen(menu->menuOptions[i]);
	}

	if(menu->typeMenu == ONE_ROW_MOV)
		menu->menuSize = rigthRow + leftRow + 7;
	else if(menu->typeMenu == DOUBLE_ROW_MOV)
		menu->menuSize = rigthRow + leftRow + 7;
	else
		menu->menuSize = rigthRow + leftRow + 5;
}





static void getBorderStyle(StyleBorder border, wchar_t borderStyle[4], Position position){

	if(border == DEFAULT_STYLE){
		borderStyle[0] = '|';
		borderStyle[1] = '-';
		borderStyle[2] = '|';
	}else if(border == WIDE_STYLE){
	
		borderStyle[0] = L'║';
		borderStyle[1] = L'═';
		borderStyle[2] = L'║';

		if(position == TOP){
			borderStyle[0] = L'╔';
			borderStyle[2] = L'╗';
		}else if(position == UNDER){
			borderStyle[0] = L'╚';
			borderStyle[2] = L'╝';
		}		
		
		
	}else if(border == ASCII_STYLE){
		borderStyle[0] = L'█';
		
		if(position == TOP)
			borderStyle[1] = L'■';
		else if(position == UNDER)
			borderStyle[1] = L'▄';
		
		borderStyle[2] = L'█';
	}

}

static void printTopOrEnd(DynamicMenu menu, uint16_t isTop){
	
	wchar_t borderStyle[4];

	getBorderStyle(menu->styleBorder, borderStyle, isTop);

	wprintf(L"%lc", borderStyle[0]);
	for(uint_fast8_t i = 0; i < menu->menuSize; i++)
		wprintf(L"%lc", borderStyle[1]);

	wprintf(L"%lc\n", borderStyle[2]);
}



static char** createStringArray(char** array, const uint_fast16_t size){

	array = calloc(size, sizeof(char*));
	CHECK_IS_EMPTY(array);

	return array;
}


static char** freeStringArray(char** array, const uint_fast16_t size){

	for(uint8_t i = 0; i < size; i++)
		array[i] = freeString(array[i]);

	free(array);
	array = NULL;

	return array;
}


static char* freeString(char* string){

	free(string);
	string = NULL;

	return string;
}


static uint8_t getBiggestString(const char** array, const uint8_t start, const uint8_t end){

	uint8_t max = strlen(array[start]);

	for(uint8_t i = start; i < end; i++){

		if(max < strlen(array[i]))
			max = strlen(array[i]);
	}

	return max;
}
