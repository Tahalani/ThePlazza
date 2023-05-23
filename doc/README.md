# Documentation Plazza

Cette documentation vous servira à comprendre le fonctionnement de Plazza.

# Table des matières

- [Arguments](#Arguments)
- [Explication](#Explication)
    - [Réception](#Réception)
    - [Client](#Client)
    - [Kitchen](#Kitchen)
    - [Variables](#variables)
- [Architecture et structure du code](#Architecture-et-structure-du-code)
    - [Pizza Generique](#Pizza-Generique)

# Arguments

./plazza 2 5 2000

- 2 : multiplicateur de temps de cuisson

- 5 : nombre de cooks par kitchen

- 2000 : temps en ms pour la création d'une pizza

# Explication

Le client envoi sa commande de pizza grace au shell. Le serveur reçoit la commande et la stocke dans une queue. Les threads de la kitchen récupèrent les commandes dans la queue et les traitent. Une fois la pizza prête, la kitchen envoi la pizza au client.

## Réception

La classe `Reception` permet de recevoir les commandes du client et de les stocker dans une queue.

## Client

La classe `Client` permet d'envoyer les commandes au serveur.

## Kitchen

La classe `Kitchen` permet de traiter les commandes et de les envoyer au client.

## Variables

- std::vector<std::string> _pizza : contient les pizzas

# Architecture et structure du code

namespace plazza {
    enum class PizzaType {
        Regina,
        Margarita,
        Americana,
        Fantasia
    };

    enum class PizzaSize {
        S,
        M,
        L,
        XL,
        XXL
    };

    enum class Ingredients {
        Dough,
        Tomato,
        Gruyere,
        Ham,
        Mushrooms,
        Steak,
        Eggplant,
        GoatCheese,
        ChiefLove
    };

    struct PizzaCommand {
        PizzaType type;
        PizzaSize size;
        int quantity;
    };

    struct PizzaTaken {
        PizzaType type;
        PizzaSize size;
    };
}


## Pizza Generique

Pour la pizza générique, nous avons utilisé un enum class pour les types de pizza, les tailles de pizza et les ingrédients. Nous avons aussi utilisé une structure pour les commandes de pizza et une autre pour les pizzas prises. Ainsi, grace a un fichier de conf, nous pouvons facilement ajouter des nouvelles pizzas.
