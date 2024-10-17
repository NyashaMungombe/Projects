#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

enum class Type { // group of constants 
    Fire,
    Water,
    Grass,
    Electric,
    Ice,
    Normal


}; // Use enum for types. 

class Pokemon
{
protected:
    //variables
    string name;
    int level;
    int health;
    int maxHealth;
    Type type;
    bool knockedOut;
    int victories;
public:
    Pokemon()
    {
        //variables
        name = "";
        level = 1;
        health = 1;
        maxHealth = 1;
        type = Type::Normal;
        knockedOut = false;
    }
    //creation of pokemon
    Pokemon(string n, int l, int mh, Type t) : name(n), level(l), health(mh), maxHealth(mh), type(t), knockedOut(false), victories(0) {

    }

    void recordVictory() {
        victories;
    }

    void display()
    {
        cout << "This level " << level << " " << name << " has " << health << " hp remaining , they are a " << getType() << " type pokemon" << endl << endl;
    }
    string getType()
    {
        if (type == Type::Fire)
        {
            return "Fire";
        }
        else if (type == Type::Water)
        {
            return "Water";
        }
        else if (type == Type::Grass)
        {
            return "Grass";
        }
        else if (type == Type::Electric)
        {
            return "Electric";
        }
        else
        {
            return "Ice";
        }
    }


    void revive() {
        // Set knockedOut to false to indicate the Pokemon is no longer knocked out
        knockedOut = false;

        // Ensure the Pokemon has at least 1 health point when revived
        health = health <= 0 ? 1 : health;

        // Inform the user that the Pokemon has been revived
        cout << name << " was revived!" << endl;
    }


    void knockOut()
    {
        //Knocking out a pokemon change knockedOut to true
        knockedOut = true;
        //A knocked out pokemon can't have any health.
        health = 0;
        cout << name << " was knocked out!" << endl;
    }

    void loseHealth(int amount)
    {
        //Deducts heath from a pokemon and prints the current health reamining
        health -= amount;
        if (health <= 0)
        {// Makes sure the health doesn't become negative. Knocks out the pokemon.
            health = 0;
            knockOut();
        }
        else
        {
            cout << name << " now has " << health << " remaining " << endl;
        }
    }

    void gainHealth(int amount)
    {//Adds to a pokemon's health
        //If a pokemon goes from 0 heath, then revive it
        if (health == 0)
        {
            revive();
        }
        health += amount;
        //Makes sure the heath does not go over the max health
        if (health >= maxHealth)
        {
            health = maxHealth;
        }
        cout << name << " now has " << health << " remaining " << endl << endl;
    }

    float calculateDamageMultiplier(Type attacker, Type defender) {
        // Adding Electric and Ice types interactions
        if ((attacker == Type::Fire && defender == Type::Grass) ||
            (attacker == Type::Water && defender == Type::Fire) ||
            (attacker == Type::Grass && defender == Type::Water) ||
            (attacker == Type::Electric && defender == Type::Water) ||
            (attacker == Type::Ice && defender == Type::Grass)) {
            return 2.0; // Super effective
        }
        if ((attacker == Type::Fire && defender == Type::Water) ||
            (attacker == Type::Water && defender == Type::Grass) ||
            (attacker == Type::Grass && defender == Type::Fire) ||
            (attacker == Type::Electric && defender == Type::Grass) ||
            (attacker == Type::Ice && defender == Type::Fire) ||
            (attacker == Type::Ice && defender == Type::Water)) {
            return 0.5;
        }
        return 1.0; // Neutral effectiveness
    }


    void attack(Pokemon& target) {
        if (knockedOut) {
            cout << name << " can't attack because it is knocked out." << endl;
            return;
        }

        // level efecttivesness calculator
        float multiplier = calculateDamageMultiplier(type, target.type);
        int damage = (1 + rand() % level) * multiplier;
        string effectiveness;

        if (multiplier == 2.0) effectiveness = "It's super effective!";
        else if (multiplier == 0.5) effectiveness = "It's not very effective.";
        else effectiveness = "";

        cout << name << " attacked " << target.name << " for " << damage << " damage. " << effectiveness << endl;
        target.loseHealth(damage);
        cout << endl;
    }
    string getName()
    {
        return name;
    }
    bool isKnockedOut()
    {
        return knockedOut;
    }
    int getLevel() {
        return level;
    }

