#ifndef FUNCIONES_UTILES_H_INCLUDED
#define FUNCIONES_UTILES_H_INCLUDED

void clear();
void pause();
enum Color{
	cNEGRO = 0,
	cAZUL = 1,
	cVERDE = 2,
	cAQUA = 3,
	cROJO = 4,
	cFUCSIA = 5,
	cDORADO = 6,
	cGRIS_CLARO = 7,
	cGRIS = 8,
	cAZUL_CLARO = 9,
	cVERDE_CLARO = 10,
	cCIAN = 11,
	cROJO_CLARO = 12,
	cMAGENTA = 13,
	cAMARILLO = 14,
	cBLANCO = 15
};
void gotoxy(short, short);
void colorError();
void colorNormal();
void barra();
void Error_Menu();
void Establecer_Fecha();
void Imprimir_Fecha();
bool Evaluar_Cadena(char*);
bool Validar_Fecha(int, int, int);
bool Es_Bisiesto(int);
void Inicializar_Ventana(int,int);
const string currentDateTime();
bool Validar_Seguro(char);
void Estado_Usuario(int, bool);
int Buscar_Cliente(int);
int Buscar_Producto(int);
void Nueva_Venta(int);
float Retorna_PrecioUnitario(int);
bool Tiene_Stock(int, int);
int Retorna_Tipo_C(int);
int Retorna_Tipo_U(int);
float retorna_Descuento(int);
void MostrarDescuentos();
void SeteaDescuentos();
void restarStock(int, int);
int Buscar_Venta(int);
void modificar_Stock();
void eliminar_Producto();
void Baja_Usuario();
int Buscar_Usuario(int);
int Validar_Usuario(User);
int Validar_Cliente(Cliente);
int getUltimo_Legajo();
void Resetear_Pass();
void cambiar_Pass_C(Cliente&);
void cambiar_Pass_U(User&);
void Alta_Usuario();
int Alta_Cliente();
int getUltimo_Cliente();
void ordenarCodigos(char);
void Alta_Producto();
int getUltimo_Producto();
void Baja_Cliente_Tiempo();
void recuadro_top(short, short, short, short, short, short);
void recuadro_midd(short, short, short, short, short, short);
void recuadro_bott(short, short, short, short, short, short);
void InicializarArchivos();
void imprimir_Una_Factura();
void imprimir_Ultima_Factura();
void menu_Factura();
void titulos_venta(int);
void titulos_preVenta(int);
void titulos_producto(int);
void titulos_cliente(int);
void titulos_usuario(int);
Fecha RetornaUltimaCompra( int );
int ContarDias( Fecha );
void BajaCliente( int );
void VerifyPuntero(FILE*);




void VerifyPuntero(FILE* Puntero)
{
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
}

