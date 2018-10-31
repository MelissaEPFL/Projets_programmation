#include "network.h"
#include <algorithm>
#include "random.h"
#include <iostream>

// - - - - - - - - - - - METHODES - - - - - - - - - - - - - - - - - - - - - - - - - - -

RandomNumbers rng;

void Network::resize(const size_t& s) {		
	
	values.clear();
	values.resize(s);
	rng.normal(values, 0, 1);
}



bool Network::add_link(const size_t& a, const size_t& b){		
	
	if ((std::find(values.begin(), values.end(), a) == values.end())
	or (std::find(values.begin(), values.end(), b) == values.end())) { throw std::string("Impossibilité de créer un lien : l'un des noeuds n'existe pas!"); }
	
	if (a == b) { throw std::string("Impossibilité de créer un lien : les deux indices passés en arguments sont les mêmes!"); }
	
	std::vector<size_t> voisins(neighbors(a));
	
	for (auto v:voisins) {
		
		if (v == b) { throw std::string("Impossibilité de créer un lien : Ce lien existe déjà!");  }
	}
	
	try { 
		
		} catch (std::string &e) {
		
		std::cerr << e << std::endl;
		
		return false;
	}
	
	links.emplace(a, b);
	links.emplace(b, a);
		
	return true;
}



size_t Network::random_connect(const double& n){	
	
	links.clear();
	std::vector<size_t> indices;
	size_t compteur(0);
	
	for (size_t i(0); i < values.size(); i += 1) {
		indices.push_back(i);
	}
			
	for (size_t i(0); i < values.size(); i += 1) {
		
		int m(rng.poisson(n));
		
		rng.shuffle(indices);
		
		compteur += 1;
				
		for (int j(0); j < m ; j += 1) {
			
			bool lien(false);
			while (!lien) {
				lien = add_link(indices[j], i);
			}
		}		
	}	
	
	return compteur;
}



size_t Network::set_values(const std::vector<double>& tab){
	
	
	if (tab.size() < values.size()){
	
		for (size_t i(0); i < tab.size(); i++) {
			
			values[i] = tab[i];
		}
	
	} else if (tab.size() >= values.size()) {
		
		values.clear();
		values = tab;
		
		return tab.size();
		
	} else if (tab.empty()) {
	
		return 0;
	}
	
	return tab.size();
}



size_t Network::size() const{
	
	if (values.empty()) {
		
		return 0;
		
	} else {
		
		return values.size();
	}	
}



size_t Network::degree(const size_t& n) const{
	
	if (n > values.size()) { throw std::string("Impossible de donner le degré : Vous essayez d'accéder à un noeud qui n'existe pas!"); }
	
	try {
		
	} catch (std::string &e) {
		
		std::cerr << e << std::endl;
		
		return 0;
	}
		
	return (links.count(n));		
}



double Network::value(const size_t& n) const{
	
	return values[n];
}



std::vector<double> Network::sorted_values() const{
	
	if (values.empty()) { throw std::string("Impossible de trier les valeurs : Le réseau est vide!"); }
	
	try{
	
	} catch (std::string &e) {
		
		std::cerr << e << std::endl;
		
		return values;
	}
		
	std::vector<double> val_s(values);
		
	std::sort(val_s.begin(), val_s.end());
	std::reverse(val_s.begin(), val_s.end());
		
	return val_s;
}



std::vector<size_t> Network::neighbors(const size_t& n) const{		
	
	
	if (n > values.size()) { throw std::string("Impossible de déterminer les voisins : ce noeud n'existe pas"); 
		
	} else {
	
		std::vector<size_t> voisins;
			
		auto val = links.equal_range(n);
				
		for (auto i = val.first; i != val.second; ++i){
				
			voisins.push_back(i->second);				
		}
		
		if (!(voisins.empty())) {
		
			return voisins;
		
		} else {
		
			throw std::string("Impossible de déterminer les voisins : Ce noeud n'a aucun voisin!");
		}
	}
	
	try { 
		
	} catch (std::string &e) {
		
		std::cerr << e << std::endl;
		
		std::vector<size_t> voisins;
		
		return voisins;
	}
	
}	


