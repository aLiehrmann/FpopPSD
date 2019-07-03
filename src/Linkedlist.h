#ifndef DEF_LINKEDLIST
#define DEF_LINKEDLIST

#include <vector>
#include <array> 
class Linkedlist;

class Interval
{
private:
    double begin;
    double end;
public:
    /**
     * @details Instancie un intervalle vide. 
     * Tout intervalle de la forme [a,b] tel que a>b est considéré comme un intervalle vide (par default [+1,-1]).
     */
    Interval();

    /**
     * Instancie un intervalle de la forme [begin_,end_].
     */
    Interval(double begin_, double end_);

    /**
     * @details Instancie l'intersection des intervalles contenus dans une liste d'intervalles. Cette intersection peut être vide ou peut prendre la forme d'un singleton.
     * @param[in] list_of_intervals_to_intersect Une liste non ordonnée d'intervalles non vides, qui ne sont pas des singletons. Cette liste peut être vide auquel cas elle instancie un intervalle vide. 
     */
    Interval(Linkedlist * list_of_intervals_to_intersect);

    /**
     * @details Met à jour l'intervalle courant en l'intersectant avec un autre intervalle.
     * @param[in] interval_to_intesect Un intervalle qui peut être vide ou prendre la forme d'un singleton.
     */
    void operator&=(Interval const& interval_to_intesect);

    /**
     * @details Compare le début de deux intervalles.
     * @returns TRUE si le début de l'intervalle 'interval1' est inférieur au début de l'intervalle 'interval2', FALSE sinon.
     */
    static bool Compare_begin(Interval const& interval1, Interval const& interval2);

    /**
     * @details Compare la fin de deux intervalles.
     * @returns TRUE si la fin de l'intervalle 'interval1' est inférieure à la fin de l'intervalle 'interval2', FALSE sinon.
     */
    static bool Compare_end(Interval const& interval1, Interval const& interval2);

    /**
     * @returns TRUE si l'intervalle courant est vide ([a,b] tel que a>b) prend la forme d'un singleton ([a,a]), FALSE sinon. 
     */
    bool IsEmpty_or_singleton();

    /**
     * @returns Renvoie le debut de l'intervalle courant.
     */
    double Get_begin();

    /**
     * @returns Renvoie la fin de l'intervalle courant.
     */
    double Get_end();

    /**
     * @details Met à jour le debut de l'intervalle courant.
     */
    void Set_begin(double begin_);

    /**
     * @details Met à jour la fin de l'intervalle courant.
     */
    void Set_end(double end_);

    
};

struct Node
{
    Interval interval;
    Node *next;
    Node *previous;    
};

class Linkedlist
{
private:
    Node *head, *tail;
    int length;
public:
    Linkedlist();
    Linkedlist(Interval l);
    ~Linkedlist();
    //static Node * mergeSort(Node * head);
    void Push_back(Interval interval);
    int Size();
    void Sort();
    Node * Front();
    Node * Back();
    double Max();
    double Min();
    bool Empty();
    void Merge();
    Node * Erase(Node * node_to_erased);
    void Update_tail();
    void Update_head();
    void Print();
    void Intersect_with(Interval & interval_to_intersect);
    void Complementary_in(Interval & d);
};

#endif