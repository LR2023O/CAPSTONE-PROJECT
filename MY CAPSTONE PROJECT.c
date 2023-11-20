#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int id;
    char username[20];
    char password[10];
} Employee;

typedef struct
{
    int bus_id;
    char bus_name[30];
    char bus_route[30];
    int total_seats;
    int available_seats;
    int seats[10][5];
} Bus;

typedef struct
{
    int booking_id;
    int bus_id;
    int employee_id;
    int num_seats;
    int booked_seats[5];  // Assuming a maximum of 5 seats in one booking
} Booking;

// Function to save bus data to a file
void saveBusData(Bus buses[], int num_buses, const char *filename)
{
    FILE *file = fopen("buses.txt","w");
    if (file != NULL)
    {
        fwrite(buses, sizeof(Bus), num_buses, file);
        fclose(file);
    }
    else
    {
        printf("Error opening file for writing bus data.\n");
    }
}

// Function to load bus data from a file
void loadBusData(Bus buses[], int *num_buses, const char *filename)
{
    FILE *file = fopen("buses.txt","r");
    if (file != NULL)
    {
        fread(buses, sizeof(Bus), 5, file);
        fclose(file);
        *num_buses = 5;
    }
    else
    {
        printf("Error opening file for reading bus data.\n");
    }
}

// Function to save booking data to a file
void saveBookingData(Booking bookings[], int num_bookings, const char *filename)
{
    FILE *file = fopen("bookings.txt","w");
    if (file != NULL)
    {
        fwrite(bookings, sizeof(Booking), num_bookings, file);
        fclose(file);
    }
    else
    {
        printf("Error opening file for writing booking data.\n");
    }
}

// Function to load booking data from a file
void loadBookingData(Booking bookings[], int *num_bookings, const char *filename)
{
    FILE *file = fopen("bookings.txt","r");
    if (file != NULL)
    {
        fread(bookings, sizeof(Booking), 5, file);
        fclose(file);
        *num_bookings = 5;
    }
    else
    {
        printf("Error opening file for reading booking data.\n");
    }
}


// Function to display available buses
void displayBuses(Bus buses[], int num_buses)
{
    printf("---------------------------------------------------------------------------------------------------------------------\n");
    printf("---------------------------------------------------------------------------------------------------------------------\n");
    printf("__________________Available Buses:________________________\n");
    for (int i = 0; i < num_buses; i++)
    {
        printf("Bus ID: %d\n", *&buses[i].bus_id);
        printf("Bus Name: %s\n", *&buses[i].bus_name);
        printf("Bus route: %s\n", *&buses[i].bus_route);
        printf("Total Seats: %d\n", *&buses[i].total_seats);
        printf("Available Seats: %d\n", *&buses[i].available_seats);
        printf("\n");
        printf("==================================================================================================================\n");
    }
}

// Function to make a booking
int makeBooking(Booking bookings[], int num_bookings, Bus buses[], int num_buses, int bus_id, int employee_id, int num_seats)
{
    for (int i = 0; i < num_buses; i++)
    {
        if (buses[i].bus_id == bus_id)
        {
            if (buses[i].available_seats >= num_seats)
            {
                // Find available seats
                int booked_seats[5];
                int seats_index = 0;
                for (int row = 0; row < 10 && seats_index < num_seats; row++)
                {
                    for (int col = 0; col < 5 && seats_index < num_seats; col++)
                    {
                        if (buses[i].seats[row][col] == 0)
                        {
                            booked_seats[seats_index] = row * 5 + col + 1;
                            buses[i].seats[row][col] = 1; // Mark the seat as booked
                            seats_index++;
                        }
                    }
                }

                if (seats_index == num_seats)
                {
                    buses[i].available_seats -= num_seats;

                    Booking newBooking;
                    newBooking.booking_id = num_bookings + 1;
                    newBooking.bus_id = bus_id;
                    newBooking.employee_id = employee_id;
                    newBooking.num_seats = num_seats;
                    for (int j = 0; j < num_seats; j++)
                    {
                        newBooking.booked_seats[j] = booked_seats[j];
                    }
                    bookings[num_bookings] = newBooking;
                    return newBooking.booking_id;
                }
            }
            else
            {
                printf("Not enough available seats on this bus.\n");
                return -1;
            }
        }
    }
    printf("Bus not found.\n");
    return -1;
}
// Function to book a specific seat in a specific bus
int bookSpecificSeat(Booking bookings[], int num_bookings, Bus buses[], int num_buses, int bus_id, int employee_id, int seat_row, int seat_col)
{
    for (int i = 0; i < num_buses; i++)
    {
        if (buses[i].bus_id == bus_id)
        {
            if (seat_row >= 0 && seat_row < 10 && seat_col >= 0 && seat_col < 5 && buses[i].seats[seat_row][seat_col] == 0)
            {
                buses[i].seats[seat_row][seat_col] = 1; // Mark the seat as booked
                buses[i].available_seats--;

                Booking newBooking;
                newBooking.booking_id = num_bookings + 1;
                newBooking.bus_id = bus_id;
                newBooking.employee_id = employee_id;
                newBooking.num_seats = 1;
                newBooking.booked_seats[0] = seat_row * 5 + seat_col + 1;

                bookings[num_bookings] = newBooking;
                return newBooking.booking_id;
            }
            else
            {
                printf("Invalid seat selection or seat already booked.\n");
                return -1;
            }
        }
    }

    printf("Bus not found.\n");
    return -1;
}

