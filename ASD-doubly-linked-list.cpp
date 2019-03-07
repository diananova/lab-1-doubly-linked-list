// Implementa le funzioni sulle liste realizzate con strutture doppiamente collegate, circolari, con sentinella, senza ordinamento
//g++ ASD-doubly-linked-list.cpp ASD-main.cpp -o asd

#include "ASD-doubly-linked-list.h"


using namespace list;

struct list::node {  // descrivo qui, fuori dal namespace, come e' fatta la struttura node: i dettagli interni non saranno visibili dal main
Elem info;
node *prev;
node *next;
};

/*************************************************/
/* Implementazione delle operazioni di utilita'  */
/*************************************************/

void readFromStream(istream& str, List& l)
{
    createEmpty(l);
    Elem e;
    str>>e;
    if (!str) throw runtime_error("Errore inserimento dati\n");
    while (e != FINEINPUT)  // assumiamo che il segnale di fine input nel file sia  FINEINPUT
        {     
        addRear(e, l);   // aggiunge l'elemento alla fine della lista
        str>>e;
        if (!str) throw runtime_error("Errore inserimento dati\n");
        }
}

void readFromFile(string nome_file, List& l)  /* legge il contenuto di una lista da file */
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    readFromStream(ifs, l);
}



void readFromStdin(List& l)         /* legge il contenuto di una lista da standard input */
{
   cout << "\nInserire una sequenza di numeri separati da spazi seguiti da " << FINEINPUT << " per terminare\n";
   readFromStream((std::cin), l);
}


void print(const List& l)           /* stampa la lista */
{
   List q = l->next;  // q "salta la sentinella" e va alla testa della lista
   while (q != l)     // avanza finche' non finisce la lista
     {
      cout << q->info << "; ";
      q = q->next; 
      }
}

/**************************************************/
/* Implementazione delle operazioni nel namespace */
/**************************************************/

void list::clear(const List& l)                 /* "smantella" la lista svuotandola */
{
	List aux = l->next;
	while (aux!=l)
	{
		aux = aux->next;
		delete aux->prev;
	}
	l->prev = l;
	l->next = l;
}


Elem list::get(int pos, const List& l)        /* WORKS restituisce l'elemento in posizione pos se presente; restituisce un elemento che per convenzione si decide che rappresenta l'elemento vuoto altrimenti*/
{
	node* temp = l;
	for (int i=-1; i<pos; i++)
	{
		if (temp->next==l) return -10000;
		temp = temp->next;
	}
	return temp->info;
	
}


void list::set(int pos, Elem e, const List& l)        /* WORKS modifica l'elemento in posizione pos, se la posizione e' ammissibile */
{
	node* curr = l;
	for (int i=-1; i<pos; i++)
	{
		if (curr->next == l) return;
		curr = curr->next;
	}
	curr->info = e;
}


void list::add(int pos, Elem e, const List& l)        /* WORKS inserisce l'elemento in posizione pos, shiftando a destra gli altri elementi */
{                                               
  node* temp = l->next;
 
  for (int i=0; i<pos; i++)
  {
	if (temp->next==l) return;
	temp = temp->next;
  }
	node* aux = new node;
	aux->info = e;
	
	aux->prev = temp->prev;
	aux->next = temp;
	temp->prev->next = aux;
	temp->prev = aux;
	return;
}


void list::addRear(Elem e,  const List& l)        /* WORKS inserisce l'elemento alla fine della lista */
{
	node* last = l->prev;	//at the beginning l->prev = l->next
	node* aux = new node;
	aux->info = e;
	aux->next = l; //point to first elem	
	l->prev = aux;
	aux->prev = last;
	last->next = aux;
	
}


void list::addFront(Elem e, const List& l)        /* WORKS inserisce l'elemento all'inizio della lista */
{
	node* aux = new node;
	aux->info = e;
	aux->next = l->next;
	l->next = aux;
	aux->prev = l;
	l->next->prev = aux;	
     
}


void list::removePos(int pos, const List& l)      /* WORKS cancella l'elemento in posizione pos dalla lista */
{
	node* temp = l->next;
	for (int i=0; i<pos; i++)
	{
		if (temp->next==l) return;
		temp = temp->next;
	}
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	delete temp;
	return;
}


void list::removeEl(Elem e, const List& l)        /* WORKS cancella tutte le occorrenze dell'elemento elem, se presenti, dalla lista */
{
	node* temp = l->next;
	while (temp!=l)
	{
		if (temp->info==e)
		{
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
		}
		temp = temp->next;
	}
	return;
}


bool list::isEmpty(const List& l)         /* WORKS restituisce true se la lista e' vuota (ed e' vuota se il next di l, e' l stessa */
{
  return (l->next == l);
}


int list::size(const List& l)           /* restituisce la dimensione della lista */
{
	List temp = l->next;
	int cont  = 0;
	while (temp!=l)
	{
		cont++;
		temp = temp->next;
	}
	return cont;
	
}


void list::createEmpty(List& l)           /* WORKS crea la lista vuota */
{
   List aux = new node;
   aux->next = aux;
   aux->prev = aux;
   l = aux;
}
