#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Room {
public:
    Room() {
        id = 0;
        type = " ";
        price = 0;
        stat = " ";
        feature = " ";
        pnext = NULL;
    }
    int id, price;
    string type, stat,feature;
    Room* pnext;
};


class Booking {
public:
    Booking() {
        id_Booking = 0;
        id_guest = 0;
        id_room = 0;
        cost = 0;
        date_in = "";
        date_out = "";
        pnext = NULL;
    }
    int id_Booking, id_guest, id_room, cost;
    string date_in, date_out;
    Booking* pnext;
};


class Guest {
public:
    Guest() {
        id = 0;
        password = "";
        name = "";
        pnext = NULL;
    }
    int id;
    string password, name;
    Guest* pnext;
};


class Admin {
public:
    Admin() {
        id = 0;
        password = "";
        name = "";
        pnext = NULL;
    }
    int id;
    string password, name;
    Admin* pnext;
};


class List_Room {
public:
    Room* phead;
    Room* ptail;
    List_Room() {
        phead = NULL;
        ptail = NULL;
    }

    void Add(Room* pnn) {
        if (phead == NULL) {
            phead = pnn;
            ptail = pnn;
        }
        else {
            ptail->pnext = pnn;
            ptail = pnn;
        }
    }
};


class List_Booking {
public:
    Booking* phead;
    Booking* ptail;
    List_Booking() {
        phead = NULL;
        ptail = NULL;
    }

    void Add(Booking* pnn) {
        if (phead == NULL) {
            phead = pnn;
            ptail = pnn;
        }
        else {
            ptail->pnext = pnn;
            ptail = pnn;
        }
    }
};


class List_Guest {
public:
    Guest* phead;
    Guest* ptail;
    List_Guest() {
        phead = NULL;
        ptail = NULL;
    }

    void Add(Guest* pnn) {
        if (phead == NULL) {
            phead = pnn;
            ptail = pnn;
        }
        else {
            ptail->pnext = pnn;
            ptail = pnn;
        }
    }
};


class List_Admin {
public:
    Admin* phead;
    Admin* ptail;
    List_Admin() {
        phead = NULL;
        ptail = NULL;
    }

    void Add(Admin* pnn) {
        if (phead == NULL) {
            phead = pnn;
            ptail = pnn;
        }
        else {
            ptail->pnext = pnn;
            ptail = pnn;
        }
    }
};


void loadRooms(List_Room& lr);
void loadBookings(List_Booking& lb);
void loadGuests(List_Guest& lg);
void loadAdmins(List_Admin& la);
void saveRooms(List_Room& lr);
void saveBookings(List_Booking& lb);
void saveGuests(List_Guest& lg);
void saveAdmins(List_Admin& la);
void guestMenu(List_Guest& lg, List_Room& lr, List_Booking& lb, int guestId);
void adminMenu(List_Admin& la, List_Room& lr, List_Booking& lb, List_Guest& lg);
void registerGuest(List_Guest& lg);
int guestLogin(List_Guest& lg);
int adminLogin(List_Admin& la);
void searchRooms(List_Room& lr);
void bookRoom(List_Room& lr, List_Booking& lb, int guestId);
void cancelBooking(List_Booking& lb, List_Room& lr, int guestId);
void viewBookingHistory(List_Booking& lb, int guestId);
void checkInOut(List_Booking& lb, List_Room& lr, int guestId);
void addRoom(List_Room& lr);
void editRoom(List_Room& lr);
void deleteRoom(List_Room& lr);
void viewAllBookings(List_Booking& lb);
void occupancyRate(List_Room& lr);
void incomeReport(List_Booking& lb);


void loadRooms(List_Room& lr) {
    ifstream file("Room.txt");
    if (file.is_open()) {
        string temp[5];
        string line;
        int ct = 0;

        while (getline(file, line)) {
            if (ct > 0) {
                int k = 0;
                for (int i = 0; i < line.length(); i++) {
                    if (line[i] == ',') {
                        k++;
                    }
                    else {
                        temp[k] += line[i];
                    }
                }

                Room* ro = new Room();
                ro->id = stoi(temp[0]);
                ro->type = temp[1];
                ro->price = stoi(temp[2]);
                ro->stat = temp[3]; // الآن stat نصي وليس رقمي
                ro->feature = temp[4];
                lr.Add(ro);

                for (int i = 0; i < 5; i++) {
                    temp[i].clear();
                }
            }
            ct++;
        }
        file.close();
    }
    else {
        cout << "Error opening Room.txt file\n";
    }
}