void Baja_Cliente_Tiempo()
{
    clear();
    int x = 20, y = 5;

    recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
    recuadro_midd(15, 19, 80, 3, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout << "BAJA CLIENTES POR TIEMPO";
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

    FILE* Puntero = fopen( "Archivos/Clientes.dat" , "rb" );
    VerifyPuntero( Puntero );

    Cliente Clientes;
    Fecha UltimaCompra;
    int Cuentabajas = 0;

    while( fread( &Clientes, sizeof Clientes, 1, Puntero ) )
    {
        if( Clientes.getEstado() == true )
        {
            ///Buscar la ultima compra del cliente

            UltimaCompra.set_fecha( RetornaUltimaCompra( Clientes.getCodigo() ) );

            ///Contar dias desde la ultima compra

            if (ContarDias( UltimaCompra ) > 90)
            {
                ///Si pasaron 90 dias, dar de baja el cliente
                BajaCliente( Clientes.getCodigo() );
                Cuentabajas++;
            }
        }
    }
    fclose( Puntero );

    y++;
    gotoxy(x, y++);
    cout << "Se dieron de baja " << Cuentabajas << " clientes." << endl;
    y++;
    gotoxy(x, ++y);
    pause();
    return;
}

Fecha RetornaUltimaCompra( int CodCli )
{
    FILE* Puntero = fopen( "Archivos/Ventas.dat" , "rb" );
    VerifyPuntero( Puntero );

    Venta Ventas;
    int Contador = 0;
    Fecha FechaAux;

    while( fread( &Ventas, sizeof Ventas, 1, Puntero ) )
    {
        if( CodCli == Ventas.getCodigo_Cliente())
        {
            FechaAux.set_fecha( Ventas.getFecha_Venta() );
            Contador++;
        }
    }

    fclose( Puntero );

    if( Contador <= 0 )
    {
        FechaAux.set_dia(1);
        FechaAux.set_mes(1);
        FechaAux.set_anio(1980);
        return FechaAux;
    } else return FechaAux;
}

int ContarDias( Fecha UltimaCompra )
{
    tm *tiempo;
    time_t fecha_sistema;
    time(&fecha_sistema);
    tiempo=localtime(&fecha_sistema);

    int DiaActual, MesActual, AnioActual;

    AnioActual=tiempo->tm_year + 1900;
    MesActual=tiempo->tm_mon + 1;
    DiaActual=tiempo->tm_mday;

    if( ( UltimaCompra.get_dia() == DiaActual ) && ( UltimaCompra.get_mes() == MesActual ) && ( UltimaCompra.get_anio() == AnioActual ) )
    {
        return 0;
    }

    int Dias = 0, Meses = 0, Anios = 0, DiasTotal = 0;

    Dias = UltimaCompra.get_dia();
    Meses = UltimaCompra.get_mes();
    Anios = UltimaCompra.get_anio();

    while( ( Dias != DiaActual ) && ( Meses != MesActual ) && ( Anios != AnioActual ) )
    {
        Dias++;
        DiasTotal++;

        switch(Meses)
        {
        case 1:
            if( Dias > 31 )
            {
                Meses++;
                Dias = 1;
                DiasTotal++;
            }
            break;

        case 2:
            if( Es_Bisiesto(Anios) == true )
            {
                if( Dias > 29 )
                {
                    Meses++;
                    Dias = 1;
                    DiasTotal++;
                }
                else
                if( Dias > 28 )
                {
                    Meses++;
                    Dias = 1;
                    DiasTotal++;
                }
            }
            break;

        case 3:
            if( Dias > 31 )
            {
                Meses++;
                Dias = 1;
                DiasTotal++;
            }
            break;

        case 4:
            if( Dias > 30 )
            {
                Meses++;
                Dias = 1;
                DiasTotal++;
            }
            break;

        case 5:
            if( Dias > 31 )
            {
                Meses++;
                Dias = 1;
                DiasTotal++;
            }
            break;

        case 6:
            if( Dias > 30 )
            {
                Meses++;
                Dias = 1;
                DiasTotal++;
            }
            break;

        case 7:
            if( Dias > 31 )
            {
                Meses++;
                Dias = 1;
                DiasTotal++;
            }
            break;

        case 8:
            if( Dias > 31 )
            {
                Meses++;
                Dias = 1;
                DiasTotal++;
            }
            break;

        case 9:
            if( Dias > 30 )
            {
                Meses++;
                Dias = 1;
                DiasTotal++;
            }
            break;

        case 10:
            if( Dias > 31 )
            {
                Meses++;
                Dias = 1;
                DiasTotal++;
            }
            break;

        case 11:
            if( Dias > 30 )
            {
                Meses++;
                Dias = 1;
                DiasTotal++;
            }
            break;

        case 12:
            if( Dias > 31 )
            {
                Meses = 1;
                Dias = 1;
                Anios++;
                DiasTotal++;
            }
            break;
        }
    }
    return DiasTotal;
}

void BajaCliente( int CodCli )
{
    FILE* Puntero = fopen( "Archivos/Clientes.dat" , "rb+" );
    VerifyPuntero( Puntero );

    Cliente Clientes;

    while( fread(&Clientes, sizeof Clientes, 1, Puntero) )
    {
        if( CodCli == Clientes.getCodigo() )
        {
            fseek( Puntero, -sizeof Clientes , SEEK_CUR );
            Clientes.setEstado( false );
            fwrite( &Clientes, sizeof Clientes, 1, Puntero );
            fclose( Puntero );
            return;
        }
    }
    fclose( Puntero );
    return;
}

void titulos_venta( int y )
{
    int x = 20;
    gotoxy(x, y);
    cout << "C" << char(162) << "digo de venta";
    gotoxy(x += 18, y);
    cout << "Fecha de venta";
    gotoxy(x += 17, y);
    cout << "Empleado";
    gotoxy(x += 11, y);
    cout << "Cliente";
    gotoxy(x += 10, y);
    cout << "Forma de pago";
    gotoxy(x += 15, y);
    cout << "Total";
}

void titulos_preVenta( int y )
{
    int x = 25;
    gotoxy(x, y);
    cout << "Art" << char(161) << "culo";
    gotoxy(x += 20, y);
    cout << "Cantidad";
    gotoxy(x += 15, y);
    cout << "Precio";
    gotoxy(x += 10, y);
    cout << "Subtotal";
}

void titulos_producto( int y )
{
    int x = 20;
    gotoxy(x, y);
    cout << "C" << char(162) << "digo";
    gotoxy(x += 12, y);
    cout << "Precio unitario";
    gotoxy(x += 21, y);
    cout << "Stock";
    gotoxy(x += 11, y);
    cout << "Descripci" << char(162) << "n";
    gotoxy(x += 20, y);
    cout << "Categor" << char(161) << "a";
}

void titulos_cliente( int y )
{
    int x = 20;
    gotoxy(x, y);
    cout << "C" << char(162) << "digo";
    gotoxy(x += 8, y);
    cout << "Nombre";
    gotoxy(x += 15, y);
    cout << "Apellido";
    gotoxy(x += 15, y);
    cout << "Contrase" << char(164) << "a";
    gotoxy(x += 15, y);
    cout << "Fecha alta";
    gotoxy(x += 12, y);
    cout << "Estado";
    gotoxy(x += 10, y);
    cout << "Tipo";
}

void titulos_usuario( int y )
{
    int x = 20;
    gotoxy(x, y);
    cout << "Legajo";
    gotoxy(x += 8, y);
    cout << "Nombre";
    gotoxy(x += 15, y);
    cout << "Apellido";
    gotoxy(x += 15, y);
    cout << "Contrase" << char(164) << "a";
    gotoxy(x += 15, y);
    cout << "Fecha alta";
    gotoxy(x += 12, y);
    cout << "Estado";
    gotoxy(x += 10, y);
    cout << "Tipo";
}

void menu_Factura()
{
    bool Menu = true;
    int x, y;
    while( Menu == true )
    {
        x = 20; y = 5;
        clear();
        recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
        colorNormal();
        gotoxy(x, y);
        cout << "FACTURAS  ";
        gotoxy(x + 60, y++);
        cout << currentDateTime();
        gotoxy(x, y++);
        barra();
        gotoxy(x, y++);
        cout << "1 - Imprimir " << char(163) << "ltima factura" ;
        gotoxy(x, y++);
        cout << "2 - Imprimir una factura" ;
        gotoxy(x, y++);
        barra();
        gotoxy(x, y++);
        cout << "Presione la opci" << char(162) << "n deseada. ESC para volver";
        recuadro_bott(14, 19, 80, 0, cROJO, cAQUA);
        gotoxy(x, y);

        switch( getch() )
        {
        case '1':
            imprimir_Ultima_Factura();
            pause();
            break;

        case '2':
            imprimir_Una_Factura();
            break;

        case 27:
            Menu = false;
            break;

        default:
            Error_Menu();
            break;
        }
    }
}

void imprimir_Una_Factura()
{
    int cod, x = 20, y = 5;
    clear();
    recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout << "IMPRIMIR UNA FACTURA";
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

    gotoxy(x, y++);
    cout << "Ingrese el c" << char(162) << "digo de venta a imprimir: ";
    cin >> cod;
    Venta venta;
	int pos = Buscar_Venta( cod );
	if( pos == -2 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "No se pudo encontrar la venta." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }
    else if ( pos == -1 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "Error de archivo de ventas." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }

    gotoxy(x, y++);
    barra();
    titulos_venta(y++);
    gotoxy(x, y++);
    barra();

    venta.Leer_Venta( pos );
    venta.Mostrar_Venta(y);
    y += 3;
    recuadro_midd(y, 19, 80, 4, cROJO, cAQUA);
    colorNormal();

    gotoxy(x, y++);
    barra();
    gotoxy(x, y++);
    titulos_preVenta(y++);
    gotoxy(x, y++);
    barra();
    Preventa preVenta;
    Producto articulo;

    FILE* Puntero = fopen( "Archivos/Preventas.dat" , "rb" );
    VerifyPuntero( Puntero );
    while( fread( &preVenta, sizeof preVenta, 1, Puntero ) )
    {
        if( preVenta.getCodigoVenta() == venta.getCodigo_Venta() )
        {
            pos = Buscar_Producto( preVenta.getCodigoArticulo() );
            if( pos == -2 )
            {
                colorError();
                gotoxy(x, y++);
                cout << "No se pudo encontrar el art" << char(161) << "culo." ;
                colorNormal();
                gotoxy(x, y++);
                pause();
                return;
            }
            else if ( pos == -1 )
            {
                colorError();
                gotoxy(x, y++);
                cout << "Error de archivo de art" << char(161) << "culos." ;
                colorNormal();
                gotoxy(x, y++);
                pause();
                return;
            }
            articulo.Leer_Producto( pos );
            gotoxy(x + 5, y);
            cout << articulo.get_descripcion();
            gotoxy(x + 25, y);
            cout << preVenta.getCantidad();
            gotoxy(x + 40, y);
            cout << preVenta.getPrecioUnitario();
            gotoxy(x + 50, y++);
            cout << preVenta.getCantidad() * preVenta.getPrecioUnitario();
            gotoxy(x, y++);
            barra();
            y++;
            recuadro_midd(y - 3, 19, 80, 4, cROJO, cAQUA);
            colorNormal();
        }
    }


    recuadro_bott(y + 2, 19, 80, 0, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y++);
    pause();
    return;
}

void imprimir_Ultima_Factura()
{
    int cod, x = 20, y = 5;
    clear();
    recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout << "IMPRIMIR " << char(233) << "LTIMA FACTURA";
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

    Venta venta;
	venta.setCodigo_Venta();
	cod = venta.getCodigo_Venta() - 1 ;

	int pos = Buscar_Venta( cod );
	if( pos == -2 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "No se pudo encontrar la venta." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }
    else if ( pos == -1 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "Error de archivo de ventas." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }

    gotoxy(x, y++);
    barra();
    titulos_venta(y++);
    gotoxy(x, y++);
    barra();

    venta.Leer_Venta( pos );
    venta.Mostrar_Venta(y);
    y += 3;
    recuadro_midd(y, 19, 80, 4, cROJO, cAQUA);
    colorNormal();

    gotoxy(x, y++);
    barra();
    gotoxy(x, y++);
    titulos_preVenta(y++);
    gotoxy(x, y++);
    barra();
    Preventa preVenta;
    Producto articulo;

    FILE* Puntero = fopen( "Archivos/Preventas.dat" , "rb" );
    VerifyPuntero( Puntero );
    while( fread( &preVenta, sizeof preVenta, 1, Puntero ) )
    {
        if( preVenta.getCodigoVenta() == venta.getCodigo_Venta() )
        {
            pos = Buscar_Producto( preVenta.getCodigoArticulo() );
            if( pos == -2 )
            {
                colorError();
                gotoxy(x, y++);
                cout << "No se pudo encontrar el art" << char(161) << "culo." ;
                colorNormal();
                gotoxy(x, y++);
                pause();
                return;
            }
            else if ( pos == -1 )
            {
                colorError();
                gotoxy(x, y++);
                cout << "Error de archivo de art" << char(161) << "culos." ;
                colorNormal();
                gotoxy(x, y++);
                pause();
                return;
            }
            articulo.Leer_Producto( pos );
            gotoxy(x + 5, y);
            cout << articulo.get_descripcion();
            gotoxy(x + 25, y);
            cout << preVenta.getCantidad();
            gotoxy(x + 40, y);
            cout << "$ " << preVenta.getPrecioUnitario();
            gotoxy(x + 50, y++);
            cout << "$ " << preVenta.getCantidad() * preVenta.getPrecioUnitario();
            gotoxy(x, y++);
            barra();
            y++;
            recuadro_midd(y - 3, 19, 80, 4, cROJO, cAQUA);
            colorNormal();
        }
    }


    recuadro_bott(y + 2, 19, 80, 0, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y++);
    pause();
    return;
}

void InicializarArchivos()
{
    FILE *Puntero;

    Puntero = fopen( "Archivos/Clientes.dat" , "rb" );
    if( Puntero == NULL )
    {
        fopen( "Archivos/Clientes.dat" , "wb" );
    }

    Puntero = fopen( "Archivos/Descuento.dat" , "rb" );
    if( Puntero == NULL )
    {
        fopen( "Archivos/Descuento.dat" , "wb" );
    }

    Puntero = fopen( "Archivos/Preventas.dat" , "rb" );
    if( Puntero == NULL )
    {
        fopen( "Archivos/Preventas.dat" , "wb" );
    }

    Puntero = fopen( "Archivos/Productos.dat" , "rb" );
    if( Puntero == NULL )
    {
        fopen( "Archivos/Productos.dat" , "wb" );
    }

    Puntero = fopen( "Archivos/Usuarios.dat" , "rb" );
    if( Puntero == NULL )
    {
        fopen( "Archivos/Usuarios.dat" , "wb" );
    }

    Puntero = fopen( "Archivos/Ventas.dat" , "rb" );
    if( Puntero == NULL )
    {
        fopen( "Archivos/Ventas.dat" , "wb" );
    }

    fclose( Puntero );

}

int getUltimo_Producto()
{
    Producto producto;
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
    int Cod = 1000;
    bool existe = false;
    while( fread( &producto, sizeof producto, 1, Puntero ) && !existe )
    {
        if( producto.get_codigo() == Cod )// && producto.get_estado() == true )
           Cod++;
        else
            existe = true;
    }
    ordenarCodigos('P');
    fclose( Puntero );
    return Cod;
}

void Alta_Producto()
{
    clear();
    Producto producto;
    bool error;
    char Descripcion[50];
    int aux_int, x = 20, y = 5;
    float aux_float;
    recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout << "ALTA PRODUCTO";
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

    producto.set_codigo( getUltimo_Producto() );
    gotoxy(x, y++);
    cout << "Ingrese descripci" << char(162) << "n del art" << char(161) << "culo: ";
    cin.ignore();
    cin.getline( Descripcion, 50 );
    strupr( Descripcion );
    producto.set_descripcion( Descripcion );
    error = true;
    gotoxy(x, y++);
    cout << "Ingrese stock: ";
    while ( error )
    {
        cin >> aux_int;
        if( aux_int >= 0 )
        {
            error = false;
            producto.set_stock( int( aux_int ) );
        }
        else
        {
            colorError();
            gotoxy(x, y++);
            cout << "El stock ingresado es inv" << char(160) << "lido." ;
            gotoxy(x, y++);
            cout << "Si desea salir, presione ESC, de lo contrario, cualquier tecla." ;
            colorNormal();
            gotoxy(x, y++);

            if( getch() == 27 )
            {
                gotoxy(x, y++);
                cout << "Cambios descartados." ;
                gotoxy(x, y++);
                pause();
                return;
            }
            gotoxy(x, y++);
            cout << "Ingr" << char(130) << "selo nuevamente: ";
            recuadro_midd(y, 19, 80, 4, cROJO, cAQUA);
            y += 5;
            colorNormal();
        }
    }
    error = true;
    gotoxy(x, y++);
    cout << "Ingrese precio unitario: $";
    while ( error )
    {
        cin >> aux_float;
        if( aux_float >= 0 )
        {
            error = false;
            producto.set_precio( aux_float);
        }
        else
        {
            colorError();
            gotoxy(x, y++);
            cout << "El precio ingresado es inv" << char(160) << "lido." ;
            gotoxy(x, y++);
            cout << "Si desea salir, presione ESC, de lo contrario, cualquier tecla." ;
            colorNormal();
            gotoxy(x, y++);

            if( getch() == 27 )
            {
                gotoxy(x, y++);
                cout << "Cambios descartados." ;
                gotoxy(x, y++);
                pause();
                return;
            }
            gotoxy(x, y++);
            cout << "Ingr" << char(130) << "selo nuevamente: ";
            recuadro_midd(y, 19, 80, 4, cROJO, cAQUA);
            y += 5;
            colorNormal();
        }
    }
    gotoxy(x, y++);
    cout << "Ingrese categor" << char(161) << "a:" ;
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
        cin >> aux_int;
        if( aux_int < 1 || aux_int > 11 )
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
                colorNormal();
                cout << "Cambios descartados." ;
                pause();
                return;
            }
            gotoxy(x, y++);
            cout << "Ingr" << char(130) << "sela nuevamente: ";
            recuadro_midd(y, 19, 80, 6, cROJO, cAQUA);
            y += 7;
            colorNormal();
        }
        else
        {
            error = false;
            producto.set_categoria( aux_int );
        }
    }
    producto.set_estado( true );
    producto.Guardar_Producto();
    recuadro_bott(y, 19, 80, 0, cROJO, cAQUA);

    clear();
    recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y++);
    cout << "ALTA PRODUCTO";
    gotoxy(x, y++);
    barra();

    gotoxy(x, y++);
    cout<<"Se cargo exitosamente el siguiente art" << char(161) << "culo: " ;
    gotoxy(x, y++);
    barra();
    titulos_producto(y++);
    gotoxy(x, y++);
    barra();
    producto.mostrar_Producto(y);
    recuadro_bott(15, 19, 80, 0, cROJO, cAQUA);
    gotoxy(x, y++);
    pause();
    return;
}

