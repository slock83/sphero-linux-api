/*************************************************************************
                           ActionHandler  -  description
                             -------------------
    début                : ven. 08 mai 2015
*************************************************************************/

//---------- Réalisation de la classe <ActionHandler> (fichier ActionHandler.tpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
//------------------------------------------------------ Include personnel

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
template<typename T>
/**
 * @brief reportAction : Permet de tenir l'actionHandler au courant de 
 * 						 l'action survenue. Tous les listener sont ensuite
 * 						 notifiés.
 * @param action : 	Un pointeur sur la structure de donnée qui contient
 * 					les informations relatives à l'action.
 */
void ActionHandler::reportAction(T* action)
{
	std::queue<listener<T> const>::iterator it;
	for(it = _listenerQueue.begin() ; it != _listenerQueue.end() ; it++)
	{
		*it(action);
	}
}

template<typename T>
/**
 * @brief addActionListener : Permet d'enregistrer un listener d'action
 * @param : listener : le listener à ajouter
 */
void ActionHandler::addActionListener(listener<T> const listener)
{
	_listenerQueue.push(listener);
}

template<typename T>
/**
 * @brief clearListener : désenregistre tous les listeners
 */
void clearListener()
{
	std::queue<listener<T> const> empty;
	std::swap(_listenerQueue, empty);

}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
ActionHandler::ActionHandler():_listenerQueue()
{
} 


ActionHandler::~ActionHandler ( )
{
} 


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées

