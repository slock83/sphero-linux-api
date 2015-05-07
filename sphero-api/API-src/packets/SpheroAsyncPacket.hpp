/*************************************************************************
    SpheroAsyncPacket 
                             -------------------
    début                : mar. 28 avril 2015
*************************************************************************/

//---------- Interface de la classe <SpheroAsyncPacket> (fichier SpheroAsyncPacket.hpp) ------
#if ! defined ( SPHEROASYNCPACKET_H )
#define SPHEROASYNCPACKET_H

//--------------------------------------------------- Interfaces utilisées
#include "SpheroPacket.hpp"

//------------------------------------------------------------- Constantes 
static const uint8_t POWER_NOTIFICATION_FLAG = 0x1;
static const uint8_t LVL_1_DIAGNOSTIC_RESPONSE = 0x2;
static const uint8_t SENSOR_DATA_STREAMING = 0x3;
static const uint8_t CONFIG_BLOCK_CONTENT = 0x4;
static const uint8_t PRESLEEP_WARNING = 0x5;
static const uint8_t MACRO_MARKERS = 0x6;
static const uint8_t COLLISION_DETECTED = 0x7;
static const uint8_t ORBBASIC_PRINT_MESSAGE = 0x8;
static const uint8_t ORBBASIC_ASCII_ERROR = 0x9;
static const uint8_t ORBBASIC_BINARY_ERROR = 0xA;
static const uint8_t SELF_LEVEL_RESULT = 0xB;
static const uint8_t GYRO_AXIS_LIMIT_EXCEEDED = 0xC;

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <SpheroAsyncPacket>
//
// Définir les comportements des paquets asynchrones reçus par sphero
//------------------------------------------------------------------------ 

class SpheroAsyncPacket : public SpheroPacket
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	
   	static bool extractPacket(int fd, Sphero* sphero, SpheroPacket** packet_ptr);
    virtual void packetAction() = 0;

//------------------------------------------------- Surcharge d'opérateurs
    SpheroAsyncPacket & operator = ( const SpheroAsyncPacket & unSpheroAsyncPacket ) = delete;


//-------------------------------------------- Constructeurs - destructeur

    SpheroAsyncPacket ( const SpheroAsyncPacket & unSpheroAsyncPacket ) = delete;

    virtual ~SpheroAsyncPacket();
//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
    SpheroAsyncPacket(Sphero* sphero);

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés
	static extractorMap_t _extractorMap;	
//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <SpheroAsyncPacket>

#endif // SpheroAsyncPacket_H

