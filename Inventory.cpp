#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

//GLOBAL SCOPE VARIABLES----------------------------------------------------
const int MAX_PRODUCTS = 100;
int prodCount = 0;
const int MAX_ORDERS = 100;
int orderCount = 0;
int orderedprodCount=0;
int choice = 0;



// I think arrays are ok for now
//Storing parameters in arrays for now.
//later will change to vectors
int prodId[MAX_PRODUCTS];
string prodName[MAX_PRODUCTS];
int prodQty[MAX_PRODUCTS];
double prodPrice[MAX_PRODUCTS];


int orderId[MAX_ORDERS];
int orderedProductId[MAX_ORDERS];
int orderQty[MAX_ORDERS];
double orderPrice[MAX_ORDERS];
string orderStatus[MAX_ORDERS];
string orderedProductName[MAX_ORDERS];
double orderedUnitPrice[MAX_ORDERS];





//FUNCTIONS being USED(just prototyping)--------------------------------------

int retrievedata();
void showMenu();
int findProduct(int id);
void addProduct();
void showProducts();
void updateQty();
void deleteProduct();
void updatePrice();
void savedata();
void viewOrders();
void placeOrder();
void saveOrder(int index);
void readOrders();

// void search_product();



int main() {
   
    retrievedata();
    readOrders();
    cout<<"Welcome to the Inventory Management System\n";

    do {
        
        showMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: showProducts(); break;
            case 2: addProduct(); break;
            case 3: updateQty(); break;
            case 4: updatePrice(); break;
            case 5: deleteProduct(); break;
            case 6: placeOrder(); break;
            case 7: viewOrders(); break; 
            case 8: savedata();  
                    cout << "The data has been saved\n"
                         << "Thanks for using INVENTORY MANAGEMENT SYSTEM!\n"; 
                    break;
            default: cout << "Invalid.\n"; break;
        }

    } while (choice != 8);

    return 0;
}


void showMenu() {
    cout << "====== Inventory Management System ======\n";
    cout << "1. Display Products\n";
    cout << "2. Add New Products\n";
    cout << "3. Update Product Quantity\n";
    cout << "4. Update Product Price\n";
    cout << "5. Delete Product\n";
    cout << "6. Place Order\n";
    cout << "7. View Orders\n";
    cout << "8. Exit\n";
    cout << "Enter your choice: ";
}

void deleteProduct() {
    int id;
    cout << "Enter product ID to delete: ";
    cin >> id;

    int index = findProduct(id);

    if (index == -1) {
        cout << "Not found.\n";
        return;
    }

    // moving everything left (teacher explained this)
    for (int i = index; i < prodCount - 1; i++) {
        prodId[i] = prodId[i + 1];
        prodName[i] = prodName[i + 1];
        prodQty[i] = prodQty[i + 1];
        prodPrice[i] = prodPrice[i + 1];
    }

    prodCount--;

    cout << "Deleted.\n";
}

void updateQty() {
    int id;
    cout << "Enter product ID: ";
    cin >> id;

    int index = findProduct(id);

    if (index == -1) {
        cout << "Not found.\n";
        return;
    }

    int newQty;
    cout << "Enter new quantity: ";
    cin >> newQty;

    prodQty[index] = newQty;

    cout << "Updated.\n";
}

void showProducts() 
{
    if (prodCount == 0) {
        cout<< "No products yet.\n";
        return;
    }
    cout << "--- Products ---\n";
    for (int i = 0; i < prodCount; i++) {
        cout << "ID: " << prodId[i]
        << ", Name: " << prodName[i]
        << ",       Qty: " << prodQty[i]
        << ",       Price: " << prodPrice[i] << endl;
    }

}
      
void addProduct() 
{
    if (prodCount == MAX_PRODUCTS) {
        cout << "Inventory full.\n";
        return;
    }

    int id;
    string name;
    int qty;
    double price;

    cout << "Enter ID: ";
    cin >> id;
    cin.ignore(); // cannot use getline it is for strings
    if(findProduct(id)==-1){
        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Quantity: ";
        cin >> qty;

        cout << "Enter Price: ";
        cin >> price;

        // storing values
       prodId[prodCount] = id;
       prodName[prodCount] = name;
       prodQty[prodCount] = qty;
       prodPrice[prodCount] = price;

       prodCount++;

       cout << "Product added.\n"; 
    }
    else{
        cout<<"Id already assigned to other product";
    }
}

int findProduct(int id) {
    for (int i = 0; i < prodCount; i++) {
        if (prodId[i] == id) {
        
            return i;
        }
    }
    return -1; // not found
}//this returns the index at which the product id is stored

