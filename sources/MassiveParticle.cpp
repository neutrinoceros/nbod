#include "MassiveParticle.h"


//initialisation des attributs statiques
vector<MassiveParticle*> MassiveParticle::adresses;//initialisation à vide


//méthodes statiques
vector<MassiveParticle*> MassiveParticle::getAdresses() {
    return adresses;
}


void MassiveParticle::printSystem(){
    int N(adresses.size());
    cout << endl;
    cout << "==================================" << endl;
    cout << N << " particles total, ";
//    cout << "epoch : " << epoch << endl;
    cout << "==================================" << endl;
    int m;
    for(m = 0 ; m < N ; m++){
        cout << "particle n°" << m << " :" << endl;
        cout << *adresses[m] << endl;
    }
}



//ceci n'est pas une méthode statique
valarray<double> MassiveParticle::compacc(MassiveParticle part2) const {
    double r(0), intensity(0);
    valarray<double> dir(0.,3), acc(0.,3);
    r = distanceTo(part2);
    dir = directionTo(part2);
    intensity = - G * part2.m_mass / (r*r);
    acc = dir * intensity;
    return acc;
}


//////////////////////////////////ne pas supprimer !!!!!!
//valarray<double> MassiveParticle::compjerk(MassiveParticle part2) const {
//    double r(0);
//    valarray<double> dir(0.,3), v(0.,3), jerk(0.,3);
//    r = distanceTo(part2);
//    v = part2.m_velocity - m_velocity;
//    dir = directionTo(part2);
//    jerk = - G * part2.m_mass *(v/pow(r,3) - 3 * dot(r*dir, v)/pow(r,5) * r*dir);
//    return jerk;
//}
//////////////////////////////////



//constructeurs
MassiveParticle::MassiveParticle() : Particle(), m_mass(rand()%maxm){
    setke();
    setradius();
    adresses.push_back(this);
}

MassiveParticle::MassiveParticle(valarray<double> pos, valarray<double> vel) : Particle(pos, vel), m_mass(rand()%maxm), m_potentialEnergy(0.){ 
    setke();
    setradius();
    adresses.push_back(this);
}

MassiveParticle::MassiveParticle(double mass) : Particle(), m_mass(mass), m_potentialEnergy(0.){
    setke();
    setradius();
    adresses.push_back(this);
}

MassiveParticle::MassiveParticle(valarray<double> pos, valarray<double> vel, double mass) : Particle(pos, vel), m_mass(mass), m_potentialEnergy(0.){
    setke();
    setradius();
    adresses.push_back(this);
}



//
void MassiveParticle::setradius(){
    m_radius = pow(m_mass/asterdensity, 1./3.);
}



//affichage copié et modifié de la version Particle, peut-être pas la méthode la plus efficace
void MassiveParticle::print(ostream &stream) const {
    stream << "MassiveParticle at : ";
    int i;
    for(i = 0 ; i < 3 ; i++) {
        stream << m_position[i] << "   ";
    }
    stream << endl << "speed, mass, kinectic e : " << getvel() << "   " << getmass() << "   " << getke() << endl;
}

//accesseurs et méthodes constantes
double MassiveParticle::getmass() const {
    return m_mass;
}

double MassiveParticle::getke() const {
    return m_kineticEnergy;
}

double MassiveParticle::boundingEnergy(MassiveParticle otherParticle) const {
    double d, be;
    d = distanceTo(otherParticle);
    be = -1./2. * m_mass * otherParticle.m_mass * G / d;
    return be;
}


MassiveParticle& MassiveParticle::operator=(MassiveParticle newpart){
    setposition(newpart.m_position);
    setvelocity(newpart.m_velocity);
    setmass(newpart.m_mass);
    setke();
    return *this;
}

//mutateurs et méthodes non constantes
void MassiveParticle::setmass(double newmass){
    m_mass = newmass;
}


void MassiveParticle::setke(){
        m_kineticEnergy = 1./2. * m_mass *  pow(getvel(), 2);
}


//operateurs hors classes

MassiveParticle operator+(MassiveParticle const& part, valarray<double> boostVect){
    MassiveParticle copy(part);
    copy += boostVect;
    return copy;
}
