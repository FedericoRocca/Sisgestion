#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

Fecha& Fecha::operator = ( const Fecha& fecha )
{
    this->Dia = fecha.Dia;
    this->Mes = fecha.Mes;
    this->Anio = fecha.Anio;
    return *this;
}

bool Fecha::operator > ( const Fecha& fecha )
{
    if( this->Anio > fecha.Anio )
        return true;
    else if( this->Anio == fecha.Anio )
        {
            if( this->Mes > fecha.Mes )
                return true;
            else if( this->Mes == fecha.Mes )
                {
                    if( this->Dia > fecha.Dia )
                        return true;
                }
        }
    return false;
}

bool Fecha::operator < ( const Fecha& fecha )
{
    if( this->Anio < fecha.Anio )
        return true;
    else if( this->Anio == fecha.Anio )
        {
            if( this->Mes < fecha.Mes )
                return true;
            else if( this->Mes == fecha.Mes )
                {
                    if( this->Dia < fecha.Dia )
                        return true;
                }
        }
    return false;
}

bool Fecha::operator == ( const Fecha& fecha )
{
    if( this->Anio == fecha.Anio && this->Mes == fecha.Mes && this->Dia == fecha.Dia )
        return true;
    else return false;
}

bool Fecha::operator >= ( const Fecha& fecha )
{
    if( *this == fecha || *this > fecha )
        return true;
    else return false;
}

bool Fecha::operator <= ( const Fecha& fecha )
{
    if( *this == fecha || *this < fecha )
        return true;
    else return false;
}

void Fecha::mostrar_Fecha(int x, int y)
{
    gotoxy(x, y);
    cout << Dia << "/" << Mes << "/" << Anio;
}

void Fecha::set_fecha( Fecha Fec )
{
    this->Anio = Fec.get_anio();
    this->Mes = Fec.get_mes();
    this->Dia = Fec.get_dia();
}

#endif // FECHA_H_INCLUDED
