#include "../libs/DynamicMenu.h"


int main(void){

	
	/*
	 * 1 --> 3
	 * 2 --> 4
	*/
	const char* options[30] = {"* MENU *", "JUGAR", "JUAGAR2", "CONFIGURACIONES", "SALIR"};
	//const char* options[30] = {"* BIENVENIDO A ABMODEL. *", "ALQUILAR AUTO", "AUTOS DISPONIBLES", "VERIFICAR RES", "MODIFICAR RES", "GANANCIA", "CONFIGURACIONES", "SALIR"};


	puts("ONE ROW \n");

	DynamicMenu menu = createMenu();
	setTypeMenu(menu, ONE_ROW);
	setBorderStyle(menu, WIDE_STYLE);
	setMenuOptins(menu, options, 5);
	setNumMovStyle(menu, DOT_STYLE);
	printMenu(menu, 0);
	destroyMenu(menu);
	
	puts("\n\nONE ROW NO HEADER\n");
 	menu = createMenu();
	setTypeMenu(menu, ONE_ROW);
	setHeaderAttributes(menu, NO_HIDDER);
	setBorderStyle(menu, DEFAULT_STYLE);
	setMenuOptins(menu, options, 5);
	setNumMovStyle(menu, PAR_STYLE);
	printMenu(menu, 0);
	destroyMenu(menu);


	puts("\n\nONE ROW MOV HEADER\n");
 	menu = createMenu();
	setTypeMenu(menu, ONE_ROW_MOV);
	setHeaderAttributes(menu, HIDDER);
	setBorderStyle(menu, WIDE_STYLE);
	setMenuOptins(menu, options, 5);
	setNumMovStyle(menu, BRACKETS_STYLE);
	printMenu(menu, 0);
	destroyMenu(menu);


	puts("\n\nONE ROW MOV  NO HEADER\n");
 	menu = createMenu();
	setTypeMenu(menu, ONE_ROW_MOV);
	setHeaderAttributes(menu, NO_HIDDER);
	setBorderStyle(menu, WIDE_STYLE);
	setMenuOptins(menu, options, 5);
	setNumMovStyle(menu, BRACKETS_STYLE);
	printMenu(menu, 0);
	destroyMenu(menu);


	/*puts("\n\n DOUBLE ROW \n");

	menu = createMenu();
	setTypeMenu(menu, DOUBLE_ROW_MOV);
	setBorderStyle(menu, WIDE_STYLE);
	setMenuOptins(menu, options, 4);
	setNumMovStyle(menu, BRACKETS_STYLE);
	printMenu(menu, 0);
	destroyMenu(menu);*/

}
