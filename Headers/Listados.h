#ifndef LISTADOS_H_INCLUDED
#define LISTADOS_H_INCLUDED

/**
Articulos con stock bajo

**/

void ListarUsuario();
void ListarUsuarios();
void ListarCliente();
void ListarClientes();
void ListarArticulo();
void ListarArticulos();
void ListarVenta();
int contar_veces_vendido(int);
void ListarArticulosMasVendidos();
void ListarArticulosMenosVendidos();
void VentaMayorValor();
bool HayVentas();
void MostrarVenta(int);
void VentaMenorValor();
void ListarVentas();
void ListarProductoNombre();

void ListarProductoNombre()
{
    clear();
    int C = 0, x = 20, y = 5;
    char prod[50];
    recuadro_top();
    recuadro_bott(14, 19, 80, 0, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout << "BUSCAR ART" << char(214) << "CULOS POR NOMBRE";
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

    gotoxy(x, y++);
    cout << "Ingres" << char(160) << " el nombre del producto a buscar. No es necesario que ingreses";
    gotoxy(x, y++);
    cout << "el nombre completo. Por ejemplo, si ingres" << char(160) << "s la palabra 'leche', va a";
    gotoxy(x, y++);
    cout << "buscar 'Leche condensada', 'Leche en polvo', 'Dulce de leche', etc...";
    gotoxy(x, y++);
    barra();

    cin.clear();
    cin.ignore();

    gotoxy(x, ++y );
    cin.getline( prod, 50 );
    y += 2;
    FILE *Puntero = fopen( "Archivos/Productos.dat", "rb" );

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

    gotoxy(x, y++);
    barra();

    recuadro_midd(y - 1, 19, 80, 10, cROJO, cAQUA);
    colorNormal();

    Producto Obj;

    gotoxy(x, ++y);
    cout << "COINCIDENCIAS: ";
    gotoxy(x, y += 2);
    barra();
    y++;
    titulos_producto(y++);
    gotoxy(x, y++);
    barra();

    while( fread( &Obj, sizeof Obj, 1, Puntero ) )
    {
        if( strstr( Obj.get_descripcion(), prod ) != NULL )
        {
            if(Obj.get_estado())
            {
                Obj.mostrar_Producto(y);
                C++;
                y++;
                gotoxy(x, ++y);
                barra();
                if( C >= 1 )
                    recuadro_midd(++y, 19, 80, 3, cROJO, cAQUA);
                colorNormal();
            }
        }
        else
        {
            if( islower( prod[0] ) )
            {
                prod[0] = toupper(prod[0]);
                if( strstr( Obj.get_descripcion(), prod ) != NULL )
                {
                    if(Obj.get_estado())
                    {
                        Obj.mostrar_Producto(y);
                        C++;
                        y++;
                        gotoxy(x, ++y);
                        barra();
                        if( C >= 1 )
                            recuadro_midd(++y, 19, 80, 3, cROJO, cAQUA);
                        colorNormal();
                    }
                }
            }
        }
    }
    fclose( Puntero );

    if( C == 0 )
    {
        y = 22;
        gotoxy(x, y++);
        cout<<"Ning" << char(163) << "n resultado para la b" << char(163) << "squeda ingresada.";
        gotoxy(x, y++);
        cout<<"Prob" << char(160) << " hacer una b" << char(163) << "squeda m" << char(160) << "s general.";
        recuadro_bott( y + 2 );
    }
    else
        recuadro_bott( y + 3 );

    colorNormal();
    gotoxy(x, ++y);
    pause();
    return;
}

void ListarVentas()
{
    clear();
    int x = 20, y = 5, c = 0;
    recuadro_top();
    colorNormal();
    gotoxy(x, y);
    cout << "LISTAR VENTAS";
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();
    if( HayVentas() == false )
    {
        colorError();
        gotoxy(x, y++);
        cout << "Sin ventas cargadas." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }

    FILE* Puntero = fopen("Archivos/Ventas.dat" , "rb+");

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

    Venta Obj;

    titulos_venta(y++);
    gotoxy(x, y++);
    barra();

    while( fread( &Obj, sizeof Obj, 1, Puntero ) )
    {
        Obj.Mostrar_Venta(y);
        c++;
        y++;
        gotoxy(x, ++y);
        barra();
        if( c >= 1 )
            recuadro_midd(++y, 19, 80, 3, cROJO, cAQUA);
        colorNormal();
    }
    fclose(Puntero);
    recuadro_bott(y + 3, 19, 80, 0, cROJO, cAQUA);
    gotoxy(x, y++);
    colorNormal();
    pause();
    return;

}

void VentaMenorValor()
{
    clear();
    int x = 20, y = 5;
    recuadro_top();
    recuadro_bott(15);
    colorNormal();
    gotoxy(x, y);
    cout << "VENTA DE MENOR VALOR";
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();
    if( HayVentas() == false )
    {
        colorError();
        gotoxy(x, y++);
        cout << "Sin ventas cargadas." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }

    FILE* Puntero = fopen("Archivos/Ventas.dat" , "rb+");

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

    int IDVenta = 0;
    float Menor;
    Venta Obj;

    while( fread( &Obj, sizeof Obj, 1, Puntero ) )
    {
        if ( IDVenta == 0)
        {
            Menor = Obj.getValor();
            IDVenta = Obj.getCodigo_Venta();
        }
            else if( Obj.getValor() < Menor )
            {
                Menor = Obj.getValor();
                IDVenta = Obj.getCodigo_Venta();
            }
    }

    titulos_venta(y++);
    gotoxy(x, y++);
    barra();

    fclose( Puntero );
    Obj.Leer_Venta( Buscar_Venta( IDVenta ) );
    Obj.Mostrar_Venta(y++);

    gotoxy(x, y++);
    barra();
    gotoxy(x, y++);
    pause();
    return;
}

bool HayVentas()
{
    FILE* Puntero = fopen("Archivos/Ventas.dat" , "rb+");

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

    fseek( Puntero, 0, SEEK_END );

    Venta Obj;
    if( (ftell( Puntero ) / sizeof Obj) <= 0 )
    {
        fclose( Puntero );
        return false;
    }
    fclose( Puntero );
    return true;
}

void VentaMayorValor()
{
    clear();
    int x = 20, y = 5;
    recuadro_top();
    recuadro_bott(15);
    colorNormal();
    gotoxy(x, y);
    cout << "VENTA DE MAYOR VALOR";
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();
    if( HayVentas() == false )
    {
        colorError();
        gotoxy(x, y++);
        cout << "Sin ventas cargadas." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }

    FILE* Puntero = fopen("Archivos/Ventas.dat" , "rb");

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

    float MayorValor;
    int IDVenta = 0;
    Venta Obj;

    while( fread(&Obj, sizeof Obj, 1, Puntero) )
    {
        if( IDVenta == 0 )
        {
            MayorValor = Obj.getValor();
            IDVenta = Obj.getCodigo_Venta();
        }
            else if( MayorValor < Obj.getValor() )
            {
                MayorValor = Obj.getValor();
                IDVenta = Obj.getCodigo_Venta();
            }
    }

    titulos_venta(y++);
    gotoxy(x, y++);
    barra();

    fclose( Puntero );
    Obj.Leer_Venta( Buscar_Venta( IDVenta ) );
    Obj.Mostrar_Venta(y++);

    gotoxy(x, y++);
    barra();
    gotoxy(x, y++);
    pause();
    return;
}

int contar_veces_vendido( int cod )
{
    FILE* Puntero = fopen( "Archivos/Preventas.dat" , "rb" );
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
    Preventa preventa;
    int c = 0;
    while( fread( &preventa, sizeof preventa, 1, Puntero ) )
    {
        if( cod == preventa.getCodigoArticulo() )
        {
            c += preventa.getCantidad();
        }
    }
    fclose( Puntero );
    return c;
}

void ListarArticulosMasVendidos()
{
    clear();
    int x = 20, y = 5;
    recuadro_top();
    colorNormal();
    gotoxy(x, y);
    cout << "LISTAR EL ART" << char(214) << "CULO M" << char(181) << "S VENDIDO ACTIVO" ;
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

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

    Producto Articulo, *vec_prod, aux_prod;
    int c, i = 0, *vec_int, aux_int, j = 0;
    fseek( Puntero, 0, SEEK_END );
    c = ftell( Puntero ) / sizeof( Producto );
    fseek( Puntero, 0, SEEK_SET );
    if( c == 0 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "No hay art" << char(161) << "culos cargados." ;
        colorNormal();
        fclose( Puntero );
        gotoxy(x, y++);
        pause();
        return;
    }
    vec_int = new int[c];
    vec_prod = new Producto[c];
    if( vec_prod == NULL )
    {
        colorError();
        gotoxy(x, y++);
        cout << "Error de memoria." ;
        colorNormal();
        fclose( Puntero );
        gotoxy(x, y++);
        pause();
        return;
    }
    if( vec_prod == NULL )
    {
        colorError();
        gotoxy(x, y++);
        cout << "Error de memoria." ;
        colorNormal();
        fclose( Puntero );
        gotoxy(x, y++);
        pause();
        return;
    }

    while( fread( &Articulo, sizeof Articulo, 1, Puntero ) )
    {
        if( Articulo.get_estado() == true )
        {
            vec_int[i] = contar_veces_vendido( Articulo.get_codigo() );
            vec_prod[i].Leer_Producto( j );
            i++;
        }
        j++;
    }
    c = i;
    for( i = 1 ; i < c ; i++ )
    {
        for( j = 0 ; j < c -1 ; j++ )
        {
            if ( vec_int[j] < vec_int[i] )
            {
                aux_int = vec_int[j];
                aux_prod = vec_prod[j];

                vec_int[j] = vec_int[i];
                vec_prod[j] = vec_prod[i];

                vec_int[i] = aux_int;
                vec_prod[i] = aux_prod;
            }
        }
    }

    titulos_producto(y++);
    gotoxy(x, y++);
    barra();

    for( i = 0 ; i < c ; i++ )
    {
        if(vec_int[0] == vec_int[i])
        {
            vec_prod[i].mostrar_Producto(y++);
            y++;
            gotoxy(x, y++);
            cout << "Vendido: " << vec_int[i] << " veces." ;
            gotoxy(x, y++);
            barra();
            recuadro_midd(++y, 19, 80, 3, cROJO, cAQUA);
            colorNormal();
        }
    }
    fclose( Puntero );
    delete[] vec_int;
    delete[] vec_prod;
    recuadro_bott(y + 3, 19, 80, 0, cROJO, cAQUA);
    gotoxy(x, y++);
    barra();
    gotoxy(x, y++);
    colorNormal();
    pause();
    return;
}

void ListarArticulosMenosVendidos()
{
    clear();
    int x = 20, y = 5;
    recuadro_top();
    colorNormal();
    gotoxy(x, y);
    cout << "LISTAR EL ART" << char(214) << "CULO MENOS VENDIDO ACTIVO" ;
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

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

    Producto Articulo, *vec_prod, aux_prod;
    int c, i = 0, *vec_int, aux_int, j = 0;
    fseek( Puntero, 0, SEEK_END );
    c = ftell( Puntero ) / sizeof( Producto );
    fseek( Puntero, 0, SEEK_SET );
    if( c == 0 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "No hay art" << char(161) << "culos cargados." ;
        colorNormal();
        fclose( Puntero );
        gotoxy(x, y++);
        pause();
        return;
    }
    vec_int = new int[c];
    vec_prod = new Producto[c];
    if( vec_prod == NULL )
    {
        colorError();
        gotoxy(x, y++);
        cout << "Error de memoria." ;
        colorNormal();
        fclose( Puntero );
        gotoxy(x, y++);
        pause();
        return;
    }
    if( vec_prod == NULL )
    {
        colorError();
        gotoxy(x, y++);
        cout << "Error de memoria." ;
        colorNormal();
        fclose( Puntero );
        gotoxy(x, y++);
        pause();
        return;
    }

    while( fread( &Articulo, sizeof Articulo, 1, Puntero ) )
    {
        if( Articulo.get_estado() == true )
        {
            vec_int[i] = contar_veces_vendido( Articulo.get_codigo() );
            vec_prod[i].Leer_Producto( j );
            i++;
        }
        j++;
    }
    c = i;
    for( i = 1 ; i < c ; i++ )
    {
        for( j = 0 ; j < c -1 ; j++ )
        {
            if ( vec_int[j] > vec_int[i] )
            {
                aux_int = vec_int[j];
                aux_prod = vec_prod[j];

                vec_int[j] = vec_int[i];
                vec_prod[j] = vec_prod[i];

                vec_int[i] = aux_int;
                vec_prod[i] = aux_prod;
            }
        }
    }
    titulos_producto(y++);
    gotoxy(x, y++);
    barra();
    for( i = 0 ; i < c ; i++ )
    {
        if(vec_int[0] == vec_int[i])
        {
            vec_prod[i].mostrar_Producto(y++);
            y++;
            gotoxy(x, y++);
            cout << "Vendido: " << vec_int[i] << " veces." ;
            gotoxy(x, y++);
            barra();
            recuadro_midd(++y, 19, 80, 3, cROJO, cAQUA);
            colorNormal();

        }
    }
    fclose( Puntero );
    delete[] vec_int;
    delete[] vec_prod;
    recuadro_bott(y + 3, 19, 80, 0, cROJO, cAQUA);
    gotoxy(x, y++);
    barra();
    gotoxy(x, y++);
    colorNormal();
    pause();
    return;
}

void ListarVenta()
{
    clear();
    int x = 20, y = 5;
    recuadro_top();
    recuadro_bott(15);
    colorNormal();
    gotoxy(x, y);
    cout << "LISTAR VENTA";
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

    gotoxy(x, y++);
    cout << "Ingresa el c" << char(162) << "digo de venta a listar: ";
    int Cod, aux;
    cin >> Cod;
    gotoxy(x, y++);
    barra();
    aux = Buscar_Venta( Cod );
    if( aux == -1 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "No se encontraron ventas." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }
    if( aux == -2 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "No se encontr" << char(162) << " esa venta." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }

    titulos_venta(y++);
    gotoxy(x, y++);
    barra();

    Venta venta;
    venta.Leer_Venta( aux );
    venta.Mostrar_Venta(y++);

    gotoxy(x, y++);
    barra();
    gotoxy(x, y++);
    pause();
    return;
}

void ListarArticulos()
{
    clear();
    FILE *P = fopen("Archivos/Productos.dat","rb");
    if( P == NULL )
    {
        clear();
        recuadro_top(5, 80, 19, 4, cROJO, cAQUA);
        colorError();
        gotoxy(40,6);
        perror("Error ");
        fclose( P );
        recuadro_bott(9, 19, 80, 0, cROJO, cAQUA);
        gotoxy(20,8);
        colorNormal();
        pause();
        exit(1);
    }
    Producto prod;
    int c = 0, x = 20, y = 5;
    recuadro_top();
    colorNormal();
    gotoxy(x, y);
    cout << "LISTAR ART" << char(214) << "CULOS" ;
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

    titulos_producto(y++);
    gotoxy(x, y++);
    barra();

    while (fread( &prod, sizeof prod, 1, P ))
    {
        if(prod.get_estado())
        {
            prod.mostrar_Producto(y);
            c++;
            y++;
            gotoxy(x, ++y);
            barra();
            if( c >= 1 )
                recuadro_midd(++y, 19, 80, 3, cROJO, cAQUA);
            colorNormal();
        }
    }
    if( c == 0 )
    {
        colorError();
        gotoxy(x,y+=2);
        cout << "No hay art" << char(161) << "culos cargados." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }
    fclose( P );
    recuadro_bott(y + 3, 19, 80, 0, cROJO, cAQUA);
    gotoxy(x, y++);
    colorNormal();
    pause();
    return;
}

void ListarArticulo()
{
    clear();
    int x = 20, y = 5;
    recuadro_top();
    recuadro_bott(15);
    colorNormal();
    gotoxy(x, y);
    cout << "LISTAR ART" << char(214) << "CULO" ;
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

    gotoxy(x, y++);
    cout << "Ingrese el c" << char(162) << "digo de producto a listar: ";
    int Cod, aux;
    cin >> Cod;
    gotoxy(x, y++);
    barra();
    aux = Buscar_Producto( Cod );
    if( aux == -1 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "No se encontraron productos." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }
    if( aux == -2 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "No se encontr" << char(162) << " ese producto." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }

    titulos_producto(y++);
    gotoxy(x, y++);
    barra();

    Producto Articulo;
    Articulo.Leer_Producto(aux);
    Articulo.mostrar_Producto(y++);

    gotoxy(x, y++);
    barra();
    gotoxy(x, y++);
    pause();
    return;
}

void ListarClientes()
{
    clear();
    int c = 0, x = 20, y = 5;
    recuadro_top(10, 90, 19, 4, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout<<"LISTAR CLIENTES";
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

    Cliente Aux;

    FILE *Puntero = fopen( "Archivos/Clientes.dat" , "rb" );

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

    titulos_cliente(y++);
    gotoxy(x, y++);
    barra();

    while( fread( &Aux, sizeof Aux, 1, Puntero ) )
    {
        if( Aux.getEstado() == true )
        {
            c++;
            Aux.Mostrar_Cliente(y);
            y++;
            gotoxy(x, ++y);
            barra();
            if( c >= 1 )
                recuadro_midd(++y, 19, 90, 3, cROJO, cAQUA);
            colorNormal();
        }
    }

    if( c == 0 )
    {
        colorError();
        gotoxy(x,y+=2);
        cout<<"No existen clientes cargados";
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;

    }
    fclose(Puntero);
    recuadro_bott(y + 3, 19, 90, 0, cROJO, cAQUA);
    gotoxy(x, y++);
    colorNormal();
    pause();
    return;
}

void ListarCliente()
{
    clear();
    int x = 20, y = 5;
    recuadro_top(10, 90, 19, 4, cROJO, cAQUA);
    recuadro_bott(15, 19, 90, 3, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout << "LISTAR CLIENTE" ;
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();

    gotoxy(x, y++);
    cout << "Ingresa el c" << char(162) << "digo de cliente a listar: ";
    int Cod, aux;
    cin >> Cod;
    gotoxy(x, y++);
    barra();
    aux = Buscar_Cliente( Cod );
    if( aux == -1 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "No se encontraron clientes." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }
    if( aux == -2 )
    {
        colorError();
        gotoxy(x, y++);
        cout << "No se encontr" << char(162) << " ese cliente." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }
    Cliente cliente;
    cliente.Leer_Cliente( aux );
    titulos_cliente(y++);
    gotoxy(x, y++);
    barra();
    cliente.Mostrar_Cliente(y++);

    gotoxy(x, y++);
    barra();
    gotoxy(x, ++y);
    pause();
    return;
}

void ListarUsuarios()
{
    User Aux;
    FILE *Puntero = fopen( "Archivos/Usuarios.dat" , "rb" );

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
    clear();
    int c = 0, x = 20, y = 5;
    recuadro_top(10, 90, 19, 4, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout << "LISTAR USUARIOS";
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();
    gotoxy(x, y++);
    titulos_usuario(y++);
    gotoxy(x, y++);
    barra();
    while( fread( &Aux, sizeof Aux, 1, Puntero ) )
    {
        if( Aux.getLegajo() != 1000 )
        {
            c++;
            Aux.Mostrar_Usuario(++y);
            y++;
            gotoxy(x, ++y);
            barra();
            if( c >= 1 )
                recuadro_midd(++y, 19, 90, 3, cROJO, cAQUA);
            colorNormal();
        }
        else
        {
            c++;
            gotoxy(x, ++y);
            cout << Aux.getLegajo();
            gotoxy(x + 8, y);
            cout<<"Administrador";

            gotoxy(x, y += 2);
            barra();
            if( c >= 1 )
                recuadro_midd(y++, 19, 90, 4, cROJO, cAQUA);
            colorNormal();
        }
    }

    if( c == 0 )
    {
        colorError();
        gotoxy(x,y++);
        cout<<"No existen usuarios cargados";
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }

    fclose(Puntero);
    recuadro_bott(y + 3, 19, 90, 0, cROJO, cAQUA);
    gotoxy(x, y++);
    colorNormal();
    pause();
    return;
}

void ListarUsuario()
{
    clear();
    int x = 20, y = 5;
    recuadro_top(10, 90, 19, 4, cROJO, cAQUA);
    recuadro_midd(15, 19, 90, 3, cROJO, cAQUA);
    recuadro_bott(18, 19, 90, 0, cROJO, cAQUA);
    colorNormal();
    gotoxy(x, y);
    cout << "LISTAR USUARIO" ;
    gotoxy(x + 60, y++);
    cout << currentDateTime();
    gotoxy(x, y++);
    barra();
    gotoxy(x, y++);
    cout << "Ingresa el c" << char(162) << "digo de usuario a listar: ";
    int Cod, aux;
    cin >> Cod;

    if( Cod == 1000 )
    {
        colorError();
        gotoxy(x,y++);
        cout<<"El usuario 1000 es el usuario ADMIN, el cual tiene ";
        gotoxy(x, y++);
        cout<<"privilegios para administrar el sistema, realizar";
        gotoxy(x, y++);
        cout<<"cambios en usuarios, descuentos y mas.";
        gotoxy(x, y++);
        cout<<"Por tal motivo, no se listan los datos del usuario.";
        gotoxy(x, y++);
        cout<<"En el caso de haber perdido el usuario ADMIN";
        gotoxy(x, y++);
        cout<<"debe ponerse en contacto con el administrador";
        gotoxy(x, y++);
        cout<<"del sistema";
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;

    }

    gotoxy(x, y++);
    barra();
    aux = Buscar_Usuario( Cod );
    if( aux == -1 )
    {
        colorError();
        gotoxy(x,y+=2);
        cout << "No se encontraron usuarios." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;

    }
    if( aux == -2 )
    {
        colorError();
        gotoxy(x,y+=2);
        cout << "No se encontr" << char(162) << " ese usuario." ;
        colorNormal();
        gotoxy(x, y++);
        pause();
        return;
    }

    User usuario;
    usuario.Leer_Usuario( aux );
    titulos_usuario(y++);
    gotoxy(x, y++);
    barra();
    usuario.Mostrar_Usuario(y);

    gotoxy(x, y += 2);
    barra();
    gotoxy(x, ++y);
    colorNormal();
    pause();
    return;
}


#endif // LISTADOS_H_INCLUDED
