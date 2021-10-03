#include <iostream> // Note - I included all files I thought I might need even if 
#include <cmath>	// I didn't end up using them just to avoid annoying debugging later
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <string.h>
using namespace std;

//defining the particale structure
struct particle { 
	double x; // position
	double p; // momentum
	double im; // inverse mass
	double v; // velocity
	double t; // kinetic energy
	double r; // radius
} ;

// function to calculate mometum from velocity
void v2p (particle &a){
	a.p = a.v /a.im;
}

void collision( particle &a, particle &b){
	double c_1, c_2, c_3, u_1, u_2;
	
	u_1 = a.v; // define inital velocity of 1st particle
	u_2 = b.v; // define inital velocity of 2nd particle
	
	// calculating required coefficients in terms of inverse masses 
	c_1 = (b.im - a.im)/(a.im + b.im);
	c_2 = 2*(a.im)/(a.im + b.im);
	c_3 = 2*(b.im)/(a.im + b.im);
	
	// updating velocities of paricles 
	a.v = c_1*u_1 + c_2*u_2;
	b.v = c_3*u_1 - c_1*u_2;
	
	// updating momemta
	v2p (a);
	v2p (b);
}

// function to calculate kinetic energy of particle
double kineticEnergy (particle *a, int NN){
	double E = 0.0;
	for (int i=1; i < NN-1; i++){ // summing kinetic energy but avoiding the walls
		E += 0.5*(a[i].v * a[i].v)/a[i].im;
	}
	return E;
}

// function to find time to next collision
double next (particle *a, int NN, int &which_n){
	double delta_t = 1e100;
	double delta_v;
	double collision_time;
	
	for (int i=0; i<=NN; i++){
		delta_v = a[i].v - a[i+1].v;
		
		if (delta_v > 0.0){
			collision_time = ((a[i+1].x-a[i+1].r) - 
			(a[i].x+a[i].r)) / delta_v;
			
			if (collision_time < delta_t){
				delta_t = collision_time;
				which_n = i;
			}
		}
	}
	return delta_t;
}

// function to increment time step
void positionStep (particle &a, double dt){
	a.x += dt * a.v;
}

//function to leap all particles forward by a certain time
void leapForward (particle *a, int NN , double dt){
	for (int n=0; n<NN; n++){
		positionStep (a[n], dt);
	}
}

// function to print out state of particle
void showState (particle *a, int NN){
	for (int i =0; i < NN; i++ ){
		cout << "\t" << a[i].x << "\t" << a[i].v; 
	}
	cout << endl;
}

//function to run the simulation
void run(particle *a, int NN, double &t, double dt, double T){
	int whichn;
	double next_collision_dt;
	double next_coll_time;
	//int collision_num = 0;
	int count=0;
	
	for(;t<=T;){
		if (count % 2 == 0 ){ 	// Writing state to file every 2 time steps. 
								// I altered the number of times when I altered the Dt to still get a good animation
			cout << t << "\t" << kineticEnergy (a, NN); 
			showState (a, NN);
		}
		
		next_collision_dt = next(a, NN, whichn);
		
		if (dt < next_collision_dt){ // see if no balls collide within next time step
			t += dt;
			for (int q=0; q<NN; q++){ // if no collisions in time set just incrimenting 
				positionStep(a[q], dt);
			}
		}
		
		else {
			leapForward (a, NN, next_collision_dt); // chaning to time of next collision
			collision(a[whichn],a[whichn+1]); // performing collision 
			
			//collision_num +=1; //count number of collisions
			
			for (int k=0; k<NN; k++){
				positionStep(a[k], dt-next_collision_dt); // updating time to dt after last time
			} 	// this is to keep all time sperations the same to ensure smooth animation

			t += dt;
		}
		count += 1;
		//cout << endl << collision_num; I used this line as the only output when investigating pi
	}
}


int main(){
	int N = 4; // setting number of particles
	double T = 100.0; // setting run time
	particle *a; // defining pointer to particle a
	
	double Dt = 0.005;	// This sets the time incriment between each step. I altered this depending on
						// the number of masses to get a smooth animation as for too great a Dt then the
						// animation didn't look real
	double t = 0.0;
	
	a = new particle [N+2]; // defining an array containing N+2 paricle structures
	
	// setting inital conditions
	for (int i=0; i<=N+1; i++){
		
		// setting walls (using inverse mass of 0 to create solid immovable walls)
		if (i == 0 || i == N+1){ 
			a[i].im = 0;
			a[i].v = 0;
			a[i].x = 1.0*i;
			a[i].r = 0;
		}
		
		// setting particles (here I'm setting 4 particles with same speed and 3 light 1 heavy)
		else { 
			if (i<4){
				a[i].im = 10;
				a[i].v = 1;
			}
			else{
				a[i].im = 0.1;
				a[i].v = -1;
				
			}
	
			a[i].x = 1.0*i;
			a[i].r = 0.1;
			
			
			//a[0].x = 1;  (these lines were the inital conditions for when I investigated pi)
			//a[3].x=1000;
			//a[1].v = 0;
			//a[2].v = -1;
			//a[1].im = 1;
			//a[2].im = 0.00000001;
		}
		v2p(a[i]);
	} 

	run (a, N+2, t, Dt, T); //calling run function

	return 0;
}
