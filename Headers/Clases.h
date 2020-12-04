#ifndef CLASES_H_INCLUDED
#define CLASES_H_INCLUDED

class Fecha
{
protected:
    int Dia;
    int Mes;
    int Anio;
public:
    void mostrar_Fecha(int, int);

    int get_dia() { return Dia; }
    int get_mes() { return Mes; }
    int get_anio() { return Anio; }
    void set_dia( int dia ) { Dia = dia; }
    void set_mes( int mes ) { Mes = mes; }
    void set_anio( int anio ) { Anio = anio; }

    void set_fecha( Fecha );

    Fecha& operator = (const Fecha&);
    bool operator < (const Fecha &);
    bool operator > (const Fecha &);
    bool operator == (const Fecha &);
    bool operator <= (const Fecha &);
    bool operator >= (const Fecha &);

    Fecha()
    {
        struct tm *tiempo;
        time_t fecha_sistema;
        time(&fecha_sistema);
        tiempo=localtime(&fecha_sistema);

        Anio=tiempo->tm_year + 1900;
        Mes=tiempo->tm_mon + 1;
        Dia=tiempo->tm_mday;
    }

};

class User
{
private:
    int Legajo; //Autonumerico a partir de 1001

protected:
    char Nombre[26];
    char Apellido[26];
    Fecha Fecha_Ingreso;
    char Contrasenia[13];
    bool Estado;
    int Tipo;

public:
    int getLegajo() { return Legajo; }
    char* GetPass() { return Contrasenia; }
    char* GetNombre() { return Nombre; }
    char* GetApellido() { return Apellido; }
    int getTipo() { return Tipo; }
    bool getEstado() { return Estado; }

    void setLegajo( int leg ){ Legajo = leg; }
    void setNombre( char *nombre ) { strcpy( Nombre, nombre ); }
    void setApellido( char *apellido ) { strcpy( Apellido, apellido ); }
    void setContrasenia( const char *contrasenia ) { strcpy( Contrasenia, contrasenia ); }
    void setTipo( int tipo ) { Tipo = tipo; }
    void setEstado(bool _Estado){ Estado = _Estado; }

    void EscribirContrasenia(  );
    bool Login_U();
    void resetPass();

    void Mostrar_Usuario(int);
    void Guardar_Usuario();
    void Guardar_Usuario( int );
    void Leer_Usuario(int);

    User& operator = (User&);

    /*User()
    {
        Legajo = 1000;
        strcpy( Nombre, "ADMIN" );
        strcpy( Apellido, "ADMIN" );
        strcpy( Contrasenia, "admin" );
        Tipo = 1;
        Estado = true;

        FILE* Puntero = fopen( "Archivos/Usuarios.dat" , "wb" );
        fwrite( this, sizeof *this, 1, Puntero );
        fclose( Puntero );
    }*/
};

class Cliente:public User
{
private:
    int Codigo;

public:
    int getCodigo() { return Codigo; }

    void setCodigo( int cod ) { Codigo = cod; }

    bool Login_C();
    void Guardar_Cliente();
    void Guardar_Cliente( int );
    void Mostrar_Cliente(int);
    void Leer_Cliente(int);

    Cliente& operator = (Cliente&);
};

class Producto
{
private:
    int Codigo;
    float Precio_Unitario;
    int Stock;
    char Descripcion[50];
    int Categoria;
    bool Estado;

public:
    int get_codigo() { return Codigo; }
    float get_precio() { return Precio_Unitario; }
    int get_stock() { return Stock; }
    char* get_descripcion() { return Descripcion; }
    int get_categoria() { return Categoria; }
    bool get_estado() { return Estado; }

    void set_codigo( int cod ) { Codigo = cod; }
    void set_precio( float precio ) { Precio_Unitario = precio; }
    void set_stock( int stock ) { Stock = stock; }
    void set_descripcion( const char *descripcion ) { strcpy(Descripcion, descripcion); }
    void set_categoria (int categoria ) { Categoria = categoria; }
    void set_estado( bool estado ) { Estado = estado; }

    void mostrar_Producto(int);
    void Guardar_Producto();
    void Guardar_Producto( int );
    void Leer_Producto(int);
};

class Venta
{
    private:
        int Codigo_Venta;
        float Valor;
        int Codigo_Cliente;
        int Legajo_Empleado;
        Fecha Fecha_Venta;
        char Forma_Pago;

    public:
        void setCodigo_Venta();
        void setValor( float _valor ) { Valor = _valor; }
        void setCodigo_Cliente( int codCliente ) { Codigo_Cliente = codCliente; }
        void setLegajo_Empleado( int legEmpleado ) { Legajo_Empleado = legEmpleado; }
        void setForma_Pago( const char forma ) { Forma_Pago = forma; }
        void ImprimeFecha(int x, int y){Fecha_Venta.mostrar_Fecha(x, y);}

        int getCodigo_Venta() { return Codigo_Venta; }
        float getValor() { return Valor; }
        int getCodigo_Cliente() { return Codigo_Cliente; }
        int getLegajo_Empleado() { return Legajo_Empleado; }
        Fecha getFecha_Venta() { return Fecha_Venta; }

        char getForma_Pago() { return Forma_Pago; }

        void Guardar_Venta();

        void Leer_Venta(int);
        void Mostrar_Venta(int);
};

class Preventa
{
  private:
    int Codigo_Venta;
    int Codigo_Articulo;
    int Cantidad;
    float Precio_Unitario;

  public:
    bool Alta_CodigoArticulo(int, int);
    bool Alta_Cantidad(int, int);
    void Alta_PrecioUnitario();
    void Alta_Codigo_Venta(int _Codigo){ Codigo_Venta = _Codigo; }
    void Guardar_Preventa();
    float RetornaValor(int);
    int getCodigoVenta(){ return Codigo_Venta; }
    int getCantidad(){ return Cantidad; }
    float getPrecioUnitario(){ return Precio_Unitario; }
    int getCodigoArticulo() { return Codigo_Articulo; }

};

enum Tipo_De_Cliente
{
    COMUN = 0,
    PREMIUM
};

enum Tipo_De_Usuario
{
    ADMIN = 1,
    VENTAS,
    PROVEEDORES
};

enum Tipo_De_Producto
{
    PERFUMERIA = 1,
    VERDULERIA,
    BEBIDAS,
    MASCOTAS,
    LIMPIEZA,
    VESTIMENTA,
    FRIGORIFICOS,
    ELECTRO,
    PANADERIA,
    ALMACEN,
    OTROS
};


#endif // CLASES_H_INCLUDED