// Function to display bookings
void displayBookings(Booking bookings[], int num_bookings)
{
    printf("\n");
    printf("-------------------------------------------------------------------------\n");
    printf("_____________________________Bookings:___________________________________\n");
    for (int i = 0; i < num_bookings; i++)
    {
        printf("Booking ID: %d\n", bookings[i].booking_id);
        printf("Bus ID: %d\n", bookings[i].bus_id);
        printf("Employee ID: %d\n", bookings[i].employee_id);
        printf("Number of Seats: %d\n", bookings[i].num_seats);
        printf("\n");
    printf("==========================================================================\n");
    }
}

int login(Employee Employees[], int num_Employees)
{
    char username[20], password[10];
    printf("______________LOGIN__________________\n");
    printf("Username:");
    scanf("%s", username);
    printf("Password:");
    scanf("%s", password);
    for (int i = 0; i < num_Employees; i++)
    {
        if (strcmp(Employees[i].username, username) == 0 && strcmp(Employees[i].password, password) == 0)
        {
            return Employees[i].id;
        }
    }
    return -1;
}
// Function to add a new bus
int addBus(Bus buses[], int num_buses, int bus_id, const char bus_name[], const char bus_route[], int total_seats, int available_seats)
{
    if (num_buses < 5)
    {
        buses[num_buses].bus_id = bus_id;
        strcpy(buses[num_buses].bus_name, bus_name);
        strcpy(buses[num_buses].bus_route, bus_route);
        buses[num_buses].total_seats = total_seats;
        buses[num_buses].available_seats = available_seats;

        // Initialize seats for the new bus
        for (int row = 0; row < 10; row++)
        {
            for (int col = 0; col < 5; col++)
            {
                buses[num_buses].seats[row][col] = 0; // Initialize all seats as available
            }
        }

        return 1; // Indicate success
    }
    else
    {
        printf("Cannot add more buses. Maximum number of buses reached.\n");
        return 0; // Indicate failure
    }
}

int removeBus(Bus buses[], int num_buses, int bus_id)
{
    int index = -1;
    for (int i = 0; i < num_buses; i++)
    {
        if (buses[i].bus_id == bus_id)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        for (int i = index; i < num_buses - 1; i++)
        {
            buses[i] = buses[i + 1];
        }
        return 1; // Indicate success
    }
    else
    {
        printf("Bus not found.\n");
        return 0; // Indicate failure
    }
}
// Function to update bus details by bus ID
void updateBus(Bus buses[], int num_buses, int bus_id, const char newBusName[],const char newbusroute[], int newTotalSeats, int newAvailableSeats)
{
    for (int i = 0; i < num_buses; i++)
    {
        if (buses[i].bus_id == bus_id)
        {
            strcpy(buses[i].bus_name, newBusName);
            strcpy(buses[i].bus_route,newbusroute);
            buses[i].total_seats = newTotalSeats;
            buses[i].available_seats = newAvailableSeats;
            printf("Bus details updated successfully.\n");
            return;
        }
    }
    printf("Bus not found.\n");
}
// Function to remove a bus by bus ID
int removeBusID(Bus buses[], int num_buses, int bus_id)
{
    int index = -1;
    for (int i = 0; i < num_buses; i++)
    {
        if (buses[i].bus_id == bus_id)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        for (int i = index; i < num_buses - 1; i++)
        {
            buses[i] = buses[i + 1];
        }
        return num_buses - 1; // Return the updated number of buses
    }
    else
    {
        printf("Bus not found.\n");
        return num_buses;
    }
}

void displayMenu() {
    printf("\n");
    printf("==========================================================================\n");
    printf("____________________________________Menu:_________________________________\n");
    printf("   1. Add a new bus\n");
    printf("   2. Remove a bus\n");
    printf("   3. Update bus details\n");
    printf("   4. Display available buses\n");
    printf("   5. Make a booking\n");
    printf("   6. Display bookings\n");
    printf("   7. Book specific seat\n");
    printf("   8. Exit\n");
    printf("\n");
    printf("===========================================================================\n");
    printf("      Select an option:");
}

