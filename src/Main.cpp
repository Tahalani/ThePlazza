/*
** EPITECH PROJECT, 2023
** theplazza
** File description:
** main
*/

#include "Configuration.hpp"
#include "Reception.hpp"
#include "PizzaRecipe.hpp"

int main(int argc, char const *argv[])
{
    try {
        plazza::Configuration config(argc, argv);
        config.setPizzaRecipes(CONF_PATH);
        std::vector<plazza::PizzaRecipe> recipes = config.getPizzaRecipes();

        for (auto &recipe : recipes) {
            std::cout << recipe.getName() << std::endl;
            std::cout << recipe.getTime() << std::endl;
        }

        for (auto &recipe : recipes) {
            for (auto &recipe_ingr : recipe.getIngredients()) {
                std::cout << recipe_ingr.second << std::endl;
            }
        }

        plazza::Reception reception(config);
        reception.run();
    } catch (plazza::ConfigurationException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (plazza::LoggerException &e) {
        std::cerr << "Logging is unavailable" << std::endl;
        return 84;
    } catch (plazza::RecipeException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}

bool operator ==(const plazza::Pizza &a, const plazza::Pizza &b) {
    return (a.type == b.type && a.size == b.size);
}