void updatePrice(){
    int id;
    cout<<"Enter the product Id: ";
    cin>>id;
    
    int z = findProduct(id);
    
    if(z == -1){
        cout<<"Product not found!";
        return;
    }

    double updatedprice;
    cout<<"Enter Updated price: ";
    cin>>updatedprice;
    prodPrice[z]=updatedprice;

    cout << "Price updated.\n";
}

void savedata(){
    ofstream file("Inventory.csv"); // overwrite file instead of append

    for(int l=0; l< prodCount; l++){
        file<<prodId[l]<<","<<prodName[l]<<","<<prodQty[l]<<","<<prodPrice[l]<<endl;
    }
    file.close();
}

int retrievedata() {
    cout << "data retrieving function was run\n";


    ifstream file("Inventory.csv");
    if (!file) {
        cout << "File doesn't exist\n";
        return 0;
    }

    prodCount = 0; //it's declared in global scope but still i am making it zero so that after every iteration it remains at zero
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string id, name, qty, price;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, qty, ',');
        getline(ss, price, ',');

        prodId[prodCount] = stoi(id);
        prodName[prodCount] = name;
        prodQty[prodCount] = stoi(qty);
        prodPrice[prodCount] = stod(price);   
 
        prodCount++;
    }

    file.close();
    cout<<"data got retrieved\n";
    return prodCount; //use this in future to display total number of products
}

// I hope this function works
void placeOrder(){
    orderStatus[orderCount]="Pending";
    int id;
    cout<<"Enter the Product ID: ";
    cin>>id;

    int i=findProduct(id);

    if(i==-1){
     cout<<"Required product not found!";
     return;
    }
    
    int quantity;
    cout<<"Enter quantity: ";
    cin>>quantity;
    if(quantity>prodQty[i]){
        cout<<"Not enough stock!"<<endl;
        return;
    }

    prodQty[i]=prodQty[i]-quantity;
    cout<<"Product quantity updated."<<endl;
    double Totalprice;
    Totalprice=(prodPrice[i])*quantity;
    cout<<"Total price for the order: "<<Totalprice<<endl;

    orderId[orderCount] = orderCount+1;
    orderedProductId[orderCount] = id;
    orderQty[orderCount] = quantity;
    orderPrice[orderCount] = Totalprice;
    orderedProductName[orderCount] = prodName[i];
    orderedUnitPrice[orderCount]   = prodPrice[i];

    saveOrder(orderCount);

    orderCount++;
}


void viewOrders() {
    if (orderCount == 0) {
        cout << "No orders placed yet.\n";
        return;
    }

    cout << "--- Orders ---\n";
    for (int i = 0; i < orderCount; i++) {
        int pindex = findProduct(orderedProductId[i]);

        cout << "Order ID: " << orderId[i]
             << ", Product ID: " << orderedProductId[i]
             << ", Name: " << orderedProductName[i]
             << ", Qty: " << orderQty[i]
             << ", Price: " <<orderedUnitPrice[i]
             << ", Total: " << orderPrice[i]
             << ", Status: "<<orderStatus[i]
             << endl;
    }
}

void saveOrder(int index){
    cout<<"saveorder fucntion was called \n";
    ofstream file("Orders.csv", ios::app);

    file << orderId[index] << ","
        << orderedProductId[index] << ","
        << prodName[ findProduct( orderedProductId[index] ) ] << ","
        << orderQty[index] << ","
        << prodPrice[ findProduct( orderedProductId[index] ) ] << ","
        << orderPrice[index]<<","
        << orderStatus[index]
        << endl;
   
   file.close();
}

void readOrders(){
    ifstream file("Orders.csv");
    if (!file) {
        cout << "Orders file not found\n";
        return;
    }

    orderCount = 0;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string oid, pid, pname, qty, uprice, total, status;

        getline(ss, oid, ',');
        getline(ss, pid, ',');
        getline(ss, pname, ',');             
        getline(ss, qty, ',');
        getline(ss, uprice, ',');
        getline(ss, total, ',');
        getline(ss, status, ',');

        orderId[orderCount]            = stoi(oid);
        orderedProductId[orderCount]   = stoi(pid);
        orderedProductName[orderCount] = pname;        // Store the product name INSIDE the orders array, NOT inside product list
        orderQty[orderCount]           = stoi(qty);
        orderedUnitPrice[orderCount]   = stod(uprice); // store price per unit (not in product list)
        orderPrice[orderCount]         = stod(total);
        orderStatus[orderCount]        = status;       // string (no stoi)

        orderCount++;
    }

    file.close();
}
