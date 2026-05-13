//////////////////////////////////////////////////
//
// spielt Prüfsummen durch
//
// (c) 2026 Bert Lange
//////////////////////////////////////////////////
#include <cstdint>      // uint8_t, uint16_t
#include <print>
#include <filesystem>   // short filename
#include <vector>
#include <string>
#include <unistd.h>     // getopt


//////////////////////////////////////////////////
// Hilfetext ausgeben
void help(  const std::string& self_name)
{
    std::println( "...");
    std::println();
    std::println( "Programmaufruf:");
    std::println( "{}", self_name);
    std::println();
    std::println( "Programmptionen:");
    std::println( "-v        Programmversion ausgeben");
    std::println();
}

// Version ausgeben
void version( void)
{
    std::println( "Fletcher's Checksum (und Varianten)");
    std::println( "erstellt: " __DATE__ " " __TIME__ " auf " __BUILD_HOST);
}


// simple checksum
uint16_t calc_sum16( const std::vector<uint8_t>& data)
{
    uint16_t  s = 0;

    for( uint16_t index = 0; index < data.size(); index++)
    {
        s += data[ index];
    }
    return s;
}


/* Calculating XMODEM CRC-16 in 'C'
   ================================
   Reference model for the translated code */

#define poly 0x1021

uint16_t xmodem_crc16( uint8_t byte, uint16_t crc)
{
    crc = crc ^ (byte << 8);
    for (int i=0; i<8; i++)
    {
        if (crc & 0x8000)
        {
            crc = crc << 1;
            crc = (crc ^ poly) & 0xFFFF;
        }
        else
        {
            crc = crc << 1;
        }
    }
    return crc;
}
uint16_t calc_crc16( const std::vector<uint8_t>& data)
{
    uint16_t  crc = 0xffff;
    for( uint16_t index = 0; index < data.size(); index++)
    {
        crc = xmodem_crc16( data[ index], crc);
    }
    return crc;
}


uint32_t calc_adler32( const std::vector<uint8_t>& data)
{
    uint32_t  a = 1;
    uint32_t  b = 0;

    for( uint16_t index = 0; index < data.size(); index++)
    {
        a = ( a + data[ index]) % 65521;
        b = ( a + b           ) % 65521;
    }
    return(( (uint32_t) b << 16) | a);
}


// Prüfsumme berechnen,
// Fletcher Modulo 256, Startwert modifiziert
// https://www.mikrocontroller.net/topic/455478#5492259
// https://de.wikipedia.org/wiki/Fletcher%E2%80%99s_Checksum
uint16_t calc_fsum_kc( const std::vector<uint8_t>& data)
{
    uint8_t  a = data[ 0];
    uint8_t  b = 0;

    for( uint16_t index = 0; index < data.size(); index++)
    {
        a = a + data[ index];
        b = b + a;
    }
    return(( (uint16_t) b << 8) | a);
}


// Fletcher Modulo 256
uint16_t calc_fsum_256( const std::vector<uint8_t>& data)
{
    uint8_t  a = 0;
    uint8_t  b = 0;

    for( uint16_t index = 0; index < data.size(); index++)
    {
        a = a + data[ index];
        b = b + a;
    }
    return(( (uint16_t) b << 8) | a);
}


// Fletcher Modulo 255
uint16_t calc_fsum_255( const std::vector<uint8_t>& data)
{
    uint16_t  a = 0;
    uint16_t  b = 0;

    for( uint16_t index = 0; index < data.size(); index++)
    {
        a = ( a + data[ index]) % 255;
        b = ( b + a) % 255;
    }
    return(( (uint16_t) b << 8) | a);
}


// Fletcher-16, ones complement (Modulo 2^K-1)
uint32_t calc_fletcher16( const std::vector<uint8_t>& data)
{
    uint16_t  a = 0;
    uint16_t  b = 0;
    uint16_t  M = 65535;

    for( uint16_t index = 0; index < data.size(); index++)
    {
        a = ( a + data[ index]) % M;
        b = ( b + a) % M;
    }
    return ((uint32_t) b << 16) | a;
}


// XOR checksum
uint8_t calc_xor( const std::vector<uint8_t>& data)
{
    uint8_t  s = 0;

    for( uint16_t index = 0; index < data.size(); index++)
    {
        s ^= data[ index];
    }
    return s;
}


void process_block
(
    const std::vector<uint8_t>& data,
    std::string comment
)
{
    std::print( "{}", comment);
    std::print( "    Länge {}", data.size());
    std::print( "    Adler-32 {:08X}", calc_adler32( data));
    std::print( "    crc16 {:04X}", calc_crc16( data));
    std::print( "    fletcher 255 {:04X}", calc_fsum_255( data));
    std::print( "    fletcher 256 {:04X}", calc_fsum_256( data));
    std::print( "    fletcher KC {:04X}", calc_fsum_kc( data));
    std::print( "    XOR8  {:02X}", calc_xor( data));
    std::print( "    sum16 {:04X}", calc_sum16( data));
    //std::print( "    fletcher 16  {:08X}", calc_fletcher16( data));
    std::println();
}

//////////////////////////////////////////////////
int main( int argc, char** argv)
{

    const std::string self_name = argv[ 0];
    int c;


    // Argumente auswerten
    while(( c = getopt( argc, argv, "hvd")) != -1)
    {
        switch( c)
        {
            case 'h':
            case '?':
                help( self_name);
                exit( EXIT_SUCCESS);
                break;

            case 'v':
                version();
                exit( EXIT_SUCCESS);
                break;
        }
    }

    std::vector<uint8_t> x( 8192, 0);
    std::vector<uint8_t> y( 8192, 1);
    std::vector<uint8_t> f( 8192, 0x55);
    std::vector<uint8_t> z( 8192, 0xff);

    process_block( x, "zero");
    process_block( y, "ones");
    process_block( f, "55h ");
    process_block( z, "FFs ");

    exit( EXIT_SUCCESS);
}
