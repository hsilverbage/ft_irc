#!/bin/bash

# Demande à l'utilisateur de saisir une valeur
read valeur

# Affiche la valeur saisie par l'utilisateur

# Lancement de netcat dans un sous-shell
(
    # Exécution de netcat en arrière-plan
    echo "nc localhost 8080\r"

    # Attendre un court instant pour laisser le temps à netcat de s'exécuter
    sleep 1

    # Envoyer les commandes initiales à netcat
    {
        echo "PASS test\r"
        echo "NICK $valeur\r"
        echo "USER $valeur 0 * :$valeur\r"
    } | nc localhost 8080

    # Attendre la fin de netcat
    wait
)

# Quitter le script
exit 0