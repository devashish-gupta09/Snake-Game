#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
using namespace std;

class snake
{
    int height = 25; // height of the given area for game
    int width = 100; // width of the given area for game
    int upflag = 0;
    int downflag = 0;
    int leftflag = 0;
    int rightflag = 0;
    int counter;     // updates the score
    int endgame = 0; // check for conditions for game over
    int speed = 100; // initial speed of the snake (or sleep timer for the snake in each transition)
    int fcount;
    int x;
    int y;
    int fx;
    int fy;
    char playername[30];

    struct node // linked list data structure
    {
        int nx, ny;
        struct node *next;
        struct node *back;
    };

    struct node *head = NULL;

    void gotoxy(int x, int y) // function for the co-ordinate system
    {
        COORD pos = {x, y};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }

    void result() // real-time score tracker
    {
        textcolour(7);
        gotoxy(104, 0);
        cout << playername << "'s SCORE : " << counter * 100 << endl;
        gotoxy(104, 2);
    }

    void textcolour(int k) // colour picker for the console
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, k);
    }

public:
    void rect() // area for the snake game
    {
        textcolour(6);
        for (int i = 0; i <= width; i++)
        {
            gotoxy(i, 0);
            cout << "/";
            gotoxy(i, height);
            cout << "/";
        }
        for (int i = 0; i <= height; i++)
        {
            gotoxy(0, i);
            cout << "/";
            gotoxy(width, i);
            cout << "/";
        }
    }

    void resetflag()
    {
        upflag = 0;
        downflag = 0;
        leftflag = 0;
        rightflag = 0;
    }

    void setup()
    {
        counter = 0;
        speed = 100;
        endgame = 0;
        rect();
        resetflag();
        result();

        head = new node;
        head->nx = width / 2;
        head->ny = height / 2;
        head->next = NULL;
        head->back = NULL;
        x = width / 2;
        y = height / 2;

    checkpoint1:
        fx = rand() % width;
        if (fx == 0 || fx == width)
            goto checkpoint1;

    checkpoint2:
        fy = rand() % height;
        if (fy == 0 || fy == height)
            goto checkpoint2;
    }

    void drawlist(struct node *h, int k)
    {
        struct node *ptr;
        ptr = h;
        while (ptr != NULL)
        {
            gotoxy(ptr->nx, ptr->ny);
            cout << "o";
            ptr = ptr->next;
        }
    }

    void destroylist(struct node *h)
    {
        struct node *ptr;
        ptr = h;
        while (ptr != NULL)
        {
            gotoxy(ptr->nx, ptr->ny);
            cout << " ";
            ptr = ptr->next;
        }
    }

    void food()
    {
        textcolour(10);
        drawlist(head, 2);
        gotoxy(fx, fy);
        cout << "*";
        Sleep(speed);
        destroylist(head);
    }

    void play()
    {
        int h;
        char ch;

        int i = 0;

        if (kbhit())
        {
            ch = getch();
            h = ch;
            switch (h)
            {
            case 72:
                if (downflag != 1)
                {
                    resetflag();
                    upflag = 1;
                }
                break;

            case 80:
                if (upflag != 1)
                {
                    resetflag();
                    downflag = 1;
                }
                break;

            case 75:
                if (rightflag != 1)
                {
                    resetflag();
                    leftflag = 1;
                }
                break;

            case 77:
                if (leftflag != 1)
                {
                    resetflag();
                    rightflag = 1;
                }
                break;

            case 112:
                gotoxy(20, height / 2);
                cout << "Your game has been paused. ";
                system("pause");
                system("cls");
                rect();
                result();

            default:
                break;
            }
        }
    }

    void box(int m1, int n1, int m2, int n2)
    {
        for (int i = m1; i <= m2; i++)
        {
            gotoxy(i, n1);
            cout << "//";
            gotoxy(i, n2);
            cout << "//";
        }

        for (int i = n1; i <= n2; i++)
        {
            gotoxy(m1, i);
            cout << "//";
            gotoxy(m2, i);
            cout << "//";
        }
    }

    int welcome()
    {
        box(width / 2 - width / 4, height / 2 - height / 4, width / 2 + width / 4, height / 2 + height / 4);

        gotoxy(width / 2 - 15, height / 2 - 10);
        cout << "<<< WELCOME TO SNAKE GAME >>> ";
        cin.ignore();

        gotoxy(width / 2 - 16, height / 2);
        cout << "Enter Your Name : ";
        cin.get(playername, 30);

        system("cls");
    }

    char end()
    {
        snake s;
        char c;
        gotoxy(width / 2 - 5, height / 2 - 4);
        cout << "GAME OVER " << endl;
        // box(width / 2 - width / 4, height / 2 - height / 4, width / 2 + width / 4, height / 2 + height / 4);

        gotoxy(width / 2 - 15, height / 2 - 2);
        cout << playername << " You Scored : " << counter * 100;

        save();

        cin.ignore();

        gotoxy(width / 2 - 15, height / 2 + 4);
        cout << "Want To Play Again ? (Y/N) : ";
        cin >> c;

        system("cls");
        return c;
    }

    void run()
    {
        if (upflag == 1)
            y--;
        else if (downflag == 1)
            y++;
        else if (leftflag == 1)
            x--;
        else if (rightflag == 1)
            x++;
    }

    void dolist(struct node *h, int pp, int qq)
    {
        struct node *ptr, *prev;
        ptr = h;
        prev = h;

        while (ptr->next != NULL)
        {
            prev = ptr;
            ptr = ptr->next;
        }
        while (prev != h)
        {
            ptr->nx = prev->nx;
            ptr->ny = prev->ny;
            prev = prev->back;
            ptr = ptr->back;
        }
        ptr->nx = prev->nx;
        ptr->ny = prev->ny;
        prev->nx = pp;
        prev->ny = qq;
    }

    void drawagain()
    {
        if (x == width)
        {
            x = 1;
        }
        if (x == 0)
        {
            x = width - 1;
        }
        if (y == 0)
        {
            y = height - 1;
        }
        if (y == height)
        {
            y = 1;
        }
    }

    void generatefood()
    {
    checkpoint1:
        fx = rand() % width;
        if (fx == 0 || fx == width)
            goto checkpoint1;
    checkpoint2:
        fy = rand() % height;
        if (fy == 0 || fy == height)
            goto checkpoint2;
    }

    void checkfcount()
    {
        if (fcount == 0)
        {
            endgame = 1;
        }
    }

    void check()
    {

        if (x == width || x == 0)
            endgame = 1;
        if (y == height || y == 0)
            endgame = 1;

        drawagain();

        struct node *h;
        h = head->next;
        while (h != NULL)
        {
            if (x == h->nx && y == h->ny)
            {
                endgame = 1;
                break;
            }
            h = h->next;
        }

        if (x == fx && y == fy)
        {
            struct node *t, *ptr, *prev;
            t = new node;
            t->next = NULL;
            t->back = NULL;
            ptr = head;
            prev = head;
            while (ptr->next != NULL)
            {
                ptr = ptr->next;
            }
            ptr->next = t;
            t->back = ptr;
            generatefood();
            speed = speed - 2;
            counter++;
            result();
        }
        dolist(head, x, y);
    }

    void game1()
    {
        char ch;
        do
        {
            setup();
            rect();
            while (!endgame)
            {
                food();
                play();
                run();
                check();
            }
            ch = end();
        } while (ch == 'y' || ch == 'Y');
    }

    void save()
    {
        snake s;
        ofstream out;
        out.open("record.txt", ios::app);
        out << "Name: " << playername << " \t\t Score: " << counter * 100 << endl;
        out.close();
    }

    void viewscore()
    {
        snake s;
        ifstream in;
        string st;
        in.open("record.txt");
        in.seekg(0);
        if (!in)
            cout << "Error" << endl;
        else
        {
            while (!in.eof())
            {
                getline(in, st);
                cout << st << endl;
            }
        }
        in.close();
    }
    void instructions()
    {
        // box(width / 2 - width / 4, height / 2 - height / 4, width / 2 + width / 4, height / 2 + height / 4);

        gotoxy(width / 2 - 15, height / 2 - 10);
        cout << "<<< WELCOME TO SNAKE GAME >>> ";
        // cin.ignore();

        gotoxy(width / 2 - 8, height / 2 - 6);
        cout << "**INSTRUCTIONS**";
        gotoxy(width / 4 - 10, height / 2 - 2);
        cout << "-> The game begins once you press any key." << endl;
        gotoxy(width / 4 - 10, height / 2 - 1);
        cout << "-> Your task is to simply eat the (*) shaped food." << endl;
        gotoxy(width / 4 - 10, height / 2);
        cout << "-> Use the UP, DOWN, LEFT, RIGHT keys to change the direction of the snake." << endl;
        gotoxy(width / 4 - 10, height / 2 + 1);
        cout << "-> The game will end if either you touch the walls of the given area or eat yourself(>_<)" << endl;
        gotoxy(width / 4 - 10, height / 2 + 2);
        cout << "-> Press 'P' to pause the game at any moment." << endl;
        gotoxy(width / 4 - 10, height / 2 + 3);
        cout << "-> Press any key other than 'P' to resume the game." << endl;
        gotoxy(width / 4 - 10, height / 2 + 4);
        cout << "-> Press 'ESC' to quit the game without saving your record." << endl;
        gotoxy(width / 4 - 10, height / 2 + 6);
        cout << ">>THAT's ALL!! HOPE YOU ENJOY THE GAME. LET's SEE WHO SCORES THE MOST :)";
        gotoxy(width / 4 - 10, height / 2 + 8);
        system("pause");
        system("cls");
    }
};

int main()
{
    snake s;
mainmenu:
    system("cls");
    cout << "Welcome to SNAKE Game" << endl
         << "1. New Game" << endl
         << "2. View Scores" << endl
         << "Enter your choice : ";
    int choice;
    cin >> choice;
    system("cls");

    if (choice == 1)
    {
        s.instructions();
        s.welcome();
        s.game1();
        system("exit");
    }
    else
    {
        s.viewscore();
        cout << "Press 1 to return to main menu" << endl;
        cout << "Press 2 to exit the code" << endl;
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            goto mainmenu;
        }
        else
        {
            system("cls");
            exit(0);
        }
    }

    return 0;
}