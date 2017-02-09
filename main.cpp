// Monty Hall Problem Simulation to show a the results when switching and when not switching.
// This simulation enacts the exact conditions of the Monty Hall Problem 10,000 times. 
// Also shows a 1/3rd chance of winning when choosing not to switch.
// It is more advantageous to switch, but it is not a 2/3 ratio.
// This Simulation suggest the standard conjecture is incorrect through experimentation.

// This simulation has been Created by John McClain for the purposes of exploration
// into the wonderful world of computer simulation, Have a nice day.

// Results from No Switch (1/3 Chance to Win)
// 1: 3326 wins / 6674 losses
// 2: 3293 wins / 6707 losses
// 3: 3245 wins / 6755 losses
// 4: 3374 wins / 6626 losses
// 5: 3352 wins / 6648 losses

//Results from Switch (1/2 Chance to Win)
// 1: 4981 wins / 5019 losses
// 2: 4969 wins / 5031 losses
// 3: 4988 wins / 5012 losses
// 4: 5028 wins / 4972 losses
// 5: 4949 wins / 5051 losses



#include <iostream>
#include <stdlib.h>
#include <time.h>

struct Door{
    
    bool is_Car;
    bool goat_Revealed;
};

int set_doors(Door* Doors){
    
    for(int i = 0; i < 3; i++){
        Doors[i].goat_Revealed = false;
    }
        
    int car_location = rand()%3;
            
    if(car_location == 0){
        
        Doors[0].is_Car = true;
        Doors[1].is_Car = false;
        Doors[2].is_Car = false;
    }
    
    if(car_location == 1){
        
        Doors[0].is_Car = false;
        Doors[1].is_Car = true;
        Doors[2].is_Car = false;
    }
    
    if(car_location == 2){
        
        Doors[0].is_Car = false;
        Doors[1].is_Car = false;
        Doors[2].is_Car = true;
    }
    
    return car_location;
} //  This does the job of randomly selecting a door to place the "Car" behind.

void reveal_goat(Door* Doors , int Choice){
    
    if(Doors[0].is_Car && Choice == 0){
        
        Doors[(rand()%2 + 1)].goat_Revealed = true;        
    }
    
    if(Doors[0].is_Car && Choice == 1){
        
        Doors[2].goat_Revealed = true;        
    }
    
    if(Doors[0].is_Car && Choice == 2){
        
        Doors[1].goat_Revealed = true;        
    } // First Door Potential Goat Condition    
    //===========================================
    
    if(Doors[1].is_Car && Choice == 0){
        
        Doors[2].goat_Revealed = true;        
    }
    
    if(Doors[1].is_Car && Choice == 1){
        
        bool above = rand()%2;
        
        if(above) {
            
            Doors[2].goat_Revealed = true;  
        } else {
            
            Doors[0].goat_Revealed = true;
        }
    }
    
    if(Doors[1].is_Car && Choice == 2){
        
        Doors[0].goat_Revealed = true;        
    } // Second Door Potential Goat Condition 
    //============================================
    
    if(Doors[2].is_Car && Choice == 0){
        Doors[1].goat_Revealed = true; 
    }
    
    if(Doors[2].is_Car && Choice == 1){
        Doors[0].goat_Revealed = true;        
    }
    
    if(Doors[2].is_Car && Choice == 2){        
        Doors[(2 - rand()%2 )].goat_Revealed = true;        
    } // Third Door Potential Goat Condition
    //===========================================
} // This selects of of the "Not Car" Doors to reveal.

int enact_switch(Door* Doors, int Choice){
    
    if(Doors[0].goat_Revealed) {
                 
        if(Choice == 1){
            
            Choice = 2;
        }else {
            Choice = 1;
            
        }    
    }
        
    if(Doors[1].goat_Revealed ){
                
        if(Choice == 2){
        
            Choice = 1;
        }else {
    
            Choice = 0;          
        }  
    }
    
    if(Doors[2].goat_Revealed ){
                
        if(Choice == 1){
        
            Choice = 0;
        }else {
    
            Choice = 1;          
        }  
    }    
    return Choice;
} // This switches the choice to one of the remaining doors upon request.


int main(int argc, char** argv) {

    Door Doors[3];
    int wins = 0;
    int losses = 0;
    int car_location = 0;
    int Choice = 0;
    bool to_switch = true;
        
    srand(time(NULL)); 
    
    // Init^
    
    for(int i = 0; i < 10000; i++){ // Operate 10000 Times
        
        car_location = set_doors(Doors);
        Choice = rand()%3; // Init Doors, and Make Initial Choice        
        
        reveal_goat(Doors,Choice); // Reveal one "Not_Car" Door
        
        
        if(to_switch) {
            Choice = enact_switch(Doors ,Choice);
        } // Switch if to_switch is set. (Alter to_switch for your test scenarios).
        
        
            if(Choice == car_location) wins++;
            if(Choice != car_location) losses++;
            // Tally wins and losses
    }
        
    std::cout << "Wins: " << wins << "\n";
    std::cout << "Losses: " << losses << "\n";    
    // Report Wins and Losses
    
    return 0;
}