int getUltimo_Cliente()
{
    Cliente cliente;
    FILE* Puntero = fopen( "Archivos/Clientes.dat" , "rb+" );
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
    int Cod = 1;
    while( fread( &cliente, sizeof cliente, 1, Puntero ) )
    {
        if( cliente.getCodigo() == Cod )// && cliente.getEstado() == true )
           Cod++;
        else
            fseek(Puntero,0,SEEK_END);
    }
    ordenarCodigos('C');
    fclose( Puntero );
    return Cod;
}

int Validar_Cliente( Cliente cliente )
{
	Cliente aux;
	FILE *p;
	p = fopen( "Archivos/Clientes.dat", "rb" );
	if ( p == NULL )
		return -1;
	while ( fread( &aux, sizeof aux, 1, p ) )
	{
		if ( cliente.getCodigo() == aux.getCodigo() )
		{
		    if ( strcmp( cliente.GetPass(), aux.GetPass() ) == 0 )
		    {
                if ( aux.getEstado() == true )
                {
                    fclose( p );
                    return 0;
                }
		    }
		}
	}
	fclose( p );
	return 1;
}

int Alta_Cliente()
{
    int x = 20, y = 5;
    clear();
    recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout << "ALTA CLIENTE";
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

    Cliente cliente;
    char aux[26];
    int Tipo;
    bool continuar = true;
    cliente.setCodigo( getUltimo_Cliente() );

    gotoxy(x, y++);
    cout << "Ingresa el nombre del cliente: ";
    cin.ignore();
    cin.get( aux, 26 );
    strupr( aux );
    cliente.setNombre( aux );

    gotoxy(x, y++);
    cout << "Ingresa el apellido del cliente: ";
    cin.ignore();
    cin.get( aux, 26 );
    strupr( aux );
    cliente.setApellido( aux );

    cliente.resetPass();
    while(continuar)
    {
        gotoxy(x, y++);
        cout << "Ingresa el tipo de cliente (0 - com" << char(163) << "n, 1 - premium: ";
        Tipo = getch();

        if( Tipo == 27 )
        {
            clear();
            recuadro_top(5, 80, 19, 4, cROJO, cAQUA);
            colorError();
            gotoxy(40,6);
            cout << "Registro NO guardado";
            recuadro_bott(9, 19, 80, 0, cROJO, cAQUA);
            gotoxy(20,8);
            colorNormal();
            pause();
            return -2;
        }

        if( Tipo < '0' || Tipo > '1' )
        {
            clear();
            recuadro_top(5, 80, 19, 4, cROJO, cAQUA);
            recuadro_midd(15, 19, 80, 3, cROJO, cAQUA);
            colorError();
            gotoxy(40,6);
            cout << "Tipo de cliente ingresado incorrecto. Intente nuevamente." ;
            recuadro_bott(9, 19, 80, 0, cROJO, cAQUA);
            gotoxy(20,8);
            colorNormal();
            pause();

            x = 20; x = 5;

            clear();
            recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
            recuadro_midd(15, 19, 80, 3, cROJO, cAQUA);
            recuadro_bott(18, 19, 80, 0, cROJO, cAQUA);
            colorError();
            gotoxy(x, y++);
            cout << "ALTA CLIENTE";
            gotoxy(x, y++);
            barra();
            gotoxy(x, y++);
            cout << "Ingresa el nombre del cliente: ";
            gotoxy(x, y++);
            cout << cliente.GetNombre();
            gotoxy(x, y++);
            cout << "Ingresa el apellido del cliente: ";
            gotoxy(x, y++);
            cout << cliente.GetApellido();

        }
        else
        {
            if( Tipo == 48 )
            {
                cliente.setTipo( 0 );
            } else cliente.setTipo( 1 );

            continuar = false;
        }
    }
    cliente.setEstado( true );
    cliente.Guardar_Cliente();

    gotoxy(x, y++);
    barra();
    gotoxy(x, y++);
    cout << "Se cargo con exito el siguiente cliente: " ;
    gotoxy(x, y++);
    barra();
    titulos_cliente(y++);
    gotoxy(x, y++);
    barra();
    cliente.Mostrar_Cliente(y);
    recuadro_midd(y, 19, 80, 3, cROJO, cAQUA);
    recuadro_bott(y + 3, 19, 80, 0, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y++);
    pause();
    return cliente.getCodigo();
}