void saveRooms(List_Room& lr) {
    ofstream file("Room.txt");
    if (file.is_open()) {
        file << "roomId,type,price,status,features\n"; // تأكد من تطابق العناوين
        Room* ro = lr.phead;
        while (ro != NULL) {
            file << ro->id << ","
                << ro->type << ","
                << ro->price << ","
                << ro->stat << ","
                << ro->feature << "\n";
            ro = ro->pnext;
        }
        file.close();
        cout << "Rooms saved successfully!\n"; // رسالة تأكيد
    }
    else {
        cout << "Error: Cannot open Room.txt for writing!\n";
    }
}


void loadBookings(List_Booking& lb) {
    ifstream file("Booking.txt");
    if (file.is_open()) {
        string temp[6];
        string line;
        int ct = 0;

        while (getline(file, line)) {
            if (ct > 0) {
                int k = 0;
                for (int i = 0; i < line.length(); i++) {
                    if (line[i] == ',') {
                        k++;
                    }
                    else {
                        temp[k] += line[i];
                    }
                }

                Booking* B = new Booking();
                B->id_Booking = stoi(temp[0]);
                B->id_guest = stoi(temp[1]);
                B->id_room = stoi(temp[2]);
                B->date_in = temp[3];
                B->date_out = temp[4];
                B->cost = stod(temp[5]);
                lb.Add(B);

                for (int i = 0; i < 6; i++) {
                    temp[i].clear();
                }
            }
            ct++;
        }
        file.close();
    }
    else {
        cout << "Error opening Booking.txt file\n";
    }
}


void saveBookings(List_Booking& lb) {
    ofstream file("Booking.txt");
    if (file.is_open()) {
        file << "bookingId,guestId,roomId,cost,date_in,date_out\n";
        Booking* B = lb.phead;
        while (B != NULL) {
            file << B->id_Booking << "," << B->id_guest << "," << B->id_room << ","
                << B->cost << "," << B->date_in << "," << B->date_out << "\n";
            B = B->pnext;
        }
        file.close();
    }
    else {
        cout << "Error saving to Booking.txt file\n";
    }
}


void loadGuests(List_Guest& lg) {
    ifstream file("Guest.txt");
    if (file.is_open()) {
        string temp[3];
        string line;
        int ct = 0;

        while (getline(file, line)) {
            if (ct > 0) {
                int k = 0;
                for (int i = 0; i < line.length(); i++) {
                    if (line[i] == ',') {
                        k++;
                    }
                    else {
                        temp[k] += line[i];
                    }
                }

                Guest* g = new Guest();
                g->id = stoi(temp[0]);
                g->name = temp[1];
                g->password = temp[2];
                lg.Add(g);

                for (int i = 0; i < 3; i++) {
                    temp[i].clear();
                }
            }
            ct++;
        }
        file.close();
    }
    else {
        cout << "Error opening Guest.txt file\n";
    }
}


void saveGuests(List_Guest& lg) {
    ofstream file("Guest.txt");
    if (file.is_open()) {
        file << "ID,Name,Password\n";
        Guest* g = lg.phead;
        while (g != NULL) {
            file << g->id << "," << g->name << "," << g->password << "\n";
            g = g->pnext;
        }
        file.close();
    }
    else {
        cout << "Error saving to Guest.txt file\n";
    }
}


void loadAdmins(List_Admin& la) {
    ifstream file("Admin.txt");
    if (file.is_open()) {
        string temp[3];
        string line;
        int ct = 0;

        while (getline(file, line)) {
            if (ct > 0) {
                int k = 0;
                for (int i = 0; i < line.length(); i++) {
                    if (line[i] == ',') {
                        k++;
                    }
                    else {
                        temp[k] += line[i];
                    }
                }

                Admin* a = new Admin();
                a->id = stoi(temp[0]);
                a->name = temp[1];
                a->password = temp[2];
                la.Add(a);

                for (int i = 0; i < 3; i++) {
                    temp[i].clear();
                }
            }
            ct++;
        }
        file.close();
    }
    else {
        cout << "Error opening Admin.txt file\n";
    }
}


