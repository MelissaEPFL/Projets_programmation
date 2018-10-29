#include "network.h"
#include <algorithm>
#include "random.h"

// - - - - - - - - - - - METHODES - - - - - - - - - - - - - - - - - - - - - - - - - - -

RandomNumbers rng;

void Network::resize(const size_t& s){
	
	values.clear();
	values.resize(s);
	rng.normal(values, 0, 1);
}



bool Network::add_link(const size_t& a, const size_t& b){
	
	if ((std::max(a, b) < values.size()) and (a != b)) {
		
		links.emplace(a, b);
		links.emplace(b, a);
		
		return true;
		
	} else {
		
		throw std::string("Vous tentez de créer un lien entre un ou deux noeud(s) qui n'existent pas");
		
		return false;
	}	
}



size_t Network::random_connect(const double& m){
	
	links.clear();
	std::vector<size_t> indices;
	size_t compteur(0);
	
	for (size_t i(0); i < values.size(); i += 1) {
		indices.push_back(i);
	}
			
	for (size_t i(0); i < values.size(); i += 1) {
		
		int n(rng.poisson(m));
		
		rng.shuffle(indices);
		
		compteur += 1;
				
		for (int j(0); j < n ; j += 1) {
			
			add_link(indices[j], i);
		}		
	}	
	
	return compteur;
}



size_t Network::set_values(const std::vector<double>& tab){
	
	if (!(tab.empty())) {
		
		values = tab;
		
		return tab.size();
		
	} else {
		
		return 0;
	}
}



size_t Network::size() const{
	
	if (values.empty()) {
		
		return 0;
		
	} else {
		
		return values.size();
	}	
}



size_t Network::degree(const size_t& n) const{
	
	if (n < values.size()) {
		
		return (links.count(n));
		
	} else {
		
		throw std::string("Vous essayez d'accéder à un noeud qui n'existe pas!");
		
		return 0;
	}		
}



double Network::value(const size_t& n) const{
	
	return values[n];
}



std::vector<double> Network::sorted_values() const{
	
	if (!(values.empty())) {
		
		std::vector<double> val_s(values);
		
		std::sort(val_s.begin(), val_s.end());
		std::reverse(val_s.begin(), val_s.end());
		
		return val_s;
	
	} else {
		
		throw std::string("Vous ne pouvez pas trier un réseau vide!");
	}
		
	return values;
}



std::vector<size_t> Network::neighbors(const size_t& n) const{		
	
	std::vector<size_t> voisins;
	
	if (n < values.size()) {
	
		auto val = links.equal_range(n);
			
		for (auto i = val.first; i != val.second; ++i){
				
			voisins.push_back((*i).second);				
		}
		
		if (!(voisins.empty())) {
		
			return voisins;
		
		} else {
		
			throw std::string("Ce noeud n'a aucun voisin!");
		}
		
	} else {
		
		throw std::string("Vous essayez d'accéder à un noeud qui n'existe pas!");
	}	
}	


