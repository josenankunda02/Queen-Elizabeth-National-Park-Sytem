

/*GROUP MEMBERS




NANKUNDA JOSEPHINE                21/U/0843 2100700843
MOSES MUGOYA HARRISON             21/U/10447/PS    256708676830
Prajapati Heli Anilkumar          21/X/20194/PS
Mpagi Nelly                       21/U/10649/PS
Muhangi Elioda                    22/U/6342
*/




#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include <avr/eeprom.h>
// KEYPAD CONNECTIONS
#define ROW1 PJ4
#define ROW2 PJ5
#define ROW3 PJ6
#define ROW4 PJ7
#define COL1 PJ2
#define COL2 PJ1
#define COL3 PJ0

#define ROW_PORT PORTJ
#define ROW_DDR DDRJ

#define COL_PORT PORTJ
#define COL_PIN PINJ
#define COL_DDR DDRJ

// LCD for the fridge conneActions
#define RS PG0
#define EN PG2
#define D4 PH4
#define D5 PH5
#define D6 PH6
#define D7 PH7

// LCD commands
#define LCD_CLEAR 0x01
#define LCD_HOME 0x02
#define LCD_ENTRY_MODE 0x06
#define LCD_DISPLAY_ON 0x0E
#define LCD_FUNCTION_RESET 0x30
#define LCD_FUNCTION_SET 0x38

// GATE MOTOR CONNECTIONS
#define MOTOR_PORT PORTC
#define MOTOR_DDR DDRC
#define MOTOR_OPEN_PIN PC2
#define MOTOR_CLOSE_PIN PC3

// Fridge MOTOR CONNECTIONS
#define MOTOR_DISPENSE_WATER_PORT PORTC
#define MOTOR_DISPENSE_WATER_DDR DDRC
#define MOTOR_DISPENSE_WATER_PIN PC2

// MONEY SLOT MOTOR
#define MOTOR_DISPENSE_WATER_PORT PORTC
#define MOTOR_DISPENSE_WATER_DDR DDRC
#define MOTOR_DISPENSE_WATER_PIN PC2

// BUZZER CONNECTIONS
#define BUZZER_PORT PORTC
#define BUZZER_DDR DDRC
#define BUZZER_PIN PC0

// SWITCH CONNECTIONS
#define SWITCH_ENTER PD0
#define SWITCH_OUT PD1

// LED CONNECTIONS
#define LED_PIN PC5
#define LED_PORT PORTC
#define LED_DDR DDRC






//EEPROM ADDRESSES
#define Capacity_Adress 736
#define  Remaining_capacity 752
#define password_Address 768
#define child_fee_address 350
#define adult_fee_address 360
#define water_price_address 370
#define park_capacity_address 380
#define number_plate_address 390
#define tourist_in_park_address 400
#define children_in_park_address 410
#define adults_in_park_address 420
#define total_money_address 430
#define fridge_money_address 440
#define entrance_money_address 450

#define vehicles_address 470
#define vehicles_outside 480
#define drivers_in_park 490






//GLOBAL VARIABLES
int childFee = 10000;  
int adultFee = 20000;  
int water_price=1500;
int tourist_park_capacity = 100;	 
unsigned char Password[6] = "456789";  
int fridge_capacity = 50;
int num_bottles_in_fridge=50;//starting value which is updated

// int childFee=0 ;  //
// int adultFee=0 ;  //
// int water_price=0;
// int tourist_park_capacity=0;	 //
// char maintenancePassword[]={};  // Example password
// int fridge_capacity=0;
// int num_bottles_in_fridge=0;


char numberplate[20][6]={};
int touristsInPark = 0;  // Track the number of tourists in the park
int num_children_in_park=0;
int num_adults_in_park=0;
int num_drivers_in_park=0;
int num_vehicles_in_park=0;
int num_vehicles_outside=0;

int total_money_collected=0;
int fridge_money_collected=0;
int entrance_fee_collected=0;



// Method to write a block of data to EEPROM
void write_data_to_eeprom(const void* data, uint16_t address, size_t size) {
	eeprom_update_block(data, (void*)address, size);
}

// Method to read a block of data from EEPROM
void read_data_from_eeprom(void* data, uint16_t address, size_t size) {
	eeprom_read_block(data, (void*)address, size);
}

