#include <iostream>
#include <string>
using namespace std;

/*
TODO => le nom / description ne doivent pas etre modifiable et vous utilisez la méthod strict.
vous modifier votre énum de maniere à l'utiliser avec le formalise classe

toutes vos variables doivent être initialisés avec un formalisme propre à C++
*/

enum class urgence { CLASSIQUE, URGENT, VITAL };

struct todo_t
{
    string _nom;
    string _description;
    urgence _importance;
    struct todo_t* p_previous;
    struct todo_t* p_next;
};

typedef struct todo_header_s
{
    int _length;
    todo_t* p_head;
    todo_t* p_tail;
}todo_header_t;

void initTodo(todo_header_t* todo_list, string nom, string desc, urgence importance)
{
    //todo_t* todo = (todo_t*)malloc(sizeof(todo_t));
    todo_t* todo = new todo_t();

    if (todo != NULL)
    {
        todo->_nom = nom;
        todo->_description = desc;
        todo->_importance = importance;
        todo->p_previous = NULL;
        todo->p_next = NULL;

        if (todo_list->_length == 0)
        {
            todo_list->p_head = todo;
        }

        todo_t* last_todo = todo_list->p_head;

        while (last_todo->p_next != NULL)
            last_todo = last_todo->p_next;

        if (todo_list->_length != 0)
        {
            last_todo->p_next = todo;
            todo->p_previous = last_todo;
        }

        todo_list->p_tail = todo;
        todo_list->_length++;
    }
}

void displayList(todo_header_t* todo_list)
{
    todo_t* todo = todo_list->p_head;
    urgence importance = urgence::CLASSIQUE;
    int choix;

    do
    {
        cout << "\nQuel niveau d'urgence minimal souhaitez-vous voir ? (0 = classique / 1 = urgent / 2 = vital)" << endl;
        cout << "Votre choix : ";
        cin >> choix;
    } while (choix < 0 || choix > 2);

    while (todo != NULL)
    {
        switch (choix)
        {
            case 0:
                cout << todo->_nom << " : " << todo->_description << " (" << (int)todo->_importance << ")" << endl;
                break;

            case 1:
                if (todo->_importance != urgence::CLASSIQUE)
                {
                    cout << todo->_nom << " : " << todo->_description << " (" << (int)todo->_importance << ")" << endl;
                }
                break;

            case 2:
                if (todo->_importance == urgence::VITAL)
                {
                    cout << todo->_nom << " : " << todo->_description << " (" << (int)todo->_importance << ")" << endl;
                }
                break;
        }

        todo = todo->p_next;
    }
}

void deleteTodo(todo_header_t* todo_list)
{
    todo_t* todo = todo_list->p_head;
    string nom;

    cout << endl << "Quel est le nom de la tache que vous voulez supprimer ?" << endl;
    cout << "> ";
    cin >> nom;

    while (todo != NULL)
    {
        //if (strcmp(todo->_nom, nom) == 0)
        if(todo->_nom == nom)
        {
            if (todo->p_previous != NULL)
                todo->p_previous->p_next = todo->p_next;

            if (todo->p_next != NULL)
                todo->p_next->p_previous = todo->p_previous;

            if (todo->p_previous == NULL)
                todo_list->p_head = todo->p_next;

            if (todo->p_next == NULL)
                todo_list->p_tail = todo->p_previous;

            todo_list->_length--;

            delete todo;
            return;
        }

        todo = todo->p_next;
    }
}

