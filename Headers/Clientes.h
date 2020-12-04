#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

Cliente& Cliente::operator = ( Cliente& cliente)
{
    strcpy( this->Nombre, cliente.Nombre );
    strcpy( this->Apellido, cliente.Nombre );
    strcpy( this->Contrasenia, cliente.Contrasenia );
    this->Estado = cliente.Estado;
    this->Tipo = cliente.Tipo;
    this->setCodigo( cliente.getCodigo() );
    return *this;
}

bool Cliente::Login_C()
{
	int x, y;
    while( true )
    {
        x = 20; y = 5;
        clear();
        recuadro_top();
        recuadro_bott(15);
        colorNormal();
        gotoxy(x, y++);
        cout << "LOGIN";
		gotoxy(x, y++);
		barra();
		gotoxy(x, y++);
		cout << "Ingrese c" << char(162) << "digo de cliente: ";
        cin >> Codigo;
        if( Buscar_Cliente( Codigo ) < 0 )
        {
            colorError();
            gotoxy(40, y + 2);
            cout << "Cliente ingresado inexistente.";
            gotoxy(40, y + 3);
            pause();
            colorNormal();
            return false;
        }

        gotoxy(x, y++);
		cout << "Ingrese contrase" << char( 164 ) << "a: ";
		EscribirContrasenia();
		if ( Validar_Cliente( *this ) != 0 )
		{
		    colorError();
			y += 2;
            gotoxy(x, y++);
            cout << "El cliente o contrase" << char( 164 ) << "a ingresados son inv" << char( 160 ) << "lidos" ;
            gotoxy(x, y++);
            colorNormal();
			cout << "Si desea salir, presione la tecla ESC. De lo contrario, cualquier otra.";
			gotoxy(x, y++);
			if ( getch() == 27 )
			{
				return false;
			}
		}
		else
			return true;
	}
}

void Cliente::Mostrar_Cliente(int y)     /**   TAMAÑO 7   **/
{
    int x = 20;
    gotoxy(x, y);
    cout << Codigo ;

    gotoxy(x += 8, y);
    cout << Nombre ;

    gotoxy(x += 15, y);
    cout << Apellido ;

    gotoxy(x += 15, y);
    cout << Contrasenia ;

    Fecha_Ingreso.mostrar_Fecha(x += 15, y);

    gotoxy(x += 12, y);
    if( Estado == true )
        cout << "Activo" ;
    else cout << "Inactivo" ;

    gotoxy(x += 10, y);
    cout << Tipo << " - ";
    switch( Tipo )
    {
    case COMUN:
        cout << "(Com" << char(163) << "n)";
        break;

    case PREMIUM:
        cout << "(Premium)";
        break;

    }
}

void Cliente::Guardar_Cliente()
{
    FILE* Puntero = fopen( "Archivos/Clientes.dat" , "ab" );

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

void Cliente::Guardar_Cliente( int pos )
{
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

    fseek( Puntero, pos * sizeof *this, SEEK_SET );
    fwrite( this, sizeof *this, 1, Puntero );

    fclose( Puntero );

}

void Cliente::Leer_Cliente( int pos )
{
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

    fseek( Puntero, pos * sizeof *this, SEEK_SET );
    fread( this, sizeof *this, 1, Puntero );

    fclose( Puntero );
}

#endif // CLIENTES_H_INCLUDED