void set_configurations(){
	// Store the values of the variables in their corresponding EEPROM addresses
	write_data_to_eeprom( &childFee,child_fee_address, sizeof(childFee));
	write_data_to_eeprom( &adultFee,adult_fee_address, sizeof(adultFee));
	write_data_to_eeprom( &water_price,water_price_address, sizeof(water_price));
	write_data_to_eeprom( &tourist_park_capacity,park_capacity_address, sizeof(tourist_park_capacity));
	write_data_to_eeprom( Password,password_Address, sizeof(Password));
	write_data_to_eeprom( &fridge_capacity,Capacity_Adress, sizeof(fridge_capacity));
	write_data_to_eeprom( numberplate, number_plate_address,sizeof(numberplate));
	write_data_to_eeprom( &touristsInPark,tourist_park_capacity, sizeof(touristsInPark));
	write_data_to_eeprom( &num_children_in_park, children_in_park_address,sizeof(num_children_in_park));
	write_data_to_eeprom( &num_adults_in_park,adults_in_park_address, sizeof(num_adults_in_park));
	write_data_to_eeprom( &num_drivers_in_park,drivers_in_park, sizeof(num_drivers_in_park));
	write_data_to_eeprom( &num_vehicles_in_park,vehicles_address, sizeof(num_vehicles_in_park));
	write_data_to_eeprom( &num_vehicles_outside,vehicles_outside, sizeof(num_vehicles_outside));
	write_data_to_eeprom( &num_bottles_in_fridge, Remaining_capacity,sizeof(num_bottles_in_fridge));
	write_data_to_eeprom( &total_money_collected, total_money_address,sizeof(total_money_collected));
	write_data_to_eeprom( &fridge_money_collected,fridge_money_address, sizeof(fridge_money_collected));
	write_data_to_eeprom( &entrance_fee_collected,entrance_money_address, sizeof(entrance_fee_collected));
	
}

void retrieve_configs(){
	
	// Read data from the corresponding EEPROM addresses and store in variables
	read_data_from_eeprom( &childFee,child_fee_address, sizeof(childFee));
	read_data_from_eeprom( &adultFee,adult_fee_address, sizeof(adultFee));
	read_data_from_eeprom( &water_price,water_price_address, sizeof(water_price));
	read_data_from_eeprom( &tourist_park_capacity,park_capacity_address, sizeof(tourist_park_capacity));
	read_data_from_eeprom( Password, password_Address, sizeof(Password));
	read_data_from_eeprom( &fridge_capacity,Capacity_Adress, sizeof(fridge_capacity));
	read_data_from_eeprom( numberplate,number_plate_address, sizeof(numberplate));
	read_data_from_eeprom( &touristsInPark,tourist_in_park_address, sizeof(touristsInPark));
	read_data_from_eeprom( &num_children_in_park,children_in_park_address, sizeof(num_children_in_park));
	read_data_from_eeprom( &num_adults_in_park,adults_in_park_address, sizeof(num_adults_in_park));
	read_data_from_eeprom( &num_drivers_in_park,drivers_in_park, sizeof(num_drivers_in_park));
	read_data_from_eeprom( &num_vehicles_in_park,vehicles_address, sizeof(num_vehicles_in_park));
	read_data_from_eeprom( &num_vehicles_outside,vehicles_outside, sizeof(num_vehicles_outside));
	read_data_from_eeprom( &num_bottles_in_fridge, Remaining_capacity,sizeof(num_bottles_in_fridge));
	read_data_from_eeprom( &total_money_collected,total_money_address, sizeof(total_money_collected));
	read_data_from_eeprom( &fridge_money_collected,fridge_money_address, sizeof(fridge_money_collected));
	read_data_from_eeprom( &entrance_fee_collected,entrance_money_address, sizeof(entrance_fee_collected));
	
}




#define DEBOUNCE_DELAY_MS 50

volatile uint8_t switchInPressed = 0;
volatile uint8_t switchOutPressed = 0;

int counter = 0;
char *pressed_key = "00000";
int num_bottles = 0;
char *converted_string = "";


/***************************************** GATE LCD********************************************************************************/
void lcd_command(unsigned char command)
{
	PORTA = command;
	PORTB &= ~(1 << 2); // COMMAND MODE
	PORTB &= ~(1 << 1); // WRITE MODE
	PORTB |= (1 << 0);
	_delay_ms(5);
	PORTB &= ~(1 << 0);
}

void lcd_data(unsigned char data)
{
	PORTA = data;
	PORTB |= (1 << 2);	// COMMAND MODE
	PORTB &= ~(1 << 1); // WRITE MODE
	PORTB |= (1 << 0);
	_delay_ms(5);
	PORTB &= ~(1 << 0);
}

void lcd_init()
{
	lcd_command(0x38);
	lcd_command(0x0c);
	lcd_command(0x06);
	lcd_command(0x01);
}

void lcd_print(char info[])
{
	int size = strlen(info);
	for (int i = 0; i < size; i++)
	{
		lcd_data(info[i]);
	}
}
/***************************************** END********************************************************************************/





/***************************************** FRIDGE LCD********************************************************************************/

void lcd_command_f(unsigned char command)
{
	PORTH = command;
	PORTG &= ~(1 << 3); // COMMAND MODE
	PORTG &= ~(1 << 4); // WRITE MODE
	PORTG |= (1 << 5);
	_delay_ms(10);
	PORTG &= ~(1 << 5);
}