void Alta_Usuario()
{
    int x = 20, y = 5;
    clear();
    recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout << "ALTA USUARIO";
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

    User usuario;
    char aux[26];
    int Tipo;
    bool continuar = true;
    usuario.setLegajo( getUltimo_Legajo() );
    gotoxy(x, y++);
    cout << "Ingresa el nombre del usuario: ";
    cin.ignore();
    cin.get( aux, 26 );
    strupr( aux );
    usuario.setNombre( aux );

    gotoxy(x, y++);
    cout << "Ingresa el apellido del usuario: ";
    cin.ignore();
    cin.get( aux, 26 );
    strupr( aux );
    usuario.setApellido( aux );

    usuario.resetPass();

    gotoxy(x, y++);
    cout << "1 - Admin, 2 - Ventas, 3 - Proveedores" ;

    while( continuar )
    {
        gotoxy(x, y++);
        cout << "Ingresa el tipo de usuario: ";
        cin >> Tipo;
        if( Tipo < ADMIN || Tipo > PROVEEDORES )
        {
            gotoxy(x, y++);
            colorError();
            cout << "Tipo de usuario ingresado incorrecto. Vuelva a intentarlo " ;
            gotoxy(x, y++);
            cout << "Si desea volver al menu anterior, presione ESC " ;
            recuadro_midd(y, 19, 80, 5, cROJO, cAQUA);
            recuadro_bott(y + 5, 19, 80, 0, cROJO, cAQUA);
            colorNormal();
            pause();
            if( getch() == 27 )
            {
                clear();
                recuadro_top(5, 80, 19, 4, cROJO, cAQUA);
                colorError();
                gotoxy(40,6);
                cout << "Registro NO guardado";
                recuadro_bott(9, 19, 80, 0, cROJO, cAQUA);
                gotoxy(20,8);
                colorNormal();
                pause();
                return;
            }

        }
        else
        {
            continuar = false;
            usuario.setTipo( Tipo );
        }
    }
    usuario.setEstado( true );
    usuario.Guardar_Usuario();

    gotoxy(x, y++);
    barra();
    gotoxy(x, y++);
    cout << "Se cargo con exito el siguiente usuario: " ;
    gotoxy(x, y++);
    barra();
    titulos_usuario(y++);
    gotoxy(x, y++);
    barra();
    usuario.Mostrar_Usuario(y);
    recuadro_midd(y, 19, 80, 7, cROJO, cAQUA);
    recuadro_bott(y + 8, 19, 80, 0, cROJO, cAQUA);
    gotoxy(x, y += 7);
    pause();
    return;
}