int main() {
    Employee employees[3];
    employees[0].id = 1;
    strcpy(employees[0].username, "Employee1");
    strcpy(employees[0].password, "password1");
    employees[1].id = 2;
    strcpy(employees[1].username, "Employee2");
    strcpy(employees[1].password, "password2");
    employees[2].id = 3;
    strcpy(employees[2].username, "Employee3");
    strcpy(employees[2].password, "password3");

int num_buses=5;
    Bus buses[5];
    buses[0].bus_id = 1;
    strcpy(buses[0].bus_name, "BusA");
    strcpy(buses[0].bus_route,"Nairobi,Kisumu");
    buses[0].total_seats = 50;
    buses[0].available_seats = 50;


    buses[1].bus_id = 2;
    strcpy(buses[1].bus_name, "BusB");
    strcpy(buses[1].bus_route,"Nairobi,Eldoret");
    buses[1].total_seats = 40;
    buses[1].available_seats = 40;

    buses[2].bus_id = 3;
    strcpy(buses[2].bus_name, "BusC");
    strcpy(buses[2].bus_route,"Nairobi,Mombasa");
    buses[2].total_seats = 56;
    buses[2].available_seats = 56;

    buses[3].bus_id = 4;
    strcpy(buses[3].bus_name, "BusD");
    strcpy(buses[3].bus_route,"Nairobi,Kampala");
    buses[3].total_seats = 56;
    buses[3].available_seats = 56;

    buses[4].bus_id = 5;
    strcpy(buses[4].bus_name, "BusE");
    strcpy(buses[4].bus_route,"Kisumu,Mombasa");
    buses[4].total_seats = 40;
    buses[4].available_seats = 40;

    Booking bookings[5];
    int num_bookings = 0;

    int result = login(employees, 3);
    if (result != -1) {
        printf("Login successful. Employee ID: %d\n", result);

        // Load data from files
loadBusData(buses, &num_buses, "bus_data.bin");
loadBookingData(bookings, &num_bookings, "booking_data.bin");

// Save data to files
saveBusData(buses, num_buses, "bus_data.bin");
saveBookingData(bookings, num_bookings, "booking_data.bin");

        int option;

        do {
            displayMenu();
            scanf("%d", &option);
    switch (option) {
        case 1:
            // Add a new bus
            {
            int bus_id, total_seats, available_seats;
            char bus_name[30],bus_route[30];

            printf("Enter Bus ID: ");
            scanf("%d", &bus_id);

            printf("Enter Bus Name: ");
            scanf("%s", *&bus_name);

            printf("Enter Bus route: ");
            scanf("%s", bus_route);

            printf("Enter Total Seats: ");
            scanf("%d", &total_seats);

            printf("Enter Available Seats: ");
            scanf("%d", &available_seats);



        int success = addBus(buses, num_buses, bus_id, bus_name, bus_route, total_seats, available_seats);
                if (success)
                {
                    num_buses++;
                    printf("Bus added successfully.\n");
                }
                break;
            }

        case 2:
            // Remove a bus
            {
            int removeBusID;

            printf("Enter the Bus ID to remove: ");
            scanf("%d", &removeBusID);

          int success = removeBus(buses, num_buses, removeBusID);
                if (success)
                {
                    num_buses--;
                    printf("Bus removed successfully.\n");
                }
                break;
            }

        case 3:
            // Update bus details
            {
            int updateBusID;
            char newBusName[30];
            char newbusroute[30];
            int newTotalSeats;
            int newAvailableSeats;

            printf("Enter the Bus ID to update: ");
            scanf("%d", &updateBusID);

            printf("Enter the new Bus Name: ");
            scanf("%s", newBusName);

            printf("Enter the new Bus route: ");
            scanf("%s", newbusroute);

            printf("Enter the new Total Seats: ");
            scanf("%d", &newTotalSeats);

            printf("Enter the new Available Seats: ");
            scanf("%d", &newAvailableSeats);

            updateBus(buses, num_buses, updateBusID, newBusName,newbusroute, newTotalSeats, newAvailableSeats);
            break;
            }
        case 4:
            {
            displayBuses(buses, num_buses);
            break;
            }
        case 5:
            // Make a booking
            {
            int bus_id, num_seats;
            printf("Enter the Bus ID for booking: ");
            scanf("%d", &bus_id);
            printf("Enter the number of seats to book: ");
            scanf("%d", &num_seats);

            int bookingID = makeBooking(bookings, num_bookings, buses, num_buses, bus_id, result, num_seats);
            if (bookingID != -1)
            {
                printf("Booking successful. Booking ID: %d\n", bookingID);
            }
            break;
            }
            case 6:
   // Display bookings
            {
            displayBookings(bookings, num_bookings);
            break;
            }
        case 7:

             // Book a specific seat
    {
        int bus_id, seat_row, seat_col;
        printf("Enter the Bus ID for booking: ");
        scanf("%d", &bus_id);
        printf("Enter the row number of the seat: ");
        scanf("%d", &seat_row);
        printf("Enter the column number of the seat: ");
        scanf("%d", &seat_col);

        int bookingID = bookSpecificSeat(bookings, num_bookings, buses, num_buses, bus_id, result, seat_row, seat_col);
        if (bookingID != -1)
        {
            printf("Booking successful. Booking ID: %d\n", bookingID);
        }
        break;
    }
        case 8:
             // Exit
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid option. Please select a valid option.\n");
            }
        } while (option != 8);
    }
    else
    {
        printf("Login failed. Please check your credentials.\n");
    }

    return 0;
}