void lcd_data_f(unsigned char data)
{
	PORTH = data;
	PORTG |= (1 << 3);	// data MODE
	PORTG &= ~(1 << 4); // WRITE MODE
	PORTG |= (1 << 5);
	_delay_ms(10);
	PORTG &= ~(1 << 5);
}

void lcd_init_f()
{
	lcd_command_f(0x38);
	lcd_command_f(0x0c);
	lcd_command_f(0x06);
	lcd_command_f(0x01);
}

void lcd_print_f(char info[])
{
	int size = strlen(info);
	for (int i = 0; i < size; i++)
	{
		lcd_data_f(info[i]);
	}
}
/***************************************** END********************************************************************************/

//function that counts numbers plates in a row
int countStoredRows(char num_plate[20][6]) {
	int numRows = 0;
	
	for (int i = 0; i < 20; i++) {
		if (num_plate[i][0] == '\0') {
			// '\0' as an indicator of an empty or uninitialized row
			break; 
		}
		numRows++;
	}

	return numRows;
}






/***************************************** VIRTUAL TERMINAL********************************************************************************/
// Define baud rate and calculations
#define F_CPU 8000000UL
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void USART_Init()
{
	// Set baud rate
	UBRR0H = (unsigned char)(BAUD_PRESCALE >> 8);
	UBRR0L = (unsigned char)(BAUD_PRESCALE);

	// Enable receiver and transmitter
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	// Set frame format: 8 data bits, 1 stop bit, no parity
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}



void USART_Transmit(unsigned char data[])
{
	// Wait for empty transmit buffer
	int length = strlen(data);

	for (int k = 0; k < length; k++){
		while (!(UCSR0A & (1 << UDRE0)));

		// Put data into buffer, sends the data
		UDR0 = data[k];
	}
}


//function that transmits characters
void USART_TransmitChar(unsigned char data)
{
	// Wait for empty transmit buffer

	while (!(UCSR0A & (1 << UDRE0)));
		

	// Put data into buffer, sends the data
	UDR0 = data;
}

// function that receives strings
unsigned char USART_Receive(){
	// Wait for data to be received
	while (!(UCSR0A & (1 << RXC0)))	;

	// Get and return received data from buffer
	return UDR0;
}


//function that receives integers
int USART_ReceiveInt() {
	char buffer[10];  // Assume an integer will not be longer than 10 digits
	int i = 0;

	while (1) {
		while ((UCSR0A & (1 << RXC0)) == 0);

		char receivedChar = UDR0;
		USART_TransmitChar(receivedChar);

		if (receivedChar == '\r' || receivedChar == '\n') {
			buffer[i] = '\0'; // Null-terminate the string
			break;
		} else {
			buffer[i] = receivedChar;
			i++;
		}
	}

	int intValue = atoi(buffer); // Convert the received string to an integer
	return intValue;
}

/***********************************************END***************************/



