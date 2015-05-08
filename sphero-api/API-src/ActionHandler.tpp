/*************************************************************************
                           ActionHandler  -  description
                             -------------------
    début                : ven. 08 mai 2015
*************************************************************************/

//----- Réalisation de la classe <ActionHandler> (fichier ActionHandler.tpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
//------------------------------------------------------ Include personnel

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
/**
 * @brief reportAction : Permet de tenir l'actionHandler au courant de 
 * 						 l'action survenue. Tous les listener sont ensuite
 * 						 notifiés.
 * @param action : 	Un pointeur sur la structure de donnée qui contient
 * 					les informations relatives à l'action.
 */
template<typename ...T>
void ActionHandler<T...>::reportAction(T... action)
{
	typename listenerQueue_t::iterator it;
	for(it = _listenerQueue.begin() ; it != _listenerQueue.end() ; it++)
	{
		*it(action...);
	}
}

template<typename ...T>
/**
 * @brief addActionListener : Permet d'enregistrer un listener d'action
 * @param : listener : le listener à ajouter
 */
void ActionHandler<T...>::addActionListener(listener_t listener)
{
	_listenerQueue.push(listener);
}

template<typename ...T>
/**
 * @brief clearListener : désenregistre tous les listeners
 */
void ActionHandler<T...>::clearListener()
{
	listenerQueue_t empty;
	std::swap(_listenerQueue, empty);
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
template<typename ...T>
ActionHandler<T...>::ActionHandler():_listenerQueue()
{
} 


template<typename ...T>
ActionHandler<T...>::~ActionHandler ( )
{
} 


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées

