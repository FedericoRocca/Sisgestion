#ifndef MENUES_H_INCLUDED
#define MENUES_H_INCLUDED

void Menu_Administrativo();
void Menu_Clientes();
void Menu_Admin(User);
void Menu_ventas(User);
void Menu_Listados();

void Menu_Listados()
{
    bool Menu = true;
    int x, y;
    while( Menu == true )
    {
        x = 20; y = 5;
        clear();
        recuadro_top();
        colorNormal();
        gotoxy(x, y);
        cout << "MEN" << char(233) << " LISTADOS   ";
        gotoxy(x + 60, y++);
        cout << currentDateTime();
        gotoxy(x, y++);
        barra();
        gotoxy(x, y++);
        cout << "1 - Consultar usuario";
        gotoxy(x, y++);
        cout << "2 - Listar todos los usuarios";
        gotoxy(x, y++);
        cout << "3 - Consultar cliente";
        gotoxy(x, y++);
        cout << "4 - Listar todos los clientes";
        gotoxy(x, y++);
        cout << "5 - Listar art" << char(161) << "culo";
        gotoxy(x, y++);
        cout << "6 - Listar todos los art" << char(161) << "culos";
        gotoxy(x, y++);
        cout << "7 - Listar art" << char(161) << "culo m" << char(160) << "s vendido";
        gotoxy(x, y++);
        cout << "8 - Listar art" << char(161) << "culo menos vendido";
        gotoxy(x, y++);
        cout << "9 - Listar venta de mayor valor";
        gotoxy(x, y++);
        cout << "0 - Listar venta de menor valor";
        gotoxy(x, y++);
        cout << "a - Listar venta";
        gotoxy(x, y++);
        cout << "b - Listar ventas";
        gotoxy(x, y++);
        barra();
        gotoxy(x, y++);
        cout << "Presione la opci" << char(162) << "n deseada. ESC para volver";
        recuadro_bott(y + 1);
        recuadro_midd(14, 19, 80, 7, cROJO, cAQUA);
        colorNormal();
        gotoxy(x, y);

        switch( getch() )
        {
        case '1':
            ListarUsuario();
            break;

        case '2':
            ListarUsuarios();
            break;

        case '3':
            ListarCliente();
            break;

        case '4':
            ListarClientes();
            break;

        case '5':
            ListarArticulo();
            break;

        case '6':
            ListarArticulos();
            break;

        case '7':
            ListarArticulosMasVendidos();
            break;

        case '8':
            ListarArticulosMenosVendidos();
            break;

        case '9':
            VentaMayorValor();
            break;

        case '0':
            VentaMenorValor();
            break;

        case 97:
            ListarVenta();
            break;

        case 98:
            ListarVentas();
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

void Menu_Ventas(User usuario)
{
    bool Menu = true;
    Cliente Cli;
    int x, y;
    while( Menu == true )
    {
        x = 20; y = 5;
        clear();
        recuadro_top();
        colorNormal();
        gotoxy(x, y);
        cout<<"MEN" << char(233) << " VENTAS";
        gotoxy(x + 60, y++);
        cout << currentDateTime();
        gotoxy(x, y++);
        barra();
        gotoxy(x, y++);
        cout << "1 - Nueva venta";
        gotoxy(x, y++);
        cout << "2 - Cambiar contrase" << char(164) << "a de usuario";
        gotoxy(x, y++);
        cout << "3 - Alta de cliente";
        gotoxy(x, y++);
        cout << "4 - Consultar cliente";
        gotoxy(x, y++);
        cout << "5 - Imprimir " << char(163) << "ltima factura";
        gotoxy(x, y++);
        cout << "6 - Imprimir una factura";
        gotoxy(x, y++);
        barra();
        gotoxy(x, y++);
        cout << "Presione la opci" << char(162) << "n deseada. ESC para volver";
        recuadro_bott(y + 1);
        gotoxy(x, y);

        switch( getch() )
        {
        case '1':
            Nueva_Venta(usuario.getLegajo());
            break;

        case '2':
            cambiar_Pass_U(usuario);
            break;

        case '3':
            Alta_Cliente();
            break;

        case '4':
            ListarCliente();
            break;

        case '5':
            imprimir_Ultima_Factura();
            break;

        case '6':
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

void Menu_Admin(User Usuario)
{
    bool Menu = true;
    Cliente _Cliente;
    int x, y;
    while( Menu == true )
    {
        x = 20; y = 5;
        clear();
        recuadro_top();
        colorNormal();
        gotoxy(x, y);
        cout << "MEN" << char(233) << " ADMINISTRACI" << char(224) << "N ";
        gotoxy(x + 60, y++);
        cout << currentDateTime();
        gotoxy(x, y++);
        barra();
        gotoxy(x, y++);
        cout << "1 - Alta usuario" ;
        gotoxy(x, y++);
        cout << "2 - Baja usuario" ;
        gotoxy(x, y++);
        cout << "3 - Alta cliente" ;
        gotoxy(x, y++);
        cout << "4 - Baja cliente por tiempo" ;
        gotoxy(x, y++);
        cout << "5 - Resetear contra" << char(164) << "a de usuario" ;
        if( Usuario.getLegajo() != 1000 )
        {
            gotoxy(x, y++);
            cout << "6 - Cambiar mi contrase" << char(164) << "a" ;
            gotoxy(x, y++);
            cout << "7 - Mostrar descuentos" ;
            gotoxy(x, y++);
            cout << "8 - Setear descuentos" ;
            gotoxy(x, y++);
            cout << "9 - Menu listados" ;
            gotoxy(x, y++);
            barra();
            gotoxy(x, y++);
            cout << "Presione la opci" << char(162) << "n deseada. ESC para volver";
            recuadro_bott(y + 1);
            gotoxy(x, y);
        }
        else
        {
            gotoxy(x, y++);
            cout << "7 - Mostrar descuentos" ;
            gotoxy(x, y++);
            cout << "8 - Setear descuentos" ;
            gotoxy(x, y++);
            cout << "9 - Menu listados" ;
            gotoxy(x, y++);
            barra();
            gotoxy(x, y++);
            cout << "Presione la opci" << char(162) << "n deseada. ESC para volver";
            recuadro_bott(y + 1);
            gotoxy(x, y);
        }
        recuadro_midd(y - 3);

        switch( getch() )
        {
        case '1':
            Alta_Usuario();
            break;
        case '2':
            Baja_Usuario();
            break;
        case '3':
            Alta_Cliente();
            break;
        case '4':
            Baja_Cliente_Tiempo();
            break;
        case '5':
            Resetear_Pass();
            break;
        case '6':
            if( Usuario.getLegajo() != 1000 )
            {
                cambiar_Pass_U( Usuario );
            }
            break;
        case '7':
            MostrarDescuentos();
            break;
        case '8':
            SeteaDescuentos();
            break;
        case '9':
            Menu_Listados();
            break;
        case 27:
            Menu = false;
            break;
        default:
            Error_Menu();
            break;
        }
    }
    return;
}

void Menu_Proveedores( User usuario )
{
    bool Menu = true;
    int x, y;
    while( Menu == true )
    {
        x = 20; y = 5;
        clear();
        recuadro_top();
        colorNormal();
        gotoxy(x, y);
        cout << "MEN" << char(233) << " PROVEEDORES";
        gotoxy(x + 60, y++);
        cout << currentDateTime();
        gotoxy(x, y++);
        barra();
        gotoxy(x, y++);
        cout << "1 - Nuevo art" << char(161) << "culo";
        gotoxy(x, y++);
        cout << "2 - Modificar stock";
        gotoxy(x, y++);
        cout << "3 - Eliminar art" << char(161) << "culo";
        gotoxy(x, y++);
        cout << "4 - Consultar articulo";
        gotoxy(x, y++);
        cout << "5 - Listar todos los articulos";
        gotoxy(x, y++);
        cout << "6 - Cambiar contrase" << char(164) << "a";
        gotoxy(x, y++);
        barra();
        gotoxy(x, y++);
        cout << "Presione la opci" << char(162) << "n deseada. ESC para volver";
        recuadro_bott(y + 1);
        recuadro_midd(y - 3);
        gotoxy(x, y);


        switch( getch() )
        {
        case '1':
            Alta_Producto();
            break;

        case '2':
            modificar_Stock();
            break;

        case '3':
            eliminar_Producto();
            break;

        case '4':
            ListarArticulo();
            break;

        case '5':
            ListarArticulos();
            break;

        case '6':
            cambiar_Pass_U( usuario );
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

void Menu_Administrativo()
{
    User usuario;
    if ( usuario.Login_U() == true )
    {
        switch( Retorna_Tipo_U( usuario.getLegajo() ) )
        {
        case ADMIN:
            Menu_Admin(usuario);
            break;

        case VENTAS:
            Menu_Ventas(usuario);
            break;

        case PROVEEDORES:
            Menu_Proveedores(usuario);
            break;

        default:
            clear();
            cout<<"Algun error hay con el tipo, ya que esta devolviendo un tipo ???? ";
            pause();
            break;

        }
    }
}

void Menu_Clientes()
{
    Cliente cliente;
    if( cliente.Login_C() == true )
    {
        bool Menu = true;
        int x, y;
        while( Menu == true )
        {
            x = 20; y = 5;
            clear();
            recuadro_top();
            colorNormal();
            gotoxy(x, y);
            cout << "MEN" << char(233) << " CLIENTES  ";
            gotoxy(x + 60, y++);
            cout << currentDateTime();
            gotoxy(x, y++);
            barra();
            gotoxy(x, y++);
            cout << "1 - Listar productos" ;
            gotoxy(x, y++);
            cout << "2 - Cambiar contrase" << char(164) << "a" ;
            gotoxy(x, y++);
            cout << "3 - Buscar producto por nombre" ;
            gotoxy(x, y++);
            barra();
            gotoxy(x, y++);
            cout << "Presione la opci" << char(162) << "n deseada. ESC para volver";
            recuadro_bott(14);
            gotoxy(x, y);

            switch( getch() )
            {
            case '1':
                ListarArticulos();
                break;

            case '2':
                cambiar_Pass_C( cliente );
                break;

            case '3':
                ListarProductoNombre();
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
}


#endif // MENUES_H_INCLUDED