/***********************************************LOGIC FUNCTIONS FOR THE SWITCH TO HANDLE MENU***************************/
void registerTourists(){
	USART_Transmit("1) Register Incoming car\r\n");
	USART_Transmit("2) Register Outgoing Car\r\n");
	
    unsigned char choose = USART_Receive();

switch (choose)
{
	case '1':
	//register incoming Car
	Incoming_Car();
	break;
	
	case '2':
	// Register outgoing car
	Outgoing_Car();
	break;
	
	default:
	USART_Transmit("INVALID INPUT");
	break;
}

}
void Incoming_Car(){
	 //REGISTER TOURISTS AND INCREAMENT TOURISTS IN PARK
	read_data_from_eeprom( &num_vehicles_outside,vehicles_outside, sizeof(num_vehicles_outside));
	read_data_from_eeprom( &childFee,child_fee_address, sizeof(childFee));
	read_data_from_eeprom( &adultFee,adult_fee_address, sizeof(adultFee));
	read_data_from_eeprom( &tourist_park_capacity,park_capacity_address, sizeof(tourist_park_capacity));
	read_data_from_eeprom( numberplate,number_plate_address, sizeof(numberplate));
	read_data_from_eeprom( &touristsInPark,tourist_in_park_address, sizeof(touristsInPark));
	read_data_from_eeprom( &num_children_in_park,children_in_park_address, sizeof(num_children_in_park));
	read_data_from_eeprom( &num_adults_in_park,adults_in_park_address, sizeof(num_adults_in_park));
	read_data_from_eeprom( &num_drivers_in_park,drivers_in_park, sizeof(num_drivers_in_park));
	read_data_from_eeprom( &num_vehicles_in_park,vehicles_address, sizeof(num_vehicles_in_park));
	read_data_from_eeprom( &total_money_collected,total_money_address, sizeof(total_money_collected));
	read_data_from_eeprom( &entrance_fee_collected,entrance_money_address, sizeof(entrance_fee_collected));
	
	
	if (touristsInPark==tourist_park_capacity){
	USART_Transmit("\r\n");
	USART_Transmit("Park is full can't register");
	
	lcd_command(0x01); // clear screen
	lcd_command(0x80);
	lcd_print("PARK FULL");
	_delay_ms(100);
	num_vehicles_outside + 1;
	
	//update cars outside
	write_data_to_eeprom( &num_vehicles_outside,vehicles_outside, sizeof(num_vehicles_outside));
	}else{
		
	USART_Transmit("REGISTER INCOMING TOURISTS\r\n");
	
	lcd_command(0x01); // clear screen
	lcd_command(0x80);
	lcd_print("REGISTERING");
	_delay_ms(100);
	USART_Transmit("Number of children: ");
	int childn = USART_ReceiveInt();
	
	USART_Transmit("Number of Adults: ");
	int adults = USART_ReceiveInt();
	
	
	USART_Transmit("Enter Numberplate: ");
	char num_plate;
	int plate_size=countStoredRows(numberplate);
	for (int i=0; i<6; i++)	{
		num_plate=USART_Receive();
		numberplate[plate_size][i]=num_plate;
		USART_TransmitChar(num_plate);
		
	}
	
	//CALCULATIONS
	int chils_cash= childFee * childn;
	int ad_cash= adultFee * adults;
	touristsInPark += childn + adults;
	num_children_in_park += childn;
	num_adults_in_park += adults;
	num_drivers_in_park += 1;
	num_vehicles_in_park += 1;
	total_money_collected += chils_cash + ad_cash;
	entrance_fee_collected +=  chils_cash + ad_cash;
	
	//UPDATE THE EEPROM
	write_data_to_eeprom( numberplate, number_plate_address,sizeof(numberplate));
	write_data_to_eeprom( &touristsInPark,tourist_park_capacity, sizeof(touristsInPark));
	write_data_to_eeprom( &num_children_in_park, children_in_park_address,sizeof(num_children_in_park));
	write_data_to_eeprom( &num_adults_in_park,adults_in_park_address, sizeof(num_adults_in_park));
	write_data_to_eeprom( &num_drivers_in_park,drivers_in_park, sizeof(num_drivers_in_park));
	write_data_to_eeprom( &num_vehicles_in_park,vehicles_address, sizeof(num_vehicles_in_park));
	write_data_to_eeprom( &total_money_collected, total_money_address,sizeof(total_money_collected));
	write_data_to_eeprom( &entrance_fee_collected,entrance_money_address, sizeof(entrance_fee_collected));
	
	USART_Transmit("\r\n");
	USART_Transmit("REGISTRATION SUCCESSFUL...\r\n");
	
	lcd_command(0x01); // clear screen
	lcd_command(0x80);
	lcd_print("DONE ENTER");
	_delay_ms(100);
}
}


 void Outgoing_Car(){
	 
	 //REGISTER TOURISTS AND DECREAMENT TOURISTS IN PARK
	 read_data_from_eeprom( &num_vehicles_outside,vehicles_outside, sizeof(num_vehicles_outside));
	 read_data_from_eeprom( &tourist_park_capacity,park_capacity_address, sizeof(tourist_park_capacity));
	 read_data_from_eeprom( numberplate,number_plate_address, sizeof(numberplate));
	 read_data_from_eeprom( &touristsInPark,tourist_in_park_address, sizeof(touristsInPark));
	 read_data_from_eeprom( &num_children_in_park,children_in_park_address, sizeof(num_children_in_park));
	 read_data_from_eeprom( &num_adults_in_park,adults_in_park_address, sizeof(num_adults_in_park));
	 read_data_from_eeprom( &num_drivers_in_park,drivers_in_park, sizeof(num_drivers_in_park));
	 read_data_from_eeprom( &num_vehicles_in_park,vehicles_address, sizeof(num_vehicles_in_park));
	 
	 if (touristsInPark==tourist_park_capacity)
	 {  
		 num_vehicles_outside - 1;
		 
		 //update cars outside
		 write_data_to_eeprom( &num_vehicles_outside,vehicles_outside, sizeof(num_vehicles_outside));
	 } 
	 else
	 {
		
		USART_Transmit("REGISTER OUTGOING TOURISTS\r\n");
		
		lcd_command(0x01); // clear screen
		lcd_command(0x80);
		lcd_print("REGISTERING");
		_delay_ms(100);
		USART_Transmit("Number of children: ");
		int child = USART_ReceiveInt();
		
		USART_Transmit("Number of Adults: ");
		int adult = USART_ReceiveInt();
		
		
		USART_Transmit("Enter Numberplate: ");
		char num_plate;
		int plate_size=countStoredRows(numberplate);
		for (int i=0; i<6; i++)	{
			num_plate=USART_Receive();
			numberplate[plate_size][i]=num_plate;
			USART_TransmitChar(num_plate);
			
		}
		
		//CALCULATIONS
		
		touristsInPark -= child + adult;
		num_children_in_park -= child;
		num_adults_in_park -= adult;
		num_drivers_in_park -= 1;
		num_vehicles_in_park -= 1;
		//numberplate -=num_plate;

		
		//UPDATE THE EEPROM
		write_data_to_eeprom( numberplate, number_plate_address,sizeof(numberplate));
		write_data_to_eeprom( &touristsInPark,tourist_park_capacity, sizeof(touristsInPark));
		write_data_to_eeprom( &num_children_in_park, children_in_park_address,sizeof(num_children_in_park));
		write_data_to_eeprom( &num_adults_in_park,adults_in_park_address, sizeof(num_adults_in_park));
		write_data_to_eeprom( &num_drivers_in_park,drivers_in_park, sizeof(num_drivers_in_park));
		write_data_to_eeprom( &num_vehicles_in_park,vehicles_address, sizeof(num_vehicles_in_park));
		
		
		USART_Transmit("\r\n");
		USART_Transmit("REGISTRATION SUCCESSFUL.. BYE...\r\n"); 
		
		lcd_command(0x01); // clear screen
		lcd_command(0x80);
		lcd_print("DONE EXIT");
		_delay_ms(100);
	 }
}

