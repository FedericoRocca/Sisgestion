#ifndef VENTAS_H_INCLUDED
#define VENTAS_H_INCLUDED

void Venta::setCodigo_Venta()
{
    FILE* Puntero = fopen( "Archivos/Ventas.dat" , "rb" );

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

    int Contador = 0;

    while( fread( this, sizeof *this, 1, Puntero ) )
    {
        Contador++;
    }

    Codigo_Venta = ++Contador;

    fclose( Puntero );

}

void Venta::Guardar_Venta()
{
    FILE* Puntero = fopen("Archivos/Ventas.dat" , "ab");

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
    fclose(Puntero);
}

float Preventa::RetornaValor(int CodigoVenta)
{

    FILE* Puntero = fopen("Archivos/Preventas.dat" , "ab");

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

    Preventa Aux;
    float Total = 0;

    while( fread( &Aux, sizeof Aux, 1, Puntero ) )
    {
        if( CodigoVenta == Aux.getCodigoVenta() )
        {
            Total += Aux.getCantidad() * Aux.getPrecioUnitario();
        }
    }

    fclose( Puntero );

    return Total;

}

void Preventa::Guardar_Preventa()
{
    FILE* Puntero = fopen("Archivos/Preventas.dat" , "ab");

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
    fclose(Puntero);
}

bool Preventa::Alta_CodigoArticulo(int x, int y)
{
    int CodArt;
    gotoxy(x, y++);
    cout<<"Ingresa el codigo de articulo: ";
    cin>>CodArt;

    /*if( Existe_Articulo( CodArt ) == false )
    {
        colorError();
        gotoxy(x, y++);
        cout << "El producto no existe";
        colorNormal();
        gotoxy(x, y++);
        pause();
        return false;
    }*/
    Codigo_Articulo = CodArt;

    Producto articulo;
    int pos = Buscar_Producto( CodArt );
    if( pos == -2 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "El producto no existe";
        colorNormal();
        gotoxy(x, y++);
        pause();
        return false;
    }
    articulo.Leer_Producto( pos );
    articulo.mostrar_Producto(y);

    return true;

};

bool Preventa::Alta_Cantidad(int x, int y)
{
    int Cant;
    gotoxy(x, y++);
    cout << "Ingresa la cantidad: ";
    cin >> Cant;

    if( Cant <= 0 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "Sin ventas cargadas." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return false;
    }

    Cantidad = Cant;
    if( Tiene_Stock( Codigo_Articulo, Cant ) )
        return true;
    else
        return false;
};

void Preventa::Alta_PrecioUnitario()
{
    Precio_Unitario = Retorna_PrecioUnitario( Codigo_Articulo );
}

void Venta::Leer_Venta( int pos )
{
    FILE* Puntero = fopen( "Archivos/Ventas.dat" , "rb+" );

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

void Venta::Mostrar_Venta(int y)    /**  TAMAÑO 6   **/
{
    int x = 20;
    gotoxy(x, y);
    cout << Codigo_Venta ;

    Fecha_Venta.mostrar_Fecha(x += 18, y);

    gotoxy(x += 17, y);
    cout << Legajo_Empleado ;

    gotoxy(x += 11, y);
    cout << Codigo_Cliente << "  ";
    if( Retorna_Tipo_C( Codigo_Cliente ) == 1 )
        cout << "(C/D)" ;
    else
        cout << "(S/D)" ;

    gotoxy(x += 10, y);
    switch( Forma_Pago )
    {
    case 'E':
        cout << "efectivo." ;
        break;
    case 'D':
        cout << "d" << char(130) << "bito." ;
        break;
    case 'C':
        cout << "cr" << char(130) << "dito." ;
        break;
    }

    gotoxy(x += 15, y);
    cout << "$" << Valor ;
}

#endif // VENTAS_H_INCLUDED