void saveAdmins(List_Admin& la) {
    ofstream file("Admin.txt");
    if (file.is_open()) {
        file << "ID,Name,Password\n";
        Admin* a = la.phead;
        while (a != NULL) {
            file << a->id << "," << a->name << "," << a->password << "\n";
            a = a->pnext;
        }
        file.close();
    }
    else {
        cout << "Error saving to Admin.txt file\n";
    }
}


void guestMenu(List_Guest& lg, List_Room& lr, List_Booking& lb, int guestId) {
    int choice;
    while (true) {
        cout << "\nGuest Menu:\n";
        cout << "1. Search Rooms\n";
        cout << "2. Book Room\n";
        cout << "3. View Booking History\n";
        cout << "4. Cancel Booking\n";
        cout << "5. Check-In/Check-Out\n";
        cout << "0. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            searchRooms(lr);
        }
        else if (choice == 2) {
            bookRoom(lr, lb, guestId);
        }
        else if (choice == 3) {
            viewBookingHistory(lb, guestId);
        }
        else if (choice == 4) {
            cancelBooking(lb, lr, guestId);
        }
        else if (choice == 5) {
            checkInOut(lb, lr, guestId);
        }
        else if (choice == 0) {
            cout << "Logging out...\n";
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}


void adminMenu(List_Admin& la, List_Room& lr, List_Booking& lb, List_Guest& lg) {
    int choice;
    while (true) {
        cout << "\nAdmin Menu:\n";
        cout << "1. Add Room\n";
        cout << "2. Edit Room\n";
        cout << "3. Delete Room\n";
        cout << "4. View All Bookings\n";
        cout << "5. Monitor Occupancy Rate\n";
        cout << "6. Income Report\n";
        cout << "0. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            addRoom(lr);
        }
        else if (choice == 2) {
            editRoom(lr);
        }
        else if (choice == 3) {
            deleteRoom(lr);
        }
        else if (choice == 4) {
            viewAllBookings(lb);
        }
        else if (choice == 5) {
            occupancyRate(lr);
        }
        else if (choice == 6) {
            incomeReport(lb);
        }
        else if (choice == 0) {
            cout << "Logging out...\n";
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

void registerGuest(List_Guest& lg) {
    Guest* g = new Guest();

    cout << "\nGuest Registration:\n";
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, g->name);

    cout << "Enter password: ";
    getline(cin, g->password);

    // Generate new ID
    if (lg.ptail != NULL) {
        g->id = lg.ptail->id + 1;
    }
    else {
        g->id = 1;
    }

    lg.Add(g);
    saveGuests(lg);
    cout << "Registration successful! Your ID is: " << g->id << "\n";
}


int guestLogin(List_Guest& lg) {
    int id;
    string password;

    cout << "\nGuest Login:\n";
    cout << "Enter ID: ";
    cin >> id;

    cout << "Enter password: ";
    cin.ignore();
    getline(cin, password);

    Guest* g = lg.phead;
    while (g != NULL) {
        if (g->id == id && g->password == password) {
            cout << "Login successful! Welcome, " << g->name << "!\n";
            return id;
        }
        g = g->pnext;
    }

    cout << "Invalid ID or password.\n";
    return -1;
}


int adminLogin(List_Admin& la) {
    string name, password;

    cout << "\nAdmin Login:\n";
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter password: ";
    getline(cin, password);

    Admin* a = la.phead;
    while (a != NULL) {
        if (a->name == name && a->password == password) {
            cout << "Login successful! Welcome, " << a->name << "!\n";
            return 1;
        }
        a = a->pnext;
    }

    cout << "Invalid name or password.\n";
    return 0;
}


void searchRooms(List_Room& lr) {
    int choice;
    cout << "\nSearch Rooms By:\n";
    cout << "1. Type\n";
    cout << "2. Price Range\n";
    cout << "3. Availability\n";
    cout << "Enter choice: ";
    cin >> choice;

    Room* ro = lr.phead;
    int found = 0;

    if (choice == 1) {
        string type;
        cout << "Enter room type (single/Double/Suite): ";
        cin.ignore();
        getline(cin, type);

        while (ro != NULL) {
            if (ro->type == type) {
                cout << "ID: " << ro->id << ", Type: " << ro->type
                    << ", Price: " << ro->price << ", Status: " << ro->stat << ", Features: " << ro->feature << "\n";
                found = 1;
            }
            ro = ro->pnext;
        }
    }
    else if (choice == 2) {
        int minPrice, maxPrice;
        cout << "Enter minimum price: ";
        cin >> minPrice;
        cout << "Enter maximum price: ";
        cin >> maxPrice;

        while (ro != NULL) {
            if (ro->price >= minPrice && ro->price <= maxPrice) {
                cout << "ID: " << ro->id << ", Type: " << ro->type << ", Price: " << ro->price << ", Status: " << ro->stat 
                    << ",Features: " << ro->feature << "\n";
                found = 1;
            }
            ro = ro->pnext;
        }
    }
    else if (choice == 3) {
        searchRooms(lr); 
    }
}

void bookRoom(List_Room& lr, List_Booking& lb, int guestId) {
        int roomId;
        string date_in, date_out;

        
        cout << "\nAvailable Rooms:\n";
        Room* ro = lr.phead;
        while (ro != NULL) {
            if (ro->stat == "available") {  
                cout << "ID: " << ro->id << ", Type: " << ro->type
                    << ", Price: " << ro->price << ", Features: " << ro->feature << "\n";
            }
            ro = ro->pnext;
        }

        
        cout << "Enter room ID to book: ";
        cin >> roomId;

        
        ro = lr.phead;
        Room* selectedRoom = NULL;
        while (ro != NULL) {
            if (ro->id == roomId && ro->stat == "available") {  
                selectedRoom = ro;
                break;
            }
            ro = ro->pnext;
        }

        if (selectedRoom == NULL) {
            cout << "Invalid room ID or room is not available.\n";
            return;
        }

        cout << "Enter check-in date (DD/MM/YYYY): ";
        cin.ignore();
        getline(cin, date_in);

        cout << "Enter check-out date (DD/MM/YYYY): ";
        getline(cin, date_out);

        
        int days = 1;
        float vat = 0.14; 
        float cost = selectedRoom->price * days * (1 + vat);

       
        Booking* B = new Booking();
        if (lb.ptail != NULL) {
            B->id_Booking = lb.ptail->id_Booking + 1;
        }
        else {
           B->id_Booking = 1;
        }
        B->id_guest = guestId;
        B->id_room = roomId;
        B->date_in = date_in;
        B->date_out = date_out;
        B->cost = cost;

       
        selectedRoom->stat = "booked"; 

       
        lb.Add(B);

       
        saveRooms(lr);
        saveBookings(lb);

        cout << "Booking successful! Booking ID: " << B->id_Booking << "\n";
        cout << "Total cost (including VAT): " << cost << "\n";
}

void cancelBooking(List_Booking& lb, List_Room& lr, int guestId) {
    int bookingId;

    cout << "\nYour Bookings:\n";
    Booking* B = lb.phead;
    while (B != NULL) {
        if (B->id_guest == guestId) {
            cout << "Booking ID: " << B->id_Booking << ", Room ID: " << B->id_room
                << ", Check-in: " << B->date_in << ", Check-out: " << B->date_out
                << ", Total Cost: " << B->cost << "\n";
        }
        B = B->pnext;
    }

    cout << "Enter booking ID to cancel: ";
    cin >> bookingId;

    
    Booking* prev = NULL;
    B = lb.phead;
    while (B != NULL) {
        if (B->id_Booking == bookingId && B->id_guest == guestId) {
            
            Room* ro = lr.phead;
            while (ro != NULL) {
                if (ro->id == B->id_room) {
                    ro->stat = 1;
                    break;
                }
                ro = ro->pnext;
            }

          
            if (prev == NULL) {
                lb.phead = B->pnext;
            }
            else {
                prev->pnext = B->pnext;
            }

            if (B == lb.ptail) {
                lb.ptail = prev;
            }

            delete B;

           
            saveRooms(lr);
            saveBookings(lb);

            cout << "Booking canceled successfully.\n";
            return;
        }
        prev = B;
        B = B->pnext;
    }

    cout << "Booking not found or you don't have permission to cancel it.\n";
}


void viewBookingHistory(List_Booking& lb, int guestId) {
    cout << "\nYour Booking History:\n";
    Booking* B = lb.phead;
    int found = 0;

    while (B != NULL) {
        if (B->id_guest == guestId) {
            cout << "Booking ID: " << B->id_Booking << ", Room ID: " << B->id_room
                << ", Check-in: " << B->date_in << ", Check-out: " << B->date_out
                << ", Total Cost: " << B->cost << "\n";
            found = 1;
        }
        B = B->pnext;
    }

    if (found == 0) {
        cout << "No bookings found.\n";
    }
}

void checkInOut(List_Booking& lb, List_Room& lr, int guestId) {
    int bookingId, choice;

    cout << "\nYour Bookings:\n";
    Booking* B = lb.phead;
    while (B != NULL) {
        if (B->id_guest == guestId) {
            cout << "Booking ID: " << B->id_Booking << ", Room ID: " << B->id_room
                << ", Check-in: " << B->date_in << ", Check-out: " << B->date_out
                << ", Total Cost: " << B->cost << "\n";
        }
        B = B->pnext;
    }

    cout << "Enter booking ID: ";
    cin >> bookingId;

    cout << "1. Check-In\n2. Check-Out\nEnter choice: ";
    cin >> choice;

    
    B = lb.phead;
    while (B != NULL) {
        if (B->id_Booking == bookingId && B->id_guest == guestId) {
           
            Room* ro = lr.phead;
            while (ro != NULL) {
                if (ro->id == B->id_room) {
                    if (choice == 1) {
                        ro->stat = "booked"; 
                        cout << "Checked in successfully.\n";
                    }
                    else if (choice == 2) {
                        ro->stat = "Available"; 
                        cout << "Checked out successfully.\n";
                    }
                    else {
                        cout << "Invalid choice.\n";
                        return;
                    }

                    saveRooms(lr);
                    return;
                }
                ro = ro->pnext;
            }
        }
        B = B->pnext;
    }

    cout << "Booking not found or you don't have permission.\n";
}


void addRoom(List_Room& lr) {
    Room* ro = new Room();

    cout << "\nAdd New Room:\n";
    cout << "Enter room type (single/Double/Suite): ";
    cin.ignore();
    getline(cin, ro->type);

    cout << "Enter price: ";
    cin >> ro->price;
    cout << "Enter The status of the room\n";
    cin.ignore();
    getline(cin, ro->stat);
    cout << "Enter features (comma separated): ";
    cin.ignore();
    getline(cin, ro->feature);

    
    if (lr.ptail != NULL) {
        ro->id = lr.ptail->id + 1;
    }
    else {
        ro->id = 1;
    }

   
    lr.Add(ro);

    saveRooms(lr);
    cout << "Room added successfully. Room ID: " << ro->id << "\n";
}


void editRoom(List_Room& lr) {
    int roomId;

    cout << "\nAll Rooms:\n";
    Room* ro = lr.phead;
    while (ro != NULL) {
        cout << "ID: " << ro->id << ", Type: " << ro->type
            << ", Price: " << ro->price << ", Status: " << ro->stat<< ", Features: " << ro->feature << "\n";
        ro = ro->pnext;
    }

    cout << "Enter room ID to edit: ";
    cin >> roomId;

    
    ro = lr.phead;
    while (ro != NULL) {
        if (ro->id == roomId) {
            cout << "Current details:\n";
            cout << "Type: " << ro->type << "\n";
            cout << "Price: " << ro->price << "\n";
            cout << "Status: " << ro->stat<< "\n";
            cout << "Features: " << ro->feature << "\n";

            cout << "Enter new type (leave blank to keep current): ";
            string newType;
            cin.ignore();
            getline(cin, newType);
            cout << "Enter new price (0 to keep current): ";
            int newPrice;
            cin >> newPrice;
            if (newPrice > 0) {
                ro->price = newPrice;
            }

            cout << "Enter new status ( available,  booked): ";
            int newStatus;
            cin >> newStatus;
            if (newStatus == "booked" || newStatus == "available") {
                ro->stat = newStatus;
            }

            cout << "Enter new features (leave blank to keep current): ";
            string newFeatures;
            cin.ignore();
            getline(cin, newFeatures);
      
            saveRooms(lr);
            cout << "Room updated successfully.\n";
            return;
        }
        ro = ro->pnext;
    }

    cout << "Room not found.\n";
}


void deleteRoom(List_Room& lr) {
    int roomId;

    cout << "\nAll Rooms:\n";
    Room* ro = lr.phead;
    while (ro != NULL) {
        cout << "ID: " << ro->id << ", Type: " << ro->type
            << ", Price: " << ro->price << ", Status: " << ro->stat<< " Features: " << ro->feature << "\n";
        ro = ro->pnext;
    }

    cout << "Enter room ID to delete: ";
    cin >> roomId;

    Room* prev = NULL;
    ro = lr.phead;
    while (ro != NULL) {
        if (ro->id == roomId) {
            if (prev == NULL) {
                lr.phead = ro->pnext;
            }
            else {
                prev->pnext = ro->pnext;
            }

            if (ro == lr.ptail) {
                lr.ptail = prev;
            }

            delete ro;

            saveRooms(lr);
            cout << "Room deleted successfully.\n";
            return;
        }
        prev = ro;
        ro = ro->pnext;
    }

    cout << "Room not found.\n";
}


void viewAllBookings(List_Booking& lb) {
    cout << "\nAll Bookings:\n";
    Booking* B = lb.phead;

    if (B == NULL) {
        cout << "No bookings found.\n";
        return;
    }

    while (B != NULL) {
        cout << "Booking ID: " << B->id_Booking << ", Guest ID: " << B->id_guest
            << ", Room ID: " << B->id_room << ", Check-in: " << B->date_in
            << ", Check-out: " << B->date_out << ", Total Cost: " << B->cost << "\n";
        B = B->pnext;
    }
}


void occupancyRate(List_Room& lr) {
    int totalRooms = 0;
    int occupiedRooms = 0;

    Room* ro = lr.phead;
    while (ro != NULL) {
        totalRooms++;
        if (ro->stat == "booked") {
            occupiedRooms++;
        }
        ro = ro->pnext;
    }

    if (totalRooms == 0) {
        cout << "No rooms in the system.\n";
        return;
    }

    float rate = (float)occupiedRooms / totalRooms * 100;
    cout << "\nOccupancy Report:\n";
    cout << "Total rooms: " << totalRooms << "\n";
    cout << "Occupied rooms: " << occupiedRooms << "\n";
    cout << "Occupancy rate: " << rate << "%\n";
}


void incomeReport(List_Booking& lb) {
    float totalIncome = 0;

    Booking* B = lb.phead;
    while (B != NULL) {
        totalIncome += B->cost;
        B = B->pnext;
    }

    cout << "\nIncome Report:\n";
    cout << "Total income from all bookings: " << totalIncome << "\n";
}

int main() {
    List_Room lr;
    List_Booking lb;
    List_Guest lg;
    List_Admin la;

   
    loadRooms(lr);
    loadBookings(lb);
    loadGuests(lg);
    loadAdmins(la);

    int choice;
    while (true) {
        cout << "\n=============================\n";
        cout << " Hotel Management System\n";
        cout << "=============================\n";
        cout << "1. Guest Login\n";
        cout << "2. Guest Register\n";
        cout << "3. Admin Login\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int guestId = guestLogin(lg);
            if (guestId != -1) {
                guestMenu(lg, lr, lb, guestId);
            }
        }
        else if (choice == 2) {
            registerGuest(lg);
        }
        else if (choice == 3) {
            if (adminLogin(la)) {
                adminMenu(la, lr, lb, lg);
            }
        }
        else if (choice == 0) {
           
            saveRooms(lr);
            saveBookings(lb);
            saveGuests(lg);
            saveAdmins(la);
            cout << "Thank you for using the system!\n";
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}