void number_bottles_in_fridge(){
	
	read_data_from_eeprom( &num_bottles_in_fridge, Remaining_capacity,sizeof(num_bottles_in_fridge));
	char bottles[4];
	sprintf(bottles, "%d", num_bottles_in_fridge);
	USART_Transmit("Remaining bottles are:..");
	USART_Transmit(bottles);
	USART_Transmit("\r\n");
	
}

void checkTouristsCount(){
	read_data_from_eeprom( &num_children_in_park,children_in_park_address, sizeof(num_children_in_park));
	read_data_from_eeprom( &num_adults_in_park,adults_in_park_address, sizeof(num_adults_in_park));

	char nc[5];
	char na[5];
	
	sprintf(nc, "%d", num_children_in_park);
	sprintf(na, "%d", num_adults_in_park);
	
	USART_Transmit("\r\n");
	USART_Transmit("Children in park: ");
	USART_Transmit(nc);
	USART_Transmit("\r\n");
	
	USART_Transmit("Adults in park: ");
	USART_Transmit(na);
	USART_Transmit("\r\n");

}

void checkVehiclesInPark(){
	//counting them
	read_data_from_eeprom( &num_vehicles_in_park,vehicles_address, sizeof(num_vehicles_in_park));
	char vehicles[4];
	sprintf(vehicles, "%d", num_vehicles_in_park);
	USART_Transmit("Vehicles  inside the park are:..");
	USART_Transmit(vehicles);
	USART_Transmit("\r\n");
//print their number plates
	read_data_from_eeprom( numberplate,number_plate_address, sizeof(numberplate));
	int pl_size = countStoredRows(numberplate);
	for (int a=0; a<pl_size;a++){
		for (int j=0; j <6; j++){
			USART_TransmitChar(numberplate[a][j]); 
		}
		USART_Transmit(" ");
	}
	
}

void checkCollectedFunds(){
	// Implement code to check collected funds
	read_data_from_eeprom( &fridge_money_collected,fridge_money_address, sizeof(fridge_money_collected));
	read_data_from_eeprom( &entrance_fee_collected,entrance_money_address, sizeof(entrance_fee_collected));
	
	char fridge_money_str[8];
	char entrance_money_str[8];
	
	sprintf(fridge_money_str, "%d", fridge_money_collected);
	sprintf(entrance_money_str, "%d", entrance_fee_collected);
	// Send the count information via UART
	
	USART_Transmit("Fridge money collected: UGX ");
	USART_Transmit(fridge_money_str);
	USART_Transmit("\r\n");
	
	USART_Transmit("Entrance fee fund collected: UGX ");
	USART_Transmit(entrance_money_str);
	USART_Transmit("\r\n");
}

