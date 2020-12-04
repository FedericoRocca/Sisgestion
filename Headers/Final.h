#ifndef FINAL_H_INCLUDED
#define FINAL_H_INCLUDED

/// listar articulos a partir de cierta categoria

void ListarArticulosXCategoria()
{
    clear();
    int x = 20, y = 5, categoria, cont = 0;
    bool error = true;
    Producto articulo;
    recuadro_top();
    colorNormal();

    gotoxy(x, y);
    cout << "LISTAR ART" << char(214) << "CULOS POR CATEGOR" << char(214) << "A" ;
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

    gotoxy(x, y++);
    cout << "Ingrese la categor" << char(161) << "a a listar:" ;
    gotoxy(x, y++);
    cout << "1 - Perfumer" << char(161) << "a   | 2 - Verduler" << char(161) << "a | 3 - Bebidas" ;
    gotoxy(x, y++);
    cout << "4 - Mascotas     | 5 - Limpieza   | 6 - Vestimenta" ;
    gotoxy(x, y++);
    cout << "7 - Frigor" << char(161) << "ficos | 8 - Electro    | 9 - Panader" << char(161) << "a" ;
    gotoxy(x, y++);
    cout << "10 - Almac" << char(130) << "n     | 11 - Otros" ;
    error = true;
    while( error )
    {
        gotoxy(x + 31, y - 5);
        cin >> categoria;
        if( categoria < 1 || categoria > 11 )
        {
            colorError();
            gotoxy(x, y++);
            cout << "La categor" << char(161) << "a ingresada es inv" << char(160) << "lida." ;
            gotoxy(x, y++);
            cout << "Si desea salir, presione ESC, de lo contrario, cualquier tecla." ;
            colorNormal();
            gotoxy(x, y++);

            if( getch() == 27 )
            {
                pause();
                return;
            }
            gotoxy(x, y++);
            cout << "Ingr" << char(130) << "sela nuevamente: ";
            recuadro_midd(y - 1, 19, 80, 9, cROJO, cAQUA);
            y += 7;
            colorNormal();
        }
        else
            error = false;
    }

    gotoxy(x, y++);
    barra();

    titulos_producto(y++);
    gotoxy(x, y++);
    barra();

    FILE* puntero = fopen( "Archivos/Productos.dat" , "rb" );
    VerifyPuntero( puntero );

    while (fread( &articulo, sizeof articulo, 1, puntero ))
    {
        if( articulo.get_estado() && articulo.get_categoria() == categoria )
        {
            articulo.mostrar_Producto(y);
            cont++;
            y++;
            gotoxy(x, ++y);
            barra();
            if( cont >= 1 )
                recuadro_midd(y - 2, 19, 80, 5, cROJO, cAQUA);
            y++;
            colorNormal();
        }
    }

    if( cont == 0 )
    {
        colorError();
        gotoxy(x,y+=2);
        cout << "No hay art" << char(161) << "culos con la categor" << char(161) << "a elegida." ;
        colorNormal();
        recuadro_midd(y - 2, 19, 80, 5, cROJO, cAQUA);
        recuadro_bott(y + 3, 19, 80, 0, cROJO, cAQUA);
        colorNormal();
        gotoxy(x, ++y);
        pause();
        return;
    }

    fclose( puntero );
    recuadro_bott(y + 3, 19, 80, 0, cROJO, cAQUA);
    gotoxy(x, y++);
    colorNormal();
    pause();
    return;
}


#endif // FINAL_H_INCLUDED
