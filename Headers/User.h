#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

User& User::operator = ( User& usuario)
{
    this->setLegajo( usuario.getLegajo() );
    strcpy( this->Nombre, usuario.Nombre );
    strcpy( this->Apellido, usuario.Nombre );
    strcpy( this->Contrasenia, usuario.Contrasenia );
    this->Estado = usuario.Estado;
    this->Tipo = usuario.Tipo;
    return *this;
}

void User::EscribirContrasenia(  )
{
    cin.clear();
    COORD pos;
	int i = 0, a;
	while ( i < 13 )
	{
	    pos = getPosicionXY();
		a = getch();
		if ( a == 13 )
		{
			Contrasenia [i] = '\0';
			return;
		}
		if ( a == 8 )
		{
		    if( i > 0 )
		    {
                Contrasenia [i--] = '\0';
                pos.X--;
                gotoxy( pos.X, pos.Y );
                cout << " ";
                gotoxy( pos.X, pos.Y );
		    }
		}
		else
		{
		    gotoxy( pos.X, pos.Y );
			cout << "*";
			Contrasenia [i] = char( a );
			i++;
			pos.X++;
		}

	}
}

bool User::Login_U()
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
		cout << "Ingrese c" << char(162) << "digo de usuario: ";
        cin >> Legajo;
        if( Buscar_Usuario( Legajo ) < 0 )
        {
            colorError();
            gotoxy(40, y + 2);
            cout << "Legajo ingresado inexistente." ;
            gotoxy(40, y + 3);
            pause();
            colorNormal();
            return false;
        }

        gotoxy(x, y++);
		cout << "Ingrese contrase" << char( 164 ) << "a: ";
		EscribirContrasenia();
		if ( Validar_Usuario( *this ) != 0 )
		{
			colorError();
			y += 2;
            gotoxy(x, y++);
            cout << "El usuario o contrase" << char( 164 ) << "a ingresados son inv" << char( 160 ) << "lidos" ;
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

void User::Mostrar_Usuario(int y)     /**   TAMAÑO 7   **/
{
    int x = 20;
    gotoxy(x, y);
    cout << Legajo ;

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
    ///cout << Tipo << " - ";
    switch( Tipo )
    {
    case ADMIN:
        cout << "Admin";
        break;

    case VENTAS:
        cout << "Ventas";
        break;

    case PROVEEDORES:
        cout << "Proveedores";
        break;
    }
}

void User::Guardar_Usuario()
{
    FILE* Puntero = fopen( "Archivos/Usuarios.dat" , "ab" );

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

void User::Guardar_Usuario( int pos )
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

    fseek( Puntero, pos * sizeof *this, SEEK_SET );
    fwrite( this, sizeof *this, 1, Puntero );

    fclose( Puntero );

}

void User::resetPass()
{
    strcpy( Contrasenia, "default" );
}

void User::Leer_Usuario( int pos )
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

    fseek( Puntero, pos * sizeof *this, SEEK_SET );
    fread( this, sizeof *this, 1, Puntero );

    fclose( Puntero );
}

#endif // USER_H_INCLUDED
