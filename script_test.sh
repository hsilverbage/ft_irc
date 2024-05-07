#!/bin/bash

# Définir les variables du serveur IRC
serveur="localhost"
port="8080"
canal="#example"

# Se connecter au serveur IRC
nc $serveur $port

# Envoyer les informations d'identification
echo "PASS test" >&2
echo "NICK MonPseudo" >&2
echo "USER MonPseudo 0 * :MonNom" >&2

# Rejoindre un canal
echo "JOIN $canal" >&2

# Lire et afficher les messages
while read -r ligne; do
    # Afficher les messages sur la sortie standard
    echo "$ligne"
done


