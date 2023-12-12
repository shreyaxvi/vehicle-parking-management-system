#include <ctime>
#include <iostream>

#include <string.h>
#include <cstdlib>

#define EMPTY 0
#define FULL 1



#define MAX_SLOTS 10
#define MAX_BUS_SLOT 2
#define MAX_CAR_SLOT 5
#define MAX_BIKE_SLOT 10
#define MAX_AUTO_SLOT 5

#define BUS_PARKING_RATE 10
#define CAR_PARKING_RATE 5
#define BIKE_PARKING_RATE 2
#define AUTO_PARKING_RATE 5


using namespace std;

struct slot_param_t  
{
	char vehicleNumber[12];
	char ownerName[30];
	char startTimeString[100];
	char endTimeString[100];
	int start_time_hr;
	int end_time_hr;
	bool slot_status;
	
} ;


class parkVehicle
{
private:
	int slot_type;
	int max_slots;
	int rate_per_hr;
	struct slot_param_t  slot_param[MAX_SLOTS];

public:

	parkVehicle(int, int, int);	// constructor declared	
	
    void park_vehicle();
    void remove_vehicle();
    
    friend void check_status(parkVehicle, parkVehicle, parkVehicle, parkVehicle);
};


parkVehicle :: parkVehicle(int x, int y, int z)
{
	slot_type = x;
	max_slots = y;
	rate_per_hr = z;
}


// this function will handle all parking operations
void parkVehicle::park_vehicle( )
{
	int i;
	char vehicle_str[4][6]={"Bus","Car","Auto","Bike"};
	for (i = 0; i < max_slots; i++)
	{
		if(slot_param[i].slot_status == EMPTY)
		{
			// to get local time	
			time_t currTime;
			tm* currTm;
			int hrs;
			char hrStr[5] ;
		
			time(&currTime);
			currTm = localtime(&currTime);
		
			cout << "Enter vehicle number: ";
			cin.sync();
			cin.getline(slot_param[i].vehicleNumber, 12); 
			
			cout << "Enter owner name: ";
		    cin.sync();
		    cin.getline(slot_param[i].ownerName, 30);    
		    
		    strftime(slot_param[i].startTimeString, 50, "DD/MM/YY:HH:MM:SS %d/%m/%Y %H : %M : %S", currTm);
		    
			strftime(hrStr, 50, "%H", currTm);
		    
		    slot_param[i].start_time_hr = atoi(hrStr);
		    slot_param[i].slot_status = FULL;
		
			// Print Receipt
		    cout << "\nHere is your receipt:\n";
		    cout << "*****************************************************************\n";    
		    cout << "Vehicle number: " << slot_param[i].vehicleNumber << endl;
		    cout << "Vehicle owner name: " << slot_param[i].ownerName << endl;
		    cout << "Vehicle parking time: " << slot_param[i].startTimeString << endl;
		    cout << vehicle_str[slot_type-1] <<" parking slot number: " <<  i+1 << endl;
		    cout << "*****************************************************************\n";

			break;    			  			
		}
			
	}
	
	if ((i == max_slots ) )
		cout << "\nSorry! parking slot is not available\n";	
}


// this function will handle all un-parking operations
void parkVehicle::remove_vehicle()
{
    int choose;
    int flag;
    char vehicle_num[12];
    int i;
    

	cout << "Enter vehicle number: ";
	cin.sync();
	cin >> vehicle_num;
	
    	
	for (i=0; i < max_slots; i++)
	{
		if(strcmp(vehicle_num, slot_param[i].vehicleNumber) == 0)
		{
				// to get local time	
			time_t currTime;
			tm* currTm;
			int hrs;
			int total_hrs;
			char hrStr[5] ;
		
			time(&currTime);
			currTm = localtime(&currTime);
		 
		    strftime(slot_param[i].endTimeString, 50, "DD/MM/YY:HH:MM:SS %d/%m/%Y %H : %M : %S", currTm);
		    
			strftime(hrStr, 50, "%H", currTm);
		    
		    slot_param[i].end_time_hr = atoi(hrStr);
		    slot_param[i].slot_status = EMPTY;
		    total_hrs = slot_param[i].end_time_hr - slot_param[i].start_time_hr  + 1;
		
			// Print Receipt
		    cout << "\nHere is your receipt:\n";
		    cout << "*****************************************************************\n";    
		    cout << "Vehicle number: " << slot_param[i].vehicleNumber << endl;
		    cout << "Vehicle owner name: " << slot_param[i].ownerName << endl;
		    cout << "Vehicle entry time: " << slot_param[i].startTimeString << endl;
		    cout << "Vehicle exit time: " << slot_param[i].endTimeString << endl;
		    cout << "Bus parking slot number: " << i + 1 << endl;
		    cout << "No of hours:  " << total_hrs ;
		    cout << "\t\t Charges: Rs  " << total_hrs * rate_per_hr << endl;    
		    cout << "*****************************************************************\n";		
			
			break;    			  			
		}
			
	}
	
	if ((i == max_slots ) )
		cout << "\nSorry! Vehicle not found\n";

}