void checkDriversCount()
{
	// Get number of drivers with the number plates
	
	read_data_from_eeprom( &num_drivers_in_park,drivers_in_park, sizeof(num_drivers_in_park));
	char drivers[4];
	sprintf(drivers, "%d", num_drivers_in_park);
	USART_Transmit("Drivers in the park are:..");
	USART_Transmit(drivers);
	USART_Transmit("\r\n");
	
	read_data_from_eeprom( numberplate,number_plate_address, sizeof(numberplate));
	int pl_size = countStoredRows(numberplate);
	for (int a=0; a<pl_size;a++){
		for (int j=0; j <6; j++){
			USART_TransmitChar(numberplate[a][j]);
		}
		USART_Transmit(" ");
	}
}

 void replenishFridge() {
	read_data_from_eeprom( Password, password_Address, sizeof(Password));
	read_data_from_eeprom( &fridge_capacity,Capacity_Adress, sizeof(fridge_capacity));
	read_data_from_eeprom( &num_bottles_in_fridge, Remaining_capacity,sizeof(num_bottles_in_fridge));
	
	
	USART_Transmit("Enter your maintenance password: \r\n");
	char password_array[6];
	for (int i=0; i<6; i++)	{
		password_array[i] = USART_Receive();
		USART_TransmitChar(password_array[i]);
	}
	
	int password_equality= 1;
	int password_len=sizeof(Password)/sizeof(Password[0]);
	for(int j=0; j < password_len; j++){
		if (Password[j] != password_array[j]){
			password_equality =0;
			break;
		}
	}
	
	if(password_equality==1){
		if (fridge_capacity==num_bottles_in_fridge)	{
			USART_Transmit("\r\n");
			USART_Transmit("Fridge already full to capacity. You can't add more bottles.\r\n");
		}else{
			USART_Transmit("\r\n");
			USART_Transmit("Enter number of bottles to add to fridge: \r\n");
			int bottles_to_add= USART_ReceiveInt();
			if ( (bottles_to_add + num_bottles_in_fridge)>fridge_capacity )	{
				USART_Transmit("\r\n");
				USART_Transmit("Too many! Enter less bottles. You can't exceed capacity.\r\n");
			}else{
				num_bottles_in_fridge +=bottles_to_add;
				write_data_to_eeprom( &num_bottles_in_fridge, Remaining_capacity,sizeof(num_bottles_in_fridge));
				
				USART_Transmit("\r\n");
				USART_Transmit("Fridge replenished successfully.\r\n");
			}
			
		}
	}else{
		USART_Transmit("\r\n");
		USART_Transmit("Incorrect password !!! \r\n");
	}
	
	
}

void checkCarsWaitingOutside()
{
	//  code to check cars waiting outside
	read_data_from_eeprom( &num_vehicles_outside,vehicles_outside, sizeof(num_vehicles_outside));
	char cars[4];
	sprintf(cars, "%d", num_vehicles_outside);
	USART_Transmit("Cars waiting outside are:..");
	USART_Transmit(cars);
	USART_Transmit("\r\n");
	
}

void checkParkStatus()
{
	// Implement code to check park status
	read_data_from_eeprom( &tourist_park_capacity,park_capacity_address, sizeof(tourist_park_capacity));
	read_data_from_eeprom( &touristsInPark,tourist_in_park_address, sizeof(touristsInPark));
	if (touristsInPark==tourist_park_capacity)
	{
		USART_Transmit("Park if full");
	} 
	else
	{
		USART_Transmit("Park is not full");
	}
}
/****************************************************END*******************/




/************************************ Display virtual console menu****************************/
void handleSerialConsole()
{
	// menu for serial console 
	
	USART_Transmit("\r\n        QUEEN ELIZABETH NATIONAL PARK\r\n");
	USART_Transmit("Select an option:\r\n");

	USART_Transmit("1. Register Tourists\r\n");

	USART_Transmit("2.Tourists Categorized by age group\r\n");

	USART_Transmit("3. Money collected by park\r\n");

	USART_Transmit("4. Vehicles in the park\r\n");

	USART_Transmit("5. Replenish fridge\r\n");

	USART_Transmit("6. Number of Bottles in the fridge\r\n");

	USART_Transmit("7. Cars waiting outside gate\r\n");
	
	USART_Transmit("8.Check drivers in park \r\n");

	USART_Transmit("9.Is Park full? \r\n");

	// User input

	unsigned char choice = USART_Receive();

	switch (choice)
	{
	case '1':
		// Register to display
		registerTourists();
		break;
	case '2':
		// Tourists categorized by group
		checkTouristsCount();

		break;
	case '3':

		// Money collected
		checkCollectedFunds();
		break;
	case '4':
		// Vehicles in the park
		checkVehiclesInPark();
		break;
	case '5':
		// Replenish fridge
		replenishFridge();
		break;
	case '6':
		// Number of bottles in the fridge
		number_bottles_in_fridge();
		break;

	case '7':
		// Cars waiting outside gate
		checkCarsWaitingOutside();
	case '8':
		// Check DRIVERS IN PARK
		checkDriversCount();

	case '9':
		// Check if park is full
		checkParkStatus();

	default:
		// Handle invalid choice
		USART_Transmit("INVALID INPUT");
		break;
	}
	
}

/************************************ END****************************/





/***************************************** KEY PAD********************************************************************************/
char *int_to_string(int value)
{
	sprintf(converted_string, "%d", value); // Convert integer to string
	return converted_string;
}

char *keypad_to_lcd()
{

	while (1)
	{
		// get pressed key & print on LCD
		int key = read_keypad();

		if (key != -1)
		{

			// convert key to string
			pressed_key = int_to_string(key);

			lcd_print_f(pressed_key);

			_delay_ms(50);
			break;
		}
	}

	return pressed_key;
}

