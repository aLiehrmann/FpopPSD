#ifndef DEF_SAMPLING
#define DEF_SAMPLING

#include "Candidate.h"
#include <list>
#include <vector>
#include <random>

class Sampling
{
private:
public:
    /**
     * @returns nb entiers naturels tirés alétoirement dans l'intervalle ]0+p,n+p[ (tirage avec remise).
     */
    static std::vector<int> Rand_with_replacement(int p, int n, int nb);
    
    /**
     * @returns nb entiers naturels tirés alétoirement dans l'intervalle ]0+p,n+p[ (tirage sans remise) si nb<n, sinon tous les entiers naturels contenus dans cet intervalle. 
     */
    static std::vector<int> Rand_without_replacement(int p, int n, int nb);
    
    /**
     * @returns un entier naturel tiré alétoirement dans l'intervalle ]0+p,n+p[.
     */
    static std::vector<int> Rand_one(int p, int n, int nb);
    
    /**
     * @returns l'ensemble des entiers naturels de l'intervalle ]0+p,n+p[.
     * @param[in] nb non utilisé pas la méthode.
     * @param[in] choose non utilisé pas la méthode.
     * @param[in] engine non utilisé pas la méthode.
     */
    static std::vector<int> All(int p, int n, int nb);
    
    /**
     * @returns les nb derniers entiers naturels de l'intervalle ]0+p,n+p[ si nb < n, sinon tous les entiers naturels contenus dans cet intervalle.
     * @param[in] choose non utilisé pas la méthode.
     * @param[in] engine non utilisé pas la méthode.
     */
    static std::vector<int> Last(int p ,int n, int nb);
    
    /**
     * @returns les nb ème entier naturel de l'intervalle ]0+p,n+p[ si nb < n, sinon n-1+p.
     * @param[in] choose non utilisé pas la méthode.
     * @param[in] engine non utilisé pas la méthode.
     */
    static std::vector<int> Only(int p, int n, int nb);
};
#endif