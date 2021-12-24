#include "../libs/DynamicMenu.h"


int main(void){

	
	
	//const char* options[80] = {"* MENU *", "JUGAR", "JUAGAR2", "CONFIGURACIONES", "SALIR"};
	const char* options[30] = {"* BIENVENIDO A ABMODEL. *", "ALQUILAR AUTO", "AUTOS DISPONIBLES", "VERIFICAR RES", "MODIFICAR RES", "GANANCIA", "CONFIGURACIONES", "SALIR"};
	//const char* options[80] = {"* MASTERMIND *", "J1 VS. CPU", "J1 VS. J2", "CONFIGURACIONES", "SALIR"};
	//const char* options[80] = {"* CACA *", "OSPDOKAS", "KJDSAN", "LDANKLASD", "LSAKND", "KJDANS"};
	//const char* options[80] = {"*CACA", "LDKANSL", "DLKNA", "dlnsald"};

	puts("DOUBLE ROW \n");

	DynamicMenu menu = createMenu();
	setTypeMenu(menu, DOUBLE_ROW);
	setBorderStyle(menu, WIDE_STYLE);
	setMenuOptins(menu, options, 8);
	setNumMovStyle(menu, DOT_STYLE);
	printMenu(menu, 0);
	destroyMenu(menu);
	
	puts("\n\nDOUBLE ROW NO HEADER\n");
 	menu = createMenu();
	setTypeMenu(menu, DOUBLE_ROW);
	setHeaderAttributes(menu, NO_HIDDER);
	setBorderStyle(menu, DEFAULT_STYLE);
	setMenuOptins(menu, options, 8);
	setNumMovStyle(menu, PAR_STYLE);
	printMenu(menu, 0);
	destroyMenu(menu);


	puts("\n\nDOUBLE ROW MOV HEADER\n");
 	menu = createMenu();
	setTypeMenu(menu, DOUBLE_ROW_MOV);
	setHeaderAttributes(menu, HIDDER);
	setBorderStyle(menu, WIDE_STYLE);
	setMenuOptins(menu, options, 8);
	setNumMovStyle(menu, BRACKETS_STYLE);
	printMenu(menu, 0);
	destroyMenu(menu);

	
	puts("\n\nDOUBLE ROW MOV  NO HEADER\n");
 	menu = createMenu();
	setTypeMenu(menu, DOUBLE_ROW_MOV);
	setHeaderAttributes(menu, NO_HIDDER);
	setBorderStyle(menu, WIDE_STYLE);
	setMenuOptins(menu, options, 8);
	setNumMovStyle(menu, BRACKETS_STYLE);
	printMenu(menu, 0);
	destroyMenu(menu);



	puts("\n\n DOUBLE ROW MOVE - NO HEADER\n");

	menu = createMenu();
	setTypeMenu(menu, ONE_ROW_MOV);
	setHeaderAttributes(menu, NO_HIDDER);
	setBorderStyle(menu, WIDE_STYLE);
	setMenuOptins(menu, options, 8);
	setNumMovStyle(menu, BRACKETS_STYLE);
	printMenu(menu, 0);
	destroyMenu(menu);
	
	puts("\n\n ONE ROW\n");
	menu = createMenu();
	setTypeMenu(menu, ONE_ROW);
	setHeaderAttributes(menu, HIDDER);
	setBorderStyle(menu, WIDE_STYLE);
	setMenuOptins(menu, options, 8);
	setNumMovStyle(menu, PAR_STYLE);
	printMenu(menu, 0);
	destroyMenu(menu);

	puts("\n\n ONE ROW  - NO HEADER\n");
	menu = createMenu();
	setTypeMenu(menu, ONE_ROW);
	setHeaderAttributes(menu, NO_HIDDER);
	setBorderStyle(menu, WIDE_STYLE);
	setMenuOptins(menu, options, 8);
	setNumMovStyle(menu, DOT_STYLE);
	printMenu(menu, 0);
	destroyMenu(menu);


	puts("\n\n ONE ROW MOVE - HEADER\n");
	menu = createMenu();
	setTypeMenu(menu, ONE_ROW_MOV);
	setHeaderAttributes(menu, HIDDER);
	setBorderStyle(menu, WIDE_STYLE);
	setMenuOptins(menu, options, 8);
	setNumMovStyle(menu, HOOKS_STYLE);
	printMenu(menu, 0);
	destroyMenu(menu);

	puts("\n\n ONE ROW MOVE - NO HEADER\n");
	menu = createMenu();
	setTypeMenu(menu, ONE_ROW_MOV);
	setHeaderAttributes(menu, NO_HIDDER);
	setBorderStyle(menu, WIDE_STYLE);
	setMenuOptins(menu, options, 8);
	setNumMovStyle(menu, BRACKETS_STYLE);
	printMenu(menu, 0);
	destroyMenu(menu);
	

}