void keypad_init(void)
{
	// Set row pins to output
	ROW_DDR |= (1 << ROW1) | (1 << ROW2) | (1 << ROW3) | (1 << ROW4);

	// Set column pins to input
	COL_DDR &= ~((1 << COL1) | (1 << COL2) | (1 << COL3));

	// Enable pull-up resistors on column pins
	COL_PORT |= (1 << COL1) | (1 << COL2) | (1 << COL3);
}

int read_keypad(void)
{
	int row_pins[] = {ROW1, ROW2, ROW3, ROW4};
	int col_pins[] = {COL1, COL2, COL3};
	int key = -1;

	// Scan each row
	for (int i = 0; i < 4; i++)
	{
		// Set current row pin to low
		ROW_PORT &= ~(1 << row_pins[i]);

		// Check which column pin is low
		for (int j = 0; j < 3; j++)
		{

			if ((COL_PIN & (1 << col_pins[j])) == 0)
			{
				if ((row_pins[i] == ROW4) && (col_pins[j] == COL2)) // when 0 is pressed
				{
					key = 0;
				}
				else
				{
					key = (i * 3) + j + 1;
				}
			}
		}

		// Set current row pin to high
		ROW_PORT |= (1 << row_pins[i]);

		// If a key was pressed, exit the loop
		if (key != -1)
		{
			break;
		}
	}

	return key;
}
/***************************************** END********************************************************************************/


/***************************************** ISR********************************************************************************/
// Interrupt Service Provider to handle interrupt for Enter Switch
ISR(INT0_vect)
{

	if (!switchInPressed)
	{
		switchInPressed = 1;			   // Flag to avoid re-triggering during
		BUZZER_PORT |= (1 << BUZZER_PIN);  // Turn on the buzzer
		_delay_ms(100);					   // Buzzer sound for 1 second
		BUZZER_PORT &= ~(1 << BUZZER_PIN); // Turn off the buzzer
		_delay_ms(1);
		lcd_command(0x80);
		lcd_print(" Incoming Tourist ");
		lcd_command(0xc0);
		lcd_print(" Vehicle ");

		_delay_ms(100);
		// Open the gate for 3 seconds
		MOTOR_PORT |= (1 << MOTOR_OPEN_PIN);
		_delay_ms(3000);
		
		lcd_command(0x01); // clear screen
		lcd_command(0x80);
		lcd_print("GATE OPENING");
		_delay_ms(100);
		MOTOR_PORT &= ~(1 << MOTOR_OPEN_PIN);

		// Close the gate for 2 seconds
		MOTOR_PORT |= (1 << MOTOR_CLOSE_PIN);
		_delay_ms(2000);
		
		lcd_command(0x01); // clear screen
		lcd_command(0x80);
		lcd_print("GATE CLOSING");
		_delay_ms(100);
		MOTOR_PORT &= ~(1 << MOTOR_CLOSE_PIN);

		switchInPressed = 0; // Clear the switch flag for the next press
	}
}

// Interrupt Service Provider to handle interrupt for Outgoing Switch

ISR(INT1_vect)
{

	if (!switchOutPressed)
	{
		switchOutPressed = 1;			   // Flag to avoid re-triggering during De bounce
		BUZZER_PORT |= (1 << BUZZER_PIN);  // Turn on the buzzer
		_delay_ms(100);					   // Buzzer sound for 1 second
		BUZZER_PORT &= ~(1 << BUZZER_PIN); // Turn off the buzzer

		// Open the gate for 3 seconds
		MOTOR_PORT |= (1 << MOTOR_OPEN_PIN);
		_delay_ms(3000);
		MOTOR_PORT &= ~(1 << MOTOR_OPEN_PIN);

		// Close the gate for 2 seconds
		MOTOR_PORT |= (1 << MOTOR_CLOSE_PIN);
		_delay_ms(2000);
		MOTOR_PORT &= ~(1 << MOTOR_CLOSE_PIN);

		switchOutPressed = 0; // Clear the switch flag for the next press
	}
}

/*****************************************END********************************************************************************/