void Resetear_Pass()
{
    int Legajo, x = 20, y = 5, pos;
    bool continuar;
    clear();
    recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
    recuadro_bott(15, 19, 80, 0, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout << "RESETEAR CONTRASE" << char(165) << "A";
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

    gotoxy(x, y++);
    cout << "Ingresa el usuario a resetear la contrase" << char(164) << "a: ";
    cin >> Legajo;
    pos = Buscar_Usuario( Legajo );
    if( pos < 0 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "El usuario ingresado no existe..." ;
        recuadro_bott(15, 19, 80, 0, cROJO, cAQUA);
        gotoxy(x, y++);
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }
    clear();
    x = 20; y = 5;
    User Usuario;
    Usuario.Leer_Usuario( pos );

    recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
    recuadro_midd(15, 19, 80, 3, cROJO, cAQUA);
    recuadro_bott(18, 19, 80, 0, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y++);
    cout << "RESETEAR CONTRASE" << char(165) << "A";
    gotoxy(x, y++);
    barra();

    gotoxy(x, y++);
    cout << "Desea resetear la contrase" << char(164) << "a del siguiente usuario?" ;
    gotoxy(x, y++);
    cout << "S para SI / N para NO" ;
    Usuario.Mostrar_Usuario(y);
    gotoxy(x, y += 7);
    barra();
    y++;
    while( continuar )
    {
        switch( getch() )
        {
        case 'S':
        case 's':
            Usuario.resetPass();
            Usuario.Guardar_Usuario( pos );
            clear();
            x = 20; y = 5;

            recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
            colorNormal();
            gotoxy(x, y++);
            cout << "RESETEAR CONTRASE" << char(165) << "A";
            gotoxy(x, y++);
            barra();

            gotoxy(x, y++);
            cout << "Usuario " << Legajo << " con nueva contrase" << char(164) << "a: " << Usuario.GetPass() ;
            continuar = false;
            break;
        case 'N':
        case 'n':
            colorError();
            gotoxy(x, y++);
            cout << "Cambios descartados." ;
            colorNormal();
            continuar = false;
            break;
        default:
            gotoxy(x, y++);
            cout << "Opci" << char(162) << "n incorecta. Vuelva a intentarlo." ;
            break;
        }
    }
    gotoxy(x, y + 2);
    pause();
    return;
}

int getUltimo_Legajo()
{
    User usuario;
    FILE* Puntero = fopen( "Archivos/Usuarios.dat" , "rb" );
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
    int Leg = 1000;
    while( fread( &usuario, sizeof usuario, 1, Puntero ) )
    {
        if( usuario.getLegajo() == Leg )// && usuario.getEstado() == true )
           Leg++;
        else
            fseek(Puntero,0,SEEK_END);
    }
    ordenarCodigos('U');
    fclose( Puntero );
    return Leg;
}

int Validar_Usuario( User usuario )
{
	User aux;
	FILE *p;
	p = fopen( "Archivos/Usuarios.dat", "rb" );
	if ( p == NULL )
		return -1;
	while ( fread( &aux, sizeof aux, 1, p ) )
	{
		if ( usuario.getLegajo() == aux.getLegajo() )
		{
		    if ( strcmp( usuario.GetPass(), aux.GetPass() ) == 0 )
		    {
                if ( usuario.getEstado() == true )
                {
                    fclose( p );
                    return 0;
                }
		    }
		}
	}
	fclose( p );
	return 1;
}

void Baja_Usuario()
{
    clear();
    User Usuario;
    int x = 20, y = 5, leg, pos;

    recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
    recuadro_midd(15, 19, 80, 3, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout << "BAJA USUARIO";
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

    gotoxy(x, y++);
    cout << "Ingresa el legajo a dar de baja: ";
    bool continuar = true;
    cin >> leg;
    pos = Buscar_Usuario( leg );
    if( pos >= 0 )
    {
        Usuario.Leer_Usuario( pos );
        gotoxy(x, y++);
        cout << "Proceder con la baja del siguiente usuario?" ;
        gotoxy(x, y++);
        cout << "S para SI / N para NO" ;
        gotoxy(x, y++);
        barra();
        titulos_usuario(y++);
        gotoxy(x, y++);
        barra();
        Usuario.Mostrar_Usuario(y);
        recuadro_midd(y, 19, 80, 3, cROJO, cAQUA);
        recuadro_bott(y += 3, 19, 80, 0, cROJO, cAQUA);
        colorNormal();
        y++;
        gotoxy(x, y++);
        barra();
        while( continuar )
        {
            switch( getch() )
            {
            case 'S':
            case 's':
                Usuario.setEstado( false );
                Usuario.Guardar_Usuario( pos );
                gotoxy(x, y++);
                cout << "Usuario dado de baja correctamente." ;
                continuar = false;
                break;
            case 'N':
            case 'n':
                colorError();
                gotoxy(x, y++);
                cout << "Cambios descartados." ;
                colorNormal();
                continuar = false;
                break;
            default:
                gotoxy(x, y++);
                cout << "Opci" << char(162) << "n incorecta. Vuelva a intentarlo." ;
                break;
            }
        }
        gotoxy(x, y++);
        pause();
        return;
    }
    gotoxy(x, y++);
    cout << "Usuario NO existe" ;
    pause();
}

int Buscar_Venta( int Cod )
{
    Venta V;
	int pos;
	FILE *p;
	p = fopen( "Archivos/Ventas.dat", "rb" );
	if ( p == NULL )
	{
		return -1;
	}
	while ( fread( &V, sizeof V, 1, p ) )
	{
		if ( V.getCodigo_Venta() == Cod )
		{
			pos = ftell( p ) / ( sizeof V );
			fclose( p );
			return pos - 1;
		}
	}
	fclose( p );
	return -2;
}

int Buscar_Producto( int Cod )
{
	Producto P;
	int pos;
	FILE *p;
	p = fopen( "Archivos/Productos.dat", "rb" );
	if ( p == NULL )
	{
		return -1;
	}
	while ( fread( &P, sizeof P, 1, p ) )
	{
		if ( P.get_codigo() == Cod && P.get_estado() == true )
		{
			pos = ftell( p ) / ( sizeof P );
			fclose( p );
			return pos - 1;
		}
	}
	fclose( p );
	return -2;
}

void modificar_Stock()
{
    int cod, stock, pos, x = 20, y = 5;
    clear();
    recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
    recuadro_midd(15, 19, 80, 3, cROJO, cAQUA);
    recuadro_bott(18, 19, 80, 0, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout << "MODIFICAR STOCK";
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

    gotoxy(x, y++);
    cout << "Ingrese el c" << char(162) << "digo de art" << char(161) << "culo a modificar: ";
    cin >> cod;
    Producto P;
	pos = Buscar_Producto( cod );
	if( pos == -2 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "No se pudo encontrar el art" << char(161) << "culo." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }
    else if ( pos == -1 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "Error de archivo de art" << char(161) << "culos." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }
	P.Leer_Producto( pos );
	gotoxy(x, y++);
	barra();
	gotoxy(x, y++);
    cout << "El stock actual es: " << P.get_stock() ;
    gotoxy(x, y++);
    cout << "Ingrese el nuevo stock: ";
    cin >> stock;
    P.set_stock( stock );
    barra();
    P.Guardar_Producto( pos );
    gotoxy(x, y++);
    cout << "Guardado exitoso." ;
    gotoxy(x, y++);
    barra();
    titulos_producto(y++);
    gotoxy(x, y++);
    barra();
    P.mostrar_Producto(y++);
    gotoxy(x, y++);
    barra();
    gotoxy(x, y++);
    pause();
    return;
}

void eliminar_Producto()
{
    int cod, x = 20, y = 5;
    clear();
    recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
    recuadro_midd(15, 19, 80, 3, cROJO, cAQUA);
    recuadro_bott(18, 19, 80, 0, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout << "ELIMINAR ART" << char(214) << "CULO";
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

    gotoxy(x, y++);
    cout << "Ingrese el c" << char(162) << "digo de art" << char(161) << "culo a eliminar: ";
    cin >> cod;
    Producto P;
	int pos = Buscar_Producto( cod );
	if( pos == -2 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "No se pudo encontrar el art" << char(161) << "culo." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }
    else if ( pos == -1 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "Error de archivo de art" << char(161) << "culos." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }
    gotoxy(x, y++);
    barra();
    titulos_producto(y++);
    gotoxy(x, y++);
    barra();
    P.Leer_Producto( pos );
    P.mostrar_Producto(y++);
    gotoxy(x, y++);
    barra();
    gotoxy(x, y++);
    cout << "Esta seguro que desea ELIMINAR el ART" << char(214) << "CULO? (S/N): ";
    while( true )
    {
        switch( getch() )
        {
        case 83:
        case 115:
            P.set_estado( false );
            P.Guardar_Producto( pos );
            gotoxy(x, y++);
            cout << "Art" << char(161) << "culo eliminado." ;
            gotoxy(x, y++);
            pause();
            return;
            break;
        case 78:
        case 110:
            gotoxy(x, y++);
            cout << "Cambios descartados." ;
            gotoxy(x, y++);
            pause();
            return;
            break;
        default:
            gotoxy(x, y++);
            cout << "Opci" << char(162) << "n incorrecta, vuelva a intentarlo." ;
            break;
        }
    }
}

void restarStock( int codigo, int cantidad  )
{
    Producto producto;
    int aux = Buscar_Producto( codigo );
    producto.Leer_Producto( aux );
    producto.set_stock( producto.get_stock() - cantidad );
    producto.Guardar_Producto( aux );
    return;
}

void MostrarDescuentos()
{
    clear();
    int x = 20, y = 5;
    recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
    recuadro_bott(15, 19, 80, 0, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout << "MOSTRAR DESCUENTOS";
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

    gotoxy(x, y++);
    cout << "Descuento por cliente premium: " << ( 1 - retorna_Descuento(0) ) * 100 << "%" ;
    gotoxy(x, y++);
    cout << "Descuento por pago en efectivo: " << ( 1 - retorna_Descuento(1) ) * 100 << "%" ;
    gotoxy(x, y++);
    cout << "Descuento por pago con tarjeta de cr" << char(130) << "dito: " << ( 1 - retorna_Descuento(2) ) * 100 << "%" ;
    gotoxy(x, y++);
    cout << "Descuento por pago con tarjeta de d" << char(130) << "bito: " << ( 1 - retorna_Descuento(3) ) * 100 << "%" ;
    gotoxy(x, y++);
    barra();
    gotoxy(x, y++);
    pause();
}

void SeteaDescuentos()
{
    clear();
    int x = 20, y = 5;
    recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
    recuadro_bott(15, 19, 80, 0, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout << "SETEAR DESCUENTOS";
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

    gotoxy(x, y++);
    cout << "1 - Descuento por cliente premium" ;
    gotoxy(x, y++);
    cout << "2 - Descuento por pago en efectivo" ;
    gotoxy(x, y++);
    cout << "3 - Descuento por pago con tarjeta de cr" << char(130) << "dito" ;
    gotoxy(x, y++);
    cout << "4 - Descuento por pago con tarjeta de d" << char(130) << "bito" ;
    gotoxy(x, y++);
    cout<<"Ingrese opci" << char(162) << "n: ";
    bool continuar = true;
    int opcion;
    while( continuar )
    {
        opcion = getch();
        switch( opcion )
        {
        case 49:
            cout << "1" ;
            opcion = 0;
            continuar = false;
            gotoxy(x, y++);
            cout << "Descuento actual: " << ( 1 - retorna_Descuento(0) ) * 100 << "%" ;
            break;
        case 50:
            cout << "2" ;
            opcion = 1;
            continuar = false;
            gotoxy(x, y++);
            cout << "Descuento actual: " << ( 1 - retorna_Descuento(1) ) * 100 << "%" ;
            break;
        case 51:
            cout << "3" ;
            opcion = 2;
            continuar = false;
            gotoxy(x, y++);
            cout << "Descuento actual: " << ( 1 - retorna_Descuento(2) ) * 100 << "%" ;
            break;
        case 52:
            cout << "4" ;
            opcion = 3;
            continuar = false;
            gotoxy(x, y++);
            cout << "Descuento actual: " << ( 1 - retorna_Descuento(3) ) * 100 << "%" ;
            break;
        default:
            gotoxy(x, y++);
            cout << "Opci" << char(162) << "n incorrecta. Intente nuevamente: ";
            break;
        }
    }
    continuar = true;
    gotoxy(x, y++);
    cout << "Ingrese el descuento deseado (formato 50%): %";
    float Desc;
    while( continuar )
    {
        cin >> Desc;
        if( Desc < 0 || Desc > 100 )
        {
            gotoxy(x, y++);
            cout << "Valor ingresado incorrecto. Vuelva a intentarlo" ;
        }
        else
            continuar = false;
    }
    Desc = ( 100 - Desc ) / 100;
    if( Desc == 0 )
        Desc = 1;
    FILE *Puntero = fopen( "Archivos/Descuento.dat" , "rb+" );
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
    fseek( Puntero, opcion * sizeof( float ) , SEEK_SET );
    fwrite( &Desc, sizeof Desc, 1, Puntero );
    fclose( Puntero );

    gotoxy(x, y++);
    barra();
    gotoxy(x, y++);
    cout << "Descuento seteado con exito." ;
    gotoxy(x, y++);
    pause();
    return;
}

float retorna_Descuento( int pos )
{
/*************************************************************

RECIBE:
        0 DESCUENTO POR CLIENTE
        1 DESCUENTO POR PAGO EN EFECTIVO
        2 DESCUENTO POR PAGO EN CREDITO
        3 DESCUENTO POR PAGO EN DEBITO

**************************************************************/

    FILE* Puntero = fopen( "Archivos/Descuento.dat" , "rb+" );
    if( Puntero == NULL )
        return -1;
    float Aux;
    fseek( Puntero, sizeof (float) * pos, SEEK_SET );
    fread( &Aux, sizeof (float), 1, Puntero );
    fclose( Puntero );
    return Aux;
}

float Retorna_PrecioUnitario(int CodArt)
{
    FILE* Puntero = fopen( "Archivos/Productos.dat" , "rb" );

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

    Producto Aux;

    while( fread( &Aux, sizeof Aux, 1, Puntero ) )
    {
        if( CodArt == Aux.get_codigo() && Aux.get_estado() == true )
        {
            fclose( Puntero );
            return Aux.get_precio();
        }
    }

    fclose( Puntero );
    return -1;

}

bool Tiene_Stock(int CodArt, int cant)
{
    Producto Aux;
    Aux.Leer_Producto( Buscar_Producto( CodArt ) );
    int stock = Aux.get_stock();
    if( ( stock - cant ) > 0 )
        return true;
    else
        return false;
}

void Nueva_Venta(int Legajo)
{
    float subtotal = 0, total;
    bool continuar = true;
    int aux, x, y;
    Venta Obj_Venta;
    Preventa Obj_PreVenta;

    clear();
    x = 20; y = 5;
    recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
    recuadro_midd(15, 19, 80, 10, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout << "NUEVA VENTA             ";
    gotoxy(x + 60, y++);
    cout << currentDateTime() ;
    gotoxy(x, y++);
    barra();

    Obj_Venta.setCodigo_Venta();
    Obj_Venta.setLegajo_Empleado(Legajo);
    Obj_PreVenta.Alta_Codigo_Venta( Obj_Venta.getCodigo_Venta() );
    FILE *Puntero = fopen("Archivos/Preventas.dat","ab");
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
    gotoxy(x, y);
    cout << "C" << char(162) << "digo de venta: ";
    gotoxy(x + 40, y++);
    cout << Obj_Venta.getCodigo_Venta() ;
    gotoxy(x, y);
    cout << "Empleado: ";
    gotoxy(x + 40, y++);
    cout << Obj_Venta.getLegajo_Empleado() ;
    gotoxy(x, y++);
    barra();
    while(continuar)
    {
        clear();
        x = 20; y = 5;
        recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
        recuadro_midd(15, 19, 80, 10, cROJO, cAQUA);
        colorNormal();
        gotoxy(x, y);
        cout << "NUEVA VENTA             ";
        gotoxy(x + 60, y++);
        cout << currentDateTime() ;
        gotoxy(x, y++);
        barra();
        gotoxy(x, y);
        cout << "C" << char(162) << "digo de venta: ";
        gotoxy(x + 40, y++);
        cout << Obj_Venta.getCodigo_Venta() ;
        gotoxy(x, y);
        cout << "Empleado: ";
        gotoxy(x + 40, y++);
        cout << Obj_Venta.getLegajo_Empleado() ;
        gotoxy(x, y++);
        barra();
        gotoxy(x, y);
        cout << "Subtotal: $";
        gotoxy(x + 40, y++);
        cout << subtotal ;
        gotoxy(x, y++);
        barra();
        if( Obj_PreVenta.Alta_CodigoArticulo(x, y) )
        {
            if( Obj_PreVenta.Alta_Cantidad(x, y += 6) )
            {
                y++;
                restarStock( Obj_PreVenta.getCodigoArticulo(), Obj_PreVenta.getCantidad() );
                Obj_PreVenta.Alta_PrecioUnitario();
                Obj_PreVenta.Guardar_Preventa();
                subtotal += Obj_PreVenta.getCantidad() * Obj_PreVenta.getPrecioUnitario();
            }
            else
            {
                y += 3;
                colorError();
                gotoxy(x, y++);
                cout << "Se descart" << char(162) << " este art" << char(161) << "culo por falta de stock." ;
                colorNormal();
            }
        }
        else
        {
            y += 3;
            colorError();
            gotoxy(x, y++);
            cout << "Se descart" << char(162) << " este art" << char(161) << "culo." ;
            colorNormal();
        }
        gotoxy(x, y++);
        barra();
        gotoxy(x, y++);
        cout << "Presione cualquier tecla para seguir cargando, de lo contrario, ESC." ;
        switch( getch() )
        {
        case 27:
            continuar = false;
            break;
        }
    }
    clear();
    x = 20; y = 5;
    recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
    recuadro_midd(15, 19, 80, 10, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout << "NUEVA VENTA             ";
    gotoxy(x + 60, y++);
    cout << currentDateTime() ;
    gotoxy(x, y++);
    barra();
    gotoxy(x, y);
    cout << "C" << char(162) << "digo de venta: ";
    gotoxy(x + 40, y++);
    cout << Obj_Venta.getCodigo_Venta() ;
    gotoxy(x, y);
    cout << "Empleado: ";
    gotoxy(x + 40, y++);
    cout << Obj_Venta.getLegajo_Empleado() ;
    gotoxy(x, y++);
    barra();
    gotoxy(x, y);
    cout << "Subtotal: $";
    gotoxy(x + 40, y++);
    cout << subtotal ;
    gotoxy(x, y++);
    barra();
    gotoxy(x, y++);
    cout << "Ingrese 1 - cliente registrado, 2 - desea registrarse, 3 - continuar igual: ";
    continuar = true;
    while( continuar )
    {
        switch( getch() )
        {
        case 49:
            gotoxy(x, y++);
            cout << "Ingrese c" << char(162) << "digo de cliente: ";
            cin >> aux;
            if( Buscar_Cliente( aux ) >= 0 )
            {
                Obj_Venta.setCodigo_Cliente( aux );
                continuar = false;
            }
            else
            {
                colorError();
                gotoxy(x, y++);
                cout << "Cliente no encontrado. Vuelva a intentarlo o presione 0 para seguir sin cargarlo" ;
                colorNormal();
            }
            break;
        case 50:
            aux = Alta_Cliente();
            if( aux != -2 )
            {
                Obj_Venta.setCodigo_Cliente( aux );
                continuar = false;
            }
            break;
        case 48:
        case 51:
            Obj_Venta.setCodigo_Cliente( 0 );
            continuar = false;
            break;
        default:
            gotoxy(x, y++);
            cout << "Opci" << char(162) << "n incorrecta. Vuelva a intentarlo." ;
            break;
        }
    }
    clear();
    x = 20; y = 5;
    recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
    recuadro_midd(15, 19, 80, 10, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout << "NUEVA VENTA             ";
    gotoxy(x + 60, y++);
    cout << currentDateTime() ;
    gotoxy(x, y++);
    barra();
    gotoxy(x, y);
    cout << "C" << char(162) << "digo de venta: ";
    gotoxy(x + 40, y++);
    cout << Obj_Venta.getCodigo_Venta() ;
    gotoxy(x, y);
    cout << "Empleado: ";
    gotoxy(x + 40, y++);
    cout << Obj_Venta.getLegajo_Empleado() ;
    gotoxy(x, y);
    cout << "Cliente: ";
    gotoxy(x + 40, y++);
    cout << Obj_Venta.getCodigo_Cliente() ;
    gotoxy(x, y++);
    barra();
    gotoxy(x, y++);
    if( Retorna_Tipo_C( Obj_Venta.getCodigo_Cliente() ) == 1 )
    {
        total = subtotal * retorna_Descuento( 0 ) ;
        gotoxy(x, y);
        cout << "Subtotal: $";
        gotoxy(x + 40, y++);
        cout << total ;
    }
    else
    {
        total = subtotal;
        gotoxy(x, y);
        cout << "Subtotal: $";
        gotoxy(x + 40, y++);
        cout << total ;
    }
    gotoxy(x, y++);
    barra();
    gotoxy(x, y++);
    cout << "1 - Efectivo,  2 - Cr" << char(130) << "dito,  3 - D" << char(130) << "bito" ;
    subtotal = total;
    continuar = true;
    while( continuar )
    {
        gotoxy(x, y++);
        cout << "Ingrese su forma de pago: ";
        switch( getch() )
        {
        case '1':
            gotoxy(x, y++);
            cout << "1" ;
            total = subtotal * retorna_Descuento( 1 );
            gotoxy(x, y++);
            barra();
            gotoxy(x, y++);
            cout << "Confirmar el pago de: $" << total << " con efectivo?" ;
            gotoxy(x, y++);
            cout << "(ENTER para confirmar, cualquier tecla para cambiar.)" ;
            if( getch() == 13 )
            {
                Obj_Venta.setForma_Pago( 'E' );
                continuar = false;
            }
            break;
        case '2':
            gotoxy(x, y++);
            cout << "2" ;
            total = subtotal * retorna_Descuento( 2 );
            gotoxy(x, y++);
            barra();
            gotoxy(x, y++);
            cout << "Confirmar el pago de: $" << total << " con cr" << char(130) << "dito?" ;
            gotoxy(x, y++);
            cout << "(ENTER para confirmar, cualquier tecla para cambiar.)" ;
            if( getch() == 13 )
            {
                Obj_Venta.setForma_Pago( 'C' );
                continuar = false;
            }
            break;
        case '3':
            gotoxy(x, y++);
            cout << "3" ;
            total = subtotal * retorna_Descuento( 3 );
            gotoxy(x, y++);
            barra();
            gotoxy(x, y++);
            cout << "Confirmar el pago de: $" << total << " con d" << char(130) << "bito?" ;
            gotoxy(x, y++);
            cout << "(ENTER para confirmar, cualquier tecla para cambiar.)" ;
            if( getch() == 13 )
            {
                Obj_Venta.setForma_Pago( 'D' );
                continuar = false;
            }
            break;
        default:
            colorError();
            gotoxy(x, y++);
            cout << "Opci" << char(162) << "n incorrecta. Vuelva a intentarlo" ;
            colorNormal();
        }
    }
    Obj_Venta.setValor( total );
    Obj_Venta.Guardar_Venta();

    clear();
    x = 20; y = 5;
    recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
    recuadro_midd(15, 19, 80, 10, cROJO, cAQUA);
    recuadro_bott(25, 19, 80, 0, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout << "VENTA GUARDADA";
    gotoxy(x + 60, y++);
    cout << currentDateTime() ;
    gotoxy(x, y++);
    barra();
    gotoxy(x, y);
    cout << "C" << char(162) << "digo de venta: ";
    gotoxy(x + 40, y++);
    cout << Obj_Venta.getCodigo_Venta() ;
    gotoxy(x, y);
    cout << "Empleado: ";
    gotoxy(x + 40, y++);
    cout << Obj_Venta.getLegajo_Empleado() ;
    gotoxy(x, y);
    cout << "Cliente: ";
    gotoxy(x + 40, y);
    cout << Obj_Venta.getCodigo_Cliente() << " - ";
    if( Retorna_Tipo_C( Obj_Venta.getCodigo_Cliente() ) == 0 )
        cout << "con descuento." ;
    else
        cout << "sin descuento." ;
    y++;
    gotoxy(x, y++);
    barra();
    gotoxy(x, y);
    cout << "Forma de pago: ";
    switch( Obj_Venta.getForma_Pago() )
    {
    case 'E':
        gotoxy(x + 40, y++);
        cout << "efectivo." ;
        break;
    case 'D':
        gotoxy(x + 40, y++);
        cout << "d" << char(130) << "bito." ;
        break;
    case 'C':
        gotoxy(x + 40, y++);
        cout << "cr" << char(130) << "dito." ;
        break;
    }
    gotoxy(x, y);
    cout << "Total: $";
    gotoxy(x + 40, y++);
    cout << Obj_Venta.getValor() ;
    gotoxy(x, y++);
    barra();
    gotoxy(x, y++);
    pause();
    imprimir_Ultima_Factura();
    return;
}

void Estado_Usuario( int Legajo, bool _Estado)
{
    FILE* Puntero = fopen( "Archivos/Usuarios.dat" , "rb+" );

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

    User AUX;

    while( fread(&AUX, sizeof AUX, 1, Puntero) )
    {
        if( Legajo == AUX.getLegajo() )
        {
            fseek( Puntero, -sizeof AUX, SEEK_CUR );
            AUX.setEstado(_Estado);
            fwrite(&AUX, sizeof AUX, 1, Puntero);
            fclose(Puntero);
            return;
        }
    }

    fclose(Puntero);
    return;
}

bool Validar_Seguro(char *Seguro)
{
    strupr(Seguro);

    if( strcmp(Seguro, "S") == 0 )
    {
        return true;
    } else return false;
}

const string currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d/%m/%Y %X", &tstruct);

    return buf;
}

void Inicializar_Ventana(int Ancho, int Alto)
{
    _COORD coord;
    coord.X = Ancho;
    coord.Y = Alto;

    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = 50;
    Rect.Right = Ancho - 1 ;

    SetConsoleTitle("Sisgestion - Puyelli Sebastian - Rocca Federico - LabII");
    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle
    SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size
    SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size
    colorNormal();
}

bool Es_Bisiesto(int Anio)
{
    if( ( Anio%4 == 0 && Anio%100 != 100 ) || Anio%400 ==0 )
    {
        return true;
    }
    return false;
}

bool Validar_Fecha(int Dia, int Mes, int Anio)
{
    bool Bisiesto = false;
    Bisiesto = Es_Bisiesto( Anio );

    //comprobamos que los datos ingresados esten en un rango valido
    if(Dia > 0 && Dia < 32 && Mes > 0 && Mes < 13 && Anio > 0 ){
        if(Mes == 1 || Mes == 3 || Mes == 5 || Mes == 7 || Mes == 8 || Mes == 10 || Mes == 12)
        {
           return true;
        }
        else
        {
            if(Mes == 2 && Dia < 30 && Bisiesto)
                return true;
            else if(Mes == 2 && Dia < 29 && !Bisiesto)
                return true;
            else if(Mes != 2 && Dia < 31)
                return true;
            else
                return false;
        }
    }
    else
        return false;
}

bool Evaluar_Cadena(char* Cadena)
{
    ///Evalua una cadena, es caso de encontrar numero o simbolos devuelve true
    int i=0;
    while( Cadena[i] != '\0' )
    {

        if(
           Cadena[i] != 'a' && Cadena[i] != 'A' &&
           Cadena[i] != 'b' && Cadena[i] != 'B' &&
           Cadena[i] != 'c' && Cadena[i] != 'C' &&
           Cadena[i] != 'd' && Cadena[i] != 'D' &&
           Cadena[i] != 'e' && Cadena[i] != 'E' &&
           Cadena[i] != 'f' && Cadena[i] != 'F' &&
           Cadena[i] != 'g' && Cadena[i] != 'G' &&
           Cadena[i] != 'h' && Cadena[i] != 'H' &&
           Cadena[i] != 'i' && Cadena[i] != 'I' &&
           Cadena[i] != 'j' && Cadena[i] != 'J' &&
           Cadena[i] != 'k' && Cadena[i] != 'K' &&
           Cadena[i] != 'l' && Cadena[i] != 'L' &&
           Cadena[i] != 'm' && Cadena[i] != 'M' &&
           Cadena[i] != 'n' && Cadena[i] != 'N' &&
           Cadena[i] != 'o' && Cadena[i] != 'O' &&
           Cadena[i] != 'p' && Cadena[i] != 'P' &&
           Cadena[i] != 'q' && Cadena[i] != 'Q' &&
           Cadena[i] != 'r' && Cadena[i] != 'R' &&
           Cadena[i] != 's' && Cadena[i] != 'S' &&
           Cadena[i] != 't' && Cadena[i] != 'T' &&
           Cadena[i] != 'u' && Cadena[i] != 'U' &&
           Cadena[i] != 'v' && Cadena[i] != 'V' &&
           Cadena[i] != 'w' && Cadena[i] != 'W' &&
           Cadena[i] != 'x' && Cadena[i] != 'X' &&
           Cadena[i] != 'y' && Cadena[i] != 'Y' &&
           Cadena[i] != 'z' && Cadena[i] != 'Z'
           )
        {
            return true;
        }
        i++;
    }
    return false;
}

void textcolor( short colorTexto = 15, short colorFondo = 0 )
{
	short color = colorTexto + colorFondo * 16;
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), color );
}

void colorError()
{
	textcolor( cROJO, cBLANCO );
}

void colorNormal()
{
	textcolor( cBLANCO, cAQUA );
}

void Error_Menu()
{
    clear();
    recuadro_top(5, 80, 19, 4, cROJO, cAQUA);
    colorError();
    gotoxy(40,6);
    cout << "Se ingreso una opcion inexistente.";
    recuadro_bott(9, 19, 80, 0, cROJO, cAQUA);
    gotoxy(20,8);
    colorNormal();
    pause();
}

void pause()
{
    cout<<"Presione cualquier tecla para continuar...";
    system("pause >NUL");
}

void clear()
{
    if( getenv("OS") == NULL)
    {
        system(" clear ");
    } else
        {
            system(" cls ");
        }
}

void barra()
{
    for ( int i = 0; i < 79; i++ )
    {
        cout << char( 196 );
    }
}

void gotoxy( short x, short y )
{
	COORD a;
	a.X = x;
	a.Y = y;
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), a );
}

COORD getPosicionXY()
{
    COORD A;
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    HANDLE Hcon;
    Hcon = GetStdHandle ( STD_OUTPUT_HANDLE );
    GetConsoleScreenBufferInfo ( Hcon, &SBInfo );
    A.X = SBInfo.dwCursorPosition.X;
    A.Y = SBInfo.dwCursorPosition.Y;
    return A;
}

void escribirContrasenia( char *pass )
{
    COORD pos;
	int i = 0, a;
	while ( i < 13 )
	{
	    pos = getPosicionXY();
		a = getch();
		if ( a == 13 )
		{
			pass [i] = '\0';
			return;
		}
		if ( a == 8 )
		{
		    if( i > 0)
			{
			    pass [i--] = '\0';
                pos.X--;
                gotoxy( pos.X, pos.Y );
                cout << " ";
                gotoxy( pos.X, pos.Y );
			}
		}
		else
		{
			cout << "*";
			pass [i] = char( a );
			i++;
			pos.X++;
		}

	}
}

int Buscar_Usuario( int Leg)
{
	User U;
	int pos;
	FILE *p;
	p = fopen( "Archivos/Usuarios.dat", "rb" );
	if ( p == NULL )
	{
		return -1;
	}
	while ( fread( &U, sizeof U, 1, p ) )
	{
		if ( U.getLegajo() == Leg && U.getEstado() == true )
		{
			pos = ftell( p ) / ( sizeof U );
			fclose( p );
			return pos - 1;
		}
	}
	fclose( p );
	return -2;
}

int Buscar_Cliente( int Cod )
{
	Cliente C;
	int pos;
	FILE *p;
	p = fopen( "Archivos/Clientes.dat", "rb" );
	if ( p == NULL )
	{
		return -1;
	}
	while ( fread( &C, sizeof C, 1, p ) )
	{
		if ( C.getCodigo() == Cod && C.getEstado() == true )
		{
			pos = ftell( p ) / ( sizeof C );
			fclose( p );
			return pos - 1;
		}
	}
	fclose( p );
	return -2;
}

int Retorna_Tipo_C(int _Codigo)
{
    FILE* Puntero = fopen( "Archivos/Clientes.dat" , "rb" );

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

    Cliente C;

    while( fread( &C, sizeof C, 1, Puntero ) )
    {
        if( _Codigo == C.getCodigo() )
        {
            fclose( Puntero );
            return C.getTipo();
        }
    }

    fclose( Puntero );
    return -1;
}

int Retorna_Tipo_U(int _Legajo)
{
    FILE* Puntero = fopen( "Archivos/Usuarios.dat" , "rb" );

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

    User Usuario;

    while( fread( &Usuario, sizeof Usuario, 1, Puntero ) )
    {
        if( _Legajo == Usuario.getLegajo() )
        {
            fclose( Puntero );
            return Usuario.getTipo();
        }
    }

    fclose( Puntero );
    return -1;
}

void cambiar_Pass_C(Cliente &cliente)
{
    clear();
    int x = 20, y = 5;
    recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
    recuadro_bott(15, 19, 80, 0, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout << "CAMBIAR CONTRASE" << char(165) << "A DE CLIENTE";
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

    char contrasenia[13];
    int pos = Buscar_Cliente( cliente.getCodigo() );
    if( pos == -1 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "Error de archivo." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }
    else if( pos == -2 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "Error, cliente no encontrado." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }
    cliente.Leer_Cliente( pos );
    gotoxy(x, y);
    cout << "Ingrese contrase" << char(164) << "a actual: ";
    escribirContrasenia(contrasenia);
    y += 2;
    if( strcmp(contrasenia,cliente.GetPass()) != 0 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "Error, la contrase" << char(164) << "a no coincide con el cliente logueado." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }
    gotoxy(x, ++y);
    cout << "Ingrese contrase" << char(164) << "a nueva: ";
    escribirContrasenia(contrasenia);
    y++;
    gotoxy(x, y);
    cout << "Vuelva a escribir la contrase" << char(164) << "a nueva: ";
    char pass[13];
    escribirContrasenia(pass);
    y += 2;
    if( strcmp(contrasenia,pass) != 0 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "Error, las contrase" << char(164) << "as no coinciden." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }
    cliente.setContrasenia( pass );
    cliente.Guardar_Cliente( pos );
    gotoxy(x, y++);
    cout << "Contraseña cambiada exitosamente." ;
    gotoxy(x, y++);
    pause();
    return;
}

void cambiar_Pass_U(User &usuario)
{
    clear();
    int x = 20, y = 5;
    recuadro_top(10, 80, 19, 4, cROJO, cAQUA);
    recuadro_bott(15, 19, 80, 0, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout << "CAMBIAR CONTRASE" << char(165) << "A DE USUARIO";
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

    char contrasenia[13];
    int pos = Buscar_Usuario( usuario.getLegajo() );
    if( pos == -1 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "Error de archivo." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }
    else if( pos == -2 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "Error, usuario no encontrado." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }
    usuario.Leer_Usuario( pos );
    gotoxy(x, y);
    cout << "Ingrese contrase" << char(164) << "a actual: ";
    escribirContrasenia(contrasenia);
    y += 2;
    if( strcmp(contrasenia,usuario.GetPass()) != 0 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "Error, la contrase" << char(164) << "a no coincide con el usuario logueado." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }
    gotoxy(x, ++y);
    cout << "Ingrese contrase" << char(164) << "a nueva: ";
    escribirContrasenia(contrasenia);
    y++;
    gotoxy(x, y);
    cout << "Vuelva a escribir la contrase" << char(164) << "a nueva: ";
    char pass[13];
    escribirContrasenia(pass);
    y += 2;
    if( strcmp(contrasenia,pass) != 0 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "Error, las contrase" << char(164) << "as no coinciden." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }
    usuario.setContrasenia( pass );
    usuario.Guardar_Usuario( pos );
    gotoxy(x, y++);
    cout << "Contraseña cambiada exitosamente." ;
    gotoxy(x, y++);
    pause();
    return;
}

void ordenarCodigos(char tipo)
{
    FILE *p;
    int tam, i, j;
    switch(tipo)
    {
    case 'U':
        {
            p=fopen("Archivos/Usuarios.dat","rb+");
            if( p == NULL )
            {
                clear();
                recuadro_top(5, 80, 19, 4, cROJO, cAQUA);
                colorError();
                gotoxy(40,6);
                perror("Error ");
                fclose( p );
                recuadro_bott(9, 19, 80, 0, cROJO, cAQUA);
                gotoxy(20,8);
                colorNormal();
                pause();
                exit(1);
            }
            fseek(p, 0, SEEK_END);
            tam = ftell(p) / sizeof( User );
            User usuAux, *usuVec;
            usuVec = new User [tam];
            if( usuVec == NULL )
            {
                fclose(p);
                exit(1);;
            }
            fseek(p, 0, SEEK_SET);
            fread(usuVec, sizeof( User ), tam, p);
            for(i=0;i<(tam-1);i++)
            {
                for(j=i+1;j<tam;j++)
                {
                    if( ( usuVec[j].getLegajo() < usuVec[i].getLegajo() ) && ( ( usuVec[j].getEstado() == true ) && ( usuVec[i].getEstado() == true ) ) )
                    {
                        /// aux = vec[j] ;
                        usuAux = usuVec[j];

                        /// vec[j] = vec[i] ;
                        usuVec [j] = usuVec [i];

                        /// vec[i] = aux ;
                        usuVec [i] = usuAux;
                    }
                }
            }
            fseek(p, 0, SEEK_SET);
            fwrite(usuVec, sizeof( User ), tam, p);
            delete []usuVec;
            fclose(p);
        }
        break;
    case 'C':
        {
            p=fopen("Archivos/Clientes.dat","rb+");
            if( p == NULL )
            {
                clear();
                recuadro_top(5, 80, 19, 4, cROJO, cAQUA);
                colorError();
                gotoxy(40,6);
                perror("Error ");
                fclose( p );
                recuadro_bott(9, 19, 80, 0, cROJO, cAQUA);
                gotoxy(20,8);
                colorNormal();
                pause();
                exit(1);
            }
            fseek(p, 0, SEEK_END);
            tam=ftell(p)/sizeof( Cliente );
            Cliente cliAux, *cliVec;
            cliVec = new Cliente [tam];
            if( cliVec == NULL )
            {
                fclose(p);
                exit(1);
            }
            fseek(p, 0, SEEK_SET);
            fread(cliVec, sizeof( Cliente ), tam, p);
            for(i=0;i<(tam-1);i++)
            {
                for(j=i+1;j<tam;j++)
                {
                    if( ( cliVec[j].getCodigo() < cliVec[i].getCodigo() ) && ( ( cliVec[j].getEstado() == true ) && ( cliVec[i].getEstado() == true ) ) )
                    {
                        /// aux = vec[j]. ;
                        cliAux = cliVec [j];

                        /// vec[j]. = vec[i]. ;
                        cliVec [j] = cliVec [i];

                        /// vec[i]. = aux ;
                        cliVec [i] = cliAux;

                    }
                }
            }
            fseek(p, 0, SEEK_SET);
            fwrite(cliVec, sizeof( Cliente ), tam, p);
            delete []cliVec;
            fclose(p);
        }
        break;
    case 'P':
        {
            p=fopen("Archivos/Productos.dat","rb+");
            if( p == NULL )
            {
                clear();
                recuadro_top(5, 80, 19, 4, cROJO, cAQUA);
                colorError();
                gotoxy(40,6);
                perror("Error ");
                fclose( p );
                recuadro_bott(9, 19, 80, 0, cROJO, cAQUA);
                gotoxy(20,8);
                colorNormal();
                pause();
                exit(1);
            }
            fseek(p, 0, SEEK_END);
            tam=ftell(p)/sizeof( Producto );
            Producto prodAux, *prodVec;
            prodVec = new Producto [tam];
            if( prodVec == NULL )
            {
                fclose(p);
                exit(1);
            }
            fseek(p, 0, SEEK_SET);
            fread(prodVec, sizeof( Producto ), tam, p);
            for(i=0;i<(tam-1);i++)
            {
                for(j=i+1;j<tam;j++)
                {
                    if( ( prodVec[j].get_codigo() < prodVec[i].get_codigo() ) && ( ( prodVec[j].get_estado() == true ) && ( prodVec[i].get_estado() == true ) ) )
                    {
                        /// aux = vec[j]. ;
                        prodAux = prodVec [j];

                        /// vec[j]. = vec[i]. ;
                        prodVec [j] = prodVec [i];

                        /// vec[i]. = aux ;
                        prodVec [i] = prodAux;

                    }
                }
            }
            fseek(p, 0, SEEK_SET);
            fwrite(prodVec, sizeof( Producto ), tam, p);
            delete []prodVec;
            fclose(p);
        }
        break;
    }
}

void recuadro_top(short alto = 10, short ancho = 80, short iniX = 19, short iniY = 4, short colorLinea = cROJO, short colorFondo = cAQUA)
{
    int i, j;
    for(i = iniX ; i <= iniX + ancho ; i++)
    {
        for(j = iniY ; j <= iniY + alto ; j++)
        {
            gotoxy(i, j);
            textcolor(colorLinea, colorFondo);
            //Arriba izquierda
            if( i == iniX && j == iniY )
            {
                cout << (char) 201;
            }
                //Arriba derecha
                else if( i == iniX + ancho && j == iniY )
                {
                    cout << (char) 187;
                }

                    //Lineas arriba
                    else if( j == iniY )
                    {
                        cout << (char) 205;
                    }
                        //Lineas izquierda y derecha
                        else if( i == iniX || i == iniX + ancho )
                        {
                            cout << (char) 186;
                        }
                            //Dentro del recuadro
                            else
                            {
                                cout << " ";
                            }
        }
    }
}

void recuadro_midd(short iniY, short iniX = 19, short ancho = 80, short alto = 3, short colorLinea = cROJO, short colorFondo = cAQUA)
{
    int i, j;
    for( i = iniX ; i <= iniX + ancho ; i++)
    {
        for(j = iniY ; j <= iniY + alto ; j++)
        {
            gotoxy(i, j);
            textcolor(colorLinea, colorFondo);
            //Lineas izquierda y derecha
            if( i == iniX || i == iniX + ancho )
            {
                cout << (char) 186;
            }
        }
    }
}

void recuadro_bott(short iniY, short iniX = 19, short ancho = 80, short alto = 0, short colorLinea = cROJO, short colorFondo = cAQUA)
{
    int i, j;
    for(i = iniX ; i <= iniX + ancho ; i++)
    {
        for(j = iniY ; j <= iniY + alto ; j++)
        {
            gotoxy(i, j);
            textcolor( colorLinea, colorFondo );
            //Abajo izquierda
            if( i == iniX && j == iniY )
            {
                cout << (char) 200;
            }
                //Abajo derecha
                else if( i == iniX + ancho && j == iniY )
                {
                    cout << (char) 188;
                }
                    //Linea abajo
                    else if( j == iniY )
                    {
                        cout << (char) 205;
                    }
                        /*//Lineas izquierda y derecha
                        else if( i == iniX || i == iniX + ancho )
                        {
                            gotoxy(i, j );
                            cout << (char) 186;
                        }*/
        }
    }
}


#endif // FUNCIONES_UTILES_H_INCLUDED
