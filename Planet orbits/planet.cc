//planet.cc simulates a 2 body inverse square law problem
#include <iostream>
#include <cmath>
using namespace std;

#define D  2 //number of dimensions
struct particle { //definining the structure of the 'particle' which contains all the info needed for calculations
	double x[D]; 
	double v[D]; 
	double F[D]; 
	double m;
	double M;
	double G;
	double t;
	double E;
} ;

//function to calculate force
void force( particle &a ){
	double xsq = 0.00;
	double x_pow;
	
	for (int i = 0; i < D; i++){ //calculating the distance to origin squared  
		xsq += pow(a.x[i],2); 
	}
	
	x_pow = pow(xsq,1.5); //calculating squared distance to the power 3/2
	
	for (int i = 0; i < D; i++){
		a.F[i] = -((a.G)*(a.M)*(a.m)*(a.x[i]))/(x_pow); //calculating vecotr force using inverse sqaure law
	}	
}

//function to calculate the new position of particle after a position step
void positionStep(particle &a, double dt){
	for (int i = 0; i < D; i++){
		a.x[i] += dt * a.v[i]; 
	}
	//cout << a.x[0] << "\t" << a.x[1];
}

//function to calculate new velocity after step
void velocityStep(particle &a, double dt){
	for (int i = 0; i< D; i++){
		a.v[i] += (dt*a.F[i])/(a.m);
	}	
}

//function to calculate the kinetic energy of the particle
void energy(particle &a){
	double v2=0;
	
	for (int i = 0; i<D ; i++){ //calculating v squared
		v2 += a.v[i]*a.v[i];
	}
	a.E = (0.5)*(a.m)*(v2);
}

//function to print ot time,x_0,x_1
void showPos(particle &a){
	printf( "%f \t" , a.t); //first prints the time out 
	
	for (int i = 0; i<D; i++){
		printf( "%12.6g \t" , a.x[i]); //then prints the x and y positions all serperated by a tab
	}
	
}

//function to print v_1 v_2 energy
void showVel(particle &a){
	for (int i = 0; i<D; i++){
		printf( "%f \t" , a.v[i]); //prints the compoments of velocity 
	}
	printf("%f \n", a.E); //prints out the energy and then a new line
}

//function to run through iteration using eulers method
void euler(particle &a){
	double dt = 0.01;
	
	for (int i = 0; i<1000; i++){
		force(a);
		positionStep(a, dt);
		velocityStep(a, dt);
		a.t += dt;
		energy(a);
		
		showPos(a);
		showVel(a);
	}
}

//function to implement leapfrog method 
void leapfrog(particle &a){ 
	double dt = 0.01;
	
	for (int i =0; i<1000; i++){
		positionStep(a, (dt*0.5) );
		a.t += dt/2;
		force(a);
		velocityStep(a, dt*0.5);
		positionStep(a, dt*0.5);
		a.t += dt*0.5;
		showPos(a);
		showVel(a);
	}
}

int main()
{
	particle a; //declaring particle a and all the inital conditions
	a.v[0] = 0.4;
	a.v[1] = 0;
	a.x[0] = 1;
	a.x[1] = 1;
	a.G = 6.67*pow(10,-11); 
	a.M = (1/6.67)*pow(10,11); 
	a.m = 1;
	a.t = 0.00;
	
	leapfrog(a);
	//euler(a); //run either euler method or leapfrog method (instead of using a user option to input a choice
	// of method I choose to comment in/out the relevant method as then i would run the program and pipe
	// the output straight into a file )
		
	return 0;
}
