#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string xor_encrypt(const string& message, const string& cle) {
    string resultat;
    char notation_caret = '^';
    for (size_t i = 0; i < message.size(); ++i) {
        char char_c = message[i] ^ cle[i % cle.size()];
        if(!isprint(char_c))
        {
            resultat += notation_caret;
        }
        resultat += char_c;
    }
    return resultat;
}

int main()
{
    string m_file = "message.txt";
    string k_file = "clef.txt";
    string c_file = "chiffre.txt";

     // Lecture du message
    string message;
    ifstream message_in(m_file);
    if (message_in.is_open()) {
        getline(message_in, message);
        message_in.close();
    } else {
        cerr << "Impossible d'ouvrir le fichier message.txt" << endl;
        return 1;
    }

    // Lecture de la clé
    string cle;
    ifstream key_in(k_file);
    if (key_in.is_open()) {
        getline(key_in, cle);
        key_in.close();
    } else {
        cerr << "Impossible d'ouvrir le fichier clef.txt" << endl;
        return 1;
    }

    string chiffre = xor_encrypt(message, cle);

     // Écriture du résultat chiffré dans le fichier
    ofstream output(c_file);
    if (output.is_open()) {
        output << chiffre;
        output.close();
        cout << "Message chiffré sauvegardé dans " << c_file << endl;
    } else {
        cerr << "Impossible d'écrire dans le fichier chiffre.txt" << endl;
        return 1;
    }

    return 0;
}
