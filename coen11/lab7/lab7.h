// unions
typedef union u{
    int bday[2];
    char ophone[20];
} U;

//structures
typedef struct entry{
    char first_name[50];
    char last_name[50];
    char phone_number[15];
    int flag;
    U info;
} Entry;

//node for linked list
typedef struct node{
    Entry ent;
    struct node *next;
} NODE;

//global variables
extern int counter;  //only to display how long is the linked list, not used for checks
extern NODE* head;

// functions
int main ();
void insert(Entry e);
void show_all();
void show_name();
void delete();
void delete_name();
int check_duplicate(char fname[], char lname[]);

void read_from_keyboard();
void deleteall();
void read_from_file();
void save_to_file();