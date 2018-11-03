#include "network.h"
#include <algorithm>
#include "random.h"
#include <iostream>

// - - - - - - - - - - - METHODES - - - - - - - - - - - - - - - - - - - - - - - - - - -

void Network::resize(const size_t& s) {		
	
	values.clear();
	values.resize(s);
	RNG.normal(values, 0, 1);
}



bool Network::add_link(const size_t& a, const size_t& b){		
	
	if ((std::max(a,b) >= values.size()) or (a == b)) { 
		
		return false;
	}
	
	std::vector<size_t> voisins(neighbors(a));
	
	for (auto v:voisins) {
		
		if (v == b) { 
			
			return false;
		}
	}
	
	links.emplace(a, b);
	links.emplace(b, a);
		
	return true;
}



size_t Network::random_connect(const double& n){	
	
	links.clear();
	std::vector<size_t> indices;
	size_t compteur(0);
	size_t taille(values.size());
	
	for (size_t i(0); i < taille; i += 1) {		
		indices.push_back(i);
	}
			
	for (size_t i(0); i < taille; i += 1) {
		
		int m(RNG.poisson(n));
		
		for (int j(0); j < m ; j += 1) {
			
			bool lien(false);
			
			while (!lien ) {
				
				RNG.shuffle(indices);
				
				lien = add_link(i, indices[j]);
			}
			compteur += 1;
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
	
	if (n > values.size()) { 
		
		return 0;
		
	} else {	
		
		return (links.count(n));	
	}	
}



double Network::value(const size_t& n) const{
	
	return values[n];
}



std::vector<double> Network::sorted_values() const{
	
	if (values.empty()) { 
	
		return values;
	} else {
		
		std::vector<double> val_s(values);
		
		std::sort(val_s.begin(), val_s.end());
		std::reverse(val_s.begin(), val_s.end());
		
		return val_s;
	}
}



std::vector<size_t> Network::neighbors(const size_t& n) const{		
	
	std::vector<size_t> voisins;
	
	if (n > values.size()) { 
		
		return voisins;
		
	} else {
		
		for (auto l:links){
			
			if (l.first == n) {
				
				voisins.push_back(l.second);
			}		
		}
	}	
	return voisins;
}	


