#!/bin/bash

# Fonction utilitaire pour créer l'arborescence d'un test
create_test() {
    local id=$1
    local desc=$2
    local run_cmd=$3
    local log_content=$4
    local expected_out=$5

    mkdir -p "Test$id"
    echo "$desc" > "Test$id/description"
    echo "$run_cmd" > "Test$id/run"
    echo -e "$log_content" > "Test$id/test.log"
    echo -e "$expected_out" > "Test$id/std.out"
    chmod +x "Test$id/run"
}

echo "Génération des 20 tests conformes à LogStats.cpp..."

# Variables de formatage pour éviter la répétition (basées sur LogStats.cpp)
HEADER="Classement des 10 documents les plus consultés :"
NO_RESULT="Aucun résultat trouvé pour les critères demandés."

# --- GROUPE 1 : TOP 10 ET TRI (Tests 01-04) ---
create_test "10" "Nominal : Moins de 10 documents" "../../analog test.log" \
"192.1 - - [01/Jan/2026:10:00:00 +0100] \"GET /page1.html HTTP/1.1\" 200 100 \"-\" \"-\"" \
"$HEADER
/page1.html (1 hits)"

create_test "11" "Nominal : Plus de 10 documents (limite et tri)" "../../analog test.log" \
"$(for i in {1..12}; do echo "192.1 - - [01/Jan/2026:10:00:00 +0100] \"GET /p$i.html HTTP/1.1\" 200 100 \"-\" \"-\""; done)
192.1 - - [01/Jan/2026:10:00:01 +0100] \"GET /p1.html HTTP/1.1\" 200 100 \"-\" \"-\"" \
"$HEADER
/p1.html (2 hits)
/p10.html (1 hits)
/p11.html (1 hits)
/p12.html (1 hits)
/p2.html (1 hits)
/p3.html (1 hits)
/p4.html (1 hits)
/p5.html (1 hits)
/p6.html (1 hits)
/p7.html (1 hits)"

create_test "12" "Tri décroissant par hits" "../../analog test.log" \
"192.1 - - [01/Jan/2026:10:00:00 +0100] \"GET /fav.html HTTP/1.1\" 200 100 \"-\" \"-\"
192.1 - - [01/Jan/2026:10:00:00 +0100] \"GET /fav.html HTTP/1.1\" 200 100 \"-\" \"-\"
192.1 - - [01/Jan/2026:10:00:00 +0100] \"GET /normal.html HTTP/1.1\" 200 100 \"-\" \"-\"" \
"$HEADER
/fav.html (2 hits)
/normal.html (1 hits)"

create_test "13" "Doublons d'URL identiques" "../../analog test.log" \
"192.1 - - [01/Jan/2026:10:00:00 +0100] \"GET /index.html HTTP/1.1\" 200 100 \"-\" \"-\"
192.1 - - [01/Jan/2026:10:00:00 +0100] \"GET /index.html HTTP/1.1\" 200 100 \"-\" \"-\"" \
"$HEADER
/index.html (2 hits)"

# --- GROUPE 2 : FILTRE EXTENSIONS -e (Tests 05-08) ---
create_test "14" "Exclusion basique (.js, .css, .jpg)" "../../analog -e test.log" \
"192.1 - - [01/Jan/2026:10:00:00 +0100] \"GET /script.js HTTP/1.1\" 200 100 \"-\" \"-\"
192.1 - - [01/Jan/2026:10:00:00 +0100] \"GET /style.css HTTP/1.1\" 200 100 \"-\" \"-\"
192.1 - - [01/Jan/2026:10:00:00 +0100] \"GET /page.html HTTP/1.1\" 200 100 \"-\" \"-\"" \
"$HEADER
/page.html (1 hits)"

create_test "15" "Insensibilité à la casse (Majuscules)" "../../analog -e test.log" \
"192.1 - - [01/Jan/2026:10:00:00 +0100] \"GET /PHOTO.JPG HTTP/1.1\" 200 100 \"-\" \"-\"
192.1 - - [01/Jan/2026:10:00:00 +0100] \"GET /page.html HTTP/1.1\" 200 100 \"-\" \"-\"" \
"$HEADER
/page.html (1 hits)"

create_test "16" "Exclusion totale (Reste rien)" "../../analog -e test.log" \
"192.1 - - [01/Jan/2026:10:00:00 +0100] \"GET /logo.png HTTP/1.1\" 200 100 \"-\" \"-\"" \
"$NO_RESULT"

create_test "17" "Extensions complexes (double point)" "../../analog -e test.log" \
"192.1 - - [01/Jan/2026:10:00:00 +0100] \"GET /archive.tar.gz HTTP/1.1\" 200 100 \"-\" \"-\"" \
"$HEADER
/archive.tar.gz (1 hits)"

