#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED

void Producto::Guardar_Producto()
{
    FILE* Puntero = fopen( "Archivos/Productos.dat" , "ab" );

    if( Puntero == NULL )
    {
        clear();
        recuadro_top(5, 80, 19, 4, cROJO, cAQUA);
        colorError();
        gotoxy(40,6);
        perror("Error ");
        fclose( Puntero );
        recuadro_bott(9, 19, 80, 0, cROJO, cAQUA);
        gotoxy(20,8);
        colorNormal();
        pause();
        exit(1);
    }

    fwrite( this, sizeof *this, 1, Puntero );

    fclose( Puntero );
}

void Producto::Guardar_Producto( int pos )
{
    FILE* Puntero = fopen( "Archivos/Productos.dat" , "rb+" );

    if( Puntero == NULL )
    {
        clear();
        recuadro_top(5, 80, 19, 4, cROJO, cAQUA);
        colorError();
        gotoxy(40,6);
        perror("Error ");
        fclose( Puntero );
        recuadro_bott(9, 19, 80, 0, cROJO, cAQUA);
        gotoxy(20,8);
        colorNormal();
        pause();
        exit(1);
    }

    fseek( Puntero, pos * sizeof *this, SEEK_SET );
    fwrite( this, sizeof *this, 1, Puntero );

    fclose( Puntero );
}

void Producto::mostrar_Producto(int y)          /** TAMAÑO 5  **/
{
    int x = 20;
    gotoxy(x, y);
    cout << Codigo ;

    gotoxy(x +=12, y);
    cout << "$" << Precio_Unitario ;

    gotoxy(x +=21, y);
    cout << Stock;

    gotoxy(x +=11, y);
    cout << Descripcion ;

    gotoxy(x +=20, y);
    cout << Categoria << " (";
    switch( Categoria )
    {
    case 1:
        cout << "Perfumer" << char(161) << "a";
        break;
    case 2:
        cout << "Verduler" << char(161) << "a";
        break;
    case 3:
        cout << "Bebidas";
        break;
    case 4:
        cout << "Mascotas";
        break;
    case 5:
        cout << "Limpieza";
        break;
    case 6:
        cout << "Vestimenta";
        break;
    case 7:
        cout << "Frigor" << char(161) << "ficos";
        break;
    case 8:
        cout << "Electro";
        break;
    case 9:
        cout << "Panader" << char(161) << "a";
        break;
    case 10:
        cout << "Almac" << char(130) << "n";
        break;
    case 11:
        cout << "Otros";
        break;
    }
    cout << ")";
}

void Producto::Leer_Producto( int pos )
{
    FILE* Puntero = fopen( "Archivos/Productos.dat" , "rb+" );

    if( Puntero == NULL )
    {
        clear();
        recuadro_top(5, 80, 19, 4, cROJO, cAQUA);
        colorError();
        gotoxy(40,6);
        perror("Error ");
        fclose( Puntero );
        recuadro_bott(9, 19, 80, 0, cROJO, cAQUA);
        gotoxy(20,8);
        colorNormal();
        pause();
        exit(1);
    }

    fseek( Puntero, pos * sizeof *this, SEEK_SET );
    fread( this, sizeof *this, 1, Puntero );

    fclose( Puntero );
}

#endif // PRODUCTOS_H_INCLUDED
