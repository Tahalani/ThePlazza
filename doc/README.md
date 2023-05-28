# Documentation Plazza

Cette documentation vous servira à comprendre le fonctionnement de Plazza.

# Table des matières

- [Arguments](#Arguments)
- [Explication](#Explication)
    - [Réception](#Réception)
    - [Kitchen](#Kitchen)
    - [Cooks](#Cooks)
- [Architecture](#Architecture)
    - [Recettes configurables](#Recettes-configurables)

# Arguments

./plazza 2 5 2000

- 2 : multiplicateur de temps de cuisson

- 5 : nombre de chefs par cuisine

- 2000 : temps en millisecondes pour le réapprovisionnement des ingrédients (1 ingrédient de chaque type par réapprovisionnement)

# Explication

- Le client envoie sa commande de pizzas à l'aide du shell. 
- Le serveur reçoit la commande et la stocke dans une queue.
- Les threads de la kitchen récupèrent les commandes dans la queue et les traitent. 
- Une fois la pizza prête, la kitchen envoi la pizza au client.

## Réception

La classe `Reception` permet de recevoir les commandes du client et de les envoyer aux cuisines.

## Kitchen

La classe `Kitchen` permet de traiter les commandes et de les répartir parmi plusieurs chefs.

## Cooks

La classe `ThreadPool` permet de cuisiner les pizzas demandées par la cuisine.

# Architecture

```cpp
namespace plazza {
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
}
```

## Recettes configurables

Les recettes de pizzas sont modifiables à l'aide de fichiers de configuration, trouvables dans le dossier ``config``.