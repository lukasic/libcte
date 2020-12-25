/**
 * Conditial Text Extension (CTE)
 *
 * V kontexte tohto modulu podmieneným textom myslíme to, že text obsahuje
 * špeciálne formulky, príkazy a zástupné znaky. Pomocou nich vieme určiť,
 * ako sa vygeneruje text.
 *
 * CTE umožňuje kontrolovať formát textu pomocou podmienok
 * a premenných. Presúvame tým možnosť generovanie textu zo zdrojového
 * kódu do samotného stringu, ktorý si vieme načítať napr. zo súboru,
 * databázy alebo zo šablóny.
 *
 * Implementované v C++ za použitia STL (Standard Template Library).
 *
 * Syntax a pravidlá:
 *  (1) Vstupný text je prezentovaný pomocou std::string, ktorý by mal
 *      umožňovať použitie akýchkoľvek 8 bitových znakov okrem NULL char.
 *  (2) Ak chceme použiť premennú, jej názov vložíme medzi {$ $}
 *      Obmedzenie: text nemôže obsahovať práve tieto sekvencie,
 *                  escapovanie nie je podporované.
 *  (3) Ak chceme použiť jednoduchú podmienku, vložíme ju medzi {% %},
 *      za tým vložíme text, ktorý sa má vykonať, ak je podmienka splnená.
 *      Niečo ako "else" nie je podporované. Koniec bloku: {% end %}
 *      - Podporované sú operátory porovnávania.
 *      - Pre špecifikovanie dátového typu pred podmienku vložíme: (typ)
 *        Podporované typy: (int), (long), (float), (double), (str)
 *        Implicitný typ: (str)
 *        (Implementácia počíta s možným rozšírením.)
 *      Obmedzenie: v texte nemôžeme použiť sekvenciu {%, %}, {% end %}
 *  (4) Podmienky môžu obsahovať premenné.
 *  (5) Podmienky je možné do seba vnorovať.
 *
 * Jednoduché príklady:
 *   "{% (int) {$ premenna $} > 5 %}Premenná je väčšia ako 5{% end %}"
 *   "{% "text" == "t e x t" %}ak to vidis, je to chyba...{% end %}"
 *
 * @author Lukáš Kasič, lukas@kasic.sk
 * @created 2015
 *
 */