/***************************************** FRIDGE LOGIC********************************************************************************/
void dispense_bottles()
{
	PORTH |= (1 << PH0);
	lcd_command_f(0x01); // clear screen
	lcd_command(0x80);
	lcd_print_f("GET SOME WATER");
	_delay_ms(100);
	// enter the number of bottles
	lcd_print_f("Bottles ? : ");
	

	int bots = read_keypad();
	while (bots == -1){
		bots = read_keypad();	
	}
	char bts[3];
	sprintf(bts, "%d", bots);
	lcd_print_f(bts);

	lcd_command_f(0xC0); // cursor down

	// calculate bill
	/*int bill = atoi(num_bottles) * 1500;*/
	int bill = 0;
	bill = bots * 1500;
	char bill_string[8];
	sprintf(bill_string, "%d", bill);

	// printing total amount of money
	lcd_print_f("Bill: UGX ");
	/*lcd_print_f(int_to_string(bill));*/
	lcd_print_f(bill_string);
	_delay_ms(2000);
	lcd_command_f(0x01);
	lcd_command_f(0x80);
	// enter the number of bottles
	lcd_print_f("1. Pay cash 2:EXIT");

	int choice = read_keypad();
	while (choice == -1)
	{
		choice = read_keypad();
	}
	char cc[3];
	sprintf(cc, "%d", choice);
	lcd_command_f(0xc0);
	lcd_print_f(cc);
	_delay_ms(2000);

	if (choice == 1){
		lcd_command_f(0x01); // Clear screen
		lcd_command_f(0x80); // set cursor to first line/row
		lcd_print_f("Opening money slot");
		for (int i=0; i<3; i++)	{
			PORTF |=(1<<1);
			_delay_ms(2000);
			PORTF &= ~(1<<1);
			_delay_ms(1000);
		}
		
		lcd_command_f(0xc0); // set cursor to first line/row
		lcd_print_f("Insert your money");
		_delay_ms(2000);
		
		// Read data from the corresponding EEPROM addresses and store in variables
		read_data_from_eeprom( &water_price,water_price_address, sizeof(water_price));
		
		read_data_from_eeprom( &num_bottles_in_fridge, Remaining_capacity,sizeof(num_bottles_in_fridge));
		read_data_from_eeprom( &total_money_collected,total_money_address, sizeof(total_money_collected));
		read_data_from_eeprom( &fridge_money_collected,fridge_money_address, sizeof(fridge_money_collected));
				
		
		int bottle_cash= water_price *  bots;
		
		num_bottles_in_fridge -=bots;
		fridge_money_collected += bottle_cash;
		total_money_collected += bottle_cash;
		
		write_data_to_eeprom( &num_bottles_in_fridge, Remaining_capacity,sizeof(num_bottles_in_fridge));
		write_data_to_eeprom( &total_money_collected,total_money_address, sizeof(total_money_collected));
		write_data_to_eeprom( &fridge_money_collected,fridge_money_address, sizeof(fridge_money_collected));
		
		lcd_command_f(0x01); // Clear screen
		lcd_command_f(0x80); // set cursor to first line/row
		lcd_print_f("Dispensing bottles..");
		
		for (int j=0; j<bots; j++)	{
			PORTF |= (1<<5);
			_delay_ms(1000);
			PORTF &=~(1<<5);
			_delay_ms(2000);
			
		}
		
		lcd_command_f(0xc0); // set cursor to first line/row
		lcd_print_f("Thank you.");
		
	}else if (choice == 2){
		lcd_command_f(0x01); // Clear screen
		lcd_command_f(0x80); // set cursor to first line/row
		// enter the number of bottles
		lcd_print_f("TRANSACTION CANCELLED");
		_delay_ms(1000);
	}else{
		lcd_command_f(0x01);
		lcd_command_f(0x80);
		// enter the number of bottles
		lcd_print_f("INVALID INPUT");
		_delay_ms(1000);
	}
}

/***************************************** END********************************************************************************/


int main(void)
{

	USART_Init();


	// data direction for the gate LCD
	DDRB = 0xFF;
	DDRA = 0xFF;
	DDRH = 0xFF;
	DDRG = 0xFF;
	
	//motor DDR
	DDRF =0xFF;

	// Initialize the necessary ports
	MOTOR_DDR |= (1 << MOTOR_OPEN_PIN) | (1 << MOTOR_CLOSE_PIN);
	BUZZER_DDR |= (1 << BUZZER_PIN);

	// Initialize the switch pin (PD0) as an input with a pull-up resistor
	PORTD |= (1 << SWITCH_ENTER) | (1 << SWITCH_OUT);
	DDRD &= ~(1 << SWITCH_ENTER) | (1 << SWITCH_OUT);

	// Initialize External Interrupt 0 (PD0)

	EIMSK |= (1 << INT1) | (1 << INT0) | (1 << INT4); // Enable external interrupt 0
	EICRA |= (1 << ISC01);							  // Falling edge generates an interrupt FOR INT0
	EICRB |= (1 << ISC41);							  // Falling edge generates an interrupt FOR INT4

	// Initialize External Interrupt 1 (PD1)
	EICRA |= (1 << ISC11); // Falling edge generates an interrupt for INT1

	sei(); // Enable global interrupts

	lcd_init();
	lcd_init_f();
	keypad_init();

	set_configurations();
	while (1)
	{

		USART_Init();
		handleSerialConsole();
		
	}
	return 0;
}

/***************************************** INTERRUPT TO GET FRIDGE ON********************************************************************************/
ISR(INT4_vect)
{
	dispense_bottles();
}