// This function will check parking status declared as friend
void check_status(parkVehicle bus, parkVehicle car, parkVehicle bike, parkVehicle autos)
{
	
	
	int i;
	int bus_count = 0;
	int car_count = 0;
	int bike_count = 0;
	int auto_count = 0;
	
	char status;
	
    for (i=0; i < bus.max_slots; i++)
	{
		if(bus.slot_param[i].slot_status == FULL)
			bus_count++;			
	}
	
	for (i=0; i < car.max_slots; i++)
	{
		if(car.slot_param[i].slot_status == FULL)
			car_count++;			
	}
	
	for (i=0; i < bike.max_slots; i++)
	{
		if(bike.slot_param[i].slot_status == FULL)
			bike_count++;			
	}
	
	for (i=0; i < autos.max_slots; i++)
	{
		if(bike.slot_param[i].slot_status == FULL)
			auto_count++;			
	}
	
    cout << "\n           -: PARKING STATUS :-\n\n";
    cout << bus_count <<  " Bus parked  | " << MAX_BUS_SLOT - bus_count << " Bus slot is available" << endl;
    cout << car_count <<  " Car parked  | " << MAX_CAR_SLOT - car_count << " Car slot is available" << endl;
    cout << bike_count << " Bike parked | " << MAX_BIKE_SLOT - bike_count << " Bike slot is available" << endl;
    cout << auto_count << " Auto parked | " << MAX_AUTO_SLOT - auto_count << " Auto slot is available" << endl;
    
    cout << "\nBus Slots:  ";
    for (i=0; i < bus.max_slots; i++)
	{
		if(bus.slot_param[i].slot_status == FULL)
			cout << "F	 ";
		else
			cout << "E	 ";			
	}
	cout << endl;	  
 
    cout << "Car Slots:  ";
    for (i=0; i < car.max_slots; i++)
	{
		if(car.slot_param[i].slot_status == FULL)
			cout << "F	 ";
		else
			cout << "E	 ";			
	}
	cout << endl;
	
    cout << "Bike Slots: ";
    for (i=0; i < bike.max_slots; i++)
	{
		if(bike.slot_param[i].slot_status == FULL)
			cout << "F	 ";
		else
			cout << "E	 ";			
	}
	cout << endl;
	
    cout << "Auto Slots: ";
    for (i=0; i < autos.max_slots; i++)
	{
		if(autos.slot_param[i].slot_status == FULL)
			cout << "F	 ";
		else
			cout << "E	 ";			
	}
	cout << endl;		  	  
    
}


// main function create menu for parking stand
int main()
{
    int choose_vehicle, choose_op;
    
    
    static parkVehicle bus(1, MAX_BUS_SLOT, BUS_PARKING_RATE), car(2, MAX_CAR_SLOT, CAR_PARKING_RATE), bike(3, MAX_BIKE_SLOT, BIKE_PARKING_RATE), autos(4, MAX_AUTO_SLOT, AUTO_PARKING_RATE); // implicit call
	    
    do
    {        
        cout<<"\n\t\t\t -----------------------------------------------------------------";
        cout<<"\n\t\t\t |              WELCOME TO VISION 9 PARKING STAND                |";
        cout<<"\n\t\t\t |---------------------------------------------------------------|";
        cout<<"\n\t\t\t |                    Vehicle Parking Rates:                     |";
        cout<<"\n\t\t\t |                                                               |";
        cout<<"\n\t\t\t |  Bus parking per hr  - Rs 10       Car parking per hr - Rs 05 |";
        cout<<"\n\t\t\t |  Bike parking per hr - Rs 02       Auto parking per hr- Rs 05 |";       
        cout<<"\n\t\t\t |                                                               |";
        cout<<"\n\t\t\t |                                                               |";
        cout<<"\n\t\t\t -----------------------------------------------------------------";
		     
     	
        cout << "\n\n\n Choose option: \n";
        
	    cout << " \t 1. Bus\n\t 2. Car\n\t 3. Bike\n\t 4. Auto\n\t 5. ParkingStatus\n\t 6. Exit\n";
	    cin.sync();
	    cin >> choose_vehicle;
	    switch (choose_vehicle)
	    {
	    	// Bus
			case 1:
				cout << "\nSelect Operation: \n\t 1. park_vehicle\n\t 2. remove_vehicle \n";
				cin >> choose_op;
				switch (choose_op)
				{
				    case 1:
				        bus.park_vehicle();
				        break;        
				        
				    case 2:
				        bus.remove_vehicle();
				        break;        

				    default:
				        cout << "\nInvalid option try again\n";
						break;			           
				}
				break;
			// Car
			case 2:
				cout << "\nSelect Operation: \n\t 1. park_vehicle\n\t 2. remove_vehicle \n";
				cin.sync();
				cin >> choose_op;
				switch (choose_op)
				{
				    case 1:
				        car.park_vehicle();
				        break;
										        
				    case 2:
				        car.remove_vehicle();
				        break;        
			        
				    default:
				        cout << "\nInvalid option try again\n";
						break;			           
				}
	    		break;
			// bike
			case 3:
				cout << "\nSelect Operation: \n\t 1. park_vehicle\n\t 2. remove_vehicle \n";
				cin.sync();
				cin >> choose_op;
				switch (choose_op)
				{
				    case 1:
				        bike.park_vehicle();
				        break;
				        
				    case 2:
				        bike.remove_vehicle();
				        break;        

				        
				    default:
				        cout << "\nInvalid option try again\n";
						break;			           
				}
				break;
			// auto
			case 4:
				cout << "\nSelect Operation: \n\t 1. park_vehicle\n\t 2. remove_vehicle \n";
				cin.sync();
				cin >> choose_op;
				switch (choose_op)
				{
				    case 1:
				        autos.park_vehicle();
				        break;
										        
				    case 2:
				        autos.remove_vehicle();
				        break;        
				        
				    default:
				        cout << "\nInvalid option try again\n";
						break;			           
				}				
				break;
				
 			// parking status
			case 5:
			   check_status(bus, car, bike, autos);
			    break;

 			// Exit
			case 6:
			    cout << "\nThank you for using our parking stand\n\n";
			    break;
			   
			default:
			    cout << "\nInvalid option try again\n";			    
			    break;
		} //switch
	} while (choose_vehicle != 6);
    return 0;
} 