# --- GROUPE 3 : FILTRE HORAIRE -t (Tests 09-12) ---
create_test "18" "Plage horaire [H, H+1[" "../../analog -t 14 test.log" \
"192.1 - - [01/Jan/2026:14:30:00 +0100] \"GET /a.html HTTP/1.1\" 200 100 \"-\" \"-\"
192.1 - - [01/Jan/2026:15:00:00 +0100] \"GET /b.html HTTP/1.1\" 200 100 \"-\" \"-\"" \
"Attention : seulement les hits entre 14h et 15h sont pris en compte.
$HEADER
/a.html (1 hits)"

create_test "19" "Limite basse inclusive (H:00:00)" "../../analog -t 14 test.log" \
"192.1 - - [01/Jan/2026:14:00:00 +0100] \"GET /exact.html HTTP/1.1\" 200 100 \"-\" \"-\"" \
"Attention : seulement les hits entre 14h et 15h sont pris en compte.
$HEADER
/exact.html (1 hits)"

create_test "20" "Heure sans aucune donnée" "../../analog -t 4 test.log" \
"192.1 - - [01/Jan/2026:10:00:00 +0100] \"GET /page.html HTTP/1.1\" 200 100 \"-\" \"-\"" \
"Attention : seulement les hits entre 4h et 5h sont pris en compte.
$NO_RESULT"

create_test "21" "Plage horaire minuit (0h)" "../../analog -t 0 test.log" \
"192.1 - - [01/Jan/2026:00:59:59 +0100] \"GET /nuit.html HTTP/1.1\" 200 100 \"-\" \"-\"" \
"Attention : seulement les hits entre 0h et 1h sont pris en compte.
$HEADER
/nuit.html (1 hits)"

# --- GROUPE 4 : GRAPHE -g (Tests 13-16) ---
create_test "22" "Génération GraphViz message" "../../analog -g g.dot test.log" \
"192.1 - - [01/Jan/2026:10:00:00 +0100] \"GET /cible.html HTTP/1.1\" 200 100 \"/source.html\" \"-\"" \
"Fichier .dot généré avec succès.
$HEADER
/cible.html (1 hits)"

create_test "23" "Referer local (Base URL removal)" "../../analog -g g.dot test.log" \
"192.1 - - [01/Jan/2026:10:00:00 +0100] \"GET /page.html HTTP/1.1\" 200 100 \"http://intranet-if.insa-lyon.fr/index.html\" \"-\"" \
"Fichier .dot généré avec succès.
$HEADER
/page.html (1 hits)"

create_test "24" "Referer local racine" "../../analog -g g.dot test.log" \
"192.1 - - [01/Jan/2026:10:00:00 +0100] \"GET /page.html HTTP/1.1\" 200 100 \"http://intranet-if.insa-lyon.fr\" \"-\"" \
"Fichier .dot généré avec succès.
$HEADER
/page.html (1 hits)"

create_test "25" "Referer externe (Google)" "../../analog -g g.dot test.log" \
"192.1 - - [01/Jan/2026:10:00:00 +0100] \"GET /page.html HTTP/1.1\" 200 100 \"https://www.google.com/\" \"-\"" \
"Fichier .dot généré avec succès.
$HEADER
/page.html (1 hits)"

# --- GROUPE 5 : ROBUSTESSE PARSING (Tests 17-20) ---
create_test "26" "Nettoyage paramètres URL (?)" "../../analog test.log" \
"192.1 - - [01/Jan/2026:10:00:00 +0100] \"GET /search.php?q=insa HTTP/1.1\" 200 100 \"-\" \"-\"
192.1 - - [01/Jan/2026:10:00:01 +0100] \"GET /search.php?q=cpp HTTP/1.1\" 200 100 \"-\" \"-\"" \
"$HEADER
/search.php (2 hits)"

create_test "27" "Nettoyage ancres URL (#)" "../../analog test.log" \
"192.1 - - [01/Jan/2026:10:00:00 +0100] \"GET /doc.html#section1 HTTP/1.1\" 200 100 \"-\" \"-\"" \
"$HEADER
/doc.html (1 hits)"

create_test "28" "Fichier Log vide" "../../analog test.log" "" \
"$NO_RESULT"

create_test "29" "Mix complet : -e -t -g" "../../analog -e -t 10 -g g.dot test.log" \
"192.1 - - [01/Jan/2026:10:00:00 +0100] \"GET /page.html HTTP/1.1\" 200 100 \"/\" \"-\"
192.1 - - [01/Jan/2026:10:00:01 +0100] \"GET /img.png HTTP/1.1\" 200 100 \"/\" \"-\"
192.1 - - [01/Jan/2026:11:00:00 +0100] \"GET /page2.html HTTP/1.1\" 200 100 \"/\" \"-\"" \
"Attention : seulement les hits entre 10h et 11h sont pris en compte.
Fichier .dot généré avec succès.
$HEADER
/page.html (1 hits)"

echo "Génération terminée. Lancez ./test.sh pour vérifier votre code."