void updateTodo(todo_header_t* todo_list)
{
    todo_t* todo = todo_list->p_head;
    int choix = 0;
    string nomTodo;
    string texte;
    int importance;

    cout << endl << "Quel est le nom de la tache que vous voulez modifier ?" << endl;
    cout << "> ";
    cin >> nomTodo;

    do
    {
        cout << endl << "Que souhaitez-vous modifier ?" << endl;
        cout << "0) Rien" << endl;
        cout << "1) Nom" << endl;
        cout << "2) Description" << endl;
        cout << "3) Importance" << endl;
        cout << "> ";
        cin >> choix;
    } while (choix < 0 || choix > 3);

    switch (choix)
    {
    case 0: // Rien
        return;

    case 1: // Nom
        cout << "Comment souhaitez-vous modifier le nom ?" << endl;
        cout << "> ";
        cin >> texte;
        break;

    case 2: // Description
        cout << "Comment souhaitez-vous modifier la description ?" << endl;
        cout << "> ";
        cin >> texte;
        break;

    case 3: // Importance
        cout << "Comment souhaitez-vous modifier l'importance ?" << endl;
        cout << "> ";
        cin >> importance;
        break;
    }

    while (todo != NULL)
    {
        if (todo->_nom == nomTodo)
        {
            switch (choix)
            {
            case 1: // Nom
                todo->_nom = texte;
                break;

            case 2: // Description
                todo->_description = texte;
                break;

            case 3: // Importance
                todo->_importance = (urgence)importance;
                break;
            }
            return;
        }

        todo = todo->p_next;
    }
}

void suppr(todo_header_t* todo_list)
{
    todo_t* todo = todo_list->p_head;

    if (todo != NULL)
    {
        while (todo->p_next != NULL)
        {
            todo = todo->p_next;
            delete todo->p_previous;
        }

        if (todo != NULL)
            delete todo;
    }
    delete todo_list;
}

int main()
{
    int continuer(1);
    int choix{ 0 };
    string nom;
    string desc;
    auto importance = 0;
    //todo_header_t* todo_list = (todo_header_t*)malloc(sizeof(todo_header_t));
    todo_header_t* todo_list = new todo_header_t();

    constexpr string_view nom1  = "Vim";
    constexpr string_view desc1 = "Desinstaller Vim.";

    constexpr string_view nom2  = "Cafe";
    constexpr string_view desc2 = "Boire un cafe.";

    constexpr string_view nom3  = "Free";
    constexpr string_view desc3 = "Liberer la memoire allouee.";

    urgence urgInit = urgence::CLASSIQUE;

    if (todo_list != NULL)
    {
        todo_list->_length = 0;
        todo_list->p_head = NULL;
        todo_list->p_tail = NULL;

        urgInit = urgence::CLASSIQUE;
        initTodo(todo_list, nom1.data(), desc1.data(), urgInit);

        urgInit = urgence::VITAL;
        initTodo(todo_list, nom2.data(), desc2.data(), urgInit);

        urgInit = urgence::URGENT;
        initTodo(todo_list, nom3.data(), desc3.data(), urgInit);

        while (continuer)
        {
            // MENU (La fonction existe déjà pour l'exo 1 et je peux pas m'en resservir)
            cout << endl << "Que voulez-vous faire ?" << endl;
            cout << "0) Quitter." << endl;
            cout << "1) Voir la liste des taches a faire." << endl;
            cout << "2) Ajouter une tache." << endl;
            cout << "3) Modifier une tache." << endl;
            cout << "4) Supprimer une tache." << endl;
            cout << "Votre choix : ";
            cin >> choix;

            if (choix < 0 || choix > 4)
            {
                cout << "Choix inconnu." << endl;
                continue;
            }

            switch (choix)
            {
            case 0: // Quitter
                continuer = 0;
                break;

            case 1: // Display
                displayList(todo_list);
                break;

            case 2: // Add
                cout << "Quel nom voulez-vous donner a votre tache ?" << endl;
                cout << "> ";
                cin >> nom;
                //scanf("%s", nom);
                cout << "Quelle description voulez-vous donner a votre tache ?" << endl;
                cout << "> ";
                cin >> desc;
                //scanf("%s", desc);
                cout << "Quelle importance voulez-vous donner a votre tache ?" << endl;
                cout << "> ";
                cin >> importance;
                //scanf("%d", &importance);

                initTodo(todo_list, nom, desc, (urgence)importance);
                break;

            case 3: // Update
                updateTodo(todo_list);
                break;

            case 4: // Delete
                deleteTodo(todo_list);
                break;
            }
        }

        suppr(todo_list);
    }
    cout << endl << "Bonne journee !" << endl;
    return 0;
}
