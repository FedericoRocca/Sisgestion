#include <iostream>

using namespace std;

#include <cstdio>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <io.h>

#include "Headers/Clases.h"
#include "Headers/Funciones_Utiles.h"
#include "Headers/Fecha.h"
#include "Headers/User.h"
#include "Headers/Clientes.h"
#include "Headers/Productos.h"
#include "Headers/Ventas.h"
#include "Headers/Listados.h"

#include "Headers/Final.h"

#include "Headers/Menues.h"


int main()
{
    InicializarArchivos();
    Inicializar_Ventana( 130, 60);
    bool Menu = true;
    int x, y;
    while( Menu == true )
    {
        x = 20; y = 5;
        clear();
        recuadro_top();
        colorNormal();
        gotoxy(x, y);
        cout << "Sisgestion  ";
        gotoxy(x + 60, y++);
        cout << currentDateTime();
        gotoxy(x, y++);
        barra();
        gotoxy(x, y++);
        cout << "1 - Acceso administrativo";
        gotoxy(x, y++);
        cout << "2 - Acceso a clientes";
        gotoxy(x, y++);
        cout << "3 - Final - Listar art" << char(161) << "culos por categor" << char(161) << "a";
        gotoxy(x, y++);
        barra();
        gotoxy(x, y++);
        cout << "Presione la opci" << char(162) << "n deseada. ESC para salir";
        recuadro_bott(y + 3);
        colorNormal();
        gotoxy(x, y);

        switch( getch() )
        {
        case '1':
            Menu_Administrativo();
            break;

        case '2':
            Menu_Clientes();
            break;

        case '3':
            ListarArticulosXCategoria();
            break;

        case 27:
            Menu = false;
            break;

        default:
            Error_Menu();
            break;
        }

    }
    return 0;
}