    int getHealth() {
        return health;
    }
    int getMaxHealth() {
        return maxHealth;
    }

    int getVictories() {
        return victories;
    }



};
class Trainer : public Pokemon //inheritance
{
private:
    //A trainer has a one pokemon, a number of potions and a name. When the trainer gets created, they are assigned a pokemon
    Pokemon pokemon;
    string name;
    int numOfPotions;

public:
    vector<Pokemon> pokemons;


    Trainer(Pokemon p, string n, int pot)
    {
        pokemon = p;
        name = n;
        numOfPotions = pot;
    }
    void addPokemon(const Pokemon& pokemon) {
        pokemons.push_back(pokemon);
    }
    void display()
    {//display the trainer name and thier pokemon to the screen
        cout << "Trainer " << name << " has the pokemon " << pokemon.getName() << endl;
    }

    void usePotion()
    {//Uses a potion on pokemon, assuming you have at least one potion.

        if (numOfPotions > 0)
        {
            cout << name << " Used a potion ";
            //decrement number of potions
            numOfPotions -= 1;
            //a potion restores 5 health;
            pokemon.gainHealth(5);
        }
        else
        {
            cout << "You do not have any potions" << endl;
        }

    }

    void attackOtherTrainer(Trainer& otherTrainer) //trainer is passed by reference
    {//attack the other trainers pokemon;
        pokemon.attack(otherTrainer.pokemon);
    }
    Pokemon getPokemon() //return the pokemon object
    {
        return pokemon;
    }
    string getName() //return the trainers name
    {
        return name;
    }
    int getNumOfPotions()// return the number of potions, this is used as a check alongside if the pokemon is knocked out
    {
        return numOfPotions;
    }

    bool checkIfPokemonKnockedOut() {
        if (pokemon.isKnockedOut()) {
            cout << "Your Pokemon has been knocked out. Do you want to quit or continue? enter quit  ";

            char choice;
            cin >> choice;
            if (choice == 'q' || choice == 'Q') {
                return 0;
            }
            else if (choice == 'c' || choice == 'C') {
                // If the trainer wants to continue, they should get a new Pokemon
                cout << "Please choose a new Pokemon: ";
                int index;
                cin >> index;
                pokemon = pokemons[index];
                cout << endl;
                return true;
            }
            else {
                cout << "You have quit" << endl;

                return false;
            }
        }
        return false;
    }
};
//trainers are passed by reference, so that the values are operated on correctly.
void getBattleAction(Trainer& trainer1, Trainer& trainer2) {
    // Check if trainer1's Pokemon is knocked out
    if (trainer1.checkIfPokemonKnockedOut()) {
        cout << "battle ended" << endl;
    }

    int trainerInput;
    cout << trainer1.getName() << ": fight (1) or use potion (2): ";
    cin >> trainerInput;

    // Consume the remaining newline character
    cin.ignore();

    // Check if trainer1's Pokemon is knocked out after getting the input
    if (trainer1.checkIfPokemonKnockedOut()) {
        return;
    }

    switch (trainerInput) {
    case 1:
        trainer1.attackOtherTrainer(trainer2);
        break;
    case 2:
        trainer1.usePotion();
        break;
    default:
        break;
    }
}

void saveMatchData(Trainer& winner, Trainer& loser) {
    // Open the file in append mode
    ofstream file("player_data.txt", ios::app);

    // Check if the file is open
    if (file.is_open()) {
        // Write the match data
        file << "Match Result:\n";
        file << "Winner: " << winner.getName() << ", Pokémon: " << winner.getPokemon().getName() << "\n";
        file << "Loser: " << loser.getName() << ", Pokémon: " << loser.getPokemon().getName() << "\n";
        file << "---------------------------------\n";

        // Save the winner's Pokemon data
        file << "Winner's Pokemon Data:\n";
        file << "Name: " << winner.getPokemon().getName() << "\n";
        file << "Level: " << winner.getPokemon().getLevel() << "\n";
        file << "HP: " << winner.getPokemon().getHealth() << "/" << winner.getPokemon().getMaxHealth() << "\n";
        file << "Type: " << winner.getPokemon().getType() << "\n";
        file << "Victories: " << winner.getPokemon().getVictories() + 1 << "\n";
        file << "---------------------------------\n";

        // Save the loser's Pokemon data
        file << "Loser's Pokemon Data:\n";
        file << "Name: " << loser.getPokemon().getName() << "\n";
        file << "Level: " << loser.getPokemon().getLevel() << "\n";
        file << "HP: " << loser.getPokemon().getHealth() << "/" << loser.getPokemon().getMaxHealth() << "\n";
        file << "Type: " << loser.getPokemon().getType() << "\n";
        file << "Victories: " << loser.getPokemon().getVictories() << "\n";
        file << "---------------------------------\n";

        // Close the file
        file.close();
    }
    else {
        cout << "Unable to open file for writing.\n";
    }
}



int main()
{// objects 
    srand(time(0));
    Pokemon charmander("Charmander", 10, 50, Type::Fire); // name, the level, the health and the type
    Pokemon squirtle("Squirtle", 12, 60, Type::Water);
    Pokemon bulbasaur("Bulbasaur", 8, 40, Type::Grass);
    Pokemon pikachu("Pikachu", 11, 55, Type::Electric);
    Pokemon lapras("Lapras", 10, 70, Type::Ice);
    Pokemon eevee("Eevee", 7, 55, Type::Normal);
    Pokemon jolteon("Jolteon", 9, 45, Type::Electric);
    Pokemon flareon("Flareon", 10, 65, Type::Fire);
    Pokemon vaporeon("Vaporeon", 10, 70, Type::Water);
    Pokemon espeon("Espeon", 12, 60, Type::Normal);
    Pokemon umbreon("Umbreon", 11, 70, Type::Normal);
    Pokemon leafeon("Leafeon", 8, 60, Type::Grass);
    Pokemon glaceon("Glaceon", 9, 60, Type::Ice);
    Pokemon sylveon("Sylveon", 12, 65, Type::Normal);
    Pokemon magikarp("Magikarp", 5, 20, Type::Water);
    Pokemon gyarados("Gyarados", 18, 90, Type::Water);

    vector<Pokemon> pokemons = {
         charmander, squirtle, bulbasaur, pikachu, lapras,
         eevee, jolteon, flareon, vaporeon, espeon,
         umbreon, leafeon, glaceon, sylveon, magikarp, gyarados
    };

    //invite trainers to enter thier names
    cout << "Welcome to pokemon battle simulator" << endl;
    cout << "Trainer 1: Please enter your name " << endl;
    string trainer1name;
    getline(cin, trainer1name);

    Trainer trainer1(pokemons[rand() % pokemons.size()], trainer1name, 5); //randomize

    cout << "Trainer 2: Please enter your name " << endl;
    string trainer2name;
    getline(cin, trainer2name);

    cout << endl;

    Trainer trainer2(pokemons[rand() % pokemons.size()], trainer2name, 5);
    //display trainer information to the screen
    trainer1.display();
    trainer1.getPokemon().display();

    trainer2.display();
    trainer2.getPokemon().display();
    bool stillBattling = true;






    while (stillBattling) {

        // Trainer 1's turn
        if (!trainer1.getPokemon().isKnockedOut()) {
            getBattleAction(trainer1, trainer2);

        }
        else if (!trainer1.checkIfPokemonKnockedOut()) {
            cout << trainer1.getName() << " has no more capable Pokemon. " << trainer2.getName() << " wins!" << endl;
            break;
        }

        // Check if trainer2's Pokémon is knocked out after trainer1's action
        if (trainer2.getPokemon().isKnockedOut() && !trainer2.checkIfPokemonKnockedOut()) {
            cout << trainer2.getName() << " has no more capable Pokemon. " << trainer1.getName() << " wins!" << endl;
            break;
        }

        // Trainer 2's turn
        if (!trainer2.getPokemon().isKnockedOut()) {
            getBattleAction(trainer2, trainer1);
        }
        else if (!trainer2.checkIfPokemonKnockedOut()) {
            cout << trainer2.getName() << " has no more capable Pokemon. " << trainer1.getName() << " wins!" << endl;
            break;
        }

        // Check if trainer1's Pokémon is knocked out after trainer2's action
        if (trainer1.getPokemon().isKnockedOut() && !trainer1.checkIfPokemonKnockedOut()) {
            cout << trainer1.getName() << " has no more capable Pokemon. " << trainer2.getName() << " wins!" << endl;
            break;


        }

        // Determine the winner and loser for demonstration purposes
        Trainer winner = trainer1; // Assume trainer1 is the winner
        Trainer loser = trainer2;  // Assume trainer2 is the loser

        // Save the match data
        saveMatchData(winner, loser);


    }
